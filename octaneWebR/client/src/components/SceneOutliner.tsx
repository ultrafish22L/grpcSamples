/**
 * Scene Outliner Component (React TypeScript)
 * Hierarchical tree view of Octane scene
 * P0.3 Performance Optimization: Virtual scrolling for large scenes (10K+ nodes)
 */

import { useEffect, useState, useMemo } from 'react';
import { FixedSizeList } from 'react-window';
import { useOctane } from '../hooks/useOctane';
import { SceneNode } from '../services/OctaneClient';
import { ContextMenu, ContextMenuItem } from './ContextMenu';

// Node icon mapping based on Octane API type strings (e.g., 'PT_GEOMETRY')
// Reference: octaneWeb/js/utils/OctaneIconMapper.js
// API returns string types like 'PT_GEOMETRY', not numeric enums
const NODE_ICON_MAP: Record<string, string> = {
  // Parameter types
  'PT_BOOL': '☑️',
  'PT_FLOAT': '🔢',
  'PT_INT': '🔢',
  'PT_ENUM': '📋',
  'PT_RGB': '🎨',
  'PT_STRING': '📝',
  'PT_TRANSFORM': '🔄',
  
  // Scene node types
  'PT_RENDER_TARGET': '🎯',
  'PT_RENDERTARGET': '🎯',  // Fallback without underscore
  'PT_MESH': '🫖',
  'PT_GEOMETRY': '🫖',
  'PT_CAMERA': '📷',
  'PT_LIGHT': '💡',
  'PT_MATERIAL': '🎨',
  'PT_EMISSION': '💡',
  'PT_TEXTURE': '🖼️',
  'PT_DISPLACEMENT': '〰️',
  'PT_ENVIRONMENT': '🌍',
  'PT_MEDIUM': '💨',
  
  // Settings and configuration types
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

/**
 * Flat tree node for virtual scrolling
 */
interface FlatTreeNode {
  node: SceneNode;
  depth: number;
  hasChildren: boolean;
  isExpanded: boolean;
}

/**
 * Flatten hierarchical tree to list for virtual scrolling
 * Only includes visible nodes (respects expand/collapse state)
 */
function flattenTree(
  nodes: SceneNode[], 
  depth: number, 
  expandedSet: Set<number | undefined>
): FlatTreeNode[] {
  const result: FlatTreeNode[] = [];
  
  for (const node of nodes) {
    const hasChildren = !!(node.children && node.children.length > 0);
    const isExpanded = expandedSet.has(node.handle);
    
    result.push({
      node,
      depth,
      hasChildren,
      isExpanded,
    });
    
    // Recursively add children if expanded
    if (isExpanded && hasChildren) {
      result.push(...flattenTree(node.children!, depth + 1, expandedSet));
    }
  }
  
  return result;
}

/**
 * Virtual scrolling row component
 */
interface TreeRowProps {
  index: number;
  style: React.CSSProperties;
  data: {
    flatNodes: FlatTreeNode[];
    selectedHandle: number | null;
    onSelect: (node: SceneNode) => void;
    onToggleExpand: (handle: number | undefined) => void;
    onContextMenu: (node: SceneNode, x: number, y: number) => void;
  };
}

function TreeRow({ index, style, data }: TreeRowProps) {
  const { flatNodes, selectedHandle, onSelect, onToggleExpand, onContextMenu } = data;
  const { node, depth, hasChildren, isExpanded } = flatNodes[index];
  const isSelected = selectedHandle === node.handle;

  const handleContextMenu = (e: React.MouseEvent) => {
    e.preventDefault();
    e.stopPropagation();
    if (node.type !== 'SceneRoot') {
      onContextMenu(node, e.clientX, e.clientY);
    }
  };

  return (
    <div
      style={{
        ...style,
        paddingLeft: `${depth * 20}px`,
      }}
      className={`tree-node level-${depth} ${isSelected ? 'selected' : ''}`}
      data-handle={node.handle}
      onClick={() => {
        if (node.type !== 'SceneRoot') {
          onSelect(node);
        }
      }}
      onContextMenu={handleContextMenu}
    >
      <div className="node-content">
        {hasChildren ? (
          <span
            className={`node-toggle ${isExpanded ? 'expanded' : 'collapsed'}`}
            onClick={(e) => {
              e.stopPropagation();
              onToggleExpand(node.handle);
            }}
          >
            {isExpanded ? '−' : '+'}
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
  const [contextMenu, setContextMenu] = useState<{ node: SceneNode; x: number; y: number } | null>(null);
  
  // P0.3: Track expanded nodes for virtual scrolling
  // Scene root (handle 0) starts expanded by default
  const [expandedNodes, setExpandedNodes] = useState<Set<number | undefined>>(new Set([0]));

  const handleNodeSelect = (node: SceneNode) => {
    setSelectedNode(node);
    onNodeSelect?.(node);
  };

  const handleToggleExpand = (handle: number | undefined) => {
    setExpandedNodes(prev => {
      const next = new Set(prev);
      if (next.has(handle)) {
        next.delete(handle);
      } else {
        next.add(handle);
      }
      return next;
    });
  };

  const handleContextMenu = (node: SceneNode, x: number, y: number) => {
    setContextMenu({ node, x, y });
  };

  const handleContextMenuClose = () => {
    setContextMenu(null);
  };

  const handleContextMenuAction = (action: string) => {
    console.log(`Scene Outliner context menu action: ${action}`, contextMenu?.node);
    // TODO: Implement context menu actions
    switch (action) {
      case 'render':
        console.log('Render action - to be implemented');
        break;
      case 'save':
        console.log('Save action - to be implemented');
        break;
      case 'cut':
        console.log('Cut action - to be implemented');
        break;
      case 'copy':
        console.log('Copy action - to be implemented');
        break;
      case 'paste':
        console.log('Paste action - to be implemented');
        break;
      case 'delete':
        console.log('Delete action - to be implemented');
        break;
      case 'show-in-graph':
        console.log('Show in Graph Editor - to be implemented');
        break;
      case 'show-in-lua':
        console.log('Show in Lua API browser - to be implemented');
        break;
    }
  };

  const sceneOutlinerContextMenuItems: ContextMenuItem[] = [
    { label: 'Render', action: 'render' },
    { label: 'Save...', action: 'save' },
    { label: '', action: '', separator: true },
    { label: 'Cut', action: 'cut', shortcut: 'Ctrl+X' },
    { label: 'Copy', action: 'copy', shortcut: 'Ctrl+C' },
    { label: 'Paste', action: 'paste', shortcut: 'Ctrl+V', disabled: true },
    { label: '', action: '', separator: true },
    { label: 'Delete', action: 'delete', shortcut: 'Del' },
    { label: '', action: '', separator: true },
    { label: 'Show in Graph Editor', action: 'show-in-graph' },
    { label: 'Show in Lua API browser', action: 'show-in-lua' },
  ];

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

  // P0.3: Memoized flat tree for virtual scrolling
  // Only recalculates when tree or expanded state changes
  const flatTree = useMemo(() => {
    if (sceneTree.length === 0) return [];
    
    // Create synthetic Scene root with children
    const syntheticRoot: SceneNode = {
      handle: 0,
      name: 'Scene',
      type: 'SceneRoot',
      typeEnum: 0,
      children: sceneTree
    };
    
    console.log('🔄 [Performance] Flattening tree for virtual scroll (memoized)');
    return flattenTree([syntheticRoot], 0, expandedNodes);
  }, [sceneTree, expandedNodes]);

  // Calculate container height for virtual list
  const containerHeight = 400; // Adjust based on your layout
  const rowHeight = 24; // Height per tree row

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
          ) : flatTree.length > 0 ? (
            <div className="scene-mesh-list">
              {/* P0.3: Virtual scrolling for large scenes (10K+ nodes) */}
              <FixedSizeList
                height={containerHeight}
                itemCount={flatTree.length}
                itemSize={rowHeight}
                width="100%"
                itemData={{
                  flatNodes: flatTree,
                  selectedHandle: selectedNode?.handle || null,
                  onSelect: handleNodeSelect,
                  onToggleExpand: handleToggleExpand,
                  onContextMenu: handleContextMenu,
                }}
              >
                {TreeRow}
              </FixedSizeList>
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

      {/* Context Menu */}
      {contextMenu && (
        <ContextMenu
          items={sceneOutlinerContextMenuItems}
          x={contextMenu.x}
          y={contextMenu.y}
          onClose={handleContextMenuClose}
          onItemClick={handleContextMenuAction}
        />
      )}
    </div>
  );
}
