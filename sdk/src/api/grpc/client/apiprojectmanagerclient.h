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
    class ApiRootNodeGraphProxy;
}


#include "apiprojectmanager.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}

#include "grpcchangeevents.h"

namespace OctaneGRPC
{

/// Proxy class for ApiProjectManager
class ApiProjectManagerProxy : public GRPCBase
{
public:
    /// Returns whether the project manager is valid. The project manager is created after
    /// the modules loaded.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isValid();

    /// Returns the root node graph of the current project.
    ///
    /// NOTE: The object is owned by Octane and should NOT be destroyed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiRootNodeGraphProxy rootNodeGraph();

    /// Returns the application preferences node (node type NT_LOCAL_APP_PREFS).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeProxy applicationPreferences();

    /// Returns the project settings node (node type NT_PROJECT_SETTINGS). This node will be
    /// deleted when the current project is closed. NULL if the project manager is invalid
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeProxy projectSettings();

    /// Returns the project metadata node (node type NT_METADATA)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeProxy projectMetadata();

    /// Returns the preview render target of the current project. NULL if the project manager is invalid.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeProxy previewRenderTarget();

    /// Returns the geometry of the material ball we use for previewing.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeProxy materialBall();

    /// Returns the absolute path to the current project. The returned pointer is owned by Octane
    /// and stays valid until the next call of getCurrentProject().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getCurrentProject();

    /// Resets a project to a fresh new project.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool resetProject(
            bool   suppressUI
            );

    /// Loads a project into octane. A project is either and .ocs file or
    /// a .orbx file.
    ///
    /// @param[in]  projectPath
    ///     Absolute path to the project file on disk.
    /// @param[in] assetMissingCallback
    ///     Callback will be called if the ocs loader could not find an asset file.
    /// @param[in]  assetMissingCallbackUserData
    ///     Opaque user data passed in by the plug in.
    /// @param[in]  evaluate
    ///     Setting this to FALSE will speedup the project load by not evaluating the root node
    ///     graph which skips loading the file data as well as scripted node graph execution.
    ///     Use this just if you just need to inspect the project contents. Projects loaded with
    ///     evaluation disabled are not suitable for rendering. If you need to render a project
    ///     previously loaded with evaluation disabled you'll need to reload it enabling it.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure.
    static bool loadProject(
            const char *                              projectPath,
            Octane::AssetMissingCallbackT             assetMissingcallback,
            void *                                    assetMissinguserData,
            const bool                                evaluate
            );

    /// Returns TRUE if the project is loaded from a package (.orbx).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool loadedFromPackage();

    /// Returns the OCS version that the current project was loaded from.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::VersionT loadedOcsVersion();

    /// Saves a project.
    ///
    /// @note While saving a project into a package no other threads should modify either the
    ///     project's root node graph or other node graphs as it is not a thread-safe operation.
    /// @note This function is not supported by all SDK flavours
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure in which case there should have been additional error
    ///     messages on the log.
    static bool saveProject();

    /// Saves a project under a different name.
    ///
    /// @note While saving a project into a package no other threads should modify either the
    ///     project's root node graph or other node graphs as it is not a thread-safe operation.
    /// @note Procedurally generated geometry is saved as OBJ so just regular polygonal geometry
    ///     will be exported ignoring hair and particle primitives.
    /// @note This function is not supported by all SDK flavours
    /// @param[in]  path
    ///     Absolute path to the file on disk. This can be a .orbx file
    ///     or a .ocs file.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure in which case there should have been additional error
    ///     messages on the log.
    static bool saveProjectAs(
            const char *   path
            );

    /// Saves a project into an orbx package. The resulting orbx will include extra data with
    /// animated bounding boxes of the scene geometry which can be later visualized when the orbx is
    /// loaded in ApiReferenceGraph (GT_REFERENCE).
    ///
    /// @note While saving a project into a package no other threads should modify either the
    ///     project's root node graph or other node graphs as it is not a thread-safe operation.
    /// @note Procedurally generated geometry is saved as OBJ so just regular polygonal geometry
    ///     will be exported ignoring hair and particle primitives.
    /// @note This function is not supported by all SDK flavours
    /// @param[in]  path
    ///     Absolute path to the file on disk. Only .orbx files are supported.
    /// @param[in]  referencePackageSettings
    ///     Configures the export parameters of the bounding boxes
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure in which case there should have been additional error
    ///     messages on the log.
    static bool saveProjectAsReferencePackage(
            const char *                              path,
            const Octane::ReferencePackageExportSettings & referencePackageSettings
            );

    /// Unpacks a package into the provided directory. If no package path is specified, the package
    /// of the current project will unpacked. Obviously, the latter will work only if the project
    /// was loaded from a package. This will NOT switch the current loaded package to
    /// the unpacked package.
    ///
    /// @note This function is not supported by all SDK flavours
    /// @param[in]  unpackDir
    ///     Absolute path to the unpack directory (must not be NULL).
    /// @param[in]  packagePath
    ///     Absolute path of the package file (.orbx) or NULL if the project package should be
    ///     unpacked.
    /// @param[in]  unpackName
    ///     The filename to unpack or NULL if the whole package should be unpacked.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the package was unpacked successfully FALSE on failure in which case there
    ///     should have been additional error messages on the log.
    static bool unpackPackage(
            const char *                              unpackDir,
            const char *                              packagePath,
            const char *                              unpackName
            );

    /// Adds a new observer for the project.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void addObserver(
            GRPCProjectManagerObserver   observer
            );

    /// Removes an existing observer.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void removeObserver(
            GRPCProjectManagerObserver   removeObserver
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
