/**
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
};

// ApiItemPtr.PointerType enum values from common.proto
window.OctaneTypes.ApiItemPointerType = {
    ApiItem: 0,
    ApiNode: 1,
    ApiNodeGraph: 2,
    ApiRootNodeGraph: 3,
    ApiReferenceGraph: 4,
};

// ApiNodeGraphPtr.PointerType enum values from common.proto
window.OctaneTypes.ApiNodeGraphPointerType = {
    ApiNodeGraph: 0,
    ApiRootNodeGraph: 1,
    ApiReferenceGraph: 2,
};

// Commonly used type combinations for convenience
window.OctaneTypes.CommonTypes = {
    // For ObjectPtr requests (uses ObjectRef.ObjectType)
    NODE: window.OctaneTypes.ObjectType.ApiNode,                    // 17
    ROOT_NODE_GRAPH: window.OctaneTypes.ObjectType.ApiRootNodeGraph, // 18
    NODE_GRAPH: window.OctaneTypes.ObjectType.ApiNodeGraph,         // 20
    
    // For ApiItemPtr requests (uses ApiItemPtr.PointerType)
    ITEM_NODE: window.OctaneTypes.ApiItemPointerType.ApiNode,       // 1
    ITEM_NODE_GRAPH: window.OctaneTypes.ApiItemPointerType.ApiNodeGraph, // 2
    ITEM_ROOT_NODE_GRAPH: window.OctaneTypes.ApiItemPointerType.ApiRootNodeGraph, // 3
};

// Helper functions for creating properly typed object pointers
window.OctaneTypes.createObjectPtr = (handle, type) => ({
    handle: handle,
    type: type
});

window.OctaneTypes.createApiItemPtr = (handle, pointerType) => ({
    handle: handle,
    type: pointerType
});

window.OctaneTypes.createApiNodeGraphPtr = (handle, pointerType) => ({
    handle: handle,
    pointer_type: pointerType
});

// Validation helpers
window.OctaneTypes.isValidObjectType = (type) => {
    return Object.values(window.OctaneTypes.ObjectType).includes(type);
};

window.OctaneTypes.isValidApiItemPointerType = (type) => {
    return Object.values(window.OctaneTypes.ApiItemPointerType).includes(type);
};

window.OctaneTypes.isValidApiNodeGraphPointerType = (type) => {
    return Object.values(window.OctaneTypes.ApiNodeGraphPointerType).includes(type);
};

// Type name lookup for debugging
window.OctaneTypes.getObjectTypeName = (type) => {
    const entry = Object.entries(window.OctaneTypes.ObjectType).find(([name, value]) => value === type);
    return entry ? entry[0] : `Unknown(${type})`;
};

window.OctaneTypes.getApiItemPointerTypeName = (type) => {
    const entry = Object.entries(window.OctaneTypes.ApiItemPointerType).find(([name, value]) => value === type);
    return entry ? entry[0] : `Unknown(${type})`;
};

window.OctaneTypes.getApiNodeGraphPointerTypeName = (type) => {
    const entry = Object.entries(window.OctaneTypes.ApiNodeGraphPointerType).find(([name, value]) => value === type);
    return entry ? entry[0] : `Unknown(${type})`;
};

// Log successful loading
console.log('✅ OctaneTypes constants loaded successfully (AUTO-GENERATED)');
console.log('📋 Available types:', Object.keys(window.OctaneTypes.ObjectType).length, 'ObjectTypes,', 
           Object.keys(window.OctaneTypes.ApiItemPointerType).length, 'ApiItemPointerTypes,',
           Object.keys(window.OctaneTypes.ApiNodeGraphPointerType).length, 'ApiNodeGraphPointerTypes');
