/**
 * Scene Outliner Controls Component
 * Official OTOY Scene Outliner control bar implementation
 * Based on official documentation: Three tabs (Scene, Live DB, Local DB) + Collapse/Refresh buttons
 */

class SceneOutlinerControls {
    constructor(containerId, octaneClient = null) {
        this.container = document.getElementById(containerId);
        this.client = octaneClient;
        this.currentTab = 'scene';
        this.isCollapsed = false;
        
        this.setupEventListeners();
        console.log('🎛️ Scene Outliner Controls initialized with official OTOY interface');
    }
    
    setupEventListeners() {
        // Tab switching functionality
        const tabs = this.container.querySelectorAll('.scene-tab');
        tabs.forEach(tab => {
            tab.addEventListener('click', (e) => {
                const tabName = e.target.dataset.tab;
                this.switchTab(tabName);
            });
        });
        
        // Collapse/Expand All button
        const collapseBtn = this.container.querySelector('.collapse-btn');
        if (collapseBtn) {
            collapseBtn.addEventListener('click', () => {
                this.toggleCollapseAll();
            });
        }
        
        // Refresh button
        const refreshBtn = this.container.querySelector('.refresh-btn');
        if (refreshBtn) {
            refreshBtn.addEventListener('click', () => {
                this.refreshContent();
            });
        }
        
        console.log('✅ Scene Outliner Controls event listeners setup complete');
    }
    
    /**
     * Switch between Scene, Live DB, and Local DB tabs
     * Official OTOY three-tab system implementation
     */
    switchTab(tabName) {
        console.log(`🔄 Switching to ${tabName} tab`);
        
        // Update tab buttons
        const tabs = this.container.querySelectorAll('.scene-tab');
        tabs.forEach(tab => {
            if (tab.dataset.tab === tabName) {
                tab.classList.add('active');
            } else {
                tab.classList.remove('active');
            }
        });
        
        // Update tab content
        const contents = this.container.querySelectorAll('.scene-tab-content');
        contents.forEach(content => {
            if (content.dataset.content === tabName) {
                content.classList.add('active');
            } else {
                content.classList.remove('active');
            }
        });
        
        this.currentTab = tabName;
        
        // Load content based on tab
        switch (tabName) {
            case 'scene':
                this.loadSceneContent();
                break;
            case 'livedb':
                this.loadLiveDBContent();
                break;
            case 'localdb':
                this.loadLocalDBContent();
                break;
        }
        
        console.log(`✅ Switched to ${tabName} tab successfully`);
    }
    
    /**
     * Toggle collapse/expand all scene nodes
     * Official OTOY collapse functionality
     */
    toggleCollapseAll() {
        console.log('🔽 Toggling collapse/expand all nodes');
        
        this.isCollapsed = !this.isCollapsed;
        const collapseBtn = this.container.querySelector('.collapse-btn');
        
        if (this.isCollapsed) {
            collapseBtn.textContent = '⊞'; // Expand symbol
            collapseBtn.title = 'Expand All';
            this.collapseAllNodes();
        } else {
            collapseBtn.textContent = '⊟'; // Collapse symbol
            collapseBtn.title = 'Collapse All';
            this.expandAllNodes();
        }
        
        console.log(`✅ ${this.isCollapsed ? 'Collapsed' : 'Expanded'} all nodes`);
    }
    
    /**
     * Refresh current tab content
     * Official OTOY refresh functionality for database content
     */
    refreshContent() {
        console.log(`🔄 Refreshing ${this.currentTab} content`);
        
        const refreshBtn = this.container.querySelector('.refresh-btn');
        refreshBtn.style.animation = 'spin 0.5s linear';
        
        setTimeout(() => {
            refreshBtn.style.animation = '';
        }, 500);
        
        switch (this.currentTab) {
            case 'scene':
                this.refreshSceneContent();
                break;
            case 'livedb':
                this.refreshLiveDBContent();
                break;
            case 'localdb':
                this.refreshLocalDBContent();
                break;
        }
        
        console.log(`✅ Refreshed ${this.currentTab} content`);
    }
    
    /**
     * Load Scene tab content (hierarchical tree)
     */
    loadSceneContent() {
        console.log('📁 Loading Scene content');
        
        // Trigger scene tree reload if Scene Outliner component exists
        if (window.sceneOutliner && typeof window.sceneOutliner.loadSceneTree === 'function') {
            window.sceneOutliner.loadSceneTree();
        }
    }
    
    /**
     * Load Live DB content (online community macros database)
     * Official OTOY: Tree structure showing macros from OctaneRender community
     */
    loadLiveDBContent() {
        console.log('🌐 Loading Live DB content - OctaneRender community macros');
        
        const liveDBContent = this.container.querySelector('[data-content="livedb"]');
        if (liveDBContent) {
            liveDBContent.innerHTML = `
                <div class="scene-tree">
                    <div class="db-loading">🌐 Connecting to OctaneRender community...</div>
                </div>
            `;
            
            // Simulate loading Live DB tree structure (in real implementation, this would connect to OTOY servers)
            setTimeout(() => {
                liveDBContent.innerHTML = `
                    <div class="scene-tree">
                        <div class="tree-node level-0" data-node-id="livedb-root">
                            <div class="node-content">
                                <span class="node-toggle expanded">−</span>
                                <span class="node-icon">🌐</span>
                                <span class="node-label">Live Database</span>
                            </div>
                        </div>
                        <div class="tree-node level-1" data-node-id="materials-category">
                            <div class="node-content">
                                <span class="node-toggle expanded">−</span>
                                <span class="node-icon">🎨</span>
                                <span class="node-label">Materials</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="metal-materials">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">⚙️</span>
                                <span class="node-label">Metal Materials (47)</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="glass-materials">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">💎</span>
                                <span class="node-label">Glass Materials (23)</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="organic-materials">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">🌿</span>
                                <span class="node-label">Organic Materials (31)</span>
                            </div>
                        </div>
                        <div class="tree-node level-1" data-node-id="nodegraphs-category">
                            <div class="node-content">
                                <span class="node-toggle expanded">−</span>
                                <span class="node-icon">🔗</span>
                                <span class="node-label">Node Graphs</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="lighting-graphs">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">💡</span>
                                <span class="node-label">Lighting Setups (15)</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="shader-graphs">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">🎭</span>
                                <span class="node-label">Shader Networks (28)</span>
                            </div>
                        </div>
                        <div class="tree-node level-1" data-node-id="macros-category">
                            <div class="node-content">
                                <span class="node-toggle expanded">−</span>
                                <span class="node-icon">📦</span>
                                <span class="node-label">Community Macros</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="procedural-macros">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">🔄</span>
                                <span class="node-label">Procedural Textures (42)</span>
                            </div>
                        </div>
                    </div>
                `;
            }, 1000);
        }
    }
    
    /**
     * Load Local DB content (local packages of Nodes, Nodegraphs, and Node trees)
     * Official OTOY: Tree structure showing local asset management with thumbnails
     */
    loadLocalDBContent() {
        console.log('💾 Loading Local DB content - Local packages and assets');
        
        const localDBContent = this.container.querySelector('[data-content="localdb"]');
        if (localDBContent) {
            localDBContent.innerHTML = `
                <div class="scene-tree">
                    <div class="db-loading">💾 Scanning local asset directory...</div>
                </div>
            `;
            
            // Simulate loading Local DB tree structure (in real implementation, this would scan local files)
            setTimeout(() => {
                localDBContent.innerHTML = `
                    <div class="scene-tree">
                        <div class="tree-node level-0" data-node-id="localdb-root">
                            <div class="node-content">
                                <span class="node-toggle expanded">−</span>
                                <span class="node-icon">💾</span>
                                <span class="node-label">Local Database</span>
                            </div>
                        </div>
                        <div class="tree-node level-1" data-node-id="project-materials">
                            <div class="node-content">
                                <span class="node-toggle expanded">−</span>
                                <span class="node-icon">📁</span>
                                <span class="node-label">Project Materials</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="custom-metals">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">⚙️</span>
                                <span class="node-label">Custom Metals (3)</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="project-glass">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">💎</span>
                                <span class="node-label">Project Glass (2)</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="wood-textures">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">🌿</span>
                                <span class="node-label">Wood Textures (4)</span>
                            </div>
                        </div>
                        <div class="tree-node level-1" data-node-id="saved-nodegraphs">
                            <div class="node-content">
                                <span class="node-toggle expanded">−</span>
                                <span class="node-icon">🔗</span>
                                <span class="node-label">Saved Node Graphs</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="lighting-setups">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">💡</span>
                                <span class="node-label">Lighting Setups (2)</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="custom-shaders">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">🎭</span>
                                <span class="node-label">Custom Shaders (5)</span>
                            </div>
                        </div>
                        <div class="tree-node level-1" data-node-id="node-packages">
                            <div class="node-content">
                                <span class="node-toggle expanded">−</span>
                                <span class="node-icon">📦</span>
                                <span class="node-label">Node Packages</span>
                            </div>
                        </div>
                        <div class="tree-node level-2" data-node-id="macro-collection">
                            <div class="node-content">
                                <span class="node-toggle collapsed">+</span>
                                <span class="node-icon">🔄</span>
                                <span class="node-label">Macro Collection (8)</span>
                            </div>
                        </div>
                    </div>
                `;
            }, 800);
        }
    }
    
    /**
     * Refresh Scene content
     */
    refreshSceneContent() {
        if (window.sceneOutliner && typeof window.sceneOutliner.loadSceneTree === 'function') {
            window.sceneOutliner.loadSceneTree();
        }
    }
    
    /**
     * Refresh Live DB content
     */
    refreshLiveDBContent() {
        this.loadLiveDBContent();
    }
    
    /**
     * Refresh Local DB content
     */
    refreshLocalDBContent() {
        this.loadLocalDBContent();
    }
    
    /**
     * Collapse all scene nodes
     */
    collapseAllNodes() {
        const sceneTree = document.querySelector('#scene-tree');
        if (sceneTree) {
            const expandedNodes = sceneTree.querySelectorAll('.node-toggle.expanded');
            expandedNodes.forEach(toggle => {
                toggle.classList.remove('expanded');
                toggle.classList.add('collapsed');
            });
            
            // Hide all child nodes
            const childNodes = sceneTree.querySelectorAll('.tree-node[class*="level-"]:not(.level-0)');
            childNodes.forEach(node => {
                node.style.display = 'none';
            });
        }
    }
    
    /**
     * Expand all scene nodes
     */
    expandAllNodes() {
        const sceneTree = document.querySelector('#scene-tree');
        if (sceneTree) {
            const collapsedNodes = sceneTree.querySelectorAll('.node-toggle.collapsed');
            collapsedNodes.forEach(toggle => {
                toggle.classList.remove('collapsed');
                toggle.classList.add('expanded');
            });
            
            // Show all child nodes
            const childNodes = sceneTree.querySelectorAll('.tree-node[class*="level-"]:not(.level-0)');
            childNodes.forEach(node => {
                node.style.display = 'block';
            });
        }
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = SceneOutlinerControls;
}