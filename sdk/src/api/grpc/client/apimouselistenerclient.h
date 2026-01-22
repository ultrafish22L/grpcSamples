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


#include "apimouselistener.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiMouseListener
class ApiMouseListenerProxy : public GRPCBase
{
public:
    static ApiMouseListenerProxy create(
            GRPCMouseEventCallbackT                  mouseEventsCallback,
            void *                                    privateData
            );

    /// Destroys the listener created with create(..).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
