/*
 * Octane gRPC Type Constants
 * 
 * AUTO-GENERATED from protobuf files - DO NOT EDIT MANUALLY
 * Generated from: octaneProxy/generated/common_pb2.py
 * 
 * This eliminates hardcoded type values in ObjectPtr requests and ensures
 * consistency with the actual protobuf definitions.
 */

// Make constants available globally
window.OctaneTypes = window.OctaneTypes || {};

/*
window.OctaneTypes.AttributeType = {
    AT_UNKNOWN: 0,

    AT_BOOL: 1,
    AT_INT: 2,
    AT_INT2: 3,
    AT_INT3: 4,
    AT_INT4: 5,
    AT_LONG: 14,
    AT_LONG2: 15,
    AT_FLOAT: 6,
    AT_FLOAT2: 7,
    AT_FLOAT3: 8,
    AT_FLOAT4: 9,
    AT_STRING: 10,
    AT_FILENAME: 11,
    AT_BYTE: 12,
    AT_MATRIX: 13,
};
*/

window.OctaneTypes.AttributeType = {
    AT_UNKNOWN:0,
    AT_BOOL:1,
    AT_BYTE:2,
    AT_INT:3,
    AT_INT2:4,
    AT_INT3:5,
    AT_INT4:6,
    AT_LONG:7,
    AT_LONG2:8,
    AT_FLOAT:9,
    AT_FLOAT2:90,
    AT_FLOAT3:11,
    AT_FLOAT4:12,
    AT_MATRIX:13,
    AT_STRING:14,
};

window.OctaneTypes.NodePinType = {
    PT_UNKNOWN: 0,
    PT_BOOL: 1,
    PT_FLOAT: 2,
    PT_INT: 3,
    PT_TRANSFORM: 4,
    PT_TEXTURE: 5,
    PT_EMISSION: 6,
    PT_MATERIAL: 7,
    PT_CAMERA: 8,
    PT_ENVIRONMENT: 9,
    PT_IMAGER: 10,
    PT_KERNEL: 11,
    PT_GEOMETRY: 12,
    PT_MEDIUM: 13,
    PT_PHASEFUNCTION: 14,
    PT_FILM_SETTINGS: 15,
    PT_ENUM: 16,
    PT_OBJECTLAYER: 17,
    PT_POSTPROCESSING: 18,
    PT_RENDERTARGET: 19,
    PT_WORK_PANE: 20,
    PT_PROJECTION: 21,
    PT_DISPLACEMENT: 22,
    PT_STRING: 23,
    PT_RENDER_PASSES: 24,
    PT_RENDER_LAYER: 25,
    PT_VOLUME_RAMP: 26,
    PT_ANIMATION_SETTINGS: 27,
    PT_LUT: 28,
    PT_RENDER_JOB: 29,
    PT_TOON_RAMP: 30,
    PT_BIT_MASK: 31,
    PT_ROUND_EDGES: 32,
    PT_MATERIAL_LAYER: 33,
    PT_OCIO_VIEW: 34,
    PT_OCIO_LOOK: 35,
    PT_OCIO_COLOR_SPACE: 36,
    PT_OUTPUT_AOV_GROUP: 37,
    PT_OUTPUT_AOV: 38,
    PT_TEX_COMPOSITE_LAYER: 39,
    PT_OUTPUT_AOV_LAYER: 40,
    PT_BLENDING_SETTINGS: 44,
    PT_POST_VOLUME: 45,
    PT_TRACE_SET_VISIBILITY_RULE_GROUP: 46,
    PT_TRACE_SET_VISIBILITY_RULE: 47,
};

window.OctaneTypes.AttributeId = {
    A_VALUE: 185,
};

// ObjectRef.ObjectType enum values from common.proto
window.OctaneTypes.ObjectType = {
    ApiFileName: 0,
    ApiGeometryExporter: 1,
    ApiGuiComponent: 2,
    MetaData: 3,
    ApiImageBuffer: 4,
    ImageType: 5,
    LayerInfo: 6,
    ApiAttributeInfo: 7,
    ApiOcioConfig: 8,
    ApiOctaneModuleInfo: 9,
    ApiOutputColorSpaceInfo: 10,
    ApiSharedSurface: 11,
    ImageExportSettings: 12,
    RenderPassExport: 13,
    RenderResultStatistics: 14,
    ReferencePackageExportSettings: 15,
    ApiItem: 16,
    ApiItem: 16,
    ApiItem: 16,
    ApiNode: 17,
    ApiRootNodeGraph: 18,
    ApiReferenceGraph: 19,
    ApiNodeGraph: 20,
    AnimationTimeTransform: 21,
    ApiAnimationTimeTransform: 22,
    ApiLinearTimeTransform: 23,
    SocketAddress: 24,
    TimeSpanT: 25,
    FrameRangeT: 26,
    ApiCustomCurveEditorController: 27,
    DBCategoryArray: 28,
    DBMaterialArray: 29,
    ImageInfo: 30,
    ApiItemArray: 31,
    Package: 32,
    Category: 33,
    ApiNodeArray: 34,
    ApiOcioConfigLoader: 35,
    ApiOcioContextManager: 36,
    ApiPackage: 37,
    ApiRenderImage: 38,
    ApiSceneExporter: 39,
    VdbGridInfo: 40,
    VdbInfo: 41,
    ApiMainWindow: 42,
    ApiProjectWorkspace: 43,
    ApiNodePinInfo: 44,
    ApiCompatibilityModeInfo: 45,
    ApiCompatibilityModeInfoSet: 46,
    ApiNodeInspector: 47,
    ApiRenderView: 48,
    NetRenderStatus: 49,
    VdbGridSampler: 50,
    ApiSceneOutliner: 51,
    ApiNodeGraphEditor: 52,
    ApiLocalDB_Category: 53,
    ApiLocalDB_Package: 54,
    ApiDBMaterialManager_DBCategoryArray: 55,
    ApiDBMaterialManager_DBMaterialArray: 56,
    ApiBinaryTable: 57,
    ApiBinaryGroup: 58,
    ApiLock: 59,
    ApiWorkPaneModuleInfo: 60,
    ApiNodeGraphModuleInfo: 61,
    ApiCommandModuleInfo: 62,
    ApiThread: 63,
    ApiModuleNodeGraph: 64,
    ApiSelectionManager: 65,
    ApiSelectionManager_PinSelection: 66,
    ApiCheckBox: 67,
    ApiCollapsiblePanelStack: 68,
    ApiColorSwatch: 69,
    ApiComboBoxItem: 70,
    ApiComboBox: 71,
    ApiFileChooser: 72,
    ApiGridLayout: 73,
    ApiLabel: 74,
    ApiModalDialog: 75,
    ApiMouseListener: 76,
    ApiNumericBox: 77,
    ApiProgressBar: 78,
    ApiTable: 79,
    ApiTextButton: 80,
    ApiTextEditor: 81,
    ApiTitleComponent: 82,
    ApiWindow: 83,
    ApiImage: 84,
    ApiImageComponent: 85,
    ApiPinSelection: 86,
    ApiMouseEvent: 87,
    ApiRenderEngine_PickIntersection: 88,
    ApiCustomCurveEditorController_Drawer: 89,
    ApiCustomCurveEditorController_Listener: 90,
    ApiTileGridLoader: 91,
    ApiGaussianSplatCloudNode: 92,

    ApiNodePinInfoEx: 44,
};

// Helper functions for creating properly typed object pointers
window.OctaneTypes.createObjectPtr = (handle, type) => ({
    handle: handle,
    type: type
});

// Type name lookup for debugging
window.OctaneTypes.getObjectTypeName = (type) => {
    const entry = Object.entries(window.OctaneTypes.ObjectType).find(([name, value]) => value === type);
    return entry ? entry[0] : `Unknown(${type})`;
};


// Log successful loading
console.log('OctaneTypes constants loaded successfully (AUTO-GENERATED)');
