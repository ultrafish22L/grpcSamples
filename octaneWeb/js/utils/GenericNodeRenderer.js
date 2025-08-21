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

        // Initialize with common groups expanded by default
        this.expandedGroups.add('scene');
        this.expandedGroups.add('render-settings');
        this.expandedGroups.add('film-settings');
        this.expandedGroups.add('animation');
        this.expandedGroups.add('kernel');
        this.expandedGroups.add('quality');
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
        console.log(`GenericNodeRenderer: Rendering node "${nodeData.name}" type: ${nodeData.outtype}`);
        
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
        const icon = nodeData.inspectorIcon || this.iconMapper?.getNodeIcon(nodeData.outtype, nodeData.name) || '📦';
        const color = nodeData.inspectorColor || this.iconMapper?.getNodeColor(nodeData.outtype) || '#666';
        const hasChildren = nodeData.children && nodeData.children.length > 0;
        const nodeId = `node-${nodeData.handle}`;
        
        let html = ``;
        let groupName = null;
        if (nodeData.pinInfo && nodeData.pinInfo.groupName && nodeData.pinInfo.groupName) {
             groupName = nodeData.pinInfo.groupName;
        }
        if (groupName != this.lastGroup) {
            if (this.lastGroup != null) {
                // end last group
                this.lastGroup = null;
                html += `</div>`;
            }  
            if (groupName != null) {
                console.log(`renderNodeAtLevel: GROUP "${nodeData.pinInfo.groupName}"`);

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
        // Check if expanded: default to true if allNodesExpandedByDefault, otherwise check set
        const isExpanded = this.allNodesExpandedByDefault ? 
            !this.expandedNodes.has(`collapsed-${nodeId}`) : 
            this.expandedNodes.has(nodeId);
        
        // Determine collapse/expand icon
        let collapseIcon = '';
        if (hasChildren && level > 0) {
            collapseIcon = isExpanded ? '▼' : '►';
        }
        if (nodeData.attrType == null) {
            html += `<div class="node-box node-level-${level}" data-node-handle="${nodeData.handle}" data-node-id="${nodeId}">
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
            html += `<div class="node-box node-level-${level}" data-node-handle="${nodeData.handle}" data-node-id="${nodeId}">
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
        if (hasChildren) {
            html += `<div class="octane-group-content" data-toggle-content="${nodeId}" style="display: ${isExpanded ? 'block' : 'none'}">`;
            level++;
            for (const child of nodeData.children) {
                html += this.renderNodeAtLevel(child, level);
            }
            html += `</div>`;
        }
        if (level == 0 && this.lastGroup != null) {
            // end last group
            this.lastGroup = null;
            html += `</div>`;
        }            
        return html;
    }
    
    /**
     * Render node's own parameters (like camera type dropdown)
     * @param {Object} nodeData - Node data
     * @returns {string} - HTML for node parameters
     */
    renderNodeParameters(nodeData) {
        // For Camera nodes, render the camera type dropdown
        if (nodeData.outtype === 'NT_CAMERA' || nodeData.name === 'Camera') {
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
        if (nodeData.outtype === 'NT_ENVIRONMENT' || nodeData.name === 'Environment') {
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
        if (nodeData.outtype === 'NT_MATERIAL' || nodeData.name === 'cube') {
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
        if (nodeData.pinInfo == null) {
            // For any other node type, add a generic dropdown
/*
            return `
                <div class="node-parameter-controls">
                    <select class="parameter-dropdown" data-parameter="node-type">
                        <option value="default">${nodeData.name} settings</option>
                        <option value="advanced">Advanced ${nodeData.name}</option>
                    </select>
                </div>
            `;
*/
            return ``;
        }
        return this.renderControl(nodeData);  
    }
    
           
/*
    ATTRIBUTE_TYPE(AT_UNKNOWN   , 0)

    ATTRIBUTE_TYPE(AT_BOOL      , 1)
    ATTRIBUTE_TYPE(AT_INT       , 2)
    ATTRIBUTE_TYPE(AT_INT2      , 3)
    ATTRIBUTE_TYPE(AT_INT3      , 4)
    ATTRIBUTE_TYPE(AT_INT4      , 5)
    ATTRIBUTE_TYPE(AT_LONG      , 14)
    ATTRIBUTE_TYPE(AT_LONG2     , 15)
    ATTRIBUTE_TYPE(AT_FLOAT     , 6)
    ATTRIBUTE_TYPE(AT_FLOAT2    , 7)
    ATTRIBUTE_TYPE(AT_FLOAT3    , 8)
    ATTRIBUTE_TYPE(AT_FLOAT4    , 9)
    ATTRIBUTE_TYPE(AT_STRING    , 10)
    ATTRIBUTE_TYPE(AT_FILENAME  , 11)
    ATTRIBUTE_TYPE(AT_BYTE      , 12)
    ATTRIBUTE_TYPE(AT_MATRIX    , 13)
*/



 /**
     * @param {Object} nodeData - Pin data
     */
    getValue(nodeData) {

        console.log(`GenericNodeRenderer: getValue "${nodeData.name}" type: ${nodeData.attrType}`);

        if (nodeData.attrType == null) {
            return null
        }
        const stripAtAndCamelCase = str => {
            const result = str.startsWith("AT_") ? str.substring(3) : str;
            return result ? result.charAt(0).toUpperCase() + result.slice(1).toLowerCase() : result;
        };
        let callsig = "ApiItemGetter/get" + stripAtAndCamelCase(nodeData.attrType);
        let result;
        try {   
            result = window.grpcApi.makeApiCallSync(
                callsig, 
                nodeData.handle,
                { id: window.OctaneTypes.AttributeId.A_VALUE },
            );
            if (!result.success) {
                throw new Error('Failed getValue', callsig);
            }
        } catch (error) {
            console.error('❌ Failed getValue:', callsig, error);
        }
        let value = result.data.result;
        value = Array.isArray(value) ? value[0] : value;

        return value
    }

    /**
     * Create appropriate control for parameter
     * @param {Object} nodeData - Pin data
     * @returns {string} - HTML for the control
     */
    renderControl(nodeData) {

        const index = nodeData.pinInfo.index;

//        return `<input type="text" class="octane-text-input parameter-control" value="${''}" 
//        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-type="text">`;

        const value = this.getValue(nodeData);

        if (nodeData.attrType == "AT_BOOL") {
            return `<input type="checkbox" class="octane-checkbox parameter-control" ${value} 
                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-type="boolean">`;
        }
        else if (nodeData.attrType == "AT_FLOAT") {
            return `<input type="number" class="octane-number-input parameter-control" value="${value}" step="0.001" 
                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-type="number">`;
        }
        else if (nodeData.attrType == "AT_FLOAT2") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="vector2">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="1" data-type="vector2">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_FLOAT3") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="0.001" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="0.001" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="1" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="0.001" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="2" data-type="vector3">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_FLOAT4") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="0.001" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="0.001" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="1" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="0.001" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="2" data-type="vector3">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_INT") {
            return `<input type="number" class="octane-number-input parameter-control" value="${value}" step="1" 
                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-type="number">`;
        }
        else if (nodeData.attrType == "AT_INT2") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="vector2">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="1" data-type="vector2">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_INT3") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="1" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="1" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="1" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="1" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="2" data-type="vector3">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_STRING" || nodeData.attrType == "AT_FILENAME") {
            return `<input type="text" class="octane-text-input parameter-control" value="${value}" 
                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-type="text">`;
        }

        return `<input type="text" class="octane-text-input parameter-control" value="${''}" 
                data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-type="text">`;
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
        
        let html = `<select class="octane-dropdown parameter-control" data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-type="enum">`;
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

/*
            else if (nodeData.attrType == "AT_FLOAT4") {

                let result = window.grpcApi.makeApiCallSync(
                    'ApiItemGetter/getFloat4', 
                    nodeData.handle,
                    { id: window.OctaneTypes.AttributeId.A_VALUE },
                );
                if (!result.success) {
                    throw new Error('Failed ApiItemGetter/getFloat4');
                }
                const dims = nodeData.pinInfo.floatInfo.dimCount;

                switch (dims)
                {
                    case 1:
                    {
                        let value = result.data.result;
                        value = Array.isArray(value) ? value[0] : value;

                        return `
                            <div class="octane-vector-control">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="float">
                            </div>
                        `;
                    }
                        break;
                    case 2:
                    {
                        let value = result.data.result;
                        value = Array.isArray(value) ? value[0] : value;

                        return `
                            <div class="octane-vector-control">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="vector2">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="1" data-type="vector2">
                            </div>
                        `;
                    }
                        break;
                    case 3:
                    {
                        let value = result.data.result;
                        value = Array.isArray(value) ? value[0] : value;

                        return `
                            <div class="octane-vector-control">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="vector3">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="1" data-type="vector3">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="2" data-type="vector3">
                            </div>
                        `;
                    }
                        break;
                    case 4:
                    {
                        let value = result.data.result;
                        value = Array.isArray(value) ? value[0] : value;

                        return `
                            <div class="octane-vector-control">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.x}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="0" data-type="vector4">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.y}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="1" data-type="vector4">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.z}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="2" data-type="vector4">
                                <input type="number" class="octane-vector-input parameter-control" value="${value.w}" step="0.001" 
                                    data-parameter="${nodeData.name}" data-index="${index}" data-handle="${nodeData.handle}" data-component="3" data-type="vector4">
                            </div>
                        `;
                    }
                        break;
                }
            }

            */