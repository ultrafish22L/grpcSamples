/**
 * Scene Outliner Component (React TypeScript)
 * Hierarchical tree view of Octane scene
 */

import React, { useEffect, useState } from 'react';
import { useOctane } from '../hooks/useOctane';
import { SceneNode } from '../services/OctaneClient';

// Node Pin Type mapping (from OctaneIconMapper.js)
// API returns string types like 'PT_GEOMETRY', not numeric enums
const NODE_ICON_MAP: Record<string, string> = {
  'PT_BOOL': '☑️',
  'PT_FLOAT': '🔢',
  'PT_INT': '🔢',
  'PT_ENUM': '📋',
  'PT_RGB': '🎨',
  'PT_RENDER_TARGET': '🎯',
  'PT_RENDERTARGET': '🎯',
  'PT_MESH': '🫖',
  'PT_GEOMETRY': '🫖',
  'PT_CAMERA': '📷',
  'PT_LIGHT': '💡',
  'PT_MATERIAL': '🎨',
  'PT_ENVIRONMENT': '🌍',
  'PT_FILM_SETTINGS': '🎬',
  'PT_ANIMATION_SETTINGS': '⏱️',
  'PT_KERNEL': '🔧',
  'PT_RENDER_LAYER': '🎭',
  'PT_RENDER_PASSES': '📊',
  'PT_OUTPUT_AOV_GROUP': '📤',
  'PT_IMAGER': '📷',
  'PT_POSTPROCESSING': '⚙️',
};

const getNodeIcon = (node: SceneNode): string => {
  // Special case: Scene root
  if (node.type === 'SceneRoot' || node.name === 'Scene') {
    return '📁'; // Folder icon for scene root
  }
  
  // API returns string types like 'PT_GEOMETRY', not numeric enums
  const outType = node.type || '';
  
  // Check if we have an icon mapping
  if (NODE_ICON_MAP[outType]) {
    return NODE_ICON_MAP[outType];
  }
  
  // Default icon for unknown types
  return '⚪';
};

interface SceneTreeItemProps {
  node: SceneNode;
  depth: number;
  onSelect: (node: SceneNode) => void;
  selectedHandle: number | null;
}

function SceneTreeItem({ node, depth, onSelect, selectedHandle }: SceneTreeItemProps) {
  // Scene root starts expanded by default
  const [expanded, setExpanded] = useState(node.type === 'SceneRoot');
  const hasChildren = node.children && node.children.length > 0;
  const isSelected = selectedHandle === node.handle;

  return (
    <>
      <div
        className={`tree-node level-${depth} ${isSelected ? 'selected' : ''}`}
        data-handle={node.handle}
        onClick={() => {
          // Don't select the synthetic Scene root
          if (node.type !== 'SceneRoot') {
            onSelect(node);
          }
        }}
      >
        <div className="node-content">
          {hasChildren ? (
            <span
              className={`node-toggle ${expanded ? 'expanded' : 'collapsed'}`}
              onClick={(e) => {
                e.stopPropagation();
                setExpanded(!expanded);
              }}
            >
              {expanded ? '−' : '+'}
            </span>
          ) : (
            <span className="node-spacer"></span>
          )}
          <span className="node-icon">{getNodeIcon(node)}</span>
          <span className="node-name">
            {node.name}
            {node.type !== 'SceneRoot' && node.type && (
              <span className="node-type-label"> Type {node.type}</span>
            )}
          </span>
        </div>
      </div>
      {expanded && hasChildren && node.children!.map(child => (
        <SceneTreeItem
          key={child.handle}
          node={child}
          depth={depth + 1}
          onSelect={onSelect}
          selectedHandle={selectedHandle}
        />
      ))}
    </>
  );
}

interface SceneOutlinerProps {
  onNodeSelect?: (node: SceneNode | null) => void;
}

type TabType = 'scene' | 'livedb' | 'localdb';

export function SceneOutliner({ onNodeSelect }: SceneOutlinerProps) {
  const { client, connected } = useOctane();
  const [selectedNode, setSelectedNode] = useState<SceneNode | null>(null);
  const [loading, setLoading] = useState(false);
  const [activeTab, setActiveTab] = useState<TabType>('scene');
  const [sceneTree, setSceneTree] = useState<SceneNode[]>([]);

  const handleNodeSelect = (node: SceneNode) => {
    setSelectedNode(node);
    onNodeSelect?.(node);
  };

  const loadSceneTree = async () => {
    if (!connected) {
      console.log('⚠️ Cannot load scene: not connected');
      return;
    }
    if (!client) {
      console.log('⚠️ Cannot load scene: no client');
      return;
    }

    console.log('🔄 Loading scene tree from Octane...');
    setLoading(true);
    
    try {
      // Use the new buildSceneTree method that properly recurses
      const tree = await client.buildSceneTree();
      setSceneTree(tree);
      
      console.log(`✅ Loaded ${tree.length} top-level items`);
      
      // Debug: Log the typeEnum values for each item
      tree.forEach((item, idx) => {
        console.log(`📊 Scene item ${idx}: ${item.name} typeEnum=${item.typeEnum} type=${item.type}`);
      });
    } catch (error: any) {
      console.error('❌ Failed to load scene tree:', error);
      console.error('Error stack:', error.stack);
    } finally {
      setLoading(false);
    }
  };

  // Auto-load on connect (only once when connected becomes true)
  useEffect(() => {
    console.log('🔍 SceneOutliner useEffect triggered:', { connected, hasClient: !!client });
    if (connected && client) {
      console.log('🎬 Auto-loading scene tree on connect');
      loadSceneTree();
    } else {
      console.log('⏳ Waiting for connection...');
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [connected, client]);

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
          ) : loading ? (
            <div className="scene-loading">Loading scene...</div>
          ) : sceneTree.length > 0 ? (
            <div className="scene-mesh-list">
              {/* Create a synthetic Scene root node with children */}
              <SceneTreeItem
                node={{
                  handle: 0,
                  name: 'Scene',
                  type: 'SceneRoot',
                  typeEnum: 0,
                  children: sceneTree
                }}
                depth={0}
                onSelect={handleNodeSelect}
                selectedHandle={selectedNode?.handle || null}
              />
            </div>
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
