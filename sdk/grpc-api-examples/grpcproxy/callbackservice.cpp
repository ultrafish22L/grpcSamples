// Copyright (C) 2025 OTOY NZ Ltd.

#include "callbackservice.h"
#include "apinodeclient.h"
#include "apimoduleglobalclient.h"
#include "apimodulenodegraphclient.h"
#include "apicommandmoduleinfoclient.h"
#include "apiguicomponentclient.h"
#include "apicolorswatchclient.h"
#include "apigridlayoutclient.h"
#include "apirootnodegraphclient.h"
#include "apicheckboxclient.h"
#include "apicomboboxclient.h"
#include "apimouseeventclient.h"
#include "apinumericboxclient.h"
#include "apiocioconfigclient.h"
#include "apiwindowclient.h"
#include "apitextbuttonclient.h"
#include "apitexteditorclient.h"
#include "grpcmaininterface.h"
#include "grpcmouseevent.h"
#include "grpcsettings.h"
#include "apicontrol.h"

namespace OctaneGRPC
{

void CallbackHandlerImpl::setInterface(
    GRPCMainInterface * mainInterface)
{
    mMainInterface = mainInterface;
}


void CallbackHandlerImpl::registerModule(
    const Octane::ModuleIdT                                   moduleId,
    const char *                                              fullName,
    const char *                                              description,
    const char *                                              author,
    const Octane::VersionT                                    versionNumber,
    const Octane::ApiCommandModuleInfo::CommandModuleRunFuncT runFunction,
    const ApiImageProxy &                                     icon,
    const char *                                              shortcutGroupName,
    const int                                                 shortcutKeyCode,
    const int                                                 shortcutModifierKeyFlag)
{
    ApiCommandModuleInfoProxy info = ApiCommandModuleInfoProxy::create(moduleId, fullName, description, author, versionNumber);
    info.setRunFunction(runFunction);
    info.setIcon(&icon);
    info.assignShortcutKey(shortcutGroupName, shortcutKeyCode, shortcutModifierKeyFlag);

    // register as dynamically linked module
    ApiModuleGlobalProxy::registerCommandModule(info);

    info.destroy();
}


grpc::Status CallbackHandlerImpl::PerformBlocking(
    grpc::ServerContext *             context,
    const ::google::protobuf::Empty * request,
    octaneapi::CallbackAck *          response)
{
    ApiControlService::callBlockingFunc();

    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::IsReady(
    grpc::ServerContext *             context,
    const octaneapi::IsReadyRequest * request,
    octaneapi::IsReadyResponse *      response)
{
    // let the caller know we are ready
    if (mMainInterface)
    {
        response->set_success(mMainInterface->isReady());
    }
    else
    {
        response->set_success(false);
    }
    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::Start(
    grpc::ServerContext *           context,
    const octaneapi::StartRequest * request,
    octaneapi::StartResponse *      response)
{
    if (mMainInterface)
    {
        std::string callbackString = request->callbacksource();
        bool displayEnglish        = request->displayingenglish();
        int secondLanguage         = request->secondlanguage();
        if (callbackString == "")
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "ID cannot be empty");
        }
        GRPCSettings::getInstance().setUniqueString(callbackString);
        mMainInterface->start(callbackString, displayEnglish, secondLanguage);
    }

    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::Stop(
    grpc::ServerContext *          context,
    const octaneapi::StopRequest * request,
    octaneapi::StopResponse *      response)
{
    if (mMainInterface)
    {
        mMainInterface->stop();
    }
    //#ifdef _NODE_GRAPH_EXAMPLE
    //#else
    //
    //    if (gApplication)
    //    {
    //        delete gApplication;
    //        gApplication = nullptr;
    //    }
    //
    //    // 1) Post a lambda to the JUCE message thread to quit the app
    //    juce::MessageManager::callAsync([]()
    //        {
    //            // This runs on the main JUCE thread
    //            // Safely shut down the JUCEApplication
    //            juce::JUCEApplicationBase::quit();
    //        });
    //
    //#endif
    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::Notify(
    grpc::ServerContext *                  context,
    const octaneapi::NotificationRequest * request,
    octaneapi::NotificationResponse *      response)
{
    //juce::ScopedLock lock(mDataMutex);    // Thread-safe access

    //std::cout << "Received callback! Notification ID: " << request->notification_id()
    //    << ", Message: " << request->message() << std::endl;
    //const ::octaneapi::ApiArrayApiRenderImage & images = request->images();
    //response->set_status("Received successfully!");
    //// see apirender.proto
    ////message ApiArrayApiRenderImage {//ApiArray<ApiRenderImage 
    ////    repeated ApiRenderImage arrayData = 1; // Temporary placeholder field.
    ////}
    //if (mMainWnd)
    //{
    //    mMainWnd->renderComponent().receiveImageData(images);
    //}

    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::LoadRenderStateProject(
    ::grpc::ServerContext* context,
    const ::octaneapi::LoadRenderStateProjectRequest* request,
    ::octaneapi::LoadRenderStateProjectResponse* response)
{
    int       callbackId    = request->callback_id();
    uint64_t  userDataU64   = request->user_data();
    void *    userDataPtr   = reinterpret_cast<void*>(userDataU64);

    const std::string & customProjectFileName = request->customprojectfilename();
    float  customProjectTime                  = request->customprojecttime();
    uint32_t customVersion                    = (uint32_t)request->customversion();
    const std::string & customDataStr         = request->custom_data();
    const void *        customData     = static_cast<const void*>(customDataStr.data());
    uint32_t            customDataSize = static_cast<uint32_t>(customDataStr.size());

    auto * nodePtr = CallbackStorage::invokeGRPCLoadRenderStateProject(
        callbackId,
        customProjectFileName.c_str(),
        customProjectTime,
        customVersion,
        customData,
        customDataSize,
        userDataPtr
    );

    if (nodePtr)
    {
        auto * modNodeGraph = new ::octaneapi::ObjectRef();
        modNodeGraph->set_handle(nodePtr->getObjectHandle());
        modNodeGraph->set_type(::octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
        response->set_allocated_modulenodegraph(modNodeGraph);
    }

    return ::grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::OnDaemonUpdate(
    ::grpc::ServerContext *                  context,
    const ::octaneapi::DaemonUpdateRequest * request,
    ::octaneapi::CallbackAck *               response)
{
    int      callbackId = request->callback_id();
    uint64_t userVal    = request->user_data();
    void*    userPtr    = reinterpret_cast<void*>(userVal);

    int daemonCount = request->daemoninfoarray_size();

    std::unique_ptr<Octane::NetDaemonInfo[]> daemonObjects(
        new Octane::NetDaemonInfo[daemonCount]
    );

    std::vector<const Octane::NetDaemonInfo*> daemonPtrVec;
    daemonPtrVec.reserve(daemonCount);

    std::vector<std::unique_ptr<char[]>> ownedStrings;
    ownedStrings.reserve(2 * daemonCount);

    for (int i = 0; i < daemonCount; ++i)
    {
        const auto & src = request->daemoninfoarray(i);
        Octane::NetDaemonInfo & dst = daemonObjects[i];

        dst.mIpAddress    = static_cast<Octane::IPv4T>(src.ipaddress());
        dst.mState        = static_cast<Octane::NetDaemonState>(src.state());
        dst.mGpuCount     = src.gpucount();
        dst.mSlaveVersion = src.slaveversion();

        dst.mBoundMasterAddress.mIpAddress = static_cast<Octane::IPv4T>(
            src.boundmasteraddress().ipaddress()
            );
        dst.mBoundMasterAddress.mPort = static_cast<uint16_t>(
            src.boundmasteraddress().port()
            );

        {
            const std::string & nameStr = src.name();
            std::unique_ptr<char[]> buf(new char[nameStr.size() + 1]);
            std::memcpy(buf.get(), nameStr.c_str(), nameStr.size() + 1);
            dst.mName = buf.get(); 
            ownedStrings.push_back(std::move(buf)); 
        }

        {
            const std::string & bmNameStr = src.boundmastername();
            std::unique_ptr<char[]> buf(new char[bmNameStr.size() + 1]);
            std::memcpy(buf.get(), bmNameStr.c_str(), bmNameStr.size() + 1);
            dst.mBoundMasterName = buf.get();
            ownedStrings.push_back(std::move(buf)); 
        }

        daemonPtrVec.push_back(&dst);
    }

    Octane::ApiArray<const Octane::NetDaemonInfo*> daemonInfoArray;
    daemonInfoArray.mData = daemonPtrVec.data();
    daemonInfoArray.mSize = static_cast<size_t>(daemonCount);

    CallbackStorage::invokeOnDaemonUpdate(callbackId, daemonInfoArray, userPtr);

    // Set success in the gRPC response
    response->set_success(true);
    return ::grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::OnStatusUpdate(
    ::grpc::ServerContext *                  context,
    const ::octaneapi::StatusUpdateRequest * request,
    ::octaneapi::CallbackAck *               response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function/
    Octane::NetRenderStatus netstatus;

    netstatus.mNetSlaveCount = request->status().netslavecount();
    netstatus.mUpdatingNetSlaveCount = request->status().updatingnetslavecount();
    netstatus.mUpdatedNetSlaveCount = request->status().updatednetslavecount();
    netstatus.mPendingSize = request->status().pendingsize();
    netstatus.mTotalSize = request->status().totalsize();
    netstatus.mNetGpuCount = request->status().netgpucount();
    netstatus.mInUseNetGpuCount = request->status().inusenetgpucount();

    CallbackStorage::invokeOnStatusUpdate(callbackId, netstatus, userDataPtr);

    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::TriggerFunc (
    grpc::ServerContext *                 context,
    const octaneapi::TriggerFuncRequest * request,
    octaneapi::CallbackAck *              response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function/
    CallbackStorage::invokeOnTriggerFunc(callbackId, userDataPtr);
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::EvaluateFunc (
    grpc::ServerContext*                   context,
    const octaneapi::EvaluateFuncRequest * request,
    octaneapi::CallbackAck *               response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function/
    CallbackStorage::invokeCleanupFunc(callbackId, userDataPtr);
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::CleanupFunc (
    grpc::ServerContext *                 context,
    const octaneapi::CleanupFuncRequest * request,
    octaneapi::CallbackAck *              response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function/
    CallbackStorage::invokeCleanupFunc(callbackId, userDataPtr);
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::DestroyFunc (
    grpc::ServerContext *                 context,
    const octaneapi::DestroyFuncRequest * request,
    octaneapi::CallbackAck *              response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function/
    CallbackStorage::invokeDestroyFunc(callbackId, userDataPtr);
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::ColorChanged(
    grpc::ServerContext *                  context,
    const octaneapi::ColorChangedRequest * request,
    octaneapi::CallbackAck *               response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    octaneapi::ObjectRef apiColorSwatchProxyPtr = request->apicolorswatch();
    ApiColorSwatchProxy apiColorSwatchProxy;
    apiColorSwatchProxy.attachObjectHandle(apiColorSwatchProxyPtr.handle());

    // Call the client-side callback function/
    CallbackStorage::invokeColorChanged(callbackId, apiColorSwatchProxy, userDataPtr);
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::CreateFunc (
    grpc::ServerContext *                  context,
    const octaneapi::CreateFuncRequest *   request,
    octaneapi::CreateFuncResponse *        response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();

    octaneapi::ObjectRef apiModuleNodeGraphPtr = request->modulenodegraph();
    ApiModuleNodeGraphProxy apiModuleNodeGraph;
    apiModuleNodeGraph.attachObjectHandle(apiModuleNodeGraphPtr.handle());

    // Call the client-side callback function/
    void * userDataPtr = CallbackStorage::invokeGRPCCreateFunc(callbackId, &apiModuleNodeGraph);
    uint64_t userData = reinterpret_cast<uint64_t>(userDataPtr);
    response->set_user_data(userData);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::InitFunc (
    grpc::ServerContext *              context,
    const octaneapi::InitFuncRequest *     request,
    octaneapi::InitFuncResponse *          response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();

    octaneapi::ObjectRef apiGridLayoutPtr = request->apigridlayout();
    ApiGridLayoutProxy apiGridLayout;
    apiGridLayout.attachObjectHandle(apiGridLayoutPtr.handle());

    // Call the client-side callback function/
    void * userDataPtr = CallbackStorage::invokeGRPCInitFunc(callbackId, &apiGridLayout);
    uint64_t userData = reinterpret_cast<uint64_t>(userDataPtr);
    response->set_user_data(userData);
    return grpc::Status::OK; 
}


grpc::Status CallbackHandlerImpl::ChangeManagerObserver (
    grpc::ServerContext *                           context,
    const octaneapi::ChangeManagerObserverRequest * request,
    octaneapi::CallbackAck *                        response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    GRPCChangeManagerChangeEvent eventData;

    octaneapi::ObjectRef changedOwnerPtr = request->eventdata().changedowner();
    ApiItemProxy changedOwner;
    changedOwner.attachObjectHandle(changedOwnerPtr.handle());

    octaneapi::ObjectRef changedItemPtr = request->eventdata().changeditem();
    ApiItemProxy changedItem;
    changedItem.attachObjectHandle(changedItemPtr.handle());

    eventData.mChangedOwner = &changedOwner;
    eventData.mChangedItem = &changedItem;

    eventData.mType = (GRPCChangeManagerChangeEvent::Type)request->eventdata().type();
    eventData.mChangedOwnerPinIx = request->eventdata().changedownerpinix();
    eventData.mChangedPinIx = request->eventdata().changedpinix();
    int numIndices = request->eventdata().changedindices_size();
    for (int h = 0; h < numIndices; h++)
    {
        eventData.mChangedIndices.push_back(request->eventdata().changedindices(h));
    }

    // Call the client-side callback function
    CallbackStorage::invokeGRPCChangeObserver(callbackId, eventData, userDataPtr);

    // Indicate that the callback was successfully processed
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::ChangeManagerTimeObserver (
    grpc::ServerContext *                               context,
    const octaneapi::ChangeManagerTimeObserverRequest * request,
    octaneapi::CallbackAck *                            response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    //// Extract button reference
    // 'void GRPCBase::attachObjectHandle(int64_t)': cannot convert 'this' pointer from 'const ApiRootNodeGraphProxy' to 'GRPCBase &'
    octaneapi::ObjectRef rootGraphPtr = request->eventdata().rootgraph();
    ApiRootNodeGraphProxy rootGraphProxy;
    rootGraphProxy.attachObjectHandle(rootGraphPtr.handle());

    GRPCChangeManagerTimeChangeEvent eventData;
    eventData.mRootGraph = &rootGraphProxy;
    eventData.mType = (GRPCChangeManagerTimeChangeEvent::Type)request->eventdata().type();
    // Call the client-side callback function
    CallbackStorage::invokeGRPCChangeTimeObserver(callbackId, eventData, userDataPtr);

    // Indicate that the callback was successfully processed
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::ProjectManagerObserver(
    grpc::ServerContext *                context,
    const octaneapi::ObserverRequest *   request,
    octaneapi::CallbackAck *             response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function/
    CallbackStorage::invokeGRPCProjectManagerObserver(callbackId, userDataPtr);

    // Indicate that the callback was successfully processed
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::SelectionManagerObserver(
    grpc::ServerContext *              context,
    const octaneapi::ObserverRequest * request,
    octaneapi::CallbackAck *           response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function/
    CallbackStorage::invokeGRPCSelectionManagerObserver(callbackId, userDataPtr);

    // Indicate that the callback was successfully processed
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::CommandModuleRunFunc(
    grpc::ServerContext *                          context,
    const octaneapi::CommandModuleRunFuncRequest * request,
    octaneapi::CallbackAck *                       response)
{
    // Extract data from the gRPC request 
    int callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    //request->call
    // Convert `userData` back to a pointer
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function/
    CallbackStorage::invokeCommandModuleRunFunc(callbackId, (void*)userData);

    // Indicate that the callback was successfully processed
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::ObserverCallback(
    grpc::ServerContext *                      context,
    const octaneapi::ObserverCallbackRequest * request,
    octaneapi::CallbackAck *                   response)
{
    // Extract data from the gRPC request
    int callbackId = request->callback_id();
    std::string path = request->path();
    uint64_t userData = request->user_data();
    Octane::ApiLocalDB::UpdateType type = (Octane::ApiLocalDB::UpdateType)request->type();

    // Convert `userData` back to a pointer
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function
    CallbackStorage::invokeObserverCallback(callbackId, (void*)userDataPtr, type, path.c_str());

    // Indicate that the callback was successfully processed
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::DbViewLoaded(
    grpc::ServerContext *                  context,
    const octaneapi::DbViewLoadedRequest * request,
    octaneapi::CallbackAck *               response)
{
    // Extract data from the gRPC request
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    int32_t origin = request->origin();

    // Convert `userData` back to a pointer
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function
    CallbackStorage::invokeDbViewLoadedCallback(callbackId, (void*)userData, static_cast<Octane::ItemDbOrigin>(origin));

    // Indicate that the callback was successfully processed
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::OnNewStatistics(
    grpc::ServerContext *                   context,
    const octaneapi::BasicCallbackRequest * request,
    octaneapi::CallbackAck *                response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function
    CallbackStorage::invokeOnNewStatisticsCallback(callbackId, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::Finish(
    grpc::ServerContext *            context,
    const octaneapi::FinishRequest * request,
    octaneapi::CallbackAck *         response)
{
    // Extract data from the gRPC request
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);
    bool success = request->success();
    std::string errorMsg = request->error_msg();
    std::string sceneGuid = request->scene_guid();
    std::string rootGuid = request->root_guid();
    std::string sceneName = request->scene_name();

    // Call the client-side callback function
    CallbackStorage::invokeFinishCallback(callbackId, success, errorMsg.c_str(), sceneGuid.c_str(), rootGuid.c_str(), sceneName.c_str(), userDataPtr);

    // Indicate success in the response
    response->set_success(true);

    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::OnTileBlended(
    grpc::ServerContext *                   context,
    const octaneapi::BasicCallbackRequest * request,
    octaneapi::CallbackAck *                response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function
    CallbackStorage::invokeOnTileBlendedCallback(callbackId, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::OnNewImage(
    grpc::ServerContext *                context,
    const octaneapi::OnNewImageRequest * request,
    octaneapi::CallbackAck *             response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void *>(userData);

    //// Extract render images
    std::vector<Octane::ApiRenderImage> renderImages;
    for (int i = 0; i < request->render_images().data_size(); ++i)
    {
        const ::octaneapi::ApiRenderImage & image = request->render_images().data(i);
        int imagesize = image.buffer().size();
        const char * imagedata = image.buffer().data().data();
        int imageSizeX = image.size().x();
        int imageSizeY = image.size().y();

        Octane::ApiRenderImage img; 
       
        img.mCalculatedSamplesPerPixel = image.calculatedsamplesperpixel(); 
        img.mType = static_cast<Octane::ImageType>(image.type());
        img.mColorSpace = static_cast<Octane::NamedColorSpace>(image.colorspace());
        img.mIsLinear = image.islinear();
        img.mSize.x = image.size().x();
        img.mSize.y = image.size().y();
        img.mPitch = image.pitch();

        //buffer
        img.mBuffer = nullptr;
        size_t imgSize = img.mSize.x * img.mSize.x * img.mPitch;// image.mbuffer().size();
        if (imgSize > 0)
        {
            img.mBuffer = new char[imgSize];
            memcpy((void*)img.mBuffer, (char*)image.buffer().data().data(), image.buffer().size());
        }
        else
        {
            assert(false);
        }

        img.mTonemappedSamplesPerPixel = image.tonemappedsamplesperpixel();
        img.mCalculatedSamplesPerPixel = image.calculatedsamplesperpixel();
        img.mRegionSamplesPerPixel = image.regionsamplesperpixel();
        img.mMaxSamplesPerPixel = image.maxsamplesperpixel();
        img.mSamplesPerSecond = image.samplespersecond();
        img.mRenderTime = image.rendertime(); 
        img.mChangeLevel = static_cast<Octane::CLevelT>(image.changelevel().value());
        img.mHasPendingUpdates = image.haspendingupdates();
        img.mSubSampling = static_cast<Octane::SubSampleMode>(image.subsampling());
        img.mHasAlpha = image.hasalpha();
        img.mPremultipliedAlphaType = static_cast<Octane::PremultipliedAlphaType>(image.premultipliedalphatype());
        img.mKeepEnvironment = image.keepenvironment();

        renderImages.push_back(img);
    }
    Octane::ApiArray<Octane::ApiRenderImage> images(renderImages.data(), renderImages.size());
    CallbackStorage::invokeOnNewImageCallback(callbackId, images, userDataPtr);

    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::OnOcioError(
    grpc::ServerContext *                 context,
    const octaneapi::OnOcioErrorRequest * request,
    octaneapi::CallbackAck *              response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Extract has_error flag
    bool hasError = request->has_error();

    // Extract error messages
    std::vector<const char*> messages;
    for (const auto& msg : request->messages())
    {
        messages.push_back(msg.c_str());
    }
    StringArrayT strArray(messages.data(), messages.size());
    // Call the client-side callback function
    CallbackStorage::invokeOnOcioErrorCallback(callbackId, strArray, hasError, userDataPtr);
    // clientOnOcioErrorCallback(messages, hasError, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::OnRenderFailure(
    grpc::ServerContext *                   context,
    const octaneapi::BasicCallbackRequest * request,
    octaneapi::CallbackAck *                response)
{ 
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function
    // clientOnRenderFailureCallback(userDataPtr);
    CallbackStorage::invokeOnRenderFailureCallback(callbackId, userDataPtr);
    // Indicate success in the response
    response->set_success(true);
    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::NextChunk(
    grpc::ServerContext *               context,
    const octaneapi::NextChunkRequest * request,
    octaneapi::NextChunkResponse *      response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Declare variables for returned chunk size and data
    unsigned char* dataChunk = nullptr;

    size_t chunkSize = CallbackStorage::invokeNextChunkCallback(callbackId, userDataPtr, dataChunk);
    // Set the chunk size
    response->set_chunk_size(chunkSize);

    // Copy binary chunk data into gRPC response
    response->set_data_chunk(dataChunk, chunkSize);

    // Free the dataChunk buffer if client allocated it (depends on how data is managed)
    delete[] dataChunk;

    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::Checked(
    grpc::ServerContext * context,
    const octaneapi::CheckedRequest * request,
    octaneapi::CallbackAck * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    //// Extract button reference
    octaneapi::ObjectRef buttonPtr = request->button();
    ApiCheckBoxProxy checkBox;
    checkBox.attachObjectHandle(buttonPtr.handle());

    //// Call the client-side callback function 
    CallbackStorage::invokeGRPCCheckedCallback(callbackId, checkBox, userDataPtr);
    // Indicate success in the response
    response->set_success(true);
    return grpc::Status::OK;
};


grpc::Status CallbackHandlerImpl::ComboBoxChanged(
    grpc::ServerContext * context,
    const octaneapi::ComboBoxChangedRequest * request,
    octaneapi::CallbackAck * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void* userDataPtr = reinterpret_cast<void*>(userData);

    //// Extract combo box reference
    octaneapi::ObjectRef comboBoxPtr = request->combo_box();
    ApiComboBoxProxy comboBox;
    comboBox.attachObjectHandle(comboBoxPtr.handle());

    //// Call the client-side callback function
    CallbackStorage::invokeGRPCComboBoxChangedCallback(callbackId, comboBox, userDataPtr);
    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
};


grpc::Status CallbackHandlerImpl::ApiLog(
    grpc::ServerContext * context,
    const octaneapi::ApiLogRequest * request,
    octaneapi::CallbackAck * response)
{
    // Extract log type and message
    int32_t callbackId = request->callback_id();
    int logType = request->log_type();
    std::string message = request->message();

    // Call the client-side callback function
    // clientApiLogCallback(logType, message.c_str());
    CallbackStorage::invokeApiLogCallback(callbackId, (Octane::ApiLogManager::LogMessageType)logType, message.c_str());

    // Indicate success in the response
    response->set_success(true);
    return grpc::Status::OK;
};


grpc::Status CallbackHandlerImpl::OnMainWindowClose(
    grpc::ServerContext * context,
    const octaneapi::BasicCallbackRequest * request,
    octaneapi::CallbackAck * response)
{ 

    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function
    CallbackStorage::invokeOnMainWindowCloseCallback(callbackId, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc::Status::OK;
};


grpc::Status CallbackHandlerImpl::MouseEvent(
    grpc::ServerContext * context,
    const octaneapi::MouseEventRequest * request,
    octaneapi::CallbackAck * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Extract event type
    int eventType = request->event_type();

    const auto & grpcEvent = request->event();

    GRPCApiMouseEventData eventData;
    eventData.mMouseDownPosX = grpcEvent.mousedownposx();
    eventData.mMouseDownPosY = grpcEvent.mousedownposy();
    eventData.mNumberOfClicks = grpcEvent.numberofclicks();
    eventData.mPositionX = grpcEvent.positionx();
    eventData.mPositionY = grpcEvent.positiony();
    eventData.mEventComponent = new ApiGuiComponentProxy();
    eventData.mEventComponent->attachObjectHandle(grpcEvent.eventcomponent().handle());
    eventData.mOriginator = new ApiGuiComponentProxy();
    eventData.mOriginator->attachObjectHandle(grpcEvent.originator().handle());
    //mouseEvent.mEventComponent
    //event.setX(grpcEvent.x());
    //event.setY(grpcEvent.y());
    //event.setButton(grpcEvent.button());
    //event.setState(grpcEvent.state());

    //// Extract mouse wheel details
    const auto & grpcWheelDetails = request->wheel_details();
    Octane::ApiMouseWheelDetails wheelDetails;
    wheelDetails.mDeltaX = grpcWheelDetails.deltax();
    wheelDetails.mDeltaY = grpcWheelDetails.deltay();
    wheelDetails.mIsInertial = grpcWheelDetails.isinertial();
    wheelDetails.mIsReversed = grpcWheelDetails.isreversed();
    wheelDetails.mIsSmooth = grpcWheelDetails.issmooth();

    // Call the client-side callback function
    CallbackStorage::invokeGRPCMouseEventCallback(callbackId, static_cast<Octane::ApiMouseEventType>(eventType), eventData, wheelDetails, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc::Status::OK;
};


grpc::Status CallbackHandlerImpl::DbViewClosing(
    grpc::ServerContext * context,
    const octaneapi::BasicCallbackRequest * request,
    octaneapi::CallbackAck * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function
    // clientDbViewClosingCallback(userDataPtr);
    CallbackStorage::invokeDbViewClosingCallback(callbackId, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
};


grpc::Status CallbackHandlerImpl::NumericBoxChanged(
    grpc::ServerContext * context,
    const octaneapi::NumericBoxChangedRequest * request,
    octaneapi::CallbackAck * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Extract numeric box reference
    octaneapi::ObjectRef numericBoxPtr = request->numeric_box();
    ApiNumericBoxProxy numericBox;
    numericBox.attachObjectHandle(numericBoxPtr.handle());

    // Call the client-side callback function
    CallbackStorage::invokeGRPCNumericBoxChangedCallback(callbackId, numericBox, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
};


grpc::Status CallbackHandlerImpl::Callback1(
    grpc::ServerContext *               context,
    const octaneapi::Callback1Request * request,
    octaneapi::CallbackAck *            response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Extract loading flag
    bool loading = request->loading();

    //// Extract configuration reference
    //ObjectRef configPtr = request->config(); 
    octaneapi::ObjectRef ocioConfigPtr = request->config();
    ApiOcioConfigProxy ocioConfig;
    ocioConfig.attachObjectHandle(ocioConfigPtr.handle());

    //// Call the client-side callback function
    CallbackStorage::invokeGRPCCallback1(callbackId, loading, &ocioConfig, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
};


grpc::Status CallbackHandlerImpl::Callback2(
    grpc::ServerContext * context,
    const octaneapi::Callback2Request * request,
    octaneapi::CallbackAck * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Extract configuration reference
    octaneapi::ObjectRef ocioConfigPtr = request->config();
    ApiOcioConfigProxy ocioConfig;
    ocioConfig.attachObjectHandle(ocioConfigPtr.handle());

    // Extract context usability flag
    bool contextUsable = request->context_usable();

    // Call the client-side callback function 
    CallbackStorage::invokeGRPCCallback2(callbackId, &ocioConfig, contextUsable, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::ApiProjectManager_AssetMissing(
    grpc::ServerContext * context,
    const octaneapi::AssetMissingRequest * request,
    octaneapi::AssetMissingResponse * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Extract file name
    std::string fileName = request->file_name();

    // Call the client-side callback function to get the resolved file path
    const char * resolvedPath = CallbackStorage::invokeApiProjectManager_AssetMissingCallback(callbackId, fileName.c_str(), userDataPtr);

    // Set the response with the resolved file path
    if (resolvedPath)
    {
        response->set_resolved_file_path(resolvedPath);
    }
    else
    {
        response->set_resolved_file_path("");  // Return an empty string if no path is found
    }
    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::NumRows(
    grpc::ServerContext * context,
    const octaneapi::BasicCallbackRequest * request,
    octaneapi::NumRowsResponse * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Call the client-side callback function to get the row count
    int numRows = CallbackStorage::invokeNumRowsCallback(callbackId, userDataPtr);

    // Set the response with the number of rows
    response->set_num_rows(numRows);

    return grpc::Status::OK;
}


grpc::Status CallbackHandlerImpl::Content(
    grpc::ServerContext *             context,
    const octaneapi::ContentRequest * request,
    octaneapi::ContentResponse *      response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void* userDataPtr = reinterpret_cast<void*>(userData);

    // Extract row and column values
    int row = request->row();
    int column = request->column();

    // Call the client-side callback function to retrieve the content
    const char * content = CallbackStorage::invokeContentCallback(callbackId, row, column, userDataPtr);

    // Set the response with the retrieved content
    if (content)
    {
        response->set_content(content);
    }
    else
    {
        response->set_content("");  // Return an empty string if content is not found
    }
    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::ButtonClicked(
    grpc::ServerContext * context,
    const octaneapi::ButtonClickedRequest * request,
    octaneapi::CallbackAck * response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t  userData = request->user_data();
    void*  userDataPtr = reinterpret_cast<void*>(userData);

    // Extract button reference
    octaneapi::ObjectRef buttonPtr = request->text_button();
    ApiTextButtonProxy textBtn;
    textBtn.attachObjectHandle(buttonPtr.handle());

    // Call the client-side callback function
    CallbackStorage::invokeGRPCButtonClickedCallback(callbackId, textBtn, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::SelectionChanged(
    grpc::ServerContext *                      context,
    const octaneapi::SelectionChangedRequest * request,
    octaneapi::CallbackAck *                   response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t  userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Extract last selected row
    int lastRowSelected = request->last_row_selected();

    // Call the client-side callback function
    CallbackStorage::invokeSelectionChangedCallback(callbackId, lastRowSelected, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::TextEditorChanged(
    grpc::ServerContext *                       context,
    const octaneapi::TextEditorChangedRequest * request,
    octaneapi::CallbackAck *                    response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Extract text editor reference
    octaneapi::ObjectRef textEditorPtr = request->text_edit();
    ApiTextEditorProxy textEdit;
    textEdit.attachObjectHandle(textEditorPtr.handle());

    // Call the client-side callback function
    CallbackStorage::invokeGRPCTextEditorChangedCallback(callbackId, textEdit, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
}


grpc::Status CallbackHandlerImpl::OnWindowClose(
    grpc::ServerContext *                   context,
    const octaneapi::OnWindowCloseRequest * request,
    octaneapi::CallbackAck *                response)
{
    // Extract user_data
    int32_t callbackId = request->callback_id();
    uint64_t  userData = request->user_data();
    void * userDataPtr = reinterpret_cast<void*>(userData);

    // Extract window reference 
    octaneapi::ObjectRef windowPtr = request->window();
    ApiWindowProxy wnd;
    wnd.attachObjectHandle(windowPtr.handle());

    // Call the client-side callback function
    CallbackStorage::invokeGRPCOnWindowCloseCallback(callbackId, wnd, userDataPtr);

    // Indicate success in the response
    response->set_success(true);
    return grpc:: Status::OK;
}

} // namespace OctaneGRPC