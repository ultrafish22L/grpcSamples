/**
 * Custom Octane Node Component for ReactFlow
 * Matches the visual style and behavior of octaneWeb's NodeGraphEditor
 */

import { memo } from 'react';
import { Handle, Position } from '@xyflow/react';
import { SceneNode } from '../../services/OctaneClient';
import { OctaneIconMapper } from '../../utils/OctaneIconMapper';

export interface OctaneNodeData extends Record<string, unknown> {
  sceneNode: SceneNode;
  inputs?: Array<{
    id: string;
    label?: string;
    pinInfo?: any;
  }>;
  output?: {
    id: string;
    label?: string;
    pinInfo?: any;
  };
  onContextMenu?: (event: React.MouseEvent, nodeId: string) => void;
}

type OctaneNodeProps = {
  data: OctaneNodeData;
  selected?: boolean;
  id: string;
};

/**
 * Custom node component matching Octane Studio styling
 */
export const OctaneNode = memo((props: OctaneNodeProps) => {
  const { data, selected, id } = props;
  const { sceneNode, inputs = [], output, onContextMenu } = data;
  
  // Get node color from nodeInfo
  const nodeColor = sceneNode.nodeInfo?.nodeColor 
    ? OctaneIconMapper.formatColorValue(sceneNode.nodeInfo.nodeColor)
    : '#666';

  // Calculate dynamic width based on inputs
  const inputCount = inputs.length;
  const minWidth = 180;
  const minPinSpacing = 30; // Increased spacing for better visibility
  const calculatedWidth = inputCount > 0 
    ? Math.max(minWidth, inputCount * minPinSpacing + 40) 
    : minWidth;

  const handleContextMenu = (event: React.MouseEvent) => {
    if (onContextMenu) {
      event.preventDefault();
      event.stopPropagation();
      console.log('🖱️ [OctaneNode] Context menu triggered for node:', id);
      onContextMenu(event, id);
    }
  };

  return (
    <div
      className="octane-node"
      onContextMenu={handleContextMenu}
      style={{
        width: calculatedWidth,
        minWidth: minWidth,
        height: 32,
        backgroundColor: nodeColor,
        border: selected ? '2px solid #4a90e2' : '1px solid #555',
        borderRadius: 4,
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        position: 'relative',
        padding: '0 10px',
        cursor: 'grab',
      }}
    >
      {/* Input handles on top */}
      {inputs.map((input: any, index: number) => {
        const socketColor = input.pinInfo?.pinColor !== undefined
          ? OctaneIconMapper.formatColorValue(input.pinInfo.pinColor)
          : 'rgba(243, 220, 222, 1)';
        
        const inputSpacing = calculatedWidth / (inputs.length + 1);
        const socketX = inputSpacing * (index + 1) - calculatedWidth / 2;

        // Pin appearance: filled if connected to collapsed node, unfilled if connected to expanded node
        // Collapsed nodes are default value nodes (Float value, RGB color, etc.)
        const isConnectedToCollapsed = input.handle !== undefined && input.handle !== 0 &&
                                      (input.name?.includes('value') || input.name?.includes('color'));
        
        return (
          <Handle
            key={input.id}
            type="target"
            position={Position.Top}
            id={input.id}
            style={{
              left: `calc(50% + ${socketX}px)`,
              top: -4, // Move slightly above the node
              width: 12,
              height: 12,
              // Filled if connected to collapsed, unfilled (transparent) if connected to expanded
              backgroundColor: isConnectedToCollapsed ? socketColor : 'transparent',
              border: `2px solid ${socketColor}`,
              borderRadius: '50%',
              zIndex: 10,
            }}
            title={input.label || `Input ${index}`}
          />
        );
      })}

      {/* Node title */}
      <div
        style={{
          color: '#fff',
          fontSize: 11,
          fontFamily: 'Arial, sans-serif',
          textAlign: 'center',
          whiteSpace: 'nowrap',
          overflow: 'hidden',
          textOverflow: 'ellipsis',
          userSelect: 'none',
        }}
      >
        {sceneNode.name || sceneNode.type}
      </div>

      {/* Output handle on bottom */}
      {output && (() => {
        const outputColor = sceneNode.nodeInfo?.nodeColor !== undefined
          ? OctaneIconMapper.formatColorValue(sceneNode.nodeInfo.nodeColor)
          : 'rgba(243, 220, 222, 1)';
        
        return (
          <Handle
            type="source"
            position={Position.Bottom}
            id={output.id}
            style={{
              left: '50%',
              bottom: -4, // Move slightly below the node
              width: 12,
              height: 12,
              backgroundColor: outputColor,
              border: `2px solid ${outputColor}`,
              borderRadius: '50%',
              zIndex: 10,
            }}
            title={output.label || 'Output'}
          />
        );
      })()}
    </div>
  );
});

OctaneNode.displayName = 'OctaneNode';