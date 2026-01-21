import { useMemo, useState, useCallback } from 'react';
import { useStore } from '../../store/useStore';
import { AIEndpointNodeData, ImageNodeData, VideoNodeData, TextInputNodeData, AppNode } from '../../types';
import { inferEndpointSchema, InputParameter } from '../../utils/endpointSchema';
import { logger } from '../../services/logger';
import styles from './NodeInspector.module.css';

export function NodeInspector() {
  const { nodes, edges, updateNode } = useStore();
  const selectedNodes = nodes.filter((n) => n.selected);
  const selectedNode = selectedNodes.length === 1 ? selectedNodes[0] : null;

  if (!selectedNode) {
    return (
      <div className={styles.inspector}>
        <div className={styles.emptyState}>
          <div className={styles.emptyIcon}>🔍</div>
          <div className={styles.emptyText}>Select a node to inspect</div>
        </div>
      </div>
    );
  }

  return (
    <div className={styles.inspector}>
      <div className={styles.inspectorHeader}>
        <h2 className={styles.inspectorTitle}>Node Inspector</h2>
        <div className={styles.nodeType}>{selectedNode.type}</div>
      </div>

      <div className={styles.inspectorContent}>
        {selectedNode.type === 'aiEndpoint' && (
          <AIEndpointInspector node={selectedNode} updateNode={updateNode} />
        )}
        {selectedNode.type === 'image' && (
          <MediaInspector node={selectedNode} updateNode={updateNode} type="image" nodes={nodes} edges={edges} />
        )}
        {selectedNode.type === 'video' && (
          <MediaInspector node={selectedNode} updateNode={updateNode} type="video" nodes={nodes} edges={edges} />
        )}
        {selectedNode.type === 'textInput' && (
          <TextInputInspector node={selectedNode} updateNode={updateNode} />
        )}
      </div>
    </div>
  );
}

interface AIEndpointInspectorProps {
  node: {
    id: string;
    data: unknown;
  };
  updateNode: (id: string, data: Partial<unknown>) => void;
}

function AIEndpointInspector({ node, updateNode }: AIEndpointInspectorProps) {
  const data = node.data as AIEndpointNodeData;
  const { endpoint, parameters = {}, isExecuting = false } = data;
  const schema = useMemo(() => inferEndpointSchema(endpoint), [endpoint]);

  const handleParameterChange = (paramName: string, value: unknown) => {
    const newParams = { ...parameters, [paramName]: value };
    updateNode(node.id, { parameters: newParams });
    logger.debug('Parameter updated', { node: node.id, param: paramName, value });
  };

  const handleCreate = async () => {
    logger.info('Creating with AI endpoint', { endpoint: endpoint.endpoint_id, parameters });
    updateNode(node.id, { isExecuting: true });

    // TODO: Implement actual API call
    setTimeout(() => {
      updateNode(node.id, {
        isExecuting: false,
        result: { success: true, message: 'Mock result (API not implemented)' },
      });
      logger.info('AI endpoint execution complete', { endpoint: endpoint.endpoint_id });
    }, 2000);
  };

  return (
    <>
      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>{endpoint.title}</h3>
        <div className={styles.sectionSubtitle}>{endpoint.vendor}</div>
        <div className={styles.description}>{endpoint.description}</div>
      </div>

      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>Parameters</h3>
        <div className={styles.parameterList}>
          {schema.inputs.map((input) => (
            <div key={input.name} className={styles.parameterItem}>
              <label className={styles.parameterLabel} title={input.description}>
                {input.label}
                {input.required && <span className={styles.required}>*</span>}
              </label>
              {renderControl(input, parameters[input.name], (value) =>
                handleParameterChange(input.name, value)
              )}
              {input.description && (
                <div className={styles.parameterHint}>{input.description}</div>
              )}
            </div>
          ))}
        </div>
      </div>

      <div className={styles.section}>
        <button
          className={styles.createButton}
          onClick={handleCreate}
          disabled={isExecuting}
        >
          {isExecuting ? '⏳ Creating...' : '▶ Create'}
        </button>
      </div>
    </>
  );
}

interface MediaInspectorProps {
  node: {
    id: string;
    data: unknown;
  };
  updateNode: (id: string, data: Partial<unknown>) => void;
  type: 'image' | 'video';
  nodes: AppNode[];
  edges: any[];
}

function MediaInspector({ node, type, nodes, edges }: MediaInspectorProps) {
  const data = node.data as ImageNodeData | VideoNodeData;
  const { items = [] } = data;
  const [previewExpanded, setPreviewExpanded] = useState(true);

  // Find connected input sources
  const connectedInputs = useMemo(() => {
    return edges
      .filter((edge) => edge.target === node.id)
      .map((edge) => {
        const sourceNode = nodes.find((n) => n.id === edge.source);
        if (!sourceNode) return null;
        
        // Get the source data based on node type
        let sourceData: any = null;
        if (sourceNode.type === 'image' || sourceNode.type === 'video') {
          const mediaData = sourceNode.data as ImageNodeData | VideoNodeData;
          const handleIndex = parseInt(edge.sourceHandle?.replace('output-', '') || '0');
          sourceData = mediaData.items[handleIndex];
        }
        
        return {
          nodeId: sourceNode.id,
          nodeType: sourceNode.type,
          handleId: edge.sourceHandle,
          data: sourceData,
        };
      })
      .filter((conn) => conn !== null);
  }, [edges, node.id, nodes]);

  const togglePreview = useCallback(() => {
    setPreviewExpanded(!previewExpanded);
  }, [previewExpanded]);

  return (
    <>
      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>{type === 'image' ? 'Image' : 'Video'} Node</h3>
        <div className={styles.description}>
          {items.length} {type === 'image' ? 'image' : 'video'}
          {items.length !== 1 ? 's' : ''} loaded
          {connectedInputs.length > 0 && (
            <span> • {connectedInputs.length} connected input{connectedInputs.length !== 1 ? 's' : ''}</span>
          )}
        </div>
      </div>

      {/* Preview Section with Collapse */}
      <div className={styles.section}>
        <div className={styles.previewHeader}>
          <h3 className={styles.sectionTitle}>Preview</h3>
          <button
            className={styles.collapseButton}
            onClick={togglePreview}
            title={previewExpanded ? 'Collapse' : 'Expand'}
          >
            {previewExpanded ? '▼' : '▶'}
          </button>
        </div>

        {previewExpanded && (
          <div className={styles.previewArea}>
            {/* Connected Inputs */}
            {connectedInputs.length > 0 && (
              <div className={styles.connectedInputs}>
                <h4 className={styles.subsectionTitle}>Connected Inputs</h4>
                <div className={styles.connectedList}>
                  {connectedInputs.map((conn, index) => (
                    <div key={index} className={styles.connectedItem}>
                      <div className={styles.connectedIcon}>
                        {conn.nodeType === 'image' ? '🖼️' : conn.nodeType === 'video' ? '🎬' : '📎'}
                      </div>
                      <div className={styles.connectedInfo}>
                        <div className={styles.connectedNodeId}>
                          {conn.nodeType} node
                        </div>
                        {conn.data && (conn.data.preview || conn.data.url) && (
                          <div className={styles.connectedPreview}>
                            {type === 'image' ? (
                              <img
                                src={conn.data.preview || conn.data.url}
                                alt={conn.data.name || 'Connected'}
                                className={styles.connectedThumbnail}
                              />
                            ) : (
                              <video
                                src={conn.data.preview || conn.data.url}
                                className={styles.connectedThumbnail}
                                muted
                              />
                            )}
                          </div>
                        )}
                      </div>
                    </div>
                  ))}
                </div>
              </div>
            )}

            {/* Local Items */}
            {items.length > 0 && (
              <div className={styles.localItems}>
                <h4 className={styles.subsectionTitle}>Local Items</h4>
                <div className={styles.mediaPreviewGrid}>
                  {items.map((item, index) => (
                    <div key={item.id} className={styles.mediaPreviewItem}>
                      {type === 'image' ? (
                        (item.preview || item.url) && (
                          <img
                            src={item.preview || item.url}
                            alt={item.name || `Image ${index + 1}`}
                            className={styles.mediaThumbnail}
                          />
                        )
                      ) : (
                        (item.preview || item.url) && (
                          <video
                            src={item.preview || item.url}
                            className={styles.mediaThumbnail}
                            controls
                            muted
                          />
                        )
                      )}
                      <div className={styles.mediaPreviewLabel}>
                        {index + 1}. {item.name || 'Untitled'}
                      </div>
                    </div>
                  ))}
                </div>
              </div>
            )}

            {items.length === 0 && connectedInputs.length === 0 && (
              <div className={styles.emptyPreview}>
                No items or connections
              </div>
            )}
          </div>
        )}
      </div>

      {/* Items List Section */}
      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>Items List</h3>
        <div className={styles.mediaList}>
          {items.map((item, index) => (
            <div key={item.id} className={styles.mediaListItem}>
              <div className={styles.mediaItemNumber}>{index + 1}</div>
              <div className={styles.mediaItemInfo}>
                <div className={styles.mediaItemName}>{item.name || 'Untitled'}</div>
                {item.url && (
                  <div className={styles.mediaItemUrl}>
                    {item.url.substring(0, 40)}...
                  </div>
                )}
              </div>
            </div>
          ))}
          {items.length === 0 && (
            <div className={styles.emptyMediaList}>No items loaded</div>
          )}
        </div>
      </div>
    </>
  );
}

interface TextInputInspectorProps {
  node: {
    id: string;
    data: unknown;
  };
  updateNode: (id: string, data: Partial<unknown>) => void;
}

function TextInputInspector({ node, updateNode }: TextInputInspectorProps) {
  const data = node.data as TextInputNodeData;
  const { value = '' } = data;

  const handleValueChange = (newValue: string) => {
    updateNode(node.id, { value: newValue });
    logger.debug('Text node value updated', { node: node.id, length: newValue.length });
  };

  return (
    <>
      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>Text Input Node</h3>
        <div className={styles.description}>
          {value.length} character{value.length !== 1 ? 's' : ''}
        </div>
      </div>

      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>Text Content</h3>
        <textarea
          className={styles.textInput}
          value={value}
          onChange={(e) => handleValueChange(e.target.value)}
          placeholder="Enter text..."
          rows={10}
          style={{ width: '100%', resize: 'vertical' }}
        />
      </div>
    </>
  );
}

function renderControl(
  input: InputParameter,
  value: unknown,
  onChange: (value: unknown) => void
) {
  switch (input.type) {
    case 'text':
      return (
        <textarea
          className={styles.textInput}
          value={(value as string) || ''}
          onChange={(e) => onChange(e.target.value)}
          placeholder={input.description}
          rows={3}
        />
      );

    case 'integer':
      return (
        <input
          type="number"
          className={styles.numberInput}
          value={(value as number) ?? (input.default as number) ?? ''}
          onChange={(e) => onChange(parseInt(e.target.value) || 0)}
          min={input.min}
          max={input.max}
          step={1}
          placeholder={input.description}
        />
      );

    case 'float':
      return (
        <input
          type="number"
          className={styles.numberInput}
          value={(value as number) ?? (input.default as number) ?? ''}
          onChange={(e) => onChange(parseFloat(e.target.value) || 0)}
          min={input.min}
          max={input.max}
          step={input.step || 0.1}
          placeholder={input.description}
        />
      );

    case 'select':
      return (
        <select
          className={styles.selectInput}
          value={(value as string) ?? (input.default as string) ?? ''}
          onChange={(e) => onChange(e.target.value)}
        >
          <option value="">Select...</option>
          {input.options?.map((opt) => (
            <option key={opt} value={opt}>
              {opt}
            </option>
          ))}
        </select>
      );

    case 'boolean':
      return (
        <label className={styles.checkboxLabel}>
          <input
            type="checkbox"
            checked={(value as boolean) || false}
            onChange={(e) => onChange(e.target.checked)}
          />
          <span>Enable</span>
        </label>
      );

    case 'image':
    case 'video':
    case 'audio':
      return (
        <div className={styles.mediaPlaceholder}>
          {value ? '✓ Connected via pin' : 'Connect via input pin'}
        </div>
      );

    default:
      return (
        <input
          type="text"
          className={styles.textInput}
          value={(value as string) || ''}
          onChange={(e) => onChange(e.target.value)}
        />
      );
  }
}
