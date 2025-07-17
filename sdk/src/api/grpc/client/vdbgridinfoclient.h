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

/// Proxy class for VdbGridInfo
class VdbGridInfoProxy : public GRPCBase
{
public:
    /// Returns the name of this grid. Don't deallocate this, it is owned by VdbGridInfo, which
    /// takes care of deallocating it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string name() const;

    /// Returns the type of this grid.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string type() const;

    /// Returns the width, height and depth of the grid in voxels.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    OctaneVec::uint32_3 resolution() const;

    /// Returns the minimum active voxel bounding box of the grid.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    OctaneVec::int32_3 minBound() const;

    /// Returns the maximum active voxel bounding box of the grid.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    OctaneVec::int32_3 maxBound() const;

    /// Returns the _transposed_ transform from the VDB, excluding the perspective projection. This
    /// is to match with how transforms are stored by Octane.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    OctaneVec::MatrixF transform() const;

private:
    static GRPCSettings & getGRPCSettings();
};
