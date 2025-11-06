import React, { useState, useEffect } from 'react';
import { useSceneStore } from '../../store/sceneStore';
import { useConnectionStore } from '../../store/connectionStore';
import { octaneClient, SceneNode } from '../../api/octaneClient';
import './SceneOutliner.css';

interface SceneOutlinerProps {
  className?: string;
}

export const SceneOutliner: React.FC<SceneOutlinerProps> = ({ className = '' }) => {
  const [activeTab, setActiveTab] = useState<'scene' | 'link' | 'local'>('scene');
  const [searchTerm, setSearchTerm] = useState('');
  
  const { sceneData, selectedNode, expandedNodes, loading, setSceneData, selectNode, toggleNodeExpanded, setLoading } = useSceneStore();
  const { connected } = useConnectionStore();

  // Load scene tree when connected
  useEffect(() => {
    if (connected) {
      loadSceneTree();
    }
  }, [connected]);

  const loadSceneTree = async () => {
    setLoading(true);
    try {
      const data = await octaneClient.buildSceneTree();
      setSceneData(data);
    } catch (error) {
      console.error('Failed to load scene tree:', error);
    } finally {
      setLoading(false);
    }
  };

  const handleNodeClick = (handle: string) => {
    selectNode(handle);
  };

  const getNodeIcon = (type: string) => {
    const icons: Record<string, string> = {
      'mesh': '🔷',
      'camera': '📷',
      'light': '💡',
      'material': '🎨',
      'rendertarget': '🎯',
      'transform': '📐'
    };
    return icons[type] || '📦';
  };

  const renderTreeNode = (node: SceneNode, level: number = 0) => {
    const isExpanded = expandedNodes.has(node.handle);
    const isSelected = selectedNode === node.handle;
    const hasChildren = node.children && node.children.length > 0;

    return (
      <div key={node.handle} className="tree-node-container">
        <div
          className={`tree-node ${isSelected ? 'selected' : ''}`}
          style={{ paddingLeft: `${level * 16 + 8}px` }}
          onClick={() => handleNodeClick(node.handle)}
          data-handle={node.handle}
        >
          {hasChildren && (
            <span 
              className="expand-icon"
              onClick={(e) => {
                e.stopPropagation();
                toggleNodeExpanded(node.handle);
              }}
            >
              {isExpanded ? '▼' : '▶'}
            </span>
          )}
          {!hasChildren && <span className="expand-icon-spacer" />}
          <span className="node-icon">{getNodeIcon(node.type)}</span>
          <span className="node-name">{node.name}</span>
        </div>
        {hasChildren && isExpanded && (
          <div className="tree-node-children">
            {node.children!.map(child => renderTreeNode(child, level + 1))}
          </div>
        )}
      </div>
    );
  };

  const tree = sceneData.tree;
  const filteredTree = searchTerm
    ? tree.filter(node => node.name.toLowerCase().includes(searchTerm.toLowerCase()))
    : tree;

  return (
    <aside className={`scene-outliner-panel ${className}`}>
      <div className="panel-header">
        <h3>Scene Outliner</h3>
        <div className="outliner-controls">
          <button className="control-btn" title="Collapse All">⊟</button>
          <button className="control-btn" title="Expand All">⊞</button>
          <button className="control-btn" title="Refresh">↻</button>
        </div>
      </div>

      <div className="outliner-tabs">
        <button
          className={`tab ${activeTab === 'scene' ? 'active' : ''}`}
          onClick={() => setActiveTab('scene')}
        >
          Scene
        </button>
        <button
          className={`tab ${activeTab === 'link' ? 'active' : ''}`}
          onClick={() => setActiveTab('link')}
        >
          Link
        </button>
        <button
          className={`tab ${activeTab === 'local' ? 'active' : ''}`}
          onClick={() => setActiveTab('local')}
        >
          Local
        </button>
      </div>

      <div className="search-box">
        <input
          type="text"
          placeholder="Search scene..."
          value={searchTerm}
          onChange={(e) => setSearchTerm(e.target.value)}
          className="search-input"
        />
      </div>

      <div className="scene-tree">
        {loading ? (
          <div className="empty-message">Loading scene...</div>
        ) : filteredTree.length > 0 ? (
          filteredTree.map(node => renderTreeNode(node, 0))
        ) : (
          <div className="empty-message">
            {connected ? (searchTerm ? 'No matching nodes' : 'No scene data') : 'Connect to Octane to load scene'}
          </div>
        )}
      </div>
    </aside>
  );
};
