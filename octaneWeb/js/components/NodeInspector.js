/**
 * Node Inspector Component
 * Parameter controls for selected nodes
 */

class NodeInspector extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        this.selectedNode = null;
        this.parameters = {};
    }
    
    async onInitialize() {
        this.render();
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
    }
    
    render() {
        this.element.innerHTML = `
            <div class="inspector-loading">Select a node to inspect...</div>
        `;
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
        this.element.innerHTML = `
            <div class="inspector-loading">Select a node to inspect...</div>
        `;
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