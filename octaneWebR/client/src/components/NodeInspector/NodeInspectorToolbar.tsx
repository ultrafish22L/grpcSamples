/**
 * Node Inspector Toolbar Component
 * Matches Octane SE Manual Figure 2 - Quick access buttons in the Node Inspector
 * https://docs.otoy.com/standaloneSE/TheNodeInspector.html
 * 
 * These buttons allow quick jump to commonly used nodes:
 * RenderTarget, Camera, Resolution, Environment, Imager, Kernel, and Current Mesh
 */

import { useCallback } from 'react';
import { getNodeInspectorIcon } from '../../utils/UIIconMapping';

export function NodeInspectorToolbar() {
  
  // Button handlers based on Octane SE Manual Figure 2
  
  // 1. Expand All Nodes
  const handleExpandAll = useCallback(() => {
    console.log('📂 Expand All Nodes');
    // TODO: Expand all collapsed nodes in the inspector
  }, []);

  // 2. Jump to Render Target
  const handleJumpToRenderTarget = useCallback(() => {
    console.log('🎯 Jump to Render Target node');
    // TODO: Select and display Render Target node
  }, []);

  // 3. Jump to Environment Settings
  const handleJumpToEnvironment = useCallback(() => {
    console.log('🌅 Jump to Environment Settings');
    // TODO: Select and display Environment node
  }, []);

  // 4. Jump to Current Geometry
  const handleJumpToCurrentGeometry = useCallback(() => {
    console.log('🔷 Jump to Current Geometry');
    // TODO: Select and display current mesh/geometry node
  }, []);

  // 5. Jump to Animation Settings
  const handleJumpToAnimation = useCallback(() => {
    console.log('🎬 Jump to Animation Settings');
    // TODO: Select and display Animation settings node
  }, []);

  // 6. Jump to Active Render Layer
  const handleJumpToActiveLayer = useCallback(() => {
    console.log('🔴 Jump to Active Render Layer');
    // TODO: Select and display active render layer
  }, []);

  // 7. Jump to AOV Group
  const handleJumpToAOVGroup = useCallback(() => {
    console.log('📊 Jump to AOV Group');
    // TODO: Select and display AOV Group node
  }, []);

  // 8. Jump to Post Processing
  const handleJumpToPostProcessing = useCallback(() => {
    console.log('🎨 Jump to Post Processing');
    // TODO: Select and display Post Processing node
  }, []);

  // 9. Collapse All Nodes
  const handleCollapseAll = useCallback(() => {
    console.log('📁 Collapse All Nodes');
    // TODO: Collapse all expanded nodes in the inspector
  }, []);

  // 10. Jump to Camera Settings
  const handleJumpToCamera = useCallback(() => {
    console.log('📷 Jump to Camera Settings');
    // TODO: Select and display Camera node
  }, []);

  // 11. Jump to Visible Environment Settings
  const handleJumpToVisibleEnvironment = useCallback(() => {
    console.log('👁️ Jump to Visible Environment Settings');
    // TODO: Select and display Visible Environment node
  }, []);

  // 12. Jump to Film Settings
  const handleJumpToFilm = useCallback(() => {
    console.log('🎞️ Jump to Film Settings');
    // TODO: Select and display Film Settings node
  }, []);

  // 13. Jump to Current Kernel
  const handleJumpToKernel = useCallback(() => {
    console.log('⚙️ Jump to Current Kernel');
    // TODO: Select and display Current Kernel node
  }, []);

  // 14. Jump to Render AOV Node
  const handleJumpToRenderAOV = useCallback(() => {
    console.log('📈 Jump to Render AOV Node');
    // TODO: Select and display Render AOV node
  }, []);

  // 15. Jump to Camera Imager
  const handleJumpToCameraImager = useCallback(() => {
    console.log('📸 Jump to Camera Imager');
    // TODO: Select and display Camera Imager node
  }, []);

  return (
    <div className="node-inspector-toolbar">
      {/* Button 1: Expand All Nodes */}
      <button
        className="toolbar-button"
        onClick={handleExpandAll}
        title="Expand All Nodes"
      >
        <img src={getNodeInspectorIcon('EXPAND_ALL_NODES')} alt="Expand all" />
      </button>

      {/* Button 2: Render Target */}
      <button
        className="toolbar-button"
        onClick={handleJumpToRenderTarget}
        title="Render Target"
      >
        <img src={getNodeInspectorIcon('RENDER_TARGET')} alt="Render target" />
      </button>

      {/* Button 3: Environment Settings */}
      <button
        className="toolbar-button"
        onClick={handleJumpToEnvironment}
        title="Environment Settings"
      >
        <img src={getNodeInspectorIcon('ENVIRONMENT_SETTINGS')} alt="Environment" />
      </button>

      {/* Button 4: Current Geometry */}
      <button
        className="toolbar-button"
        onClick={handleJumpToCurrentGeometry}
        title="Current Geometry"
      >
        <img src={getNodeInspectorIcon('CURRENT_GEOMETRY')} alt="Current geometry" />
      </button>

      {/* Button 5: Animation Settings */}
      <button
        className="toolbar-button"
        onClick={handleJumpToAnimation}
        title="Animation Settings"
      >
        <img src={getNodeInspectorIcon('ANIMATION_SETTINGS')} alt="Animation" />
      </button>

      {/* Button 6: Active Render Layer */}
      <button
        className="toolbar-button toolbar-button-highlight"
        onClick={handleJumpToActiveLayer}
        title="Active Render Layer"
      >
        <img src={getNodeInspectorIcon('ACTIVE_RENDER_LAYER')} alt="Active render layer" />
      </button>

      {/* Button 7: AOV Group */}
      <button
        className="toolbar-button"
        onClick={handleJumpToAOVGroup}
        title="AOV Group"
      >
        <img src={getNodeInspectorIcon('AOV_GROUP')} alt="AOV group" />
      </button>

      {/* Button 8: Post Processing */}
      <button
        className="toolbar-button"
        onClick={handleJumpToPostProcessing}
        title="Post Processing"
      >
        <img src={getNodeInspectorIcon('POST_PROCESSING')} alt="Post processing" />
      </button>

      {/* Button 9: Collapse All Nodes */}
      <button
        className="toolbar-button"
        onClick={handleCollapseAll}
        title="Collapse All Nodes"
      >
        <img src={getNodeInspectorIcon('COLLAPSE_ALL_NODES')} alt="Collapse all" />
      </button>

      {/* Button 10: Camera Settings */}
      <button
        className="toolbar-button"
        onClick={handleJumpToCamera}
        title="Camera Settings"
      >
        <img src={getNodeInspectorIcon('CAMERA_SETTINGS')} alt="Camera" />
      </button>

      {/* Button 11: Visible Environment Settings */}
      <button
        className="toolbar-button"
        onClick={handleJumpToVisibleEnvironment}
        title="Visible Environment Settings"
      >
        <img src={getNodeInspectorIcon('VISIBLE_ENVIRONMENT_SETTINGS')} alt="Visible environment" />
      </button>

      {/* Button 12: Film Settings */}
      <button
        className="toolbar-button"
        onClick={handleJumpToFilm}
        title="Film Settings"
      >
        <img src={getNodeInspectorIcon('FILM_SETTINGS')} alt="Film settings" />
      </button>

      {/* Button 13: Current Kernel */}
      <button
        className="toolbar-button"
        onClick={handleJumpToKernel}
        title="Current Kernel"
      >
        <img src={getNodeInspectorIcon('CURRENT_KERNEL')} alt="Current kernel" />
      </button>

      {/* Button 14: Render AOV Node */}
      <button
        className="toolbar-button"
        onClick={handleJumpToRenderAOV}
        title="Render AOV Node"
      >
        <img src={getNodeInspectorIcon('RENDER_AOV_NODE')} alt="Render AOV" />
      </button>

      {/* Button 15: Camera Imager */}
      <button
        className="toolbar-button"
        onClick={handleJumpToCameraImager}
        title="Camera Imager"
      >
        <img src={getNodeInspectorIcon('CAMERA_IMAGER')} alt="Camera imager" />
      </button>
    </div>
  );
}
