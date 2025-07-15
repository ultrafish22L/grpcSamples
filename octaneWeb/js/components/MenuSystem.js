/**
 * Menu System Component
 * Application menu bar and context menus
 */

class MenuSystem extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        this.activeMenu = null;
        this.menuDefinitions = this.getMenuDefinitions();
    }
    
    async onInitialize() {
        this.setupMenuItems();
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
        
        return `
            <div class="context-menu-item ${disabled}" data-action="${item.action || ''}">
                ${icon}
                <span>${item.label}</span>
                ${shortcut}
            </div>
        `;
    }
    
    setupDropdownEventListeners(dropdown) {
        const items = dropdown.querySelectorAll('.context-menu-item:not(.disabled)');
        
        items.forEach(item => {
            this.addEventListener(item, 'click', (e) => {
                const action = item.dataset.action;
                if (action) {
                    this.executeMenuAction(action);
                }
                this.closeAllMenus();
            });
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
    
    closeAllMenus() {
        // Remove active state from menu items
        const activeItems = this.element.querySelectorAll('.menu-item.active');
        activeItems.forEach(item => item.classList.remove('active'));
        
        // Remove dropdown menus
        const dropdowns = document.querySelectorAll('.menu-dropdown');
        dropdowns.forEach(dropdown => dropdown.remove());
        
        this.activeMenu = null;
    }
    
    async executeMenuAction(action) {
        console.log('Executing menu action:', action);
        
        switch (action) {
            case 'file.new':
                await this.newScene();
                break;
            case 'file.open':
                await this.openScene();
                break;
            case 'file.save':
                await this.saveScene();
                break;
            case 'file.saveAs':
                await this.saveSceneAs();
                break;
            case 'file.import':
                await this.importFile();
                break;
            case 'file.export':
                await this.exportFile();
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
            case 'view.refresh':
                await this.refresh();
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
                { label: 'New Scene', action: 'file.new', shortcut: 'Ctrl+N', icon: '📄' },
                { label: 'Open Scene...', action: 'file.open', shortcut: 'Ctrl+O', icon: '📂' },
                { type: 'separator' },
                { label: 'Save Scene', action: 'file.save', shortcut: 'Ctrl+S', icon: '💾' },
                { label: 'Save Scene As...', action: 'file.saveAs', shortcut: 'Ctrl+Shift+S', icon: '💾' },
                { type: 'separator' },
                { label: 'Import...', action: 'file.import', shortcut: 'Ctrl+I', icon: '📥' },
                { label: 'Export...', action: 'file.export', shortcut: 'Ctrl+E', icon: '📤' }
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
        console.log('New scene');
        // TODO: Implement new scene
    }
    
    async openScene() {
        console.log('Open scene');
        // TODO: Implement open scene
    }
    
    async saveScene() {
        console.log('Save scene');
        // TODO: Implement save scene
    }
    
    async saveSceneAs() {
        console.log('Save scene as');
        // TODO: Implement save scene as
    }
    
    async importFile() {
        console.log('Import file');
        // TODO: Implement import
    }
    
    async exportFile() {
        console.log('Export file');
        // TODO: Implement export
    }
    
    async undo() {
        if (this.stateManager) {
            this.stateManager.undo();
        }
    }
    
    async redo() {
        if (this.stateManager) {
            this.stateManager.redo();
        }
    }
    
    async cut() {
        console.log('Cut');
        // TODO: Implement cut
    }
    
    async copy() {
        console.log('Copy');
        // TODO: Implement copy
    }
    
    async paste() {
        console.log('Paste');
        // TODO: Implement paste
    }
    
    async deleteSelected() {
        console.log('Delete selected');
        // TODO: Implement delete selected
    }
    
    async selectAll() {
        console.log('Select all');
        // TODO: Implement select all
    }
    
    async refresh() {
        if (this.client && this.client.isConnected) {
            await this.client.syncSceneHierarchy();
            await this.client.syncNodeGraph();
        }
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
                    <p>A complete web-based interface for Octane Render, providing pixel-perfect recreation of the native application through gRPC LiveLink integration.</p>
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
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = MenuSystem;
} else if (typeof window !== 'undefined') {
    window.MenuSystem = MenuSystem;
}