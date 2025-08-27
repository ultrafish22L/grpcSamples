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
    }
    
    setupControlEventListeners() {
        //  Generic parameter control handlers for GenericNodeRenderer controls
        const parameterControls = this.element.querySelectorAll('.parameter-control');
        parameterControls.forEach(control => {
            this.addEventListener(control, 'change', (e) => {
                console.log('.parameter-control change:', e.target.dataset.parameter, e.target.value);
                this.handleParameterChange(e.target);
            });
/*
            this.addEventListener(control, 'input', (e) => {
                console.log('.parameter-control input:', e.target.dataset.parameter, e.target.value);
                this.handleParameterChange(e.target);
            });
*/
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
    
    /**
     * Find node data directly from scene list
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
            this.genericRenderer.setupEventHandlers(inspectorContainer);
        } else {
            console.error('❌ Failed NodeInspector.renderNodesRecurse()');
        }
        
        // Setup event listeners for the controls
        this.setupControlEventListeners();
    }

    
    async updateParameterValue(paramName, value) {
        if (!this.selectedNode) return;
        
        try {
            await this.client.updateNodeParameter(this.selectedNode, paramName, value);
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
        const nodeData = this.findNodeInSceneItems( handle);
        if (nodeData == null || nodeData.attrInfo == null) {
            console.warn('NodeInspector.handleParameterChange() nodeData == null || nodeData.attrInfo == null', handle, {element});
            return;
        }
        const datatype = element.dataset.type;
        const component = element.dataset.component;
        console.log(`handleParameterChange ${nodeData.name} ${datatype} ${component ? component:""} `, element.value);

        let value = nodeData.value
        console.log(`handleParameterChange nodeData.value = `, JSON.stringify(value));
        switch (nodeData.attrInfo.type) {
        case "AT_BOOL":
            value[datatype] = element.value == "on" ? 1 : 0;
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
        console.log(`handleParameterChange newValue = `, JSON.stringify(value));
        nodeData.value = value

        let result;
        try {        
             result = window.grpcApi.makeApiCallSync(
                'ApiItem/setByAttrID', 
                nodeData.handle,
                { id: window.OctaneTypes.AttributeId.A_VALUE,
                    evaluate: true,
                    ...value,
                },
            );
            if (!result.success) {
                throw new Error('NodeInspector.Failed ApiItem/setByAttrId');
            }
            result = window.grpcApi.makeApiCallSync('ApiChangeManager/update');            
            if (!result.success) {
                throw new Error('Failed ApiChangeManager/update');
            }
        } catch (error) {
            console.error('❌ Failed NodeInspector.handleParameterChange(): ', error);
        }     
    }
    
    /**
     * Get value from UI element based on its type
     */
    getElementValue(element) {

        const handle = element.dataset.handle ? parseInt(element.dataset.handle) : 0;
//        const nodeData = this.scene.map[handle];
        const nodeData = this.findNodeInSceneItems(handle);
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

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspector;
} else if (typeof window !== 'undefined') {
    window.NodeInspector = NodeInspector;
}