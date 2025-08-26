/**
 * Scene Outliner with Synchronous API Integration
 * 
 * Hierarchical scene tree component that displays the complete Octane scene
 * structure with real-time synchronization to the Octane LiveLink service.
 * Provides node selection, search functionality, and expand/collapse controls.
 * 
 * Core Features:
 * - Real-time scene tree synchronization with Octane LiveLink
 * - Hierarchical display with expand/collapse functionality
 * - Node selection with cross-component event coordination
 * - Search and filtering capabilities for large scenes
 * - Professional Octane-style UI with proper icons and styling
 * - Auto-selection of render target on initialization
 * 
 * Technical Architecture:
 * - Synchronous gRPC API calls for reliable data consistency
 * - Asynchronous UI updates for responsive user experience
 * - Event-driven communication with NodeInspector and NodeGraph
 * - Cached scene data for performance optimization
 * - Unified selection events across all components
 * 
 * API Integration:
 * - Uses buildSceneTree API for hierarchical scene data
 * - Maintains node handle to name mapping for efficient lookups
 * - Coordinates with NodeInspector for parameter editing
 * - Synchronizes selection state across all UI components
 */

class SceneOutlinerSync {
    constructor(element, eventSystem) {
        console.log('DEBUG: SceneOutlinerSync constructor called');
        console.log('DEBUG: element:', element);
        console.log('DEBUG: eventSystem:', eventSystem);
        
        this.element = element;
        this.eventSystem = eventSystem;
        this.lastScene = {};
        this.scene = { map:[], items:null };

        this.expandedNodes = new Set(['scene-root', 'item-1000025']); // Expand Scene and Render target by default
        this.searchTerm = '';
        this.selectedNodeHandle = null;
        
        this.setupEventHandlers();
        
        // Auto-load scene tree after a short delay
        console.log('DEBUG: Setting up auto-load timer...');
        setTimeout(() => {
            console.log('DEBUG: Auto-loading scene tree...');
            this.loadSceneTree();
        }, 100);
    }
    
    setupEventHandlers() {
        // Search functionality
        const searchInput = this.element.querySelector('#scene-search');
        if (searchInput) {
            this.addEventListener(searchInput, 'input', (e) => {
                this.searchTerm = e.target.value.toLowerCase();
                
                // Use real scene data if available
                if (this.lastScene && this.lastScene.items.length > 0) {
                    this.renderRealSceneTree(this.lastScene);
                }
            });
        }
        // Listen for scene node selection (unified event for all components)
        this.eventSystem.on('sceneNodeSelected', (handle) => {
//            this.updateSelectedNode(handle);
        });
        
    }
    
    // Unified selection function - called both on initialization and user clicks
    selectNode(handle, nodeName, nodeId = null, source = 'programmatic') {
        console.log('Unified selectNode called:', { handle, nodeName, nodeId, source });
        
        // Update internal state
        this.selectedNodeHandle = handle;
        
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
    }


    
    /**
     * ASYNCHRONOUS function that loads scene tree
     * UI loads immediately, then updates when scene data is ready
     */
    async loadSceneTree() {
        console.log('DEBUG: loadSceneTree() called');
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) {
            console.error('❌ Scene tree container not found');
            return;
        }
        
        console.log('DEBUG: Found tree container, showing loading state');
        // Show loading state immediately - UI is responsive
        treeContainer.innerHTML = '<div class="scene-loading">Loading scene from Octane...</div>';
        
        console.log('DEBUG: Checking grpcApi availability...');
        console.log('DEBUG: window.grpcApi available?', !!window.grpcApi);
        console.log('DEBUG: makeApiCallSync method available?', !!(window.grpcApi && window.grpcApi.makeApiCallSync));
        
        try {
            console.log('Starting SYNCHRONOUS scene tree loading sequence...');
            
            // All API calls are now SYNCHRONOUS and BLOCKING
            // This ensures proper sequential dependencies
            console.log('DEBUG: About to call loadSceneTreeSync()...');
            this.scene.items = this.loadSceneTreeSync();
            
            // Store scene data for later requests
            this.lastScene = this.scene;
            
            // Render the real scene tree (UI update happens here)
            this.renderRealSceneTree(this.scene);
            
            // Update other components with real scene data
            this.eventSystem.emit('sceneDataLoaded', this.scene);
            
            console.log('Scene tree loading completed successfully');
            
        } catch (error) {
            console.error('❌ Failed to load scene tree:', error);
            
            // Clear stored scene data and notify other components
            this.lastScene = {};
            this.scene = {}
            this.eventSystem.emit('sceneDataLoaded', {});
            
            treeContainer.innerHTML = `
                <div class="scene-error">
                    <div class="error-icon"></div>
                    <div class="error-title">Octane Not Available</div>
                    <div class="error-message">
                        Please start Octane Render on 127.0.0.1:51022<br>
                        <small>Error: ${error.message}</small>
                    </div>
                    <div class="error-actions">
                        <button onclick="window.sceneOutliner.loadSceneTree()" class="retry-btn">Retry</button>
                    </div>
                </div>
            `;
        }
    }

    delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }




    /**
     * SYNCHRONOUS scene tree loading with blocking API calls
     * STRUCTURED DEBUGGING: Isolate exactly where Octane crashes
     * @returns {Array} Scene items array
     */
    loadSceneTreeSync(itemHandle = null, sceneItems = null, level = 0) {
        let result;
//        if (level >= 3)
//            return scene;
        level = level + 1;

        if (sceneItems == null) {
            sceneItems = [];
        }
        let graphInfo
        let nodeInfo
        try {
            if (itemHandle == null)
            {
                // first call, get the root
                result = window.grpcApi.makeApiCallSync(
                    'ApiProjectManager/rootNodeGraph'
                );
                if (!result.success) {
                    throw new Error('Failed ApiProjectManager/rootNodeGraph');
                }
                itemHandle = result.data.result.handle;
            }
            // is it a graph or node?
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
                result = window.grpcApi.makeApiCallSync(
                    'ApiNodeGraph/info1', 
                    itemHandle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodeGraph/info1');
                }
                graphInfo = result.data.data;

                // Get owned items
                result = window.grpcApi.makeApiCallSync(
                    'ApiNodeGraph/getOwnedItems', 
                    itemHandle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodeGraph/getOwnedItems');
                }
                const ownedItemsHandle = result.data.list.handle

                // Get the size of the item array
                result = window.grpcApi.makeApiCallSync(
                    'ApiItemArray/size', 
                    ownedItemsHandle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiItemArray/size');
                }
                const size = result.data.result;

                for (let i = 0; i < size; i++) {
                    // get it
                    result = window.grpcApi.makeApiCallSync(
                        'ApiItemArray/get', 
                        ownedItemsHandle,
                        {index: i},
                    );
                    if (!result.success) {
                        throw new Error('Failed ApiItemArray/get');
                    }
                    // will recurse to loadSceneTreeSync()
                    this.addSceneItem(sceneItems, result.data.result, level, graphInfo);
                }
//                sceneItems.sort((a, b) => a.handle - b.handle); 

                return sceneItems
            }
            // its a node
            result = window.grpcApi.makeApiCallSync(
                'ApiNode/info', 
                itemHandle,
            );
            if (!result.success) {
                throw new Error('Failed ApiNode/info');
            }
            nodeInfo = result.data.result
                        
            // Get the pins
            // pinCount may not == pinInfoCount
            let pinCount = nodeInfo.pinInfoCount;

            result = window.grpcApi.makeApiCallSync(
                'ApiNode/pinCount', 
                itemHandle
            );
            if (!result.success) {
                throw new Error('Failed ApiNode/pinCount');
            }
            pinCount = result.data.result;
            console.log(`pinCount = ${pinCount} nodeInfo.pinInfoCount = ${nodeInfo.pinInfoCount}`);  

            for (let i = 0; i < pinCount; i++) {
                // Get the pin connected node
                result = window.grpcApi.makeApiCallSync(
                    'ApiNode/connectedNodeIx', 
                    itemHandle,
                    { pinIx: i, enterWrapperNode: true },
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/connectedNodeIx');
                }        
                const connectedNode = result.data.result;

                if (connectedNode == null) {
                    continue;
                }
                // Get the pin label
                result = window.grpcApi.makeApiCallSync(
                    'ApiNode/pinLabelIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinLabelIx');
                }
                let pinInfo = { staticLabel: result.data.result, index:i };

                // Get the pin type
                result = window.grpcApi.makeApiCallSync(
                    'ApiNode/pinTypeIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinTypeIx');
                }
                pinInfo.type = result.data.result;
//                console.log('pinInfo.type', pinInfo.type);

//                pinInfo.type = window.OctaneTypes.NodePinType[pinInfo.type];
//                console.log('pinInfo.type', pinInfo.type);
/*                
                // Get the pin info handle
                result = window.grpcApi.makeApiCallSync(
                    'ApiNode/pinInfoIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinInfoIx');
                }

                console.log('before ApiNodePinInfoEx/getApiNodePinInfo', result.data.result.handle);

                // Get the pin info 
                result = window.grpcApi.makeApiCallSync(
                    'ApiNodePinInfoEx/getApiNodePinInfo', 
                    result.data.result.handle
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodePinInfoEx/getApiNodePinInfo');
                }
                console.log('pinInfo ', JSON.stringify(result));
                pinInfo = result.data.result;
*/
                // will recurse to loadSceneTreeSync()
                this.addSceneItem(sceneItems, connectedNode, level, graphInfo, nodeInfo, pinInfo);
            }
        } catch (error) {
            console.error('❌ Failed loadSceneTreeSync:', error);
        }
//        sceneItems.sort((a, b) => a.handle - b.handle); 
        return sceneItems;
    }
    
        
    /**

     */
    addSceneItem(sceneItems, item, level = 0, graphInfo = null, nodeInfo = null, pinInfo = null) { 

        let itemName;
        let outType;

        if (!item || !item.handle)
            return;

        try {
            let result;
            
            // basic item params
            // name
            result = window.grpcApi.makeApiCallSync(
                'ApiItem/name',
                item.handle
            );
            if (!result.success) {
                throw new Error('Failed GenericNodeRenderer.addSceneItem()');
            }
            itemName = result.data.result;

            // outtype
            result = window.grpcApi.makeApiCallSync(
                'ApiItem/outType',
                item.handle
            );
            if (!result.success) {
                throw new Error('Failed to get item outType');
            }
            outType = result.data.result;

            if (pinInfo != null && pinInfo.staticLabel != "") {
                itemName = pinInfo.staticLabel;
            }

        } catch (error) {
            console.error('❌ Failed GenericNodeRenderer.addSceneItem(): ', error);
        }
        let children = this.loadSceneTreeSync(item.handle, null, level);

        let attrInfo = null;
        if (children.length == 0) {
            try {        
                // end node, get value's attribute
                let result = window.grpcApi.makeApiCallSync(
                    'ApiItem/attrInfo', 
                    item.handle,
                    { id: window.OctaneTypes.AttributeId.A_VALUE },
                );
                if (!result.success) {
                    throw new Error('Failed GenericNodeRenderer.addSceneItem(): ApiItem/attrInfo');
                }
                attrInfo = result.data.result;

            } catch (error) {
                console.error('❌ Failed GenericNodeRenderer.addSceneItem(): ', error);
            }
            console.log(`EndNode    ${item.handle} ${itemName} ${outType} ${attrInfo?.type}`);            
        }
        else {
            console.log(`ParentNode ${item.handle} ${itemName} ${outType} ${pinInfo?.type}`);            
        }
        // save it
        sceneItems.push({
            name: itemName,
            handle: item.handle,
            outType: outType,
            graphInfo: graphInfo,
            nodeInfo: nodeInfo,
            attrInfo: attrInfo,
            pinInfo: pinInfo,
            children: children,
        });
        this.scene.map[item.handle] = sceneItems[sceneItems.size-1];
    }

    renderRealSceneTree(scene) {
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) return;
        
        if (scene.items.length === 0) {
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
                    <span class="node-toggle ${this.expandedNodes.has('scene-root') ? 'expanded' : 'collapsed'}">${this.expandedNodes.has('scene-root') ? '−' : '+'}</span>
                    <span class="node-icon">📁</span>
                    <span class="node-name">Scene</span>
                </div>
            </div>
        `;
        
        // Add child items recursively if Scene is expanded
        if (this.expandedNodes.has('scene-root')) {
            treeHTML += this.renderTreeLevel(scene.items, 1);
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
            const icon = window.OctaneIconMapper ? 
                window.OctaneIconMapper.getNodeIcon(item.outType, item.name) : 
                this.getOctaneIconFor(item.outType, item.name);
            const nodeId = `item-${item.handle}`;
            const isSelected = item.name === 'Render target'; // Match Octane screenshot
            const hasChildren = item.children && item.children.length > 0;
            const isExpanded = this.expandedNodes.has(nodeId);
            
            html += `
                <div class="tree-node scene-item level-${level} ${isSelected ? 'selected' : ''}" data-node-id="${nodeId}" data-handle="${item.handle}">
                    <div class="node-content">
                        ${hasChildren ? 
                            `<span class="node-toggle ${isExpanded ? 'expanded' : 'collapsed'}">${isExpanded ? '−' : '+'}</span>` : 
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
    
    getOctaneIconFor(outType, name) {
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
        if (outType === 'PT_BOOL' || name === 'Bool value') {
            return '☑️'; // Checkbox for boolean parameters
        }
        if (outType === 'PT_FLOAT' || name === 'Float value') {
            return '🔢'; // Numbers for float parameters
        }
        if (outType === 'PT_INT' || name === 'Int value') {
            return '🔢'; // Numbers for integer parameters
        }
        if (outType === 'PT_ENUM' || name === 'Enum value') {
            return '📋'; // List for enum parameters
        }
        if (outType === 'PT_RGB' || name === 'RGB color') {
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
        
        return iconMap[outType] || '⬜';
    }
    
    getIconFor(outType) {
        const iconMap = {
            'unknown': '⬜',
            'mesh': '▲',
            'camera': '📷',
            'light': '💡',
            'material': '🎨',
            'texture': '🖼️',
            'group': '📁'
        };
        
        return iconMap[outType] || '⬜';
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
                this.renderRealSceneTree(this.lastScene);
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
                
                this.selectNode(handle, nodeName, nodeId);

                this.eventSystem.emit('sceneNodeSelected', handle);
            });
        });
           
    }
    
    addEventListener(element, event, handler) {
        element.addEventListener(event, handler);
    }
    

}

// Export for use
window.SceneOutlinerSync = SceneOutlinerSync;