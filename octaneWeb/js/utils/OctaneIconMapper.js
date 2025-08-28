/**
 * Unified Icon and Color Mapping System
 * Consolidates all icon/color mappings from across the application
 * 
 * PHASE 1: Consolidation without breaking existing functionality
 * This file consolidates all the scattered icon and color mapping functions
 * from NodeInspector.js and SceneOutlinerSync.js
 */

class OctaneIconMapper {
    
            /**
     * Format color value for HTML color input
     * @param {*} value - Color value (array, string, or number)
     * @returns {string} - Hex color string
     */
    static formatColorValue(value) {
        if (typeof value === 'string' && value.startsWith('#')) {
            return value;
        }
        if (Array.isArray(value) && value.length >= 3) {
            // RGB array [r, g, b] where values are 0-1
            const r = Math.round((value[0] || 0) * 255);
            const g = Math.round((value[1] || 0) * 255);
            const b = Math.round((value[2] || 0) * 255);
            return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
        }
        if (typeof value === 'number') {
            return `#${value.toString(16).padStart(2, '0')}`;
        }
        return '#ffffff'; // Default white
    }

    /**
     * Get icon for node types (consolidated from SceneOutlinerSync.js)
     * This replaces getOctaneIconFor() function
     */
    static getNodeIcon(outType) {
        
        // Handle parameter types with specific icons
        if (outType === 'PT_BOOL' || name === 'Bool value') {
            return '☑️'; // Checkbox for boolean parameters
        }
        if (outType === 'PT_FLOAT' || name === 'Float value') {
            return '🔢'; // Numbers for float parameters
        }
        if (outType === 'PT_INT' || name === 'Int value') {
            return '🔢'; // Numbers for integer parameters
        }
        if (outType === 'PT_ENUM' || name === 'Enum value') {
            return '📋'; // List for enum parameters
        }
        if (outType === 'PT_RGB' || name === 'RGB color') {
            return '🎨'; // Color palette for RGB parameters
        }
        
        // Fallback based on type
        const iconMap = {
            'PT_RENDER_TARGET': '🎯',
            'PT_MESH': '🫖',
            'PT_GEOMETRY': '🫖',
            'PT_CAMERA': '📷',
            'PT_LIGHT': '💡',
            'PT_MATERIAL': '🎨',
            'PT_ENVIRONMENT': '🌍',
            'PT_FILM_SETTINGS': '🎬',
            'PT_ANIMATION_SETTINGS': '⏱️',
            'PT_KERNEL': '🔧',
            'PT_RENDER_LAYER': '🎭',
            'PT_RENDER_PASSES': '📊',
            'PT_OUTPUT_AOV_GROUP': '📤',
            'PT_IMAGER': '📷',
            'PT_POSTPROCESSING': '⚙️',
            'unknown': '⬜'
        };
        
        return iconMap[outType] || iconMap['unknown'];
    }
    
    /**
     * Get icon for parameters (consolidated from NodeInspector.js - both versions)
     * This replaces both getParameterIcon() functions
     */
    static getParameterIcon(paramName, paramType) {
        // First check the detailed parameter name mapping (from NodeInspector.js line 2868)
        const nameIcons = {
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
        
        if (nameIcons[paramName]) {
            return nameIcons[paramName];
        }
        
        // Then check the technical parameter mapping (from NodeInspector.js line 1072)
        const technicalIcons = {
            'sensor_width': '▣',
            'focal_length': '◐', 
            'f_stop': '◯',
            'field_of_view': '◐',
            'scale_of_view': '▤',
            'distortion': '◈',
            'lens_shift': '⟷',
            'perspective_correction': '◐',
            'pixel_aspect_ratio': '▦',
            'near_clip_depth': '▤',
            'far_clip_depth': '▤',
            'auto_focus': '◎',
            'focal_depth': '▤',
            'aperture': '◯',
            'aperture_aspect_ratio': '▦',
            'aperture_edge': '▢',
            'bokeh_side_count': '#',
            'bokeh_rotation': '↻',
            'bokeh_roundedness': '◯'
        };
        
        if (technicalIcons[paramName]) {
            return technicalIcons[paramName];
        }
        
        // Finally check type-based icons
        const typeIcons = {
            'checkbox': '☑️',
            'numeric-slider': '🎚️',
            'numeric-input': '🔢',
            'dropdown': '📋',
            'color-picker': '🎨',
            'text-input': '📝',
            'FLOAT': '🔢',
            'INT': '🔢',
            'BOOL': '☑️',
            'COLOR': '🎨',
            'STRING': '📝',
            'ENUM': '📋'
        };
        
        if (typeIcons[paramType]) {
            return typeIcons[paramType];
        }
        
        // Default fallback
        return paramType === 'bool' ? '☐' : 
               (paramType === 'float' || paramType === 'int') ? '▤' : '◦';
    }
    
    /**
     * Get color for node types
     * This can be expanded to include color mappings as needed
     */
    static gePinColor(outType) {
        // Color mapping based on node types
        const colorMap = {
            'PT_RENDER_TARGET': '#ff6b6b',  // Red for render targets
            'PT_CAMERA': '#4ecdc4',         // Teal for cameras
            'PT_LIGHT': '#ffe66d',          // Yellow for lights
            'PT_MATERIAL': '#a8e6cf',       // Green for materials
            'PT_MESH': '#ffd93d',           // Gold for meshes
            'PT_ENVIRONMENT': '#6c5ce7',    // Purple for environments
            'unknown': '#95a5a6'            // Gray for unknown
        };
        
        return colorMap[outType] || colorMap['unknown'];
    }
    
    /**
     * Get icon for pin groups
     * This will be used for parameter group headers
     */
    static getPinGroupIcon(groupName) {
        const groupIcons = {
            'Physical camera parameters': '📐',
            'Viewing angle': '👁️',
            'Clipping': '✂️',
            'Depth of field': '🎯',
            'Position': '🔄',
            'Stereo': '👀',
            'Diffuse': '🎨',
            'Specular': '✨',
            'Light': '💡',
            'Render settings': '⚙️',
            'Transform': '🔄',
            'Material': '🎨',
            'Lighting': '💡'
        };
        
        return groupIcons[groupName] || '📁';
    }

}

// Make available globally for backward compatibility
window.OctaneIconMapper = OctaneIconMapper;

// Export for module systems
if (typeof module !== 'undefined' && module.exports) {
    module.exports = OctaneIconMapper;
}

console.log('OctaneIconMapper loaded - consolidated icon/color mapping system');