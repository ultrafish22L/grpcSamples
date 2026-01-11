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
  EdgeMouseHandler,
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
  const { fitView, getNode, screenToFlowPosition } = useReactFlow();
  
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
  const reconnectingFromRef = useRef<{ nodeId: string; handleId: string | null | undefined; handleType: 'source' | 'target' } | null>(null);

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
            // FIX: Check pinColor !== undefined to handle black (0) correctly
            const edgeColor = (childNode.pinInfo?.pinColor !== undefined && childNode.pinInfo?.pinColor !== null)
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
              reconnectable: true, // CRITICAL: Enable edge reconnection by dragging
              style: { 
                stroke: edgeColor, 
                strokeWidth: 3 
              },
            };

            graphEdges.push(edge);
            console.log(`🔗 Edge created: ${sourceHandle} → ${targetHandle} (color: ${edgeColor})`);
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
          maxZoom: 1.0,        // Don't zoom in too much
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
      
      // FIX: Check pinColor !== undefined to handle black (0) correctly
      if (handleType === 'source' && nodeData.output?.pinInfo) {
        const pinColor = nodeData.output.pinInfo.pinColor;
        if (pinColor !== undefined && pinColor !== null) {
          handleColor = OctaneIconMapper.formatColorValue(pinColor);
        }
      } else if (handleType === 'target' && nodeData.inputs) {
        const input = nodeData.inputs.find(i => i.id === handleId);
        if (input?.pinInfo) {
          const pinColor = input.pinInfo.pinColor;
          if (pinColor !== undefined && pinColor !== null) {
            handleColor = OctaneIconMapper.formatColorValue(pinColor);
          }
        }
      }

      console.log('🎨 Setting connection line color:', handleColor);
      setConnectionLineColor(handleColor);

      // OCTANE BEHAVIOR: Keep original connections visible during drag
      // Only remove them when a new connection succeeds
      // For input pins (target), track existing edge for replacement
      // For output pins (source), don't track - just add new connection
      if (handleType === 'target') {
        const existingEdge = edges.find(
          e => e.target === nodeId && e.targetHandle === handleId
        );
        
        if (existingEdge) {
          console.log('📌 Input pin has existing connection:', existingEdge.id, '(will replace on success)');
          connectingEdgeRef.current = existingEdge;
        } else {
          connectingEdgeRef.current = null;
        }
      } else {
        // Output pin - allow multiple connections, don't track for removal
        console.log('📤 Output pin - allowing multiple connections');
        connectingEdgeRef.current = null;
      }
    },
    [nodes, edges]
  );

  /**
   * Handle connection end - cleanup only
   * Original edges stay visible during drag, so nothing to restore
   */
  const onConnectEnd: OnConnectEnd = useCallback(() => {
    console.log('🔌 Connection drag ended');
    
    // Reset state
    setConnectionLineColor('#4a90e2'); // Reset to default
    connectingEdgeRef.current = null;
    reconnectingFromRef.current = null;
  }, []);

  /**
   * Handle edge click - disconnect from closest pin and start reconnection drag
   * Clicking on an edge spline disconnects from the closest pin and starts dragging from the other
   */
  const onEdgeClick: EdgeMouseHandler = useCallback((event: React.MouseEvent, edge: Edge) => {
    event.stopPropagation();
    
    console.log('🔗 Edge clicked:', edge.id);
    
    // Get click position in screen coordinates
    const clickX = event.clientX;
    const clickY = event.clientY;
    
    // Get source and target node positions
    const sourceNode = getNode(edge.source);
    const targetNode = getNode(edge.target);
    
    if (!sourceNode || !targetNode) {
      console.error('❌ Could not find source or target node');
      return;
    }
    
    // Calculate node center positions (approximate - nodes are ~200px wide, ~100px tall)
    const sourceX = sourceNode.position.x + 100; // Approximate center X
    const sourceY = sourceNode.position.y + 50;  // Approximate center Y
    const targetX = targetNode.position.x + 100;
    const targetY = targetNode.position.y + 50;
    
    // Convert flow positions to screen positions for comparison
    // We need to account for zoom and pan, but for distance comparison we can use flow coords
    const flowClick = screenToFlowPosition({ x: clickX, y: clickY });
    
    // Calculate distances from click to source and target
    const distToSource = Math.sqrt(
      Math.pow(flowClick.x - sourceX, 2) + Math.pow(flowClick.y - sourceY, 2)
    );
    const distToTarget = Math.sqrt(
      Math.pow(flowClick.x - targetX, 2) + Math.pow(flowClick.y - targetY, 2)
    );
    
    console.log('📏 Distance to source:', distToSource, 'target:', distToTarget);
    
    // Determine which end to disconnect (closest to click)
    const disconnectFromSource = distToSource < distToTarget;
    
    // The OTHER end is where we'll drag from (the one staying connected)
    const dragFromNodeId = disconnectFromSource ? edge.target : edge.source;
    const dragFromHandleId = disconnectFromSource ? edge.targetHandle : edge.sourceHandle;
    const dragFromHandleType = disconnectFromSource ? 'target' : 'source';
    
    console.log(`🔌 Disconnecting from ${disconnectFromSource ? 'source' : 'target'}, will drag from ${dragFromHandleType}`);
    
    // Remove the edge immediately
    setEdges(eds => eds.filter(e => e.id !== edge.id));
    
    // Store reconnection info
    reconnectingFromRef.current = {
      nodeId: dragFromNodeId,
      handleId: dragFromHandleId,
      handleType: dragFromHandleType as 'source' | 'target'
    };
    
    // Trigger connection start behavior (set color, etc.)
    const dragFromNode = getNode(dragFromNodeId);
    if (dragFromNode) {
      const nodeData = dragFromNode.data as OctaneNodeData;
      let handleColor = '#4a90e2';
      
      // FIX: Check pinColor !== undefined to handle black (0) correctly
      if (dragFromHandleType === 'source' && nodeData.output?.pinInfo) {
        const pinColor = nodeData.output.pinInfo.pinColor;
        if (pinColor !== undefined && pinColor !== null) {
          handleColor = OctaneIconMapper.formatColorValue(pinColor);
        }
      } else if (dragFromHandleType === 'target' && nodeData.inputs) {
        const input = nodeData.inputs.find(i => i.id === dragFromHandleId);
        if (input?.pinInfo) {
          const pinColor = input.pinInfo.pinColor;
          if (pinColor !== undefined && pinColor !== null) {
            handleColor = OctaneIconMapper.formatColorValue(pinColor);
          }
        }
      }
      
      setConnectionLineColor(handleColor);
    }
    
    // Try to programmatically trigger connection drag by finding and clicking the handle
    // Find the handle element and trigger mousedown to start ReactFlow's connection drag
    setTimeout(() => {
      const handleSelector = dragFromHandleType === 'source'
        ? `[data-nodeid="${dragFromNodeId}"][data-handleid="${dragFromHandleId}"][data-handlepos="right"]`
        : `[data-nodeid="${dragFromNodeId}"][data-handleid="${dragFromHandleId}"][data-handlepos="left"]`;
      
      const handleElement = document.querySelector(handleSelector) as HTMLElement;
      
      if (handleElement) {
        console.log('🎯 Found handle element, triggering synthetic drag start');
        
        // Create synthetic mouse event at current mouse position
        const mouseDownEvent = new MouseEvent('mousedown', {
          bubbles: true,
          cancelable: true,
          clientX: clickX,
          clientY: clickY,
          button: 0
        });
        
        // Dispatch to the handle to trigger ReactFlow's connection drag
        handleElement.dispatchEvent(mouseDownEvent);
        
        console.log('✅ Synthetic drag started from handle');
      } else {
        console.warn('⚠️ Could not find handle element:', handleSelector);
        console.log('💡 User can manually drag from the', dragFromHandleType, 'pin to reconnect');
      }
    }, 0);
    
  }, [getNode, screenToFlowPosition, setEdges]);

  /**
   * Handle new connections
   * OCTANE BEHAVIOR:
   * - Output pins can connect to multiple inputs (one-to-many)
   * - Input pins can only connect to one output (many-to-one)
   * - Replace old input connection only when new connection succeeds
   */
  const onConnect = useCallback(
    async (connection: Connection) => {
      try {
        if (!connection.source || !connection.target) {
          console.warn('⚠️ Invalid connection - missing source or target');
          return;
        }

        console.log('🔗 Starting connection creation:', {
          source: connection.source,
          target: connection.target,
          sourceHandle: connection.sourceHandle,
          targetHandle: connection.targetHandle,
        });

        // Check if target input pin already has a connection (needs replacement)
        const existingTargetEdge = edges.find(
          e => e.target === connection.target && e.targetHandle === connection.targetHandle
        );

        // If we were dragging FROM an input pin (connectingEdgeRef), remove that old connection
        const edgesToRemove: string[] = [];
        
        if (connectingEdgeRef.current) {
          console.log('🔄 Removing old source connection:', connectingEdgeRef.current.id);
          edgesToRemove.push(connectingEdgeRef.current.id);
        }
        
        if (existingTargetEdge && existingTargetEdge.id !== connectingEdgeRef.current?.id) {
          console.log('🔄 Removing old target connection:', existingTargetEdge.id);
          edgesToRemove.push(existingTargetEdge.id);
        }

        // Call Octane API to connect nodes
        const sourceHandle = parseInt(connection.source);
        const targetHandle = parseInt(connection.target);

        // Extract pin index from targetHandle (format: "input-N")
        const pinIdx = connection.targetHandle 
          ? parseInt(connection.targetHandle.split('-')[1]) 
          : 0;

        // Get old source handle for cleanup (if replacing connection)
        const oldSourceHandle = existingTargetEdge 
          ? parseInt(existingTargetEdge.source)
          : null;

        console.log('📤 Calling ApiNode.connectToIx:', {
          targetHandle,
          pinIdx,
          sourceHandle,
        });

        const inputItem  = connectingEdgeRef.current ? client.lookupItem(sourceHandle) : client.lookupItem(targetHandle);
        const outputItem = connectingEdgeRef.current ? client.lookupItem(targetHandle) : client.lookupItem(sourceHandle);

        if (!inputItem || !outputItem || !inputItem.children) {
          console.error('❌ Input or Output item not found');
          return;
        }
        const child = inputItem.children[pinIdx];

        if (!child || !child.pinInfo) {
          console.error('❌ Input item has no pin', pinIdx);
          return;
        }
        if (child.pinInfo.type != outputItem.outType) {
          console.error('❌ Input pin does not match output type', child.pinInfo.type, outputItem.outType);
          return;
        }

        // FIX: Read edge color from actual pin info, not stale connectionLineColor state
        const pinColor = child.pinInfo.pinColor;
        const edgeColor = (pinColor !== undefined && pinColor !== null)
          ? OctaneIconMapper.formatColorValue(pinColor)
          : '#4a90e2';

/*
        const response = await client.callApi('ApiNode', 'connectToIx', targetHandle, {
          pinIdx,
          sourceNode: {
            handle: sourceHandle,
            type: 17, // ApiNode type
          },
          evaluate: true, // Trigger evaluation after connection
        });

        console.log('✅ ApiNode.connectToIx response:', response);
*/
        // Create edge ID matching the format used in scene tree building
        const edgeId = `e${sourceHandle}-${targetHandle}-${pinIdx}`;

        // Remove old edges and add new edge
        setEdges((eds) => {
          // Filter out old edges
          const filtered = edgesToRemove.length > 0 
            ? eds.filter(e => !edgesToRemove.includes(e.id))
            : eds;
          
          // Check if edge already exists (shouldn't happen, but safety check)
          const edgeExists = filtered.find(e => e.id === edgeId);
          if (edgeExists) {
            console.log('⚠️ Edge already exists, not adding duplicate:', edgeId);
            return eds;
          }
          
          // Add new edge with correct color from pin info
          // Safe to assert as non-null because we checked at start of function
          const newEdge: Edge = {
            id: edgeId,
            source: connection.source!,
            target: connection.target!,
            sourceHandle: connection.sourceHandle || 'output-0',
            targetHandle: connection.targetHandle || `input-${pinIdx}`,
            type: 'default',
            reconnectable: true,
            animated: false,
            style: { 
              stroke: edgeColor, 
              strokeWidth: 3 
            },
          };
          
          console.log('✅ Adding new edge to ReactFlow:', newEdge, 'with color:', edgeColor);
          return addEdge(newEdge, filtered);
        });

        // Clear the connecting edge ref
        connectingEdgeRef.current = null;

        // Optimized cleanup: remove orphaned collapsed nodes without full rebuild
        console.log('🔄 Cleaning up orphaned nodes (optimized)...');
        await client.handlePinConnectionCleanup(oldSourceHandle);
        console.log('✅ Connection complete!');
        
      } catch (error) {
        console.error('❌ Failed to create connection:', error);
        
        // If API call failed, don't add edge to state
        connectingEdgeRef.current = null;
      }
    },
    [client, setEdges, edges]
  );

  /**
   * Validate connections before allowing them
   * - Source must be an output handle (source)
   * - Target must be an input handle (target)
   */
  const isValidConnection = useCallback(
    (connection: Connection) => {
      console.log('🔍 Validating connection:', connection);
      
      // Basic validation
      if (!connection.source || !connection.target) {
        console.log('❌ Invalid: Missing source or target');
        return false;
      }
      
      // Prevent self-connections
      if (connection.source === connection.target) {
        console.log('❌ Invalid: Self-connection');
        return false;
      }
      
      console.log('✅ Connection is valid');
      return true;
    },
    []
  );

  /**
   * Handle edge changes (delegate to base handler, reconnection handled in onConnectStart)
   */
  const onEdgesChange = useCallback(
    (changes: EdgeChange[]) => {
      // Apply changes using the base handler from useEdgesState
      onEdgesChangeBase(changes);
    },
    [onEdgesChangeBase]
  );

  /**
   * Handle node deletion with optimized cascade
   */
  const onNodesDelete = useCallback(
    async (deletedNodes: Node[]) => {
      try {
        console.log(`🗑️ Deleting ${deletedNodes.length} nodes (optimized)...`);
        for (const node of deletedNodes) {
          const handle = parseInt(node.id);
          await client.deleteNodeOptimized(handle);
        }
        console.log('✅ All nodes deleted (optimized)');
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
        // Note: createNode() already performs optimized scene tree update
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
        onEdgeClick={onEdgeClick}
        isValidConnection={isValidConnection}
        onNodesDelete={onNodesDelete}
        onNodeClick={onNodeClick}
        nodeTypes={nodeTypes}
        minZoom={0.1}
        maxZoom={4}
        defaultEdgeOptions={{
          type: 'default',
          animated: false,
          reconnectable: true,
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
