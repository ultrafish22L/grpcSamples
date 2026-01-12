/**
 * Node Context Menu Component
 * Context menu displayed when right-clicking on nodes in the graph editor
 * Provides options: Delete Selected, Save as Macro, Render Node, Group Items, Show in Outliner
 */

import { useEffect, useRef } from 'react';

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

    document.addEventListener('mousedown', handleClickOutside);
    return () => {
      document.removeEventListener('mousedown', handleClickOutside);
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

  const handleMenuItemClick = (action: () => void) => {
    action();
    onClose();
  };

  return (
    <div
      ref={menuRef}
      style={{
        position: 'fixed',
        left: `${x}px`,
        top: `${y}px`,
        backgroundColor: '#2a2a2a',
        border: '1px solid #444',
        borderRadius: '4px',
        padding: '4px 0',
        minWidth: '200px',
        zIndex: 10000,
        boxShadow: '0 4px 12px rgba(0, 0, 0, 0.5)',
        fontFamily: 'Arial, sans-serif',
        fontSize: '13px',
        color: '#e0e0e0',
      }}
    >
      {/* Delete Selected Nodes */}
      <div
        onClick={() => handleMenuItemClick(onDeleteSelected)}
        style={{
          padding: '8px 16px',
          cursor: 'pointer',
          display: 'flex',
          alignItems: 'center',
          gap: '8px',
        }}
        onMouseEnter={(e) => {
          e.currentTarget.style.backgroundColor = '#3a3a3a';
        }}
        onMouseLeave={(e) => {
          e.currentTarget.style.backgroundColor = 'transparent';
        }}
      >
        <span>🗑️</span>
        <span>Delete Selected {selectedNodeCount > 1 ? `(${selectedNodeCount})` : ''}</span>
      </div>

      {/* Separator */}
      <div
        style={{
          height: '1px',
          backgroundColor: '#444',
          margin: '4px 0',
        }}
      />

      {/* Save as Macro */}
      <div
        onClick={() => handleMenuItemClick(onSaveAsMacro)}
        style={{
          padding: '8px 16px',
          cursor: 'pointer',
          display: 'flex',
          alignItems: 'center',
          gap: '8px',
        }}
        onMouseEnter={(e) => {
          e.currentTarget.style.backgroundColor = '#3a3a3a';
        }}
        onMouseLeave={(e) => {
          e.currentTarget.style.backgroundColor = 'transparent';
        }}
      >
        <span>💾</span>
        <span>Save as Macro</span>
      </div>

      {/* Render Node */}
      <div
        onClick={() => handleMenuItemClick(onRenderNode)}
        style={{
          padding: '8px 16px',
          cursor: 'pointer',
          display: 'flex',
          alignItems: 'center',
          gap: '8px',
        }}
        onMouseEnter={(e) => {
          e.currentTarget.style.backgroundColor = '#3a3a3a';
        }}
        onMouseLeave={(e) => {
          e.currentTarget.style.backgroundColor = 'transparent';
        }}
      >
        <span>🎬</span>
        <span>Render Node</span>
      </div>

      {/* Separator */}
      <div
        style={{
          height: '1px',
          backgroundColor: '#444',
          margin: '4px 0',
        }}
      />

      {/* Group Items */}
      <div
        onClick={() => handleMenuItemClick(onGroupItems)}
        style={{
          padding: '8px 16px',
          cursor: selectedNodeCount > 1 ? 'pointer' : 'not-allowed',
          display: 'flex',
          alignItems: 'center',
          gap: '8px',
          opacity: selectedNodeCount > 1 ? 1 : 0.5,
        }}
        onMouseEnter={(e) => {
          if (selectedNodeCount > 1) {
            e.currentTarget.style.backgroundColor = '#3a3a3a';
          }
        }}
        onMouseLeave={(e) => {
          e.currentTarget.style.backgroundColor = 'transparent';
        }}
      >
        <span>📦</span>
        <span>Group Items</span>
      </div>

      {/* Separator */}
      <div
        style={{
          height: '1px',
          backgroundColor: '#444',
          margin: '4px 0',
        }}
      />

      {/* Show in Outliner */}
      <div
        onClick={() => handleMenuItemClick(onShowInOutliner)}
        style={{
          padding: '8px 16px',
          cursor: 'pointer',
          display: 'flex',
          alignItems: 'center',
          gap: '8px',
        }}
        onMouseEnter={(e) => {
          e.currentTarget.style.backgroundColor = '#3a3a3a';
        }}
        onMouseLeave={(e) => {
          e.currentTarget.style.backgroundColor = 'transparent';
        }}
      >
        <span>🔍</span>
        <span>Show in Outliner</span>
      </div>
    </div>
  );
}
