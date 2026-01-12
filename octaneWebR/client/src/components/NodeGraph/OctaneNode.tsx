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
  onContextMenu?: (event: React.MouseEvent, nodeId: string) => void;
}

/**
 * Custom node component matching Octane Studio styling
 */
export const OctaneNode = memo(({ data, selected, id }: NodeProps<OctaneNodeData>) => {
  const { sceneNode, inputs = [], output, onContextMenu } = data;
  
  console.log(`🎨 [OctaneNode] Rendering node "${sceneNode.name}":`, {
    inputs: inputs.length,
    hasOutput: !!output,
    inputDetails: inputs.map(i => ({ id: i.id, label: i.label })),
  });
  
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
      {inputs.map((input, index) => {
        const socketColor = input.pinInfo?.pinColor !== undefined
          ? OctaneIconMapper.formatColorValue(input.pinInfo.pinColor)
          : 'rgba(243, 220, 222, 1)';
        
        const inputSpacing = calculatedWidth / (inputs.length + 1);
        const socketX = inputSpacing * (index + 1) - calculatedWidth / 2;

        console.log(`🎨 [OctaneNode]   Input ${index} handle:`, {
          id: input.id,
          color: socketColor,
          posX: socketX,
        });

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
              backgroundColor: socketColor,
              border: '2px solid #f4f7f6',
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
      {output && (
        <>
          {console.log(`🎨 [OctaneNode]   Output handle:`, {
            id: output.id,
            label: output.label,
            nodeColor: sceneNode.nodeInfo?.nodeColor,
          })}
          <Handle
            type="source"
            position={Position.Bottom}
            id={output.id}
            style={{
              left: '50%',
              bottom: -4, // Move slightly below the node
              width: 12,
              height: 12,
              backgroundColor: sceneNode.nodeInfo?.nodeColor !== undefined
                ? OctaneIconMapper.formatColorValue(sceneNode.nodeInfo.nodeColor)
                : 'rgba(243, 220, 222, 1)',
              border: '2px solid #f4f7f6',
              borderRadius: '50%',
              zIndex: 10,
            }}
            title={output.label || 'Output'}
          />
        </>
      )}
    </div>
  );
});

OctaneNode.displayName = 'OctaneNode';

/*
Type '{ children: (void | Element)[]; }' is not assignable to type '{ children?: ReactNode; }'.
  Types of property 'children' are incompatible.
    Type '(void | Element)[]' is not assignable to type 'ReactNode'.
      Type '(void | Element)[]' is not assignable to type 'Iterable<ReactNode>'.
        The types returned by '[Symbol.iterator]().next(...)' are incompatible between these types.
          Type 'IteratorResult<void | Element, undefined>' is not assignable to type 'IteratorResult<ReactNode, any>'.
            Type 'IteratorYieldResult<void | Element>' is not assignable to type 'IteratorResult<ReactNode, any>'.
              Type 'IteratorYieldResult<void | Element>' is not assignable to type 'IteratorYieldResult<ReactNode>'.
                Type 'void | Element' is not assignable to type 'ReactNode'.
                  Type 'void' is not assignable to type 'ReactNode'.ts(2322)
*/