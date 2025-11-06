import { useRef, useEffect } from 'react';
import { useRenderStore } from '@/store/renderStore';
import './RenderViewport.css';

export const RenderViewport = () => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const imageData = useRenderStore(state => state.imageData);
  
  // Draw image data to canvas when it updates
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas || !imageData) return;
    
    const ctx = canvas.getContext('2d');
    if (ctx) {
      ctx.putImageData(imageData, 0, 0);
    }
  }, [imageData]);
  
  // Auto-resize canvas to fill container
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    const resizeObserver = new ResizeObserver(entries => {
      for (const entry of entries) {
        const { width, height } = entry.contentRect;
        canvas.width = width;
        canvas.height = height;
        
        // Redraw image data after resize if available
        if (imageData) {
          const ctx = canvas.getContext('2d');
          if (ctx) {
            ctx.putImageData(imageData, 0, 0);
          }
        }
      }
    });
    
    const parent = canvas.parentElement;
    if (parent) {
      resizeObserver.observe(parent);
    }
    
    return () => resizeObserver.disconnect();
  }, [imageData]);
  
  return (
    <canvas 
      ref={canvasRef}
      className="render-canvas"
    />
  );
};
