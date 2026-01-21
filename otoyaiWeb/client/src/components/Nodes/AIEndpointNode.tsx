import { memo, useState, useCallback, useMemo, useEffect } from 'react';
import { Handle, Position, NodeProps, useReactFlow } from '@xyflow/react';
import { AIEndpointNodeData } from '../../types';
import { inferEndpointSchema, isMediaInput, InputParameter } from '../../utils/endpointSchema';
import { logger } from '../../services/logger';
import styles from './nodes.module.css';

function AIEndpointNodeComponent({ data, selected, id }: NodeProps) {
  const typedData = data as unknown as AIEndpointNodeData;
  const { endpoint, parameters = {}, isExecuting = false } = typedData;
  const { updateNodeData } = useReactFlow();
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);

  const schema = useMemo(() => inferEndpointSchema(endpoint), [endpoint]);

  // Initialize parameters with defaults
  useEffect(() => {
    const defaultParams: Record<string, unknown> = {};
    schema.inputs.forEach((input) => {
      if (input.default !== undefined && parameters[input.name] === undefined) {
        defaultParams[input.name] = input.default;
      }
    });
    if (Object.keys(defaultParams).length > 0) {
      updateNodeData(id, { parameters: { ...parameters, ...defaultParams } });
    }
  }, [schema, id, parameters, updateNodeData]);

  const handleParameterChange = useCallback(
    (paramName: string, value: unknown) => {
      const newParams = { ...parameters, [paramName]: value };
      updateNodeData(id, { parameters: newParams });
      logger.debug('Parameter updated', { node: id, param: paramName, value });
    },
    [id, parameters, updateNodeData]
  );

  const handleCreate = useCallback(async () => {
    logger.info('Creating with AI endpoint', { endpoint: endpoint.endpoint_id, parameters });
    updateNodeData(id, { isExecuting: true });
    
    // TODO: Implement actual API call
    setTimeout(() => {
      updateNodeData(id, { 
        isExecuting: false,
        result: { success: true, message: 'Mock result (API not implemented)' }
      });
      logger.info('AI endpoint execution complete', { endpoint: endpoint.endpoint_id });
    }, 2000);
  }, [endpoint, parameters, id, updateNodeData]);

  const handleContextMenu = useCallback((e: React.MouseEvent) => {
    e.preventDefault();
    setContextMenu({ x: e.clientX, y: e.clientY });
  }, []);

  const closeContextMenu = useCallback(() => {
    setContextMenu(null);
  }, []);

  useEffect(() => {
    if (contextMenu) {
      const handleClick = () => closeContextMenu();
      document.addEventListener('click', handleClick);
      return () => document.removeEventListener('click', handleClick);
    }
  }, [contextMenu, closeContextMenu]);

  const handleDelete = useCallback(() => {
    logger.info('Delete node requested', { id });
    // TODO: Implement node deletion
    closeContextMenu();
  }, [id, closeContextMenu]);

  const handleDuplicate = useCallback(() => {
    logger.info('Duplicate node requested', { id });
    // TODO: Implement node duplication
    closeContextMenu();
  }, [id, closeContextMenu]);

  // Calculate handle positions
  const handleSpacing = 40; // pixels between handles
  const headerHeight = 80; // approximate header height

  return (
    <>
      <div 
        className={`${styles.baseNode} ${styles.aiEndpointNode} ${selected ? styles.selected : ''}`}
        onContextMenu={handleContextMenu}
      >
        <div className={styles.nodeHeader}>
          <h3 className={styles.nodeTitle} title={endpoint.description}>
            {endpoint.title}
          </h3>
          <div className={styles.nodeVendor}>{endpoint.vendor}</div>
        </div>

        {/* Input Handles and Parameters */}
        <div className={styles.parameterList}>
          {schema.inputs.map((input, index) => {
            const handleTop = headerHeight + index * handleSpacing;
            const isMedia = isMediaInput(input.type);
            
            return (
              <div key={input.name} className={styles.parameterItem}>
                <Handle
                  type="target"
                  position={Position.Left}
                  id={input.name}
                  className={isMedia ? styles.handleOpen : styles.handleFilled}
                  style={{ top: handleTop }}
                  title={input.description}
                />
                
                <div className={styles.parameterControl}>
                  <label className={styles.parameterLabel} title={input.description}>
                    {input.label}
                    {input.required && <span className={styles.required}>*</span>}
                  </label>
                  
                  {renderControl(input, parameters[input.name], handleParameterChange)}
                </div>
              </div>
            );
          })}
        </div>

        {/* Create Button */}
        <button
          className={styles.createButton}
          onClick={handleCreate}
          disabled={isExecuting}
        >
          {isExecuting ? '⏳ Creating...' : '▶ Create'}
        </button>

        {/* Output Handle */}
        <Handle
          type="source"
          position={Position.Right}
          id="output"
          className={styles.handleOpen}
          title={`Output: ${schema.outputs[0]?.type || 'result'}`}
        />
      </div>

      {/* Context Menu */}
      {contextMenu && (
        <div
          className={styles.nodeContextMenu}
          style={{ position: 'fixed', left: contextMenu.x, top: contextMenu.y }}
          onClick={(e) => e.stopPropagation()}
        >
          <div className={styles.contextMenuItem} onClick={handleDuplicate}>
            📋 Duplicate
          </div>
          <div className={styles.contextMenuItem} onClick={handleDelete}>
            🗑️ Delete
          </div>
        </div>
      )}
    </>
  );
}

function renderControl(
  input: InputParameter,
  value: unknown,
  onChange: (name: string, value: unknown) => void
) {
  switch (input.type) {
    case 'text':
      return (
        <textarea
          className={styles.textInput}
          value={(value as string) || ''}
          onChange={(e) => onChange(input.name, e.target.value)}
          placeholder={input.description}
          rows={2}
        />
      );

    case 'number':
      return (
        <input
          type="number"
          className={styles.numberInput}
          value={(value as number) ?? (input.default as number) ?? ''}
          onChange={(e) => onChange(input.name, parseFloat(e.target.value) || 0)}
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
          onChange={(e) => onChange(input.name, e.target.value)}
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
            onChange={(e) => onChange(input.name, e.target.checked)}
          />
          <span>Enable</span>
        </label>
      );

    case 'image':
    case 'video':
    case 'audio':
      // Media inputs are connected via handles
      return (
        <div className={styles.mediaPlaceholder}>
          {value ? '✓ Connected' : 'Connect via handle →'}
        </div>
      );

    default:
      return (
        <input
          type="text"
          className={styles.textInput}
          value={(value as string) || ''}
          onChange={(e) => onChange(input.name, e.target.value)}
        />
      );
  }
}

export const AIEndpointNode = memo(AIEndpointNodeComponent);
AIEndpointNode.displayName = 'AIEndpointNode';
