/**
 * Node Graph Editor Component - ReactFlow Implementation
 * Replaces 956-line custom SVG implementation with ReactFlow
 * Maintains all functionality from octaneWeb's NodeGraphEditor.js
 */

import { useEffect, useCallback, useRef, useState } from 'react';
import {
  ReactFlow,
  Node,
  Edge,
  Background,
  BackgroundVariant,
  MiniMap,
  useNodesState,
  useEdgesState,
  useReactFlow,
  addEdge,
  reconnectEdge,
  Connection,
  NodeTypes,
  ReactFlowProvider,
  OnConnectStart,
  OnConnectEnd,
  EdgeChange,
} from '@xyflow/react';
import { OnReconnectEnd } from '@xyflow/system';
import '@xyflow/react/dist/style.css';

import { SceneNode } from '../../services/OctaneClient';
import { useOctane } from '../../hooks/useOctane';
import { OctaneNode, OctaneNodeData } from './OctaneNode';
import { OctaneIconMapper } from '../../utils/OctaneIconMapper';
import { NodeTypeContextMenu } from './NodeTypeContextMenu';
import { NodeContextMenu } from './NodeContextMenu';
import { NodeType } from '../../constants/OctaneTypes';

interface NodeGraphEditorProps {
  sceneTree: SceneNode[];
  selectedNode?: SceneNode | null;
  onNodeSelect?: (node: SceneNode | null) => void;
}

// Define custom node types
const nodeTypes = {
  octane: OctaneNode,
} as const satisfies NodeTypes;

/**
 * Inner component with ReactFlow context access
 */
function NodeGraphEditorInner({ sceneTree, selectedNode, onNodeSelect }: NodeGraphEditorProps) {
  const { client, connected } = useOctane();
  const { fitView } = useReactFlow();
  
  const [nodes, setNodes, onNodesChange] = useNodesState<Node<OctaneNodeData>>([]);
  const [edges, setEdges, onEdgesChangeBase] = useEdgesState<Edge>([]);
  
  // Track whether initial fitView has been called (should only happen once after initial scene sync)
  const hasInitialFitView = useRef(false);
  
  // Context menu state
  const [contextMenuVisible, setContextMenuVisible] = useState(false);
  const [contextMenuPosition, setContextMenuPosition] = useState({ x: 0, y: 0 });
  const [contextMenuType, setContextMenuType] = useState<'node' | 'add'>('add'); // 'node' = right-click on node, 'add' = right-click on empty space
  const [contextMenuNodeId, setContextMenuNodeId] = useState<string | null>(null); // Track which node was right-clicked

  // Track connection line color during drag (matches source pin color)
  const [connectionLineColor, setConnectionLineColor] = useState('#ffc107');
  const connectingEdgeRef = useRef<Edge | null>(null); // Track if creating new connection vs reconnecting

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
      // Include nodes with handle=0 (NO_ITEM/empty pins) if they have pinInfo
      if (!item.handle && !item.pinInfo) {
        return;
      }

      const handleStr = String(item.handle || 0);
      nodeMap.set(handleStr, item);

      // Extract input pins from item.children
      const inputs = item.children || [];
      
      const inputHandles = inputs.map((input: any, inputIndex: number) => {
        // Check if connected node is at top level (level 1) in scene tree
        // Top-level nodes are visible in NGE, nested nodes are collapsed
        const isConnectedNodeAtTopLevel = input.handle && tree.some((topNode: SceneNode) => topNode.handle === input.handle);
        
        return {
          id: `input-${inputIndex}`,
          label: input.staticLabel || input.name,
          pinInfo: input.pinInfo,
          handle: input.handle,  // Connected node handle
          isAtTopLevel: isConnectedNodeAtTopLevel,  // For collapsed detection
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
          onContextMenu: handleNodeContextMenu,
        },
      };

      graphNodes.push(node);
    });

    // Create connections between TOP-LEVEL nodes only
    tree.forEach((node) => {
      // Skip if node has no handle/pinInfo or no children
      if ((!node.handle && !node.pinInfo) || !node.children || node.children.length === 0) {
        return;
      }

      const targetHandle = String(node.handle || 0);
      
      // Check each child (input pin) for connections
      node.children.forEach((childNode: any, inputIndex: number) => {
        // Include connections even if handle=0, as long as pinInfo exists (empty pins with data)
        if (childNode.handle !== undefined || childNode.pinInfo) {
          const sourceHandle = String(childNode.handle || 0);
          
          // Only create edge if BOTH nodes are in our top-level nodeMap
          if (nodeMap.has(sourceHandle) && nodeMap.has(targetHandle)) {
            // FIX: Check pinColor !== undefined to handle black (0) correctly
            const edgeColor = (childNode.pinInfo?.pinColor !== undefined && childNode.pinInfo?.pinColor !== null)
              ? OctaneIconMapper.formatColorValue(childNode.pinInfo.pinColor)
              : '#ffc107';
            
            const edge: Edge = {
              id: `e${sourceHandle}-${targetHandle}-${inputIndex}`,
              source: sourceHandle,
              target: targetHandle,
              sourceHandle: 'output-0',
              targetHandle: `input-${inputIndex}`,
              animated: false,
              selectable: true,
              focusable: true,
              interactionWidth: 20, // ReactFlow v12: wider click area for easier selection
              style: { 
                stroke: edgeColor, 
                strokeWidth: 3 
              },
              data: {
                source: sourceHandle,
                target: targetHandle,
                sourceHandle: 'output-0',
                targetHandle: `input-${inputIndex}`,
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
  }, [client]); // Add client dependency for scene map access

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
      let handleColor = '#ffc107'; // Default color
      
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
    setConnectionLineColor('#ffc107'); // Reset to default
    connectingEdgeRef.current = null;
  }, []);

  /**
   * Handle edge reconnect - ReactFlow's built-in edge reconnection
   * Triggered when user drags an edge endpoint to a new handle
   * Uses ReactFlow's reconnectEdge utility as per best practices
   */
  const onReconnect = useCallback((oldEdge: Edge, newConnection: Connection) => {
    console.log('🔄 RECONNECT triggered:', oldEdge.id, '→', newConnection);
    
    // Detect no-op reconnection: user dropped edge back on the same pin
    if (oldEdge.target === newConnection.target && 
        oldEdge.targetHandle === newConnection.targetHandle &&
        oldEdge.source === newConnection.source &&
        oldEdge.sourceHandle === newConnection.sourceHandle) {
      console.log('⏭️ No-op reconnection detected - ignoring (same source and target)');
      return;
    }
    
    // Update UI using ReactFlow's official reconnectEdge utility
    setEdges((eds) => reconnectEdge(oldEdge, newConnection, eds));

    // Sync with Octane in background (async operations after state update)
    if (!client) {
      console.warn('⚠️ Cannot sync edge reconnection: No Octane client');
      return;
    }

    // Sync reconnection with Octane (disconnect old, connect new)
    (async () => {
      try {
        // Disconnect old connection
        const oldTargetHandle = parseInt(oldEdge.target);
        const oldPinIdx = oldEdge.targetHandle ? 
          parseInt(oldEdge.targetHandle.split('-')[1]) : 0;
        
        console.log(`🔌 Disconnecting old: node=${oldTargetHandle}, pin=${oldPinIdx}`);
        await client.disconnectPin(oldTargetHandle, oldPinIdx);
        
        // Connect new connection
        const newTargetHandle = parseInt(newConnection.target!);
        const newSourceHandle = parseInt(newConnection.source!);
        const newPinIdx = newConnection.targetHandle ? 
          parseInt(newConnection.targetHandle.split('-')[1]) : 0;
        
        console.log(`🔌 Connecting new: source=${newSourceHandle} → target=${newTargetHandle}, pin=${newPinIdx}`);
        await client.connectPinByIndex(newTargetHandle, newPinIdx, newSourceHandle, true);
        console.log('✅ Octane edge reconnected');
      } catch (error) {
        console.error('❌ Failed to sync edge reconnection with Octane:', error);
      }
    })();
  }, [client, setEdges]);

  /**
   * Handle edge reconnect end - detect failed reconnections
   * When user drags an edge and drops on empty space, disconnect it in Octane
   * OCTANE BEHAVIOR: Failed reconnection = disconnect the edge entirely
   * 
   * ReactFlow v12 Pattern: Use connectionState.isValid to detect success/failure
   */
  const onReconnectEnd: OnReconnectEnd = useCallback(
    (_event, edge, _handleType, connectionState) => {
      console.log('🔄 RECONNECT END:', edge.id, 'isValid:', connectionState.isValid);
      
      // If reconnection succeeded (connectionState.isValid === true), onReconnect already handled it
      if (connectionState.isValid) {
        console.log('✅ Reconnection succeeded - onReconnect already handled sync');
        return;
      }

      // Failed reconnection - user dropped on empty space or invalid target
      // Disconnect the edge in Octane and remove from UI
      console.log('❌ Reconnection failed - disconnecting edge:', edge.id);

      if (!client) {
        console.warn('⚠️ Cannot disconnect edge: No Octane client');
        return;
      }

      // Disconnect in Octane and remove from UI
      (async () => {
        try {
          // Parse edge info: target node and pin index
          const targetHandle = parseInt(edge.target);
          const pinIdx = edge.targetHandle 
            ? parseInt(edge.targetHandle.split('-')[1]) 
            : 0;

          console.log(`🔌 Disconnecting in Octane: node=${targetHandle}, pin=${pinIdx}`);
          await client.disconnectPin(targetHandle, pinIdx);
          console.log('✅ Pin disconnected in Octane');

          // Remove edge from UI
          setEdges((eds) => eds.filter(e => e.id !== edge.id));
          console.log('✅ Edge removed from UI');
          
        } catch (error) {
          console.error('❌ Failed to disconnect edge:', error);
        }
      })();
    }, 
    [client, setEdges]
  );

  /**
   * Handle edge click - Octane behavior: disconnect at closest pin, start drag from other end
   * This function is passed to custom edges via data.onClick
   */
  // Edge click/reconnection is now handled by ReactFlow's built-in edgesReconnectable feature
  // No custom logic needed - just drag edge ends to reconnect

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

        // Detect no-op: reconnecting to same source (duplicate connection)
        if (existingTargetEdge && existingTargetEdge.source === connection.source && 
            existingTargetEdge.sourceHandle === connection.sourceHandle) {
          console.log('⏭️ No-op connection detected - already connected to same source, ignoring');
          connectingEdgeRef.current = null;
          return;
        }

        // If we were dragging FROM an input pin (connectingEdgeRef), remove that old connection
        const edgesToRemove: string[] = [];
        const nodesToRemove: string[] = [];
        
        if (connectingEdgeRef.current) {
          console.log('🔄 Removing old source connection:', connectingEdgeRef.current.id);
          edgesToRemove.push(connectingEdgeRef.current.id);
        }
        
        if (existingTargetEdge && existingTargetEdge.id !== connectingEdgeRef.current?.id) {
          console.log('🔄 Removing old target connection:', existingTargetEdge.id);
          edgesToRemove.push(existingTargetEdge.id);
          
          // COLLAPSED NODE CLEANUP: Check if old connection points to a collapsed (default value) node
          // Octane automatically deletes these when replaced with a new connection
          const oldSourceHandle = parseInt(existingTargetEdge.source);
          const oldSourceNode = client.lookupItem(oldSourceHandle);
          
          if (oldSourceNode) {
            // A collapsed node is typically:
            // 1. A default value node (Float value, RGB color, Bool value, etc.)
            // 2. Has nodeInfo.takesPinDefaultValue = true OR
            // 3. Matches the pin's defaultNodeType
            const isCollapsedNode = oldSourceNode.nodeInfo?.takesPinDefaultValue === true ||
                                   oldSourceNode.name?.includes('value') ||
                                   oldSourceNode.name?.includes('color');
            
            if (isCollapsedNode) {
              console.log('🗑️ Detected collapsed node to remove:', oldSourceNode.name, oldSourceHandle);
              nodesToRemove.push(existingTargetEdge.source);
            }
          }
        }

        // Call Octane API to connect nodes
        const sourceHandle = parseInt(connection.source);
        const targetHandle = parseInt(connection.target);

        // Extract pin index from targetHandle (format: "input-N")
        const pinIdx = connection.targetHandle 
          ? parseInt(connection.targetHandle.split('-')[1]) 
          : 0;

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
          : '#ffc107';

        // Connect pin in Octane
        await client.connectPinByIndex(targetHandle, pinIdx, sourceHandle, true);
        console.log('✅ Pin connected in Octane');

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
            animated: false,
            selectable: true,
            focusable: true,
            interactionWidth: 20, // ReactFlow v12: wider click area for easier selection
            style: { 
              stroke: edgeColor, 
              strokeWidth: 3 
            },
          };
          
          console.log('✅ Adding new edge to ReactFlow:', newEdge, 'with color:', edgeColor);
          return addEdge(newEdge, filtered);
        });

        // Remove collapsed nodes from scene and ReactFlow
        if (nodesToRemove.length > 0) {
          console.log('🗑️ Removing', nodesToRemove.length, 'collapsed node(s)');
          
          // Remove from ReactFlow nodes
          setNodes((nds) => nds.filter(n => !nodesToRemove.includes(n.id)));
          
          // Remove from scene.map
          nodesToRemove.forEach(nodeId => {
            const handleNum = parseInt(nodeId);
            const removedNode = client.lookupItem(handleNum);
            if (removedNode) {
              console.log('  🗑️ Removed from scene.map:', removedNode.name, handleNum);
              client.removeFromScene(handleNum);
            }
          });
          
          console.log('✅ Collapsed node cleanup complete');
        }

        // Clear the connecting edge ref
        connectingEdgeRef.current = null;

        // NO scene sync - connection only updates local UI state
        // Collapsed nodes removed locally, no full rebuild needed
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
    (connection: Edge | Connection) => {
      // Basic validation
      if (!connection.source || !connection.target) {
        console.warn('⚠️ Invalid connection: Missing source or target');
        return false;
      }
      
      // Prevent self-connections
      if (connection.source === connection.target) {
        console.warn('⚠️ Invalid connection: Self-connection not allowed');
        return false;
      }
      
      return true;
    },
    []
  );

  /**
   * Handle edge changes (delegate to base handler, reconnection handled in onConnectStart)
   */
  const onEdgesChange = useCallback(
    (changes: EdgeChange[]) => {
      // DEBUG: Log edge changes
      console.log('📝 EDGE CHANGES:', changes);
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
   * Handle edge click - select edge for visual feedback
   */
  const onEdgeClick = useCallback(
    (_event: React.MouseEvent, edge: Edge) => {
      console.log('🔗 Edge clicked:', edge.id);
      // Edge selection is handled automatically by ReactFlow
    },
    []
  );



  /**
   * Handle edge deletion (keyboard Delete key or context menu)
   * NOTE: Currently connections are visual-only in ReactFlow and not synced to Octane backend
   * When backend sync is implemented, this should call ApiNode.disconnectIx or similar
   */
  const onEdgesDelete = useCallback(
    async (deletedEdges: Edge[]) => {
      console.log(`✂️ Deleted ${deletedEdges.length} edge(s) from graph (visual only)`);
      // TODO: When backend connection sync is implemented, add API calls here
      // For each edge: await client.callApi('ApiNode', 'disconnectIx', targetHandle, { pinIdx });
    },
    []
  );

  /**
   * Context menu event handlers
   */
  // Handle right-click on empty pane (add node menu)
  // Using ReactFlow v12's official onPaneContextMenu prop
  const handlePaneContextMenu = useCallback((event: React.MouseEvent | MouseEvent) => {
    console.log('🖱️ [NodeGraphEditor] Pane context menu triggered', {
      position: { x: event.clientX, y: event.clientY },
    });
    event.preventDefault();
    setContextMenuPosition({ x: event.clientX, y: event.clientY });
    setContextMenuType('add');
    setContextMenuNodeId(null);
    setContextMenuVisible(true);
  }, []);

  // Handle right-click on a node (node actions menu)
  const handleNodeContextMenu = useCallback((event: React.MouseEvent, nodeId: string) => {
    console.log('🖱️ [NodeGraphEditor] handleNodeContextMenu fired!', {
      nodeId,
      position: { x: event.clientX, y: event.clientY }
    });
    event.preventDefault();
    event.stopPropagation();
    
    // Select the right-clicked node in ReactFlow
    setNodes((nds) =>
      nds.map((n) => ({
        ...n,
        selected: n.id === nodeId,
      }))
    );
    
    // Select the node app-wide (Scene Outliner, Node Inspector, etc.)
    const sceneNode = sceneTree.find((item) => String(item.handle) === nodeId);
    if (sceneNode && onNodeSelect) {
      onNodeSelect(sceneNode);
      console.log('✅ Node selected app-wide:', sceneNode.name);
    }
    
    setContextMenuPosition({ x: event.clientX, y: event.clientY });
    setContextMenuType('node');
    setContextMenuNodeId(nodeId);
    setContextMenuVisible(true);
  }, [sceneTree, onNodeSelect, setNodes]);

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
    setContextMenuNodeId(null);
  }, []);



  /**
   * Node context menu action handlers
   */
  const handleDeleteSelected = useCallback(async () => {
    const selectedNodes = nodes.filter((n) => n.selected);
    
    if (selectedNodes.length === 0) {
      console.warn('⚠️ No nodes selected for deletion');
      return;
    }

    console.log(`🗑️ Deleting ${selectedNodes.length} selected node(s)...`);
    
    for (const node of selectedNodes) {
      try {
        const success = await client.deleteNode(node.id);
        if (success) {
          console.log(`✅ Deleted node: ${node.id}`);
        } else {
          console.error(`❌ Failed to delete node: ${node.id}`);
        }
      } catch (error) {
        console.error(`❌ Error deleting node ${node.id}:`, error);
      }
    }
  }, [nodes, client]);

  const handleSaveAsMacro = useCallback(() => {
    const selectedNodes = nodes.filter((n) => n.selected);
    console.log('💾 Save as Macro - Selected nodes:', selectedNodes.length);
    // TODO: Implement save to LocalDB
    // Requires: apilocaldb.proto API integration
    alert('Save as Macro feature requires LocalDB API integration\n(apilocaldb.proto)\n\nComing soon!');
  }, [nodes]);

  const handleRenderNode = useCallback(() => {
    console.log('🎬 Render Node - Node ID:', contextMenuNodeId);
    // TODO: Implement render target switching
    // Requires: API to set render target to specific node
    alert('Render Node feature requires render target switching API\n\nComing soon!');
  }, [contextMenuNodeId]);

  const handleGroupItems = useCallback(() => {
    const selectedNodes = nodes.filter((n) => n.selected);
    
    if (selectedNodes.length < 2) {
      console.warn('⚠️ Need at least 2 nodes selected to create a group');
      return;
    }
    
    console.log('📦 Group Items - Selected nodes:', selectedNodes.length);
    // TODO: Implement node grouping
    // Requires: API to create node groups and maintain connections
    alert(`Group ${selectedNodes.length} nodes feature requires grouping API\n\nComing soon!`);
  }, [nodes]);

  const handleShowInOutliner = useCallback(() => {
    console.log('🔍 Show in Outliner - Node ID:', contextMenuNodeId);
    
    // Find the node and its corresponding scene node
    const reactFlowNode = nodes.find((n) => n.id === contextMenuNodeId);
    if (reactFlowNode) {
      // Trigger selection in Scene Outliner
      const sceneNode = sceneTree.find((item) => String(item.handle) === reactFlowNode.id);
      if (sceneNode && onNodeSelect) {
        onNodeSelect(sceneNode);
        console.log('✅ Node selected in outliner:', sceneNode.name);
      }
    }
  }, [contextMenuNodeId, nodes, sceneTree, onNodeSelect]);



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
    <>
      {/* Context Menus */}
      {contextMenuVisible && contextMenuType === 'add' && (
        <NodeTypeContextMenu
          x={contextMenuPosition.x}
          y={contextMenuPosition.y}
          onSelectNodeType={handleSelectNodeType}
          onClose={handleCloseContextMenu}
        />
      )}
      
      {contextMenuVisible && contextMenuType === 'node' && (
        <NodeContextMenu
          x={contextMenuPosition.x}
          y={contextMenuPosition.y}
          selectedNodeCount={nodes.filter((n) => n.selected).length}
          onDeleteSelected={handleDeleteSelected}
          onSaveAsMacro={handleSaveAsMacro}
          onRenderNode={handleRenderNode}
          onGroupItems={handleGroupItems}
          onShowInOutliner={handleShowInOutliner}
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
        onReconnect={onReconnect}
        onReconnectEnd={onReconnectEnd}
        isValidConnection={isValidConnection}
        onNodesDelete={onNodesDelete}
        onEdgesDelete={onEdgesDelete}
        onNodeClick={onNodeClick}
        onEdgeClick={onEdgeClick}
        onPaneContextMenu={handlePaneContextMenu}
        elementsSelectable={true}
        nodesConnectable={true}
        nodesDraggable={true}
        edgesFocusable={true}
        edgesReconnectable={true} // Enable edge reconnection by dragging
        reconnectRadius={50} // Allow clicking within 50px of edge to start reconnect (larger area)
        panOnDrag={[1, 2]} // Only pan with middle/right mouse button, not left button
        selectionOnDrag={false}
        selectNodesOnDrag={false}
        nodeTypes={nodeTypes}
        minZoom={0.1}
        maxZoom={4}
        defaultEdgeOptions={{
          type: 'default', // Use default edges - custom component blocks reconnection
          animated: false,
          selectable: true,
          focusable: true,
          interactionWidth: 20, // ReactFlow v12: wider click area for easier selection
          style: { stroke: '#ffc107', strokeWidth: 3 },
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
    </>
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
