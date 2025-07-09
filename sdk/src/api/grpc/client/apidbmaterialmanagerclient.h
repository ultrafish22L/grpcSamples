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
class ApiNodeProxy;
class ApiNodeGraphProxy;
class ApiDBMaterialManagerProxy_DBCategoryArray;
class ApiDBMaterialManagerProxy_DBMaterialArray;


#include "apidbmaterialmanager.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiDBMaterialManager
class ApiDBMaterialManagerProxy : public GRPCBase
{
public:
    /// Returns a list of the categories in the LiveDB. This will fetch
    /// the list online and thus is an expensive operation.
    ///
    /// @param[out] list
    ///     List of the LiveDB categories.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure. This will only fail when the
    ///     categories couldn't be fetched online.
    static bool getCategories(
            ApiDBMaterialManagerProxy_DBCategoryArray &list
            );

    /// Returns the list of materials for a category. This will fetch the 
    /// list online and thus is an expensive operation.
    ///
    /// @param[in]  categoryId
    ///     Id of the category from which we'd like the materials.
    /// @param[out] list
    ///     List of materials.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure.
    static bool getMaterials(
            const int                                 categoryId,
            ApiDBMaterialManagerProxy_DBMaterialArray &list
            );

    /// Gets an image of the material rendered on the material ball from the
    /// LiveDB server. The underlying implementation will cache the downloaded
    /// images, so any given image will be downloaded only once.
    ///
    /// @note This function is not supported by all SDK flavors
    /// @param[in]  materialId
    ///     Id identifying the material
    /// @param[in]  requestedSize
    ///     Requested image size.
    /// @param[in]  view
    ///     Which view to download. One of the values in Octane#LiveDbThumbnailView.
    ///     If view is VIEW_COMBINED a small image of all views stacked on top of each other is
    ///     returned.
    /// @param[out]  size
    ///     The size of the returned image. If view is not VIEW_COMBINED the downloaded image
    ///     will be resized so it fits in the square with side requestedSize. For VIEW_COMBINED
    ///     the size is ignored and a fixed size is returned.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     pointer to image data. The data must be freed with freeMaterialPreview().
    ///     If the download fails, the returned size is (0, 0) and the function returns
    ///     nullptr.
    ///
    ///     The buffer has 4 channels (red, green, blue, alpha) and has 1 byte per channel.
    ///     There is no padding between lines.
    static std::unique_ptr<uint8_t> getMaterialPreview(
            const int                                 materialId,
            const uint32_t                            requestedSize,
            Octane::LiveDbThumbnailView               view,
            Octane::uint32_2 &                        size
            );

    /// Downloads a material from the LiveDB. A material downloaded from the LiveDB
    /// is a nodegraph with a single output node (output linker node).
    ///
    /// @param[in]  materialId
    ///     Id of the material in the live db.
    /// @param[in]  destinationGraph 
    ///     The material graph will be copied into this graph.
    /// @param[out] outputNode
    ///     Optional pointer to the output linker node of the material graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure.
    static bool downloadMaterial(
            const int                                 materialId,
            ApiNodeGraphProxy &                       destinationGraph,
            ApiNodeProxy **                           outputNode
            );

    /// Downloads a material from the LiveDB. This will put the material nodegraph
    /// into the project root graph and saves out the assets in the provided path.
    /// The texture nodes will be reloaded to use the assets on disk.
    /// It mimics the old behavior of getNode.
    ///
    /// @param[in]  materialId
    ///     Id of the material in the live db.
    /// @param[in]  assetPath
    ///     Absolute path to the asset save locations (directory).
    ///     This directory must exist on disk otherwise the nodes aren't converted.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return 
    ///     The material or the texture node. This is the material or texture node in
    ///     the graph connected to the output linker node. Returns NULL when the download
    ///     failed.
    static ApiNodeProxy downloadMaterial(
            const int                                 materialId,
            const char *                              assetPath
            );

private:
    static GRPCSettings & getGRPCSettings();
};
