// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apimainwindowclient.h"
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
#include "apimainwindow.grpc.pb.h"
#include "apinodegraphclient.h"
#include "apiprojectworkspaceclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiMainWindowProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiMainWindowProxy ApiMainWindowProxy::fetchOrCreateInstance(
            Octane::ApiMainWindow::OnMainWindowCloseCallbackT callback,
            void *const                               callbackPrivateData
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::fetchOrCreateInstanceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::OnMainWindowCloseCallbackT * callbackIn = new octaneapi::OnMainWindowCloseCallbackT();
    // setup callback function callback
        callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_callback(callbackIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callbackPrivateData' [in] parameter to the request packet.
    uint64_t callbackprivatedataIn;
    callbackprivatedataIn = reinterpret_cast<uint64_t>(callbackPrivateData);
    request.set_callbackprivatedata(callbackprivatedataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMainWindow::fetchOrCreateInstanceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->fetchOrCreateInstance(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnMainWindowCloseCallback( response.callbackid(), callback);
        CallbackStorage::registerOnMainWindowCloseCallback( response.callbackid(), callback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiMainWindowProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
        return retVal;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
        ApiMainWindowProxy retVal;
        return retVal;
    }
};


void ApiMainWindowProxy::runDispatchLoopUntil(
            const int                                 millis
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::runDispatchLoopUntilRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'millis' [in] parameter to the request packet.
    int32_t millisIn;
    millisIn = millis;
    request.set_millis(millisIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->runDispatchLoopUntil(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


void ApiMainWindowProxy::setDpi(
            const uint32_t                            dpi
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::setDpiRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dpi' [in] parameter to the request packet.
    uint32_t dpiIn;
    dpiIn = dpi;
    request.set_dpi(dpiIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->setDpi(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


void ApiMainWindowProxy::addContentComponent(
            ApiGuiComponentProxy &                    contentComponent
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::addContentComponentRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMainWindow);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'contentComponent' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * contentcomponentIn = new octaneapi::ObjectRef();
    contentcomponentIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    contentcomponentIn->set_handle(contentComponent.getObjectHandle());
    request.set_allocated_contentcomponent(contentcomponentIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->addContentComponent(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


ApiProjectWorkspaceProxy ApiMainWindowProxy::projectWorkspace() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::projectWorkspaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMainWindow);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMainWindow::projectWorkspaceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->projectWorkspace(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiProjectWorkspaceProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());
        return retVal;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
        ApiProjectWorkspaceProxy retVal;
        return retVal;
    }
};


ApiProjectWorkspaceProxy ApiMainWindowProxy::projectWorkspace()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::projectWorkspace1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMainWindow);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMainWindow::projectWorkspace1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->projectWorkspace1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiProjectWorkspaceProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());
        return retVal;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
        ApiProjectWorkspaceProxy retVal;
        return retVal;
    }
};


void ApiMainWindowProxy::show(
            bool                                      maximized
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::showRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMainWindow);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'maximized' [in] parameter to the request packet.
    bool maximizedIn;
    maximizedIn = maximized;
    request.set_maximized(maximizedIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->show(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


void ApiMainWindowProxy::hide()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::hideRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMainWindow);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->hide(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


bool ApiMainWindowProxy::visible() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::visibleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMainWindow);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMainWindow::visibleResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->visible(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
    return retVal;
};


void ApiMainWindowProxy::setDefaultGraph(
            ApiNodeGraphProxy *                       graph
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::setDefaultGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMainWindow);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'graph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * graphIn = new octaneapi::ObjectRef();
    graphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);
    graphIn->set_handle(graph->getObjectHandle());
    request.set_allocated_graph(graphIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->setDefaultGraph(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


ApiNodeGraphProxy ApiMainWindowProxy::defaultGraph() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMainWindow::defaultGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMainWindow);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMainWindow::defaultGraphResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMainWindowService::Stub> stub =
        octaneapi::ApiMainWindowService::NewStub(getGRPCSettings().getChannel());
    status = stub->defaultGraph(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeGraphProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());
        return retVal;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
        ApiNodeGraphProxy retVal;
        return retVal;
    }
};


} //end of namespace
