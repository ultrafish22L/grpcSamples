// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octaneenums.h"
#include "octanetypes.h"
#include "octaneids.h"



namespace Octane
{

class ApiImage;
struct ApiAttributeInfo;
class  ApiItem;
class ApiNode;
struct ApiNodeGraphInfo;
struct ApiNodeInfo;
struct ApiNodePinInfo;
struct ApiRenderPassInfo;

//--------------------------------------------------------------------------------------------------
/// Query information from the API.
class OCTANEAPI_DECL ApiInfo 
{
    OCTANEAPI_NO_COPY(ApiInfo);

public:

    //--- General System Information ---

    /// Returns the version of the Octane DLL. You can verify that the correct DLL is loaded by
    /// matching the DLL version against OCTANE_VERSION (from octaneversion.h).
    static int octaneVersion();

    /// Returns the full name of the Octane DLL build.
    static const char* octaneName();

    /// Returns TRUE if the DLL is a demo version
    static bool isDemoVersion();

    /// Returns TRUE if the DLL is a subscription version.
    static bool isSubscriptionVersion();

    /// Returns -1 for builds with no tiers or the build tier index (1-3).
    /// @note Currently only the subscription build supports tiers  
    static int tierIdx();

    /// Returns a string describing the OS version.
    /// (e.g. "Windows Vista 64-bit")
    static const char* osVersionInfo();

    ///  Returns the driver version string (NVIDIA only)
    static const char* driverVersionInfo();

    /// Returns info about the cpu(s).
    ///
    /// @param[out]  cpuVendor
    ///     Pointer to a pointer that will be set to the C string of the CPU vendor name (e.g.
    ///     "GenuineIntel"). Can be NULL.
    ///     NOTE: This string is owned by the API, don't delete it!
    /// @param[out]  cpuModel
    ///     Pointer to a pointer that will be set to the C string of the CPU model name (e.g.
    ///     "Intel(R) Core(TM) i7-3820 CPU @ 3.60GHz"). Can be NULL.
    ///     NOTE: This string is owned by the API, don't delete it!
    /// @param[out]  clockSpeedMhz
    ///     Receives the CPU clock speed in MHz.
    /// @param[out]  nbCores
    ///     Receives the number of physical cpu cores in the system.
    static void cpuInfo(
        const char * * cpuVendor,
        const char * * cpuModel,
        uint32_t &     clockSpeedMhz,
        uint32_t &     nbCores);

    /// Returns the absolute path of the texture cache folder
    ///
    /// @return
    ///     The absolute path of the texture cache folder.
    ///     NOTE: you don't need to release the returned string
    static const char* texCacheFolder();

    //--- Node System ---

    /// Returns a sorted list of all attribute types.
    ///
    /// @param[out] attributeTypes
    ///     Array of attribute types. This array is owned by the API.
    /// @param[out] size
    ///     Size of the array.
    static void getAttributeTypes(
        const AttributeType * & attributeTypes,
        size_t &                size);

    /// Returns a sorted list of all pin types.
    ///
    /// @param[out] pinTypes
    ///     Array of pin types. This array is owned by the API.
    /// @param[out] size
    ///     Size of the array.
    static void getPinTypes(
        const NodePinType * & pinTypes,
        size_t &              size);

    /// Returns a sorted list of all graph types.
    ///
    /// @param[out] graphTypes
    ///     Array of graph types. This array is owned by the API.
    /// @param[out] size
    ///     Size of the array.
    static void getGraphTypes(
        const NodeGraphType * & graphTypes,
        size_t &                size);

    /// Returns a sorted list of all node types.
    ///
    /// @param[out] nodesTypes
    ///     Array of node types. This array is owned by the API.
    /// @param[out] size
    ///     Size of the array.
    static void getNodeTypes(
        const NodeType * & nodesTypes,
        size_t &           size);

    /// Returns info for this particular node type or NULL if no info is available.
    static const ApiNodeInfo* nodeInfo(
        const NodeType type);

    /// Returns info for this particular graph type or NULL if no info is available.
    static const ApiNodeGraphInfo* graphInfo(
        NodeGraphType type);

    /// Returns an image containing the icon of a given node type
    /// Note: Octane is the owner of the returned image and @ref ApiImage::destroy() should not be called.
    static const ApiImage* nodeIconImage(
        const NodeType nodeType);

    /// Returns an image containing the icon of a given graph type
    /// Note: Octane is the owner of the returned image and @ref ApiImage::destroy() should not be called.
    static const ApiImage* graphIconImage(
        const NodeGraphType nodeGraphType);

    /// Returns info for an attribute available on nodes of the given type or NULL if no info for the
    /// attribute is available.
    /// @note attrId is the ID of the attribute, eg Octane::A_SHADER_CODE
    static const ApiAttributeInfo* attributeInfo(
        NodeType    type,
        AttributeId attrId);

    /// Returns info for an attribute available on nodes of the given type or NULL
    /// if no info for the attribute is available. 
    /// @note attrIx is the index of the attribute in the infos of the node, not attribute ID.
    static const ApiAttributeInfo* attributeInfo(
        NodeType type,
        uint32_t attrIx);

    /// Returns info for an attribute available on graphs of the given type or NULL
    /// if no info for the attribute is available.
    /// @note attrIx is the index of the attribute in the infos of the node, not attribute ID.
    static const ApiAttributeInfo* attributeInfo(
        NodeGraphType type,
        uint32_t      attrIx);

    /// Returns info for a pin available on a node or NULL if there's no such pin.
    static const ApiNodePinInfo* nodePinInfo(
        NodeType nodeType,
        uint32_t pinIx);

    /// Returns the name for an attribute type, e.g. "AT_BOOL" for AT_BOOL.
    static const char* getAttributeTypeName(
        AttributeType type);

    /// Returns the name for a node pin type, e.g. "PT_BOOL" for PT_BOOL.
    static const char* getPinTypeName(
        NodePinType type);

    /// Returns the color for a node pin type (ARGB encoded).
    static uint32_t getPinTypeColor(
        NodePinType type);

    /// Returns the name for a node graph type, e.g. "GT_STANDARD" for GT_STANDARD.
    static const char* getGraphTypeName(
        NodeGraphType type);

    /// Returns the name for a node type, e.g. "NT_TEX_MIX" for NT_TEX_MIX.
    static const char* getNodeTypeName(
        NodeType type);

    /// Returns the type name of an api item.
    static const char* getItemTypeName(
        const ApiItem & item);

    /// Returns the name for an attribute ID, e.g. "value" for A_VALUE.
    static const char* getAttributeName(
        AttributeId id);

    /// Returns the ID for an attribute name, e.g. A_VALUE for "value".
    static AttributeId getAttributeId(
        const char * attributeName);

    /// Returns the enum name for an attribute ID, e.g. "A_VALUE" for A_VALUE.
    static const char* getAttributeIdName(
        AttributeId id);

    /// Returns the enum name for an attribute name, e.g. "A_VALUE" for "value".
    static const char* getAttributeIdName(
        const char * attributeName);

    /// Returns the name for a pin ID, e.g. "diffuse" for P_DIFFUSE.
    static const char* getPinName(
        PinId id);

    /// Returns the ID for a pin name, e.g. P_DIFFUSE for "diffuse".
    static PinId getPinId(
        const char * pinName);

    /// Returns the enum name for a pin ID, e.g. "P_DIFFUSE" for P_DIFFUSE.
    static const char* getPinIdName(
        PinId id);

    /// Returns the enum name for a pin name, e.g. "P_DIFFUSE" for "diffuse".
    static const char* getPinIdName(
        const char * pinName);
    
    /// Get the string name of an OSL value type of a given texture value type enum
    static const char* getTextureValueTypeName(
        TextureValueType textureValueType);

    /// Get the OSL value type for a given OSL type name
    static TextureValueType getTextureValueTypeForOslType(
        const char* oslType);

    /// Returns a list of graphs compatible with the output type and a list
    /// of nodes compatible with the output type.
    ///
    /// @param[in]  outputType
    ///     node/graph output type.
    /// @param[out] compatGraphs
    ///     Array of graph types compatible with the provided output type. Will
    ///     be NULL if there are no compatible graphs. This array is owned by the API.
    /// @param[out] compatGraphsSize
    ///     Size of the compatible graphs array.
    /// @param[out] compatNodes
    ///     Array of node types compatible with the provided output type. Will be
    ///     NULL if there are node compatible nodes. This array is owned by the API.
    /// @param[out] compatNodesSize
    ///     Size of the compatible nodes array.
    static void getCompatibleTypes(
        NodePinType       outType,
        NodeGraphType * & compatGraphs,
        size_t &          compatGraphsSize,
        NodeType * &      compatNodes,
        size_t &          compatNodesSize);

    ///--- Render Passes ---

    /// Returns the information related to a render pass given its id
    static const ApiRenderPassInfo& renderPassInfo(
        RenderPassId id);

    /// Returns the blending mode name of a render pass
    static const char* renderPassBlendingModeName(
        BlendingModeId id);

    /// Returns an array with all the available render pass ids. Usefull for iterating
    /// over all render pass ids in Octane.
    ///
    /// @param[out] length
    ///     Length of the returned array.
    /// @return
    ///     Array of all available render pass ids. This array doesn't change at runtime.
    ///     Don't free up this array it's a static array owned by the API.
    static const RenderPassId* getAllRenderPassIds(
        size_t & length);

    /// Returns the @ref RenderPassId for the provided render AOV node or @ref RENDER_PASS_UNKNOWN
    /// if it's not a valid render AOV node.
    static RenderPassId getRenderPassIdFromRenderAovNode(
        const ApiNode & node);

    /// Returns the @ref ApiRenderPassInfo corresponding to the provided render AOV node. If @ref node
    /// is not a valid render AOV node, the returned @ref ApiRenderPassInfo is for @ref RENDER_PASS_UNKNOWN.
    static const ApiRenderPassInfo & getRenderAovInfoFromRenderAovNode(
        const ApiNode & node);

    /// Returns the name of the render pass associated with the id.
    /// @deprecated Use #renderPassInfo instead
    static OCTANE_DEPRECATED const char* renderPassName(
        RenderPassId id);

    /// Returns the short (~ abbreviated) name of a render pass.
    /// @deprecated Use #renderPassInfo instead
    static OCTANE_DEPRECATED const char* renderPassShortName(
        RenderPassId id);

    /// Returns the pin id for a render pass.
    /// @deprecated Use #renderPassInfo instead
    static OCTANE_DEPRECATED PinId renderPassIdToPinId(
        RenderPassId id);

    /// Returns the group name of a render pass
    /// @deprecated USe RenderPassInfo::mCategory instead.
    static OCTANE_DEPRECATED const char* renderPassGroupName(
        RenderPassGroupId id);

    /// Returns the render pass id for a pin id.
    /// @deprecated With the introduction of render AOV nodes.
    static OCTANE_DEPRECATED RenderPassId pinIdToRenderPassId(
        PinId pinId);

    /// Finds the bool pin used to enable/disable the render pass. Returns FALSE
    /// if no pin is found for the render pass.
    /// @deprecated With the introduction of render AOV nodes.
    static OCTANE_DEPRECATED bool findPinIdForRenderPassId(
        RenderPassId renderPassId,
        PinId &      pinId);

    /// Finds the render pass you can enable/disable with the passed in pin id. Returns
    /// FALSE if this pin isn't used to enable/disable a render pass.
    /// @deprecated With the introduction of render AOV nodes.
    static OCTANE_DEPRECATED bool findRenderPassIdForPinId(
        PinId          pinId,
        RenderPassId & renderPassId);
};

} // namespace Octane
