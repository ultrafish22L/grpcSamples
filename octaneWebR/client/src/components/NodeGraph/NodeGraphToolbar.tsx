/**
 * Node Graph Editor Toolbar Component
 * Vertical toolbar on left side matching Octane SE Figure 10
 * Provides quick access to common node graph operations
 */

import { useCallback } from 'react';
import { useReactFlow } from '@xyflow/react';
import './NodeGraphToolbar.css';

interface NodeGraphToolbarProps {
  onSearchOpen: () => void;
}

export function NodeGraphToolbar({ onSearchOpen }: NodeGraphToolbarProps) {
  const { fitView, zoomIn, zoomOut, getNodes } = useReactFlow();

  // Frame all nodes (zoom to fit all)
  const handleFrameAll = useCallback(() => {
    fitView({ padding: 0.2, duration: 300 });
  }, [fitView]);

  // Frame selected nodes
  const handleFrameSelected = useCallback(() => {
    const selectedNodes = getNodes().filter(node => node.selected);
    if (selectedNodes.length === 0) {
      console.log('No nodes selected to frame');
      return;
    }

    // Use fitView with nodes parameter to automatically center and zoom
    fitView({
      padding: 0.2,
      duration: 300,
      nodes: selectedNodes,
    });
  }, [getNodes, fitView]);

  const handleZoomIn = useCallback(() => {
    zoomIn({ duration: 200 });
  }, [zoomIn]);

  const handleZoomOut = useCallback(() => {
    zoomOut({ duration: 200 });
  }, [zoomOut]);

  const handleAutoLayout = useCallback(() => {
    console.log('Auto-layout feature - organizing nodes...');
    // TODO: Implement auto-layout algorithm
    alert('Auto-layout feature coming soon!\n\nThis will automatically organize nodes in a clean layout.');
  }, []);

  return (
    <div className="node-graph-toolbar">
      <button
        className="toolbar-button"
        onClick={handleFrameAll}
        title="Frame All (Fit all nodes in view)"
      >
        <svg width="20" height="20" viewBox="0 0 20 20">
          <rect x="2" y="2" width="16" height="16" fill="none" stroke="currentColor" strokeWidth="2" />
          <rect x="5" y="5" width="3" height="3" fill="currentColor" />
          <rect x="12" y="5" width="3" height="3" fill="currentColor" />
          <rect x="5" y="12" width="3" height="3" fill="currentColor" />
          <rect x="12" y="12" width="3" height="3" fill="currentColor" />
        </svg>
      </button>

      <button
        className="toolbar-button"
        onClick={handleFrameSelected}
        title="Frame Selected (Fit selected nodes in view)"
      >
        <svg width="20" height="20" viewBox="0 0 20 20">
          <rect x="2" y="2" width="16" height="16" fill="none" stroke="currentColor" strokeWidth="2" strokeDasharray="2,2" />
          <rect x="7" y="7" width="6" height="6" fill="currentColor" />
        </svg>
      </button>

      <div className="toolbar-separator" />

      <button
        className="toolbar-button"
        onClick={handleZoomIn}
        title="Zoom In"
      >
        <svg width="20" height="20" viewBox="0 0 20 20">
          <circle cx="8" cy="8" r="6" fill="none" stroke="currentColor" strokeWidth="2" />
          <line x1="13" y1="13" x2="18" y2="18" stroke="currentColor" strokeWidth="2" />
          <line x1="8" y1="5" x2="8" y2="11" stroke="currentColor" strokeWidth="2" />
          <line x1="5" y1="8" x2="11" y2="8" stroke="currentColor" strokeWidth="2" />
        </svg>
      </button>

      <button
        className="toolbar-button"
        onClick={handleZoomOut}
        title="Zoom Out"
      >
        <svg width="20" height="20" viewBox="0 0 20 20">
          <circle cx="8" cy="8" r="6" fill="none" stroke="currentColor" strokeWidth="2" />
          <line x1="13" y1="13" x2="18" y2="18" stroke="currentColor" strokeWidth="2" />
          <line x1="5" y1="8" x2="11" y2="8" stroke="currentColor" strokeWidth="2" />
        </svg>
      </button>

      <div className="toolbar-separator" />

      <button
        className="toolbar-button"
        onClick={onSearchOpen}
        title="Search Nodes (Ctrl+F)"
      >
        <svg width="20" height="20" viewBox="0 0 20 20">
          <circle cx="8" cy="8" r="6" fill="none" stroke="currentColor" strokeWidth="2" />
          <line x1="13" y1="13" x2="18" y2="18" stroke="currentColor" strokeWidth="2" />
        </svg>
      </button>

      <button
        className="toolbar-button"
        onClick={handleAutoLayout}
        title="Auto-Layout Nodes"
      >
        <svg width="20" height="20" viewBox="0 0 20 20">
          <rect x="2" y="2" width="6" height="6" fill="currentColor" />
          <rect x="12" y="2" width="6" height="6" fill="currentColor" />
          <rect x="7" y="12" width="6" height="6" fill="currentColor" />
          <line x1="5" y1="8" x2="10" y2="12" stroke="currentColor" strokeWidth="2" />
          <line x1="15" y1="8" x2="10" y2="12" stroke="currentColor" strokeWidth="2" />
        </svg>
      </button>
    </div>
  );
}
