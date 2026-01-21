import { memo, useRef, ChangeEvent } from 'react';
import { Handle, Position, NodeProps } from '@xyflow/react';
import { VideoNodeData } from '../../types';
import styles from './nodes.module.css';

export const VideoNode = memo(({ data, selected }: NodeProps<VideoNodeData>) => {
  const fileInputRef = useRef<HTMLInputElement>(null);

  const handleFileSelect = (e: ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0];
    if (file) {
      const url = URL.createObjectURL(file);
      data.preview = url;
      data.file = file;
    }
  };

  return (
    <div className={`${styles.baseNode} ${selected ? styles.selected : ''}`}>
      <div className={styles.nodeHeader}>
        <h3 className={styles.nodeTitle}>Video</h3>
      </div>

      <input
        type="text"
        placeholder="Video URL"
        className={styles.nodeInput}
        value={data.url || ''}
        onChange={(e) => (data.url = e.target.value)}
      />

      <input
        ref={fileInputRef}
        type="file"
        accept="video/*"
        className={styles.fileInput}
        onChange={handleFileSelect}
      />

      <button
        className={styles.fileButton}
        onClick={() => fileInputRef.current?.click()}
      >
        Upload Video
      </button>

      {(data.preview || data.url) && (
        <video
          src={data.preview || data.url}
          controls
          className={styles.nodePreview}
        />
      )}

      <Handle type="source" position={Position.Right} id="output" />
    </div>
  );
});

VideoNode.displayName = 'VideoNode';
