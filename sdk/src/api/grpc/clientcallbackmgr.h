// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
#include <unordered_map>
#include <map>
#include <functional>
#include <mutex>
#include "grpcchangeevents.h"
#include "apilogmanager.h"
#include "apimouselistener.h"
#include "apiarray.h"
#include "apicolorswatch.h"
#include "octaneenums.h"
#include "apilocaldb.h"
#include "apirendercloudmanager.h"
#include "apirender.h"
#include "apinetrendermanager.h"
#include "apinodesystem.h"
#include "apitable.h"
#include "apimainwindow.h"


// Forward-declare any custom types if needed, e.g. Octane::ApiRenderImage
class ApiCheckBoxProxy;
class ApiComboBoxProxy;
class ApiMouseEventProxy;
class ApiGridLayoutProxy;
class ApiNodeProxy;
class ApiModuleNodeGraphProxy;
class ApiNumericBoxProxy;
class ApiComboBoxProxy;
class ApiColorSwatchProxy;
class ApiOcioConfigProxy;
class ApiTextButtonProxy;
class ApiTextEditorProxy;
class ApiWindowProxy;
struct GRPCApiMouseEventData;
struct GRPCProjectManagerChangeEvent;
struct GRPCProjectManagerTimeChangeEvent;

typedef const char* GuidT;

typedef void (*OnStatusUpdateT)(
    const Octane::NetRenderStatus &status,
    void                  *userData);

typedef void(*OnDaemonUpdateT)(
    const ApiArray<const Octane::NetDaemonInfo*> &daemonInfoArray,
    void                                 *user);

typedef void (*CleanupFuncT)(
    void *const userData);

typedef void* (*GRPCInitFuncT)(
    ApiGridLayoutProxy* const gridLayout);

typedef void* (*GRPCCreateFuncT)(
    ApiModuleNodeGraphProxy* const graph);

typedef void (*DestroyFuncT)(
    void *const userData);

typedef void (*OnEvaluateFuncT)(
    void *const userData);

typedef void(*OnTriggerFuncT)(
    void *const userData);

typedef ApiNodeProxy* (*GRPCLoadRenderStateProjectT)(
    const char *const customProjectFileName,
    const float       customProjectTime,
    const uint32_t    customVersion,
    const void *const customData,
    const uint32_t    customDataSize,
    void       *const privateCallbackData);

// GRPCComboBoxChangedCallback
typedef void (*GRPCColorChangedT)(
    ApiColorSwatchProxy & colorSwatch,
    void * userData);

typedef bool (*CommandModuleRunFuncT)(
    void *const workpaneUserData);

typedef void (*ObserverCallbackT)(
    void * opaqueData,
    Octane::ApiLocalDB::UpdateType type,
    const char * path);

typedef void (*DbViewLoadedCallbackT)(
    void * userData,
    Octane::ItemDbOrigin origin);
 
// GRPCCheckedCallback
typedef void (*GRPCCheckedCallbackT)(
    ApiCheckBoxProxy& /*button*/,
    void* /*userData*/);

// GRPCComboBoxChangedCallback
typedef void (*GRPCComboBoxChangedCallbackT)(
    ApiComboBoxProxy &  comboBox ,
    void *              userData);

// ApiLogCallbackProc
typedef void (*ApiLogCallbackProc)(
    Octane::ApiLogManager::LogMessageType /*type*/,
    const char* /*message*/);

// OnMainWindowCloseCallback
typedef void (*OnMainWindowCloseCallbackT)(
    void* /*privateData*/);

// GRPCMouseEventCallback
typedef void (*GRPCMouseEventCallbackT)(
    const Octane::ApiMouseEventType /*type*/,
    const GRPCApiMouseEventData& /*event*/,
    const Octane::ApiMouseWheelDetails& /*wheelDetails*/,
    void* /*privateData*/);

// DbViewClosingCallback
typedef void (*DbViewClosingCallbackT)(
    void* /*userData*/);

// GRPCNumericBoxChangedCallback
typedef  void (*GRPCNumericBoxChangedCallbackT)(
    ApiNumericBoxProxy & /*numericBox*/,
    void *               /*userData*/);

// GRPCCallback1
typedef void (*GRPCCallback1T)(bool /*loading*/,
    ApiOcioConfigProxy* /*config*/,
    void * /*privateData*/);

// GRPCCallback2
typedef void (*GRPCCallback2T)(ApiOcioConfigProxy* /*config*/,
    bool /*contextUsableForConversion*/,
    void * /*privateData*/);

// GRPCButtonClickedCallback
typedef void (*GRPCButtonClickedCallbackT)(
    ApiTextButtonProxy & /*textButton*/,
    void *               /*userData*/);

// GRPCTextEditorChangedCallback
typedef void (*GRPCTextEditorChangedCallbackT)(
    ApiTextEditorProxy & /*textEdit*/,
    void *               /*userData*/);

// GRPCOnWindowCloseCallback
typedef void (*GRPCOnWindowCloseCallbackT)(
     ApiWindowProxy & textEdit,
     void *           userData);

typedef void (*GRPCChangeManagerChangeT)(
    const GRPCChangeManagerChangeEvent & changeEvent,
    void *                               userData);

typedef void (*GRPCChangeManagerTimeChangeT)(
    const GRPCChangeManagerTimeChangeEvent & changeEvent,
    void *                                   userData);

typedef void (*OnApiProjectManagerChangeT)(
    void *              userData);

typedef void (*OnSelectionManagerChangeT)(
    void *              userData);


class CallbackStorage
{
public:
    // Register methods

    static void registerOnStatusUpdate(int id, OnStatusUpdateT callback);

    static void registerOnDaemonUpdate(int id, OnDaemonUpdateT callback);

    static void registerCleanupFunc(int id, CleanupFuncT callback);

    static void registerGRPCInitFunc(int id, GRPCInitFuncT callback);

    static void registerGRPCCreateFunc(int id, GRPCCreateFuncT  callback);

    static void registerDestroyFunc(int id, DestroyFuncT callback);

    static void registerOnEvaluateFunc(int id, OnEvaluateFuncT callback);

    static void registerOnTriggerFunc(int id, OnTriggerFuncT callback);

    static void registerGRPCLoadRenderStateProject(int id, GRPCLoadRenderStateProjectT callback);

    static void registerGRPCChangeObserver(int id, GRPCChangeManagerChangeT callback);

    static void registerGRPCChangeTimeObserver(int id, GRPCChangeManagerTimeChangeT callback);

    static void registerGRPCProjectManagerObserver(int id, OnApiProjectManagerChangeT callback);
    
    static void registerGRPCSelectionManagerObserver(int id, OnSelectionManagerChangeT callback);

    static void registerColorChanged(int id, GRPCColorChangedT callback);

    static void registerCommandModuleRunFunc(int id, CommandModuleRunFuncT callback);

    static void registerObserverCallback(int id, ObserverCallbackT callback);

    static void registerDbViewLoadedCallback(int id, DbViewLoadedCallbackT callback);

    static void registerFinishCallback(int id, Octane::ApiRenderCloudManager::FinishCallbackT callback);

    static void registerOnTileBlendedCallback(int id, Octane::ApiRenderEngine::OnTileBlendedCallbackT callback);

    static void registerOnNewStatisticsCallback(int id, Octane::ApiRenderEngine::OnNewStatisticsCallbackT callback);

    static void registerOnNewImageCallback(int id, Octane::ApiRenderEngine::OnNewImageCallbackT callback);

    static void registerOnOcioErrorCallback(int id, Octane::ApiRenderEngine::OnOcioErrorCallbackT callback);

    static void registerOnRenderFailureCallback(int id, Octane::ApiRenderEngine::OnRenderFailureCallbackT callback);

    static void registerNextChunkCallback(int id, Octane::ApiRootNodeGraph::NextChunkCallbackT callback);

    static void registerGRPCCheckedCallback(int id, GRPCCheckedCallbackT callback);

    static void registerGRPCComboBoxChangedCallback(int id, GRPCComboBoxChangedCallbackT callback);

    static void registerApiLogCallbackProc(int id, ApiLogCallbackProc callback);

    static void registerOnMainWindowCloseCallback(int id, Octane::ApiMainWindow::OnMainWindowCloseCallbackT callback);

    static void registerGRPCMouseEventCallback(int id, GRPCMouseEventCallbackT callback);

    static void registerDbViewClosingCallback(int id, DbViewClosingCallbackT callback);

    static void registerGRPCNumericBoxChangedCallback(int id, GRPCNumericBoxChangedCallbackT cb);

    static void registerGRPCCallback1(int id, GRPCCallback1T callback);

    static void registerGRPCCallback2(int id, GRPCCallback2T callback);

    static void registerApiProjectManager_AssetMissingCallback(int id, Octane::AssetMissingCallbackT cb);

    static void registerUpdateCallback(int id, Octane::ApiRenderCloudManager::UpdateCallbackT callback);

    static void registerAsyncUpdateCallback(int id, Octane::ApiRenderEngine::AsyncUpdateCallbackT callback);

    static void registerAssetMissingCallback(int id, Octane::AssetMissingCallbackT callback);

    static void registerNumRowsCallback(int id, Octane::ApiTable::NumRowsCallbackT callback);

    static void registerContentCallback(int id, Octane::ApiTable::ContentCallbackT callback);

    static void registerGRPCButtonClickedCallback(int id, GRPCButtonClickedCallbackT callback);

    static void registerSelectionChangedCallback(int id, Octane::ApiTable::SelectionChangedCallbackT callback);

    static void registerGRPCTextEditorChangedCallback(int id, GRPCTextEditorChangedCallbackT cb);

    static void registerGRPCOnWindowCloseCallback(int id, GRPCOnWindowCloseCallbackT callback);

    static int unregisterOnDaemonUpdate(OnDaemonUpdateT callback);

    static int unregisterOnStatusUpdate(OnStatusUpdateT callback);

    static int unregisterCleanupFunc( CleanupFuncT callback);

    static int unregisterGRPCInitFunc( GRPCInitFuncT callback);

    static int unregisterGRPCCreateFunc( GRPCCreateFuncT  callback);

    static int unregisterDestroyFunc( DestroyFuncT callback);

    static int unregisterOnEvaluateFunc( OnEvaluateFuncT callback);

    static int unregisterOnTriggerFunc( OnTriggerFuncT callback);

    static int unregisterGRPCLoadRenderStateProject( GRPCLoadRenderStateProjectT callback);

    static int unregisterGRPCChangeObserver( GRPCChangeManagerChangeT callback);

    static int unregisterGRPCChangeTimeObserver( GRPCChangeManagerTimeChangeT callback);

    static int unregisterGRPCProjectManagerObserver( OnApiProjectManagerChangeT callback);

    static int unregisterGRPCSelectionManagerObserver( OnSelectionManagerChangeT callback);

    static int unregisterColorChanged( GRPCColorChangedT callback);

    static int unregisterCommandModuleRunFunc( CommandModuleRunFuncT callback);

    static int unregisterObserverCallback( ObserverCallbackT callback);

    static int unregisterDbViewLoadedCallback( DbViewLoadedCallbackT callback);

    static int unregisterFinishCallback( Octane::ApiRenderCloudManager::FinishCallbackT callback);

    static int unregisterOnTileBlendedCallback( Octane::ApiRenderEngine::OnTileBlendedCallbackT callback);

    static int unregisterOnNewStatisticsCallback( Octane::ApiRenderEngine::OnNewStatisticsCallbackT callback);

    static int unregisterOnNewImageCallback( Octane::ApiRenderEngine::OnNewImageCallbackT callback);

    static int unregisterOnOcioErrorCallback( Octane::ApiRenderEngine::OnOcioErrorCallbackT callback);

    static int unregisterOnRenderFailureCallback( Octane::ApiRenderEngine::OnRenderFailureCallbackT callback);

    static int unregisterNextChunkCallback( Octane::ApiRootNodeGraph::NextChunkCallbackT callback);

    static int unregisterGRPCCheckedCallback( GRPCCheckedCallbackT callback);

    static int unregisterGRPCComboBoxChangedCallback( GRPCComboBoxChangedCallbackT callback);

    static int unregisterApiLogCallbackProc( ApiLogCallbackProc callback);

    static int unregisterOnMainWindowCloseCallback( Octane::ApiMainWindow::OnMainWindowCloseCallbackT callback);

    static int unregisterGRPCMouseEventCallback( GRPCMouseEventCallbackT callback);

    static int unregisterDbViewClosingCallback( DbViewClosingCallbackT callback);

    static int unregisterGRPCNumericBoxChangedCallback( GRPCNumericBoxChangedCallbackT cb);

    static int unregisterGRPCCallback1( GRPCCallback1T callback);

    static int unregisterGRPCCallback2( GRPCCallback2T callback);

    static int unregisterApiProjectManager_AssetMissingCallback( Octane::AssetMissingCallbackT cb);

    static int unregisterUpdateCallback( Octane::ApiRenderCloudManager::UpdateCallbackT callback);

    static int unregisterAsyncUpdateCallback( Octane::ApiRenderEngine::AsyncUpdateCallbackT callback);

    static int unregisterAssetMissingCallback( Octane::AssetMissingCallbackT callback);

    static int unregisterNumRowsCallback( Octane::ApiTable::NumRowsCallbackT callback);

    static int unregisterContentCallback( Octane::ApiTable::ContentCallbackT callback);

    static int unregisterGRPCButtonClickedCallback( GRPCButtonClickedCallbackT callback);

    static int unregisterSelectionChangedCallback( Octane::ApiTable::SelectionChangedCallbackT callback);

    static int unregisterGRPCTextEditorChangedCallback( GRPCTextEditorChangedCallbackT cb);

    static int unregisterGRPCOnWindowCloseCallback( GRPCOnWindowCloseCallbackT callback);

    static void invokeOnDaemonUpdate(
        int                                    id,
        const ApiArray<const Octane::NetDaemonInfo*> & daemonInfoArray,
        void *                                 serData);

    static void invokeOnStatusUpdate(
        int                     id,
        const Octane::NetRenderStatus & status,
        void *                  userData);

    static void invokeCleanupFunc(
        int                   id,
        void *                userData);

    static void * invokeGRPCInitFunc(
        int                          id,
        ApiGridLayoutProxy *  const  gridLayout);

    static void * invokeGRPCCreateFunc(
        int                               id,
        ApiModuleNodeGraphProxy *  const  moduleNodeGraph);

    static void  invokeDestroyFunc(
        int                   id,
        void * const          userData);

    static void invokeOnEvaluateFunc(
        int                   id,
        void *const           userData);

    static void invokeOnTriggerFunc(
        int                   id,
        void *const           userData);

    static ApiNodeProxy * invokeGRPCLoadRenderStateProject(
        int                   id,
        const char *const     customProjectFileName,
        const float           customProjectTime,
        const uint32_t        customVersion,
        const void *const     customData,
        const uint32_t        customDataSize,
        void       *const     privateCallbackData);

    static void invokeGRPCChangeObserver(
        int                                  id,
        const GRPCChangeManagerChangeEvent & changeEvent,
        void *                               userData);

    static void invokeGRPCChangeTimeObserver(
        int                                      id,
        const GRPCChangeManagerTimeChangeEvent & changeEvent,
        void *                                   userData);

    static void invokeGRPCProjectManagerObserver(
        int                 id,
        void *              userData);//

    static void invokeGRPCSelectionManagerObserver(
        int                 id,
        void *              userData);//

    // Invocation methods
    static void invokeColorChanged(
        int                   id,
        ApiColorSwatchProxy & colorSwatch,
        void *                userData);

    static bool invokeCommandModuleRunFunc(
        int          id,
        void * const workpaneUserData);

    static void invokeObserverCallback(
        int                            id,
        void *                         opaqueData,
        Octane::ApiLocalDB::UpdateType type,
        const char *                   path);

    static void invokeDbViewLoadedCallback(int id, void * userData, Octane::ItemDbOrigin origin);

    static void invokeFinishCallback(
        int           id,
        const bool    success,
        const char *  errorMsg,
        const GuidT   sceneGuid,
        const GuidT   rootGuid,
        const char  * sceneName,
        void        * data);//

    static void invokeOnTileBlendedCallback(  int id, void * userData);//

    static void invokeOnNewStatisticsCallback( int id, void * userData);//

    static void invokeOnNewImageCallback( 
        int                              id,
        const ApiArray<ApiRenderImage> & renderImages,
        void *                           userData);//

    static void invokeOnOcioErrorCallback(         
        int                              id,
        const ApiArray<const char *> &   messages,
        bool                             hasError,
        void *                           userData);//

    static void invokeOnRenderFailureCallback(
        int                              id,
        void *                           userData);//

    static size_t invokeNextChunkCallback(
        int                 id,
        void *              userData, 
        unsigned char* &    dataChunk);//

    static void invokeGRPCCheckedCallback(
        int                id,
        ApiCheckBoxProxy & button,
        void *             userData);//

    static void invokeGRPCComboBoxChangedCallback(
        int                 id,
        ApiComboBoxProxy  & comboBox,
        void *              userData);

    static void invokeApiLogCallback(
        int                                   id,
        Octane::ApiLogManager::LogMessageType type,
        const char *                          message);

    static void invokeOnMainWindowCloseCallback(
        int    id,
        void * privateData);

    static void invokeGRPCMouseEventCallback(
        int                                  id,
        Octane::ApiMouseEventType            evType,
        const GRPCApiMouseEventData &        event,
        const Octane::ApiMouseWheelDetails & wheelDetails,
        void *                               privateData);

    static void invokeDbViewClosingCallback(
        int    id,
        void * userData);

    static void invokeGRPCNumericBoxChangedCallback(
        int                  id,
        ApiNumericBoxProxy & numericBox,
        void *               userData);

    static void invokeGRPCCallback1(
        int                  id,
        bool                 loading,
        ApiOcioConfigProxy * config,
        void *               privateData);

    static void invokeGRPCCallback2(
        int                  id,
        ApiOcioConfigProxy * config,
        bool                 contextUsableForConversion,
        void *               privateData);

    static const char *  invokeApiProjectManager_AssetMissingCallback(
        int          id,
        const char * fileName,
        void       * userData);

    static bool invokeUpdateCallback(
        int          id,
        const float percent,
        void        *data);

    static void invokeAsyncUpdateCallback(
        int           id,
        const CLevelT changeLevel,
        void *        userData);//

    static const char *  invokeAssetMissingCallback(
        int           id,
        const char *  fileName,
        void       *  userData);//

    static int invokeNumRowsCallback(
        int    id,
        void * privateData);//

    static const char*  invokeContentCallback(
        int       id,
        const int row,
        const int column,
        void *    privateData);//

    static void invokeGRPCButtonClickedCallback(
        int                  id,
        ApiTextButtonProxy & textButton,
        void *               userData );

    static void invokeSelectionChangedCallback( 
        int       id,
        const int lastRowSelected,
        void *    privateData);//

    static void invokeGRPCTextEditorChangedCallback(
        int                  id,
        ApiTextEditorProxy & textEdit,
        void *               userData);

    static void invokeGRPCOnWindowCloseCallback(
        int              id,
        ApiWindowProxy & window,
        void *           userData);
private:
    static std::mutex sMutex;
     
    // Private vectors for storing raw function pointers
    static std::map<int, OnStatusUpdateT> sOnStatusUpdateCallbacks;
    static std::map<int, OnDaemonUpdateT> sOnDaemonUpdateCallbacks;
    static std::map<int, CleanupFuncT> sCleanupFuncCallbacks;
    static std::map<int, GRPCInitFuncT> sInitFuncCallbacks;
    static std::map<int, GRPCCreateFuncT> sCreateFuncCallbacks;
    static std::map<int, DestroyFuncT> sDestroyFuncCallbacks;
    static std::map<int, OnEvaluateFuncT> sEvaluateFuncCallbacks;
    static std::map<int, OnTriggerFuncT> sTriggerFuncCallbacks;
    static std::map<int, GRPCLoadRenderStateProjectT> sLoadRenderStateCallbacks;
    static std::map<int, GRPCChangeManagerChangeT> sOnChangeManagerChangeCallbacks;
    static std::map<int, GRPCChangeManagerTimeChangeT> sChangeManagerTimeChangeCallbacks;
    static std::map<int, OnApiProjectManagerChangeT> sApiProjectManagerChangeCallbacks;
    static std::map<int, OnSelectionManagerChangeT> sSelectionManagerChangeCallbacks;
    static std::map<int, GRPCColorChangedT> sColorChangedCallbacks;
    static std::map<int, CommandModuleRunFuncT> sCommandModuleRunFuncCallbacks;
    static std::map<int, ObserverCallbackT> sObserverCallbacks;
    static std::map<int, DbViewLoadedCallbackT> sDbViewLoadedCallbacks;
    static std::map<int, Octane::ApiRenderCloudManager::FinishCallbackT> sFinishCallbacks;
    static std::map<int, Octane::ApiRenderEngine::OnTileBlendedCallbackT> sOnTileBlendedCallbacks;
    static std::map<int, Octane::ApiRenderEngine::OnNewStatisticsCallbackT> sOnNewStatisticsCallbacks;
    static std::map<int, Octane::ApiRenderEngine::OnNewImageCallbackT> sOnNewImageCallbacks;
    static std::map<int, Octane::ApiRenderEngine::OnOcioErrorCallbackT> sOnOcioErrorCallbacks;
    static std::map<int, Octane::ApiRenderEngine::OnRenderFailureCallbackT> sOnRenderFailureCallbacks;
    static std::map<int, Octane::ApiRootNodeGraph::NextChunkCallbackT> sNextChunkCallbacks;
    static std::map<int, GRPCCheckedCallbackT> sGrpcCheckedCallbacks;
    static std::map<int, GRPCComboBoxChangedCallbackT> sGrpcComboBoxChangedCallbacks;
    static std::map<int, ApiLogCallbackProc> sApiLogCallbackProcs;
    static std::map<int, Octane::ApiMainWindow::OnMainWindowCloseCallbackT> sOnMainWindowCloseCallbacks;
    static std::map<int, GRPCMouseEventCallbackT> sGrpcMouseEventCallbacks;
    static std::map<int, DbViewClosingCallbackT> sDbViewClosingCallbacks;
    static std::map<int, GRPCNumericBoxChangedCallbackT> sGrpcNumericBoxChangedCallbacks;
    static std::map<int, GRPCCallback1T> sGrpcCallback1s;
    static std::map<int, GRPCCallback2T> sGrpcCallback2s;
    static std::map<int, Octane::AssetMissingCallbackT> sApiProjectManagerAssetMissingCallbacks;
    static std::map<int, Octane::ApiRenderCloudManager::UpdateCallbackT> sUpdateCallbacks;
    static std::map<int, Octane::ApiRenderEngine::AsyncUpdateCallbackT> sAsyncUpdateCallbacks;
    static std::map<int, Octane::AssetMissingCallbackT> sAssetMissingCallbacks;
    static std::map<int, Octane::ApiTable::NumRowsCallbackT> sNumRowsCallbacks;
    static std::map<int, Octane::ApiTable::ContentCallbackT> sContentCallbacks;
    static std::map<int, GRPCButtonClickedCallbackT> sGrpcButtonClickedCallbacks;
    static std::map<int, Octane::ApiTable::SelectionChangedCallbackT> sSelectionChangedCallbacks;
    static std::map<int, GRPCTextEditorChangedCallbackT> sGrpcTextEditorChangedCallbacks;
    static std::map<int, GRPCOnWindowCloseCallbackT> sGrpcOnWindowCloseCallbacks;


    // Helper for storing callbacks in a thread-safe way
    template<typename T>
    static void storeCallback(std::map<int, T> & container, int id, T cb)
    {
        std::lock_guard<std::mutex> lock(sMutex);
        container[id] = cb;
    }


    // Helper to safely fetch an entry before calling it
    template <typename T>
    static T fetchFromMap(const std::map<int, T>& m, int id)
    {
        std::lock_guard<std::mutex> lock(CallbackStorage::sMutex);
        auto it = m.find(id);
        if (it != m.end())
        {
            return it->second;
        }
        return nullptr;
    }

    template <typename T>
    static int getCallbackId(std::map<int, T>& container, T callback)
    {
        std::lock_guard<std::mutex> lock(CallbackStorage::sMutex);

        for (auto it = container.begin(); it != container.end(); ++it)
        {
            if (it->second == callback)
            {
                int foundId = it->first;
                return foundId;
            }
        }
        return -1;
    }

    template <typename T>
    static int removeCallback(std::map<int, T>& container, T callback)
    {
        std::lock_guard<std::mutex> lock(CallbackStorage::sMutex);

        for (auto it = container.begin(); it != container.end(); ++it)
        {
            if (it->second == callback)
            {
                int foundId = it->first;
                container.erase(it);
                return foundId;
            }
        }
        return -1;
    }
};

#endif //#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)