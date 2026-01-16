/**
 * MenuBar Component
 * Main application menu bar with dropdowns and file operations
 */

import React, { useState, useCallback, useEffect, useRef, useMemo } from 'react';
import { useFileDialog } from '../hooks/useFileDialog';
import { useRecentFiles } from '../hooks/useRecentFiles';
import { useOctane } from '../hooks/useOctane';
import { useKeyboardShortcuts } from '../hooks/useKeyboardShortcuts';
import { MenuDropdown } from './MenuDropdown';
import { KeyboardShortcutsDialog } from './KeyboardShortcutsDialog';
import { PreferencesDialog } from './PreferencesDialog';
import { BatchRenderingDialog } from './BatchRenderingDialog';
import { DaylightAnimationDialog } from './DaylightAnimationDialog';
import { TurntableAnimationDialog } from './TurntableAnimationDialog';
import { AboutDialog } from './AboutDialog';
import { SavePackageDialog } from './SavePackageDialog';
import { getMenuDefinitions } from '../config/menuDefinitions';
import { MenuAction } from '../types/menu';
import { commandHistory } from '../services/CommandHistory';

interface PanelVisibility {
  renderViewport: boolean;
  nodeInspector: boolean;
  graphEditor: boolean;
  sceneOutliner: boolean;
}

interface MenuBarProps {
  onSceneRefresh?: () => void;
  onMaterialDatabaseOpen?: () => void;
  panelVisibility?: PanelVisibility;
  onTogglePanelVisibility?: (panel: 'renderViewport' | 'nodeInspector' | 'graphEditor' | 'sceneOutliner') => void;
  onResetLayout?: () => void;
}

function MenuBar({ onSceneRefresh, onMaterialDatabaseOpen, panelVisibility, onTogglePanelVisibility, onResetLayout }: MenuBarProps) {
  const [activeMenu, setActiveMenu] = useState<string | null>(null);
  const [activeMenuAnchor, setActiveMenuAnchor] = useState<HTMLElement | null>(null);
  const [isShortcutsDialogOpen, setIsShortcutsDialogOpen] = useState(false);
  const [isPreferencesDialogOpen, setIsPreferencesDialogOpen] = useState(false);
  const [isBatchRenderingDialogOpen, setIsBatchRenderingDialogOpen] = useState(false);
  const [isDaylightAnimationDialogOpen, setIsDaylightAnimationDialogOpen] = useState(false);
  const [isTurntableAnimationDialogOpen, setIsTurntableAnimationDialogOpen] = useState(false);
  const [isAboutDialogOpen, setIsAboutDialogOpen] = useState(false);
  const [isSavePackageDialogOpen, setIsSavePackageDialogOpen] = useState(false);
  const menuBarRef = useRef<HTMLDivElement>(null);

  const { openFileDialog } = useFileDialog();
  const { recentFiles, addRecentFile, clearRecentFiles, getRecentFilePaths } = useRecentFiles();
  const { client, connected } = useOctane();

  // Get menu definitions with current recent files and panel visibility
  const menuDefinitions = useMemo(() => {
    return getMenuDefinitions(getRecentFilePaths(), panelVisibility);
  }, [recentFiles, getRecentFilePaths, panelVisibility]);

  // Close menu when clicking outside
  useEffect(() => {
    const handleClickOutside = (e: MouseEvent) => {
      if (menuBarRef.current && !menuBarRef.current.contains(e.target as Node)) {
        setActiveMenu(null);
        setActiveMenuAnchor(null);
      }
    };

    if (activeMenu) {
      document.addEventListener('mousedown', handleClickOutside);
      return () => document.removeEventListener('mousedown', handleClickOutside);
    }
  }, [activeMenu]);

  const handleMenuClick = useCallback((menuName: string, element: HTMLElement) => {
    if (activeMenu === menuName) {
      setActiveMenu(null);
      setActiveMenuAnchor(null);
    } else {
      setActiveMenu(menuName);
      setActiveMenuAnchor(element);
    }
  }, [activeMenu]);

  const handleMenuMouseEnter = useCallback((menuName: string, element: HTMLElement) => {
    if (activeMenu !== null) {
      setActiveMenu(menuName);
      setActiveMenuAnchor(element);
    }
  }, [activeMenu]);

  const closeMenu = useCallback(() => {
    setActiveMenu(null);
    setActiveMenuAnchor(null);
  }, []);

  const showNotification = useCallback((message: string, type: 'success' | 'error' | 'info' = 'info') => {
    console.log(`[${type.toUpperCase()}] ${message}`);
    // TODO: Implement toast notification system
  }, []);

  const showWarnNotConnected = useCallback((action: string) => {
    showNotification(`Cannot ${action}: Not connected to Octane`, 'error');
  }, [showNotification]);

  // Menu action handlers
  const handleMenuAction = useCallback(async (action: MenuAction, data?: any) => {
    console.log('🎯 Menu action:', action, data);
    closeMenu();

    switch (action) {
      // File menu actions
      case 'file.new':
        if (!connected) {
          showWarnNotConnected('create new scene');
          return;
        }
        try {
          const response = await client.callApi('ApiProjectManager', 'resetProject', {});
          if (response) {
            showNotification('New scene created', 'success');
            onSceneRefresh?.();
          }
        } catch (error) {
          console.error('Failed to create new scene:', error);
          showNotification('Failed to create new scene', 'error');
        }
        break;

      case 'file.open':
        {
          const files = await openFileDialog({
            accept: '.orbx',
            multiple: false
          });
          if (files && files.length > 0) {
            const file = files[0];
            console.log('Opening scene file:', file.name);
            
            if (!connected) {
              showWarnNotConnected('open scene');
              return;
            }

            try {
              // TODO: Implement scene file loading via Octane API
              // This requires reading the file and sending it to Octane
              const response = await client.callApi('ApiProjectManager', 'loadProject', {
                path: file.name
              });
              
              if (response) {
                addRecentFile(file.name);
                showNotification(`Loaded: ${file.name}`, 'success');
                onSceneRefresh?.();
              }
            } catch (error) {
              console.error('Failed to open scene:', error);
              showNotification(`Failed to open ${file.name}`, 'error');
            }
          }
        }
        break;

      case 'file.openRecent':
        if (data) {
          console.log('Opening recent file:', data);
          if (!connected) {
            showWarnNotConnected('open recent file');
            return;
          }
          try {
            const response = await client.callApi('ApiProjectManager', 'loadProject', {
              path: data
            });
            if (response) {
              showNotification(`Loaded: ${data}`, 'success');
              onSceneRefresh?.();
            }
          } catch (error) {
            console.error('Failed to open recent file:', error);
            showNotification(`Failed to open ${data}`, 'error');
          }
        }
        break;

      case 'file.clearRecent':
        clearRecentFiles();
        showNotification('Recent files cleared', 'success');
        break;

      case 'file.save':
        if (!connected) {
          showWarnNotConnected('save scene');
          return;
        }
        try {
          const response = await client.callApi('ApiProjectManager', 'saveProject', {});
          if (response) {
            showNotification('Scene saved', 'success');
          }
        } catch (error) {
          console.error('Failed to save scene:', error);
          showNotification('Failed to save scene', 'error');
        }
        break;

      case 'file.saveAs':
        {
          const files = await openFileDialog({
            accept: '.orbx',
            multiple: false
          });
          if (files && files.length > 0) {
            const filename = files[0].name;
            if (!connected) {
              showWarnNotConnected('save scene');
              return;
            }
            try {
              const response = await client.callApi('ApiProjectManager', 'saveProjectAs', {
                path: filename
              });
              if (response) {
                addRecentFile(filename);
                showNotification(`Saved as: ${filename}`, 'success');
              }
            } catch (error) {
              console.error('Failed to save scene as:', error);
              showNotification(`Failed to save as ${filename}`, 'error');
            }
          }
        }
        break;

      case 'file.saveAsPackage':
        setIsSavePackageDialogOpen(true);
        console.log('📦 Opening Save as Package dialog');
        break;

      case 'file.saveAsDefault':
        if (!connected) {
          showWarnNotConnected('save default scene');
          return;
        }
        try {
          // Save current scene as default startup scene
          const defaultScenePath = 'default.ocs';
          const response = await client.callApi('ApiProjectManager', 'saveProjectAs', {
            path: defaultScenePath
          });
          if (response && response.result) {
            // Store the default scene path in localStorage for future reference
            localStorage.setItem('octaneWebR_defaultScene', defaultScenePath);
            showNotification('Current scene saved as default', 'success');
            console.log('✅ Default scene saved:', defaultScenePath);
          } else {
            showNotification('Failed to save default scene', 'error');
          }
        } catch (error) {
          console.error('Failed to save default scene:', error);
          showNotification('Failed to save default scene', 'error');
        }
        break;

      case 'file.preferences':
        setIsPreferencesDialogOpen(true);
        console.log('🔧 Opening Preferences dialog');
        break;

      // Edit menu actions
      case 'edit.undo':
        try {
          const undoDescription = commandHistory.getUndoDescription();
          const success = await commandHistory.undo();
          if (success) {
            showNotification(`Undone: ${undoDescription}`, 'success');
            console.log('↶ Undo successful');
          } else {
            showNotification('Nothing to undo', 'info');
          }
        } catch (error) {
          console.error('Undo failed:', error);
          showNotification('Undo failed', 'error');
        }
        break;

      case 'edit.redo':
        try {
          const redoDescription = commandHistory.getRedoDescription();
          const success = await commandHistory.redo();
          if (success) {
            showNotification(`Redone: ${redoDescription}`, 'success');
            console.log('↷ Redo successful');
          } else {
            showNotification('Nothing to redo', 'info');
          }
        } catch (error) {
          console.error('Redo failed:', error);
          showNotification('Redo failed', 'error');
        }
        break;

      // Script menu actions
      case 'script.batchRender':
        setIsBatchRenderingDialogOpen(true);
        console.log('🎬 Opening Batch Rendering dialog');
        break;

      case 'script.daylightAnimation':
        setIsDaylightAnimationDialogOpen(true);
        console.log('☀️ Opening Daylight Animation dialog');
        break;

      case 'script.turntableAnimation':
        setIsTurntableAnimationDialogOpen(true);
        console.log('🔄 Opening Turntable Animation dialog');
        break;

      // View menu actions
      case 'view.renderViewport':
        onTogglePanelVisibility?.('renderViewport');
        console.log('👁️ Toggled Render Viewport visibility');
        break;
      
      case 'view.nodeInspector':
        onTogglePanelVisibility?.('nodeInspector');
        console.log('👁️ Toggled Node Inspector visibility');
        break;
      
      case 'view.graphEditor':
        onTogglePanelVisibility?.('graphEditor');
        console.log('👁️ Toggled Graph Editor visibility');
        break;
      
      case 'view.sceneOutliner':
        onTogglePanelVisibility?.('sceneOutliner');
        console.log('👁️ Toggled Scene Outliner visibility');
        break;

      // Window menu actions
      case 'window.resetWorkspace':
        onResetLayout?.();
        showNotification('Workspace reset to defaults', 'success');
        break;

      case 'view.refresh':
        onSceneRefresh?.();
        showNotification('Scene refreshed', 'success');
        break;

      // Help menu actions
      case 'help.shortcuts':
        setIsShortcutsDialogOpen(true);
        break;

      case 'help.docs':
        window.open('https://docs.otoy.com/standaloneSE/CoverPage.html', '_blank');
        break;

      case 'help.bug':
        window.open('https://github.com/ultrafish22L/grpcSamples/issues/new', '_blank');
        console.log('🐛 Opening GitHub issues for bug report');
        break;

      case 'help.about':
        setIsAboutDialogOpen(true);
        console.log('ℹ️ Opening About dialog');
        break;

      default:
        console.warn('Menu action not yet implemented:', action);
        showNotification(`Action "${action}" not yet implemented`, 'info');
    }
  }, [
    client,
    connected,
    openFileDialog,
    addRecentFile,
    clearRecentFiles,
    showWarnNotConnected,
    showNotification,
    closeMenu,
    onSceneRefresh,
    onMaterialDatabaseOpen,
    onTogglePanelVisibility,
    onResetLayout
  ]);

  // Global keyboard shortcuts for file and edit operations
  const keyboardShortcuts = useMemo(() => [
    {
      key: 'n',
      ctrl: true,
      description: 'New scene',
      handler: () => handleMenuAction('file.new')
    },
    {
      key: 'o',
      ctrl: true,
      description: 'Open scene',
      handler: () => handleMenuAction('file.open')
    },
    {
      key: 's',
      ctrl: true,
      description: 'Save scene',
      handler: () => handleMenuAction('file.save')
    },
    {
      key: 's',
      ctrl: true,
      shift: true,
      description: 'Save scene as',
      handler: () => handleMenuAction('file.saveAs')
    },
    {
      key: ',',
      ctrl: true,
      description: 'Open preferences',
      handler: () => handleMenuAction('file.preferences')
    },
    {
      key: 'z',
      ctrl: true,
      description: 'Undo',
      handler: () => handleMenuAction('edit.undo')
    },
    {
      key: 'y',
      ctrl: true,
      description: 'Redo',
      handler: () => handleMenuAction('edit.redo')
    },
    {
      key: 'F5',
      description: 'Refresh scene',
      handler: () => handleMenuAction('view.refresh')
    },
    {
      key: 'F1',
      description: 'Open documentation',
      handler: () => handleMenuAction('help.docs')
    },
    {
      key: 'F11',
      description: 'Toggle fullscreen',
      handler: () => {
        if (!document.fullscreenElement) {
          document.documentElement.requestFullscreen().catch(err => {
            console.error('Failed to enter fullscreen:', err);
          });
        } else {
          document.exitFullscreen();
        }
      }
    }
  ], [handleMenuAction]);

  // Register keyboard shortcuts
  useKeyboardShortcuts(keyboardShortcuts);

  const menuItems = ['file', 'edit', 'render', 'script', 'view', 'window', 'help'];

  return (
    <nav ref={menuBarRef} className="main-menu">
      {menuItems.map(menuName => (
        <div
          key={menuName}
          className={`menu-item ${activeMenu === menuName ? 'active' : ''}`}
          data-menu={menuName}
          onClick={(e) => handleMenuClick(menuName, e.currentTarget)}
          onMouseEnter={(e) => handleMenuMouseEnter(menuName, e.currentTarget)}
        >
          {menuName.charAt(0).toUpperCase() + menuName.slice(1)}
        </div>
      ))}

      {/* Render active dropdown */}
      {activeMenu && activeMenuAnchor && menuDefinitions[activeMenu] && (
        <MenuDropdown
          items={menuDefinitions[activeMenu]}
          anchorElement={activeMenuAnchor}
          onItemClick={handleMenuAction}
          onClose={closeMenu}
        />
      )}

      {/* Keyboard Shortcuts Dialog */}
      <KeyboardShortcutsDialog
        isOpen={isShortcutsDialogOpen}
        onClose={() => setIsShortcutsDialogOpen(false)}
      />

      {/* Preferences Dialog */}
      <PreferencesDialog
        isOpen={isPreferencesDialogOpen}
        onClose={() => setIsPreferencesDialogOpen(false)}
      />

      {/* Batch Rendering Dialog */}
      <BatchRenderingDialog
        isOpen={isBatchRenderingDialogOpen}
        onClose={() => setIsBatchRenderingDialogOpen(false)}
      />

      {/* Daylight Animation Dialog */}
      <DaylightAnimationDialog
        isOpen={isDaylightAnimationDialogOpen}
        onClose={() => setIsDaylightAnimationDialogOpen(false)}
      />

      {/* Turntable Animation Dialog */}
      <TurntableAnimationDialog
        isOpen={isTurntableAnimationDialogOpen}
        onClose={() => setIsTurntableAnimationDialogOpen(false)}
      />

      {/* About Dialog */}
      <AboutDialog
        isOpen={isAboutDialogOpen}
        onClose={() => setIsAboutDialogOpen(false)}
      />

      {/* Save Package Dialog */}
      <SavePackageDialog
        isOpen={isSavePackageDialogOpen}
        onClose={() => setIsSavePackageDialogOpen(false)}
      />
    </nav>
  );
}

export const MenuBarMemoized = React.memo(MenuBar);
export { MenuBarMemoized as MenuBar };
