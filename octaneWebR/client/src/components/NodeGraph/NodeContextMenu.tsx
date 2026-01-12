/**
 * Node Context Menu Component
 * Context menu displayed when right-clicking on nodes in the graph editor
 * Provides options: Delete Selected, Save as Macro, Render Node, Group Items, Show in Outliner
 * 
 * ReactFlow v12 Best Practices:
 * - Uses createPortal for proper rendering outside parent DOM
 * - Uses CSS classes from octane-theme.css (no inline styles)
 * - Screen boundary detection to keep menu visible
 * - Standardized click event handling
 * - Proper disabled state prevents clicks
 */

import { useEffect, useRef } from 'react';
import { createPortal } from 'react-dom';

interface NodeContextMenuProps {
  x: number;
  y: number;
  selectedNodeCount: number;
  onDeleteSelected: () => void;
  onSaveAsMacro: () => void;
  onRenderNode: () => void;
  onGroupItems: () => void;
  onShowInOutliner: () => void;
  onClose: () => void;
}

export function NodeContextMenu({
  x,
  y,
  selectedNodeCount,
  onDeleteSelected,
  onSaveAsMacro,
  onRenderNode,
  onGroupItems,
  onShowInOutliner,
  onClose,
}: NodeContextMenuProps) {
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

  const handleMenuItemClick = (action: () => void, disabled = false) => {
    if (disabled) return;
    action();
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
      {/* Delete Selected Nodes */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onDeleteSelected)}
      >
        <span>🗑️</span>
        <span>Delete Selected {selectedNodeCount > 1 ? `(${selectedNodeCount})` : ''}</span>
      </div>

      {/* Separator */}
      <div className="context-menu-separator" />

      {/* Save as Macro */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onSaveAsMacro)}
      >
        <span>💾</span>
        <span>Save as Macro</span>
      </div>

      {/* Render Node */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onRenderNode)}
      >
        <span>🎬</span>
        <span>Render Node</span>
      </div>

      {/* Separator */}
      <div className="context-menu-separator" />

      {/* Group Items - disabled if less than 2 nodes selected */}
      <div
        className={`context-menu-item ${selectedNodeCount < 2 ? 'disabled' : ''}`}
        onClick={() => handleMenuItemClick(onGroupItems, selectedNodeCount < 2)}
      >
        <span>📦</span>
        <span>Group Items</span>
      </div>

      {/* Separator */}
      <div className="context-menu-separator" />

      {/* Show in Outliner */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onShowInOutliner)}
      >
        <span>🔍</span>
        <span>Show in Outliner</span>
      </div>
    </div>,
    document.body
  );
}
