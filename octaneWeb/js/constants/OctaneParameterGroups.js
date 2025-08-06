/**
 * Octane Parameter Groups - Exact mapping to match Octane Studio interface
 * Defines parameter groups and their organization for different node types
 */

// Camera node parameter groups (matching Octane Studio exactly)
const CAMERA_PARAMETER_GROUPS = {
    'Physical camera parameters': {
        order: 1,
        expanded: true,
        parameters: [
            { 
                name: 'Orthographic', 
                type: 'boolean', 
                default: false,
                pinName: 'orthographic'
            },
            { 
                name: 'Sensor width', 
                type: 'float', 
                min: 0.1, 
                max: 1000, 
                default: 36.0,
                pinName: 'sensorWidth',
                unit: 'mm'
            },
            { 
                name: 'Focal length', 
                type: 'float', 
                min: 0.1, 
                max: 1000, 
                default: 50.0,
                pinName: 'focalLength',
                unit: 'mm'
            },
            { 
                name: 'F-stop', 
                type: 'float', 
                min: 0.1, 
                max: 64, 
                default: 2.8,
                pinName: 'fstop'
            }
        ]
    },
    
    'Viewing angle': {
        order: 2,
        expanded: true,
        parameters: [
            { 
                name: 'Field of view', 
                type: 'float', 
                min: 0.1, 
                max: 179.9, 
                default: 45.0,
                pinName: 'fieldOfView',
                unit: '°'
            },
            { 
                name: 'Scale of view', 
                type: 'float', 
                min: 0.001, 
                max: 1000, 
                default: 1.0,
                pinName: 'scaleOfView'
            },
            { 
                name: 'Distortion', 
                type: 'float', 
                min: -10, 
                max: 10, 
                default: 0.0,
                pinName: 'distortion'
            },
            { 
                name: 'Lens shift', 
                type: 'vector2', 
                default: [0.0, 0.0],
                pinName: 'lensShift'
            },
            { 
                name: 'Perspective correction', 
                type: 'boolean', 
                default: false,
                pinName: 'perspectiveCorrection'
            },
            { 
                name: 'Pixel aspect ratio', 
                type: 'float', 
                min: 0.1, 
                max: 10, 
                default: 1.0,
                pinName: 'pixelAspectRatio'
            }
        ]
    },
    
    'Clipping': {
        order: 3,
        expanded: true,
        parameters: [
            { 
                name: 'Near clip depth', 
                type: 'float', 
                min: 0.0001, 
                max: 1000, 
                default: 0.001,
                pinName: 'nearClipDepth',
                unit: 'm'
            },
            { 
                name: 'Far clip depth', 
                type: 'float', 
                min: 0.001, 
                max: 100000, 
                default: 1000,
                pinName: 'farClipDepth',
                unit: 'm',
                special: 'infinity' // Can be set to infinity
            }
        ]
    },
    
    'Depth of field': {
        order: 4,
        expanded: true,
        parameters: [
            { 
                name: 'Auto-focus', 
                type: 'boolean', 
                default: false,
                pinName: 'autoFocus'
            },
            { 
                name: 'Focal depth', 
                type: 'float', 
                min: 0.001, 
                max: 1000, 
                default: 1.0,
                pinName: 'focalDepth',
                unit: 'm'
            },
            { 
                name: 'Aperture', 
                type: 'float', 
                min: 0.0, 
                max: 1.0, 
                default: 0.0,
                pinName: 'aperture'
            },
            { 
                name: 'Aperture aspect ratio', 
                type: 'float', 
                min: 0.1, 
                max: 10, 
                default: 1.0,
                pinName: 'apertureAspectRatio'
            },
            { 
                name: 'Aperture edge', 
                type: 'float', 
                min: 0.0, 
                max: 1.0, 
                default: 1.0,
                pinName: 'apertureEdge'
            },
            { 
                name: 'Bokeh side count', 
                type: 'integer', 
                min: 3, 
                max: 16, 
                default: 6,
                pinName: 'bokehSideCount'
            },
            { 
                name: 'Bokeh rotation', 
                type: 'float', 
                min: 0, 
                max: 360, 
                default: 0.0,
                pinName: 'bokehRotation',
                unit: '°'
            },
            { 
                name: 'Bokeh roundedness', 
                type: 'float', 
                min: 0.0, 
                max: 1.0, 
                default: 1.0,
                pinName: 'bokehRoundedness'
            }
        ]
    },
    
    'Position': {
        order: 5,
        expanded: true,
        parameters: [
            { 
                name: 'Position', 
                type: 'vector3', 
                default: [0.0, 0.0, 0.0],
                pinName: 'position',
                unit: 'm'
            },
            { 
                name: 'Target', 
                type: 'vector3', 
                default: [0.0, 0.0, -1.0],
                pinName: 'target',
                unit: 'm'
            },
            { 
                name: 'Up-vector', 
                type: 'vector3', 
                default: [0.0, 1.0, 0.0],
                pinName: 'upVector'
            }
        ]
    },
    
    'Stereo': {
        order: 6,
        expanded: true,
        parameters: [
            { 
                name: 'Stereo output', 
                type: 'enum', 
                options: ['Disabled', 'Left eye', 'Right eye', 'Both eyes'],
                default: 'Disabled',
                pinName: 'stereoOutput'
            },
            { 
                name: 'Stereo mode', 
                type: 'enum', 
                options: ['Off-axis', 'Parallel', 'Toe-in'],
                default: 'Off-axis',
                pinName: 'stereoMode'
            },
            { 
                name: 'Eye distance', 
                type: 'float', 
                min: 0.001, 
                max: 1.0, 
                default: 0.065,
                pinName: 'eyeDistance',
                unit: 'm'
            },
            { 
                name: 'Swap eyes', 
                type: 'boolean', 
                default: false,
                pinName: 'swapEyes'
            },
            { 
                name: 'Left stereo filter', 
                type: 'color', 
                default: [1.0, 0.0, 1.0], // Magenta
                pinName: 'leftStereoFilter'
            },
            { 
                name: 'Right stereo filter', 
                type: 'color', 
                default: [1.0, 0.0, 1.0], // Magenta
                pinName: 'rightStereoFilter'
            }
        ]
    }
};

// Material node parameter groups
const MATERIAL_PARAMETER_GROUPS = {
    'Diffuse': {
        order: 1,
        expanded: true,
        parameters: [
            { 
                name: 'Diffuse', 
                type: 'color', 
                default: [0.8, 0.8, 0.8],
                pinName: 'diffuse'
            },
            { 
                name: 'Opacity', 
                type: 'float', 
                min: 0.0, 
                max: 1.0, 
                default: 1.0,
                pinName: 'opacity'
            }
        ]
    },
    
    'Specular': {
        order: 2,
        expanded: true,
        parameters: [
            { 
                name: 'Specular', 
                type: 'color', 
                default: [1.0, 1.0, 1.0],
                pinName: 'specular'
            },
            { 
                name: 'Roughness', 
                type: 'float', 
                min: 0.0, 
                max: 1.0, 
                default: 0.1,
                pinName: 'roughness'
            },
            { 
                name: 'IOR', 
                type: 'float', 
                min: 1.0, 
                max: 5.0, 
                default: 1.5,
                pinName: 'ior'
            }
        ]
    }
};

// Light node parameter groups
const LIGHT_PARAMETER_GROUPS = {
    'Light': {
        order: 1,
        expanded: true,
        parameters: [
            { 
                name: 'Power', 
                type: 'float', 
                min: 0.0, 
                max: 1000000, 
                default: 100.0,
                pinName: 'power',
                unit: 'W'
            },
            { 
                name: 'Efficacy', 
                type: 'float', 
                min: 0.1, 
                max: 1000, 
                default: 17.0,
                pinName: 'efficacy',
                unit: 'lm/W'
            },
            { 
                name: 'Color', 
                type: 'color', 
                default: [1.0, 1.0, 1.0],
                pinName: 'color'
            }
        ]
    }
};

// Render target parameter groups
const RENDER_TARGET_PARAMETER_GROUPS = {
    'Render settings': {
        order: 1,
        expanded: true,
        parameters: [
            { 
                name: 'Resolution', 
                type: 'vector2i', 
                default: [1920, 1080],
                pinName: 'resolution'
            },
            { 
                name: 'Max samples', 
                type: 'integer', 
                min: 1, 
                max: 100000, 
                default: 1000,
                pinName: 'maxSamples'
            }
        ]
    }
};

// Node type to parameter groups mapping
const NODE_TYPE_PARAMETER_GROUPS = {
    'NT_CAMERA': CAMERA_PARAMETER_GROUPS,
    'NT_THIN_LENS_CAMERA': CAMERA_PARAMETER_GROUPS,
    'NT_MATERIAL': MATERIAL_PARAMETER_GROUPS,
    'NT_LIGHT': LIGHT_PARAMETER_GROUPS,
    'NT_RENDERTARGET': RENDER_TARGET_PARAMETER_GROUPS,
    
    // Fallback for unknown node types
    'default': {
        'Parameters': {
            order: 1,
            expanded: true,
            parameters: []
        }
    }
};

/**
 * Get parameter groups for a specific node type
 */
function getParameterGroupsForNodeType(nodeType) {
    return NODE_TYPE_PARAMETER_GROUPS[nodeType] || NODE_TYPE_PARAMETER_GROUPS['default'];
}

/**
 * Get parameter definition by pin name
 */
function getParameterDefinition(nodeType, pinName) {
    const groups = getParameterGroupsForNodeType(nodeType);
    
    for (const groupName in groups) {
        const group = groups[groupName];
        for (const param of group.parameters) {
            if (param.pinName === pinName) {
                return param;
            }
        }
    }
    
    return null;
}

/**
 * Get all parameter definitions for a node type as a flat array
 */
function getAllParametersForNodeType(nodeType) {
    const groups = getParameterGroupsForNodeType(nodeType);
    const allParams = [];
    
    for (const groupName in groups) {
        const group = groups[groupName];
        for (const param of group.parameters) {
            allParams.push({
                ...param,
                groupName: groupName,
                groupOrder: group.order
            });
        }
    }
    
    return allParams.sort((a, b) => a.groupOrder - b.groupOrder);
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        CAMERA_PARAMETER_GROUPS,
        MATERIAL_PARAMETER_GROUPS,
        LIGHT_PARAMETER_GROUPS,
        RENDER_TARGET_PARAMETER_GROUPS,
        NODE_TYPE_PARAMETER_GROUPS,
        getParameterGroupsForNodeType,
        getParameterDefinition,
        getAllParametersForNodeType
    };
} else {
    // Browser environment
    window.OctaneParameterGroups = {
        CAMERA_PARAMETER_GROUPS,
        MATERIAL_PARAMETER_GROUPS,
        LIGHT_PARAMETER_GROUPS,
        RENDER_TARGET_PARAMETER_GROUPS,
        NODE_TYPE_PARAMETER_GROUPS,
        getParameterGroupsForNodeType,
        getParameterDefinition,
        getAllParametersForNodeType
    };
}