import { memo } from 'react';
import { Handle, Position, NodeProps } from '@xyflow/react';
import { AIEndpointNodeData } from '../../types';
import styles from './nodes.module.css';

export const AIEndpointNode = memo(({ data, selected }: NodeProps<AIEndpointNodeData>) => {
  const { endpoint } = data;

  return (
    <div className={`${styles.baseNode} ${selected ? styles.selected : ''}`}>
      <Handle type="target" position={Position.Left} id="input" />
      
      <div className={styles.nodeHeader}>
        <div>
          <h3 className={styles.nodeTitle}>{endpoint.title}</h3>
          <div className={styles.nodeVendor}>{endpoint.vendor}</div>
        </div>
      </div>

      {endpoint.category.map((cat, i) => (
        <span key={i} className={styles.nodeCategory}>
          {cat}
        </span>
      ))}

      <p className={styles.nodeDescription}>{endpoint.description}</p>

      <Handle type="source" position={Position.Right} id="output" />
    </div>
  );
});

AIEndpointNode.displayName = 'AIEndpointNode';
