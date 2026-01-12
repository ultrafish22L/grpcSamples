/**
 * Edge Context Menu Component
 * Context menu displayed when right-clicking on edges in the graph editor
 * Provides option to delete the connection
 * 
 * ReactFlow v12 Best Practices:
 * - Uses createPortal for proper rendering
 * - Uses CSS classes from octane-theme.css
 * - Screen boundary detection
 */

import { useEffect, useRef } from 'react';
import { createPortal } from 'react-dom';

interface EdgeContextMenuProps {
  x: number;
  y: number;
  onDeleteEdge: () => void;
  onClose: () => void;
}

export function EdgeContextMenu({
  x,
  y,
  onDeleteEdge,
  onClose,
}: EdgeContextMenuProps) {
  const menuRef = useRef<HTMLDivElement>(null);

  // Close menu when clicking outside
  useEffect(() => {
    const handleClickOutside = (event: MouseEvent) => {
      if (menuRef.current && !menuRef.current.contains(event.target as Node)) {
        onClose();
      }
    };

    document.addEventListener('click', handleClickOutside);
    return () => {
      document.removeEventListener('click', handleClickOutside);
    };
  }, [onClose]);

  // Close menu on Escape key
  useEffect(() => {
    const handleEscape = (event: KeyboardEvent) => {
      if (event.key === 'Escape') {
        onClose();
      }
    };

    document.addEventListener('keydown', handleEscape);
    return () => {
      document.removeEventListener('keydown', handleEscape);
    };
  }, [onClose]);

  // Adjust menu position to stay on screen
  useEffect(() => {
    if (!menuRef.current) return;

    const rect = menuRef.current.getBoundingClientRect();
    let adjustedX = x;
    let adjustedY = y;

    // Keep menu on screen
    if (rect.right > window.innerWidth) {
      adjustedX = x - rect.width;
    }
    if (rect.bottom > window.innerHeight) {
      adjustedY = y - rect.height;
    }

    if (adjustedX !== x || adjustedY !== y) {
      menuRef.current.style.left = `${adjustedX}px`;
      menuRef.current.style.top = `${adjustedY}px`;
    }
  }, [x, y]);

  const handleDeleteClick = () => {
    onDeleteEdge();
    onClose();
  };

  // Render to document.body using portal
  return createPortal(
    <div
      ref={menuRef}
      className="node-context-menu"
      style={{
        position: 'fixed',
        left: x,
        top: y,
        zIndex: 10000,
      }}
    >
      {/* Delete Connection */}
      <div
        className="context-menu-item"
        onClick={handleDeleteClick}
      >
        <span>✂️</span>
        <span>Delete Connection</span>
      </div>
    </div>,
    document.body
  );
}
