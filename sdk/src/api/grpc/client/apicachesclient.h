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
namespace OctaneGRPC
{
    class ApiNodeProxy;
}


#include "apicaches.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiCaches
class ApiCachesProxy : public GRPCBase
{
public:
    /// Returns the maximum size of the meshlet cache in bytes. It is the same value that is stored
    /// in A_MESHLET_CACHE_SIZE in the application preferences node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint64_t getMeshletCacheSize();

    /// Returns the amount data stored in the meshlet cache in number of bytes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint64_t getMeshletCacheUsedSize();

    /// Deletes all meshlet cache files that are currently not in use.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void clearMeshletCache();

    /// Returns TRUE if a cache file can be found for the given geometry import preferences and
    /// filename / meshlet ID attribute and FALSE if not. If a meshlet cache file exists it will be
    /// opened and kept open by the mesh node.
    ///
    /// This function can be used before or after the mesh node is evaluated. When you call it
    /// before evaluation you don't have to populate the actual geometry attributes yet. This allows
    /// you to check whether you need to populate the geometry data or not and thus save a bit of
    /// memory and time.
    ///
    /// If the meshlet cache file exists and the node was not evaluated yet you still have to
    /// evaluate the mesh node to populate the material / object layer names and pins and bring the
    /// node into a consistent state.
    ///
    /// If the meshlet cache file does not exist you will have to completely populate the geometry
    /// attributes and then evaluate the mesh node. This will then kick off the meshlet build in the
    /// background. You can check the state of that build using checkMeshletBuildStatus().
    ///
    /// @param  meshNode
    ///     Pointer to the mesh node to check. Must be a valid pointer to a node of type NT_GEO_MESH.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if a valid meshlet cache file exists for the mesh node, FALSE if not.
    static bool hasMeshletCacheFile(
            ApiNodeProxy *   meshNode
            );

    /// Check the status of the cached meshlet mesh for the given mesh node. This should be run
    /// *after* the mesh node got evaluated and any meshlet data was loaded or its build was started.
    ///
    /// @param  meshNode
    ///     Pointer to the mesh node to check. Must be a valid pointer to a node of type NT_GEO_MESH.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     CACHE_NONE if meshNode is not a valid pointer to a mesh node, or to a mesh node that has
    ///     A_CONVERT_TO_MESHLETS set to FALSE. Otherwise returns one of the other enums in
    ///     CacheStatus.
    static Octane::CacheStatus checkMeshletBuildStatus(
            ApiNodeProxy *   meshNode
            );

    /// Deletes the meshlet cache file of the given node if the file isn't used anywhere else. This
    /// can be called before or after evaluation of the mesh node.
    ///
    /// @param  meshNode
    ///     Pointer to the mesh node of which the meshlet cache file should be deleted. Must be a
    ///     valid pointer to a node of type NT_GEO_MESH.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if either the node pointer didn't represent a mesh node with a valid meshlet cache
    ///     file, or if the cache file for the node was deleted. FALSE if there still exists a cache
    ///     file for the mesh node.
    static bool clearMeshletCacheFileForNode(
            ApiNodeProxy *   meshNode
            );

    /// Returns the maximum size of the virtual texture cache in bytes. It is the same value that
    /// is stored in A_VIRTUAL_TEXTURE_CACHE_SIZE in the application preferences node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint64_t getVirtualTextureCacheSize();

    /// Returns the amount data stored in the virtual texture cache in number of bytes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint64_t getVirtualTextureCacheUsedSize();

    /// Deletes virtual texture cache files that are currently not in use, until
    /// the cache reaches the desired maximum size
    ///
    /// @param maximumSize
    ///     Maximum size to keep. Pass in 0 if you want to remove all cache files not
    ///     currently in use.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void pruneVirtualTextureCache(
            uint64_t   maximumSize
            );

    /// Check the status of the cached virtual texture corresponding to the settings contained
    /// in the given node.
    ///
    /// If node is nullptr, does not present a type that supports virtual textures, or if the
    /// settings don't result in a virtual texture being used, returns CACHE_NONE.
    /// Otherwise returns one of the other constants in CacheStatus.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::CacheStatus checkVirtualTextureStatus(
            ApiNodeProxy *   node
            );

    /// Clears the cache entry matching the settings contained in the given node item
    /// This call succeeds only if there are no other node items referencing the same
    /// file, and if the build for the given cache entry is not currently in progress.
    /// The item is left in an intermediate state, evaluating the item after this call
    /// may rebuild the cache for the item.
    ///
    /// If a build is in progress, the build may be cancelled by this call, resulting
    /// in the file being deleted some indeterminate time after this call.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     true if either the node didn't represent a virtual texture cache, or if
    ///     the cache file for the node was deleted. False if there still exists a
    ///     cache file.
    static bool clearVirtualTextureCacheForNode(
            ApiNodeProxy *   node
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
