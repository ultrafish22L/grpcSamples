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
  expandAllSignal?: number;
  collapseAllSignal?: number;
}

function SceneTreeItem({ node, depth, onSelect, selectedHandle, expandAllSignal, collapseAllSignal }: SceneTreeItemProps) {
    // Scene root and Render target start expanded by default
  const [expanded, setExpanded] = useState(
    node.type === 'SceneRoot' || node.type === 'PT_RENDERTARGET'
  );
  const hasChildren = node.children && node.children.length > 0;
  const isSelected = selectedHandle === node.handle;

  // Respond to expand/collapse all signals
  useEffect(() => {
    if (expandAllSignal && expandAllSignal > 0 && hasChildren) {
      setExpanded(true);
    }
  }, [expandAllSignal, hasChildren]);

  useEffect(() => {
    if (collapseAllSignal && collapseAllSignal > 0) {
      // Don't collapse the Scene root
      if (node.type !== 'SceneRoot') {
        setExpanded(false);
      }
    }
  }, [collapseAllSignal, node.type]);

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
            expandAllSignal={expandAllSignal}
            collapseAllSignal={collapseAllSignal}
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

interface LocalDBCategory {
  handle: number;
  name: string;
  subcategories: LocalDBCategory[];
  packages: LocalDBPackage[];
  loaded: boolean;
}

interface LocalDBPackage {
  handle: number;
  name: string;
}

// LocalDB tree item component
interface LocalDBTreeItemProps {
  category: LocalDBCategory;
  depth: number;
  onLoadCategory: (category: LocalDBCategory) => void;
  onLoadPackage: (pkg: LocalDBPackage) => void;
}

function LocalDBTreeItem({ category, depth, onLoadCategory, onLoadPackage }: LocalDBTreeItemProps) {
  const [expanded, setExpanded] = useState(depth === 0); // Root starts expanded
  const hasChildren = category.subcategories.length > 0 || category.packages.length > 0;

  const handleToggle = async (e: React.MouseEvent) => {
    e.stopPropagation();
    if (!expanded && !category.loaded) {
      // Load children when expanding for the first time
      await onLoadCategory(category);
    }
    setExpanded(!expanded);
  };

  return (
    <>
      <div className={`tree-node level-${depth}`}>
        <div className="node-content">
          {hasChildren || !category.loaded ? (
            <span
              className={`node-toggle ${expanded ? 'expanded' : 'collapsed'}`}
              onClick={handleToggle}
            >
              {expanded ? '−' : '+'}
            </span>
          ) : (
            <span className="node-spacer"></span>
          )}
          <span className="node-icon">📁</span>
          <span className="node-name">{category.name}</span>
        </div>
      </div>
      {expanded && (
        <>
          {/* Render subcategories */}
          {category.subcategories.map((subcat) => (
            <LocalDBTreeItem
              key={subcat.handle}
              category={subcat}
              depth={depth + 1}
              onLoadCategory={onLoadCategory}
              onLoadPackage={onLoadPackage}
            />
          ))}
          {/* Render packages */}
          {category.packages.map((pkg) => (
            <div
              key={pkg.handle}
              className={`tree-node level-${depth + 1} package-item`}
              onDoubleClick={() => onLoadPackage(pkg)}
              title="Double-click to load package into scene"
            >
              <div className="node-content">
                <span className="node-spacer"></span>
                <span className="node-icon">📦</span>
                <span className="node-name">{pkg.name}</span>
              </div>
            </div>
          ))}
        </>
      )}
    </>
  );
}

export function SceneOutliner({ selectedNode, onNodeSelect, onSceneTreeChange, onSyncStateChange }: SceneOutlinerProps) {
  const { client, connected } = useOctane();
  const [loading, setLoading] = useState(false);
  const [activeTab, setActiveTab] = useState<TabType>('scene');
  const [localDBRoot, setLocalDBRoot] = useState<LocalDBCategory | null>(null);
  const [localDBLoading, setLocalDBLoading] = useState(false);
  const [sceneTree, setSceneTree] = useState<SceneNode[]>([]);
  const [expandAllSignal, setExpandAllSignal] = useState(0);
  const [collapseAllSignal, setCollapseAllSignal] = useState(0);

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

  // Load LocalDB categories and packages
  const loadLocalDB = async () => {
    if (!client) return;
    
    setLocalDBLoading(true);
    try {
      const rootHandle = await client.getLocalDBRoot();
      if (!rootHandle) {
        console.warn('⚠️ LocalDB not available or empty');
        setLocalDBRoot(null);
        return;
      }

      const rootName = await client.getCategoryName(rootHandle);
      const root: LocalDBCategory = {
        handle: rootHandle,
        name: rootName,
        subcategories: [],
        packages: [],
        loaded: false
      };

      // Load root level categories and packages
      await loadCategoryChildren(root);
      setLocalDBRoot(root);
      console.log('✅ LocalDB loaded:', root);
    } catch (error) {
      console.error('❌ Failed to load LocalDB:', error);
      setLocalDBRoot(null);
    } finally {
      setLocalDBLoading(false);
    }
  };

  // Load children (subcategories and packages) for a category
  const loadCategoryChildren = async (category: LocalDBCategory) => {
    if (!client || category.loaded) return;

    try {
      // Load subcategories
      const subCatCount = await client.getSubCategoryCount(category.handle);
      for (let i = 0; i < subCatCount; i++) {
        const subCatHandle = await client.getSubCategory(category.handle, i);
        if (subCatHandle) {
          const subCatName = await client.getCategoryName(subCatHandle);
          category.subcategories.push({
            handle: subCatHandle,
            name: subCatName,
            subcategories: [],
            packages: [],
            loaded: false
          });
        }
      }

      // Load packages
      const pkgCount = await client.getPackageCount(category.handle);
      for (let i = 0; i < pkgCount; i++) {
        const pkgHandle = await client.getPackage(category.handle, i);
        if (pkgHandle) {
          const pkgName = await client.getPackageName(pkgHandle);
          category.packages.push({
            handle: pkgHandle,
            name: pkgName
          });
        }
      }

      category.loaded = true;
    } catch (error) {
      console.error('❌ Failed to load category children:', error);
    }
  };

  // Handle package double-click to load into scene
  const handlePackageLoad = async (pkg: LocalDBPackage) => {
    if (!client) return;
    
    try {
      console.log(`Loading package: ${pkg.name}`);
      const success = await client.loadPackage(pkg.handle);
      if (success) {
        alert(`✅ Package "${pkg.name}" loaded successfully!\n\nCheck the Node Graph to see the loaded nodes.`);
      } else {
        alert(`❌ Failed to load package "${pkg.name}"`);
      }
    } catch (error) {
      console.error('❌ Failed to load package:', error);
      alert(`❌ Error loading package: ${error}`);
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

  // Load LocalDB when Local DB tab becomes active
  useEffect(() => {
    if (activeTab === 'localdb' && !localDBRoot && !localDBLoading && client) {
      loadLocalDB();
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [activeTab, client]);

  const handleExpandAll = () => {
    setExpandAllSignal(prev => prev + 1);
  };

  const handleCollapseAll = () => {
    setCollapseAllSignal(prev => prev + 1);
  };

  return (
    <div className="scene-outliner">
      {/* Scene Outliner Button Bar (above tabs) */}
      <div className="scene-outliner-button-bar">
        <button 
          className="outliner-btn" 
          title="Expand all nodes" 
          data-action="expand-tree"
          onClick={handleExpandAll}
          disabled={loading || !connected || sceneTree.length === 0}
        >
          ⊞
        </button>
        <button 
          className="outliner-btn" 
          title="Collapse all nodes" 
          data-action="collapse-tree"
          onClick={handleCollapseAll}
          disabled={loading || !connected || sceneTree.length === 0}
        >
          ⊟
        </button>
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
                expandAllSignal={expandAllSignal}
                collapseAllSignal={collapseAllSignal}
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
          {localDBLoading && (
            <div className="scene-loading">Loading LocalDB...</div>
          )}
          {!localDBLoading && !localDBRoot && (
            <div className="db-status">
              Local DB - No materials found
              <br />
              <small>Add materials to your LocalDB directory to see them here</small>
            </div>
          )}
          {!localDBLoading && localDBRoot && (
            <div className="scene-tree">
              <LocalDBTreeItem
                category={localDBRoot}
                depth={0}
                onLoadCategory={async (cat) => {
                  await loadCategoryChildren(cat);
                  // Force re-render by updating state
                  setLocalDBRoot({ ...localDBRoot });
                }}
                onLoadPackage={handlePackageLoad}
              />
            </div>
          )}
        </div>
      </div>
    </div>
  );
}
