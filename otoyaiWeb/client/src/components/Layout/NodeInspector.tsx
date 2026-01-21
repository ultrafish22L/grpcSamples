import { useMemo } from 'react';
import { useStore } from '../../store/useStore';
import { AIEndpointNodeData, ImageNodeData, VideoNodeData } from '../../types';
import { inferEndpointSchema, InputParameter } from '../../utils/endpointSchema';
import { logger } from '../../services/logger';
import styles from './NodeInspector.module.css';

export function NodeInspector() {
  const { nodes, updateNode } = useStore();
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
          <MediaInspector node={selectedNode} updateNode={updateNode} type="image" />
        )}
        {selectedNode.type === 'video' && (
          <MediaInspector node={selectedNode} updateNode={updateNode} type="video" />
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
}

function MediaInspector({ node, type }: MediaInspectorProps) {
  const data = node.data as ImageNodeData | VideoNodeData;
  const { items = [] } = data;

  return (
    <>
      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>{type === 'image' ? 'Image' : 'Video'} Node</h3>
        <div className={styles.description}>
          {items.length} {type === 'image' ? 'image' : 'video'}
          {items.length !== 1 ? 's' : ''} loaded
        </div>
      </div>

      <div className={styles.section}>
        <h3 className={styles.sectionTitle}>Items</h3>
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

    case 'number':
      return (
        <input
          type="number"
          className={styles.numberInput}
          value={(value as number) ?? (input.default as number) ?? ''}
          onChange={(e) => onChange(parseFloat(e.target.value) || 0)}
          min={input.min}
          max={input.max}
          step={input.step || 1}
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
