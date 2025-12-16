/**
 * Scene Outliner Component (React TypeScript)
 * Hierarchical tree view of Octane scene
 */

import React, { useEffect, useState } from 'react';
import { useOctane } from '../hooks/useOctane';
import { SceneNode } from '../services/OctaneClient';

// Node type enum mapping (from octaneids.proto)
const NODE_TYPE_MAP: Record<number, { icon: string; label: string }> = {
  1: { icon: '📦', label: 'Mesh' }, // NT_GEO_MESH
  14: { icon: '☀️', label: 'Daylight' }, // NT_ENV_DAYLIGHT
  15: { icon: '📷', label: 'Camera' }, // NT_IMAGER_CAMERA
  56: { icon: '🎥', label: 'Render Target' }, // NT_RENDERTARGET
  85: { icon: '🔌', label: 'Graph Input' }, // NT_PROGRAMMABLE_GRAPH_INPUT
  123: { icon: '💡', label: 'Point Light' }, // NT_TOON_POINT_LIGHT
  124: { icon: '💡', label: 'Directional Light' }, // NT_TOON_DIRECTIONAL_LIGHT
  148: { icon: '💡', label: 'Quad Light' }, // NT_LIGHT_QUAD
  149: { icon: '💡', label: 'Sphere Light' }, // NT_LIGHT_SPHERE
  152: { icon: '💡', label: 'Spot Light' }, // NT_LIGHT_VOLUME_SPOT
  402: { icon: '💡', label: 'Analytic Light' }, // NT_LIGHT_ANALYTIC
  403: { icon: '💡', label: 'Directional Light' }, // NT_LIGHT_DIRECTIONAL
};

const getNodeIcon = (typeEnum: number): string => {
  // Check exact match
  if (NODE_TYPE_MAP[typeEnum]) {
    return NODE_TYPE_MAP[typeEnum].icon;
  }
  
  // Check for material range (50000-50136)
  if (typeEnum >= 50000 && typeEnum <= 50136) {
    return '🎨'; // Material
  }
  
  // Default icon
  return '⚪';
};

const getNodeLabel = (typeEnum: number): string => {
  if (NODE_TYPE_MAP[typeEnum]) {
    return NODE_TYPE_MAP[typeEnum].label;
  }
  
  if (typeEnum >= 50000 && typeEnum <= 50136) {
    return 'Material';
  }
  
  return `Node Type ${typeEnum}`;
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
  const [meshes, setMeshes] = useState<any[]>([]);

  const handleNodeSelect = (node: SceneNode) => {
    setSelectedNode(node);
    onNodeSelect?.(node);
  };

  const loadSceneTree = async () => {
    if (!connected) return;

    setLoading(true);
    try {
      console.log('🔄 Loading full scene tree from Octane...');
      
      // Step 1: Get root node graph
      const rootResponse = await client.callApi('ApiProjectManager', 'rootNodeGraph', {});
      console.log('✅ Root node graph:', rootResponse);
      
      if (!rootResponse?.result?.handle) {
        throw new Error('No root handle returned');
      }
      
      const rootHandle = rootResponse.result.handle;
      
      // Step 2: Check if it's a graph
      const isGraphResponse = await client.callApi('ApiItem', 'isGraph', rootHandle);
      console.log('✅ Is graph:', isGraphResponse);
      
      const isGraph = isGraphResponse?.result;
      
      if (isGraph) {
        // Step 3: Get owned items
        const ownedItemsResponse = await client.callApi('ApiNodeGraph', 'getOwnedItems', rootHandle);
        console.log('✅ Owned items:', ownedItemsResponse);
        
        if (!ownedItemsResponse?.list?.handle) {
          throw new Error('No owned items handle');
        }
        
        const ownedItemsHandle = ownedItemsResponse.list.handle;
        
        // Step 4: Get array size
        const sizeResponse = await client.callApi('ApiItemArray', 'size', ownedItemsHandle);
        console.log('✅ Array size:', sizeResponse);
        
        const size = sizeResponse?.result || 0;
        
        // Step 5: Iterate through items and get item info
        const items = [];
        for (let i = 0; i < size; i++) {
          const itemResponse = await client.callApi('ApiItemArray', 'get', ownedItemsHandle, { index: i });
          if (itemResponse?.result?.handle) {
            const handle = itemResponse.result.handle;
            
            // Get item name
            let name = 'Unknown';
            try {
              const nameResponse = await client.callApi('ApiItem', 'name', handle);
              name = nameResponse?.result || `Item ${i}`;
            } catch (err) {
              console.warn(`Failed to get name for handle ${handle}:`, err);
            }
            
            // Get item type
            let type = 'unknown';
            let typeEnum = 0;
            try {
              const typeResponse = await client.callApi('ApiItem', 'type', handle);
              typeEnum = typeResponse?.result || 0;
              type = `type_${typeEnum}`;
            } catch (err) {
              console.warn(`Failed to get type for handle ${handle}:`, err);
            }
            
            items.push({
              handle,
              name,
              type,
              typeEnum
            });
          }
        }
        
        console.log(`📦 Loaded ${items.length} scene items from Octane:`, items);
        setMeshes(items); // Reuse meshes state for now
      }
    } catch (error: any) {
      console.error('❌ Failed to load scene tree:', error);
    } finally {
      setLoading(false);
    }
  };

  // Auto-load on connect
  useEffect(() => {
    if (connected && meshes.length === 0) {
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
          ) : meshes.length > 0 ? (
            <div className="scene-mesh-list">
              <div className="tree-node">
                <span className="tree-icon">🌳</span>
                <span className="tree-label">Scene</span>
              </div>
              {meshes.map((mesh, index) => (
                <div key={mesh.id || index} className="scene-tree-item">
                  <div
                    className={`tree-node ${selectedNode?.handle === mesh.id ? 'selected' : ''}`}
                    style={{ paddingLeft: '16px' }}
                    onClick={() => {
                      const node: SceneNode = {
                        handle: mesh.id,
                        name: mesh.name,
                        type: 'mesh',
                        children: []
                      };
                      handleNodeSelect(node);
                    }}
                  >
                    <span className="tree-icon">📦</span>
                    <span className="tree-label">{mesh.name}</span>
                    <span className="tree-type">mesh</span>
                  </div>
                </div>
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
