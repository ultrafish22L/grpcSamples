import { memo, useState, useCallback, useEffect } from 'react';
import { Handle, Position, NodeProps, useUpdateNodeInternals } from '@xyflow/react';
import { VideoNodeData, MediaItem } from '../../types';
import styles from './nodes.module.css';

function VideoNodeComponent({ id, data, selected }: NodeProps) {
  const updateNodeInternals = useUpdateNodeInternals();
  const [, forceUpdate] = useState({});
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);
  const typedData = data as unknown as VideoNodeData;

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
      const url = prompt('Enter video URL:');
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
      input.accept = 'video/*';
      input.onchange = (e: Event) => {
        const file = (e.target as HTMLInputElement).files?.[0];
        if (file) {
          const url = URL.createObjectURL(file);
          newItem.preview = url;
          newItem.file = file;
          newItem.name = file.name;
          typedData.items.push(newItem);
          updateNodeInternals(id);
          forceUpdate({});
        }
      };
      input.click();
      return; // Don't update yet, wait for file load
    }
  };

  const deleteItem = (itemId: string) => {
    typedData.items = typedData.items.filter((item: MediaItem) => item.id !== itemId);
    updateNodeInternals(id);
    forceUpdate({});
  };

  const toggleCollapse = (itemId: string) => {
    const item = typedData.items.find((i: MediaItem) => i.id === itemId);
    if (item) {
      item.collapsed = !item.collapsed;
      forceUpdate({});
    }
  };

  const hasMultipleItems = typedData.items.length > 1;

  const handleContextMenu = useCallback((e: React.MouseEvent) => {
    e.preventDefault();
    setContextMenu({ x: e.clientX, y: e.clientY });
  }, []);

  const closeContextMenu = useCallback(() => {
    setContextMenu(null);
  }, []);

  useEffect(() => {
    if (contextMenu) {
      const handleClick = () => closeContextMenu();
      document.addEventListener('click', handleClick);
      return () => document.removeEventListener('click', handleClick);
    }
  }, [contextMenu, closeContextMenu]);

  return (
    <>
      <div 
        className={`${styles.baseNode} ${selected ? styles.selected : ''}`}
        onContextMenu={handleContextMenu}
      >
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
          {typedData.items.map((item: MediaItem) => (
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

              {!item.collapsed && (item.preview || item.url) && (
                <div className={styles.mediaItemContent}>
                  <video
                    src={item.preview || item.url}
                    controls
                    className={styles.nodePreview}
                  />
                </div>
              )}
            </div>
          ))}

          {typedData.items.length === 0 && (
            <div className={styles.emptyState}>
              Click + buttons above to add videos
            </div>
          )}
        </div>

        {/* Output handles - Bottom */}
        {typedData.items.map((item: MediaItem, index: number) => {
          const nodeWidth = 220; // Match the min-width in CSS
          const numOutputs = typedData.items.length;
          const spacing = nodeWidth / (numOutputs + 1);
          const handleLeft = spacing * (index + 1);
          
          return (
            <Handle
              key={item.id}
              type="source"
              position={Position.Bottom}
              id={item.id}
              className={styles.handleOpen}
              style={{
                left: handleLeft,
                bottom: -6,
              }}
              title={item.name || 'Video output'}
            />
          );
        })}
      </div>

      {contextMenu && (
        <div
          className={styles.nodeContextMenu}
          style={{ position: 'fixed', left: contextMenu.x, top: contextMenu.y }}
          onClick={(e) => e.stopPropagation()}
        >
          <div className={styles.contextMenuItem}>
            📋 Duplicate
          </div>
          <div className={styles.contextMenuItem}>
            🗑️ Delete
          </div>
        </div>
      )}
    </>
  );
}

export const VideoNode = memo(VideoNodeComponent);
VideoNode.displayName = 'VideoNode';
