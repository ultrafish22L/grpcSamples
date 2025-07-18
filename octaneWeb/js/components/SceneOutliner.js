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
                treeContainer.innerHTML = '<div class="scene-loading">Loading scene tree...</div>';
            }
            
            if (this.client.isConnected && typeof this.client.getSceneData === 'function') {
                const result = await this.client.getSceneData();
                if (result.success && result.hierarchy) {
                    this.sceneData = result.hierarchy;
                    this.renderTree();
                } else {
                    if (treeContainer) {
                        treeContainer.innerHTML = '<div class="scene-loading">Failed to load scene data</div>';
                    }
                }
            } else {
                // Extensive mock hierarchical data for realistic testing
                this.sceneData = [
                    {
                        id: 'scene_root',
                        name: 'OctaneRender Scene',
                        type: 'group',
                        visible: true,
                        children: [
                            {
                                id: 'geometry_group',
                                name: 'Geometry',
                                type: 'group',
                                visible: true,
                                children: [
                                    {
                                        id: 'buildings_group',
                                        name: 'Buildings',
                                        type: 'group',
                                        visible: true,
                                        children: [
                                            { id: 'building_main', name: 'Main Building', type: 'mesh', visible: true },
                                            { id: 'building_tower', name: 'Tower', type: 'mesh', visible: true },
                                            { id: 'building_annex', name: 'Annex', type: 'mesh', visible: false }
                                        ]
                                    },
                                    {
                                        id: 'vehicles_group',
                                        name: 'Vehicles',
                                        type: 'group',
                                        visible: true,
                                        children: [
                                            { id: 'car_sports', name: 'Sports Car', type: 'mesh', visible: true },
                                            { id: 'car_sedan', name: 'Sedan', type: 'mesh', visible: true },
                                            { id: 'motorcycle', name: 'Motorcycle', type: 'mesh', visible: false }
                                        ]
                                    },
                                    {
                                        id: 'environment_group',
                                        name: 'Environment',
                                        type: 'group',
                                        visible: true,
                                        children: [
                                            { id: 'terrain', name: 'Terrain', type: 'mesh', visible: true },
                                            { id: 'trees', name: 'Trees', type: 'mesh', visible: true },
                                            { id: 'rocks', name: 'Rocks', type: 'mesh', visible: true },
                                            { id: 'water_plane', name: 'Water Surface', type: 'mesh', visible: true }
                                        ]
                                    }
                                ]
                            },
                            {
                                id: 'lights_group',
                                name: 'Lights',
                                type: 'group',
                                visible: true,
                                children: [
                                    {
                                        id: 'sun_lights',
                                        name: 'Sun Lights',
                                        type: 'group',
                                        visible: true,
                                        children: [
                                            { id: 'sun_main', name: 'Main Sun', type: 'light', visible: true },
                                            { id: 'sun_rim', name: 'Rim Sun', type: 'light', visible: true }
                                        ]
                                    },
                                    {
                                        id: 'area_lights',
                                        name: 'Area Lights',
                                        type: 'group',
                                        visible: true,
                                        children: [
                                            { id: 'area_key', name: 'Key Light', type: 'light', visible: true },
                                            { id: 'area_fill', name: 'Fill Light', type: 'light', visible: true },
                                            { id: 'area_back', name: 'Back Light', type: 'light', visible: false }
                                        ]
                                    },
                                    { id: 'hdri_env', name: 'HDRI Environment', type: 'light', visible: true }
                                ]
                            },
                            {
                                id: 'cameras_group',
                                name: 'Cameras',
                                type: 'group',
                                visible: true,
                                children: [
                                    { id: 'cam_hero', name: 'Hero Shot', type: 'camera', visible: true },
                                    { id: 'cam_wide', name: 'Wide Angle', type: 'camera', visible: true },
                                    { id: 'cam_close', name: 'Close Up', type: 'camera', visible: false },
                                    { id: 'cam_ortho', name: 'Orthographic', type: 'camera', visible: false }
                                ]
                            },
                            {
                                id: 'materials_group',
                                name: 'Materials',
                                type: 'group',
                                visible: true,
                                children: [
                                    { id: 'mat_metal', name: 'Brushed Metal', type: 'material', visible: true },
                                    { id: 'mat_glass', name: 'Clear Glass', type: 'material', visible: true },
                                    { id: 'mat_concrete', name: 'Concrete', type: 'material', visible: true },
                                    { id: 'mat_fabric', name: 'Fabric', type: 'material', visible: true }
                                ]
                            }
                        ]
                    }
                ];
                this.renderTree();
            }
        } catch (error) {
            console.error('Failed to load scene tree:', error);
            const treeContainer = this.element.querySelector('#scene-tree');
            if (treeContainer) {
                treeContainer.innerHTML = '<div class="scene-loading">Error loading scene tree</div>';
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
            // Use mock hierarchical data if no server data
            this.sceneData = this.getMockHierarchicalData();
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
                        children: lightNodes.length > 0 ? lightNodes.map(node => ({
                            id: node.id,
                            name: node.name,
                            type: 'light',
                            visible: node.visible !== false
                        })) : [
                            { id: 'sun_light', name: 'Sun Light', type: 'light', visible: true },
                            { id: 'area_light', name: 'Area Light', type: 'light', visible: true }
                        ]
                    },
                    {
                        id: 'cameras_group',
                        name: 'Cameras',
                        type: 'group',
                        visible: true,
                        children: cameraNodes.length > 0 ? cameraNodes.map(node => ({
                            id: node.id,
                            name: node.name,
                            type: 'camera',
                            visible: node.visible !== false
                        })) : [
                            { id: 'main_camera', name: 'Main Camera', type: 'camera', visible: true },
                            { id: 'ortho_camera', name: 'Orthographic Camera', type: 'camera', visible: false }
                        ]
                    }
                ]
            }
        ];
    }
    
    getMockHierarchicalData() {
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
                        children: [
                            { id: 'cube1', name: 'Cube', type: 'mesh', visible: true },
                            { id: 'sphere1', name: 'Sphere', type: 'mesh', visible: true },
                            { id: 'teapot1', name: 'Teapot', type: 'mesh', visible: false }
                        ]
                    },
                    {
                        id: 'lights_group',
                        name: 'Lights',
                        type: 'group',
                        visible: true,
                        children: [
                            { id: 'sun_light', name: 'Sun Light', type: 'light', visible: true },
                            { id: 'area_light', name: 'Area Light', type: 'light', visible: true }
                        ]
                    },
                    {
                        id: 'cameras_group',
                        name: 'Cameras',
                        type: 'group',
                        visible: true,
                        children: [
                            { id: 'main_camera', name: 'Main Camera', type: 'camera', visible: true },
                            { id: 'ortho_camera', name: 'Orthographic Camera', type: 'camera', visible: false }
                        ]
                    }
                ]
            }
        ];
    }
    
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
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = SceneOutliner;
} else if (typeof window !== 'undefined') {
    window.SceneOutliner = SceneOutliner;
}