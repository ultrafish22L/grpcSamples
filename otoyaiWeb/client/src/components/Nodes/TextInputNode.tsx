import { memo, useState, useCallback, useEffect, useMemo } from 'react';
import { Handle, Position, NodeProps, useReactFlow } from '@xyflow/react';
import { TextInputNodeData } from '../../types';
import { getHandleColorClass } from '../../utils/connectionValidator';
import styles from './nodes.module.css';

function TextInputNodeComponent({ data, selected, id }: NodeProps) {
  const typedData = data as unknown as TextInputNodeData;
  const { updateNodeData } = useReactFlow();
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);
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
          onClick={(e) => e.stopPropagation()}
        />
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

export const TextInputNode = memo(TextInputNodeComponent);
TextInputNode.displayName = 'TextInputNode';
