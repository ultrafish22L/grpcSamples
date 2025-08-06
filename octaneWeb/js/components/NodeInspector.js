/**
 * Node Inspector Component
 * Professional Octane-style parameter controls for selected nodes
 * Matches the exact layout and styling of Octane Render Studio
 */

class NodeInspector extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        this.selectedNode = null;
        this.selectedNodeType = null;
        this.parameters = {};
        this.collapsedGroups = new Set();
        
        // Cache for scene data from Scene Outliner (optimization)
        this.nodeCache = new Map(); // handle -> nodeData
        this.nodeLookup = new Map(); // name -> handle
        this.sceneDataLoaded = false;
    }
    
    async onInitialize() {
//        this.renderGenericInspector();
        
        // Auto-select Render target by default (matching Octane Studio behavior)
//        setTimeout(() => {
//            this.autoSelectRenderTarget();
//        }, 500);
    }
    
    autoSelectRenderTarget() {
        // Simulate selecting the Render target node to match Octane Studio's default behavior
        const renderTargetData = {
            nodeId: 'render-target',
            nodeName: 'Render target',
            nodeType: 'render_target',
            source: 'autoSelect'
        };
        
        console.log('🎯 Auto-selecting Render target to match Octane Studio behavior');
        this.updateSelectedNode(renderTargetData);
        
        // Also emit the selection event to sync with other components
        this.eventSystem.emit('sceneNodeSelected', renderTargetData);
    }
    
    setupEventListeners() {
        // Listen for scene data loading from SceneOutliner (OPTIMIZATION)
        this.eventSystem.on('sceneDataLoaded', (sceneItems) => {
            this.updateSceneDataCache(sceneItems);
        });
        
        // Listen for selection updates
        this.client.on('ui:selectionUpdate', (selection) => {
            this.updateSelection(selection);
        });
        
        // Listen for scene node selection from SceneOutliner
        this.eventSystem.on('sceneNodeSelected', (data) => {
            this.updateSelectedNode(data);
        });
        
        // Listen for node selection from NodeGraphEditor
        this.eventSystem.on('nodeGraphNodeSelected', (data) => {
            this.updateSelectedNode(data);
        });
        
        // Listen for node parameter updates
        this.client.on('ui:nodeParameterUpdate', (data) => {
            this.updateParameter(data.nodeId, data.parameterName, data.value);
        });
        
        // Force click events to work by bypassing CSS pointer-events issues
        this.setupForceClickHandlers();
    }
    
    setupForceClickHandlers() {
        // ULTIMATE SOLUTION: Global coordinate-based click detection that bypasses all CSS pointer-events issues
        const rightPanel = document.querySelector('.right-panel');
        if (!rightPanel) return;

        console.log('🎯 Setting up coordinate-based click detection system');

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
                
                console.log('🎯 Coordinate-based click detected in right panel at:', x, y);
                
                // Use elementsFromPoint to find what's actually under the cursor
                const elementsUnderCursor = document.elementsFromPoint(x, y);
                console.log('🔍 Elements under cursor:', elementsUnderCursor.map(el => `${el.tagName}.${el.className} [bid=${el.getAttribute('bid')}]`));
                
                // Find the first clickable element in the right panel
                for (const element of elementsUnderCursor) {
                    // Skip elements that are not in the right panel
                    if (!rightPanel.contains(element)) continue;
                    
                    // Handle parameter group headers (expand/collapse)
                    if (element.hasAttribute && element.hasAttribute('data-group')) {
                        const groupName = element.getAttribute('data-group');
                        console.log('🔽 Coordinate-based toggle of parameter group:', groupName);
                        this.toggleParameterGroup(groupName);
                        event.preventDefault();
                        event.stopPropagation();
                        return;
                    }
                    
                    // Handle checkboxes
                    if (element.classList && element.classList.contains('parameter-checkbox')) {
                        console.log('☑️ Coordinate-based checkbox click:', element);
                        element.checked = !element.checked;
                        this.handleParameterChange(element);
                        event.preventDefault();
                        event.stopPropagation();
                        return;
                    }
                    
                    // Handle dropdowns
                    if (element.classList && element.classList.contains('parameter-dropdown')) {
                        console.log('📋 Coordinate-based dropdown click:', element);
                        element.focus();
                        // Let dropdown handle itself naturally
                        return;
                    }
                    
                    // Handle number inputs
                    if (element.classList && element.classList.contains('parameter-number-input')) {
                        console.log('🔢 Coordinate-based number input click:', element);
                        element.focus();
                        return;
                    }
                    
                    // Handle parameter group headers by checking parent elements
                    let parent = element.parentElement;
                    while (parent && rightPanel.contains(parent)) {
                        if (parent.hasAttribute && parent.hasAttribute('data-group')) {
                            const groupName = parent.getAttribute('data-group');
                            console.log('🔽 Coordinate-based toggle of parameter group (via parent):', groupName);
                            this.toggleParameterGroup(groupName);
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
    
    handleParameterClick(target, event) {
        // Handle collapsible group headers
        if (target.hasAttribute('data-group')) {
            const groupName = target.getAttribute('data-group');
            this.toggleParameterGroup(groupName);
            return;
        }
        
        // Handle other parameter controls
        if (target.classList.contains('parameter-checkbox')) {
            target.checked = !target.checked;
            this.updateParameterValue(target.id, target.checked);
        } else if (target.classList.contains('parameter-dropdown')) {
            // Let the dropdown handle itself
        } else if (target.classList.contains('parameter-input')) {
            target.focus();
        }
    }
    
    toggleParameterGroup(groupName) {
        const header = this.element.querySelector(`[data-group="${groupName}"]`);
        const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
        const icon = header?.querySelector('.parameter-group-icon');
        
        if (header && content && icon) {
            if (this.collapsedGroups.has(groupName)) {
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
    
    updateParameterValue(paramName, value) {
        console.log(`Updating parameter: ${paramName} = ${value}`);
        
        // Store the parameter value
        this.parameters[paramName] = value;
        
        // If we have a selected node, send the update to the server
        if (this.selectedNode) {
            this.client.emit('ui:updateNodeParameter', {
                nodeId: this.selectedNode,
                parameterName: paramName,
                value: value
            });
        }
    }
    
    setupInspectorEventListeners() {
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
                    this.collapsedGroups.delete(groupName);
                } else {
                    header.classList.add('collapsed');
                    content.style.display = 'none';
                    icon.textContent = '▶';
                    this.collapsedGroups.add(groupName);
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
        
        // Initialize collapsed state
        this.initializeCollapsedGroups();
    }
    
    initializeCollapsedGroups() {
        // Start with all groups collapsed except the main ones
        const collapsibleGroups = ['physical-camera', 'viewing-angle', 'clipping', 'depth-of-field'];
        collapsibleGroups.forEach(groupName => {
            const header = this.element.querySelector(`[data-group="${groupName}"]`);
            const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
            const icon = header?.querySelector('.parameter-group-icon');
            
            if (header && content && icon) {
                header.classList.add('collapsed');
                content.style.display = 'none';
                icon.textContent = '▶';
                this.collapsedGroups.add(groupName);
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
     * OPTIMIZATION: Update scene data cache from Scene Outliner
     * This eliminates the need for redundant tree traversal
     */
    updateSceneDataCache(sceneItems) {
        console.log('🚀 OPTIMIZATION: Updating Node Inspector cache with scene data');
        
        // Clear existing cache
        this.nodeCache.clear();
        this.nodeLookup.clear();
        
        // Recursively populate cache from scene tree
        this.populateCacheRecursively(sceneItems);
        
        this.sceneDataLoaded = true;
        console.log(`✅ OPTIMIZATION: Cached ${this.nodeCache.size} nodes for instant access`);
    }
    
    /**
     * Recursively populate node cache from scene tree data
     */
    populateCacheRecursively(items) {
        if (!items || !Array.isArray(items)) return;
        
        items.forEach(item => {
            if (item.handle) {
                // Store node data by handle
                this.nodeCache.set(item.handle, {
                    name: item.name,
                    handle: item.handle,
                    type: item.type,
                    outtype: item.outtype,
                    children: item.children || []
                });
                
                // Store name -> handle lookup
                if (item.name) {
                    this.nodeLookup.set(item.name, item.handle);
                }
            }
            
            // Recursively process children
            if (item.children && item.children.length > 0) {
                this.populateCacheRecursively(item.children);
            }
        });
    }
    
    /**
     * OPTIMIZATION: Get cached node data by handle
     */
    getCachedNodeData(handle) {
        return this.nodeCache.get(handle);
    }
    
    /**
     * OPTIMIZATION: Get node handle by name
     */
    getNodeHandleByName(name) {
        return this.nodeLookup.get(name);
    }
    
    async updateSelectedNode(data) {
        console.log('🎯 NodeInspector received selection from', data.source + ':', data);
        
        // Handle different data formats from SceneOutliner vs NodeGraphEditor
        this.selectedNode = data.nodeId || data.handle;
        this.selectedNodeType = data.nodeType;
        this.selectedNodeName = data.nodeName;
        this.selectedNodeHandle = data.handle || data.sceneHandle;
        
        // Update the dropdown to reflect the selected node
        this.updateInspectorDropdown(this.selectedNodeName);
        
        // Load and render full parameter tree for the selected node
        await this.loadAndRenderFullParameterTree(data);
    }
    
    updateInspectorDropdown(nodeName) {
        // Update the dropdown in the node inspector header to show the selected node
        const dropdown = this.element.querySelector('.node-selector select');
        if (dropdown && nodeName) {
            // Check if option exists, if not add it
            let optionExists = false;
            for (let option of dropdown.options) {
                if (option.value === nodeName) {
                    option.selected = true;
                    optionExists = true;
                    break;
                }
            }
            
            // If option doesn't exist, add it and select it
            if (!optionExists) {
                const newOption = document.createElement('option');
                newOption.value = nodeName;
                newOption.textContent = nodeName;
                newOption.selected = true;
                dropdown.appendChild(newOption);
            }
            
            console.log('🎯 Updated NodeInspector dropdown to:', nodeName);
        }
    }
    
    async loadNodeParameters(nodeId) {
        this.selectedNode = nodeId;
        
        try {
            // Get node details from client
            const nodeData = await this.client.getObjectDetails(nodeId);
            
            if (nodeData.success && nodeData.data) {
                this.parameters = nodeData.data.parameters || {};
                this.renderNodeInspector(nodeData.data);
            }
        } catch (error) {
            console.error('Failed to load node parameters:', error);
            this.showError('Failed to load node parameters');
        }
    }
    
    renderNodeInspector(nodeData) {
        const { name, type, parameters = {} } = nodeData;
        
        this.element.innerHTML = `
            <div class="node-inspector-header">
                <div class="node-type-icon">${this.getNodeTypeIcon(type)}</div>
                <div class="node-name">${name}</div>
            </div>
            <div class="inspector-content">
                ${this.renderParameterGroups(parameters)}
            </div>
        `;
        
        this.setupParameterEventListeners();
    }
    
    renderParameterGroups(parameters) {
        const groups = this.groupParameters(parameters);
        
        return Object.entries(groups).map(([groupName, groupParams]) => {
            return `
                <div class="parameter-group">
                    <div class="parameter-group-header">
                        <span>${groupName}</span>
                        <span class="parameter-group-toggle">▼</span>
                    </div>
                    <div class="parameter-group-content">
                        ${this.renderParameters(groupParams)}
                    </div>
                </div>
            `;
        }).join('');
    }
    
    groupParameters(parameters) {
        const groups = {};
        
        Object.entries(parameters).forEach(([name, param]) => {
            const groupName = param.group || 'General';
            if (!groups[groupName]) {
                groups[groupName] = {};
            }
            groups[groupName][name] = param;
        });
        
        return groups;
    }
    
    renderParameters(parameters) {
        return Object.entries(parameters).map(([name, param]) => {
            return this.renderParameter(name, param);
        }).join('');
    }
    
    renderParameter(name, param) {
        const { type, value, min, max, label } = param;
        const displayLabel = label || name;
        
        return `
            <div class="parameter-row">
                <div class="parameter-label">${displayLabel}:</div>
                <div class="parameter-control">
                    ${this.renderParameterControl(name, type, value, { min, max })}
                </div>
            </div>
        `;
    }
    
    renderParameterControl(name, type, value, options = {}) {
        switch (type) {
            case 'float':
            case 'int':
                return this.renderNumericControl(name, type, value, options);
            case 'bool':
                return this.renderBooleanControl(name, value);
            case 'string':
                return this.renderStringControl(name, value);
            case 'color':
                return this.renderColorControl(name, value);
            case 'enum':
                return this.renderEnumControl(name, value, options.values || []);
            default:
                return this.renderStringControl(name, value);
        }
    }
    
    renderNumericControl(name, type, value, { min, max }) {
        const step = type === 'int' ? '1' : '0.01';
        const minAttr = min !== undefined ? `min="${min}"` : '';
        const maxAttr = max !== undefined ? `max="${max}"` : '';
        
        return `
            <input type="number" 
                   class="parameter-input" 
                   data-param="${name}" 
                   value="${value}" 
                   step="${step}" 
                   ${minAttr} 
                   ${maxAttr} />
            ${min !== undefined && max !== undefined ? this.renderSlider(name, value, min, max) : ''}
        `;
    }
    
    renderSlider(name, value, min, max) {
        const percentage = ((value - min) / (max - min)) * 100;
        
        return `
            <div class="parameter-slider" data-param="${name}" data-min="${min}" data-max="${max}">
                <div class="parameter-slider-track" style="width: ${percentage}%"></div>
                <div class="parameter-slider-thumb" style="left: ${percentage}%"></div>
            </div>
        `;
    }
    
    renderBooleanControl(name, value) {
        return `
            <div class="parameter-checkbox ${value ? 'checked' : ''}" data-param="${name}"></div>
        `;
    }
    
    renderStringControl(name, value) {
        return `
            <input type="text" 
                   class="parameter-input" 
                   data-param="${name}" 
                   value="${value}" />
        `;
    }
    
    renderColorControl(name, value) {
        const [r, g, b] = value || [1, 1, 1];
        const hexColor = this.rgbToHex(r, g, b);
        
        return `
            <div class="parameter-color" data-param="${name}">
                <div class="parameter-color-swatch" style="background-color: ${hexColor}"></div>
            </div>
            <input type="color" 
                   class="parameter-input" 
                   data-param="${name}" 
                   value="${hexColor}" 
                   style="width: 60px;" />
        `;
    }
    
    renderEnumControl(name, value, values) {
        const options = values.map(val => 
            `<option value="${val}" ${val === value ? 'selected' : ''}>${val}</option>`
        ).join('');
        
        return `
            <select class="parameter-dropdown" data-param="${name}">
                ${options}
            </select>
        `;
    }
    
    setupParameterEventListeners() {
        // Parameter inputs
        const inputs = this.element.querySelectorAll('.parameter-input');
        inputs.forEach(input => {
            this.addEventListener(input, 'change', (e) => {
                this.updateParameterValue(e.target.dataset.param, e.target.value);
            });
        });
        
        // Checkboxes
        const checkboxes = this.element.querySelectorAll('.parameter-checkbox');
        checkboxes.forEach(checkbox => {
            this.addEventListener(checkbox, 'click', (e) => {
                const isChecked = !checkbox.classList.contains('checked');
                checkbox.classList.toggle('checked', isChecked);
                this.updateParameterValue(checkbox.dataset.param, isChecked);
            });
        });
        
        // Sliders
        const sliders = this.element.querySelectorAll('.parameter-slider');
        sliders.forEach(slider => {
            this.setupSliderEvents(slider);
        });
        
        // Group toggles
        const groupHeaders = this.element.querySelectorAll('.parameter-group-header');
        groupHeaders.forEach(header => {
            this.addEventListener(header, 'click', (e) => {
                const group = header.parentElement;
                group.classList.toggle('collapsed');
            });
        });
    }
    
    setupSliderEvents(slider) {
        let isDragging = false;
        
        const updateSlider = (e) => {
            const rect = slider.getBoundingClientRect();
            const percentage = Math.max(0, Math.min(1, (e.clientX - rect.left) / rect.width));
            
            const min = parseFloat(slider.dataset.min);
            const max = parseFloat(slider.dataset.max);
            const value = min + (max - min) * percentage;
            
            const track = slider.querySelector('.parameter-slider-track');
            const thumb = slider.querySelector('.parameter-slider-thumb');
            
            track.style.width = `${percentage * 100}%`;
            thumb.style.left = `${percentage * 100}%`;
            
            this.updateParameterValue(slider.dataset.param, value);
        };
        
        this.addEventListener(slider, 'mousedown', (e) => {
            isDragging = true;
            updateSlider(e);
        });
        
        this.addEventListener(document, 'mousemove', (e) => {
            if (isDragging) {
                updateSlider(e);
            }
        });
        
        this.addEventListener(document, 'mouseup', () => {
            isDragging = false;
        });
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
    
    getNodeTypeIcon(type) {
        const icons = {
            'environment': '🌍',
            'material': 'M',
            'texture': 'T',
            'light': 'L',
            'camera': '📷',
            'geometry': 'G',
            'render': 'R'
        };
        return icons[type] || 'N';
    }
    
    rgbToHex(r, g, b) {
        const toHex = (c) => {
            const hex = Math.round(c * 255).toString(16);
            return hex.length === 1 ? '0' + hex : hex;
        };
        return `#${toHex(r)}${toHex(g)}${toHex(b)}`;
    }
    
    updateInspectorDropdown(nodeName) {
        // Update the dropdown in the existing header to show the selected node
        const dropdown = document.querySelector('.node-inspector-panel select');
        if (dropdown && nodeName) {
            // Check if option exists, if not add it
            let optionExists = false;
            for (let option of dropdown.options) {
                if (option.value === nodeName) {
                    option.selected = true;
                    optionExists = true;
                    break;
                }
            }

            // If option doesn't exist, add it and select it
            if (!optionExists) {
                const newOption = document.createElement('option');
                newOption.value = nodeName;
                newOption.textContent = nodeName;
                newOption.selected = true;
                dropdown.appendChild(newOption);
            }
        }
    }

    setupOctaneInspectorEvents() {
        // Setup section toggle functionality
        const sectionHeaders = this.element.querySelectorAll('.section-header');
        sectionHeaders.forEach(header => {
            header.addEventListener('click', () => {
                const section = header.dataset.section;
                const content = this.element.querySelector(`[data-content="${section}"]`);
                const toggle = header.querySelector('.section-toggle');
                
                if (content.style.display === 'none') {
                    content.style.display = 'block';
                    toggle.textContent = '▼';
                } else {
                    content.style.display = 'none';
                    toggle.textContent = '▶';
                }
            });
        });

        // Setup slider synchronization
        const sliders = this.element.querySelectorAll('.param-slider');
        sliders.forEach(slider => {
            const numberInput = slider.parentElement.querySelector('.param-number');
            if (numberInput) {
                slider.addEventListener('input', () => {
                    numberInput.value = slider.value;
                });
                
                numberInput.addEventListener('input', () => {
                    slider.value = numberInput.value;
                });
            }
        });

        // Setup grid button toggles
        const gridButtons = this.element.querySelectorAll('.grid-button');
        gridButtons.forEach(button => {
            button.addEventListener('click', () => {
                button.classList.toggle('active');
            });
        });

        // Setup color picker interactions
        const colorPickers = this.element.querySelectorAll('.param-color-picker');
        colorPickers.forEach(picker => {
            picker.addEventListener('click', () => {
                // In a real implementation, this would open a color picker dialog
                console.log('Color picker clicked');
            });
        });
    }
    
    /**
     * OPTIMIZED: Load and render full parameter tree for selected node
     * Uses cached scene data instead of redundant tree traversal
     */
    async loadAndRenderFullParameterTree(data) {
        console.log('🚀 OPTIMIZED: Loading parameter tree for node:', data.nodeName);
        
        // Show loading state
        this.showLoadingState(data);
        
        try {
            // OPTIMIZATION: Use cached node data if available
            const nodeHandle = this.selectedNodeHandle || this.selectedNode;
            let nodeData = null;
            
            if (this.sceneDataLoaded && nodeHandle) {
                nodeData = this.getCachedNodeData(nodeHandle);
                console.log('✅ OPTIMIZATION: Using cached node data:', nodeData);
            }
            
            // Load only parameter VALUES (not tree structure)
            const parameters = await this.loadNodeParameterValuesOptimized(nodeHandle, nodeData);
            
            console.log('✅ OPTIMIZED: Loaded parameter values:', parameters);
            
            // Render the full inspector with all parameters
            this.renderFullParameterInspector(data, parameters);
            
        } catch (error) {
            console.error('❌ Failed to load parameter tree:', error);
            
            // Fallback to original method if optimization fails
            console.log('🔄 Falling back to full tree traversal...');
            try {
                const parameters = await this.loadNodeParametersRecursively(
                    this.selectedNodeHandle || this.selectedNode, 
                    3 // max depth
                );
                this.renderFullParameterInspector(data, parameters);
            } catch (fallbackError) {
                console.error('❌ Fallback also failed:', fallbackError);
                this.showErrorState(data, fallbackError);
            }
        }
    }
    
    /**
     * OPTIMIZED: Load only parameter VALUES for a node (using cached metadata)
     * This replaces the inefficient recursive tree traversal
     */
    async loadNodeParameterValuesOptimized(nodeHandle, cachedNodeData) {
        if (!nodeHandle) {
            console.warn('⚠️ OPTIMIZATION: No node handle provided');
            return {};
        }
        
        const parameters = {};
        
        try {
            console.log(`🚀 OPTIMIZATION: Loading parameter values for node ${nodeHandle} (${cachedNodeData?.name || 'unknown'})`);
            
            // Get pin count for this node (single API call)
            const pinCountResult = window.grpcApi.makeApiCallSync(
                'ApiNode/pinCount',
                nodeHandle
            );
            
            if (!pinCountResult.success) {
                console.warn('⚠️ OPTIMIZATION: Failed to get pin count for node:', nodeHandle);
                return parameters;
            }
            
            const pinCount = pinCountResult.data.result;
            console.log(`📌 OPTIMIZATION: Node has ${pinCount} pins (cached metadata: ${cachedNodeData ? 'available' : 'not available'})`);
            
            // Load parameter values efficiently (no tree traversal)
            for (let i = 0; i < pinCount; i++) {
                try {
                    // Small delay to prevent API overload
//                    await this.delay(25); // Reduced from 50ms for better performance
                    
                    // Use SAFE ApiNode methods to get pin information
                    const [pinNameResult, pinTypeResult, pinLabelResult] = await Promise.all([
                        window.grpcApi.makeApiCallSync('ApiNode/pinNameIx', nodeHandle, { index: i }),
                        window.grpcApi.makeApiCallSync('ApiNode/pinTypeIx', nodeHandle, { index: i }),
                        window.grpcApi.makeApiCallSync('ApiNode/pinLabelIx', nodeHandle, { index: i })
                    ]);
                    
                    // Skip if we can't get basic pin info
                    if (!pinNameResult.success && !pinTypeResult.success) {
                        continue;
                    }
                    
                    const pinName = pinNameResult.success ? pinNameResult.data.result : `pin_${i}`;
                    const pinType = pinTypeResult.success ? pinTypeResult.data.result : 'unknown';
                    const pinLabel = pinLabelResult.success ? pinLabelResult.data.result : pinName;
                    
                    // Get pin value using safe methods
                    let pinValue = null;
                    try {
                        const valueResult = await this.getParameterValueSafe(nodeHandle, i, pinType);
                        if (valueResult.success) {
                            pinValue = valueResult.data;
                        }
                    } catch (valueError) {
                        console.warn(`⚠️ OPTIMIZATION: Could not get value for pin ${i}:`, valueError);
                    }
                    
                    // Store parameter data
                    parameters[pinName] = {
                        name: pinName,
                        label: pinLabel,
                        type: pinType,
                        value: pinValue,
                        index: i,
                        // Use cached metadata if available
                        nodeType: cachedNodeData?.outtype || 'unknown',
                        nodeName: cachedNodeData?.name || 'unknown'
                    };
                    
                } catch (pinError) {
                    console.warn(`⚠️ OPTIMIZATION: Error processing pin ${i}:`, pinError);
                    continue;
                }
            }
            
            console.log(`✅ OPTIMIZATION: Loaded ${Object.keys(parameters).length} parameter values efficiently`);
            
        } catch (error) {
            console.error('❌ OPTIMIZATION: Error in loadNodeParameterValuesOptimized:', error);
        }
        
        return parameters;
    }
    
    /**
     * Recursively load all parameters for a node (FALLBACK METHOD)
     */
    async loadNodeParametersRecursively(nodeHandle, maxDepth = 3, currentDepth = 0) {
        if (currentDepth >= maxDepth || !nodeHandle) {
            return {};
        }
        
        const parameters = {};
        
        try {
            console.log(`🔍 Loading parameters for node handle ${nodeHandle} (depth ${currentDepth})`);
            
            // Get pin count for this node
            const pinCountResult = window.grpcApi.makeApiCallSync(
                'ApiNode/pinCount',
                nodeHandle
            );
            
            if (!pinCountResult.success) {
                console.warn('⚠️ Failed to get pin count for node:', nodeHandle);
                return parameters;
            }
            
            const pinCount = pinCountResult.data.result;
            console.log(`📌 Node has ${pinCount} pins`);
            
            // Iterate through all pins
            for (let i = 0; i < pinCount; i++) {
                try {
                    // Add small delay to prevent overwhelming the API
//                    await this.delay(50);
                    
                    // Use SAFE ApiNode methods to get pin information (avoiding problematic ApiNodePinInfoEx)
                    const pinNameResult = window.grpcApi.makeApiCallSync(
                        'ApiNode/pinNameIx',
                        nodeHandle,
                        { index: i }
                    );
                    
                    const pinTypeResult = window.grpcApi.makeApiCallSync(
                        'ApiNode/pinTypeIx',
                        nodeHandle,
                        { index: i }
                    );
                    
                    const pinLabelResult = window.grpcApi.makeApiCallSync(
                        'ApiNode/pinLabelIx',
                        nodeHandle,
                        { index: i }
                    );
                    
                    // Skip if we can't get basic pin info
                    if (!pinNameResult.success && !pinTypeResult.success) {
                        continue;
                    }
                    
                    const pinName = pinNameResult.success ? pinNameResult.data.result : `pin_${i}`;
                    const pinType = pinTypeResult.success ? pinTypeResult.data.result : 'unknown';
                    const pinLabel = pinLabelResult.success ? pinLabelResult.data.result : pinName;
                    
                    // Try to get pin value using safe methods
                    let pinValue = null;
                    try {
                        const valueResult = window.grpcApi.makeApiCallSync(
                            'ApiNode/getPinValueIx',
                            nodeHandle,
                            { index: i }
                        );
                        if (valueResult.success) {
                            pinValue = valueResult.data.result;
                        }
                    } catch (valueError) {
                        console.warn(`⚠️ Could not get value for pin ${i}:`, valueError);
                    }
                    
                    // Extract parameter information using safe data
                    const paramName = pinLabel || pinName || `Parameter ${i}`;
                    
                    parameters[paramName] = {
                        name: paramName,
                        type: pinType || 'unknown',
                        value: pinValue,
                        index: i,
                        pinName: pinName,
                        pinLabel: pinLabel,
                        pinType: pinType
                    };
                    
                    console.log(`✅ Loaded parameter: ${paramName} (${pinType}) = ${pinValue}`);
                    
                    // Also check for connected nodes (for nested parameters)
                    const connectedNodeResult = window.grpcApi.makeApiCallSync(
                        'ApiNode/connectedNodeIx',
                        nodeHandle,
                        { pinIx: i, enterWrapperNode: true }
                    );
                    
                    if (connectedNodeResult.success && connectedNodeResult.data.result) {
                        const connectedNode = connectedNodeResult.data.result;
                        
                        if (connectedNode.handle && connectedNode.handle !== nodeHandle) {
                            // Recursively load parameters from connected node
                            const nestedParams = await this.loadNodeParametersRecursively(
                                connectedNode.handle,
                                maxDepth,
                                currentDepth + 1
                            );
                            
                            // Merge nested parameters with a prefix
                            Object.keys(nestedParams).forEach(nestedParamName => {
                                const prefixedName = `${paramName || 'Connected'}.${nestedParamName}`;
                                parameters[prefixedName] = nestedParams[nestedParamName];
                            });
                        }
                    }
                    
                } catch (pinError) {
                    console.warn(`⚠️ Error loading pin ${i}:`, pinError);
                    continue;
                }
            }
            
        } catch (error) {
            console.error('❌ Error in loadNodeParametersRecursively:', error);
        }
        
        return parameters;
    }
    
    /**
     * Safely get parameter value using available ApiNode methods
     */
    async getParameterValueSafe(nodeHandle, index, pinType) {
        try {
            // Try different value getter methods based on type
            const methods = [
                'ApiNode/getPinValueIx',
            ];
            
            for (const method of methods) {
                try {
                    const result = window.grpcApi.makeApiCallSync(method, nodeHandle, { index });
                    if (result.success && result.data.result !== undefined) {
                        return { success: true, data: result.data.result };
                    }
                } catch (error) {
                    // Try next method
                    continue;
                }
            }
            
            return { success: false, error: 'No suitable value getter method found' };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }
    
    /**
     * Safely set parameter value using available ApiNode methods
     */
    async setParameterValueSafe(nodeHandle, index, value, pinType) {
        try {
            const result = window.grpcApi.makeApiCallSync('ApiNode/setPinValue', nodeHandle, {
                index: index,
                value: value
            });
            
            return { success: result.success, data: result.data };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }
    
    /**
     * Handle parameter value changes with safe API calls
     */
    async handleParameterChange(element) {
        if (!this.selectedNodeHandle || !element.dataset.index) {
            return;
        }
        
        const index = parseInt(element.dataset.index);
        const newValue = this.getElementValue(element);
        
        console.log(`🔄 Updating parameter at pin ${index} to:`, newValue);
        
        try {
            const result = await this.setParameterValueSafe(this.selectedNodeHandle, index, newValue);
            if (result.success) {
                console.log(`✅ Parameter updated successfully`);
                // Update UI to reflect change
                this.updateParameterDisplay(element, newValue);
            } else {
                console.error(`❌ Failed to update parameter:`, result.error);
            }
        } catch (error) {
            console.error(`❌ Error updating parameter:`, error);
        }
    }
    
    /**
     * Get value from UI element based on its type
     */
    getElementValue(element) {
        if (element.type === 'checkbox') {
            return element.checked;
        } else if (element.type === 'number' || element.type === 'range') {
            return parseFloat(element.value);
        } else if (element.tagName === 'SELECT') {
            return element.value;
        } else {
            return element.value;
        }
    }
    
    /**
     * Update parameter display after successful change
     */
    updateParameterDisplay(element, newValue) {
        // Update any associated display elements
        const displayElement = element.parentElement.querySelector('.parameter-value-display');
        if (displayElement) {
            displayElement.textContent = newValue;
        }
    }
    
    /**
     * Render full parameter inspector with all loaded parameters
     */
    renderFullParameterInspector(data, parameters) {
        // Import parameter renderer (will be loaded dynamically)
        this.loadParameterRenderer().then(() => {
            this.doRenderFullParameterInspector(data, parameters);
        });
    }
    
    async loadParameterRenderer() {
        if (!window.ParameterRenderer) {
            // For now, we'll implement a basic version inline
            // In production, this would import the ParameterRenderer module
            console.log('📦 Loading parameter renderer...');
        }
    }
    
    doRenderFullParameterInspector(data, parameters) {
        const parameterCount = Object.keys(parameters).length;
        
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
                    <div class="parameter-row">
                        <span class="parameter-icon">🔢</span>
                        <span class="parameter-label">Parameters:</span>
                        <span class="parameter-value">${parameterCount} found</span>
                    </div>
                </div>
                
                ${this.renderParameterGroups(parameters)}
            </div>
        `;
        
        this.setupParameterHandlers();
        this.setupParameterEventListeners();
    }
    
    /**
     * Render parameters organized into collapsible groups
     */
    renderParameterGroups(parameters) {
        const groups = this.organizeParametersIntoGroups(parameters);
        let html = '';
        
        Object.keys(groups).forEach(groupName => {
            const group = groups[groupName];
            const isCollapsed = this.collapsedGroups.has(groupName);
            
            html += `
                <div class="parameter-group">
                    <div class="parameter-group-header ${isCollapsed ? 'collapsed' : ''}" 
                         data-group="${groupName}">
                        <span class="parameter-group-icon">${isCollapsed ? '▶' : '▼'}</span>
                        <span class="parameter-group-title">${group.title}</span>
                        <span class="parameter-group-count">(${group.parameters.length})</span>
                    </div>
                    <div class="parameter-group-content" 
                         data-group-content="${groupName}"
                         style="display: ${isCollapsed ? 'none' : 'block'}">
                        ${this.renderParametersInGroup(group.parameters)}
                    </div>
                </div>
            `;
        });
        
        return html;
    }
    
    /**
     * Organize parameters into logical groups
     */
    organizeParametersIntoGroups(parameters) {
        const groups = {
            'camera': { title: 'Camera', parameters: [] },
            'physical-camera': { title: 'Physical camera parameters', parameters: [] },
            'viewing-angle': { title: 'Viewing angle', parameters: [] },
            'clipping': { title: 'Clipping', parameters: [] },
            'depth-of-field': { title: 'Depth of field', parameters: [] },
            'transform': { title: 'Transform', parameters: [] },
            'material': { title: 'Material', parameters: [] },
            'lighting': { title: 'Lighting', parameters: [] },
            'general': { title: 'General', parameters: [] }
        };
        
        // Group parameters based on their names
        Object.keys(parameters).forEach(paramName => {
            const param = parameters[paramName];
            const lowerName = paramName.toLowerCase();
            
            let assigned = false;
            
            // Camera parameters
            if (lowerName.includes('orthographic') || lowerName.includes('camera type')) {
                groups['camera'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Physical camera parameters
            else if (lowerName.includes('sensor') || lowerName.includes('focal') || lowerName.includes('f-stop')) {
                groups['physical-camera'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Viewing angle parameters
            else if (lowerName.includes('field of view') || lowerName.includes('scale of view') || 
                     lowerName.includes('distortion') || lowerName.includes('lens shift')) {
                groups['viewing-angle'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Clipping parameters
            else if (lowerName.includes('clip') || lowerName.includes('near') || lowerName.includes('far')) {
                groups['clipping'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Depth of field parameters
            else if (lowerName.includes('focus') || lowerName.includes('aperture') || lowerName.includes('bokeh')) {
                groups['depth-of-field'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Transform parameters
            else if (lowerName.includes('position') || lowerName.includes('rotation') || lowerName.includes('scale')) {
                groups['transform'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Material parameters
            else if (lowerName.includes('diffuse') || lowerName.includes('specular') || 
                     lowerName.includes('roughness') || lowerName.includes('metallic') || lowerName.includes('opacity')) {
                groups['material'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Lighting parameters
            else if (lowerName.includes('intensity') || lowerName.includes('power') || 
                     lowerName.includes('temperature') || lowerName.includes('color')) {
                groups['lighting'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            
            // Default to general group
            if (!assigned) {
                groups['general'].parameters.push({ name: paramName, ...param });
            }
        });
        
        // Remove empty groups
        Object.keys(groups).forEach(groupName => {
            if (groups[groupName].parameters.length === 0) {
                delete groups[groupName];
            }
        });
        
        return groups;
    }
    
    /**
     * Render parameters within a group
     */
    renderParametersInGroup(parameters) {
        let html = '';
        
        parameters.forEach(param => {
            html += this.renderSingleParameter(param);
        });
        
        return html;
    }
    
    /**
     * Render a single parameter with appropriate UI control
     */
    renderSingleParameter(param) {
        const paramType = this.detectParameterType(param);
        const icon = this.getParameterIcon(param.name, paramType);
        
        let controlHtml = '';
        
        switch (paramType) {
            case 'checkbox':
                controlHtml = this.renderCheckboxControl(param);
                break;
            case 'numeric-slider':
                controlHtml = this.renderNumericSliderControl(param);
                break;
            case 'numeric-input':
                controlHtml = this.renderNumericInputControl(param);
                break;
            case 'dropdown':
                controlHtml = this.renderDropdownControl(param);
                break;
            case 'color-picker':
                controlHtml = this.renderColorPickerControl(param);
                break;
            default:
                controlHtml = this.renderTextInputControl(param);
                break;
        }
        
        return `
            <div class="parameter-row" data-param="${param.name}" data-type="${paramType}">
                <div class="parameter-label">
                    <span class="parameter-icon">${icon}</span>
                    <span class="parameter-name">${param.name}</span>
                </div>
                <div class="parameter-control">
                    ${controlHtml}
                </div>
            </div>
        `;
    }
    
    // Parameter control rendering methods
    renderCheckboxControl(param) {
        const checked = param.value === true || param.value === 'true';
        return `
            <label class="parameter-checkbox-container">
                <input type="checkbox" 
                       class="parameter-checkbox" 
                       id="param-${param.name}"
                       ${checked ? 'checked' : ''}
                       data-param="${param.name}">
                <span class="parameter-checkbox-custom"></span>
            </label>
        `;
    }
    
    renderNumericSliderControl(param) {
        const value = param.value || 0;
        const min = param.min !== undefined ? param.min : 0;
        const max = param.max !== undefined ? param.max : 100;
        const step = param.step || 0.01;
        
        return `
            <div class="parameter-numeric-slider-container">
                <input type="range" 
                       class="parameter-slider" 
                       id="slider-${param.name}"
                       min="${min}" 
                       max="${max}" 
                       step="${step}" 
                       value="${value}"
                       data-param="${param.name}">
                <input type="number" 
                       class="parameter-number-input" 
                       id="input-${param.name}"
                       min="${min}" 
                       max="${max}" 
                       step="${step}" 
                       value="${value}"
                       data-param="${param.name}">
                <div class="parameter-controls">
                    <button class="param-increment" data-param="${param.name}" data-step="${step}">▲</button>
                    <button class="param-decrement" data-param="${param.name}" data-step="${step}">▼</button>
                </div>
            </div>
        `;
    }
    
    renderNumericInputControl(param) {
        const value = param.value || 0;
        const step = param.step || 1;
        
        return `
            <div class="parameter-numeric-input-container">
                <input type="number" 
                       class="parameter-number-input" 
                       id="input-${param.name}"
                       step="${step}" 
                       value="${value}"
                       data-param="${param.name}">
                <div class="parameter-controls">
                    <button class="param-increment" data-param="${param.name}" data-step="${step}">▲</button>
                    <button class="param-decrement" data-param="${param.name}" data-step="${step}">▼</button>
                </div>
            </div>
        `;
    }
    
    renderDropdownControl(param) {
        const options = param.options || [];
        const value = param.value || '';
        
        let optionsHtml = '';
        options.forEach(option => {
            const optionValue = typeof option === 'object' ? option.value : option;
            const optionLabel = typeof option === 'object' ? option.label : option;
            const selected = optionValue === value ? 'selected' : '';
            optionsHtml += `<option value="${optionValue}" ${selected}>${optionLabel}</option>`;
        });
        
        return `
            <select class="parameter-dropdown" 
                    id="dropdown-${param.name}"
                    data-param="${param.name}">
                ${optionsHtml}
            </select>
        `;
    }
    
    renderColorPickerControl(param) {
        const value = param.value || '#ffffff';
        const hexValue = this.colorToHex(value);
        
        return `
            <div class="parameter-color-container">
                <div class="parameter-color-preview" style="background-color: ${hexValue}"></div>
                <input type="color" 
                       class="parameter-color-picker" 
                       id="color-${param.name}"
                       value="${hexValue}"
                       data-param="${param.name}">
                <input type="text" 
                       class="parameter-color-hex" 
                       id="hex-${param.name}"
                       value="${hexValue}"
                       data-param="${param.name}"
                       maxlength="7">
            </div>
        `;
    }
    
    renderTextInputControl(param) {
        const value = param.value || '';
        
        return `
            <input type="text" 
                   class="parameter-text-input" 
                   id="text-${param.name}"
                   value="${value}"
                   data-param="${param.name}">
        `;
    }
    
    // Utility methods
    detectParameterType(param) {
        if (param.type) {
            const type = param.type.toUpperCase();
            if (type.includes('BOOL')) return 'checkbox';
            if (type.includes('FLOAT') || type.includes('DOUBLE')) {
                return param.min !== undefined && param.max !== undefined ? 'numeric-slider' : 'numeric-input';
            }
            if (type.includes('INT')) return 'numeric-input';
            if (type.includes('ENUM') || type.includes('CHOICE')) return 'dropdown';
            if (type.includes('COLOR')) return 'color-picker';
        }
        
        // Infer from value
        if (typeof param.value === 'boolean') return 'checkbox';
        if (typeof param.value === 'number') {
            return param.min !== undefined && param.max !== undefined ? 'numeric-slider' : 'numeric-input';
        }
        
        // Check for options
        if (param.options && Array.isArray(param.options)) return 'dropdown';
        
        // Check name patterns
        const lowerName = param.name.toLowerCase();
        if (lowerName.includes('color')) return 'color-picker';
        if (lowerName.includes('enable') || lowerName.includes('orthographic')) return 'checkbox';
        
        return 'text-input';
    }
    
    getParameterIcon(paramName, paramType) {
        const icons = {
            'Orthographic': '📐',
            'Sensor width': '📏',
            'Focal length': '🔍',
            'F-stop': '📷',
            'Field of view': '👁️',
            'Scale of view': '🔍',
            'Distortion': '🌀',
            'Lens shift': '↔️',
            'Near clip depth': '✂️',
            'Far clip depth': '✂️',
            'Auto-focus': '🎯',
            'Focal depth': '📏',
            'Aperture': '⭕'
        };
        
        return icons[paramName] || this.getTypeIcon(paramType);
    }
    
    getTypeIcon(paramType) {
        const typeIcons = {
            'checkbox': '☑️',
            'numeric-slider': '🎚️',
            'numeric-input': '🔢',
            'dropdown': '📋',
            'color-picker': '🎨',
            'text-input': '📝'
        };
        
        return typeIcons[paramType] || '⚙️';
    }
    
    colorToHex(color) {
        if (typeof color === 'string' && color.startsWith('#')) {
            return color;
        }
        
        if (Array.isArray(color)) {
            const r = Math.round(color[0] * 255);
            const g = Math.round(color[1] * 255);
            const b = Math.round(color[2] * 255);
            return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
        }
        
        return '#ffffff';
    }
    
    /**
     * Setup event listeners for all parameter controls
     */
    setupParameterEventListeners() {
        // Numeric slider controls
        this.element.querySelectorAll('.parameter-slider').forEach(slider => {
            slider.addEventListener('input', (e) => {
                const paramName = e.target.dataset.param;
                const value = parseFloat(e.target.value);
                const input = this.element.querySelector(`#input-${paramName}`);
                if (input) input.value = value;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Numeric input controls
        this.element.querySelectorAll('.parameter-number-input').forEach(input => {
            input.addEventListener('input', (e) => {
                const paramName = e.target.dataset.param;
                const value = parseFloat(e.target.value);
                const slider = this.element.querySelector(`#slider-${paramName}`);
                if (slider) slider.value = value;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Increment/decrement buttons
        this.element.querySelectorAll('.param-increment').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const paramName = e.target.dataset.param;
                const step = parseFloat(e.target.dataset.step);
                const input = this.element.querySelector(`#input-${paramName}`);
                if (input) {
                    const newValue = parseFloat(input.value) + step;
                    input.value = newValue;
                    const slider = this.element.querySelector(`#slider-${paramName}`);
                    if (slider) slider.value = newValue;
                    this.handleParameterChange(paramName, newValue);
                }
            });
        });
        
        this.element.querySelectorAll('.param-decrement').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const paramName = e.target.dataset.param;
                const step = parseFloat(e.target.dataset.step);
                const input = this.element.querySelector(`#input-${paramName}`);
                if (input) {
                    const newValue = parseFloat(input.value) - step;
                    input.value = newValue;
                    const slider = this.element.querySelector(`#slider-${paramName}`);
                    if (slider) slider.value = newValue;
                    this.handleParameterChange(paramName, newValue);
                }
            });
        });
        
        // Checkbox controls
        this.element.querySelectorAll('.parameter-checkbox').forEach(checkbox => {
            checkbox.addEventListener('change', (e) => {
                const paramName = e.target.dataset.param;
                const value = e.target.checked;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Dropdown controls
        this.element.querySelectorAll('.parameter-dropdown').forEach(dropdown => {
            dropdown.addEventListener('change', (e) => {
                const paramName = e.target.dataset.param;
                const value = e.target.value;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Color picker controls
        this.element.querySelectorAll('.parameter-color-picker').forEach(picker => {
            picker.addEventListener('input', (e) => {
                const paramName = e.target.dataset.param;
                const value = e.target.value;
                const hexInput = this.element.querySelector(`#hex-${paramName}`);
                const preview = this.element.querySelector(`#color-${paramName}`).parentElement.querySelector('.parameter-color-preview');
                if (hexInput) hexInput.value = value;
                if (preview) preview.style.backgroundColor = value;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Text input controls
        this.element.querySelectorAll('.parameter-text-input').forEach(input => {
            input.addEventListener('input', (e) => {
                const paramName = e.target.dataset.param;
                const value = e.target.value;
                this.handleParameterChange(paramName, value);
            });
        });
    }
    
    /**
     * Handle parameter value changes
     */
    handleParameterChange(paramName, value) {
        console.log(`🔄 Parameter changed: ${paramName} = ${value}`);
        
        // Store the parameter value
        this.parameters[paramName] = value;
        
        // Send update to Octane if we have a selected node
        if (this.selectedNodeHandle) {
            this.updateOctaneParameter(paramName, value);
        }
        
        // Emit parameter change event for other components
        this.eventSystem.emit('parameterChanged', {
            nodeId: this.selectedNode,
            paramName: paramName,
            value: value
        });
    }
    
    /**
     * Update parameter in Octane
     */
    async updateOctaneParameter(paramName, value) {
        try {
            // This would send the parameter update to Octane
            // Implementation depends on the specific API for parameter updates
            console.log(`📤 Sending parameter update to Octane: ${paramName} = ${value}`);
            
            // For now, just log the update
            // In a real implementation, this would call the appropriate gRPC method
            
        } catch (error) {
            console.error('❌ Failed to update Octane parameter:', error);
        }
    }
    
    /**
     * Show loading state while parameters are being loaded
     */
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
     * Show error state if parameter loading fails
     */
    showErrorState(data, error) {
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
                
                <div class="error-state">
                    <div class="error-icon">❌</div>
                    <p>Failed to load parameters</p>
                    <details>
                        <summary>Error details</summary>
                        <pre>${error.message || error}</pre>
                    </details>
                    <button class="retry-button" onclick="this.parentElement.parentElement.parentElement.parentElement.querySelector('.node-selector select').dispatchEvent(new Event('change'))">
                        🔄 Retry
                    </button>
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
    
    renderGenericInspector(data) {
        // This method is now replaced by loadAndRenderFullParameterTree
        // Keep for backward compatibility
        this.loadAndRenderFullParameterTree(data);
    }
    
    setupParameterHandlers() {
        // Setup handlers for parameter groups
        const groupHeaders = this.element.querySelectorAll('.parameter-group-header');
        groupHeaders.forEach(header => {
            header.addEventListener('click', (e) => {
                const groupName = header.dataset.group;
                this.toggleParameterGroup(groupName);
            });
        });
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspector;
} else if (typeof window !== 'undefined') {
    window.NodeInspector = NodeInspector;
}