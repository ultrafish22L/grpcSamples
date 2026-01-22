// Copyright (C) 2026 OTOY NZ Ltd.

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


#include "apirender.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiRenderImage
class ApiRenderImageProxy : public GRPCBase
{
public:
    /// Little convenience function to check if this buffer is empty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isEmpty() const;

    /// Little convenience function to check if a render result is LDR (1 byte per channel) or HDR
    /// (2 or 4 bytes per channel).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isHdr() const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
