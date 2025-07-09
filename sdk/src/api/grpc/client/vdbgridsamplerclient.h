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


#include "octanevolume.h"


class Convert;

class GRPCSettings;

/// Proxy class for VdbGridSampler
class VdbGridSamplerProxy : public GRPCBase
{
public:
    /// Returns the voxel value at the given location of the current grid.
    ///
    /// @param [in] x
    ///     The x coordinate of the sample point in world/local space based on how the sampler has been created
    /// @param [in] y
    ///     The y coordinate of the sample point in world/local space based on how the sampler has been created
    /// @param [in] z
    ///     The z coordinate of the sample point in world/local space based on how the sampler has been created
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The sampled value at the given coordinate, if succeeded. OR zero on failure
    float getValue(
            const float                               x,
            const float                               y,
            const float                               z
            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
