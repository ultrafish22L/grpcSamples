// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apinodeclient.h"
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
#include "apinodesystem_3.grpc.pb.h"
#include "apinodesystem_5.grpc.pb.h"
#include "apinodesystem_6.grpc.pb.h"
#include "apinodesystem_7.grpc.pb.h"
#include "apinodesystem_8.grpc.pb.h"
#include "apiitemclient.h"
#include "apinodegraphclient.h"
#include "apirootnodegraphclient.h"
#include "apinodepininfoclient.h"
#include "apinodearrayclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapifilepath.h"
#include "convertapinodeinfo.h"
#include "convertapitexturenodetypeinfo_apitexturenodetypeinfo_configuration.h"


namespace OctaneGRPC
{


GRPCSettings & ApiNodeProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiNodeProxy ApiNodeProxy::create(
            const Octane::NodeType                    type,
            ApiNodeGraphProxy &                       ownerGraph,
            const bool                                configurePins
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
        typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ownerGraph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * ownergraphIn = new octaneapi::ObjectRef();
    ownergraphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);
    ownergraphIn->set_handle(ownerGraph.getObjectHandle());
    request.set_allocated_ownergraph(ownergraphIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'configurePins' [in] parameter to the request packet.
    bool configurepinsIn;
    configurepinsIn = configurePins;
    request.set_configurepins(configurepinsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


bool ApiNodeProxy::addDynamicPinForLoading(
            const Octane::NodePinType                 type,
            const char *                              name
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::addDynamicPinForLoadingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodePinType typeIn;
        typeIn = static_cast<octaneapi::NodePinType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::addDynamicPinForLoadingResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->addDynamicPinForLoading(context.get(), request, &response);

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


const ApiNodeInfoProxy ApiNodeProxy::info() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::infoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::infoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->info(context.get(), request, &response);

    ApiNodeInfoProxy retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiNodeInfo resultOut = response.result();
        ApiNodeInfoConverter::convert(resultOut, retVal);
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


Octane::NodeType ApiNodeProxy::type() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::typeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::typeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->type(context.get(), request, &response);

    Octane::NodeType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NodeType resultOut = response.result();
        retVal = static_cast<Octane::NodeType>(resultOut);
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


Octane::TextureValueType ApiNodeProxy::outputTextureValueType() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::outputTextureValueTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::outputTextureValueTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->outputTextureValueType(context.get(), request, &response);

    Octane::TextureValueType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::TextureValueType resultOut = response.result();
        retVal = static_cast<Octane::TextureValueType>(resultOut);
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


bool ApiNodeProxy::setTextureTypeConfiguration(
            const Octane::ApiTextureNodeTypeInfo::Configuration & configuration,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setTextureTypeConfigurationRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'configuration' [in] parameter to the request packet.
    octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration * configurationIn = new octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration();
    // Using Converter 5, type = const Octane::ApiTextureNodeTypeInfo::Configuration &, protoType = ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration
    ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_ConfigurationConverter::convert(configuration, *configurationIn);
    request.set_allocated_configuration(configurationIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::setTextureTypeConfigurationResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setTextureTypeConfiguration(context.get(), request, &response);

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


void ApiNodeProxy::configureEmptyPins()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::configureEmptyPinsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->configureEmptyPins(context.get(), request, &response);

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


uint32_t ApiNodeProxy::pinCount() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinCount(context.get(), request, &response);

    uint32_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint32_t resultOut = response.result();
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


uint32_t ApiNodeProxy::staticPinCount() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::staticPinCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::staticPinCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->staticPinCount(context.get(), request, &response);

    uint32_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint32_t resultOut = response.result();
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


uint32_t ApiNodeProxy::dynPinCount() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::dynPinCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::dynPinCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->dynPinCount(context.get(), request, &response);

    uint32_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint32_t resultOut = response.result();
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


bool ApiNodeProxy::hasPin(
            const Octane::PinId                       pinId
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::hasPinRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::hasPinResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasPin(context.get(), request, &response);

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


bool ApiNodeProxy::hasPin(
            const char *                              pinName
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::hasPin1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::hasPin1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasPin1(context.get(), request, &response);

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


bool ApiNodeProxy::hasPinIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::hasPinIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::hasPinIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasPinIx(context.get(), request, &response);

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


bool ApiNodeProxy::findPin(
            const Octane::PinId                       id,
            uint32_t &                                foundIndex
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::findPinRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::findPinResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->findPin(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'foundIndex' [out] parameter from the gRPC response packet
        uint32_t foundIndexOut = response.foundindex();
        foundIndex = foundIndexOut;
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


bool ApiNodeProxy::findPin(
            const char *                              name,
            uint32_t &                                foundIndex
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::findPin1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::findPin1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->findPin1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'foundIndex' [out] parameter from the gRPC response packet
        uint32_t foundIndexOut = response.foundindex();
        foundIndex = foundIndexOut;
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


Octane::PinId ApiNodeProxy::pinId(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinId(context.get(), request, &response);

    Octane::PinId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::PinId resultOut = response.result();
        retVal = static_cast<Octane::PinId>(resultOut);
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


Octane::PinId ApiNodeProxy::pinIdIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinIdIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinIdIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinIdIx(context.get(), request, &response);

    Octane::PinId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::PinId resultOut = response.result();
        retVal = static_cast<Octane::PinId>(resultOut);
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


std::string ApiNodeProxy::pinName(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinName(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


std::string ApiNodeProxy::pinNameIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinNameIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinNameIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinNameIx(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


std::string ApiNodeProxy::pinLabel(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinLabelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinLabelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinLabel(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


std::string ApiNodeProxy::pinLabel(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinLabel1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinLabel1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinLabel1(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


std::string ApiNodeProxy::pinLabelIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinLabelIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinLabelIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinLabelIx(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


Octane::NodePinType ApiNodeProxy::pinType(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinType(context.get(), request, &response);

    Octane::NodePinType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NodePinType resultOut = response.result();
        retVal = static_cast<Octane::NodePinType>(resultOut);
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


Octane::NodePinType ApiNodeProxy::pinType(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinType1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinType1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinType1(context.get(), request, &response);

    Octane::NodePinType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NodePinType resultOut = response.result();
        retVal = static_cast<Octane::NodePinType>(resultOut);
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


Octane::NodePinType ApiNodeProxy::pinTypeIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinTypeIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinTypeIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinTypeIx(context.get(), request, &response);

    Octane::NodePinType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NodePinType resultOut = response.result();
        retVal = static_cast<Octane::NodePinType>(resultOut);
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


Octane::TextureValueType ApiNodeProxy::pinTextureValueType(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinTextureValueTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinTextureValueTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinTextureValueType(context.get(), request, &response);

    Octane::TextureValueType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::TextureValueType resultOut = response.result();
        retVal = static_cast<Octane::TextureValueType>(resultOut);
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


Octane::TextureValueType ApiNodeProxy::pinTextureValueTypeIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinTextureValueTypeIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinTextureValueTypeIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinTextureValueTypeIx(context.get(), request, &response);

    Octane::TextureValueType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::TextureValueType resultOut = response.result();
        retVal = static_cast<Octane::TextureValueType>(resultOut);
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


ApiNodePinInfoProxy ApiNodeProxy::pinInfo(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinInfo(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodePinInfoProxy retVal;
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
        ApiNodePinInfoProxy retVal;
        return retVal;
    }
};


ApiNodePinInfoProxy ApiNodeProxy::pinInfo(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinInfo1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinInfo1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinInfo1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodePinInfoProxy retVal;
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
        ApiNodePinInfoProxy retVal;
        return retVal;
    }
};


ApiNodePinInfoProxy ApiNodeProxy::pinInfoIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinInfoIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinInfoIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinInfoIx(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodePinInfoProxy retVal;
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
        ApiNodePinInfoProxy retVal;
        return retVal;
    }
};


bool ApiNodeProxy::pinsAreDirty() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::pinsAreDirtyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::pinsAreDirtyResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinsAreDirty(context.get(), request, &response);

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


bool ApiNodeProxy::isDirtyPin(
            const Octane::PinId                       pinId
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::isDirtyPinRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::isDirtyPinResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDirtyPin(context.get(), request, &response);

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


bool ApiNodeProxy::isDirtyPin(
            const char *                              pinName
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::isDirtyPin1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::isDirtyPin1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDirtyPin1(context.get(), request, &response);

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


bool ApiNodeProxy::isDirtyPinIx(
            const uint32_t                            pinIx
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::isDirtyPinIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::isDirtyPinIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDirtyPinIx(context.get(), request, &response);

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


bool ApiNodeProxy::canConnectTo(
            const Octane::PinId                       pinId,
            const ApiNodeProxy *                      sourceNode,
            const bool                                doCycleCheck
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::canConnectToRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourcenodeIn = new octaneapi::ObjectRef();
    sourcenodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    sourcenodeIn->set_handle(sourceNode->getObjectHandle());
    request.set_allocated_sourcenode(sourcenodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'doCycleCheck' [in] parameter to the request packet.
    bool docyclecheckIn;
    docyclecheckIn = doCycleCheck;
    request.set_docyclecheck(docyclecheckIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::canConnectToResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->canConnectTo(context.get(), request, &response);

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


bool ApiNodeProxy::canConnectTo(
            const char *                              pinName,
            const ApiNodeProxy *                      sourceNode,
            const bool                                doCycleCheck
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::canConnectTo1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourcenodeIn = new octaneapi::ObjectRef();
    sourcenodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    sourcenodeIn->set_handle(sourceNode->getObjectHandle());
    request.set_allocated_sourcenode(sourcenodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'doCycleCheck' [in] parameter to the request packet.
    bool docyclecheckIn;
    docyclecheckIn = doCycleCheck;
    request.set_docyclecheck(docyclecheckIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::canConnectTo1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->canConnectTo1(context.get(), request, &response);

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


bool ApiNodeProxy::canConnectToIx(
            const uint32_t                            pinIx,
            const ApiNodeProxy *                      sourceNode,
            const bool                                doCycleCheck
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::canConnectToIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourcenodeIn = new octaneapi::ObjectRef();
    sourcenodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    sourcenodeIn->set_handle(sourceNode->getObjectHandle());
    request.set_allocated_sourcenode(sourcenodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'doCycleCheck' [in] parameter to the request packet.
    bool docyclecheckIn;
    docyclecheckIn = doCycleCheck;
    request.set_docyclecheck(docyclecheckIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::canConnectToIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->canConnectToIx(context.get(), request, &response);

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


void ApiNodeProxy::connectTo(
            const Octane::PinId                       pinId,
            ApiNodeProxy *                            sourceNode,
            const bool                                evaluate,
            const bool                                doCycleCheck
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::connectToRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourcenodeIn = new octaneapi::ObjectRef();
    sourcenodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    sourcenodeIn->set_handle(sourceNode->getObjectHandle());
    request.set_allocated_sourcenode(sourcenodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'doCycleCheck' [in] parameter to the request packet.
    bool docyclecheckIn;
    docyclecheckIn = doCycleCheck;
    request.set_docyclecheck(docyclecheckIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->connectTo(context.get(), request, &response);

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


void ApiNodeProxy::connectTo(
            const char *                              pinName,
            ApiNodeProxy *                            sourceNode,
            const bool                                evaluate,
            const bool                                doCycleCheck
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::connectTo1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourcenodeIn = new octaneapi::ObjectRef();
    sourcenodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    sourcenodeIn->set_handle(sourceNode->getObjectHandle());
    request.set_allocated_sourcenode(sourcenodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'doCycleCheck' [in] parameter to the request packet.
    bool docyclecheckIn;
    docyclecheckIn = doCycleCheck;
    request.set_docyclecheck(docyclecheckIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->connectTo1(context.get(), request, &response);

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


void ApiNodeProxy::connectToIx(
            const uint32_t                            pinIdx,
            ApiNodeProxy *                            sourceNode,
            const bool                                evaluate,
            const bool                                doCycleCheck
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::connectToIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIdx' [in] parameter to the request packet.
    uint32_t pinidxIn;
    pinidxIn = pinIdx;
    request.set_pinidx(pinidxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourcenodeIn = new octaneapi::ObjectRef();
    sourcenodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    sourcenodeIn->set_handle(sourceNode->getObjectHandle());
    request.set_allocated_sourcenode(sourcenodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'doCycleCheck' [in] parameter to the request packet.
    bool docyclecheckIn;
    docyclecheckIn = doCycleCheck;
    request.set_docyclecheck(docyclecheckIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->connectToIx(context.get(), request, &response);

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


ApiNodeProxy ApiNodeProxy::connectedNode(
            const Octane::PinId                       pinId,
            const bool                                enterWrapperNode
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::connectedNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'enterWrapperNode' [in] parameter to the request packet.
    bool enterwrappernodeIn;
    enterwrappernodeIn = enterWrapperNode;
    request.set_enterwrappernode(enterwrappernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::connectedNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->connectedNode(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiNodeProxy::connectedNode(
            const char *const                         pinName,
            const bool                                enterWrapperNode
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::connectedNode1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'enterWrapperNode' [in] parameter to the request packet.
    bool enterwrappernodeIn;
    enterwrappernodeIn = enterWrapperNode;
    request.set_enterwrappernode(enterwrappernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::connectedNode1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->connectedNode1(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiNodeProxy::connectedNodeIx(
            const uint32_t                            pinIx,
            const bool                                enterWrapperNode
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::connectedNodeIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'enterWrapperNode' [in] parameter to the request packet.
    bool enterwrappernodeIn;
    enterwrappernodeIn = enterWrapperNode;
    request.set_enterwrappernode(enterwrappernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::connectedNodeIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->connectedNodeIx(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiNodeProxy::inputNode(
            const Octane::PinId                       pinId,
            const bool                                enterWrapperNodes
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::inputNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'enterWrapperNodes' [in] parameter to the request packet.
    bool enterwrappernodesIn;
    enterwrappernodesIn = enterWrapperNodes;
    request.set_enterwrappernodes(enterwrappernodesIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::inputNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->inputNode(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiNodeProxy::inputNode(
            const char *const                         pinName,
            const bool                                enterWrapperNodes
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::inputNode1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'enterWrapperNodes' [in] parameter to the request packet.
    bool enterwrappernodesIn;
    enterwrappernodesIn = enterWrapperNodes;
    request.set_enterwrappernodes(enterwrappernodesIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::inputNode1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->inputNode1(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiNodeProxy::inputNodeIx(
            const uint32_t                            index,
            const bool                                enterWrapperNodes
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::inputNodeIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'enterWrapperNodes' [in] parameter to the request packet.
    bool enterwrappernodesIn;
    enterwrappernodesIn = enterWrapperNodes;
    request.set_enterwrappernodes(enterwrappernodesIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::inputNodeIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->inputNodeIx(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


void ApiNodeProxy::destinationNodes(
            ApiNodeArrayProxy &                       nodes,
            std::vector<std::string> &                pinNames
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::destinationNodesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::destinationNodesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->destinationNodes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'nodes' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef nodesOut = response.nodes();
        nodes.attachObjectHandle(nodesOut.handle());

        /////////////////////////////////////////////////////////////////////
        // Process 'pinNames' [out] parameter from the gRPC response packet
        octaneapi::StringArrayT pinNamesOut = response.pinnames();
        pinNames.reserve(pinNamesOut.data_size());
        for (int i = 0; i < pinNamesOut.data_size(); i++)
        {
            pinNames.push_back(pinNamesOut.data(i));
        }
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


ApiNodePinInfoProxy ApiNodeProxy::buildLinkerNodePinInfo()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::buildLinkerNodePinInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::buildLinkerNodePinInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->buildLinkerNodePinInfo(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodePinInfoProxy retVal;
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
        ApiNodePinInfoProxy retVal;
        return retVal;
    }
};


ApiNodePinInfoProxy ApiNodeProxy::buildDestinationPinInfo()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::buildDestinationPinInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::buildDestinationPinInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->buildDestinationPinInfo(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodePinInfoProxy retVal;
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
        ApiNodePinInfoProxy retVal;
        return retVal;
    }
};


ApiItemProxy ApiNodeProxy::ownedItem(
            const Octane::PinId                       pinId
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::ownedItemRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::ownedItemResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->ownedItem(context.get(), request, &response);

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
        ApiItemProxy retVal;
        return retVal;
    }
};


ApiItemProxy ApiNodeProxy::ownedItem(
            const char *                              pinName
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::ownedItem1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::ownedItem1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->ownedItem1(context.get(), request, &response);

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
        ApiItemProxy retVal;
        return retVal;
    }
};


ApiItemProxy ApiNodeProxy::ownedItemIx(
            const uint32_t                            pinIx
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::ownedItemIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::ownedItemIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->ownedItemIx(context.get(), request, &response);

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
        ApiItemProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiNodeProxy::createInternal(
            const Octane::PinId                       pinId,
            const Octane::NodeType                    type,
            const bool                                configurePins,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::createInternalRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
        typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'configurePins' [in] parameter to the request packet.
    bool configurepinsIn;
    configurepinsIn = configurePins;
    request.set_configurepins(configurepinsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::createInternalResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->createInternal(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiNodeProxy::createInternal(
            const char *                              pinName,
            const Octane::NodeType                    type,
            const bool                                configurePins,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::createInternal1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
        typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'configurePins' [in] parameter to the request packet.
    bool configurepinsIn;
    configurepinsIn = configurePins;
    request.set_configurepins(configurepinsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::createInternal1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->createInternal1(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiNodeProxy::createInternalIx(
            const uint32_t                            pinIx,
            const Octane::NodeType                    type,
            const bool                                configurePins,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::createInternalIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
        typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'configurePins' [in] parameter to the request packet.
    bool configurepinsIn;
    configurepinsIn = configurePins;
    request.set_configurepins(configurepinsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::createInternalIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->createInternalIx(context.get(), request, &response);

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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeGraphProxy ApiNodeProxy::createInternal(
            const Octane::PinId                       pinId,
            const Octane::NodeGraphType               type,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::createInternal2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeGraphType typeIn;
        typeIn = static_cast<octaneapi::NodeGraphType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::createInternal2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->createInternal2(context.get(), request, &response);

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
        ApiNodeGraphProxy retVal;
        return retVal;
    }
};


ApiNodeGraphProxy ApiNodeProxy::createInternal(
            const char *                              pinName,
            const Octane::NodeGraphType               type,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::createInternal3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeGraphType typeIn;
        typeIn = static_cast<octaneapi::NodeGraphType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::createInternal3Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->createInternal3(context.get(), request, &response);

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
        ApiNodeGraphProxy retVal;
        return retVal;
    }
};


ApiNodeGraphProxy ApiNodeProxy::createInternalIx(
            const uint32_t                            pinIx,
            const Octane::NodeGraphType               type,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::createInternalIx1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeGraphType typeIn;
        typeIn = static_cast<octaneapi::NodeGraphType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::createInternalIx1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->createInternalIx1(context.get(), request, &response);

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
        ApiNodeGraphProxy retVal;
        return retVal;
    }
};


ApiItemProxy ApiNodeProxy::copyFrom(
            const Octane::PinId                       pinId,
            const ApiItemProxy *                      sourceItem,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::copyFromRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourceitemIn = new octaneapi::ObjectRef();
    sourceitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    sourceitemIn->set_handle(sourceItem->getObjectHandle());
    request.set_allocated_sourceitem(sourceitemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::copyFromResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyFrom(context.get(), request, &response);

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
        ApiItemProxy retVal;
        return retVal;
    }
};


ApiItemProxy ApiNodeProxy::copyFrom(
            const char *                              pinName,
            const ApiItemProxy *                      sourceItem,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::copyFrom1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourceitemIn = new octaneapi::ObjectRef();
    sourceitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    sourceitemIn->set_handle(sourceItem->getObjectHandle());
    request.set_allocated_sourceitem(sourceitemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::copyFrom1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyFrom1(context.get(), request, &response);

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
        ApiItemProxy retVal;
        return retVal;
    }
};


ApiItemProxy ApiNodeProxy::copyFromIx(
            const uint32_t                            pinIx,
            const ApiItemProxy *                      sourceItem,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::copyFromIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sourceItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * sourceitemIn = new octaneapi::ObjectRef();
    sourceitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    sourceitemIn->set_handle(sourceItem->getObjectHandle());
    request.set_allocated_sourceitem(sourceitemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::copyFromIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyFromIx(context.get(), request, &response);

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
        ApiItemProxy retVal;
        return retVal;
    }
};


bool ApiNodeProxy::getPinBool(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinBoolRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinBoolResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinBool(context.get(), request, &response);

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


float ApiNodeProxy::getPinFloat(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloatRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloatResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat(context.get(), request, &response);

    float retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        float resultOut = response.result();
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


OctaneVec::float_2 ApiNodeProxy::getPinFloat2(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat2(context.get(), request, &response);

    OctaneVec::float_2 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_2 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
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


OctaneVec::float_3 ApiNodeProxy::getPinFloat3(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat3Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat3(context.get(), request, &response);

    OctaneVec::float_3 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_3 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
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


OctaneVec::float_4 ApiNodeProxy::getPinFloat4(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat4Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat4(context.get(), request, &response);

    OctaneVec::float_4 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_4 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
        retVal.w = resultOut.w();
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


int32_t ApiNodeProxy::getPinInt(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinIntRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinIntResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt(context.get(), request, &response);

    int32_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
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


OctaneVec::int32_2 ApiNodeProxy::getPinInt2(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt2(context.get(), request, &response);

    OctaneVec::int32_2 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_2 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
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


OctaneVec::int32_3 ApiNodeProxy::getPinInt3(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt3Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt3(context.get(), request, &response);

    OctaneVec::int32_3 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_3 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
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


OctaneVec::int32_4 ApiNodeProxy::getPinInt4(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt4Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt4(context.get(), request, &response);

    OctaneVec::int32_4 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_4 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
        retVal.w = resultOut.w();
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


OctaneVec::MatrixF ApiNodeProxy::getPinMatrix(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinMatrixRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinMatrixResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinMatrix(context.get(), request, &response);

    OctaneVec::MatrixF retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::MatrixF resultOut = response.result();
    MatrixConverter::convertMatrixToOctane(resultOut, retVal);
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


std::string ApiNodeProxy::getPinString(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinStringRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinStringResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinString(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


Octane::ApiFilePath ApiNodeProxy::getPinFilePath(
            const Octane::PinId                       id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFilePathRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFilePathResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFilePath(context.get(), request, &response);

    Octane::ApiFilePath retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiFilePath resultOut = response.result();
        ApiFilePathConverter::convert(resultOut, retVal);
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


bool ApiNodeProxy::getPinBool(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinBool1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinBool1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinBool1(context.get(), request, &response);

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


float ApiNodeProxy::getPinFloat(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat1(context.get(), request, &response);

    float retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        float resultOut = response.result();
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


OctaneVec::float_2 ApiNodeProxy::getPinFloat2(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat21Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat21Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat21(context.get(), request, &response);

    OctaneVec::float_2 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_2 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
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


OctaneVec::float_3 ApiNodeProxy::getPinFloat3(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat31Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat31Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat31(context.get(), request, &response);

    OctaneVec::float_3 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_3 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
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


OctaneVec::float_4 ApiNodeProxy::getPinFloat4(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat41Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat41Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat41(context.get(), request, &response);

    OctaneVec::float_4 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_4 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
        retVal.w = resultOut.w();
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


int32_t ApiNodeProxy::getPinInt(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt1(context.get(), request, &response);

    int32_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
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


OctaneVec::int32_2 ApiNodeProxy::getPinInt2(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt21Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt21Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt21(context.get(), request, &response);

    OctaneVec::int32_2 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_2 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
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


OctaneVec::int32_3 ApiNodeProxy::getPinInt3(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt31Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt31Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt31(context.get(), request, &response);

    OctaneVec::int32_3 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_3 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
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


OctaneVec::int32_4 ApiNodeProxy::getPinInt4(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt41Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt41Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt41(context.get(), request, &response);

    OctaneVec::int32_4 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_4 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
        retVal.w = resultOut.w();
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


OctaneVec::MatrixF ApiNodeProxy::getPinMatrix(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinMatrix1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinMatrix1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinMatrix1(context.get(), request, &response);

    OctaneVec::MatrixF retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::MatrixF resultOut = response.result();
    MatrixConverter::convertMatrixToOctane(resultOut, retVal);
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


std::string ApiNodeProxy::getPinString(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinString1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinString1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinString1(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


Octane::ApiFilePath ApiNodeProxy::getPinFilePath(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFilePath1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFilePath1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFilePath1(context.get(), request, &response);

    Octane::ApiFilePath retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiFilePath resultOut = response.result();
        ApiFilePathConverter::convert(resultOut, retVal);
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


bool ApiNodeProxy::getPinBoolIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinBoolIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinBoolIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinBoolIx(context.get(), request, &response);

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


float ApiNodeProxy::getPinFloatIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloatIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloatIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloatIx(context.get(), request, &response);

    float retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        float resultOut = response.result();
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


OctaneVec::float_2 ApiNodeProxy::getPinFloat2Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat2IxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat2IxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat2Ix(context.get(), request, &response);

    OctaneVec::float_2 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_2 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
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


OctaneVec::float_3 ApiNodeProxy::getPinFloat3Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat3IxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat3IxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat3Ix(context.get(), request, &response);

    OctaneVec::float_3 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_3 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
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


OctaneVec::float_4 ApiNodeProxy::getPinFloat4Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFloat4IxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFloat4IxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFloat4Ix(context.get(), request, &response);

    OctaneVec::float_4 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::float_4 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
        retVal.w = resultOut.w();
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


int32_t ApiNodeProxy::getPinIntIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinIntIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinIntIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinIntIx(context.get(), request, &response);

    int32_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
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


OctaneVec::int32_2 ApiNodeProxy::getPinInt2Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt2IxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt2IxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt2Ix(context.get(), request, &response);

    OctaneVec::int32_2 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_2 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
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


OctaneVec::int32_3 ApiNodeProxy::getPinInt3Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt3IxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt3IxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt3Ix(context.get(), request, &response);

    OctaneVec::int32_3 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_3 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
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


OctaneVec::int32_4 ApiNodeProxy::getPinInt4Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinInt4IxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinInt4IxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinInt4Ix(context.get(), request, &response);

    OctaneVec::int32_4 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::int32_4 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
        retVal.z = resultOut.z();
        retVal.w = resultOut.w();
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


OctaneVec::MatrixF ApiNodeProxy::getPinMatrixIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinMatrixIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinMatrixIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinMatrixIx(context.get(), request, &response);

    OctaneVec::MatrixF retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::MatrixF resultOut = response.result();
    MatrixConverter::convertMatrixToOctane(resultOut, retVal);
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


std::string ApiNodeProxy::getPinStringIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinStringIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinStringIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinStringIx(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


Octane::ApiFilePath ApiNodeProxy::getPinFilePathIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinFilePathIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinFilePathIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinFilePathIx(context.get(), request, &response);

    Octane::ApiFilePath retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiFilePath resultOut = response.result();
        ApiFilePathConverter::convert(resultOut, retVal);
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            bool &                                    value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        bool valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            float &                                   value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        float valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue2(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_2 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue3Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue3(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_3 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue4Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue4(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_4 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
        value.w = valueOut.w();
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            int32_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue5Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue5(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        int32_t valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue6Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue6(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_2 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue7Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue7(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_3 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue8Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue8(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_4 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
        value.w = valueOut.w();
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::MatrixF &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue9Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue9(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::MatrixF valueOut = response.value();
    MatrixConverter::convertMatrixToOctane(valueOut, value);
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            std::string &                             value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue10Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue10(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        std::string valueOut = response.value();
        // param.mType = const char *&
        value =  valueOut;
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


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            Octane::ApiFilePath &                     value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue11Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue11(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::ApiFilePath valueOut = response.value();
        ApiFilePathConverter::convert(valueOut, value);
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            bool &                                    value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue12Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue12Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue12(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        bool valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            float &                                   value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue13Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue13Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue13(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        float valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::float_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue14Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue14Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue14(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_2 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::float_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue15Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue15Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue15(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_3 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::float_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue16Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue16Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue16(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_4 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
        value.w = valueOut.w();
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            int32_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue17Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue17Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue17(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        int32_t valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::int32_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue18Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue18Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue18(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_2 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::int32_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue19Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue19Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue19(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_3 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::int32_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue20Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue20Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue20(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_4 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
        value.w = valueOut.w();
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::MatrixF &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue21Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue21Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue21(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::MatrixF valueOut = response.value();
    MatrixConverter::convertMatrixToOctane(valueOut, value);
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            std::string &                             value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue22Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue22Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue22(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        std::string valueOut = response.value();
        // param.mType = const char *&
        value =  valueOut;
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


void ApiNodeProxy::getPinValue(
            const char *                              name,
            Octane::ApiFilePath &                     value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValue23Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValue23Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValue23(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::ApiFilePath valueOut = response.value();
        ApiFilePathConverter::convert(valueOut, value);
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            bool &                                    value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        bool valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            float &                                   value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        float valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx2(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_2 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx3Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx3(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_3 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx4Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx4(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_4 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
        value.w = valueOut.w();
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            int32_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx5Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx5(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        int32_t valueOut = response.value();
        value = valueOut;
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx6Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx6(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_2 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx7Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx7(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_3 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx8Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx8(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_4 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
        value.w = valueOut.w();
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::MatrixF &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx9Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx9(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::MatrixF valueOut = response.value();
    MatrixConverter::convertMatrixToOctane(valueOut, value);
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            std::string &                             value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx10Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx10(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        std::string valueOut = response.value();
        // param.mType = const char *&
        value =  valueOut;
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


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            Octane::ApiFilePath &                     value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::getPinValueIx11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::getPinValueIx11Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinValueIx11(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::ApiFilePath valueOut = response.value();
        ApiFilePathConverter::convert(valueOut, value);
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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    bool valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    float valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue1(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_2 * valueIn = new octaneapi::float_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue2(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_3 * valueIn = new octaneapi::float_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue3(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_4 * valueIn = new octaneapi::float_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue4(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue5(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_2 * valueIn = new octaneapi::int32_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue6(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_3 * valueIn = new octaneapi::int32_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue7(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_4 * valueIn = new octaneapi::int32_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue8(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::MatrixF * valueIn = new octaneapi::MatrixF();
MatrixConverter::convertMatrixToProto(value, *valueIn);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue9(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const char *const                         value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    std::string * valueIn = new std::string();
    *valueIn = checkString(value);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue10(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
        idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::ApiFilePath * valueIn = new octaneapi::ApiFilePath();
    ApiFilePathConverter::convert(value, *valueIn);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue11(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue12Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    bool valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue12(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue13Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    float valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue13(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue14Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_2 * valueIn = new octaneapi::float_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue14(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue15Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_3 * valueIn = new octaneapi::float_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue15(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue16Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_4 * valueIn = new octaneapi::float_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue16(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue17Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue17(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue18Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_2 * valueIn = new octaneapi::int32_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue18(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue19Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_3 * valueIn = new octaneapi::int32_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue19(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue20Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_4 * valueIn = new octaneapi::int32_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue20(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue21Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::MatrixF * valueIn = new octaneapi::MatrixF();
MatrixConverter::convertMatrixToProto(value, *valueIn);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue21(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const char *const                         value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue22Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    std::string * valueIn = new std::string();
    *valueIn = checkString(value);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue22(context.get(), request, &response);

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


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValue23Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::ApiFilePath * valueIn = new octaneapi::ApiFilePath();
    ApiFilePathConverter::convert(value, *valueIn);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValue23(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    bool valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    float valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx1(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_2 * valueIn = new octaneapi::float_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx2(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_3 * valueIn = new octaneapi::float_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx3(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_4 * valueIn = new octaneapi::float_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx4(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx5(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_2 * valueIn = new octaneapi::int32_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx6(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_3 * valueIn = new octaneapi::int32_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx7(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_4 * valueIn = new octaneapi::int32_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx8(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::MatrixF * valueIn = new octaneapi::MatrixF();
MatrixConverter::convertMatrixToProto(value, *valueIn);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx9(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const char *const                         value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    std::string * valueIn = new std::string();
    *valueIn = checkString(value);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx10(context.get(), request, &response);

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


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::setPinValueIx11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::ApiFilePath * valueIn = new octaneapi::ApiFilePath();
    ApiFilePathConverter::convert(value, *valueIn);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPinValueIx11(context.get(), request, &response);

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


bool ApiNodeProxy::storeToDb()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::storeToDbRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::storeToDbResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->storeToDb(context.get(), request, &response);

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


void ApiNodeProxy::showOslWindow(
            bool                                      force
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::showOslWindowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'force' [in] parameter to the request packet.
    bool forceIn;
    forceIn = force;
    request.set_force(forceIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->showOslWindow(context.get(), request, &response);

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


bool ApiNodeProxy::closeOslWindow(
            bool                                      force
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::closeOslWindowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'force' [in] parameter to the request packet.
    bool forceIn;
    forceIn = force;
    request.set_force(forceIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::closeOslWindowResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->closeOslWindow(context.get(), request, &response);

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


bool ApiNodeProxy::unpackFileData(
            const char *                              assetPath,
            bool                                      recursive
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNode::unpackFileDataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetPath' [in] parameter to the request packet.
    std::string * assetpathIn = new std::string();
    *assetpathIn = checkString(assetPath);
    request.set_allocated_assetpath(assetpathIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'recursive' [in] parameter to the request packet.
    bool recursiveIn;
    recursiveIn = recursive;
    request.set_recursive(recursiveIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNode::unpackFileDataResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeService::Stub> stub =
        octaneapi::ApiNodeService::NewStub(getGRPCSettings().getChannel());
    status = stub->unpackFileData(context.get(), request, &response);

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
