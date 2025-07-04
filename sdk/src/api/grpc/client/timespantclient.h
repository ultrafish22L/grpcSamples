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


#include "octanetime.h"


class Convert;

class GRPCSettings;

/// Proxy class for TimeSpanT
class TimeSpanTProxy : public GRPCBase
{
public:
    static Octane::TimeSpanT make(
            Octane::TimeT                             begin,
            Octane::TimeT                             end
            );

    /// Returns the length of this time interval.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::TimeT length(            ) const;

    /// Returns TRUE if this interval has zero length.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool empty(            ) const;

    /// Adds an offset to the start and end of the interval.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void shift(
            Octane::TimeT                             offset
            );

    /// Returns TRUE if the passed time is inside the interval.
    /// @param[in] time
    ///     The time to test.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool contains(
            const Octane::TimeT                       time
            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
