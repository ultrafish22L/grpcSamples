// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#include "apinodesystem.h"



namespace Octane
{
    

/// This class provides functions to query and clear file caches.
class OCTANEAPI_DECL ApiCaches
{
public:

    /// Returns the maximum size of the meshlet cache in bytes. It is the same value that is stored
    /// in A_MESHLET_CACHE_SIZE in the application preferences node.
    static uint64_t getMeshletCacheSize();

    /// Returns the amount data stored in the meshlet cache in number of bytes.
    static uint64_t getMeshletCacheUsedSize();

    /// Deletes all meshlet cache files that are currently not in use.
    static void clearMeshletCache();
};


}   // namespace Octane
