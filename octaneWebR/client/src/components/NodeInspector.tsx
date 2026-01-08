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
import { OctaneIconMapper } from '../utils/OctaneIconMapper';

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
  const groupIcon = OctaneIconMapper.getPinGroupIcon(groupName);

  return (
    <div className="inspector-group-indent">
      <div 
        className={`inspector-group-header ${expanded ? 'expanded' : 'collapsed'}`}
        onClick={() => setExpanded(!expanded)}
      >
        <span className="inspector-group-icon">{expanded ? '▼' : '▶'}</span>
        <span className="inspector-group-name-icon">{groupIcon}</span>
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

// Track hasGroup at each level (matching GenericNodeRenderer grouping logic)
// This will be used in future updates to match octaneWeb's group nesting behavior
const hasGroupAtLevel: boolean[] = [];

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
  const typeStr = String(node.type || node.outType || 'unknown');
  const icon = node.icon || OctaneIconMapper.getNodeIcon(typeStr, node.name);
  const color = node.nodeInfo?.nodeColor ? OctaneIconMapper.formatNodeColor(node.nodeInfo.nodeColor) : '#666';
  const name = node.pinInfo?.staticLabel || node.name;

  // Fetch parameter value for end nodes (matching octaneWeb's GenericNodeRenderer.getValue())
  useEffect(() => {
    const fetchValue = async () => {
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

      try {
        // attrInfo.type is already a STRING like "AT_FLOAT3" from the API
        // Use it directly, no conversion needed
        const expectedType = AttrType[node.attrInfo.type as keyof typeof AttrType];
        
        console.log(`🔍 Calling getByAttrID for ${node.name}:`);
        console.log(`  - attribute_id: ${AttributeId.A_VALUE}`);
        console.log(`  - expected_type: ${expectedType}`);

        // Pass just the handle string - callApi will wrap it in objectPtr automatically
        const response = await client.callApi(
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
            type: expectedType
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

  // Render the parameter control based on type (matching octaneWeb GenericNodeRenderer exactly)
  const renderParameterControl = () => {
    if (!paramValue) return null;

    const { value, type } = paramValue;

    // Controls must be wrapped in parameter-control-container or parameter-checkbox-container
    // which are then wrapped in node-parameter-controls div (matching octaneWeb structure)
    let controlHtml = null;

    switch (type) {
      case AttrType.AT_BOOL: {
        const boolValue = typeof value === 'boolean' ? value : false;
        controlHtml = (
          <div className="parameter-checkbox-container">
            <input 
              type="checkbox" 
              className="octane-checkbox parameter-control" 
              checked={boolValue}
              onChange={(e) => handleValueChange(e.target.checked)}
              style={{ background: '#2b2b2b' }}
            />
          </div>
        );
        break;
      }
      
      case AttrType.AT_FLOAT: {
        const floatValue = typeof value === 'number' ? value : 0;
        controlHtml = (
          <div className="parameter-control-container">
            <input 
              type="number" 
              className="octane-number-input parameter-control" 
              value={floatValue || 0}
              step="0.001"
              onChange={(e) => handleValueChange(parseFloat(e.target.value))}
            />
          </div>
        );
        break;
      }
      
      case AttrType.AT_FLOAT2: {
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0 } = value;
          controlHtml = (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={x || 0}
                step="0.001"
                onChange={(e) => handleValueChange({ x: parseFloat(e.target.value), y })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={y || 0}
                step="0.001"
                onChange={(e) => handleValueChange({ x, y: parseFloat(e.target.value) })}
              />
            </div>
          );
        }
        break;
      }
      
      case AttrType.AT_FLOAT3: {
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0, z = 0 } = value;
          
          // Check if this is a color (NT_TEX_RGB)
          if (node.nodeInfo?.type === 'NT_TEX_RGB') {
            const hexColor = OctaneIconMapper.formatColorValue(value);
            controlHtml = (
              <div className="parameter-control-container">
                <input 
                  type="color" 
                  className="octane-color-input parameter-control" 
                  value={hexColor}
                  style={{ background: hexColor, color: hexColor }}
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
          } else {
            controlHtml = (
              <div className="parameter-control-container">
                <input 
                  type="number" 
                  className="octane-number-input parameter-control" 
                  value={x || 0}
                  step="0.001"
                  onChange={(e) => handleValueChange({ x: parseFloat(e.target.value), y, z })}
                />
                <input 
                  type="number" 
                  className="octane-number-input parameter-control" 
                  value={y || 0}
                  step="0.001"
                  onChange={(e) => handleValueChange({ x, y: parseFloat(e.target.value), z })}
                />
                <input 
                  type="number" 
                  className="octane-number-input parameter-control" 
                  value={z || 0}
                  step="0.001"
                  onChange={(e) => handleValueChange({ x, y, z: parseFloat(e.target.value) })}
                />
              </div>
            );
          }
        }
        break;
      }
      
      case AttrType.AT_FLOAT4: {
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0, z = 0, w = 0 } = value;
          const dimCount = node.pinInfo?.floatInfo?.dimCount || 4;
          
          // Render based on dimension count (matching octaneWeb exactly)
          switch (dimCount) {
            case 1:
              controlHtml = (
                <div className="parameter-control-container">
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={x || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x: parseFloat(e.target.value), y, z, w })}
                  />
                </div>
              );
              break;
            case 2:
              controlHtml = (
                <div className="parameter-control-container">
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={x || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x: parseFloat(e.target.value), y, z, w })}
                  />
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={y || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x, y: parseFloat(e.target.value), z, w })}
                  />
                </div>
              );
              break;
            case 3:
              controlHtml = (
                <div className="parameter-control-container">
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={x || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x: parseFloat(e.target.value), y, z, w })}
                  />
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={y || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x, y: parseFloat(e.target.value), z, w })}
                  />
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={z || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x, y, z: parseFloat(e.target.value), w })}
                  />
                </div>
              );
              break;
            default: // 4 components
              controlHtml = (
                <div className="parameter-control-container">
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={x || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x: parseFloat(e.target.value), y, z, w })}
                  />
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={y || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x, y: parseFloat(e.target.value), z, w })}
                  />
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={z || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x, y, z: parseFloat(e.target.value), w })}
                  />
                  <input 
                    type="number" 
                    className="octane-number-input parameter-control" 
                    value={w || 0}
                    step="0.001"
                    onChange={(e) => handleValueChange({ x, y, z, w: parseFloat(e.target.value) })}
                  />
                </div>
              );
              break;
          }
        }
        break;
      }
      
      case AttrType.AT_INT: {
        const intValue = typeof value === 'number' ? value : 0;
        
        // Check if this is an enum (NT_ENUM) - render dropdown
        if (node.nodeInfo?.type === 'NT_ENUM') {
          // TODO: Fetch enum options and render dropdown
          // For now, render as number input
          controlHtml = (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={intValue || 0}
                step="1"
                onChange={(e) => handleValueChange(parseInt(e.target.value))}
              />
            </div>
          );
        } else {
          controlHtml = (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={intValue || 0}
                step="1"
                onChange={(e) => handleValueChange(parseInt(e.target.value))}
              />
            </div>
          );
        }
        break;
      }
      
      case AttrType.AT_INT2: {
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0 } = value;
          controlHtml = (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={x || 0}
                step="1"
                onChange={(e) => handleValueChange({ x: parseInt(e.target.value), y })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={y || 0}
                step="1"
                onChange={(e) => handleValueChange({ x, y: parseInt(e.target.value) })}
              />
            </div>
          );
        }
        break;
      }
      
      case AttrType.AT_INT3: {
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0, z = 0 } = value;
          controlHtml = (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={x || 0}
                step="1"
                onChange={(e) => handleValueChange({ x: parseInt(e.target.value), y, z })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={y || 0}
                step="1"
                onChange={(e) => handleValueChange({ x, y: parseInt(e.target.value), z })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={z || 0}
                step="1"
                onChange={(e) => handleValueChange({ x, y, z: parseInt(e.target.value) })}
              />
            </div>
          );
        }
        break;
      }
      
      case AttrType.AT_INT4: {
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0, z = 0, w = 0 } = value;
          controlHtml = (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={x || 0}
                step="1"
                onChange={(e) => handleValueChange({ x: parseInt(e.target.value), y, z, w })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={y || 0}
                step="1"
                onChange={(e) => handleValueChange({ x, y: parseInt(e.target.value), z, w })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={z || 0}
                step="1"
                onChange={(e) => handleValueChange({ x, y, z: parseInt(e.target.value), w })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={w || 0}
                step="1"
                onChange={(e) => handleValueChange({ x, y, z, w: parseInt(e.target.value) })}
              />
            </div>
          );
        }
        break;
      }
      
      case AttrType.AT_LONG: {
        const longValue = typeof value === 'number' ? value : 0;
        controlHtml = (
          <div className="parameter-control-container">
            <input 
              type="number" 
              className="octane-number-input parameter-control" 
              value={longValue || 0}
              step="1"
              onChange={(e) => handleValueChange(parseInt(e.target.value))}
            />
          </div>
        );
        break;
      }
      
      case AttrType.AT_LONG2: {
        if (value && typeof value === 'object' && 'x' in value) {
          const { x = 0, y = 0 } = value;
          controlHtml = (
            <div className="parameter-control-container">
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={x || 0}
                step="1"
                onChange={(e) => handleValueChange({ x: parseInt(e.target.value), y })}
              />
              <input 
                type="number" 
                className="octane-number-input parameter-control" 
                value={y || 0}
                step="1"
                onChange={(e) => handleValueChange({ x, y: parseInt(e.target.value) })}
              />
            </div>
          );
        }
        break;
      }
      
      case AttrType.AT_STRING: {
        const stringValue = typeof value === 'string' ? value : '';
        controlHtml = (
          <input 
            type="text" 
            className="octane-text-input parameter-control" 
            value={stringValue}
            onChange={(e) => handleValueChange(e.target.value)}
          />
        );
        break;
      }
      
      default: {
        // For unknown types, render as text input
        const stringValue = typeof value === 'string' ? value : '';
        controlHtml = (
          <input 
            type="text" 
            className="octane-text-input parameter-control" 
            value={stringValue}
            onChange={(e) => handleValueChange(e.target.value)}
          />
        );
        break;
      }
    }

    // Wrap in node-parameter-controls div (matching octaneWeb GenericNodeRenderer structure)
    return controlHtml ? (
      <div className="node-parameter-controls">
        {controlHtml}
      </div>
    ) : null;
  };

  // Determine the indent class (matching GenericNodeRenderer logic)
  // Future: use node.pinInfo?.groupName for advanced group nesting like octaneWeb
  const indentClass = level === 0 ? 'node-indent-0' : 
                     hasGroupAtLevel[level] ? 'node-indent-done' : 
                     'node-indent';

  // Determine collapse/expand icon
  const collapseIcon = hasChildren && level > 0 ? (expanded ? '▼' : '▶') : '';

  // Render as parameter node (end node with attrInfo)
  if (node.attrInfo) {
    return (
      <div className={indentClass} style={{ display: 'block' }}>
        <div className="node-box-parameter" data-node-handle={node.handle} data-node-id={nodeId}>
          <div className="node-icon-box" style={{ backgroundColor: color }}>
            <span className="node-icon">{icon}</span>
          </div>
          <div className="node-content">
            <div className="node-label" onClick={hasChildren ? handleToggle : undefined}>
              {collapseIcon && <span className="collapse-icon">{collapseIcon}</span>}
              <span className="node-title">{name}</span>
              {renderParameterControl()}
            </div>
          </div>
        </div>
        {hasChildren && (
          <div 
            className="node-toggle-content"
            data-toggle-content={nodeId}
            style={{ display: expanded ? 'block' : 'none' }}
          >
            {node.children!.map((child, childIdx) => (
              <NodeParameter
                key={`${child.handle}-${childIdx}`}
                node={child}
                level={level + 1}
                onToggle={onToggle}
              />
            ))}
          </div>
        )}
      </div>
    );
  }

  // Render as node group (non-parameter nodes)
  return (
    <div className={indentClass} style={{ display: 'block' }}>
      <div className="node-box" data-node-handle={node.handle} data-node-id={nodeId}>
        <div className="node-icon-box" style={{ backgroundColor: color }}>
          <span className="node-icon">{icon}</span>
        </div>
        <div className="node-content">
          <div className="node-label" onClick={hasChildren ? handleToggle : undefined}>
            {collapseIcon && <span className="collapse-icon">{collapseIcon}</span>}
            <span className="node-title">{name}</span>
          </div>
        </div>
      </div>
      {hasChildren && (
        <div 
          className="node-toggle-content"
          data-toggle-content={nodeId}
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
