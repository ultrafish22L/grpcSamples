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
#include "apinodegraphclient.h"


#include "apireferencegraph.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiReferenceGraph
class ApiReferenceGraphProxy : public ApiNodeGraphProxy
{
public:
    /// creates a new graph of the GT_REFERENCE type.
    ///
    /// @param[in]  ownergraph 
    ///     graph that will own the new ApiReferenceGraph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     pointer to the created graph or null if creation failed.
    static ApiReferenceGraphProxy create(
            ApiNodeGraphProxy &                       ownerGraph
            );

    /// Returns ApiReferenceGraph interface for the ApiNodeGraph of GT_REFERENCE type
    /// 
    /// @param[in] nodeGraph
    ///     The node graph to obtain API for. 
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return 
    ///     The ApiReferenceGraph object pointer if nodeGraph type is GT_REFERENCE. NULL otherwise.
    static ApiReferenceGraphProxy obtain(
            ApiNodeGraphProxy *                       nodeGraph
            );

    /// Returns true if the AABB data is present in the referenced orbx
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasAabbData(            ) const;

    /// Returns the number of AABB entries for all outputs. This value doesn't change
    /// unless the reference is loaded/reloaded.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t totalAabbEntries(            ) const;

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The number of Octane::AABBF that have been written into the buffer
    size_t fetchAllBounds(
            Octane::AABBF *                           buffer,
            size_t                                    bufferSize
            ) const;

    /// Returns the number of AABB entries for the certain output node. This value doesn't change
    /// unless the reference is loaded/reloaded.
    /// Note: it will always return 0 for non-geometry outputs (e.g. material outputs)
    ///
    /// @param[in] outputIndex
    ///     the index of the output in the outputNodes() list.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The number of AABB entries
    uint32_t totalAabbEntriesForOutput(
            uint32_t                                  outputIndex
            ) const;

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The number of Octane::AABBF that have been written into the buffer
    size_t fetchBoundsForOutput(
            uint32_t                                  outputIndex,
            Octane::AABBF *                           buffer,
            size_t                                    bufferSize
            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
