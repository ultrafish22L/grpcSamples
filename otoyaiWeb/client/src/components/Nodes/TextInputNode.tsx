import { memo, useState, useCallback, useEffect } from 'react';
import { Handle, Position, NodeProps } from '@xyflow/react';
import { TextInputNodeData } from '../../types';
import styles from './nodes.module.css';

function TextInputNodeComponent({ data, selected }: NodeProps) {
  const typedData = data as unknown as TextInputNodeData;
  const [contextMenu, setContextMenu] = useState<{ x: number; y: number } | null>(null);

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
          <h3 className={styles.nodeTitle}>{typedData.label || 'Text Input'}</h3>
        </div>

        <textarea
          className={`${styles.nodeInput} ${styles.nodeTextarea}`}
          placeholder="Enter text..."
          value={typedData.value}
          onChange={(e) => (typedData.value = e.target.value)}
        />

        <Handle 
          type="source" 
          position={Position.Bottom} 
          id="output"
          className={styles.handleOpen}
          style={{ left: '50%', bottom: 0, transform: 'translate(-50%, 50%)' }}
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
