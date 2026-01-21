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
          <AIEndpointInspector node={selectedNode} updateNode={updateNode} nodes={nodes} edges={edges} />
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
  nodes: AppNode[];
  edges: any[];
}

function AIEndpointInspector({ node, updateNode, nodes, edges }: AIEndpointInspectorProps) {
  const data = node.data as AIEndpointNodeData;
  const { endpoint, parameters = {}, isExecuting = false } = data;
  const schema = useMemo(() => inferEndpointSchema(endpoint), [endpoint]);

  // Find connected inputs for each parameter
  const connectedInputs = useMemo(() => {
    const connections: Record<string, any> = {};
    
    // Find all edges targeting this node
    const incomingEdges = edges.filter((edge) => edge.target === node.id);
    
    for (const edge of incomingEdges) {
      const sourceNode = nodes.find((n) => n.id === edge.source);
      if (!sourceNode) continue;
      
      const targetHandle = edge.targetHandle; // This is the input parameter name
      if (!targetHandle) continue;
      
      // Get the source data based on node type
      let sourceData: any = null;
      
      if (sourceNode.type === 'textInput') {
        sourceData = {
          type: 'text',
          value: (sourceNode.data as TextInputNodeData).value || '',
          nodeType: 'textInput',
        };
      } else if (sourceNode.type === 'image') {
        const imageData = sourceNode.data as ImageNodeData;
        const handleIndex = parseInt(edge.sourceHandle?.replace('output-', '') || '0');
        const item = imageData.items[handleIndex];
        sourceData = {
          type: 'image',
          item: item,
          nodeType: 'image',
        };
      } else if (sourceNode.type === 'video') {
        const videoData = sourceNode.data as VideoNodeData;
        const handleIndex = parseInt(edge.sourceHandle?.replace('output-', '') || '0');
        const item = videoData.items[handleIndex];
        sourceData = {
          type: 'video',
          item: item,
          nodeType: 'video',
        };
      }
      
      if (sourceData) {
        connections[targetHandle] = sourceData;
      }
    }
    
    return connections;
  }, [edges, node.id, nodes]);

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
              {renderControl(
                input,
                parameters[input.name],
                (value) => handleParameterChange(input.name, value),
                connectedInputs[input.name]
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
  const [expandedItems, setExpandedItems] = useState<Set<string>>(new Set());

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
          id: `connected-${edge.id}`,
          nodeId: sourceNode.id,
          nodeType: sourceNode.type,
          handleId: edge.sourceHandle,
          data: sourceData,
          isConnected: true,
        };
      })
      .filter((conn) => conn !== null);
  }, [edges, node.id, nodes]);

  const toggleItem = useCallback((itemId: string) => {
    setExpandedItems((prev) => {
      const next = new Set(prev);
      if (next.has(itemId)) {
        next.delete(itemId);
      } else {
        next.add(itemId);
      }
      return next;
    });
  }, []);

  // Combine connected inputs and local items
  const allItems = [
    ...connectedInputs.map((conn) => ({
      id: conn.id,
      name: conn.data?.name || 'Connected item',
      preview: conn.data?.preview,
      url: conn.data?.url,
      isConnected: true,
      nodeType: conn.nodeType as string | undefined,
    })),
    ...items.map((item, index) => ({
      id: item.id,
      name: item.name || `Item ${index + 1}`,
      preview: item.preview,
      url: item.url,
      isConnected: false,
      nodeType: undefined as string | undefined,
    })),
  ];

  return (
    <>
      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>{type === 'image' ? 'Image' : 'Video'} Node</h3>
        <div className={styles.description}>
          {items.length} local • {connectedInputs.length} connected
        </div>
      </div>

      {/* Single List of Collapsible Items */}
      <div className={styles.section}>
        <div className={styles.inspectorMediaList}>
          {allItems.map((item, index) => {
            const isExpanded = expandedItems.has(item.id);
            return (
              <div key={item.id} className={styles.inspectorMediaItem}>
                <div 
                  className={styles.inspectorMediaHeader}
                  onClick={() => toggleItem(item.id)}
                >
                  <button className={styles.collapseButton}>
                    {isExpanded ? '▼' : '▶'}
                  </button>
                  <div className={styles.inspectorMediaIndex}>{index + 1}</div>
                  <div className={styles.inspectorMediaName}>
                    {item.name}
                    {item.isConnected && item.nodeType && (
                      <span className={styles.connectedBadgeInline}>
                        🔗 {item.nodeType}
                      </span>
                    )}
                  </div>
                </div>
                
                {isExpanded && (item.preview || item.url) && (
                  <div className={styles.inspectorMediaPreview}>
                    {type === 'image' ? (
                      <img
                        src={item.preview || item.url}
                        alt={item.name}
                        className={styles.inspectorMediaImage}
                      />
                    ) : (
                      <video
                        src={item.preview || item.url}
                        className={styles.inspectorMediaVideo}
                        controls
                        muted
                      />
                    )}
                  </div>
                )}
              </div>
            );
          })}
          
          {allItems.length === 0 && (
            <div className={styles.emptyMediaList}>
              No items or connections
            </div>
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
  onChange: (value: unknown) => void,
  connectedInput?: any
) {
  switch (input.type) {
    case 'text':
      // Show connected text if available
      if (connectedInput?.type === 'text') {
        return (
          <div className={styles.connectedTextDisplay}>
            <div className={styles.connectedBadge}>
              ✓ Connected from text node
            </div>
            <textarea
              className={styles.textInput}
              value={connectedInput.value}
              readOnly
              rows={3}
              style={{ opacity: 0.8, cursor: 'not-allowed' }}
            />
          </div>
        );
      }
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
      // Show connected image if available
      if (connectedInput?.type === 'image' && connectedInput.item) {
        const item = connectedInput.item;
        return (
          <div className={styles.connectedMediaDisplay}>
            <div className={styles.connectedBadge}>
              ✓ Connected from image node
            </div>
            {(item.preview || item.url) && (
              <img
                src={item.preview || item.url}
                alt={item.name || 'Connected image'}
                className={styles.connectedMediaPreview}
              />
            )}
            <div className={styles.connectedMediaName}>
              {item.name || 'Untitled image'}
            </div>
          </div>
        );
      }
      return (
        <div className={styles.mediaPlaceholder}>
          Connect via input pin
        </div>
      );

    case 'video':
      // Show connected video if available
      if (connectedInput?.type === 'video' && connectedInput.item) {
        const item = connectedInput.item;
        return (
          <div className={styles.connectedMediaDisplay}>
            <div className={styles.connectedBadge}>
              ✓ Connected from video node
            </div>
            {(item.preview || item.url) && (
              <video
                src={item.preview || item.url}
                className={styles.connectedMediaPreview}
                controls
                muted
              />
            )}
            <div className={styles.connectedMediaName}>
              {item.name || 'Untitled video'}
            </div>
          </div>
        );
      }
      return (
        <div className={styles.mediaPlaceholder}>
          Connect via input pin
        </div>
      );

    case 'audio':
      return (
        <div className={styles.mediaPlaceholder}>
          {connectedInput ? '✓ Connected via pin' : 'Connect via input pin'}
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
