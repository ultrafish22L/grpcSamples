import { memo, useState, useCallback, useEffect, useMemo, useRef } from 'react';
import { createPortal } from 'react-dom';
import { Handle, Position, NodeProps, useUpdateNodeInternals, useReactFlow } from '@xyflow/react';
import { ImageNodeData, MediaItem } from '../../types';
import { getHandleColorClass } from '../../utils/connectionValidator';
import { useStore } from '../../store/useStore';
import { logger } from '../../services/logger';
import styles from './nodes.module.css';

function ImageNodeComponent({ id, data, selected }: NodeProps) {
  const updateNodeInternals = useUpdateNodeInternals();
  const { updateNodeData } = useReactFlow();
  const { onNodesChange, addNode } = useStore();
  const [, forceUpdate] = useState({});
  const typedData = data as unknown as ImageNodeData;
  const previewCollapsed = typedData.previewCollapsed ?? true;
  const contextMenuRef = useRef<HTMLDivElement>(null);

  // Initialize items if empty
  if (!typedData.items || typedData.items.length === 0) {
    typedData.items = [];
  }

  const togglePreview = useCallback(() => {
    updateNodeData(id, { previewCollapsed: !previewCollapsed });
  }, [id, previewCollapsed, updateNodeData]);

  // Generate title from first filename (at least 22 chars)
  const nodeTitle = useMemo(() => {
    if (typedData.items.length > 0) {
      const item = typedData.items[0];
      const name = item.name || item.url?.split('/').pop() || 'Image';
      // Show at least 22 characters or the full name if shorter
      if (name.length > 22) {
        return name.substring(0, 22) + '...';
      }
      return name;
    }
    return 'Image';
  }, [typedData.items.length, typedData.items[0]?.name, typedData.items[0]?.url]);

  const addItem = useCallback((e: React.MouseEvent, type: 'url' | 'file') => {
    e.stopPropagation();
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
  }, [id, typedData.items, updateNodeInternals]);

  const deleteItem = useCallback((e: React.MouseEvent, itemId: string) => {
    e.stopPropagation();
    typedData.items = typedData.items.filter((item) => item.id !== itemId);
    updateNodeInternals(id);
    forceUpdate({});
  }, [id, typedData.items, updateNodeInternals]);

  // TODO: Implement collapse functionality for gallery view
  // const toggleCollapse = useCallback((e: React.MouseEvent, itemId: string) => {
  //   e.stopPropagation();
  //   const item = typedData.items.find((i) => i.id === itemId);
  //   if (item) {
  //     item.collapsed = !item.collapsed;
  //     forceUpdate({});
  //   }
  // }, [typedData.items]);

  // const hasMultipleItems = typedData.items.length > 1;
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);

  const handleContextMenu = useCallback((e: React.MouseEvent) => {
    e.preventDefault();
    setContextMenu({ x: e.clientX, y: e.clientY });
  }, []);

  const closeContextMenu = useCallback(() => {
    setContextMenu(null);
  }, []);

  const handleDelete = useCallback(() => {
    logger.info('Delete image node requested', { id });
    onNodesChange([{ type: 'remove', id }]);
    closeContextMenu();
  }, [id, onNodesChange, closeContextMenu]);

  const handleDuplicate = useCallback(() => {
    logger.info('Duplicate image node requested', { id });
    const newNode = {
      id: `${id}-copy-${Date.now()}`,
      type: 'image',
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

        {/* Collapsible Preview Area */}
        {!previewCollapsed && (
          <div className={styles.imageNodePreview} onClick={(e) => e.stopPropagation()}>
            {typedData.items.length === 0 ? (
              <div className={styles.emptyState}>
                Click + buttons above to add images
              </div>
            ) : (
              <div className={styles.imageList}>
                {typedData.items.map((item) => (
                  <div key={item.id} className={styles.imageListItem}>
                    {(item.preview || item.url) && (
                      <img
                        src={item.preview || item.url}
                        alt={item.name || 'Image'}
                        className={styles.imageListImage}
                      />
                    )}
                    <div className={styles.imageListItemFooter}>
                      <span className={styles.imageListItemName}>
                        {item.name || item.url || 'New Image'}
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
                ))}
              </div>
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
            className={`${styles.handleOpen} ${styles[getHandleColorClass('image')]}`}
            style={{
              left: '50%',
              bottom: 0,
              transform: 'translate(-50%, 50%)',
            }}
            title="Image output"
            onClick={(e) => { e.stopPropagation(); togglePreview(); }}
          />
        ) : (
          typedData.items.map((item: MediaItem, index: number) => {
            const numOutputs = typedData.items.length;
            // Calculate position as percentage for proper scaling
            const leftPercent = (100 / (numOutputs + 1)) * (index + 1);
            const hasImage = item.url || item.file;
            
            return (
              <Handle
                key={item.id}
                type="source"
                position={Position.Bottom}
                id={`output-${index}`}
                className={`${hasImage ? styles.handleFilled : styles.handleOpen} ${styles[getHandleColorClass('image')]}`}
                style={{
                  left: `${leftPercent}%`,
                  bottom: 0,
                  transform: 'translate(-50%, 50%)',
                }}
                title={item.name || 'Image output'}
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

export const ImageNode = memo(ImageNodeComponent);
ImageNode.displayName = 'ImageNode';
