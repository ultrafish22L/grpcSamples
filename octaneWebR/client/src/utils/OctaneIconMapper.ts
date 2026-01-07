/**
 * Octane Icon Mapper for React TypeScript
 * Provides consistent icon mapping matching the reference screenshot
 */

export class OctaneIconMapper {
  
  /**
   * Get icon for parameter types (matching reference screenshot exactly)
   */
  static getParameterIcon(type: string, nodeType?: string): string {
    // Parameter type icons (matching reference screenshot)
    switch (type) {
      case 'PT_BOOL':
      case 'AT_BOOL':
        return '☑'; // Checkbox icon (not emoji)
      
      case 'PT_FLOAT':
      case 'AT_FLOAT':
      case 'PT_INT':
      case 'AT_INT':
        return '🔢'; // Number icon
      
      case 'PT_ENUM':
      case 'AT_ENUM':
        return '📋'; // Dropdown list icon
      
      case 'PT_RGB':
      case 'AT_RGB':
      case 'PT_FLOAT3':
      case 'AT_FLOAT3':
        // Check if this is a color parameter
        if (nodeType === 'NT_TEX_RGB' || type.includes('COLOR')) {
          return '🎨'; // Color palette icon
        }
        return '🔢'; // Vector number icon
      
      case 'PT_FLOAT2':
      case 'AT_FLOAT2':
      case 'PT_LONG2':
      case 'AT_LONG2':
        return '🔢'; // Vector number icon
      
      case 'PT_STRING':
      case 'AT_STRING':
        return '📝'; // Text icon
      
      default:
        return '⚙'; // Generic parameter icon
    }
  }

  /**
   * Get icon for node types (matching reference screenshot)
   */
  static getNodeIcon(outType: string): string {
    const iconMap: Record<string, string> = {
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
      'PT_POST_PROCESSING': '⚙️',
    };

    return iconMap[outType] || '⚙';
  }

  /**
   * Format color value for HTML color input (matching reference)
   */
  static formatColorValue(value: any): string {
    if (typeof value === 'string' && value.startsWith('#')) {
      return value;
    }
    
    if (Array.isArray(value) && value.length >= 3) {
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
    
    return '#ffffff'; // Default white
  }

  /**
   * Parse HTML color input back to Octane format
   */
  static parseColorValue(hexColor: string): { x: number; y: number; z: number } {
    if (typeof hexColor === 'string' && hexColor.startsWith('#')) {
      const r = parseInt(hexColor.substring(1, 3), 16) / 255;
      const g = parseInt(hexColor.substring(3, 5), 16) / 255;
      const b = parseInt(hexColor.substring(5, 7), 16) / 255;
      return { x: r, y: g, z: b };
    }
    return { x: 1, y: 1, z: 1 }; // Default white
  }

  /**
   * Format node color from Octane color value
   */
  static formatNodeColor(nodeColor?: number): string {
    if (!nodeColor) return '#666666';
    
    // Convert Octane node color to hex
    const r = (nodeColor >> 16) & 0xFF;
    const g = (nodeColor >> 8) & 0xFF;
    const b = nodeColor & 0xFF;
    
    return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
  }
}

// Helper functions for backward compatibility
export function getNodeIcon(node: any): string {
  return OctaneIconMapper.getNodeIcon(node.type || node.outType || 'PT_UNKNOWN');
}

export function formatColor(nodeColor?: number): string {
  return OctaneIconMapper.formatNodeColor(nodeColor);
}