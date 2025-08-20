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
        
        console.log(`🚀 GenericNodeRenderer: Rendering node "${nodeData.name}" type: ${nodeData.outtype}`);
        
        let html = '';
        
        // Render the top-level selected node (level 0, no indent, no collapse icon)
        html += this.renderTopNode(nodeData);
        
        // Render child nodes recursively if they exist, but exclude the selected node itself
        if (nodeData.children && nodeData.children.length > 0) {
            // Filter out the selected node from children to avoid duplication
            const filteredChildren = nodeData.children.filter(child => child.handle !== nodeData.handle);
            if (filteredChildren.length > 0) {
                html += this.renderChildNodes(filteredChildren, 1);
            }
        }
        
        return html;
    }
    
    /**
     * Render the top-level selected node (no indentation, no collapse icon)
     * @param {Object} nodeData - The selected node data
     * @returns {string} - HTML for the top node
     */
    renderTopNode(nodeData) {
        // Use inspector-specific color/icon if available, otherwise fall back to iconMapper
        const icon = nodeData.inspectorIcon || this.iconMapper?.getNodeIcon(nodeData.outtype, nodeData.name) || '📦';
        const color = nodeData.inspectorColor || this.iconMapper?.getNodeColor(nodeData.outtype) || '#666';
        
        return `
            <div class="node-box node-level-0" data-node-handle="${nodeData.handle}">
                <div class="node-icon-box" style="background-color: ${color}">
                    <span class="node-icon">${icon}</span>
                </div>
                <div class="node-content">
                    <div class="node-header">
                        <span class="node-title">${nodeData.name}</span>
                        ${this.renderNodeParameters(nodeData)}
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render child nodes recursively with proper indentation
     * @param {Array} children - Array of child node data
     * @param {number} level - Current indentation level
     * @returns {string} - HTML for child nodes
     */
    renderChildNodes(children, level) {
        if (!children || !Array.isArray(children)) return '';
        
        let html = '';
        
        for (const child of children) {
            html += this.renderNodeAtLevel(child, level);
        }
        
        return html;
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
        
        // Check if expanded: default to true if allNodesExpandedByDefault, otherwise check set
        const isExpanded = this.allNodesExpandedByDefault ? 
            !this.expandedNodes.has(`collapsed-${nodeId}`) : 
            this.expandedNodes.has(nodeId);
        
        // Determine collapse/expand icon
        let collapseIcon = '';
        if (hasChildren) {
            collapseIcon = isExpanded ? '▼' : '►';
        }
        
        let html = `
            <div class="node-box node-level-${level}" data-node-handle="${nodeData.handle}" data-node-id="${nodeId}">
                <div class="node-icon-box" style="background-color: ${color}">
                    <span class="node-icon">${icon}</span>
                </div>
                <div class="node-content">
                    <div class="node-header" ${hasChildren ? `data-toggle="${nodeId}"` : ''}>
                        ${collapseIcon ? `<span class="collapse-icon">${collapseIcon}</span>` : ''}
                        <span class="node-title">${nodeData.name}</span>
                        ${this.renderNodeParameters(nodeData)}
                    </div>
                </div>
            </div>
        `;
        
        // Render children if expanded - at the same level as parent, not nested inside
        if (hasChildren && isExpanded) {
            html += this.renderChildNodes(nodeData.children, level + 1);
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
        window.debugConsole?.addLog('info', ' renderNodeParameters:', nodeData.outtype);

        if (nodeData.pinInfo == null) {
            // For any other node type, add a generic dropdown
            return `
                <div class="node-parameter-controls">
                    <select class="parameter-dropdown" data-parameter="node-type">
                        <option value="default">${nodeData.name} settings</option>
                        <option value="advanced">Advanced ${nodeData.name}</option>
                    </select>
                </div>
            `;
        }
//        if (nodeData.outtype == "PT_BOOL" || nodeData.outtype == "PT_FLOAT") {
            return this.renderPin(nodeData);  
//        }
        return ``;
    }
    
        
    /**
     * Render a single pin/parameter with interactive controls
     * @param {Object} nodeData - Pin data
     * @returns {string} - HTML for the pin
     */
    renderPin(nodeData) {
        
        let html = `;
            <div class="octane-parameter-row" data-pin-name="${nodeData.name}">
                <div class="octane-parameter-label">
                    <span class="octane-parameter-name">${nodeData.name}</span>
                </div>
                <div class="octane-parameter-control">
        `;
       
        // Create appropriate control based on parameter type and value
        html = this.createParameterControl(nodeData);
        
//        html += `
//                </div>
//            </div>
//        `;
        
        return html;
    }

    /**
     * Render pin groups using ApiNodePinInfo data
     * @param {Array} groups - Pin group data from ApiNodePinInfo
     * @param {number} level - Current indentation level
     * @returns {string} - HTML for pin groups
     */
    renderPinGroups(groups, level) {
        if (!groups || !Array.isArray(groups)) return '';
        
        let html = '';
        
        for (const group of groups) {
            html += this.renderPinGroup(group, level);
        }
        
        return html;
    }
    
    /**
     * Render a single pin group
     * @param {Object} groupData - Pin group data
     * @param {number} level - Indentation level
     * @returns {string} - HTML for the pin group
     */
    renderPinGroup(groupData, level) {
        const groupId = `group-${groupData.name.toLowerCase().replace(/\s+/g, '-')}`;
        const isExpanded = this.expandedGroups.has(groupId);
        const collapseIcon = isExpanded ? '▼' : '►';
        const icon = this.iconMapper?.getPinGroupIcon(groupData.name) || '📁';
        const color = this.iconMapper?.getNodeColor('PIN_GROUP') || '#555';
        
        let html = `
            <div class="node-box node-level-${level} pin-group" data-group-id="${groupId}">
                <div class="node-icon-box" style="background-color: ${color}">
                    <span class="node-icon">${icon}</span>
                </div>
                <div class="node-content">
                    <div class="node-header" data-toggle="${groupId}">
                        <span class="collapse-icon">${collapseIcon}</span>
                        <span class="node-title">${groupData.name}</span>
                    </div>
        `;
        
        // Render group content if expanded
        if (isExpanded && groupData.pins) {
            html += `<div class="node-children" data-children="${groupId}">`;
            html += this.renderPinGroupPins(groupData.pins, level + 1);
            html += `</div>`;
        }
        
        html += `
                </div>
            </div>
        `;
        
        return html;
    }
    
    /**
     * Render pins within a pin group
     * @param {Array} pins - Array of pin data
     * @param {number} level - Indentation level
     * @returns {string} - HTML for pins
     */
    renderPinGroupPins(pins, level) {
        if (!pins || !Array.isArray(pins)) return '';
        
        let html = '';
        
        for (const pin of pins) {
            html += this.renderPin(pin, level);
        }
        
        return html;
    }
    
    /**
     * Create appropriate control for parameter
     * @param {Object} nodeData - Pin data
     * @returns {string} - HTML for the control
     */
    createParameterControl(nodeData) {
        const name = nodeData.name.toLowerCase();
        const index = nodeData.pinInfo.index

        const checked = 'checked';
        const numValue = 0;
        const value = "string";
        const x = 0;
        const y = 0;
        const z = 0;
            
/*
        if (nodeData.outtype == "PT_BOOL") {
            const checked = 'checked';
            return `<input type="checkbox" class="octane-checkbox parameter-control" ${checked} 
                           data-parameter="${nodeData.name}" data-index="${index}" data-type="boolean">`;
        }
        else if (nodeData.outtype == "PT_FLOAT") {

            const numValue = 0;
            return `<input type="number" class="octane-number-input parameter-control" value="${numValue}" step="0.001" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-type="number">`;
        }
        else if (nodeData.outtype == "PT_TEXTURE") {

            const colorValue = this.formatColorValue(0);
            return `<input type="color" class="octane-color-input parameter-control" value="${colorValue}" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-type="color">`;
        }
        
        // Dropdown parameters
        if (name.includes('mode') || name.includes('model') || name.includes('type') || 
            name.includes('alignment') || name.includes('action') || name.includes('order') ||
            name.includes('curve') || name.includes('quality') || name.includes('denoiser')) {
            return this.createDropdownControl(nodeData);
        }
        
        // Vector parameters (like position, target)
        if (name.includes('position') || name.includes('target') || name.includes('vector') ||
            name.includes('direction') || name.includes('shift') || name.includes('resolution')) {
            return this.createVectorControl(nodeData);
        }
*/        
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
        if (nodeData.attrType == "AT_BOOL") {
            return `<input type="checkbox" class="octane-checkbox parameter-control" ${checked} 
                           data-parameter="${nodeData.name}" data-index="${index}" data-type="boolean">`;
        }
        else if (nodeData.attrType == "AT_FLOAT") {
            return `<input type="number" class="octane-number-input parameter-control" value="${numValue}" step="0.001" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-type="number">`;
        }
        else if (nodeData.attrType == "AT_FLOAT2") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${x}" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="0" data-type="vector2">
                    <span class="vector-separator">×</span>
                    <input type="number" class="octane-vector-input parameter-control" value="${y}" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="1" data-type="vector2">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_FLOAT3" || nodeData.attrType == "AT_FLOAT4") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${x}" step="0.001" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="0" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${y}" step="0.001" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="1" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${z}" step="0.001" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="2" data-type="vector3">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_INT") {
                return `<input type="number" class="octane-number-input parameter-control" value="${numValue}" step="1" 
                        data-parameter="${nodeData.name}" data-index="${index}" data-type="number">`;
        }
        else if (nodeData.attrType == "AT_INT2") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${x}" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="0" data-type="vector2">
                    <span class="vector-separator">×</span>
                    <input type="number" class="octane-vector-input parameter-control" value="${y}" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="1" data-type="vector2">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_INT3") {
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${x}" step="1" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="0" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${y}" step="1" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="1" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${z}" step="1" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="2" data-type="vector3">
                </div>
            `;
        }
        else if (nodeData.attrType == "AT_STRING" || nodeData.attrType == "AT_FILENAME") {
                return `<input type="text" class="octane-text-input parameter-control" value="${value || ''}" 
                       data-parameter="${nodeData.name}" data-index="${index}" data-type="text">`;
        }
        return `<input type="text" class="octane-text-input parameter-control" value="${value || ''}" 
                data-parameter="${nodeData.name}" data-index="${index}" data-type="text">`;
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
        
        let html = `<select class="octane-dropdown parameter-control" data-parameter="${nodeData.name}" data-index="${index}" data-type="enum">`;
        options.forEach((option, optIndex) => {
            const selected = optIndex === 0 ? 'selected' : '';
            html += `<option value="${option.toLowerCase()}" ${selected}>${option}</option>`;
        });
        html += `</select>`;
        
        return html;
    }
    
    /**
     * Create vector control for multi-value parameters
     * @param {Object} nodeData - Pin data
     * @returns {string} - HTML for vector control
     */
    createVectorControl(nodeData) {
        const index = nodeData.index || 0;
        const value = nodeData.value || [];
        
        // For vector parameters, create multiple number inputs
        if (nodeData.name.toLowerCase().includes('resolution')) {
            const x = Array.isArray(value) ? (value[0] || 1920) : 1920;
            const y = Array.isArray(value) ? (value[1] || 1080) : 1080;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${x}" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="0" data-type="vector2">
                    <span class="vector-separator">×</span>
                    <input type="number" class="octane-vector-input parameter-control" value="${y}" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="1" data-type="vector2">
                </div>
            `;
        } else {
            // 3D vector (position, target, etc.)
            const x = Array.isArray(value) ? (value[0] || 0) : 0;
            const y = Array.isArray(value) ? (value[1] || 0) : 0;
            const z = Array.isArray(value) ? (value[2] || 0) : 0;
            return `
                <div class="octane-vector-control">
                    <input type="number" class="octane-vector-input parameter-control" value="${x}" step="0.001" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="0" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${y}" step="0.001" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="1" data-type="vector3">
                    <input type="number" class="octane-vector-input parameter-control" value="${z}" step="0.001" 
                           data-parameter="${nodeData.name}" data-index="${index}" data-component="2" data-type="vector3">
                </div>
            `;
        }
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


    

    async loadGenericParameterValues(nodeHandle) {
        window.debugConsole?.addLog('info', ['🔧 NodeInspector: Loading parameter values for handle', nodeHandle]);
        
        const parameters = {};
        
        try {
            // Get pin count for this node (single API call)
            window.debugConsole?.addLog('info', ['🔍 NodeInspector: Calling ApiNode/pinCount for handle', nodeHandle]);
            const pinCountResult = window.grpcApi.makeApiCallSync('ApiNode/pinCount', nodeHandle);
            window.debugConsole?.addLog('info', ['🔍 NodeInspector: Pin count result for handle', nodeHandle, ':', JSON.stringify(pinCountResult)]);
            
            if (pinCountResult && pinCountResult.success) {
                window.debugConsole?.addLog('info', ['📌 NodeInspector: Pin count API success, data:', JSON.stringify(pinCountResult.data), 'type:', typeof pinCountResult.data]);
                
                // Extract the actual pin count value
                let pinCount = 0;
                if (typeof pinCountResult.data === 'number') {
                    pinCount = pinCountResult.data;
                } else if (typeof pinCountResult.data === 'object' && pinCountResult.data !== null) {
                    // Handle different possible object structures
                    if (pinCountResult.data.value !== undefined) {
                        pinCount = pinCountResult.data.value;
                    } else if (pinCountResult.data.count !== undefined) {
                        pinCount = pinCountResult.data.count;
                    } else if (pinCountResult.data.pinCount !== undefined) {
                        pinCount = pinCountResult.data.pinCount;
                    } else {
                        // Try to get the first numeric property
                        for (const key in pinCountResult.data) {
                            if (typeof pinCountResult.data[key] === 'number') {
                                pinCount = pinCountResult.data[key];
                                window.debugConsole?.addLog('info', ['🔍 NodeInspector: Found numeric property', key, '=', pinCountResult.data[key]]);
                                break;
                            }
                        }
                    }
                }
                
                window.debugConsole?.addLog('info', ['📌 NodeInspector: Extracted pin count:', pinCount]);
                
                if (pinCount > 0) {
                    window.debugConsole?.addLog('info', ['📌 NodeInspector: Node has', pinCount, 'pins']);
                
                // Load all pin values using pinIx functions
                window.debugConsole?.addLog('info', ['🔄 NodeInspector: Starting to load', pinCount, 'pins using pinIx functions']);
                for (let pinIndex = 0; pinIndex < pinCount; pinIndex++) {
                    window.debugConsole?.addLog('info', ['🔄 NodeInspector: Loading pin', pinIndex, 'of', pinCount]);
                    try {
                        // Try type-specific ApiNode pinIx methods to get pin value
                        let pinValue = null;
                        let pinType = 'unknown';
                        
                        // Try different type-specific getters using ApiNode service (correct service for pinIx functions)
                        const typeGetters = [
                            { method: 'ApiNode/getPinBoolIx', type: 'bool' },
                            { method: 'ApiNode/getPinFloatIx', type: 'float' },
                            { method: 'ApiNode/getPinFloat2Ix', type: 'float2' },
                            { method: 'ApiNode/getPinFloat3Ix', type: 'float3' },
                            { method: 'ApiNode/getPinFloat4Ix', type: 'float4' },
                            { method: 'ApiNode/getPinIntIx', type: 'int' },
                            { method: 'ApiNode/getPinInt2Ix', type: 'int2' },
                            { method: 'ApiNode/getPinInt3Ix', type: 'int3' },
                            { method: 'ApiNode/getPinInt4Ix', type: 'int4' },
                            { method: 'ApiNode/getPinStringIx', type: 'string' },
                            { method: 'ApiNode/getPinFilePathIx', type: 'filepath' }
                        ];
                        
                        for (const getter of typeGetters) {
                            try {
                                const result = window.grpcApi.makeApiCallSync(getter.method, nodeHandle, { index: pinIndex });
                                if (result && result.success) {
                                    pinValue = result.data;
                                    pinType = getter.type;
                                    window.debugConsole?.addLog('info', ['✅ NodeInspector: Got', getter.type, 'value for pin index', pinIndex, ':', pinValue]);
                                    break;
                                }
                            } catch (error) {
                                // Continue to next type
                            }
                        }
                        
                        if (pinValue !== null) {
                            // Use pin index as key since we don't need pin names
                            const paramKey = `pin_${pinIndex}`;
                            parameters[paramKey] = {
                                value: pinValue,
                                pinIndex: pinIndex,
                                type: pinType,
                                name: paramKey
                            };
                            window.debugConsole?.addLog('info', ['✅ NodeInspector: Added parameter:', paramKey, 'type:', pinType, 'value:', pinValue]);
                        } else {
                            window.debugConsole?.addLog('warn', ['❌ NodeInspector: Failed to get value for pin index', pinIndex]);
                        }
                    } catch (pinError) {
                        window.debugConsole?.addLog('error', ['💥 NodeInspector: Error loading pin', pinIndex, ':', pinError.message]);
                    }
                }
                } else {
                    window.debugConsole?.addLog('warn', ['⚠️ NodeInspector: Pin count is 0 for handle', nodeHandle]);
                }
            } else {
                window.debugConsole?.addLog('error', ['❌ NodeInspector: Pin count API failed for handle', nodeHandle, 'result:', pinCountResult]);
            }
            
        } catch (error) {
            window.debugConsole?.addLog('error', ['❌ NodeInspector: Failed to load parameter values', error.message]);
        }
        
        return parameters;
    }

    */