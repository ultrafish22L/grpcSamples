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


#include "apitilegrid.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiTileGridLoader
class ApiTileGridLoaderProxy : public GRPCBase
{
public:
    /// Creates a pattern for generating file names, as described in the
        /// attribute info of A_GRID_FILE_PATTERN on NT_TEX_IMAGE_TILES.
        ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     ApiTileGridLoader object. This must be released by calling destroy().
    static ApiTileGridLoaderProxy create();

    /// Destroy this object.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Initialize from settings stored in a supported node item (NT_TEX_IMAGE_TILES and NT_TEX_IMAGE_TILE_SET)
        /// Equivalent to calling updatePattern() and applyStoredSettings(), but it reads the source data from the
        /// passed in node item.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void loadFromNodeItem(
            const ApiItemProxy *   node
            );

    /// Store data in this object in a supported node item (NT_TEX_IMAGE_TILES and NT_TEX_IMAGE_TILE_SET)
        /// This does not evaluate the item. This allows modifying other settings in the node before loading
        /// any assets. The caller should call node->evaluate() after finishing this setup.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void saveToNodeItem(
            ApiItemProxy *   node
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void applyStoredSettings(
            const Octane::ApiTileGridSettings &       initialSettings,
            Octane::ApiArray<const char *>            initialFiles,
            bool                                      inPackage
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void inferSettingsFromFilename(
            const char *                              firstImg,
            Octane::uint32_2 &                        indices
            );

    /// Look for tiles in the file system. This requires that a valid parent directory is set up.
        ///
        /// @param newSize
        ///     If not {0, 0}, the grid will be resized to this size, and only newly added cells are scanned.
        ///     If a pattern has UV indices, this means scanning in newly added rows or columns, while with
        ///     linear indices, this means scanning added file names at the end.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void scanTiles(
            OctaneVec::uint32_2   newSize
            );

    /// Automatically resize a tile grid. This clears the internal list of tiles
        /// and scans the file system to see how many rows or columns contain existing files.
        ///
        /// If the pattern has an index, the grid will only grow in the V direction.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void automaticSizeGrid();

    /// Get the current settings.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    const Octane::ApiTileGridSettings getSettings() const;

    /// Change the settings stored in this object, and if the list of files is set, add or
        /// remove padding to it so that it covers the new grid size.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void updateSettings(
            const Octane::ApiTileGridSettings &   settings
            );

    /// Get the list of files.
        ///
        /// This internally reallocates some buffer to back the returned array.
        /// The returned array stays valid as long as this object stays valid and the list of
        /// files is not modified by another operation.
        ///
        /// If the list wasn't populated in any way before this may return an empty array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::vector<std::string> getFiles();

    /// Populate the current list of files.
        /// This requires that the grid size has been previously set up with updateSettings().
        /// This call does not update the parent directory, or the file name pattern.
        /// If possible the caller should update the pattern accordingly, or set it to the
        /// empty string.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setFiles(
            Octane::ApiArray<const char *>   files
            );

    /// Check if a cell has a file assigned to it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasFileInCell(
            const Octane::uint32_2   cellIndex
            ) const;

    /// For cells which aren't empty, return the file name. (without any parent directories)
        /// Returned pointers remain valid as long as the grid is not modified.
        /// For empty cells return nullptr.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string fileNameForCell(
            const Octane::uint32_2   cellIndex
            ) const;

    /// Count the number of valid files in the currently defined tile grid.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t count() const;

    /// Updates the file name pattern. If you are going to store these settings in
        /// a node, you should also update the list of files accordingly, eg. by calling
        /// scanTiles().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void updatePattern(
            const char *   pattern
            );

    /// Returns true if the pattern is empty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasEmptyPattern() const;

    /// Returns the pattern as a string.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string patternString() const;

    /// True if the pattern contains any placeholders. Implies not empty.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasPlaceholders() const;

    /// True if the pattern has any linear indexing (including UDIM).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasIndex() const;

    /// True if the pattern has a UDIM placeholder.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasUDIM() const;

    /// True if the pattern uses two-dimensional indexing.
    /// @param[out] status
    ///     Contains the status of the gRPC call
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
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     Resulting file name. Will remain valid until the next call
        ///     to this function on this object.
    std::string substitute(
            const uint32_t                            start,
            const uint32_t                            index,
            const uint32_t                            u,
            const uint32_t                            v
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
