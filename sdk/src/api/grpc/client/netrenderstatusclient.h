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


#include "octanenet.h"


class Convert;

class GRPCSettings;

/// Proxy class for NetRenderStatus
class NetRenderStatusProxy : public GRPCBase
{
public:
    /// Resets and nullifies everything.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clear();

private:
    static GRPCSettings & getGRPCSettings();
};
