/**
 * Node Inspector Component (React TypeScript)
 * Displays properties of selected scene node
 */

import React from 'react';
import { SceneNode } from '../services/OctaneClient';

interface NodeInspectorProps {
  node: SceneNode | null;
}

export function NodeInspector({ node }: NodeInspectorProps) {
  if (!node) {
    return (
      <div className="node-inspector">
        <h3>Node Inspector</h3>
        <p className="status-text">Select a node to view properties</p>
      </div>
    );
  }

  return (
    <div className="node-inspector">
      <h3>Node Inspector</h3>
      <div className="inspector-content">
        <div className="property-group">
          <div className="property">
            <label>Name:</label>
            <span>{node.name}</span>
          </div>
          <div className="property">
            <label>Type:</label>
            <span>{node.type}</span>
          </div>
          <div className="property">
            <label>Handle:</label>
            <span>{node.handle}</span>
          </div>
          <div className="property">
            <label>Visible:</label>
            <span>{node.visible ? 'Yes' : 'No'}</span>
          </div>
        </div>

        {node.children && node.children.length > 0 && (
          <div className="property-group">
            <h4>Children</h4>
            <p>{node.children.length} child nodes</p>
          </div>
        )}

        <div className="property-group">
          <h4>Raw Data</h4>
          <pre className="raw-data">
            {JSON.stringify(node, null, 2)}
          </pre>
        </div>
      </div>
    </div>
  );
}
