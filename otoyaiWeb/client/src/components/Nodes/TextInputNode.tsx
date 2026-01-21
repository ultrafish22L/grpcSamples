import { memo, useState, useCallback, useEffect, useMemo, useRef } from 'react';
import { createPortal } from 'react-dom';
import { Handle, Position, NodeProps, useReactFlow } from '@xyflow/react';
import { TextInputNodeData } from '../../types';
import { getHandleColorClass } from '../../utils/connectionValidator';
import { useStore } from '../../store/useStore';
import { logger } from '../../services/logger';
import styles from './nodes.module.css';

function TextInputNodeComponent({ data, selected, id }: NodeProps) {
  const typedData = data as unknown as TextInputNodeData;
  const { updateNodeData } = useReactFlow();
  const { onNodesChange, addNode, nodes } = useStore();
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);
  const contextMenuRef = useRef<HTMLDivElement>(null);
  const previewCollapsed = typedData.previewCollapsed ?? true;

  const handleTextChange = useCallback((e: React.ChangeEvent<HTMLTextAreaElement>) => {
    updateNodeData(id, { value: e.target.value });
  }, [id, updateNodeData]);

  const togglePreview = useCallback(() => {
    updateNodeData(id, { previewCollapsed: !previewCollapsed });
  }, [id, previewCollapsed, updateNodeData]);

  // Generate title from first 22 characters of text
  const nodeTitle = useMemo(() => {
    if (!typedData.value || typedData.value.trim() === '') {
      return 'Text Node';
    }
    const text = typedData.value.trim();
    return text.length > 22 ? text.substring(0, 22) + '...' : text;
  }, [typedData.value]);

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

  const handleDelete = useCallback(() => {
    logger.info('Delete text input node requested', { id });
    onNodesChange([{ type: 'remove', id }]);
    closeContextMenu();
  }, [id, onNodesChange, closeContextMenu]);

  const handleDuplicate = useCallback(() => {
    logger.info('Duplicate text input node requested', { id });
    const newNode = {
      id: `${id}-copy-${Date.now()}`,
      type: 'textInput',
      position: { x: selected ? 50 : 0, y: selected ? 50 : 0 },
      data: { ...typedData },
    };
    addNode(newNode as any);
    closeContextMenu();
  }, [id, typedData, selected, addNode, closeContextMenu]);
  
  return (
    <>
      <div 
        className={`${styles.baseNode} ${styles.aiEndpointNode} ${selected ? styles.selected : ''}`}
        onContextMenu={handleContextMenu}
      >
        <div className={styles.nodeHeader}>
          <h3 className={styles.nodeTitle}>{nodeTitle}</h3>
        </div>

        {/* Collapsible Preview Area */}
        {!previewCollapsed && (
          <div className={styles.textNodePreview}>
            <textarea
              className={`${styles.nodeInput} ${styles.nodeTextarea}`}
              placeholder="Enter text..."
              value={typedData.value}
              onChange={handleTextChange}
              onClick={(e) => e.stopPropagation()}
              style={{ 
                margin: 0, 
                padding: '8px', 
                border: 'none', 
                borderRadius: 0
              }}
            />
          </div>
        )}

        <Handle 
          type="source" 
          position={Position.Bottom} 
          id="output"
          className={`${typedData.value ? styles.handleFilled : styles.handleOpen} ${styles[getHandleColorClass('string')]}`}
          style={{ left: '50%', bottom: 0, transform: 'translate(-50%, 50%)' }}
          title="Text output"
          onClick={(e) => { e.stopPropagation(); togglePreview(); }}
        />
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

export const TextInputNode = memo(TextInputNodeComponent);
TextInputNode.displayName = 'TextInputNode';
