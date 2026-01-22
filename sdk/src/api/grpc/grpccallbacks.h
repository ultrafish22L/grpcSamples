// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#include <grpcpp/grpcpp.h>
#include "module/gui/apicheckbox.h"
#include "module/gui/apicolorswatch.h"
#include "module/gui/apicombobox.h"
#include "module/gui/apigridlayout.h"
#include "module/gui/apimouselistener.h" 
#include "module/gui/apinumericbox.h"
#include "module/gui/apitextbutton.h"
#include "module/gui/apitexteditor.h"
#include "module/gui/apiwindow.h"
#include "module/apimodulenodegraph.h"
#include "module/apiselectionmanager.h"
#include "apichangemanager.h"
#include "apiprojectmanager.h"
#include "apiocioconfig.h"
#include "apilogmanager.h"
#include "apiarray.h"
#include "apirender.h"
#include "apilocaldb.h"
#include <octanenet.h>
#include "protoc/callback.grpc.pb.h"
#include <future>
#include <queue>
#include <utility> // for std::pair
#include <unordered_map>

//#include "moduleserver.h"

namespace Octane
{
    class ApiNode;
};


struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine hashes
    }
};

class ModuleServer;

class GRPCCallbackMgr
{
public:
    GRPCCallbackMgr();

    virtual ~GRPCCallbackMgr();

    struct CallbackPool
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> availableIds;
        std::set<int> usedIds;
        int maxSize = 40; // Maximum IDs per method
    };

    void setModuleServer(ModuleServer * moduleServer)
    {
        mModuleServer = moduleServer;
    }

    static GRPCCallbackMgr& getInstance()
    {
        static GRPCCallbackMgr instance;
        return instance;
    }

    int getNextCallbackId(
        const std::string & methodName,
        const std::string & moduleId);

    void releaseCallbackId(
        const std::string & methodName,
        int callbackId);

    void releaseCallbackIdsByModule(
        const std::string & moduleId);

    std::string getModuleIdFromCallbackId(
        const std::string & methodName,
        int                 callbackId);

    std::unique_ptr< octaneapi::CallbackHandler::Stub >& getStub(
        const std::string & uniqueId);

    bool performBlockingOperation(const std::string & uniqueModuleId);

    Octane::ApiNode * LoadRenderStateProject(
        int            callbackid,
        const char *   customProjectFileName,
        float          customProjectTime,
        unsigned int   customVersion,
        const void *   customData,
        unsigned int   customDataSize,
        void *         privateCallbackData,
        grpc::Status & status);

    void OnDaemonUpdate(
        int                                                    callbackid,
        const Octane::ApiArray<const Octane::NetDaemonInfo*> & daemonInfoArray,
        void *                                                 user,
        grpc::Status &                                         status);

    void OnStatusUpdate(
        int                             callbackid,
        const Octane::NetRenderStatus & netstatus,
        void *                          userData,
        grpc::Status &                  status);

    void OnTriggerFunc(
        int            callbackid,
        void *         param0,
        grpc::Status & status);

    void OnEvaluateFunc(
        int              callbackid,
        void *           param0,
        grpc::Status &   status);

    void CleanupFunc(
        int            callbackid,
        void *         param0,
        grpc::Status & status);

    void DestroyFunc(
        int              callbackid,
        void *           param0,
        grpc::Status &   status);

    void ColorChanged(
        int                      callbackid,
        Octane::ApiColorSwatch & param0,
        void *                   param1,
        grpc::Status &           status);

    void * CreateFunc(
        int                          callbackid,
        Octane::ApiModuleNodeGraph * moduleNodeGraph,
        grpc::Status &               status);

    void * InitFunc(
        int                     callbackid,
        Octane::ApiGridLayout * apiGridLayout,
        grpc::Status &          status);

    void ApiChangeManagerChangeObserver(
        int                                         callbackid,
        const Octane::ApiChangeManager::ChangeEvent & param0,
        void *                                      param1,
        grpc::Status &                              status);

    void ApiChangeManagerChangeTimeObserver(
        int                                         callbackid,
        const Octane::ApiChangeManager::TimeEvent & param0,
        void *                                      param,
        grpc::Status &                              status);

    void ApiProjectManagerProjectManagerObserver(
        int             callbackid,
        void *          param,
        grpc::Status &  status);

    void ApiSelectionManagerSelectionManagerObserver(
        int             callbackid,
        void *          param,
        grpc::Status &  status);

    bool CommandModuleRunFunc(
        int callbackId,
        void *                          userData,
        grpc::Status &                  status);

    void ObserverCallback(
        int callbackId,
        void *                          userData,
        Octane::ApiLocalDB::UpdateType  type,
        const char *                    path,
        grpc::Status &                  status);

    void DbViewLoadedCallback(
        int callbackId,
        void *               userData,
        Octane::ItemDbOrigin origin,
        grpc::Status &       status);

    void FinishCallback(
        int callbackId,
        bool            success,
        const char *    errorMsg,
        const char *    sceneGuid,
        const char *    rootGuid,
        const char *    sceneName,
        void *          data,
        grpc::Status &  status);

    void OnTileBlendedCallback(
        int callbackId,
        void *          userData,
        grpc::Status &  status);

    void OnNewStatisticsCallback(
        int callbackId,
        void *          userData,
        grpc::Status &  status);

    void OnNewImageCallback(
        int callbackId,
        const Octane::ApiArray<Octane::ApiRenderImage> & renderImages,
        void *                                           userData,
        grpc::Status &                                   status);

    void OnOcioErrorCallback(
        int callbackId,
        const Octane::ApiArray<const char*> & messages,
        bool                                  hasError,
        void *                                userData,
        grpc::Status &                        status);

    void OnRenderFailureCallback(
        int callbackId,
        void *          userData,
        grpc::Status &  status);

    unsigned long long NextChunkCallback(
        int callbackId,
        void *          userData,
        unsigned char*& dataChunk,
        grpc::Status &  status);

    void CheckedCallback(
        int callbackId,
        Octane::ApiCheckBox & button,
        void *                userData,
        grpc::Status &        status);

    void ComboBoxChangedCallback(
        int callbackId,
        Octane::ApiComboBox & comboBox,
        void *                userData,
        grpc::Status &        status);

    void ApiLogCallbackProc(
        int callbackId,
        Octane::ApiLogManager::LogMessageType type,
        const char *                          message,
        grpc::Status &                        status);

    void OnMainWindowCloseCallback(
        int callbackId,
        void *          privateData,
        grpc::Status &  status);

    void MouseEventCallback(
        int callbackId,
        Octane::ApiMouseEventType            type,
        const Octane::ApiMouseEvent &        event,
        const Octane::ApiMouseWheelDetails & wheelDetails,
        void *                               privateData,
        grpc::Status &                       status);

    void DbViewClosingCallback(
        int callbackId,
        void *          userData,
        grpc::Status &  status);

    void NumericBoxChangedCallback(
        int callbackId,
        Octane::ApiNumericBox & numericBox,
        void *                  userData,
        grpc::Status &          status);

    void Callback(
        int callbackId,
        bool                    loading,
        Octane::ApiOcioConfig * config,
        void *                  privateData,
        grpc::Status &          status);

    void Callback(
        int callbackId,
        Octane::ApiOcioConfig * config,
        bool                    contextUsableForConversion,
        void *                  privateData,
        grpc::Status &          status);

    const char* ApiProjectManagerAssetMissingCallback(
        int callbackId,
        const char *    fileName,
        void *          userData,
        grpc::Status &  status);

    bool UpdateCallback(
        int callbackId,
        float           percent,
        void *          userData,
        grpc::Status &  status);

    bool AsyncUpdateCallback(
        int callbackId,
        unsigned long long changeLevel,
        void *             userData,
        grpc::Status &     status);

    const char* AssetMissingCallback(
        int callbackId,
        const char *    fileName,
        void *          userData,
        grpc::Status &  status);

    int NumRowsCallback(
        int callbackId,
        void *          userData,
        grpc::Status &  status);

    const char* ContentCallback(
        int callbackId,
        int             row,
        int             column,
        void *          userData,
        grpc::Status &  status);

    void ButtonClickedCallback(
        int callbackId,
        Octane::ApiTextButton & textButton,
        void *                  userData,
        grpc::Status &          status);

    void SelectionChangedCallback(
        int callbackId,
        int             lastRowSelected,
        void *          userData,
        grpc::Status &  status);

    void TextEditorChangedCallback(
        int callbackId,
        Octane::ApiTextEditor & textEdit,
        void *                  userData,
        grpc::Status &          status);

    void OnWindowCloseCallback(
        int callbackId,
        Octane::ApiWindow & textEdit,
        void *              userData,
        grpc::Status &      status);

    GRPCCallbackMgr(const GRPCCallbackMgr& ) = delete;

    GRPCCallbackMgr& operator=(const GRPCCallbackMgr& ) = delete;

protected:

    ModuleServer * mModuleServer = nullptr;
    struct StubInfo
    {
        std::shared_ptr<grpc::Channel> channel;
        std::unique_ptr<octaneapi::CallbackHandler::Stub> stub;
    };

    mutable std::mutex mMutex;
    std::unordered_map<std::string, StubInfo> mStubMap;
    std::unique_ptr<grpc::CompletionQueue> mCompletionQueue;
    std::unordered_map<std::string, CallbackPool> mCallbackPools;
    // maps callback ID to moduleI
    std::unordered_map<std::pair<std::string, int>, std::string, pair_hash> mCallbackIdToModuleId;

};

#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)