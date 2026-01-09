/**
 * Node Type Context Menu Component
 * Hierarchical menu for creating new nodes
 * Matches octaneWeb's NodeGraphEditor.js showContextMenu() functionality
 */

import { useEffect, useRef, useState, useCallback } from 'react';
import { getNodeCategories, getNodeTypesForCategory } from '../../constants/NodeTypes';

interface NodeTypeContextMenuProps {
  x: number;
  y: number;
  onSelectNodeType: (nodeType: string) => void;
  onClose: () => void;
}

export function NodeTypeContextMenu({
  x,
  y,
  onSelectNodeType,
  onClose,
}: NodeTypeContextMenuProps) {
  const menuRef = useRef<HTMLDivElement>(null);
  const [hoveredCategory, setHoveredCategory] = useState<string | null>(null);
  const [submenuPosition, setSubmenuPosition] = useState<{ top: number; left: number }>({ top: 0, left: 0 });
  const categories = getNodeCategories();

  // Close menu on click outside
  useEffect(() => {
    const handleClickOutside = (e: MouseEvent) => {
      if (menuRef.current && !menuRef.current.contains(e.target as Node)) {
        onClose();
      }
    };

    document.addEventListener('mousedown', handleClickOutside);
    return () => document.removeEventListener('mousedown', handleClickOutside);
  }, [onClose]);

  // Close menu on Escape key
  useEffect(() => {
    const handleEscape = (e: KeyboardEvent) => {
      if (e.key === 'Escape') {
        onClose();
      }
    };

    document.addEventListener('keydown', handleEscape);
    return () => document.removeEventListener('keydown', handleEscape);
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

  const handleCategoryMouseEnter = useCallback((category: string, e: React.MouseEvent<HTMLDivElement>) => {
    setHoveredCategory(category);
    
    const categoryRect = e.currentTarget.getBoundingClientRect();
    let submenuLeft = categoryRect.right + 2;
    let submenuTop = categoryRect.top;

    // Adjust if submenu goes off screen
    // We'll adjust this after render if needed
    setSubmenuPosition({ top: submenuTop, left: submenuLeft });
  }, []);

  const handleCategoryMouseLeave = useCallback(() => {
    setHoveredCategory(null);
  }, []);

  const handleNodeTypeClick = useCallback((nodeType: string) => {
    console.log('🎨 [ContextMenu] Selected node type:', nodeType);
    onSelectNodeType(nodeType);
    onClose();
  }, [onSelectNodeType, onClose]);

  return (
    <>
      {/* Main menu */}
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
        {categories.map((category) => {
          const nodeTypes = getNodeTypesForCategory(category);
          if (!nodeTypes) return null;

          return (
            <div
              key={category}
              className="context-menu-category"
              onMouseEnter={(e) => handleCategoryMouseEnter(category, e)}
              onMouseLeave={handleCategoryMouseLeave}
            >
              {category}
              <span className="category-arrow">▶</span>
              
              {/* Submenu for this category */}
              {hoveredCategory === category && (
                <div
                  className="context-submenu"
                  style={{
                    position: 'fixed',
                    left: submenuPosition.left,
                    top: submenuPosition.top,
                  }}
                >
                  {Object.entries(nodeTypes).map(([nodeType, info]) => (
                    <div
                      key={nodeType}
                      className="context-menu-item"
                      onClick={() => handleNodeTypeClick(nodeType)}
                      title={nodeType}
                    >
                      <span
                        className="node-type-color"
                        style={{ backgroundColor: info.color }}
                      />
                      {info.name}
                    </div>
                  ))}
                </div>
              )}
            </div>
          );
        })}
      </div>
    </>
  );
}
