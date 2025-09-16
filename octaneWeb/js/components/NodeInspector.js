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
    constructor(element, stateManager) {
        super(element, stateManager);
        
        // Current node selection state
        this.selectedNode = null;             // Currently selected node handle
        this.selectedNodeType = null;         // Type of selected node for rendering
        this.parameters = {};                 // Current parameter values cache
        
        // UI state management
        this.sceneDataLoaded = false;        // Scene data loading state
        this.collapsedGroups = new Set(); // Track expanded/collapsed state
        this.collapsedNodes = new Set();  // Track expanded nodes

        // Generic node rendering system for flexible parameter display
        this.genericRenderer = null;         // Initialized in onInitialize()
        this.nodeHtmlMap = new Map();
    }
    
    async onInitialize() {
        // Initialize Generic Node Renderer
        this.genericRenderer = new window.GenericNodeRenderer(window.OctaneIconMapper);
        console.log('NodeInspector: GenericNodeRenderer initialized');

         this.renderNodes();
    }
    
    setupEventListeners() {
        // Listen for scene data loading 
        this.eventSystem.on('sceneDataLoaded', (scene) => {

            this.sceneDataLoaded = true;
            console.log('NodeInspector received sceneDataLoaded event:', scene.tree.length);
        });
        
        // Listen for node selection 
        this.eventSystem.on('sceneNodeSelected', (handle) => {
            this.updateSelectedNode(handle);
        });
        
        // Listen for node parameter updates
        window.octaneClient.on('nodeParameterUpdate', (data) => {
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
        //

        // Handle expand/collapse clicks
        rightPanel.addEventListener('click', (event) => {

            // Get click coordinates
            const x = event.clientX;
            const y = event.clientY;
            console.log('click detected in right panel at:', x, y);

            let element = event.target.closest('[data-toggle]');
            if (element) {
                const nodeid = element.getAttribute('data-toggle');
                console.log('Coordinate-based toggle of parameter parent:', nodeid);
                this.toggleParent(nodeid);

                event.preventDefault();
                event.stopPropagation();
                return;
            }
            element = event.target.closest('[data-group]');
            if (element) {
                const nodeid = element.getAttribute('data-group');
                console.log('Coordinate-based toggle of parameter group:', nodeid);
                this.toggleGroup(nodeid);

                event.preventDefault();
                event.stopPropagation();
                return;
            }
        });

        return;

        // Global document click handler that intercepts ALL clicks
        rightPanel.addEventListener('click', (event) => {
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

        console.log('toggleParent:', nodeid);
//        console.log('toggleParent:', `${this.element.tagName}.${this.element.className} [bid=${this.element.getAttribute('bid')}]`);
        
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
        const icon = header?.querySelector('.inspector-group-icon');
        
        console.log('toggleGroup:', groupName);
//        console.log('toggleGroup:', `${element.tagName}.${element.className} [bid=${element.getAttribute('bid')}]`);

        if (header && content && icon) {
            if (content.style.display === 'none') {
                // Expand
//                header.classList.remove('collapsed');
                content.style.display = 'block';
                icon.textContent = '▼';
                this.collapsedGroups.delete(groupName);
            } else {
                // Collapse
//                header.classList.add('collapsed');
                content.style.display = 'none';
                icon.textContent = '▶';
                this.collapsedGroups.add(groupName);
            }
        }
    }
    

    
    setupControlEventListeners() {
/*        
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
  */      
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
                console.log('.parameter-control change:', e.target.dataset.parameter, e.target.value);
                this.handleParameterChange(e.target);
            });
        });
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
    

    
   
    async updateSelectedNode(handle) {
        console.log('NodeInspector received selection handle:', handle);
        
        // Find node data directly from scene list (generic approach)
        const nodeData = window.octaneClient.lookupItem(handle);
        if (nodeData.handle && nodeData.handle == this.selectedNodeHandle) {
            // no change
            return;
        }
        this.selectedNodeHandle = nodeData.handle;

        // Generic parameter loading based on node type mapping
        await this.renderNodes(nodeData);

        // Emit resize event for components
        setTimeout(() => {
            window.dispatchEvent(new Event('resize'));
        }, 300);        
    }
    
    /**
     * GENERIC: Load node parameters based on node type mapping
     * This replaces specialized functions with a generic approach
     */
    async renderNodes(nodeData) {
        // Show loading state
        this.showLoadingState(nodeData);
        
        try {
            // Render the inspector using GenericNodeRenderer
            this.renderNodesRecurse(nodeData);
            
        } catch (error) {
            console.error('❌ Failed NodeInspector.renderNodes():', error);
        }
    }
    

    /**
     * GENERIC: Render parameter inspector using GenericNodeRenderer
     */
    renderNodesRecurse(nodeData) {
        if (!nodeData) {
            console.error('❌ Failed NodeInspector.renderNodesRecurse() : nodeData == null');
            return;
        }
        console.log(`NodeInspector.renderNodesRecurse() ${nodeData.name} ${nodeData.outType}`);

        const html = this.genericRenderer.renderNode(nodeData);
//        const html = this.renderNode(nodeData);
        
        // Update the inspector container directly
        const inspectorContainer = document.getElementById('node-inspector');
        if (inspectorContainer) {
            inspectorContainer.innerHTML = html;
//            this.genericRenderer.setupEventHandlers(inspectorContainer);
        } else {
            console.error('❌ Failed NodeInspector.renderNodesRecurse()');
        }
        
        // Setup event listeners for the controls
        this.setupControlEventListeners();
    }

    
    async updateParameterValue(paramName, value) {
        if (!this.selectedNode) return;
        
        try {
            await window.octaneClient.updateNodeParameter(this.selectedNode, paramName, value);
            this.parameters[paramName] = { ...this.parameters[paramName], value };
        } catch (error) {
            console.error('NodeInspector.updateParameterValue(): ', error);
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
        const handle = element.dataset.handle;
        const nodeData = window.octaneClient.lookupItem( handle);
        if (nodeData == null || nodeData.attrInfo == null) {
            console.warn('NodeInspector.handleParameterChange() nodeData == null || nodeData.attrInfo == null', handle, {element});
            return;
        }
        const datatype = element.dataset.type;
        const component = element.dataset.component;

        let value = nodeData.value
        switch (nodeData.attrInfo.type) {
        case "AT_BOOL":
//            console.log(`handleParameterChange element.checked = ${element.checked}`);
            value[datatype] = element.checked;
            break;
        case "AT_FLOAT":
            value[datatype] = parseFloat(element.value);
            break;
        case "AT_INT":
        case "AT_LONG":
            value[datatype] = parseInt(element.value);
            break;
        case "AT_STRING":
        case "AT_FILENAME":
            value[datatype] = element.value
            break;
        case "AT_FLOAT2":
        case "AT_FLOAT3":
        case "AT_FLOAT4":
            value[datatype][component] = parseFloat(element.value);
            break;
        case "AT_INT2":
        case "AT_INT3":
        case "AT_INT4":
        case "AT_LONG2":
            value[datatype][component] = parseInt(element.value);
            break;
        }
        console.log(`handleParameterChange ${nodeData.name} ${datatype} ${component ? component:""} newValue = `, JSON.stringify(value));
        nodeData.value = value

        let response = window.octaneClient.makeApiCallAsync(
            'ApiItem/setByAttrID', 
            nodeData.handle,
            { id: window.OctaneTypes.AttributeId.A_VALUE,
                evaluate: true,
                ...value,
            },
        );
        if (response.success) {
            window.octaneClient.makeApiCallAsync('ApiChangeManager/update');         
        }   
    }
    
    /**
     * Get value from UI element based on its type
     */
    getElementValue(element) {

        const handle = element.dataset.handle ? parseInt(element.dataset.handle) : 0;
        const nodeData = window.octaneClient.lookupItem(handle);
        if (nodeData == null || nodeData.attrInfo == null) {
            console.warn('NodeInspector.getElementValue() node error no attr', handle, {element});
            return;
        }
//        return this.genericRenderer.getValue(nodeData);
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

    showLoadingState(nodeData) {
        if (!nodeData) {
            this.element.innerHTML = `
                <div class="node-inspector-header">
                    <h3>Node inspector</h3>
                </div>
                <div class="node-inspector-content">
                    <div class="empty-message">
                        <p>Empty</p>
                    </div>
                </div>
            `;
        }
        else {
            this.element.innerHTML = `
                <div class="node-inspector-header">
                    <h3>Node inspector</h3>
                    <select class="node-selector">
                        <option value="${nodeData.name}" selected>${nodeData.name}</option>
                    </select>
                </div>
                <div class="node-inspector-content">
                    <div class="loading-parameters">
                        <div class="loading-spinner"></div>
                        <p>Loading parameters...</p>
                    </div>
                </div>
            `;
        }
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspector;
} else if (typeof window !== 'undefined') {
    window.NodeInspector = NodeInspector;
}