import { memo, useState, useCallback, useEffect, useMemo } from 'react';
import { Handle, Position, NodeProps, useUpdateNodeInternals, useReactFlow } from '@xyflow/react';
import { VideoNodeData, MediaItem } from '../../types';
import styles from './nodes.module.css';

function VideoNodeComponent({ id, data, selected }: NodeProps) {
  const updateNodeInternals = useUpdateNodeInternals();
  const { updateNodeData } = useReactFlow();
  const [, forceUpdate] = useState({});
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);
  const typedData = data as unknown as VideoNodeData;
  const previewCollapsed = typedData.previewCollapsed ?? true;

  // Initialize items if empty
  if (!typedData.items || typedData.items.length === 0) {
    typedData.items = [];
  }

  const togglePreview = useCallback(() => {
    updateNodeData(id, { previewCollapsed: !previewCollapsed });
  }, [id, previewCollapsed, updateNodeData]);

  // Generate title from first filename (minimum 22 chars or full name)
  const nodeTitle = useMemo(() => {
    if (typedData.items.length > 0) {
      const item = typedData.items[0];
      const name = item.name || item.url?.split('/').pop() || 'Video';
      return name.length > 22 ? name.substring(0, 22) + '...' : name;
    }
    return 'Video';
  }, [typedData.items]);

  const addItem = useCallback((e: React.MouseEvent, type: 'url' | 'file') => {
    e.stopPropagation();
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
  }, [id, typedData.items, updateNodeInternals]);

  const deleteItem = useCallback((e: React.MouseEvent, itemId: string) => {
    e.stopPropagation();
    typedData.items = typedData.items.filter((item: MediaItem) => item.id !== itemId);
    updateNodeInternals(id);
    forceUpdate({});
  }, [id, typedData.items, updateNodeInternals]);

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
        className={`${styles.baseNode} ${styles.aiEndpointNode} ${selected ? styles.selected : ''}`}
        onContextMenu={handleContextMenu}
        onClick={togglePreview}
      >
        <div className={styles.nodeHeader}>
          <h3 className={styles.nodeTitle}>{nodeTitle}</h3>
          <div className={styles.headerButtons} style={{ gap: '4px', marginLeft: '8px' }}>
            <button
              className={styles.iconButton}
              onClick={(e) => addItem(e, 'url')}
              title="Add URL"
            >
              +🔗
            </button>
            <button
              className={styles.iconButton}
              onClick={(e) => addItem(e, 'file')}
              title="Add File"
            >
              +📁
            </button>
          </div>
        </div>

        {/* Collapsible Preview Area - Scrollable Vertical List */}
        {!previewCollapsed && (
          <div className={styles.videoNodePreview} onClick={(e) => e.stopPropagation()}>
            {typedData.items.length === 0 ? (
              <div className={styles.emptyState}>
                Click + buttons above to add videos
              </div>
            ) : (
              typedData.items.map((item: MediaItem) => (
                <div key={item.id} className={styles.videoItemContainer}>
                  {(item.preview || item.url) && (
                    <video
                      src={item.preview || item.url}
                      controls
                      className={styles.videoPreview}
                    />
                  )}
                  <div className={styles.videoFooter}>
                    <span className={styles.videoFilename}>
                      {item.name || item.url?.split('/').pop() || 'video'}
                    </span>
                    <button
                      className={styles.deleteButton}
                      onClick={(e) => deleteItem(e, item.id)}
                      title="Delete"
                    >
                      ×
                    </button>
                  </div>
                </div>
              ))
            )}
          </div>
        )}

        {/* Output handles - Bottom */}
        {typedData.items.map((item: MediaItem, index: number) => {
          const nodeWidth = 220; // Match the min-width in CSS
          const numOutputs = typedData.items.length;
          const spacing = nodeWidth / (numOutputs + 1);
          const handleLeft = spacing * (index + 1);
          const hasVideo = item.url || item.file;
          
          return (
            <Handle
              key={item.id}
              type="source"
              position={Position.Bottom}
              id={item.id}
              className={hasVideo ? styles.handleFilled : styles.handleOpen}
              style={{
                left: handleLeft,
                bottom: 0,
                transform: 'translate(-50%, 50%)',
              }}
              title={item.name || 'Video output'}
              onClick={(e) => e.stopPropagation()}
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
