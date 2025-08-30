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

        this.setupEventHandlers();

        const treeContainer = this.element.querySelector('#scene-tree');
        if (treeContainer) {
            treeContainer.innerHTML = '<div class="scene-loading">Loading scene from Octane...</div>';
        }
    }
    
        
    setupEventHandlers() {
        // Search functionality
        const searchInput = this.element.querySelector('#scene-search');
        if (searchInput) {
            this.addEventListener(searchInput, 'input', (e) => {
                this.searchTerm = e.target.value.toLowerCase();
                
                this.render();
            });
        }
        // Listen for scene node selection (unified event for all components)
        this.eventSystem.on('sceneNodeSelected', (handle) => {
            this.updateSelectedNode(handle);
        });
                // Listen for scene data loaded from SceneOutliner
        this.eventSystem.on('sceneDataLoaded', (scene) => {
            console.log('SceneOutlinerSync received sceneDataLoaded event:', scene.tree.length);
            this.render();
        });
    }
    
    // Unified selection function - called both on initialization and user clicks
    updateSelectedNode(handle) {
        
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
/*
            treeContainer.innerHTML = `
                <div class="scene-error">
                    <div class="error-icon"></div>
                    <div class="error-title">Octane Not Available</div>
                    <div class="error-message">
                        Please start Octane Render on 127.0.0.1:51022<br>
                        <small>Error: ${error.message}</small>
                    </div>
                    <div class="error-actions">
                        <button onclick="window.sceneOutliner.syncScene()" class="retry-btn">Retry</button>
                    </div>
                </div>
            `;
*/

    render() {

        const treeContainer = this.element.querySelector('#scene-tree');
        if (!treeContainer) return;
        
        const scene = window.octaneClient.getScene();

        if (scene.tree.length === 0) {
            treeContainer.innerHTML = `
                <div class="scene-empty">
                    <div class="empty-message">Empty</div>
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
            treeHTML += this.renderTreeLevel(scene.tree, 1);
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