// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_DB_MATERIAL_MANAGER_H_
#define _API_DB_MATERIAL_MANAGER_H_ 1

#ifndef OCTANE_DEMO_VERSION

#include "octaneenums.h"
#include "octanevectypes.h"

// maximum length of a name in the live db
#define LIVE_DB_MAX_NAME_LEN 256

namespace Octane
{

class ApiNode;
class ApiNodeGraph;

//--------------------------------------------------------------------------------------------------
/// Manages access to OctaneRender Live database. This class is thread-safe.
class OCTANEAPI_DECL ApiDBMaterialManager
{
public:

    /// Represents a single LiveDB category.
    class DBCategory
    {
    public:

        /// id of this category
        int                mID;
        /// id representing the parent of this category (-1 for a root category)
        int                mParentID;
        /// Describes the assets stored in this category:
        OctaneLiveCategory mTypeID;
        /// name of this category
        char               mName[LIVE_DB_MAX_NAME_LEN];
    };


    /// A list of LiveDB categories.
    class OCTANEAPI_DECL DBCategoryArray
    {
    public:

        DBCategoryArray();

        ~DBCategoryArray();

        /// Initializes this array with size elements.
        void init(
            const size_t size);

        /// Destroys all the elements in this array.
        void free();

        /// Returns the internal array of categories.
        DBCategory* getCategory();

        /// Returns the number of categories.
        size_t getCount() const;

    private:

        DBCategory *mData;
        size_t     mSize;
    };

    /// Information about a material in the LiveDB.
    class DBMaterial
    {
    public:

        /// id identifying this material in the category
        int  mID;
        /// id of the parent category
        int  mCategoryID;
        /// name of this material
        char mName[LIVE_DB_MAX_NAME_LEN];
        /// nickname of the user that uploaded the material
        char mNickname[LIVE_DB_MAX_NAME_LEN];
        /// copyright notice for the material
        char mCopyright[LIVE_DB_MAX_NAME_LEN];
    };


    /// A list of LiveDB materials.
    class OCTANEAPI_DECL DBMaterialArray
    {
    public:

        DBMaterialArray();

        ~DBMaterialArray();

        /// Initializes this list with size elements.
        void init(
            const size_t size);

        /// Destroys all the elements in this array.
        void free();

        /// Returns the internal array of materials
        DBMaterial *getMaterial();

        /// Returns the number of materials.
        size_t getCount() const;

    private:

        DBMaterial *mData;
        size_t     mSize;
    };


    /// Returns a list of the categories in the LiveDB. This will fetch
    /// the list online and thus is an expensive operation.
    ///
    /// @param[out] list
    ///     List of the LiveDB categories.
    /// @return
    ///     TRUE on success, FALSE on failure. This will only fail when the
    ///     categories couldn't be fetched online.
    static bool getCategories(
        DBCategoryArray &list);

    /// Returns the list of materials for a category. This will fetch the 
    /// list online and thus is an expensive operation.
    ///
    /// @param[in]  categoryId
    ///     Id of the category from which we'd like the materials.
    /// @param[out] list
    ///     List of materials.
    /// @return
    ///     TRUE on success, FALSE on failure.
    static bool getMaterials(
        const int       categoryId,
        DBMaterialArray &list);

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
    /// @return
    ///     pointer to image data. The data must be freed with freeMaterialPreview().
    ///     If the download fails, the returned size is (0, 0) and the function returns
    ///     nullptr.
    ///
    ///     The buffer has 4 channels (red, green, blue, alpha) and has 1 byte per channel.
    ///     There is no padding between lines.
    static const uint8_t *getMaterialPreview(
        const int           materialId,
        const uint32_t      requestedSize,
        LiveDbThumbnailView view,
        Octane::uint32_2    &size);

    /// Free a material preview returned by getMaterialPreview()
    static void freeMaterialPreview(
        const uint8_t *preview);

    /// Downloads a material from the LiveDB. A material downloaded from the LiveDB
    /// is a nodegraph with a single output node (output linker node).
    ///
    /// @param[in]  materialId
    ///     Id of the material in the live db.
    /// @param[in]  destinationGraph 
    ///     The material graph will be copied into this graph.
    /// @param[out] outputNode
    ///     Optional pointer to the output linker node of the material graph.
    /// @return
    ///     TRUE on success, FALSE on failure.
    static bool downloadMaterial(
        const int    materialId,
        ApiNodeGraph &destinationGraph,
        ApiNode      **outputNode=NULL);

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
    /// @return 
    ///     The material or the texture node. This is the material or texture node in
    ///     the graph connected to the output linker node. Returns NULL when the download
    ///     failed.
    static ApiNode* downloadMaterial(
        const int  materialId,
        const char *assetPath);
};


} // namespace Octane

#endif  // #ifndef OCTANE_DEMO_VERSION

#endif // #ifndef _API_DB_MATERIAL_MANAGER_H_

