// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apinodegrapheditorclient.h"
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
#include "apinodegrapheditor.grpc.pb.h"
#include "apinodegraphclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiNodeGraphEditorProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiNodeGraphEditorProxy ApiNodeGraphEditorProxy::create(
            const ApiNodeGraphProxy *                 content,
            const bool                                unfold,
            void *                                    privateData
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphEditor::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'content' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * contentIn = new octaneapi::ObjectRef();
    contentIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);
    contentIn->set_handle(content->getObjectHandle());
    request.set_allocated_content(contentIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'unfold' [in] parameter to the request packet.
    bool unfoldIn;
    unfoldIn = unfold;
    request.set_unfold(unfoldIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'privateData' [in] parameter to the request packet.
    uint64_t privatedataIn;
    privatedataIn = reinterpret_cast<uint64_t>(privateData);
    request.set_privatedata(privatedataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraphEditor::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphEditorService::Stub> stub =
        octaneapi::ApiNodeGraphEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeGraphEditorProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());
        return retVal;
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
        ApiNodeGraphEditorProxy retVal;
        return retVal;
    }
};


void ApiNodeGraphEditorProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphEditor::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphEditor);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphEditorService::Stub> stub =
        octaneapi::ApiNodeGraphEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->destroy(context.get(), request, &response);

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


void ApiNodeGraphEditorProxy::setContentGraph(
            const ApiNodeGraphProxy *const            graph
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphEditor::setContentGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphEditor);
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
    std::unique_ptr<octaneapi::ApiNodeGraphEditorService::Stub> stub =
        octaneapi::ApiNodeGraphEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->setContentGraph(context.get(), request, &response);

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


void ApiNodeGraphEditorProxy::addGraph(
            const ApiNodeGraphProxy *const            graph
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphEditor::addGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphEditor);
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
    std::unique_ptr<octaneapi::ApiNodeGraphEditorService::Stub> stub =
        octaneapi::ApiNodeGraphEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->addGraph(context.get(), request, &response);

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


