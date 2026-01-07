/**
 * Octane gRPC Type Constants
 * 
 * Converted from octaneWeb/js/constants/OctaneTypes.js
 * These match the protobuf ObjectRef.ObjectType enum values from common.proto
 */

export const ObjectType = {
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
  ApiNodePinInfoEx: 44,
} as const;

export type ObjectTypeName = keyof typeof ObjectType;

/**
 * Helper to create properly typed object pointer
 */
export function createObjectPtr(handle: string, type: number) {
  return {
    handle,
    type
  };
}

/**
 * Get ObjectType value for a service name
 * Used to automatically wrap handles in objectPtr structure
 */
export function getObjectTypeForService(serviceName: string): number | undefined {
  return ObjectType[serviceName as ObjectTypeName];
}

/**
 * Get type name from type value (for debugging)
 */
export function getObjectTypeName(type: number): string {
  const entry = Object.entries(ObjectType).find(([_name, value]) => value === type);
  return entry ? entry[0] : `Unknown(${type})`;
}

/**
 * Attribute IDs for node attributes
 * These match the AttributeId enum from Octane
 */
export const AttributeId = {
  A_VALUE: 185,
  // Add more as needed
} as const;

/**
 * Attribute types for node values
 * These match the AttrType enum from Octane
 * Expanded from octaneWeb's AttributeType mapping
 */
export const AttrType = {
  AT_UNKNOWN: 0,
  AT_BOOL: 1,
  AT_INT: 2,
  AT_INT2: 3,
  AT_INT3: 4,
  AT_INT4: 5,
  AT_FLOAT: 6,
  AT_FLOAT2: 7,
  AT_FLOAT3: 8,
  AT_FLOAT4: 9,
  AT_STRING: 10,
  AT_FILENAME: 11,
  AT_BYTE: 12,
  AT_MATRIX: 13,
  AT_LONG: 14,
  AT_LONG2: 15,
} as const;


