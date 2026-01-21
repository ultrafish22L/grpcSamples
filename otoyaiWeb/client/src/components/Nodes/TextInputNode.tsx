import { memo } from 'react';
import { Handle, Position, NodeProps } from '@xyflow/react';
import { TextInputNodeData } from '../../types';
import styles from './nodes.module.css';

function TextInputNodeComponent({ data, selected }: NodeProps) {
  const typedData = data as unknown as TextInputNodeData;
  
  return (
    <div className={`${styles.baseNode} ${selected ? styles.selected : ''}`}>
      <div className={styles.nodeHeader}>
        <h3 className={styles.nodeTitle}>{typedData.label || 'Text Input'}</h3>
      </div>

      <textarea
        className={`${styles.nodeInput} ${styles.nodeTextarea}`}
        placeholder="Enter text..."
        value={typedData.value}
        onChange={(e) => (typedData.value = e.target.value)}
      />

      <Handle type="source" position={Position.Right} id="output" />
    </div>
  );
}

export const TextInputNode = memo(TextInputNodeComponent);
TextInputNode.displayName = 'TextInputNode';
