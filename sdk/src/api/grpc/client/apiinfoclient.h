// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"
class ApiNodePinInfoProxy;
class ApiItemProxy;
class ApiNodeProxy;
class ApiImageProxy;
class ApiRenderPassInfoProxy;
struct ApiNodeInfoProxy;


#include "apiinfo.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiInfo
class ApiInfoProxy : public GRPCBase
{
public:
    /// Returns the version of the Octane DLL. You can verify that the correct DLL is loaded by
    /// matching the DLL version against OCTANE_VERSION (from octaneversion.h).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static int octaneVersion();

    /// Returns the full name of the Octane DLL build.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string octaneName();

    /// Returns TRUE if the DLL is a demo version
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isDemoVersion();

    /// Returns TRUE if the DLL is a subscription version.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isSubscriptionVersion();

    /// Returns -1 for builds with no tiers or the build tier index (1-3).
    /// @note Currently only the subscription build supports tiers
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static int tierIdx();

    /// Returns a string describing the OS version.
    /// (e.g. "Windows Vista 64-bit")
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string osVersionInfo();

    ///  Returns the driver version string (NVIDIA only)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string driverVersionInfo();

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void cpuInfo(
            std::string &                             cpuVendor,
            std::string &                             cpuModel,
            uint32_t &                                clockSpeedMhz,
            uint32_t &                                nbCores
            );

    /// Returns the absolute path of the texture cache folder
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The absolute path of the texture cache folder.
    ///     NOTE: you don't need to release the returned string
    static std::string texCacheFolder();

    /// Returns a sorted list of all attribute types.
    ///
    /// @param[out] attributeTypes
    ///     Array of attribute types. This array is owned by the API.
    /// @param[out] size
    ///     Size of the array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getAttributeTypes(
            std::vector<Octane::AttributeType> &      attributeTypes,
            size_t &                                  size
            );

    /// Returns a sorted list of all pin types.
    ///
    /// @param[out] pinTypes
    ///     Array of pin types. This array is owned by the API.
    /// @param[out] size
    ///     Size of the array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getPinTypes(
            std::vector<Octane::NodePinType> &        pinTypes,
            size_t &                                  size
            );

    /// Returns a sorted list of all graph types.
    ///
    /// @param[out] graphTypes
    ///     Array of graph types. This array is owned by the API.
    /// @param[out] size
    ///     Size of the array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getGraphTypes(
            std::vector<Octane::NodeGraphType> &      graphTypes,
            size_t &                                  size
            );

    /// Returns a sorted list of all node types.
    ///
    /// @param[out] nodesTypes
    ///     Array of node types. This array is owned by the API.
    /// @param[out] size
    ///     Size of the array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getNodeTypes(
            std::vector<Octane::NodeType> &           nodesTypes,
            size_t &                                  size
            );

    /// Returns info for this particular node type or NULL if no info is available.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static const ApiNodeInfoProxy nodeInfo(
            const Octane::NodeType   type
            );

    /// Returns info for this particular graph type or NULL if no info is available.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static const Octane::ApiNodeGraphInfo graphInfo(
            Octane::NodeGraphType   type
            );

    /// Returns an image containing the icon of a given node type
    /// Note: Octane is the owner of the returned image and @ref ApiImage::destroy() should not be called.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiImageProxy nodeIconImage(
            const Octane::NodeType   nodeType
            );

    /// Returns an image containing the icon of a given graph type
    /// Note: Octane is the owner of the returned image and @ref ApiImage::destroy() should not be called.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiImageProxy graphIconImage(
            const Octane::NodeGraphType   nodeGraphType
            );

    /// Returns info for an attribute available on nodes of the given type or NULL if no info for the
    /// attribute is available.
    /// @note attrId is the ID of the attribute, eg Octane::A_SHADER_CODE
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static const Octane::ApiAttributeInfo attributeInfo(
            Octane::NodeType                          type,
            Octane::AttributeId                       attrId
            );

    /// Returns info for an attribute available on nodes of the given type or NULL
    /// if no info for the attribute is available.
    /// @note attrIx is the index of the attribute in the infos of the node, not attribute ID.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static const Octane::ApiAttributeInfo attributeInfo(
            Octane::NodeType                          type,
            uint32_t                                  attrIx
            );

    /// Returns info for an attribute available on graphs of the given type or NULL
    /// if no info for the attribute is available.
    /// @note attrIx is the index of the attribute in the infos of the node, not attribute ID.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static const Octane::ApiAttributeInfo attributeInfo(
            Octane::NodeGraphType                     type,
            uint32_t                                  attrIx
            );

    /// Returns info for a pin available on a node or NULL if there's no such pin.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodePinInfoProxy nodePinInfo(
            Octane::NodeType                          nodeType,
            uint32_t                                  pinIx
            );

    /// Returns the name for an attribute type, e.g. "AT_BOOL" for AT_BOOL.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getAttributeTypeName(
            Octane::AttributeType   type
            );

    /// Returns the name for a node pin type, e.g. "PT_BOOL" for PT_BOOL.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getPinTypeName(
            Octane::NodePinType   type
            );

    /// Returns the color for a node pin type (ARGB encoded).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint32_t getPinTypeColor(
            Octane::NodePinType   type
            );

    /// Returns the name for a node graph type, e.g. "GT_STANDARD" for GT_STANDARD.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getGraphTypeName(
            Octane::NodeGraphType   type
            );

    /// Returns the name for a node type, e.g. "NT_TEX_MIX" for NT_TEX_MIX.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getNodeTypeName(
            Octane::NodeType   type
            );

    /// Returns the type name of an api item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getItemTypeName(
            const ApiItemProxy &   item
            );

    /// Returns the name for an attribute ID, e.g. "value" for A_VALUE.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getAttributeName(
            Octane::AttributeId   id
            );

    /// Returns the ID for an attribute name, e.g. A_VALUE for "value".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::AttributeId getAttributeId(
            const char *   attributeName
            );

    /// Returns the enum name for an attribute ID, e.g. "A_VALUE" for A_VALUE.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getAttributeIdName(
            Octane::AttributeId   id
            );

    /// Returns the enum name for an attribute name, e.g. "A_VALUE" for "value".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getAttributeIdName(
            const char *   attributeName
            );

    /// Returns the name for a pin ID, e.g. "diffuse" for P_DIFFUSE.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getPinName(
            Octane::PinId   id
            );

    /// Returns the ID for a pin name, e.g. P_DIFFUSE for "diffuse".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::PinId getPinId(
            const char *   pinName
            );

    /// Returns the enum name for a pin ID, e.g. "P_DIFFUSE" for P_DIFFUSE.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getPinIdName(
            Octane::PinId   id
            );

    /// Returns the enum name for a pin name, e.g. "P_DIFFUSE" for "diffuse".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getPinIdName(
            const char *   pinName
            );

    /// Get the string name of an OSL value type of a given texture value type enum
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getTextureValueTypeName(
            Octane::TextureValueType   textureValueType
            );

    /// Get the OSL value type for a given OSL type name
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::TextureValueType getTextureValueTypeForOslType(
            const char *   oslType
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void getCompatibleTypes(
            Octane::NodePinType                       outType,
            std::vector<Octane::NodeGraphType>        compatGraphs,
            size_t &                                  compatGraphsSize,
            std::vector<Octane::NodeType>             compatNodes,
            size_t &                                  compatNodesSize
            );

    /// Returns the information related to a render pass given its id
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static const Octane::ApiRenderPassInfo renderPassInfo(
            Octane::RenderPassId   id
            );

    /// Returns an array with all the available render pass ids. Usefull for iterating
    /// over all render pass ids in Octane.
    ///
    /// @param[out] length
    ///     Length of the returned array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Array of all available render pass ids. This array doesn't change at runtime.
    ///     Don't free up this array it's a static array owned by the API.
    static std::vector<Octane::RenderPassId> getAllRenderPassIds(
            size_t &   length
            );

    /// Returns the @ref RenderPassId for the provided render AOV node or @ref RENDER_PASS_UNKNOWN
    /// if it's not a valid render AOV node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::RenderPassId getRenderPassIdFromRenderAovNode(
            const ApiNodeProxy &   node
            );

    /// Returns the @ref ApiRenderPassInfo corresponding to the provided render AOV node. If @ref node
    /// is not a valid render AOV node, the returned @ref ApiRenderPassInfo is for @ref RENDER_PASS_UNKNOWN.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static const Octane::ApiRenderPassInfo getRenderAovInfoFromRenderAovNode(
            const ApiNodeProxy &   node
            );

    /// Returns the name of the render pass associated with the id.
    /// @deprecated Use #renderPassInfo instead
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string renderPassName(
            Octane::RenderPassId   id
            );

    /// Returns the short (~ abbreviated) name of a render pass.
    /// @deprecated Use #renderPassInfo instead
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string renderPassShortName(
            Octane::RenderPassId   id
            );

    /// Returns the pin id for a render pass.
    /// @deprecated Use #renderPassInfo instead
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::PinId renderPassIdToPinId(
            Octane::RenderPassId   id
            );

    /// Returns the group name of a render pass
    /// @deprecated USe RenderPassInfo::mCategory instead.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string renderPassGroupName(
            Octane::RenderPassGroupId   id
            );

    /// Returns the render pass id for a pin id.
    /// @deprecated With the introduction of render AOV nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::RenderPassId pinIdToRenderPassId(
            Octane::PinId   pinId
            );

    /// Finds the bool pin used to enable/disable the render pass. Returns FALSE
    /// if no pin is found for the render pass.
    /// @deprecated With the introduction of render AOV nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool findPinIdForRenderPassId(
            Octane::RenderPassId                      renderPassId,
            Octane::PinId &                           pinId
            );

    /// Finds the render pass you can enable/disable with the passed in pin id. Returns
    /// FALSE if this pin isn't used to enable/disable a render pass.
    /// @deprecated With the introduction of render AOV nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool findRenderPassIdForPinId(
            Octane::PinId                             pinId,
            Octane::RenderPassId &                    renderPassId
            );

private:
    static GRPCSettings & getGRPCSettings();
};
