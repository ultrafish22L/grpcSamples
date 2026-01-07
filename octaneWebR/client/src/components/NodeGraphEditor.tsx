/**
 * Node Graph Editor Component (React TypeScript)
 * Visual node-based editor showing scene hierarchy as a graph
 */

import React, { useState, useEffect, useRef } from 'react';
import { SceneNode } from '../services/OctaneClient';
import { useOctane } from '../hooks/useOctane';
import { OctaneIconMapper } from '../utils/OctaneIconMapper';

interface NodeGraphEditorProps {
  selectedNode?: SceneNode | null;
}

interface GraphNode {
  id: number;
  data: SceneNode;
  x: number;
  y: number;
  width: number;
  height: number;
}

interface GraphConnection {
  from: number;
  to: number;
  fromSocket: { x: number; y: number };
  toSocket: { x: number; y: number };
}

export function NodeGraphEditor({ selectedNode }: NodeGraphEditorProps) {
  const { client, connected } = useOctane();
  const [nodes, setNodes] = useState<GraphNode[]>([]);
  const [connections, setConnections] = useState<GraphConnection[]>([]);
  const [viewport, setViewport] = useState({ x: 0, y: 0, zoom: 1 });
  const [isDragging, setIsDragging] = useState(false);
  const [dragStart, setDragStart] = useState({ x: 0, y: 0 });
  const containerRef = useRef<HTMLDivElement>(null);

  // Listen to scene tree updates from OctaneClient (don't load independently)
  useEffect(() => {
    if (!connected) return;
    
    const handleSceneUpdate = (_scene: any) => {
      console.log('📊 NodeGraphEditor: Scene updated, rendering graph');
      loadSceneGraph();
    };
    
    client.on('sceneTreeUpdated', handleSceneUpdate);
    
    // Load existing scene if available
    if (client.getScene().tree.length > 0) {
      loadSceneGraph();
    }
    
    return () => {
      client.off('sceneTreeUpdated', handleSceneUpdate);
    };
  }, [connected]);

  const loadSceneGraph = async () => {
    try {
      // Use existing scene data from client (don't call buildSceneTree again)
      const sceneTree = client.getScene().tree;
      
      if (sceneTree.length === 0) {
        console.log('No scene nodes to display in graph');
        return;
      }

      // Layout nodes horizontally
      const nodeSpacing = 220;
      const yCenter = 200;
      
      // Use Map to prevent duplicate nodes
      const nodeMap = new Map<number, GraphNode>();
      const graphConnections: GraphConnection[] = [];

      // First pass: collect all unique nodes
      const collectNodes = (items: SceneNode[], level: number = 0) => {
        items.forEach((item) => {
          // Skip items without a handle
          if (typeof item.handle !== 'number') {
            return;
          }
          
          if (!nodeMap.has(item.handle)) {
            const node: GraphNode = {
              id: item.handle,
              data: item,
              x: 100 + nodeMap.size * nodeSpacing,
              y: yCenter + level * 150,
              width: 180,
              height: 80
            };
            nodeMap.set(item.handle, node);
          }
          
          // Recursively collect children
          if (item.children && item.children.length > 0) {
            collectNodes(item.children, level + 1);
          }
        });
      };

      collectNodes(sceneTree);

      // Second pass: create connections from parents to children
      sceneTree.forEach((item) => {
        const processConnections = (parent: SceneNode) => {
          if (parent.children && parent.children.length > 0 && typeof parent.handle === 'number') {
            const parentNode = nodeMap.get(parent.handle);
            
            parent.children.forEach((child) => {
              if (typeof child.handle !== 'number') {
                return;
              }
              const childNode = nodeMap.get(child.handle);
              
              if (parentNode && childNode) {
                graphConnections.push({
                  from: parentNode.id,
                  to: childNode.id,
                  fromSocket: { x: parentNode.x + parentNode.width / 2, y: parentNode.y + parentNode.height },
                  toSocket: { x: childNode.x + childNode.width / 2, y: childNode.y }
                });
              }
              
              // Recursively process child connections
              processConnections(child);
            });
          }
        };
        
        processConnections(item);
      });

      const graphNodes = Array.from(nodeMap.values());
      setNodes(graphNodes);
      setConnections(graphConnections);
      
      console.log(`✅ Loaded ${graphNodes.length} nodes with ${graphConnections.length} connections`);
    } catch (error) {
      console.error('Failed to load scene graph:', error);
    }
  };

  // Handle pan/zoom
  const handleMouseDown = (e: React.MouseEvent) => {
    if (e.button === 0) { // Left click
      setIsDragging(true);
      setDragStart({ x: e.clientX - viewport.x, y: e.clientY - viewport.y });
    }
  };

  const handleMouseMove = (e: React.MouseEvent) => {
    if (isDragging) {
      setViewport({
        ...viewport,
        x: e.clientX - dragStart.x,
        y: e.clientY - dragStart.y
      });
    }
  };

  const handleMouseUp = () => {
    setIsDragging(false);
  };

  const handleWheel = (e: React.WheelEvent) => {
    e.preventDefault();
    const zoomFactor = e.deltaY > 0 ? 0.9 : 1.1;
    setViewport({
      ...viewport,
      zoom: Math.max(0.1, Math.min(2, viewport.zoom * zoomFactor))
    });
  };

  // Get node icon using OctaneIconMapper
  const getNodeIcon = (node: SceneNode): string => {
    const typeStr = String(node.type || node.outType || 'unknown');
    return OctaneIconMapper.getNodeIcon(typeStr, node.name);
  };

  // Get node color
  const getNodeColor = (node: SceneNode): string => {
    if (node.nodeInfo?.nodeColor) {
      const { x, y, z } = node.nodeInfo.nodeColor;
      const r = Math.round((x || 0) * 255);
      const g = Math.round((y || 0) * 255);
      const b = Math.round((z || 0) * 255);
      return `rgb(${r}, ${g}, ${b})`;
    }
    return '#666';
  };

  // Draw bezier connection curve
  const getConnectionPath = (conn: GraphConnection): string => {
    const { fromSocket, toSocket } = conn;
    const midY = (fromSocket.y + toSocket.y) / 2;
    return `M ${fromSocket.x} ${fromSocket.y} 
            C ${fromSocket.x} ${midY}, 
              ${toSocket.x} ${midY}, 
              ${toSocket.x} ${toSocket.y}`;
  };

  if (!connected) {
    return (
      <div className="node-graph-empty">
        <p>Connect to Octane to view node graph</p>
      </div>
    );
  }

  if (nodes.length === 0) {
    return (
      <div className="node-graph-empty">
        <p>No scene nodes available</p>
        <button onClick={loadSceneGraph} className="reload-btn">
          🔄 Reload Scene Graph
        </button>
      </div>
    );
  }

  return (
    <div 
      ref={containerRef}
      className="node-graph-svg-container"
      onMouseDown={handleMouseDown}
      onMouseMove={handleMouseMove}
      onMouseUp={handleMouseUp}
      onMouseLeave={handleMouseUp}
      onWheel={handleWheel}
      style={{ cursor: isDragging ? 'grabbing' : 'grab' }}
    >
      <svg 
        width="100%" 
        height="100%" 
        style={{ background: '#1a1a1a' }}
      >
        <g transform={`translate(${viewport.x}, ${viewport.y}) scale(${viewport.zoom})`}>
          {/* Draw connections first (behind nodes) */}
          {connections.map((conn, idx) => (
            <path
              key={`conn-${idx}`}
              d={getConnectionPath(conn)}
              stroke="#4a90e2"
              strokeWidth={2}
              fill="none"
            />
          ))}

          {/* Draw nodes */}
          {nodes.map(node => {
            const isSelected = selectedNode?.handle === node.id;
            const color = getNodeColor(node.data);
            const icon = getNodeIcon(node.data);

            return (
              <g key={node.id} transform={`translate(${node.x}, ${node.y})`}>
                {/* Node box */}
                <rect
                  width={node.width}
                  height={node.height}
                  rx={4}
                  fill={color}
                  stroke={isSelected ? '#4a90e2' : '#555'}
                  strokeWidth={isSelected ? 2 : 1}
                />

                {/* Node header */}
                <rect
                  width={node.width}
                  height={28}
                  rx={4}
                  fill="rgba(0,0,0,0.3)"
                />

                {/* Node icon */}
                <text
                  x={10}
                  y={20}
                  fill="#fff"
                  fontSize="16"
                >
                  {icon}
                </text>

                {/* Node name */}
                <text
                  x={35}
                  y={20}
                  fill="#fff"
                  fontSize="12"
                  fontFamily="Arial"
                >
                  {node.data.name}
                </text>

                {/* Node type */}
                <text
                  x={node.width / 2}
                  y={node.height / 2 + 15}
                  fill="#bbb"
                  fontSize="10"
                  fontFamily="Arial"
                  textAnchor="middle"
                >
                  {node.data.type}
                </text>

                {/* Input socket (top center) */}
                {node.data.children && node.data.children.length > 0 && (
                  <circle
                    cx={node.width / 2}
                    cy={0}
                    r={4}
                    fill="#f4f7f6"
                    stroke="#555"
                  />
                )}

                {/* Output socket (bottom center) */}
                <circle
                  cx={node.width / 2}
                  cy={node.height}
                  r={4}
                  fill="#f4f7f6"
                  stroke="#555"
                />
              </g>
            );
          })}
        </g>
      </svg>

      {/* Zoom controls overlay */}
      <div className="node-graph-zoom-overlay">
        <div className="zoom-info">Zoom: {(viewport.zoom * 100).toFixed(0)}%</div>
        <button onClick={() => setViewport({ ...viewport, zoom: 1, x: 0, y: 0 })}>
          Reset View
        </button>
      </div>
    </div>
  );
}
