/**
 * Node Inspector Toolbar Icon Mapping
 * Maps Node Inspector quick access buttons to Octane UI icon files
 * Based on Octane SE Manual Figure 2: Quick access buttons in the Node Inspector
 * https://docs.otoy.com/standaloneSE/TheNodeInspector.html
 * 
 * These buttons allow the user to quickly jump to the most commonly used nodes:
 * RenderTarget, Camera, Resolution, Environment, Imager, Kernel, and Current Mesh
 */

export interface NodeInspectorIconMapping {
  [buttonId: string]: string;
}

/**
 * Node Inspector Toolbar Icon Mappings
 * Based on Figure 2 from the Octane SE Manual
 * 
 * Button order from manual (can be displayed vertically or horizontally):
 * 1. Expand All Nodes
 * 2. Render Target
 * 3. Environment Settings
 * 4. Current Geometry
 * 5. Animation Settings
 * 6. Active Render Layer (RED icon)
 * 7. AOV Group
 * 8. Post Processing
 * 9. Collapse All nodes
 * 10. Camera Settings
 * 11. Visible Environment Settings
 * 12. Film Settings
 * 13. Current Kernel
 * 14. Render AOV Node
 * 15. Camera Imager
 */
export const NODE_INSPECTOR_ICON_MAP: NodeInspectorIconMapping = {
  // Quick Access Buttons
  'expand-all-nodes': 'UNCOLLAPSE NODES window.png',
  'render-target': 'RENDER TARGET node.png',
  'environment-settings': 'ENVIRONMENT node.png',
  'current-geometry': 'MESH node.png',
  'animation-settings': 'ANIMATION node.png',
  'active-render-layer': 'render_layer.png',
  'aov-group': 'AOV node.png',
  'post-processing': 'POST node.png',
  'collapse-all-nodes': 'COLLAPSE NODES window.png',
  'camera-settings': 'CAMERA node.png',
  'visible-environment-settings': 'VISIBLE ENVIRONMENT node.png',
  'film-settings': 'FILM node.png',
  'current-kernel': 'RENDER KERNEL node.png',
  'render-aov-node': 'AOV node.png',
  'camera-imager': 'IMAGER node.png',
};

/**
 * Get icon path for a Node Inspector toolbar button
 * @param buttonId Node Inspector button ID
 * @returns path to icon file, or undefined if no mapping exists
 */
export function getNodeInspectorIconPath(buttonId: string): string | undefined {
  const iconFile = NODE_INSPECTOR_ICON_MAP[buttonId];
  if (iconFile) {
    return `/icons/${iconFile}`;
  }
  return undefined;
}

/**
 * Check if a Node Inspector button has an icon mapping
 */
export function hasNodeInspectorIcon(buttonId: string): boolean {
  return buttonId in NODE_INSPECTOR_ICON_MAP;
}

/**
 * Get all Node Inspector button IDs
 */
export function getNodeInspectorButtonIds(): string[] {
  return Object.keys(NODE_INSPECTOR_ICON_MAP);
}
