// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#include "callback.grpc.pb.h"
#include "clientcallbackmgr.h"
#include <grpcpp/grpcpp.h>
#include "apimodule.h"
#include <mutex>

class MainComponent;

namespace OctaneGRPC
{
    class ApiImageProxy;
    class GRPCModuleBase;
    class GRPCMainInterface;
}

namespace OctaneGRPC
{
// Class that implements the callback interface used to receieve events/callvbacks/commands
// from Octane
class CallbackHandlerImpl : public octaneapi::CallbackHandler::Service
{
public:
    // Pointer to the main object that controls the GRPC server
    GRPCModuleBase * mMain = nullptr;

    // pointer to the Module implementation interface
    void setInterface(
        GRPCMainInterface * mainInterface);

    // Helper function that wraps ApiModuleGlobal::registerCommandModule. THis normally would be called from
    // within the Start method (see below)
    void registerModule(
        const Octane::ModuleIdT                                   moduleId,
        const char *                                              fullName,
        const char *                                              description,
        const char *                                              author,
        const Octane::VersionT                                    versionNumber,
        const Octane::ApiCommandModuleInfo::CommandModuleRunFuncT runFunction,
        const OctaneGRPC::ApiImageProxy &                         icon,
        const char *                                              shortcutGroupName = nullptr,
        const int                                                 shortcutKeyCode = -1,
        const int                                                 shortcutModifierKeyFlag = 0);

    // Called by Octane after we make a call to startBlockingOperation (see ApiControlService).
    // We can then call back to Octane with multiple calls while Octane displays a modal dialog
    // display that prevents user interference.
    grpc::Status PerformBlocking(
        grpc::ServerContext* context,
        const ::google::protobuf::Empty* request,
        octaneapi::CallbackAck* response) override;

    /// Called by Octane to see if the module is ready for loading
    grpc::Status IsReady(
        grpc::ServerContext* context,
        const octaneapi::IsReadyRequest* request,
        octaneapi::IsReadyResponse* response) override;

    /// Called by Octane when it loads the module
    grpc::Status Start(
        grpc::ServerContext* context,
        const octaneapi::StartRequest* request,
        octaneapi::StartResponse* response) override;

    /// Called by Octane when it unloads the module
    grpc::Status Stop(
        grpc::ServerContext* context,
        const octaneapi::StopRequest* request,
        octaneapi::StopResponse* response) override;

    // Not used for Module SDK. Originally added to recieve render updates when the GRPC API was
    // used in the context of the Plugin SDK
    grpc::Status Notify(
        grpc::ServerContext* context,
        const octaneapi::NotificationRequest* request,
        octaneapi::NotificationResponse* response) override;

    // Called when Octane's LoadRenderStateProject callback function is called
    grpc::Status LoadRenderStateProject(
        ::grpc::ServerContext* context,
        const ::octaneapi::LoadRenderStateProjectRequest* request,
        ::octaneapi::LoadRenderStateProjectResponse* response) override;

    // Called when Octane's OnDaemonUpdate callback function is called
    grpc::Status OnDaemonUpdate(
        ::grpc::ServerContext* context,
        const ::octaneapi::DaemonUpdateRequest* request,
        ::octaneapi::CallbackAck* response)  override;

    // Called when Octane's OnStatusUpdate callback function is called
    grpc::Status OnStatusUpdate(
        ::grpc::ServerContext* context,
        const ::octaneapi::StatusUpdateRequest* request,
        ::octaneapi::CallbackAck* response) override;

    // Called when Octane's TriggerFunc callback function is called
    grpc::Status TriggerFunc(
        grpc::ServerContext* context,
        const octaneapi::TriggerFuncRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's EvaluateFunc callback function is called
    grpc::Status EvaluateFunc(
        grpc::ServerContext* context,
        const octaneapi::EvaluateFuncRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's CleanupFunc callback function is called
    grpc::Status CleanupFunc(
        grpc::ServerContext* context,
        const octaneapi::CleanupFuncRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's DestroyFunc callback function is called
    grpc::Status DestroyFunc(
        grpc::ServerContext* context,
        const octaneapi::DestroyFuncRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's ColorChanged callback function is called
    grpc::Status ColorChanged(
        grpc::ServerContext* context,
        const octaneapi::ColorChangedRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's CreateFunc callback function is called
    grpc::Status CreateFunc(
        grpc::ServerContext* context,
        const octaneapi::CreateFuncRequest* request,
        octaneapi::CreateFuncResponse* response) override;

    // Called when Octane's LoadRenderStateProject callback function is called
    grpc::Status InitFunc(
        grpc::ServerContext* context,
        const octaneapi::InitFuncRequest* request,
        octaneapi::InitFuncResponse* response) override;

    // Called when Octane's ChangeManagerObserver callback function is called
    grpc::Status ChangeManagerObserver(
        grpc::ServerContext* context,
        const octaneapi::ChangeManagerObserverRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's ChangeManagerTimeObserver callback function is called
    grpc::Status ChangeManagerTimeObserver(
        grpc::ServerContext* context,
        const octaneapi::ChangeManagerTimeObserverRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's ProjectManagerObserver callback function is called
    grpc::Status ProjectManagerObserver(
        grpc::ServerContext* context,
        const octaneapi::ObserverRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's SelectionManagerObserver callback function is called
    grpc::Status SelectionManagerObserver(
        grpc::ServerContext* context,
        const octaneapi::ObserverRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's CommandModuleRunFunc callback function is called
    grpc::Status CommandModuleRunFunc(
        grpc::ServerContext* context,
        const octaneapi::CommandModuleRunFuncRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's ObserverCallback callback function is called
    grpc::Status ObserverCallback(
        grpc::ServerContext* context,
        const octaneapi::ObserverCallbackRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's DbViewLoaded callback function is called
    grpc::Status DbViewLoaded(
        grpc::ServerContext* context,
        const octaneapi::DbViewLoadedRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's Finish callback function is called
    grpc::Status Finish(
        grpc::ServerContext* context,
        const octaneapi::FinishRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's OnTileBlended callback function is called
    grpc::Status OnTileBlended(
        grpc::ServerContext* context,
        const octaneapi::BasicCallbackRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's OnNewStatistics callback function is called
    grpc::Status OnNewStatistics(
        grpc::ServerContext* context,
        const octaneapi::BasicCallbackRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's OnNewImage callback function is called
    grpc::Status OnNewImage(
        grpc::ServerContext* context,
        const octaneapi::OnNewImageRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's OnOcioError callback function is called
    grpc::Status OnOcioError(
        grpc::ServerContext* context,
        const octaneapi::OnOcioErrorRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's OnRenderFailure callback function is called
    grpc::Status OnRenderFailure(
        grpc::ServerContext* context,
        const octaneapi::BasicCallbackRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's NextChunk callback function is called
    grpc::Status NextChunk(
        grpc::ServerContext* context,
        const octaneapi::NextChunkRequest* request,
        octaneapi::NextChunkResponse* response) override;

    // Called when Octane's Checked callback function is called
    grpc::Status Checked(
        grpc::ServerContext* context,
        const octaneapi::CheckedRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's ComboBoxChanged callback function is called
    grpc::Status ComboBoxChanged(
        grpc::ServerContext* context,
        const octaneapi::ComboBoxChangedRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's ApiLog callback function is called
    grpc::Status ApiLog(
        grpc::ServerContext* context,
        const octaneapi::ApiLogRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's OnMainWindowClose callback function is called
    grpc::Status OnMainWindowClose(
        grpc::ServerContext* context,
        const octaneapi::BasicCallbackRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's MouseEvent callback function is called
    grpc::Status MouseEvent(
        grpc::ServerContext* context,
        const octaneapi::MouseEventRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's DbViewClosing callback function is called
    grpc::Status DbViewClosing(
        grpc::ServerContext* context,
        const octaneapi::BasicCallbackRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's NumericBoxChanged callback function is called
    grpc::Status NumericBoxChanged(
        grpc::ServerContext* context,
        const octaneapi::NumericBoxChangedRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's Callback1 callback function is called
    grpc::Status Callback1(
        grpc::ServerContext* context,
        const octaneapi::Callback1Request* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's Callback2 callback function is called
    grpc::Status Callback2(
        grpc::ServerContext* context,
        const octaneapi::Callback2Request* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's ApiProjectManager_AssetMissing callback function is called
    grpc::Status ApiProjectManager_AssetMissing(
        grpc::ServerContext* context,
        const octaneapi::AssetMissingRequest* request,
        octaneapi::AssetMissingResponse* response) override;

    // Called when Octane's NumRows callback function is called
    grpc::Status NumRows(
        grpc::ServerContext* context,
        const octaneapi::BasicCallbackRequest* request,
        octaneapi::NumRowsResponse* response) override;

    // Called when Octane's Content callback function is called
    grpc::Status Content(
        grpc::ServerContext* context,
        const octaneapi::ContentRequest* request,
        octaneapi::ContentResponse* response) override;

    // Called when Octane's ButtonClicked callback function is called
    grpc::Status ButtonClicked(
        grpc::ServerContext* context,
        const octaneapi::ButtonClickedRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's SelectionChanged callback function is called
    grpc::Status SelectionChanged(
        grpc::ServerContext* context,
        const octaneapi::SelectionChangedRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's TextEditorChanged callback function is called
    grpc::Status TextEditorChanged(
        grpc::ServerContext* context,
        const octaneapi::TextEditorChangedRequest* request,
        octaneapi::CallbackAck* response) override;

    // Called when Octane's OnWindowClose callback function is called
    grpc::Status OnWindowClose(
        grpc::ServerContext* context,
        const octaneapi::OnWindowCloseRequest* request,
        octaneapi::CallbackAck* response) override;

private:
    std::mutex mDataMutex;
    OctaneGRPC::GRPCMainInterface* mMainInterface = nullptr;
};

}// namespace OctaneGRPC