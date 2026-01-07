/**
 * Node Inspector Component (React TypeScript)
 * Professional parameter editing interface matching Octane Render Studio exactly
 * 
 * This component replicates the exact layout and styling from the reference screenshot:
 * - Compact parameter rows with proper spacing
 * - Blue parameter icons on the left
 * - Parameter names in the center
 * - Input controls on the right (numbers with spinners, checkboxes, color bars)
 * - Proper grouping with collapsible sections
 * - Professional dark theme matching Octane Studio
 */

import React, { useState, useEffect } from 'react';
import { SceneNode } from '../services/OctaneClient';
import { useOctane } from '../hooks/useOctane';
import { AttributeId, AttrType } from '../constants/OctaneTypes';

interface NodeInspectorProps {
  node: SceneNode | null;
}

interface ParameterValue {
  value: any;
  type: number;
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
  onToggle 
}: { 
  node: SceneNode; 
  level: number; 
  onToggle: (nodeId: string) => void;
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

  // Fetch parameter value for end nodes (matching octaneWeb's GenericNodeRenderer.getValue())
  useEffect(() => {
    const fetchValue = () => {
      // Log every node to understand the tree structure
      if (level < 3) {  // Only log first 3 levels to avoid spam
        console.log(`📋 NodeParameter: "${node.name}" - hasChildren:${hasChildren}, has attrInfo:${!!node.attrInfo}, isEndNode:${isEndNode}, handle:${node.handle}`);
      }
      
      if (!node.attrInfo || !node.handle || !isEndNode) {
        return;  // Skip without verbose logging
      }
      
      console.log(`🔍 Fetching value for end node: "${node.name}"`);
      console.log(`  - handle: ${node.handle}`);
      console.log(`  - attrInfo.type: ${node.attrInfo.type}`);
      console.log(`  - AttributeId.A_VALUE: ${AttributeId.A_VALUE}`);
      
//      📨 Request body: {"objectPtr":{"handle":"1000349","type":16},"attribute_id":185,"expected_type":"AT_BOOL"}

      try {
    // attrInfo.type is already a STRING like "AT_FLOAT3" from the API
        // Use it directly, no conversion needed
        const expectedType = AttrType[node.attrInfo.type as keyof typeof AttrType];
        
        console.log(`🔍 Calling getByAttrID for ${node.name}:`);
        console.log(`  - attribute_id: ${AttributeId.A_VALUE}`);
        console.log(`  - expected_type: ${expectedType}`);

        // Pass just the handle string - callApi will wrap it in objectPtr automatically
        const response = client.callApi(
          'ApiItem',
          'getByAttrID',
          node.handle,  // Pass handle as string
          {
            attribute_id: AttributeId.A_VALUE, // 185 - Use constant instead of hardcoded value
            expected_type: expectedType  // number
          }
        );
        
        if (response) {
          console.log(`✅ Got value for ${node.name}:`, response);
          // Extract the actual value from the response
          // API returns format like: {float_value: 2, value: "float_value"}
          // We need to get the value from the field indicated by response.value
          const valueField = response.value || Object.keys(response)[0];
          const actualValue = response[valueField];
          
          setParamValue({
            value: actualValue,
            type: expectedType,
            raw: response  // Keep raw response for debugging
          });
        }
      } catch (error) {
        // Silently ignore - not all end nodes have values
        console.log(`❌ No value for ${node.name}:`, error);
      }
    };
    
    fetchValue();
  }, [isEndNode, node.handle, node.attrInfo, client]);

  const handleToggle = () => {
    setExpanded(!expanded);
    onToggle(nodeId);
  };

  // Handle parameter value change
  const handleValueChange = async (newValue: any) => {
    if (!node.handle || !node.attrInfo) return;
    
    try {
      // Update value through API (to be implemented)
      console.log(`📝 Value change for ${node.name}:`, newValue);
      // TODO: Call setByAttrID to update the value in Octane
    } catch (error) {
      console.error(`❌ Failed to update ${node.name}:`, error);
    }
  };

  // Get the proper parameter icon (blue gear for most parameters)
  const getParameterIcon = (attrType: string, nodeType?: string) => {
    // In the reference screenshot, most parameters show a blue gear icon
    // Only special cases like colors might show different icons
    if (attrType === 'AT_FLOAT3' && (node.name.toLowerCase().includes('color') || nodeType === 'NT_TEX_RGB')) {
      return '🎨'; // Color icon for color parameters
    }
    return '⚙'; // Blue gear icon for most parameters
  };

  // Render the parameter control based on type (matching reference screenshot exactly)
  const renderParameterControl = () => {
    if (!paramValue) return null;

    const { value, type } = paramValue;

    switch (type) {
      case AttrType.AT_BOOL:
        const boolValue = typeof value === 'boolean' ? value : false;
        return (
          <div className="parameter-checkbox-container">
            <input 
              type="checkbox" 
              className="octane-checkbox parameter-control" 
              checked={boolValue}
              onChange={(e) => handleValueChange(e.target.checked)}
            />
          </div>
        );
      
      case AttrType.AT_FLOAT:
        const floatValue = typeof value === 'number' ? value : 0;
        return (
          <div className="parameter-control-container">
            <input 
              type="number" 
              className="octane-number-input parameter-control" 
              value={floatValue.toFixed(3)}
              step="0.001"
              onChange={(e) => handleValueChange(parseFloat(e.target.value))}
            />
          </div>
        );
      
      case AttrType.AT_INT:
      case AttrType.AT_LONG:
        const intValue = typeof value === 'number' ? value : 0;
        return (
          <div className="parameter-control-wrapper">
            <input 
              type="number" 
              className="parameter-number-input" 
              value={intValue}
              step="1"
              onChange={(e) => handleValueChange(parseInt(e.target.value))}
            />
          </div>
        );
      
      case AttrType.AT_FLOAT2:
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0 } = value;
          return (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={x}
                step="0.001"
                onChange={(e) => handleValueChange({ x: parseFloat(e.target.value), y })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={y}
                step="0.001"
                onChange={(e) => handleValueChange({ x, y: parseFloat(e.target.value) })}
              />
            </div>
          );
        }
        return null;
      
      case AttrType.AT_FLOAT3:
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0, z = 0 } = value;
          
          // Check if this is a color parameter (matching reference screenshot)
          const isColor = node.nodeInfo?.type === 'NT_TEX_RGB' || 
                          node.name.toLowerCase().includes('color') ||
                          node.name.toLowerCase().includes('sky') ||
                          node.name.toLowerCase().includes('sunset');
          
          if (isColor) {
            // Display as color input (matching reference screenshot exactly)
            const r = Math.round(Math.max(0, Math.min(1, x)) * 255);
            const g = Math.round(Math.max(0, Math.min(1, y)) * 255);
            const b = Math.round(Math.max(0, Math.min(1, z)) * 255);
            const hexColor = `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
            
            return (
              <div className="parameter-control-container">
                <input 
                  type="color" 
                  className="octane-color-input parameter-control" 
                  value={hexColor}
                  title={`RGB: ${x.toFixed(3)}, ${y.toFixed(3)}, ${z.toFixed(3)}`}
                  onChange={(e) => {
                    const hex = e.target.value;
                    const r = parseInt(hex.substring(1, 3), 16) / 255;
                    const g = parseInt(hex.substring(3, 5), 16) / 255;
                    const b = parseInt(hex.substring(5, 7), 16) / 255;
                    handleValueChange({ x: r, y: g, z: b });
                  }}
                />
              </div>
            );
          }
          
          // Display as numeric vector (3 separate number inputs)
          return (
            <div className="parameter-control-wrapper parameter-vector3">
              <input 
                type="number" 
                className="parameter-number-input parameter-vector-component" 
                value={x.toFixed(6)}
                step="0.000001"
                onChange={(e) => handleValueChange({ x: parseFloat(e.target.value), y, z })}
              />
              <input 
                type="number" 
                className="parameter-number-input parameter-vector-component" 
                value={y.toFixed(6)}
                step="0.000001"
                onChange={(e) => handleValueChange({ x, y: parseFloat(e.target.value), z })}
              />
              <input 
                type="number" 
                className="parameter-number-input parameter-vector-component" 
                value={z.toFixed(6)}
                step="0.000001"
                onChange={(e) => handleValueChange({ x, y, z: parseFloat(e.target.value) })}
              />
            </div>
          );
        }
        return null;
      
      case AttrType.AT_LONG2:
      case AttrType.AT_INT2:
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0 } = value;
          return (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={x}
                step="1"
                onChange={(e) => handleValueChange({ x: parseInt(e.target.value), y })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={y}
                step="1"
                onChange={(e) => handleValueChange({ x, y: parseInt(e.target.value) })}
              />
            </div>
          );
        }
        return null;
      
      case AttrType.AT_STRING:
      case AttrType.AT_FILENAME:
        const stringValue = typeof value === 'string' ? value : '';
        return (
          <div className="parameter-control-container">
            <input 
              type="text" 
              className="octane-text-input parameter-control" 
              value={stringValue}
              onChange={(e) => handleValueChange(e.target.value)}
            />
          </div>
        );
      
      default:
        // For unknown types, display as read-only text
        const displayValue = value !== undefined 
          ? (typeof value === 'object' ? JSON.stringify(value) : String(value))
          : '';
        return (
          <span className="parameter-value">
            {displayValue}
          </span>
        );
    }
  };

  // Render as parameter row (matching reference screenshot exactly)
  if (isEndNode) {
    // Get the appropriate icon for this parameter type
    const getParameterIcon = (): string => {
      if (!paramValue) return '📷';
      
      switch (paramValue.type) {
        case AttrType.AT_BOOL:
          return '☑️';
        case AttrType.AT_FLOAT3:
          // Check if this is a color parameter
          if (node.nodeInfo?.type === 'NT_TEX_RGB' || 
              node.name.toLowerCase().includes('color') ||
              node.name.toLowerCase().includes('sky') ||
              node.name.toLowerCase().includes('sunset')) {
            return '🎨';
          }
          return '📷';
        case AttrType.AT_ENUM:
          return '📋';
        default:
          return '📷';
      }
    };
    
    return (
      <div className="octane-parameter-row" data-node-handle={node.handle}>
        <div className="octane-parameter-label">
          <div className="octane-parameter-icon">
            {getParameterIcon()}
          </div>
          <span className="octane-parameter-name">{name}</span>
        </div>
        <div className="octane-parameter-control">
          {renderParameterControl()}
        </div>
      </div>
    );
  }

  // Render as node group (matching reference screenshot)
  return (
    <div className={level === 0 ? 'node-indent-0' : 'node-indent'}>
      <div className="node-box" data-node-handle={node.handle}>
        <div className="node-icon-box" style={{ backgroundColor: color }}>
          <span className="node-icon">{icon}</span>
        </div>
        <div className="node-content">
          <div className="node-label" onClick={hasChildren ? handleToggle : undefined}>
            {hasChildren && (
              <span className="collapse-icon">{expanded ? '▼' : '▶'}</span>
            )}
            <span className="node-title">{name}</span>
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
                <ParameterGroup key={`group-${groupName}-${idx}`} groupName={groupName}>
                  {children.map((child, childIdx) => (
                    <NodeParameter
                      key={`${child.handle}-${childIdx}`}
                      node={child}
                      level={level + 1}
                      onToggle={onToggle}
                    />
                  ))}
                </ParameterGroup>
              );
            } else {
              // Fix: Wrap ungrouped children in a Fragment to avoid array-within-array
              return (
                <React.Fragment key={`nogroup-${idx}`}>
                  {children.map((child, childIdx) => (
                    <NodeParameter
                      key={`${child.handle}-${childIdx}`}
                      node={child}
                      level={level + 1}
                      onToggle={onToggle}
                    />
                  ))}
                </React.Fragment>
              );
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
  // NOTE: Node expansion state is managed internally by NodeParameter component
  const handleToggle = (_nodeId: string) => {
    // Placeholder for future centralized expansion state management
  };

  if (!node) {
    return (
      <div className="node-inspector">
        <div className="node-inspector-header">
          <div className="inspector-title">
            <span className="inspector-icon">🎯</span>
            <span>Node inspector</span>
          </div>
        </div>
        <div className="inspector-content">
          <div className="empty-message">Empty</div>
        </div>
      </div>
    );
  }

  return (
    <div className="octane-node-inspector">
      {/* Header with dropdown (matching reference screenshot) */}
      <div className="octane-inspector-header">
        <div className="octane-inspector-title">
          <span className="octane-inspector-icon">🎯</span>
          <span>Node inspector</span>
        </div>
        <div className="octane-inspector-dropdown">
          <select className="octane-inspector-target-select">
            <option value={node.name}>{node.name}</option>
          </select>
          <span className="octane-inspector-dropdown-arrow">▼</span>
        </div>
      </div>
      
      {/* Content */}
      <div className="octane-inspector-content">
        <NodeParameter 
          node={node} 
          level={0} 
          onToggle={handleToggle}
        />
      </div>
    </div>
  );
}
