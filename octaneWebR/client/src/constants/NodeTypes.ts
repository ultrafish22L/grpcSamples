/**
 * Octane Node Type Definitions
 * Ported from octaneWeb's NodeGraphEditor.js initNodeTypes()
 * Based on octaneids.h from Octane API
 */

export interface NodeTypeInfo {
  name: string;
  color: string;
}

export interface NodeTypeCategory {
  [nodeType: string]: NodeTypeInfo;
}

export interface NodeTypeHierarchy {
  [category: string]: NodeTypeCategory;
}

/**
 * Complete Octane node type hierarchy
 * Matches octaneWeb's NodeGraphEditor.js line 1190-1279
 */
export const OCTANE_NODE_TYPES: NodeTypeHierarchy = {
  'Cameras': {
    'NT_CAM_BAKING': { name: 'Baking camera', color: '#8B4513' },
    'NT_CAM_OSL_BAKING': { name: 'OSL baking camera', color: '#8B4513' },
    'NT_CAM_OSL': { name: 'OSL camera', color: '#8B4513' },
    'NT_CAM_PANORAMIC': { name: 'Panoramic camera', color: '#8B4513' },
    'NT_CAM_SIMULATED_LENS': { name: 'Realistic lens camera', color: '#8B4513' },
    'NT_CAM_THINLENS': { name: 'Thin lens camera', color: '#8B4513' },
    'NT_CAM_UNIVERSAL': { name: 'Universal camera', color: '#8B4513' },
  },
  'Displacement': {
    'NT_DISPLACEMENT': { name: 'Displacement', color: '#FF6B35' }
  },
  'Emission': {
    'NT_EMIS_BLACKBODY': { name: 'Blackbody emission', color: '#FFD700' },
    'NT_EMIS_TEXTURE': { name: 'Texture emission', color: '#FFD700' }
  },
  'Environments': {
    'NT_ENV_DAYLIGHT': { name: 'Daylight environment', color: '#87CEEB' },
    'NT_ENV_PLANETARY': { name: 'Planetary environment', color: '#87CEEB' },
    'NT_ENV_TEXTURE': { name: 'Texture environment', color: '#87CEEB' }
  },
  'Geometry': {
    'NT_GEO_MESH': { name: 'Mesh', color: '#32CD32' },
    'NT_GEO_GROUP': { name: 'Group', color: '#32CD32' },
    'NT_GEO_PLACEMENT': { name: 'Placement', color: '#32CD32' },
    'NT_GEO_SCATTER': { name: 'Scatter', color: '#32CD32' },
    'NT_GEO_PLANE': { name: 'Plane', color: '#32CD32' },
    'NT_GEO_VOLUME': { name: 'Volume', color: '#32CD32' },
    'NT_GEO_OBJECT': { name: 'Object', color: '#32CD32' }
  },
  'Input': {
    'NT_BOOL': { name: 'Boolean', color: '#9370DB' },
    'NT_FLOAT': { name: 'Float', color: '#9370DB' },
    'NT_INT': { name: 'Integer', color: '#9370DB' },
    'NT_ENUM': { name: 'Enum', color: '#9370DB' }
  },
  'Kernels': {
    'NT_KERN_PMC': { name: 'PMC kernel', color: '#FF1493' },
    'NT_KERN_DIRECTLIGHTING': { name: 'Direct lighting kernel', color: '#FF1493' },
    'NT_KERN_PATHTRACING': { name: 'Path tracing kernel', color: '#FF1493' },
    'NT_KERN_INFO': { name: 'Info kernel', color: '#FF1493' }
  },
  'Lights': {
    'NT_LIGHT_QUAD': { name: 'Quad light', color: '#FFFF00' },
    'NT_LIGHT_SPHERE': { name: 'Sphere light', color: '#FFFF00' },
    'NT_LIGHT_VOLUME_SPOT': { name: 'Volume spot light', color: '#FFFF00' },
    'NT_LIGHT_DIRECTIONAL': { name: 'Directional light', color: '#FFFF00' },
    'NT_LIGHT_ANALYTIC': { name: 'Analytic light', color: '#FFFF00' }
  },
  'Materials': {
    'NT_MAT_DIFFUSE': { name: 'Diffuse material', color: '#4169E1' },
    'NT_MAT_GLOSSY': { name: 'Glossy material', color: '#4169E1' },
    'NT_MAT_SPECULAR': { name: 'Specular material', color: '#4169E1' },
    'NT_MAT_MIX': { name: 'Mix material', color: '#4169E1' },
    'NT_MAT_PORTAL': { name: 'Portal material', color: '#4169E1' },
    'NT_MAT_UNIVERSAL': { name: 'Universal material', color: '#4169E1' },
    'NT_MAT_METAL': { name: 'Metal material', color: '#4169E1' },
    'NT_MAT_TOON': { name: 'Toon material', color: '#4169E1' }
  },
  'Medium': {
    'NT_MED_ABSORPTION': { name: 'Absorption medium', color: '#8A2BE2' },
    'NT_MED_SCATTERING': { name: 'Scattering medium', color: '#8A2BE2' },
    'NT_MED_VOLUME': { name: 'Volume medium', color: '#8A2BE2' },
    'NT_MED_RANDOMWALK': { name: 'Random walk medium', color: '#8A2BE2' }
  },
  'Textures': {
    'NT_TEX_IMAGE': { name: 'Image texture', color: '#20B2AA' },
    'NT_TEX_FLOATIMAGE': { name: 'Float image texture', color: '#20B2AA' },
    'NT_TEX_ALPHAIMAGE': { name: 'Alpha image texture', color: '#20B2AA' },
    'NT_TEX_RGB': { name: 'RGB texture', color: '#20B2AA' },
    'NT_TEX_FLOAT': { name: 'Float texture', color: '#20B2AA' },
    'NT_TEX_NOISE': { name: 'Noise texture', color: '#20B2AA' },
    'NT_TEX_CHECKS': { name: 'Checks texture', color: '#20B2AA' },
    'NT_TEX_MARBLE': { name: 'Marble texture', color: '#20B2AA' },
    'NT_TEX_TURBULENCE': { name: 'Turbulence texture', color: '#20B2AA' },
    'NT_TEX_MIX': { name: 'Mix texture', color: '#20B2AA' },
    'NT_TEX_MULTIPLY': { name: 'Multiply texture', color: '#20B2AA' },
    'NT_TEX_ADD': { name: 'Add texture', color: '#20B2AA' },
    'NT_TEX_SUBTRACT': { name: 'Subtract texture', color: '#20B2AA' },
    'NT_TEX_GRADIENT': { name: 'Gradient texture', color: '#20B2AA' },
    'NT_TEX_FALLOFF': { name: 'Falloff texture', color: '#20B2AA' }
  },
  'RenderTarget': {
    'NT_RENDERTARGET': { name: 'Render Target', color: '#20B2AA' },
  },
};

/**
 * Get all categories
 */
export function getNodeCategories(): string[] {
  return Object.keys(OCTANE_NODE_TYPES);
}

/**
 * Get node types for a specific category
 */
export function getNodeTypesForCategory(category: string): NodeTypeCategory | undefined {
  return OCTANE_NODE_TYPES[category];
}

/**
 * Get node type info
 */
export function getNodeTypeInfo(nodeType: string): NodeTypeInfo | undefined {
  for (const category of Object.values(OCTANE_NODE_TYPES)) {
    if (category[nodeType]) {
      return category[nodeType];
    }
  }
  return undefined;
}
