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
namespace OctaneGRPC
{
    class VdbGridInfoProxy;
    class VdbGridSamplerProxy;
}


#include "octanevolume.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for VdbInfo
class VdbInfoProxy : public GRPCBase
{
public:
    /// If the VDB information was loaded successfully, this will return TRUE, otherwise FALSE.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool valid() const;

    /// Returns the number of grids stored in the VDB file.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t gridCount() const;

    /// Returns a pointer to the VdbGridInfo of the specified index or NULL if the index is invalid
    /// or the VdbInfo wasn't loaded correctly.
    ///
    /// @param[in] index
    ///     The index of the grid in the VDB file.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns if index < gridCount() then this returns a pointer to a VdbGridInfo. Otherwise
    ///     NULL.
    VdbGridInfoProxy grid(
            const uint32_t   index
            ) const;

    /// Returns a pointer to the VdbGridSampler of the specified index or NULL if the index is invalid
    /// , the current grid is not a float grid or the VdbInfo wasn't loaded correctly.
    ///
    /// @param[in] index
    ///     The index of the grid in the VDB file.
    /// @param[in] ignoreVdbTransform
    ///     The flag indicating if we will apply the world transform
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns if index < gridCount() and the expecting grid is a float grid then this returns
    ///     a pointer to a VdbGridSampler. Otherwise NULL.
    VdbGridSamplerProxy sampler(
            const uint32_t                            index,
            const bool                                ignoreVdbTransform
            );

    /// Destroys the single sampler if any
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroySampler();

    /// Convenience function to check whether a grid a) exists, b) is of a suitable type for the
    /// channel specified. If not, then it will find one that is suitable. If there are none, then
    /// it will return NULL.
    ///
    /// @param[in] channelAttributeId
    ///     One of: A_VOLUME_ABSORPTION_ID,         float grid
    ///             A_VOLUME_EMISSION_ID,           float grid
    ///             A_VOLUME_SCATTER_ID,            float grid
    ///             A_VOLUME_VELOCITY_ID,           float3 grid
    ///             A_VOLUME_VELOCITY_ID_X,         float grid
    ///             A_VOLUME_VELOCITY_ID_Y or       float grid
    ///             A_VOLUME_VELOCITY_ID_Z.         float grid
    /// @param[in] gridName
    ///     Preferred grid name, perhaps as specified by the end-user. This grid name may be
    ///     invalid, or specify a name that does not exist in this VDB.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns
    ///     If gridName specifies a grid that exists in this VDB, and it is of the correct type for
    ///     the channel specified in channelAttributeId, then the name will be returned unchanged.
    ///     If not, the name of the first grid in the VDB that matches the correct type will be
    ///     returned. In the case that there are none suitable, then this function will return
    ///     NULL.
    std::string findGrid(
            const Octane::AttributeId                 channelAttributeId,
            const char *const                         gridName
            ) const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
