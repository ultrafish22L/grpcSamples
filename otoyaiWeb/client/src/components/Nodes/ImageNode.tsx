import { memo, useState } from 'react';
import { Handle, Position, NodeProps, useUpdateNodeInternals } from '@xyflow/react';
import { ImageNodeData, MediaItem } from '../../types';
import styles from './nodes.module.css';

function ImageNodeComponent({ id, data, selected }: NodeProps) {
  const updateNodeInternals = useUpdateNodeInternals();
  const [, forceUpdate] = useState({});
  const typedData = data as unknown as ImageNodeData;

  // Initialize items if empty
  if (!typedData.items || typedData.items.length === 0) {
    typedData.items = [];
  }

  const addItem = (type: 'url' | 'file') => {
    const newItem: MediaItem = {
      id: `${Date.now()}-${Math.random()}`,
      collapsed: false,
    };

    if (type === 'url') {
      // Show prompt dialog for URL
      const url = prompt('Enter image URL:');
      if (url && url.trim()) {
        newItem.url = url.trim();
        newItem.name = url.split('/').pop() || url;
        typedData.items.push(newItem);
        updateNodeInternals(id);
        forceUpdate({});
      }
      return;
    } else {
      // Trigger file picker
      const input = document.createElement('input');
      input.type = 'file';
      input.accept = 'image/*';
      input.onchange = (e: Event) => {
        const file = (e.target as HTMLInputElement).files?.[0];
        if (file) {
          const reader = new FileReader();
          reader.onload = (event) => {
            newItem.preview = event.target?.result as string;
            newItem.file = file;
            newItem.name = file.name;
            typedData.items.push(newItem);
            updateNodeInternals(id);
            forceUpdate({});
          };
          reader.readAsDataURL(file);
        }
      };
      input.click();
      return; // Don't update yet, wait for file load
    }
  };

  const deleteItem = (itemId: string) => {
    typedData.items = typedData.items.filter((item) => item.id !== itemId);
    updateNodeInternals(id);
    forceUpdate({});
  };

  const toggleCollapse = (itemId: string) => {
    const item = typedData.items.find((i) => i.id === itemId);
    if (item) {
      item.collapsed = !item.collapsed;
      forceUpdate({});
    }
  };

  const hasMultipleItems = typedData.items.length > 1;

  return (
    <div className={`${styles.baseNode} ${selected ? styles.selected : ''}`}>
      <div className={styles.nodeHeader}>
        <h3 className={styles.nodeTitle}>Image</h3>
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
        {typedData.items.map((item) => (
          <div key={item.id} className={styles.mediaItem}>
            <div className={styles.mediaItemHeader}>
              <button
                className={styles.collapseButton}
                onClick={() => toggleCollapse(item.id)}
              >
                {item.collapsed ? '▶' : '▼'}
              </button>
              <span className={styles.mediaItemName}>
                {item.name || item.url || 'New Image'}
              </span>
              <button
                className={styles.deleteButton}
                onClick={() => deleteItem(item.id)}
                title="Delete"
              >
                ×
              </button>
            </div>

            {!item.collapsed && (item.preview || item.url) && (
              <div className={styles.mediaItemContent}>
                <img
                  src={item.preview || item.url}
                  alt="Preview"
                  className={styles.nodePreview}
                />
              </div>
            )}
          </div>
        ))}

        {typedData.items.length === 0 && (
          <div className={styles.emptyState}>
            Click + buttons above to add images
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
      {typedData.items.map((item: MediaItem, index: number) => (
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
}

export const ImageNode = memo(ImageNodeComponent);
ImageNode.displayName = 'ImageNode';
