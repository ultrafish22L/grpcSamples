import { memo, useState, useCallback, useMemo, useEffect, useRef } from 'react';
import { createPortal } from 'react-dom';
import { Handle, Position, NodeProps, useReactFlow } from '@xyflow/react';
import { AIEndpointNodeData, TextInputNodeData, ImageNodeData, VideoNodeData } from '../../types';
import { inferEndpointSchema, isMediaInput } from '../../utils/endpointSchema';
import { getHandleColorClass, mapOutputTypeToHandleType, mapInputTypeToHandleType } from '../../utils/connectionValidator';
import { useStore } from '../../store/useStore';
import { logger } from '../../services/logger';
import { otoyAPI } from '../../services/api';
import { packageParameters, resolveConnectedParameters } from '../../utils/parameterPackager';
import styles from './nodes.module.css';

type ExecutionStatus = 'idle' | 'executing' | 'completed' | 'error';

function AIEndpointNodeComponent({ data, selected, id }: NodeProps) {
  const typedData = data as unknown as AIEndpointNodeData;
  const { endpoint, selectedPin = 'output', result, previewCollapsed = true } = typedData;
  const { updateNodeData, getEdges } = useReactFlow();
  const { onNodesChange, addNode, nodes } = useStore();
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);
  const contextMenuRef = useRef<HTMLDivElement>(null);
  const [executionStatus, setExecutionStatus] = useState<ExecutionStatus>('idle');

  const schema = useMemo(() => inferEndpointSchema(endpoint), [endpoint]);
  
  // Helper to check if a handle is connected
  const isHandleConnected = useCallback((handleId: string, handleType: 'source' | 'target') => {
    const edges = getEdges();
    return edges.some(edge => {
      if (handleType === 'target') {
        return edge.target === id && edge.targetHandle === handleId;
      } else {
        return edge.source === id && edge.sourceHandle === handleId;
      }
    });
  }, [id, getEdges]);

  const handlePinClick = useCallback((pinName: string) => {
    updateNodeData(id, { selectedPin: pinName });
    logger.debug('Pin selected', { node: id, pin: pinName });
    
    // If clicking output pin, toggle preview
    if (pinName === 'output') {
      updateNodeData(id, { previewCollapsed: !previewCollapsed });
    }
  }, [id, previewCollapsed, updateNodeData]);

  // TODO: Add UI button to toggle preview
  // const togglePreview = useCallback(() => {
  //   updateNodeData(id, { previewCollapsed: !previewCollapsed });
  // }, [id, previewCollapsed, updateNodeData]);

  // Get values from connected input nodes
  const getConnectedValues = useCallback(() => {
    const edges = getEdges();
    const connectedValues: Record<string, any> = {};
    
    for (const input of schema.inputs) {
      const handleId = `input-${input.name}`;
      const edge = edges.find(e => e.target === id && e.targetHandle === handleId);
      
      if (edge) {
        const sourceNode = nodes.find(n => n.id === edge.source);
        if (sourceNode) {
          // Get value from source node based on type with proper type guards
          if (sourceNode.type === 'textInput') {
            const textData = sourceNode.data as TextInputNodeData;
            connectedValues[input.name] = textData.value;
          } else if (sourceNode.type === 'image' || sourceNode.type === 'video') {
            // For media nodes with multiple outputs, get the specific item
            const mediaData = sourceNode.data as ImageNodeData | VideoNodeData;
            const sourceHandle = edge.sourceHandle;
            if (sourceHandle && sourceHandle.startsWith('output-')) {
              const itemId = sourceHandle.replace('output-', '');
              const item = mediaData.items?.find((i) => i.id === itemId);
              if (item) {
                connectedValues[input.name] = item.preview || item.url || item.file;
              }
            }
          } else if (sourceNode.type === 'aiEndpoint') {
            // Get result from AI endpoint output
            const aiData = sourceNode.data as AIEndpointNodeData;
            connectedValues[input.name] = aiData.result;
          }
        }
      }
    }
    
    return connectedValues;
  }, [id, schema.inputs, getEdges, nodes]);

  const handleExecute = useCallback(async () => {
    if (executionStatus === 'executing') return;

    setExecutionStatus('executing');
    logger.info('Starting AI endpoint execution', { 
      nodeId: id, 
      endpoint: endpoint.endpoint_id 
    });

    try {
      // Get connected values and merge with node parameters
      const connectedValues = getConnectedValues();
      const nodeParameters = typedData.parameters || {};
      const resolvedParameters = resolveConnectedParameters(nodeParameters, connectedValues);
      
      logger.debug('Resolved parameters', { 
        nodeId: id, 
        resolved: Object.keys(resolvedParameters),
        connected: Object.keys(connectedValues)
      });

      // Package parameters for API call
      const packagedParameters = await packageParameters(resolvedParameters, schema.inputs);
      
      logger.debug('Packaged parameters', { 
        nodeId: id, 
        keys: Object.keys(packagedParameters)
      });

      // Execute endpoint
      const response = await otoyAPI.executeEndpoint({
        endpoint_id: endpoint.endpoint_id,
        parameters: packagedParameters,
      });

      if (response.success) {
        updateNodeData(id, { 
          result: response.data,
          error: undefined 
        });
        setExecutionStatus('completed');
        logger.info('AI endpoint execution completed', { 
          nodeId: id,
          resultKeys: Object.keys(response.data || {})
        });
        
        // Reset to idle after 2 seconds
        setTimeout(() => setExecutionStatus('idle'), 2000);
      } else {
        throw new Error(response.error || 'Execution failed');
      }
    } catch (error) {
      const errorMessage = (error as Error).message || 'Unknown error';
      updateNodeData(id, { 
        result: undefined,
        error: errorMessage 
      });
      setExecutionStatus('error');
      logger.error('AI endpoint execution failed', error as Error);
      
      // Reset to idle after 3 seconds
      setTimeout(() => setExecutionStatus('idle'), 3000);
    }
  }, [id, endpoint.endpoint_id, executionStatus, updateNodeData, getConnectedValues, typedData.parameters, schema.inputs]);

  const handleContextMenu = useCallback((e: React.MouseEvent) => {
    e.preventDefault();
    
    // Select this node before showing context menu
    if (!selected) {
      const selectionChanges = nodes.map(node => ({
        id: node.id,
        type: 'select' as const,
        selected: node.id === id
      }));
      onNodesChange(selectionChanges);
    }
    
    setContextMenu({ x: e.clientX, y: e.clientY });
  }, [selected, nodes, id, onNodesChange]);

  const closeContextMenu = useCallback(() => {
    setContextMenu(null);
  }, []);

  // Calculate adjusted position to keep menu in viewport
  const contextMenuPosition = useMemo(() => {
    if (!contextMenu) return { left: 0, top: 0 };
    
    const menuWidth = 150; // Approximate width from CSS
    const menuHeight = 80; // Approximate height for 2 items
    const padding = 8; // Padding from viewport edge
    
    let { x, y } = contextMenu;
    
    // Adjust horizontal position
    if (x + menuWidth > window.innerWidth - padding) {
      x = window.innerWidth - menuWidth - padding;
    }
    if (x < padding) {
      x = padding;
    }
    
    // Adjust vertical position
    if (y + menuHeight > window.innerHeight - padding) {
      y = window.innerHeight - menuHeight - padding;
    }
    if (y < padding) {
      y = padding;
    }
    
    return { left: x, top: y };
  }, [contextMenu]);

  useEffect(() => {
    if (contextMenu) {
      const handleClick = () => closeContextMenu();
      document.addEventListener('click', handleClick);
      return () => document.removeEventListener('click', handleClick);
    }
  }, [contextMenu, closeContextMenu]);

  const handleDelete = useCallback(() => {
    logger.info('Delete AI endpoint node requested', { id });
    onNodesChange([{ type: 'remove', id }]);
    closeContextMenu();
  }, [id, onNodesChange, closeContextMenu]);

  const handleDuplicate = useCallback(() => {
    logger.info('Duplicate AI endpoint node requested', { id });
    const newNode = {
      id: `${id}-copy-${Date.now()}`,
      type: 'aiEndpoint',
      position: { x: selected ? 50 : 0, y: selected ? 50 : 0 },
      data: { ...typedData },
    };
    addNode(newNode as any);
    closeContextMenu();
  }, [id, typedData, selected, addNode, closeContextMenu]);

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
          const isConnected = isHandleConnected(input.name, 'target');
          const hasValue = typedData.parameters?.[input.name] != null && typedData.parameters[input.name] !== '';
          // Input pins: filled if (has value AND not connected), unfilled if (empty OR connected)
          const isFilled = hasValue && !isConnected;
          
          // Map input type to handle type for color coding
          const handleType = mapInputTypeToHandleType(input.type);
          
          return (
            <Handle
              key={input.name}
              type="target"
              position={Position.Top}
              id={input.name}
              className={`${isFilled ? styles.handleFilled : styles.handleOpen} ${isSelected ? styles.handleSelected : ''} ${styles[getHandleColorClass(handleType)]}`}
              style={{ left: handleLeft, top: 0, transform: 'translate(-50%, -50%)' }}
              title={`${input.label}${input.required ? ' (required)' : ''}\n${input.description || ''}`}
              onClick={(e) => { e.stopPropagation(); handlePinClick(input.name); }}
            />
          );
        })}

        {/* Title Bar with Play Button */}
        <div className={styles.nodeHeader}>
          <h3 className={styles.nodeTitle}>{endpoint.title}</h3>
          <button 
            className={`${styles.playButton} ${styles[`playButton${executionStatus.charAt(0).toUpperCase() + executionStatus.slice(1)}`]}`}
            onClick={(e) => { e.stopPropagation(); handleExecute(); }}
            disabled={executionStatus === 'executing'}
            title={executionStatus === 'executing' ? 'Executing...' : 'Execute endpoint'}
          >
            <span className={executionStatus === 'executing' ? styles.spinning : ''}>
              {getExecutionIcon()}
            </span>
          </button>
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
          const hasResult = result != null;
          // Output pins: always visible, filled if has value, unfilled if empty
          const isFilled = hasResult;
          
          const outputId = index === 0 ? 'output' : `output-${index}`;
          
          // Convert output type to HandleType for color mapping
          const handleType = mapOutputTypeToHandleType(output.type);
          
          return (
            <Handle
              key={outputId}
              type="source"
              position={Position.Bottom}
              id={outputId}
              className={`${isFilled ? styles.handleFilled : styles.handleOpen} ${isSelected ? styles.handleSelected : ''} ${styles[getHandleColorClass(handleType)]}`}
              style={{ left: handleLeft, bottom: 0, transform: 'translate(-50%, 50%)' }}
              title={`Output: ${output.type || 'result'}`}
              onClick={(e) => { e.stopPropagation(); handlePinClick('output'); }}
            />
          );
        })}
      </div>

      {/* Context Menu - Rendered via Portal */}
      {contextMenu && createPortal(
        <div
          ref={contextMenuRef}
          className={styles.nodeContextMenu}
          style={{ 
            position: 'fixed', 
            left: `${contextMenuPosition.left}px`, 
            top: `${contextMenuPosition.top}px` 
          }}
          onClick={(e) => e.stopPropagation()}
        >
          <div className={styles.contextMenuItem} onClick={handleDuplicate}>
            📋 Duplicate
          </div>
          <div className={styles.contextMenuItem} onClick={handleDelete}>
            🗑️ Delete
          </div>
        </div>,
        document.body
      )}
    </>
  );
}

export const AIEndpointNode = memo(AIEndpointNodeComponent);
AIEndpointNode.displayName = 'AIEndpointNode';
