/**
 * Node Graph Editor Component - ReactFlow Implementation
 * Replaces 956-line custom SVG implementation with ReactFlow
 * Maintains all functionality from octaneWeb's NodeGraphEditor.js
 */

import { useEffect, useCallback, useRef } from 'react';
import ReactFlow, {
  Node,
  Edge,
  Background,
  BackgroundVariant,
  MiniMap,
  useNodesState,
  useEdgesState,
  addEdge,
  Connection,
  NodeTypes,
  ReactFlowProvider,
} from 'reactflow';
import 'reactflow/dist/style.css';

import { SceneNode } from '../../services/OctaneClient';
import { useOctane } from '../../hooks/useOctane';
import { OctaneNode, OctaneNodeData } from './OctaneNode';
import { OctaneIconMapper } from '../../utils/OctaneIconMapper';

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
  
  const [nodes, setNodes, onNodesChange] = useNodesState([]);
  const [edges, setEdges, onEdgesChange] = useEdgesState([]);
  const containerRef = useRef<HTMLDivElement>(null);

  /**
   * Convert scene tree to ReactFlow nodes and edges
   * Following octaneWeb's NodeGraphEditor.js pattern:
   * - Only show TOP-LEVEL nodes from scene.tree (no recursive children)
   * - Only show direct connections between top-level nodes
   * - Use bezier curves for connection splines
   */
  const convertSceneToGraph = useCallback((tree: SceneNode[]) => {
    console.log('🔄 [convertSceneToGraph] Starting conversion...');
    console.log('🔄 [convertSceneToGraph] Top-level nodes:', tree.length);
    console.groupCollapsed('🔄 Converting scene tree to ReactFlow graph');
    
    const graphNodes: Node<OctaneNodeData>[] = [];
    const graphEdges: Edge[] = [];
    const nodeMap = new Map<string, SceneNode>();

    // Only process TOP-LEVEL nodes (matching octaneWeb behavior)
    // octaneWeb: scene.tree.forEach((item, index) => { ... })
    const nodeSpacing = 250;
    const yCenter = 300;
    
    tree.forEach((item, index) => {
      console.log(`🔄 [convertSceneToGraph] Processing top-level node ${index}:`, {
        name: item.name,
        handle: item.handle,
        type: item.type,
        typeEnum: item.typeEnum,
        hasChildren: !!item.children?.length,
        childCount: item.children?.length || 0
      });
      
      // Skip nodes without handles
      if (!item.handle) {
        console.log(`🔄 [convertSceneToGraph]   ⚠️ Skipping node without handle: ${item.name}`);
        return;
      }

      const handleStr = String(item.handle);
      nodeMap.set(handleStr, item);

      // Extract input pins from item.children (matching octaneWeb line 1020)
      const inputs = item.children || [];
      console.log(`🔄 [convertSceneToGraph]   📌 Node "${item.name}" has ${inputs.length} inputs`);
      
      const inputHandles = inputs.map((input: any, inputIndex: number) => {
        console.log(`🔄 [convertSceneToGraph]     Input ${inputIndex}:`, {
          name: input.staticLabel || input.name,
          pinInfo: input.pinInfo,
          connectedNode: input.connectedNode?.name,
        });
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
      console.log(`🔄 [convertSceneToGraph]   📌 Node "${item.name}" output:`, { output });

      // Position nodes horizontally with spacing (matching octaneWeb layout)
      const node: Node<OctaneNodeData> = {
        id: handleStr,
        type: 'octane',
        position: { 
          x: 100 + (index * nodeSpacing),
          y: yCenter + (index * 20), // Slight vertical offset per node
        },
        data: {
          sceneNode: item,
          inputs: inputHandles,
          output,
        },
      };

      graphNodes.push(node);
      console.log(`🔄 [convertSceneToGraph]   ✅ Created node: ${item.name} (${handleStr}) with ${inputHandles.length} inputs and 1 output`);
    });

    // Create connections between TOP-LEVEL nodes only
    // Look for connections in node.children (matching octaneWeb pattern)
    console.log(`🔄 [convertSceneToGraph] Creating edges...`);
    tree.forEach((node) => {
      if (!node.handle || !node.children || node.children.length === 0) {
        console.log(`🔄 [convertSceneToGraph]   ⚠️ Node "${node.name}" has no children, skipping edge creation`);
        return;
      }

      const targetHandle = String(node.handle);
      
      // Check each child (input pin) for connections
      // Each child IS a connected node (source)
      node.children.forEach((childNode: any, inputIndex: number) => {
        if (childNode.handle) {
          const sourceHandle = String(childNode.handle);
          
          console.log(`🔄 [convertSceneToGraph]   🔗 Found connection: "${childNode.name}" → "${node.name}" (pin ${inputIndex})`);
          console.log(`🔄 [convertSceneToGraph]      Source handle: ${sourceHandle}, Target handle: ${targetHandle}`);
          console.log(`🔄 [convertSceneToGraph]      Source in map: ${nodeMap.has(sourceHandle)}, Target in map: ${nodeMap.has(targetHandle)}`);
          
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
            console.log(`🔄 [convertSceneToGraph]      ✅ Created edge with color: ${edgeColor}`);
          } else {
            console.log(`🔄 [convertSceneToGraph]      ⚠️ Skipping edge - one or both nodes not in top-level map`);
          }
        }
      });
    });

    console.log(`🔄 [convertSceneToGraph] Completed: ${graphNodes.length} nodes, ${graphEdges.length} edges`);
    console.debug(`Created ${graphNodes.length} top-level nodes and ${graphEdges.length} edges`);
    console.groupEnd();

    return { nodes: graphNodes, edges: graphEdges };
  }, []);

  /**
   * Load scene graph when sceneTree changes
   */
  useEffect(() => {
    console.log('📊 [NodeGraphEditor] useEffect triggered');
    console.log('📊 [NodeGraphEditor] sceneTree:', sceneTree);
    console.log('📊 [NodeGraphEditor] sceneTree length:', sceneTree?.length || 0);
    
    if (!sceneTree || sceneTree.length === 0) {
      console.log('📊 [NodeGraphEditor] No scene tree data - setting empty nodes/edges');
      console.debug('No scene tree data available');
      setNodes([]);
      setEdges([]);
      return;
    }

    console.log('📊 [NodeGraphEditor] Converting scene tree to graph...');
    console.log(`Loading scene graph with ${sceneTree.length} root nodes`);
    const { nodes: graphNodes, edges: graphEdges } = convertSceneToGraph(sceneTree);
    
    console.log('📊 [NodeGraphEditor] Conversion complete:');
    console.log('📊 [NodeGraphEditor]   - nodes:', graphNodes.length);
    console.log('📊 [NodeGraphEditor]   - edges:', graphEdges.length);
    console.log('📊 [NodeGraphEditor] First node:', graphNodes[0]);
    
    setNodes(graphNodes);
    setEdges(graphEdges);

    // Note: Don't auto-fit view - use default zoom level matching Octane
    // The defaultViewport prop on ReactFlow sets the initial zoom
  }, [sceneTree, convertSceneToGraph, setNodes, setEdges]);

  /**
   * Handle new connections
   */
  const onConnect = useCallback(
    async (connection: Connection) => {
      console.log('Creating connection:', connection);

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

        console.log('Connection created successfully');

        // Add edge to ReactFlow
        setEdges((eds) => addEdge(connection, eds));

        // Refresh scene tree
        await client.buildSceneTree();
      } catch (error) {
        console.error('Failed to create connection:', error);
      }
    },
    [client, setEdges]
  );

  /**
   * Handle node deletion
   */
  const onNodesDelete = useCallback(
    async (deletedNodes: Node[]) => {
      console.log('Deleting nodes:', deletedNodes.map((n) => n.id));

      try {
        for (const node of deletedNodes) {
          const handle = parseInt(node.id);
          await client.callApi('ApiItem', 'deleteItem', handle, {});
        }

        console.log('Nodes deleted successfully');
        
        // Refresh scene tree
        await client.buildSceneTree();
      } catch (error) {
        console.error('Failed to delete nodes:', error);
      }
    },
    [client]
  );



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
    <div ref={containerRef} style={{ width: '100%', height: '100%', position: 'relative' }}>
      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onConnect={onConnect}
        onNodesDelete={onNodesDelete}
        nodeTypes={nodeTypes}
        defaultViewport={{ x: 100, y: 100, zoom: 0.2}}
        minZoom={0.1}
        maxZoom={4}
        defaultEdgeOptions={{
          type: 'default',
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
export function NodeGraphEditor({ sceneTree }: NodeGraphEditorProps) {
  return (
    <ReactFlowProvider>
      <NodeGraphEditorInner sceneTree={sceneTree} />
    </ReactFlowProvider>
  );
}
