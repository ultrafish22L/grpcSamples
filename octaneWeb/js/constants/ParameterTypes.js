/**
 * Parameter Types and UI Control Mappings
 * Maps Octane parameter types to appropriate UI controls
 * Based on analysis of Octane Render Studio interface
 */

// Parameter type to UI control mapping
export const PARAMETER_TYPES = {
    // Numeric types
    'FLOAT': 'numeric-slider',
    'DOUBLE': 'numeric-slider', 
    'INT': 'numeric-input',
    'UINT': 'numeric-input',
    
    // Boolean types
    'BOOL': 'checkbox',
    'BOOLEAN': 'checkbox',
    
    // Selection types
    'ENUM': 'dropdown',
    'CHOICE': 'dropdown',
    'SELECT': 'dropdown',
    
    // Color types
    'COLOR': 'color-picker',
    'RGB': 'color-picker',
    'RGBA': 'color-picker',
    
    // Text types
    'STRING': 'text-input',
    'TEXT': 'text-input',
    'PATH': 'file-input',
    
    // Vector types
    'VECTOR2': 'vector2-input',
    'VECTOR3': 'vector3-input',
    'VECTOR4': 'vector4-input'
};

// Parameter groups matching Octane UI layout
export const PARAMETER_GROUPS = {
    'camera': {
        title: 'Camera',
        icon: '📷',
        parameters: ['Camera type', 'Orthographic']
    },
    'physical-camera': {
        title: 'Physical camera parameters', 
        icon: '📐',
        parameters: ['Sensor width', 'Focal length', 'F-stop']
    },
    'viewing-angle': {
        title: 'Viewing angle',
        icon: '👁️',
        parameters: ['Field of view', 'Scale of view', 'Distortion', 'Lens shift']
    },
    'clipping': {
        title: 'Clipping',
        icon: '✂️', 
        parameters: ['Near clip depth', 'Far clip depth']
    },
    'depth-of-field': {
        title: 'Depth of field',
        icon: '🎯',
        parameters: ['Auto-focus', 'Focal depth', 'Aperture', 'Aperture aspect ratio', 'Aperture edge', 'Bokeh side count']
    },
    'transform': {
        title: 'Transform',
        icon: '🔄',
        parameters: ['Position', 'Rotation', 'Scale']
    },
    'material': {
        title: 'Material',
        icon: '🎨',
        parameters: ['Diffuse', 'Specular', 'Roughness', 'Metallic', 'Opacity']
    },
    'lighting': {
        title: 'Lighting',
        icon: '💡',
        parameters: ['Intensity', 'Color', 'Temperature', 'Power']
    }
};

// Parameter name to group mapping (for auto-categorization)
export const PARAMETER_TO_GROUP = {};

// Build reverse mapping
Object.keys(PARAMETER_GROUPS).forEach(groupKey => {
    const group = PARAMETER_GROUPS[groupKey];
    group.parameters.forEach(paramName => {
        PARAMETER_TO_GROUP[paramName.toLowerCase()] = groupKey;
    });
});

// Parameter value ranges and defaults
export const PARAMETER_RANGES = {
    'Sensor width': { min: 1, max: 100, default: 36, step: 0.1, unit: 'mm' },
    'Focal length': { min: 1, max: 1000, default: 50, step: 0.1, unit: 'mm' },
    'F-stop': { min: 0.1, max: 64, default: 2.8, step: 0.1, unit: 'f/' },
    'Field of view': { min: 1, max: 179, default: 39.6, step: 0.1, unit: '°' },
    'Scale of view': { min: 0.1, max: 10, default: 17.14, step: 0.01, unit: '' },
    'Distortion': { min: -1, max: 1, default: 0, step: 0.001, unit: '' },
    'Near clip depth': { min: 0.001, max: 1000, default: 0.1, step: 0.001, unit: 'units' },
    'Far clip depth': { min: 1, max: 10000, default: 1000, step: 1, unit: 'units' },
    'Focal depth': { min: 0.1, max: 1000, default: 1.118, step: 0.001, unit: 'units' },
    'Aperture': { min: 0, max: 1, default: 0.893, step: 0.001, unit: '' },
    'Aperture aspect ratio': { min: 0.1, max: 10, default: 1, step: 0.01, unit: '' },
    'Aperture edge': { min: 0, max: 1, default: 1, step: 0.01, unit: '' },
    'Bokeh side count': { min: 3, max: 12, default: 6, step: 1, unit: '' }
};

// Parameter icons for visual identification
export const PARAMETER_ICONS = {
    // Camera parameters
    'Orthographic': '📐',
    'Sensor width': '📏',
    'Focal length': '🔍',
    'F-stop': '📷',
    
    // Viewing parameters
    'Field of view': '👁️',
    'Scale of view': '🔍',
    'Distortion': '🌀',
    'Lens shift': '↔️',
    'Perspective correction': '📐',
    'Pixel aspect ratio': '📺',
    
    // Clipping parameters
    'Near clip depth': '✂️',
    'Far clip depth': '✂️',
    
    // Depth of field parameters
    'Auto-focus': '🎯',
    'Focal depth': '📏',
    'Aperture': '⭕',
    'Aperture aspect ratio': '📐',
    'Aperture edge': '🔘',
    'Bokeh side count': '⬡',
    
    // Default icons by type
    'FLOAT': '🔢',
    'INT': '🔢',
    'BOOL': '☑️',
    'COLOR': '🎨',
    'STRING': '📝',
    'ENUM': '📋'
};

// Detect parameter type from Octane API data
export function detectParameterType(paramData) {
    if (!paramData) return 'text-input';
    
    // Check explicit type mapping first
    if (paramData.type && PARAMETER_TYPES[paramData.type.toUpperCase()]) {
        return PARAMETER_TYPES[paramData.type.toUpperCase()];
    }
    
    // Infer from value type
    if (typeof paramData.value === 'boolean') return 'checkbox';
    if (typeof paramData.value === 'number') {
        // Check if it has min/max for slider vs input
        if (paramData.min !== undefined && paramData.max !== undefined) {
            return 'numeric-slider';
        }
        return 'numeric-input';
    }
    
    // Check for options/enum
    if (paramData.options && Array.isArray(paramData.options)) {
        return 'dropdown';
    }
    
    // Check for color patterns
    if (paramData.name && paramData.name.toLowerCase().includes('color')) {
        return 'color-picker';
    }
    
    // Default to text input
    return 'text-input';
}

// Get parameter group for a parameter name
export function getParameterGroup(paramName) {
    const key = paramName.toLowerCase();
    return PARAMETER_TO_GROUP[key] || 'general';
}

// Get parameter icon
export function getParameterIcon(paramName, paramType) {
    return PARAMETER_ICONS[paramName] || PARAMETER_ICONS[paramType] || '⚙️';
}

// Get parameter range/constraints
export function getParameterRange(paramName) {
    return PARAMETER_RANGES[paramName] || {
        min: 0,
        max: 100,
        default: 0,
        step: 1,
        unit: ''
    };
}