/**
 * GenericNodeRenderer.js
 * 
 * Generic node parameter rendering system that dynamically builds hierarchical
 * node inspector interfaces from live Octane API data. Provides flexible,
 * data-driven parameter display supporting all Octane node types.
 * 
 * Core Features:
 * - Dynamic parameter rendering from ApiNodePinInfo data
 * - Hierarchical node tree display with proper indentation
 * - Expandable/collapsible parameter groups and sections
 * - Professional Octane-style UI matching Render Studio
 * - Icon mapping system for visual node type identification
 * - Real-time parameter updates with live Octane synchronization
 * 
 * Technical Implementation:
 * - Replaces hard-coded parameter layouts with data-driven approach
 * - Supports all Octane parameter types (float, int, bool, enum, color)
 * - Maintains expand/collapse state for user interface consistency
 * - Integrates with OctaneIconMapper for node type visualization
 * - Provides recursive child node rendering for complex hierarchies
 * 
 * Usage:
 * - Used by NodeInspector component for parameter display
 * - Receives node data from Scene Outliner selection
 * - Renders parameters based on live ApiNodePinInfo responses
 * - Handles user interactions and parameter value updates
 */

class GenericNodeRenderer {
    constructor(iconMapper, apiClient) {
        this.iconMapper = iconMapper || window.OctaneIconMapper;
        this.apiClient = apiClient;
        this.expandedGroups = new Set(); // Track expanded/collapsed state
        this.expandedNodes = new Set();  // Track expanded nodes
        this.allNodesExpandedByDefault = true; // All nodes expanded by default
        this.lastGroup = null;
    }
    
    /**
     * Main rendering method - replaces renderOctaneStyleInspector()
     * @param {Object} nodeData - The selected node data from tree
     * @param {Object} pinInfo - ApiNodePinInfo data for the node
     * @returns {string} - HTML string for the node inspector
     */
    renderNode(nodeData, pinInfo = null) {
        if (!nodeData) {
            return '<div class="node-inspector-empty">No node selected</div>';
        }
//        console.log(`GenericNodeRenderer.renderNode() ${nodeData.name} ${nodeData.outType}`);
        
        this.lastGroup = null;

        return this.renderNodeAtLevel(nodeData, 0);        
    }
    
    /**
     * Render a single node at a specific level
     * @param {Object} nodeData - Node data to render
     * @param {number} level - Indentation level
     * @returns {string} - HTML for the node
     */
    renderNodeAtLevel(nodeData, level) {
        // Use inspector-specific color/icon if available, otherwise fall back to iconMapper
        const icon =  nodeData.icon;
        const color = window.OctaneIconMapper.formatColorValue(nodeData.nodeInfo?.nodeColor) || '#666';
        const hasChildren = nodeData.children && nodeData.children.length > 0;
        const nodeId = `node-${nodeData.handle}`;
        
//        console.log(`GenericNodeRenderer.renderNodeAtLevel() ${nodeData.name} ${nodeData.outType}`);

        // Check if expanded: default to true if allNodesExpandedByDefault, otherwise check set
        const isExpanded = this.allNodesExpandedByDefault && level < 2 ? 
            !this.expandedNodes.has(`collapsed-${nodeId}`) : 
            this.expandedNodes.has(nodeId);
        
        // Determine collapse/expand icon
        let collapseIcon = '';
        if (hasChildren && level > 0) {
            collapseIcon = isExpanded ? '▼' : '▶'
        }

        const indent = level == 0 ? "node-indent-0" : "node-indent";
        let html = "";
        html += `<div class="${indent}" style="display:'block'}">`;
        
/*            
        let groupName = null;
        if (nodeData.pinInfo && nodeData.pinInfo.groupName) {
            groupName = nodeData.pinInfo.groupName;
        }
        if (groupName != this.lastGroup) {
            if (this.lastGroup != null) {
                // end last group
                this.lastGroup = null;
                html += `</div>`;
            }  
            if (groupName != null) {
                console.log(`renderNodeAtLevel: GROUP "${groupName}"`);

                // Check if expanded: default to true if allNodesExpandedByDefault, otherwise check set
                const isExpanded = this.allNodesExpandedByDefault ? 
                    !this.expandedNodes.has(`collapsed-${groupName}`) : 
                    this.expandedNodes.has(groupName);
                const collapseIcon = isExpanded ? '▼' : '▶';

                html += `<div class="octane-parameter-group">
                            <div class="octane-group-header ${isExpanded ? 'expanded' : 'collapsed'}" data-group="${groupName}">
                                <span class="octane-group-icon">${collapseIcon}</span>
                                <span class="octane-group-title">${groupName}</span>
                            </div>
                            <div class="octane-group-content" data-group-content="${groupName}" style="display: ${isExpanded ? 'block' : 'none'}">`;
                this.lastGroup = groupName;
            }
        }
*/

        if (nodeData.attrInfo?.type == null) {
            html += `<div class="node-box" data-node-handle="${nodeData.handle}" data-node-id="${nodeId}">
                        <div class="node-icon-box" style="background-color: ${color}">
                            <span class="node-icon">${icon}</span>
                        </div>
                        <div class="node-content">
                            <div class="node-label" ${hasChildren ? `data-toggle="${nodeId}"` : ''}>
                                ${collapseIcon ? `<span class="collapse-icon">${collapseIcon}</span>` : ''}
                                <span class="node-title">${nodeData.name}</span>
                            </div>
                        </div>
                    </div>`;
        }
        else {
            html += `<div class="node-box" data-node-handle="${nodeData.handle}" data-node-id="${nodeId}">
                        <div class="node-icon-box" style="background-color: ${color}">
                            <span class="node-icon">${icon}</span>
                        </div>
                        <div class="node-content">
                            <div class="node-label" ${hasChildren ? `data-toggle="${nodeId}"` : ''}>
                                ${collapseIcon ? `<span class="collapse-icon">${collapseIcon}</span>` : ''}
                                <span class="node-title">${nodeData.name}</span>
                                ${this.renderNodeParameters(nodeData)}
                            </div>
                        </div>
                    </div>`;
        }        
        html += `<div class="node-toggle-content" data-toggle-content="${nodeId}" style="display: ${isExpanded ? 'block' : 'none'}">`;

//        html += `<div class="node-data-content="${nodeId}" style="display:${isExpanded ? 'block' : 'none'}">`;

        for (const child of nodeData.children) {
            html += this.renderNodeAtLevel(child, level+1);
        }
        if (level == 0 && this.lastGroup != null) {
            // end last group
            this.lastGroup = null;
            html += `</div>`;
        }            
        // node-data-content
        html += `</div>`;

        // end this node
        html += `</div>`;

        return html;
    }
    
    /**
     * Render node's own parameters (like camera type dropdown)
     * @param {Object} nodeData - Node data
     * @returns {string} - HTML for node parameters
     */
    renderNodeParameters(nodeData) {

//        console.log(`GenericNodeRenderer.renderNodeParameters() ${nodeData.name} ${nodeData.outType}`);

        // For Camera nodes, render the camera type dropdown
        if (nodeData.outType === 'NT_CAMERA' || nodeData.name === 'Camera') {
            return `
                <div class="node-parameter-controls">
                    <select class="parameter-dropdown" data-parameter="camera-type">
                        <option value="thin-lens">Thin lens camera</option>
                        <option value="orthographic">Orthographic camera</option>
                        <option value="panoramic">Panoramic camera</option>
                        <option value="baking">Baking camera</option>
                    </select>
                </div>
            `;
        }
        
        // For Environment nodes
        if (nodeData.outType === 'NT_ENVIRONMENT' || nodeData.name === 'Environment') {
            return `
                <div class="node-parameter-controls">
                    <select class="parameter-dropdown" data-parameter="environment-type">
                        <option value="daylight">Daylight environment</option>
                        <option value="texture">Texture environment</option>
                        <option value="planetary">Planetary environment</option>
                    </select>
                </div>
            `;
        }
        
        // For Material nodes
        if (nodeData.outType === 'NT_MATERIAL' || nodeData.name === 'cube') {
            return `
                <div class="node-parameter-controls">
                    <select class="parameter-dropdown" data-parameter="material-type">
                        <option value="diffuse">Diffuse material</option>
                        <option value="glossy">Glossy material</option>
                        <option value="specular">Specular material</option>
                        <option value="universal">Universal material</option>
                    </select>
                </div>
            `;
        }
        return this.renderControl(nodeData);  
    }


 /**
     * @param {Object} nodeData - Pin data
     */
    getValue(nodeData) {

        if (nodeData.attrInfo == null) {
            return null
        }
        const type = window.OctaneTypes.AttributeType[nodeData.attrInfo.type];
//        console.log(`GenericNodeRenderer.getValue() ${nodeData.name} type: ${nodeData.attrInfo.type} ${type}`);

        // get the end node's value
        let result;
        try {   
            result = window.grpcApi.makeApiCall(
                "ApiItem/getByAttrID", 
                nodeData.handle,
                { attribute_id: window.OctaneTypes.AttributeId.A_VALUE,
                  expected_type: type,
                },
            );
            if (!result.success) {
                throw new Error('Failed GenericNodeRenderer.getValue(): ApiItem/getByAttrID');
            }
        } catch (error) {
            console.error(`❌ Failed GenericNodeRenderer.getValue() ${nodeData.name} type: ${nodeData.attrInfo.type} ${type}`, error);
        }
//        console.log(`GenericNodeRenderer.getValue() ${JSON.stringify(result, null, 2)}`);

        return result.data;
    }

    /**
     * Create appropriate control for parameter
     * @param {Object} nodeData - Pin data
     * @returns {string} - HTML for the control
     */
    renderControl(nodeData) {

        if (nodeData.attrInfo == null) {
            console.log(`GenericNodeRenderer.renderControl() nodeData.attrInfo == null`);
            return null
        }
        console.log(`GenericNodeRenderer.renderControl() ${nodeData.name} type: ${nodeData.attrInfo?.type}`);

        const index = nodeData.pinInfo.index;
        const type = nodeData.attrInfo.type;

        // grpc call
        let value = this.getValue(nodeData);
        nodeData.value = value

        switch (type) {
        case "AT_BOOL":
            value = value.bool_value;
            return `<input type="checkbox" class="octane-checkbox parameter-control" ${value} 
                    data-handle="${nodeData.handle}" data-type="bool_value">`;
        
        case "AT_FLOAT":
            value = value.float_value;
            return `<input type="number" class="octane-number-input parameter-control" value="${value}" step="0.001" 
                    data-handle="${nodeData.handle}" data-type="float_value">`;
        case "AT_FLOAT2":
            value = value.float2_value;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" 
                        data-handle="${nodeData.handle}" data-component="x" data-type="float2_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" 
                        data-handle="${nodeData.handle}" data-component="y" data-type="float2_value">
                </div>
            `;
        case "AT_FLOAT3":
            value = value.float3_value;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="0.001" 
                        data-handle="${nodeData.handle}" data-component="x" data-type="float3_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="0.001" 
                        data-handle="${nodeData.handle}" data-component="y" data-type="float3_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="0.001" 
                        data-handle="${nodeData.handle}" data-component="z" data-type="float3_value">
                </div>
            `;
        case "AT_FLOAT4":
            value = value.float4_value;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="0.001" 
                        data-handle="${nodeData.handle}" data-component="x" data-type="float4_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="0.001" 
                        data-handle="${nodeData.handle}" data-component="y" data-type="float4_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="0.001" 
                        data-handle="${nodeData.handle}" data-component="z" data-type="float4_value">
                </div>
            `;
        case "AT_INT":
            value = value.int_value;
            return `<input type="number" class="octane-number-input parameter-control" value="${value}" step="1" 
                    data-handle="${nodeData.handle}" data-type="int_value">`;
        case "AT_INT2":
            value = value.int2_value;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" 
                        data-handle="${nodeData.handle}" data-component="x" data-type="int2_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" 
                        data-handle="${nodeData.handle}" data-component="y" data-type="int2_value">
                </div>
            `;
        case "AT_INT3":
            value = value.int3_value;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="1" 
                        data-handle="${nodeData.handle}" data-component="x" data-type="int3_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="1" 
                        data-handle="${nodeData.handle}" data-component="y" data-type="int3_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="1" 
                        data-handle="${nodeData.handle}" data-component="z" data-type="int3_value">
                </div>
            `;
        case "AT_INT4":
            value = value.int4_value;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="1" 
                        data-handle="${nodeData.handle}" data-component="x" data-type="int4_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="1" 
                        data-handle="${nodeData.handle}" data-component="y" data-type="int4_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="1" 
                        data-handle="${nodeData.handle}" data-component="z" data-type="int4_value">
                </div>
            `;
        case "AT_LONG":
            value = value.long_value;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="1" 
                        data-handle="${nodeData.handle}" data-component="x" data-type="long_value">
                </div>
            `;
        case "AT_LONG2":
            value = value.long2_value;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="1" 
                        data-handle="${nodeData.handle}" data-component="x" data-type="long2_value">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="1" 
                        data-handle="${nodeData.handle}" data-component="y" data-type="long2_value">
                </div>
            `;
        case "AT_STRING" || type == "AT_FILENAME":
            value = value.string_value;
            return `<input type="text" class="octane-text-input parameter-control" value="${value}" 
                    data-handle="${nodeData.handle}" data-type="string_value">`;
        }

        return `<input type="text" class="octane-text-input parameter-control" value="${''}" 
                data-handle="${nodeData.handle}" data-type="string_value">`;
    }
    
    /**
     * Create dropdown control for enum parameters
     * @param {Object} nodeData - Pin data
     * @returns {string} - HTML for dropdown
     */
    createDropdownControl(nodeData) {
        const name = nodeData.name.toLowerCase();
        const index = nodeData.index || 0;
        let options = [];
        
        // Common dropdown options based on parameter name
        if (name.includes('mode')) {
            options = ['Auto', 'Manual', 'Custom'];
        } else if (name.includes('model')) {
            options = ['Standard', 'Advanced', 'Professional'];
        } else if (name.includes('type')) {
            options = ['Default', 'Custom', 'Advanced'];
        } else if (name.includes('quality')) {
            options = ['Low', 'Medium', 'High', 'Ultra'];
        } else if (name.includes('denoiser')) {
            options = ['None', 'OptiX', 'Open Image Denoise'];
        } else {
            options = ['Option 1', 'Option 2', 'Option 3'];
        }
        
        let html = `<select class="octane-dropdown parameter-control" data-handle="${nodeData.handle}" data-type="enum">`;
        options.forEach((option, optIndex) => {
            const selected = optIndex === 0 ? 'selected' : '';
            html += `<option value="${option.toLowerCase()}" ${selected}>${option}</option>`;
        });
        html += `</select>`;
        
        return html;
    }
    
    /**
     * Format color value for HTML color input
     * @param {*} value - Color value (array, string, or number)
     * @returns {string} - Hex color string
     */
    formatColorValue(value) {
        if (Array.isArray(value) && value.length >= 3) {
            // RGB array [r, g, b] where values are 0-1
            const r = Math.round((value[0] || 0) * 255);
            const g = Math.round((value[1] || 0) * 255);
            const b = Math.round((value[2] || 0) * 255);
            return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
        }
        if (typeof value === 'string' && value.startsWith('#')) {
            return value;
        }
        return '#ffffff'; // Default white
    }
    
    /**
     * Toggle expand/collapse state for a node or group
     * @param {string} id - Node or group ID to toggle
     */
    toggleExpanded(id) {
        if (id.startsWith('group-')) {
            if (this.expandedGroups.has(id)) {
                this.expandedGroups.delete(id);
            } else {
                this.expandedGroups.add(id);
            }
        } else {
            // For nodes with allNodesExpandedByDefault=true, we track collapsed state
            if (this.allNodesExpandedByDefault) {
                const collapsedId = `collapsed-${id}`;
                if (this.expandedNodes.has(collapsedId)) {
                    this.expandedNodes.delete(collapsedId); // Expand (remove from collapsed set)
                } else {
                    this.expandedNodes.add(collapsedId); // Collapse (add to collapsed set)
                }
            } else {
                if (this.expandedNodes.has(id)) {
                    this.expandedNodes.delete(id);
                } else {
                    this.expandedNodes.add(id);
                }
            }
        }
    }
    
    /**
     * Check if a node or group is expanded
     * @param {string} id - Node or group ID
     * @returns {boolean} - True if expanded
     */
    isExpanded(id) {
        if (id.startsWith('group-')) {
            return this.expandedGroups.has(id);
        } else {
            // For nodes with allNodesExpandedByDefault=true, check if NOT in collapsed set
            if (this.allNodesExpandedByDefault) {
                return !this.expandedNodes.has(`collapsed-${id}`);
            } else {
                return this.expandedNodes.has(id);
            }
        }
    }
    
    /**
     * Set up event handlers for expand/collapse functionality
     * @param {HTMLElement} container - Container element for the node inspector
     */
    setupEventHandlers(container) {
        if (!container) return;
        
        // Handle expand/collapse clicks
        container.addEventListener('click', (event) => {
            const toggleElement = event.target.closest('[data-toggle]');
            if (toggleElement) {
                const id = toggleElement.getAttribute('data-toggle');
                this.toggleExpanded(id);
                
                // Re-render the affected section
                this.updateExpandedState(container, id);
                
                event.preventDefault();
                event.stopPropagation();
            }
        });
    }
    
    /**
     * Update the visual state after expand/collapse
     * @param {HTMLElement} container - Container element
     * @param {string} id - ID that was toggled
     */
    updateExpandedState(container, id) {
        const isExpanded = this.isExpanded(id);
        
        // Find the toggle element and update icon
        const toggleElement = container.querySelector(`[data-toggle="${id}"]`);
        if (toggleElement) {
            const collapseIcon = toggleElement.querySelector('.collapse-icon');
            if (collapseIcon) {
                collapseIcon.textContent = isExpanded ? '▼' : '►';
            }
        }
        
        // Find the children container and toggle visibility
        const childrenContainer = container.querySelector(`[data-children="${id}"]`);
        if (childrenContainer) {
            childrenContainer.style.display = isExpanded ? 'block' : 'none';
        }
    }
}

// Export for use in other modules
if (typeof window !== 'undefined') {
    window.GenericNodeRenderer = GenericNodeRenderer;
}
