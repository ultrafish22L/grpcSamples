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
        this.expandedNodes = new Set(['scene-root', 'item-1000025']); // Expand Scene and Render target by default
        this.searchTerm = '';
        this.selectedNodeHandle = null;
        this.selectedNodeName = null;
        
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
        
        // Listen for node selection from NodeGraphEditor to sync selection
        this.eventSystem.on('nodeGraphNodeSelected', (data) => {
            this.updateSelectionFromNodeGraph(data);
        });
    }
    
    // Unified selection function - called both on initialization and user clicks
    selectNode(handle, nodeName, nodeId = null, source = 'programmatic') {
        console.log('🎯 Unified selectNode called:', { handle, nodeName, nodeId, source });
        
        // Update internal state
        this.selectedNodeHandle = handle;
        this.selectedNodeName = nodeName;
        
        // Update visual selection in tree
        const treeContainer = this.element.querySelector('.scene-tree');
        if (treeContainer) {
            // Remove previous selection
            treeContainer.querySelectorAll('.tree-node').forEach(n => n.classList.remove('selected'));
            
            // Add selection to target node
            const targetNode = treeContainer.querySelector(`[data-handle="${handle}"]`);
            if (targetNode) {
                targetNode.classList.add('selected');
            }
        }
        
        // Emit selection event to update other components
        if (handle && handle !== 'scene-root') {
            this.eventSystem.emit('sceneNodeSelected', { 
                handle: handle,
                nodeId: nodeId || `item-${handle}`,
                nodeName: nodeName,
                source: source
            });
            
            console.log('🎯 Unified selection emitted:', { handle, nodeName, source });
        }
    }

    updateSelectionFromNodeGraph(data) {
        console.log('🎯 SceneOutliner received NodeGraph selection:', data);
        
        // Find and select the corresponding node in the scene tree
        const treeContainer = this.element.querySelector('.tree-container');
        if (!treeContainer) return;
        
        // Clear existing selection
        treeContainer.querySelectorAll('.tree-node').forEach(n => n.classList.remove('selected'));
        
        // Find the node by name or handle and select it
        const treeNodes = treeContainer.querySelectorAll('.tree-node');
        treeNodes.forEach(node => {
            const nodeName = node.querySelector('.node-name')?.textContent || '';
            const handle = node.dataset.handle;
            
            if (nodeName === data.nodeName || handle === data.sceneHandle) {
                node.classList.add('selected');
                console.log('🎯 SceneOutliner synced selection to:', nodeName);
            }
        });
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
            const sceneItems = this.loadSceneTreeSync(null, [], 0);
            
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
    loadSceneTreeSync(itemHandle, sceneItems, level) {
        let result;
        if (level >= 2)
            return sceneItems;
        level = level + 1;

        try {
            if (itemHandle == null)
            {
                // Get the itemHandle node
                result = window.grpcApi.makeApiCallSync(
                    'ApiProjectManager/rootNodeGraph'
                );
                if (!result.success) {
                    throw new Error('Failed ApiProjectManager/rootNodeGraph');
                }
                itemHandle = result.data.result.handle;
            }
            // Get isGraph
            result = window.grpcApi.makeApiCallSync(
                'ApiItem/isGraph', 
                itemHandle 
            );
            if (!result.success) {
                throw new Error('Failed ApiItem/isGraph');
            }
            if (result.data.result)
            {
                // its a graph
                // Get owned items
                result = window.grpcApi.makeApiCallSync(
                    'ApiNodeGraph/getOwnedItems', 
                    itemHandle
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodeGraph/getOwnedItems');
                }
                const ownedItemsHandle = result.data.list.handle

                // Get the size of the item array
                result = window.grpcApi.makeApiCallSync(
                    'ApiItemArray/size', 
                    result.data.list.handle
                );
                if (!result.success) {
                    throw new Error('Failed ApiItemArray/size');
                }
                const size = result.data.result;

                for (let i = 0; i < size; i++) {
                    // Get the item
                    result = window.grpcApi.makeApiCallSync(
                        'ApiItemArray/get1', 
                        ownedItemsHandle,
                        {index: i},
                    );
                    if (!result.success) {
                        throw new Error('Failed ApiItemArray/get1');
                    }
                    this.addSceneItem(result.data.result, sceneItems, level, null);
                }
                return sceneItems
            }
            // its a node
            // Get the pins
            result = window.grpcApi.makeApiCallSync(
                'ApiNode/pinCount', 
                itemHandle
            );
            if (!result.success) {
                throw new Error('Failed ApiNode/pinCount');
            }
            const pinCount = result.data.result;

            for (let i = 0; i < pinCount; i++) {
                // Get the pin info
                result = window.grpcApi.makeApiCallSync(
                    'ApiNode/pinInfoIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinInfoIx');
                }
                const pinInfo = result.data.result;

                // Get the pin connected node
                result = window.grpcApi.makeApiCallSync(
                    'ApiNode/connectedNodeIx', 
                    itemHandle,
                    {pinIx: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/connectedNodeIx');
                }                
                this.addSceneItem(result.data.result, sceneItems, level, pinInfo);
            }
        } catch (error) {
            console.error('❌ Failed loadSceneTreeSync:', error);
        }
        return sceneItems;
    }
    
        
    /**

     */
    addSceneItem(item, sceneItems, level, pinInfo) { 

        let itemName;
        let outType;

        if (!item || !item.handle)
            return;

        try {
            let result;
            
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
            outType = result.data.result;

            if (pinInfo) {
                console.log("  pinInfo", pinInfo);

                result = window.grpcApi.makeApiCallSync(
                    'ApiNodePinInfoEx/getApiNodePinInfo',
                    pinInfo.handle,
                );
                if (!result.success) {
                    throw new Error('Failed to get item outtype');
                }
                console.log("  ", result.data);
            }
        } catch (error) {
            console.error('❌ Failed addSceneItem:', error);
        }

        let children = [];
        children = this.loadSceneTreeSync(item.handle, children, level);

        console.log("ADDING ", itemName, outType);


        sceneItems.push({
            name: itemName,
            handle: item.handle,
            type: item.type,
            outtype: outType,
            children: children,
        });
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
        
        // Create Scene root node
        let treeHTML = `
            <div class="tree-node scene-root level-0" data-node-id="scene-root">
                <div class="node-content">
                    <span class="node-toggle ${this.expandedNodes.has('scene-root') ? 'expanded' : 'collapsed'}"></span>
                    <span class="node-icon">📁</span>
                    <span class="node-name">Scene</span>
                </div>
            </div>
        `;
        
        // Add child items recursively if Scene is expanded
        if (this.expandedNodes.has('scene-root')) {
            treeHTML += this.renderTreeLevel(sceneItems, 1);
        }
        
        treeContainer.innerHTML = treeHTML;
        
        // Add event handlers
        this.addTreeEventHandlers(treeContainer);
    }
    
    renderTreeLevel(items, level) {
        let html = '';
        
        // Filter items based on search term
        const filteredItems = items.filter(item => 
            !this.searchTerm || 
            (item.name && item.name.toLowerCase().includes(this.searchTerm))
        );
        
        filteredItems.forEach(item => {
            const icon = this.getOctaneIconFor(item.outtype, item.name);
            const nodeId = `item-${item.handle}`;
            const isSelected = item.name === 'Render target'; // Match Octane screenshot
            const hasChildren = item.children && item.children.length > 0;
            const isExpanded = this.expandedNodes.has(nodeId);
            
            html += `
                <div class="tree-node scene-item level-${level} ${isSelected ? 'selected' : ''}" data-node-id="${nodeId}" data-handle="${item.handle}">
                    <div class="node-content">
                        ${hasChildren ? 
                            `<span class="node-toggle ${isExpanded ? 'expanded' : 'collapsed'}"></span>` : 
                            '<span class="node-spacer"></span>'
                        }
                        <span class="node-icon">${icon}</span>
                        <span class="node-name">${item.name}</span>
                    </div>
                </div>
            `;
            
            // Recursively render children if expanded
            if (hasChildren && isExpanded) {
                html += this.renderTreeLevel(item.children, level + 1);
            }
        });
        
        return html;
    }
    
    getOctaneIconFor(outtype, name) {
        // Match exact Octane icons based on name and type
        if (name === 'Render target') {
            return '🎯'; // Target icon for render target
        }
        if (name === 'teapot.obj' || (name && name.includes('.obj'))) {
            return '🫖'; // Teapot icon for mesh objects
        }
        if (name === 'Daylight environment' || (name && name.includes('environment'))) {
            return '🌍'; // Environment icon
        }
        if (name === 'Film settings') {
            return '🎬'; // Film settings icon
        }
        if (name === 'Animation settings') {
            return '⏱️'; // Animation icon
        }
        if (name === 'Direct lighting kernel' || (name && name.includes('kernel'))) {
            return '🔧'; // Kernel icon
        }
        if (name === 'Render layer') {
            return '🎭'; // Render layer icon
        }
        if (name === 'Render passes') {
            return '📊'; // Render passes icon
        }
        if (name === 'Output AOV group') {
            return '📤'; // Output AOVs icon
        }
        if (name === 'Imager') {
            return '📷'; // Imager icon
        }
        if (name === 'Post processing') {
            return '⚙️'; // Post processing icon
        }
        
        // Handle parameter types with specific icons
        if (outtype === 'PT_BOOL' || name === 'Bool value') {
            return '☑️'; // Checkbox for boolean parameters
        }
        if (outtype === 'PT_FLOAT' || name === 'Float value') {
            return '🔢'; // Numbers for float parameters
        }
        if (outtype === 'PT_INT' || name === 'Int value') {
            return '🔢'; // Numbers for integer parameters
        }
        if (outtype === 'PT_ENUM' || name === 'Enum value') {
            return '📋'; // List for enum parameters
        }
        if (outtype === 'PT_RGB' || name === 'RGB color') {
            return '🎨'; // Color palette for RGB parameters
        }
        
        // Fallback based on type
        const iconMap = {
            'PT_RENDER_TARGET': '🎯',
            'PT_MESH': '🫖',
            'PT_GEOMETRY': '🫖',
            'PT_CAMERA': '📷',
            'PT_LIGHT': '💡',
            'PT_MATERIAL': '🎨',
            'PT_ENVIRONMENT': '🌍',
            'PT_FILM_SETTINGS': '🎬',
            'PT_ANIMATION_SETTINGS': '⏱️',
            'PT_KERNEL': '🔧',
            'PT_RENDER_LAYER': '🎭',
            'PT_RENDER_PASSES': '📊',
            'PT_OUTPUT_AOV_GROUP': '📤',
            'PT_IMAGER': '📷',
            'PT_POSTPROCESSING': '⚙️',
            'unknown': '⬜'
        };
        
        return iconMap[outtype] || '⬜';
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
                const nodeElement = e.target.closest('.tree-node');
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
        const sceneNodes = treeContainer.querySelectorAll('.tree-node');
        sceneNodes.forEach(node => {
            this.addEventListener(node, 'click', (e) => {
                if (e.target.classList.contains('node-toggle')) return;
                
                // Use unified selection function
                const handle = node.dataset.handle;
                const nodeId = node.dataset.nodeId;
                const nodeName = node.querySelector('.node-name')?.textContent || '';
                
                this.selectNode(handle, nodeName, nodeId, 'sceneOutliner');
            });
        });
        
        // Auto-select "Render target" on initial load (matching Octane Studio behavior)
        if (!this.selectedNodeHandle) {
            const renderTargetNode = treeContainer.querySelector('.tree-node .node-name');
            if (renderTargetNode) {
                // Find the Render target node
                const allNodes = treeContainer.querySelectorAll('.tree-node');
                for (const node of allNodes) {
                    const nodeName = node.querySelector('.node-name')?.textContent;
                    if (nodeName === 'Render target') {
                        const handle = node.dataset.handle;
                        const nodeId = node.dataset.nodeId;
                        console.log('🎯 Auto-selecting Render target on initialization:', { handle, nodeName, nodeId });
                        
                        // Small delay to ensure NodeGraphEditor has created nodes
                        setTimeout(() => {
                            this.selectNode(handle, nodeName, nodeId, 'initialization');
                        }, 100);
                        break;
                    }
                }
            }
        }
    }
    
    addEventListener(element, event, handler) {
        element.addEventListener(event, handler);
    }
    

}

// Export for use
window.SceneOutlinerSync = SceneOutlinerSync;