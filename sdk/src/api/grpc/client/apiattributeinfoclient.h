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


#include "octaneinfos.h"


class Convert;

class GRPCSettings;

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

private:
    static GRPCSettings & getGRPCSettings();
};
