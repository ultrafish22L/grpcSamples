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
    handle?: number;
    nodeInfo?: any;
    name?: string;
    connectedNodeName?: string | null;
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
        border: selected ? '2px solid #ffc107' : '1px solid #555',
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

        // Pin appearance logic:
        // - Collapsed node at pin: pin connects to a node NOT at level 1 (not visible in NGE) → SOLID ⬤
        // - Expanded node at pin: pin connects to a node AT level 1 (visible in NGE) → OUTLINE ○
        // - No connection at pin: pin has no connected node → OUTLINE ○
        const isConnectedToCollapsed = input.handle !== undefined && 
                                      input.handle !== 0 && 
                                      !input.isAtTopLevel;
        
        // Build enhanced tooltip with pin name, type, description, and connected node
        // Using all available data from Octane's ApiNodePinInfo
        const buildTooltip = () => {
          const parts = [];
          
          // Pin name/label (staticLabel is preferred, fallback to staticName)
          const pinName = input.pinInfo?.staticLabel || input.pinInfo?.staticName || input.label || `Input ${index}`;
          parts.push(`📌 ${pinName}`);
          
          // Pin description (from ApiNodePinInfo.description)
          if (input.pinInfo?.description) {
            parts.push(`ℹ️ ${input.pinInfo.description}`);
          }
          
          // Pin type (NodePinType from ApiNodePinInfo.type)
          const pinTypeMap: Record<number, string> = {
            0: 'Unknown', 1: 'Geometry', 2: 'Material', 3: 'Texture', 4: 'Environment',
            5: 'Camera', 6: 'Emission', 7: 'Displacement', 8: 'Medium', 9: 'Projection',
            10: 'Transform', 11: 'RenderTarget', 12: 'Imager', 13: 'PostProc', 14: 'RenderAOV',
            15: 'OutputAOV', 16: 'RenderLayer', 17: 'ObjectLayer'
          };
          if (input.pinInfo?.type !== undefined) {
            const typeName = pinTypeMap[input.pinInfo.type] || `Type ${input.pinInfo.type}`;
            parts.push(`🏷️ Pin Type: ${typeName}`);
          }
          
          // Group name (from ApiNodePinInfo.groupName)
          if (input.pinInfo?.groupName) {
            parts.push(`📁 Group: ${input.pinInfo.groupName}`);
          }
          
          // Connected node name
          if (input.connectedNodeName) {
            parts.push(`🔗 Connected: ${input.connectedNodeName}`);
          } else if (input.handle === 0) {
            parts.push('⚪ Empty/Default');
          } else {
            parts.push('⚪ Not connected');
          }
          
          return parts.join('\n');
        };
        
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
            title={buildTooltip()}
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
        
        // Build enhanced output tooltip
        // Using all available data from Octane's ApiNodeInfo
        const buildOutputTooltip = () => {
          const parts = [];
          
          // Node name/label (defaultName from ApiNodeInfo is preferred)
          const nodeName = sceneNode.nodeInfo?.defaultName || sceneNode.name || sceneNode.type;
          parts.push(`📤 Output: ${nodeName}`);
          
          // Node description (from ApiNodeInfo.description)
          if (sceneNode.nodeInfo?.description) {
            parts.push(`ℹ️ ${sceneNode.nodeInfo.description}`);
          }
          
          // Output pin type (NodePinType from ApiNodeInfo.outType)
          const pinTypeMap: Record<number, string> = {
            0: 'Unknown', 1: 'Geometry', 2: 'Material', 3: 'Texture', 4: 'Environment',
            5: 'Camera', 6: 'Emission', 7: 'Displacement', 8: 'Medium', 9: 'Projection',
            10: 'Transform', 11: 'RenderTarget', 12: 'Imager', 13: 'PostProc', 14: 'RenderAOV',
            15: 'OutputAOV', 16: 'RenderLayer', 17: 'ObjectLayer'
          };
          if (sceneNode.nodeInfo?.outType !== undefined) {
            const typeName = pinTypeMap[sceneNode.nodeInfo.outType] || `Type ${sceneNode.nodeInfo.outType}`;
            parts.push(`🏷️ Output Type: ${typeName}`);
          }
          
          // Category (from ApiNodeInfo.category)
          if (sceneNode.nodeInfo?.category) {
            parts.push(`📂 Category: ${sceneNode.nodeInfo.category}`);
          }
          
          // Special node types (from ApiNodeInfo flags)
          const nodeFlags = [];
          if (sceneNode.nodeInfo?.isLinker) nodeFlags.push('Linker');
          if (sceneNode.nodeInfo?.isOutputLinker) nodeFlags.push('Output Linker');
          if (sceneNode.nodeInfo?.isTypedTextureNode) nodeFlags.push('Typed Texture');
          if (nodeFlags.length > 0) {
            parts.push(`🔧 ${nodeFlags.join(', ')}`);
          }
          
          return parts.join('\n');
        };
        
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
            title={buildOutputTooltip()}
          />
        );
      })()}
    </div>
  );
});

OctaneNode.displayName = 'OctaneNode';