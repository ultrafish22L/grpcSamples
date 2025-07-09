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


#include "octanerenderpasses.h"


class Convert;

class GRPCSettings;

/// Proxy class for RenderResultStatistics
class RenderResultStatisticsProxy : public GRPCBase
{
public:
    /// Clears our members and sets the sub sample mode to SUBSAMPLE_NONE and the state to
    /// RSTATE_STOPPED.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clear(            );

    /// Returns the internal film resolution
    /// @param[out] status
    ///     Contains the status of the gRPC call
    OctaneVec::uint32_2 internalFilmResolution(            ) const;

    /// Returns the type of the channels, this is either float or 8-bit unsigned int
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::ImageChannelType channelType(            ) const;

    /// Returns the samples per pixel of the specified render pass.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t samplesPerPixel(
            const Octane::RenderPassId                renderPassId
            ) const;

    /// Returns the maximum samples per pixel of the specified render pass.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t maxSamplesPerPixel(
            const Octane::RenderPassId                renderPassId
            ) const;

    /// Returns the samples per second of the specified render pass.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    double samplesPerSecond(
            const Octane::RenderPassId                renderPassId
            ) const;

    /// Returns the render progress for the specified render pass.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    double progress(
            const Octane::RenderPassId                renderPassId
            ) const;

    /// Returns TRUE if at least one sample per pixel has been calculated for the specified render
    /// pass.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool started(
            const Octane::RenderPassId                renderPassId
            ) const;

    /// Returns TRUE if all samples per pixel have been calculated for the specified render pass.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool finished(
            const Octane::RenderPassId                renderPassId
            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
