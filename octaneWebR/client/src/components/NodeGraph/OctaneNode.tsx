/**
 * Custom Octane Node Component for ReactFlow
 * Matches the visual style and behavior of octaneWeb's NodeGraphEditor
 */

import { memo } from 'react';
import { Handle, Position, NodeProps } from 'reactflow';
import { SceneNode } from '../../services/OctaneClient';
import { OctaneIconMapper } from '../../utils/OctaneIconMapper';

export interface OctaneNodeData {
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
}

/**
 * Custom node component matching Octane Studio styling
 */
export const OctaneNode = memo(({ data, selected }: NodeProps<OctaneNodeData>) => {
  const { sceneNode, inputs = [], output } = data;
  
  // Get node color from nodeInfo
  const nodeColor = sceneNode.nodeInfo?.nodeColor 
    ? OctaneIconMapper.formatColorValue(sceneNode.nodeInfo.nodeColor)
    : '#666';

  // Calculate dynamic width based on inputs
  const inputCount = inputs.length;
  const minWidth = 180;
  const minPinSpacing = 20;
  const calculatedWidth = inputCount > 0 
    ? Math.max(minWidth, inputCount * minPinSpacing + 40) 
    : minWidth;

  return (
    <div
      className="octane-node"
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
      {inputs.map((input, index) => {
        const socketColor = input.pinInfo?.pinColor
          ? OctaneIconMapper.formatColorValue(input.pinInfo.pinColor)
          : 'rgba(243, 220, 222, 1)';
        
        const inputSpacing = calculatedWidth / (inputs.length + 1);
        const socketX = inputSpacing * (index + 1) - calculatedWidth / 2;

        return (
          <Handle
            key={input.id}
            type="target"
            position={Position.Top}
            id={input.id}
            style={{
              left: `calc(50% + ${socketX}px)`,
              top: 0,
              width: 8,
              height: 8,
              backgroundColor: socketColor,
              border: '1px solid #f4f7f6',
              borderRadius: '50%',
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
      {output && (
        <Handle
          type="source"
          position={Position.Bottom}
          id={output.id}
          style={{
            left: '50%',
            bottom: 0,
            width: 8,
            height: 8,
            backgroundColor: output.pinInfo?.pinColor
              ? OctaneIconMapper.formatColorValue(output.pinInfo.pinColor)
              : 'rgba(243, 220, 222, 1)',
            border: '1px solid #f4f7f6',
            borderRadius: '50%',
          }}
          title={output.label || 'Output'}
        />
      )}
    </div>
  );
});

OctaneNode.displayName = 'OctaneNode';
