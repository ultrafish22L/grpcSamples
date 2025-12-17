import React, { useEffect } from 'react';
import { useSceneStore } from '../../store/sceneStore';

interface TreeItemProps {
  node: any;
  onSelect: (id: string) => void;
  onToggleExpand: (id: string) => void;
  onToggleVisibility: (id: string) => void;
  depth?: number;
}

const TreeItem: React.FC<TreeItemProps> = ({ node, onSelect, onToggleExpand, onToggleVisibility, depth = 0 }) => {
  const hasChildren = node.children && node.children.length > 0;

  return (
    <div className="tree-item" style={{ paddingLeft: `${depth * 20}px` }}>
      <div className={`tree-row ${node.selected ? 'selected' : ''}`}>
        <span 
          className="expand-arrow" 
          onClick={() => hasChildren && onToggleExpand(node.id)}
          style={{ cursor: hasChildren ? 'pointer' : 'default', width: '16px' }}
        >
          {hasChildren ? (node.expanded ? '▼' : '▶') : ''}
        </span>
        
        <span className="node-icon">📦</span>
        
        <span className="node-name" onClick={() => onSelect(node.id)}>
          {node.name || 'Unnamed'}
        </span>
        
        <span
          className="visibility-toggle"
          onClick={() => onToggleVisibility(node.id)}
          style={{ marginLeft: 'auto', cursor: 'pointer' }}
        >
          {node.visible ? '👁' : '👁‍🗨'}
        </span>
      </div>

      {node.expanded && hasChildren && (
        <div className="tree-children">
          {node.children.map((child: any) => (
            <TreeItem
              key={child.id}
              node={child}
              onSelect={onSelect}
              onToggleExpand={onToggleExpand}
              onToggleVisibility={onToggleVisibility}
              depth={depth + 1}
            />
          ))}
        </div>
      )}
    </div>
  );
};

const SceneOutliner: React.FC<{ connected: boolean }> = ({ connected }) => {
  const { sceneTree, loadScene, selectNode, toggleExpanded, toggleVisibility, loading } = useSceneStore();

  useEffect(() => {
    if (connected && sceneTree.length === 0) {
      loadScene();
    }
  }, [connected]);

  return (
    <div className="scene-outliner">
      <header className="panel-header">
        <h3>SCENE OUTLINER</h3>
        <div className="panel-controls">
          <button title="Refresh" disabled={!connected || loading} onClick={() => loadScene()}>
            ↻
          </button>
        </div>
      </header>

      <nav className="outliner-tabs">
        <button className="active">Scene</button>
        <button>Link</button>
        <button>Local</button>
      </nav>

      <input
        type="text"
        className="search-input"
        placeholder="Search scene..."
        disabled={!connected}
      />

      <div className="tree-container">
        {!connected ? (
          <div className="empty-message">
            ⚠️ Connect to Octane to load scene
          </div>
        ) : loading ? (
          <div className="empty-message">Loading scene...</div>
        ) : sceneTree.length === 0 ? (
          <div className="empty-message">No scene data</div>
        ) : (
          sceneTree.map(node => (
            <TreeItem
              key={node.id}
              node={node}
              onSelect={selectNode}
              onToggleExpand={toggleExpanded}
              onToggleVisibility={toggleVisibility}
            />
          ))
        )}
      </div>
    </div>
  );
};

export default SceneOutliner;
