/**
 * GenericNodeRenderer.js
 * 
 * Generic node inspector renderer that builds hierarchical node trees
 * from real tree data and ApiNodePinInfo, replacing hard-coded approaches.
 * 
 * Based on the actual Octane Node Inspector layout structure.
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
        
        // Render pin groups if pinInfo is available
        if (pinInfo && pinInfo.groups) {
            html += this.renderPinGroups(pinInfo.groups, 1);
        }
        
        return html;
    }
    
    /**
     * Render the top-level selected node (no indentation, no collapse icon)
     * @param {Object} nodeData - The selected node data
     * @returns {string} - HTML for the top node
     */
    renderTopNode(nodeData) {
        const icon = this.iconMapper?.getNodeIcon(nodeData.outtype, nodeData.name) || '📦';
        const color = this.iconMapper?.getNodeColor(nodeData.outtype) || '#666';
        
        return `
            <div class="node-box node-level-0" data-node-handle="${nodeData.handle}">
                <div class="node-icon-box" style="background-color: ${color}">
                    <span class="node-icon">${icon}</span>
                </div>
                <div class="node-content">
                    <div class="node-header">
                        <span class="node-title">${nodeData.name}</span>
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
        const icon = this.iconMapper?.getNodeIcon(nodeData.outtype, nodeData.name) || '📦';
        const color = this.iconMapper?.getNodeColor(nodeData.outtype) || '#666';
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
        `;
        
        // Render children if expanded
        if (hasChildren && isExpanded) {
            html += `<div class="node-children" data-children="${nodeId}">`;
            html += this.renderChildNodes(nodeData.children, level + 1);
            html += `</div>`;
        }
        
        html += `
                </div>
            </div>
        `;
        
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
        
        // For any other node type, add a generic dropdown
        if (nodeData.children && nodeData.children.length > 0) {
            return `
                <div class="node-parameter-controls">
                    <select class="parameter-dropdown" data-parameter="node-type">
                        <option value="default">${nodeData.name} settings</option>
                        <option value="advanced">Advanced ${nodeData.name}</option>
                    </select>
                </div>
            `;
        }
        
        return '';
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
     * Render a single pin/parameter
     * @param {Object} pinData - Pin data
     * @param {number} level - Indentation level
     * @returns {string} - HTML for the pin
     */
    renderPin(pinData, level) {
        const icon = this.iconMapper?.getParameterIcon(pinData.type) || '⚙';
        const color = this.iconMapper?.getNodeColor('PARAMETER') || '#444';
        const hasValue = pinData.value !== undefined && pinData.value !== null;
        
        let html = `
            <div class="node-box node-level-${level} parameter" data-pin-name="${pinData.name}">
                <div class="node-icon-box" style="background-color: ${color}">
                    <span class="node-icon">${icon}</span>
                </div>
                <div class="node-content">
                    <div class="node-header">
                        <span class="node-title">${pinData.name}:</span>
        `;
        
        // Add value display if available
        if (hasValue) {
            html += `<span class="parameter-value">${pinData.value}</span>`;
            if (pinData.unit) {
                html += `<span class="parameter-unit">${pinData.unit}</span>`;
            }
        }
        
        html += `
                    </div>
                </div>
            </div>
        `;
        
        return html;
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