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


#include "apianimationtimetransform.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiLinearTimeTransform
class ApiLinearTimeTransformProxy : public GRPCBase
{
public:
    /// The delay of the animation start time in seconds
    /// @param[out] status
    ///     Contains the status of the gRPC call
    float delay() const;

    /// The scale of the animation playback speed (default is 1).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    float speedUp() const;

    /// Returns TRUE when custom interval is enabled.
    /// The animation outside this interval will be cut out.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool customIntervalEnabled() const;

    /// Returns interval of the animation that should be played.
    /// It is untransformed local time of the animation in seconds.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::TimeSpanT customInterval() const;

private:
    static GRPCSettings & getGRPCSettings();
};
