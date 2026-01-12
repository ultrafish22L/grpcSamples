/**
 * Scene Outliner Component (React TypeScript)
 * Hierarchical tree view of Octane scene
 */

import { useEffect, useState } from 'react';
import { useOctane } from '../hooks/useOctane';
import { SceneNode } from '../services/OctaneClient';
import { OctaneIconMapper } from '../utils/OctaneIconMapper';

const getNodeIcon = (node: SceneNode): string => {
  // Special case: Scene root
  if (node.type === 'SceneRoot' || node.name === 'Scene') {
    return '📁'; // Folder icon for scene root
  }
  
  // Use OctaneIconMapper for consistent icon mapping
  const outType = String(node.type || node.outType || 'unknown');
  return OctaneIconMapper.getNodeIcon(outType, node.name);
};

interface SceneTreeItemProps {
  node: SceneNode;
  depth: number;
  onSelect: (node: SceneNode) => void;
  selectedHandle: number | null;
}

function SceneTreeItem({ node, depth, onSelect, selectedHandle }: SceneTreeItemProps) {
    // Scene root and Render target start expanded by default
  const [expanded, setExpanded] = useState(
    node.type === 'SceneRoot' || node.type === 'PT_RENDERTARGET'
  );
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
          <span className="node-name">{node.name}</span>
        </div>
      </div>
      {expanded && hasChildren && node.children!.map((child, index) => {
        // Generate unique key: use handle + pin index for NO_ITEM nodes (handle=0)
        // Pin index comes from pinInfo.ix, fallback to array index
        const uniqueKey = child.handle !== 0 
          ? child.handle 
          : `${node.handle}_pin${child.pinInfo?.ix ?? index}`;
        
        return (
          <SceneTreeItem
            key={uniqueKey}
            node={child}
            depth={depth + 1}
            onSelect={onSelect}
            selectedHandle={selectedHandle}
          />
        );
      })}
    </>
  );
}

interface SceneOutlinerProps {
  selectedNode?: SceneNode | null;
  onNodeSelect?: (node: SceneNode | null) => void;
  onSceneTreeChange?: (sceneTree: SceneNode[]) => void;
  onSyncStateChange?: (syncing: boolean) => void;
}

type TabType = 'scene' | 'livedb' | 'localdb';

export function SceneOutliner({ selectedNode, onNodeSelect, onSceneTreeChange, onSyncStateChange }: SceneOutlinerProps) {
  const { client, connected } = useOctane();
  const [loading, setLoading] = useState(false);
  const [activeTab, setActiveTab] = useState<TabType>('scene');
  const [sceneTree, setSceneTree] = useState<SceneNode[]>([]);

  const handleNodeSelect = (node: SceneNode) => {
    onNodeSelect?.(node);
  };

  const loadSceneTree = async () => {
    if (!connected || !client) {
      return;
    }

    console.log('🔄 Loading scene tree from Octane...');
    setLoading(true);
    onSyncStateChange?.(true);
    
    try {
      const tree = await client.buildSceneTree();
      
      setSceneTree(tree);
      onSceneTreeChange?.(tree);
      
      console.log(`✅ Loaded ${tree.length} top-level items`);

      // Auto-select render target node after scene is loaded
      const findRenderTarget = (nodes: SceneNode[]): SceneNode | null => {
        for (const node of nodes) {
          if (node.type === 'PT_RENDERTARGET' || node.type === 'PT_RENDER_TARGET') {
            return node;
          }
          if (node.children) {
            const found = findRenderTarget(node.children);
            if (found) return found;
          }
        }
        return null;
      };

      const renderTarget = findRenderTarget(tree);
      if (renderTarget) {
        handleNodeSelect(renderTarget);
      }
    } catch (error: any) {
      console.error('❌ Failed to load scene tree:', error);
    } finally {
      setLoading(false);
      onSyncStateChange?.(false);
    }
  };

  // Auto-load on connect (only once when connected becomes true)
  useEffect(() => {
    if (connected && client) {
      loadSceneTree();
    } else if (client && !loading) {
      // Fallback: Force load scene tree even if connected state is false
      loadSceneTree();
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
                  handle: -1, // Use -1 for synthetic root to avoid collision with NO_ITEM (0)
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
