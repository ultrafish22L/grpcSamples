import { memo } from 'react';
import { Handle, Position, NodeProps } from '@xyflow/react';
import { AIEndpointNodeData } from '../../types';
import styles from './nodes.module.css';

function AIEndpointNodeComponent({ data, selected }: NodeProps) {
  const typedData = data as unknown as AIEndpointNodeData;
  const { endpoint } = typedData;

  return (
    <div className={`${styles.baseNode} ${selected ? styles.selected : ''}`}>
      <Handle type="target" position={Position.Left} id="input" />
      
      <div className={styles.nodeHeader}>
        <div>
          <h3 className={styles.nodeTitle}>{endpoint.title}</h3>
          <div className={styles.nodeVendor}>{endpoint.vendor}</div>
        </div>
      </div>

      {endpoint.category.map((cat: string, i: number) => (
        <span key={i} className={styles.nodeCategory}>
          {cat}
        </span>
      ))}

      <p className={styles.nodeDescription}>{endpoint.description}</p>

      <Handle type="source" position={Position.Right} id="output" />
    </div>
  );
}

export const AIEndpointNode = memo(AIEndpointNodeComponent);
AIEndpointNode.displayName = 'AIEndpointNode';
