/**
 * Node Inspector Component (React TypeScript)
 * Hierarchical node parameter display matching octaneWeb implementation
 */

import React, { useState, useEffect } from 'react';
import { SceneNode } from '../services/OctaneClient';
import { useOctane } from '../hooks/useOctane';
import { ContextMenu, ContextMenuItem } from './ContextMenu';

interface NodeInspectorProps {
  node: SceneNode | null;
}

interface ParameterValue {
  value: any;
  type: string;
}

// Parameter group display component
function ParameterGroup({ 
  groupName, 
  children, 
  defaultExpanded = true 
}: { 
  groupName: string; 
  children: React.ReactNode; 
  defaultExpanded?: boolean;
}) {
  const [expanded, setExpanded] = useState(defaultExpanded);

  return (
    <div className="inspector-group-indent">
      <div 
        className={`inspector-group-header ${expanded ? 'expanded' : 'collapsed'}`}
        onClick={() => setExpanded(!expanded)}
      >
        <span className="inspector-group-icon">{expanded ? '▼' : '▶'}</span>
        <span className="inspector-group-label">{groupName}</span>
      </div>
      <div 
        className="inspector-group-content" 
        style={{ display: expanded ? 'block' : 'none' }}
      >
        {children}
      </div>
    </div>
  );
}

// Node parameter item component
function NodeParameter({ 
  node, 
  level, 
  onToggle,
  onContextMenu
}: { 
  node: SceneNode; 
  level: number; 
  onToggle: (nodeId: string) => void;
  onContextMenu: (node: SceneNode, x: number, y: number) => void;
}) {
  const { client } = useOctane();
  const [paramValue, setParamValue] = useState<ParameterValue | null>(null);
  const [expanded, setExpanded] = useState(level < 2);
  
  const hasChildren = node.children && node.children.length > 0;
  const isEndNode = !hasChildren && node.attrInfo;
  const nodeId = `node-${node.handle}`;
  const icon = node.icon || getNodeIcon(node);
  const color = node.nodeInfo?.nodeColor ? formatColor(node.nodeInfo.nodeColor) : '#666';
  const name = node.name;  // Name already includes pinInfo.staticLabel from OctaneClient

  // Fetch parameter value for end nodes
  useEffect(() => {
    if (isEndNode && node.attrInfo) {
      fetchParameterValue();
    }
  }, [isEndNode, node.handle]);

  const fetchParameterValue = async () => {
    if (!node.attrInfo) return;
    
    try {
      const response = await client.callApi(
        'ApiItem',
        'getByAttrID',
        node.handle,
        {
          attribute_id: 12, // A_VALUE
          expected_type: node.attrInfo.type
        }
      );
      
      if (response) {
        setParamValue({
          value: response,
          type: node.attrInfo.type
        });
      }
    } catch (error) {
      console.error('Failed to fetch parameter value:', error);
    }
  };

  const handleToggle = () => {
    setExpanded(!expanded);
    onToggle(nodeId);
  };

  // Render parameter value as text (matching reference screenshot)
  const renderValue = () => {
    if (!paramValue) return null;

    const { value, type } = paramValue;

    switch (type) {
      case 'AT_BOOL':
        return (
          <span className="parameter-value">
            {value?.result ? '☑' : '☐'}
          </span>
        );
      
      case 'AT_FLOAT':
        return (
          <span className="parameter-value">
            {typeof value?.result === 'number' ? value.result.toFixed(6) : '0.000000'}
          </span>
        );
      
      case 'AT_INT':
        return (
          <span className="parameter-value">
            {value?.result || 0}
          </span>
        );
      
      case 'AT_FLOAT3':
        if (value?.result) {
          const { x, y, z } = value.result;
          
          // Check if this is a color parameter (RGB values between 0 and 1)
          const isColor = node.attrInfo?.type === 'AT_FLOAT3' && 
                          x >= 0 && x <= 1 && y >= 0 && y <= 1 && z >= 0 && z <= 1;
          
          if (isColor) {
            // Display as colored bar
            const r = Math.round(x * 255);
            const g = Math.round(y * 255);
            const b = Math.round(z * 255);
            const colorStyle = `rgb(${r}, ${g}, ${b})`;
            return (
              <div className="color-parameter">
                <div className="color-bar" style={{ backgroundColor: colorStyle }}></div>
                <span className="parameter-value">
                  {x.toFixed(4)}, {y.toFixed(4)}, {z.toFixed(4)}
                </span>
              </div>
            );
          }
          
          // Display as numeric vector
          return (
            <span className="parameter-value">
              {(x || 0).toFixed(6)}, {(y || 0).toFixed(6)}, {(z || 0).toFixed(6)}
            </span>
          );
        }
        return <span className="parameter-value">0, 0, 0</span>;
      
      case 'AT_STRING':
      case 'AT_FILENAME':
        return (
          <span className="parameter-value">
            {value?.result || ''}
          </span>
        );
      
      default:
        // For unknown types, try to display the result value
        const displayValue = value?.result !== undefined 
          ? (typeof value.result === 'object' ? JSON.stringify(value.result) : String(value.result))
          : '';
        return (
          <span className="parameter-value">
            {displayValue}
          </span>
        );
    }
  };

  const handleContextMenu = (e: React.MouseEvent) => {
    e.preventDefault();
    e.stopPropagation();
    onContextMenu(node, e.clientX, e.clientY);
  };

  const indentClass = level === 0 ? 'node-indent-0' : 'node-indent';
  
  return (
    <div className={indentClass}>
      <div 
        className={isEndNode ? 'node-box-parameter' : 'node-box'}
        data-node-handle={node.handle}
        onContextMenu={handleContextMenu}
      >
        {isEndNode ? (
          // Parameters use blue icon styling (matching reference screenshot)
          <div className="parameter-icon">
            <span>{icon}</span>
          </div>
        ) : (
          // Non-parameter nodes use colored icon box
          <div className="node-icon-box" style={{ backgroundColor: color }}>
            <span className="node-icon">{icon}</span>
          </div>
        )}
        <div className="node-content">
          <div className="node-label" onClick={hasChildren ? handleToggle : undefined}>
            {hasChildren && (
              <span className="collapse-icon">{expanded ? '▼' : '▶'}</span>
            )}
            <span className="node-title">{name}</span>
            {isEndNode && renderValue()}
          </div>
        </div>
      </div>
      
      {hasChildren && (
        <div 
          className="node-toggle-content"
          style={{ display: expanded ? 'block' : 'none' }}
        >
          {groupChildren(node.children!).map(({ groupName, children }, idx) => {
            if (groupName) {
              return (
                <ParameterGroup key={`group-${idx}`} groupName={groupName}>
                  {children.map(child => (
                    <NodeParameter
                      key={child.handle}
                      node={child}
                      level={level + 1}
                      onToggle={onToggle}
                      onContextMenu={onContextMenu}
                    />
                  ))}
                </ParameterGroup>
              );
            } else {
              return children.map(child => (
                <NodeParameter
                  key={child.handle}
                  node={child}
                  level={level + 1}
                  onToggle={onToggle}
                  onContextMenu={onContextMenu}
                />
              ));
            }
          })}
        </div>
      )}
    </div>
  );
}

// Helper: Get node icon
function getNodeIcon(node: SceneNode): string {
  const iconMap: Record<string, string> = {
    'Bool': '☑️',
    'Float': '🔢',
    'Int': '🔢',
    'Transform': '🔄',
    'Texture': '🎨',
    'Material': '🎨',
    'Camera': '📷',
    'Environment': '🌍',
    'Geometry': '🫖',
    'Render Target': '🎯',
  };
  
  return iconMap[node.type] || '⚪';
}

// Helper: Format color from node info
function formatColor(color: any): string {
  if (typeof color === 'object' && color.x !== undefined) {
    const r = Math.round((color.x || 0) * 255);
    const g = Math.round((color.y || 0) * 255);
    const b = Math.round((color.z || 0) * 255);
    return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
  }
  return '#666';
}

// Helper: Group children by pinInfo.groupName
function groupChildren(children: SceneNode[]): Array<{ groupName: string | null; children: SceneNode[] }> {
  const groups: Array<{ groupName: string | null; children: SceneNode[] }> = [];
  let currentGroup: { groupName: string | null; children: SceneNode[] } | null = null;

  for (const child of children) {
    const groupName = child.pinInfo?.groupName || null;
    
    if (!currentGroup || currentGroup.groupName !== groupName) {
      currentGroup = { groupName, children: [] };
      groups.push(currentGroup);
    }
    
    currentGroup.children.push(child);
  }

  return groups;
}

export function NodeInspector({ node }: NodeInspectorProps) {
  const [contextMenu, setContextMenu] = useState<{ node: SceneNode; x: number; y: number } | null>(null);

  // NOTE: Node expansion state is managed internally by NodeParameter component
  const handleToggle = (_nodeId: string) => {
    // Placeholder for future centralized expansion state management
  };

  const handleContextMenu = (paramNode: SceneNode, x: number, y: number) => {
    setContextMenu({ node: paramNode, x, y });
  };

  const handleContextMenuClose = () => {
    setContextMenu(null);
  };

  const handleContextMenuAction = (action: string) => {
    console.log(`Node Inspector context menu action: ${action}`, contextMenu?.node);
    // TODO: Implement context menu actions
    switch (action) {
      case 'save':
        console.log('Save action - to be implemented');
        break;
      case 'cut':
        console.log('Cut action - to be implemented');
        break;
      case 'copy':
        console.log('Copy action - to be implemented');
        break;
      case 'paste':
        console.log('Paste action - to be implemented');
        break;
      case 'delete':
        console.log('Delete action - to be implemented');
        break;
      case 'expand':
        console.log('Expand action - to be implemented');
        break;
      case 'show-in-outliner':
        console.log('Show in Outliner - to be implemented');
        break;
      case 'show-in-graph':
        console.log('Show in Graph Editor - to be implemented');
        break;
      case 'show-in-lua':
        console.log('Show in Lua API browser - to be implemented');
        break;
    }
  };

  const nodeInspectorContextMenuItems: ContextMenuItem[] = [
    { label: 'Save...', action: 'save' },
    { label: '', action: '', separator: true },
    { label: 'Cut', action: 'cut', shortcut: 'Ctrl+X' },
    { label: 'Copy', action: 'copy', shortcut: 'Ctrl+C' },
    { label: 'Paste', action: 'paste', shortcut: 'Ctrl+V', disabled: true },
    { label: '', action: '', separator: true },
    { label: 'Delete', action: 'delete', shortcut: 'Del' },
    { label: '', action: '', separator: true },
    { label: 'Expand', action: 'expand' },
    { label: '', action: '', separator: true },
    { label: 'Show in Outliner', action: 'show-in-outliner' },
    { label: 'Show in Graph Editor', action: 'show-in-graph' },
    { label: 'Show in Lua API browser', action: 'show-in-lua' },
  ];

  if (!node) {
    return (
      <div className="node-inspector">
        <div className="empty-message">Empty</div>
      </div>
    );
  }

  return (
    <div className="node-inspector">
      <div className="inspector-content">
        <NodeParameter 
          node={node} 
          level={0} 
          onToggle={handleToggle}
          onContextMenu={handleContextMenu}
        />
      </div>

      {/* Context Menu */}
      {contextMenu && (
        <ContextMenu
          items={nodeInspectorContextMenuItems}
          x={contextMenu.x}
          y={contextMenu.y}
          onClose={handleContextMenuClose}
          onItemClick={handleContextMenuAction}
        />
      )}
    </div>
  );
}
