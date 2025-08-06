/**
 * Parameter Renderer Utility
 * Generates professional UI controls for different parameter types
 * Matches Octane Render Studio styling and behavior
 */

import { detectParameterType, getParameterIcon, getParameterRange } from '../constants/ParameterTypes.js';

export class ParameterRenderer {
    constructor() {
        this.parameterChangeHandlers = new Map();
    }
    
    /**
     * Render a parameter with appropriate UI control
     */
    renderParameter(paramName, paramData, groupName = 'general') {
        const paramType = detectParameterType(paramData);
        const icon = getParameterIcon(paramName, paramType);
        const range = getParameterRange(paramName);
        
        const container = document.createElement('div');
        container.className = 'parameter-row';
        container.dataset.param = paramName;
        container.dataset.type = paramType;
        container.dataset.group = groupName;
        
        // Parameter label with icon
        const label = document.createElement('div');
        label.className = 'parameter-label';
        label.innerHTML = `
            <span class="parameter-icon">${icon}</span>
            <span class="parameter-name">${paramName}</span>
        `;
        
        // Parameter control
        const control = document.createElement('div');
        control.className = 'parameter-control';
        
        switch (paramType) {
            case 'numeric-slider':
                control.appendChild(this.renderNumericSlider(paramName, paramData, range));
                break;
            case 'numeric-input':
                control.appendChild(this.renderNumericInput(paramName, paramData, range));
                break;
            case 'checkbox':
                control.appendChild(this.renderCheckbox(paramName, paramData));
                break;
            case 'dropdown':
                control.appendChild(this.renderDropdown(paramName, paramData));
                break;
            case 'color-picker':
                control.appendChild(this.renderColorPicker(paramName, paramData));
                break;
            case 'vector2-input':
                control.appendChild(this.renderVector2Input(paramName, paramData));
                break;
            case 'vector3-input':
                control.appendChild(this.renderVector3Input(paramName, paramData));
                break;
            case 'text-input':
            default:
                control.appendChild(this.renderTextInput(paramName, paramData));
                break;
        }
        
        container.appendChild(label);
        container.appendChild(control);
        
        return container;
    }
    
    /**
     * Render numeric slider with input field and inc/dec buttons
     */
    renderNumericSlider(paramName, paramData, range) {
        const container = document.createElement('div');
        container.className = 'parameter-numeric-slider-container';
        
        const value = paramData.value || range.default || 0;
        const min = paramData.min !== undefined ? paramData.min : range.min;
        const max = paramData.max !== undefined ? paramData.max : range.max;
        const step = paramData.step || range.step || 0.01;
        
        container.innerHTML = `
            <div class="parameter-slider-wrapper">
                <input type="range" 
                       class="parameter-slider" 
                       id="slider-${paramName}"
                       min="${min}" 
                       max="${max}" 
                       step="${step}" 
                       value="${value}"
                       data-param="${paramName}">
                <div class="parameter-slider-track">
                    <div class="parameter-slider-fill" style="width: ${((value - min) / (max - min)) * 100}%"></div>
                    <div class="parameter-slider-thumb" style="left: ${((value - min) / (max - min)) * 100}%"></div>
                </div>
            </div>
            <div class="parameter-numeric-input-container">
                <input type="number" 
                       class="parameter-number-input" 
                       id="input-${paramName}"
                       min="${min}" 
                       max="${max}" 
                       step="${step}" 
                       value="${value}"
                       data-param="${paramName}">
                <div class="parameter-controls">
                    <button class="param-increment" data-param="${paramName}" data-step="${step}">▲</button>
                    <button class="param-decrement" data-param="${paramName}" data-step="${step}">▼</button>
                </div>
                ${range.unit ? `<span class="parameter-unit">${range.unit}</span>` : ''}
            </div>
        `;
        
        // Setup event listeners
        this.setupNumericSliderEvents(container, paramName);
        
        return container;
    }
    
    /**
     * Render numeric input with inc/dec buttons
     */
    renderNumericInput(paramName, paramData, range) {
        const container = document.createElement('div');
        container.className = 'parameter-numeric-input-container';
        
        const value = paramData.value || range.default || 0;
        const min = paramData.min !== undefined ? paramData.min : range.min;
        const max = paramData.max !== undefined ? paramData.max : range.max;
        const step = paramData.step || range.step || 1;
        
        container.innerHTML = `
            <input type="number" 
                   class="parameter-number-input" 
                   id="input-${paramName}"
                   min="${min}" 
                   max="${max}" 
                   step="${step}" 
                   value="${value}"
                   data-param="${paramName}">
            <div class="parameter-controls">
                <button class="param-increment" data-param="${paramName}" data-step="${step}">▲</button>
                <button class="param-decrement" data-param="${paramName}" data-step="${step}">▼</button>
            </div>
            ${range.unit ? `<span class="parameter-unit">${range.unit}</span>` : ''}
        `;
        
        // Setup event listeners
        this.setupNumericInputEvents(container, paramName);
        
        return container;
    }
    
    /**
     * Render checkbox control
     */
    renderCheckbox(paramName, paramData) {
        const container = document.createElement('div');
        container.className = 'parameter-checkbox-container';
        
        const checked = paramData.value === true || paramData.value === 'true';
        
        container.innerHTML = `
            <label class="parameter-checkbox-label">
                <input type="checkbox" 
                       class="parameter-checkbox" 
                       id="checkbox-${paramName}"
                       ${checked ? 'checked' : ''}
                       data-param="${paramName}">
                <span class="parameter-checkbox-custom"></span>
            </label>
        `;
        
        // Setup event listeners
        this.setupCheckboxEvents(container, paramName);
        
        return container;
    }
    
    /**
     * Render dropdown/select control
     */
    renderDropdown(paramName, paramData) {
        const container = document.createElement('div');
        container.className = 'parameter-dropdown-container';
        
        const options = paramData.options || [];
        const value = paramData.value || '';
        
        let optionsHtml = '';
        options.forEach(option => {
            const optionValue = typeof option === 'object' ? option.value : option;
            const optionLabel = typeof option === 'object' ? option.label : option;
            const selected = optionValue === value ? 'selected' : '';
            optionsHtml += `<option value="${optionValue}" ${selected}>${optionLabel}</option>`;
        });
        
        container.innerHTML = `
            <select class="parameter-dropdown" 
                    id="dropdown-${paramName}"
                    data-param="${paramName}">
                ${optionsHtml}
            </select>
            <span class="parameter-dropdown-arrow">▼</span>
        `;
        
        // Setup event listeners
        this.setupDropdownEvents(container, paramName);
        
        return container;
    }
    
    /**
     * Render color picker control
     */
    renderColorPicker(paramName, paramData) {
        const container = document.createElement('div');
        container.className = 'parameter-color-container';
        
        const value = paramData.value || '#ffffff';
        const hexValue = this.colorToHex(value);
        
        container.innerHTML = `
            <div class="parameter-color-preview" style="background-color: ${hexValue}"></div>
            <input type="color" 
                   class="parameter-color-picker" 
                   id="color-${paramName}"
                   value="${hexValue}"
                   data-param="${paramName}">
            <input type="text" 
                   class="parameter-color-hex" 
                   id="hex-${paramName}"
                   value="${hexValue}"
                   data-param="${paramName}"
                   maxlength="7"
                   pattern="^#[0-9A-Fa-f]{6}$">
        `;
        
        // Setup event listeners
        this.setupColorPickerEvents(container, paramName);
        
        return container;
    }
    
    /**
     * Render vector2 input (dual numeric inputs)
     */
    renderVector2Input(paramName, paramData) {
        const container = document.createElement('div');
        container.className = 'parameter-vector2-container';
        
        const value = paramData.value || [0, 0];
        const x = Array.isArray(value) ? value[0] : value.x || 0;
        const y = Array.isArray(value) ? value[1] : value.y || 0;
        
        container.innerHTML = `
            <div class="parameter-vector-input">
                <label>X:</label>
                <input type="number" 
                       class="parameter-vector-component" 
                       id="vector-${paramName}-x"
                       value="${x}"
                       data-param="${paramName}"
                       data-component="x"
                       step="0.001">
            </div>
            <div class="parameter-vector-input">
                <label>Y:</label>
                <input type="number" 
                       class="parameter-vector-component" 
                       id="vector-${paramName}-y"
                       value="${y}"
                       data-param="${paramName}"
                       data-component="y"
                       step="0.001">
            </div>
        `;
        
        // Setup event listeners
        this.setupVectorInputEvents(container, paramName, 2);
        
        return container;
    }
    
    /**
     * Render vector3 input (triple numeric inputs)
     */
    renderVector3Input(paramName, paramData) {
        const container = document.createElement('div');
        container.className = 'parameter-vector3-container';
        
        const value = paramData.value || [0, 0, 0];
        const x = Array.isArray(value) ? value[0] : value.x || 0;
        const y = Array.isArray(value) ? value[1] : value.y || 0;
        const z = Array.isArray(value) ? value[2] : value.z || 0;
        
        container.innerHTML = `
            <div class="parameter-vector-input">
                <label>X:</label>
                <input type="number" 
                       class="parameter-vector-component" 
                       id="vector-${paramName}-x"
                       value="${x}"
                       data-param="${paramName}"
                       data-component="x"
                       step="0.001">
            </div>
            <div class="parameter-vector-input">
                <label>Y:</label>
                <input type="number" 
                       class="parameter-vector-component" 
                       id="vector-${paramName}-y"
                       value="${y}"
                       data-param="${paramName}"
                       data-component="y"
                       step="0.001">
            </div>
            <div class="parameter-vector-input">
                <label>Z:</label>
                <input type="number" 
                       class="parameter-vector-component" 
                       id="vector-${paramName}-z"
                       value="${z}"
                       data-param="${paramName}"
                       data-component="z"
                       step="0.001">
            </div>
        `;
        
        // Setup event listeners
        this.setupVectorInputEvents(container, paramName, 3);
        
        return container;
    }
    
    /**
     * Render text input control
     */
    renderTextInput(paramName, paramData) {
        const container = document.createElement('div');
        container.className = 'parameter-text-container';
        
        const value = paramData.value || '';
        
        container.innerHTML = `
            <input type="text" 
                   class="parameter-text-input" 
                   id="text-${paramName}"
                   value="${value}"
                   data-param="${paramName}">
        `;
        
        // Setup event listeners
        this.setupTextInputEvents(container, paramName);
        
        return container;
    }
    
    // Event listener setup methods
    setupNumericSliderEvents(container, paramName) {
        const slider = container.querySelector('.parameter-slider');
        const input = container.querySelector('.parameter-number-input');
        const incrementBtn = container.querySelector('.param-increment');
        const decrementBtn = container.querySelector('.param-decrement');
        const fill = container.querySelector('.parameter-slider-fill');
        const thumb = container.querySelector('.parameter-slider-thumb');
        
        const updateSliderVisual = (value) => {
            const min = parseFloat(slider.min);
            const max = parseFloat(slider.max);
            const percentage = ((value - min) / (max - min)) * 100;
            fill.style.width = `${percentage}%`;
            thumb.style.left = `${percentage}%`;
        };
        
        slider.addEventListener('input', (e) => {
            const value = parseFloat(e.target.value);
            input.value = value;
            updateSliderVisual(value);
            this.emitParameterChange(paramName, value);
        });
        
        input.addEventListener('input', (e) => {
            const value = parseFloat(e.target.value);
            slider.value = value;
            updateSliderVisual(value);
            this.emitParameterChange(paramName, value);
        });
        
        incrementBtn.addEventListener('click', (e) => {
            const step = parseFloat(e.target.dataset.step);
            const currentValue = parseFloat(input.value);
            const newValue = Math.min(parseFloat(slider.max), currentValue + step);
            input.value = newValue;
            slider.value = newValue;
            updateSliderVisual(newValue);
            this.emitParameterChange(paramName, newValue);
        });
        
        decrementBtn.addEventListener('click', (e) => {
            const step = parseFloat(e.target.dataset.step);
            const currentValue = parseFloat(input.value);
            const newValue = Math.max(parseFloat(slider.min), currentValue - step);
            input.value = newValue;
            slider.value = newValue;
            updateSliderVisual(newValue);
            this.emitParameterChange(paramName, newValue);
        });
    }
    
    setupNumericInputEvents(container, paramName) {
        const input = container.querySelector('.parameter-number-input');
        const incrementBtn = container.querySelector('.param-increment');
        const decrementBtn = container.querySelector('.param-decrement');
        
        input.addEventListener('input', (e) => {
            const value = parseFloat(e.target.value);
            this.emitParameterChange(paramName, value);
        });
        
        incrementBtn.addEventListener('click', (e) => {
            const step = parseFloat(e.target.dataset.step);
            const currentValue = parseFloat(input.value);
            const newValue = currentValue + step;
            input.value = newValue;
            this.emitParameterChange(paramName, newValue);
        });
        
        decrementBtn.addEventListener('click', (e) => {
            const step = parseFloat(e.target.dataset.step);
            const currentValue = parseFloat(input.value);
            const newValue = currentValue - step;
            input.value = newValue;
            this.emitParameterChange(paramName, newValue);
        });
    }
    
    setupCheckboxEvents(container, paramName) {
        const checkbox = container.querySelector('.parameter-checkbox');
        
        checkbox.addEventListener('change', (e) => {
            this.emitParameterChange(paramName, e.target.checked);
        });
    }
    
    setupDropdownEvents(container, paramName) {
        const dropdown = container.querySelector('.parameter-dropdown');
        
        dropdown.addEventListener('change', (e) => {
            this.emitParameterChange(paramName, e.target.value);
        });
    }
    
    setupColorPickerEvents(container, paramName) {
        const colorPicker = container.querySelector('.parameter-color-picker');
        const hexInput = container.querySelector('.parameter-color-hex');
        const preview = container.querySelector('.parameter-color-preview');
        
        colorPicker.addEventListener('input', (e) => {
            const color = e.target.value;
            hexInput.value = color;
            preview.style.backgroundColor = color;
            this.emitParameterChange(paramName, color);
        });
        
        hexInput.addEventListener('input', (e) => {
            const color = e.target.value;
            if (/^#[0-9A-Fa-f]{6}$/.test(color)) {
                colorPicker.value = color;
                preview.style.backgroundColor = color;
                this.emitParameterChange(paramName, color);
            }
        });
    }
    
    setupVectorInputEvents(container, paramName, componentCount) {
        const inputs = container.querySelectorAll('.parameter-vector-component');
        
        inputs.forEach(input => {
            input.addEventListener('input', (e) => {
                const components = Array.from(inputs).map(inp => parseFloat(inp.value) || 0);
                this.emitParameterChange(paramName, components);
            });
        });
    }
    
    setupTextInputEvents(container, paramName) {
        const input = container.querySelector('.parameter-text-input');
        
        input.addEventListener('input', (e) => {
            this.emitParameterChange(paramName, e.target.value);
        });
    }
    
    // Utility methods
    colorToHex(color) {
        if (typeof color === 'string' && color.startsWith('#')) {
            return color;
        }
        
        if (Array.isArray(color)) {
            // Convert RGB array to hex
            const r = Math.round(color[0] * 255);
            const g = Math.round(color[1] * 255);
            const b = Math.round(color[2] * 255);
            return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
        }
        
        return '#ffffff';
    }
    
    // Parameter change event emission
    emitParameterChange(paramName, value) {
        const handler = this.parameterChangeHandlers.get(paramName);
        if (handler) {
            handler(paramName, value);
        }
        
        // Emit global parameter change event
        document.dispatchEvent(new CustomEvent('parameterChange', {
            detail: { paramName, value }
        }));
    }
    
    // Register parameter change handler
    onParameterChange(paramName, handler) {
        this.parameterChangeHandlers.set(paramName, handler);
    }
    
    // Remove parameter change handler
    offParameterChange(paramName) {
        this.parameterChangeHandlers.delete(paramName);
    }
}

// Export singleton instance
export const parameterRenderer = new ParameterRenderer();