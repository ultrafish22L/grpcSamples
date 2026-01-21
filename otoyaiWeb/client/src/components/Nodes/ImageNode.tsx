import { memo, useRef, ChangeEvent } from 'react';
import { Handle, Position, NodeProps } from '@xyflow/react';
import { ImageNodeData } from '../../types';
import styles from './nodes.module.css';

export const ImageNode = memo(({ data, selected }: NodeProps<ImageNodeData>) => {
  const fileInputRef = useRef<HTMLInputElement>(null);

  const handleFileSelect = (e: ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0];
    if (file) {
      const reader = new FileReader();
      reader.onload = (event) => {
        const preview = event.target?.result as string;
        data.preview = preview;
        data.file = file;
      };
      reader.readAsDataURL(file);
    }
  };

  return (
    <div className={`${styles.baseNode} ${selected ? styles.selected : ''}`}>
      <div className={styles.nodeHeader}>
        <h3 className={styles.nodeTitle}>Image</h3>
      </div>

      <input
        type="text"
        placeholder="Image URL"
        className={styles.nodeInput}
        value={data.url || ''}
        onChange={(e) => (data.url = e.target.value)}
      />

      <input
        ref={fileInputRef}
        type="file"
        accept="image/*"
        className={styles.fileInput}
        onChange={handleFileSelect}
      />

      <button
        className={styles.fileButton}
        onClick={() => fileInputRef.current?.click()}
      >
        Upload Image
      </button>

      {(data.preview || data.url) && (
        <img
          src={data.preview || data.url}
          alt="Preview"
          className={styles.nodePreview}
        />
      )}

      <Handle type="source" position={Position.Right} id="output" />
    </div>
  );
});

ImageNode.displayName = 'ImageNode';
