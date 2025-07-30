/**
 * Scene Outliner with SYNCHRONOUS API calls
 * Demonstrates proper architectural pattern:
 * - gRPC calls are BLOCKING/SYNCHRONOUS (sequential dependencies)
 * - UI updates are ASYNCHRONOUS (non-blocking)
 */

class SceneOutlinerSync {
    constructor(element, eventSystem) {
        console.log('🔍 DEBUG: SceneOutlinerSync constructor called');
        console.log('🔍 DEBUG: element:', element);
        console.log('🔍 DEBUG: eventSystem:', eventSystem);
        
        this.element = element;
        this.eventSystem = eventSystem;
        this.lastSceneItems = [];
        this.expandedNodes = new Set(['scene-root']);
        this.searchTerm = '';
        
        this.setupEventHandlers();
        
        // Auto-load scene tree after a short delay
        console.log('🔍 DEBUG: Setting up auto-load timer...');
        setTimeout(() => {
            console.log('🔍 DEBUG: Auto-loading scene tree...');
            this.loadSceneTree();
        }, 1000);
    }
    
    setupEventHandlers() {
        // Search functionality
        const searchInput = this.element.querySelector('#scene-search');
        if (searchInput) {
            this.addEventListener(searchInput, 'input', (e) => {
                this.searchTerm = e.target.value.toLowerCase();
                
                // Use real scene data if available
                if (this.lastSceneItems && this.lastSceneItems.length > 0) {
                    this.renderRealSceneTree(this.lastSceneItems);
                }
            });
        }
    }
    
    /**
     * ASYNCHRONOUS function that loads scene tree
     * UI loads immediately, then updates when scene data is ready
     */
    async loadSceneTree() {
        console.log('🔍 DEBUG: loadSceneTree() called');
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) {
            console.error('❌ Scene tree container not found');
            return;
        }
        
        console.log('🔍 DEBUG: Found tree container, showing loading state');
        // Show loading state immediately - UI is responsive
        treeContainer.innerHTML = '<div class="scene-loading">🔍 Loading scene from Octane...</div>';
        
        console.log('🔍 DEBUG: Checking grpcApi availability...');
        console.log('🔍 DEBUG: window.grpcApi available?', !!window.grpcApi);
        console.log('🔍 DEBUG: makeApiCallSync method available?', !!(window.grpcApi && window.grpcApi.makeApiCallSync));
        
        try {
            console.log('🔒 Starting SYNCHRONOUS scene tree loading sequence...');
            
            // All API calls are now SYNCHRONOUS and BLOCKING
            // This ensures proper sequential dependencies
            console.log('🔍 DEBUG: About to call loadSceneTreeSync()...');
            const sceneItems = this.loadSceneTreeSync();
            console.log('🔍 DEBUG: loadSceneTreeSync() returned:', sceneItems);
            
            // Store scene data for later requests
            this.lastSceneItems = sceneItems;
            
            // Render the real scene tree (UI update happens here)
            this.renderRealSceneTree(sceneItems);
            
            // Update other components with real scene data
            this.eventSystem.emit('sceneDataLoaded', sceneItems);
            
            console.log('✅ Scene tree loading completed successfully');
            
        } catch (error) {
            console.error('❌ Failed to load scene tree:', error);
            
            // Clear stored scene data and notify other components
            this.lastSceneItems = [];
            this.eventSystem.emit('sceneDataLoaded', []);
            
            treeContainer.innerHTML = `
                <div class="scene-error">
                    <div class="error-icon">⚠️</div>
                    <div class="error-title">Octane Not Available</div>
                    <div class="error-message">
                        Please start Octane Render on 127.0.0.1:51022<br>
                        <small>Error: ${error.message}</small>
                    </div>
                    <div class="error-actions">
                        <button onclick="window.sceneOutliner.loadSceneTree()" class="retry-btn">🔄 Retry</button>
                    </div>
                </div>
            `;
        }
    }
    
    /**
     * SYNCHRONOUS scene tree loading with blocking API calls
     * STRUCTURED DEBUGGING: Isolate exactly where Octane crashes
     * @returns {Array} Scene items array
     */
    loadSceneTreeSync() {
        console.log('🔍 DEBUG: Starting synchronous scene tree loading...');
        
        let result;
        // STEP 1: Get the root node graph (BLOCKING)
        result = window.grpcApi.makeApiCallSync(
            'ApiProjectManager/rootNodeGraph'
        );
        if (!result.success) {
            throw new Error('Failed to get root node graph');
        }
        // STEP 2: Get owned items from the root node graph (BLOCKING - depends on step 1)
        result = window.grpcApi.makeApiCallSync(
            'ApiNodeGraph/getOwnedItems', 
            result.data.result.handle  // DEPENDS on step 1 result
        );
        if (!result.success) {
            throw new Error('Failed to get owned items');
        }
        const ownedItemsHandle = result.data.list.handle

        // STEP 3: Get the size of the item array (BLOCKING - depends on step 2)
        result = window.grpcApi.makeApiCallSync(
            'ApiItemArray/size', 
            result.data.list.handle  // DEPENDS on step 2 result
        );
        if (!result.success) {
            throw new Error('Failed to get array size');
        }
        const size = result.data.result;
        const sceneItems = [];

        for (let i = 0; i < size; i++) {
            // STEP 4: Get the item
            result = window.grpcApi.makeApiCallSync(
                'ApiItemArray/get1', 
                ownedItemsHandle,
                {index: i},
            );
            if (!result.success) {
                throw new Error('Failed to get item');
            }
            const item = result.data.result;
            let itemName = `Item_${item.handle}`;  // Default fallback name
            
            // SAFE API CALL: Test name call with error isolation
            result = window.grpcApi.makeApiCallSync(
                'ApiItem/name',
                item.handle
            );
            if (!result.success) {
                throw new Error('Failed to get item name');
            }
            itemName = result.data.result;

            result = window.grpcApi.makeApiCallSync(
                'ApiItem/outType',
                item.handle
            );
            if (!result.success) {
                throw new Error('Failed to get item outtype');
            }
            sceneItems.push({
                name: itemName,
                handle: item.handle,
                type: item.type,
                outtype: result.data.result,
                children: []
            });
        }
        return sceneItems;
    }
    
    renderRealSceneTree(sceneItems) {
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) return;
        
        if (sceneItems.length === 0) {
            treeContainer.innerHTML = `
                <div class="scene-empty">
                    <div class="empty-icon">📁</div>
                    <div class="empty-message">No scene items found</div>
                </div>
            `;
            return;
        }
        
        // Filter items based on search term
        const filteredItems = sceneItems.filter(item => 
            item.name.toLowerCase().includes(this.searchTerm)
        );
        
        let treeHTML = `
            <div class="scene-node scene-root" data-node-id="scene-root">
                <div class="node-content">
                    <span class="node-toggle ${this.expandedNodes.has('scene-root') ? 'expanded' : 'collapsed'}">▼</span>
                    <span class="node-icon">🌍</span>
                    <span class="node-name">Scene</span>
                    <span class="node-visibility" data-handle="scene-root">👁</span>
                </div>
        `;
        
        if (this.expandedNodes.has('scene-root')) {
            filteredItems.forEach(item => {
                const icon = this.getIconFor(item.outtype);
                const nodeId = `item-${item.handle}`;
                
                treeHTML += `
                    <div class="scene-node scene-item" data-node-id="${nodeId}" data-handle="${item.handle}">
                        <div class="node-content">
                            <span class="node-spacer"></span>
                            <span class="node-icon">${icon}</span>
                            <span class="node-name">${item.name}</span>
                            <span class="node-handle">[${item.handle}]</span>
                            <span class="node-visibility" data-handle="${item.handle}">👁</span>
                        </div>
                    </div>
                `;
            });
        }
        
        treeHTML += '</div>';
        treeContainer.innerHTML = treeHTML;
        
        // Add event handlers
        this.addTreeEventHandlers(treeContainer);
    }
    
    getIconFor(outtype) {
        const iconMap = {
            'unknown': '⬜',
            'mesh': '▲',
            'camera': '📷',
            'light': '💡',
            'material': '🎨',
            'texture': '🖼️',
            'group': '📁'
        };
        
        return iconMap[outtype] || '⬜';
    }
    
    addTreeEventHandlers(treeContainer) {
        // Add click handlers for expand/collapse
        const toggles = treeContainer.querySelectorAll('.node-toggle');
        toggles.forEach(toggle => {
            this.addEventListener(toggle, 'click', (e) => {
                e.stopPropagation();
                const nodeElement = e.target.closest('.scene-node');
                const nodeId = nodeElement.dataset.nodeId;
                
                if (this.expandedNodes.has(nodeId)) {
                    this.expandedNodes.delete(nodeId);
                } else {
                    this.expandedNodes.add(nodeId);
                }
                
                // Re-render tree to show/hide children
                this.renderRealSceneTree(this.lastSceneItems || []);
            });
        });
        
        // Add click handlers for scene nodes
        const sceneNodes = treeContainer.querySelectorAll('.scene-node');
        sceneNodes.forEach(node => {
            this.addEventListener(node, 'click', (e) => {
                if (e.target.classList.contains('node-toggle')) return;
                
                // Remove previous selection
                treeContainer.querySelectorAll('.scene-node').forEach(n => n.classList.remove('selected'));
                
                // Add selection to clicked node
                node.classList.add('selected');
                
                // Emit selection event
                const handle = node.dataset.handle;
                if (handle && handle !== 'scene-root') {
                    this.eventSystem.emit('nodeSelected', { handle: handle });
                }
            });
        });
    }
    
    addEventListener(element, event, handler) {
        element.addEventListener(event, handler);
    }
    

}

// Export for use
window.SceneOutlinerSync = SceneOutlinerSync;