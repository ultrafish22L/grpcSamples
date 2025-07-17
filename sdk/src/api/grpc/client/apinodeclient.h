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
class ApiItemProxy;
class ApiNodeGraphProxy;
class ApiRootNodeGraphProxy;
class ApiNodePinInfoProxy;
class ApiNodeArrayProxy;
#include "apiitemclient.h"


#include "apinodesystem.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiNode
class ApiNodeProxy : public ApiItemProxy
{
public:
    /// Creates a new node of the specified type.
    ///
    /// @param[in]  type
    ///     The type of the node to create.
    /// @param[in]  ownerGraph
    ///     The graph to which we add the node.
    /// @param[in]  configurePins  (optional, default=TRUE)
    ///     If set to TRUE, all pins will have the default node created as internal nodes. If set
    ///     to FALSE, no default nodes are created.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the created node or NULL if creation failed.
    static ApiNodeProxy create(
            const Octane::NodeType                    type,
            ApiNodeGraphProxy &                       ownerGraph,
            const bool                                configurePins
            );

    /// Adds a new dynamic pin to this node.
    ///
    /// This call should only be used while loading nodes from a scene file, and before
    /// convertAndEvaluate() is called on the parent root graph.
    ///
    /// This call can fail to add a pin if this node has a type which doesn't contain dynamic pins,
    /// or if it only allows dynamic pins of a different type. Dynamic pins should always added
    /// in the same order as they were when saving the file.
    ///
    /// If successful the new dynamic pin will always be the last pin on the node, at index
    /// pinCount() - 1.
    ///
    /// @param[in] type
    ///     The pin type.
    /// @param[in] name
    ///     The name of this dynamic pin
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     true if a dynamic pin was added.
    bool addDynamicPinForLoading(
            const Octane::NodePinType                 type,
            const char *                              name
            );

    /// Returns the info for this node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    const ApiNodeInfoProxy info() const;

    /// Returns the type of this node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::NodeType type() const;

    /// Texture nodes that represent OSL code can defined the texture value type of their output.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The TextureValueType of the output texture value (default is TEXTURE_VALUE_TYPE_UNKNOWN).
    Octane::TextureValueType outputTextureValueType() const;

    /// Set the typed texture node to a given texture type configuration
    ///
    /// @param[in]  configuration
    ///     A texture type configuration
    /// @param[in]  evaluate
    ///     Whether to evaluate the node after reconfiguration (default is TRUE)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if setting the node to the provided texture type configuration succeeded, FALSE otherwise
    bool setTextureTypeConfiguration(
            const Octane::ApiTextureNodeTypeInfo::Configuration & configuration,
            const bool                                evaluate
            );

    /// Creates default nodes for empty/unconnected pins that have a default node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void configureEmptyPins();

    /// Returns the total (static + dynamic) number of pins of this node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t pinCount() const;

    /// Returns the number of static pins.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t staticPinCount() const;

    /// Returns the number of dynamic pins.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t dynPinCount() const;

    /// Returns TRUE if a static pin with the specified ID exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasPin(
            const Octane::PinId   pinId
            ) const;

    /// Returns TRUE if a static pin with the specified name exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasPin(
            const char *   pinName
            ) const;

    /// Returns TRUE if a static or dynamic pin with the specified index exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasPinIx(
            const uint32_t   index
            ) const;

    /// Returns TRUE if a static pin with this ID exists and returns its index in "foundIndex".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool findPin(
            const Octane::PinId                       id,
            uint32_t &                                foundIndex
            ) const;

    /// Returns TRUE if a static or dynamic pin with this name exists and returns its index in
    /// "foundIndex".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool findPin(
            const char *                              name,
            uint32_t &                                foundIndex
            ) const;

    /// Returns the pin id of a static pin based on its name. Returns P_UNKNOWN if there's no such
    /// pin.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::PinId pinId(
            const char *   name
            ) const;

    /// Returns the pin id of a static pin based on its index. Returns P_UNKNOWN if there's no such
    /// pin.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::PinId pinIdIx(
            const uint32_t   index
            ) const;

    /// Returns the name of a static pin based on its ID. Returns "" if no such pin exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string pinName(
            const Octane::PinId   id
            ) const;

    /// Returns the name of a static or dynamic pin based on its index. Returns "" if no such pin
    /// exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string pinNameIx(
            const uint32_t   index
            ) const;

    /// Returns the label of a static pin specified by its ID. Returns "" if no such pin exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string pinLabel(
            const Octane::PinId   id
            ) const;

    /// Returns the label of a static or dynamic pin specified by its name. Returns "" if no such
    /// pin exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string pinLabel(
            const char *   name
            ) const;

    /// Returns the label of a static or dynamic pin specified by its index. Returns "" if no such
    /// pin exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string pinLabelIx(
            const uint32_t   index
            ) const;

    /// Returns the pin type of a static pin based on its pin id. Returns PT_UNKNOWN if no such pin
    /// exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::NodePinType pinType(
            const Octane::PinId   id
            ) const;

    /// Returns the pin type of the static or dynamic pin with the specified name. Returns
    /// PT_UNKNOWN if no such pin exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::NodePinType pinType(
            const char *   name
            ) const;

    /// Returns the pin type of the static or dynamic pin at the specified index. Returns PT_UNKNOWN
    /// if no such pin exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::NodePinType pinTypeIx(
            const uint32_t   index
            ) const;

    /// Texture nodes that represent OSL code can defined the texture value type of their pins.
    /// It can be decided dynamically for certain nodes that need it to be, based on user selected types on the node.
    ///
    /// @param[in]  name
    ///     The name of the pin asked about for its TextureValueType.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The TextureValueType of the value carried by the provided pin (default is TEXTURE_VALUE_TYPE_UNKNOWN).
    Octane::TextureValueType pinTextureValueType(
            const char *   name
            ) const;

    /// Texture nodes that represent OSL code can defined the texture value type of their pins.
    /// It can be decided dynamically for certain nodes that need it to be, based on user selected types on the node.
    ///
    /// @param[in]  index
    ///     The index of the pin asked about for its TextureValueType.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The TextureValueType of the value carried by the provided pin (default is TEXTURE_VALUE_TYPE_UNKNOWN).
    Octane::TextureValueType pinTextureValueTypeIx(
            const uint32_t   index
            ) const;

    /// Returns the pin info of a static pin based on its pin id. Returns the fallback pin info
    /// (with pin ID P_UNKNOWN) if there is no such pin.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodePinInfoProxy pinInfo(
            const Octane::PinId   id
            ) const;

    /// Returns the pin info of a static or dynamic pin based on the pin name. Returns the fallback
    /// pin info (with pin ID P_UNKNOWN) if there is no such pin. Note that dynamic pins also have
    /// pin ID P_UNKNOWN.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodePinInfoProxy pinInfo(
            const char *   name
            ) const;

    /// Returns the pin info of a static or dynamic pin based on its index. Returns the fallback
    /// pin info (with pin ID P_UNKNOWN) if there is no such pin. Note that dynamic pins also have
    /// pin ID P_UNKNOWN.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodePinInfoProxy pinInfoIx(
            const uint32_t   index
            ) const;

    /// Returns TRUE if any of the pins are flagged dirty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool pinsAreDirty() const;

    /// Returns TRUE if the pin is flagged dirty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isDirtyPin(
            const Octane::PinId   pinId
            ) const;

    /// Returns TRUE if the pin is flagged dirty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isDirtyPin(
            const char *   pinName
            ) const;

    /// Returns TRUE if the pin is flagged dirty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isDirtyPinIx(
            const uint32_t   pinIx
            ) const;

    /// Checks if the connection can be made from sourceNode to this node.
    ///
    /// @param[in]  pinId
    ///     Id identifying the pin on this node.
    /// @param[in]  sourceNode
    ///     The node we'd like to connect to the pin.
    /// @param[in]  doCycleCheck
    ///     If TRUE we check that the connection doesn't introduce a cycle.
    ///     Cycle checking can be costly on complex graphs. Only ommit this
    ///     if you're sure you're not making any cycles.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the connection can be made. FALSE otherwise.
    bool canConnectTo(
            const Octane::PinId                       pinId,
            const ApiNodeProxy *                      sourceNode,
            const bool                                doCycleCheck
            ) const;

    /// Same as above but identifying the pin by name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool canConnectTo(
            const char *                              pinName,
            const ApiNodeProxy *                      sourceNode,
            const bool                                doCycleCheck
            ) const;

    /// Same as above but identifying the pin by index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool canConnectToIx(
            const uint32_t                            pinIx,
            const ApiNodeProxy *                      sourceNode,
            const bool                                doCycleCheck
            ) const;

    /// Connects a source node to one of this node's pin.
    ///
    /// @param[in]  pinId
    ///     ID of the destination pin.
    /// @param[in]  sourceNode
    ///     Source node to connect to the destination pin. If the ptr is NULL the pin will be
    ///     disconnected and if it owned an item, the item will be destroyed.
    /// @param[in]  evaluate
    ///     If set to TRUE, the parent node of the pin will be evaluated.
    /// @param[in]  doCycleCheck
    ///     TRUE if we'd like to do the cycle check before connecting.
    ///     Only ommit this when you're sure that you're not making any cycles.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void connectTo(
            const Octane::PinId                       pinId,
            ApiNodeProxy *                            sourceNode,
            const bool                                evaluate,
            const bool                                doCycleCheck
            );

    /// Same as above but identifying the pin by name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void connectTo(
            const char *                              pinName,
            ApiNodeProxy *                            sourceNode,
            const bool                                evaluate,
            const bool                                doCycleCheck
            );

    /// Same as above but identifying the pin by index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void connectToIx(
            const uint32_t                            pinIdx,
            ApiNodeProxy *                            sourceNode,
            const bool                                evaluate,
            const bool                                doCycleCheck
            );

    /// Returns the node connected to a pin.
    ///
    /// @param[in]  pinId
    ///     Id identifying the pin.
    /// @param[in]  enterWrapperNodes
    ///     If set to TRUE the connected node is a built-in wrapper node, then the returned node
    ///     will be the output linker of the wrapped script graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     A pointer to the connected node (if there's one), NULL otherwise.
    ApiNodeProxy connectedNode(
            const Octane::PinId                       pinId,
            const bool                                enterWrapperNode
            ) const;

    /// Same as above but identifies the pin based on name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy connectedNode(
            const char *const                         pinName,
            const bool                                enterWrapperNode
            ) const;

    /// Same as above but identifies the pin based on index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy connectedNodeIx(
            const uint32_t                            pinIx,
            const bool                                enterWrapperNode
            ) const;

    /// Returns the input node of a pin, skipping linker nodes.
    ///
    /// @param[in]  pinId
    ///     Id identifying the pin.
    /// @param[in]  enterWrapperNodes
    ///     Set to TRUE if built-in wrapper nodes should be entered (see connectedNode()).
    ///     The default value is FALSE.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     A pointer to the input node (if there's one), NULL otherwise.
    ApiNodeProxy inputNode(
            const Octane::PinId                       pinId,
            const bool                                enterWrapperNodes
            ) const;

    /// Same as above but identifies the pin based on name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy inputNode(
            const char *const                         pinName,
            const bool                                enterWrapperNodes
            ) const;

    /// Same as above but identifies the pin based on index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy inputNodeIx(
            const uint32_t                            index,
            const bool                                enterWrapperNodes
            ) const;

    /// Returns the destination nodes of this node.
    ///
    /// @param[out] nodes
    ///     Array of the destination nodes.
    /// @param[out]  pinNames
    ///     Array of the destination pin names. This array is owned by the API and
    ///     valid until the next call to this function. This array has the same length
    ///     as nodes and contains the id of the pin on each corresponding node.
    ///     (e.g. pinNames[0] is the id of the pin on node nodes[0])
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destinationNodes(
            ApiNodeArrayProxy &                       nodes,
            std::vector<std::string> &                pinNames
            ) const;

    /// Builds a node pin info out of the pin infos of all non-linker destination pins of an input
    /// linker node. It also takes the name, the description (A_DESCRIPTION) and group (A_GROUP)
    /// attributes of the linker node into account and applies those to the generated pin info.
    ///
    /// The returned pin info stays valid until the next time this function is called.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     A reference of the created pin info.
    ApiNodePinInfoProxy buildLinkerNodePinInfo();

    /// Builds a node pin info out of the pin infos of all non-linker destination pins of this node.
    /// These members will not be populated:
    ///
    /// ApiNodePinInfo::mStaticName
    ///                 mStaticLabel
    ///                 mDescription
    ///                 mGroupName
    ///                 mDefaultNodeType
    ///                 mMinVersion
    ///                 mEndVersion
    ///
    /// The returned pin info stays valid until the next time this function is called.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     A reference of the created pin info.
    ApiNodePinInfoProxy buildDestinationPinInfo();

    /// Returns the owned item of a pin (Or NULL if the pin owns nothing).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiItemProxy ownedItem(
            const Octane::PinId   pinId
            ) const;

    /// Same as above but identifies the pin based on name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiItemProxy ownedItem(
            const char *   pinName
            ) const;

    /// Same as above but identifies the pin based on index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiItemProxy ownedItemIx(
            const uint32_t   pinIx
            ) const;

    /// Creates a node internal a pin. If the pin already owned an item, it will be destroyed.
    ///
    /// @param[in]  pinId
    ///     Pin ID identifying the pin in which we'd like to create the node.
    /// @param[in]  type
    ///     Type of the node to create in the pin. The output type of the node must match the type
    ///     of the pin.
    /// @param[in]  configurePins  (optional, default=TRUE)
    ///     If set to TRUE, all pins will have the default node created as internal nodes. If set
    ///     to FALSE, no default nodes are created.
    /// @param[in]  evaluate  (optional, default=TRUE)
    ///     If set to TRUE, the new node and this node will be evaluated.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created item or NULL if the node could not be created.
    ApiNodeProxy createInternal(
            const Octane::PinId                       pinId,
            const Octane::NodeType                    type,
            const bool                                configurePins,
            const bool                                evaluate
            );

    /// Same as above but identifies the pin based on name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy createInternal(
            const char *                              pinName,
            const Octane::NodeType                    type,
            const bool                                configurePins,
            const bool                                evaluate
            );

    /// Same as above but identifies the pin based on index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy createInternalIx(
            const uint32_t                            pinIx,
            const Octane::NodeType                    type,
            const bool                                configurePins,
            const bool                                evaluate
            );

    /// Creates a node graph internal a pin. If the pin already owned an item, it will be destroyed.
    ///
    /// @param[in]  pinId
    ///     Pin ID identifying the pin in which we'd like to create the node graph.
    /// @param[in]  type
    ///     Type of the node graph to create in the pin. The node graph needs to have a default
    ///     linker node of the type of the pin or the pin will stay unconnected.
    /// @param[in]  evaluate  (optional, default=TRUE)
    ///     If set to TRUE, the new node and this node will be evaluated.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created item or NULL if the node graph could not be created.
    ApiNodeGraphProxy createInternal(
            const Octane::PinId                       pinId,
            const Octane::NodeGraphType               type,
            const bool                                evaluate
            );

    /// Same as above but identifies the pin based on name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeGraphProxy createInternal(
            const char *                              pinName,
            const Octane::NodeGraphType               type,
            const bool                                evaluate
            );

    /// Same as above but identifies the pin based on index
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeGraphProxy createInternalIx(
            const uint32_t                            pinIx,
            const Octane::NodeGraphType               type,
            const bool                                evaluate
            );

    /// Copies an item into a pin or does nothing if the item can't be copied into the pin, because
    /// the item is a node with the incorrect type.
    ///
    /// @param[in]  pinId
    ///     The ID of the pin into which the item should be copied.
    /// @param[in]  sourceItem
    ///     The item to copy into the pin.
    /// @param[in]  evaluate
    ///     If set to TRUE, the node will be evaluated after the copy.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The newly created item or NULL if the source item could not be copied into the pin.
    ApiItemProxy copyFrom(
            const Octane::PinId                       pinId,
            const ApiItemProxy *                      sourceItem,
            const bool                                evaluate
            );

    /// Same as above, but identifying the pin via its name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiItemProxy copyFrom(
            const char *                              pinName,
            const ApiItemProxy *                      sourceItem,
            const bool                                evaluate
            );

    /// Same as above, but identifying the pin via its index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiItemProxy copyFromIx(
            const uint32_t                            pinIx,
            const ApiItemProxy *                      sourceItem,
            const bool                                evaluate
            );

    /// Returns the value of a value node (skipping linker nodes) or the default
    /// value of the pin if it's not connected to value node. These should getters should
    /// only be called on a pin of the appropriate type (e.g. getBool on PT_BOOL).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool getPinBool(
            const Octane::PinId   id
            ) const;

    float getPinFloat(
            const Octane::PinId   id
            ) const;

    OctaneVec::float_2 getPinFloat2(
            const Octane::PinId   id
            ) const;

    OctaneVec::float_3 getPinFloat3(
            const Octane::PinId   id
            ) const;

    OctaneVec::float_4 getPinFloat4(
            const Octane::PinId   id
            ) const;

    int32_t getPinInt(
            const Octane::PinId   id
            ) const;

    OctaneVec::int32_2 getPinInt2(
            const Octane::PinId   id
            ) const;

    OctaneVec::int32_3 getPinInt3(
            const Octane::PinId   id
            ) const;

    OctaneVec::int32_4 getPinInt4(
            const Octane::PinId   id
            ) const;

    OctaneVec::MatrixF getPinMatrix(
            const Octane::PinId   id
            ) const;

    std::string getPinString(
            const Octane::PinId   id
            ) const;

    Octane::ApiFilePath getPinFilePath(
            const Octane::PinId   id
            ) const;

    /// Same as above but identifies the pin via name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool getPinBool(
            const char *   name
            ) const;

    float getPinFloat(
            const char *   name
            ) const;

    OctaneVec::float_2 getPinFloat2(
            const char *   name
            ) const;

    OctaneVec::float_3 getPinFloat3(
            const char *   name
            ) const;

    OctaneVec::float_4 getPinFloat4(
            const char *   name
            ) const;

    int32_t getPinInt(
            const char *   name
            ) const;

    OctaneVec::int32_2 getPinInt2(
            const char *   name
            ) const;

    OctaneVec::int32_3 getPinInt3(
            const char *   name
            ) const;

    OctaneVec::int32_4 getPinInt4(
            const char *   name
            ) const;

    OctaneVec::MatrixF getPinMatrix(
            const char *   name
            ) const;

    std::string getPinString(
            const char *   name
            ) const;

    Octane::ApiFilePath getPinFilePath(
            const char *   name
            ) const;

    /// Same as above but identifies the pin via index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool getPinBoolIx(
            const uint32_t   index
            ) const;

    float getPinFloatIx(
            const uint32_t   index
            ) const;

    OctaneVec::float_2 getPinFloat2Ix(
            const uint32_t   index
            ) const;

    OctaneVec::float_3 getPinFloat3Ix(
            const uint32_t   index
            ) const;

    OctaneVec::float_4 getPinFloat4Ix(
            const uint32_t   index
            ) const;

    int32_t getPinIntIx(
            const uint32_t   index
            ) const;

    OctaneVec::int32_2 getPinInt2Ix(
            const uint32_t   index
            ) const;

    OctaneVec::int32_3 getPinInt3Ix(
            const uint32_t   index
            ) const;

    OctaneVec::int32_4 getPinInt4Ix(
            const uint32_t   index
            ) const;

    OctaneVec::MatrixF getPinMatrixIx(
            const uint32_t   index
            ) const;

    std::string getPinStringIx(
            const uint32_t   index
            ) const;

    Octane::ApiFilePath getPinFilePathIx(
            const uint32_t   index
            ) const;

    /// Returns the value in an out argument.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void getPinValue(
            const Octane::PinId                       id,
            bool &                                    value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            float &                                   value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_2 &                      value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_3 &                      value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_4 &                      value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            int32_t &                                 value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_2 &                      value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_3 &                      value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_4 &                      value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            OctaneVec::MatrixF &                      value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            std::string &                             value
            ) const;

    void getPinValue(
            const Octane::PinId                       id,
            Octane::ApiFilePath &                     value
            ) const;

    /// Same as above but identifies the pin via name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void getPinValue(
            const char *                              name,
            bool &                                    value
            ) const;

    void getPinValue(
            const char *                              name,
            float &                                   value
            ) const;

    void getPinValue(
            const char *                              name,
            OctaneVec::float_2 &                      value
            ) const;

    void getPinValue(
            const char *                              name,
            OctaneVec::float_3 &                      value
            ) const;

    void getPinValue(
            const char *                              name,
            OctaneVec::float_4 &                      value
            ) const;

    void getPinValue(
            const char *                              name,
            int32_t &                                 value
            ) const;

    void getPinValue(
            const char *                              name,
            OctaneVec::int32_2 &                      value
            ) const;

    void getPinValue(
            const char *                              name,
            OctaneVec::int32_3 &                      value
            ) const;

    void getPinValue(
            const char *                              name,
            OctaneVec::int32_4 &                      value
            ) const;

    void getPinValue(
            const char *                              name,
            OctaneVec::MatrixF &                      value
            ) const;

    void getPinValue(
            const char *                              name,
            std::string &                             value
            ) const;

    void getPinValue(
            const char *                              name,
            Octane::ApiFilePath &                     value
            ) const;

    /// Same as above but identifies the pin via index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void getPinValueIx(
            const uint32_t                            index,
            bool &                                    value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            float &                                   value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_2 &                      value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_3 &                      value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_4 &                      value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            int32_t &                                 value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_2 &                      value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_3 &                      value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_4 &                      value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            OctaneVec::MatrixF &                      value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            std::string &                             value
            ) const;

    void getPinValueIx(
            const uint32_t                            index,
            Octane::ApiFilePath &                     value
            ) const;

    /// Sets a connected node's value attribute through a pin. This means
    /// that the value is clamped (if applicable) to the allowed range of the pin.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setPinValue(
            const Octane::PinId                       id,
            const bool                                value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const float                               value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const int32_t                             value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const char *const                         value,
            const bool                                evaluate
            );

    void setPinValue(
            const Octane::PinId                       id,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            );

    /// Same as above but identifies the pin via name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setPinValue(
            const char *                              name,
            const bool                                value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const float                               value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const int32_t                             value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const char *const                         value,
            const bool                                evaluate
            );

    void setPinValue(
            const char *                              name,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            );

    /// Same as above but identifies the pin via index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setPinValueIx(
            const uint32_t                            index,
            const bool                                value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const float                               value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const int32_t                             value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const char *const                         value,
            const bool                                evaluate
            );

    void setPinValueIx(
            const uint32_t                            index,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            );

    /// Opens a UI to allow the user choose where and how the specified node should be stored.
    ///
    /// The node will either be copied into a node graph and connected with a corresponding output
    /// linker of - if the node is already an output linker - the owner graph of the output linker
    /// will be stored.
    ///
    /// @note This function is not supported by all SDK flavours
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the node was stored successfully, FALSE on failure in which case there
    ///     should have been additional error messages on the log.
    bool storeToDb();

    /// Show the OSL editor window for this node.
    /// If no editor is open yet, then the current node will be shown in a new editor, and this
    /// call will block until the user closes the window (or until closeOslWindow() is called).
    ///
    /// If a window is already open, the existing editor will load this node and this call
    /// immediately returns. If force is set to false then the user may cancel this load if there
    /// currently are unsaved changes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void showOslWindow(
            bool   force
            );

    /// Request closing the OSL editor window
    /// If force is false, then the user may cancel if the editor currently has unsaved
    /// changes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     true if the window was closed, false if the user canceled.
    static bool closeOslWindow(
            bool   force
            );

    /// Unpack all file data of the node that is coming from an ORBX package and optionally the file
    /// data of its input nodes. The unpacked resources are stored in a specified directory and the A_FILENAME /
    /// A_PACKAGE attributes will be switched to the new file path as well.
    ///
    /// @param  assetPath
    ///     Absolute path to the asset save locations (directory). If the directory doesn't exist,
    ///     it will be created.
    /// @param  recursive
    ///     If TRUE then the given node will be unpacked and all nodes that are connected with its
    ///     inputs.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if unpacking succeeded. In the case that any node fails to unpack, we will continue
    ///     trying to unpack the rest (if any).
    bool unpackFileData(
            const char *                              assetPath,
            bool                                      recursive
            );

private:
    static GRPCSettings & getGRPCSettings();
};
