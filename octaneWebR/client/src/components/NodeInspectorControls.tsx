/**
 * Node Inspector Controls Component (React TypeScript)
 * Vertical column of quick-access buttons for jumping to specific nodes
 * Port of octaneWeb/js/components/NodeInspectorControls.js
 */

import { useState } from 'react';
import { SceneNode } from '../services/OctaneClient';

interface NodeInspectorControlsProps {
  sceneTree: SceneNode[];
  onNodeSelect: (node: SceneNode) => void;
  onExpandAll?: () => void;
  onCollapseAll?: () => void;
}

export function NodeInspectorControls({ 
  sceneTree, 
  onNodeSelect,
  onExpandAll,
  onCollapseAll 
}: NodeInspectorControlsProps) {
  const [activeButton, setActiveButton] = useState<string | null>(null);

  /**
   * Find node by type in scene tree (recursive search)
   */
  const findNodeByType = (nodes: SceneNode[], targetType: string): SceneNode | null => {
    for (const node of nodes) {
      // Match by type or name
      if (node.type === targetType || node.outType === targetType || node.name === targetType) {
        return node;
      }
      // Recursively search children
      if (node.children && node.children.length > 0) {
        const found = findNodeByType(node.children, targetType);
        if (found) return found;
      }
    }
    return null;
  };

  /**
   * Find node by name pattern (case-insensitive)
   */
  const findNodeByName = (nodes: SceneNode[], namePattern: string): SceneNode | null => {
    const pattern = namePattern.toLowerCase();
    for (const node of nodes) {
      if (node.name?.toLowerCase().includes(pattern)) {
        return node;
      }
      if (node.children && node.children.length > 0) {
        const found = findNodeByName(node.children, pattern);
        if (found) return found;
      }
    }
    return null;
  };

  /**
   * Jump to specific node type
   */
  const jumpToNode = (buttonId: string, nodeType: string) => {
    console.log(`🎯 Jumping to ${nodeType} node`);
    
    // Update active button state
    setActiveButton(buttonId);

    // Find the node in scene tree
    let targetNode: SceneNode | null = null;

    // Try different search strategies based on node type
    switch (buttonId) {
      case 'rendertarget':
        targetNode = findNodeByType(sceneTree, 'PT_RENDERTARGET');
        break;
      case 'camera':
      case 'camera-alt':
        targetNode = findNodeByType(sceneTree, 'PT_CAMERA') || findNodeByName(sceneTree, 'camera');
        break;
      case 'environment':
        targetNode = findNodeByName(sceneTree, 'environment');
        break;
      case 'visible-environment':
        targetNode = findNodeByName(sceneTree, 'visible environment');
        break;
      case 'geometry':
        targetNode = findNodeByType(sceneTree, 'PT_GEOMETRY');
        break;
      case 'animation':
        targetNode = findNodeByName(sceneTree, 'animation');
        break;
      case 'render-layer':
        targetNode = findNodeByName(sceneTree, 'render layer');
        break;
      case 'aov-group':
        targetNode = findNodeByName(sceneTree, 'aov');
        break;
      case 'post-processing':
        targetNode = findNodeByName(sceneTree, 'post processing');
        break;
      case 'film':
        targetNode = findNodeByName(sceneTree, 'film');
        break;
      case 'kernel':
        targetNode = findNodeByName(sceneTree, 'kernel');
        break;
      case 'render-aov':
        targetNode = findNodeByName(sceneTree, 'render aov');
        break;
      case 'camera-imager':
        targetNode = findNodeByName(sceneTree, 'imager');
        break;
    }

    if (targetNode) {
      console.log(`✅ Found ${nodeType} node:`, targetNode.name);
      onNodeSelect(targetNode);
    } else {
      console.warn(`⚠️ Could not find ${nodeType} node in scene tree`);
    }
  };

  const handleExpandAll = () => {
    console.log('📂 Expanding all nodes');
    if (onExpandAll) onExpandAll();
  };

  const handleCollapseAll = () => {
    console.log('📁 Collapsing all nodes');
    if (onCollapseAll) onCollapseAll();
  };

  return (
    <div className="node-inspector-controls-vertical">
      {/* Top Row Buttons */}
      <button 
        className={`quick-btn ${activeButton === 'expand-all' ? 'active' : ''}`}
        title="Expand All Nodes" 
        onClick={handleExpandAll}
      >
        📂
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'rendertarget' ? 'active' : ''}`}
        title="Render Target" 
        onClick={() => jumpToNode('rendertarget', 'PT_RENDERTARGET')}
      >
        📄
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'camera' ? 'active' : ''}`}
        title="Camera Settings" 
        onClick={() => jumpToNode('camera', 'Camera')}
      >
        📷
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'environment' ? 'active' : ''}`}
        title="Environment Settings" 
        onClick={() => jumpToNode('environment', 'Environment')}
      >
        🌍
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'geometry' ? 'active' : ''}`}
        title="Current Geometry" 
        onClick={() => jumpToNode('geometry', 'PT_GEOMETRY')}
      >
        🔷
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'animation' ? 'active' : ''}`}
        title="Animation Settings" 
        onClick={() => jumpToNode('animation', 'Animation')}
      >
        🎬
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'render-layer' ? 'active' : ''}`}
        title="Active Render Layer" 
        onClick={() => jumpToNode('render-layer', 'Render Layer')}
      >
        🎭
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'aov-group' ? 'active' : ''}`}
        title="AOV Group" 
        onClick={() => jumpToNode('aov-group', 'AOV Group')}
      >
        🔵
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'post-processing' ? 'active' : ''}`}
        title="Post Processing" 
        onClick={() => jumpToNode('post-processing', 'Post Processing')}
      >
        🎨
      </button>

      {/* Spacer */}
      <div className="controls-spacer-vertical"></div>

      {/* Bottom Row Buttons */}
      <button 
        className={`quick-btn ${activeButton === 'collapse-all' ? 'active' : ''}`}
        title="Collapse All nodes" 
        onClick={handleCollapseAll}
      >
        📁
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'camera-alt' ? 'active' : ''}`}
        title="Camera Settings" 
        onClick={() => jumpToNode('camera-alt', 'Camera')}
      >
        📸
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'visible-environment' ? 'active' : ''}`}
        title="Visible Environment Settings" 
        onClick={() => jumpToNode('visible-environment', 'Visible Environment')}
      >
        🌐
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'film' ? 'active' : ''}`}
        title="Film Settings" 
        onClick={() => jumpToNode('film', 'Film')}
      >
        🎞️
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'kernel' ? 'active' : ''}`}
        title="Current kernel" 
        onClick={() => jumpToNode('kernel', 'Kernel')}
      >
        ⚙️
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'render-aov' ? 'active' : ''}`}
        title="Render AOV Node" 
        onClick={() => jumpToNode('render-aov', 'Render AOV')}
      >
        🔴
      </button>
      
      <button 
        className={`quick-btn ${activeButton === 'camera-imager' ? 'active' : ''}`}
        title="Camera Imager" 
        onClick={() => jumpToNode('camera-imager', 'Imager')}
      >
        📹
      </button>
    </div>
  );
}
