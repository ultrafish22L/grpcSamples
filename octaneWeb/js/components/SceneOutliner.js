/**
 * Scene Outliner Component
 * Hierarchical tree view of scene objects
 */

class SceneOutliner extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        this.sceneData = [];
        this.selectedObjects = new Set();
        this.expandedNodes = new Set();
        this.searchTerm = '';
    }
    
    async onInitialize() {
        this.render();
        this.setupSearch();
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
    
    updateScene(sceneState) {
        this.sceneData = sceneState.hierarchy || [];
        this.renderTree();
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
            <div class="scene-node ${isSelected ? 'selected' : ''}" 
                 data-node-id="${node.id}" 
                 style="padding-left: ${indent}px">
                <div class="scene-node-indent">
                    ${hasChildren ? `<span class="scene-node-toggle" data-node-id="${node.id}">${toggleIcon}</span>` : ''}
                </div>
                <div class="scene-node-icon">${nodeIcon}</div>
                <div class="scene-node-label">${node.name}</div>
                <div class="scene-node-visibility" data-node-id="${node.id}" title="Toggle visibility">${visibilityIcon}</div>
            </div>
        `;
        
        if (hasChildren && isExpanded) {
            html += this.renderNodes(node.children, depth + 1);
        }
        
        return html;
    }
    
    getNodeIcon(type) {
        const icons = {
            'mesh': '🔷',
            'light': '💡',
            'camera': '📷',
            'material': '🎨',
            'group': '📁',
            'transform': '🔄'
        };
        return icons[type] || '📦';
    }
    
    setupNodeEventListeners() {
        // Node selection
        const nodes = this.element.querySelectorAll('.scene-node');
        nodes.forEach(node => {
            this.addEventListener(node, 'click', (e) => {
                const nodeId = node.dataset.nodeId;
                this.selectNode(nodeId, e.ctrlKey || e.metaKey);
            });
            
            this.addEventListener(node, 'contextmenu', (e) => {
                e.preventDefault();
                const nodeId = node.dataset.nodeId;
                this.showContextMenu(nodeId, e.clientX, e.clientY);
            });
        });
        
        // Toggle expansion
        const toggles = this.element.querySelectorAll('.scene-node-toggle');
        toggles.forEach(toggle => {
            this.addEventListener(toggle, 'click', (e) => {
                e.stopPropagation();
                const nodeId = toggle.dataset.nodeId;
                this.toggleNode(nodeId);
            });
        });
        
        // Toggle visibility
        const visibilityToggles = this.element.querySelectorAll('.scene-node-visibility');
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
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = SceneOutliner;
} else if (typeof window !== 'undefined') {
    window.SceneOutliner = SceneOutliner;
}