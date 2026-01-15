/**
 * Menu System Type Definitions
 */

export interface MenuItem {
  type?: 'item' | 'separator';
  label?: string;
  action?: string;
  shortcut?: string;
  icon?: string;
  enabled?: boolean;
  checked?: boolean;  // For toggle menu items (e.g., panel visibility)
  submenu?: MenuItem[];
  data?: any;
}

export interface MenuDefinition {
  [key: string]: MenuItem[];
}

export type MenuAction = 
  | 'file.new'
  | 'file.open'
  | 'file.openRecent'
  | 'file.clearRecent'
  | 'file.save'
  | 'file.saveAs'
  | 'file.saveAsPackage'
  | 'file.saveAsPackageSettings'
  | 'file.unpackPackage'
  | 'file.loadRenderState'
  | 'file.saveRenderState'
  | 'file.saveAsDefault'
  | 'file.preferences'
  | 'edit.undo'
  | 'edit.redo'
  | 'edit.cut'
  | 'edit.copy'
  | 'edit.paste'
  | 'edit.delete'
  | 'edit.selectAll'
  | 'script.batchRender'
  | 'script.daylightAnimation'
  | 'script.turntableAnimation'
  | 'view.renderViewport'
  | 'view.nodeInspector'
  | 'view.graphEditor'
  | 'view.sceneOutliner'
  | 'view.refresh'
  | 'window.materialDatabase'
  | 'window.resetLayout'
  | 'window.fullscreen'
  | 'help.docs'
  | 'help.shortcuts'
  | 'help.bug'
  | 'help.about';

export interface MenuActionHandler {
  (action: MenuAction, data?: any): void | Promise<void>;
}
