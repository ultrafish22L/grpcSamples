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

interface SceneOutlinerProps {
  onNodeSelect?: (node: SceneNode | null) => void;
}

type TabType = 'scene' | 'livedb' | 'localdb';

export function SceneOutliner({ onNodeSelect }: SceneOutlinerProps) {
  const { client, connected, scene } = useOctane();
  const [selectedNode, setSelectedNode] = useState<SceneNode | null>(null);
  const [loading, setLoading] = useState(false);
  const [activeTab, setActiveTab] = useState<TabType>('scene');

  const handleNodeSelect = (node: SceneNode) => {
    setSelectedNode(node);
    onNodeSelect?.(node);
  };

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
      {/* Scene Outliner Button Bar (above tabs) */}
      <div className="scene-outliner-button-bar">
        <button className="outliner-btn" title="Expand tree" data-action="expand-tree">⊞</button>
        <button className="outliner-btn" title="Collapse tree" data-action="collapse-tree">⊟</button>
        <button 
          className="outliner-btn refresh-tree-btn" 
          title="Refresh tree" 
          data-action="refresh-tree"
          onClick={loadSceneTree}
          disabled={loading || !connected}
        >
          {loading ? '⟳' : '🔄'}
        </button>
      </div>
      
      {/* Scene Outliner Tabs */}
      <div className="scene-outliner-tabs">
        <button 
          className={`scene-tab ${activeTab === 'scene' ? 'active' : ''}`} 
          data-tab="scene" 
          title="Scene hierarchy view"
          onClick={() => setActiveTab('scene')}
        >
          Scene
        </button>
        <button 
          className={`scene-tab ${activeTab === 'livedb' ? 'active' : ''}`} 
          data-tab="livedb" 
          title="Live database materials"
          onClick={() => setActiveTab('livedb')}
        >
          Live DB
        </button>
        <button 
          className={`scene-tab ${activeTab === 'localdb' ? 'active' : ''}`} 
          data-tab="localdb" 
          title="Local database materials"
          onClick={() => setActiveTab('localdb')}
        >
          Local DB
        </button>
      </div>
      
      {/* Tab Content: Scene */}
      <div className={`scene-tab-content ${activeTab === 'scene' ? 'active' : ''}`} data-content="scene">
        <div className="scene-tree">
          {!connected ? (
            <div className="scene-loading">Not connected</div>
          ) : scene && scene.tree.length > 0 ? (
            scene.tree.map(node => (
              <SceneTreeItem
                key={node.handle}
                node={node}
                depth={0}
                onSelect={handleNodeSelect}
                selectedHandle={selectedNode?.handle || null}
              />
            ))
          ) : (
            <div className="scene-loading">Click refresh to load scene</div>
          )}
        </div>
      </div>
      
      {/* Tab Content: Live DB */}
      <div className={`scene-tab-content ${activeTab === 'livedb' ? 'active' : ''}`} data-content="livedb">
        <div className="db-content">
          <div className="db-status">Live DB - Connect to access online materials</div>
        </div>
      </div>
      
      {/* Tab Content: Local DB */}
      <div className={`scene-tab-content ${activeTab === 'localdb' ? 'active' : ''}`} data-content="localdb">
        <div className="db-content">
          <div className="db-status">Local DB - No local materials found</div>
        </div>
      </div>
    </div>
  );
}
