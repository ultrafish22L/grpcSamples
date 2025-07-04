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
class ApiNodeArrayProxy;
#include "apinodegraphclient.h"


#include "apinodesystem.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiRootNodeGraph
class ApiRootNodeGraphProxy : public ApiNodeGraphProxy
{
public:
    /// Creates a root node graph (graph without owner) with the specified version.
    /// The caller owns the object and needs to delete it if it's not used anymore.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiRootNodeGraphProxy create(
            const Octane::VersionT                    version
            );

    /// Clears the root node graph (it will be empty afterwards) and sets it to the specified
    /// version.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void init(
            const Octane::VersionT                    version
            );

    /// Converts the root node graph to the current version and evaluates all nodes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void convertAndEvaluate(            );

    /// Returns the total time span for all animations in this graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::TimeSpanT animationTimeSpan(            ) const;

    /// Updates the time of all attributes in this root node graph. This will always evaluate 
    /// the changed nodes in the root node graph.
    /// 
    /// @param[in] time
    ///     The new time stamp
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void updateTime(
            const Octane::TimeT                       time
            );

    /// Imports a scene from disk into this graph. The version conversion is done automatically.
    /// 
    /// If the loading was successful, the old content of the root node graph will be gone.
    ///
    /// @param[in]  path 
    ///     Absolute path to the .ocs or .orbx file.
    /// @param[out] ocsVersion
    ///     Octane version the OCS XML string was written with.
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure.
    bool importFromFile(
            const char *                              path,
            Octane::VersionT &                        ocsVersion,
            Octane::AssetMissingCallbackT             assetMissingCallback,
            void *                                    assetsMissingCallbackUserData
            );

    /// Imports an OCS XML string scene from disk into this graph.  The version conversion 
    /// is done automatically.
    /// 
    /// If the loading was successful, the old content of the root node graph will be gone.
    ///
    /// @param[in]  baseDirectory
    ///     Path to a base directory used to resolve relative paths in the xml.
    /// @param[out] ocsVersion
    ///     Octane version the OCS XML string was written with.
    /// @param[in]  xml
    ///     XML string. Doesn't need to be null terminated.
    /// @param[in]  xmlLength
    ///     Length of the XML string (excl. any terminators).
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure.
    bool importOcsFromMemory(
            const char *                              baseDirectory,
            Octane::VersionT &                        ocsVersion,
            const char *                              xml,
            const size_t                              xmlLength,
            Octane::AssetMissingCallbackT             assetMissingCallback,
            void *                                    assetsMissingCallbackUserData
            );

    /// Imports an ORBX data from memory into this graph, chunk by chunk. The version conversion 
    /// is done automatically.
    /// 
    /// If the loading was successful, the old content of the root node graph will be gone.
    ///
    /// @param[in]  baseDirectory
    ///     Path to a base directory used to unpack the assets from the ORBX.
    ///     If asset files with the same name already exist in given directory,
    ///     they will not be rewritten. 
    /// @param[out] ocsVersion
    ///     Octane version the ORBX project data was written with.
    /// @param[in] getOrbxChunkCallback
    ///     The callback that returns ORBX file data in memory buffer chunk by chunk.
    /// @param[in]  orbxChunkCallbackUserData
    ///     Opaque user data passed in by the plugin.
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure.
    bool importOrbxFromCallback(
            const char *                              baseDirectory,
            Octane::VersionT &                        ocsVersion,
            Octane::ApiRootNodeGraph::NextChunkCallbackT getOrbxChunkCallback,
            void *                                    orbxChunkCallbackUserData,
            Octane::AssetMissingCallbackT             assetMissingCallback,
            void *                                    assetMissingCallbackUserData
            );

    /// Imports an ORBX data from memory into this graph. The version conversion 
    /// is done automatically.
    /// This is the faster version, as it does not use the dynamically reallocated buffer
    /// during loading ORBX data chunk by chunk.
    /// 
    /// If the loading was successful, the old content of the root node graph will be gone.
    ///
    /// @param[in]  baseDirectory
    ///     Path to a base directory used to unpack the assets from the ORBX.
    ///     If asset files with the same name already exist in given directory,
    ///     they will not be rewritten. 
    /// @param[out] ocsVersion
    ///     Octane version the ORBX project data was written with.
    /// @param[in] orbxData
    ///     The ORBX data buffer.
    /// @param[in] dataSize
    ///     The size of ORBX data buffer.
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure.
    bool importOrbxFromMemory(
            const char *                              baseDirectory,
            Octane::VersionT &                        ocsVersion,
            const void *                              orbxData,
            const size_t                              dataSize,
            Octane::AssetMissingCallbackT             assetMissingCallback,
            void *                                    assetsMissingCallbackUserData
            );

    /// Exports this root graph into a file (regular ocs or package).
    /// In-memory data in nodes will be written out to file:
    ///
    ///     * texture raw image buffer -> png/exr file
    ///     * raw mesh geometry        -> obj file
    ///
    /// @note This function is not supported by all SDK flavours
    /// @param[in]  filePath 
    ///     absolute path of the file. This can be a .orbx or a .ocs file.
    /// @param[in]  useRelativePaths (optional)
    ///     set whether to save asset file paths relative to @ref filePath
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on successful write, FALSE otherwisein which case there
    ///     should have been additional error messages on the log.
    bool exportToFile(
            const char *                              filePath,
            bool                                      useRelativePaths
            ) const;

    /// Exports this graph into a string and optionally exports the raw data.
    ///
    /// @param[in]  baseDirectory 
    ///     Absolute path to the export directory for assets (optional).
    ///     If not provided, assets aren't exported.
    /// @param[in]  useRelativePaths (optional)
    ///     set whether to save asset file paths relative to @ref baseDirectory
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Null terminated OCS XML, which is owned by the API and shouldn't be deleted and stays
    ///     valid until the next call of this function.
    std::string exportToString(
            const char *                              baseDirectory,
            bool                                      useRelativePaths
            ) const;

    /// Returns the number of reference graphs that this root graph contains
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t referenceGraphCount(            ) const;

    /// Loads all reference graphs in this graph
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void loadAllReferences(            );

    /// Unloads all reference graphs in this graph
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void unloadAllReferences(            );

private:
    static GRPCSettings & getGRPCSettings();
};
