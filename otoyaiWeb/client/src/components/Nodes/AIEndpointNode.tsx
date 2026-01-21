import { memo, useState, useCallback, useMemo, useEffect } from 'react';
import { Handle, Position, NodeProps, useReactFlow } from '@xyflow/react';
import { AIEndpointNodeData } from '../../types';
import { inferEndpointSchema, isMediaInput } from '../../utils/endpointSchema';
import { logger } from '../../services/logger';
import styles from './nodes.module.css';

type ExecutionStatus = 'idle' | 'executing' | 'completed' | 'error';

function AIEndpointNodeComponent({ data, selected, id }: NodeProps) {
  const typedData = data as unknown as AIEndpointNodeData;
  const { endpoint, selectedPin = 'output', result } = typedData;
  const { updateNodeData } = useReactFlow();
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);
  const [executionStatus, setExecutionStatus] = useState<ExecutionStatus>('idle');

  const schema = useMemo(() => inferEndpointSchema(endpoint), [endpoint]);

  const handlePinClick = useCallback((pinName: string) => {
    updateNodeData(id, { selectedPin: pinName });
    logger.debug('Pin selected', { node: id, pin: pinName });
  }, [id, updateNodeData]);

  const handleExecute = useCallback(async () => {
    if (executionStatus === 'executing') return;

    setExecutionStatus('executing');
    logger.info('Starting AI endpoint execution', { 
      nodeId: id, 
      endpoint: endpoint.endpoint_id 
    });

    try {
      // TODO: Implement actual API call
      // For now, simulate execution with a delay
      await new Promise(resolve => setTimeout(resolve, 3000));
      
      // Mock result
      const mockResult = {
        url: 'https://via.placeholder.com/512',
        status: 'completed'
      };
      
      updateNodeData(id, { result: mockResult });
      setExecutionStatus('completed');
      logger.info('AI endpoint execution completed', { nodeId: id });
      
      // Reset to idle after 2 seconds
      setTimeout(() => setExecutionStatus('idle'), 2000);
    } catch (error) {
      setExecutionStatus('error');
      logger.error('AI endpoint execution failed', error as Error);
      
      // Reset to idle after 3 seconds
      setTimeout(() => setExecutionStatus('idle'), 3000);
    }
  }, [id, endpoint.endpoint_id, executionStatus, updateNodeData]);

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

  // Get the appropriate icon based on execution status
  const getExecutionIcon = () => {
    switch (executionStatus) {
      case 'executing':
        return '⟳'; // Rotating circle
      case 'completed':
        return '✓'; // Check mark
      case 'error':
        return '✕'; // X mark
      default:
        return '▶'; // Play button
    }
  };

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
              style={{ left: handleLeft, top: 0, transform: 'translate(-50%, -50%)' }}
              title={`${input.label}${input.required ? ' (required)' : ''}\n${input.description || ''}`}
              onClick={() => handlePinClick(input.name)}
            />
          );
        })}

        {/* Title Bar with Play Button */}
        <div className={styles.nodeHeader}>
          <h3 className={styles.nodeTitle}>{endpoint.title}</h3>
          <button 
            className={`${styles.playButton} ${styles[`playButton${executionStatus.charAt(0).toUpperCase() + executionStatus.slice(1)}`]}`}
            onClick={handleExecute}
            disabled={executionStatus === 'executing'}
            title={executionStatus === 'executing' ? 'Executing...' : 'Execute endpoint'}
          >
            <span className={executionStatus === 'executing' ? styles.spinning : ''}>
              {getExecutionIcon()}
            </span>
          </button>
        </div>

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
              style={{ left: handleLeft, bottom: 0, transform: 'translate(-50%, 50%)' }}
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
