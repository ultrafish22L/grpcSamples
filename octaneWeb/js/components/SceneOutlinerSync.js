/**
 * Scene Outliner with SYNCHRONOUS API calls
 * Demonstrates proper architectural pattern:
 * - gRPC calls are BLOCKING/SYNCHRONOUS (sequential dependencies)
 * - UI updates are ASYNCHRONOUS (non-blocking)
 */

class SceneOutlinerSync {
    constructor(element, eventSystem) {
        this.element = element;
        this.eventSystem = eventSystem;
        this.lastSceneItems = [];
        this.expandedNodes = new Set(['scene-root']);
        this.searchTerm = '';
        
        this.setupEventHandlers();
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
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) {
            console.error('❌ Scene tree container not found');
            return;
        }
        
        // Show loading state immediately - UI is responsive
        treeContainer.innerHTML = '<div class="scene-loading">🔍 Loading scene from Octane...</div>';
        
        try {
            console.log('🔒 Starting SYNCHRONOUS scene tree loading sequence...');
            
            // All API calls are now SYNCHRONOUS and BLOCKING
            // This ensures proper sequential dependencies
            const sceneItems = this.loadSceneTreeSync();
            
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
     * All calls depend on previous results - must be sequential
     * @returns {Array} Scene items array
     */
    loadSceneTreeSync() {
        console.log('🔒 SYNC: Starting synchronous scene tree loading...');
        
        // STEP 1: Get the root node graph (BLOCKING)
        console.log('🔒 SYNC: Getting root node graph...');
        const rootResult = window.grpcApi.makeApiCallSync('ApiProjectManager/rootNodeGraph');
        
        if (!rootResult.success) {
            throw new Error('Failed to get root node graph');
        }
        
        console.log('📋 SYNC: Root node graph result:', rootResult);
        
        // STEP 2: Get owned items from the root node graph (BLOCKING - depends on step 1)
        console.log('🔒 SYNC: Getting owned items...');
        const ownedItemsResult = window.grpcApi.makeApiCallSync(
            'ApiNodeGraph/getOwnedItems', 
            rootResult.data.result.handle  // DEPENDS on step 1 result
        );
        
        if (!ownedItemsResult.success) {
            throw new Error('Failed to get owned items');
        }
        
        console.log('📋 SYNC: Owned items result:', ownedItemsResult);
        
        // STEP 3: Get the size of the item array (BLOCKING - depends on step 2)
        console.log('🔒 SYNC: Getting array size...');
        const sizeResult = window.grpcApi.makeApiCallSync(
            'ApiItemArray/size', 
            ownedItemsResult.data.list.handle  // DEPENDS on step 2 result
        );
        
        if (!sizeResult.success) {
            throw new Error('Failed to get array size');
        }
        
        console.log('📋 SYNC: Array size result:', sizeResult);
        
        // STEP 4: Get all items (BLOCKING - depends on step 2)
        console.log('🔒 SYNC: Getting all items...');
        const itemsResult = window.grpcApi.makeApiCallSync(
            'ApiItemArray/items', 
            ownedItemsResult.data.list.handle  // DEPENDS on step 2 result
        );
        
        if (!itemsResult.success || !itemsResult.data.result || !itemsResult.data.result.data) {
            throw new Error('Failed to get items array');
        }
        
        const items = itemsResult.data.result.data;
        console.log(`📋 SYNC: Got ${items.length} items to process`);
        
        // STEP 5: Process each item (BLOCKING - depends on step 4)
        const sceneItems = [];
        
        for (let i = 0; i < items.length; i++) {
            const item = items[i];
            const handle = item.handle;
            const type = item.type;
            
            console.log(`🔒 SYNC: Processing item ${i + 1}/${items.length}: handle=${handle}, type=${type}`);
            
            // Get the actual name of the API item (BLOCKING)
            let actualName = `Item_${handle}`;  // Default fallback name
            let superclass = 'unknown';
            
            try {
                // Get name (BLOCKING)
                console.log(`🔒 SYNC: Getting name for handle ${handle}`);
                const nameResult = window.grpcApi.makeApiCallSync(
                    'ApiItem/name',
                    handle
                );
                
                if (nameResult.success && nameResult.data.result) {
                    actualName = nameResult.data.result;
                    console.log(`✅ SYNC: Got name: "${actualName}" for handle ${handle}`);
                } else {
                    console.warn(`⚠️ SYNC: Name call failed for handle ${handle}:`, nameResult);
                }
                
                // Get superclass (BLOCKING)
                console.log(`🔒 SYNC: Getting superclass for handle ${handle}`);
                const superclassResult = window.grpcApi.makeApiCallSync(
                    'ApiItem/superclass',
                    handle
                );
                
                if (superclassResult.success && superclassResult.data.result) {
                    superclass = superclassResult.data.result;
                    console.log(`✅ SYNC: Got superclass: "${superclass}" for handle ${handle}`);
                } else {
                    console.warn(`⚠️ SYNC: Superclass call failed for handle ${handle}:`, superclassResult);
                }
                
            } catch (error) {
                console.error(`💥 SYNC: Exception processing item ${handle}:`, error);
                // Continue processing other items even if one fails
            }
            
            sceneItems.push({
                name: actualName,
                handle: handle,
                type: type,
                superclass: superclass,
                children: []
            });
            
            console.log(`✅ SYNC: Added item to scene: ${actualName} [${handle}]`);
        }
        
        console.log(`🔒 SYNC: Completed processing ${sceneItems.length} items`);
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
                const icon = this.getIconForSuperclass(item.superclass);
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
    
    getIconForSuperclass(superclass) {
        const iconMap = {
            'unknown': '⬜',
            'mesh': '▲',
            'camera': '📷',
            'light': '💡',
            'material': '🎨',
            'texture': '🖼️',
            'group': '📁'
        };
        
        return iconMap[superclass] || '⬜';
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