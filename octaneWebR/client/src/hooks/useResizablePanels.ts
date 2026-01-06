/**
 * Resizable Panels Hook
 * Manages drag-to-resize functionality for panel boundaries
 */

import { useState, useCallback, useEffect, useRef } from 'react';

interface PanelSizes {
  left: number;
  center: number;
  right: number;
  bottom: number;
}

export function useResizablePanels() {
  const [panelSizes, setPanelSizes] = useState<PanelSizes>({
    left: 200,    // Scene Outliner width
    center: 0,    // Will be calculated
    right: 320,   // Node Inspector width
    bottom: 350,  // Node Graph Editor height
  });

  const [isDragging, setIsDragging] = useState(false);
  const [dragType, setDragType] = useState<'left' | 'right' | 'bottom' | null>(null);
  const containerRef = useRef<HTMLDivElement>(null);

  // Handle mouse down on splitter
  const handleSplitterMouseDown = useCallback((type: 'left' | 'right' | 'bottom') => {
    console.log(`🖱️ Splitter drag started: ${type}`);
    setIsDragging(true);
    setDragType(type);
    document.body.style.cursor = type === 'bottom' ? 'row-resize' : 'col-resize';
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
      const mouseY = e.clientY - containerRect.top;

      setPanelSizes(prev => {
        const TOTAL_SPLITTERS = 8; // Two 4px splitters
        
        if (dragType === 'left') {
          // Dragging left boundary (between Scene Outliner and center)
          const minLeft = 150;
          const maxLeft = containerRect.width - prev.right - TOTAL_SPLITTERS - 400;
          const newLeft = Math.max(minLeft, Math.min(maxLeft, mouseX));
          console.log(`📏 Left panel resize: ${newLeft}px (mouse: ${mouseX}px)`);
          
          return {
            ...prev,
            left: newLeft,
          };
        } else if (dragType === 'right') {
          // Dragging right boundary (between center and Node Inspector)
          const minRight = 250;
          const maxRight = containerRect.width - prev.left - TOTAL_SPLITTERS - 400;
          const distanceFromRight = containerRect.width - mouseX;
          const newRight = Math.max(minRight, Math.min(maxRight, distanceFromRight));
          console.log(`📏 Right panel resize: ${newRight}px (mouse: ${mouseX}px)`);
          
          return {
            ...prev,
            right: newRight,
          };
        } else if (dragType === 'bottom') {
          // Dragging bottom boundary (between top panels and Node Graph Editor)
          const minBottom = 150;
          const maxBottom = containerRect.height - 200; // Leave room for top panels
          const distanceFromBottom = containerRect.height - mouseY;
          const newBottom = Math.max(minBottom, Math.min(maxBottom, distanceFromBottom));
          console.log(`📏 Bottom panel resize: ${newBottom}px (mouse: ${mouseY}px)`);
          
          return {
            ...prev,
            bottom: newBottom,
          };
        }
        
        return prev;
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
