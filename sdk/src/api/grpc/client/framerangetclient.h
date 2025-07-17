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

/// Proxy class for FrameRangeT
class FrameRangeTProxy : public GRPCBase
{
public:
    static Octane::FrameRangeT make(
            const int32_t                             begin,
            const int32_t                             end
            );

    /// returns the amount of frames
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t count() const;

private:
    static GRPCSettings & getGRPCSettings();
};
