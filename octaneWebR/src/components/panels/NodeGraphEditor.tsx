import React, { useRef } from 'react';

const NodeGraphEditor: React.FC<{ connected: boolean }> = ({ connected }) => {
  const canvasRef = useRef<HTMLCanvasElement>(null);

  return (
    <div className="node-graph-editor">
      <header className="graph-header">
        <h4>NODE GRAPH EDITOR</h4>
        <div className="graph-controls">
          <button title="Zoom in">+</button>
          <button title="Zoom out">-</button>
          <button title="Fit all">⊡</button>
        </div>
      </header>

      <canvas
        ref={canvasRef}
        className="node-graph-canvas"
        width={800}
        height={400}
        style={{
          width: '100%',
          height: '100%',
          backgroundColor: '#2a2a2a'
        }}
      />

      {!connected && (
        <div className="viewport-overlay">
          <div className="empty-message">
            Connect to Octane to edit node graph
          </div>
        </div>
      )}
    </div>
  );
};

export default NodeGraphEditor;
