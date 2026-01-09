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
  | 'file.activationStatus'
  | 'file.quit'
  | 'edit.undo'
  | 'edit.redo'
  | 'edit.cut'
  | 'edit.copy'
  | 'edit.paste'
  | 'edit.delete'
  | 'edit.selectAll'
  | 'script.run'
  | 'script.editor'
  | 'script.reload'
  | 'module.manager'
  | 'module.install'
  | 'module.refresh'
  | 'cloud.render'
  | 'cloud.account'
  | 'cloud.upload'
  | 'cloud.download'
  | 'window.sceneOutliner'
  | 'window.nodeInspector'
  | 'window.nodeGraph'
  | 'window.resetLayout'
  | 'window.fullscreen'
  | 'view.refresh'
  | 'help.docs'
  | 'help.shortcuts'
  | 'help.bug'
  | 'help.about';

export interface MenuActionHandler {
  (action: MenuAction, data?: any): void | Promise<void>;
}
