// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_PROJECT_MANAGER_H_
#define _API_PROJECT_MANAGER_H_ 1

#include "apinodesystem.h"
#include "octanereferenceexport.h"
#include "octanetypes.h"


namespace Octane
{

class ApiNode;
class ApiRootNodeGraph;

//--------------------------------------------------------------------------------------------------
/// Manages the current project in OctaneRender.
class OCTANEAPI_DECL ApiProjectManager
{
public:
    /// Returns whether the project manager is valid. The project manager is created after 
    /// the modules loaded.  
    static bool isValid();

    /// Returns the root node graph of the current project.
    ///
    /// NOTE: The object is owned by Octane and should NOT be destroyed.
    static ApiRootNodeGraph& rootNodeGraph();

    /// Returns the application preferences node (node type NT_LOCAL_APP_PREFS).
    static ApiNode& applicationPreferences();

    /// Returns the project settings node (node type NT_PROJECT_SETTINGS). This node will be
    /// deleted when the current project is closed. NULL if the project manager is invalid
    static ApiNode& projectSettings();

    /// Returns the project metadata node (node type NT_METADATA)
    static ApiNode& projectMetadata();

    /// Returns the preview render target of the current project. NULL if the project manager is invalid.
    static ApiNode& previewRenderTarget();

    /// Returns the geometry of the material ball we use for previewing.
    static const ApiNode& materialBall();

    /// Returns the absolute path to the current project. The returned pointer is owned by Octane
    /// and stays valid until the next call of getCurrentProject().
    static const char* getCurrentProject();

    /// Resets a project to a fresh new project.
    static bool resetProject();

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
    /// @return
    ///     TRUE on success, FALSE on failure.
    static bool loadProject(
        const char            *projectPath,
        AssetMissingCallbackT assetMissingcallback = NULL,
        void*                 assetMissinguserData = NULL,
        const bool            evaluate             = true);

    /// Returns TRUE if the project is loaded from a package (.orbx).
    static bool loadedFromPackage();

    /// Returns the OCS version that the current project was loaded from.
    static Octane::VersionT loadedOcsVersion();

    /// Saves a project.
    ///
    /// @note While saving a project into a package no other threads should modify either the
    ///     project's root node graph or other node graphs as it is not a thread-safe operation.
    /// @note This function is not supported by all SDK flavours
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
    /// @return
    ///     TRUE on success, FALSE on failure in which case there should have been additional error
    ///     messages on the log.
    static bool saveProjectAs(
        const char *path);

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
    /// @return
    ///     TRUE on success, FALSE on failure in which case there should have been additional error
    ///     messages on the log.
    static bool saveProjectAsReferencePackage(
        const char *                           path,
        const ReferencePackageExportSettings & referencePackageSettings);

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
    /// @return
    ///     TRUE if the package was unpacked successfully FALSE on failure in which case there
    ///     should have been additional error messages on the log.
    static bool unpackPackage(
        const char *unpackDir,
        const char *packagePath = NULL,
        const char* unpackName = NULL);

    /// Project observer object. This object's callback is called when a new project is created or
    /// the existing project is deleted.
    struct Observer
    {
         /// Callback, called on a project event.
        typedef void (*OnChangeT)(
            void *userData);

        /// Called after a new project is created and before the old project is deleted.
        /// ApiProjectManager functions will reference the new project at this point.
        OnChangeT mOnProjectNew;
        /// User data passed back unmodified in the callback.
        void      *mUserData;
    };
 
    /// Adds a new observer for the project.
    static void addObserver(
        Observer &observer);

    /// Removes an existing observer.
    static void removeObserver(
        Observer &removeObserver);
};

}


#endif // #ifndef _API_PROJECT_MANAGER_H_
