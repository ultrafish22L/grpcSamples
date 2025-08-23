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
#include "apiguicomponentclient.h"


#include "apititlecomponent.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiTitleComponent
class ApiTitleComponentProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new title component.
    ///
    /// @param[in]  text
    ///     Text that appears in the title component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Returns a pointer to the newly created title component.
    static ApiTitleComponentProxy create(
            const char *   text
            );

    /// Destroys this title component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
