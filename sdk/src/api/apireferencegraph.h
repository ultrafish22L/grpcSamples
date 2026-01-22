// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include "apinodesystem.h"
#include "octaneaabb.h"
#include "octaneenums.h"
#include "octanetime.h"
#include "octanetypes.h"

namespace Octane
{

/// The reference graph is a node graph of type GT_REFERENCE that allows loading orbx/ocs file
/// contents inside the graph and exposes corresponding inputs and outputs. In addition, each
/// render target in the referenced orbx/ocs will produce an extra output so that it's geometry
/// can be accessed. Please see the GT_REFERENCE node graph attributes for the basic reference.
///
/// ApiReferenceGraph can be used to obtain the animated bounding boxes when the orbx file
/// was saved with AABB data (e.g. to display in the host application viewport).
/// Usage example:
///
///     // It may be a good idea to store a bounds vector somewhere in the object member variable 
///     // so that it's memory doesn't get reallocated every time we fetch the bounds (e.g. when
///     // current animation frame or time changes).
///
///     std::vector<Octane::AABBF> mAabbs;
///
///     ...
///
///     // Create reference graph
///     Octane::ApiReferenceGraph * referenceGraph =
///         Octane::ApiReferenceGraph::create(Octane::ApiProjectManager::rootNodeGraph());
///
///     // Set orbx path
///     referenceGraph->set(Octane::A_EXTERNAL_REFERENCE_PATH, "path_to_my_orbx.orbx", false);
///
///     // Reference will be loaded during evaluation
///     referenceGraph->evaluate();
///
///     // If orbx has the AABB data, it will be available after the graph is evaluated
///     if (!referenceGraph->hasAabbData())
///     {
///         mAabbs.clear();
///         return;
///     }
///     mAabbs.resize(referenceGraph->totalAabbEntries());
///     // Fill the mAabbs vector with the data
///     referenceGraph->fetchAllBounds(mAabbs.data(), mAabbs.size());
///     // The AABBs can be used for drawing. Make sure to fetch it again if time/frame changes.
///
/// To handle each geometry output of the graph separately, use fetchBoundsForOutput() and 
/// totalAabbEntriesForOutput()
/// 
class OCTANEAPI_DECL ApiReferenceGraph : public ApiNodeGraph
{
    OCTANEAPI_NO_COPY(ApiReferenceGraph);

public:

    /// creates a new graph of the GT_REFERENCE type.
    ///
    /// @param[in]  ownergraph 
    ///     graph that will own the new ApiReferenceGraph.
    /// @return
    ///     pointer to the created graph or null if creation failed.
    static ApiReferenceGraph * create(
        ApiNodeGraph & ownerGraph);

    /// Returns ApiReferenceGraph interface for the ApiNodeGraph of GT_REFERENCE type
    /// 
    /// @param[in] nodeGraph
    ///     The node graph to obtain API for. 
    /// @return 
    ///     The ApiReferenceGraph object pointer if nodeGraph type is GT_REFERENCE. NULL otherwise.
    static ApiReferenceGraph * obtain(
        ApiNodeGraph * nodeGraph);

    /// Returns true if the AABB data is present in the referenced orbx
    bool hasAabbData() const;

    /// Returns the number of AABB entries for all outputs. This value doesn't change
    /// unless the reference is loaded/reloaded.
    uint32_t totalAabbEntries() const;

    /// Populates the buffer with AABBs for all the output nodes at current time.
    /// If time transform is assigned to this graph (or any of of it's owners), it will be accounted
    /// for. 
    /// Note: the scene time can be set in the ApiRootNodeGraph::updateTime().
    /// Use totalAabbEntries() to get the buffer size that fits all the available bounds.
    /// This can be used to display bounding boxes for a particular output of the reference graph
    /// (e.g. in the host app viewport).
    /// NOTE: The returned AABBs are in the reference graph coordinate system. E.g. if the reference
    /// graph outputs are connected to the placement node, the AABBs will need to be transformed by 
    /// the placement node matrix to get the world space AABB. See AABBF::transformed().
    /// 
    /// @param[in] outputIndex
    ///     The index of the output node in the getOutputNodes() array
    /// @param[out] buffer
    ///     The buffer to store the result.
    ///     The buffer size in bytes must be at least bufferSize*sizeof(Octane::AABBF).
    ///     To ensure smooth memory management, consider using std::vector<Octane::AABBF> with
    ///     size equal to bufferSize.
    /// @param[in] bufferSize
    ///     The number of Octane::AABBF that can be put in the buffer (not the size in bytes).
    ///     If this number is smaller than totalAabbEntries(), the extra entries will be skipped.
    /// @return
    ///     The number of Octane::AABBF that have been written into the buffer
    size_t fetchAllBounds(
        Octane::AABBF * buffer,
        size_t          bufferSize) const;

    /// Returns the number of AABB entries for the certain output node. This value doesn't change
    /// unless the reference is loaded/reloaded.
    /// Note: it will always return 0 for non-geometry outputs (e.g. material outputs)
    ///
    /// @param[in] outputIndex
    ///     the index of the output in the outputNodes() list.
    /// @return
    ///     The number of AABB entries
    uint32_t totalAabbEntriesForOutput(
        uint32_t outputIndex) const;

    /// Populates the buffer with AABBs for a particular output node index at current scene time.
    /// If time transform is assigned to this graph (or any of it's owners), it will be accounted
    /// for.
    /// Note: the scene time can be set in the ApiRootNodeGraph::updateTime().
    /// Use totalAabbEntriesForOutput() to get the buffer size that fits all the bounds for a
    /// particular output node index.
    /// This can be used to display bounding boxes for a particular output of the reference graph
    /// (e.g. in the host app viewport).
    /// NOTE: The returned AABBs are in the reference graph coordinate system. E.g. if the reference
    /// graph outputs are connected to the placement node, the AABBs will need to be transformed by 
    /// the placement node matrix to get the world space AABB. See AABBF::transformed().
    /// 
    /// @param[in] outputIndex
    ///     The index of the output node in the getOutputNodes() array
    /// @param[out] buffer
    ///     The buffer to store the result.
    ///     The buffer size in bytes must be at least bufferSize*sizeof(Octane::AABBF).
    ///     To ensure smooth memory management, consider using std::vector<Octane::AABBF> with
    ///     size equal to bufferSize.
    /// @param[in] bufferSize
    ///     The number of Octane::AABBF that can be put in the buffer (not the size in bytes).
    ///     If this number is smaller than totalAabbEntriesForOutput(outputIndex), the extra entries
    ///     will be skipped.
    /// @return
    ///     The number of Octane::AABBF that have been written into the buffer
    size_t fetchBoundsForOutput(
        uint32_t        outputIndex,
        Octane::AABBF * buffer,
        size_t          bufferSize) const;
};

}

