#!/usr/bin/env node
/**
 * Extract all Octane node types from octaneids.proto and generate
 * a complete NodeTypes.ts file with proper categorization
 */

const fs = require('fs');
const path = require('path');

// Read octaneids.proto
const protoPath = path.join(__dirname, '../../sdk/src/api/grpc/protodef/octaneids.proto');
const protoContent = fs.readFileSync(protoPath, 'utf-8');

// Extract NodeType enum
const nodeTypeMatch = protoContent.match(/enum NodeType\s*\{([^}]+)\}/s);
if (!nodeTypeMatch) {
  console.error('Could not find NodeType enum in octaneids.proto');
  process.exit(1);
}

const nodeTypeEnum = nodeTypeMatch[1];

// Parse node types (skip deprecated ones starting with _)
const nodeTypes = [];
const lines = nodeTypeEnum.split('\n');
for (const line of lines) {
  const match = line.match(/^\s*(NT_[A-Z_0-9]+)\s*=\s*\d+/);
  if (match && !match[1].startsWith('_NT_')) {
    nodeTypes.push(match[1]);
  }
}

console.log(`Found ${nodeTypes.length} node types`);

// Categorization map based on NT_ prefix
const categoryMap = {
  'NT_CAM_': 'Cameras',
  'NT_DISPLACEMENT': 'Displacement',
  'NT_EMIS_': 'Emission',
  'NT_ENV_': 'Environments',
  'NT_GEO_': 'Geometry',
  'NT_BOOL': 'Input',
  'NT_FLOAT': 'Input',
  'NT_INT': 'Input',
  'NT_ENUM': 'Input',
  'NT_STRING': 'Input',
  'NT_FILE': 'Input',
  'NT_DIRECTORY': 'Input',
  'NT_KERN_': 'Kernels',
  'NT_LIGHT_': 'Lights',
  'NT_TOON_POINT_LIGHT': 'Lights',
  'NT_TOON_DIRECTIONAL_LIGHT': 'Lights',
  'NT_MAT_': 'Materials',
  'NT_MED_': 'Medium',
  'NT_PHASE_': 'Phase Functions',
  'NT_PROJ_': 'Projection',
  'NT_SCATTER_': 'Scatter',
  'NT_TEX_': 'Textures',
  'NT_TRANSFORM_': 'Transform',
  'NT_SUN_DIRECTION': 'Transform',
  'NT_RENDERTARGET': 'Render Target',
  'NT_RENDER_': 'Render',
  'NT_AOV_': 'AOVs',
  'NT_OUTPUT_AOV': 'Output AOVs',
  'NT_COMPOSITE_AOV': 'Output AOVs',
  'NT_POSTPROCESSING': 'Post Processing',
  'NT_POST_': 'Post Processing',
  'NT_IMAGER_': 'Imager',
  'NT_OBJECTLAYER': 'Object Layer',
  'NT_VERTEX_DISPLACEMENT': 'Displacement',
  'NT_VOLUME_RAMP': 'Volume Ramp',
  'NT_ANIMATION_SETTINGS': 'Animation',
  'NT_FILM_SETTINGS': 'Film Settings',
  'NT_LUT_': 'LUT',
  'NT_RENDER_JOB_': 'Render Jobs',
  'NT_TOON_RAMP': 'Toon Ramp',
  'NT_BIT_MASK': 'Masks',
  'NT_ROUND_EDGES': 'Materials',
  'NT_OCIO_': 'Color Management',
  'NT_BLENDING_SETTINGS': 'Blending',
  'NT_TRACE_SET_': 'Trace Sets',
  'NT_METADATA': 'Metadata',
  'NT_ANNOTATION': 'Annotation',
  'NT_IN_': 'Graph Inputs',
  'NT_RNDR_VERSION': 'System',
  'NT_SWITCH_': 'Switch Nodes',
};

// Category colors (matching Octane's color scheme)
const categoryColors = {
  'Cameras': '#8B4513',
  'Displacement': '#FF6B35',
  'Emission': '#FFD700',
  'Environments': '#87CEEB',
  'Geometry': '#32CD32',
  'Input': '#9370DB',
  'Kernels': '#FF1493',
  'Lights': '#FFFF00',
  'Materials': '#4169E1',
  'Medium': '#8A2BE2',
  'Phase Functions': '#BA55D3',
  'Projection': '#FF8C00',
  'Scatter': '#98FB98',
  'Textures': '#20B2AA',
  'Transform': '#DC143C',
  'Render Target': '#FFA07A',
  'Render': '#FFA07A',
  'AOVs': '#FF69B4',
  'Output AOVs': '#FF1493',
  'Post Processing': '#DDA0DD',
  'Imager': '#F0E68C',
  'Object Layer': '#7B68EE',
  'Volume Ramp': '#8A2BE2',
  'Animation': '#FFB6C1',
  'Film Settings': '#FFA500',
  'LUT': '#FFDAB9',
  'Render Jobs': '#CD853F',
  'Toon Ramp': '#FF6347',
  'Masks': '#808080',
  'Color Management': '#E6E6FA',
  'Blending': '#F5DEB3',
  'Trace Sets': '#D8BFD8',
  'Metadata': '#A9A9A9',
  'Annotation': '#D3D3D3',
  'Graph Inputs': '#9370DB',
  'System': '#696969',
  'Switch Nodes': '#BC8F8F',
};

// Function to determine category for a node type
function getCategory(nodeType) {
  // Try exact match first
  if (categoryMap[nodeType]) {
    return categoryMap[nodeType];
  }
  
  // Try prefix match
  for (const [prefix, category] of Object.entries(categoryMap)) {
    if (nodeType.startsWith(prefix)) {
      return category;
    }
  }
  
  return 'Other';
}

// Function to convert NT_SOMETHING_NAME to "Something Name"
function toHumanReadable(nodeType) {
  return nodeType
    .substring(3) // Remove NT_
    .split('_')
    .map(word => word.charAt(0) + word.slice(1).toLowerCase())
    .join(' ');
}

// Group node types by category
const categorized = {};
for (const nodeType of nodeTypes) {
  const category = getCategory(nodeType);
  if (!categorized[category]) {
    categorized[category] = {};
  }
  
  const color = categoryColors[category] || '#808080';
  categorized[category][nodeType] = {
    name: toHumanReadable(nodeType),
    color: color
  };
}

// Sort categories alphabetically
const sortedCategories = Object.keys(categorized).sort();

// Generate TypeScript file
let tsContent = `/**
 * Complete Octane Node Type Definitions
 * Auto-generated from octaneids.proto
 * 
 * Total nodes: ${nodeTypes.length}
 * Categories: ${sortedCategories.length}
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
 * Complete Octane node type hierarchy with all ${nodeTypes.length} node types
 */
export const OCTANE_NODE_TYPES: NodeTypeHierarchy = {\n`;

for (const category of sortedCategories) {
  tsContent += `  '${category}': {\n`;
  const nodes = categorized[category];
  const nodeKeys = Object.keys(nodes).sort();
  for (const nodeType of nodeKeys) {
    const info = nodes[nodeType];
    tsContent += `    '${nodeType}': { name: '${info.name}', color: '${info.color}' },\n`;
  }
  tsContent += `  },\n`;
}

tsContent += `};

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

/**
 * Get all node types as a flat list
 */
export function getAllNodeTypes(): string[] {
  const allTypes: string[] = [];
  for (const category of Object.values(OCTANE_NODE_TYPES)) {
    allTypes.push(...Object.keys(category));
  }
  return allTypes.sort();
}
`;

// Write to file
const outputPath = path.join(__dirname, '../client/src/constants/NodeTypes.ts');
fs.writeFileSync(outputPath, tsContent);

console.log(`✅ Generated NodeTypes.ts with ${nodeTypes.length} node types in ${sortedCategories.length} categories`);
console.log(`📝 Output: ${outputPath}`);
console.log(`\n📊 Categories:`);
for (const category of sortedCategories) {
  const count = Object.keys(categorized[category]).length;
  console.log(`  - ${category}: ${count} nodes`);
}
