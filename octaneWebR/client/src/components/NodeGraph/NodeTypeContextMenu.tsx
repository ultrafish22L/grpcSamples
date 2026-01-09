/**
 * Node Type Context Menu Component
 * Hierarchical menu for creating new nodes
 * Matches octaneWeb's NodeGraphEditor.js showContextMenu() functionality
 */

import { useEffect, useRef, useState, useCallback } from 'react';
import { createPortal } from 'react-dom';
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
  const submenuRef = useRef<HTMLDivElement>(null);
  const [hoveredCategory, setHoveredCategory] = useState<string | null>(null);
  const [submenuPosition, setSubmenuPosition] = useState<{ top: number; left: number }>({ top: 0, left: 0 });
  const hideTimeoutRef = useRef<NodeJS.Timeout | null>(null);
  const categories = getNodeCategories();

  // Close menu on click outside (matching octaneWeb line 167: uses 'click' not 'mousedown')
  useEffect(() => {
    const handleClickOutside = (e: MouseEvent) => {
      if (menuRef.current && !menuRef.current.contains(e.target as Node)) {
        onClose();
      }
    };

    document.addEventListener('click', handleClickOutside);
    return () => document.removeEventListener('click', handleClickOutside);
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

  // Cleanup timeout on unmount
  useEffect(() => {
    return () => {
      if (hideTimeoutRef.current) {
        clearTimeout(hideTimeoutRef.current);
      }
    };
  }, []);

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
    // Clear any pending hide timeout
    if (hideTimeoutRef.current) {
      clearTimeout(hideTimeoutRef.current);
      hideTimeoutRef.current = null;
    }

    setHoveredCategory(category);
    
    // Position submenu to the right of the category item (matching octaneWeb lines 294-313)
    const categoryRect = e.currentTarget.getBoundingClientRect();
    let submenuLeft = categoryRect.right + 2;
    let submenuTop = categoryRect.top;

    setSubmenuPosition({ top: submenuTop, left: submenuLeft });
  }, []);

  const handleCategoryMouseLeave = useCallback(() => {
    // Add delay before hiding to allow moving mouse to submenu
    hideTimeoutRef.current = setTimeout(() => {
      setHoveredCategory(null);
    }, 150); // 150ms delay is standard for hover menus
  }, []);

  const handleSubmenuMouseEnter = useCallback(() => {
    // Keep submenu visible when hovering over it
    if (hideTimeoutRef.current) {
      clearTimeout(hideTimeoutRef.current);
      hideTimeoutRef.current = null;
    }
  }, []);

  const handleSubmenuMouseLeave = useCallback(() => {
    // Hide submenu when mouse leaves it
    setHoveredCategory(null);
  }, []);

  // Adjust submenu position if it goes off-screen (matching octaneWeb lines 300-306)
  useEffect(() => {
    if (!hoveredCategory) return;

    // Give submenu a frame to render so we can measure it
    const timeoutId = setTimeout(() => {
      const submenuElement = document.querySelector('.context-submenu') as HTMLElement;
      if (!submenuElement) return;

      const submenuRect = submenuElement.getBoundingClientRect();
      let adjustedLeft = submenuPosition.left;
      let adjustedTop = submenuPosition.top;

      // If submenu goes off right edge, show on left side instead
      if (submenuRect.right > window.innerWidth) {
        const categoryElement = document.querySelector('.context-menu-category:hover') as HTMLElement;
        if (categoryElement) {
          const categoryRect = categoryElement.getBoundingClientRect();
          adjustedLeft = categoryRect.left - submenuRect.width - 2;
        }
      }

      // If submenu goes off bottom edge, adjust top position
      if (submenuRect.bottom > window.innerHeight) {
        adjustedTop = window.innerHeight - submenuRect.height;
      }

      if (adjustedLeft !== submenuPosition.left || adjustedTop !== submenuPosition.top) {
        setSubmenuPosition({ top: adjustedTop, left: adjustedLeft });
      }
    }, 0);

    return () => clearTimeout(timeoutId);
  }, [hoveredCategory, submenuPosition]);

  const handleNodeTypeClick = useCallback((nodeType: string) => {
    console.log('🎨 [ContextMenu] Selected node type:', nodeType);
    onSelectNodeType(nodeType);
    onClose();
  }, [onSelectNodeType, onClose]);

  // Render menu to document.body using portal (matching octaneWeb line 319: document.body.appendChild)
  return createPortal(
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
                  ref={submenuRef}
                  className="context-submenu"
                  onMouseEnter={handleSubmenuMouseEnter}
                  onMouseLeave={handleSubmenuMouseLeave}
                  style={{
                    display: 'block', // Override CSS display: none (matching octaneWeb line 308)
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
    </>,
    document.body // Render to document.body (matching octaneWeb approach)
  );
}
