// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apinodegraphclient.h"
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
#include "apinodesystem_1.grpc.pb.h"
#include "apinodesystem_2.grpc.pb.h"
#include "apinodesystem_3.grpc.pb.h"
#include "apinodesystem_4.grpc.pb.h"
#include "apinodesystem_5.grpc.pb.h"
#include "apinodesystem_6.grpc.pb.h"
#include "apinodesystem_7.grpc.pb.h"
#include "apinodesystem_8.grpc.pb.h"
#include "apiitemclient.h"
#include "apinodeclient.h"
#include "apinodearrayclient.h"
#include "apiitemarrayclient.h"
#include "apianimationtimetransformclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapinodegraphinfo.h"


GRPCSettings & ApiNodeGraphProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiNodeGraphProxy ApiNodeGraphProxy::create(
            const Octane::NodeGraphType               type, //// test821 //// 
            ApiNodeGraphProxy &                       ownerGraph //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeGraphType typeIn;
    typeIn = static_cast<octaneapi::NodeGraphType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ownerGraph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * ownergraphIn = new octaneapi::ObjectRef();////761////
    ownergraphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    ownergraphIn->set_handle(ownerGraph.getObjectHandle());
    request.set_allocated_ownergraph(ownergraphIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->create1(context.get(), request, &response);

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
        ApiNodeGraphProxy retVal;////714////
        return retVal;
    }
};


const Octane::ApiNodeGraphInfo ApiNodeGraphProxy::info() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::infoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::infoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->info1(context.get(), request, &response);

    Octane::ApiNodeGraphInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiNodeGraphInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiNodeGraphInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiNodeGraphInfo;////
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


Octane::NodeGraphType ApiNodeGraphProxy::type() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::typeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::typeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->type1(context.get(), request, &response);

    Octane::NodeGraphType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NodeGraphType resultOut = response.result();
        retVal = static_cast<Octane::NodeGraphType>(resultOut);
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


void ApiNodeGraphProxy::getOwnedItems(
            ApiItemArrayProxy &                       list //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::getOwnedItemsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::getOwnedItemsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getOwnedItems(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'list' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef listOut = response.list();
        list.attachObjectHandle(listOut.handle());////test 80////
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


void ApiNodeGraphProxy::getInputNodes(
            ApiNodeArrayProxy &                       list //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::getInputNodesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::getInputNodesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputNodes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'list' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef listOut = response.list();
        list.attachObjectHandle(listOut.handle());////test 80////
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


void ApiNodeGraphProxy::getOutputNodes(
            ApiNodeArrayProxy &                       list //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::getOutputNodesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::getOutputNodesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getOutputNodes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'list' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef listOut = response.list();
        list.attachObjectHandle(listOut.handle());////test 80////
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


void ApiNodeGraphProxy::findNodes(
            const Octane::NodeType                    type, //// test821 //// 
            ApiNodeArrayProxy &                       list, //// test821 //// 
            const bool                                recurse //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::findNodesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
    typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'recurse' [in] parameter to the request packet.
    bool recurseIn;
    recurseIn = recurse;////2 const bool////
    request.set_recurse(recurseIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::findNodesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->findNodes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'list' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef listOut = response.list();
        list.attachObjectHandle(listOut.handle());////test 80////
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


ApiNodeProxy ApiNodeGraphProxy::findFirstNode(
            const Octane::NodeType                    type //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::findFirstNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
    typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::findFirstNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->findFirstNode(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeProxy retVal;
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
        ApiNodeProxy retVal;////714////
        return retVal;
    }
};


ApiNodeProxy ApiNodeGraphProxy::findFirstOutputNode(
            const Octane::NodePinType                 pinType //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::findFirstOutputNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinType' [in] parameter to the request packet.
    octaneapi::NodePinType pintypeIn;
    pintypeIn = static_cast<octaneapi::NodePinType>(pinType);
    request.set_pintype(pintypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::findFirstOutputNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->findFirstOutputNode(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeProxy retVal;
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
        ApiNodeProxy retVal;////714////
        return retVal;
    }
};


void ApiNodeGraphProxy::findItemsByName(
            const char *                              name, //// test821 //// 
            ApiItemArrayProxy &                       list, //// test821 //// 
            const bool                                recurse //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::findItemsByNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string(); //// name type=string;//// ////721////
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'recurse' [in] parameter to the request packet.
    bool recurseIn;
    recurseIn = recurse;////2 const bool////
    request.set_recurse(recurseIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::findItemsByNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->findItemsByName(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'list' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef listOut = response.list();
        list.attachObjectHandle(listOut.handle());////test 80////
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


void ApiNodeGraphProxy::setLinearTimeTransform(
            const float                               delay, //// test821 //// 
            const float                               speedUp, //// test821 //// 
            const Octane::TimeSpanT                   customInterval //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::setLinearTimeTransformRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'delay' [in] parameter to the request packet.
    float delayIn;
    delayIn = delay;////2 const float////
    request.set_delay(delayIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'speedUp' [in] parameter to the request packet.
    float speedupIn;
    speedupIn = speedUp;////2 const float////
    request.set_speedup(speedupIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'customInterval' [in] parameter to the request packet.
    octaneapi::TimeSpanT * customintervalIn = new octaneapi::TimeSpanT(); //// customInterval type=TimeSpanT;//// ////721////
    //// TimeSpanT TEST////
    customintervalIn->mutable_begin()->set_value(static_cast<float>(customInterval.begin));
    customintervalIn->mutable_end()->set_value(static_cast<float>(customInterval.end));
    request.set_allocated_custominterval(customintervalIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setLinearTimeTransform(context.get(), request, &response);

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


ApiAnimationTimeTransformProxy ApiNodeGraphProxy::timeTransform() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::timeTransformRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::timeTransformResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->timeTransform(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiAnimationTimeTransformProxy retVal;
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
        ApiAnimationTimeTransformProxy retVal;////714////
        return retVal;
    }
};


void ApiNodeGraphProxy::clearTimeTransform()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::clearTimeTransformRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearTimeTransform(context.get(), request, &response);

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


std::vector<std::string> ApiNodeGraphProxy::getAssetPaths()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::getAssetPathsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::getAssetPathsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAssetPaths(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::StringArrayT resultOut = response.result();
        std::vector<std::string> retVal;////218////
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            //// param.mProtoCppType = StringArrayT param.mType = Octane::StringArrayT ////
            retVal.push_back(resultOut.data(i));
        }
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
        return {};
    }
};


void ApiNodeGraphProxy::recenter(
            const OctaneVec::float_2                  center //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::recenterRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'center' [in] parameter to the request packet.
    octaneapi::float_2 * centerIn = new octaneapi::float_2(); //// center type=float_2;//// ////721////
    (*centerIn).set_x(center.x);
    (*centerIn).set_y(center.y);
    request.set_allocated_center(centerIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->recenter(context.get(), request, &response);

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


void ApiNodeGraphProxy::clear()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::clearRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->clear(context.get(), request, &response);

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


void ApiNodeGraphProxy::copyFrom(
            const ApiNodeGraphProxy &                 source, //// test821 //// 
            const ApiItemProxy *const *               origItems, //// test821 //// 
            const size_t                              origItemCount, //// test821 //// 
            ApiItemArrayProxy *                       copiedItems //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::copyFromRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'source' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourceIn = new octaneapi::ObjectRef();////761////
    sourceIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    sourceIn->set_handle(source.getObjectHandle());
    request.set_allocated_source(sourceIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'origItems' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * origitemsIn = new octaneapi::ObjectRefArrayT(); //// origItems type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = const Octane::ApiItem *const * ////
    for (size_t h = 0; h < origItemCount; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = origitemsIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////4////
         item->set_handle(origItems[h]->getObjectHandle());
    }
    request.set_allocated_origitems(origitemsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'origItemCount' [in] parameter to the request packet.
    uint32_t origitemcountIn;
    origitemcountIn = static_cast<uint32_t>(origItemCount);////2 const size_t////
    request.set_origitemcount(origitemcountIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::copyFromResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyFrom1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'copiedItems' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef copiedItemsOut = response.copieditems();
        copiedItems->attachObjectHandle(copiedItemsOut.handle());////test 79b////
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


ApiItemProxy ApiNodeGraphProxy::copyFrom(
            const ApiItemProxy &                      sourceItem //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::copyFrom1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourceitemIn = new octaneapi::ObjectRef();////761////
    sourceitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////5////
    sourceitemIn->set_handle(sourceItem.getObjectHandle());
    request.set_allocated_sourceitem(sourceitemIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::copyFrom1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyFrom11(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiItemProxy retVal;
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
        ApiItemProxy retVal;////714////
        return retVal;
    }
};


ApiItemProxy ApiNodeGraphProxy::copyItemTree(
            const ApiItemProxy &                      rootItem //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::copyItemTreeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rootItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * rootitemIn = new octaneapi::ObjectRef();////761////
    rootitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////5////
    rootitemIn->set_handle(rootItem.getObjectHandle());
    request.set_allocated_rootitem(rootitemIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::copyItemTreeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyItemTree(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiItemProxy retVal;
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
        ApiItemProxy retVal;////714////
        return retVal;
    }
};


void ApiNodeGraphProxy::copyFrom(
            const ApiItemProxy *const *               sourceItems, //// test821 //// 
            const size_t                              sourceItemsCount, //// test821 //// 
            ApiItemArrayProxy *                       sourceItemCopies, //// test821 //// 
            const ApiItemProxy *const *               origItems, //// test821 //// 
            const size_t                              origItemsCount, //// test821 //// 
            ApiItemArrayProxy *                       origItemCopies //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::copyFrom2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceItems' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * sourceitemsIn = new octaneapi::ObjectRefArrayT(); //// sourceItems type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = const Octane::ApiItem *const * ////
    for (size_t h = 0; h < sourceItemsCount; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = sourceitemsIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////4////
         item->set_handle(sourceItems[h]->getObjectHandle());
    }
    request.set_allocated_sourceitems(sourceitemsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceItemsCount' [in] parameter to the request packet.
    uint32_t sourceitemscountIn;
    sourceitemscountIn = static_cast<uint32_t>(sourceItemsCount);////2 const size_t////
    request.set_sourceitemscount(sourceitemscountIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'origItems' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * origitemsIn = new octaneapi::ObjectRefArrayT(); //// origItems type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = const Octane::ApiItem *const * ////
    for (size_t h = 0; h < origItemsCount; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = origitemsIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////4////
         item->set_handle(origItems[h]->getObjectHandle());
    }
    request.set_allocated_origitems(origitemsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'origItemsCount' [in] parameter to the request packet.
    uint32_t origitemscountIn;
    origitemscountIn = static_cast<uint32_t>(origItemsCount);////2 const size_t////
    request.set_origitemscount(origitemscountIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::copyFrom2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyFrom2(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'sourceItemCopies' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef sourceItemCopiesOut = response.sourceitemcopies();
        sourceItemCopies->attachObjectHandle(sourceItemCopiesOut.handle());////test 79b////

        /////////////////////////////////////////////////////////////////////
        // Process 'origItemCopies' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef origItemCopiesOut = response.origitemcopies();
        origItemCopies->attachObjectHandle(origItemCopiesOut.handle());////test 79b////
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


ApiNodeGraphProxy ApiNodeGraphProxy::groupItems(
            ApiItemProxy *const *const                items, //// test821 //// 
            const size_t                              itemsCount //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::groupItemsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'items' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * itemsIn = new octaneapi::ObjectRefArrayT(); //// items type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = Octane::ApiItem *const *const ////
    for (size_t h = 0; h < itemsCount; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = itemsIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////4////
         item->set_handle(items[h]->getObjectHandle());
    }
    request.set_allocated_items(itemsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'itemsCount' [in] parameter to the request packet.
    uint32_t itemscountIn;
    itemscountIn = static_cast<uint32_t>(itemsCount);////2 const size_t////
    request.set_itemscount(itemscountIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::groupItemsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->groupItems(context.get(), request, &response);

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
        ApiNodeGraphProxy retVal;////714////
        return retVal;
    }
};


void ApiNodeGraphProxy::ungroup(
            ApiItemArrayProxy *const                  ungroupedItems //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::ungroupRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::ungroupResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->ungroup(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'ungroupedItems' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef ungroupedItemsOut = response.ungroupeditems();
        ungroupedItems->attachObjectHandle(ungroupedItemsOut.handle());////test 79b////
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


void ApiNodeGraphProxy::unfold(
            const bool                                recursive //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::unfoldRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'recursive' [in] parameter to the request packet.
    bool recursiveIn;
    recursiveIn = recursive;////2 const bool////
    request.set_recursive(recursiveIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->unfold(context.get(), request, &response);

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


std::string ApiNodeGraphProxy::showWindow(
            const bool                                unfold, //// test821 //// 
            const char *                              windowState, //// test821 //// 
            bool                                      alwaysOnTop //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::showWindowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'unfold' [in] parameter to the request packet.
    bool unfoldIn;
    unfoldIn = unfold;////2 const bool////
    request.set_unfold(unfoldIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'windowState' [in] parameter to the request packet.
    std::string * windowstateIn = new std::string(); //// windowState type=string;//// ////721////
    *windowstateIn = checkString(windowState);
    request.set_allocated_windowstate(windowstateIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'alwaysOnTop' [in] parameter to the request packet.
    bool alwaysontopIn;
    alwaysontopIn = alwaysOnTop;////2 bool////
    request.set_alwaysontop(alwaysontopIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::showWindowResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->showWindow(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
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


void ApiNodeGraphProxy::closeWindow()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::closeWindowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->closeWindow(context.get(), request, &response);

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


void ApiNodeGraphProxy::showDbWindow(
            Octane::ApiNodeGraph::DbViewClosingCallbackT * dbViewClosingCallback, //// test821 //// 
            Octane::ApiNodeGraph::DbViewLoadedCallbackT * dbViewLoadedCallback, //// test821 //// 
            void *                                    userData, //// test821 //// 
            const bool                                showLiveDb //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::showDbWindowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'dbViewClosingCallback' [in] parameter to the request packet.
    octaneapi::DbViewClosingCallbackT * dbviewclosingcallbackIn = new octaneapi::DbViewClosingCallbackT(); //// dbViewClosingCallback type=DbViewClosingCallbackT;//// ////721////
    // setup callback function dbViewClosingCallback
    //int dbViewClosingCallbackCallbackId = GRPCSettings::getNextCallbackId("DbViewClosingCallback"); 
    //CallbackStorage::registerDbViewClosingCallback(dbViewClosingCallbackCallbackId, dbViewClosingCallback);
    dbviewclosingcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //dbviewclosingcallbackIn->set_callbackid(dbViewClosingCallbackCallbackId);
    //if(className == "ApiNodeGraph" && method.mName == "showDbWindow") return true;
    request.set_allocated_dbviewclosingcallback(dbviewclosingcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'dbViewLoadedCallback' [in] parameter to the request packet.
    octaneapi::DbViewLoadedCallbackT * dbviewloadedcallbackIn = new octaneapi::DbViewLoadedCallbackT(); //// dbViewLoadedCallback type=DbViewLoadedCallbackT;//// ////721////
    // setup callback function dbViewLoadedCallback
    //int dbViewLoadedCallbackCallbackId = GRPCSettings::getNextCallbackId("DbViewLoadedCallback"); 
    //CallbackStorage::registerDbViewLoadedCallback(dbViewLoadedCallbackCallbackId, dbViewLoadedCallback);
    dbviewloadedcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //dbviewloadedcallbackIn->set_callbackid(dbViewLoadedCallbackCallbackId);
    //if(className == "ApiNodeGraph" && method.mName == "showDbWindow") return true;
    request.set_allocated_dbviewloadedcallback(dbviewloadedcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'showLiveDb' [in] parameter to the request packet.
    bool showlivedbIn;
    showlivedbIn = showLiveDb;////2 const bool////
    request.set_showlivedb(showlivedbIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraph::showDbWindowResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->showDbWindow(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerDbViewClosingCallback( response.callbackid(), dbViewClosingCallback);
        CallbackStorage::registerDbViewClosingCallback( response.callbackid(), dbViewClosingCallback);
        // set callback Id CallbackStorage::registerDbViewLoadedCallback( response.callbackid2(), dbViewLoadedCallback);
        CallbackStorage::registerDbViewLoadedCallback( response.callbackid2(), dbViewLoadedCallback);
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


void ApiNodeGraphProxy::closeDbWindow(
            bool                                      clearData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraph::closeDbWindowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'clearData' [in] parameter to the request packet.
    bool cleardataIn;
    cleardataIn = clearData;////2 bool////
    request.set_cleardata(cleardataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphService::Stub> stub = 
        octaneapi::ApiNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->closeDbWindow(context.get(), request, &response);

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


