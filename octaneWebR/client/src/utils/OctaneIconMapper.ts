/**
 * OctaneIconMapper - Backward Compatibility Layer
 * 
 * This module provides backward compatibility by delegating to the proper modules:
 * - PinTypes.ts for PT_ type icon/color lookups
 * - NodeTypes.ts for NT_ type icon lookups
 * - ColorUtils.ts for color conversion utilities
 * 
 * New code should import directly from those modules instead of using this.
 * 
 * @deprecated Use PinTypes, NodeTypes, and ColorUtils directly
 */

import { getIconForType, getColorForType } from '../constants/PinTypes';
import { formatColorValue, parseColorValue, formatNodeColor } from './ColorUtils';

/**
 * @deprecated Use functions from PinTypes, NodeTypes, and ColorUtils directly
 */
export class OctaneIconMapper {
  
  /**
   * @deprecated Use formatColorValue from ColorUtils instead
   */
  static formatColorValue = formatColorValue;

  /**
   * @deprecated Use parseColorValue from ColorUtils instead
   */
  static getColorValue = parseColorValue;

  /**
   * @deprecated Use getIconForType from PinTypes instead
   */
  static getNodeIcon(outType: string, name?: string): string {
    return getIconForType(outType, name);
  }

  /**
   * @deprecated Use getColorForType from PinTypes instead
   */
  static getPinColor(pinType: string): string {
    return getColorForType(pinType);
  }

  /**
   * @deprecated Use formatNodeColor from ColorUtils instead
   */
  static formatNodeColor = formatNodeColor;
}

/**
 * @deprecated Use getIconForType from PinTypes instead
 */
export function getNodeIcon(node: any): string {
  return getIconForType(node.type || node.outType || 'unknown', node.name);
}

/**
 * @deprecated Use formatNodeColor from ColorUtils instead
 */
export function formatColor(nodeColor?: number | { x: number; y: number; z: number }): string {
  return formatNodeColor(nodeColor);
}