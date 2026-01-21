import { memo, useCallback } from 'react';
import {
  ReactFlow,
  Background,
  Controls,
  MiniMap,
  BackgroundVariant,
  NodeTypes,
  Connection,
  Edge,
} from '@xyflow/react';
import '@xyflow/react/dist/style.css';
import { useStore } from '../../store/useStore';
import { AIEndpointNode, ImageNode, VideoNode, TextInputNode } from '../Nodes';
import { isValidConnection } from '../../utils/connectionValidator';
import { logger } from '../../services/logger';
import styles from './NodeGraph.module.css';

const nodeTypes: NodeTypes = {
  aiEndpoint: AIEndpointNode as any,
  image: ImageNode as any,
  video: VideoNode as any,
  textInput: TextInputNode as any,
};

export const NodeGraph = memo(() => {
  const { nodes, edges, onNodesChange, onEdgesChange, onConnect, onReconnect } = useStore();

  const handleNodesChange = useCallback(
    (changes: any) => onNodesChange(changes),
    [onNodesChange]
  );

  const handleEdgesChange = useCallback(
    (changes: any) => onEdgesChange(changes),
    [onEdgesChange]
  );

  const handleConnect = useCallback(
    (connection: any) => onConnect(connection),
    [onConnect]
  );

  const handleIsValidConnection = useCallback(
    (connection: Connection | Edge) => {
      // Convert Edge to Connection format if needed
      const conn: Connection = 'id' in connection 
        ? {
            source: connection.source,
            target: connection.target,
            sourceHandle: connection.sourceHandle ?? null,
            targetHandle: connection.targetHandle ?? null,
          }
        : connection;
      
      const valid = isValidConnection(conn, nodes);
      if (!valid) {
        logger.warn('Invalid connection attempted', {
          source: conn.source,
          target: conn.target,
        });
      }
      return valid;
    },
    [nodes]
  );

  const handleReconnect = useCallback(
    (oldEdge: Edge, newConnection: Connection) => {
      onReconnect(oldEdge, newConnection);
    },
    [onReconnect]
  );

  const handleReconnectStart = useCallback(
    (_event: React.MouseEvent, edge: Edge) => {
      logger.debug('Edge reconnect started', { edge: edge.id });
    },
    []
  );

  const handleReconnectEnd = useCallback(
    (_event: MouseEvent | TouchEvent, edge: Edge) => {
      // If the reconnect ends without a new connection, the edge is automatically removed
      logger.debug('Edge reconnect ended', { edge: edge.id });
    },
    []
  );

  const handleEdgeClick = useCallback(
    (_event: React.MouseEvent, edge: Edge) => {
      // Only delete when clicking the middle of the edge (not near pins)
      // Edge reconnection handles dragging when clicking near pins
      logger.info('Edge clicked for deletion', { edge: edge.id });
      onEdgesChange([{ type: 'remove', id: edge.id }]);
    },
    [onEdgesChange]
  );

  return (
    <div className={styles.nodeGraph}>
      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={handleNodesChange}
        onEdgesChange={handleEdgesChange}
        onConnect={handleConnect}
        onEdgeClick={handleEdgeClick}
        onReconnect={handleReconnect}
        onReconnectStart={handleReconnectStart}
        onReconnectEnd={handleReconnectEnd}
        isValidConnection={handleIsValidConnection}
        nodeTypes={nodeTypes}
        reconnectRadius={20}
        fitView
        className={styles.reactFlowWrapper}
      >
        <Background variant={BackgroundVariant.Dots} gap={16} size={1} />
        <Controls />
        <MiniMap
          nodeColor={(node) => {
            switch (node.type) {
              case 'aiEndpoint':
                return '#00d4ff';
              case 'image':
                return '#44ff44';
              case 'video':
                return '#ff44ff';
              case 'textInput':
                return '#ffaa44';
              default:
                return '#4a4a4a';
            }
          }}
        />
      </ReactFlow>
    </div>
  );
});

NodeGraph.displayName = 'NodeGraph';
