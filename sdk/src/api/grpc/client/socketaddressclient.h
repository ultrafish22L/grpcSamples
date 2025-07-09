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

/// Proxy class for SocketAddress
class SocketAddressProxy : public GRPCBase
{
public:
    /// checks if this address makes sense
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isValid(            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
