/**
 * Scene Outliner Component (React TypeScript)
 * Hierarchical tree view of Octane scene
 */

import React, { useEffect, useState } from 'react';
import { useOctane } from '../hooks/useOctane';
import { SceneNode } from '../services/OctaneClient';

// Node Pin Type mapping (from OctaneTypes.js NodePinType enum)
// These values come from ApiItem/outType API call
const NODE_PIN_TYPE_MAP: Record<number, { icon: string; label: string }> = {
  1: { icon: '☑️', label: 'Bool' }, // PT_BOOL
  2: { icon: '🔢', label: 'Float' }, // PT_FLOAT
  3: { icon: '🔢', label: 'Int' }, // PT_INT
  4: { icon: '🔄', label: 'Transform' }, // PT_TRANSFORM
  5: { icon: '🎨', label: 'Texture' }, // PT_TEXTURE
  6: { icon: '💡', label: 'Emission' }, // PT_EMISSION
  7: { icon: '🎨', label: 'Material' }, // PT_MATERIAL
  8: { icon: '📷', label: 'Camera' }, // PT_CAMERA
  9: { icon: '🌍', label: 'Environment' }, // PT_ENVIRONMENT
  10: { icon: '📷', label: 'Imager' }, // PT_IMAGER
  11: { icon: '🔧', label: 'Kernel' }, // PT_KERNEL
  12: { icon: '🫖', label: 'Geometry' }, // PT_GEOMETRY
  13: { icon: '☁️', label: 'Medium' }, // PT_MEDIUM
  15: { icon: '🎬', label: 'Film Settings' }, // PT_FILM_SETTINGS
  16: { icon: '📋', label: 'Enum' }, // PT_ENUM
  18: { icon: '⚙️', label: 'Postprocessing' }, // PT_POSTPROCESSING
  19: { icon: '🎯', label: 'Render Target' }, // PT_RENDERTARGET
  22: { icon: '🗺️', label: 'Displacement' }, // PT_DISPLACEMENT
  23: { icon: '📝', label: 'String' }, // PT_STRING
  24: { icon: '📊', label: 'Render Passes' }, // PT_RENDER_PASSES
  25: { icon: '🎭', label: 'Render Layer' }, // PT_RENDER_LAYER
  27: { icon: '⏱️', label: 'Animation Settings' }, // PT_ANIMATION_SETTINGS
  37: { icon: '📤', label: 'Output AOV Group' }, // PT_OUTPUT_AOV_GROUP
};

const getNodeIcon = (typeEnum: number): string => {
  // Check exact match
  if (NODE_PIN_TYPE_MAP[typeEnum]) {
    return NODE_PIN_TYPE_MAP[typeEnum].icon;
  }
  
  // Check for material range (50000-50136)
  if (typeEnum >= 50000 && typeEnum <= 50136) {
    return '🎨'; // Material
  }
  
  // Default icon
  return '⚪';
};

const getNodeLabel = (typeEnum: number): string => {
  if (NODE_PIN_TYPE_MAP[typeEnum]) {
    return NODE_PIN_TYPE_MAP[typeEnum].label;
  }
  
  if (typeEnum >= 50000 && typeEnum <= 50136) {
    return 'Material';
  }
  
  return `Type ${typeEnum}`;
};

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
        <span className="tree-icon">{getNodeIcon(node.typeEnum || 0)}</span>
        <span className="tree-label">{node.name}</span>
        <span className="tree-type">{getNodeLabel(node.typeEnum || 0)}</span>
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
    if (!connected) return;

    setLoading(true);
    try {
      console.log('🔄 Loading scene tree from Octane...');
      
      // Use the new buildSceneTree method that properly recurses
      const tree = await client.buildSceneTree();
      setSceneTree(tree);
      
      console.log(`✅ Loaded ${tree.length} top-level items`);
    } catch (error: any) {
      console.error('❌ Failed to load scene tree:', error);
    } finally {
      setLoading(false);
    }
  };

  // Auto-load on connect (only once when connected becomes true)
  useEffect(() => {
    if (connected) {
      console.log('🎬 Auto-loading scene tree on connect');
      loadSceneTree();
    }
  }, [connected]);

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
              {/* Scene root node */}
              <div className="tree-node scene-root">
                <span className="tree-icon">🌳</span>
                <span className="tree-label">Scene</span>
              </div>
              {/* Hierarchical scene items */}
              {sceneTree.map(node => (
                <SceneTreeItem
                  key={node.handle}
                  node={node}
                  depth={1}
                  onSelect={handleNodeSelect}
                  selectedHandle={selectedNode?.handle || null}
                />
              ))}
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
