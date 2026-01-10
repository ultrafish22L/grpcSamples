/**
 * Node Graph Editor Component - ReactFlow Implementation
 * Replaces 956-line custom SVG implementation with ReactFlow
 * Maintains all functionality from octaneWeb's NodeGraphEditor.js
 */

import { useEffect, useCallback, useRef, useState } from 'react';
import ReactFlow, {
  Node,
  Edge,
  Background,
  BackgroundVariant,
  MiniMap,
  useNodesState,
  useEdgesState,
  useReactFlow,
  addEdge,
  Connection,
  NodeTypes,
  ReactFlowProvider,
  OnConnectStart,
  OnConnectEnd,
  EdgeChange,
} from 'reactflow';
import 'reactflow/dist/style.css';

import { SceneNode } from '../../services/OctaneClient';
import { useOctane } from '../../hooks/useOctane';
import { OctaneNode, OctaneNodeData } from './OctaneNode';
import { OctaneIconMapper } from '../../utils/OctaneIconMapper';
import { NodeTypeContextMenu } from './NodeTypeContextMenu';
import { NodeType } from '../../constants/OctaneTypes';

interface NodeGraphEditorProps {
  sceneTree: SceneNode[];
  selectedNode?: SceneNode | null;
  onNodeSelect?: (node: SceneNode | null) => void;
}

// Define custom node types
const nodeTypes: NodeTypes = {
  octane: OctaneNode,
};

/**
 * Inner component with ReactFlow context access
 */
function NodeGraphEditorInner({ sceneTree, selectedNode, onNodeSelect }: NodeGraphEditorProps) {
  const { client, connected } = useOctane();
  const { fitView } = useReactFlow();
  
  const [nodes, setNodes, onNodesChange] = useNodesState([]);
  const [edges, setEdges, onEdgesChangeBase] = useEdgesState([]);
  const containerRef = useRef<HTMLDivElement>(null);
  
  // Track whether initial fitView has been called (should only happen once after initial scene sync)
  const hasInitialFitView = useRef(false);
  
  // Context menu state
  const [contextMenuVisible, setContextMenuVisible] = useState(false);
  const [contextMenuPosition, setContextMenuPosition] = useState({ x: 0, y: 0 });

  // Track connection line color during drag (matches source pin color)
  const [connectionLineColor, setConnectionLineColor] = useState('#4a90e2');
  const connectingEdgeRef = useRef<Edge | null>(null); // Track if reconnecting existing edge

  /**
   * Convert scene tree to ReactFlow nodes and edges
   * Following octaneWeb's NodeGraphEditor.js pattern:
   * - Only show TOP-LEVEL nodes from scene.tree (no recursive children)
   * - Only show direct connections between top-level nodes
   * - Use bezier curves for connection splines
   */
  const convertSceneToGraph = useCallback((tree: SceneNode[]) => {
    const graphNodes: Node<OctaneNodeData>[] = [];
    const graphEdges: Edge[] = [];
    const nodeMap = new Map<string, SceneNode>();

    // Only process TOP-LEVEL nodes (matching octaneWeb behavior)
    const nodeSpacing = 250;
    const yCenter = 300;
    
    tree.forEach((item, index) => {
      if (!item.handle) {
        return;
      }

      const handleStr = String(item.handle);
      nodeMap.set(handleStr, item);

      // Extract input pins from item.children
      const inputs = item.children || [];
      
      const inputHandles = inputs.map((input: any, inputIndex: number) => {
        return {
          id: `input-${inputIndex}`,
          label: input.staticLabel || input.name,
          pinInfo: input.pinInfo,
        };
      });

      // Create output handle
      const output = {
        id: 'output-0',
        label: item.name,
        pinInfo: item.pinInfo,
      };

      // Position nodes horizontally with spacing
      const node: Node<OctaneNodeData> = {
        id: handleStr,
        type: 'octane',
        position: { 
          x: 100 + (index * nodeSpacing),
          y: yCenter + (index * 20),
        },
        data: {
          sceneNode: item,
          inputs: inputHandles,
          output,
        },
      };

      graphNodes.push(node);
    });

    // Create connections between TOP-LEVEL nodes only
    tree.forEach((node) => {
      if (!node.handle || !node.children || node.children.length === 0) {
        return;
      }

      const targetHandle = String(node.handle);
      
      // Check each child (input pin) for connections
      node.children.forEach((childNode: any, inputIndex: number) => {
        if (childNode.handle) {
          const sourceHandle = String(childNode.handle);
          
          // Only create edge if BOTH nodes are in our top-level nodeMap
          if (nodeMap.has(sourceHandle) && nodeMap.has(targetHandle)) {
            const edgeColor = childNode.pinInfo?.pinColor 
              ? OctaneIconMapper.formatColorValue(childNode.pinInfo.pinColor)
              : '#4a90e2';
            
            const edge: Edge = {
              id: `e${sourceHandle}-${targetHandle}-${inputIndex}`,
              source: sourceHandle,
              target: targetHandle,
              sourceHandle: 'output-0',
              targetHandle: `input-${inputIndex}`,
              type: 'default', // Use 'default' for bezier curves (matching Octane)
              animated: false,
              style: { 
                stroke: edgeColor, 
                strokeWidth: 3 
              },
            };

            graphEdges.push(edge);
          }
        }
      });
    });

    console.log(`🔄 Node Graph: ${graphNodes.length} nodes, ${graphEdges.length} edges`);

    return { nodes: graphNodes, edges: graphEdges };
  }, []);

  /**
   * Load scene graph when sceneTree changes
   */
  useEffect(() => {
    if (!sceneTree || sceneTree.length === 0) {
      setNodes([]);
      setEdges([]);
      return;
    }

    const { nodes: graphNodes, edges: graphEdges } = convertSceneToGraph(sceneTree);
    
    setNodes(graphNodes);
    setEdges(graphEdges);
  }, [sceneTree, convertSceneToGraph, setNodes, setEdges]);

  /**
   * Synchronize node selection when selectedNode changes externally (e.g., from SceneOutliner)
   */
  useEffect(() => {
    if (!selectedNode || nodes.length === 0) {
      // Clear selection
      setNodes((nds) =>
        nds.map((node) => ({
          ...node,
          selected: false,
        }))
      );
      return;
    }

    const selectedHandle = String(selectedNode.handle);
    
    setNodes((nds) =>
      nds.map((node) => ({
        ...node,
        selected: node.id === selectedHandle,
      }))
    );
  }, [selectedNode, setNodes, nodes.length]);

  /**
   * Fit view ONCE when initial scene is loaded
   * After that, preserve user's zoom/pan position
   * (Don't auto-fit when user creates new nodes - that's annoying!)
   */
  useEffect(() => {
    if (nodes.length > 0 && !hasInitialFitView.current) {
      // Use setTimeout to ensure ReactFlow has finished rendering
      setTimeout(() => {
        fitView({ 
          padding: 0.2,        // 20% padding around nodes
          includeHiddenNodes: false,
          minZoom: 0.5,        // Don't zoom out too far
          maxZoom: 1.5,        // Don't zoom in too much
          duration: 300,       // Smooth animation (300ms)
        });
        hasInitialFitView.current = true;
      }, 100);
    }
  }, [nodes, fitView]);

  /**
   * Handle connection start - capture source handle color for drag line
   */
  const onConnectStart: OnConnectStart = useCallback(
    (_event, { nodeId, handleId, handleType }) => {
      console.log('🔌 Connection drag started:', { nodeId, handleId, handleType });
      
      // Find the source node and handle to get its color
      const sourceNode = nodes.find(n => n.id === nodeId);
      if (!sourceNode) return;

      const nodeData = sourceNode.data as OctaneNodeData;
      
      // Get handle color based on type (source = output, target = input)
      let handleColor = '#4a90e2'; // Default color
      
      if (handleType === 'source' && nodeData.output?.pinInfo?.pinColor) {
        handleColor = OctaneIconMapper.formatColorValue(nodeData.output.pinInfo.pinColor);
      } else if (handleType === 'target' && nodeData.inputs) {
        const input = nodeData.inputs.find(i => i.id === handleId);
        if (input?.pinInfo?.pinColor) {
          handleColor = OctaneIconMapper.formatColorValue(input.pinInfo.pinColor);
        }
      }

      console.log('🎨 Setting connection line color:', handleColor);
      setConnectionLineColor(handleColor);

      // Check if we're dragging from an existing connection
      const existingEdge = edges.find(
        e => (e.source === nodeId && e.sourceHandle === handleId) ||
             (e.target === nodeId && e.targetHandle === handleId)
      );

      if (existingEdge) {
        console.log('📌 Reconnecting existing edge:', existingEdge.id);
        connectingEdgeRef.current = existingEdge;
      } else {
        connectingEdgeRef.current = null;
      }
    },
    [nodes, edges]
  );

  /**
   * Handle connection end - cleanup
   */
  const onConnectEnd: OnConnectEnd = useCallback(() => {
    console.log('🔌 Connection drag ended');
    setConnectionLineColor('#4a90e2'); // Reset to default
    connectingEdgeRef.current = null;
  }, []);

  /**
   * Handle new connections
   */
  const onConnect = useCallback(
    async (connection: Connection) => {
      try {
        if (!connection.source || !connection.target) return;

        console.log('🔗 Creating connection:', connection);

        // If we were reconnecting an existing edge, remove it first
        if (connectingEdgeRef.current) {
          console.log('🔄 Disconnecting old edge:', connectingEdgeRef.current.id);
          
          // Remove old edge from state
          setEdges((eds) => eds.filter(e => e.id !== connectingEdgeRef.current?.id));

          // TODO: Call Octane API to disconnect the old connection
          // This would require knowing the target pin index
        }

        // Call Octane API to connect nodes
        const sourceHandle = parseInt(connection.source);
        const targetHandle = parseInt(connection.target);

        // Extract pin index from targetHandle (format: "input-N")
        const pinIdx = connection.targetHandle 
          ? parseInt(connection.targetHandle.split('-')[1]) 
          : 0;

        await client.callApi('ApiNode', 'connectToIx', targetHandle, {
          pinIdx,
          sourceNode: {
            handle: sourceHandle,
            type: 17, // ApiNode type
          },
        });

        // Add edge to ReactFlow with matching color
        const newEdge = {
          ...connection,
          id: `e${connection.source}-${connection.target}-${pinIdx}`,
          style: { 
            stroke: connectionLineColor, 
            strokeWidth: 3 
          },
        };

        setEdges((eds) => addEdge(newEdge, eds));

        // Refresh scene tree
        await client.buildSceneTree();
      } catch (error) {
        console.error('❌ Failed to create connection:', error);
      }
    },
    [client, setEdges, connectionLineColor]
  );

  /**
   * Handle edge changes (including removals for reconnection)
   */
  const onEdgesChange = useCallback(
    (changes: EdgeChange[]) => {
      console.log('🔄 Edge changes:', changes);
      
      // Check if this is an edge removal (start of reconnection)
      changes.forEach(change => {
        if (change.type === 'remove') {
          const edge = edges.find(e => e.id === change.id);
          if (edge) {
            console.log('🗑️ Edge being removed for reconnection:', edge.id);
            // Store reference for reconnection
            connectingEdgeRef.current = edge;
          }
        }
      });

      // Apply changes using the base handler from useEdgesState
      onEdgesChangeBase(changes);
    },
    [edges, onEdgesChangeBase]
  );

  /**
   * Handle node deletion
   */
  const onNodesDelete = useCallback(
    async (deletedNodes: Node[]) => {
      try {
        for (const node of deletedNodes) {
          const handle = parseInt(node.id);
          await client.callApi('ApiItem', 'deleteItem', handle, {});
        }
        
        // Refresh scene tree
        await client.buildSceneTree();
      } catch (error) {
        console.error('Failed to delete nodes:', error);
      }
    },
    [client]
  );

  /**
   * Handle node selection - synchronize with Scene Outliner and Node Inspector
   */
  const onNodeClick = useCallback(
    (_event: React.MouseEvent, node: Node<OctaneNodeData>) => {
      const sceneNode = node.data.sceneNode;
      onNodeSelect?.(sceneNode);
      console.log('🎯 Node Graph: Selected node:', sceneNode.name);
    },
    [onNodeSelect]
  );

  /**
   * Context menu event handlers
   */
  const handleContextMenu = useCallback((event: React.MouseEvent) => {
    event.preventDefault();
    setContextMenuPosition({ x: event.clientX, y: event.clientY });
    setContextMenuVisible(true);
  }, []);

  const handleSelectNodeType = useCallback(async (nodeType: string) => {
    const nodeTypeId = NodeType[nodeType];
    if (nodeTypeId === undefined) {
      console.error('❌ Unknown node type:', nodeType);
      return;
    }

    try {
      const createdHandle = await client.createNode(nodeType, nodeTypeId);
      if (createdHandle) {
        console.log('✅ Node created successfully:', createdHandle);
      } else {
        console.error('❌ Failed to create node');
      }
    } catch (error) {
      console.error('❌ Error creating node:', error);
    }
  }, [client]);

  const handleCloseContextMenu = useCallback(() => {
    setContextMenuVisible(false);
  }, []);



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
      </div>
    );
  }

  return (
    <div 
      ref={containerRef} 
      style={{ width: '100%', height: '100%', position: 'relative' }}
      onContextMenu={handleContextMenu}
    >
      {/* Context Menu */}
      {contextMenuVisible && (
        <NodeTypeContextMenu
          x={contextMenuPosition.x}
          y={contextMenuPosition.y}
          onSelectNodeType={handleSelectNodeType}
          onClose={handleCloseContextMenu}
        />
      )}

      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onConnect={onConnect}
        onConnectStart={onConnectStart}
        onConnectEnd={onConnectEnd}
        onNodesDelete={onNodesDelete}
        onNodeClick={onNodeClick}
        nodeTypes={nodeTypes}
        minZoom={0.1}
        maxZoom={4}
        defaultEdgeOptions={{
          type: 'default',
          animated: false,
          style: { stroke: '#4a90e2', strokeWidth: 2 },
        }}
        connectionLineStyle={{
          stroke: connectionLineColor,
          strokeWidth: 3,
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

        {/* Minimap for navigation - top-left with yellow Octane styling */}
        <MiniMap
          position="top-left"
          nodeColor={(node) => {
            const data = node.data as OctaneNodeData;
            return data.sceneNode.nodeInfo?.nodeColor
              ? '#' + data.sceneNode.nodeInfo.nodeColor.toString(16).padStart(6, '0')
              : '#666';
          }}
          style={{
            background: 'rgba(60, 60, 30, 0.8)',
            border: '2px solid rgba(200, 180, 80, 0.8)',
            borderRadius: 4,
          }}
          maskColor="rgba(0, 0, 0, 0.6)"
        />
      </ReactFlow>
    </div>
  );
}

/**
 * Main component wrapped with ReactFlow provider
 */
export function NodeGraphEditor({ sceneTree, selectedNode, onNodeSelect }: NodeGraphEditorProps) {
  return (
    <ReactFlowProvider>
      <NodeGraphEditorInner sceneTree={sceneTree} selectedNode={selectedNode} onNodeSelect={onNodeSelect} />
    </ReactFlowProvider>
  );
}
