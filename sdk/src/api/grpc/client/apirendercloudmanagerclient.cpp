// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apirendercloudmanagerclient.h"
#include <cassert>
#include <stdexcept>
#include "octanerenderpasses.h"
#include "octaneimageexport.h"
#include "octaneinfos.h"
#include "octaneids.h"
#include "octanenet.h"
#include "octanemodulesinfo.h"
#include "octanereferenceexport.h"
#include <grpcpp/grpcpp.h>
#include "apirendercloudmanager.grpc.pb.h"
#include "apirootnodegraphclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapirendercloudmanager_apirendercloudmanager_subscriptioninfo.h"


namespace OctaneGRPC
{


GRPCSettings & ApiRenderCloudManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiRenderCloudManagerProxy::userSubscriptionInfo(
            Octane::ApiRenderCloudManager::SubscriptionInfo & subscriptionInfo
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderCloudManager::userSubscriptionInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderCloudManager::userSubscriptionInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderCloudManagerService::Stub> stub =
        octaneapi::ApiRenderCloudManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->userSubscriptionInfo(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'subscriptionInfo' [out] parameter from the gRPC response packet
        octaneapi::ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfo subscriptionInfoOut = response.subscriptioninfo();
        ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfoConverter::convert(subscriptionInfoOut, subscriptionInfo);
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


void ApiRenderCloudManagerProxy::uploadCurrentProject(
            const Octane::ApiRenderCloudManager::GuidT rootGuid,
            Octane::ApiRenderCloudManager::UpdateCallbackT onUpdate,
            Octane::ApiRenderCloudManager::FinishCallbackT onFinish,
            void *                                    callbackData
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderCloudManager::uploadCurrentProjectRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'rootGuid' [in] parameter to the request packet.
    octaneapi::GuidT * rootguidIn = new octaneapi::GuidT();
    rootguidIn->set_guid(std::string(rootGuid));
    request.set_allocated_rootguid(rootguidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'onUpdate' [in] parameter to the request packet.
    octaneapi::UpdateCallbackT * onupdateIn = new octaneapi::UpdateCallbackT();
    // setup callback function onUpdate
        onupdateIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_onupdate(onupdateIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'onFinish' [in] parameter to the request packet.
    octaneapi::FinishCallbackT * onfinishIn = new octaneapi::FinishCallbackT();
    // setup callback function onFinish
        onfinishIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_onfinish(onfinishIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callbackData' [in] parameter to the request packet.
    uint64_t callbackdataIn;
    callbackdataIn = reinterpret_cast<uint64_t>(callbackData);
    request.set_callbackdata(callbackdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderCloudManager::uploadCurrentProjectResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderCloudManagerService::Stub> stub =
        octaneapi::ApiRenderCloudManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->uploadCurrentProject(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerUpdateCallback( response.callbackid(), onUpdate);
        CallbackStorage::registerUpdateCallback( response.callbackid(), onUpdate);
        // set callback Id CallbackStorage::registerFinishCallback( response.callbackid2(), onFinish);
        CallbackStorage::registerFinishCallback( response.callbackid2(), onFinish);
        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId2' [out] parameter from the gRPC response packet
        int32_t callbackId2Out = response.callbackid2();
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
};


void ApiRenderCloudManagerProxy::uploadRootNodeGraph(
            const ApiRootNodeGraphProxy &             rootNodeGraph,
            const Octane::ApiRenderCloudManager::GuidT rootGuid,
            Octane::ApiRenderCloudManager::UpdateCallbackT onUpdate,
            Octane::ApiRenderCloudManager::FinishCallbackT onFinish,
            void *                                    callbackData
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderCloudManager::uploadRootNodeGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'rootNodeGraph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * rootnodegraphIn = new octaneapi::ObjectRef();
    rootnodegraphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);
    rootnodegraphIn->set_handle(rootNodeGraph.getObjectHandle());
    request.set_allocated_rootnodegraph(rootnodegraphIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rootGuid' [in] parameter to the request packet.
    octaneapi::GuidT * rootguidIn = new octaneapi::GuidT();
    rootguidIn->set_guid(std::string(rootGuid));
    request.set_allocated_rootguid(rootguidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'onUpdate' [in] parameter to the request packet.
    octaneapi::UpdateCallbackT * onupdateIn = new octaneapi::UpdateCallbackT();
    // setup callback function onUpdate
        onupdateIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_onupdate(onupdateIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'onFinish' [in] parameter to the request packet.
    octaneapi::FinishCallbackT * onfinishIn = new octaneapi::FinishCallbackT();
    // setup callback function onFinish
        onfinishIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_onfinish(onfinishIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callbackData' [in] parameter to the request packet.
    uint64_t callbackdataIn;
    callbackdataIn = reinterpret_cast<uint64_t>(callbackData);
    request.set_callbackdata(callbackdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderCloudManager::uploadRootNodeGraphResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderCloudManagerService::Stub> stub =
        octaneapi::ApiRenderCloudManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->uploadRootNodeGraph(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerUpdateCallback( response.callbackid(), onUpdate);
        CallbackStorage::registerUpdateCallback( response.callbackid(), onUpdate);
        // set callback Id CallbackStorage::registerFinishCallback( response.callbackid2(), onFinish);
        CallbackStorage::registerFinishCallback( response.callbackid2(), onFinish);
        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId2' [out] parameter from the gRPC response packet
        int32_t callbackId2Out = response.callbackid2();
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
};


bool ApiRenderCloudManagerProxy::newRenderTask(
            const Octane::ApiRenderCloudManager::GuidT sceneGuid
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderCloudManager::newRenderTaskRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'sceneGuid' [in] parameter to the request packet.
    octaneapi::GuidT * sceneguidIn = new octaneapi::GuidT();
    sceneguidIn->set_guid(std::string(sceneGuid));
    request.set_allocated_sceneguid(sceneguidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderCloudManager::newRenderTaskResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderCloudManagerService::Stub> stub =
        octaneapi::ApiRenderCloudManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->newRenderTask(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


} //end of namespace
