/**
 * Scene Outliner Component (React TypeScript)
 * Hierarchical tree view of Octane scene
 */

import React, { useEffect, useState } from 'react';
import { useOctane } from '../hooks/useOctane';
import { SceneNode } from '../services/OctaneClient';

interface SceneTreeItemProps {
  node: SceneNode;
  depth: number;
  onSelect: (node: SceneNode) => void;
  selectedHandle: number | null;
}

function SceneTreeItem({ node, depth, onSelect, selectedHandle }: SceneTreeItemProps) {
  const [expanded, setExpanded] = useState(false);
  const hasChildren = node.children && node.children.length > 0;

  return (
    <div className="scene-tree-item">
      <div
        className={`tree-node ${selectedHandle === node.handle ? 'selected' : ''}`}
        style={{ paddingLeft: `${depth * 16}px` }}
        onClick={() => onSelect(node)}
      >
        {hasChildren && (
          <span
            className="tree-expand"
            onClick={(e) => {
              e.stopPropagation();
              setExpanded(!expanded);
            }}
          >
            {expanded ? '▼' : '▶'}
          </span>
        )}
        <span className="tree-icon">📦</span>
        <span className="tree-label">{node.name}</span>
        <span className="tree-type">{node.type}</span>
      </div>
      {expanded && hasChildren && (
        <div className="tree-children">
          {node.children!.map(child => (
            <SceneTreeItem
              key={child.handle}
              node={child}
              depth={depth + 1}
              onSelect={onSelect}
              selectedHandle={selectedHandle}
            />
          ))}
        </div>
      )}
    </div>
  );
}

export function SceneOutliner() {
  const { client, connected, scene } = useOctane();
  const [selectedNode, setSelectedNode] = useState<SceneNode | null>(null);
  const [loading, setLoading] = useState(false);

  const loadSceneTree = async () => {
    if (!connected) return;

    setLoading(true);
    try {
      // Test with GetMeshes which exists in LiveLink proto
      const response = await client.callApi('LiveLink', 'GetMeshes', {});
      console.log('✅ GetMeshes response:', response);
    } catch (error: any) {
      console.error('❌ Failed to load meshes:', error);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="scene-outliner">
      <div className="outliner-header">
        <h3>Scene Outliner</h3>
        <button onClick={loadSceneTree} disabled={!connected || loading}>
          {loading ? '⟳' : '↻'} Refresh
        </button>
      </div>
      <div className="outliner-tree">
        {!connected ? (
          <p className="status-text">Not connected</p>
        ) : scene && scene.tree.length > 0 ? (
          scene.tree.map(node => (
            <SceneTreeItem
              key={node.handle}
              node={node}
              depth={0}
              onSelect={setSelectedNode}
              selectedHandle={selectedNode?.handle || null}
            />
          ))
        ) : (
          <p className="status-text">
            <button onClick={loadSceneTree}>Load Scene Tree</button>
          </p>
        )}
      </div>
    </div>
  );
}
