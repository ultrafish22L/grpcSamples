// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_TILE_GRID_H_
#define _API_TILE_GRID_H_  1

#include "apiarray.h"
#include "octanevectypes.h"

/// This header provides some of the functionality used to select source images
/// for UV tiles and tile set nodes.


namespace Octane
{
    class ApiItem;

    /// Settings passed in and out of our pattern matching component
    struct ApiTileGridSettings
    {
        /// Parent directory for the files loaded into the tiles. May be nullptr
        /// if the object wasn't initialized yet, or if it was initialized from a
        /// node item inside an ORBX file.
        /// When passing in a ApiTileGridSettings to one of the functions in ApiTileGridLoader
        /// this string is always copied to an internal buffer.
        const char *     mParent;
        /// Size of the tile grid. The dimensions must not be 0.
        Octane::uint32_2 mGridSize;
        /// Flip order of grid tiles in V direction
        /// This field isn't used by this class, the first tile in getFiles() or the tile
        /// at index (0, 0) is always the tile where I = 0, U = 0 and V = 0.
        /// If this setting is true, the UI should present the first tile in the top left corner,
        /// otherwise it should be in the bottom left corner.
        /// This setting is loaded and stored in node items.
        bool             mGridFlipV;
        /// Index used for the first tile (this will be set to 0 or 1; ignored
        /// for UDIM indices)
        uint32_t         mStart;
    };


    /// A ApiTileGridLoader contains a list of files and the settings to load these files and lay
    /// them out in a grid.
    class OCTANEAPI_DECL ApiTileGridLoader
    {
    public:
        /// Creates a pattern for generating file names, as described in the 
        /// attribute info of A_GRID_FILE_PATTERN on NT_TEX_IMAGE_TILES.
        ///
        /// @return
        ///     ApiTileGridLoader object. This must be released by calling destroy().
        static ApiTileGridLoader * create();

        /// Destroy this object.
        void destroy();

        // -- high level functions to load and save to node items --

        /// Initialize from settings stored in a supported node item (NT_TEX_IMAGE_TILES and NT_TEX_IMAGE_TILE_SET)
        /// Equivalent to calling updatePattern() and applyStoredSettings(), but it reads the source data from the
        /// passed in node item.
        void loadFromNodeItem(
            const ApiItem * node);

        /// Store data in this object in a supported node item (NT_TEX_IMAGE_TILES and NT_TEX_IMAGE_TILE_SET)
        /// This does not evaluate the item. This allows modifying other settings in the node before loading
        /// any assets. The caller should call node->evaluate() after finishing this setup.
        void saveToNodeItem(
            ApiItem * node);

        // -- functions to automatically populate settings and files --

        /// Set from settings stored in a node. Updates the settings and files in this object.
        ///
        /// @param initialSettings
        ///     Stored settings. If mParent is set to nullptr and the files are not stored
        ///     in an ORBX package, it will be inferred from one of the files in initialFiles.
        ///     mStart will be set to 0 or 1 if this matches up with the first valid file name
        ///     in initialFiles.
        /// @param initialFiles
        ///     The list of files in the node in question. 
        /// @param inPackage 
        ///     True if the node exists inside an ORBX package.
        void applyStoredSettings(
            const ApiTileGridSettings & initialSettings,
            ApiArray<const char*> initialFiles,
            bool inPackage);

        /// Given a file name, guess which pattern it may represent.
        /// Update this object with the guessed pattern and settings.
        /// This can be used after the user selects the first image in a new node.
        /// 
        /// If the given file name doesn't contain plausible placeholders, hasPlaceholders()
        /// will return false after this call.
        ///
        /// @param firstImg 
        ///     Selected file name. Ideally this is the first tile in the grid.
        /// @param indices
        ///     indices in the grid where we think the given tile is
        void inferSettingsFromFilename(
            const char * firstImg,
            Octane::uint32_2 & indices);

        /// Look for tiles in the file system. This requires that a valid parent directory is set up.
        ///
        /// @param newSize
        ///     If not {0, 0}, the grid will be resized to this size, and only newly added cells are scanned.
        ///     If a pattern has UV indices, this means scanning in newly added rows or columns, while with
        ///     linear indices, this means scanning added file names at the end.
        void scanTiles(
            uint32_2 newSize);

        /// Automatically resize a tile grid. This clears the internal list of tiles
        /// and scans the file system to see how many rows or columns contain existing files.
        ///
        /// If the pattern has an index, the grid will only grow in the V direction.
        void automaticSizeGrid();

        // -- settings --

        /// Get the current settings.
        const ApiTileGridSettings & getSettings() const;

        /// Change the settings stored in this object, and if the list of files is set, add or
        /// remove padding to it so that it covers the new grid size.
        void updateSettings(
            const ApiTileGridSettings & settings);

        // -- files --

        /// Get the list of files.
        ///
        /// This internally reallocates some buffer to back the returned array.
        /// The returned array stays valid as long as this object stays valid and the list of
        /// files is not modified by another operation.
        ///
        /// If the list wasn't populated in any way before this may return an empty array.
        ApiArray<const char*> getFiles();

        /// Populate the current list of files.
        /// This requires that the grid size has been previously set up with updateSettings().
        /// This call does not update the parent directory, or the file name pattern.
        /// If possible the caller should update the pattern accordingly, or set it to the
        /// empty string.
        void setFiles(
            ApiArray<const char*> files);

        /// Check if a cell has a file assigned to it.
        bool hasFileInCell(
            const Octane::uint32_2 cellIndex) const;

        /// For cells which aren't empty, return the file name. (without any parent directories)
        /// Returned pointers remain valid as long as the grid is not modified.
        /// For empty cells return nullptr.
        const char * fileNameForCell(
            const Octane::uint32_2 cellIndex) const;

        /// Count the number of valid files in the currently defined tile grid.
        size_t count() const;

        // -- pattern --

        /// Updates the file name pattern. If you are going to store these settings in
        /// a node, you should also update the list of files accordingly, eg. by calling
        /// scanTiles().
        void updatePattern(
            const char * pattern);

        /// Returns true if the pattern is empty.
        bool hasEmptyPattern() const;

        /// Returns the pattern as a string.
        const char * patternString() const;

        /// True if the pattern contains any placeholders. Implies not empty.
        bool hasPlaceholders() const;

        /// True if the pattern has any linear indexing (including UDIM).
        bool hasIndex() const;

        /// True if the pattern has a UDIM placeholder.
        bool hasUDIM() const;

        /// True if the pattern uses two-dimensional indexing.
        bool hasUv() const;

        /// Sutstitute placeholders in the file name pattern with the given
        /// indices
        ///
        /// @param start
        ///     Index where the numbering should start (usually 0 or 1)
        /// @param index
        ///     Linear row major index of the tile
        /// @param u
        ///     Index of the tile in the U direction
        /// @param v
        ///     Index of the tile in the V direction
        /// @return
        ///     Resulting file name. Will remain valid until the next call
        ///     to this function on this object.
        const char * substitute(
            const uint32_t start,
            const uint32_t index,
            const uint32_t u,
            const uint32_t v);
    };

} // namespace Octane


#endif // #ifndef _API_TILE_GRID_H_
