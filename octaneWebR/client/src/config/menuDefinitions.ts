/**
 * Menu Definitions
 * Defines all menu items and their structure
 */

import { MenuDefinition, MenuItem } from '../types/menu';

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
      { label: 'Preferences...', action: 'file.preferences', shortcut: 'Ctrl+,' }
    ],
    edit: [
      { label: 'Undo', action: 'edit.undo', shortcut: 'Ctrl+Z', icon: '↶' },
      { label: 'Redo', action: 'edit.redo', shortcut: 'Ctrl+Y', icon: '↷' },
      { type: 'separator' },
      { label: 'Cut', action: 'edit.cut', shortcut: 'Ctrl+X', icon: '✂️' },
      { label: 'Copy', action: 'edit.copy', shortcut: 'Ctrl+C', icon: '📋' },
      { label: 'Paste', action: 'edit.paste', shortcut: 'Ctrl+V', icon: '📄' },
      { label: 'Delete', action: 'edit.delete', shortcut: 'Del', icon: '🗑️' },
      { type: 'separator' },
      { label: 'Select All', action: 'edit.selectAll', shortcut: 'Ctrl+A', icon: '☑️' }
    ],
    script: [
      { label: 'Batch Rendering...', action: 'script.batchRender', icon: '🎬' },
      { label: 'Daylight Animation...', action: 'script.daylightAnimation', icon: '☀️' },
      { label: 'Turntable Animation...', action: 'script.turntableAnimation', icon: '🔄' }
    ],
    view: [
      { 
        label: 'Render Viewport', 
        action: 'view.renderViewport', 
        icon: '🖼️',
        checked: panelVisibility?.renderViewport ?? true
      },
      { 
        label: 'Node Inspector', 
        action: 'view.nodeInspector', 
        icon: '🔍',
        checked: panelVisibility?.nodeInspector ?? true
      },
      { 
        label: 'Graph Editor', 
        action: 'view.graphEditor', 
        icon: '🕸️',
        checked: panelVisibility?.graphEditor ?? true
      },
      { 
        label: 'Scene Outliner', 
        action: 'view.sceneOutliner', 
        icon: '🌳',
        checked: panelVisibility?.sceneOutliner ?? true
      },
      { type: 'separator' },
      { label: 'Refresh Scene', action: 'view.refresh', shortcut: 'F5', icon: '🔄' }
    ],
    window: [
      { label: 'Material Database', action: 'window.materialDatabase', icon: '💎' },
      { type: 'separator' },
      { label: 'Reset Layout', action: 'window.resetLayout', icon: '↺' },
      { label: 'Fullscreen', action: 'window.fullscreen', shortcut: 'F11', icon: '⛶' }
    ],
    help: [
      { label: 'Documentation', action: 'help.docs', shortcut: 'F1', icon: '📚' },
      { label: 'Keyboard Shortcuts', action: 'help.shortcuts', icon: '⌨️' },
      { type: 'separator' },
      { label: 'Report Bug', action: 'help.bug', icon: '🐛' },
      { label: 'About OctaneWebR', action: 'help.about', icon: 'ℹ️' }
    ]
  };
}
