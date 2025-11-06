import React, { useRef, useEffect, useState } from 'react';
import './NodeGraph.css';

interface NodeGraphProps {
  className?: string;
}

export const NodeGraph: React.FC<NodeGraphProps> = ({ className = '' }) => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [isPanning, setIsPanning] = useState(false);
  const [panOffset, setPanOffset] = useState({ x: 0, y: 0 });
  const [lastMousePos, setLastMousePos] = useState({ x: 0, y: 0 });

  // No mock data - will be loaded from Octane
  const nodes: any[] = [];

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;

    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    // Set canvas size
    const updateSize = () => {
      const rect = canvas.parentElement?.getBoundingClientRect();
      if (rect) {
        canvas.width = rect.width;
        canvas.height = rect.height;
        drawGraph();
      }
    };

    const drawGraph = () => {
      // Clear canvas
      ctx.fillStyle = '#1a1a1a';
      ctx.fillRect(0, 0, canvas.width, canvas.height);

      // Draw grid
      ctx.strokeStyle = '#2a2a2a';
      ctx.lineWidth = 1;
      
      const gridSize = 20;
      for (let x = panOffset.x % gridSize; x < canvas.width; x += gridSize) {
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x, canvas.height);
        ctx.stroke();
      }
      for (let y = panOffset.y % gridSize; y < canvas.height; y += gridSize) {
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(canvas.width, y);
        ctx.stroke();
      }

      // Draw connections (only if nodes exist)
      if (nodes.length >= 2) {
        ctx.strokeStyle = '#5ac8fa';
        ctx.lineWidth = 2;
        ctx.beginPath();
        ctx.moveTo(nodes[0].x + panOffset.x, nodes[0].y + nodes[0].height / 2 + panOffset.y);
        ctx.bezierCurveTo(
          nodes[0].x - 50 + panOffset.x,
          nodes[0].y + nodes[0].height / 2 + panOffset.y,
          nodes[1].x + nodes[1].width + 50 + panOffset.x,
          nodes[1].y + nodes[1].height / 2 + panOffset.y,
          nodes[1].x + nodes[1].width + panOffset.x,
          nodes[1].y + nodes[1].height / 2 + panOffset.y
        );
        ctx.stroke();
      }

      // Draw nodes
      nodes.forEach(node => {
        const x = node.x + panOffset.x;
        const y = node.y + panOffset.y;

        // Node background
        ctx.fillStyle = '#2a2a2a';
        ctx.fillRect(x, y, node.width, node.height);

        // Node border
        ctx.strokeStyle = node.color;
        ctx.lineWidth = 2;
        ctx.strokeRect(x, y, node.width, node.height);

        // Node header
        ctx.fillStyle = node.color;
        ctx.fillRect(x, y, node.width, 20);

        // Node name
        ctx.fillStyle = '#fff';
        ctx.font = '11px sans-serif';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.fillText(node.name, x + node.width / 2, y + 10);
      });
    };

    updateSize();
    window.addEventListener('resize', updateSize);

    return () => {
      window.removeEventListener('resize', updateSize);
    };
  }, [panOffset]);

  const handleMouseDown = (e: React.MouseEvent) => {
    if (e.button === 1 || (e.button === 0 && e.altKey)) {
      setIsPanning(true);
      setLastMousePos({ x: e.clientX, y: e.clientY });
      e.preventDefault();
    }
  };

  const handleMouseMove = (e: React.MouseEvent) => {
    if (isPanning) {
      const dx = e.clientX - lastMousePos.x;
      const dy = e.clientY - lastMousePos.y;
      setPanOffset(prev => ({ x: prev.x + dx, y: prev.y + dy }));
      setLastMousePos({ x: e.clientX, y: e.clientY });
    }
  };

  const handleMouseUp = () => {
    setIsPanning(false);
  };

  return (
    <div className={`node-graph-panel ${className}`}>
      <div className="panel-header">
        <h3>Node Graph Editor</h3>
        <div className="graph-controls">
          <button className="control-btn" title="Zoom In">+</button>
          <button className="control-btn" title="Zoom Out">-</button>
          <button className="control-btn" title="Fit View">⊡</button>
        </div>
      </div>
      <div className="graph-container">
        <canvas
          ref={canvasRef}
          className="graph-canvas"
          onMouseDown={handleMouseDown}
          onMouseMove={handleMouseMove}
          onMouseUp={handleMouseUp}
          onMouseLeave={handleMouseUp}
        />
      </div>
    </div>
  );
};
