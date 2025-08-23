// Copyright (C) 2025 OTOY NZ Ltd.

#include "clientcallbackmgr.h"
#include "grpcsettings.h"
// Static member definitions
namespace OctaneGRPC
{

    std::mutex CallbackStorage::sMutex;

    std::map<int, OnStatusUpdateT> CallbackStorage::sOnStatusUpdateCallbacks;
    std::map<int, OnDaemonUpdateT> CallbackStorage::sOnDaemonUpdateCallbacks;
    std::map<int, CleanupFuncT> CallbackStorage::sCleanupFuncCallbacks;
    std::map<int, GRPCInitFuncT> CallbackStorage::sInitFuncCallbacks;
    std::map<int, GRPCCreateFuncT> CallbackStorage::sCreateFuncCallbacks;
    std::map<int, DestroyFuncT> CallbackStorage::sDestroyFuncCallbacks;
    std::map<int, OnEvaluateFuncT> CallbackStorage::sEvaluateFuncCallbacks;
    std::map<int, OnTriggerFuncT> CallbackStorage::sTriggerFuncCallbacks;
    std::map<int, GRPCLoadRenderStateProjectT> CallbackStorage::sLoadRenderStateCallbacks;
    std::map<int, GRPCChangeManagerChangeT> CallbackStorage::sOnChangeManagerChangeCallbacks;
    std::map<int, GRPCChangeManagerTimeChangeT> CallbackStorage::sChangeManagerTimeChangeCallbacks;
    std::map<int, OnApiProjectManagerChangeT> CallbackStorage::sApiProjectManagerChangeCallbacks;
    std::map<int, OnSelectionManagerChangeT> CallbackStorage::sSelectionManagerChangeCallbacks;
    std::map<int, GRPCColorChangedT> CallbackStorage::sColorChangedCallbacks;
    std::map<int, CommandModuleRunFuncT> CallbackStorage::sCommandModuleRunFuncCallbacks;
    std::map<int, ObserverCallbackT> CallbackStorage::sObserverCallbacks;
    std::map<int, DbViewLoadedCallbackT> CallbackStorage::sDbViewLoadedCallbacks;
    std::map<int, Octane::ApiRenderCloudManager::FinishCallbackT> CallbackStorage::sFinishCallbacks;
    std::map<int, Octane::ApiRenderEngine::OnTileBlendedCallbackT> CallbackStorage::sOnTileBlendedCallbacks;
    std::map<int, Octane::ApiRenderEngine::OnNewStatisticsCallbackT> CallbackStorage::sOnNewStatisticsCallbacks;
    std::map<int, Octane::ApiRenderEngine::OnNewImageCallbackT> CallbackStorage::sOnNewImageCallbacks;
    std::map<int, Octane::ApiRenderEngine::OnOcioErrorCallbackT> CallbackStorage::sOnOcioErrorCallbacks;
    std::map<int, Octane::ApiRenderEngine::OnRenderFailureCallbackT> CallbackStorage::sOnRenderFailureCallbacks;
    std::map<int, Octane::ApiRootNodeGraph::NextChunkCallbackT> CallbackStorage::sNextChunkCallbacks;
    std::map<int, GRPCCheckedCallbackT> CallbackStorage::sGrpcCheckedCallbacks;
    std::map<int, GRPCComboBoxChangedCallbackT> CallbackStorage::sGrpcComboBoxChangedCallbacks;
    std::map<int, ApiLogCallbackProc> CallbackStorage::sApiLogCallbackProcs;
    std::map<int, Octane::ApiMainWindow::OnMainWindowCloseCallbackT> CallbackStorage::sOnMainWindowCloseCallbacks;
    std::map<int, GRPCMouseEventCallbackT> CallbackStorage::sGrpcMouseEventCallbacks;
    std::map<int, DbViewClosingCallbackT> CallbackStorage::sDbViewClosingCallbacks;
    std::map<int, GRPCNumericBoxChangedCallbackT> CallbackStorage::sGrpcNumericBoxChangedCallbacks;
    std::map<int, GRPCCallback1T> CallbackStorage::sGrpcCallback1s;
    std::map<int, GRPCCallback2T> CallbackStorage::sGrpcCallback2s;
    std::map<int, Octane::AssetMissingCallbackT> CallbackStorage::sApiProjectManagerAssetMissingCallbacks;
    std::map<int, Octane::ApiRenderCloudManager::UpdateCallbackT> CallbackStorage::sUpdateCallbacks;
    std::map<int, Octane::ApiRenderEngine::AsyncUpdateCallbackT> CallbackStorage::sAsyncUpdateCallbacks;
    std::map<int, Octane::AssetMissingCallbackT> CallbackStorage::sAssetMissingCallbacks;
    std::map<int, Octane::ApiTable::NumRowsCallbackT> CallbackStorage::sNumRowsCallbacks;
    std::map<int, Octane::ApiTable::ContentCallbackT> CallbackStorage::sContentCallbacks;
    std::map<int, GRPCButtonClickedCallbackT> CallbackStorage::sGrpcButtonClickedCallbacks;
    std::map<int, Octane::ApiTable::SelectionChangedCallbackT> CallbackStorage::sSelectionChangedCallbacks;
    std::map<int, GRPCTextEditorChangedCallbackT> CallbackStorage::sGrpcTextEditorChangedCallbacks;
    std::map<int, GRPCOnWindowCloseCallbackT> CallbackStorage::sGrpcOnWindowCloseCallbacks;


    void CallbackStorage::registerOnDaemonUpdate(
        int          id,
        OnDaemonUpdateT callback)
    {
        storeCallback(sOnDaemonUpdateCallbacks, id, callback);
    }


    void CallbackStorage::registerOnStatusUpdate(
        int                                                    id,
        OnStatusUpdateT callback)
    {
        storeCallback(sOnStatusUpdateCallbacks, id, callback);
    }


    void CallbackStorage::registerCleanupFunc(
        int          id,
        CleanupFuncT callback)
    {
        storeCallback(sCleanupFuncCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCInitFunc(
        int           id,
        GRPCInitFuncT callback)
    {
        storeCallback(sInitFuncCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCCreateFunc(
        int             id,
        GRPCCreateFuncT callback)
    {
        storeCallback(sCreateFuncCallbacks, id, callback);
    }


    void CallbackStorage::registerDestroyFunc(
        int          id,
        DestroyFuncT callback)
    {
        storeCallback(sDestroyFuncCallbacks, id, callback);
    }

    void CallbackStorage::registerOnEvaluateFunc(
        int             id,
        OnEvaluateFuncT callback)
    {
        storeCallback(sEvaluateFuncCallbacks, id, callback);
    }

    void CallbackStorage::registerOnTriggerFunc(
        int            id,
        OnTriggerFuncT callback)
    {
        storeCallback(sTriggerFuncCallbacks, id, callback);
    }

    void CallbackStorage::registerGRPCLoadRenderStateProject(
        int                         id,
        GRPCLoadRenderStateProjectT callback)
    {
        storeCallback(sLoadRenderStateCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCChangeObserver(
        int                      id,
        GRPCChangeManagerChangeT callback)
    {
        storeCallback(sOnChangeManagerChangeCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCChangeTimeObserver(
        int                        id,
        GRPCChangeManagerTimeChangeT callback)
    {
        storeCallback(sChangeManagerTimeChangeCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCProjectManagerObserver(
        int                        id,
        OnApiProjectManagerChangeT callback)
    {
        storeCallback(sApiProjectManagerChangeCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCSelectionManagerObserver(
        int                       id,
        OnSelectionManagerChangeT callback)
    {
        storeCallback(sSelectionManagerChangeCallbacks, id, callback);
    }


    void CallbackStorage::registerColorChanged(
        int                   id,
        GRPCColorChangedT     callback)
    {
        storeCallback(sColorChangedCallbacks, id, callback);
    }


    void CallbackStorage::registerCommandModuleRunFunc(
        int                   id,
        CommandModuleRunFuncT callback)
    {
        storeCallback(sCommandModuleRunFuncCallbacks, id, callback);
    }


    void CallbackStorage::registerObserverCallback(
        int               id,
        ObserverCallbackT callback)
    {
        storeCallback(sObserverCallbacks, id, callback);
    }


    void CallbackStorage::registerDbViewLoadedCallback(
        int                   id,
        DbViewLoadedCallbackT callback)
    {
        storeCallback(sDbViewLoadedCallbacks, id, callback);
    }


    void CallbackStorage::registerFinishCallback(
        int                                            id,
        Octane::ApiRenderCloudManager::FinishCallbackT callback)
    {
        storeCallback(sFinishCallbacks, id, callback);
    }


    void CallbackStorage::registerOnTileBlendedCallback(
        int                                             id,
        Octane::ApiRenderEngine::OnTileBlendedCallbackT callback)
    {
        storeCallback(sOnTileBlendedCallbacks, id, callback);
    }


    void CallbackStorage::registerOnNewStatisticsCallback(
        int                                               id,
        Octane::ApiRenderEngine::OnNewStatisticsCallbackT callback)
    {
        storeCallback(sOnNewStatisticsCallbacks, id, callback);
    }


    void CallbackStorage::registerOnNewImageCallback(
        int                                          id,
        Octane::ApiRenderEngine::OnNewImageCallbackT callback)
    {
        storeCallback(sOnNewImageCallbacks, id, callback);
    }


    void CallbackStorage::registerOnOcioErrorCallback(
        int                                           id,
        Octane::ApiRenderEngine::OnOcioErrorCallbackT callback)
    {
        storeCallback(sOnOcioErrorCallbacks, id, callback);
    }


    void CallbackStorage::registerOnRenderFailureCallback(
        int                                               id,
        Octane::ApiRenderEngine::OnRenderFailureCallbackT callback)
    {
        storeCallback(sOnRenderFailureCallbacks, id, callback);
    }


    void CallbackStorage::registerNextChunkCallback(
        int                                          id,
        Octane::ApiRootNodeGraph::NextChunkCallbackT callback)
    {
        storeCallback(sNextChunkCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCCheckedCallback(
        int                  id,
        GRPCCheckedCallbackT callback)
    {
        storeCallback(sGrpcCheckedCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCComboBoxChangedCallback(
        int                          id,
        GRPCComboBoxChangedCallbackT callback)
    {
        storeCallback(sGrpcComboBoxChangedCallbacks, id, callback);
    }


    void CallbackStorage::registerApiLogCallbackProc(
        int                id,
        ApiLogCallbackProc callback)
    {
        storeCallback(sApiLogCallbackProcs, id, callback);
    }


    void CallbackStorage::registerOnMainWindowCloseCallback(
        int                                               id,
        Octane::ApiMainWindow::OnMainWindowCloseCallbackT callback)
    {
        storeCallback(sOnMainWindowCloseCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCMouseEventCallback(
        int                     id,
        GRPCMouseEventCallbackT callback)
    {
        storeCallback(sGrpcMouseEventCallbacks, id, callback);
    }


    void CallbackStorage::registerDbViewClosingCallback(
        int                    id,
        DbViewClosingCallbackT callback)
    {
        storeCallback(sDbViewClosingCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCNumericBoxChangedCallback(
        int                            id,
        GRPCNumericBoxChangedCallbackT callback)
    {
        storeCallback(sGrpcNumericBoxChangedCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCCallback1(
        int            id,
        GRPCCallback1T callback)
    {
        storeCallback(sGrpcCallback1s, id, callback);
    }


    void CallbackStorage::registerGRPCCallback2(
        int            id,
        GRPCCallback2T callback)
    {
        storeCallback(sGrpcCallback2s, id, callback);
    }


    void CallbackStorage::registerApiProjectManager_AssetMissingCallback(
        int                           id,
        Octane::AssetMissingCallbackT callback)
    {
        storeCallback(sApiProjectManagerAssetMissingCallbacks, id, callback);
    }


    void CallbackStorage::registerUpdateCallback(
        int                                            id,
        Octane::ApiRenderCloudManager::UpdateCallbackT callback)
    {
        storeCallback(sUpdateCallbacks, id, callback);
    }


    void CallbackStorage::registerAsyncUpdateCallback(
        int                                           id,
        Octane::ApiRenderEngine::AsyncUpdateCallbackT callback)
    {
        storeCallback(sAsyncUpdateCallbacks, id, callback);
    }


    void CallbackStorage::registerAssetMissingCallback(
        int                           id,
        Octane::AssetMissingCallbackT callback)
    {
        storeCallback(sAssetMissingCallbacks, id, callback);
    }


    void CallbackStorage::registerNumRowsCallback(
        int                                id,
        Octane::ApiTable::NumRowsCallbackT callback)
    {
        storeCallback(sNumRowsCallbacks, id, callback);
    }


    void CallbackStorage::registerContentCallback(
        int                                id,
        Octane::ApiTable::ContentCallbackT callback)
    {
        storeCallback(sContentCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCButtonClickedCallback(
        int                        id,
        GRPCButtonClickedCallbackT callback)
    {
        storeCallback(sGrpcButtonClickedCallbacks, id, callback);
    }


    void CallbackStorage::registerSelectionChangedCallback(
        int                                         id,
        Octane::ApiTable::SelectionChangedCallbackT callback)
    {
        storeCallback(sSelectionChangedCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCTextEditorChangedCallback(
        int                            id,
        GRPCTextEditorChangedCallbackT callback)
    {
        storeCallback(sGrpcTextEditorChangedCallbacks, id, callback);
    }


    void CallbackStorage::registerGRPCOnWindowCloseCallback(
        int                        id,
        GRPCOnWindowCloseCallbackT callback)
    {
        storeCallback(sGrpcOnWindowCloseCallbacks, id, callback);
    }


    int CallbackStorage::unregisterOnDaemonUpdate(
        OnDaemonUpdateT callback)
    {
        return removeCallback(sOnDaemonUpdateCallbacks, callback);
    }


    int CallbackStorage::unregisterOnStatusUpdate(
        OnStatusUpdateT callback)
    {
        return removeCallback(sOnStatusUpdateCallbacks, callback);
    }


    int CallbackStorage::unregisterCleanupFunc(
        CleanupFuncT callback)
    {
        return removeCallback(sCleanupFuncCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCInitFunc(
        GRPCInitFuncT callback)
    {
        return removeCallback(sInitFuncCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCCreateFunc(
        GRPCCreateFuncT callback)
    {
        return removeCallback(sCreateFuncCallbacks, callback);
    }


    int CallbackStorage::unregisterDestroyFunc(
        DestroyFuncT callback)
    {
        return removeCallback(sDestroyFuncCallbacks, callback);
    }


    int CallbackStorage::unregisterOnEvaluateFunc(
        OnEvaluateFuncT callback)
    {
        return removeCallback(sEvaluateFuncCallbacks, callback);
    }


    int CallbackStorage::unregisterOnTriggerFunc(
        OnTriggerFuncT callback)
    {
        return removeCallback(sTriggerFuncCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCLoadRenderStateProject(
        GRPCLoadRenderStateProjectT callback)
    {
        return removeCallback(sLoadRenderStateCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCChangeObserver(
        GRPCChangeManagerChangeT callback)
    {
        return removeCallback(sOnChangeManagerChangeCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCChangeTimeObserver(
        GRPCChangeManagerTimeChangeT callback)
    {
        return removeCallback(sChangeManagerTimeChangeCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCProjectManagerObserver(
        OnApiProjectManagerChangeT callback)
    {
        return removeCallback(sApiProjectManagerChangeCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCSelectionManagerObserver(
        OnSelectionManagerChangeT callback)
    {
        return removeCallback(sSelectionManagerChangeCallbacks, callback);
    }


    int CallbackStorage::unregisterColorChanged(
        GRPCColorChangedT callback)
    {
        return removeCallback(sColorChangedCallbacks, callback);
    }


    int CallbackStorage::unregisterCommandModuleRunFunc(
        CommandModuleRunFuncT callback)
    {
        return removeCallback(sCommandModuleRunFuncCallbacks, callback);
    }


    int CallbackStorage::unregisterObserverCallback(
        ObserverCallbackT callback)
    {
        return removeCallback(sObserverCallbacks, callback);
    }


    int CallbackStorage::unregisterDbViewLoadedCallback(
        DbViewLoadedCallbackT callback)
    {
        return removeCallback(sDbViewLoadedCallbacks, callback);
    }


    int CallbackStorage::unregisterFinishCallback(
        Octane::ApiRenderCloudManager::FinishCallbackT callback)
    {
        return removeCallback(sFinishCallbacks, callback);
    }


    int CallbackStorage::unregisterOnTileBlendedCallback(
        Octane::ApiRenderEngine::OnTileBlendedCallbackT callback)
    {
        return removeCallback(sOnTileBlendedCallbacks, callback);
    }


    int CallbackStorage::unregisterOnNewStatisticsCallback(
        Octane::ApiRenderEngine::OnNewStatisticsCallbackT callback)
    {
        return removeCallback(sOnNewStatisticsCallbacks, callback);
    }


    int CallbackStorage::unregisterOnNewImageCallback(
        Octane::ApiRenderEngine::OnNewImageCallbackT callback)
    {
        return removeCallback(sOnNewImageCallbacks, callback);
    }


    int CallbackStorage::unregisterOnOcioErrorCallback(
        Octane::ApiRenderEngine::OnOcioErrorCallbackT callback)
    {
        return removeCallback(sOnOcioErrorCallbacks, callback);
    }


    int CallbackStorage::unregisterOnRenderFailureCallback(
        Octane::ApiRenderEngine::OnRenderFailureCallbackT callback)
    {
        return removeCallback(sOnRenderFailureCallbacks, callback);
    }


    int CallbackStorage::unregisterNextChunkCallback(
        Octane::ApiRootNodeGraph::NextChunkCallbackT callback)
    {
        return removeCallback(sNextChunkCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCCheckedCallback(
        GRPCCheckedCallbackT callback)
    {
        return removeCallback(sGrpcCheckedCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCComboBoxChangedCallback(
        GRPCComboBoxChangedCallbackT callback)
    {
        return removeCallback(sGrpcComboBoxChangedCallbacks, callback);
    }


    int CallbackStorage::unregisterApiLogCallbackProc(
        ApiLogCallbackProc callback)
    {
        return removeCallback(sApiLogCallbackProcs, callback);
    }


    int CallbackStorage::unregisterOnMainWindowCloseCallback(
        Octane::ApiMainWindow::OnMainWindowCloseCallbackT callback)
    {
        return removeCallback(sOnMainWindowCloseCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCMouseEventCallback(
        GRPCMouseEventCallbackT callback)
    {
        return removeCallback(sGrpcMouseEventCallbacks, callback);
    }


    int CallbackStorage::unregisterDbViewClosingCallback(
        DbViewClosingCallbackT callback)
    {
        return removeCallback(sDbViewClosingCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCNumericBoxChangedCallback(
        GRPCNumericBoxChangedCallbackT cb)
    {
        return removeCallback(sGrpcNumericBoxChangedCallbacks, cb);
    }


    int CallbackStorage::unregisterGRPCCallback1(
        GRPCCallback1T callback)
    {
        return removeCallback(sGrpcCallback1s, callback);
    }


    int CallbackStorage::unregisterGRPCCallback2(
        GRPCCallback2T callback)
    {
        return removeCallback(sGrpcCallback2s, callback);
    }


    int CallbackStorage::unregisterApiProjectManager_AssetMissingCallback(
        Octane::AssetMissingCallbackT cb)
    {
        return removeCallback(sApiProjectManagerAssetMissingCallbacks, cb);
    }


    int CallbackStorage::unregisterUpdateCallback(
        Octane::ApiRenderCloudManager::UpdateCallbackT callback)
    {
        return removeCallback(sUpdateCallbacks, callback);
    }


    int CallbackStorage::unregisterAsyncUpdateCallback(
        Octane::ApiRenderEngine::AsyncUpdateCallbackT callback)
    {
        return removeCallback(sAsyncUpdateCallbacks, callback);
    }


    int CallbackStorage::unregisterAssetMissingCallback(
        Octane::AssetMissingCallbackT callback)
    {
        return removeCallback(sAssetMissingCallbacks, callback);
    }


    int CallbackStorage::unregisterNumRowsCallback(
        Octane::ApiTable::NumRowsCallbackT callback)
    {
        return removeCallback(sNumRowsCallbacks, callback);
    }


    int CallbackStorage::unregisterContentCallback(
        Octane::ApiTable::ContentCallbackT callback)
    {
        return removeCallback(sContentCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCButtonClickedCallback(
        GRPCButtonClickedCallbackT callback)
    {
        return removeCallback(sGrpcButtonClickedCallbacks, callback);
    }


    int CallbackStorage::unregisterSelectionChangedCallback(
        Octane::ApiTable::SelectionChangedCallbackT callback)
    {
        return removeCallback(sSelectionChangedCallbacks, callback);
    }


    int CallbackStorage::unregisterGRPCTextEditorChangedCallback(
        GRPCTextEditorChangedCallbackT cb)
    {
        return removeCallback(sGrpcTextEditorChangedCallbacks, cb);
    }


    int CallbackStorage::unregisterGRPCOnWindowCloseCallback(
        GRPCOnWindowCloseCallbackT callback)
    {
        return removeCallback(sGrpcOnWindowCloseCallbacks, callback);
    }


    void CallbackStorage::invokeOnDaemonUpdate(
        int                                    id,
        const ApiArray<const NetDaemonInfo*> & daemonInfoArray,
        void                                 * userData)
    {
        auto fn = fetchFromMap(sOnDaemonUpdateCallbacks, id);
        if (fn) fn(daemonInfoArray, userData);
    }


    void CallbackStorage::invokeOnStatusUpdate(
        int                     id,
        const NetRenderStatus & netstatus,
        void *                  userData)
    {
        auto fn = fetchFromMap(sOnStatusUpdateCallbacks, id);
        if (fn) fn(netstatus, userData);
    }


    void CallbackStorage::invokeCleanupFunc(
        int                   id,
        void *                userData)
    {
        auto fn = fetchFromMap(sCleanupFuncCallbacks, id);
        if (fn) fn(userData);
    }


    void * CallbackStorage::invokeGRPCInitFunc(
        int                   id,
        ApiGridLayoutProxy *  const gridLayout)
    {
        auto fn = fetchFromMap(sInitFuncCallbacks, id);
        return fn ? fn(gridLayout) : nullptr;
    }


    void * CallbackStorage::invokeGRPCCreateFunc(
        int                        id,
        ApiModuleNodeGraphProxy *  const  gridLayout)
    {
        auto fn = fetchFromMap(sCreateFuncCallbacks, id);
        return fn ? fn(gridLayout) : nullptr;
    }


    void CallbackStorage::invokeDestroyFunc(
        int                   id,
        void * const          userData)
    {
        auto fn = fetchFromMap(sDestroyFuncCallbacks, id);
        if (fn) fn(userData);
    }


    void CallbackStorage::invokeOnEvaluateFunc(
        int                   id,
        void * const          userData)
    {
        auto fn = fetchFromMap(sEvaluateFuncCallbacks, id);
        if (fn) fn(userData);
    }


    void CallbackStorage::invokeOnTriggerFunc(
        int                   id,
        void * const          userData)
    {
        auto fn = fetchFromMap(sTriggerFuncCallbacks, id);
        if (fn) fn(userData);
    }


    ApiNodeProxy * CallbackStorage::invokeGRPCLoadRenderStateProject(
        int                   id,
        const char * const    customProjectFileName,
        const float           customProjectTime,
        const uint32_t        customVersion,
        const void * const    customData,
        const uint32_t        customDataSize,
        void       * const    privateCallbackData)
    {
        auto fn = fetchFromMap(sLoadRenderStateCallbacks, id);
        return fn ? fn( customProjectFileName,
                        customProjectTime,
                        customVersion,
                        customData,
                        customDataSize,
                        privateCallbackData) : nullptr;
    }


    void CallbackStorage::invokeGRPCChangeObserver(
        int                                  id,
        const GRPCChangeManagerChangeEvent & changeEvent,
        void *                               userData)
    {
        auto fn = fetchFromMap(sOnChangeManagerChangeCallbacks, id);
        if (fn) fn(changeEvent, userData);
    }

    void CallbackStorage::invokeGRPCChangeTimeObserver(
        int                                      id,
        const GRPCChangeManagerTimeChangeEvent & changeEvent,
        void *                                   userData)
    {
        auto fn = fetchFromMap(sChangeManagerTimeChangeCallbacks, id);
        if (fn) fn(changeEvent, userData);
    }


    void CallbackStorage::invokeGRPCProjectManagerObserver(
        int                 id,
        void *              userData)
    {
        auto fn = fetchFromMap(sApiProjectManagerChangeCallbacks, id);
        if (fn) fn(userData);
    }


    void CallbackStorage::invokeGRPCSelectionManagerObserver(
        int                 id,
        void *              userData)
    {
        auto fn = fetchFromMap(sSelectionManagerChangeCallbacks, id);
        if (fn) fn(userData);
    }


    void CallbackStorage::invokeColorChanged(
        int                   id,
        ApiColorSwatchProxy & colorSwatch,
        void *                userData)
    {
        auto fn = fetchFromMap(sColorChangedCallbacks, id);
        if (fn) fn(colorSwatch, userData);
    }


    bool CallbackStorage::invokeCommandModuleRunFunc(
        int          id,
        void * const workpaneUserData)
    {
        auto fn = fetchFromMap(sCommandModuleRunFuncCallbacks, id);
        return fn ? fn(workpaneUserData) : false;
    }


    void CallbackStorage::invokeObserverCallback(
        int                            id,
        void *                         opaqueData,
        Octane::ApiLocalDB::UpdateType type,
        const char *                   path)
    {
        auto fn = fetchFromMap(sObserverCallbacks, id);
        if (fn) fn(opaqueData, type, path);
    }


    void CallbackStorage::invokeDbViewLoadedCallback(
        int                  id,
        void *               userData,
        Octane::ItemDbOrigin origin)
    {
        auto fn = fetchFromMap(sDbViewLoadedCallbacks, id);
        if (fn) fn(userData, origin);
    }


    void CallbackStorage::invokeFinishCallback(
        int           id,
        const bool    success,
        const char *  errorMsg,
        const GuidT   sceneGuid,
        const GuidT   rootGuid,
        const char  * sceneName,
        void        * data)
    {
        auto fn = fetchFromMap(sFinishCallbacks, id);
        if (fn) fn(success, errorMsg, sceneGuid, rootGuid, sceneName, data);
    }


    void CallbackStorage::invokeOnTileBlendedCallback(  
        int    id,
        void * userData)
    {
        auto fn = fetchFromMap(sOnTileBlendedCallbacks, id);
        if (fn) fn(userData);
    }


    void CallbackStorage::invokeOnNewStatisticsCallback(
        int    id,
        void * userData)
    {
        auto fn = fetchFromMap(sOnNewStatisticsCallbacks, id);
        if (fn) fn(userData);
    }


    void CallbackStorage:: invokeOnNewImageCallback(
        int                              id,
        const ApiArray<ApiRenderImage> & renderImages,
        void *                           userData)
    {
        auto fn = fetchFromMap(sOnNewImageCallbacks, id);
        if (fn) fn(renderImages, userData);
    }


    void CallbackStorage::invokeOnOcioErrorCallback(
        int                              id,
        const ApiArray<const char *> &   messages,
        bool                             hasError,
        void *                           userData)
    {
        auto fn = fetchFromMap(sOnOcioErrorCallbacks, id);
        if (fn) fn(messages, hasError, userData);
    }


    void CallbackStorage::invokeOnRenderFailureCallback(
        int                              id,
        void *                           userData)
    {
        auto fn = fetchFromMap(sOnRenderFailureCallbacks, id);
        if (fn) fn(userData);
    }


    size_t CallbackStorage::invokeNextChunkCallback(
        int                 id,
        void *              userData,
        unsigned char* &    dataChunk)
    {
        auto fn = fetchFromMap(sNextChunkCallbacks, id);
        if (fn)
        {
            return fn(userData, dataChunk);
        }
        return 0;
    }


    void CallbackStorage::invokeGRPCCheckedCallback(
        int               id,
        ApiCheckBoxProxy & button,
        void *            userData)
    {
        auto fn = fetchFromMap(sGrpcCheckedCallbacks, id);
        if (fn) fn(button, userData);
    }


    void CallbackStorage::invokeGRPCComboBoxChangedCallback(
        int                id,
        ApiComboBoxProxy & comboBox,
        void *             userData)
    {
        auto fn = fetchFromMap(sGrpcComboBoxChangedCallbacks, id);
        if (fn) fn(comboBox, userData);
    }


    void CallbackStorage::invokeApiLogCallback(
        int                                   id,
        Octane::ApiLogManager::LogMessageType type,
        const char *                          message)
    {
        auto fn = fetchFromMap(sApiLogCallbackProcs, id);
        if (fn) fn(type, message);
    }


    void CallbackStorage::invokeOnMainWindowCloseCallback(
        int    id,
        void * privateData)
    {
        auto fn = fetchFromMap(sOnMainWindowCloseCallbacks, id);
        if (fn) fn(privateData);
    }


    void CallbackStorage::invokeGRPCMouseEventCallback(
        int                                  id,
        Octane::ApiMouseEventType            evType,
        const GRPCApiMouseEventData &           event,
        const Octane::ApiMouseWheelDetails & wheelDetails,
        void *                               privateData)
    {
        auto fn = fetchFromMap(sGrpcMouseEventCallbacks, id);
        if (fn) fn(evType, event, wheelDetails, privateData);
    }


    void CallbackStorage::invokeDbViewClosingCallback(
        int    id,
        void * userData)
    {
        auto fn = fetchFromMap(sDbViewClosingCallbacks, id);
        if (fn) fn(userData);
    }


    void CallbackStorage::invokeGRPCNumericBoxChangedCallback(
        int                  id,
        ApiNumericBoxProxy & numericBox,
        void *               userData)
    {
        auto fn = fetchFromMap(sGrpcNumericBoxChangedCallbacks, id);
        if (fn) fn(numericBox, userData);
    }


    void CallbackStorage::invokeGRPCCallback1(int id,
        bool                 loading,
        ApiOcioConfigProxy * config,
        void *               privateData)
    {
        auto fn = fetchFromMap(sGrpcCallback1s, id);
        if (fn) fn(loading, config, privateData);
    }


    void CallbackStorage::invokeGRPCCallback2(int id,
        ApiOcioConfigProxy * config,
        bool                 contextUsableForConversion,
        void *               privateData)
    {
        auto fn = fetchFromMap(sGrpcCallback2s, id);
        if (fn) fn(config, contextUsableForConversion, privateData);
    }


    const char *  CallbackStorage::invokeApiProjectManager_AssetMissingCallback(
        int          id,
        const char * fileName,
        void       * userData)
    {
        auto fn = fetchFromMap(sApiProjectManagerAssetMissingCallbacks, id);
        if (fn)
        {
            return fn(fileName, userData);
        }
        return "";
    }


    bool CallbackStorage::invokeUpdateCallback(
        int          id,
        const float percent,
        void        *data)
    {
        auto fn = fetchFromMap(sUpdateCallbacks, id);
        return fn ? fn(percent, data) : false;
    }


    void CallbackStorage::invokeAsyncUpdateCallback(
        int           id,
        const CLevelT changeLevel,
        void *        userData)
    {
        auto fn = fetchFromMap(sAsyncUpdateCallbacks, id);
        if (fn) fn(changeLevel, userData);
    }


    const char * CallbackStorage::invokeAssetMissingCallback(
        int           id,
        const char *  fileName,
        void       *  userData)
    {
        auto fn = fetchFromMap(sAssetMissingCallbacks, id);
        if (fn)
        {
            return fn(fileName, userData);
        }
        return "";
    }


    int CallbackStorage::invokeNumRowsCallback(
        int    id,
        void * privateData)
    {
        auto fn = fetchFromMap(sNumRowsCallbacks, id);
        if (fn)
        {
            return fn(privateData);
        }
        return 0;
    }


    const char* CallbackStorage::invokeContentCallback(
        int       id,
        const int row,
        const int column,
        void *    privateData)
    {
        auto fn = fetchFromMap(sContentCallbacks, id);
        if (fn)
        {
            return fn(row, column, privateData);
        }
        return "";
    }


    void CallbackStorage::invokeGRPCButtonClickedCallback(
        int                  id,
        ApiTextButtonProxy & textButton,
        void *               userData)
    {
        auto fn = fetchFromMap(sGrpcButtonClickedCallbacks, id);
        if (fn) fn(textButton, userData);
    }


    void CallbackStorage::invokeSelectionChangedCallback(
        int       id,
        const int lastRowSelected,
        void *    privateData)
    {
        auto fn = fetchFromMap(sSelectionChangedCallbacks, id);
        if (fn) fn(lastRowSelected, privateData);
    }


    void CallbackStorage::invokeGRPCTextEditorChangedCallback(
        int                  id,
        ApiTextEditorProxy & textEdit,
        void *               userData)
    {
        auto fn = fetchFromMap(sGrpcTextEditorChangedCallbacks, id);
        if (fn) fn(textEdit, userData);
    }


    void CallbackStorage::invokeGRPCOnWindowCloseCallback(
        int              id,
        ApiWindowProxy & window,
        void *           userData)
    {
        auto fn = fetchFromMap(sGrpcOnWindowCloseCallbacks, id);
        if (fn) fn(window, userData);
    }

}// namespace OctaneGRPC