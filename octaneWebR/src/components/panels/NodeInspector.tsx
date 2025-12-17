import React from 'react';
import { useSceneStore } from '../../store/sceneStore';

const NodeInspector: React.FC<{ connected: boolean }> = ({ connected }) => {
  const { selectedNode } = useSceneStore();

  return (
    <div className="node-inspector">
      <header className="panel-header">
        <h3>NODE INSPECTOR</h3>
      </header>

      <div className="inspector-content">
        {!connected ? (
          <div className="empty-message">
            Connect to Octane to inspect nodes
          </div>
        ) : !selectedNode ? (
          <div className="empty-message">
            Select a node to inspect
          </div>
        ) : (
          <div className="parameter-list">
            <div className="parameter-row">
              <label className="param-label">Name</label>
              <div className="param-control">{selectedNode.name}</div>
            </div>
            <div className="parameter-row">
              <label className="param-label">Type</label>
              <div className="param-control">{selectedNode.type}</div>
            </div>
            <div className="parameter-row">
              <label className="param-label">ID</label>
              <div className="param-control">{selectedNode.id}</div>
            </div>
          </div>
        )}
      </div>
    </div>
  );
};

export default NodeInspector;
