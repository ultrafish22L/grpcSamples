/**
 * Octane Parameter Renderer - Professional UI controls matching Octane Studio exactly
 * Generates HTML for different parameter types with Octane-style controls
 */

class OctaneParameterRenderer {
    constructor() {
        this.controlId = 0;
    }
    
    /**
     * Generate unique control ID
     */
    getNextId() {
        return `param_${++this.controlId}`;
    }
    
    /**
     * Render parameter groups in Octane Studio style
     */
    renderParameterGroups(nodeType, parameters) {
        if (!window.OctaneParameterGroups) {
            console.warn('OctaneParameterGroups not loaded');
            return this.renderFallbackParameters(parameters);
        }
        
        const groups = window.OctaneParameterGroups.getParameterGroupsForNodeType(nodeType);
        let html = '';
        
        // Sort groups by order
        const sortedGroups = Object.entries(groups).sort((a, b) => a[1].order - b[1].order);
        
        for (const [groupName, groupConfig] of sortedGroups) {
            html += this.renderParameterGroup(groupName, groupConfig, parameters);
        }
        
        return html;
    }
    
    /**
     * Render a single parameter group with Octane styling
     */
    renderParameterGroup(groupName, groupConfig, actualParameters) {
        const isExpanded = groupConfig.expanded !== false;
        const expandIcon = isExpanded ? '▼' : '▶';
        
        let groupHtml = `
            <div class="octane-parameter-group">
                <div class="octane-group-header ${isExpanded ? 'expanded' : 'collapsed'}" 
                     data-group="${groupName}">
                    <span class="octane-group-icon">${expandIcon}</span>
                    <span class="octane-group-title">${groupName}</span>
                </div>
                <div class="octane-group-content" data-group-content="${groupName}" 
                     style="display: ${isExpanded ? 'block' : 'none'}">
        `;
        
        // Render parameters in this group
        for (const paramDef of groupConfig.parameters) {
            const actualParam = this.findActualParameter(actualParameters, paramDef.pinName);
            groupHtml += this.renderOctaneParameter(paramDef, actualParam);
        }
        
        groupHtml += `
                </div>
            </div>
        `;
        
        return groupHtml;
    }
    
    /**
     * Find actual parameter data by pin name
     */
    findActualParameter(actualParameters, pinName) {
        if (!actualParameters) return null;
        
        for (const paramName in actualParameters) {
            const param = actualParameters[paramName];
            if (param.name === pinName || paramName === pinName) {
                return param;
            }
        }
        return null;
    }
    
    /**
     * Render individual parameter with Octane-style controls
     */
    renderOctaneParameter(paramDef, actualParam) {
        const value = actualParam ? actualParam.value : paramDef.default;
        const id = this.getNextId();
        
        switch (paramDef.type) {
            case 'boolean':
                return this.renderOctaneBoolean(paramDef, value, id);
            case 'float':
                return this.renderOctaneFloat(paramDef, value, id);
            case 'integer':
                return this.renderOctaneInteger(paramDef, value, id);
            case 'vector2':
                return this.renderOctaneVector2(paramDef, value, id);
            case 'vector3':
                return this.renderOctaneVector3(paramDef, value, id);
            case 'vector2i':
                return this.renderOctaneVector2i(paramDef, value, id);
            case 'color':
                return this.renderOctaneColor(paramDef, value, id);
            case 'enum':
                return this.renderOctaneEnum(paramDef, value, id);
            default:
                return this.renderOctaneGeneric(paramDef, value, id);
        }
    }
    
    /**
     * Render boolean parameter (checkbox) in Octane style
     */
    renderOctaneBoolean(paramDef, value, id) {
        const checked = value ? 'checked' : '';
        const checkmark = value ? '✓' : '';
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <div class="octane-checkbox-container">
                        <input type="checkbox" id="${id}" class="octane-checkbox" 
                               ${checked} data-pin-name="${paramDef.pinName}">
                        <label for="${id}" class="octane-checkbox-label">
                            <span class="octane-checkbox-custom">
                                <span class="octane-checkbox-checkmark">${checkmark}</span>
                            </span>
                            <span class="octane-parameter-label">${paramDef.name}</span>
                        </label>
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render float parameter (slider + number input) in Octane style
     */
    renderOctaneFloat(paramDef, value, id) {
        const numValue = typeof value === 'number' ? value : (paramDef.default || 0);
        const min = paramDef.min || 0;
        const max = paramDef.max || 100;
        const step = this.calculateStep(min, max);
        const unit = paramDef.unit ? ` ${paramDef.unit}` : '';
        const isInfinity = paramDef.special === 'infinity' && (numValue >= max || numValue === Infinity);
        const displayValue = isInfinity ? '∞' : numValue.toFixed(6).replace(/\.?0+$/, '');
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${paramDef.name}:</label>
                    <div class="octane-control-group">
                        <input type="range" class="octane-slider" 
                               min="${min}" max="${max}" value="${numValue}" step="${step}"
                               data-pin-name="${paramDef.pinName}" data-param-type="float">
                        <input type="text" class="octane-number-input" 
                               value="${displayValue}" data-pin-name="${paramDef.pinName}"
                               data-param-type="float" data-min="${min}" data-max="${max}">
                        ${unit ? `<span class="octane-unit">${unit}</span>` : ''}
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render integer parameter in Octane style
     */
    renderOctaneInteger(paramDef, value, id) {
        const numValue = typeof value === 'number' ? Math.round(value) : (paramDef.default || 0);
        const min = paramDef.min || 0;
        const max = paramDef.max || 100;
        const unit = paramDef.unit ? ` ${paramDef.unit}` : '';
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${paramDef.name}:</label>
                    <div class="octane-control-group">
                        <input type="range" class="octane-slider" 
                               min="${min}" max="${max}" value="${numValue}" step="1"
                               data-pin-name="${paramDef.pinName}" data-param-type="integer">
                        <input type="number" class="octane-number-input" 
                               value="${numValue}" min="${min}" max="${max}" step="1"
                               data-pin-name="${paramDef.pinName}" data-param-type="integer">
                        ${unit ? `<span class="octane-unit">${unit}</span>` : ''}
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render vector2 parameter (dual number inputs) in Octane style
     */
    renderOctaneVector2(paramDef, value, id) {
        const vecValue = Array.isArray(value) ? value : (paramDef.default || [0, 0]);
        const unit = paramDef.unit ? ` ${paramDef.unit}` : '';
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${paramDef.name}:</label>
                    <div class="octane-vector-group">
                        <input type="number" class="octane-vector-input" 
                               value="${vecValue[0]}" step="0.001"
                               data-pin-name="${paramDef.pinName}" data-param-type="vector2" data-component="0">
                        <span class="octane-vector-separator">|</span>
                        <input type="number" class="octane-vector-input" 
                               value="${vecValue[1]}" step="0.001"
                               data-pin-name="${paramDef.pinName}" data-param-type="vector2" data-component="1">
                        ${unit ? `<span class="octane-unit">${unit}</span>` : ''}
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render vector3 parameter (triple number inputs) in Octane style
     */
    renderOctaneVector3(paramDef, value, id) {
        const vecValue = Array.isArray(value) ? value : (paramDef.default || [0, 0, 0]);
        const unit = paramDef.unit ? ` ${paramDef.unit}` : '';
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${paramDef.name}:</label>
                    <div class="octane-vector-group">
                        <input type="number" class="octane-vector-input" 
                               value="${vecValue[0]}" step="0.001"
                               data-pin-name="${paramDef.pinName}" data-param-type="vector3" data-component="0">
                        <span class="octane-vector-separator">|</span>
                        <input type="number" class="octane-vector-input" 
                               value="${vecValue[1]}" step="0.001"
                               data-pin-name="${paramDef.pinName}" data-param-type="vector3" data-component="1">
                        <span class="octane-vector-separator">|</span>
                        <input type="number" class="octane-vector-input" 
                               value="${vecValue[2]}" step="0.001"
                               data-pin-name="${paramDef.pinName}" data-param-type="vector3" data-component="2">
                        ${unit ? `<span class="octane-unit">${unit}</span>` : ''}
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render vector2i parameter (dual integer inputs) in Octane style
     */
    renderOctaneVector2i(paramDef, value, id) {
        const vecValue = Array.isArray(value) ? value : (paramDef.default || [0, 0]);
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${paramDef.name}:</label>
                    <div class="octane-vector-group">
                        <input type="number" class="octane-vector-input" 
                               value="${Math.round(vecValue[0])}" step="1"
                               data-pin-name="${paramDef.pinName}" data-param-type="vector2i" data-component="0">
                        <span class="octane-vector-separator">×</span>
                        <input type="number" class="octane-vector-input" 
                               value="${Math.round(vecValue[1])}" step="1"
                               data-pin-name="${paramDef.pinName}" data-param-type="vector2i" data-component="1">
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render color parameter with color bar in Octane style
     */
    renderOctaneColor(paramDef, value, id) {
        const colorValue = Array.isArray(value) ? value : (paramDef.default || [1, 1, 1]);
        const rgbColor = `rgb(${Math.round(colorValue[0] * 255)}, ${Math.round(colorValue[1] * 255)}, ${Math.round(colorValue[2] * 255)})`;
        const hexColor = this.rgbToHex(colorValue[0], colorValue[1], colorValue[2]);
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${paramDef.name}:</label>
                    <div class="octane-color-group">
                        <div class="octane-color-bar" style="background-color: ${rgbColor};"
                             data-pin-name="${paramDef.pinName}" data-param-type="color"></div>
                        <input type="color" class="octane-color-picker" 
                               value="${hexColor}" data-pin-name="${paramDef.pinName}" data-param-type="color">
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render enum parameter (dropdown) in Octane style
     */
    renderOctaneEnum(paramDef, value, id) {
        const selectedValue = value || paramDef.default;
        let optionsHtml = '';
        
        for (const option of paramDef.options) {
            const selected = option === selectedValue ? 'selected' : '';
            optionsHtml += `<option value="${option}" ${selected}>${option}</option>`;
        }
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${paramDef.name}:</label>
                    <div class="octane-control-group">
                        <select class="octane-dropdown" data-pin-name="${paramDef.pinName}" data-param-type="enum">
                            ${optionsHtml}
                        </select>
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render generic parameter for unknown types
     */
    renderOctaneGeneric(paramDef, value, id) {
        const displayValue = value !== undefined ? String(value) : '';
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${paramDef.name}:</label>
                    <div class="octane-control-group">
                        <input type="text" class="octane-text-input" 
                               value="${displayValue}" data-pin-name="${paramDef.pinName}" data-param-type="generic">
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Calculate appropriate step value for sliders
     */
    calculateStep(min, max) {
        const range = max - min;
        if (range <= 1) return 0.001;
        if (range <= 10) return 0.01;
        if (range <= 100) return 0.1;
        return 1;
    }
    
    /**
     * Convert RGB values (0-1) to hex color
     */
    rgbToHex(r, g, b) {
        const toHex = (c) => {
            const hex = Math.round(c * 255).toString(16);
            return hex.length === 1 ? '0' + hex : hex;
        };
        return `#${toHex(r)}${toHex(g)}${toHex(b)}`;
    }
    
    /**
     * Fallback renderer for when parameter groups are not available
     */
    renderFallbackParameters(parameters) {
        let html = '<div class="octane-parameter-group">';
        html += '<div class="octane-group-header expanded"><span class="octane-group-icon">▼</span><span class="octane-group-title">Parameters</span></div>';
        html += '<div class="octane-group-content">';
        
        for (const paramName in parameters) {
            const param = parameters[paramName];
            html += this.renderFallbackParameter(param);
        }
        
        html += '</div></div>';
        return html;
    }
    
    /**
     * Render fallback parameter when no definition is available
     */
    renderFallbackParameter(param) {
        const id = this.getNextId();
        const value = param.value !== undefined ? param.value : '';
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-control">
                    <span class="octane-parameter-icon">►</span>
                    <label class="octane-parameter-label">${param.label || param.name}:</label>
                    <div class="octane-control-group">
                        <input type="text" class="octane-text-input" 
                               value="${value}" data-pin-name="${param.name}" data-param-type="generic">
                    </div>
                </div>
            </div>
        `;
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { OctaneParameterRenderer };
} else {
    // Browser environment
    window.OctaneParameterRenderer = OctaneParameterRenderer;
}