/**
 * Menu Definitions
 * Defines all menu items and their structure
 */

import { MenuDefinition, MenuItem } from '../types/menu';
import { getMenuIcon } from '../utils/MenuIconMapping';

interface PanelVisibility {
  renderViewport: boolean;
  nodeInspector: boolean;
  graphEditor: boolean;
  sceneOutliner: boolean;
}

export function getMenuDefinitions(recentFiles: string[] = [], panelVisibility?: PanelVisibility): MenuDefinition {
  // Build recent files submenu
  const recentFilesSubmenu: MenuItem[] = recentFiles.length > 0
    ? [
        ...recentFiles.map(path => ({
          label: path.split(/[\\\/]/).pop() || path,
          action: 'file.openRecent',
          data: path
        })),
        { type: 'separator' as const },
        { label: 'Clear Recent', action: 'file.clearRecent' }
      ]
    : [
        { label: '(No recent files)', enabled: false }
      ];

  return {
    file: [
      { label: 'New', action: 'file.new', shortcut: 'Ctrl+N' },
      { label: 'Open...', action: 'file.open', shortcut: 'Ctrl+O' },
      {
        label: 'Recent projects',
        action: 'file.recent',
        submenu: recentFilesSubmenu
      },
      { type: 'separator' },
      { label: 'Save', action: 'file.save', shortcut: 'Ctrl+S' },
      { label: 'Save as...', action: 'file.saveAs', shortcut: 'Ctrl+Shift+S' },
      { label: 'Save as package...', action: 'file.saveAsPackage' },
      { label: 'Save as package settings...', action: 'file.saveAsPackageSettings' },
      { label: 'Unpack package...', action: 'file.unpackPackage' },
      { type: 'separator' },
      { label: 'Load render state...', action: 'file.loadRenderState' },
      { label: 'Save render state...', action: 'file.saveRenderState' },
      { type: 'separator' },
      { label: 'Save as default', action: 'file.saveAsDefault' },
      { type: 'separator' },
      { label: 'Preferences...', action: 'file.preferences', shortcut: 'Ctrl+,' },
      { type: 'separator' },
      { label: 'Activation status...', action: 'file.activationStatus' },
      { type: 'separator' },
      { label: 'Quit', action: 'file.quit', shortcut: 'Ctrl+Q' }
    ],
    edit: [
      { label: 'Undo', action: 'edit.undo', shortcut: 'Ctrl+Z', icon: getMenuIcon('edit.undo') },
      { label: 'Redo', action: 'edit.redo', shortcut: 'Ctrl+Y', icon: getMenuIcon('edit.redo') },
      { type: 'separator' },
      { label: 'Cut', action: 'edit.cut', shortcut: 'Ctrl+X' },
      { label: 'Copy', action: 'edit.copy', shortcut: 'Ctrl+C', icon: getMenuIcon('edit.copy') },
      { label: 'Paste', action: 'edit.paste', shortcut: 'Ctrl+V' },
      { label: 'Delete', action: 'edit.delete', shortcut: 'Del' },
      { type: 'separator' },
      { label: 'Select All', action: 'edit.selectAll', shortcut: 'Ctrl+A' }
    ],
    render: [
      { label: 'Upload scene snapshot', action: 'render.uploadSnapshot' },
      { label: 'Render', action: 'render.render' },
      { label: 'Open Render Network...', action: 'render.openRenderNetwork' },
      { label: 'Open Render Network (external)...', action: 'render.openRenderNetworkExternal' }
    ],
    script: [
      { label: 'Batch Rendering...', action: 'script.batchRender', icon: getMenuIcon('script.batchRender') },
      { label: 'Daylight Animation...', action: 'script.daylightAnimation', icon: getMenuIcon('script.daylightAnimation') },
      { label: 'Turntable Animation...', action: 'script.turntableAnimation', icon: getMenuIcon('script.turntableAnimation') }
    ],
    view: [
      { 
        label: 'Render Viewport', 
        action: 'view.renderViewport', 
        icon: getMenuIcon('view.renderViewport'),
        checked: panelVisibility?.renderViewport ?? true
      },
      { 
        label: 'Node Inspector', 
        action: 'view.nodeInspector', 
        icon: getMenuIcon('view.nodeInspector'),
        checked: panelVisibility?.nodeInspector ?? true
      },
      { 
        label: 'Graph Editor', 
        action: 'view.graphEditor', 
        icon: getMenuIcon('view.graphEditor'),
        checked: panelVisibility?.graphEditor ?? true
      },
      { 
        label: 'Scene Outliner', 
        action: 'view.sceneOutliner', 
        icon: getMenuIcon('view.sceneOutliner'),
        checked: panelVisibility?.sceneOutliner ?? true
      },
      { type: 'separator' },
      { label: 'Refresh Scene', action: 'view.refresh', shortcut: 'F5', icon: getMenuIcon('view.refresh') }
    ],
    window: [
      { label: 'Reset workspace', action: 'window.resetWorkspace' },
      { label: 'Save workspace layout...', action: 'window.saveWorkspaceLayout' },
      { label: 'Load workspace layout...', action: 'window.loadWorkspaceLayout' },
      { label: 'Rescan layout folder', action: 'window.rescanLayoutFolder' },
      { label: 'Save as default layout', action: 'window.saveAsDefaultLayout' },
      { label: 'Load default layout', action: 'window.loadDefaultLayout' },
      { type: 'separator' },
      { label: 'Create log window', action: 'window.createLogWindow' },
      { label: 'Create graph editor', action: 'window.createGraphEditor' },
      { label: 'Create scene viewport', action: 'window.createSceneViewport' },
      { label: 'Create scene outliner', action: 'window.createSceneOutliner' },
      { type: 'separator' },
      { label: 'Create scene graph export', action: 'window.createSceneGraphExport' },
      { type: 'separator' },
      { label: 'Create script editor', action: 'window.createScriptEditor' },
      { label: 'Create OSL editor', action: 'window.createOSLEditor', icon: getMenuIcon('window.createOSLEditor') },
      { label: 'Create Lua API browser', action: 'window.createLuaAPIBrowser' },
      { label: 'Create USD stage editor', action: 'window.createUSDStageEditor' }
    ],
    help: [
      { label: 'Documentation', action: 'help.docs', shortcut: 'F1', icon: getMenuIcon('help.docs') },
      { label: 'Keyboard Shortcuts', action: 'help.shortcuts' },
      { type: 'separator' },
      { label: 'Report Bug', action: 'help.bug' },
      { label: 'About OctaneWebR', action: 'help.about' }
    ]
  };
}
