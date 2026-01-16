/**
 * Node Graph Editor Toolbar Component
 * Matches Octane SE Manual Figure 10 - The Graph Editor buttons
 * https://docs.otoy.com/standaloneSE/TheGraphEditor.html
 * 
 * Documented buttons (converted to vertical layout, docked left):
 * 1. Recenter View
 * 2. Re-arrange Graph with Sub-graph
 * 3. Re-arrange Graph
 * 4. View/Hide Render Target Preview Scene
 * 5. View/Hide Mesh Preview Scene
 * 6. View/Hide Material Preview Scene
 * 7. View/Hide Texture Preview Scene
 * 8. Snap Items To Grid
 * 9. View/Hide Graph Editor Grid
 */

import { useCallback, useState } from 'react';

interface NodeGraphToolbarProps {
  gridVisible: boolean;
  setGridVisible: (visible: boolean) => void;
  snapToGrid: boolean;
  setSnapToGrid: (snap: boolean) => void;
  onRecenterView?: () => void; // Optional callback for recenter (from ReactFlow fitView)
}

export function NodeGraphToolbar({ 
  gridVisible, 
  setGridVisible, 
  snapToGrid, 
  setSnapToGrid,
  onRecenterView
}: NodeGraphToolbarProps) {
  
  // Toggle states for preview scenes (managed locally)
  const [renderTargetPreview, setRenderTargetPreview] = useState(false);
  const [meshPreview, setMeshPreview] = useState(false);
  const [materialPreview, setMaterialPreview] = useState(false);
  const [texturePreview, setTexturePreview] = useState(false);

  // 1. Recenter View
  const handleRecenterView = useCallback(() => {
    console.log('🎯 Recenter View');
    if (onRecenterView) {
      onRecenterView();
    }
  }, [onRecenterView]);

  // 2. Re-arrange Graph with Sub-graph
  const handleRearrangeWithSubgraph = useCallback(() => {
    console.log('🔄 Re-arrange Graph with Sub-graph');
    // TODO: Auto-layout including sub-graphs
  }, []);

  // 3. Re-arrange Graph
  const handleRearrangeGraph = useCallback(() => {
    console.log('📐 Re-arrange Graph');
    // TODO: Auto-layout algorithm
  }, []);

  // 4. View/Hide Render Target Preview Scene
  const handleToggleRenderTargetPreview = useCallback(() => {
    setRenderTargetPreview(prev => {
      const newState = !prev;
      console.log(`📹 Render Target Preview: ${newState ? 'SHOW' : 'HIDE'}`);
      return newState;
    });
    // TODO: Show/hide render target preview
  }, []);

  // 5. View/Hide Mesh Preview Scene
  const handleToggleMeshPreview = useCallback(() => {
    setMeshPreview(prev => {
      const newState = !prev;
      console.log(`🔷 Mesh Preview: ${newState ? 'SHOW' : 'HIDE'}`);
      return newState;
    });
    // TODO: Show/hide mesh preview
  }, []);

  // 6. View/Hide Material Preview Scene
  const handleToggleMaterialPreview = useCallback(() => {
    setMaterialPreview(prev => {
      const newState = !prev;
      console.log(`🎨 Material Preview: ${newState ? 'SHOW' : 'HIDE'}`);
      return newState;
    });
    // TODO: Show/hide material preview
  }, []);

  // 7. View/Hide Texture Preview Scene
  const handleToggleTexturePreview = useCallback(() => {
    setTexturePreview(prev => {
      const newState = !prev;
      console.log(`🖼️ Texture Preview: ${newState ? 'SHOW' : 'HIDE'}`);
      return newState;
    });
    // TODO: Show/hide texture preview
  }, []);

  // 8. Snap Items To Grid
  const handleToggleGridSnap = useCallback(() => {
    const newState = !snapToGrid;
    setSnapToGrid(newState);
    console.log(`🧲 Snap Items To Grid: ${newState ? 'ON' : 'OFF'}`);
  }, [snapToGrid, setSnapToGrid]);

  // 9. View/Hide Graph Editor Grid
  const handleToggleGrid = useCallback(() => {
    const newState = !gridVisible;
    setGridVisible(newState);
    console.log(`📊 Graph Editor Grid: ${newState ? 'SHOW' : 'HIDE'}`);
  }, [gridVisible, setGridVisible]);

  return (
    <div className="node-graph-toolbar">
      {/* 1. Recenter View - Red crosshairs/target icon */}
      <button
        className="toolbar-button"
        onClick={handleRecenterView}
        title="Recenter View"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <circle cx="8" cy="8" r="6" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <line x1="8" y1="2" x2="8" y2="6" stroke="currentColor" strokeWidth="2" />
          <line x1="8" y1="10" x2="8" y2="14" stroke="currentColor" strokeWidth="2" />
          <line x1="2" y1="8" x2="6" y2="8" stroke="currentColor" strokeWidth="2" />
          <line x1="10" y1="8" x2="14" y2="8" stroke="currentColor" strokeWidth="2" />
          <circle cx="8" cy="8" r="1.5" fill="currentColor" />
        </svg>
      </button>

      {/* 2. Re-arrange Graph with Sub-graph - Grid with nodes icon */}
      <button
        className="toolbar-button"
        onClick={handleRearrangeWithSubgraph}
        title="Re-arrange Graph with Sub-graph"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <rect x="1" y="1" width="5" height="4" fill="currentColor" opacity="0.6" />
          <rect x="10" y="1" width="5" height="4" fill="currentColor" opacity="0.6" />
          <rect x="1" y="6" width="5" height="4" fill="currentColor" opacity="0.6" />
          <rect x="10" y="6" width="5" height="4" fill="currentColor" opacity="0.6" />
          <rect x="1" y="11" width="5" height="4" fill="currentColor" opacity="0.6" />
          <rect x="10" y="11" width="5" height="4" fill="currentColor" opacity="0.6" />
        </svg>
      </button>

      {/* 3. Re-arrange Graph - Simple grid pattern */}
      <button
        className="toolbar-button"
        onClick={handleRearrangeGraph}
        title="Re-arrange Graph"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <rect x="2" y="2" width="4" height="4" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <rect x="10" y="2" width="4" height="4" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <rect x="2" y="10" width="4" height="4" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <rect x="10" y="10" width="4" height="4" fill="none" stroke="currentColor" strokeWidth="1.5" />
        </svg>
      </button>

      {/* 4. View/Hide Render Target Preview Scene - Camera/render icon */}
      <button
        className={`toolbar-button ${renderTargetPreview ? 'active' : ''}`}
        onClick={handleToggleRenderTargetPreview}
        title="View/Hide Render Target Preview Scene"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <rect x="1" y="4" width="14" height="9" rx="1" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <circle cx="8" cy="9" r="2.5" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <rect x="5" y="2" width="6" height="2" fill="currentColor" />
          <circle cx="12" cy="6" r="0.8" fill="currentColor" />
        </svg>
      </button>

      {/* 5. View/Hide Mesh Preview Scene - Mesh/geometry icon */}
      <button
        className={`toolbar-button ${meshPreview ? 'active' : ''}`}
        onClick={handleToggleMeshPreview}
        title="View/Hide Mesh Preview Scene"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <polygon points="8,2 14,6 14,11 8,14 2,11 2,6" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <line x1="8" y1="2" x2="8" y2="14" stroke="currentColor" strokeWidth="1" />
          <line x1="2" y1="6" x2="14" y2="6" stroke="currentColor" strokeWidth="1" />
          <line x1="2" y1="11" x2="14" y2="11" stroke="currentColor" strokeWidth="1" />
        </svg>
      </button>

      {/* 6. View/Hide Material Preview Scene - Sphere/material icon */}
      <button
        className={`toolbar-button ${materialPreview ? 'active' : ''}`}
        onClick={handleToggleMaterialPreview}
        title="View/Hide Material Preview Scene"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <circle cx="8" cy="8" r="6" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <ellipse cx="8" cy="8" rx="6" ry="2" fill="none" stroke="currentColor" strokeWidth="1" opacity="0.5" />
          <ellipse cx="8" cy="8" rx="2" ry="6" fill="none" stroke="currentColor" strokeWidth="1" opacity="0.5" />
          <circle cx="6" cy="6" r="1.5" fill="currentColor" opacity="0.3" />
        </svg>
      </button>

      {/* 7. View/Hide Texture Preview Scene - Texture pattern icon */}
      <button
        className={`toolbar-button ${texturePreview ? 'active' : ''}`}
        onClick={handleToggleTexturePreview}
        title="View/Hide Texture Preview Scene"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <rect x="1" y="1" width="14" height="14" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <path d="M1 5 L5 1 M1 9 L9 1 M1 13 L13 1 M5 15 L15 5 M9 15 L15 9 M13 15 L15 13" stroke="currentColor" strokeWidth="1" opacity="0.6" />
        </svg>
      </button>

      {/* 8. Snap Items To Grid - Grid with snap icon */}
      <button
        className={`toolbar-button ${snapToGrid ? 'active' : ''}`}
        onClick={handleToggleGridSnap}
        title="Snap Items To Grid"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <circle cx="3" cy="3" r="1" fill="currentColor" opacity="0.4" />
          <circle cx="8" cy="3" r="1" fill="currentColor" opacity="0.4" />
          <circle cx="13" cy="3" r="1" fill="currentColor" opacity="0.4" />
          <circle cx="3" cy="8" r="1" fill="currentColor" opacity="0.4" />
          <circle cx="8" cy="8" r="1" fill="currentColor" opacity="0.4" />
          <circle cx="13" cy="8" r="1" fill="currentColor" opacity="0.4" />
          <circle cx="3" cy="13" r="1" fill="currentColor" opacity="0.4" />
          <circle cx="8" cy="13" r="1" fill="currentColor" opacity="0.4" />
          <circle cx="13" cy="13" r="1" fill="currentColor" opacity="0.4" />
          <rect x="6.5" y="6.5" width="3" height="3" fill="none" stroke="currentColor" strokeWidth="1.5" />
        </svg>
      </button>

      {/* 9. View/Hide Graph Editor Grid - Grid pattern icon */}
      <button
        className={`toolbar-button ${gridVisible ? 'active' : ''}`}
        onClick={handleToggleGrid}
        title="View/Hide Graph Editor Grid"
      >
        <svg width="14" height="14" viewBox="0 0 16 16">
          <line x1="0" y1="4" x2="16" y2="4" stroke="currentColor" strokeWidth="0.5" />
          <line x1="0" y1="8" x2="16" y2="8" stroke="currentColor" strokeWidth="0.5" />
          <line x1="0" y1="12" x2="16" y2="12" stroke="currentColor" strokeWidth="0.5" />
          <line x1="4" y1="0" x2="4" y2="16" stroke="currentColor" strokeWidth="0.5" />
          <line x1="8" y1="0" x2="8" y2="16" stroke="currentColor" strokeWidth="0.5" />
          <line x1="12" y1="0" x2="12" y2="16" stroke="currentColor" strokeWidth="0.5" />
        </svg>
      </button>
    </div>
  );
}
