// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_LOCAL_DB_H_
#define _API_LOCAL_DB_H_    1

#include "octanetypes.h"
#include "octanevectypes.h"

namespace Octane
{

class ApiNodeGraph;
class ApiRootNodeGraph;

//--------------------------------------------------------------------------------------------------
/// This class allows you to access the localDB of Octane.
///
/// @note This is not supported by all SDK flavours. Check @ref ApiLocalDB::isSupported()
///     to know whether it is or not.
class OCTANEAPI_DECL ApiLocalDB
{
public:

    enum UpdateType
    {
        /// Notified when a category is added
        CATEGORY_ADDED,
        /// Notified when UI components should refresh the contents
        /// of a category. This applies recursively to all child
        /// categories.
        CATEGORY_REFRESHED,
        /// Notified when a category has been deleted. This may be raised
        /// once to indicate a category and all of its contents was deleted.
        CATEGORY_DELETED,
        /// Notified when a single package is saved
        PACKAGE_SAVED,
        /// Notified when meta data on a package has changed. The only such
        /// data currently supported is a thumbnail image.
        PACKAGE_CHANGED,
        /// Notified when a single package has been  deleted
        PACKAGE_DELETED,
    };

    typedef void (ObserverCallback)(
        void * opaqueData,
        UpdateType type,
        const char * path);

    /// Represents a package in LocalDB. This object represents the current state
    /// of a package in localDB, it will not reflect future updates.
    /// 
    /// All Package objects returned from the API must be released using free().
    class OCTANEAPI_DECL Package
    {
    public:

        /// Get the name for this package
        /// The returned pointer will remain valid until this package object is freed
        const char *name() const;

        /// Get the file name for this package
        /// The returned pointer will remain valid until this package object is freed
        ///
        /// Note: it is recommended to use Category::savePackage() and category::deletePackage()
        /// to add and remove packages, this will raise the corresponding events.
        const char *fileName() const;

        /// Check if a preview image embedded into this package.
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
        const char *getThumbnail(
            uint32_2 &size) const;

        /// Loads this package into a root node graph
        bool loadPackage(
            ApiNodeGraph &destinationGraph);

        /// Releases any memory allocated for this package
        void free();
    };


    /// Represents a category in LocalDB. This object represents the current state
    /// of a category in localDB, it will not reflect future updates.
    /// 
    /// All Category objects returned from the API must be released using free().
    class OCTANEAPI_DECL Category
    {
    public:

        /// Get the name for this category.
        const char *name() const;

        /// Returns the directory where the files in this category are.
        const char *fileName() const;

        /// Returns the number of subcategories in this category
        size_t subCategoryCount() const;

        /// returns the name of one of the subcategories in this category.
        const char *subCategoryName(
            size_t index) const;

        /// returns one of the subcategories in this category. The returned object must be freed
        /// using free()
        Category *subCategory(
            size_t index) const;

        /// Returns the number of packages in this category
        size_t packageCount() const;

        /// Returns one of the packages in this category.  The returned object must be freed
        /// using Package::free()
        Package *package(
            size_t index) const;

        /// Get a package. Returns NULL if no category with this path exists.
        /// 
        /// @param[in] path
        ///     The relative path from this category to the category.
        Category *categoryByPath(
            const char *path) const;

        /// Get a package. Returns NULL if no package with this path exists.
        /// 
        /// @param[in] path
        ///     The relative path from this category to the package.
        Package *packageByPath(
            const char *path) const;

        /// Creates a new category.
        /// 
        /// @param[in] name
        ///     The name of the new category.
        /// @return
        ///     The newly created category, or the existing category if a category with this name
        ///     already existed. May return NULL on failure.
        Category *createCategory(
            const char *name);

        /// Delete a child category of this category, including all subcategories and packages
        /// inside it.
        ///
        /// This will not free any Category and Package objects referring to
        /// child categories.
        /// 
        /// @return
        ///     true if the category got deleted.
        bool deleteCategory(
            const char *name);

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
        bool savePackage(
            const char          *name,
            ApiRootNodeGraph    *graph,
            const unsigned char *thumbnail,
            uint32_2            thumbnailSize);

        /// Delete a package in this category.
        ///
        /// This will not free any Package objects.
        /// 
        /// @return
        ///     true if the category got deleted.
        bool deletePackage(
            const char *name);

        /// Releases any memory allocated for this category
        void free();

    };

    /// Tells whether @ref ApiLocalDb is supported by this build
    static bool isSupported();

    /// Returns the root category of the local DB
    ///
    /// @note The returned category must be freed using free()
    /// @return
    ///     the root category or a NULL pointer if there was an error, in which case
    ///     there should have been additional error messages on the log.
    static Category *root();

    /// Moves the localDb folder to a new location. This call will also update the
    /// preferences node.
    /// 
    /// This will raise a CATEGORY_REFRESH event for root if the directory is changed.
    ///
    /// @param[in] newPath
    ///     The new localDB directory
    /// @param[in] moveFiles
    ///     if true, move all existing packages to the new location. If the original
    ///     folder is empty after this operation it will be deleted.
    /// @return
    ///     true if the operation was successful, false if the new location is not writable or
    ///     there was an error in which case there should have been additional error messages
    ///     on the log.
    static bool setRootDirectory(
        const char *newPath,
        bool       moveFiles);

    /// Add an observer to receive change notifications for localDB updates
    static void addObserver(
        void *             opaqueData,
        ObserverCallback * callback);

    /// Remove an observer to receive change notifications for localDB updates
    static void removeObserver(
        void *             opaqueData,
        ObserverCallback * callback);
};

} // namespace Octane


#endif // #infdef _API_LOCAL_DB_H_
