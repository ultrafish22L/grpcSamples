import { memo, useState, useCallback, useMemo, useEffect } from 'react';
import { Handle, Position, NodeProps, useReactFlow } from '@xyflow/react';
import { AIEndpointNodeData } from '../../types';
import { inferEndpointSchema, isMediaInput } from '../../utils/endpointSchema';
import { logger } from '../../services/logger';
import styles from './nodes.module.css';

function AIEndpointNodeComponent({ data, selected, id }: NodeProps) {
  const typedData = data as unknown as AIEndpointNodeData;
  const { endpoint, selectedPin = 'output', result } = typedData;
  const { updateNodeData } = useReactFlow();
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);

  const schema = useMemo(() => inferEndpointSchema(endpoint), [endpoint]);

  const handlePinClick = useCallback((pinName: string) => {
    updateNodeData(id, { selectedPin: pinName });
    logger.debug('Pin selected', { node: id, pin: pinName });
  }, [id, updateNodeData]);

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
  const handleSpacing = 30;
  const headerHeight = 50;

  // Determine what to show in preview
  const previewContent = useMemo(() => {
    if (selectedPin === 'output') {
      if (result && typeof result === 'object' && 'url' in result) {
        return <img src={(result as { url: string }).url} alt="Output" className={styles.previewImage} />;
      }
      return (
        <div className={styles.previewPlaceholder}>
          <div className={styles.previewIcon}>🎨</div>
          <div className={styles.previewText}>Output preview</div>
        </div>
      );
    }
    
    // Show preview for selected input pin
    const input = schema.inputs.find(i => i.name === selectedPin);
    if (input && isMediaInput(input.type)) {
      return (
        <div className={styles.previewPlaceholder}>
          <div className={styles.previewIcon}>
            {input.type === 'image' ? '🖼️' : input.type === 'video' ? '🎬' : '🎵'}
          </div>
          <div className={styles.previewText}>{input.label}</div>
        </div>
      );
    }

    return null;
  }, [selectedPin, result, schema.inputs]);

  return (
    <>
      <div 
        className={`${styles.baseNode} ${styles.aiEndpointNode} ${selected ? styles.selected : ''}`}
        onContextMenu={handleContextMenu}
        title={endpoint.description}
      >
        {/* Header with title and buttons */}
        <div className={styles.nodeHeader}>
          <div className={styles.nodeTitleArea}>
            <h3 className={styles.nodeTitle}>
              {endpoint.title}
            </h3>
          </div>
          <div className={styles.nodeHeaderButtons}>
            <button 
              className={styles.nodeHeaderButton}
              onClick={handleDuplicate}
              title="Duplicate node"
            >
              📋
            </button>
            <button 
              className={styles.nodeHeaderButton}
              onClick={handleDelete}
              title="Delete node"
            >
              🗑️
            </button>
          </div>
        </div>

        {/* Preview Area */}
        <div className={styles.previewArea}>
          {previewContent}
        </div>

        {/* Input Handles */}
        {schema.inputs.map((input, index) => {
          const handleTop = headerHeight + index * handleSpacing;
          const isMedia = isMediaInput(input.type);
          const isSelected = selectedPin === input.name;
          
          return (
            <Handle
              key={input.name}
              type="target"
              position={Position.Left}
              id={input.name}
              className={`${isMedia ? styles.handleOpen : styles.handleFilled} ${isSelected ? styles.handleSelected : ''}`}
              style={{ top: handleTop }}
              title={`${input.label}${input.required ? ' (required)' : ''}\n${input.description || ''}`}
              onClick={() => handlePinClick(input.name)}
            />
          );
        })}

        {/* Output Handle */}
        <Handle
          type="source"
          position={Position.Right}
          id="output"
          className={`${styles.handleOpen} ${selectedPin === 'output' ? styles.handleSelected : ''}`}
          title={`Output: ${schema.outputs[0]?.type || 'result'}`}
          onClick={() => handlePinClick('output')}
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

export const AIEndpointNode = memo(AIEndpointNodeComponent);
AIEndpointNode.displayName = 'AIEndpointNode';
