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


#include "apidiagnostics.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiDiagnostics
class ApiDiagnosticsProxy : public GRPCBase
{
public:
    /// Crashes the software after the specified number of seconds
    ///
    /// @param[in]  delayInSeconds
    ///     The delay before generating the access violation
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void diagnosticCommand(
            const uint32_t                            commandType,
            const uint32_t                            delayInSeconds
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
