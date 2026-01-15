/**
 * MenuBar Component
 * Main application menu bar with dropdowns and file operations
 */

import { useState, useCallback, useEffect, useRef, useMemo } from 'react';
import { useFileDialog } from '../hooks/useFileDialog';
import { useRecentFiles } from '../hooks/useRecentFiles';
import { useOctane } from '../hooks/useOctane';
import { useKeyboardShortcuts } from '../hooks/useKeyboardShortcuts';
import { MenuDropdown } from './MenuDropdown';
import { KeyboardShortcutsDialog } from './KeyboardShortcutsDialog';
import { getMenuDefinitions } from '../config/menuDefinitions';
import { MenuAction } from '../types/menu';

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

export function MenuBar({ onSceneRefresh, onMaterialDatabaseOpen, panelVisibility, onTogglePanelVisibility, onResetLayout }: MenuBarProps) {
  const [activeMenu, setActiveMenu] = useState<string | null>(null);
  const [activeMenuAnchor, setActiveMenuAnchor] = useState<HTMLElement | null>(null);
  const [isShortcutsDialogOpen, setIsShortcutsDialogOpen] = useState(false);
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

      // Edit menu actions
      case 'edit.undo':
        console.log('Undo not yet implemented');
        showNotification('Undo not yet implemented', 'info');
        break;

      case 'edit.redo':
        console.log('Redo not yet implemented');
        showNotification('Redo not yet implemented', 'info');
        break;

      // Script menu actions
      case 'script.batchRender':
        console.log('Batch Rendering not yet implemented');
        showNotification('Batch Rendering dialog coming soon', 'info');
        break;

      case 'script.daylightAnimation':
        console.log('Daylight Animation not yet implemented');
        showNotification('Daylight Animation dialog coming soon', 'info');
        break;

      case 'script.turntableAnimation':
        console.log('Turntable Animation not yet implemented');
        showNotification('Turntable Animation dialog coming soon', 'info');
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
      case 'window.materialDatabase':
        onMaterialDatabaseOpen?.();
        break;

      case 'window.resetLayout':
        onResetLayout?.();
        showNotification('Layout reset to defaults', 'success');
        break;

      case 'window.fullscreen':
        if (document.fullscreenElement) {
          document.exitFullscreen();
        } else {
          document.documentElement.requestFullscreen();
        }
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

      case 'help.about':
        alert('OctaneWebR - React + TypeScript port of octaneWeb\n\nA browser-based interface for OTOY Octane Render via LiveLink gRPC API');
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

  // Global keyboard shortcuts for file operations
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
    }
  ], [handleMenuAction]);

  // Register keyboard shortcuts
  useKeyboardShortcuts(keyboardShortcuts);

  const menuItems = ['file', 'edit', 'script', 'view', 'window', 'help'];

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
    </nav>
  );
}
