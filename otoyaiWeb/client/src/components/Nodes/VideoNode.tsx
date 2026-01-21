import { memo, useState, useCallback, useEffect, useLayoutEffect, useMemo, useRef } from 'react';
import { createPortal } from 'react-dom';
import { Handle, Position, NodeProps, useUpdateNodeInternals, useReactFlow } from '@xyflow/react';
import { VideoNodeData, MediaItem } from '../../types';
import { getHandleColorClass } from '../../utils/connectionValidator';
import { useStore } from '../../store/useStore';
import { logger } from '../../services/logger';
import styles from './nodes.module.css';

function VideoNodeComponent({ id, data, selected }: NodeProps) {
  const updateNodeInternals = useUpdateNodeInternals();
  const { updateNodeData } = useReactFlow();
  const { onNodesChange, addNode, edges, setEdges, nodes } = useStore();
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);
  const contextMenuRef = useRef<HTMLDivElement>(null);
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
        const newItems = [...typedData.items, newItem];
        updateNodeData(id, { items: newItems });
        updateNodeInternals(id);
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
          const newItems = [...typedData.items, newItem];
          updateNodeData(id, { items: newItems });
          updateNodeInternals(id);
        }
      };
      input.click();
      return; // Don't update yet, wait for file load
    }
  }, [id, typedData.items, updateNodeInternals, updateNodeData]);

  const deleteItem = useCallback((e: React.MouseEvent, itemId: string) => {
    e.stopPropagation();
    const newItems = typedData.items.filter((item: MediaItem) => item.id !== itemId);
    updateNodeData(id, { items: newItems });
    
    // Remove edges connected to this handle
    const handleId = `output-${itemId}`;
    const updatedEdges = edges.filter((edge) => 
      !(edge.source === id && edge.sourceHandle === handleId)
    );
    if (updatedEdges.length !== edges.length) {
      logger.info('Removed edges for deleted item', { nodeId: id, itemId, handleId });
      setEdges(updatedEdges);
    }
    
    updateNodeInternals(id);
  }, [id, typedData.items, updateNodeInternals, updateNodeData, edges, setEdges]);

  const handleContextMenu = useCallback((e: React.MouseEvent) => {
    e.preventDefault();
    
    // Select this node before showing context menu
    if (!selected) {
      const selectionChanges = nodes.map(node => ({
        id: node.id,
        type: 'select' as const,
        selected: node.id === id
      }));
      onNodesChange(selectionChanges);
    }
    
    setContextMenu({ x: e.clientX, y: e.clientY });
  }, [selected, nodes, id, onNodesChange]);

  const closeContextMenu = useCallback(() => {
    setContextMenu(null);
  }, []);

  const handleDelete = useCallback(() => {
    logger.info('Delete video node requested', { id });
    onNodesChange([{ type: 'remove', id }]);
    closeContextMenu();
  }, [id, onNodesChange, closeContextMenu]);

  const handleDuplicate = useCallback(() => {
    logger.info('Duplicate video node requested', { id });
    const newNode = {
      id: `${id}-copy-${Date.now()}`,
      type: 'video',
      position: { x: selected ? 50 : 0, y: selected ? 50 : 0 },
      data: { ...typedData, items: [...typedData.items] },
    };
    addNode(newNode as any);
    closeContextMenu();
  }, [id, typedData, selected, addNode, closeContextMenu]);

  // Calculate adjusted position to keep menu in viewport
  const contextMenuPosition = useMemo(() => {
    if (!contextMenu) return { left: 0, top: 0 };
    
    const menuWidth = 150; // Approximate width from CSS
    const menuHeight = 80; // Approximate height for 2 items
    const padding = 8; // Padding from viewport edge
    
    let { x, y } = contextMenu;
    
    // Adjust horizontal position
    if (x + menuWidth > window.innerWidth - padding) {
      x = window.innerWidth - menuWidth - padding;
    }
    if (x < padding) {
      x = padding;
    }
    
    // Adjust vertical position
    if (y + menuHeight > window.innerHeight - padding) {
      y = window.innerHeight - menuHeight - padding;
    }
    if (y < padding) {
      y = padding;
    }
    
    return { left: x, top: y };
  }, [contextMenu]);

  useEffect(() => {
    if (contextMenu) {
      const handleClick = () => closeContextMenu();
      document.addEventListener('click', handleClick);
      return () => document.removeEventListener('click', handleClick);
    }
  }, [contextMenu, closeContextMenu]);

  // Update node internals when items change to recalculate handle positions
  // Use useLayoutEffect to ensure this runs after DOM updates but before paint
  useLayoutEffect(() => {
    updateNodeInternals(id);
  }, [typedData.items.length, id, updateNodeInternals]);

  return (
    <>
      <div 
        className={`${styles.baseNode} ${styles.aiEndpointNode} ${selected ? styles.selected : ''}`}
        onContextMenu={handleContextMenu}
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
        {typedData.items.length === 0 ? (
          // Always show one empty output handle when no items
          <Handle
            type="source"
            position={Position.Bottom}
            id="output"
            className={`${styles.handleOpen} ${styles[getHandleColorClass('video')]}`}
            style={{
              left: '50%',
              bottom: 0,
              transform: 'translate(-50%, 50%)',
            }}
            title="Video output"
            onClick={(e) => { e.stopPropagation(); togglePreview(); }}
          />
        ) : (
          typedData.items.map((item: MediaItem, index: number) => {
            const numOutputs = typedData.items.length;
            // Calculate position as percentage for proper scaling
            const leftPercent = (100 / (numOutputs + 1)) * (index + 1);
            const hasVideo = item.url || item.file;
            
            return (
              <Handle
                key={item.id}
                type="source"
                position={Position.Bottom}
                id={`output-${item.id}`}
                className={`${hasVideo ? styles.handleFilled : styles.handleOpen} ${styles[getHandleColorClass('video')]}`}
                style={{
                  left: `${leftPercent}%`,
                  bottom: 0,
                  transform: 'translate(-50%, 50%)',
                }}
                title={item.name || 'Video output'}
                onClick={(e) => { e.stopPropagation(); togglePreview(); }}
              />
            );
          })
        )}
      </div>

      {contextMenu && createPortal(
        <div
          ref={contextMenuRef}
          className={styles.nodeContextMenu}
          style={{ 
            position: 'fixed', 
            left: `${contextMenuPosition.left}px`, 
            top: `${contextMenuPosition.top}px` 
          }}
          onClick={(e) => e.stopPropagation()}
        >
          <div className={styles.contextMenuItem} onClick={handleDuplicate}>
            📋 Duplicate
          </div>
          <div className={styles.contextMenuItem} onClick={handleDelete}>
            🗑️ Delete
          </div>
        </div>,
        document.body
      )}
    </>
  );
}

export const VideoNode = memo(VideoNodeComponent);
VideoNode.displayName = 'VideoNode';
