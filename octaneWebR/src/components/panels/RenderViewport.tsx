import React, { useRef } from 'react';

const RenderViewport: React.FC<{ connected: boolean }> = ({ connected }) => {
  const canvasRef = useRef<HTMLCanvasElement>(null);

  return (
    <div className="render-viewport">
      <header className="viewport-header">
        <h4>Render Viewport</h4>
        <div className="viewport-controls">
          {/* Add controls later */}
        </div>
      </header>
      
      <canvas
        ref={canvasRef}
        className="render-canvas"
        width={800}
        height={600}
        style={{
          width: '100%',
          height: '100%',
          backgroundColor: '#1a1a1a'
        }}
      />
      
      {!connected && (
        <div className="viewport-overlay">
          <div className="empty-message">
            Connect to Octane to view render
          </div>
        </div>
      )}
    </div>
  );
};

export default RenderViewport;
