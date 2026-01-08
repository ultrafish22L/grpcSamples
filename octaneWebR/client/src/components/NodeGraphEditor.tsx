/**
 * Node Graph Editor Component (React TypeScript)
 * Visual node-based editor showing scene hierarchy as a graph
 * Enhanced with full node editor features: sockets, dragging, tooltips, context menu
 */

import React, { useState, useEffect, useRef, useCallback } from 'react';
import { SceneNode } from '../services/OctaneClient';
import { useOctane } from '../hooks/useOctane';
import { OctaneIconMapper } from '../utils/OctaneIconMapper';

interface NodeGraphEditorProps {
  // No props needed - component manages its own state
}

interface GraphNode {
  id: number;
  data: SceneNode;
  x: number;
  y: number;
  width: number;
  height: number;
}

interface Socket {
  nodeId: number;
  type: 'input' | 'output';
  index: number;
  x: number;
  y: number;
  name?: string;
}

interface GraphConnection {
  from: number;
  to: number;
  fromSocket: { x: number; y: number };
  toSocket: { x: number; y: number };
}

interface Tooltip {
  visible: boolean;
  text: string;
  x: number;
  y: number;
}

interface ContextMenu {
  visible: boolean;
  x: number;
  y: number;
}

export function NodeGraphEditor(_props: NodeGraphEditorProps) {
  const { client, connected } = useOctane();
  const [nodes, setNodes] = useState<GraphNode[]>([]);
  const [connections, setConnections] = useState<GraphConnection[]>([]);
  const [viewport, setViewport] = useState({ x: 0, y: 0, zoom: 1 });
  const [selectedNodeIds, setSelectedNodeIds] = useState<Set<number>>(new Set());
  
  // Dragging state
  const [isDraggingCanvas, setIsDraggingCanvas] = useState(false);
  const [isDraggingNode, setIsDraggingNode] = useState(false);
  const [isDraggingConnection, setIsDraggingConnection] = useState(false);
  const [draggedNodeId, setDraggedNodeId] = useState<number | null>(null);
  const [dragOffset, setDragOffset] = useState({ x: 0, y: 0 });
  const [dragStart, setDragStart] = useState({ x: 0, y: 0 });
  const [tempConnection, setTempConnection] = useState<{ from: Socket; toX: number; toY: number } | null>(null);
  
  // UI state
  const [tooltip, setTooltip] = useState<Tooltip>({ visible: false, text: '', x: 0, y: 0 });
  const [contextMenu, setContextMenu] = useState<ContextMenu>({ visible: false, x: 0, y: 0 });
  
  const containerRef = useRef<HTMLDivElement>(null);
  const svgRef = useRef<SVGSVGElement>(null);

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

  // Convert screen coordinates to SVG coordinates accounting for viewport transform
  const screenToSvg = useCallback((screenX: number, screenY: number) => {
    if (!svgRef.current) return { x: 0, y: 0 };
    const rect = svgRef.current.getBoundingClientRect();
    return {
      x: (screenX - rect.left - viewport.x) / viewport.zoom,
      y: (screenY - rect.top - viewport.y) / viewport.zoom
    };
  }, [viewport]);

  // Get sockets for a node
  const getNodeSockets = useCallback((node: GraphNode): Socket[] => {
    const sockets: Socket[] = [];
    
    // Output socket (bottom center)
    sockets.push({
      nodeId: node.id,
      type: 'output',
      index: 0,
      x: node.x + node.width / 2,
      y: node.y + node.height,
      name: 'Output'
    });
    
    // Input socket (top center) if node has children
    if (node.data.children && node.data.children.length > 0) {
      sockets.push({
        nodeId: node.id,
        type: 'input',
        index: 0,
        x: node.x + node.width / 2,
        y: node.y,
        name: 'Input'
      });
    }
    
    return sockets;
  }, []);

  // Check if point is near socket
  const getSocketAtPoint = useCallback((x: number, y: number, threshold = 8): Socket | null => {
    for (const node of nodes) {
      const sockets = getNodeSockets(node);
      for (const socket of sockets) {
        const dx = x - socket.x;
        const dy = y - socket.y;
        const distance = Math.sqrt(dx * dx + dy * dy);
        if (distance < threshold) {
          return socket;
        }
      }
    }
    return null;
  }, [nodes, getNodeSockets]);

  // Check if point is inside node
  const getNodeAtPoint = useCallback((x: number, y: number): GraphNode | null => {
    // Check in reverse order so top nodes are prioritized
    for (let i = nodes.length - 1; i >= 0; i--) {
      const node = nodes[i];
      if (x >= node.x && x <= node.x + node.width &&
          y >= node.y && y <= node.y + node.height) {
        return node;
      }
    }
    return null;
  }, [nodes]);

  // Handle mouse down - start dragging node, connection, or canvas
  const handleMouseDown = (e: React.MouseEvent) => {
    // Hide context menu on any click
    setContextMenu({ visible: false, x: 0, y: 0 });
    
    if (e.button !== 0) return; // Only left click
    
    const svgPoint = screenToSvg(e.clientX, e.clientY);
    
    // Check if clicking on socket (for connection dragging)
    const socket = getSocketAtPoint(svgPoint.x, svgPoint.y);
    if (socket) {
      setIsDraggingConnection(true);
      setTempConnection({
        from: socket,
        toX: svgPoint.x,
        toY: svgPoint.y
      });
      return;
    }
    
    // Check if clicking on node (for node dragging)
    const node = getNodeAtPoint(svgPoint.x, svgPoint.y);
    if (node) {
      setIsDraggingNode(true);
      setDraggedNodeId(node.id);
      setDragOffset({
        x: svgPoint.x - node.x,
        y: svgPoint.y - node.y
      });
      
      // Multi-select with Ctrl/Cmd key
      if (e.ctrlKey || e.metaKey) {
        setSelectedNodeIds(prev => {
          const newSet = new Set(prev);
          if (newSet.has(node.id)) {
            newSet.delete(node.id);
          } else {
            newSet.add(node.id);
          }
          return newSet;
        });
      } else {
        setSelectedNodeIds(new Set([node.id]));
      }
      return;
    }
    
    // Canvas dragging
    setIsDraggingCanvas(true);
    setDragStart({ x: e.clientX - viewport.x, y: e.clientY - viewport.y });
  };

  // Handle mouse move - update dragging
  const handleMouseMove = (e: React.MouseEvent) => {
    const svgPoint = screenToSvg(e.clientX, e.clientY);
    
    // Update temp connection line
    if (isDraggingConnection && tempConnection) {
      setTempConnection({
        ...tempConnection,
        toX: svgPoint.x,
        toY: svgPoint.y
      });
      return;
    }
    
    // Update node position
    if (isDraggingNode && draggedNodeId !== null) {
      setNodes(prevNodes =>
        prevNodes.map(node =>
          node.id === draggedNodeId
            ? {
                ...node,
                x: svgPoint.x - dragOffset.x,
                y: svgPoint.y - dragOffset.y
              }
            : node
        )
      );
      // Update connections for the moved node
      setConnections(prevConnections =>
        prevConnections.map(conn => {
          const fromNode = nodes.find(n => n.id === conn.from);
          const toNode = nodes.find(n => n.id === conn.to);
          if (fromNode && toNode) {
            return {
              ...conn,
              fromSocket: { x: fromNode.x + fromNode.width / 2, y: fromNode.y + fromNode.height },
              toSocket: { x: toNode.x + toNode.width / 2, y: toNode.y }
            };
          }
          return conn;
        })
      );
      return;
    }
    
    // Canvas panning
    if (isDraggingCanvas) {
      setViewport({
        ...viewport,
        x: e.clientX - dragStart.x,
        y: e.clientY - dragStart.y
      });
      return;
    }
    
    // Show tooltip on socket hover
    const socket = getSocketAtPoint(svgPoint.x, svgPoint.y);
    if (socket) {
      setTooltip({
        visible: true,
        text: socket.name || `${socket.type} socket`,
        x: e.clientX,
        y: e.clientY - 30
      });
    } else {
      setTooltip({ visible: false, text: '', x: 0, y: 0 });
    }
  };

  // Handle mouse up - finish dragging
  const handleMouseUp = (e: React.MouseEvent) => {
    // Finish connection dragging
    if (isDraggingConnection && tempConnection) {
      const svgPoint = screenToSvg(e.clientX, e.clientY);
      const targetSocket = getSocketAtPoint(svgPoint.x, svgPoint.y);
      
      // Create connection if dropped on valid target socket
      if (targetSocket && 
          targetSocket.nodeId !== tempConnection.from.nodeId &&
          targetSocket.type !== tempConnection.from.type) {
        // TODO: Call Octane API to create connection
        console.log('Create connection:', tempConnection.from, '→', targetSocket);
      }
      
      setIsDraggingConnection(false);
      setTempConnection(null);
    }
    
    setIsDraggingNode(false);
    setDraggedNodeId(null);
    setIsDraggingCanvas(false);
  };

  // Handle right-click context menu
  const handleContextMenu = (e: React.MouseEvent) => {
    e.preventDefault();
    setContextMenu({
      visible: true,
      x: e.clientX,
      y: e.clientY
    });
  };

  // Handle keyboard shortcuts
  useEffect(() => {
    const handleKeyDown = (e: KeyboardEvent) => {
      // Delete selected nodes
      if ((e.key === 'Delete' || e.key === 'Backspace') && selectedNodeIds.size > 0) {
        // TODO: Call Octane API to delete nodes
        console.log('Delete nodes:', Array.from(selectedNodeIds));
        e.preventDefault();
      }
      
      // Hide context menu on Escape
      if (e.key === 'Escape') {
        setContextMenu({ visible: false, x: 0, y: 0 });
      }
    };
    
    window.addEventListener('keydown', handleKeyDown);
    return () => window.removeEventListener('keydown', handleKeyDown);
  }, [selectedNodeIds]);

  const handleWheel = (e: React.WheelEvent) => {
    e.preventDefault();
    const zoomFactor = e.deltaY > 0 ? 0.9 : 1.1;
    setViewport({
      ...viewport,
      zoom: Math.max(0.1, Math.min(2, viewport.zoom * zoomFactor))
    });
  };

  // Draw grid pattern
  const renderGrid = () => {
    const gridSize = 20;
    const gridColor = '#2a2a2a';
    const lines: JSX.Element[] = [];
    
    // Calculate visible area
    const startX = Math.floor(-viewport.x / viewport.zoom / gridSize) * gridSize;
    const startY = Math.floor(-viewport.y / viewport.zoom / gridSize) * gridSize;
    const endX = startX + (svgRef.current?.clientWidth || 0) / viewport.zoom + gridSize;
    const endY = startY + (svgRef.current?.clientHeight || 0) / viewport.zoom + gridSize;
    
    // Vertical lines
    for (let x = startX; x < endX; x += gridSize) {
      lines.push(
        <line
          key={`v-${x}`}
          x1={x}
          y1={startY}
          x2={x}
          y2={endY}
          stroke={gridColor}
          strokeWidth={0.5}
        />
      );
    }
    
    // Horizontal lines
    for (let y = startY; y < endY; y += gridSize) {
      lines.push(
        <line
          key={`h-${y}`}
          x1={startX}
          y1={y}
          x2={endX}
          y2={y}
          stroke={gridColor}
          strokeWidth={0.5}
        />
      );
    }
    
    return lines;
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

  const getCursor = () => {
    if (isDraggingCanvas) return 'grabbing';
    if (isDraggingNode) return 'move';
    if (isDraggingConnection) return 'crosshair';
    return 'default';
  };

  return (
    <div 
      ref={containerRef}
      className="node-graph-svg-container"
      onMouseDown={handleMouseDown}
      onMouseMove={handleMouseMove}
      onMouseUp={handleMouseUp}
      onMouseLeave={handleMouseUp}
      onWheel={handleWheel}
      onContextMenu={handleContextMenu}
      style={{ cursor: getCursor() }}
    >
      <svg 
        ref={svgRef}
        width="100%" 
        height="100%" 
        style={{ background: '#1a1a1a' }}
      >
        <g transform={`translate(${viewport.x}, ${viewport.y}) scale(${viewport.zoom})`}>
          {/* Grid background */}
          {renderGrid()}

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

          {/* Draw temp connection being dragged */}
          {tempConnection && (
            <path
              d={`M ${tempConnection.from.x} ${tempConnection.from.y} 
                  L ${tempConnection.toX} ${tempConnection.toY}`}
              stroke="#4a90e2"
              strokeWidth={2}
              strokeDasharray="5,5"
              fill="none"
            />
          )}

          {/* Draw nodes */}
          {nodes.map(node => {
            const isSelected = selectedNodeIds.has(node.id);
            const color = getNodeColor(node.data);
            const icon = getNodeIcon(node.data);
            const sockets = getNodeSockets(node);

            return (
              <g key={node.id} transform={`translate(${node.x}, ${node.y})`}>
                {/* Node box */}
                <rect
                  width={node.width}
                  height={node.height}
                  rx={4}
                  fill={color}
                  stroke={isSelected ? '#4a90e2' : '#555'}
                  strokeWidth={isSelected ? 3 : 1}
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

                {/* Render sockets */}
                {sockets.map((socket, idx) => (
                  <circle
                    key={`socket-${idx}`}
                    cx={socket.x - node.x}
                    cy={socket.y - node.y}
                    r={6}
                    fill={socket.type === 'input' ? '#7ec97e' : '#e2a14a'}
                    stroke="#fff"
                    strokeWidth={1.5}
                    style={{ cursor: 'crosshair' }}
                  />
                ))}
              </g>
            );
          })}
        </g>
      </svg>

      {/* Tooltip overlay */}
      {tooltip.visible && (
        <div
          className="node-graph-tooltip"
          style={{
            position: 'fixed',
            left: tooltip.x,
            top: tooltip.y,
            pointerEvents: 'none'
          }}
        >
          {tooltip.text}
        </div>
      )}

      {/* Context menu overlay */}
      {contextMenu.visible && (
        <div
          className="node-graph-context-menu"
          style={{
            position: 'fixed',
            left: contextMenu.x,
            top: contextMenu.y
          }}
        >
          <div className="context-menu-item" onClick={() => {
            console.log('Add node at:', contextMenu.x, contextMenu.y);
            setContextMenu({ visible: false, x: 0, y: 0 });
          }}>
            ➕ Add Node
          </div>
          <div className="context-menu-item" onClick={() => {
            console.log('Fit all nodes');
            setContextMenu({ visible: false, x: 0, y: 0 });
            // TODO: Calculate bounding box and center view
          }}>
            🔲 Fit All
          </div>
        </div>
      )}

      {/* Toolbar overlay */}
      <div className="node-graph-toolbar">
        <button 
          className="toolbar-btn" 
          title="Add Node"
          onClick={() => console.log('Add node')}
        >
          ➕
        </button>
        <button 
          className="toolbar-btn" 
          title="Delete Selected"
          onClick={() => {
            if (selectedNodeIds.size > 0) {
              console.log('Delete nodes:', Array.from(selectedNodeIds));
            }
          }}
          disabled={selectedNodeIds.size === 0}
        >
          🗑️
        </button>
        <button 
          className="toolbar-btn" 
          title="Fit All"
          onClick={() => setViewport({ x: 0, y: 0, zoom: 1 })}
        >
          🔲
        </button>
      </div>

      {/* Zoom info overlay */}
      <div className="node-graph-zoom-overlay">
        <div className="zoom-info">Zoom: {(viewport.zoom * 100).toFixed(0)}%</div>
        <button onClick={() => setViewport({ ...viewport, zoom: 1, x: 0, y: 0 })}>
          Reset View
        </button>
      </div>
    </div>
  );
}
