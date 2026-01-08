/**
 * Node Graph Editor Component - ReactFlow Implementation
 * Replaces 956-line custom SVG implementation with ReactFlow
 * Maintains all functionality from octaneWeb's NodeGraphEditor.js
 */

import React, { useState, useEffect, useCallback, useRef } from 'react';
import ReactFlow, {
  Node,
  Edge,
  Controls,
  Background,
  BackgroundVariant,
  MiniMap,
  useNodesState,
  useEdgesState,
  addEdge,
  Connection,
  NodeTypes,
  Panel,
  ReactFlowProvider,
  useReactFlow,
} from 'reactflow';
import 'reactflow/dist/style.css';

import { SceneNode } from '../../services/OctaneClient';
import { useOctane } from '../../hooks/useOctane';
import { OctaneNode, OctaneNodeData } from './OctaneNode';
import { Logger } from '../../utils/Logger';

interface NodeGraphEditorProps {
  sceneTree: SceneNode[];
}

// Define custom node types
const nodeTypes: NodeTypes = {
  octane: OctaneNode,
};

/**
 * Inner component with ReactFlow context access
 */
function NodeGraphEditorInner({ sceneTree }: NodeGraphEditorProps) {
  const { client, connected } = useOctane();
  const reactFlowInstance = useReactFlow();
  
  const [nodes, setNodes, onNodesChange] = useNodesState([]);
  const [edges, setEdges, onEdgesChange] = useEdgesState([]);
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);
  const containerRef = useRef<HTMLDivElement>(null);

  /**
   * Convert scene tree to ReactFlow nodes and edges
   */
  const convertSceneToGraph = useCallback((tree: SceneNode[]) => {
    Logger.group('🔄 Converting scene tree to ReactFlow graph', true);
    
    const nodeMap = new Map<number, SceneNode>();
    const graphNodes: Node<OctaneNodeData>[] = [];
    const graphEdges: Edge[] = [];

    // First pass: collect all nodes with handles
    const collectNodes = (items: SceneNode[], level: number = 0) => {
      items.forEach((item) => {
        if (typeof item.handle === 'number') {
          nodeMap.set(item.handle, item);
        }
        if (item.children && item.children.length > 0) {
          collectNodes(item.children, level + 1);
        }
      });
    };

    collectNodes(tree);
    Logger.debug(`Collected ${nodeMap.size} nodes from scene tree`);

    // Second pass: create ReactFlow nodes
    const nodeSpacing = 220;
    const levelOffset = 150;
    let nodeIndex = 0;

    nodeMap.forEach((sceneNode, handle) => {
      // Extract input pins from nodeInfo
      const inputs = sceneNode.nodeInfo?.inputs || [];
      const inputHandles = inputs.map((input: any, index: number) => ({
        id: `input-${index}`,
        label: input.staticLabel || input.name,
        pinInfo: input.pinInfo,
      }));

      // Create output handle
      const output = {
        id: 'output-0',
        label: sceneNode.name,
        pinInfo: sceneNode.pinInfo,
      };

      const node: Node<OctaneNodeData> = {
        id: String(handle),
        type: 'octane',
        position: { 
          x: 100 + (nodeIndex % 5) * nodeSpacing, 
          y: 200 + Math.floor(nodeIndex / 5) * levelOffset 
        },
        data: {
          sceneNode,
          inputs: inputHandles,
          output,
        },
      };

      graphNodes.push(node);
      nodeIndex++;
    });

    // Third pass: create connections/edges
    const processConnections = (node: SceneNode) => {
      if (node.children && node.children.length > 0 && typeof node.handle === 'number') {
        node.children.forEach((child) => {
          if (typeof child.handle !== 'number') return;

          const edge: Edge = {
            id: `e${node.handle}-${child.handle}`,
            source: String(node.handle),
            target: String(child.handle),
            sourceHandle: 'output-0',
            targetHandle: 'input-0',
            type: 'smoothstep',
            animated: false,
            style: { stroke: '#4a90e2', strokeWidth: 2 },
          };

          graphEdges.push(edge);
        });
      }

      // Recursively process children
      if (node.children) {
        node.children.forEach(processConnections);
      }
    };

    tree.forEach(processConnections);

    Logger.debug(`Created ${graphNodes.length} nodes and ${graphEdges.length} edges`);
    Logger.groupEnd();

    return { nodes: graphNodes, edges: graphEdges };
  }, []);

  /**
   * Load scene graph when sceneTree changes
   */
  useEffect(() => {
    if (!sceneTree || sceneTree.length === 0) {
      Logger.debug('No scene tree data available');
      setNodes([]);
      setEdges([]);
      return;
    }

    Logger.info(`Loading scene graph with ${sceneTree.length} root nodes`);
    const { nodes: graphNodes, edges: graphEdges } = convertSceneToGraph(sceneTree);
    
    setNodes(graphNodes);
    setEdges(graphEdges);

    // Fit view after nodes are loaded
    setTimeout(() => {
      if (graphNodes.length > 0) {
        reactFlowInstance.fitView({ padding: 0.2, duration: 400 });
      }
    }, 100);
  }, [sceneTree, convertSceneToGraph, setNodes, setEdges, reactFlowInstance]);

  /**
   * Handle new connections
   */
  const onConnect = useCallback(
    async (connection: Connection) => {
      Logger.info('Creating connection:', connection);

      try {
        if (!connection.source || !connection.target) return;

        // Call Octane API to connect nodes
        const sourceHandle = parseInt(connection.source);
        const targetHandle = parseInt(connection.target);

        await client.callApi('ApiNode', 'connectToIx', targetHandle, {
          pinIdx: 0, // Assume first input pin for now
          sourceNode: {
            handle: sourceHandle,
            type: 17, // ApiNode type
          },
        });

        Logger.info('Connection created successfully');

        // Add edge to ReactFlow
        setEdges((eds) => addEdge(connection, eds));

        // Refresh scene tree
        await client.buildSceneTree();
      } catch (error) {
        Logger.error('Failed to create connection:', error);
      }
    },
    [client, setEdges]
  );

  /**
   * Handle node deletion
   */
  const onNodesDelete = useCallback(
    async (deletedNodes: Node[]) => {
      Logger.info('Deleting nodes:', deletedNodes.map((n) => n.id));

      try {
        for (const node of deletedNodes) {
          const handle = parseInt(node.id);
          await client.callApi('ApiItem', 'deleteItem', handle, {});
        }

        Logger.info('Nodes deleted successfully');
        
        // Refresh scene tree
        await client.buildSceneTree();
      } catch (error) {
        Logger.error('Failed to delete nodes:', error);
      }
    },
    [client]
  );

  /**
   * Context menu handler
   */
  const onPaneContextMenu = useCallback((event: React.MouseEvent) => {
    event.preventDefault();
    setContextMenu({ x: event.clientX, y: event.clientY });
  }, []);

  /**
   * Hide context menu on click outside
   */
  const onPaneClick = useCallback(() => {
    setContextMenu(null);
  }, []);

  /**
   * Fit all nodes in view
   */
  const handleFitView = useCallback(() => {
    reactFlowInstance.fitView({ padding: 0.2, duration: 400 });
  }, [reactFlowInstance]);

  /**
   * Add new node at center of viewport
   */
  const handleAddNode = useCallback(() => {
    const position = reactFlowInstance.project({ 
      x: window.innerWidth / 2, 
      y: window.innerHeight / 2 
    });

    Logger.info('Creating new node at position:', position);

    // TODO: Implement node creation via Octane API
    // For now, show placeholder
    Logger.warn('Node creation not yet implemented');
  }, [reactFlowInstance]);

  /**
   * Delete selected nodes
   */
  const handleDeleteSelected = useCallback(() => {
    const selectedNodes = nodes.filter((node) => node.selected);
    if (selectedNodes.length > 0) {
      onNodesDelete(selectedNodes);
    }
  }, [nodes, onNodesDelete]);

  // Not connected state
  if (!connected) {
    return (
      <div className="node-graph-empty">
        <p>Connect to Octane to view node graph</p>
      </div>
    );
  }

  // No nodes state
  if (nodes.length === 0) {
    return (
      <div className="node-graph-empty">
        <p>No scene nodes available</p>
        <p style={{ fontSize: '12px', color: '#888', marginTop: '10px' }}>
          Load a scene in Octane to see the node graph
        </p>
      </div>
    );
  }

  return (
    <div ref={containerRef} style={{ width: '100%', height: '100%', position: 'relative' }}>
      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onConnect={onConnect}
        onNodesDelete={onNodesDelete}
        onPaneContextMenu={onPaneContextMenu}
        onPaneClick={onPaneClick}
        nodeTypes={nodeTypes}
        fitView
        minZoom={0.1}
        maxZoom={4}
        defaultEdgeOptions={{
          type: 'smoothstep',
          animated: false,
          style: { stroke: '#4a90e2', strokeWidth: 2 },
        }}
        className="node-graph-reactflow"
        style={{ background: '#1a1a1a' }}
      >
        {/* Grid background matching Octane style */}
        <Background 
          variant={BackgroundVariant.Dots} 
          gap={20} 
          size={1} 
          color="#333"
        />

        {/* Zoom and fit controls */}
        <Controls 
          showInteractive={false}
          style={{
            background: '#2a2a2a',
            border: '1px solid #444',
            borderRadius: 4,
          }}
        />

        {/* Minimap for navigation */}
        <MiniMap
          nodeColor={(node) => {
            const data = node.data as OctaneNodeData;
            return data.sceneNode.nodeInfo?.nodeColor
              ? '#' + data.sceneNode.nodeInfo.nodeColor.toString(16).padStart(6, '0')
              : '#666';
          }}
          style={{
            background: '#2a2a2a',
            border: '1px solid #444',
          }}
          maskColor="rgba(0, 0, 0, 0.6)"
        />

        {/* Custom toolbar panel */}
        <Panel position="top-left" style={{ margin: 10 }}>
          <div className="node-graph-toolbar" style={{ display: 'flex', gap: 8 }}>
            <button
              className="toolbar-btn"
              onClick={handleAddNode}
              title="Add Node"
              style={{
                background: '#2a2a2a',
                border: '1px solid #444',
                color: '#fff',
                padding: '6px 12px',
                borderRadius: 4,
                cursor: 'pointer',
              }}
            >
              ➕ Add Node
            </button>
            <button
              className="toolbar-btn"
              onClick={handleDeleteSelected}
              title="Delete Selected"
              style={{
                background: '#2a2a2a',
                border: '1px solid #444',
                color: '#fff',
                padding: '6px 12px',
                borderRadius: 4,
                cursor: 'pointer',
              }}
            >
              🗑️ Delete
            </button>
            <button
              className="toolbar-btn"
              onClick={handleFitView}
              title="Fit All"
              style={{
                background: '#2a2a2a',
                border: '1px solid #444',
                color: '#fff',
                padding: '6px 12px',
                borderRadius: 4,
                cursor: 'pointer',
              }}
            >
              🔲 Fit All
            </button>
          </div>
        </Panel>

        {/* Zoom level indicator */}
        <Panel position="bottom-right" style={{ margin: 10 }}>
          <div
            style={{
              background: '#2a2a2a',
              border: '1px solid #444',
              padding: '4px 8px',
              borderRadius: 4,
              fontSize: 12,
              color: '#aaa',
            }}
          >
            {Math.round(reactFlowInstance.getZoom() * 100)}%
          </div>
        </Panel>
      </ReactFlow>

      {/* Context menu */}
      {contextMenu && (
        <div
          className="node-graph-context-menu"
          style={{
            position: 'fixed',
            left: contextMenu.x,
            top: contextMenu.y,
            background: '#2a2a2a',
            border: '1px solid #444',
            borderRadius: 4,
            padding: 4,
            zIndex: 1000,
          }}
          onMouseLeave={() => setContextMenu(null)}
        >
          <div
            className="context-menu-item"
            onClick={() => {
              handleAddNode();
              setContextMenu(null);
            }}
            style={{
              padding: '6px 12px',
              cursor: 'pointer',
              color: '#fff',
              fontSize: 12,
            }}
          >
            ➕ Add Node
          </div>
          <div
            className="context-menu-item"
            onClick={() => {
              handleFitView();
              setContextMenu(null);
            }}
            style={{
              padding: '6px 12px',
              cursor: 'pointer',
              color: '#fff',
              fontSize: 12,
            }}
          >
            🔲 Fit All
          </div>
        </div>
      )}
    </div>
  );
}

/**
 * Main component wrapped with ReactFlow provider
 */
export function NodeGraphEditor({ sceneTree }: NodeGraphEditorProps) {
  return (
    <ReactFlowProvider>
      <NodeGraphEditorInner sceneTree={sceneTree} />
    </ReactFlowProvider>
  );
}
