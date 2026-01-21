import { memo, useState, useCallback, useMemo, useEffect } from 'react';
import { Handle, Position, NodeProps, useReactFlow } from '@xyflow/react';
import { AIEndpointNodeData } from '../../types';
import { inferEndpointSchema, isMediaInput } from '../../utils/endpointSchema';
import { logger } from '../../services/logger';
import styles from './nodes.module.css';

function AIEndpointNodeComponent({ data, selected, id }: NodeProps) {
  const typedData = data as unknown as AIEndpointNodeData;
  const { endpoint, selectedPin = 'output', result, previewCollapsed = true } = typedData;
  const { updateNodeData } = useReactFlow();
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);

  const schema = useMemo(() => inferEndpointSchema(endpoint), [endpoint]);

  const handlePinClick = useCallback((pinName: string) => {
    updateNodeData(id, { selectedPin: pinName });
    logger.debug('Pin selected', { node: id, pin: pinName });
  }, [id, updateNodeData]);

  const togglePreview = useCallback(() => {
    updateNodeData(id, { previewCollapsed: !previewCollapsed });
  }, [id, previewCollapsed, updateNodeData]);

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

  // Calculate node width for handle positioning
  const nodeWidth = 220; // Match the min-width in CSS

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
        {/* Input Handles - Top */}
        {schema.inputs.map((input, index) => {
          const numInputs = schema.inputs.length;
          const spacing = nodeWidth / (numInputs + 1);
          const handleLeft = spacing * (index + 1);
          
          const isSelected = selectedPin === input.name;
          const isConnected = false; // TODO: Check if handle is connected
          const hasValue = typedData.parameters?.[input.name] != null && typedData.parameters[input.name] !== '';
          const isFilled = hasValue && !isConnected;
          
          return (
            <Handle
              key={input.name}
              type="target"
              position={Position.Top}
              id={input.name}
              className={`${isFilled ? styles.handleFilled : styles.handleOpen} ${isSelected ? styles.handleSelected : ''}`}
              style={{ left: handleLeft, top: -6 }}
              title={`${input.label}${input.required ? ' (required)' : ''}\n${input.description || ''}`}
              onClick={() => handlePinClick(input.name)}
            />
          );
        })}

        {/* Title Bar */}
        <div className={styles.nodeHeader} onClick={togglePreview}>
          <h3 className={styles.nodeTitle}>{endpoint.title}</h3>
          <span className={styles.collapseIndicator}>{previewCollapsed ? '▶' : '▼'}</span>
        </div>

        {/* Collapsible Preview Area */}
        {!previewCollapsed && (
          <div className={styles.previewArea}>
            {previewContent}
          </div>
        )}

        {/* Output Handles - Bottom */}
        {schema.outputs.map((output, index) => {
          const numOutputs = schema.outputs.length;
          const spacing = nodeWidth / (numOutputs + 1);
          const handleLeft = spacing * (index + 1);
          
          const isSelected = selectedPin === 'output';
          const isConnected = false; // TODO: Check if handle is connected
          const hasResult = result != null;
          const isFilled = hasResult && !isConnected;
          
          return (
            <Handle
              key={output.name}
              type="source"
              position={Position.Bottom}
              id={output.name}
              className={`${isFilled ? styles.handleFilled : styles.handleOpen} ${isSelected ? styles.handleSelected : ''}`}
              style={{ left: handleLeft, bottom: -6 }}
              title={`Output: ${output.type || 'result'}`}
              onClick={() => handlePinClick('output')}
            />
          );
        })}
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
