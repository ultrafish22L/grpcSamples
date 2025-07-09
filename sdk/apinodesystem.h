// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_NODE_SYSTEM_H_
#define _API_NODE_SYSTEM_H_ 1

#include "apianimationtimetransform.h"
#include "apiarray.h"
#include "octaneenums.h"
#include "octaneids.h"
#include "octanematrix.h"
#include "octanetime.h"
#include "octanetypes.h"
#include "octanevectypes.h"
#include "octaneversion.h"
#include "octaneinfos.h"

namespace Octane
{


class ApiItemArray;
class ApiNode;
class ApiNodeArray;
class ApiNodeGraph;
class ApiRootNodeGraph;
struct ApiAttributeInfo;
struct ApiNodeGraphInfo;
struct ApiNodeInfo;
struct ApiNodePinInfo;
struct ApiTimeSampling;


/// \brief Callback used to delete memory passed in the attach methods. It is called 
/// when octane no longer needs the memory.
///
/// @param[in]  data
///    pointer to the memory to be deleted
/// @param[in]  size
///    The size of the data in bytes
/// @param[in]  userData
///     The userData data pointer that was passed when this callback was registered.
typedef void (*AttachDataDeallocT)(
    void * data,
    size_t size,
    void * userData);

/// \brief Callback used if the ocs loader could not find an asset file
/// 
/// @param[in]  fileName
///     fileName that is missing.
/// @param[in]  userData
///     User data provided back with the callback.
/// @return  
///     Resolved file with full path. Return Null or empty string if file cannot be resolved
typedef const char* (*AssetMissingCallbackT)(
    const char *fileName,
    void       *userData);


/// Represents a path to a file in either the file system or an ORBX package
/// In paths returned by the API, both strings will be valid, although they may be empty ("").
struct ApiFilePath
{
    /// The package name, will be set to the empty string for files on the file system.
    const char *mPackage;
    /// The file name. Will be empty 
    const char *mFileName;
};


//--------------------------------------------------------------------------------------------------
/// \brief Base class providing functionality common to nodes and node graphs.
/// 
/// THREAD-SAFETY:
/// The node system is NOT thread-safe. I.e. changes in the node system need to be guarded by the
/// caller to avoid other threads accessing bogus data. All calls that pass nodes into the various
/// parts of Octane, are executed synchronously, i.e. the nodes are used during that call, but not
/// after the call has returned.
class OCTANEAPI_DECL ApiItem
{
    OCTANEAPI_NO_COPY(ApiItem);

public:

    /// Destroys this item. This will disconnect the node or the the linker nodes of the graph
    /// connected to external nodes and will destroy all items owned by this item.
    void destroy();

    /// Returns the name of this item.
    const char* name() const;

    /// Sets the name of this item.
    void setName(
        const char *name);

    /// Returns the position of the item inside its owner.
    float_2 position() const;

    /// Sets the position of this item.
    void setPosition(
        const float_2 newPos);

    /// Adds a UI operation flag to this node item and this flags will be only used when making a 
    /// direct interaction from UI.
    /// For options check UIOperationsFlag enum in octaneenums.h
    void setUIOperationFlags(
        const enum_t flags);

    /// Returns the UI operation flags of this node item.
    enum_t uiOperationFlags() const;

    /// Sets the node item to selected state (for the window opened using ApiNodeGraph::showWindow())
    void select() const;

    /// Returns the current time of this item.
    Octane::TimeT time() const;

    /// Returns the output type for this item. PT_UNKNOWN means this item
    /// cannot be connected to any pin. For graphs this means the output type of
    /// the default linker node.
    NodePinType outType() const;

    /// Returns the persistent ID of the node item. All node items of the same root node graph are
    /// guaranteed to have different persistent IDs. But items of different root node graphs can
    /// have the same persistent ID.
    uint64_t persistentId() const;

    /// Returns the unique ID of the node item. Unique IDs are unique within the same running
    /// instance of Octane. A valid node item will have a non-zero unique ID and an invalid node
    /// item will have a unique ID of zero.
    uint32_t uniqueId() const;

    /// Collects all items that are connected to this node item.
    /// Connected input graphs will be collected as a whole, i.e. the tree traversal can lead
    /// outside the graph containing the root item, but not into nested graphs.
    /// Items that are owned by node pins are not explicitly collected.
    ///
    /// @param[out]  treeitems
    ///     The found items (including rootItem) will be added to this array.
    void collectItemTree(
        ApiItemArray & treeItems);

    /// If the item is owned by a node graph, this function will remove all items owned by that node
    /// graph that are not directly/indirectly connected with the item.
    void deleteUnconnectedItems() const;

#ifndef OCTANE_DEMO_VERSION

    /// If this item stores file data that has been provided by plugins directly, this function
    /// will export that data into a file with the specified name. This is currently only supported
    /// for nodes of types NT_GEO_MESH and NT_TEX_IMAGE.
    ///
    /// @param[in]  destinationDir
    ///     Absolute path to the destination directory on disk. The export filename is determined
    ///     by Octane and can be read from the item via the A_FILENAME attribute.
    void switchToFileData(
        const char *destinationDir);

#endif

    /// Returns the version of the item.
    VersionT version() const;

#ifndef OCTANE_STANDALONE

    /// Sets the private plugin data pointer that is stored with this item. It will NOT be copied
    /// and NOT be stored persistently.
    void setPluginData(
        void *data);

    /// Returns the private plugin data pointer stored with this item.
    void* pluginData() const;

    /// Sets the private plugin data string that is stored with this item, which mus tbe null
    /// terminated. This string will be copied and stored persistently with the item.
    void setPluginDataStr(
        const char *data);

    /// Returns the private plugin data string that is stored with this item. The pointer is owned
    /// by Octane and stays valid until setPluginDataStr() is called.
    const char* pluginDataStr() const;

#endif

    /// @name Casting
    //@{

    /// Returns TRUE if this item is a graph.
    bool isGraph() const;

    /// Returns TRUE if this item is a node.
    bool isNode() const;

    /// Returns TRUE if the item is an input/output linker node.
    bool isLinker() const;

    /// Returns TRUE if the item is an input linker node.
    bool isInputLinker() const;

    /// Returns TRUE if the item is an output linker node.
    bool isOutputLinker() const;

    /// Downcasts this item to a graph. Returns NULL if this item is a node.
    const ApiNodeGraph* toGraph() const;
    
    /// Downcasts this item to a node. Returns NULL if this item is a graph.
    const ApiNode* toNode() const;

    /// Downcasts this item to a graph. Returns NULL if this item is a node. (non-const)
    ApiNodeGraph* toGraph();
    
    /// Downcasts this item to a node. Returns NULL if this item is a graph. (non-const)
    ApiNode* toNode();
 
    //@}

    /// @name Ownership
    //@{

    /// Returns TRUE if this item has an owner (graph or pin), usually always TRUE with the
    /// exception of root node graphs, which never have an owner.
    bool hasOwner() const;

    /// Returns TRUE if this item is owned by a graph.
    bool graphOwned() const; 

    /// Returns TRUE if this item is owned by a pin.
    bool pinOwned() const;

    /// Gets the graph owner (if any).
    ///
    /// @return
    ///     The graph that owns this item. NULL in case this item is the root graph
    ///     or owned by a pin.
    ApiNodeGraph* graphOwner() const;

    /// Gets the pin owner (if any).
    ///
    /// @param[out] pinIx
    ///     Index of the pin on the returned node. (Only valid if the returned node
    ///     is not NULL).
    /// @return
    ///     The node which has the pin owning this item. NULL in case this item is
    ///     not owned by a pin.
    ApiNode* pinOwner(
        uint32_t &pinIx) const;

    /// Returns the root node graph which contains this node item. If this item is a root node graph
    /// it returns itself.
    const ApiRootNodeGraph& rootGraph() const;

    /// Returns the root node graph which contains this node item. If this item is a root node graph
    /// it returns itself.
    ApiRootNodeGraph& rootGraph();
    //@}

    /// @name Attributes
    //@{

    /// Returns the number of attributes of this item.
    uint32_t attrCount() const;

    /// Returns TRUE if an attribute with the specified ID exists.
    bool hasAttr(
        const AttributeId id) const;

    /// Returns TRUE if an attribute with the specified name exists.
    bool hasAttr(
        const char *name) const;

    /// Returns TRUE if an attribute with this ID exists and returns its index in "foundIndex".
    bool findAttr(
        const AttributeId id,
        uint32_t          &foundIndex) const;

    /// Returns TRUE if an attribute with this name exists and returns its index in "foundIndex".
    bool findAttr(
        const char *name,
        uint32_t   &foundIndex) const;

    /// Returns the ID of attribute provided by it's name. Returns A_UNKNOWN when
    /// there's no such attribute.
    AttributeId attrId(
        const char *name) const;

    /// Returns the ID of the attribute at index. Returns A_UNKNOWN when there's
    /// no such attribute.
    AttributeId attrIdIx(
        const uint32_t index) const;

    /// Returns the name of the attribute at the provided ID or "unknown" if there's no such attribute.
    const char* attrName(
        const AttributeId id) const;

    /// Returns the name of the attribute at the index or "unknown" if there's no such attribute.
    const char* attrNameIx(
        const uint32_t index) const;

    /// Returns the type of the attribute identified by it's ID. Returns AT_UNKNOWN when
    /// there's no such attribute.
    AttributeType attrType(
        const AttributeId id) const;

    /// Returns the type of the attribute identified by it's name. Returns AT_UNKNOWN when
    /// there's no such attribute.
    AttributeType attrType(
        const char *attrName) const;

    /// Returns the type of the attribute at the index. Returns AT_UNKNOWN when
    /// there's no such attribute.
    AttributeType attrTypeIx(
        const uint32_t index) const;

    /// Returns the info for the attribute identified by the ID. Returns the fallback attribute
    /// info (with attribute ID A_UNKNOWN) if there is no such attribute.
    const ApiAttributeInfo& attrInfo(
        const AttributeId id) const;

    /// Returns the info for the attribute identified by the name. Returns the fallback attribute
    /// info (with attribute ID A_UNKNOWN) if there is no such attribute.
    const ApiAttributeInfo& attrInfo(
        const char *name) const;

    /// Returns the info for the attribute at index. Returns the fallback attribute
    /// info (with attribute ID A_UNKNOWN) if there is no such attribute.
    const ApiAttributeInfo& attrInfoIx(
        const uint32_t index) const;

    /// Returns TRUE if any of the attributes are flagged dirty.
    bool attrAreDirty() const;

    /// Returns TRUE if the attribute is flagged dirty.
    bool isDirtyAttr(
        const AttributeId id) const;

    /// Returns TRUE if the attribute is flagged dirty.
    bool isDirtyAttr(
        const char *name) const;

    /// Returns TRUE if the attribute is flagged dirty.
    bool isDirtyAttrIx(
        const uint32_t index) const;

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
    void copyAttrFrom(
        const Octane::AttributeId destId,
        const ApiItem             &srcItem,
        const Octane::AttributeId srcId,
        const bool                evaluate=true);

    /// Copies the attribute into our attribute, specified by its name.
    void copyAttrFrom(
        const Octane::AttributeId destId,
        const ApiItem             &srcItem,
        const char                *srcAttrName,
        const bool                evaluate=true);

    /// Copies the attribute into our attribute, specified by its index.
    void copyAttrFromIx(
        const Octane::AttributeId destId,
        const ApiItem             &srcItem,
        const uint32_t            srcAttrIx,
        const bool                evaluate=true);

    /// Copies all matching attributes from another item into this item.
    void copyAttrFrom(
        const ApiItem &srcItem,
        const bool    evaluate=true);

    /// Clears all attributes.
    void clearAllAttr(
        const bool evaluate);

    /// Clears the attribute specified by its ID.
    void clearAttr(
        const AttributeId id,
        const bool        evaluate=true);

    /// Clears the attribute specified by its name.
    void clearAttr(
        const char *name,
        const bool evaluate=true);

    /// Clears the attribute specified by its index.
    void clearAttrIx(
        const uint32_t index,
        const bool     evaluate=true);

    //@}

    /// @name Attribute getters
    /// Return the value for the attribute, selecting by attribute ID
    //@{
    bool         getBool       (const AttributeId id) const;
    int32_t      getInt        (const AttributeId id) const;
    int32_2      getInt2       (const AttributeId id) const;
    int32_3      getInt3       (const AttributeId id) const;
    int32_4      getInt4       (const AttributeId id) const;
    int64_t      getLong       (const AttributeId id) const;
    int64_2      getLong2      (const AttributeId id) const;
    float        getFloat      (const AttributeId id) const;
    float_2      getFloat2     (const AttributeId id) const;
    float_3      getFloat3     (const AttributeId id) const;
    float_4      getFloat4     (const AttributeId id) const;
    MatrixF      getMatrix     (const AttributeId id) const;
    const char*  getString     (const AttributeId id) const;
    BoolArrayT   getBoolArray  (const AttributeId id) const;
    IntArrayT    getIntArray   (const AttributeId id) const;
    Int2ArrayT   getInt2Array  (const AttributeId id) const;
    Int3ArrayT   getInt3Array  (const AttributeId id) const;
    Int4ArrayT   getInt4Array  (const AttributeId id) const;
    LongArrayT   getLongArray  (const AttributeId id) const;
    Long2ArrayT  getLong2Array (const AttributeId id) const;
    MatrixArrayT getMatrixArray(const AttributeId id) const;
    FloatArrayT  getFloatArray (const AttributeId id) const;
    Float2ArrayT getFloat2Array(const AttributeId id) const;
    Float3ArrayT getFloat3Array(const AttributeId id) const;
    Float4ArrayT getFloat4Array(const AttributeId id) const;
    StringArrayT getStringArray(const AttributeId id) const;
    ByteArrayT   getByteArray  (const AttributeId id) const;
    //@}

    /// @name Attribute getters (2)
    /// Return the value for the attribute, selecting by attribute name
    //@{
    bool         getBool       (const char *name) const;
    int32_t      getInt        (const char *name) const;
    int32_2      getInt2       (const char *name) const;
    int32_3      getInt3       (const char *name) const;
    int32_4      getInt4       (const char *name) const;
    int64_t      getLong       (const char *name) const;
    int64_2      getLong2      (const char *name) const;
    float        getFloat      (const char *name) const;
    float_2      getFloat2     (const char *name) const;
    float_3      getFloat3     (const char *name) const;
    float_4      getFloat4     (const char *name) const;
    MatrixF      getMatrix     (const char *name) const;
    const char*  getString     (const char *name) const;
    BoolArrayT   getBoolArray  (const char *name) const;
    IntArrayT    getIntArray   (const char *name) const;
    Int2ArrayT   getInt2Array  (const char *name) const;
    Int3ArrayT   getInt3Array  (const char *name) const;
    Int4ArrayT   getInt4Array  (const char *name) const;
    LongArrayT   getLongArray  (const char *name) const;
    Long2ArrayT  getLong2Array (const char *name) const;
    FloatArrayT  getFloatArray (const char *name) const;
    Float2ArrayT getFloat2Array(const char *name) const;
    Float3ArrayT getFloat3Array(const char *name) const;
    Float4ArrayT getFloat4Array(const char *name) const;
    MatrixArrayT getMatrixArray(const char *name) const;
    StringArrayT getStringArray(const char *name) const;
    ByteArrayT   getByteArray  (const char *name) const;
    //@}

    /// @name Attribute getters (3)
    /// Return the value for the attribute, selecting by attribute index
    //@{
    bool         getBoolIx       (const uint32_t index) const;
    int32_t      getIntIx        (const uint32_t index) const;
    int32_2      getInt2Ix       (const uint32_t index) const;
    int32_3      getInt3Ix       (const uint32_t index) const;
    int32_4      getInt4Ix       (const uint32_t index) const;
    int64_t      getLongIx       (const uint32_t index) const;
    int64_2      getLong2Ix      (const uint32_t index) const;
    float        getFloatIx      (const uint32_t index) const;
    float_2      getFloat2Ix     (const uint32_t index) const;
    float_3      getFloat3Ix     (const uint32_t index) const;
    float_4      getFloat4Ix     (const uint32_t index) const;
    MatrixF      getMatrixIx     (const uint32_t index) const;
    const char*  getStringIx     (const uint32_t index) const;
    BoolArrayT   getBoolArrayIx  (const uint32_t index) const;
    IntArrayT    getIntArrayIx   (const uint32_t index) const;
    Int2ArrayT   getInt2ArrayIx  (const uint32_t index) const;
    Int3ArrayT   getInt3ArrayIx  (const uint32_t index) const;
    Int4ArrayT   getInt4ArrayIx  (const uint32_t index) const;
    LongArrayT   getLongArrayIx  (const uint32_t index) const;
    Long2ArrayT  getLong2ArrayIx (const uint32_t index) const;
    FloatArrayT  getFloatArrayIx (const uint32_t index) const;
    Float2ArrayT getFloat2ArrayIx(const uint32_t index) const;
    Float3ArrayT getFloat3ArrayIx(const uint32_t index) const;
    Float4ArrayT getFloat4ArrayIx(const uint32_t index) const;
    MatrixArrayT getMatrixArrayIx(const uint32_t index) const;
    StringArrayT getStringArrayIx(const uint32_t index) const;
    ByteArrayT   getByteArrayIx  (const uint32_t index) const;
    //@}

    /// @name Attribute getters (4)
    /// Get the value for the attribute, selecting by attribute ID
    //@{
    void get(const AttributeId id,  bool         &value) const;
    void get(const AttributeId id,  int32_t      &value) const;
    void get(const AttributeId id,  int32_2      &value) const;
    void get(const AttributeId id,  int32_3      &value) const;
    void get(const AttributeId id,  int32_4      &value) const;
    void get(const AttributeId id,  int64_t      &value) const;
    void get(const AttributeId id,  int64_2      &value) const;
    void get(const AttributeId id,  float        &value) const;
    void get(const AttributeId id,  float_2      &value) const;
    void get(const AttributeId id,  float_3      &value) const;
    void get(const AttributeId id,  float_4      &value) const;
    void get(const AttributeId id,  MatrixF      &value) const;
    void get(const AttributeId id,  const char*  &value) const;
    void get(const AttributeId id,  BoolArrayT   &arr  ) const;
    void get(const AttributeId id,  IntArrayT    &arr  ) const;
    void get(const AttributeId id,  Int2ArrayT   &arr  ) const;
    void get(const AttributeId id,  Int3ArrayT   &arr  ) const;
    void get(const AttributeId id,  Int4ArrayT   &arr  ) const;
    void get(const AttributeId id,  LongArrayT   &arr  ) const;
    void get(const AttributeId id,  Long2ArrayT  &arr  ) const;
    void get(const AttributeId id,  FloatArrayT  &arr  ) const;
    void get(const AttributeId id,  Float2ArrayT &arr  ) const;
    void get(const AttributeId id,  Float3ArrayT &arr  ) const;
    void get(const AttributeId id,  Float4ArrayT &arr  ) const;
    void get(const AttributeId id,  MatrixArrayT &arr  ) const;
    void get(const AttributeId id,  StringArrayT &arr  ) const;
    void get(const AttributeId id,  ByteArrayT   &arr  ) const;
    //@}

    /// @name Attribute getters (5)
    /// Get the value for the attribute, selecting by attribute name
    //@{
    void get(const char *name,  bool         &value) const;
    void get(const char *name,  int32_t      &value) const;
    void get(const char *name,  int32_2      &value) const;
    void get(const char *name,  int32_3      &value) const;
    void get(const char *name,  int32_4      &value) const;
    void get(const char *name,  int64_t      &value) const;
    void get(const char *name,  int64_2      &value) const;
    void get(const char *name,  float        &value) const;
    void get(const char *name,  float_2      &value) const;
    void get(const char *name,  float_3      &value) const;
    void get(const char *name,  float_4      &value) const;
    void get(const char *name,  MatrixF      &value) const;
    void get(const char *name,  const char*  &value) const;
    void get(const char *name,  BoolArrayT   &arr  ) const;
    void get(const char *name,  IntArrayT    &arr  ) const;
    void get(const char *name,  Int2ArrayT   &arr  ) const;
    void get(const char *name,  Int3ArrayT   &arr  ) const;
    void get(const char *name,  Int4ArrayT   &arr  ) const;
    void get(const char *name,  LongArrayT   &arr  ) const;
    void get(const char *name,  Long2ArrayT  &arr  ) const;
    void get(const char *name,  FloatArrayT  &arr  ) const;
    void get(const char *name,  Float2ArrayT &arr  ) const;
    void get(const char *name,  Float3ArrayT &arr  ) const;
    void get(const char *name,  Float4ArrayT &arr  ) const;
    void get(const char *name,  MatrixArrayT &arr  ) const;
    void get(const char *name,  StringArrayT &arr  ) const;
    void get(const char *name,  ByteArrayT   &arr  ) const;
    //@}

    /// @name Attribute getters (6)
    /// Get the value for the attribute, selecting by attribute index
    //@{
    void getIx(const uint32_t index,  bool         &value) const;
    void getIx(const uint32_t index,  int32_t      &value) const;
    void getIx(const uint32_t index,  int32_2      &value) const;
    void getIx(const uint32_t index,  int32_3      &value) const;
    void getIx(const uint32_t index,  int32_4      &value) const;
    void getIx(const uint32_t index,  int64_t      &value) const;
    void getIx(const uint32_t index,  int64_2      &value) const;
    void getIx(const uint32_t index,  float        &value) const;
    void getIx(const uint32_t index,  float_2      &value) const;
    void getIx(const uint32_t index,  float_3      &value) const;
    void getIx(const uint32_t index,  float_4      &value) const;
    void getIx(const uint32_t index,  MatrixF      &value) const;
    void getIx(const uint32_t index,  const char*  &value) const;
    void getIx(const uint32_t index,  BoolArrayT   &arr  ) const;
    void getIx(const uint32_t index,  IntArrayT    &arr  ) const;
    void getIx(const uint32_t index,  Int2ArrayT   &arr  ) const;
    void getIx(const uint32_t index,  Int3ArrayT   &arr  ) const;
    void getIx(const uint32_t index,  Int4ArrayT   &arr  ) const;
    void getIx(const uint32_t index,  LongArrayT   &arr  ) const;
    void getIx(const uint32_t index,  Long2ArrayT  &arr  ) const;
    void getIx(const uint32_t index,  FloatArrayT  &arr  ) const;
    void getIx(const uint32_t index,  Float2ArrayT &arr  ) const;
    void getIx(const uint32_t index,  Float3ArrayT &arr  ) const;
    void getIx(const uint32_t index,  Float4ArrayT &arr  ) const;
    void getIx(const uint32_t index,  MatrixArrayT &arr  ) const;
    void getIx(const uint32_t index,  StringArrayT &arr  ) const;
    void getIx(const uint32_t index,  ByteArrayT   &arr  ) const;
    //@}

    /// @name Attribute setters (1)
    /// Set the value for the attribute, selecting by attribute ID
    //@{
    void set(const AttributeId id,  const bool         value,  const bool evaluate=true);
    void set(const AttributeId id,  const int32_t      value,  const bool evaluate=true);
    void set(const AttributeId id,  const int32_2     &value,  const bool evaluate=true);
    void set(const AttributeId id,  const int32_3     &value,  const bool evaluate=true);
    void set(const AttributeId id,  const int32_4     &value,  const bool evaluate=true);
    void set(const AttributeId id,  const int64_t      value,  const bool evaluate=true);
    void set(const AttributeId id,  const int64_2     &value,  const bool evaluate=true);
    void set(const AttributeId id,  const float        value,  const bool evaluate=true);
    void set(const AttributeId id,  const float_2     &value,  const bool evaluate=true);
    void set(const AttributeId id,  const float_3     &value,  const bool evaluate=true);
    void set(const AttributeId id,  const float_4     &value,  const bool evaluate=true);
    void set(const AttributeId id,  const MatrixF     &value,  const bool evaluate=true);
    void set(const AttributeId id,  const char *       value,  const bool evaluate=true);
    void set(const AttributeId id,  const bool        *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const int32_t     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const int32_2     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const int32_3     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const int32_4     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const int64_t     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const int64_2     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const float       *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const float_2     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const float_3     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const float_4     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const MatrixF     *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const char *const *arr,  const size_t size,  const bool evaluate=true);
    void set(const AttributeId id,  const uint8_t     *arr,  const size_t size,  const bool evaluate=true);
    //@}

    /// @name Attribute setters (2)
    /// Attach existing data to the attribute, selecting by attribute ID. It is the responsibility 
    /// of the caller to release the memory.
    //@{
    void attach(const AttributeId id,  const bool        *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const int32_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const int32_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const int32_3     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const int32_4     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const int64_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const int64_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const float       *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const float_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const float_3     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const float_4     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const MatrixF     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const AttributeId id,  const uint8_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    //@}

    /// @name Attribute setters (2)
    /// Set the value for the attribute, selecting by attribute name
    //@{
    void set(const char *name,  const bool         value,  const bool evaluate=true);
    void set(const char *name,  const int32_t      value,  const bool evaluate=true);
    void set(const char *name,  const int32_2     &value,  const bool evaluate=true);
    void set(const char *name,  const int32_3     &value,  const bool evaluate=true);
    void set(const char *name,  const int32_4     &value,  const bool evaluate=true);
    void set(const char *name,  const int64_t      value,  const bool evaluate=true);
    void set(const char *name,  const int64_2     &value,  const bool evaluate=true);
    void set(const char *name,  const float        value,  const bool evaluate=true);
    void set(const char *name,  const float_2     &value,  const bool evaluate=true);
    void set(const char *name,  const float_3     &value,  const bool evaluate=true);
    void set(const char *name,  const float_4     &value,  const bool evaluate=true);
    void set(const char *name,  const MatrixF     &value,  const bool evaluate=true);
    void set(const char *name,  const char *       value,  const bool evaluate=true);
    void set(const char *name,  const bool        *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const int32_t     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const int32_2     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const int32_3     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const int32_4     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const int64_t     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const int64_2     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const float       *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const float_2     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const float_3     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const float_4     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const MatrixF     *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const char *const *arr,  const size_t size,  const bool evaluate=true);
    void set(const char *name,  const uint8_t     *arr,  const size_t size,  const bool evaluate=true);
    //@}

    /// @name Attribute setters (2)
    /// Attach existing data to the attribute, selecting by attribute name. It is the responsibility 
    /// of the caller to release the memory.
    //@{
    void attach(const char *name,  const bool        *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const int32_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const int32_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const int32_3     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const int32_4     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const int64_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const int64_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const float       *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const float_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const float_3     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const float_4     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const MatrixF     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attach(const char *name,  const uint8_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    //@}

    /// @name Attribute setters (3)
    /// Set the value for the attribute, selecting by attribute index
    //@{
    void setIx(const uint32_t index,  const bool         value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int32_t      value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int32_2     &value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int32_3     &value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int32_4     &value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int64_t      value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int64_2     &value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const float        value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const float_2     &value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const float_3     &value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const float_4     &value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const MatrixF     &value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const char *       value,  const bool evaluate=true);
    void setIx(const uint32_t index,  const bool        *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int32_t     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int32_2     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int32_3     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int32_4     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int64_t     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const int64_2     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const float       *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const float_2     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const float_3     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const float_4     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const MatrixF     *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const char *const *arr,  const size_t size,  const bool evaluate=true);
    void setIx(const uint32_t index,  const uint8_t     *arr,  const size_t size,  const bool evaluate=true);
    //@}

    /// @name Attribute setters (2)
    /// Attach existing data to the attribute, selecting by attribute index. It is the responsibility 
    /// of the caller to release the memory.
    //@{
    void attachIx(const uint32_t index,  const bool        *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const int32_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const int32_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const int32_3     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const int32_4     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const int64_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const int64_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const float       *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const float_2     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const float_3     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const float_4     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const MatrixF     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const char *const *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    void attachIx(const uint32_t index,  const uint8_t     *arr,  const size_t size,  AttachDataDeallocT callback,  void * userData = nullptr,  const bool evaluate=true);
    //@}

    /// @name Animation getters
    ///
    /// These getters return the raw data that was copied into the attribute. This is only possible
    /// if internally a "RegularAnimator" is used, which is the case if the animated data was set via
    /// the API (see the description of setAnim() below). If the attribute doesn't have a
    /// "RegularAnimator", an empty array is returned. The data layout for animated array attributes
    /// is the same as described for setAnim().
    ///
    /// Get the animated value for the attribute, selecting by attribute ID
    //@{
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  BoolArrayT   &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  IntArrayT    &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  Int2ArrayT   &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  Int3ArrayT   &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  Int4ArrayT   &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  LongArrayT   &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  Long2ArrayT  &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  FloatArrayT  &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  Float2ArrayT &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  Float3ArrayT &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  Float4ArrayT &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  MatrixArrayT &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  StringArrayT &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  ByteArrayT   &values) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  BoolArrayT   &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  IntArrayT    &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  Int2ArrayT   &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  Int3ArrayT   &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  Int4ArrayT   &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  LongArrayT   &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  Long2ArrayT  &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  FloatArrayT  &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  Float2ArrayT &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  Float3ArrayT &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  Float4ArrayT &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  MatrixArrayT &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  StringArrayT &arr) const;
    void getAnim(const AttributeId id,  ApiTimeSampling &times,  size_t &numTimes,  ByteArrayT   &arr) const;
    //@}

    /// @name Animation getters (2)
    /// Get the animated value for the attribute, selecting by attribute name
    //@{
    void getAnim(const char *name,  ApiTimeSampling &times,  BoolArrayT   &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  IntArrayT    &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  Int2ArrayT   &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  Int3ArrayT   &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  Int4ArrayT   &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  LongArrayT   &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  Long2ArrayT  &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  FloatArrayT  &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  Float2ArrayT &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  Float3ArrayT &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  Float4ArrayT &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  MatrixArrayT &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  StringArrayT &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  ByteArrayT   &values) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  BoolArrayT   &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  IntArrayT    &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  Int2ArrayT   &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  Int3ArrayT   &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  Int4ArrayT   &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  LongArrayT   &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  Long2ArrayT  &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  FloatArrayT  &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  Float2ArrayT &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  Float3ArrayT &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  Float4ArrayT &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  MatrixArrayT &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  StringArrayT &arr) const;
    void getAnim(const char *name,  ApiTimeSampling &times,  size_t &numTimes,  ByteArrayT   &arr) const;
    //@}

    /// @name Animation getters (3)
    /// Get the animated value for the attribute, selecting by attribute index
    //@{
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  BoolArrayT   &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  IntArrayT    &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  Int2ArrayT   &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  Int3ArrayT   &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  Int4ArrayT   &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  LongArrayT   &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  Long2ArrayT  &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  FloatArrayT  &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  Float2ArrayT &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  Float3ArrayT &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  Float4ArrayT &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  MatrixArrayT &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  StringArrayT &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  ByteArrayT   &values) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  BoolArrayT   &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  IntArrayT    &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  Int2ArrayT   &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  Int3ArrayT   &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  Int4ArrayT   &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  LongArrayT   &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  Long2ArrayT  &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  FloatArrayT  &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  Float2ArrayT &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  Float3ArrayT &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  Float4ArrayT &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  MatrixArrayT &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  StringArrayT &arr) const;
    void getAnimIx(const uint32_t index,  ApiTimeSampling &times,  size_t &numTimes,  ByteArrayT   &arr) const;
    //@}

    /// @name Animation setters
    ///
    /// The time pattern and value arrays are copied into an internal "RegularAnimator" and can be
    /// freed after this call. All animated values that are stored in a "RegularAnimator" can be
    /// fetched via getAnim().
    ///
    /// The array type must exactly match the attribute type and the functions always come in two
    /// flavours: One for scalar attributes and one for array attributes. To set animated array
    /// attributes, you still pass in only one array, but this array stores all time samples of all
    /// array elements. If for example, you have 5 array elements (a,b,c,d,e) to animate for 3 time
    /// samples (0,1,2), and a0 represents the value for element a at time 0, the array would have
    /// size 15 and contain the following entries:
    ///  [a0 a1 a2 b0 b1 b2 c0 c1 c2 d0 d1 d2 e0 e1 e2]
    ///
    /// Set the animated value for the attribute, selecting by attribute ID
    //@{
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const bool        *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const int32_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const int32_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const int32_3     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const int32_4     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const int64_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const int64_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const float       *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const float_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const float_3     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const float_4     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const MatrixF     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const char *const *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const uint8_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const bool        *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_3     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_4     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const int64_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const int64_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const float       *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const float_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const float_3     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const float_4     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const MatrixF     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const char *const *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const AttributeId id,  const ApiTimeSampling &times,  const size_t numTimes,  const uint8_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    //@}

    /// @name Animation setters (2)
    /// Set the animated value for the attribute, selecting by attribute name
    //@{
    void setAnim(const char *name,  const ApiTimeSampling &times,  const bool        *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const int32_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const int32_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const int32_3     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const int32_4     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const int64_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const int64_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const float       *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const float_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const float_3     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const float_4     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const MatrixF     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const char *const *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const uint8_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const bool        *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_3     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_4     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const int64_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const int64_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const float       *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const float_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const float_3     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const float_4     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const MatrixF     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const char *const *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnim(const char *name,  const ApiTimeSampling &times,  const size_t numTimes,  const uint8_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    //@}

    /// @name Animation setters (3)
    /// Set the animated value for the attribute, selecting by attribute index
    //@{
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const bool        *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const int32_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const int32_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const int32_3     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const int32_4     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const int64_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const int64_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const float       *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const float_2     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const float_3     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const float_4     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const MatrixF     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const char *const *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const uint8_t     *values,  const size_t numValues,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const bool        *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_3     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const int32_4     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const int64_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const int64_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const float       *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const float_2     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const float_3     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const float_4     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const MatrixF     *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const char *const *arr,  const size_t arrSize,  const bool evaluate=true);
    void setAnimIx(const uint32_t index,  const ApiTimeSampling &times,  const size_t numTimes,  const uint8_t     *arr,  const size_t arrSize,  const bool evaluate=true);
    //@}

    /// Removes any animation from an attribute (if it has one).
    void clearAnim  (const AttributeId id);
    /// Removes any animation from an attribute (if it has one).
    void clearAnim  (const char        *name);
    /// Removes any animation from an attribute (if it has one).
    void clearAnimIx(const uint32_t    index);

    /// Returns TRUE if the attribute has an animator object assigned to it.
    bool isAnimated  (const AttributeId id);
    /// Returns TRUE if the attribute has an animator object assigned to it.
    bool isAnimated  (const char        *name);
    /// Returns TRUE if the attribute has an animator object assigned to it.
    bool isAnimatedIx(const uint32_t    index);

    /// Evaluates the item's attributes. This method is called internally when
    /// the evaluate parameter is set to true in the attribute set methods.
    ///
    /// For nodes like meshes and image textures it's necessary to set the attribute's
    /// values without evaluating them. Afterwards when all values are set up, this method
    /// needs to be called once.
    void evaluate();

    /// Expands all items owned by the pins of the node or by the input linkers of the node graph.
    void expand();

    /// Expands the current item out of its owner pin.
    ///
    /// @return
    ///     itself if the current item is not owned by a pin
    ///     or its copy otherwise
    ApiItem* expandOutOfPin();

    /// Collapse this node item down into all destination pins.
    /// All of its inputs need to be collapsed. If it is impossible, the collapse will stop at this point.
    /// A node graph will only be collapsed if it has exactly one output.
    ///
    /// @return
    ///     TRUE if the item was collapsed.
    bool collapse();

#ifndef OCTANE_DEMO_VERSION

    /// Dump all attributes of this item to a text file.
    ///
    /// @param directory
    ///     Full path to a directory where the file will be written. If NULL the file will be 
    /// created under user's desktop directory. The text file with be created using this item name.
    void dumpAttributes(
        const char *directory);

#endif

};



//--------------------------------------------------------------------------------------------------
///
class OCTANEAPI_DECL ApiNode : public ApiItem
{
    OCTANEAPI_NO_COPY(ApiNode);

    friend class ApiNodeGraph;
    friend class ApiRenderEngine;
    friend class PluginApi;
    friend class ApiChangeManager;

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
    /// @return
    ///     Pointer to the created node or NULL if creation failed.
    static ApiNode* create(
        const Octane::NodeType type,
        ApiNodeGraph           &ownerGraph,
        const bool             configurePins=true);

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
    /// @return
    ///     true if a dynamic pin was added.
    bool addDynamicPinForLoading(
        const Octane::NodePinType type,
        const char                *name);

    /// Returns the info for this node.
    const ApiNodeInfo& info() const;

    /// Returns the type of this node.
    Octane::NodeType type() const;
    
    /// Texture nodes that represent OSL code can defined the texture value type of their output.
    ///
    /// @return
    ///     The TextureValueType of the output texture value (default is TEXTURE_VALUE_TYPE_UNKNOWN).
    TextureValueType outputTextureValueType() const;
    
    /// Get the texture type configuration the node is currently set to
    ///
    /// @return
    ///     The texture type configuration the node is currently set to (nullptr if not a typed texture node).
    const Octane::ApiTextureNodeTypeInfo::Configuration * textureTypeConfiguration() const;
    
    /// Set the typed texture node to a given texture type configuration
    ///
    /// @param[in]  configuration
    ///     A texture type configuration
    /// @param[in]  evaluate
    ///     Whether to evaluate the node after reconfiguration (default is TRUE)
    /// @return
    ///     TRUE if setting the node to the provided texture type configuration succeeded, FALSE otherwise
    bool setTextureTypeConfiguration(
        const Octane::ApiTextureNodeTypeInfo::Configuration & configuration,
        const bool evaluate = true);
    
    /// Creates default nodes for empty/unconnected pins that have a default node.
    void configureEmptyPins();

    /// Returns the total (static + dynamic) number of pins of this node.
    uint32_t pinCount() const;

    /// Returns the number of static pins.
    uint32_t staticPinCount() const;

    /// Returns the number of dynamic pins.
    uint32_t dynPinCount() const;

    /// Returns TRUE if a static pin with the specified ID exists.
    bool hasPin(
        const PinId pinId) const;

    /// Returns TRUE if a static pin with the specified name exists.
    bool hasPin(
        const char *pinName) const;

    /// Returns TRUE if a static or dynamic pin with the specified index exists.
    bool hasPinIx(
        const uint32_t index) const;

    /// Returns TRUE if a static pin with this ID exists and returns its index in "foundIndex".
    bool findPin(
        const PinId id,
        uint32_t    &foundIndex) const;

    /// Returns TRUE if a static or dynamic pin with this name exists and returns its index in
    /// "foundIndex".
    bool findPin(
        const char *name,
        uint32_t   &foundIndex) const;

    /// Returns the pin id of a static pin based on its name. Returns P_UNKNOWN if there's no such
    /// pin.
    PinId pinId(
        const char *name) const;

    /// Returns the pin id of a static pin based on its index. Returns P_UNKNOWN if there's no such
    /// pin.
    PinId pinIdIx(
        const uint32_t index) const;

    /// Returns the name of a static pin based on its ID. Returns "" if no such pin exists.
    const char* pinName(
        const Octane::PinId id) const;

    /// Returns the name of a static or dynamic pin based on its index. Returns "" if no such pin
    /// exists.
    const char* pinNameIx(
        const uint32_t index) const;

    /// Returns the label of a static pin specified by its ID. Returns "" if no such pin exists.
    const char* pinLabel(
        const Octane::PinId id) const;

    /// Returns the label of a static or dynamic pin specified by its name. Returns "" if no such
    /// pin exists.
    const char* pinLabel(
        const char *name) const;

    /// Returns the label of a static or dynamic pin specified by its index. Returns "" if no such
    /// pin exists.
    const char* pinLabelIx(
        const uint32_t index) const;

    /// Returns the pin type of a static pin based on its pin id. Returns PT_UNKNOWN if no such pin
    /// exists.
    NodePinType pinType(
        const Octane::PinId id) const;

    /// Returns the pin type of the static or dynamic pin with the specified name. Returns
    /// PT_UNKNOWN if no such pin exists.
    NodePinType pinType(
        const char *name) const;

    /// Returns the pin type of the static or dynamic pin at the specified index. Returns PT_UNKNOWN
    /// if no such pin exists.
    NodePinType pinTypeIx(
        const uint32_t index) const;

    /// Texture nodes that represent OSL code can defined the texture value type of their pins.
    /// It can be decided dynamically for certain nodes that need it to be, based on user selected types on the node.
    ///
    /// @param[in]  name
    ///     The name of the pin asked about for its TextureValueType.
    /// @return
    ///     The TextureValueType of the value carried by the provided pin (default is TEXTURE_VALUE_TYPE_UNKNOWN).
    TextureValueType pinTextureValueType(
        const char *name) const;
    
    /// Texture nodes that represent OSL code can defined the texture value type of their pins.
    /// It can be decided dynamically for certain nodes that need it to be, based on user selected types on the node.
    ///
    /// @param[in]  index
    ///     The index of the pin asked about for its TextureValueType.
    /// @return
    ///     The TextureValueType of the value carried by the provided pin (default is TEXTURE_VALUE_TYPE_UNKNOWN).
    TextureValueType pinTextureValueTypeIx(
        const uint32_t index) const;
    
    /// Returns the pin info of a static pin based on its pin id. Returns the fallback pin info
    /// (with pin ID P_UNKNOWN) if there is no such pin.
    const ApiNodePinInfo& pinInfo(
        const PinId id) const;

    /// Returns the pin info of a static or dynamic pin based on the pin name. Returns the fallback
    /// pin info (with pin ID P_UNKNOWN) if there is no such pin. Note that dynamic pins also have
    /// pin ID P_UNKNOWN.
    const ApiNodePinInfo& pinInfo(
        const char *name) const;

    /// Returns the pin info of a static or dynamic pin based on its index. Returns the fallback
    /// pin info (with pin ID P_UNKNOWN) if there is no such pin. Note that dynamic pins also have
    /// pin ID P_UNKNOWN.
    const ApiNodePinInfo& pinInfoIx(
        const uint32_t index) const;

    /// Returns TRUE if any of the pins are flagged dirty.
    bool pinsAreDirty() const;

    /// Returns TRUE if the pin is flagged dirty.
    bool isDirtyPin(
        const PinId pinId) const;

    /// Returns TRUE if the pin is flagged dirty.
    bool isDirtyPin(
        const char *pinName) const;

    /// Returns TRUE if the pin is flagged dirty.
    bool isDirtyPinIx(
        const uint32_t pinIx) const;

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
    /// @return
    ///     TRUE if the connection can be made. FALSE otherwise.
    bool canConnectTo(
        const PinId   pinId,
        const ApiNode *sourceNode,
        const bool    doCycleCheck=false) const;

    /// Same as above but identifying the pin by name.
    bool canConnectTo(
        const char    *pinName,
        const ApiNode *sourceNode,
        const bool    doCycleCheck=false) const;

    /// Same as above but identifying the pin by index.
    bool canConnectToIx(
        const uint32_t pinIx,
        const ApiNode  *sourceNode,
        const bool     doCycleCheck=false) const;

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
    void connectTo(
        const PinId pinId,
        ApiNode     *sourceNode,
        const bool  evaluate=true,
        const bool  doCycleCheck=false);

    /// Same as above but identifying the pin by name.
    void connectTo(
        const char *pinName,
        ApiNode    *sourceNode,
        const bool  evaluate=true,
        const bool doCycleCheck=false);

    /// Same as above but identifying the pin by index.
    void connectToIx(
        const uint32_t pinIdx,
        ApiNode        *sourceNode,
        const bool     evaluate=true,
        const bool     doCycleCheck=false);

    /// Returns the node connected to a pin.
    ///
    /// @param[in]  pinId
    ///     Id identifying the pin.
    /// @param[in]  enterWrapperNodes
    ///     If set to TRUE the connected node is a built-in wrapper node, then the returned node
    ///     will be the output linker of the wrapped script graph.
    /// @return
    ///     A pointer to the connected node (if there's one), NULL otherwise.
    ApiNode* connectedNode(
        const Octane::PinId pinId,
        const bool          enterWrapperNode = false) const;

    /// Same as above but identifies the pin based on name.
    ApiNode* connectedNode(
        const char *const pinName,
        const bool        enterWrapperNode = false) const;

    /// Same as above but identifies the pin based on index.
    ApiNode* connectedNodeIx(
        const uint32_t pinIx,
        const bool     enterWrapperNode = false) const;

    /// Returns the input node of a pin, skipping linker nodes.
    ///
    /// @param[in]  pinId
    ///     Id identifying the pin.
    /// @param[in]  enterWrapperNodes
    ///     Set to TRUE if built-in wrapper nodes should be entered (see connectedNode()).
    ///     The default value is FALSE.
    /// @return
    ///     A pointer to the input node (if there's one), NULL otherwise.
    ApiNode* inputNode(
        const Octane::PinId pinId,
        const bool          enterWrapperNodes = false) const;

    /// Same as above but identifies the pin based on name.
    ApiNode* inputNode(
        const char *const pinName,
        const bool        enterWrapperNodes = false) const;

    /// Same as above but identifies the pin based on index.
    ApiNode* inputNodeIx(
        const uint32_t index,
        const bool     enterWrapperNodes = false) const;

    /// Returns the destination nodes of this node.
    ///
    /// @param[out] nodes
    ///     Array of the destination nodes.
    /// @param[out]  pinNames
    ///     Array of the destination pin names. This array is owned by the API and
    ///     valid until the next call to this function. This array has the same length
    ///     as nodes and contains the id of the pin on each corresponding node.
    ///     (e.g. pinNames[0] is the id of the pin on node nodes[0])
    void destinationNodes(
        ApiNodeArray &       nodes,
        const char *const *& pinNames) const;

    /// Builds a node pin info out of the pin infos of all non-linker destination pins of an input
    /// linker node. It also takes the name, the description (A_DESCRIPTION) and group (A_GROUP)
    /// attributes of the linker node into account and applies those to the generated pin info.
    ///
    /// The returned pin info stays valid until the next time this function is called.
    /// 
    /// @return
    ///     A reference of the created pin info.
    const ApiNodePinInfo& buildLinkerNodePinInfo();

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
    /// @return
    ///     A reference of the created pin info.
    const ApiNodePinInfo& buildDestinationPinInfo();

    /// Returns the owned item of a pin (Or NULL if the pin owns nothing).
    ApiItem* ownedItem(
        const PinId pinId) const;

    /// Same as above but identifies the pin based on name.
    ApiItem* ownedItem(
        const char *pinName) const;

    /// Same as above but identifies the pin based on index.
    ApiItem* ownedItemIx(
        const uint32_t pinIx) const;

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
    /// @return
    ///     The created item or NULL if the node could not be created.
    ApiNode* createInternal(
        const PinId            pinId,
        const Octane::NodeType type,
        const bool             configurePins=true,
        const bool             evaluate=true);

    /// Same as above but identifies the pin based on name.
    ApiNode* createInternal(
        const char             *pinName,
        const Octane::NodeType type,
        const bool             configurePins=true,
        const bool             evaluate=true);

    /// Same as above but identifies the pin based on index.
    ApiNode* createInternalIx(
        const uint32_t         pinIx,
        const Octane::NodeType type,
        const bool             configurePins=true,
        const bool             evaluate=true);

    /// Creates a node graph internal a pin. If the pin already owned an item, it will be destroyed.
    ///
    /// @param[in]  pinId
    ///     Pin ID identifying the pin in which we'd like to create the node graph.
    /// @param[in]  type
    ///     Type of the node graph to create in the pin. The node graph needs to have a default
    ///     linker node of the type of the pin or the pin will stay unconnected.
    /// @param[in]  evaluate  (optional, default=TRUE)
    ///     If set to TRUE, the new node and this node will be evaluated.
    /// @return
    ///     The created item or NULL if the node graph could not be created.
    ApiNodeGraph* createInternal(
        const PinId         pinId,
        const NodeGraphType type,
        const bool          evaluate=true);

    /// Same as above but identifies the pin based on name.
    ApiNodeGraph* createInternal(
        const char          *pinName,
        const NodeGraphType type,
        const bool          evaluate=true);

    /// Same as above but identifies the pin based on index
    ApiNodeGraph* createInternalIx(
        const uint32_t      pinIx,
        const NodeGraphType type,
        const bool          evaluate=true);

    /// Copies an item into a pin or does nothing if the item can't be copied into the pin, because
    /// the item is a node with the incorrect type.
    ///
    /// @param[in]  pinId
    ///     The ID of the pin into which the item should be copied.
    /// @param[in]  sourceItem
    ///     The item to copy into the pin.
    /// @param[in]  evaluate
    ///     If set to TRUE, the node will be evaluated after the copy.
    /// @return
    ///     The newly created item or NULL if the source item could not be copied into the pin.
    ApiItem* copyFrom(
        const PinId   pinId,
        const ApiItem *sourceItem,
        const bool    evaluate=true);

    /// Same as above, but identifying the pin via its name.
    ApiItem* copyFrom(
        const char    *pinName,
        const ApiItem *sourceItem,
        const bool    evaluate=true);

    /// Same as above, but identifying the pin via its index.
    ApiItem* copyFromIx(
        const uint32_t pinIx,
        const ApiItem  *sourceItem,
        const bool    evaluate=true);

    /// Returns the value of a value node (skipping linker nodes) or the default
    /// value of the pin if it's not connected to value node. These should getters should
    /// only be called on a pin of the appropriate type (e.g. getBool on PT_BOOL).
    bool        getPinBool    (const PinId id) const;
    float       getPinFloat   (const PinId id) const;
    float_2     getPinFloat2  (const PinId id) const;
    float_3     getPinFloat3  (const PinId id) const;
    float_4     getPinFloat4  (const PinId id) const;
    int32_t     getPinInt     (const PinId id) const;
    int32_2     getPinInt2    (const PinId id) const;
    int32_3     getPinInt3    (const PinId id) const;
    int32_4     getPinInt4    (const PinId id) const;
    MatrixF     getPinMatrix  (const PinId id) const;
    const char *getPinString  (const PinId id) const;
    ApiFilePath getPinFilePath(const PinId id) const;

    /// Same as above but identifies the pin via name.
    bool        getPinBool    (const char *name) const;
    float       getPinFloat   (const char *name) const;
    float_2     getPinFloat2  (const char *name) const;
    float_3     getPinFloat3  (const char *name) const;
    float_4     getPinFloat4  (const char *name) const;
    int32_t     getPinInt     (const char *name) const;
    int32_2     getPinInt2    (const char *name) const;
    int32_3     getPinInt3    (const char *name) const;
    int32_4     getPinInt4    (const char *name) const;
    MatrixF     getPinMatrix  (const char *name) const;
    const char *getPinString  (const char *name) const;
    ApiFilePath getPinFilePath(const char *name) const;

    /// Same as above but identifies the pin via index.
    bool        getPinBoolIx    (const uint32_t index) const;
    float       getPinFloatIx   (const uint32_t index) const;
    float_2     getPinFloat2Ix  (const uint32_t index) const;
    float_3     getPinFloat3Ix  (const uint32_t index) const;
    float_4     getPinFloat4Ix  (const uint32_t index) const;
    int32_t     getPinIntIx     (const uint32_t index) const;
    int32_2     getPinInt2Ix    (const uint32_t index) const;
    int32_3     getPinInt3Ix    (const uint32_t index) const;
    int32_4     getPinInt4Ix    (const uint32_t index) const;
    MatrixF     getPinMatrixIx  (const uint32_t index) const;
    const char *getPinStringIx  (const uint32_t index) const;
    ApiFilePath getPinFilePathIx(const uint32_t index) const;

    /// Returns the value in an out argument.
    void getPinValue(const PinId id,  bool        &value) const;
    void getPinValue(const PinId id,  float       &value) const;
    void getPinValue(const PinId id,  float_2     &value) const;
    void getPinValue(const PinId id,  float_3     &value) const;
    void getPinValue(const PinId id,  float_4     &value) const;
    void getPinValue(const PinId id,  int32_t     &value) const;
    void getPinValue(const PinId id,  int32_2     &value) const;
    void getPinValue(const PinId id,  int32_3     &value) const;
    void getPinValue(const PinId id,  int32_4     &value) const;
    void getPinValue(const PinId id,  MatrixF     &value) const;
    void getPinValue(const PinId id,  const char *&value) const;
    void getPinValue(const PinId id,  ApiFilePath &value) const;

    /// Same as above but identifies the pin via name.
    void getPinValue(const char *name,  bool        &value) const;
    void getPinValue(const char *name,  float       &value) const;
    void getPinValue(const char *name,  float_2     &value) const;
    void getPinValue(const char *name,  float_3     &value) const;
    void getPinValue(const char *name,  float_4     &value) const;
    void getPinValue(const char *name,  int32_t     &value) const;
    void getPinValue(const char *name,  int32_2     &value) const;
    void getPinValue(const char *name,  int32_3     &value) const;
    void getPinValue(const char *name,  int32_4     &value) const;
    void getPinValue(const char *name,  MatrixF     &value) const;
    void getPinValue(const char *name,  const char *&value) const;
    void getPinValue(const char *name,  ApiFilePath &value) const;

    /// Same as above but identifies the pin via index.
    void getPinValueIx(const uint32_t index,  bool        &value) const;
    void getPinValueIx(const uint32_t index,  float       &value) const;
    void getPinValueIx(const uint32_t index,  float_2     &value) const;
    void getPinValueIx(const uint32_t index,  float_3     &value) const;
    void getPinValueIx(const uint32_t index,  float_4     &value) const;
    void getPinValueIx(const uint32_t index,  int32_t     &value) const;
    void getPinValueIx(const uint32_t index,  int32_2     &value) const;
    void getPinValueIx(const uint32_t index,  int32_3     &value) const;
    void getPinValueIx(const uint32_t index,  int32_4     &value) const;
    void getPinValueIx(const uint32_t index,  MatrixF     &value) const;
    void getPinValueIx(const uint32_t index,  const char *&value) const;
    void getPinValueIx(const uint32_t index,  ApiFilePath &value) const;

    /// Sets a connected node's value attribute through a pin. This means
    /// that the value is clamped (if applicable) to the allowed range of the pin.
    void setPinValue(const PinId id,  const bool         value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const float        value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const float_2      value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const float_3      value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const float_4      value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const int32_t      value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const int32_2      value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const int32_3      value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const int32_4      value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const MatrixF     &value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const char *const  value,  const bool evaluate=true);
    void setPinValue(const PinId id,  const ApiFilePath &value,  const bool evaluate=true);
    
    /// Same as above but identifies the pin via name.
    void setPinValue(const char *name,  const bool         value,  const bool evaluate=true);
    void setPinValue(const char *name,  const float        value,  const bool evaluate=true);
    void setPinValue(const char *name,  const float_2      value,  const bool evaluate=true);
    void setPinValue(const char *name,  const float_3      value,  const bool evaluate=true);
    void setPinValue(const char *name,  const float_4      value,  const bool evaluate=true);
    void setPinValue(const char *name,  const int32_t      value,  const bool evaluate=true);
    void setPinValue(const char *name,  const int32_2      value,  const bool evaluate=true);
    void setPinValue(const char *name,  const int32_3      value,  const bool evaluate=true);
    void setPinValue(const char *name,  const int32_4      value,  const bool evaluate=true);
    void setPinValue(const char *name,  const MatrixF     &value,  const bool evaluate=true);
    void setPinValue(const char *name,  const char *const  value,  const bool evaluate=true);
    void setPinValue(const char *name,  const ApiFilePath &value,  const bool evaluate=true);
    
    /// Same as above but identifies the pin via index.
    void setPinValueIx(const uint32_t index,  const bool         value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const float        value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const float_2      value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const float_3      value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const float_4      value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const int32_t      value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const int32_2      value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const int32_3      value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const int32_4      value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const MatrixF     &value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const char *const  value,  const bool evaluate=true);
    void setPinValueIx(const uint32_t index,  const ApiFilePath &value,  const bool evaluate=true);

    /// Opens a UI to allow the user choose where and how the specified node should be stored.
    ///
    /// The node will either be copied into a node graph and connected with a corresponding output
    /// linker of - if the node is already an output linker - the owner graph of the output linker
    /// will be stored.
    ///
    /// @note This function is not supported by all SDK flavours
    ///
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
    void showOslWindow(
        bool force = false);

    /// Request closing the OSL editor window
    /// If force is false, then the user may cancel if the editor currently has unsaved
    /// changes.
    /// @return
    ///     true if the window was closed, false if the user canceled.
    static bool closeOslWindow(
        bool force = false);

#ifndef OCTANE_DEMO_VERSION

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
    /// @return 
    ///     TRUE if unpacking succeeded. In the case that any node fails to unpack, we will continue
    ///     trying to unpack the rest (if any).
    bool unpackFileData(
        const char * assetPath,
        bool         recursive);

#endif
};



//--------------------------------------------------------------------------------------------------
// Node graphs are group other node graphs and nodes.
class OCTANEAPI_DECL ApiNodeGraph : public ApiItem
{
    OCTANEAPI_NO_COPY(ApiNodeGraph);

public:

    /// Creates a new graph of the specified type.
    ///
    /// @param[in]  type
    ///     The type of the graph to create.
    /// @param[in]  ownerGraph 
    ///     Graph that will own the new graph.
    /// @return
    ///     Pointer to the created graph or NULL if creation failed.
    static ApiNodeGraph* create(
        const Octane::NodeGraphType type,
        ApiNodeGraph                &ownerGraph);

    /// Returns info for this graph.
    const ApiNodeGraphInfo& info() const;

    /// Returns this graph's type.
    Octane::NodeGraphType type() const;

    /// Returns the owned items of the node graph.
    ///
    /// @param[in]  list
    ///     Empty item list. The graph will fill it in with pointer to the items
    ///     it owns.
    void getOwnedItems(
        ApiItemArray &list) const;

    /// Returns the list of input nodes.
    void getInputNodes(
        ApiNodeArray &list) const;

    /// Returns the list of output nodes.
    void getOutputNodes(
        ApiNodeArray &list) const;

    /// Returns a list with all nodes in the graph of the given type.
    ///
    /// @param[in]  type
    ///     Type of the nodes we'd like to collect.
    /// @param[out] list 
    ///     List of nodes that have the given type.
    /// @param[in]  recurse 
    ///     Recurses into nested graphs to collect the nodes.
    void findNodes(
        const Octane::NodeType type,
        ApiNodeArray           &list,
        const bool             recurse=false) const;

    /// Returns the first node of the specified type.
    /// This function doesn't recurse in sub-graphs.
    ApiNode* findFirstNode(
        const Octane::NodeType type) const;

    /// Returns the first output linker of the specified pin type.
    /// This function doesn't recurse in sub-graphs.
    ApiNode* findFirstOutputNode(
        const Octane::NodePinType pinType) const;

    /// Find all items with a given name.
    ///
    /// @param[in]  name
    ///     The name of the items to collect.
    /// @param[out] list 
    ///     List of items that match the given name.
    /// @param[in]  recurse 
    ///     Recurses into nested graphs to collect the nodes.
    void findItemsByName(
        const char   *name,
        ApiItemArray &list,
        const bool   recurse=false) const;

    /// Assigns linear time transformation to the animation of the nested owned items
    /// Can be used to offset or scale the animation playback
    /// @param[in] delay
    ///     offset of the animation start time in seconds
    /// @param[in] speedUp
    ///     scale of the animation playback speed (1 is normal playback, 2 is 2x faster)
    /// @param[in] customInterval
    ///     Start and end time (in seconds) of the untransformed time of the animation that 
    ///     should be played. The animation outside this interval will be cut out. 
    ///     E.g. if the start time is 2s and the delay is 0s, then the transformed animation 
    ///     at time 0 will be that of the untransformed animation at time 2s.
    void setLinearTimeTransform(
        const float             delay,
        const float             speedUp,
        const Octane::TimeSpanT customInterval = Octane::TimeSpanT::make(0.0f, 0.0f));

    /// Returns current ApiAnimationTimeTransform
    /// or NULL if it doesn't have one
    const ApiAnimationTimeTransform * timeTransform() const;

    /// Removes animation time transformation
    void clearTimeTransform();

    /// Returns an array of null-terminated strings containing all paths of the assets
    /// currently used by the current node graph
    /// 
    /// @returns
    ///     The list of asset paths in the current node graph.
    ///     NOTE: The contents of this will be valid until this function is called again
    ///           from any node graph.
    StringArrayT getAssetPaths();

    /// Recenter all items in this graph around the given position.
    ///
    /// @param[in] center
    ///     The point which will be the average of the positions of all items in this graph.
    void recenter(
        const float_2 center);

    /// Clears the node graph, i.e. deletes all nodes stored in it. If you call this function on
    /// the root node graph, ALL your nodes will be gone. -> Make sure that you also destroy all
    /// reference to those nodes on the plugin side.
    void clear();

    /// Copies the items from the source graph into this graph.
    ///
    /// @param[in]  source
    ///     Source grap who's content we copy.
    /// @param[in]  origItems
    ///     Original items for which we'd like to know what their copies are.
    ///     These items don't have to have the same owner. This list is optional.
    /// @param[in]  origItemCount
    ///     The length of the list of original items.
    /// @param[out] copiedItems
    ///     Copies of the items in the list origItems. The copies are in the same
    ///     order as the origItems list. This list must be provided when origItems
    ///     is provided.
    void copyFrom(
        const ApiNodeGraph &source,
        const ApiItem      *const *origItems = NULL,
        const size_t       origItemCount     = 0,
        ApiItemArray       *copiedItems      = NULL);

    /// Copies one item into the node graph.
    ///
    /// @param[in]  sourceItem
    ///     The item to copy, this item must have an owner.
    /// @return
    ///     Ptr to the copied item or NULL if the item couldn't be copied.
    ApiItem* copyFrom(
        const ApiItem &sourceItem);

    /// Copies the tree starting at rootItem into this graph.
    ///
    /// @param[in]  rootItem
    ///     Item at the root of the copy tree, the item must have an owner. If the item is an
    ///     input linker then the returned copy is either:
    ///     - a copy of the input linker if it doesn't have a non-linker input node
    ///     - a copy of the non-linker input if the input linker has one
    /// @return
    ///     Pointer to the copied item or NULL if the item couldn't be copied.
    ApiItem * copyItemTree(
        const ApiItem & rootItem);

    /// Copies an array of items into the node graph.
    ///
    /// @param[in]  sourceItems
    ///     Pointer to an array of items (must not be NULL). All the items in the array
    ///     must have the same owner and that owner can't be NULL.
    /// @param[in]  itemCount
    ///     The size of the array, i.e. the number of items in the array.
    /// @param[out] sourceItemCopies 
    ///     Optional empty list. This method will fill it with a pointer to the copy for
    ///     each source items in sourceItems. This list has size itemCount. The copies are
    ///     in the same order as the source items.
    /// @param[in]  origItems
    ///     Optional list of original items for which we'd like to now what their copies are.
    ///     They don't have to be in sourceItems and don't have to have the same owner.
    /// @param[in]  origItemsCount
    ///     Size of origItems.
    /// @param[out] origItemsCopies
    ///     Optional list with the copies of origItems. This list must be provided if
    ///     the original items list is provided. 
    void copyFrom(
        const ApiItem *const *sourceItems,
        const size_t  sourceItemsCount,
        ApiItemArray  *sourceItemCopies = NULL,
        const ApiItem *const *origItems = NULL,
        const size_t  origItemsCount    = 0,
        ApiItemArray  *origItemCopies   = NULL);

    /// Replace a group of node items with a group node containing a copy of these items. Any
    /// connections coming from other nodes are copied through linker nodes into the new group.
    ///
    /// @param[in]  items
    ///     The list of items to copy. All these items will be destroyed after copying.
    ///     The items must all be owned by this graph.
    /// @param[in]  itemsCount
    ///     The number of items in the list.
    /// @return
    ///     The nodegraph with the items or NULL. 
    ApiNodeGraph* groupItems(
        ApiItem *const *const items,
        const size_t          itemsCount);

    /// Replaces this node graph with a copy of its content in its parent node graph. This node
    /// graph must be owned by a node graph. This node graph will be gone afterwards.
    ///
    /// @param[out]  ungroupedItems 
    ///     List of the ungrouped items.
    void ungroup(
        ApiItemArray *const ungroupedItems = nullptr);

    /// Unfolds the specified node graph if it's inspectable, i.e. places items in a way that items
    /// don't overlap and connections don't intersect much. The order of linker nodes is kept, too.
    /// In the end, all items are moved so that their center of gravity is at (0,0).
    ///
    /// @param[in]  recursive  (optional)
    ///     If set to TRUE, all nested node graphs that are inspectable are unfolded, too.
    void unfold(
        const bool recursive = false);

    //-- Nodegraph editor window --

    /// Shows the node graph in a window, allowing the user to edit this node graph. This call
    /// blocks until the window is closed. Only one window can be shown at any time by 
    /// ApiNodeGraph::showWindow(). If another window is already open, this function does nothing.
    ///
    /// @param unfold
    ///     If TRUE the graph will be unfolded.
    /// @param windowState
    ///     Optional window state. When passed into the function we try to restore the window from
    ///     this state (window position, window size and split position).
    /// @param alwaysOnTop
    ///     Whether the window should be set to always on top. Either way, the window is still shown
    ///     modally. This should be set to false unless it causes problems, because when the window
    ///     is always on top tooltips don't work (plus, preventing other applications' windows from
    ///     ever being on top of this one is a bad idea). Set this to true only if the default
    ///     behavior breaks windowing in a way that's worse than broken tooltips.
    /// @return
    ///     String with the last window state. This state can be used to restore the last state of
    ///     the window in the next showWindow() calls. This string is owned by the API and only 
    ///     valid till the next call to showWindow().
    const char* showWindow(
        const bool unfold       = true,
        const char *windowState = NULL,
        bool alwaysOnTop        = false);

    /// Closes the opened node graph editor window (if any). WARNING: calling this before 
    /// showWindow() actually shows the window will not close the window later. This race-condition
    /// is something the plugin should take care of.
    static void closeWindow();


    /// Returns the native window handle. Only returns something when the window is visible.
    static void* nativeWindowHandle(); 

    /// Window-closing callback - notifies plugins that the window is closing.
    typedef void (DbViewClosingCallbackT)(void *userData);

    /// Item loaded callback.
    typedef void (DbViewLoadedCallbackT)(void *userData, Octane::ItemDbOrigin origin);

    /// Opens a dialog window where the user can import items from liveDB and localDB.
    /// 
    /// If you use this function you must call closeDbWindow() before destroying this
    /// node graph.
    /// 
    /// Do not use this while an ApiMainWindow is open. It may cause deadlocks.
    /// 
    /// The function will open the dialog and return. The dialog is a non-modal dialog.
    /// The user may import one or more entries from liveDB or localDB before dismissing the dialog.
    /// Only one such dialog can be open at a time, if you call this while a dialog is already
    /// open, the existing dialog will be closed first.
    /// 
    /// @param[in]  dbViewClosingCallback
    ///     Called when the dialog is being closed by the user. May be nullptr.
    /// @param[in]  dbViewLoadedCallback
    ///     Called after an item has been imported. The item will be imported as child items of
    ///     this node graph.
    /// @param[in]  userData
    ///     Passed to the callbacks as the first argument.
    /// @param[in]  showLiveDb
    ///     Show the LiveDB in this window too.
    ///
    /// Usage:
    ///
    /// If you want the dialog to retain its full state every time it is opened, create a
    /// node graph and don't delete it after importing an item:
    /// @code
    ///     Octane::ApiNodeGraph *returnGraph = ...
    /// @endcode
    ///
    /// Define the callbacks:
    /// @code
    ///     void dbViewClosingCallback(void *userData) {
    ///         ...
    ///     }
    ///     void dbViewLoadedCallback(void *userData, Octane::ItemDbOrigin origin) {
    ///         ...
    ///     }
    /// @endcode
    ///
    /// Now you can show the dialog
    /// @code
    ///     pRetGraph->showDbWindow(
    ///         dbViewClosingCallback, dbViewLoadedCallback, returnGraph, /*showLiveDb = */ true);
    /// @endcode
    ///
    /// Use ApiDBMaterialManager::unpackFileData() to unpack the image textures and other
    /// assets in the imported nodes.
    void showDbWindow(
        DbViewClosingCallbackT * dbViewClosingCallback,
        DbViewLoadedCallbackT *  dbViewLoadedCallback,
        void *                   userData,
        const bool               showLiveDb = false);

    /// Closes the currently opened DB window (if any)
    ///
    /// @param[in]  clearData
    ///     Clears all cached data.
    static void closeDbWindow(
        bool clearData = false);

};



//--------------------------------------------------------------------------------------------------
/// Nodegraph without an owner and a timestamp.
class OCTANEAPI_DECL ApiRootNodeGraph : public ApiNodeGraph
{
    OCTANEAPI_NO_COPY(ApiRootNodeGraph);

public:

    /// Creates a root node graph (graph without owner) with the specified version.
    /// The caller owns the object and needs to delete it if it's not used anymore.
    static ApiRootNodeGraph* create(
        const VersionT version = OCTANE_VERSION);

    /// Clears the root node graph (it will be empty afterwards) and sets it to the specified
    /// version.
    void init(
        const VersionT version);

    /// Converts the root node graph to the current version and evaluates all nodes.
    void convertAndEvaluate();

    /// Returns the total time span for all animations in this graph.
    Octane::TimeSpanT animationTimeSpan() const;

    /// Updates the time of all attributes in this root node graph. This will always evaluate 
    /// the changed nodes in the root node graph.
    /// 
    /// @param[in] time
    ///     The new time stamp
    void updateTime(
        const Octane::TimeT time);

    /// Imports a scene from disk into this graph. The version conversion is done automatically.
    /// 
    /// If the loading was successful, the old content of the root node graph will be gone.
    ///
    /// @param[in]  path 
    ///     Absolute path to the .ocs or .orbx file.
    /// @param[out] ocsVersion
    ///     Octane version the OCS XML string was written with.
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @return
    ///     TRUE on success, FALSE on failure.
    bool importFromFile(
        const char            *path,
        Octane::VersionT      &ocsVersion,
        AssetMissingCallbackT assetMissingCallback = nullptr,
        void                  *assetsMissingCallbackUserData = nullptr);

    /// Imports an OCS XML string scene from disk into this graph.  The version conversion 
    /// is done automatically.
    /// 
    /// If the loading was successful, the old content of the root node graph will be gone.
    ///
    /// @param[in]  baseDirectory
    ///     Path to a base directory used to resolve relative paths in the xml.
    /// @param[out] ocsVersion
    ///     Octane version the OCS XML string was written with.
    /// @param[in]  xml
    ///     XML string. Doesn't need to be null terminated.
    /// @param[in]  xmlLength
    ///     Length of the XML string (excl. any terminators).
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @return
    ///     TRUE on success, FALSE on failure.
    bool importOcsFromMemory(
        const char            *baseDirectory,
        Octane::VersionT      &ocsVersion,
        const char            *xml,
        const size_t          xmlLength,
        AssetMissingCallbackT assetMissingCallback = nullptr,
        void                  *assetsMissingCallbackUserData = nullptr);

    /// Callback used in ORBX import from memory.
    ///
    /// @param[in]  userData
    ///     Opaque user data passed in by the plugin.
    /// @param[out]  dataChunk
    ///     Pointer to the buffer that will be filled by next ORBX data chunk. Set to null if there
    ///     are no more chunks.
    /// @return
    ///     Size of returned data chunk, or zero if there are no more chunks.
    typedef size_t (*NextChunkCallbackT)(void* userData, unsigned char*& dataChunk);

    /// Imports an ORBX data from memory into this graph, chunk by chunk. The version conversion 
    /// is done automatically.
    /// 
    /// If the loading was successful, the old content of the root node graph will be gone.
    ///
    /// @param[in]  baseDirectory
    ///     Path to a base directory used to unpack the assets from the ORBX.
    ///     If asset files with the same name already exist in given directory,
    ///     they will not be rewritten. 
    /// @param[out] ocsVersion
    ///     Octane version the ORBX project data was written with.
    /// @param[in] getOrbxChunkCallback
    ///     The callback that returns ORBX file data in memory buffer chunk by chunk.
    /// @param[in]  orbxChunkCallbackUserData
    ///     Opaque user data passed in by the plugin.
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @return
    ///     TRUE on success, FALSE on failure.
    bool importOrbxFromCallback(
        const char            *baseDirectory,
        Octane::VersionT      &ocsVersion,
        NextChunkCallbackT    getOrbxChunkCallback,
        void                  *orbxChunkCallbackUserData,
        AssetMissingCallbackT assetMissingCallback = nullptr,
        void                  *assetMissingCallbackUserData = nullptr);

    /// Imports an ORBX data from memory into this graph. The version conversion 
    /// is done automatically.
    /// This is the faster version, as it does not use the dynamically reallocated buffer
    /// during loading ORBX data chunk by chunk.
    /// 
    /// If the loading was successful, the old content of the root node graph will be gone.
    ///
    /// @param[in]  baseDirectory
    ///     Path to a base directory used to unpack the assets from the ORBX.
    ///     If asset files with the same name already exist in given directory,
    ///     they will not be rewritten. 
    /// @param[out] ocsVersion
    ///     Octane version the ORBX project data was written with.
    /// @param[in] orbxData
    ///     The ORBX data buffer.
    /// @param[in] dataSize
    ///     The size of ORBX data buffer.
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @return
    ///     TRUE on success, FALSE on failure.
    bool importOrbxFromMemory(
        const char            *baseDirectory,
        Octane::VersionT      &ocsVersion,
        const void            *orbxData,
        const size_t          dataSize,
        AssetMissingCallbackT assetMissingCallback = nullptr,
        void                  *assetsMissingCallbackUserData = nullptr);

    /// Exports this root graph into a file (regular ocs or package).
    /// In-memory data in nodes will be written out to file:
    ///
    ///     * texture raw image buffer -> png/exr file
    ///     * raw mesh geometry        -> obj file
    ///
    /// @note This function is not supported by all SDK flavours
    /// @param[in]  filePath 
    ///     absolute path of the file. This can be a .orbx or a .ocs file.
    /// @param[in]  useRelativePaths (optional)
    ///     set whether to save asset file paths relative to @ref filePath
    /// @return
    ///     TRUE on successful write, FALSE otherwisein which case there
    ///     should have been additional error messages on the log.
    bool exportToFile(
        const char *filePath,
        bool       useRelativePaths = true) const;

    /// Exports this graph into a string and optionally exports the raw data.
    ///
    /// @param[in]  baseDirectory 
    ///     Absolute path to the export directory for assets (optional).
    ///     If not provided, assets aren't exported.
    /// @param[in]  useRelativePaths (optional)
    ///     set whether to save asset file paths relative to @ref baseDirectory
    /// @return
    ///     Null terminated OCS XML, which is owned by the API and shouldn't be deleted and stays
    ///     valid until the next call of this function.
    const char* exportToString(
        const char *baseDirectory    = NULL,
        bool        useRelativePaths = true) const;

    /// Returns the number of reference graphs that this root graph contains
    uint32_t referenceGraphCount() const;

    /// Loads all reference graphs in this graph
    void loadAllReferences();

    /// Unloads all reference graphs in this graph
    void unloadAllReferences();
};


} // namespace Octane

#endif // #ifndef _API_NODE_SYSTEM_H_
