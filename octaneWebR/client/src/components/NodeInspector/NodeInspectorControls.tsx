/**
 * Node Inspector Controls Component (React TypeScript)
 * Vertical column of quick-access buttons for jumping to specific nodes
 * Port of octaneWeb/js/components/NodeInspectorControls.js
 */

import { useState, useCallback } from 'react';
import { SceneNode } from '../../services/OctaneClient';
import { getNodeInspectorIcon } from '../../utils/UIIconMapping';

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
  const findNodeByType = useCallback((nodes: SceneNode[], targetType: string): SceneNode | null => {
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
  }, []);

  /**
   * Find node by name pattern (case-insensitive)
   */
  const findNodeByName = useCallback((nodes: SceneNode[], namePattern: string): SceneNode | null => {
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
  }, []);

  /**
   * Jump to specific node type
   */
  const jumpToNode = useCallback((buttonId: string, nodeType: string) => {
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
  }, [sceneTree, onNodeSelect, findNodeByType, findNodeByName]);

  const handleExpandAll = useCallback(() => {
    console.log('📂 Expanding all nodes');
    if (onExpandAll) onExpandAll();
  }, [onExpandAll]);

  const handleCollapseAll = useCallback(() => {
    console.log('📁 Collapsing all nodes');
    if (onCollapseAll) onCollapseAll();
  }, [onCollapseAll]);

  // Memoized button click handlers
  const handleRenderTargetClick = useCallback(() => jumpToNode('rendertarget', 'PT_RENDERTARGET'), [jumpToNode]);
  const handleCameraClick = useCallback(() => jumpToNode('camera', 'Camera'), [jumpToNode]);
  const handleEnvironmentClick = useCallback(() => jumpToNode('environment', 'Environment'), [jumpToNode]);
  const handleGeometryClick = useCallback(() => jumpToNode('geometry', 'PT_GEOMETRY'), [jumpToNode]);
  const handleAnimationClick = useCallback(() => jumpToNode('animation', 'Animation'), [jumpToNode]);
  const handleRenderLayerClick = useCallback(() => jumpToNode('render-layer', 'Render Layer'), [jumpToNode]);
  const handleAovGroupClick = useCallback(() => jumpToNode('aov-group', 'AOV Group'), [jumpToNode]);
  const handlePostProcessingClick = useCallback(() => jumpToNode('post-processing', 'Post Processing'), [jumpToNode]);
  const handleCameraAltClick = useCallback(() => jumpToNode('camera-alt', 'Camera'), [jumpToNode]);
  const handleVisibleEnvironmentClick = useCallback(() => jumpToNode('visible-environment', 'Visible Environment'), [jumpToNode]);
  const handleFilmClick = useCallback(() => jumpToNode('film', 'Film'), [jumpToNode]);
  const handleKernelClick = useCallback(() => jumpToNode('kernel', 'Kernel'), [jumpToNode]);
  const handleRenderAovClick = useCallback(() => jumpToNode('render-aov', 'Render AOV'), [jumpToNode]);
  const handleCameraImagerClick = useCallback(() => jumpToNode('camera-imager', 'Imager'), [jumpToNode]);

  return (
    <div className="node-inspector-controls-vertical">
      {/* Buttons in exact order from Octane SE Manual Figure 2 */}
      
      {/* Button 1: Expand All Nodes */}
      <button 
        className={`quick-btn ${activeButton === 'expand-all' ? 'active' : ''}`}
        title="Expand All Nodes" 
        onClick={handleExpandAll}
      >
        <img src={getNodeInspectorIcon('EXPAND_ALL_NODES')} alt="Expand all" />
      </button>
      
      {/* Button 2: Render Target */}
      <button 
        className={`quick-btn ${activeButton === 'rendertarget' ? 'active' : ''}`}
        title="Render Target" 
        onClick={handleRenderTargetClick}
      >
        <img src={getNodeInspectorIcon('RENDER_TARGET')} alt="Render target" />
      </button>
      
      {/* Button 3: Environment Settings (NOT Camera!) */}
      <button 
        className={`quick-btn ${activeButton === 'environment' ? 'active' : ''}`}
        title="Environment Settings" 
        onClick={handleEnvironmentClick}
      >
        <img src={getNodeInspectorIcon('ENVIRONMENT_SETTINGS')} alt="Environment" />
      </button>
      
      {/* Button 4: Current Geometry */}
      <button 
        className={`quick-btn ${activeButton === 'geometry' ? 'active' : ''}`}
        title="Current Geometry" 
        onClick={handleGeometryClick}
      >
        <img src={getNodeInspectorIcon('CURRENT_GEOMETRY')} alt="Geometry" />
      </button>
      
      {/* Button 5: Animation Settings */}
      <button 
        className={`quick-btn ${activeButton === 'animation' ? 'active' : ''}`}
        title="Animation Settings" 
        onClick={handleAnimationClick}
      >
        <img src={getNodeInspectorIcon('ANIMATION_SETTINGS')} alt="Animation" />
      </button>
      
      {/* Button 6: Active Render Layer */}
      <button 
        className={`quick-btn ${activeButton === 'render-layer' ? 'active' : ''}`}
        title="Active Render Layer" 
        onClick={handleRenderLayerClick}
      >
        <img src={getNodeInspectorIcon('ACTIVE_RENDER_LAYER')} alt="Render layer" />
      </button>
      
      {/* Button 7: AOV Group */}
      <button 
        className={`quick-btn ${activeButton === 'aov-group' ? 'active' : ''}`}
        title="AOV Group" 
        onClick={handleAovGroupClick}
      >
        <img src={getNodeInspectorIcon('AOV_GROUP')} alt="AOV group" />
      </button>
      
      {/* Button 8: Post Processing */}
      <button 
        className={`quick-btn ${activeButton === 'post-processing' ? 'active' : ''}`}
        title="Post Processing" 
        onClick={handlePostProcessingClick}
      >
        <img src={getNodeInspectorIcon('POST_PROCESSING')} alt="Post processing" />
      </button>

      {/* Button 9: Collapse All Nodes */}
      <button 
        className={`quick-btn ${activeButton === 'collapse-all' ? 'active' : ''}`}
        title="Collapse All nodes" 
        onClick={handleCollapseAll}
      >
        <img src={getNodeInspectorIcon('COLLAPSE_ALL_NODES')} alt="Collapse all" />
      </button>
      
      {/* Button 10: Camera Settings */}
      <button 
        className={`quick-btn ${activeButton === 'camera' ? 'active' : ''}`}
        title="Camera Settings" 
        onClick={handleCameraClick}
      >
        <img src={getNodeInspectorIcon('CAMERA_SETTINGS')} alt="Camera" />
      </button>
      
      {/* Button 11: Visible Environment Settings */}
      <button 
        className={`quick-btn ${activeButton === 'visible-environment' ? 'active' : ''}`}
        title="Visible Environment Settings" 
        onClick={handleVisibleEnvironmentClick}
      >
        <img src={getNodeInspectorIcon('VISIBLE_ENVIRONMENT_SETTINGS')} alt="Visible environment" />
      </button>
      
      {/* Button 12: Film Settings */}
      <button 
        className={`quick-btn ${activeButton === 'film' ? 'active' : ''}`}
        title="Film Settings" 
        onClick={handleFilmClick}
      >
        <img src={getNodeInspectorIcon('FILM_SETTINGS')} alt="Film" />
      </button>
      
      {/* Button 13: Current kernel */}
      <button 
        className={`quick-btn ${activeButton === 'kernel' ? 'active' : ''}`}
        title="Current kernel" 
        onClick={handleKernelClick}
      >
        <img src={getNodeInspectorIcon('CURRENT_KERNEL')} alt="Kernel" />
      </button>
      
      {/* Button 14: Render AOV Node */}
      <button 
        className={`quick-btn ${activeButton === 'render-aov' ? 'active' : ''}`}
        title="Render AOV Node" 
        onClick={handleRenderAovClick}
      >
        <img src={getNodeInspectorIcon('RENDER_AOV_NODE')} alt="Render AOV" />
      </button>
      
      {/* Button 15: Camera Imager */}
      <button 
        className={`quick-btn ${activeButton === 'camera-imager' ? 'active' : ''}`}
        title="Camera Imager" 
        onClick={handleCameraImagerClick}
      >
        <img src={getNodeInspectorIcon('CAMERA_IMAGER')} alt="Imager" />
      </button>
    </div>
  );
}
