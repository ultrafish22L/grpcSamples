// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apichangemanagerclient.h"
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
#include "apichangemanager.grpc.pb.h"
#include "apirootnodegraphclient.h"
#include "apiitemclient.h"
#include "grpcchangeevents.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiChangeManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiChangeManagerProxy::observeApiItem(
            const ApiItemProxy &                      item,
            GRPCChangeObserver                       observer,
            const int                                 eventMask
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::observeApiItemRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'item' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    itemIn->set_handle(item.getObjectHandle());
    request.set_allocated_item(itemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCChangeObserverT * observerIn = new octaneapi::GRPCChangeObserverT();
    // setup observer function observer
    //int observerCallbackId = GRPCSettings::getNextCallbackId("GRPCChangeObserver");
    //CallbackStorage::registerGRPCChangeObserver(observerCallbackId, observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //observerIn->set_callbackid(observerCallbackId);
    observerIn->set_userdata(reinterpret_cast<uint64_t>(observer.mUserData));
    //if(className == "ApiChangeManager" && method.mName == "observeApiItem") return true;
    request.set_allocated_observer(observerIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'eventMask' [in] parameter to the request packet.
    int32_t eventmaskIn;
    eventmaskIn = eventMask;
    request.set_eventmask(eventmaskIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiChangeManager::observeApiItemResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->observeApiItem(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCChangeObserver( response.callbackid(), observer.mCallback);
        CallbackStorage::registerGRPCChangeObserver( response.callbackid(), observer.mCallback);
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


void ApiChangeManagerProxy::stopObserving(
            const ApiItemProxy &                      item,
            GRPCChangeObserver                       observer
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::stopObservingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'item' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    itemIn->set_handle(item.getObjectHandle());
    request.set_allocated_item(itemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCChangeObserverT * observerIn = new octaneapi::GRPCChangeObserverT();
    // remove observer function observer
    int observerCallbackId = CallbackStorage::unregisterGRPCChangeObserver(observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    observerIn->set_callbackid(observerCallbackId);
    request.set_allocated_observer(observerIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->stopObserving(context.get(), request, &response);

    if (status.ok())
    {
        // free callbackId
        // GRPCSettings::releaseCallbackId("GRPCChangeObserver", response.callbackid());
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


void ApiChangeManagerProxy::stopObserving(
            GRPCChangeObserver                       observer
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::stopObserving1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCChangeObserverT * observerIn = new octaneapi::GRPCChangeObserverT();
    // remove observer function observer
    int observerCallbackId = CallbackStorage::unregisterGRPCChangeObserver(observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    observerIn->set_callbackid(observerCallbackId);
    request.set_allocated_observer(observerIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->stopObserving1(context.get(), request, &response);

    if (status.ok())
    {
        // free callbackId
        // GRPCSettings::releaseCallbackId("GRPCChangeObserver", response.callbackid());
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


void ApiChangeManagerProxy::stopObserving()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::stopObserving2Request request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->stopObserving2(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiChangeManagerProxy::update()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::updateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->update(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiChangeManagerProxy::addTimeObserver(
            GRPCChangeTimeObserver                   observer,
            const ApiRootNodeGraphProxy &             rootNodeGraph
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::addTimeObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCChangeTimeObserverT * observerIn = new octaneapi::GRPCChangeTimeObserverT();
    // setup observer function observer
    //int observerCallbackId = GRPCSettings::getNextCallbackId("GRPCChangeTimeObserver");
    //CallbackStorage::registerGRPCChangeTimeObserver(observerCallbackId, observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //observerIn->set_callbackid(observerCallbackId);
    observerIn->set_userdata(reinterpret_cast<uint64_t>(observer.mUserData));
    //if(className == "ApiChangeManager" && method.mName == "addTimeObserver") return true;
    request.set_allocated_observer(observerIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rootNodeGraph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * rootnodegraphIn = new octaneapi::ObjectRef();
    rootnodegraphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);
    rootnodegraphIn->set_handle(rootNodeGraph.getObjectHandle());
    request.set_allocated_rootnodegraph(rootnodegraphIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiChangeManager::addTimeObserverResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->addTimeObserver(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCChangeTimeObserver( response.callbackid(), observer.mCallback);
        CallbackStorage::registerGRPCChangeTimeObserver( response.callbackid(), observer.mCallback);
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


void ApiChangeManagerProxy::removeTimeObserver(
            GRPCChangeTimeObserver                   observer,
            const ApiRootNodeGraphProxy *             rootNodeGraph
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::removeTimeObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCChangeTimeObserverT * observerIn = new octaneapi::GRPCChangeTimeObserverT();
    // remove observer function observer
    int observerCallbackId = CallbackStorage::unregisterGRPCChangeTimeObserver(observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    observerIn->set_callbackid(observerCallbackId);
    request.set_allocated_observer(observerIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rootNodeGraph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * rootnodegraphIn = new octaneapi::ObjectRef();
    rootnodegraphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);
    rootnodegraphIn->set_handle(rootNodeGraph->getObjectHandle());
    request.set_allocated_rootnodegraph(rootnodegraphIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeTimeObserver(context.get(), request, &response);

    if (status.ok())
    {
        // free callbackId
        // GRPCSettings::releaseCallbackId("GRPCChangeTimeObserver", response.callbackid());
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


void ApiChangeManagerProxy::stopObservingTime()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiChangeManager::stopObservingTimeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiChangeManagerService::Stub> stub =
        octaneapi::ApiChangeManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->stopObservingTime(context.get(), request, &response);

    if (status.ok())
    {
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


