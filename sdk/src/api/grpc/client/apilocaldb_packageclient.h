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
    class ApiNodeGraphProxy;
}


#include "apilocaldb.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiLocalDB_Package
class ApiLocalDBProxy_Package : public GRPCBase
{
public:
    /// Get the name for this package
        /// The returned pointer will remain valid until this package object is freed
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string name() const;

    /// Get the file name for this package
        /// The returned pointer will remain valid until this package object is freed
        ///
        /// Note: it is recommended to use Category::savePackage() and category::deletePackage()
        /// to add and remove packages, this will raise the corresponding events.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string fileName() const;

    /// Check if a preview image embedded into this package.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasThumbnail() const;

    /// Get the preview image embedded into this package. Some packages may not have a preview
        /// image, this function will return NULL for these packages.
        ///
        /// Each pixel is stored in 4 bytes (red, green, blue, alpha). There will be no padding
        /// between rows.
        ///
        /// The returned pointer will remain valid until this package object is freed
        /// @param[out] size
        ///     Will be set to the size of the image. The image will be 8-bit RGBA.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string getThumbnail(
            OctaneVec::uint32_2 &   size
            ) const;

    /// Loads this package into a root node graph
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool loadPackage(
            ApiNodeGraphProxy &   destinationGraph
            );

    /// Releases any memory allocated for this package
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void free();

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
