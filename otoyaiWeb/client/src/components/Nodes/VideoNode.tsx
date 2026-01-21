import { memo, useState } from 'react';
import { Handle, Position, NodeProps, useUpdateNodeInternals } from '@xyflow/react';
import { VideoNodeData, MediaItem } from '../../types';
import styles from './nodes.module.css';

export const VideoNode = memo(({ id, data, selected }: NodeProps<VideoNodeData>) => {
  const updateNodeInternals = useUpdateNodeInternals();
  const [, forceUpdate] = useState({});

  // Initialize items if empty
  if (!data.items || data.items.length === 0) {
    data.items = [];
  }

  const addItem = (type: 'url' | 'file') => {
    const newItem: MediaItem = {
      id: `${Date.now()}-${Math.random()}`,
      collapsed: false,
    };

    if (type === 'url') {
      // Add URL item
      data.items.push(newItem);
    } else {
      // Trigger file picker
      const input = document.createElement('input');
      input.type = 'file';
      input.accept = 'video/*';
      input.onchange = (e: Event) => {
        const file = (e.target as HTMLInputElement).files?.[0];
        if (file) {
          const url = URL.createObjectURL(file);
          newItem.preview = url;
          newItem.file = file;
          newItem.name = file.name;
          data.items.push(newItem);
          updateNodeInternals(id);
          forceUpdate({});
        }
      };
      input.click();
      return; // Don't update yet, wait for file load
    }

    updateNodeInternals(id);
    forceUpdate({});
  };

  const deleteItem = (itemId: string) => {
    data.items = data.items.filter((item) => item.id !== itemId);
    updateNodeInternals(id);
    forceUpdate({});
  };

  const toggleCollapse = (itemId: string) => {
    const item = data.items.find((i) => i.id === itemId);
    if (item) {
      item.collapsed = !item.collapsed;
      forceUpdate({});
    }
  };

  const updateItemUrl = (itemId: string, url: string) => {
    const item = data.items.find((i) => i.id === itemId);
    if (item) {
      item.url = url;
      item.name = url.split('/').pop() || url;
      forceUpdate({});
    }
  };

  const hasMultipleItems = data.items.length > 1;

  return (
    <div className={`${styles.baseNode} ${selected ? styles.selected : ''}`}>
      <div className={styles.nodeHeader}>
        <h3 className={styles.nodeTitle}>Video</h3>
        <div className={styles.headerButtons}>
          <button
            className={styles.iconButton}
            onClick={() => addItem('url')}
            title="Add URL"
          >
            +🔗
          </button>
          <button
            className={styles.iconButton}
            onClick={() => addItem('file')}
            title="Add File"
          >
            +📁
          </button>
        </div>
      </div>

      <div className={styles.mediaItems}>
        {data.items.map((item) => (
          <div key={item.id} className={styles.mediaItem}>
            <div className={styles.mediaItemHeader}>
              <button
                className={styles.collapseButton}
                onClick={() => toggleCollapse(item.id)}
              >
                {item.collapsed ? '▶' : '▼'}
              </button>
              <span className={styles.mediaItemName}>
                {item.name || item.url || 'New Video'}
              </span>
              <button
                className={styles.deleteButton}
                onClick={() => deleteItem(item.id)}
                title="Delete"
              >
                ×
              </button>
            </div>

            {!item.collapsed && (
              <div className={styles.mediaItemContent}>
                {!item.file && (
                  <input
                    type="text"
                    placeholder="Video URL"
                    className={styles.nodeInput}
                    value={item.url || ''}
                    onChange={(e) => updateItemUrl(item.id, e.target.value)}
                  />
                )}

                {(item.preview || item.url) && (
                  <video
                    src={item.preview || item.url}
                    controls
                    className={styles.nodePreview}
                  />
                )}
              </div>
            )}
          </div>
        ))}

        {data.items.length === 0 && (
          <div className={styles.emptyState}>
            Click + buttons above to add videos
          </div>
        )}
      </div>

      {/* Output handles */}
      {hasMultipleItems && (
        <Handle
          type="source"
          position={Position.Right}
          id="composite"
          style={{ top: '20px' }}
        />
      )}
      {data.items.map((item, index) => (
        <Handle
          key={item.id}
          type="source"
          position={Position.Right}
          id={item.id}
          style={{
            top: hasMultipleItems ? `${40 + index * 20}px` : '50%',
          }}
        />
      ))}
    </div>
  );
});

VideoNode.displayName = 'VideoNode';
