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
}


#include "apirendercloudmanager.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiRenderCloudManager
class ApiRenderCloudManagerProxy : public GRPCBase
{
public:
    /// Populates the provided struct with the information for the current user's
    /// subscription.
    ///
    /// @note This requires a valid SSO session and will perform a HTTP request
    ///     every time which will block the call until it returns.
    ///
    /// @param subscriptionInfo
    ///     The user's subscription info. Just meaningful if the method returns TRUE.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the subscription information could be fetch successfully, FALSE
    ///     otherwise, in which case an error wil also be displayed in the log.
    static bool userSubscriptionInfo(
            Octane::ApiRenderCloudManager::SubscriptionInfo &   subscriptionInfo
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void uploadCurrentProject(
            const Octane::ApiRenderCloudManager::GuidT rootGuid,
            Octane::ApiRenderCloudManager::UpdateCallbackT onUpdate,
            Octane::ApiRenderCloudManager::FinishCallbackT onFinish,
            void *                                    callbackData
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void uploadRootNodeGraph(
            const ApiRootNodeGraphProxy &             rootNodeGraph,
            const Octane::ApiRenderCloudManager::GuidT rootGuid,
            Octane::ApiRenderCloudManager::UpdateCallbackT onUpdate,
            Octane::ApiRenderCloudManager::FinishCallbackT onFinish,
            void *                                    callbackData
            );

    /// Opens a Web UI for creating a new render task.
    ///
    /// Has no effect if no user is currently logged in.
    ///
    /// @param[in] sceneGuid
    ///     GUID of the scene to be rendered
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the UI could be open
    static bool newRenderTask(
            const Octane::ApiRenderCloudManager::GuidT   sceneGuid
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
