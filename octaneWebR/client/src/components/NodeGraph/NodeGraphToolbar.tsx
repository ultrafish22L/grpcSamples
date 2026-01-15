/**
 * Node Graph Editor Toolbar Component
 * Vertical toolbar on left side matching Octane SE
 * Docked toolbar with compact icon buttons (Figure 10 from manual)
 */

import { useCallback } from 'react';
import { useReactFlow } from '@xyflow/react';
import './NodeGraphToolbar.css';

interface NodeGraphToolbarProps {
  onSearchOpen: () => void;
}

export function NodeGraphToolbar({ onSearchOpen }: NodeGraphToolbarProps) {
  const { fitView, zoomIn, zoomOut, getNodes } = useReactFlow();

  const handleMacroPreview = useCallback(() => {
    console.log('Show Macro/Material Preview');
    // TODO: Implement material preview
  }, []);

  const handleNodeLibrary = useCallback(() => {
    console.log('Node Library');
    // TODO: Open node library
  }, []);

  const handleLiveDB = useCallback(() => {
    console.log('LiveDB Access');
    // TODO: Open LiveDB
  }, []);

  const handleImageImport = useCallback(() => {
    console.log('Import Image');
    // TODO: Image import dialog
  }, []);

  const handleMaterialPaint = useCallback(() => {
    console.log('Material Paint Tool');
    // TODO: Material painting
  }, []);

  const handleFrameView = useCallback(() => {
    fitView({ padding: 0.2, duration: 300 });
  }, [fitView]);

  const handleCutConnections = useCallback(() => {
    console.log('Cut Connections Tool (Ctrl+Drag)');
    // Connection cutter is handled by interaction mode
  }, []);

  const handleGridSnap = useCallback(() => {
    console.log('Toggle Grid Snap');
    // TODO: Toggle grid snapping
  }, []);

  const handleAutoLayout = useCallback(() => {
    console.log('Auto-Layout');
    // TODO: Auto-layout algorithm
  }, []);

  return (
    <div className="node-graph-toolbar">
      {/* Material Preview / Macro View */}
      <button
        className="toolbar-button"
        onClick={handleMacroPreview}
        title="Show Material Preview"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <rect x="2" y="2" width="3" height="12" fill="currentColor" opacity="0.8" />
          <rect x="6" y="2" width="3" height="12" fill="currentColor" opacity="0.5" />
          <rect x="10" y="2" width="3" height="12" fill="currentColor" opacity="0.8" />
        </svg>
      </button>

      {/* Node Library / Grid */}
      <button
        className="toolbar-button"
        onClick={handleNodeLibrary}
        title="Node Library"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <rect x="1" y="1" width="6" height="6" fill="currentColor" />
          <rect x="9" y="1" width="6" height="6" fill="currentColor" />
          <rect x="1" y="9" width="6" height="6" fill="currentColor" />
          <rect x="9" y="9" width="6" height="6" fill="currentColor" />
        </svg>
      </button>

      {/* LiveDB / Material Database */}
      <button
        className="toolbar-button"
        onClick={handleLiveDB}
        title="LiveDB Material Database"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <path d="M8 2 L14 6 L8 10 L2 6 Z" fill="currentColor" />
          <path d="M2 8 L8 12 L14 8" fill="none" stroke="currentColor" strokeWidth="1.5" />
        </svg>
      </button>

      {/* Image Import */}
      <button
        className="toolbar-button"
        onClick={handleImageImport}
        title="Import Image"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <rect x="1" y="1" width="14" height="14" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <circle cx="5" cy="5" r="2" fill="currentColor" />
          <path d="M1 11 L6 6 L10 10 L15 5" fill="none" stroke="currentColor" strokeWidth="1.5" />
        </svg>
      </button>

      {/* Material Paint Tool */}
      <button
        className="toolbar-button"
        onClick={handleMaterialPaint}
        title="Material Paint Tool"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <path d="M4 12 L1 15 L3 13 L4 14 Z" fill="currentColor" />
          <path d="M5 11 L11 5 C11.5 4.5 12.5 4.5 13 5 C13.5 5.5 13.5 6.5 13 7 L7 13 L5 11 Z" fill="currentColor" />
          <circle cx="12" cy="6" r="1.5" fill="rgba(255,255,255,0.3)" />
        </svg>
      </button>

      {/* Frame View / Fit to Screen */}
      <button
        className="toolbar-button"
        onClick={handleFrameView}
        title="Frame All Nodes (F)"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <path d="M1 1 L1 6 M1 1 L6 1" stroke="currentColor" strokeWidth="2" fill="none" />
          <path d="M15 1 L15 6 M15 1 L10 1" stroke="currentColor" strokeWidth="2" fill="none" />
          <path d="M1 15 L1 10 M1 15 L6 15" stroke="currentColor" strokeWidth="2" fill="none" />
          <path d="M15 15 L15 10 M15 15 L10 15" stroke="currentColor" strokeWidth="2" fill="none" />
        </svg>
      </button>

      {/* Cut Connections Tool */}
      <button
        className="toolbar-button"
        onClick={handleCutConnections}
        title="Cut Connections (Ctrl+Drag)"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <circle cx="4" cy="4" r="3" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <circle cx="12" cy="12" r="3" fill="none" stroke="currentColor" strokeWidth="1.5" />
          <line x1="6" y1="6" x2="10" y2="10" stroke="currentColor" strokeWidth="2" />
          <line x1="8" y1="8" x2="8" y2="8" stroke="red" strokeWidth="3" strokeLinecap="round" />
        </svg>
      </button>

      {/* Grid Snap */}
      <button
        className="toolbar-button"
        onClick={handleGridSnap}
        title="Toggle Grid Snap"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <circle cx="3" cy="3" r="1" fill="currentColor" />
          <circle cx="8" cy="3" r="1" fill="currentColor" />
          <circle cx="13" cy="3" r="1" fill="currentColor" />
          <circle cx="3" cy="8" r="1" fill="currentColor" />
          <circle cx="8" cy="8" r="1" fill="currentColor" />
          <circle cx="13" cy="8" r="1" fill="currentColor" />
          <circle cx="3" cy="13" r="1" fill="currentColor" />
          <circle cx="8" cy="13" r="1" fill="currentColor" />
          <circle cx="13" cy="13" r="1" fill="currentColor" />
        </svg>
      </button>

      {/* Auto-Layout */}
      <button
        className="toolbar-button"
        onClick={handleAutoLayout}
        title="Auto-Layout Nodes"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <rect x="1" y="1" width="5" height="3" fill="currentColor" />
          <rect x="10" y="1" width="5" height="3" fill="currentColor" />
          <rect x="1" y="6" width="5" height="3" fill="currentColor" />
          <rect x="10" y="6" width="5" height="3" fill="currentColor" />
          <rect x="1" y="11" width="5" height="3" fill="currentColor" />
          <rect x="10" y="11" width="5" height="3" fill="currentColor" />
        </svg>
      </button>

      {/* Search */}
      <button
        className="toolbar-button"
        onClick={onSearchOpen}
        title="Search Nodes (Ctrl+F)"
      >
        <svg width="16" height="16" viewBox="0 0 16 16">
          <circle cx="6" cy="6" r="4" fill="none" stroke="currentColor" strokeWidth="2" />
          <line x1="9" y1="9" x2="14" y2="14" stroke="currentColor" strokeWidth="2" strokeLinecap="round" />
        </svg>
      </button>
    </div>
  );
}
