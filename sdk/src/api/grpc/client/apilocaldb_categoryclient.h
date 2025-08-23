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
namespace OctaneGRPC
{
    class ApiRootNodeGraphProxy;
    class ApiNodeGraphProxy;
    class ApiLocalDBProxy_Package;
}


#include "apilocaldb.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiLocalDB_Category
class ApiLocalDBProxy_Category : public GRPCBase
{
public:
    /// Get the name for this category.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string name() const;

    /// Returns the directory where the files in this category are.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string fileName() const;

    /// Returns the number of subcategories in this category
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t subCategoryCount() const;

    /// returns the name of one of the subcategories in this category.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string subCategoryName(
            size_t   index
            ) const;

    /// returns one of the subcategories in this category. The returned object must be freed
        /// using free()
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiLocalDBProxy_Category subCategory(
            size_t   index
            ) const;

    /// Returns the number of packages in this category
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t packageCount() const;

    /// Returns one of the packages in this category.  The returned object must be freed
        /// using Package::free()
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiLocalDBProxy_Package package(
            size_t   index
            ) const;

    /// Get a package. Returns NULL if no category with this path exists.
        ///
        /// @param[in] path
        ///     The relative path from this category to the category.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiLocalDBProxy_Category categoryByPath(
            const char *   path
            ) const;

    /// Get a package. Returns NULL if no package with this path exists.
        ///
        /// @param[in] path
        ///     The relative path from this category to the package.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiLocalDBProxy_Package packageByPath(
            const char *   path
            ) const;

    /// Creates a new category.
        ///
        /// @param[in] name
        ///     The name of the new category.
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     The newly created category, or the existing category if a category with this name
        ///     already existed. May return NULL on failure.
    ApiLocalDBProxy_Category createCategory(
            const char *   name
            );

    /// Delete a child category of this category, including all subcategories and packages
        /// inside it.
        ///
        /// This will not free any Category and Package objects referring to
        /// child categories.
        ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     true if the category got deleted.
    bool deleteCategory(
            const char *   name
            );

    /// Save a package in the localDB under this category
        /// @param[in] name
        ///     The name for this package. If a package with this name exists it will be
        ///     overwritten. Must not contain slashes.
        /// @param[in] graph
        ///     The graph to save.
        /// @param[in] thumbnail
        ///     The thumbnail to save, as a 8-bit RGBA buffer. Should be set to NULL if
        ///     thumbnailSize is (0, 0)
        /// @param[in] thumbnailSize
        ///     The size of the thumbnail image. May be set to (0, 0) to skip saving a thumbnail.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool savePackage(
            const char *                              name,
            ApiRootNodeGraphProxy *                   graph,
            const unsigned char *                     thumbnail,
            int                                       thumbnailSizeInBytes,
            OctaneVec::uint32_2                       thumbnailSize
            );

    /// Delete a package in this category.
        ///
        /// This will not free any Package objects.
        ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     true if the category got deleted.
    bool deletePackage(
            const char *   name
            );

    /// Releases any memory allocated for this category
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void free();

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
