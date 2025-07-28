/**
 * Scene Outliner Component
 * Hierarchical tree view of scene objects matching Octane's interface
 */

class SceneOutliner extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        console.log('🌳 NEW HIERARCHICAL SceneOutliner loaded! v1530');
        
        // Visual indicator that new code is loaded
        if (window.debugConsole) {
            window.debugConsole.success('✅ NEW HIERARCHICAL SceneOutliner v1530 loaded!');
        }
        
        this.sceneData = [];
        this.selectedObjects = new Set();
        this.expandedNodes = new Set(['scene_root']); // Scene root expanded by default
        this.searchTerm = '';
        this.nodeIdCounter = 0;
        this.selectedNodeId = null; // Track currently selected node
    }
    
    async onInitialize() {
        this.render();
        this.setupSearch();
        this.setupToolbarButtons();
        
        // Load initial scene tree
        await this.loadSceneTree();
    }
    
    setupEventListeners() {
        // Listen for scene updates
        this.client.on('ui:sceneUpdate', (sceneState) => {
            this.updateScene(sceneState);
        });
        
        // Listen for selection updates
        this.client.on('ui:selectionUpdate', (selection) => {
            this.updateSelection(selection);
        });
    }
    
    render() {
        this.element.innerHTML = `
            <div class="scene-outliner-toolbar">
                <input type="text" class="scene-outliner-search" placeholder="Search objects..." />
                <button class="panel-btn" title="Expand All">⊞</button>
                <button class="panel-btn" title="Collapse All">⊟</button>
            </div>
            <div class="scene-tree" id="scene-tree">
                <div class="scene-loading">Loading scene...</div>
            </div>
        `;
    }
    
    setupSearch() {
        const searchInput = this.element.querySelector('.scene-outliner-search');
        if (searchInput) {
            this.addEventListener(searchInput, 'input', (e) => {
                this.searchTerm = e.target.value.toLowerCase();
                this.renderTree();
            });
        }
    }
    
    setupToolbarButtons() {
        const expandAllBtn = this.element.querySelector('.panel-btn[title="Expand All"]');
        const collapseAllBtn = this.element.querySelector('.panel-btn[title="Collapse All"]');
        
        if (expandAllBtn) {
            this.addEventListener(expandAllBtn, 'click', () => {
                this.expandAll();
            });
        }
        
        if (collapseAllBtn) {
            this.addEventListener(collapseAllBtn, 'click', () => {
                this.collapseAll();
            });
        }
    }
    
    async loadSceneTree() {
        try {
            const treeContainer = this.element.querySelector('#scene-tree');
            if (treeContainer) {
                treeContainer.innerHTML = '<div class="scene-loading">🔍 Checking Octane connection...</div>';
            }
            
            // Test if proxy server is running and if Octane is available
            let proxyResponse, proxyResult;
            try {
                proxyResponse = await fetch('http://localhost:51023/test', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' }
                });
                proxyResult = await proxyResponse.json();
                console.log('📡 Proxy server status:', proxyResult);
            } catch (error) {
                console.log('❌ Proxy server not available:', error.message);
                treeContainer.innerHTML = `
                    <div class="scene-error">
                        <div class="error-icon">🚫</div>
                        <div class="error-title">Proxy Server Not Available</div>
                        <div class="error-message">
                            Please start the proxy server:<br>
                            <code>cd octaneWeb && python3 working_proxy.py</code>
                        </div>
                    </div>
                `;
                return;
            }
            
            // Proxy is running, but check if Octane is available
            if (!proxyResult.success) {
                treeContainer.innerHTML = `
                    <div class="scene-error">
                        <div class="error-icon">⚠️</div>
                        <div class="error-title">Octane Not Available</div>
                        <div class="error-message">
                            ${proxyResult.message}<br><br>
                            Please ensure Octane is running on:<br>
                            <code>127.0.0.1:51022</code>
                        </div>
                    </div>
                `;
                return;
            }
            
            // Test if Octane is running
            treeContainer.innerHTML = '<div class="scene-loading">🔍 Connecting to Octane...</div>';
            
            // Following ENGINEERING_DISCIPLINE.md: Real Data Enforcement
            // NO MOCK DATA EVER - only show real Octane data or clear error messages
            
            try {
                // STEP 1: Get root node graph (following exact proxy pattern from grpc_proxy.py)
                const rootResponse = await fetch('http://localhost:51023/ApiProjectManagerService/rootNodeGraph', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({})
                });
                
                if (!rootResponse.ok) {
                    throw new Error(`HTTP ${rootResponse.status}: ${rootResponse.statusText}`);
                }
                
                const rootResult = await rootResponse.json();
                console.log('📥 Root node graph response:', rootResult);
                
                if (!rootResult.success) {
                    throw new Error(rootResult.error || 'Failed to get root node graph');
                }
                
                // STEP 2: Get owned items from root node graph
                treeContainer.innerHTML = '<div class="scene-loading">📋 Loading scene items...</div>';
                
                const ownedItemsResponse = await fetch('http://localhost:51023/ApiNodeGraphService/getOwnedItems', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({
                        objectPtr: {
                            handle: rootResult.result.handle,
                            type: 20  // Convert ApiRootNodeGraph (18) to ApiNodeGraph (20) for getOwnedItems
                        }
                    })
                });
                
                if (!ownedItemsResponse.ok) {
                    throw new Error(`HTTP ${ownedItemsResponse.status}: ${ownedItemsResponse.statusText}`);
                }
                
                const ownedItemsResult = await ownedItemsResponse.json();
                console.log('📥 Owned items response:', ownedItemsResult);
                
                if (!ownedItemsResult.success) {
                    throw new Error(ownedItemsResult.error || 'Failed to get owned items');
                }
                
                // STEP 3: Get size of the items array
                treeContainer.innerHTML = '<div class="scene-loading">🔢 Getting item count...</div>';
                
                const sizeResponse = await fetch('http://localhost:51023/ApiItemArrayService/size', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({
                        objectPtr: ownedItemsResult.data.list
                    })
                });
                
                if (!sizeResponse.ok) {
                    throw new Error(`HTTP ${sizeResponse.status}: ${sizeResponse.statusText}`);
                }
                
                const sizeResult = await sizeResponse.json();
                console.log('📥 Size response:', sizeResult);
                
                if (!sizeResult.success) {
                    throw new Error(sizeResult.error || 'Failed to get array size');
                }
                
                // STEP 4: Load individual items and build scene tree
                treeContainer.innerHTML = `<div class="scene-loading">🌳 Building scene tree (${sizeResult.data.result} items)...</div>`;
                
                const sceneItems = [];
                for (let i = 0; i < sizeResult.data.result; i++) {
                    // Get item at index i
                    const itemResponse = await fetch('http://localhost:51023/ApiItemArrayService/get1', {
                        method: 'POST',
                        headers: { 'Content-Type': 'application/json' },
                        body: JSON.stringify({
                            objectPtr: ownedItemsResult.data.list,
                            index: i
                        })
                    });
                    
                    if (itemResponse.ok) {
                        const itemResult = await itemResponse.json();
                        if (itemResult.success) {
                            // Get the name of this item
                            const nameResponse = await fetch('http://localhost:51023/ApiItemService/name', {
                                method: 'POST',
                                headers: { 'Content-Type': 'application/json' },
                                body: JSON.stringify({
                                    objectPtr: itemResult.data.result
                                })
                            });
                            
                            if (nameResponse.ok) {
                                const nameResult = await nameResponse.json();
                                sceneItems.push({
                                    handle: itemResult.data.result.handle,
                                    type: itemResult.data.result.type,
                                    name: nameResult.success ? nameResult.data.result : `Item_${i}`,
                                    index: i
                                });
                            }
                        }
                    }
                }
                
                // STEP 5: Render the real scene tree
                this.renderRealSceneTree(sceneItems);
                
                // STEP 6: Update NodeGraphEditor with real scene data
                this.eventSystem.emit('sceneDataLoaded', sceneItems);
                
                console.log('✅ Scene tree loaded successfully with real Octane data:', sceneItems); 
                // 2. ApiNodeGraphService.getOwnedItems(objectPtr)
                // 3. ApiItemArrayService.size(objectPtr) 
                // 4. ApiItemArrayService.get1(objectPtr, index)
                // 5. ApiItemService.name(objectPtr with type=16)
                
            } catch (error) {
                console.log('❌ Octane connection failed:', error.message);
                
                // Show clear error message - NO MOCK DATA
                treeContainer.innerHTML = `
                    <div class="scene-error">
                        <div class="error-icon">⚠️</div>
                        <div class="error-title">Octane Not Available</div>
                        <div class="error-message">
                            Please start Octane Render on 127.0.0.1:51022<br>
                            <small>Error: ${error.message}</small>
                        </div>
                        <div class="error-actions">
                            <button onclick="window.location.reload()" class="retry-btn">🔄 Retry</button>
                        </div>
                    </div>
                `;
            }
            
        } catch (error) {
            console.error('❌ Failed to load scene tree:', error);
            const treeContainer = this.element.querySelector('#scene-tree');
            if (treeContainer) {
                treeContainer.innerHTML = `
                    <div class="scene-error">
                        <div class="error-icon">💥</div>
                        <div class="error-title">Unexpected Error</div>
                        <div class="error-message">${error.message}</div>
                    </div>
                `;
            }
        }
    }
    
    renderRealSceneTree(sceneItems) {
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) return;
        
        if (sceneItems.length === 0) {
            treeContainer.innerHTML = `
                <div class="scene-success">
                    <div class="success-icon">✅</div>
                    <div class="success-title">Octane Connected!</div>
                    <div class="success-message">
                        Scene is empty or no accessible items found.
                    </div>
                </div>
            `;
            return;
        }
        
        // Build hierarchical tree structure matching target UI
        let treeHTML = '<div class="scene-tree-root">';
        
        // Root Scene node (always expanded)
        treeHTML += '<div class="scene-node scene-root" data-node-id="scene_root" data-expanded="true">';
        treeHTML += '<div class="scene-node-content" data-level="0">';
        treeHTML += '<span class="scene-node-indent"></span>';
        treeHTML += '<span class="scene-node-toggle">▼</span>';
        treeHTML += '<span class="scene-node-icon">🌍</span>';
        treeHTML += '<span class="scene-node-name">Scene</span>';
        treeHTML += '<span class="scene-node-visibility">👁</span>';
        treeHTML += '</div>';
        
        // Children container
        treeHTML += '<div class="scene-node-children" style="display: block;">';
        
        // Add each real scene item as child of Scene
        sceneItems.forEach(item => {
            const icon = this.getNodeIcon(item.type, item.name);
            const isSelected = this.selectedNodeId === item.handle.toString();
            
            treeHTML += `
                <div class="scene-node scene-item ${isSelected ? 'selected' : ''}" 
                     data-node-id="${item.handle}" 
                     data-node-type="${item.type}"
                     data-node-name="${item.name}">
                    <div class="scene-node-content" data-level="1">
                        <span class="scene-node-indent">    </span>
                        <span class="scene-node-icon">${icon}</span>
                        <span class="scene-node-name">${item.name}</span>
                        <span class="scene-node-handle">[${item.handle}]</span>
                        <span class="scene-node-visibility">👁</span>
                    </div>
                </div>
            `;
        });
        
        treeHTML += '</div></div></div>';
        treeContainer.innerHTML = treeHTML;
        
        // Add click handlers for real scene items
        this.setupRealSceneTreeHandlers();
        
        // Auto-select "Render target" if it exists (matching target UI)
        const renderTargetNode = treeContainer.querySelector('[data-node-name="Render target"]');
        if (renderTargetNode && !this.selectedNodeId) {
            renderTargetNode.click();
        }
    }
    
    getNodeIcon(nodeType, nodeName = '') {
        // Map Octane node types to appropriate icons, with name-based overrides
        if (nodeName.toLowerCase().includes('render target')) {
            return '🎯'; // Render target icon
        }
        if (nodeName.toLowerCase().includes('camera')) {
            return '📷'; // Camera icon
        }
        if (nodeName.toLowerCase().includes('.obj') || nodeName.toLowerCase().includes('.fbx') || nodeName.toLowerCase().includes('.ply')) {
            return '🔺'; // 3D model icon
        }
        
        const iconMap = {
            1: '📷', // Camera
            2: '💡', // Light
            3: '🔺', // Mesh/Geometry
            4: '🎨', // Material
            5: '🖼️', // Texture
            16: '📦', // Generic Item
            18: '🌐', // Root Node Graph
        };
        return iconMap[nodeType] || '📄';
    }
    
    setupRealSceneTreeHandlers() {
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) return;
        
        // Add click handlers for scene nodes
        const sceneNodes = treeContainer.querySelectorAll('.scene-node');
        sceneNodes.forEach(node => {
            this.addEventListener(node, 'click', (e) => {
                e.stopPropagation();
                const nodeId = node.dataset.nodeId;
                const nodeType = node.dataset.nodeType;
                const nodeName = node.dataset.nodeName;
                
                // Update selection
                this.selectNode(nodeId, nodeName, nodeType);
                
                console.log('🎯 Selected real scene node:', { nodeId, nodeType, nodeName });
                
                // Emit selection event for other components
                this.eventSystem.emit('sceneNodeSelected', {
                    nodeId,
                    nodeType,
                    nodeName,
                    isRealData: true
                });
            });
        });
        
        // Add visibility toggle handlers
        const visibilityToggles = treeContainer.querySelectorAll('.scene-node-visibility');
        visibilityToggles.forEach(toggle => {
            this.addEventListener(toggle, 'click', (e) => {
                e.stopPropagation();
                const isVisible = toggle.textContent === '👁';
                toggle.textContent = isVisible ? '🚫' : '👁';
                console.log('👁 Toggled visibility for real scene node');
            });
        });
    }
    
    selectNode(nodeId, nodeName, nodeType) {
        // Remove previous selection
        const treeContainer = this.element.querySelector('#scene-tree');
        if (treeContainer) {
            const previousSelected = treeContainer.querySelector('.scene-node.selected');
            if (previousSelected) {
                previousSelected.classList.remove('selected');
            }
            
            // Add selection to new node
            const newSelected = treeContainer.querySelector(`[data-node-id="${nodeId}"]`);
            if (newSelected) {
                newSelected.classList.add('selected');
                this.selectedNodeId = nodeId;
                this.selectedNodeName = nodeName;
                this.selectedNodeType = nodeType;
            }
        }
    }

    updateScene(sceneState) {
        // Transform flat server data into hierarchical structure
        const flatData = sceneState.hierarchy || [];
        console.log('🔄 Transforming flat data to hierarchical:', flatData);
        
        if (flatData.length > 0) {
            // Create hierarchical structure from flat data
            this.sceneData = this.transformToHierarchical(flatData);
        } else {
            // Show empty tree if no real data - NO MOCK DATA
            this.sceneData = [];
        }
        
        console.log('🌳 Final hierarchical data:', this.sceneData);
        this.renderTree();
    }
    
    transformToHierarchical(flatData) {
        // Group flat data into hierarchical structure
        const geometryNodes = flatData.filter(node => node.type === 'mesh');
        const lightNodes = flatData.filter(node => node.type === 'light');
        const cameraNodes = flatData.filter(node => node.type === 'camera');
        
        return [
            {
                id: 'scene_root',
                name: 'Scene',
                type: 'group',
                visible: true,
                children: [
                    {
                        id: 'geometry_group',
                        name: 'Geometry',
                        type: 'group',
                        visible: true,
                        children: geometryNodes.map(node => ({
                            id: node.id,
                            name: node.name,
                            type: 'mesh',
                            visible: node.visible !== false
                        }))
                    },
                    {
                        id: 'lights_group',
                        name: 'Lights',
                        type: 'group',
                        visible: true,
                        children: lightNodes.map(node => ({
                            id: node.id,
                            name: node.name,
                            type: 'light',
                            visible: node.visible !== false
                        }))
                    },
                    {
                        id: 'cameras_group',
                        name: 'Cameras',
                        type: 'group',
                        visible: true,
                        children: cameraNodes.map(node => ({
                            id: node.id,
                            name: node.name,
                            type: 'camera',
                            visible: node.visible !== false
                        }))
                    }
                ]
            }
        ];
    }
    
    // NO MOCK DATA FUNCTIONS - REMOVED
    
    updateSelection(selection) {
        this.selectedObjects = new Set(selection);
        this.renderTree();
    }
    
    renderTree() {
        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) return;
        
        if (this.sceneData.length === 0) {
            treeContainer.innerHTML = '<div class="scene-loading">No objects in scene</div>';
            return;
        }
        
        const treeHTML = this.renderNodes(this.sceneData, 0);
        treeContainer.innerHTML = treeHTML;
        
        // Setup node event listeners
        this.setupNodeEventListeners();
    }
    
    renderNodes(nodes, depth) {
        return nodes.map(node => this.renderNode(node, depth)).join('');
    }
    
    renderNode(node, depth) {
        const isSelected = this.selectedObjects.has(node.id);
        const isExpanded = this.expandedNodes.has(node.id);
        const hasChildren = node.children && node.children.length > 0;
        const matchesSearch = !this.searchTerm || node.name.toLowerCase().includes(this.searchTerm);
        
        if (!matchesSearch) return '';
        
        const indent = depth * 16;
        const toggleIcon = hasChildren ? (isExpanded ? '▼' : '▶') : '';
        const nodeIcon = this.getNodeIcon(node.type);
        const visibilityIcon = node.visible !== false ? '👁' : '🚫';
        
        let html = `
            <div class="tree-node ${isSelected ? 'selected' : ''}" data-node-id="${node.id}" style="padding-left: ${indent}px">
                <div class="tree-node-content">
                    <span class="tree-toggle ${hasChildren ? 'has-children' : ''}" data-node-id="${node.id}">
                        ${toggleIcon}
                    </span>
                    <span class="tree-node-icon">${nodeIcon}</span>
                    <span class="tree-node-name" title="${node.name}">${node.name}</span>
                    <span class="tree-node-visibility" data-node-id="${node.id}" title="Toggle visibility">
                        ${visibilityIcon}
                    </span>
                </div>
            </div>
        `;
        
        // Render children if expanded
        if (hasChildren && isExpanded) {
            html += this.renderNodes(node.children, depth + 1);
        }
        
        return html;
    }
    
    getNodeIcon(type) {
        const icons = {
            'mesh': '▣',      // Geometric mesh icon
            'light': '◉',     // Light source icon  
            'camera': '◎',    // Camera lens icon
            'material': '◐',  // Material shader icon
            'group': '▣',     // Group/folder icon
            'transform': '◈', // Transform node icon
            'geometry': '▣',  // Geometry icon
            'scene': '▣'      // Scene root icon
        };
        return icons[type] || '◯';
    }
    
    setupNodeEventListeners() {
        // Node selection
        const nodes = this.element.querySelectorAll('.tree-node');
        nodes.forEach(node => {
            this.addEventListener(node, 'click', (e) => {
                if (e.target.classList.contains('tree-toggle') || e.target.classList.contains('tree-node-visibility')) {
                    return; // Let specific handlers deal with these
                }
                const nodeId = node.dataset.nodeId;
                this.selectNode(nodeId, e.ctrlKey || e.metaKey);
            });
            
            this.addEventListener(node, 'contextmenu', (e) => {
                e.preventDefault();
                const nodeId = node.dataset.nodeId;
                this.showContextMenu(nodeId, e.clientX, e.clientY);
            });
        });
        
        // Toggle expand/collapse
        const toggles = this.element.querySelectorAll('.tree-toggle.has-children');
        toggles.forEach(toggle => {
            this.addEventListener(toggle, 'click', (e) => {
                e.stopPropagation();
                const nodeId = toggle.dataset.nodeId;
                this.toggleNode(nodeId);
            });
        });
        
        // Toggle visibility
        const visibilityToggles = this.element.querySelectorAll('.tree-node-visibility');
        visibilityToggles.forEach(toggle => {
            this.addEventListener(toggle, 'click', (e) => {
                e.stopPropagation();
                const nodeId = toggle.dataset.nodeId;
                this.toggleVisibility(nodeId);
            });
        });
    }
    
    async selectNode(nodeId, multiSelect = false) {
        if (multiSelect) {
            if (this.selectedObjects.has(nodeId)) {
                this.selectedObjects.delete(nodeId);
            } else {
                this.selectedObjects.add(nodeId);
            }
        } else {
            this.selectedObjects.clear();
            this.selectedObjects.add(nodeId);
        }
        
        // Update server selection
        if (this.client.isConnected) {
            await this.client.selectObjects(Array.from(this.selectedObjects));
        }
        
        this.renderTree();
    }
    
    toggleNode(nodeId) {
        if (this.expandedNodes.has(nodeId)) {
            this.expandedNodes.delete(nodeId);
        } else {
            this.expandedNodes.add(nodeId);
        }
        this.renderTree();
    }
    
    async toggleVisibility(nodeId) {
        // TODO: Implement visibility toggle
        console.log('Toggle visibility for node:', nodeId);
    }
    
    showContextMenu(nodeId, x, y) {
        // TODO: Implement context menu
        console.log('Show context menu for node:', nodeId, 'at', x, y);
    }
    
    expandAll() {
        this.expandedNodes.clear();
        this._addAllNodeIds(this.sceneData, this.expandedNodes);
        this.renderTree();
    }
    
    collapseAll() {
        this.expandedNodes.clear();
        this.renderTree();
    }
    
    _addAllNodeIds(nodes, set) {
        nodes.forEach(node => {
            if (node.children && node.children.length > 0) {
                set.add(node.id);
                this._addAllNodeIds(node.children, set);
            }
        });
    }
    
    connect() {
        console.log('🔌 SceneOutliner connecting...');
        this.loadSceneTree();
    }
    
    disconnect() {
        console.log('🔌 SceneOutliner disconnecting...');
        const treeContainer = this.element.querySelector('#scene-tree');
        if (treeContainer) {
            treeContainer.innerHTML = `
                <div class="scene-success">
                    <div class="success-icon">🔌</div>
                    <div class="success-title">Disconnected</div>
                    <div class="success-message">
                        Click the connection toggle to reconnect to Octane.
                    </div>
                </div>
            `;
        }
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = SceneOutliner;
} else if (typeof window !== 'undefined') {
    window.SceneOutliner = SceneOutliner;
}