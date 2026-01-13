/**
 * Octane Icon Loader Utility
 * 
 * Provides functions to load native Octane icons extracted from the LiveLink API.
 * Icons are stored in /public/icons/ and organized by type (nodes/ and graphs/).
 * 
 * Usage:
 *   import { getNodeIcon, getGraphIcon, NodeIcon } from '@/utils/IconLoader';
 *   
 *   // In a component:
 *   <NodeIcon nodeType="NT_MAT_DIFFUSE" size={24} />
 *   
 *   // Or get the URL directly:
 *   const iconUrl = getNodeIcon("NT_MAT_DIFFUSE");
 */

export type NodeTypeString = string; // NT_* enum values (e.g., "NT_MAT_DIFFUSE")
export type GraphTypeString = string; // GT_* enum values (e.g., "GT_STANDARD")

/**
 * Get the URL for a node type icon
 * @param nodeType Node type enum name (e.g., "NT_MAT_DIFFUSE")
 * @returns URL path to the icon PNG
 */
export function getNodeIcon(nodeType: NodeTypeString): string {
  return `/icons/nodes/${nodeType}.png`;
}

/**
 * Get the URL for a graph type icon
 * @param graphType Graph type enum name (e.g., "GT_STANDARD")
 * @returns URL path to the icon PNG
 */
export function getGraphIcon(graphType: GraphTypeString): string {
  return `/icons/graphs/${graphType}.png`;
}

/**
 * Default fallback icon when specific icon is not found
 */
export const DEFAULT_NODE_ICON = '/icons/default-node.png';
export const DEFAULT_GRAPH_ICON = '/icons/default-graph.png';

/**
 * Check if a node icon exists (client-side check)
 * Note: This doesn't actually verify file existence, just checks format
 */
export function isValidNodeType(nodeType: string): boolean {
  return nodeType.startsWith('NT_');
}

/**
 * Check if a graph icon exists (client-side check)
 * Note: This doesn't actually verify file existence, just checks format
 */
export function isValidGraphType(graphType: string): boolean {
  return graphType.startsWith('GT_');
}

/**
 * Parse node type from numeric enum value (if you have a mapping)
 * This would require the OctaneTypes constants to be imported
 */
export function getNodeTypeString(nodeTypeValue: number): NodeTypeString | null {
  // TODO: Import OctaneTypes constants and create reverse mapping
  // For now, return null - implement when needed
  return null;
}

/**
 * React component for displaying node icons
 */
import React from 'react';

export interface NodeIconProps {
  nodeType: NodeTypeString;
  size?: number;
  className?: string;
  title?: string;
}

export const NodeIcon: React.FC<NodeIconProps> = ({ 
  nodeType, 
  size = 24, 
  className = '',
  title 
}) => {
  const [hasError, setHasError] = React.useState(false);
  
  return (
    <img 
      src={hasError ? DEFAULT_NODE_ICON : getNodeIcon(nodeType)}
      alt={title || nodeType}
      title={title || nodeType}
      width={size}
      height={size}
      className={`octane-node-icon ${className}`}
      onError={() => setHasError(true)}
      style={{
        display: 'inline-block',
        verticalAlign: 'middle',
        imageRendering: 'auto',
      }}
    />
  );
};

/**
 * React component for displaying graph icons
 */
export interface GraphIconProps {
  graphType: GraphTypeString;
  size?: number;
  className?: string;
  title?: string;
}

export const GraphIcon: React.FC<GraphIconProps> = ({ 
  graphType, 
  size = 24, 
  className = '',
  title 
}) => {
  const [hasError, setHasError] = React.useState(false);
  
  return (
    <img 
      src={hasError ? DEFAULT_GRAPH_ICON : getGraphIcon(graphType)}
      alt={title || graphType}
      title={title || graphType}
      width={size}
      height={size}
      className={`octane-graph-icon ${className}`}
      onError={() => setHasError(true)}
      style={{
        display: 'inline-block',
        verticalAlign: 'middle',
        imageRendering: 'auto',
      }}
    />
  );
};

/**
 * Hook for preloading icons (useful for large lists)
 */
export function usePreloadIcons(nodeTypes: NodeTypeString[], graphTypes: GraphTypeString[] = []) {
  React.useEffect(() => {
    // Preload node icons
    nodeTypes.forEach(nodeType => {
      const img = new Image();
      img.src = getNodeIcon(nodeType);
    });
    
    // Preload graph icons
    graphTypes.forEach(graphType => {
      const img = new Image();
      img.src = getGraphIcon(graphType);
    });
  }, [nodeTypes, graphTypes]);
}

/**
 * Common node types (most frequently used)
 * These can be used for preloading or quick reference
 */
export const COMMON_NODE_TYPES = {
  // Materials
  DIFFUSE: 'NT_MAT_DIFFUSE' as NodeTypeString,
  GLOSSY: 'NT_MAT_GLOSSY' as NodeTypeString,
  SPECULAR: 'NT_MAT_SPECULAR' as NodeTypeString,
  UNIVERSAL: 'NT_MAT_UNIVERSAL' as NodeTypeString,
  MIX: 'NT_MAT_MIX' as NodeTypeString,
  
  // Textures
  IMAGE: 'NT_TEX_IMAGE' as NodeTypeString,
  RGB: 'NT_TEX_RGB' as NodeTypeString,
  FLOAT: 'NT_TEX_FLOAT' as NodeTypeString,
  NOISE: 'NT_TEX_NOISE' as NodeTypeString,
  TURBULENCE: 'NT_TEX_TURBULENCE' as NodeTypeString,
  
  // Geometry
  MESH: 'NT_GEO_MESH' as NodeTypeString,
  GROUP: 'NT_GEO_GROUP' as NodeTypeString,
  SCATTER: 'NT_GEO_SCATTER' as NodeTypeString,
  
  // Cameras
  THINLENS: 'NT_CAM_THINLENS' as NodeTypeString,
  PANORAMIC: 'NT_CAM_PANORAMIC' as NodeTypeString,
  
  // Lights
  DAYLIGHT: 'NT_ENV_DAYLIGHT' as NodeTypeString,
  TEXTURE_ENV: 'NT_ENV_TEXTURE' as NodeTypeString,
};

/**
 * Common graph types
 */
export const COMMON_GRAPH_TYPES = {
  STANDARD: 'GT_STANDARD' as GraphTypeString,
  REFERENCE: 'GT_REFERENCE' as GraphTypeString,
};
