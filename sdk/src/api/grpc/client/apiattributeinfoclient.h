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


#include "octaneinfos.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiAttributeInfo
class ApiAttributeInfoProxy : public GRPCBase
{
public:
    /// fast version validity check
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isValidFor(
            const Octane::VersionT   version
            ) const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
