// Copyright (C) 2026 OTOY NZ Ltd.

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
// static strings used when getPinValue returns pointers to string objects
static std::string gPackage;
static std::string gFilename;


namespace OctaneGRPC
{



octaneapi::ApiNode::getPinValueByXResponse callGetPinValueByPinID(
    const ApiNodeProxy &    proxy,
    const Octane::PinId     id,
    octaneapi::PinTypeId    expectedType)
{
    // Build request
    octaneapi::ApiNode::getPinValueByIDRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    ref->set_handle(proxy.getObjectHandle());

    // Correct cast to proto enum
    request.set_pin_id(static_cast<octaneapi::PinId>(id));
    request.set_expected_type(expectedType);

    // Response + call
    octaneapi::ApiNode::getPinValueByXResponse response;
    auto stub = octaneapi::ApiNodeService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getPinValueByPinID(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getPinValueByPinID error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiNode::getPinValueByXResponse callGetPinValueByName(
        const ApiNodeProxy &    proxy,
        const std::string &     name,
        octaneapi::PinTypeId    expectedType)
{
    octaneapi::ApiNode::getPinValueByNameRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    ref->set_handle(proxy.getObjectHandle());

    request.set_name(name);
    request.set_expected_type(expectedType);

    octaneapi::ApiNode::getPinValueByXResponse response;
    auto stub = octaneapi::ApiNodeService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getPinValueByName(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getPinValueByName error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiNode::getPinValueByXResponse callGetPinValueByIx(
        const ApiNodeProxy &     proxy,
        uint32_t                 index,
        octaneapi::PinTypeId     expectedType)
{
    octaneapi::ApiNode::getPinValueByIxRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    ref->set_handle(proxy.getObjectHandle());

    request.set_index(index);
    request.set_expected_type(expectedType);

    octaneapi::ApiNode::getPinValueByXResponse response;
    auto stub = octaneapi::ApiNodeService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getPinValueByIx(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getPinValueByIx error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiNode::setPinValueResponse callSetPinValueByPinID(
        const ApiNodeProxy &                               proxy,
        const Octane::PinId                                id,
        const octaneapi::ApiNode::setPinValueByIDRequest & request
        )
{
    octaneapi::ApiNode::setPinValueResponse response;

    // make a copy of request with item_ref + pin_id filled
    octaneapi::ApiNode::setPinValueByIDRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    ref->set_handle(proxy.getObjectHandle());

    req.set_pin_id(static_cast<octaneapi::PinId>(id));

    auto stub = octaneapi::ApiNodeService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setPinValueByPinID(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setPinValueByPinID error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }

    return response;
}


octaneapi::ApiNode::setPinValueResponse callSetPinValueByName(
        const ApiNodeProxy &                                 proxy,
        const std::string &                                  name,
        const octaneapi::ApiNode::setPinValueByNameRequest & request
        )
{
    octaneapi::ApiNode::setPinValueResponse response;

    octaneapi::ApiNode::setPinValueByNameRequest req = request;
    auto * ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    ref->set_handle(proxy.getObjectHandle());

    req.set_name(name);

    auto stub = octaneapi::ApiNodeService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setPinValueByName(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setPinValueByName error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }

    return response;
}


octaneapi::ApiNode::setPinValueResponse callSetPinValueByIx(
        const ApiNodeProxy &                               proxy,
        uint32_t                                           index,
        const octaneapi::ApiNode::setPinValueByIxRequest & request
        )
{
    octaneapi::ApiNode::setPinValueResponse response;

    octaneapi::ApiNode::setPinValueByIxRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    ref->set_handle(proxy.getObjectHandle());

    req.set_index(index);

    auto stub = octaneapi::ApiNodeService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setPinValueByIx(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setPinValueByIx error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }

    return response;
}


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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
        ApiItemProxy retVal;
        return retVal;
    }
};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            bool &                                    value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_BOOL);
    value = response.bool_value();
};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            float &                                   value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_FLOAT);
    value = response.float_value();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_FLOAT2);
    value.x = response.float2_value().x();
    value.y = response.float2_value().y();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_FLOAT3);
    value.x = response.float3_value().x();
    value.y = response.float3_value().y();
    value.z = response.float3_value().z();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::float_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_FLOAT4);
    value.x = response.float4_value().x();
    value.y = response.float4_value().y();
    value.z = response.float4_value().z();
    value.w = response.float4_value().w();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            int32_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_INT);
    value = response.int_value();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_INT2);
    value.x = response.int2_value().x();
    value.y = response.int2_value().y();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_INT3);
    value.x = response.int3_value().x();
    value.y = response.int3_value().y();
    value.z = response.int3_value().z();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::int32_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_INT4);
    value.x = response.int4_value().x();
    value.y = response.int4_value().y();
    value.z = response.int4_value().z();
    value.w = response.int4_value().w();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            OctaneVec::MatrixF &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_MATRIX);
    MatrixConverter::convertMatrixToOctane(response.matrix_value(), value);

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            std::string &                             value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_STRING);
    value = response.string_value();

};


void ApiNodeProxy::getPinValue(
            const Octane::PinId                       id,
            Octane::ApiFilePath &                     value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByPinID(*this, id, octaneapi::PIN_ID_FILEPATH);
    const auto & fp = response.file_path_value();
    Octane::ApiFilePath fpNative;
    gPackage = fp.package();
    gFilename = fp.filename();
    value.mPackage  = gPackage.c_str();
    value.mFileName = gFilename.c_str();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            bool &                                    value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_BOOL);
    value = response.bool_value();
};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            float &                                   value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_FLOAT);
    value = response.float_value();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::float_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_FLOAT2);
    value.x = response.float2_value().x();
    value.y = response.float2_value().y();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::float_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_FLOAT3);
    value.x = response.float3_value().x();
    value.y = response.float3_value().y();
    value.z = response.float3_value().z();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::float_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_FLOAT4);
    value.x = response.float4_value().x();
    value.y = response.float4_value().y();
    value.z = response.float4_value().z();
    value.w = response.float4_value().w();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            int32_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_INT);
    value = response.int_value();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::int32_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_INT2);
    value.x = response.int2_value().x();
    value.y = response.int2_value().y();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::int32_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_INT3);
    value.x = response.int3_value().x();
    value.y = response.int3_value().y();
    value.z = response.int3_value().z();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::int32_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_INT4);
    value.x = response.int4_value().x();
    value.y = response.int4_value().y();
    value.z = response.int4_value().z();
    value.w = response.int4_value().w();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            OctaneVec::MatrixF &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_MATRIX);
    MatrixConverter::convertMatrixToOctane(response.matrix_value(), value);

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            std::string &                             value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_STRING);
    value = response.string_value();

};


void ApiNodeProxy::getPinValue(
            const char *                              name,
            Octane::ApiFilePath &                     value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    auto response = callGetPinValueByName(*this, strName, octaneapi::PIN_ID_FILEPATH);
    const auto & fp = response.file_path_value();
    Octane::ApiFilePath fpNative;
    gPackage = fp.package();
    gFilename = fp.filename();
    value.mPackage  = gPackage.c_str();
    value.mFileName = gFilename.c_str();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            bool &                                    value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_BOOL);
    value = response.bool_value();
};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            float &                                   value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_FLOAT);
    value = response.float_value();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_FLOAT2);
    value.x = response.float2_value().x();
    value.y = response.float2_value().y();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_FLOAT3);
    value.x = response.float3_value().x();
    value.y = response.float3_value().y();
    value.z = response.float3_value().z();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::float_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_FLOAT4);
    value.x = response.float4_value().x();
    value.y = response.float4_value().y();
    value.z = response.float4_value().z();
    value.w = response.float4_value().w();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            int32_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_INT);
    value = response.int_value();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_2 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_INT2);
    value.x = response.int2_value().x();
    value.y = response.int2_value().y();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_3 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_INT3);
    value.x = response.int3_value().x();
    value.y = response.int3_value().y();
    value.z = response.int3_value().z();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::int32_4 &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_INT4);
    value.x = response.int4_value().x();
    value.y = response.int4_value().y();
    value.z = response.int4_value().z();
    value.w = response.int4_value().w();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            OctaneVec::MatrixF &                      value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_MATRIX);
    MatrixConverter::convertMatrixToOctane(response.matrix_value(), value);

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            std::string &                             value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_STRING);
    value = response.string_value();

};


void ApiNodeProxy::getPinValueIx(
            const uint32_t                            index,
            Octane::ApiFilePath &                     value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic getPinValue() helper that wraps gRPC
    auto response = callGetPinValueByIx(*this, index, octaneapi::PIN_ID_FILEPATH);
    const auto & fp = response.file_path_value();
    Octane::ApiFilePath fpNative;
    gPackage = fp.package();
    gFilename = fp.filename();
    value.mPackage  = gPackage.c_str();
    value.mFileName = gFilename.c_str();

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    request.set_bool_value(value);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    request.set_float_value(value);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    request.set_int_value(value);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    MatrixConverter::convertMatrixToProto(value, *request.mutable_matrix_value());
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const char *const                         value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIDRequest request;
    request.set_evaluate(evaluate);
    request.set_string_value(value);
    auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const Octane::PinId                       id,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
 octaneapi::ApiNode::setPinValueByIDRequest request;
 request.set_evaluate(evaluate);
 auto * fpMsg = new octaneapi::ApiFilePath();
 fpMsg->set_package(value.mPackage);
 fpMsg->set_filename(value.mFileName);
 request.set_allocated_file_path_value(fpMsg);
 auto response = callSetPinValueByPinID(*this, id, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    request.set_bool_value(value);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    request.set_float_value(value);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    request.set_int_value(value);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    MatrixConverter::convertMatrixToProto(value, *request.mutable_matrix_value());
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const char *const                         value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiNode::setPinValueByNameRequest request;
    request.set_evaluate(evaluate);
    request.set_string_value(value);
    auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValue(
            const char *                              name,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
 octaneapi::ApiNode::setPinValueByNameRequest request;
 request.set_evaluate(evaluate);
 auto * fpMsg = new octaneapi::ApiFilePath();
 fpMsg->set_package(value.mPackage);
 fpMsg->set_filename(value.mFileName);
 request.set_allocated_file_path_value(fpMsg);
 auto response = callSetPinValueByName(*this, strName, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    request.set_bool_value(value);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    request.set_float_value(value);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_float4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    request.set_int_value(value);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    auto * v = request.mutable_int4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    MatrixConverter::convertMatrixToProto(value, *request.mutable_matrix_value());
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const char *const                         value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
    octaneapi::ApiNode::setPinValueByIxRequest request;
    request.set_evaluate(evaluate);
    request.set_string_value(value);
    auto response = callSetPinValueByIx(*this, index, request);

};


void ApiNodeProxy::setPinValueIx(
            const uint32_t                            index,
            const Octane::ApiFilePath &               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic setPinValue() helper that wraps gRPC
 octaneapi::ApiNode::setPinValueByIxRequest request;
 request.set_evaluate(evaluate);
 auto * fpMsg = new octaneapi::ApiFilePath();
 fpMsg->set_package(value.mPackage);
 fpMsg->set_filename(value.mFileName);
 request.set_allocated_file_path_value(fpMsg);
 auto response = callSetPinValueByIx(*this, index, request);

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




bool ApiNodeProxy::getPinBool(
            const Octane::PinId                       id
            ) const
{
    bool value = false;
    getPinValue(id, value);
    return value;
};


float ApiNodeProxy::getPinFloat(
            const Octane::PinId                       id
            ) const
{
    float value = false;
    getPinValue(id, value);
    return value;
};


OctaneVec::float_2 ApiNodeProxy::getPinFloat2(
            const Octane::PinId                       id
            ) const
{
    OctaneVec::float_2 value = {0.0f, 0.0f};
    getPinValue(id, value);
    return value;
};


OctaneVec::float_3 ApiNodeProxy::getPinFloat3(
    const Octane::PinId id
) const
{
    OctaneVec::float_3 value = {0.0f, 0.0f, 0.0f};
    getPinValue(id, value);
    return value;
}


OctaneVec::float_4 ApiNodeProxy::getPinFloat4(
    const Octane::PinId id
) const
{
    OctaneVec::float_4 value = {0.0f, 0.0f, 0.0f, 0.0f};
    getPinValue(id, value);
    return value;
}


int32_t ApiNodeProxy::getPinInt(
    const Octane::PinId id
) const
{
    int32_t value = 0;
    getPinValue(id, value);
    return value;
}


OctaneVec::int32_2 ApiNodeProxy::getPinInt2(
    const Octane::PinId id
) const
{
    OctaneVec::int32_2 value = {0, 0};
    getPinValue(id, value);
    return value;
}


OctaneVec::int32_3 ApiNodeProxy::getPinInt3(
    const Octane::PinId id
) const
{
    OctaneVec::int32_3 value = {0, 0, 0};
    getPinValue(id, value);
    return value;
}


OctaneVec::int32_4 ApiNodeProxy::getPinInt4(
    const Octane::PinId id
) const
{
    OctaneVec::int32_4 value = {0, 0, 0, 0};
    getPinValue(id, value);
    return value;
}


OctaneVec::MatrixF ApiNodeProxy::getPinMatrix(
    const Octane::PinId id
) const
{
    OctaneVec::MatrixF value;
    getPinValue(id, value);
    return value;
}


std::string ApiNodeProxy::getPinString(
    const Octane::PinId id
) const
{
    std::string value;
    getPinValue(id, value);
    return value;
}


Octane::ApiFilePath ApiNodeProxy::getPinFilePath(
    const Octane::PinId id
) const
{
    Octane::ApiFilePath value;
    getPinValue(id, value);
    return value;
}


bool ApiNodeProxy::getPinBool(
    const char* name
) const
{
    bool value = false;
    getPinValue(name, value);   // generic gRPC-backed helper, using pin name
    return value;
}


float ApiNodeProxy::getPinFloat(
    const char* name
) const
{
    float value = 0.0f;
    getPinValue(name, value);
    return value;
}


OctaneVec::float_2 ApiNodeProxy::getPinFloat2(
    const char* name
) const
{
    OctaneVec::float_2 value = {0.0f, 0.0f};
    getPinValue(name, value);
    return value;
}


OctaneVec::float_3 ApiNodeProxy::getPinFloat3(
    const char* name
) const
{
    OctaneVec::float_3 value = {0.0f, 0.0f, 0.0f};
    getPinValue(name, value);
    return value;
}


OctaneVec::float_4 ApiNodeProxy::getPinFloat4(
    const char* name
) const
{
    OctaneVec::float_4 value = {0.0f, 0.0f, 0.0f, 0.0f};
    getPinValue(name, value);
    return value;
}


int32_t ApiNodeProxy::getPinInt(
    const char* name
) const
{
    int32_t value = 0;
    getPinValue(name, value);
    return value;
}


OctaneVec::int32_2 ApiNodeProxy::getPinInt2(
    const char* name
) const
{
    OctaneVec::int32_2 value = {0, 0};
    getPinValue(name, value);
    return value;
}


OctaneVec::int32_3 ApiNodeProxy::getPinInt3(
    const char* name
) const
{
    OctaneVec::int32_3 value = {0, 0, 0};
    getPinValue(name, value);
    return value;
}


OctaneVec::int32_4 ApiNodeProxy::getPinInt4(
    const char* name
) const
{
    OctaneVec::int32_4 value = {0, 0, 0, 0};
    getPinValue(name, value);
    return value;
}


OctaneVec::MatrixF ApiNodeProxy::getPinMatrix(
    const char* name
) const
{
    OctaneVec::MatrixF value;
    getPinValue(name, value);
    return value;
}


std::string ApiNodeProxy::getPinString(
    const char* name
) const
{
    std::string value;
    getPinValue(name, value);
    return value;
}


Octane::ApiFilePath ApiNodeProxy::getPinFilePath(
    const char* name
) const
{
    Octane::ApiFilePath value;
    getPinValue(name, value);
    return value;
}


bool ApiNodeProxy::getPinBoolIx(
    const uint32_t index
) const
{
    bool value = false;
    getPinValueIx(index, value);
    return value;
}


float ApiNodeProxy::getPinFloatIx(
    const uint32_t index
) const
{
    float value = 0.0f;
    getPinValueIx(index, value);
    return value;
}


OctaneVec::float_2 ApiNodeProxy::getPinFloat2Ix(
    const uint32_t index
) const
{
    OctaneVec::float_2 value = {0.0f, 0.0f};
    getPinValueIx(index, value);
    return value;
}


OctaneVec::float_3 ApiNodeProxy::getPinFloat3Ix(
    const uint32_t index
) const
{
    OctaneVec::float_3 value = {0.0f, 0.0f, 0.0f};
    getPinValueIx(index, value);
    return value;
}


OctaneVec::float_4 ApiNodeProxy::getPinFloat4Ix(
    const uint32_t index
) const
{
    OctaneVec::float_4 value = {0.0f, 0.0f, 0.0f, 0.0f};
    getPinValueIx(index, value);
    return value;
}


int32_t ApiNodeProxy::getPinIntIx(
    const uint32_t index
) const
{
    int32_t value = 0;
    getPinValueIx(index, value);
    return value;
}


OctaneVec::int32_2 ApiNodeProxy::getPinInt2Ix(
    const uint32_t index
) const
{
    OctaneVec::int32_2 value = {0, 0};
    getPinValueIx(index, value);
    return value;
}


OctaneVec::int32_3 ApiNodeProxy::getPinInt3Ix(
    const uint32_t index
) const
{
    OctaneVec::int32_3 value = {0, 0, 0};
    getPinValueIx(index, value);
    return value;
}


OctaneVec::int32_4 ApiNodeProxy::getPinInt4Ix(
    const uint32_t index
) const
{
    OctaneVec::int32_4 value = {0, 0, 0, 0};
    getPinValueIx(index, value);
    return value;
}


OctaneVec::MatrixF ApiNodeProxy::getPinMatrixIx(
    const uint32_t index
) const
{
    OctaneVec::MatrixF value;
    getPinValueIx(index, value);
    return value;
}


std::string ApiNodeProxy::getPinStringIx(
    const uint32_t index
) const
{
    std::string value;
    getPinValueIx(index, value);
    return value;
}


Octane::ApiFilePath ApiNodeProxy::getPinFilePathIx(
    const uint32_t index
) const
{
    Octane::ApiFilePath value;
    getPinValueIx(index, value);
    return value;
}

} //end of namespace
