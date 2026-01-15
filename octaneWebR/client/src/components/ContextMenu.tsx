/**
 * Context Menu Component
 * Reusable right-click context menu for octaneWebR
 */

import { useEffect, useRef } from 'react';

export interface ContextMenuItem {
  label: string;
  action: string;
  disabled?: boolean;
  separator?: boolean;
  shortcut?: string;
}

interface ContextMenuProps {
  items: ContextMenuItem[];
  x: number;
  y: number;
  onClose: () => void;
  onItemClick: (action: string) => void;
}

export function ContextMenu({ items, x, y, onClose, onItemClick }: ContextMenuProps) {
  const menuRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const handleClickOutside = (e: MouseEvent) => {
      if (menuRef.current && !menuRef.current.contains(e.target as Node)) {
        onClose();
      }
    };

    const handleEscape = (e: KeyboardEvent) => {
      if (e.key === 'Escape') {
        onClose();
      }
    };

    // Add listeners after a short delay to prevent immediate closing
    setTimeout(() => {
      document.addEventListener('mousedown', handleClickOutside);
      document.addEventListener('keydown', handleEscape);
    }, 0);

    return () => {
      document.removeEventListener('mousedown', handleClickOutside);
      document.removeEventListener('keydown', handleEscape);
    };
  }, [onClose]);

  const handleItemClick = (item: ContextMenuItem) => {
    if (!item.disabled && !item.separator) {
      onItemClick(item.action);
      onClose();
    }
  };

  return (
    <div
      ref={menuRef}
      className="context-menu"
      style={{
        left: `${x}px`,
        top: `${y}px`,
      }}
    >
      {items.map((item, index) => {
        if (item.separator) {
          return <div key={`separator-${index}`} className="context-menu-separator" />;
        }

        return (
          <div
            key={item.action}
            className={`context-menu-item ${item.disabled ? 'disabled' : ''}`}
            onClick={() => handleItemClick(item)}
          >
            <span className="context-menu-label">{item.label}</span>
            {item.shortcut && (
              <span className="context-menu-shortcut">{item.shortcut}</span>
            )}
          </div>
        );
      })}
    </div>
  );
}
