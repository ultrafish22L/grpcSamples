/**
 * Scene Outliner with Synchronous API Integration
 * 
 * Hierarchical scene tree component that displays the complete Octane scene
 * structure with real-time synchronization to the Octane service.
 * Provides node selection, search functionality, and expand/collapse controls.
 * 
 * Core Features:
 * - Real-time scene tree synchronization with Octane
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
        this.element = element;
        this.eventSystem = eventSystem;

        this.expandedNodes = new Set(['scene-root', 'item-1000025']); // Expand Scene and Render target by default
        this.searchTerm = '';
        this.selectedNodeHandle = null;
        this.scene = { items: null}

        this.setupEventHandlers();
        
        // Auto-load scene tree after a short delay
        console.log('Setting up auto-load timer...');
        setTimeout(() => {
            console.log('Auto-loading scene tree...');
            this.loadSceneTree();
        }, 100);
    }
    
    
    /**
     * ASYNCHRONOUS function that loads scene tree
     * UI loads immediately, then updates when scene data is ready
     */
    async loadSceneTree() {
        console.log('loadSceneTree() called');
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) {
            console.error('❌ loadSceneTree(): #scene-tree container not found');
            return;
        }
        // Show loading state immediately - UI is responsive
        treeContainer.innerHTML = '<div class="scene-loading">Loading scene from Octane...</div>';
        
        try {
            console.log('Starting SYNCHRONOUS scene tree loading sequence...');
            this.scene = { items: this.loadSceneTreeSync()};
            
            // Store scene data for later requests
            this.lastScene = this.scene;
            
            // Render the real scene tree (UI update happens here)
            this.render(this.scene);
            
            // Update other components with real scene data
            this.eventSystem.emit('sceneDataLoaded', this.scene);
            
            console.log('Scene tree loading completed successfully');
            
        } catch (error) {
            console.error('❌ Failed loadSceneTree(): ', error);
            
            // Clear stored scene data and notify other components
            this.lastScene = {};
            this.scene = { items:[]}
            this.eventSystem.emit('sceneDataLoaded', this.scene);
            
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

    /**
     * SYNCHRONOUS scene tree loading with blocking API calls
     * STRUCTURED DEBUGGING: Isolate exactly where Octane crashes
     * @returns {Array} Scene items array
     */
    loadSceneTreeSync(itemHandle, sceneItems, isGraph, level = 0) {
        let result;
//        if (level >= 3)
//            return scene;
        level = level + 1;

        if (sceneItems == null) {
            sceneItems = [];
        }
        try {
            if (itemHandle == null)
            {
                // first call, get the root
                result = window.grpcApi.makeApiCall(
                    'ApiProjectManager/rootNodeGraph'
                );
                if (!result.success) {
                    throw new Error('Failed ApiProjectManager/rootNodeGraph');
                }
                itemHandle = result.data.result.handle;
                // is it a graph or node?
                result = window.grpcApi.makeApiCall(
                    'ApiItem/isGraph', 
                    itemHandle 
                );
                if (!result.success) {
                    throw new Error('Failed ApiItem/isGraph');
                }
                isGraph = result.data.result;
            }
            if (isGraph)
            {
                // Get owned items
                result = window.grpcApi.makeApiCall(
                    'ApiNodeGraph/getOwnedItems', 
                    itemHandle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodeGraph/getOwnedItems');
                }
                const ownedItemsHandle = result.data.list.handle

                // Get the size of the item array
                result = window.grpcApi.makeApiCall(
                    'ApiItemArray/size', 
                    ownedItemsHandle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiItemArray/size');
                }
                const size = result.data.result;

                for (let i = 0; i < size; i++) {
                    // get it
                    result = window.grpcApi.makeApiCall(
                        'ApiItemArray/get', 
                        ownedItemsHandle,
                        {index: i},
                    );
                    if (!result.success) {
                        throw new Error('Failed ApiItemArray/get');
                    }
                    // will recurse to loadSceneTreeSync()
                    this.addSceneItem(sceneItems, result.data.result, null, level);
                }
//                sceneItems.sort((a, b) => a.handle - b.handle); 

                return sceneItems
            }
            // its a node
            result = window.grpcApi.makeApiCall(
                'ApiNode/pinCount', 
                itemHandle
            );
            if (!result.success) {
                throw new Error('Failed ApiNode/pinCount');
            }
            const pinCount = result.data.result;
//            console.log(`pinCount = ${pinCount} nodeInfo.pinInfoCount = ${nodeInfo.pinInfoCount}`);  

            for (let i = 0; i < pinCount; i++) {
                // Get the pin connected node
                result = window.grpcApi.makeApiCall(
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
                result = window.grpcApi.makeApiCall(
                    'ApiNode/pinLabelIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinLabelIx');
                }
                let pinInfo = { staticLabel: result.data.result, index:i };

                // Get the pin type
                result = window.grpcApi.makeApiCall(
                    'ApiNode/pinTypeIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinTypeIx');
                }
                pinInfo.parent = itemHandle;
                pinInfo.type = result.data.result;

//                console.log('pinInfo.type', pinInfo.type);

//                pinInfo.type = window.OctaneTypes.NodePinType[pinInfo.type];
//                console.log('pinInfo.type', pinInfo.type);
/*                
                // Get the pin info handle
                result = window.grpcApi.makeApiCall(
                    'ApiNode/pinInfoIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinInfoIx');
                }

                console.log('before ApiNodePinInfoEx/getApiNodePinInfo', result.data.result.handle);

                // Get the pin info 
                result = window.grpcApi.makeApiCall(
                    'ApiNodePinInfoEx/getApiNodePinInfo', 
                    result.data.result.handle
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodePinInfoEx/getApiNodePinInfo');
                }
                console.log('pinInfo ', JSON.stringify(result, null, 2));
                pinInfo = result.data.result;
*/
                // will recurse to loadSceneTreeSync()
                this.addSceneItem(sceneItems, connectedNode, pinInfo, level);
            }
        } catch (error) {
            console.error('❌ Failed loadSceneTreeSync(): ', error);
        }
//        sceneItems.sort((a, b) => a.handle - b.handle); 
        return sceneItems;
    }
    
        
    /**

     */
    addSceneItem(sceneItems, item, pinInfo, level = 0) { 

        let itemName;
        let outType;
        let graphInfo;
        let nodeInfo;
        let isGraph;

        if (!item || !item.handle)
            return;

        try {
            let result;
            
            // basic item params
            // name
            result = window.grpcApi.makeApiCall(
                'ApiItem/name',
                item.handle
            );
            if (!result.success) {
                throw new Error('Failed GenericNodeRenderer.addSceneItem()');
            }
            itemName = result.data.result;

            // outtype
            result = window.grpcApi.makeApiCall(
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
            console.log(`addSceneItem = ${itemName}`);  

            // is it a graph or node?
            result = window.grpcApi.makeApiCall(
                'ApiItem/isGraph', 
                item.handle 
            );
            if (!result.success) {
                throw new Error('Failed ApiItem/isGraph');
            }
            isGraph = result.data.result;
            if (isGraph) {
                // its a graph
                result = window.grpcApi.makeApiCall(
                    'ApiNodeGraph/info1', 
                    item.handle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodeGraph/info1');
                }
                graphInfo = result.data.result;
                console.log(`graphInfo = `, JSON.stringify(graphInfo, null, 2));  
            }
            else {
                // its a node
                result = window.grpcApi.makeApiCall(
                    'ApiNode/info', 
                    item.handle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/info');
                }
                nodeInfo = result.data.result
                console.log(`nodeInfo = `, JSON.stringify(nodeInfo, null, 2));  
            }

        } catch (error) {
            console.error('❌ Failed addSceneItem(): ', error);
        }
        let children = this.loadSceneTreeSync(item.handle, null, isGraph, level);

        let attrInfo = null;
        if (children.length == 0) {
            try {        
                // end node, get value's attribute
                const result = window.grpcApi.makeApiCall(
                    'ApiItem/attrInfo', 
                    item.handle,
                    { id: window.OctaneTypes.AttributeId.A_VALUE },
                );
                if (!result.success) {
                    throw new Error('Failed GenericNodeRenderer.addSceneItem(): ApiItem/attrInfo');
                }
                attrInfo = result.data.result;

            } catch (error) {
                console.error('❌ Failed addSceneItem(): ', error);
            }
            console.log(`EndNode    ${item.handle} ${itemName} ${outType} ${attrInfo?.type}`);            
        }
        else {
            console.log(`ParentNode ${item.handle} ${itemName} ${outType} ${pinInfo?.type}`);            
        }
       
        const icon = window.OctaneIconMapper?.getNodeIcon(outType);

        if (pinInfo) {
            pinInfo.pinColor = window.OctaneIconMapper?.gePinColor(outType);
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
            icon: icon,
        });
    }

    setupEventHandlers() {
        // Search functionality
        const searchInput = this.element.querySelector('#scene-search');
        if (searchInput) {
            this.addEventListener(searchInput, 'input', (e) => {
                this.searchTerm = e.target.value.toLowerCase();
                
                this.render(this.scene);
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

    render(scene) {
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
            const icon = item.icon; 
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
                this.render();
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