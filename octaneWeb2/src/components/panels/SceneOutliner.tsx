import React, { useState, useEffect } from 'react'
import { useSceneStore } from '../../store/sceneStore'
import { useConnectionStore } from '../../store/connectionStore'
import { SceneNode } from '../../api/octaneClient'
import { 
  NodeType, 
  NT_PROJECT, NT_CAMERA, NT_MESH, NT_SCATTERER,
  NT_LIGHT_SUN, NT_LIGHT_AREA, NT_LIGHT_PORTAL,
  NT_ENVIRONMENT, NT_TRANSFORM
} from '../../constants/octaneTypes'
import { onEvent } from '../../core/eventBus'
import './SceneOutliner.css'

interface SceneOutlinerProps {
  className?: string
}

export const SceneOutliner: React.FC<SceneOutlinerProps> = ({ className = '' }) => {
  const [activeTab, setActiveTab] = useState<'scene' | 'link' | 'local'>('scene')
  const [searchTerm, setSearchTerm] = useState('')
  
  const {
    nodes,
    selectedNodeId,
    expandedNodes,
    loading,
    loadScene,
    selectNode,
    toggleNodeExpanded,
    clearScene
  } = useSceneStore()
  
  const { isConnected } = useConnectionStore()

  // Load scene when connected
  useEffect(() => {
    if (isConnected) {
      loadScene()
    } else {
      clearScene()
    }
  }, [isConnected, loadScene, clearScene])

  // Listen for connection events
  useEffect(() => {
    const cleanup = onEvent('connection:connected', () => {
      console.log('📡 Connected - loading scene')
      loadScene()
    })
    
    return cleanup
  }, [loadScene])

  const handleNodeClick = (nodeId: string) => {
    selectNode(nodeId)
  }

  const handleToggleVisibility = async (e: React.MouseEvent, node: SceneNode) => {
    e.stopPropagation()
    
    try {
      const newVisible = !node.visible
      // TODO: Implement setNodeVisible when needed
      console.log(`Toggle visibility for ${node.name}: ${newVisible}`)
      
      // Update the node immutably
      const updatedNodes = nodes.map(n => 
        n.id === node.id ? { ...n, visible: newVisible } : n
      )
      
      // Force re-render by updating the store
      useSceneStore.setState({ nodes: updatedNodes })
    } catch (error) {
      console.error('Failed to toggle visibility:', error)
    }
  }

  const getNodeIcon = (objectType: number): string => {
    // Map NodeType enum to icons
    switch (objectType) {
      case NT_PROJECT:
        return '📁'
      case NodeType.NT_RENDERTARGET:
        return '🎯'
      case NT_CAMERA:
        return '📷'
      case NT_MESH:
        return '🔷'
      case NodeType.NT_GEO_GROUP:
        return '📦'
      case NT_SCATTERER:
        return '⚫'
      case NT_LIGHT_SUN:
      case NT_LIGHT_AREA:
      case NT_LIGHT_PORTAL:
        return '💡'
      case NT_ENVIRONMENT:
        return '🌍'
      case NodeType.NT_MAT_DIFFUSE:
      case NodeType.NT_MAT_GLOSSY:
      case NodeType.NT_MAT_SPECULAR:
        return '🎨'
      case NodeType.NT_TEX_IMAGE:
        return '🖼️'
      case NT_TRANSFORM:
        return '📐'
      default:
        return '📄'
    }
  }

  const renderTreeNode = (node: SceneNode, level: number = 0) => {
    const isExpanded = expandedNodes.has(node.id)
    const isSelected = selectedNodeId === node.id
    const hasChildren = node.hasChildren || (node.children && node.children.length > 0)

    return (
      <div key={node.id} className="tree-node-container">
        <div
          className={`tree-node ${isSelected ? 'selected' : ''}`}
          style={{ paddingLeft: `${level * 16 + 8}px` }}
          onClick={() => handleNodeClick(node.id)}
        >
          {hasChildren ? (
            <span 
              className="expand-icon"
              onClick={(e) => {
                e.stopPropagation()
                toggleNodeExpanded(node.id)
              }}
            >
              {isExpanded ? '▼' : '▶'}
            </span>
          ) : (
            <span className="expand-icon-spacer" />
          )}
          
          <span className="node-icon">{getNodeIcon(node.objectType)}</span>
          <span className="node-name">{node.name}</span>
          
          <button
            className="visibility-btn"
            onClick={(e) => handleToggleVisibility(e, node)}
            title={node.visible ? 'Hide' : 'Show'}
          >
            {node.visible ? '👁' : '👁‍🗨'}
          </button>
        </div>
        
        {hasChildren && isExpanded && node.children && node.children.length > 0 && (
          <div className="tree-node-children">
            {node.children.map(child => renderTreeNode(child, level + 1))}
          </div>
        )}
      </div>
    )
  }

  const filterTree = (nodes: SceneNode[], term: string): SceneNode[] => {
    if (!term) return nodes
    
    return nodes.filter(node => {
      const matches = node.name.toLowerCase().includes(term.toLowerCase())
      const childMatches = node.children && filterTree(node.children, term).length > 0
      return matches || childMatches
    })
  }

  const filteredTree = filterTree(nodes, searchTerm)

  return (
    <aside className={`scene-outliner-panel ${className}`}>
      <div className="panel-header">
        <h3>Scene Outliner</h3>
        <div className="outliner-controls">
          <button 
            className="control-btn" 
            title="Collapse All"
            onClick={() => useSceneStore.setState({ expandedNodes: new Set() })}
          >
            ⊟
          </button>
          <button 
            className="control-btn" 
            title="Expand All"
            onClick={() => {
              const allIds = new Set<string>()
              const collectIds = (nodes: SceneNode[]) => {
                nodes.forEach(n => {
                  allIds.add(n.id)
                  if (n.children) collectIds(n.children)
                })
              }
              collectIds(nodes)
              useSceneStore.setState({ expandedNodes: allIds })
            }}
          >
            ⊞
          </button>
          <button 
            className="control-btn" 
            title="Refresh" 
            onClick={loadScene} 
            disabled={!isConnected || loading}
          >
            ↻
          </button>
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
          <div className="empty-message">
            <div className="spinner">⏳</div>
            Loading scene from Octane...
          </div>
        ) : filteredTree.length > 0 ? (
          filteredTree.map(node => renderTreeNode(node, 0))
        ) : (
          <div className="empty-message">
            {isConnected 
              ? (searchTerm ? 'No matching nodes' : 'Empty scene') 
              : '⚠️ Connect to Octane to load scene'}
          </div>
        )}
      </div>
    </aside>
  )
}
