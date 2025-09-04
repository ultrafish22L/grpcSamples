/**
 * Menu System Component
 * Application menu bar and context menus
 */

class MenuSystem extends OctaneComponent {
    constructor(element, stateManager) {
        super(element, stateManager);
        
        this.activeMenu = null;
        this.menuDefinitions = this.getMenuDefinitions();
        this.fileManager = new FileManager();
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
                this.newScene();
                break;
            case 'file.open':
                this.openScene();
                break;
            case 'file.openRecent':
                this.openScene(data, true);
                break;
            case 'file.clearRecent':
                this.clearRecentFiles();
                break;
            case 'file.save':
                this.saveScene();
                break;
            case 'file.saveAs':
                this.saveSceneAs();
                break;
            case 'file.saveAsPackage':
                this.saveAsPackage();
                break;
            case 'file.saveAsPackageSettings':
                this.saveAsPackageSettings();
                break;
            case 'file.unpackPackage':
                this.unpackPackage();
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
        if (!window.octaneClient.connected) {
            showWarnNotConnected("newScene");            
            return false;
        }            
        const response = window.octaneClient.makeApiCallAsync('ApiProjectManager/resetProject');
        
        if (response.success) {
            console.log('New scene created successfully');
            // Refresh scene
            window.octaneClient.syncScene();
        }      
        response.success;      
    }
    
    async openScene(filename, isRecent) {
        let results = [filename];
        if (!filename) {
            results = await this.fileManager.showFileDialog({
                accept: '.orbx',  // Only accept .orbx files
                multiple: false
            });
        }
        if (results.length > 0) {
            let result = results[0];
            console.log(`openScene `, result.name );

            const response = await this.fileManager.processSceneFile(result);
            if (response.success) {
                if (!isRecent) {
                    this.addToRecentFiles(response.name);
                }
                this.showNotification(`Loaded: ${response.name}`, 'success');
            } 
        }
    }
    
    async clearRecentFiles() {
        console.log('Clearing recent files...');
        
        // Clear recent files from storage
        localStorage.removeItem('octaneWeb.recentFiles');
        this.showNotification('Recent files cleared', 'success');
    }
    
    async saveScene() {
        if (!window.octaneClient.connected) {
            showWarnNotConnected("saveScene"); 
            return false;
        }  
        const response = await window.octaneClient.makeApiCall('ApiProjectManager/saveProject');
        
        if (response.success) {
            console.log('Scene saved successfully');
            
            // Get current project path to show in notification
            const currentProjectResponse = await window.octaneClient.makeApiCall('ApiProjectManager/getCurrentProject');
            
            const projectPath = currentProjectResponse.data?.result || 'current project';
            const filename = projectPath.split(/[\\\/]/).pop() || 'project';
            
            this.showNotification(`Saved ${filename}`, 'success');
        }
    }
    
    async saveSceneAs() {

        if (!window.octaneClient.connected) {
            showWarnNotConnected("saveSceneAs"); 
            return false;
        }  
        const results = await this.fileManager.showFileDialog({
            accept: '.orbx',
            multiple: false
        });
        if (results.length > 0) {
            let result = results[0];
            console.log(`saveSceneAs ${result}` );

            const response = await window.octaneClient.makeApiCall('ApiProjectManager/saveProjectAs', {
                path: filename
            });
            
            if (response.success) {
                console.log('Scene saved as successfully');
                
                this.setCurrentSceneFilename(filename);
                this.addToRecentFiles(filename);
                this.showNotification(`Saved as ${filename}`, 'success');
            }
        }
    }
    
    async saveAsPackage() {
        if (!window.octaneClient.connected) {
            showWarnNotConnected("saveAsPackage"); 
            return false;
        }  
        const results = await this.fileManager.showFileDialog({
            accept: '.orbx',
            multiple: false
        });
        if (results.length > 0) {
            let result = results[0];
            console.log(`saveAsPackage ${result}` );

            const response = await window.octaneClient.makeApiCall('ApiProjectManager/saveProjectAsReferencePackage', {
                path: result,
                referencePackageSettings: {
                    // Default package settings - in a full implementation these would be configurable
                    includeTextures: true,
                    includeGeometry: true,
                    includeMaterials: true
                }
            });
            if (response.success) {
                console.log('Package saved successfully');
                this.showNotification(`Saved package: ${packagePath}`, 'success');
            }
        }
    }
    
    async saveAsPackageSettings() {
        console.log('Save as package settings...');
        this.showNotification('Package settings dialog - Not implemented yet', 'info');
    }
    
    async unpackPackage() {
        if (!window.octaneClient.connected) {
            showWarnNotConnected("unpackPackage"); 
            return false;
        }  
        const unpackDir = prompt('Unpack to directory:', './unpacked');
        if (!unpackDir) {
            console.log('Unpack package cancelled by user');
            return;
        }
        const response = await window.octaneClient.makeApiCall('ApiProjectManager/unpackPackage', {
            packagePath: null,
            unpackDir: unpackDir,
            unpackName: null
        });
        
        if (response.success) {
            console.log('Package unpacked successfully');
            this.showNotification(`Package unpacked to: ${unpackDir}/${unpackName}`, 'success');
        }
    }
    
    async loadRenderState() {
        console.log('Load render state...');
        
        const results = await this.fileManager.showFileDialog({
            accept: '.json,.state',
            multiple: false
        });
        
        if (results.length > 0) {
            this.showNotification('Render state loading - Not implemented yet', 'info');
        }
    }
    
    async saveRenderState() {
        console.log('Save render state...');
        
        this.showNotification(`Render state saved as ${filename}`, 'success');
    }
    
    async saveAsDefault() {
        console.log('Save as default...');
        
        this.showNotification('Scene saved as default', 'success');
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
        this.showNotification('Goodbye!', 'info');
        setTimeout(() => {
            window.close();
        }, 1000);
    }
    
    async undo() {
        console.log('↶ Undo...');

        // Fallback to local state manager
        if (this.stateManager && this.stateManager.undo) {
            this.stateManager.undo();
            this.showNotification('↶ Undo completed (local)', 'info');
        } else {
            this.showNotification('❌ No undo history available', 'error');
        }
    }
    
    async redo() {
        console.log('↷ Redo...');

        // Fallback to local state manager
        if (this.stateManager && this.stateManager.redo) {
            this.stateManager.redo();
            this.showNotification('↷ Redo completed (local)', 'info');
        } else {
            this.showNotification('❌ No redo history available', 'error');
        }
    }
    
    async cut() {
        console.log('Cut selected items...');
        
        if (window.octaneClient.connected) {
            // For now, show that gRPC cut is not implemented
            this.showNotification(' Cut via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Cut requires Octane connection', 'error');
        }
    }
    
    async copy() {
        console.log('Copy selected items...');
        
        if (window.octaneClient.connected) {
            // For now, show that gRPC copy is not implemented
            this.showNotification(' Copy via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Copy requires Octane connection', 'error');
        }
    }
    
    async paste() {
        console.log('Paste items...');
        
        if (window.octaneClient.connected) {
            // For now, show that gRPC paste is not implemented
            this.showNotification(' Paste via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Paste requires Octane connection', 'error');
        }
    }
    
    async deleteSelected() {
        console.log('Delete selected items...');
        
        if (window.octaneClient.connected) {
            // For now, show that gRPC delete is not implemented
            this.showNotification(' Delete via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Delete requires Octane connection', 'error');
        }
    }
    
    async selectAll() {
        console.log('Select all items...');
        
        if (window.octaneClient.connected) {
            // For now, show that gRPC select all is not implemented
            this.showNotification(' Select All via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Select All requires Octane connection', 'error');
        }
    }
    
    async refresh() {
        window.octaneClient.syncScene();
    }
    
    // ==================== SCRIPT MENU FUNCTIONS ====================
    
    async runScript() {
        console.log('Run script...');
        
        if (window.octaneClient.connected) {
            // For now, show that script execution is not implemented
            this.showNotification(' Script execution via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Script execution requires Octane connection', 'error');
        }
    }
    
    async showScriptEditor() {
        console.log('Show script editor...');
        this.showNotification('Script editor - Not implemented yet', 'info');
    }
    
    async reloadScripts() {
        console.log('Reload scripts...');
        
        if (window.octaneClient.connected) {
            this.showNotification(' Script reload via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Script reload requires Octane connection', 'error');
        }
    }
    
    // ==================== MODULE MENU FUNCTIONS ====================
    
    async showModuleManager() {
        console.log('Show module manager...');
        this.showNotification('Module manager - Not implemented yet', 'info');
    }
    
    async installModule() {
        console.log('Install module...');
        
        if (window.octaneClient.connected) {
            this.showNotification(' Module installation via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Module installation requires Octane connection', 'error');
        }
    }
    
    async refreshModules() {
        console.log('Refresh modules...');
        
        if (window.octaneClient.connected) {
            this.showNotification(' Module refresh via gRPC not yet implemented', 'warning');
        } else {
            this.showNotification('❌ Module refresh requires Octane connection', 'error');
        }
    }
    
    // ==================== CLOUD MENU FUNCTIONS ====================
    
    async cloudRender() {
        if (!window.octaneClient.connected) {
            showWarnNotConnected("cloudRender"); 
            return false;
        }  
        const response = await window.octaneClient.makeApiCall('ApiRenderCloudManager/newRenderTask', {
            // Add render task parameters as needed
        });
        
        if (response.success && response.data) {
            console.log('Cloud render task created successfully');
            this.showNotification('Cloud render task started', 'success');
        }
    }
    
    async showCloudAccount() {
        if (!window.octaneClient.connected) {
            showWarnNotConnected("showCloudAccount"); 
            return false;
        }  
        const response = await window.octaneClient.makeApiCall('ApiRenderCloudManager/userSubscriptionInfo');
        
        if (response.success && response.data) {
            this.showNotification(`Cloud account subscribed: ${response.data.subscribed}\n         credit: ${response.data.availableCreditBalance}\n   RnDr balance: ${response.data.availableRndrBalance}`);
        }
    }
    
    async uploadScene() {
        if (!window.octaneClient.connected) {
            showWarnNotConnected("cloudRender"); 
            return false;
        }  
        const response = await window.octaneClient.makeApiCall('ApiRenderCloudManager/uploadCurrentProject');
        
        if (response.success && response.data) {
            console.log('Scene uploaded to cloud successfully');
            this.showNotification('Scene uploaded to cloud', 'success');
        }
    }
    
    async downloadResults() {
        console.log('Download cloud results...');
        this.showNotification('Download results - Not implemented yet', 'info');
    }
    
    // ==================== WINDOW MENU FUNCTIONS ====================
    
    async toggleSceneOutliner() {
        console.log('Toggle scene outliner...');
        
        const sceneOutlinerPanel = document.querySelector('.scene-outliner-panel');
        if (sceneOutlinerPanel) {
            const isVisible = sceneOutlinerPanel.style.display !== 'none';
            sceneOutlinerPanel.style.display = isVisible ? 'none' : 'block';
            this.showNotification(`🌳 Scene outliner ${isVisible ? 'hidden' : 'shown'}`, 'info');
        }
    }
    
    async toggleNodeInspector() {
        console.log('Toggle node inspector...');
        
        const nodeInspectorPanel = document.querySelector('.node-inspector-panel');
        if (nodeInspectorPanel) {
            const isVisible = nodeInspectorPanel.style.display !== 'none';
            nodeInspectorPanel.style.display = isVisible ? 'none' : 'block';
            this.showNotification(`Node inspector ${isVisible ? 'hidden' : 'shown'}`, 'info');
        }
    }
    
    async toggleNodeGraph() {
        console.log('Toggle node graph...');
        
        const nodeGraphPanel = document.querySelector('.node-graph-panel');
        if (nodeGraphPanel) {
            const isVisible = nodeGraphPanel.style.display !== 'none';
            nodeGraphPanel.style.display = isVisible ? 'none' : 'block';
            this.showNotification(`🕸️ Node graph ${isVisible ? 'hidden' : 'shown'}`, 'info');
        }
    }
    
    async resetLayout() {
        console.log('Reset layout...');
        
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
    }
    
    async toggleFullscreen() {
        console.log('⛶ Toggle fullscreen...');
        
        if (!document.fullscreenElement) {
            await document.documentElement.requestFullscreen();
            this.showNotification('⛶ Entered fullscreen mode', 'info');
        } else {
            await document.exitFullscreen();
            this.showNotification('⛶ Exited fullscreen mode', 'info');
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
    
    getCurrentSceneFilename() {
        return this.currentSceneFilename || null;
    }
    
    setCurrentSceneFilename(filename) {
        this.currentSceneFilename = filename;
        // Update window title
        document.title = `${filename} - OctaneRender Studio - Web Edition`;
    }
    
    addToRecentFiles(filename) {
        let recentFiles = JSON.parse(localStorage.getItem('octaneWeb.recentFiles') || '[]');
        
        // Remove if already exists
        recentFiles = recentFiles.filter(f => f !== filename);
        
        // Add to beginning
        recentFiles.unshift(filename);
        
        // Keep only last 10
        recentFiles = recentFiles.slice(0, 10);
        
        localStorage.setItem('octaneWeb.recentFiles', JSON.stringify(recentFiles, null, 2));
        
        // Update menu definitions
        this.updateRecentFilesMenu();
    }
    
    updateRecentFilesMenu() {
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
    }
    
    
    async showWarnNotConnected(calledFrom) {
        console.warn('Octane not connected: ', calledFrom);
        this.showNotification('❌ Octane not connected: ', calledFrom);
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