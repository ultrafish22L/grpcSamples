/**
 * Resizable Panels Hook
 * Manages drag-to-resize functionality for panel boundaries
 */

import { useState, useCallback, useEffect, useRef } from 'react';

interface PanelSizes {
  left: number;
  center: number;
  right: number;
}

export function useResizablePanels() {
  const [panelSizes, setPanelSizes] = useState<PanelSizes>({
    left: 200,    // Scene Outliner width
    center: 0,    // Will be calculated
    right: 320,   // Node Inspector width
  });

  const [isDragging, setIsDragging] = useState(false);
  const [dragType, setDragType] = useState<'left' | 'right' | null>(null);
  const containerRef = useRef<HTMLDivElement>(null);

  // Handle mouse down on splitter
  const handleSplitterMouseDown = useCallback((type: 'left' | 'right') => {
    console.log(`🖱️ Splitter drag started: ${type}`);
    setIsDragging(true);
    setDragType(type);
    document.body.style.cursor = 'col-resize';
    document.body.style.userSelect = 'none';
  }, []);

  // Handle mouse move
  useEffect(() => {
    if (!isDragging || !dragType || !containerRef.current) return;

    const handleMouseMove = (e: MouseEvent) => {
      const container = containerRef.current;
      if (!container) return;

      const containerRect = container.getBoundingClientRect();
      const mouseX = e.clientX - containerRect.left;

      setPanelSizes(prev => {
        if (dragType === 'left') {
          // Dragging left boundary (between Scene Outliner and center)
          const minLeft = 150;
          const maxLeft = containerRect.width - prev.right - 400;
          const newLeft = Math.max(minLeft, Math.min(maxLeft, mouseX));
          
          return {
            ...prev,
            left: newLeft,
          };
        } else {
          // Dragging right boundary (between center and Node Inspector)
          const minRight = 250;
          const maxRight = containerRect.width - prev.left - 400;
          const distanceFromRight = containerRect.width - mouseX;
          const newRight = Math.max(minRight, Math.min(maxRight, distanceFromRight));
          
          return {
            ...prev,
            right: newRight,
          };
        }
      });
    };

    const handleMouseUp = () => {
      console.log('🖱️ Splitter drag ended');
      setIsDragging(false);
      setDragType(null);
      document.body.style.cursor = '';
      document.body.style.userSelect = '';
    };

    document.addEventListener('mousemove', handleMouseMove);
    document.addEventListener('mouseup', handleMouseUp);

    return () => {
      document.removeEventListener('mousemove', handleMouseMove);
      document.removeEventListener('mouseup', handleMouseUp);
    };
  }, [isDragging, dragType]);

  return {
    panelSizes,
    handleSplitterMouseDown,
    containerRef,
    isDragging,
  };
}
