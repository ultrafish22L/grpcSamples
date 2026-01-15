/**
 * Node Context Menu Component
 * Context menu displayed when right-clicking on nodes in the graph editor
 * Provides full node operations matching Octane SE
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
  onRenderNode: () => void;
  onSaveAsMacro: () => void;
  onCut: () => void;
  onCopy: () => void;
  onPaste: () => void;
  onDeleteSelected: () => void;
  onCollapseItems: () => void;
  onExpandItems: () => void;
  onGroupItems: () => void;
  onShowInOutliner: () => void;
  onShowInLuaBrowser: () => void;
  onClose: () => void;
}

export function NodeContextMenu({
  x,
  y,
  selectedNodeCount,
  onRenderNode,
  onSaveAsMacro,
  onCut,
  onCopy,
  onPaste,
  onDeleteSelected,
  onCollapseItems,
  onExpandItems,
  onGroupItems,
  onShowInOutliner,
  onShowInLuaBrowser,
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
      {/* Render */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onRenderNode)}
      >
        Render
      </div>

      {/* Save... */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onSaveAsMacro)}
      >
        Save...
      </div>

      {/* Separator */}
      <div className="context-menu-separator" />

      {/* Cut */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onCut)}
      >
        Cut
      </div>

      {/* Copy */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onCopy)}
      >
        Copy
      </div>

      {/* Paste */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onPaste)}
      >
        Paste
      </div>

      {/* Separator */}
      <div className="context-menu-separator" />

      {/* Delete */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onDeleteSelected)}
      >
        Delete
      </div>

      {/* Separator */}
      <div className="context-menu-separator" />

      {/* Collapse items */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onCollapseItems)}
      >
        Collapse items
      </div>

      {/* Expand items */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onExpandItems)}
      >
        Expand items
      </div>

      {/* Group Items */}
      <div
        className={`context-menu-item ${selectedNodeCount < 2 ? 'disabled' : ''}`}
        onClick={() => handleMenuItemClick(onGroupItems, selectedNodeCount < 2)}
      >
        Group Items
      </div>

      {/* Separator */}
      <div className="context-menu-separator" />

      {/* Show in Outliner */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onShowInOutliner)}
      >
        Show in Outliner
      </div>

      {/* Show in Lua API browser */}
      <div
        className="context-menu-item"
        onClick={() => handleMenuItemClick(onShowInLuaBrowser)}
      >
        Show in Lua API browser
      </div>
    </div>,
    document.body
  );
}
