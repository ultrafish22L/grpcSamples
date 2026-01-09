/**
 * Node Graph Toolbar Component
 * Provides Add Node, Delete Node, and Fit All controls
 * Matches octaneWeb's NodeGraphEditor.js toolbar functionality
 */

import { useCallback } from 'react';

interface NodeGraphToolbarProps {
  onAddNode: () => void;
  onDeleteNode: () => void;
  onFitView: () => void;
  hasSelection: boolean;
}

export function NodeGraphToolbar({
  onAddNode,
  onDeleteNode,
  onFitView,
  hasSelection,
}: NodeGraphToolbarProps) {
  const handleAddClick = useCallback(() => {
    console.log('🔧 [Toolbar] Add Node clicked');
    onAddNode();
  }, [onAddNode]);

  const handleDeleteClick = useCallback(() => {
    console.log('🔧 [Toolbar] Delete Node clicked');
    if (hasSelection) {
      onDeleteNode();
    } else {
      console.log('🔧 [Toolbar] No nodes selected for deletion');
    }
  }, [onDeleteNode, hasSelection]);

  const handleFitClick = useCallback(() => {
    console.log('🔧 [Toolbar] Fit All clicked');
    onFitView();
  }, [onFitView]);

  return (
    <div className="node-graph-toolbar">
      <button
        className="node-graph-tool"
        title="Add Node (right-click for menu)"
        onClick={handleAddClick}
      >
        +
      </button>
      <button
        className="node-graph-tool"
        title="Delete Selected Node (Del key)"
        onClick={handleDeleteClick}
        disabled={!hasSelection}
        style={{
          opacity: hasSelection ? 1 : 0.5,
          cursor: hasSelection ? 'pointer' : 'not-allowed',
        }}
      >
        🗑
      </button>
      <button
        className="node-graph-tool"
        title="Fit All Nodes to View"
        onClick={handleFitClick}
      >
        ⊞
      </button>
    </div>
  );
}
