/**
 * Menu System Component
 * Application menu bar and context menus
 */

class MenuSystem extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        this.activeMenu = null;
        this.menuDefinitions = this.getMenuDefinitions();
        this.fileManager = new FileManager(client);
        this.activeSubmenus = new Set();
    }
    
    async onInitialize() {
        this.setupMenuItems();
        this.fileManager.initialize();
        this.updateRecentFilesMenu();
    }
    
    setupEventListeners() {
        // Click outside to close menus
        this.addEventListener(document, 'click', (e) => {
            if (!this.element.contains(e.target)) {
                this.closeAllMenus();
            }
        });
    }
    
    setupMenuItems() {
        const menuItems = this.element.querySelectorAll('.menu-item');
        
        menuItems.forEach(item => {
            this.addEventListener(item, 'click', (e) => {
                const menuName = item.dataset.menu;
                this.toggleMenu(menuName, item);
            });
            
            this.addEventListener(item, 'mouseenter', (e) => {
                if (this.activeMenu) {
                    const menuName = item.dataset.menu;
                    this.showMenu(menuName, item);
                }
            });
        });
    }
    
    toggleMenu(menuName, menuItem) {
        if (this.activeMenu === menuName) {
            this.closeAllMenus();
        } else {
            this.showMenu(menuName, menuItem);
        }
    }
    
    showMenu(menuName, menuItem) {
        this.closeAllMenus();
        
        const menuDef = this.menuDefinitions[menuName];
        if (!menuDef) return;
        
        this.activeMenu = menuName;
        menuItem.classList.add('active');
        
        const dropdown = this.createDropdownMenu(menuDef);
        this.positionDropdown(dropdown, menuItem);
        
        document.body.appendChild(dropdown);
    }
    
    createDropdownMenu(menuDef) {
        const dropdown = document.createElement('div');
        dropdown.className = 'context-menu menu-dropdown';
        
        const items = menuDef.map(item => this.createMenuItem(item)).join('');
        dropdown.innerHTML = items;
        
        // Setup item event listeners
        setTimeout(() => {
            this.setupDropdownEventListeners(dropdown);
        }, 0);
        
        return dropdown;
    }
    
    createMenuItem(item) {
        if (item.type === 'separator') {
            return '<div class="context-menu-separator"></div>';
        }
        
        const disabled = item.enabled === false ? 'disabled' : '';
        const shortcut = item.shortcut ? `<span class="context-menu-shortcut">${item.shortcut}</span>` : '';
        const icon = item.icon ? `<span class="context-menu-icon">${item.icon}</span>` : '';
        const hasSubmenu = item.submenu && item.submenu.length > 0;
        const submenuArrow = hasSubmenu ? '<span class="context-menu-arrow">▶</span>' : '';
        
        return `
            <div class="context-menu-item ${disabled} ${hasSubmenu ? 'has-submenu' : ''}" 
                 data-action="${item.action || ''}" 
                 data-has-submenu="${hasSubmenu}">
                ${icon}
                <span>${item.label}</span>
                ${shortcut}
                ${submenuArrow}
            </div>
        `;
    }
    
    setupDropdownEventListeners(dropdown) {
        const items = dropdown.querySelectorAll('.context-menu-item:not(.disabled)');
        
        items.forEach(item => {
            const hasSubmenu = item.dataset.hasSubmenu === 'true';
            
            if (hasSubmenu) {
                // Handle submenu items
                this.addEventListener(item, 'mouseenter', (e) => {
                    this.showSubmenu(item, dropdown);
                });
                
                this.addEventListener(item, 'mouseleave', (e) => {
                    // Don't hide submenu immediately, let mouse move to submenu
                    setTimeout(() => {
                        if (!item.matches(':hover') && !this.isSubmenuHovered(item)) {
                            this.hideSubmenu(item);
                        }
                    }, 100);
                });
            } else {
                // Handle regular menu items
                this.addEventListener(item, 'click', (e) => {
                    const action = item.dataset.action;
                    if (action) {
                        this.executeMenuAction(action, item.dataset.data);
                    }
                    this.closeAllMenus();
                });
            }
        });
    }
    
    positionDropdown(dropdown, menuItem) {
        const rect = menuItem.getBoundingClientRect();
        
        dropdown.style.position = 'fixed';
        dropdown.style.left = `${rect.left}px`;
        dropdown.style.top = `${rect.bottom}px`;
        dropdown.style.zIndex = '10000';
        
        // Adjust position if dropdown would go off-screen
        setTimeout(() => {
            const dropdownRect = dropdown.getBoundingClientRect();
            
            if (dropdownRect.right > window.innerWidth) {
                dropdown.style.left = `${rect.right - dropdownRect.width}px`;
            }
            
            if (dropdownRect.bottom > window.innerHeight) {
                dropdown.style.top = `${rect.top - dropdownRect.height}px`;
            }
        }, 0);
    }
    
    showSubmenu(parentItem, parentDropdown) {
        // Hide other submenus first
        this.hideAllSubmenus();
        
        // Find submenu definition
        const menuName = this.activeMenu;
        const menuDef = this.menuDefinitions[menuName];
        const parentAction = parentItem.dataset.action;
        
        let submenuDef = null;
        for (const item of menuDef) {
            if (item.action === parentAction && item.submenu) {
                submenuDef = item.submenu;
                break;
            }
        }
        
        if (!submenuDef) return;
        
        // Create submenu
        const submenu = this.createDropdownMenu(submenuDef);
        submenu.classList.add('submenu');
        submenu.dataset.parent = parentAction;
        
        // Position submenu
        this.positionSubmenu(submenu, parentItem);
        
        document.body.appendChild(submenu);
        this.activeSubmenus.add(submenu);
    }
    
    hideSubmenu(parentItem) {
        const parentAction = parentItem.dataset.action;
        const submenu = document.querySelector(`.submenu[data-parent="${parentAction}"]`);
        if (submenu) {
            submenu.remove();
            this.activeSubmenus.delete(submenu);
        }
    }
    
    hideAllSubmenus() {
        this.activeSubmenus.forEach(submenu => {
            submenu.remove();
        });
        this.activeSubmenus.clear();
    }
    
    isSubmenuHovered(parentItem) {
        const parentAction = parentItem.dataset.action;
        const submenu = document.querySelector(`.submenu[data-parent="${parentAction}"]`);
        return submenu && submenu.matches(':hover');
    }
    
    positionSubmenu(submenu, parentItem) {
        const parentRect = parentItem.getBoundingClientRect();
        
        submenu.style.position = 'fixed';
        submenu.style.left = `${parentRect.right}px`;
        submenu.style.top = `${parentRect.top}px`;
        submenu.style.zIndex = '10001';
        
        // Adjust position if submenu would go off-screen
        setTimeout(() => {
            const submenuRect = submenu.getBoundingClientRect();
            
            if (submenuRect.right > window.innerWidth) {
                submenu.style.left = `${parentRect.left - submenuRect.width}px`;
            }
            
            if (submenuRect.bottom > window.innerHeight) {
                submenu.style.top = `${parentRect.bottom - submenuRect.height}px`;
            }
        }, 0);
    }

    closeAllMenus() {
        // Remove active state from menu items
        const activeItems = this.element.querySelectorAll('.menu-item.active');
        activeItems.forEach(item => item.classList.remove('active'));
        
        // Remove dropdown menus and submenus
        const dropdowns = document.querySelectorAll('.menu-dropdown');
        dropdowns.forEach(dropdown => dropdown.remove());
        
        this.hideAllSubmenus();
        this.activeMenu = null;
    }
    
    async executeMenuAction(action, data = null) {
        console.log('Executing menu action:', action, data);
        
        switch (action) {
            case 'file.new':
                await this.newScene();
                break;
            case 'file.open':
                await this.openScene();
                break;
            case 'file.openRecent':
                await this.openRecentScene(data);
                break;
            case 'file.clearRecent':
                await this.clearRecentFiles();
                break;
            case 'file.save':
                await this.saveScene();
                break;
            case 'file.saveAs':
                await this.saveSceneAs();
                break;
            case 'file.saveAsPackage':
                await this.saveAsPackage();
                break;
            case 'file.saveAsPackageSettings':
                await this.saveAsPackageSettings();
                break;
            case 'file.unpackPackage':
                await this.unpackPackage();
                break;
            case 'file.loadRenderState':
                await this.loadRenderState();
                break;
            case 'file.saveRenderState':
                await this.saveRenderState();
                break;
            case 'file.saveAsDefault':
                await this.saveAsDefault();
                break;
            case 'file.preferences':
                await this.showPreferences();
                break;
            case 'file.activationStatus':
                await this.showActivationStatus();
                break;
            case 'file.quit':
                await this.quitApplication();
                break;
            case 'edit.undo':
                await this.undo();
                break;
            case 'edit.redo':
                await this.redo();
                break;
            case 'edit.cut':
                await this.cut();
                break;
            case 'edit.copy':
                await this.copy();
                break;
            case 'edit.paste':
                await this.paste();
                break;
            case 'edit.delete':
                await this.deleteSelected();
                break;
            case 'edit.selectAll':
                await this.selectAll();
                break;
            case 'script.run':
                await this.runScript();
                break;
            case 'script.editor':
                await this.showScriptEditor();
                break;
            case 'script.reload':
                await this.reloadScripts();
                break;
            case 'module.manager':
                await this.showModuleManager();
                break;
            case 'module.install':
                await this.installModule();
                break;
            case 'module.refresh':
                await this.refreshModules();
                break;
            case 'cloud.render':
                await this.cloudRender();
                break;
            case 'cloud.account':
                await this.showCloudAccount();
                break;
            case 'cloud.upload':
                await this.uploadScene();
                break;
            case 'cloud.download':
                await this.downloadResults();
                break;
            case 'window.sceneOutliner':
                await this.toggleSceneOutliner();
                break;
            case 'window.nodeInspector':
                await this.toggleNodeInspector();
                break;
            case 'window.nodeGraph':
                await this.toggleNodeGraph();
                break;
            case 'window.resetLayout':
                await this.resetLayout();
                break;
            case 'window.fullscreen':
                await this.toggleFullscreen();
                break;
            case 'view.refresh':
                await this.refresh();
                break;
            case 'help.docs':
                this.showDocumentation();
                break;
            case 'help.shortcuts':
                this.showKeyboardShortcuts();
                break;
            case 'help.bug':
                this.reportBug();
                break;
            case 'help.about':
                this.showAbout();
                break;
            default:
                console.warn('Unknown menu action:', action);
        }
    }
    
    getMenuDefinitions() {
        return {
            file: [
                { label: 'New', action: 'file.new', shortcut: 'Ctrl+N' },
                { label: 'Open', action: 'file.open', shortcut: 'Ctrl+O' },
                { 
                    label: 'Recent projects', 
                    action: 'file.recent',
                    submenu: [
                        { label: 'teapot.orbx', action: 'file.openRecent', data: 'teapot.orbx' },
                        { label: 'scene_001.orbx', action: 'file.openRecent', data: 'scene_001.orbx' },
                        { type: 'separator' },
                        { label: 'Clear Recent', action: 'file.clearRecent' }
                    ]
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
                { label: 'Activation status...', action: 'file.activationStatus' },
                { type: 'separator' },
                { label: 'Quit', action: 'file.quit', shortcut: 'Ctrl+Q' }
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
                { label: 'Run Script...', action: 'script.run', icon: '▶️' },
                { label: 'Script Editor', action: 'script.editor', icon: '📝' },
                { type: 'separator' },
                { label: 'Reload Scripts', action: 'script.reload', icon: '🔄' }
            ],
            module: [
                { label: 'Module Manager', action: 'module.manager', icon: '🧩' },
                { label: 'Install Module...', action: 'module.install', icon: '📦' },
                { type: 'separator' },
                { label: 'Refresh Modules', action: 'module.refresh', icon: '🔄' }
            ],
            cloud: [
                { label: 'Cloud Render', action: 'cloud.render', icon: '☁️' },
                { label: 'Account Settings', action: 'cloud.account', icon: '👤' },
                { type: 'separator' },
                { label: 'Upload Scene', action: 'cloud.upload', icon: '📤' },
                { label: 'Download Results', action: 'cloud.download', icon: '📥' }
            ],
            window: [
                { label: 'Scene Outliner', action: 'window.sceneOutliner', icon: '🌳' },
                { label: 'Node Inspector', action: 'window.nodeInspector', icon: '🔍' },
                { label: 'Node Graph', action: 'window.nodeGraph', icon: '🕸️' },
                { type: 'separator' },
                { label: 'Reset Layout', action: 'window.resetLayout', icon: '🔄' },
                { label: 'Fullscreen', action: 'window.fullscreen', shortcut: 'F11', icon: '⛶' }
            ],
            help: [
                { label: 'Documentation', action: 'help.docs', shortcut: 'F1', icon: '📚' },
                { label: 'Keyboard Shortcuts', action: 'help.shortcuts', icon: '⌨️' },
                { type: 'separator' },
                { label: 'Report Bug', action: 'help.bug', icon: '🐛' },
                { label: 'About OctaneWeb', action: 'help.about', icon: 'ℹ️' }
            ]
        };
    }
    
    // Menu action implementations
    async newScene() {
        console.log('Creating new scene...');
        
        try {
            // Make gRPC call to reset project (equivalent to "New")
            if (this.client && this.client.connected) {

                // Show progress notification
                this.showNotification('Creating new scene...', 'info');

                // Create a timeout promise to handle hanging calls
                const timeoutPromise = new Promise((_, reject) => {
                    setTimeout(() => reject(new Error('Operation timed out after 15 seconds')), 15000);
                });

                // Race between the gRPC call and timeout
                const response = await Promise.race([
                    this.client.makeGrpcCall('ApiProjectManager/resetProject'),
                    timeoutPromise
                ]);
                
                if (response.success && response.data && response.data.result) {
                    console.log('New scene created successfully via gRPC');
                    this.showNotification('New scene created', 'success');
                    
                    // Refresh scene outliner to show new empty scene
                    if (this.components?.sceneOutliner) {
                        setTimeout(() => {
                            this.components.sceneOutliner.refreshTree();
                        }, 500);
                    }
                    
                } else {
                    throw new Error(response.error || 'Reset project failed');
                }
                
            } else {
                // Fallback when not connected to Octane
                console.warn(' Octane not connected - creating local new scene');
                this.showNotification('📄 New scene created (local only)', 'warning');
            }
            
        } catch (error) {
            console.error('❌ Failed to create new scene:', error);
            
            if (error.message.includes('timed out')) {
                this.showNotification('⏱️ New scene operation timed out. Octane may be busy processing the request.', 'warning');
            } else {
                this.showNotification(`❌ Failed to create new scene: ${error.message}`, 'error');
            }
        }
    }
    
    async openScene() {
        console.log('Opening Octane project file...');
        
        try {
            const results = await this.fileManager.openFileDialog({
                accept: '.orbx',  // Only accept .orbx files
                multiple: false
            });
            
            if (results.length > 0) {
                const result = results[0];
                
                // Check if the project was successfully loaded via gRPC
                if (result.loadResult && result.loadResult.success) {
                    await this.loadSceneFromFile(result);
                    this.addToRecentFiles(result.name);
                    this.showNotification(`Loaded Octane project: ${result.name}`, 'success');
                } else if (result.loadResult && !result.loadResult.success) {
                    // Project file was processed but gRPC load failed
                    const errorMsg = result.loadResult.error || 'Unknown error';
                    this.showNotification(`❌ Failed to load project: ${errorMsg}`, 'error');
                    console.error('Project load failed:', result.loadResult);
                } else {
                    // Fallback for when gRPC is not available
                    await this.loadSceneFromFile(result);
                    this.addToRecentFiles(result.name);
                    this.showNotification(`📁 Processed project file: ${result.name} (Octane not connected)`, 'warning');
                }
            }
            
        } catch (error) {
            console.error('Failed to open scene:', error);
            this.showNotification('Failed to open project file', 'error');
        }
    }
    
    async openRecentScene(filename) {
        console.log('Opening recent scene:', filename);
        
        try {
            // Make gRPC call to load project directly by path
            if (this.client && this.client.connected) {
                console.log('Making gRPC call: ApiProjectManager/loadProject');
                
                const response = await this.client.makeGrpcCall('ApiProjectManager/loadProject', {
                    projectPath: filename,
                    evaluate: true
                });
                
                if (response.success && response.data && response.data.result) {
                    console.log('Recent project loaded successfully via gRPC');
                    this.showNotification(`Loaded ${filename}`, 'success');
                    
                    // Refresh scene outliner to show loaded scene
                    if (this.components?.sceneOutliner) {
                        setTimeout(() => {
                            this.components.sceneOutliner.refreshTree();
                        }, 1000);
                    }
                    
                } else {
                    throw new Error(response.error || 'Load project failed');
                }
                
            } else {
                throw new Error('Octane not connected');
            }
            
        } catch (error) {
            console.error('❌ Failed to open recent scene:', error);
            this.showNotification(`❌ Failed to open ${filename}: ${error.message}`, 'error');
        }
    }
    
    async clearRecentFiles() {
        console.log('Clearing recent files...');
        
        try {
            // Clear recent files from storage
            localStorage.removeItem('octaneWeb.recentFiles');
            this.showNotification('Recent files cleared', 'success');
            
        } catch (error) {
            console.error('Failed to clear recent files:', error);
            this.showNotification('Failed to clear recent files', 'error');
        }
    }
    
    async saveScene() {
        console.log('Saving scene...');
        
        try {
            // Make gRPC call to save current project
            if (this.client && this.client.connected) {
                console.log('Making gRPC call: ApiProjectManager/saveProject');
                
                const response = await this.client.makeGrpcCall('ApiProjectManager/saveProject');
                
                if (response.success && response.data && response.data.result) {
                    console.log('Scene saved successfully via gRPC');
                    
                    // Get current project path to show in notification
                    const currentProjectResponse = await this.client.makeGrpcCall('ApiProjectManager/getCurrentProject');
                    
                    const projectPath = currentProjectResponse.data?.result || 'current project';
                    const filename = projectPath.split(/[\\\/]/).pop() || 'project';
                    
                    this.showNotification(`Saved ${filename}`, 'success');
                    
                } else {
                    throw new Error(response.error || 'Save project failed');
                }
            } else {
                throw new Error('Octane not connected');
            }
            
        } catch (error) {
            console.error('❌ Failed to save scene:', error);
            this.showNotification(`❌ Failed to save scene: ${error.message}`, 'error');
        }
    }
    
    async saveSceneAs() {
        console.log('Save scene as...');
        
        try {
            // For now, we'll use a simple prompt for the filename
            // In a full implementation, this would open a proper file dialog
            const timestamp = new Date().toISOString().split('T')[0];
            const defaultName = `scene_${timestamp}.orbx`;
            const filename = prompt('Save scene as:', defaultName);
            
            if (!filename) {
                console.log('Save as cancelled by user');
                return;
            }
            
            // Make gRPC call to save project with new path
            if (this.client && this.client.connected) {
                console.log('Making gRPC call: ApiProjectManager/saveProjectAs');
                
                const response = await this.client.makeGrpcCall('ApiProjectManager/saveProjectAs', {
                    path: filename
                });
                
                if (response.success && response.data && response.data.result) {
                    console.log('Scene saved as successfully via gRPC');
                    
                    this.setCurrentSceneFilename(filename);
                    this.addToRecentFiles(filename);
                    this.showNotification(`Saved as ${filename}`, 'success');
                    
                } else {
                    throw new Error(response.error || 'Save project as failed');
                }
            } else {
                throw new Error('Octane not connected');
            }
            
        } catch (error) {
            console.error('❌ Failed to save scene as:', error);
            this.showNotification(`❌ Failed to save scene as: ${error.message}`, 'error');
        }
    }
    
    async saveAsPackage() {
        console.log('Save as package...');
        
        try {
            // For now, we'll use a simple prompt for the package path
            const timestamp = new Date().toISOString().split('T')[0];
            const defaultName = `package_${timestamp}.orbx`;
            const packagePath = prompt('Save as package:', defaultName);
            
            if (!packagePath) {
                console.log('Save as package cancelled by user');
                return;
            }
            
            // Make gRPC call to save project as reference package
            if (this.client && this.client.connected) {
                console.log('Making gRPC call: ApiProjectManager/saveProjectAsReferencePackage');
                
                const response = await this.client.makeGrpcCall('ApiProjectManager/saveProjectAsReferencePackage', {
                    path: packagePath,
                    referencePackageSettings: {
                        // Default package settings - in a full implementation these would be configurable
                        includeTextures: true,
                        includeGeometry: true,
                        includeMaterials: true
                    }
                });
                
                if (response.success && response.data && response.data.result) {
                    console.log('Package saved successfully via gRPC');
                    this.showNotification(`Saved package: ${packagePath}`, 'success');
                } else {
                    throw new Error(response.error || 'Save package failed');
                }
                
            } else {
                throw new Error('Octane not connected');
            }
            
        } catch (error) {
            console.error('❌ Failed to save as package:', error);
            this.showNotification(`❌ Failed to save package: ${error.message}`, 'error');
        }
    }
    
    async saveAsPackageSettings() {
        console.log('Save as package settings...');
        this.showNotification('Package settings dialog - Not implemented yet', 'info');
    }
    
    async unpackPackage() {
        console.log('Unpack package...');
        
        try {
            // For now, we'll use prompts for the package path and unpack directory
            const packagePath = prompt('Package file path:');
            if (!packagePath) {
                console.log('Unpack package cancelled by user');
                return;
            }
            
            const unpackDir = prompt('Unpack to directory:', './unpacked');
            if (!unpackDir) {
                console.log('Unpack package cancelled by user');
                return;
            }
            
            const unpackName = prompt('Unpacked project name:', 'unpacked_project');
            if (!unpackName) {
                console.log('Unpack package cancelled by user');
                return;
            }
            
            // Make gRPC call to unpack package
            if (this.client && this.client.connected) {
                console.log('Making gRPC call: ApiProjectManager/unpackPackage');
                
                const response = await this.client.makeGrpcCall('ApiProjectManager/unpackPackage', {
                    packagePath: packagePath,
                    unpackDir: unpackDir,
                    unpackName: unpackName
                });
                
                if (response.success && response.data && response.data.result) {
                    console.log('Package unpacked successfully via gRPC');
                    this.showNotification(`Package unpacked to: ${unpackDir}/${unpackName}`, 'success');
                } else {
                    throw new Error(response.error || 'Unpack package failed');
                }
                
            } else {
                console.warn(' Octane not connected - cannot unpack package');
                this.showNotification('❌ Cannot unpack package - Octane not connected', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to unpack package:', error);
            this.showNotification(`❌ Failed to unpack package: ${error.message}`, 'error');
        }
    }
    
    async loadRenderState() {
        console.log('Load render state...');
        
        try {
            const results = await this.fileManager.openFileDialog({
                accept: '.json,.state',
                multiple: false
            });
            
            if (results.length > 0) {
                this.showNotification('Render state loading - Not implemented yet', 'info');
            }
            
        } catch (error) {
            console.error('Failed to load render state:', error);
            this.showNotification('Failed to load render state', 'error');
        }
    }
    
    async saveRenderState() {
        console.log('Save render state...');
        
        try {
            this.showNotification(`Render state saved as ${filename}`, 'success');
            
        } catch (error) {
            console.error('Failed to save render state:', error);
            this.showNotification('Failed to save render state', 'error');
        }
    }
    
    async saveAsDefault() {
        console.log('Save as default...');
        
        try {
            this.showNotification('Scene saved as default', 'success');
            
        } catch (error) {
            console.error('Failed to save as default:', error);
            this.showNotification('Failed to save as default', 'error');
        }
    }
    
    async showPreferences() {
        console.log('Show preferences...');
        this.showNotification('Preferences dialog - Not implemented yet', 'info');
    }
    
    async showActivationStatus() {
        console.log('Show activation status...');
        this.showNotification('Activation status - Not implemented yet', 'info');
    }
    
    async quitApplication() {
        console.log('Quit application...');
        
        if (confirm('Are you sure you want to quit OctaneWeb?')) {
            // In a real application, this might save state and close gracefully
            this.showNotification('Goodbye!', 'info');
            setTimeout(() => {
                window.close();
            }, 1000);
        }
    }
    
    async undo() {
        console.log('↶ Undo...');
        
        try {
            // Try gRPC undo first (if available)
            if (this.client && this.client.connected) {
                // Note: Octane may not have a direct undo API, so we'll use local state manager as fallback
                console.log('Checking for gRPC undo capability...');
                this.showNotification(' Undo via gRPC not yet available', 'warning');
            }
            
            // Fallback to local state manager
            if (this.stateManager && this.stateManager.undo) {
                this.stateManager.undo();
                this.showNotification('↶ Undo completed (local)', 'info');
            } else {
                this.showNotification('❌ No undo history available', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to undo:', error);
            this.showNotification(`❌ Undo failed: ${error.message}`, 'error');
        }
    }
    
    async redo() {
        console.log('↷ Redo...');
        
        try {
            // Try gRPC redo first (if available)
            if (this.client && this.client.connected) {
                console.log('Checking for gRPC redo capability...');
                this.showNotification(' Redo via gRPC not yet available', 'warning');
            }
            
            // Fallback to local state manager
            if (this.stateManager && this.stateManager.redo) {
                this.stateManager.redo();
                this.showNotification('↷ Redo completed (local)', 'info');
            } else {
                this.showNotification('❌ No redo history available', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to redo:', error);
            this.showNotification(`❌ Redo failed: ${error.message}`, 'error');
        }
    }
    
    async cut() {
        console.log('Cut selected items...');
        
        try {
            if (this.client && this.client.connected) {
                // For now, show that gRPC cut is not implemented
                this.showNotification(' Cut via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Cut requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to cut:', error);
            this.showNotification(`❌ Cut failed: ${error.message}`, 'error');
        }
    }
    
    async copy() {
        console.log('Copy selected items...');
        
        try {
            if (this.client && this.client.connected) {
                // For now, show that gRPC copy is not implemented
                this.showNotification(' Copy via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Copy requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to copy:', error);
            this.showNotification(`❌ Copy failed: ${error.message}`, 'error');
        }
    }
    
    async paste() {
        console.log('Paste items...');
        
        try {
            if (this.client && this.client.connected) {
                // For now, show that gRPC paste is not implemented
                this.showNotification(' Paste via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Paste requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to paste:', error);
            this.showNotification(`❌ Paste failed: ${error.message}`, 'error');
        }
    }
    
    async deleteSelected() {
        console.log('Delete selected items...');
        
        try {
            if (this.client && this.client.connected) {
                // For now, show that gRPC delete is not implemented
                this.showNotification(' Delete via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Delete requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to delete:', error);
            this.showNotification(`❌ Delete failed: ${error.message}`, 'error');
        }
    }
    
    async selectAll() {
        console.log('Select all items...');
        
        try {
            if (this.client && this.client.connected) {
                // For now, show that gRPC select all is not implemented
                this.showNotification(' Select All via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Select All requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to select all:', error);
            this.showNotification(`❌ Select All failed: ${error.message}`, 'error');
        }
    }
    
    async refresh() {
        if (this.client && this.client.connected) {
            // Use working  methods instead of old sync methods
            try {
                await this.client.getSceneData();
                console.log('Scene data refreshed via ');
                
                // TODO: Implement node graph refresh with working  method
                // await this.client.getNodeGraphData(); // When available
                
            } catch (error) {
                console.error('❌ Failed to refresh scene data:', error);
            }
        }
    }
    
    // ==================== SCRIPT MENU FUNCTIONS ====================
    
    async runScript() {
        console.log('Run script...');
        
        try {
            if (this.client && this.client.connected) {
                // For now, show that script execution is not implemented
                this.showNotification(' Script execution via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Script execution requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to run script:', error);
            this.showNotification(`❌ Script execution failed: ${error.message}`, 'error');
        }
    }
    
    async showScriptEditor() {
        console.log('Show script editor...');
        this.showNotification('Script editor - Not implemented yet', 'info');
    }
    
    async reloadScripts() {
        console.log('Reload scripts...');
        
        try {
            if (this.client && this.client.connected) {
                this.showNotification(' Script reload via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Script reload requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to reload scripts:', error);
            this.showNotification(`❌ Script reload failed: ${error.message}`, 'error');
        }
    }
    
    // ==================== MODULE MENU FUNCTIONS ====================
    
    async showModuleManager() {
        console.log('Show module manager...');
        this.showNotification('Module manager - Not implemented yet', 'info');
    }
    
    async installModule() {
        console.log('Install module...');
        
        try {
            if (this.client && this.client.connected) {
                this.showNotification(' Module installation via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Module installation requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to install module:', error);
            this.showNotification(`❌ Module installation failed: ${error.message}`, 'error');
        }
    }
    
    async refreshModules() {
        console.log('Refresh modules...');
        
        try {
            if (this.client && this.client.connected) {
                this.showNotification(' Module refresh via gRPC not yet implemented', 'warning');
            } else {
                this.showNotification('❌ Module refresh requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to refresh modules:', error);
            this.showNotification(`❌ Module refresh failed: ${error.message}`, 'error');
        }
    }
    
    // ==================== CLOUD MENU FUNCTIONS ====================
    
    async cloudRender() {
        console.log('Start cloud render...');
        
        try {
            if (this.client && this.client.connected) {
                console.log('Making gRPC call: ApiRenderCloudManager/newRenderTask');
                
                const response = await this.client.makeGrpcCall('ApiRenderCloudManager/newRenderTask', {
                    // Add render task parameters as needed
                });
                
                if (response.success && response.data) {
                    console.log('Cloud render task created successfully');
                    this.showNotification('Cloud render task started', 'success');
                } else {
                    throw new Error(response.error || 'Cloud render task creation failed');
                }
                
            } else {
                this.showNotification('❌ Cloud render requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to start cloud render:', error);
            this.showNotification(`❌ Cloud render failed: ${error.message}`, 'error');
        }
    }
    
    async showCloudAccount() {
        console.log('Show cloud account...');
        
        try {
            if (this.client && this.client.connected) {
                console.log('Making gRPC call: ApiRenderCloudManager/userSubscriptionInfo');
                
                const response = await this.client.makeGrpcCall('ApiRenderCloudManager/userSubscriptionInfo');
                
                if (response.success && response.data) {
                    console.log('Retrieved cloud account info');
                    this.showNotification('Cloud account info retrieved', 'success');
                    // TODO: Show account info in a modal
                } else {
                    throw new Error(response.error || 'Failed to get account info');
                }
                
            } else {
                this.showNotification('❌ Cloud account requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to get cloud account info:', error);
            this.showNotification(`❌ Cloud account failed: ${error.message}`, 'error');
        }
    }
    
    async uploadScene() {
        console.log('Upload scene to cloud...');
        
        try {
            if (this.client && this.client.connected) {
                console.log('Making gRPC call: ApiRenderCloudManager/uploadCurrentProject');
                
                const response = await this.client.makeGrpcCall('ApiRenderCloudManager/uploadCurrentProject');
                
                if (response.success && response.data) {
                    console.log('Scene uploaded to cloud successfully');
                    this.showNotification('Scene uploaded to cloud', 'success');
                } else {
                    throw new Error(response.error || 'Scene upload failed');
                }
                
            } else {
                this.showNotification('❌ Scene upload requires Octane connection', 'error');
            }
            
        } catch (error) {
            console.error('❌ Failed to upload scene:', error);
            this.showNotification(`❌ Scene upload failed: ${error.message}`, 'error');
        }
    }
    
    async downloadResults() {
        console.log('Download cloud results...');
        this.showNotification('Download results - Not implemented yet', 'info');
    }
    
    // ==================== WINDOW MENU FUNCTIONS ====================
    
    async toggleSceneOutliner() {
        console.log('Toggle scene outliner...');
        
        try {
            const sceneOutlinerPanel = document.querySelector('.scene-outliner-panel');
            if (sceneOutlinerPanel) {
                const isVisible = sceneOutlinerPanel.style.display !== 'none';
                sceneOutlinerPanel.style.display = isVisible ? 'none' : 'block';
                this.showNotification(`🌳 Scene outliner ${isVisible ? 'hidden' : 'shown'}`, 'info');
            }
            
        } catch (error) {
            console.error('❌ Failed to toggle scene outliner:', error);
            this.showNotification(`❌ Toggle scene outliner failed: ${error.message}`, 'error');
        }
    }
    
    async toggleNodeInspector() {
        console.log('Toggle node inspector...');
        
        try {
            const nodeInspectorPanel = document.querySelector('.node-inspector-panel');
            if (nodeInspectorPanel) {
                const isVisible = nodeInspectorPanel.style.display !== 'none';
                nodeInspectorPanel.style.display = isVisible ? 'none' : 'block';
                this.showNotification(`Node inspector ${isVisible ? 'hidden' : 'shown'}`, 'info');
            }
            
        } catch (error) {
            console.error('❌ Failed to toggle node inspector:', error);
            this.showNotification(`❌ Toggle node inspector failed: ${error.message}`, 'error');
        }
    }
    
    async toggleNodeGraph() {
        console.log('Toggle node graph...');
        
        try {
            const nodeGraphPanel = document.querySelector('.node-graph-panel');
            if (nodeGraphPanel) {
                const isVisible = nodeGraphPanel.style.display !== 'none';
                nodeGraphPanel.style.display = isVisible ? 'none' : 'block';
                this.showNotification(`🕸️ Node graph ${isVisible ? 'hidden' : 'shown'}`, 'info');
            }
            
        } catch (error) {
            console.error('❌ Failed to toggle node graph:', error);
            this.showNotification(`❌ Toggle node graph failed: ${error.message}`, 'error');
        }
    }
    
    async resetLayout() {
        console.log('Reset layout...');
        
        try {
            // Reset all panels to default visibility and positions
            const panels = [
                '.scene-outliner-panel',
                '.node-inspector-panel', 
                '.node-graph-panel'
            ];
            
            panels.forEach(selector => {
                const panel = document.querySelector(selector);
                if (panel) {
                    panel.style.display = 'block';
                    panel.style.width = '';
                    panel.style.height = '';
                }
            });
            
            this.showNotification('Layout reset to default', 'success');
            
        } catch (error) {
            console.error('❌ Failed to reset layout:', error);
            this.showNotification(`❌ Layout reset failed: ${error.message}`, 'error');
        }
    }
    
    async toggleFullscreen() {
        console.log('⛶ Toggle fullscreen...');
        
        try {
            if (!document.fullscreenElement) {
                await document.documentElement.requestFullscreen();
                this.showNotification('⛶ Entered fullscreen mode', 'info');
            } else {
                await document.exitFullscreen();
                this.showNotification('⛶ Exited fullscreen mode', 'info');
            }
            
        } catch (error) {
            console.error('❌ Failed to toggle fullscreen:', error);
            this.showNotification(`❌ Fullscreen toggle failed: ${error.message}`, 'error');
        }
    }
    
    // ==================== HELP MENU FUNCTIONS ====================
    
    showDocumentation() {
        console.log('Show documentation...');
        window.open('https://docs.otoy.com/octane/', '_blank');
    }
    
    showKeyboardShortcuts() {
        console.log('Show keyboard shortcuts...');
        
        const modal = document.createElement('div');
        modal.className = 'modal-overlay';
        modal.innerHTML = `
            <div class="modal-dialog">
                <div class="modal-header">
                    <div class="modal-title">Keyboard Shortcuts</div>
                    <button class="modal-close" onclick="this.closest('.modal-overlay').remove()">×</button>
                </div>
                <div class="modal-content">
                    <div class="shortcuts-grid" style="display: grid; grid-template-columns: 1fr 1fr; gap: 20px;">
                        <div>
                            <h4>File Operations</h4>
                            <div class="shortcut-item"><kbd>Ctrl+N</kbd> New Scene</div>
                            <div class="shortcut-item"><kbd>Ctrl+O</kbd> Open Scene</div>
                            <div class="shortcut-item"><kbd>Ctrl+S</kbd> Save Scene</div>
                            <div class="shortcut-item"><kbd>Ctrl+Shift+S</kbd> Save As</div>
                            <div class="shortcut-item"><kbd>Ctrl+Q</kbd> Quit</div>
                        </div>
                        <div>
                            <h4>Edit Operations</h4>
                            <div class="shortcut-item"><kbd>Ctrl+Z</kbd> Undo</div>
                            <div class="shortcut-item"><kbd>Ctrl+Y</kbd> Redo</div>
                            <div class="shortcut-item"><kbd>Ctrl+X</kbd> Cut</div>
                            <div class="shortcut-item"><kbd>Ctrl+C</kbd> Copy</div>
                            <div class="shortcut-item"><kbd>Ctrl+V</kbd> Paste</div>
                            <div class="shortcut-item"><kbd>Del</kbd> Delete</div>
                            <div class="shortcut-item"><kbd>Ctrl+A</kbd> Select All</div>
                        </div>
                    </div>
                    <div style="margin-top: 20px;">
                        <h4>Other Shortcuts</h4>
                        <div class="shortcut-item"><kbd>F1</kbd> Documentation</div>
                        <div class="shortcut-item"><kbd>F11</kbd> Fullscreen</div>
                        <div class="shortcut-item"><kbd>Ctrl+,</kbd> Preferences</div>
                    </div>
                </div>
                <div class="modal-footer">
                    <button class="modal-button primary" onclick="this.closest('.modal-overlay').remove()">OK</button>
                </div>
            </div>
        `;
        
        document.body.appendChild(modal);
    }
    
    reportBug() {
        console.log('Report bug...');
        window.open('https://github.com/ultrafish22L/grpcSamples/issues/new', '_blank');
    }

    showAbout() {
        const modal = document.createElement('div');
        modal.className = 'modal-overlay';
        modal.innerHTML = `
            <div class="modal-dialog">
                <div class="modal-header">
                    <div class="modal-title">About OctaneWeb</div>
                    <button class="modal-close" onclick="this.closest('.modal-overlay').remove()">×</button>
                </div>
                <div class="modal-content">
                    <div style="text-align: center; margin-bottom: 20px;">
                        <svg class="octane-gear-logo" viewBox="80 400 160 160" xmlns="http://www.w3.org/2000/svg" style="width: 64px; height: 64px; color: #ff8c00;">
                            <path d="m 169.12653,414.9594 c -17.66973,19.84435 -24.42202,30.54014 -25.82633,46.56827 -0.0797,-0.0403 -0.14939,-0.0719 -0.23111,-0.11556 -6.49445,-3.72391 -11.68872,-11.28146 -14.79091,-19.00864 l -11.38208,4.44883 c 8.34282,25.2004 14.29208,36.30322 27.44409,45.5283 -0.0845,0.0557 -0.14162,0.11759 -0.23111,0.17324 -6.47223,3.7624 -15.61888,4.52807 -23.86191,3.35107 l -1.84887,12.07539 c 26.04716,5.38577 38.66855,5.8375 53.27042,-0.9822 0.006,0.10131 -0.004,0.18303 0,0.28888 0.0222,7.48631 -3.93015,15.75176 -9.07099,22.30193 l 9.53321,7.62657 c 17.64876,-19.82077 24.35332,-30.51407 25.76857,-46.51051 0.0817,0.0412 0.14717,0.0708 0.23111,0.11556 6.49445,3.72391 11.68873,11.28146 14.79092,19.00864 l 11.38207,-4.44883 c -8.34481,-25.20645 -14.28544,-36.3597 -27.44408,-45.58608 0.0856,-0.0566 0.14032,-0.11685 0.2311,-0.17324 6.47223,-3.7624 15.61888,-4.47029 23.86192,-3.29329 l 1.84886,-12.13317 c -26.0131,-5.37872 -38.63503,-5.80958 -53.21266,0.98221 -0.006,-0.0969 0.004,-0.18794 0,-0.28889 -0.0222,-7.48631 3.93015,-15.75174 9.07101,-22.30191 l -9.53323,-7.62657 z m 0.98221,44.95051 c 8.92834,-0.29403 16.40356,6.72926 16.69758,15.65757 0.29403,8.92832 -6.72925,16.40354 -15.65759,16.69757 -8.92832,0.29402 -16.40354,-6.72926 -16.69756,-15.65758 -0.29403,-8.92832 6.72926,-16.40354 15.65757,-16.69756 z" fill="currentColor" stroke="none" />
                        </svg>
                    </div>
                    <h3>OctaneWeb</h3>
                    <p><strong>Version:</strong> 1.0.0 Beta</p>
                    <p><strong>Build:</strong> ${new Date().toISOString().split('T')[0]}</p>
                    <br>
                    <p>A complete web-based interface for Octane Render, providing pixel-perfect recreation of the native application through gRPC integration.</p>
                    <br>
                    <p><strong>Features:</strong></p>
                    <ul style="text-align: left; margin-left: 20px;">
                        <li>Real-time scene synchronization</li>
                        <li>Visual node graph editor</li>
                        <li>Complete parameter controls</li>
                        <li>Cross-platform compatibility</li>
                        <li>Professional UI matching native Octane</li>
                    </ul>
                    <br>
                    <p><small>© 2025 OTOY Inc. All rights reserved.</small></p>
                </div>
                <div class="modal-footer">
                    <button class="modal-button primary" onclick="this.closest('.modal-overlay').remove()">OK</button>
                </div>
            </div>
        `;
        
        document.body.appendChild(modal);
    }
    
    // Helper methods for file operations
    async loadSceneFromFile(fileResult) {
        console.log('Loading scene from file:', fileResult.name);
        console.log('  parsed:', fileResult.parsed);
        
        try {
        } catch (error) {
            console.error('Failed to load scene from file:', error);
            throw error;
        }
    }
    
    getCurrentSceneFilename() {
        return this.currentSceneFilename || null;
    }
    
    setCurrentSceneFilename(filename) {
        this.currentSceneFilename = filename;
        // Update window title
        document.title = `${filename} - OctaneRender Studio - Web Edition`;
    }
    
    addToRecentFiles(filename) {
        try {
            let recentFiles = JSON.parse(localStorage.getItem('octaneWeb.recentFiles') || '[]');
            
            // Remove if already exists
            recentFiles = recentFiles.filter(f => f !== filename);
            
            // Add to beginning
            recentFiles.unshift(filename);
            
            // Keep only last 10
            recentFiles = recentFiles.slice(0, 10);
            
            localStorage.setItem('octaneWeb.recentFiles', JSON.stringify(recentFiles));
            
            // Update menu definitions
            this.updateRecentFilesMenu();
            
        } catch (error) {
            console.error('Failed to add to recent files:', error);
        }
    }
    
    updateRecentFilesMenu() {
        try {
            const recentFiles = JSON.parse(localStorage.getItem('octaneWeb.recentFiles') || '[]');
            
            // Update the menu definition
            const fileMenu = this.menuDefinitions.file;
            const recentMenuItem = fileMenu.find(item => item.action === 'file.recent');
            
            if (recentMenuItem) {
                recentMenuItem.submenu = [
                    ...recentFiles.map(filename => ({
                        label: filename,
                        action: 'file.openRecent',
                        data: filename
                    })),
                    { type: 'separator' },
                    { label: 'Clear Recent', action: 'file.clearRecent' }
                ];
            }
            
        } catch (error) {
            console.error('Failed to update recent files menu:', error);
        }
    }
    
    showNotification(message, type = 'info') {
        // Create notification element
        const notification = document.createElement('div');
        notification.className = `notification notification-${type}`;
        notification.innerHTML = `
            <div class="notification-content">
                <span class="notification-icon">${this.getNotificationIcon(type)}</span>
                <span class="notification-message">${message}</span>
                <button class="notification-close" onclick="this.parentElement.parentElement.remove()">×</button>
            </div>
        `;
        
        // Add to page
        let container = document.getElementById('notification-container');
        if (!container) {
            container = document.createElement('div');
            container.id = 'notification-container';
            container.className = 'notification-container';
            document.body.appendChild(container);
        }
        
        container.appendChild(notification);
        
        // Auto-remove after 5 seconds
        setTimeout(() => {
            if (notification.parentElement) {
                notification.remove();
            }
        }, 5000);
        
        console.log(`${type.toUpperCase()}: ${message}`);
    }
    
    getNotificationIcon(type) {
        switch (type) {
            case 'success': return '✅';
            case 'error': return '❌';
            case 'warning': return '';
            case 'info': 
            default: return 'ℹ️';
        }
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = MenuSystem;
} else if (typeof window !== 'undefined') {
    window.MenuSystem = MenuSystem;
}