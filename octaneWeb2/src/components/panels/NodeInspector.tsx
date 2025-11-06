import React, { useState } from 'react';
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
  const [expandedGroups, setExpandedGroups] = useState<Set<string>>(
    new Set(['Physical camera parameters', 'Clipping'])
  );

  // Mock parameter data matching the screenshot
  const mockGroups: ParameterGroup[] = [
    {
      name: 'Scene',
      expanded: true,
      parameters: []
    },
    {
      name: 'Camera',
      expanded: true,
      parameters: []
    },
    {
      name: 'Orthographic',
      expanded: false,
      parameters: []
    },
    {
      name: 'Physical camera parameters',
      expanded: true,
      parameters: [
        { name: 'Sensor width', type: 'float', value: 50.000004, min: 0 },
        { name: 'Focal length', type: 'float', value: 50, min: 0 },
        { name: 'Fstop', type: 'float', value: 2.8 },
        { name: 'Viewing angle', type: 'float', value: 0 },
        { name: 'Field of view', type: 'float', value: 35.03775 },
        { name: 'Outer of view', type: 'float', value: 15.547005 },
        { name: 'Distortion', type: 'float', value: 0 },
        { name: 'Lens shift', type: 'vector', value: { x: 0, y: 0 } },
        { name: 'Perspective correction', type: 'bool', value: true }
      ]
    },
    {
      name: 'Post aspect ratio',
      expanded: false,
      parameters: [
        { name: 'Post aspect ratio', type: 'float', value: 1 }
      ]
    },
    {
      name: 'Clipping',
      expanded: true,
      parameters: [
        { name: 'Near clip depth', type: 'float', value: 0 },
        { name: 'Far clip depth', type: 'float', value: 100000000 },
        { name: 'Depth of field', type: 'float', value: 0 },
        { name: 'Auto-focus', type: 'bool', value: true },
        { name: 'Focal depth', type: 'float', value: 1.118034 },
        { name: 'Aperture', type: 'float', value: 0.0203572 },
        { name: 'Aperture aspect ratio', type: 'float', value: 1 },
        { name: 'Aperture edge', type: 'float', value: 1 }
      ]
    },
    {
      name: 'Position',
      expanded: true,
      parameters: [
        { name: 'Position', type: 'vector', value: { x: -0.280283, y: 1.786282, z: 21.050143 } }
      ]
    },
    {
      name: 'Target',
      expanded: false,
      parameters: []
    },
    {
      name: 'Up-vector',
      expanded: false,
      parameters: []
    },
    {
      name: 'Stereo',
      expanded: false,
      parameters: []
    }
  ];

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

  return (
    <aside className={`node-inspector-panel ${className}`}>
      <div className="panel-header">
        <h3>Node Inspector</h3>
      </div>

      <div className="inspector-content">
        {mockGroups.length > 0 ? (
          mockGroups.map(group => (
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
          <div className="empty-message">
            Select a node to inspect
          </div>
        )}
      </div>
    </aside>
  );
};
