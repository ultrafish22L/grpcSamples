import { memo, useCallback } from 'react';
import {
  ReactFlow,
  Background,
  Controls,
  MiniMap,
  BackgroundVariant,
  NodeTypes,
} from '@xyflow/react';
import '@xyflow/react/dist/style.css';
import { useStore } from '../../store/useStore';
import { AIEndpointNode, ImageNode, VideoNode, TextInputNode } from '../Nodes';
import styles from './NodeGraph.module.css';

const nodeTypes: NodeTypes = {
  aiEndpoint: AIEndpointNode as any,
  image: ImageNode as any,
  video: VideoNode as any,
  textInput: TextInputNode as any,
};

export const NodeGraph = memo(() => {
  const { nodes, edges, onNodesChange, onEdgesChange, onConnect } = useStore();

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

  return (
    <div className={styles.nodeGraph}>
      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={handleNodesChange}
        onEdgesChange={handleEdgesChange}
        onConnect={handleConnect}
        nodeTypes={nodeTypes}
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
