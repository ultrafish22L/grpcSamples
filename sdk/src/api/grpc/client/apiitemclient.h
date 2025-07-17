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
class ApiNodeProxy;
class ApiNodeGraphProxy;
class ApiRootNodeGraphProxy;
class ApiItemArrayProxy;
struct ApiNodeInfoProxy;


#include "apinodesystem.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiItem
class ApiItemProxy : public GRPCBase
{
public:
    /// Destroys this item. This will disconnect the node or the the linker nodes of the graph
    /// connected to external nodes and will destroy all items owned by this item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Returns the name of this item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string name() const;

    /// Sets the name of this item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setName(
            const char *   name
            );

    /// Returns the position of the item inside its owner.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    OctaneVec::float_2 position() const;

    /// Sets the position of this item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setPosition(
            const OctaneVec::float_2   newPos
            );

    /// Adds a UI operation flag to this node item and this flags will be only used when making a
    /// direct interaction from UI.
    /// For options check UIOperationsFlag enum in octaneenums.h
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setUIOperationFlags(
            const Octane::enum_t   flags
            );

    /// Returns the UI operation flags of this node item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::enum_t uiOperationFlags() const;

    /// Sets the node item to selected state (for the window opened using ApiNodeGraph::showWindow())
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void select() const;

    /// Returns the current time of this item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::TimeT time() const;

    /// Returns the output type for this item. PT_UNKNOWN means this item
    /// cannot be connected to any pin. For graphs this means the output type of
    /// the default linker node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::NodePinType outType() const;

    /// Returns the persistent ID of the node item. All node items of the same root node graph are
    /// guaranteed to have different persistent IDs. But items of different root node graphs can
    /// have the same persistent ID.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint64_t persistentId() const;

    /// Returns the unique ID of the node item. Unique IDs are unique within the same running
    /// instance of Octane. A valid node item will have a non-zero unique ID and an invalid node
    /// item will have a unique ID of zero.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t uniqueId() const;

    /// Collects all items that are connected to this node item.
    /// Connected input graphs will be collected as a whole, i.e. the tree traversal can lead
    /// outside the graph containing the root item, but not into nested graphs.
    /// Items that are owned by node pins are not explicitly collected.
    ///
    /// @param[out]  treeitems
    ///     The found items (including rootItem) will be added to this array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void collectItemTree(
            ApiItemArrayProxy &   treeItems
            );

    /// If the item is owned by a node graph, this function will remove all items owned by that node
    /// graph that are not directly/indirectly connected with the item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void deleteUnconnectedItems() const;

    /// If this item stores file data that has been provided by plugins directly, this function
    /// will export that data into a file with the specified name. This is currently only supported
    /// for nodes of types NT_GEO_MESH and NT_TEX_IMAGE.
    ///
    /// @param[in]  destinationDir
    ///     Absolute path to the destination directory on disk. The export filename is determined
    ///     by Octane and can be read from the item via the A_FILENAME attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void switchToFileData(
            const char *   destinationDir
            );

    /// Returns the version of the item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::VersionT version() const;

    /// Returns TRUE if this item is a graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isGraph() const;

    /// Returns TRUE if this item is a node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isNode() const;

    /// Returns TRUE if the item is an input/output linker node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isLinker() const;

    /// Returns TRUE if the item is an input linker node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isInputLinker() const;

    /// Returns TRUE if the item is an output linker node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isOutputLinker() const;

    /// Downcasts this item to a graph. Returns NULL if this item is a node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeGraphProxy toGraph() const;

    /// Downcasts this item to a node. Returns NULL if this item is a graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy toNode() const;

    /// Downcasts this item to a graph. Returns NULL if this item is a node. (non-const)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeGraphProxy toGraph();

    /// Downcasts this item to a node. Returns NULL if this item is a graph. (non-const)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy toNode();

    /// Returns TRUE if this item has an owner (graph or pin), usually always TRUE with the
    /// exception of root node graphs, which never have an owner.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasOwner() const;

    /// Returns TRUE if this item is owned by a graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool graphOwned() const;

    /// Returns TRUE if this item is owned by a pin.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool pinOwned() const;

    /// Gets the graph owner (if any).
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The graph that owns this item. NULL in case this item is the root graph
    ///     or owned by a pin.
    ApiNodeGraphProxy graphOwner() const;

    /// Gets the pin owner (if any).
    ///
    /// @param[out] pinIx
    ///     Index of the pin on the returned node. (Only valid if the returned node
    ///     is not NULL).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The node which has the pin owning this item. NULL in case this item is
    ///     not owned by a pin.
    ApiNodeProxy pinOwner(
            uint32_t &   pinIx
            ) const;

    /// Returns the root node graph which contains this node item. If this item is a root node graph
    /// it returns itself.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiRootNodeGraphProxy rootGraph() const;

    /// Returns the root node graph which contains this node item. If this item is a root node graph
    /// it returns itself.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiRootNodeGraphProxy rootGraph();

    /// Returns the number of attributes of this item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t attrCount() const;

    /// Returns TRUE if an attribute with the specified ID exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasAttr(
            const Octane::AttributeId   id
            ) const;

    /// Returns TRUE if an attribute with the specified name exists.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasAttr(
            const char *   name
            ) const;

    /// Returns TRUE if an attribute with this ID exists and returns its index in "foundIndex".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool findAttr(
            const Octane::AttributeId                 id,
            uint32_t &                                foundIndex
            ) const;

    /// Returns TRUE if an attribute with this name exists and returns its index in "foundIndex".
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool findAttr(
            const char *                              name,
            uint32_t &                                foundIndex
            ) const;

    /// Returns the ID of attribute provided by it's name. Returns A_UNKNOWN when
    /// there's no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::AttributeId attrId(
            const char *   name
            ) const;

    /// Returns the ID of the attribute at index. Returns A_UNKNOWN when there's
    /// no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::AttributeId attrIdIx(
            const uint32_t   index
            ) const;

    /// Returns the name of the attribute at the provided ID or "unknown" if there's no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string attrName(
            const Octane::AttributeId   id
            ) const;

    /// Returns the name of the attribute at the index or "unknown" if there's no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string attrNameIx(
            const uint32_t   index
            ) const;

    /// Returns the type of the attribute identified by it's ID. Returns AT_UNKNOWN when
    /// there's no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::AttributeType attrType(
            const Octane::AttributeId   id
            ) const;

    /// Returns the type of the attribute identified by it's name. Returns AT_UNKNOWN when
    /// there's no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::AttributeType attrType(
            const char *   attrName
            ) const;

    /// Returns the type of the attribute at the index. Returns AT_UNKNOWN when
    /// there's no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::AttributeType attrTypeIx(
            const uint32_t   index
            ) const;

    /// Returns the info for the attribute identified by the ID. Returns the fallback attribute
    /// info (with attribute ID A_UNKNOWN) if there is no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    const Octane::ApiAttributeInfo attrInfo(
            const Octane::AttributeId   id
            ) const;

    /// Returns the info for the attribute identified by the name. Returns the fallback attribute
    /// info (with attribute ID A_UNKNOWN) if there is no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    const Octane::ApiAttributeInfo attrInfo(
            const char *   name
            ) const;

    /// Returns the info for the attribute at index. Returns the fallback attribute
    /// info (with attribute ID A_UNKNOWN) if there is no such attribute.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    const Octane::ApiAttributeInfo attrInfoIx(
            const uint32_t   index
            ) const;

    /// Returns TRUE if any of the attributes are flagged dirty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool attrAreDirty() const;

    /// Returns TRUE if the attribute is flagged dirty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isDirtyAttr(
            const Octane::AttributeId   id
            ) const;

    /// Returns TRUE if the attribute is flagged dirty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isDirtyAttr(
            const char *   name
            ) const;

    /// Returns TRUE if the attribute is flagged dirty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isDirtyAttrIx(
            const uint32_t   index
            ) const;

    /// Copies another item's attribute value into this item's attribute.
    ///
    /// @param[in]  destId
    ///     Id identifying the destination attribute on this item.
    /// @param[in]  srcItem
    ///     Other item to copy the attribute value from.
    /// @param[in]  srcId
    ///     Id identifying the attribute to copy from.
    /// @param[in]  evaluate
    ///     TRUE to re-evaluate the node, FALSE otherwise.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void copyAttrFrom(
            const Octane::AttributeId                 destId,
            const ApiItemProxy &                      srcItem,
            const Octane::AttributeId                 srcId,
            const bool                                evaluate
            );

    /// Copies the attribute into our attribute, specified by its name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void copyAttrFrom(
            const Octane::AttributeId                 destId,
            const ApiItemProxy &                      srcItem,
            const char *                              srcAttrName,
            const bool                                evaluate
            );

    /// Copies the attribute into our attribute, specified by its index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void copyAttrFromIx(
            const Octane::AttributeId                 destId,
            const ApiItemProxy &                      srcItem,
            const uint32_t                            srcAttrIx,
            const bool                                evaluate
            );

    /// Copies all matching attributes from another item into this item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void copyAttrFrom(
            const ApiItemProxy &                      srcItem,
            const bool                                evaluate
            );

    /// Clears all attributes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clearAllAttr(
            const bool   evaluate
            );

    /// Clears the attribute specified by its ID.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clearAttr(
            const Octane::AttributeId                 id,
            const bool                                evaluate
            );

    /// Clears the attribute specified by its name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clearAttr(
            const char *                              name,
            const bool                                evaluate
            );

    /// Clears the attribute specified by its index.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clearAttrIx(
            const uint32_t                            index,
            const bool                                evaluate
            );

    bool getBool(
            const Octane::AttributeId   id
            ) const;

    int32_t getInt(
            const Octane::AttributeId   id
            ) const;

    OctaneVec::int32_2 getInt2(
            const Octane::AttributeId   id
            ) const;

    OctaneVec::int32_3 getInt3(
            const Octane::AttributeId   id
            ) const;

    OctaneVec::int32_4 getInt4(
            const Octane::AttributeId   id
            ) const;

    int64_t getLong(
            const Octane::AttributeId   id
            ) const;

    OctaneVec::int64_2 getLong2(
            const Octane::AttributeId   id
            ) const;

    float getFloat(
            const Octane::AttributeId   id
            ) const;

    OctaneVec::float_2 getFloat2(
            const Octane::AttributeId   id
            ) const;

    OctaneVec::float_3 getFloat3(
            const Octane::AttributeId   id
            ) const;

    OctaneVec::float_4 getFloat4(
            const Octane::AttributeId   id
            ) const;

    OctaneVec::MatrixF getMatrix(
            const Octane::AttributeId   id
            ) const;

    std::string getString(
            const Octane::AttributeId   id
            ) const;

    std::vector<bool> getBoolArray(
            const Octane::AttributeId   id
            ) const;

    std::vector<int> getIntArray(
            const Octane::AttributeId   id
            ) const;

    std::vector<OctaneVec::int32_2> getInt2Array(
            const Octane::AttributeId   id
            ) const;

    std::vector<OctaneVec::int32_3> getInt3Array(
            const Octane::AttributeId   id
            ) const;

    std::vector<OctaneVec::int32_4> getInt4Array(
            const Octane::AttributeId   id
            ) const;

    std::vector<long> getLongArray(
            const Octane::AttributeId   id
            ) const;

    std::vector<OctaneVec::int64_2> getLong2Array(
            const Octane::AttributeId   id
            ) const;

    std::vector<Octane::MatrixF> getMatrixArray(
            const Octane::AttributeId   id
            ) const;

    std::vector<float> getFloatArray(
            const Octane::AttributeId   id
            ) const;

    std::vector<OctaneVec::float_2> getFloat2Array(
            const Octane::AttributeId   id
            ) const;

    std::vector<OctaneVec::float_3> getFloat3Array(
            const Octane::AttributeId   id
            ) const;

    std::vector<OctaneVec::float_4> getFloat4Array(
            const Octane::AttributeId   id
            ) const;

    std::vector<std::string> getStringArray(
            const Octane::AttributeId   id
            ) const;

    std::vector<uint8_t> getByteArray(
            const Octane::AttributeId   id
            ) const;

    bool getBool(
            const char *   name
            ) const;

    int32_t getInt(
            const char *   name
            ) const;

    OctaneVec::int32_2 getInt2(
            const char *   name
            ) const;

    OctaneVec::int32_3 getInt3(
            const char *   name
            ) const;

    OctaneVec::int32_4 getInt4(
            const char *   name
            ) const;

    int64_t getLong(
            const char *   name
            ) const;

    OctaneVec::int64_2 getLong2(
            const char *   name
            ) const;

    float getFloat(
            const char *   name
            ) const;

    OctaneVec::float_2 getFloat2(
            const char *   name
            ) const;

    OctaneVec::float_3 getFloat3(
            const char *   name
            ) const;

    OctaneVec::float_4 getFloat4(
            const char *   name
            ) const;

    OctaneVec::MatrixF getMatrix(
            const char *   name
            ) const;

    std::string getString(
            const char *   name
            ) const;

    std::vector<bool> getBoolArray(
            const char *   name
            ) const;

    std::vector<int> getIntArray(
            const char *   name
            ) const;

    std::vector<OctaneVec::int32_2> getInt2Array(
            const char *   name
            ) const;

    std::vector<OctaneVec::int32_3> getInt3Array(
            const char *   name
            ) const;

    std::vector<OctaneVec::int32_4> getInt4Array(
            const char *   name
            ) const;

    std::vector<long> getLongArray(
            const char *   name
            ) const;

    std::vector<OctaneVec::int64_2> getLong2Array(
            const char *   name
            ) const;

    std::vector<float> getFloatArray(
            const char *   name
            ) const;

    std::vector<OctaneVec::float_2> getFloat2Array(
            const char *   name
            ) const;

    std::vector<OctaneVec::float_3> getFloat3Array(
            const char *   name
            ) const;

    std::vector<OctaneVec::float_4> getFloat4Array(
            const char *   name
            ) const;

    std::vector<Octane::MatrixF> getMatrixArray(
            const char *   name
            ) const;

    std::vector<std::string> getStringArray(
            const char *   name
            ) const;

    std::vector<uint8_t> getByteArray(
            const char *   name
            ) const;

    bool getBoolIx(
            const uint32_t   index
            ) const;

    int32_t getIntIx(
            const uint32_t   index
            ) const;

    OctaneVec::int32_2 getInt2Ix(
            const uint32_t   index
            ) const;

    OctaneVec::int32_3 getInt3Ix(
            const uint32_t   index
            ) const;

    OctaneVec::int32_4 getInt4Ix(
            const uint32_t   index
            ) const;

    int64_t getLongIx(
            const uint32_t   index
            ) const;

    OctaneVec::int64_2 getLong2Ix(
            const uint32_t   index
            ) const;

    float getFloatIx(
            const uint32_t   index
            ) const;

    OctaneVec::float_2 getFloat2Ix(
            const uint32_t   index
            ) const;

    OctaneVec::float_3 getFloat3Ix(
            const uint32_t   index
            ) const;

    OctaneVec::float_4 getFloat4Ix(
            const uint32_t   index
            ) const;

    OctaneVec::MatrixF getMatrixIx(
            const uint32_t   index
            ) const;

    std::string getStringIx(
            const uint32_t   index
            ) const;

    std::vector<bool> getBoolArrayIx(
            const uint32_t   index
            ) const;

    std::vector<int> getIntArrayIx(
            const uint32_t   index
            ) const;

    std::vector<OctaneVec::int32_2> getInt2ArrayIx(
            const uint32_t   index
            ) const;

    std::vector<OctaneVec::int32_3> getInt3ArrayIx(
            const uint32_t   index
            ) const;

    std::vector<OctaneVec::int32_4> getInt4ArrayIx(
            const uint32_t   index
            ) const;

    std::vector<long> getLongArrayIx(
            const uint32_t   index
            ) const;

    std::vector<OctaneVec::int64_2> getLong2ArrayIx(
            const uint32_t   index
            ) const;

    std::vector<float> getFloatArrayIx(
            const uint32_t   index
            ) const;

    std::vector<OctaneVec::float_2> getFloat2ArrayIx(
            const uint32_t   index
            ) const;

    std::vector<OctaneVec::float_3> getFloat3ArrayIx(
            const uint32_t   index
            ) const;

    std::vector<OctaneVec::float_4> getFloat4ArrayIx(
            const uint32_t   index
            ) const;

    std::vector<Octane::MatrixF> getMatrixArrayIx(
            const uint32_t   index
            ) const;

    std::vector<std::string> getStringArrayIx(
            const uint32_t   index
            ) const;

    std::vector<uint8_t> getByteArrayIx(
            const uint32_t   index
            ) const;

    void get(
            const Octane::AttributeId                 id,
            bool &                                    value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            int32_t &                                 value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            OctaneVec::int32_2 &                      value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            OctaneVec::int32_3 &                      value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            OctaneVec::int32_4 &                      value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            int64_t &                                 value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            OctaneVec::int64_2 &                      value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            float &                                   value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            OctaneVec::float_2 &                      value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            OctaneVec::float_3 &                      value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            OctaneVec::float_4 &                      value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            OctaneVec::MatrixF &                      value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::string &                             value
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<bool> &                       arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<int> &                        arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::int32_2> &         arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::int32_3> &         arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::int32_4> &         arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<long> &                       arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::int64_2> &         arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<float> &                      arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::float_2> &         arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::float_3> &         arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::float_4> &         arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<Octane::MatrixF> &            arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<std::string> &                arr
            ) const;

    void get(
            const Octane::AttributeId                 id,
            std::vector<uint8_t> &                    arr
            ) const;

    void get(
            const char *                              name,
            bool &                                    value
            ) const;

    void get(
            const char *                              name,
            int32_t &                                 value
            ) const;

    void get(
            const char *                              name,
            OctaneVec::int32_2 &                      value
            ) const;

    void get(
            const char *                              name,
            OctaneVec::int32_3 &                      value
            ) const;

    void get(
            const char *                              name,
            OctaneVec::int32_4 &                      value
            ) const;

    void get(
            const char *                              name,
            int64_t &                                 value
            ) const;

    void get(
            const char *                              name,
            OctaneVec::int64_2 &                      value
            ) const;

    void get(
            const char *                              name,
            float &                                   value
            ) const;

    void get(
            const char *                              name,
            OctaneVec::float_2 &                      value
            ) const;

    void get(
            const char *                              name,
            OctaneVec::float_3 &                      value
            ) const;

    void get(
            const char *                              name,
            OctaneVec::float_4 &                      value
            ) const;

    void get(
            const char *                              name,
            OctaneVec::MatrixF &                      value
            ) const;

    void get(
            const char *                              name,
            std::string &                             value
            ) const;

    void get(
            const char *                              name,
            std::vector<bool> &                       arr
            ) const;

    void get(
            const char *                              name,
            std::vector<int> &                        arr
            ) const;

    void get(
            const char *                              name,
            std::vector<OctaneVec::int32_2> &         arr
            ) const;

    void get(
            const char *                              name,
            std::vector<OctaneVec::int32_3> &         arr
            ) const;

    void get(
            const char *                              name,
            std::vector<OctaneVec::int32_4> &         arr
            ) const;

    void get(
            const char *                              name,
            std::vector<long> &                       arr
            ) const;

    void get(
            const char *                              name,
            std::vector<OctaneVec::int64_2> &         arr
            ) const;

    void get(
            const char *                              name,
            std::vector<float> &                      arr
            ) const;

    void get(
            const char *                              name,
            std::vector<OctaneVec::float_2> &         arr
            ) const;

    void get(
            const char *                              name,
            std::vector<OctaneVec::float_3> &         arr
            ) const;

    void get(
            const char *                              name,
            std::vector<OctaneVec::float_4> &         arr
            ) const;

    void get(
            const char *                              name,
            std::vector<Octane::MatrixF> &            arr
            ) const;

    void get(
            const char *                              name,
            std::vector<std::string> &                arr
            ) const;

    void get(
            const char *                              name,
            std::vector<uint8_t> &                    arr
            ) const;

    void getIx(
            const uint32_t                            index,
            bool &                                    value
            ) const;

    void getIx(
            const uint32_t                            index,
            int32_t &                                 value
            ) const;

    void getIx(
            const uint32_t                            index,
            OctaneVec::int32_2 &                      value
            ) const;

    void getIx(
            const uint32_t                            index,
            OctaneVec::int32_3 &                      value
            ) const;

    void getIx(
            const uint32_t                            index,
            OctaneVec::int32_4 &                      value
            ) const;

    void getIx(
            const uint32_t                            index,
            int64_t &                                 value
            ) const;

    void getIx(
            const uint32_t                            index,
            OctaneVec::int64_2 &                      value
            ) const;

    void getIx(
            const uint32_t                            index,
            float &                                   value
            ) const;

    void getIx(
            const uint32_t                            index,
            OctaneVec::float_2 &                      value
            ) const;

    void getIx(
            const uint32_t                            index,
            OctaneVec::float_3 &                      value
            ) const;

    void getIx(
            const uint32_t                            index,
            OctaneVec::float_4 &                      value
            ) const;

    void getIx(
            const uint32_t                            index,
            OctaneVec::MatrixF &                      value
            ) const;

    void getIx(
            const uint32_t                            index,
            std::string &                             value
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<bool> &                       arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<int> &                        arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::int32_2> &         arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::int32_3> &         arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::int32_4> &         arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<long> &                       arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::int64_2> &         arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<float> &                      arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::float_2> &         arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::float_3> &         arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::float_4> &         arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<Octane::MatrixF> &            arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<std::string> &                arr
            ) const;

    void getIx(
            const uint32_t                            index,
            std::vector<uint8_t> &                    arr
            ) const;

    void set(
            const Octane::AttributeId                 id,
            const bool                                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const int32_t                             value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_2 &                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_3 &                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_4 &                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const int64_t                             value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::int64_2 &                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const float                               value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_2 &                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_3 &                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_4 &                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const char *                              value,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const bool *                              arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const int32_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const int64_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::int64_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const float *                             arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const OctaneVec::MatrixF *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const char *const *                       arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const Octane::AttributeId                 id,
            const uint8_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const bool                                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const int32_t                             value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::int32_2 &                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::int32_3 &                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::int32_4 &                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const int64_t                             value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::int64_2 &                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const float                               value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::float_2 &                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::float_3 &                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::float_4 &                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const char *                              value,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const bool *                              arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const int32_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::int32_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::int32_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::int32_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const int64_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::int64_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const float *                             arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::float_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::float_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::float_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const OctaneVec::MatrixF *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const char *const *                       arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void set(
            const char *                              name,
            const uint8_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const bool                                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const int32_t                             value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::int32_2 &                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::int32_3 &                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::int32_4 &                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const int64_t                             value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::int64_2 &                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const float                               value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::float_2 &                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::float_3 &                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::float_4 &                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const char *                              value,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const bool *                              arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const int32_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::int32_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::int32_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::int32_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const int64_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::int64_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const float *                             arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::float_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::float_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::float_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const OctaneVec::MatrixF *                arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const char *const *                       arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void setIx(
            const uint32_t                            index,
            const uint8_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            );

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<bool> &                       values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<int> &                        values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_2> &         values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_3> &         values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_4> &         values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<long> &                       values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int64_2> &         values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<float> &                      values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_2> &         values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_3> &         values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_4> &         values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<Octane::MatrixF> &            values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<std::string> &                values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<uint8_t> &                    values
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<bool> &                       arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<int> &                        arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_2> &         arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_3> &         arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_4> &         arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<long> &                       arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int64_2> &         arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<float> &                      arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_2> &         arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_3> &         arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_4> &         arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<Octane::MatrixF> &            arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<std::string> &                arr
            ) const;

    void getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<uint8_t> &                    arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<bool> &                       values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<int> &                        values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_2> &         values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_3> &         values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_4> &         values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<long> &                       values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int64_2> &         values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<float> &                      values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_2> &         values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_3> &         values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_4> &         values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<Octane::MatrixF> &            values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<std::string> &                values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<uint8_t> &                    values
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<bool> &                       arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<int> &                        arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_2> &         arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_3> &         arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_4> &         arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<long> &                       arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int64_2> &         arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<float> &                      arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_2> &         arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_3> &         arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_4> &         arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<Octane::MatrixF> &            arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<std::string> &                arr
            ) const;

    void getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<uint8_t> &                    arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<bool> &                       values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<int> &                        values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_2> &         values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_3> &         values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_4> &         values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<long> &                       values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int64_2> &         values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<float> &                      values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_2> &         values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_3> &         values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_4> &         values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<Octane::MatrixF> &            values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<std::string> &                values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<uint8_t> &                    values
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<bool> &                       arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<int> &                        arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_2> &         arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_3> &         arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_4> &         arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<long> &                       arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int64_2> &         arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<float> &                      arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_2> &         arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_3> &         arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_4> &         arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<Octane::MatrixF> &            arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<std::string> &                arr
            ) const;

    void getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<uint8_t> &                    arr
            ) const;

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const bool *                              values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const int32_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const int64_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int64_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const float *                             values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::MatrixF *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const char *const *                       values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const uint8_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const bool *                              arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int32_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int64_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int64_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const float *                             arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::MatrixF *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const char *const *                       arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const uint8_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const bool *                              values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const int32_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const int64_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int64_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const float *                             values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::MatrixF *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const char *const *                       values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const uint8_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const bool *                              arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int32_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int64_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int64_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const float *                             arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::MatrixF *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const char *const *                       arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const uint8_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const bool *                              values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const int32_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const int64_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int64_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const float *                             values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::MatrixF *                values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const char *const *                       values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const uint8_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const bool *                              arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int32_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int64_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int64_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const float *                             arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::MatrixF *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const char *const *                       arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    void setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const uint8_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            );

    /// Removes any animation from an attribute (if it has one).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clearAnim(
            const Octane::AttributeId   id
            );

    /// Removes any animation from an attribute (if it has one).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clearAnim(
            const char *   name
            );

    /// Removes any animation from an attribute (if it has one).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clearAnimIx(
            const uint32_t   index
            );

    /// Returns TRUE if the attribute has an animator object assigned to it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isAnimated(
            const Octane::AttributeId   id
            );

    /// Returns TRUE if the attribute has an animator object assigned to it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isAnimated(
            const char *   name
            );

    /// Returns TRUE if the attribute has an animator object assigned to it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isAnimatedIx(
            const uint32_t   index
            );

    /// Evaluates the item's attributes. This method is called internally when
    /// the evaluate parameter is set to true in the attribute set methods.
    ///
    /// For nodes like meshes and image textures it's necessary to set the attribute's
    /// values without evaluating them. Afterwards when all values are set up, this method
    /// needs to be called once.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void evaluate();

    /// Expands all items owned by the pins of the node or by the input linkers of the node graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void expand();

    /// Expands the current item out of its owner pin.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     itself if the current item is not owned by a pin
    ///     or its copy otherwise
    ApiItemProxy expandOutOfPin();

    /// Collapse this node item down into all destination pins.
    /// All of its inputs need to be collapsed. If it is impossible, the collapse will stop at this point.
    /// A node graph will only be collapsed if it has exactly one output.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the item was collapsed.
    bool collapse();

    /// Dump all attributes of this item to a text file.
    ///
    /// @param directory
    ///     Full path to a directory where the file will be written. If NULL the file will be
    /// created under user's desktop directory. The text file with be created using this item name.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void dumpAttributes(
            const char *   directory
            );

private:
    static GRPCSettings & getGRPCSettings();
};
