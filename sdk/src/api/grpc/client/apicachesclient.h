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


#include "apicaches.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiCaches
class ApiCachesProxy : public GRPCBase
{
public:
    /// Returns the maximum size of the meshlet cache in bytes. It is the same value that is stored
    /// in A_MESHLET_CACHE_SIZE in the application preferences node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint64_t getMeshletCacheSize(            );

    /// Returns the amount data stored in the meshlet cache in number of bytes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint64_t getMeshletCacheUsedSize(            );

    /// Deletes all meshlet cache files that are currently not in use.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void clearMeshletCache(            );

private:
    static GRPCSettings & getGRPCSettings();
};
