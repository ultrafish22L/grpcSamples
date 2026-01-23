/**
 * Unified Icon and Color Mapping System
 * Consolidates all icon/color mappings from across the application
 * 
 * This is a direct port of octaneWeb's OctaneIconMapper.js to React TypeScript
 * Maintains exact same functionality and icon mappings for consistency
 */

import { getNodeIconPath, hasIconMapping } from '@/constants/IconMapping';

export class OctaneIconMapper {
  
  /**
   * Format color value for HTML color input
   * @param value - Color value (object, array, string, or number)
   * @returns Hex color string
   */
  static formatColorValue(value: any): string {
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
    if (typeof value === 'object' && value !== null) {
      const r = Math.round((value.x || 0) * 255);
      const g = Math.round((value.y || 0) * 255);
      const b = Math.round((value.z || 0) * 255);
      return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
    }
    if (typeof value === 'number') {
      // FIX: Properly decode uint32 pinColor value
      // Octane uses ARGB format: 0xAARRGGBB (Alpha, Red, Green, Blue)
      // Extract RGB bytes, ignoring alpha channel
      const r = (value >> 16) & 0xFF;
      const g = (value >> 8) & 0xFF;
      const b = value & 0xFF;
      return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
    }
    return '#ffffff'; // Default white
  }

  /**
   * Decode HTML color input
   * @param value - Hex color string
   * @returns Color object {x, y, z}
   */
  static getColorValue(value: any): any {
    if (typeof value === 'string' && value.startsWith('#')) {
      const out = {
        x: parseInt(value.substring(1, 3), 16) / 255,
        y: parseInt(value.substring(3, 5), 16) / 255,
        z: parseInt(value.substring(5, 7), 16) / 255
      };
      return out;
    }
    return value;
  }

  /**
   * Get icon for node types (consolidated from SceneOutlinerSync.js)
   * This replaces getOctaneIconFor() function
   * Now returns actual Octane icon file paths from the /icons/ directory
   */
  static getNodeIcon(outType: string, name?: string): string {
    // Check if it's an NT_ node type and has an icon mapping
    if (outType && outType.startsWith('NT_') && hasIconMapping(outType)) {
      return getNodeIconPath(outType);
    }

    // Handle parameter types with fallback icons
    if (outType === 'PT_BOOL' || name === 'Bool value') {
      return '/icons/BOOL node.png';
    }
    if (outType === 'PT_FLOAT' || name === 'Float value') {
      return '/icons/FLOAT node.png';
    }
    if (outType === 'PT_INT' || name === 'Int value') {
      return '/icons/INT node.png';
    }
    if (outType === 'PT_ENUM' || name === 'Enum value') {
      return '/icons/ENUM node.png';
    }
    if (outType === 'PT_RGB' || name === 'RGB color') {
      return '/icons/RGB_SPECTRUM node.png';
    }
    
    // Fallback based on parameter type with actual icon files
    const iconMap: Record<string, string> = {
      'PT_RENDER_TARGET': '/icons/RENDER_TARGET node.png',
      'PT_MESH': '/icons/MESH node.png',
      'PT_GEOMETRY': '/icons/MESH node.png',
      'PT_CAMERA': '/icons/CAMERA node.png',
      'PT_LIGHT': '/icons/QUAD_LIGHT node.png',
      'PT_MATERIAL': '/icons/UNIVERSAL_MATERIAL node.png',
      'PT_ENVIRONMENT': '/icons/ENVIRONMENT node.png',
      'PT_FILM_SETTINGS': '/icons/FILM node.png',
      'PT_ANIMATION_SETTINGS': '/icons/ANIMATION_SETTINGS node.png',
      'PT_KERNEL': '/icons/KERNEL_OUT node.png',
      'PT_RENDER_LAYER': '/icons/RENDER_LAYER node.png',
      'PT_RENDER_PASSES': '/icons/RENDER_PASSES node.png',
      'PT_OUTPUT_AOV_GROUP': '/icons/OUTPUT_AOV_GROUP node.png',
      'PT_IMAGER': '/icons/IMAGER node.png',
      'PT_POSTPROCESSING': '/icons/POST_PROCESSING node.png',
      'unknown': '/icons/CATEGORY.png'
    };
    
    return iconMap[outType] || iconMap['unknown'];
  }
  
  /**
   * Get icon for parameters (consolidated from NodeInspector.js - both versions)
   * This replaces both getParameterIcon() functions
   */
  static getParameterIcon(paramName: string, paramType?: string): string {
    // First check the detailed parameter name mapping (from NodeInspector.js line 2868)
    const nameIcons: Record<string, string> = {
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
    const technicalIcons: Record<string, string> = {
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
    const typeIcons: Record<string, string> = {
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
    
    if (paramType && typeIcons[paramType]) {
      return typeIcons[paramType];
    }
    
    // Default fallback
    return paramType === 'bool' ? '☐' : 
           (paramType === 'float' || paramType === 'int') ? '▤' : '◦';
  }
  
  /**
   * Get icon for pin groups
   * This will be used for parameter group headers
   */
  static getPinGroupIcon(groupName: string): string {
    const groupIcons: Record<string, string> = {
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

  /**
   * Format node color from Octane color value
   */
  static formatNodeColor(nodeColor?: number | { x: number; y: number; z: number }): string {
    if (!nodeColor) return '#666666';
    
    // Handle object format {x, y, z}
    if (typeof nodeColor === 'object') {
      const r = Math.round((nodeColor.x || 0) * 255);
      const g = Math.round((nodeColor.y || 0) * 255);
      const b = Math.round((nodeColor.z || 0) * 255);
      return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
    }
    
    // Handle number format (RGB packed)
    const r = (nodeColor >> 16) & 0xFF;
    const g = (nodeColor >> 8) & 0xFF;
    const b = nodeColor & 0xFF;
    
    return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
  }
}

// Helper functions for backward compatibility
export function getNodeIcon(node: any): string {
  return OctaneIconMapper.getNodeIcon(node.type || node.outType || 'unknown', node.name);
}

export function formatColor(nodeColor?: number | { x: number; y: number; z: number }): string {
  return OctaneIconMapper.formatNodeColor(nodeColor);
}

// Alias for parseColorValue (matching octaneWeb's getColorValue)
export function parseColorValue(hexColor: string): { x: number; y: number; z: number } {
  const result = OctaneIconMapper.getColorValue(hexColor);
  if (typeof result === 'object' && result.x !== undefined) {
    return result;
  }
  return { x: 1, y: 1, z: 1 }; // Default white
}

console.log('OctaneIconMapper loaded - consolidated icon/color mapping system');