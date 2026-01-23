/**
 * Menu Icon Mapping
 * Maps menu actions to Octane icons
 * 
 * Used by menuDefinitions.ts to provide proper icons for all menu items
 */

import { getEditorPanelIcon, getWindowControlIcon, getGeneralUIIcon, getPickerToolIcon } from './UIIconMapping';

/**
 * Get icon for a menu action
 * Returns the icon path or undefined if no icon is mapped
 */
export function getMenuIcon(action: string): string | undefined {
  const iconMap: Record<string, string> = {
    // Edit menu
    'edit.undo': getGeneralUIIcon('LOAD_GENERAL'), // Using LOAD as placeholder for undo
    'edit.redo': getGeneralUIIcon('LOAD_GENERAL'), // Using LOAD as placeholder for redo
    'edit.copy': getGeneralUIIcon('COPY_TO_CLIPBOARD_TEXT'),
    
    // Script menu
    'script.batchRender': getWindowControlIcon('PLAY'),
    'script.daylightAnimation': getWindowControlIcon('PLAY'),
    'script.turntableAnimation': getWindowControlIcon('PLAY'),
    
    // View menu - Editor panels
    'view.renderViewport': getEditorPanelIcon('GRAPH_EDITOR'),  // Using graph as viewport placeholder
    'view.nodeInspector': getEditorPanelIcon('NODE_INSPECTOR'),
    'view.graphEditor': getEditorPanelIcon('GRAPH_EDITOR'),
    'view.sceneOutliner': getEditorPanelIcon('OUTLINER'),
    'view.refresh': getWindowControlIcon('RECENTER'),  // Recenter as refresh
    
    // Window menu
    'window.createOSLEditor': getEditorPanelIcon('OSL_EDITOR'),
    
    // Help menu  
    'help.docs': getGeneralUIIcon('LOAD_GENERAL'),
  };
  
  return iconMap[action];
}

/**
 * Menu actions that should display checkmarks
 */
export const CHECKABLE_MENU_ACTIONS = new Set([
  'view.renderViewport',
  'view.nodeInspector', 
  'view.graphEditor',
  'view.sceneOutliner',
]);

/**
 * Menu actions that are separator lines
 */
export function isMenuSeparator(item: any): boolean {
  return item.type === 'separator';
}
