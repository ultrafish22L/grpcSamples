import { memo } from 'react';
import { Handle, Position, NodeProps } from '@xyflow/react';
import { TextInputNodeData } from '../../types';
import styles from './nodes.module.css';

export const TextInputNode = memo(({ data, selected }: NodeProps<TextInputNodeData>) => {
  return (
    <div className={`${styles.baseNode} ${selected ? styles.selected : ''}`}>
      <div className={styles.nodeHeader}>
        <h3 className={styles.nodeTitle}>{data.label || 'Text Input'}</h3>
      </div>

      <textarea
        className={`${styles.nodeInput} ${styles.nodeTextarea}`}
        placeholder="Enter text..."
        value={data.value}
        onChange={(e) => (data.value = e.target.value)}
      />

      <Handle type="source" position={Position.Right} id="output" />
    </div>
  );
});

TextInputNode.displayName = 'TextInputNode';
