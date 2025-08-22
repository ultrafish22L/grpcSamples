/**
 * Node Inspector Component
 * 
 * Professional parameter editing interface that provides real-time control
 * over Octane node parameters with live updates to the rendering engine.
 * Matches the exact layout and styling of Octane Render Studio for consistency.
 * 
 * Core Features:
 * - Real-time parameter editing with live Octane updates
 * - Professional Octane-style UI with collapsible sections
 * - Generic node rendering system supporting all Octane node types
 * - Intelligent parameter grouping and organization
 * - Auto-selection of render target on initialization
 * - Cached scene data integration for performance
 * 
 * Technical Implementation:
 * - Extends OctaneComponent for consistent lifecycle management
 * - Uses GenericNodeRenderer for flexible parameter display
 * - Maintains parameter state cache for performance optimization
 * - Integrates with Scene Outliner for node selection synchronization
 * - Provides expandable/collapsible parameter groups
 * 
 * Parameter Types Supported:
 * - Numeric inputs (float, int) with range validation
 * - Boolean checkboxes with live toggle updates
 * - Dropdown selections for enumerated values
 * - Color pickers for RGB/RGBA parameters
 * - File path inputs for texture and model loading
 */

class NodeInspector extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        // Current node selection state
        this.selectedNode = null;             // Currently selected node handle
        this.selectedNodeType = null;         // Type of selected node for rendering
        this.parameters = {};                 // Current parameter values cache
        
        // UI state management
        this.sceneDataLoaded = false;        // Scene data loading state
        
        // Generic node rendering system for flexible parameter display
        this.genericRenderer = null;         // Initialized in onInitialize()
    }
    
    async onInitialize() {
        // Initialize Generic Node Renderer
        this.genericRenderer = new window.GenericNodeRenderer(window.OctaneIconMapper, this.client);
        console.log('NodeInspector: GenericNodeRenderer initialized');
    }
    
    setupEventListeners() {
        // Listen for scene data loading from SceneOutliner (OPTIMIZATION)
        this.eventSystem.on('sceneDataLoaded', (scene) => {
            // Store the scene data cache for generic access
            this.scene = scene;
            
            this.sceneDataLoaded = true;
            console.log('NodeInspector received sceneDataLoaded event:', scene.items.length);

            this.updateSelectedNode(this.scene.items[0].handle)
        });
        
        // Listen for selection updates
        this.client.on('ui:selectionUpdate', (selection) => {
            this.updateSelection(selection);
        });
        
        // Listen for scene node selection (unified event for all components)
        this.eventSystem.on('sceneNodeSelected', (handle) => {
            this.updateSelectedNode(handle);
        });
        
        // Listen for node parameter updates
        this.client.on('ui:nodeParameterUpdate', (data) => {
            this.updateParameter(data.nodeId, data.parameterName, data.value);
        });
        
        // Force click events to work by bypassing CSS pointer-events issues
        this.setupClickHandlers();
    }
    
    setupClickHandlers() {
        // ULTIMATE SOLUTION: Global coordinate-based click detection that bypasses all CSS pointer-events issues
        const rightPanel = document.querySelector('.right-panel');
        if (!rightPanel) return;

        console.log('Setting up coordinate-based click detection system');

        // Global document click handler that intercepts ALL clicks
        document.addEventListener('click', (event) => {
            // Get click coordinates
            const x = event.clientX;
            const y = event.clientY;
            
            // Get right panel bounds
            const rightPanelRect = rightPanel.getBoundingClientRect();
            
            // Check if click is within right panel area
            if (x >= rightPanelRect.left && x <= rightPanelRect.right &&
                y >= rightPanelRect.top && y <= rightPanelRect.bottom) {
                
                console.log('Coordinate-based click detected in right panel at:', x, y);
                
                // Use elementsFromPoint to find what's actually under the cursor
                const elementsUnderCursor = document.elementsFromPoint(x, y);
//                console.log('Elements under cursor:', elementsUnderCursor.map(el => `${el.tagName}.${el.className} [bid=${el.getAttribute('bid')}]`));
                
                // Find the first clickable element in the right panel
                for (const element of elementsUnderCursor) {
                    // Skip elements that are not in the right panel
                    if (!rightPanel.contains(element)) continue;

                    console.log('Element:', `${element.tagName}.${element.className} [bid=${element.getAttribute('bid')}]`);
                    
                    // Handle parameter group headers (expand/collapse)
                    if (element.hasAttribute) {
                        if (element.hasAttribute('data-group')) {
                            const groupName = element.getAttribute('data-group');
                            console.log('Coordinate-based toggle of parameter group:', groupName);
                            this.toggleGroup(groupName);
                            event.preventDefault();
                            event.stopPropagation();
                            return;
                        }
                        if (element.hasAttribute('data-toggle')) {
                            const nodeid = element.getAttribute('data-toggle');
                            console.log('Coordinate-based toggle of parameter parent:', nodeid);
                            this.toggleParent(nodeid);
                            event.preventDefault();
                            event.stopPropagation();
                            return;
                        }
                    }
                    
                    // Handle spinner buttons
                    if (element.classList && element.classList.contains('parameter-spinner-btn')) {
                        console.log('Coordinate-based spinner button click:', element);
                        const action = element.getAttribute('data-action');
                        const paramName = element.getAttribute('data-param');
                        this.handleSpinnerClick(paramName, action);
                        event.preventDefault();
                        event.stopPropagation();
                        return;
                    }
                    
                    // Handle checkboxes
                    if (element.classList && element.classList.contains('parameter-checkbox')) {
                        console.log('Coordinate-based checkbox click:', element);
                        element.checked = !element.checked;
                        this.handleParameterChange(element);
                        event.preventDefault();
                        event.stopPropagation();
                        return;
                    }
                    
                    // Handle dropdowns
                    if (element.classList && element.classList.contains('parameter-dropdown')) {
                        console.log('Coordinate-based dropdown click:', element);
                        element.focus();
                        // Let dropdown handle itself naturally
                        return;
                    }
                    
                    // Handle number inputs
                    if (element.classList && element.classList.contains('parameter-number-input')) {
                        console.log('Coordinate-based number input click:', element);
                        element.focus();
                        return;
                    }
                    
                    // Handle parameter group headers by checking parent elements
                    let parent = element.parentElement;
                    while (parent && rightPanel.contains(parent)) {
                        if (parent.hasAttribute && parent.hasAttribute('data-group')) {
                            const groupName = parent.getAttribute('data-group');
                            console.log('Coordinate-based toggle of parameter group (via parent):', groupName);
                            this.toggleGroup(groupName);
                            event.preventDefault();
                            event.stopPropagation();
                            return;
                        }
                        parent = parent.parentElement;
                    }
                }
            }
        }, true); // Capture phase - intercepts before any other handlers
    }
    
    
    toggleParent(nodeid) {
        const header = this.element.querySelector(`[data-toggle="${nodeid}"]`);
        const content = this.element.querySelector(`[data-toggle-content="${nodeid}"]`);
        const icon = header?.querySelector('.collapse-icon');
        
        if (header && content && icon) {
            if (content.style.display === 'none') {
                // Expand
                content.style.display = 'block';
                icon.textContent = '▼';
            } else {
                // Collapse
                content.style.display = 'none';
                icon.textContent = '▶';
            }
        }
    }
    


    toggleGroup(groupName) {
        const header = this.element.querySelector(`[data-group="${groupName}"]`);
        const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
        const icon = header?.querySelector('.parameter-group-icon');
        
        if (header && content && icon) {
            if (content.style.display === 'none') {
                // Expand
                header.classList.remove('collapsed');
                content.style.display = 'block';
                icon.textContent = '▼';
                this.collapsedGroups.delete(groupName);
            } else {
                // Collapse
                header.classList.add('collapsed');
                content.style.display = 'none';
                icon.textContent = '▶';
                this.collapsedGroups.add(groupName);
            }
        }
    }
    

    
    setupCollapseEventListeners() {
        // Group collapse/expand functionality
        const groupHeaders = this.element.querySelectorAll('.parameter-group-header[data-group]');
        groupHeaders.forEach(header => {
            this.addEventListener(header, 'click', (e) => {
                const groupName = header.dataset.group;
                const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
                const icon = header.querySelector('.parameter-group-icon');
                
                if (header.classList.contains('collapsed')) {
                    header.classList.remove('collapsed');
                    content.style.display = 'block';
                    icon.textContent = '▼';
                } else {
                    header.classList.add('collapsed');
                    content.style.display = 'none';
                    icon.textContent = '▶';
                }
            });
        });
        
        // Parameter input change handlers
        const numberInputs = this.element.querySelectorAll('.parameter-number-input');
        numberInputs.forEach(input => {
            this.addEventListener(input, 'change', (e) => {
                this.handleParameterChange(e.target);
            });
            
            this.addEventListener(input, 'input', (e) => {
                this.updateSliderFromInput(e.target);
            });
        });
        
        // Checkbox handlers
        const checkboxes = this.element.querySelectorAll('.parameter-checkbox');
        checkboxes.forEach(checkbox => {
            this.addEventListener(checkbox, 'change', (e) => {
                this.handleParameterChange(e.target);
            });
        });
        
        // Dropdown handlers
        const dropdowns = this.element.querySelectorAll('.parameter-dropdown, .inspector-target-select');
        dropdowns.forEach(dropdown => {
            this.addEventListener(dropdown, 'change', (e) => {
                this.handleParameterChange(e.target);
            });
        });
        
        // NEW: Generic parameter control handlers for GenericNodeRenderer controls
        const parameterControls = this.element.querySelectorAll('.parameter-control');
        parameterControls.forEach(control => {
            this.addEventListener(control, 'change', (e) => {
                console.log('Parameter control changed:', e.target.dataset.parameter, e.target.value);
                this.handleParameterChange(e.target);
            });
            
            // Also handle input events for real-time updates on number inputs
            if (control.type === 'number' || control.type === 'range') {
                this.addEventListener(control, 'input', (e) => {
                    this.handleParameterChange(e.target);
                });
            }
        });
    }
    
    handleParameterChange(element) {
        const paramName = element.id || element.dataset.param;
        const value = element.type === 'checkbox' ? element.checked : element.value;
        
        console.log(`Parameter changed: ${paramName} = ${value}`);
        
        // Update the actual parameter if we have a selected node
        if (this.selectedNode && paramName) {
            this.updateParameterValue(paramName, value);
        }
    }
    
    handleSpinnerClick(paramName, action) {
        // Find the corresponding input field
        const input = this.element.querySelector(`input[data-param="${paramName}"]`);
        if (!input) return;
        
        const currentValue = parseFloat(input.value) || 0;
        const step = parseFloat(input.step) || 0.01;
        const min = input.min ? parseFloat(input.min) : -Infinity;
        const max = input.max ? parseFloat(input.max) : Infinity;
        
        let newValue;
        if (action === 'increment') {
            newValue = Math.min(max, currentValue + step);
        } else if (action === 'decrement') {
            newValue = Math.max(min, currentValue - step);
        } else {
            return;
        }
        
        // Update the input value
        input.value = newValue;
        
        // Trigger parameter change
        this.handleParameterChange(input);
        
        console.log(`Spinner ${action}: ${paramName} = ${newValue}`);
    }
    
    updateSliderFromInput(input) {
        const container = input.closest('.parameter-input-container');
        const slider = container?.querySelector('.parameter-slider');
        
        if (slider) {
            // Update slider position based on input value
            // This would need proper min/max values for accurate positioning
            const value = parseFloat(input.value) || 0;
            // For now, just show that the slider is responsive
            const track = slider.querySelector('.parameter-slider-track');
            const thumb = slider.querySelector('.parameter-slider-thumb');
            
            // Simple percentage calculation (would need proper min/max)
            const percentage = Math.min(100, Math.max(0, (value / 100) * 100));
            track.style.width = `${percentage}%`;
            thumb.style.left = `${percentage}%`;
        }
    }
    
    updateSelection(selection) {
        if (selection.size === 1) {
            const nodeId = Array.from(selection)[0];
            this.loadNodeParameters(nodeId);
        } else if (selection.size > 1) {
            this.showMultipleSelection(selection);
        } else {
            this.showNoSelection();
        }
    }
    
    /**
     * GENERIC: Find node data directly from scene list
     * This replaces specialized cache lookups with direct scene access
     */
    findNodeInSceneItems(handle) {
        if (!this.scene || !this.scene.items || !Array.isArray(this.scene.items)) {
            return null;
        }
//        return this.scene.map[handle];

        // Search recursively through scene
        const findRecursively = (items) => {
            for (const item of items) {
                if (item.handle == handle) {
                    return item;
                }
                if (item.children && item.children.length > 0) {
                    const found = findRecursively(item.children);
                    if (found) return found;
                }
            }
            return null;
        };
        
        return findRecursively(this.scene.items);
       
    }
    
   
    async updateSelectedNode(handle) {
        console.log('NodeInspector received selection handle:', handle);
        
        // Find node data directly from scene list (generic approach)
        const nodeData = this.findNodeInSceneItems(handle);
        if (!nodeData) {
            console.warn(' No node data found for handle:', handle);
            return;
        }
        
        // Set selection state using handle and node data
        this.selectedNodeHandle = handle;
        this.selectedNode = handle;
        this.selectedNodeType = nodeData.outtype;
        this.selectedNodeName = nodeData.name;
        
        // Generic parameter loading based on node type mapping
        await this.renderNodes({
            handle: handle,
            nodeName: nodeData.name,
            nodeType: nodeData.outtype,
            nodeData: nodeData
        });
        // Emit resize event for components
        setTimeout(() => {
            window.dispatchEvent(new Event('resize'));
        }, 300);        
    }
    
    /**
     * GENERIC: Load node parameters based on node type mapping
     * This replaces specialized functions with a generic approach
     */
    async renderNodes(nodeInfo) {
        // Show loading state
        this.showLoadingState(nodeInfo);
        
        try {
            // Render the inspector using GenericNodeRenderer
            this.renderNodesRecurse(nodeInfo);
            
        } catch (error) {
            console.error('❌ Failed to load generic node parameters:', error);
        }
    }
    

    /**
     * GENERIC: Render parameter inspector using GenericNodeRenderer
     */
    renderNodesRecurse(nodeInfo) {
        const nodeName = nodeInfo.nodeName || nodeInfo.name || 'Unknown Node';
        
        const nodeHandle = nodeInfo.handle;
        let nodeData = this.findNodeInSceneItems(nodeHandle);

        if (!nodeData) {
            console.error('❌ Node data not found for handle:', nodeHandle);
            return;
        }
        const html = this.genericRenderer.renderNode(nodeData);
//        const html = this.renderNode(nodeData);
        
        // Update the inspector container directly
        const inspectorContainer = document.getElementById('node-inspector');
        if (inspectorContainer) {
            inspectorContainer.innerHTML = html;
            this.genericRenderer.setupEventHandlers(inspectorContainer);
        } else {
            console.error('❌ Node inspector container not found');
        }
        
        // Setup event listeners for the new content
        this.setupCollapseEventListeners();
    }

    
    async updateParameterValue(paramName, value) {
        if (!this.selectedNode) return;
        
        try {
            await this.client.updateNodeParameter(this.selectedNode, paramName, value);
            this.parameters[paramName] = { ...this.parameters[paramName], value };
        } catch (error) {
            console.error('Failed to update parameter:', error);
        }
    }
    

    updateParameter(nodeId, parameterName, value) {
        if (nodeId === this.selectedNode && this.parameters[parameterName]) {
            this.parameters[parameterName].value = value;
            // Update UI to reflect the change
            this.updateParameterUI(parameterName, value);
        }
    }
    

    updateParameterUI(paramName, value) {
        const input = this.element.querySelector(`[data-param="${paramName}"]`);
        if (input) {
            if (input.type === 'checkbox') {
                input.classList.toggle('checked', value);
            } else {
                input.value = value;
            }
        }
    }
    
    
    /**
     * Handle parameter value changes with safe API calls
     */
    async handleParameterChange(element) {
        if (!this.selectedNodeHandle) {
            console.warn('handleParameterChange No selected node handle for parameter change');
            return;
        }
        const handle = element.dataset.handle ? parseInt(element.dataset.handle) : 0;
//        const nodeData = this.scene.map[handle];
        const nodeData = this.findNodeInSceneItems(handle);
        if (nodeData == null || nodeData.attrType == null) {
            console.warn('handleParameterChange node error no attr', handle, {element});
            return;
        }
        const newValue = this.getElementValue(element);
        
//        console.log(`handleParameterChange "${nodeData.name}" to:`, newValue);
        
        const CONST_ATTR_MAP = {
            ["AT_BOOL"]: "set27",
            ["AT_FLOAT"]: "set34",
            ["AT_FLOAT2"]: "set34",
            ["AT_FLOAT3"]: "set34",
            ["AT_FLOAT4"]: "set37",
            ["AT_INT"]: "set34",
            ["AT_INT2"]: "set34",
            ["AT_INT3"]: "set34",
            ["AT_INT4"]: "set34",
            ["AT_STRING"]: "set34",
            ["AT_FILENAME"]: "set34",
        };
        const sig = CONST_ATTR_MAP[nodeData.attrType]
        if (sig == null) {
            console.log(`handleParameterChange no callback for: `, nodeData.attrType);
            return;
        }
        let callsig = "ApiItemGetter/set" + sig;
        let result;
        try {        
             result = window.grpcApi.makeApiCallSync(
                'ApiItemSetter/set27', 
                nodeData.handle,
                { id: window.OctaneTypes.AttributeId.A_VALUE,
                    value: newValue,
                    evaluate: true,
                },
            );
            if (!result.success) {
                throw new Error('Failed ApiItemSetter/set27');
            }
        } catch (error) {
            console.error('❌ Failed handleParameterChange:', error);
        }     
    }
    
    /**
     * Get value from UI element based on its type
     */
    getElementValue(element) {

        const handle = element.dataset.handle ? parseInt(element.dataset.handle) : 0;
//        const nodeData = this.scene.map[handle];
        const nodeData = this.findNodeInSceneItems(handle);
        if (nodeData == null || nodeData.attrType == null) {
            console.warn('getElementValue node error no attr', handle, {element});
            return;
        }
        return this.genericRenderer.getValue(nodeData);
    }
    
    showMultipleSelection(selection) {
        this.element.innerHTML = `
            <div class="inspector-loading">
                Multiple objects selected (${selection.size})
                <br><small>Multi-object editing not yet supported</small>
            </div>
        `;
    }
    
    showNoSelection() {
        // Show the default inspector content
//        this.renderDefaultInspector();
    }
    
    showError(message) {
        this.element.innerHTML = `
            <div class="inspector-loading" style="color: var(--octane-accent-red);">
                ❌ ${message}
            </div>
        `;
    }

    showLoadingState(data) {
        this.element.innerHTML = `
            <div class="node-inspector-header">
                <h3>Node inspector</h3>
                <select class="node-selector">
                    <option value="${data.nodeName}" selected>${data.nodeName}</option>
                </select>
            </div>
            <div class="node-inspector-content">
                <div class="parameter-section">
                    <div class="parameter-row">
                        <span class="parameter-icon">📦</span>
                        <span class="parameter-label">Object Handle:</span>
                        <span class="parameter-value">[${data.nodeId || this.selectedNodeHandle}]</span>
                    </div>
                    <div class="parameter-row">
                        <span class="parameter-icon">📄</span>
                        <span class="parameter-label">Type:</span>
                        <span class="parameter-value">${data.nodeType}</span>
                    </div>
                </div>
                
                <div class="loading-parameters">
                    <div class="loading-spinner"></div>
                    <p>Loading parameters...</p>
                </div>
            </div>
        `;
    }
    
    
    /**
     * Utility delay function
     */
    delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspector;
} else if (typeof window !== 'undefined') {
    window.NodeInspector = NodeInspector;
}