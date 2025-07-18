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
    }
    
    async onInitialize() {
        this.renderDefaultInspector();
    }
    
    setupEventListeners() {
        // Listen for selection updates
        this.client.on('ui:selectionUpdate', (selection) => {
            this.updateSelection(selection);
        });
        
        // Listen for node parameter updates
        this.client.on('ui:nodeParameterUpdate', (data) => {
            this.updateParameter(data.nodeId, data.parameterName, data.value);
        });
        
        // Force click events to work by bypassing CSS pointer-events issues
        this.setupForceClickHandlers();
    }
    
    setupForceClickHandlers() {
        // Use a more aggressive approach - intercept ALL clicks and check coordinates
        document.addEventListener('click', (event) => {
            console.log('Click detected at:', event.clientX, event.clientY, 'on:', event.target, 'bid:', event.target.getAttribute('bid'));
            
            // Get the element at the click coordinates, ignoring pointer-events
            const elementAtPoint = document.elementFromPoint(event.clientX, event.clientY);
            console.log('Element at point:', elementAtPoint, 'bid:', elementAtPoint?.getAttribute('bid'));
            
            // Check if the click coordinates are within the right panel bounds
            const rightPanel = document.querySelector('.right-panel');
            if (rightPanel) {
                const rect = rightPanel.getBoundingClientRect();
                const isInRightPanel = event.clientX >= rect.left && event.clientX <= rect.right && 
                                     event.clientY >= rect.top && event.clientY <= rect.bottom;
                
                if (isInRightPanel) {
                    console.log('Click is within right panel bounds');
                    event.stopPropagation();
                    event.preventDefault();
                    
                    // Find all elements at this point and look for our target
                    const allElements = document.elementsFromPoint(event.clientX, event.clientY);
                    console.log('All elements at point:', allElements.map(el => el.tagName + (el.getAttribute('bid') ? `[${el.getAttribute('bid')}]` : '') + (el.className ? `.${el.className}` : '')));
                    
                    // Find the first element that matches our target criteria
                    const target = allElements.find(el => 
                        el.hasAttribute('data-group') || 
                        el.classList.contains('parameter-checkbox') ||
                        el.classList.contains('parameter-dropdown') ||
                        el.classList.contains('parameter-input') ||
                        el.classList.contains('parameter-slider')
                    );
                    
                    if (target) {
                        console.log('Found target element:', target);
                        this.handleParameterClick(target, event);
                    } else {
                        console.log('No target element found in stack');
                    }
                }
            }
        }, true); // Use capture phase to intercept before other handlers
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
    
    renderDefaultInspector() {
        this.element.innerHTML = `
            <div class="node-inspector-header">
                <div class="inspector-title">Node inspector</div>
                <div class="inspector-dropdown">
                    <select class="inspector-target-select">
                        <option>Render target</option>
                        <option>Camera target</option>
                        <option>Material target</option>
                    </select>
                    <div class="inspector-dropdown-arrow">▼</div>
                </div>
            </div>
            
            <div class="inspector-content">
                <div class="parameter-section">
                    <div class="parameter-section-header">
                        <div class="parameter-section-icon">▼</div>
                        <div class="parameter-section-title">Scene</div>
                    </div>
                    
                    <div class="parameter-subsection">
                        <div class="parameter-subsection-header">
                            <div class="parameter-subsection-icon">📷</div>
                            <div class="parameter-subsection-title">Camera</div>
                            <div class="parameter-subsection-dropdown">
                                <select class="parameter-dropdown">
                                    <option>Thin lens camera</option>
                                    <option>Panoramic camera</option>
                                    <option>Orthographic camera</option>
                                </select>
                            </div>
                        </div>
                        
                        <div class="parameter-group">
                            <div class="parameter-group-header">
                                <div class="parameter-group-icon">📐</div>
                                <div class="parameter-group-title">Orthographic:</div>
                                <div class="parameter-group-checkbox">
                                    <input type="checkbox" id="orthographic" class="parameter-checkbox">
                                    <label for="orthographic" class="checkbox-label"></label>
                                </div>
                            </div>
                        </div>
                        
                        <div class="parameter-group">
                            <div class="parameter-group-header collapsed" data-group="physical-camera">
                                <div class="parameter-group-icon">▼</div>
                                <div class="parameter-group-title">Physical camera parameters</div>
                            </div>
                            <div class="parameter-group-content" data-group-content="physical-camera">
                                ${this.renderPhysicalCameraParameters()}
                            </div>
                        </div>
                        
                        <div class="parameter-group">
                            <div class="parameter-group-header collapsed" data-group="viewing-angle">
                                <div class="parameter-group-icon">▼</div>
                                <div class="parameter-group-title">Viewing angle</div>
                            </div>
                            <div class="parameter-group-content" data-group-content="viewing-angle">
                                ${this.renderViewingAngleParameters()}
                            </div>
                        </div>
                        
                        <div class="parameter-group">
                            <div class="parameter-group-header">
                                <div class="parameter-group-icon">📐</div>
                                <div class="parameter-group-title">Perspective correction:</div>
                                <div class="parameter-group-checkbox">
                                    <input type="checkbox" id="perspective-correction" class="parameter-checkbox">
                                    <label for="perspective-correction" class="checkbox-label"></label>
                                </div>
                            </div>
                        </div>
                        
                        <div class="parameter-group">
                            <div class="parameter-group-header">
                                <div class="parameter-group-icon">📏</div>
                                <div class="parameter-group-title">Pixel aspect ratio:</div>
                                <div class="parameter-input-container">
                                    <input type="number" class="parameter-number-input" value="1.000" step="0.001">
                                    <div class="parameter-slider-container">
                                        <div class="parameter-slider">
                                            <div class="parameter-slider-track"></div>
                                            <div class="parameter-slider-thumb"></div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                        
                        <div class="parameter-group">
                            <div class="parameter-group-header collapsed" data-group="clipping">
                                <div class="parameter-group-icon">▼</div>
                                <div class="parameter-group-title">Clipping</div>
                            </div>
                            <div class="parameter-group-content" data-group-content="clipping">
                                ${this.renderClippingParameters()}
                            </div>
                        </div>
                        
                        <div class="parameter-group">
                            <div class="parameter-group-header collapsed" data-group="depth-of-field">
                                <div class="parameter-group-icon">▼</div>
                                <div class="parameter-group-title">Depth of field</div>
                            </div>
                            <div class="parameter-group-content" data-group-content="depth-of-field">
                                ${this.renderDepthOfFieldParameters()}
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        `;
        
        this.setupInspectorEventListeners();
    }
    
    renderPhysicalCameraParameters() {
        return `
            <div class="parameter-row">
                <div class="parameter-label">Sensor width:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="36.000" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Focal length:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="50.000" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">F-stop:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="2.8" step="0.1">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }
    
    renderViewingAngleParameters() {
        return `
            <div class="parameter-row">
                <div class="parameter-label">Field of view:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="39.597752" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Scale of view:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="17.144243" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Distortion:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="0.000" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Lens shift:</div>
                <div class="parameter-input-container dual-input">
                    <input type="number" class="parameter-number-input" value="0.000" step="0.001">
                    <input type="number" class="parameter-number-input" value="0.000" step="0.001">
                </div>
            </div>
        `;
    }
    
    renderClippingParameters() {
        return `
            <div class="parameter-row">
                <div class="parameter-label">Near clip depth:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="0.000" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Far clip depth:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="∞" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }
    
    renderDepthOfFieldParameters() {
        return `
            <div class="parameter-group">
                <div class="parameter-group-header">
                    <div class="parameter-group-icon">🎯</div>
                    <div class="parameter-group-title">Auto-focus:</div>
                    <div class="parameter-group-checkbox">
                        <input type="checkbox" id="auto-focus" class="parameter-checkbox" checked>
                        <label for="auto-focus" class="checkbox-label"></label>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Focal depth:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="1.118034" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Aperture:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="0.8928572" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Aperture aspect ratio:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="1.000" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Aperture edge:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="1.000" step="0.001">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameter-row">
                <div class="parameter-label">Bokeh side count:</div>
                <div class="parameter-input-container">
                    <input type="number" class="parameter-number-input" value="6" step="1">
                    <div class="parameter-slider-container">
                        <div class="parameter-slider">
                            <div class="parameter-slider-track"></div>
                            <div class="parameter-slider-thumb"></div>
                        </div>
                    </div>
                </div>
            </div>
        `;
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
        this.renderDefaultInspector();
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
            'material': 'M',
            'texture': 'T',
            'light': 'L',
            'camera': 'C',
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
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspector;
} else if (typeof window !== 'undefined') {
    window.NodeInspector = NodeInspector;
}