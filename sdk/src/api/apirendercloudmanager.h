// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_RENDER_CLOUD_MANAGER_H_
#define _API_RENDER_CLOUD_MANAGER_H_    1

#ifndef OCTANE_DEMO_VERSION

#include "octanetypes.h"

namespace Octane
{

class ApiRootNodeGraph;


//--------------------------------------------------------------------------------------------------
/// API for controlling cloud rendering using Octane Render Cloud.
///
/// The manager allows uploading projects and nodegraphs and trigger new render tasks on the cloud.
///
/// Usage example:
///
///     void onUploadFinished(
///        const bool  success,
///        const ApiRenderCloudManager::GuidT sceneGuid,
///        const ApiRenderCloudManager::GuidT,
///        const ApiRenderCloudManager::GuidT,
///        const char*,
///        void*)
///     {
///         if(!success) return;
///         // Open a browser window for the user to setup a new render job
//          ApiRenderCloudManager::newRenderTask(sceneGuid);
///     }
///
///     // Upload the current project
///     ApiRenderCloudManager::uploadCurrentProject(NULL, NULL, NULL, onUploadFinished);
///
/// This API is not thread safe!
class OCTANEAPI_DECL ApiRenderCloudManager
{
public:

    /// Type to identify an asset given its GUID
    typedef const char* GuidT;

    /// Data provided by the server about the current user's subscription status
    struct SubscriptionInfo
    {
        /// Whether the user has a current subscription to the cloud rendering service
        bool mSubscribed;
        /// Number of credits currently available in the user's account in USD.
        /// This can be a negative number if the user has gone into overdraft
        float mAvailableCreditBalance;
        /// Number of RNDR tokens in the user's account.
        float mAvailableRndrBalance;
    };


    /// Populates the provided struct with the information for the current user's
    /// subscription. 
    ///
    /// @note This requires a valid SSO session and will perform a HTTP request
    ///     every time which will block the call until it returns.
    ///
    /// @param subscriptionInfo
    ///     The user's subscription info. Just meaningful if the method returns TRUE.
    /// @return
    ///     TRUE if the subscription information could be fetch successfully, FALSE
    ///     otherwise, in which case an error wil also be displayed in the log.
    static bool userSubscriptionInfo(
        SubscriptionInfo &subscriptionInfo);

    /// Upload update callback type
    ///
    /// @param[in] percent
    ///     Total upload percentage
    /// @param[in] data
    ///     User data passed back to the callback
    /// @return If the callback returns true, the upload will continue, otherwise 
    ///         it will be stooped
    typedef bool (*UpdateCallbackT)(
        const float percent,
        void        *data);

    /// Upload finish callback type
    ///
    /// @param[in] success
    ///     Will contain true if the upload has finished successfully
    /// @param[in] errorMsg
    ///     If @ref success is FALSE this will contain the error message
    /// @param[in] sceneGuid
    ///     Scene GUID on the server
    /// @param[in] rootGuid
    ///     Scene's root version GUID on the server
    /// @param[in] sceneName
    ///     Scene name on the server
    /// @param[in] data
    ///     User data passed back to the callback
    typedef void (*FinishCallbackT)(
        const bool  success,
        const char  *errorMsg,
        const GuidT sceneGuid,
        const GuidT rootGuid,
        const char  *sceneName,
        void        *data);

    /// Uploads the current project to the server.
    ///
    /// This will create an internal copy of the current project's scene graph, so there's
    /// no need to keep it untouched until the upload has finished. However, should the settings
    /// graph still be valid by the time the upload is complete, it will be updated adding
    /// the server's versioning information to it.
    ///
    /// The project name on the server will be the name of the root node graph of the project.
    ///
    /// This function is asynchronous, so in order to retrieve any results
    /// you should make use of the provided callbacks.
    ///
    /// Has no effect if no user is currently logged in.
    ///
    /// @param[in] rootGuid
    ///     Scene's root version GUID on the server (this will be ignored if the project 
    ///     settings graph already contains versioning information)
    /// @param[in] onUpdate
    ///     Upload progress update callback. It will receive the name of the asset 
    ///     that is being uploaded plus the total upload progress in percentage. If the
    ///     callback returns FALSE the whole upload will be canceled.
    /// @param[in] onFinish
    ///     Upon the upload has finished (or failed) this will be called, 
    ///     providing whether the upload has been successful, in which case will 
    ///     provide the guid and name of the newly uploaded project.
    /// @param[in] callbackData
    ///     Optional data passed by the caller that is passed back to the callback functions.
    static void uploadCurrentProject(
        const GuidT     rootGuid      = 0,
        UpdateCallbackT onUpdate      = 0,
        FinishCallbackT onFinish      = 0,
        void            *callbackData = 0);

    /// Uploads a root node graph together with the current project settings to the server.
    ///
    /// This will create an internal copy of the specified root node grap, so there's
    /// no need to keep it untouched until the upload has finished. However, should the settings
    /// graph still be valid by the time the upload is complete, it will be updated adding
    /// the server's versioning information to it.
    ///
    /// This function is asynchronous, so in order to retrieve any results
    /// you should make use of the provided callbacks.
    ///
    /// Has no effect if no user is currently logged in.
    ///
    /// @param[in]  rootNodeGraph
    ///     The root node graph to upload. The name of the root node graph will be used as project
    ///     name on the server.
    /// @param[in]  rootGuid
    ///     Scene's root version GUID on the server (this will be ignored if the project settings
    ///     graph already contains versioning information)
    /// @param[in]  onUpdate
    ///     Upload progress update callback. It will receive the name of the asset 
    ///     that is being uploaded plus the total upload progress in percentage. If the
    ///     callback returns FALSE the whole upload will be canceled.
    /// @param[in]  onFinish
    ///     Upon the upload has finished (or failed) this will be called, 
    ///     providing whether the upload has been successful, in which case will 
    ///     provide the guid and name of the newly uploaded project.
    /// @param[in]  callbackData
    ///     Optional data passed by the caller that is passed back to the callback functions.
    static void uploadRootNodeGraph(
        const ApiRootNodeGraph &rootNodeGraph,
        const GuidT            rootGuid      = 0,
        UpdateCallbackT        onUpdate      = 0,
        FinishCallbackT        onFinish      = 0,
        void                   *callbackData = 0);

    /// Opens a Web UI for creating a new render task.
    ///
    /// Has no effect if no user is currently logged in.
    ///
    /// @param[in] sceneGuid
    ///     GUID of the scene to be rendered
    /// @return
    ///     TRUE if the UI could be open
    static bool newRenderTask(
        const GuidT sceneGuid);
};



} // namespace Octane

#endif // #ifndef OCTANE_DEMO_VERSION

#endif // #ifndef _API_RENDER_CLOUD_MANAGER_H_
