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


#include "apimouselistener.h"


class Convert;

class GRPCSettings;

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
    void destroy(            );

private:
    static GRPCSettings & getGRPCSettings();
};
