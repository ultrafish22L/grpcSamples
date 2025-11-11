import React, { useState, useEffect, useCallback } from 'react';
import { useSceneStore } from '../../store/sceneStore';
import { useConnectionStore } from '../../store/connectionStore';
import { octaneClient, SceneNode } from '../../api/octaneClient';
import './NodeInspector.css';

interface Parameter {
  name: string;
  type: 'float' | 'int' | 'bool' | 'string' | 'enum' | 'color' | 'vector';
  value: any;
  min?: number;
  max?: number;
  options?: string[];
}

interface ParameterGroup {
  name: string;
  expanded: boolean;
  parameters: Parameter[];
}

interface NodeInspectorProps {
  className?: string;
}

export const NodeInspector: React.FC<NodeInspectorProps> = ({ className = '' }) => {
  const [expandedGroups, setExpandedGroups] = useState<Set<string>>(new Set());
  const [parameterGroups, setParameterGroups] = useState<ParameterGroup[]>([]);
  const [loading, setLoading] = useState(false);
  const [nodeName, setNodeName] = useState<string>('');
  
  const { selectedNode } = useSceneStore();
  const { isConnected } = useConnectionStore();

  const loadNodeParameters = useCallback(async (node: SceneNode) => {
    setLoading(true);
    try {
      const handle = node.handle;
      
      // Get node info
      const nodeInfo = await octaneClient.getNodeInfo(handle);
      if (nodeInfo) {
        setNodeName(nodeInfo.name || `Node ${handle}`);
      }
      
      // Get node parameters (not yet implemented)
      const params = await octaneClient.getNodeParameters(handle, node.objectType);
      
      // For now, show empty state - parameters will be implemented later
      setParameterGroups([]);
      
      console.log('Node info:', nodeInfo);
      console.log('Node parameters:', params);
    } catch (error) {
      console.error('Failed to load node parameters:', error);
      setParameterGroups([]);
    } finally {
      setLoading(false);
    }
  }, []);

  // Load node parameters when selection changes
  useEffect(() => {
    if (isConnected && selectedNode) {
      loadNodeParameters(selectedNode);
    } else {
      setParameterGroups([]);
      setNodeName('');
    }
  }, [isConnected, selectedNode, loadNodeParameters]);

  // No mock data - show real data only
  const mockGroups: ParameterGroup[] = [];

  const toggleGroup = (groupName: string) => {
    setExpandedGroups(prev => {
      const next = new Set(prev);
      if (next.has(groupName)) {
        next.delete(groupName);
      } else {
        next.add(groupName);
      }
      return next;
    });
  };

  const renderParameterInput = (param: Parameter) => {
    switch (param.type) {
      case 'bool':
        return (
          <label className="param-checkbox">
            <input type="checkbox" checked={param.value} readOnly />
            <span className="checkbox-mark"></span>
          </label>
        );
      
      case 'float':
      case 'int':
        return (
          <input
            type="number"
            value={param.value}
            step={param.type === 'float' ? 0.01 : 1}
            className="param-input param-number"
            readOnly
          />
        );
      
      case 'vector':
        return (
          <div className="param-vector">
            <input type="number" value={param.value.x} className="param-input param-number-small" readOnly />
            <input type="number" value={param.value.y} className="param-input param-number-small" readOnly />
            {param.value.z !== undefined && (
              <input type="number" value={param.value.z} className="param-input param-number-small" readOnly />
            )}
          </div>
        );
      
      case 'enum':
        return (
          <select className="param-input param-select" value={param.value} disabled>
            {param.options?.map(opt => (
              <option key={opt} value={opt}>{opt}</option>
            ))}
          </select>
        );
      
      case 'color':
        return (
          <div className="param-color">
            <div className="color-swatch" style={{ backgroundColor: param.value }}></div>
            <input type="text" value={param.value} className="param-input" readOnly />
          </div>
        );
      
      default:
        return (
          <input type="text" value={param.value} className="param-input" readOnly />
        );
    }
  };

  const groupsToRender = parameterGroups.length > 0 ? parameterGroups : mockGroups;

  return (
    <aside className={`node-inspector-panel ${className}`}>
      <div className="panel-header">
        <h3>Node Inspector</h3>
        {nodeName && <div className="node-name">{nodeName}</div>}
      </div>

      <div className="inspector-content">
        {loading ? (
          <div className="empty-message">Loading parameters...</div>
        ) : !isConnected ? (
          <div className="empty-message">Connect to Octane to inspect nodes</div>
        ) : !selectedNode ? (
          <div className="empty-message">Select a node to inspect</div>
        ) : groupsToRender.length > 0 ? (
          groupsToRender.map(group => (
            <div key={group.name} className="param-group">
              <div 
                className="param-group-header"
                onClick={() => toggleGroup(group.name)}
              >
                <span className="expand-icon">
                  {expandedGroups.has(group.name) ? '▼' : '▶'}
                </span>
                <span className="group-name">{group.name}</span>
              </div>
              {expandedGroups.has(group.name) && group.parameters.length > 0 && (
                <div className="param-group-content">
                  {group.parameters.map(param => (
                    <div key={param.name} className="param-row">
                      <label className="param-label">{param.name}</label>
                      <div className="param-value">
                        {renderParameterInput(param)}
                      </div>
                    </div>
                  ))}
                </div>
              )}
            </div>
          ))
        ) : (
          <div className="empty-message">No parameters available</div>
        )}
      </div>
    </aside>
  );
};
