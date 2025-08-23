// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apiitemclient.h"
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
#include "apinodeclient.h"
#include "apinodegraphclient.h"
#include "apiattributeinfoclient.h"
#include "apiitemarrayclient.h"
#include "apitimesamplingclient.h"
#include "apirootnodegraphclient.h"
#include "../grpcapinodeinfo.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapiattributeinfo.h"
#include "convertapitimesampling.h"


namespace OctaneGRPC
{

octaneapi::ApiItem::getArrayResponse callGetArrayByAttrID(
        const ApiItemProxy&                   proxy,
        const Octane::AttributeId             id,
        octaneapi::AttributeTypeId            expectedType)
{
    octaneapi::ApiItem::getArrayByIDRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    request.set_attribute_id(static_cast<octaneapi::AttributeId>(id));
    request.set_expected_type(expectedType);

    octaneapi::ApiItem::getArrayResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getArrayByAttrID(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getArrayByAttrID error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::getArrayResponse callGetArrayByName(
        const ApiItemProxy&                   proxy,
        const std::string&                    name,
        octaneapi::AttributeTypeId            expectedType)
{
    octaneapi::ApiItem::getArrayByNameRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    request.set_name(name);
    request.set_expected_type(expectedType);

    octaneapi::ApiItem::getArrayResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getArrayByName(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getArrayByName error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::getArrayResponse callGetArrayByIx(
        const ApiItemProxy&                   proxy,
        uint32_t                              index,
        octaneapi::AttributeTypeId            expectedType)
{
    octaneapi::ApiItem::getArrayByIxRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    request.set_index(index);
    request.set_expected_type(expectedType);

    octaneapi::ApiItem::getArrayResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getArrayByIx(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getArrayByIx error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}

octaneapi::ApiItem::getValueResponse callGetByAttrID(
    const ApiItemProxy&                   proxy,
    const Octane::AttributeId             id,
    octaneapi::AttributeTypeId            expectedType)
{
    // Build request
    octaneapi::ApiItem::getValueByIDRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    // Correct cast to proto enum
    request.set_attribute_id(static_cast<octaneapi::AttributeId>(id));
    request.set_expected_type(expectedType);

    // Response + call
    octaneapi::ApiItem::getValueResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getByAttrID(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getByAttrID error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::getValueResponse callGetByName(
        const ApiItemProxy&                   proxy,
        const std::string &                   name,
        octaneapi::AttributeTypeId            expectedType)
{
    octaneapi::ApiItem::getValueByNameRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    request.set_name(name);
    request.set_expected_type(expectedType);

    octaneapi::ApiItem::getValueResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getByName(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getByName error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::getValueResponse callGetByIx(
        const ApiItemProxy&                   proxy,
        uint32_t                              index,
        octaneapi::AttributeTypeId            expectedType)
{
    octaneapi::ApiItem::getValueByIxRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    request.set_index(index);
    request.set_expected_type(expectedType);

    octaneapi::ApiItem::getValueResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getByIx(context.get(), request, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC getByIx error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::getAnimArrayResponse callGetAnimByAttr(
        const ApiItemProxy&                   proxy,
        const Octane::AttributeId             id,
        octaneapi::AttributeTypeId            expectedType,
        bool                                  returnNumSamples)
{
    octaneapi::ApiItem::getAnimByIDRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    request.set_attribute_id(static_cast<octaneapi::AttributeId>(id));
    request.set_expected_type(expectedType);
    request.set_want_num_samples (returnNumSamples);

    octaneapi::ApiItem::getAnimArrayResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getAnimByAttr(context.get(), request, &response);
    if (!status.ok())
        throw std::runtime_error("gRPC getAnimByAttr error (" +
                                 std::to_string(status.error_code()) + "): " +
                                 status.error_message());

    return response;
}


octaneapi::ApiItem::getAnimArrayResponse callGetAnimByName(
        const ApiItemProxy&                   proxy,
        const std::string&                    name,
        octaneapi::AttributeTypeId            expectedType,
        bool                                  returnNumSamples)
{
    octaneapi::ApiItem::getAnimByNameRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    request.set_name(name);
    request.set_expected_type(expectedType);
    request.set_want_num_samples (returnNumSamples);

    octaneapi::ApiItem::getAnimArrayResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getAnimByName(context.get(), request, &response);
    if (!status.ok())
        throw std::runtime_error("gRPC getAnimByName error (" +
                                 std::to_string(status.error_code()) + "): " +
                                 status.error_message());

    return response;
}


octaneapi::ApiItem::getAnimArrayResponse callGetAnimByIx(
        const ApiItemProxy&                   proxy,
        uint32_t                              index,
        octaneapi::AttributeTypeId            expectedType,
        bool                                  returnNumSamples)
{
    octaneapi::ApiItem::getAnimByIxRequest request;
    auto* ref = request.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    request.set_index(index);
    request.set_expected_type(expectedType);
    request.set_want_num_samples (returnNumSamples);

    octaneapi::ApiItem::getAnimArrayResponse response;
    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->getAnimByIx(context.get(), request, &response);
    if (!status.ok())
        throw std::runtime_error("gRPC getAnimByIx error (" +
                                 std::to_string(status.error_code()) + "): " +
                                 status.error_message());

    return response;
}

octaneapi::ApiItem::setValueResponse callSetByAttrID(
        const ApiItemProxy&                          proxy,
        const Octane::AttributeId                    id,
        const octaneapi::ApiItem::setValueByIDRequest& request
        )
{
    octaneapi::ApiItem::setValueResponse response;

    // make a copy of request with item_ref + attribute_id filled
    octaneapi::ApiItem::setValueByIDRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_attribute_id(static_cast<octaneapi::AttributeId>(id));

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setByAttrID(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setByAttrID error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }

    return response;
}


octaneapi::ApiItem::setValueResponse callSetByName(
        const ApiItemProxy&                          proxy,
        const std::string&                           name,
        const octaneapi::ApiItem::setValueByNameRequest& request
        )
{
    octaneapi::ApiItem::setValueResponse response;

    octaneapi::ApiItem::setValueByNameRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_name(name);

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setByName(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setByName error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }

    return response;
}


octaneapi::ApiItem::setValueResponse callSetByIx(
        const ApiItemProxy&                          proxy,
        uint32_t                                     index,
        const octaneapi::ApiItem::setValueByIxRequest& request
        )
{
    octaneapi::ApiItem::setValueResponse response;

    octaneapi::ApiItem::setValueByIxRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_index(index);

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setByIx(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setByIx error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }

    return response;
}


octaneapi::ApiItem::setArrayResponse callSetArrayByAttrID(
        const ApiItemProxy&                           proxy,
        const Octane::AttributeId                     id,
        const octaneapi::ApiItem::setArrayByIDRequest& request
        )
{
    octaneapi::ApiItem::setArrayResponse response;

    // copy request so we can fill extra required fields
    octaneapi::ApiItem::setArrayByIDRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_attribute_id(static_cast<octaneapi::AttributeId>(id));

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setArrayByAttrID(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setArrayByAttrID error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::setArrayResponse callSetArrayByName(
        const ApiItemProxy&                              proxy,
        const std::string&                               name,
        const octaneapi::ApiItem::setArrayByNameRequest& request
        )
{
    octaneapi::ApiItem::setArrayResponse response;

    octaneapi::ApiItem::setArrayByNameRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_name(name);

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setArrayByName(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setArrayByName error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::setArrayResponse callSetArrayByIx(
        const ApiItemProxy&                           proxy,
        uint32_t                                      index,
        const octaneapi::ApiItem::setArrayByIxRequest& request
        )
{
    octaneapi::ApiItem::setArrayResponse response;

    octaneapi::ApiItem::setArrayByIxRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_index(index);

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setArrayByIx(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setArrayByIx error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::setAnimArrayResponse callSetAnimByAttr(
        const ApiItemProxy&                            proxy,
        const Octane::AttributeId                      id,
        const octaneapi::ApiItem::setAnimByIDRequest&  request
        )
{
    octaneapi::ApiItem::setAnimArrayResponse response;

    // Copy incoming request and augment with object ref + id
    octaneapi::ApiItem::setAnimByIDRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_attribute_id(static_cast<octaneapi::AttributeId>(id));

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setAnimByAttr(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setAnimByAttr error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::setAnimArrayResponse callSetAnimByName(
        const ApiItemProxy&                               proxy,
        const std::string&                                name,
        const octaneapi::ApiItem::setAnimByNameRequest&   request
        )
{
    octaneapi::ApiItem::setAnimArrayResponse response;

    octaneapi::ApiItem::setAnimByNameRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_name(name);

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setAnimByName(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setAnimByName error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}


octaneapi::ApiItem::setAnimArrayResponse callSetAnimByIx(
        const ApiItemProxy&                            proxy,
        uint32_t                                       index,
        const octaneapi::ApiItem::setAnimByIxRequest&  request
        )
{
    octaneapi::ApiItem::setAnimArrayResponse response;

    octaneapi::ApiItem::setAnimByIxRequest req = request;
    auto* ref = req.mutable_item_ref();
    ref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    ref->set_handle(proxy.getObjectHandle());

    req.set_index(index);

    auto stub = octaneapi::ApiItemService::NewStub(proxy.getGRPCSettings().getChannel());
    auto context = std::make_unique<grpc::ClientContext>();

    grpc::Status status = stub->setAnimByIx(context.get(), req, &response);
    if (!status.ok())
    {
        throw std::runtime_error("gRPC setAnimByIx error (" +
                                    std::to_string(status.error_code()) + "): " +
                                    status.error_message());
    }
    return response;
}

GRPCSettings & ApiItemProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiItemProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
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


std::string ApiItemProxy::name() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::nameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::nameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->name(context.get(), request, &response);

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


void ApiItemProxy::setName(
            const char *                              name
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::setNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->setName(context.get(), request, &response);

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


OctaneVec::float_2 ApiItemProxy::position() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::positionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::positionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->position(context.get(), request, &response);

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


void ApiItemProxy::setPosition(
            const OctaneVec::float_2                  newPos
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::setPositionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newPos' [in] parameter to the request packet.
    octaneapi::float_2 * newposIn = new octaneapi::float_2();
    (*newposIn).set_x(newPos.x);
    (*newposIn).set_y(newPos.y);
    request.set_allocated_newpos(newposIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPosition(context.get(), request, &response);

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


void ApiItemProxy::setUIOperationFlags(
            const Octane::enum_t                      flags
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::setUIOperationFlagsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'flags' [in] parameter to the request packet.
    octaneapi::enum_t * flagsIn = new octaneapi::enum_t();
    (*flagsIn).set_id(flags);
    request.set_allocated_flags(flagsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->setUIOperationFlags(context.get(), request, &response);

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


Octane::enum_t ApiItemProxy::uiOperationFlags() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::uiOperationFlagsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::uiOperationFlagsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->uiOperationFlags(context.get(), request, &response);

    Octane::enum_t retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::enum_t resultOut = response.result();
        retVal = resultOut.id();
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


void ApiItemProxy::select() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::selectRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->select(context.get(), request, &response);

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


Octane::TimeT ApiItemProxy::time() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::timeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::timeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->time(context.get(), request, &response);

    Octane::TimeT retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::TimeT resultOut = response.result();
        retVal = resultOut.value();
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


Octane::NodePinType ApiItemProxy::outType() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::outTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::outTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->outType(context.get(), request, &response);

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


uint64_t ApiItemProxy::persistentId() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::persistentIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::persistentIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->persistentId(context.get(), request, &response);

    uint64_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint64_t resultOut = response.result();
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


uint32_t ApiItemProxy::uniqueId() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::uniqueIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::uniqueIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->uniqueId(context.get(), request, &response);

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


void ApiItemProxy::collectItemTree(
            ApiItemArrayProxy &                       treeItems
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::collectItemTreeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'treeItems' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * treeitemsIn = new octaneapi::ObjectRef();
    treeitemsIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItemArray);
    treeitemsIn->set_handle(treeItems.getObjectHandle());
    request.set_allocated_treeitems(treeitemsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::collectItemTreeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->collectItemTree(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'treeItems' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef treeItemsOut = response.treeitems();
        treeItems.attachObjectHandle(treeItemsOut.handle());
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


void ApiItemProxy::deleteUnconnectedItems() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::deleteUnconnectedItemsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->deleteUnconnectedItems(context.get(), request, &response);

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


void ApiItemProxy::switchToFileData(
            const char *                              destinationDir
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::switchToFileDataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'destinationDir' [in] parameter to the request packet.
    std::string * destinationdirIn = new std::string();
    *destinationdirIn = checkString(destinationDir);
    request.set_allocated_destinationdir(destinationdirIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->switchToFileData(context.get(), request, &response);

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


Octane::VersionT ApiItemProxy::version() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::versionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::versionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->version(context.get(), request, &response);

    Octane::VersionT retVal;
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


bool ApiItemProxy::isGraph() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isGraphResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isGraph(context.get(), request, &response);

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


bool ApiItemProxy::isNode() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isNode(context.get(), request, &response);

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


bool ApiItemProxy::isLinker() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isLinkerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isLinkerResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isLinker(context.get(), request, &response);

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


bool ApiItemProxy::isInputLinker() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isInputLinkerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isInputLinkerResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isInputLinker(context.get(), request, &response);

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


bool ApiItemProxy::isOutputLinker() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isOutputLinkerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isOutputLinkerResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isOutputLinker(context.get(), request, &response);

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


ApiNodeGraphProxy ApiItemProxy::toGraph() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::toGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::toGraphResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->toGraph(context.get(), request, &response);

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


ApiNodeProxy ApiItemProxy::toNode() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::toNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::toNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->toNode(context.get(), request, &response);

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


ApiNodeGraphProxy ApiItemProxy::toGraph()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::toGraph1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::toGraph1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->toGraph1(context.get(), request, &response);

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


ApiNodeProxy ApiItemProxy::toNode()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::toNode1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::toNode1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->toNode1(context.get(), request, &response);

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


bool ApiItemProxy::hasOwner() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::hasOwnerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::hasOwnerResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasOwner(context.get(), request, &response);

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


bool ApiItemProxy::graphOwned() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::graphOwnedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::graphOwnedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->graphOwned(context.get(), request, &response);

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


bool ApiItemProxy::pinOwned() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::pinOwnedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::pinOwnedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinOwned(context.get(), request, &response);

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


ApiNodeGraphProxy ApiItemProxy::graphOwner() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::graphOwnerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::graphOwnerResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->graphOwner(context.get(), request, &response);

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


ApiNodeProxy ApiItemProxy::pinOwner(
            uint32_t &                                pinIx
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::pinOwnerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::pinOwnerResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinOwner(context.get(), request, &response);

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

        /////////////////////////////////////////////////////////////////////
        // Process 'pinIx' [out] parameter from the gRPC response packet
        uint32_t pinIxOut = response.pinix();
        pinIx = pinIxOut;
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


ApiRootNodeGraphProxy ApiItemProxy::rootGraph() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::rootGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::rootGraphResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->rootGraph(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiRootNodeGraphProxy retVal;
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
        ApiRootNodeGraphProxy retVal;
        return retVal;
    }
};


ApiRootNodeGraphProxy ApiItemProxy::rootGraph()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::rootGraph1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::rootGraph1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->rootGraph1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiRootNodeGraphProxy retVal;
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
        ApiRootNodeGraphProxy retVal;
        return retVal;
    }
};


uint32_t ApiItemProxy::attrCount() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrCount(context.get(), request, &response);

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


bool ApiItemProxy::hasAttr(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::hasAttrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::hasAttrResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasAttr(context.get(), request, &response);

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


bool ApiItemProxy::hasAttr(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::hasAttr1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::hasAttr1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasAttr1(context.get(), request, &response);

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


bool ApiItemProxy::findAttr(
            const Octane::AttributeId                 id,
            uint32_t &                                foundIndex
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::findAttrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::findAttrResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->findAttr(context.get(), request, &response);

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


bool ApiItemProxy::findAttr(
            const char *                              name,
            uint32_t &                                foundIndex
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::findAttr1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::findAttr1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->findAttr1(context.get(), request, &response);

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


Octane::AttributeId ApiItemProxy::attrId(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrId(context.get(), request, &response);

    Octane::AttributeId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::AttributeId resultOut = response.result();
        retVal = static_cast<Octane::AttributeId>(resultOut);
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


Octane::AttributeId ApiItemProxy::attrIdIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrIdIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrIdIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrIdIx(context.get(), request, &response);

    Octane::AttributeId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::AttributeId resultOut = response.result();
        retVal = static_cast<Octane::AttributeId>(resultOut);
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


std::string ApiItemProxy::attrName(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrName(context.get(), request, &response);

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


std::string ApiItemProxy::attrNameIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrNameIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrNameIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrNameIx(context.get(), request, &response);

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


Octane::AttributeType ApiItemProxy::attrType(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrType(context.get(), request, &response);

    Octane::AttributeType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::AttributeType resultOut = response.result();
        retVal = static_cast<Octane::AttributeType>(resultOut);
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


Octane::AttributeType ApiItemProxy::attrType(
            const char *                              attrName
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrType1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'attrName' [in] parameter to the request packet.
    std::string * attrnameIn = new std::string();
    *attrnameIn = checkString(attrName);
    request.set_allocated_attrname(attrnameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrType1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrType1(context.get(), request, &response);

    Octane::AttributeType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::AttributeType resultOut = response.result();
        retVal = static_cast<Octane::AttributeType>(resultOut);
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


Octane::AttributeType ApiItemProxy::attrTypeIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrTypeIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrTypeIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrTypeIx(context.get(), request, &response);

    Octane::AttributeType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::AttributeType resultOut = response.result();
        retVal = static_cast<Octane::AttributeType>(resultOut);
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


const Octane::ApiAttributeInfo ApiItemProxy::attrInfo(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrInfo(context.get(), request, &response);

    Octane::ApiAttributeInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiAttributeInfo resultOut = response.result();
        ApiAttributeInfoConverter::convert(resultOut, retVal);
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


const Octane::ApiAttributeInfo ApiItemProxy::attrInfo(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrInfo1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrInfo1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrInfo1(context.get(), request, &response);

    Octane::ApiAttributeInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiAttributeInfo resultOut = response.result();
        ApiAttributeInfoConverter::convert(resultOut, retVal);
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


const Octane::ApiAttributeInfo ApiItemProxy::attrInfoIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrInfoIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrInfoIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrInfoIx(context.get(), request, &response);

    Octane::ApiAttributeInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiAttributeInfo resultOut = response.result();
        ApiAttributeInfoConverter::convert(resultOut, retVal);
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


bool ApiItemProxy::attrAreDirty() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::attrAreDirtyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::attrAreDirtyResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->attrAreDirty(context.get(), request, &response);

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


bool ApiItemProxy::isDirtyAttr(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isDirtyAttrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isDirtyAttrResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDirtyAttr(context.get(), request, &response);

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


bool ApiItemProxy::isDirtyAttr(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isDirtyAttr1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isDirtyAttr1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDirtyAttr1(context.get(), request, &response);

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


bool ApiItemProxy::isDirtyAttrIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isDirtyAttrIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isDirtyAttrIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDirtyAttrIx(context.get(), request, &response);

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


void ApiItemProxy::copyAttrFrom(
            const Octane::AttributeId                 destId,
            const ApiItemProxy &                      srcItem,
            const Octane::AttributeId                 srcId,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::copyAttrFromRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'destId' [in] parameter to the request packet.
    octaneapi::AttributeId destidIn;
        destidIn = static_cast<octaneapi::AttributeId>(destId);
    request.set_destid(destidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'srcItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * srcitemIn = new octaneapi::ObjectRef();
    srcitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    srcitemIn->set_handle(srcItem.getObjectHandle());
    request.set_allocated_srcitem(srcitemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'srcId' [in] parameter to the request packet.
    octaneapi::AttributeId srcidIn;
        srcidIn = static_cast<octaneapi::AttributeId>(srcId);
    request.set_srcid(srcidIn);

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
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyAttrFrom(context.get(), request, &response);

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


void ApiItemProxy::copyAttrFrom(
            const Octane::AttributeId                 destId,
            const ApiItemProxy &                      srcItem,
            const char *                              srcAttrName,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::copyAttrFrom1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'destId' [in] parameter to the request packet.
    octaneapi::AttributeId destidIn;
        destidIn = static_cast<octaneapi::AttributeId>(destId);
    request.set_destid(destidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'srcItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * srcitemIn = new octaneapi::ObjectRef();
    srcitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    srcitemIn->set_handle(srcItem.getObjectHandle());
    request.set_allocated_srcitem(srcitemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'srcAttrName' [in] parameter to the request packet.
    std::string * srcattrnameIn = new std::string();
    *srcattrnameIn = checkString(srcAttrName);
    request.set_allocated_srcattrname(srcattrnameIn);

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
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyAttrFrom1(context.get(), request, &response);

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


void ApiItemProxy::copyAttrFromIx(
            const Octane::AttributeId                 destId,
            const ApiItemProxy &                      srcItem,
            const uint32_t                            srcAttrIx,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::copyAttrFromIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'destId' [in] parameter to the request packet.
    octaneapi::AttributeId destidIn;
        destidIn = static_cast<octaneapi::AttributeId>(destId);
    request.set_destid(destidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'srcItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * srcitemIn = new octaneapi::ObjectRef();
    srcitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    srcitemIn->set_handle(srcItem.getObjectHandle());
    request.set_allocated_srcitem(srcitemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'srcAttrIx' [in] parameter to the request packet.
    uint32_t srcattrixIn;
    srcattrixIn = srcAttrIx;
    request.set_srcattrix(srcattrixIn);

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
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyAttrFromIx(context.get(), request, &response);

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


void ApiItemProxy::copyAttrFrom(
            const ApiItemProxy &                      srcItem,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::copyAttrFrom2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'srcItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * srcitemIn = new octaneapi::ObjectRef();
    srcitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    srcitemIn->set_handle(srcItem.getObjectHandle());
    request.set_allocated_srcitem(srcitemIn);

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
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->copyAttrFrom2(context.get(), request, &response);

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


void ApiItemProxy::clearAllAttr(
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::clearAllAttrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

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
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearAllAttr(context.get(), request, &response);

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


void ApiItemProxy::clearAttr(
            const Octane::AttributeId                 id,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::clearAttrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

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
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearAttr(context.get(), request, &response);

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


void ApiItemProxy::clearAttr(
            const char *                              name,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::clearAttr1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

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
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearAttr1(context.get(), request, &response);

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


void ApiItemProxy::clearAttrIx(
            const uint32_t                            index,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::clearAttrIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

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
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearAttrIx(context.get(), request, &response);

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


bool ApiItemProxy::getBool(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_BOOL);
    return response.bool_value();
};


int32_t ApiItemProxy::getInt(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_INT);
    return response.int_value();

};


OctaneVec::int32_2 ApiItemProxy::getInt2(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_INT2);
    OctaneVec::int32_2 result;
    result.x = response.int2_value().x();
    result.y = response.int2_value().y();
    return result;

};


OctaneVec::int32_3 ApiItemProxy::getInt3(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_INT3);
    OctaneVec::int32_3 result;
    result.x = response.int3_value().x();
    result.y = response.int3_value().y();
    result.z = response.int3_value().z();
    return result;

};


OctaneVec::int32_4 ApiItemProxy::getInt4(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_INT4);
    OctaneVec::int32_4 result;
    result.x = response.int4_value().x();
    result.y = response.int4_value().y();
    result.z = response.int4_value().z();
    result.w = response.int4_value().w();
    return result;

};


int64_t ApiItemProxy::getLong(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_LONG);
    return response.long_value();

};


OctaneVec::int64_2 ApiItemProxy::getLong2(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_LONG2);
    OctaneVec::int64_2 result;
    result.x = response.long2_value().x();
    result.y = response.long2_value().y();
    return result;

};


float ApiItemProxy::getFloat(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_FLOAT);
    return response.float_value();

};


OctaneVec::float_2 ApiItemProxy::getFloat2(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_FLOAT2);
    OctaneVec::float_2 result;
    result.x = response.float2_value().x();
    result.y = response.float2_value().y();
    return result;

};


OctaneVec::float_3 ApiItemProxy::getFloat3(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_FLOAT3);
    OctaneVec::float_3 result;
    result.x = response.float3_value().x();
    result.y = response.float3_value().y();
    result.z = response.float3_value().z();
    return result;

};


OctaneVec::float_4 ApiItemProxy::getFloat4(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_FLOAT4);
    OctaneVec::float_4 result;
    result.x = response.float4_value().x();
    result.y = response.float4_value().y();
    result.z = response.float4_value().z();
    result.w = response.float4_value().w();
    return result;

};


OctaneVec::MatrixF ApiItemProxy::getMatrix(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_MATRIX);
    OctaneVec::MatrixF result;
    MatrixConverter::convertMatrixToOctane(response.matrix_value(), result);
    return result;

};


std::string ApiItemProxy::getString(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByAttrID(*this, id, octaneapi::ATTR_ID_STRING);
    return response.string_value();

};


std::vector<bool> ApiItemProxy::getBoolArray(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<bool> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_BOOL);
    result.reserve(response.bool_array().data_size());
    for (auto v : response.bool_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<int> ApiItemProxy::getIntArray(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<int> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_INT);
    result.reserve(response.int_array().data_size());
    for (auto v : response.int_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::int32_2> ApiItemProxy::getInt2Array(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::int32_2> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_INT2);
    result.reserve(response.int2_array().data_size());
    for (const auto & e : response.int2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<OctaneVec::int32_3> ApiItemProxy::getInt3Array(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::int32_3> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_INT3);
    result.reserve(response.int3_array().data_size());
    for (const auto & e : response.int3_array().data())
    {
        result.push_back({e.x(), e.y(), e.z()});
    }
    return result;

};


std::vector<OctaneVec::int32_4> ApiItemProxy::getInt4Array(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::int32_4> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_INT4);
    result.reserve(response.int4_array().data_size());
    for (const auto & e : response.int4_array().data())
    {
        result.push_back({e.x(), e.y(), e.z(), e.w()});
    }
    return result;

};


std::vector<long> ApiItemProxy::getLongArray(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<long> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_LONG);
    result.reserve(response.long_array().data_size());
    for (auto v : response.long_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::int64_2> ApiItemProxy::getLong2Array(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::int64_2> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_LONG2);
    result.reserve(response.long2_array().data_size());
    for (const auto & e : response.long2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<Octane::MatrixF> ApiItemProxy::getMatrixArray(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::MatrixF> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_MATRIX);
    result.reserve(response.matrix_array().data_size());
    for (const auto & e : response.matrix_array().data())
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(e, m);
        result.push_back(m);
    }
    return result;

};


std::vector<float> ApiItemProxy::getFloatArray(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<float> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_FLOAT);
    result.reserve(response.float_array().data_size());
    for (auto v : response.float_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::float_2> ApiItemProxy::getFloat2Array(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::float_2> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_FLOAT2);
    result.reserve(response.float2_array().data_size());
    for (const auto & e : response.float2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<OctaneVec::float_3> ApiItemProxy::getFloat3Array(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::float_3> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_FLOAT3);
    result.reserve(response.float3_array().data_size());
    for (const auto & e : response.float3_array().data())
    {
        result.push_back({e.x(), e.y(), e.z()});
    }
    return result;

};


std::vector<OctaneVec::float_4> ApiItemProxy::getFloat4Array(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::float_4> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_FLOAT4);
    result.reserve(response.float4_array().data_size());
    for (const auto & e : response.float4_array().data())
    {
        result.push_back({e.x(), e.y(), e.z(), e.w()});
    }
    return result;

};


std::vector<std::string> ApiItemProxy::getStringArray(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<std::string> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_STRING);
    result.reserve(response.string_array().data_size());
    for (auto & s : response.string_array().data())
    {
        result.push_back(s);
    }
    return result;

};


std::vector<uint8_t> ApiItemProxy::getByteArray(
            const Octane::AttributeId                 id
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<uint8_t> result;
    auto response = callGetArrayByAttrID(*this, id, octaneapi::ATTR_ID_BYTE);
    const std::string & bytes = response.byte_array().data();
    result.assign(bytes.begin(), bytes.end());
    return result;

};


bool ApiItemProxy::getBool(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_BOOL);
    return response.bool_value();
};


int32_t ApiItemProxy::getInt(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_INT);
    return response.int_value();

};


OctaneVec::int32_2 ApiItemProxy::getInt2(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_INT2);
    OctaneVec::int32_2 result;
    result.x = response.int2_value().x();
    result.y = response.int2_value().y();
    return result;

};


OctaneVec::int32_3 ApiItemProxy::getInt3(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_INT3);
    OctaneVec::int32_3 result;
    result.x = response.int3_value().x();
    result.y = response.int3_value().y();
    result.z = response.int3_value().z();
    return result;

};


OctaneVec::int32_4 ApiItemProxy::getInt4(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_INT4);
    OctaneVec::int32_4 result;
    result.x = response.int4_value().x();
    result.y = response.int4_value().y();
    result.z = response.int4_value().z();
    result.w = response.int4_value().w();
    return result;

};


int64_t ApiItemProxy::getLong(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_LONG);
    return response.long_value();

};


OctaneVec::int64_2 ApiItemProxy::getLong2(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_LONG2);
    OctaneVec::int64_2 result;
    result.x = response.long2_value().x();
    result.y = response.long2_value().y();
    return result;

};


float ApiItemProxy::getFloat(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_FLOAT);
    return response.float_value();

};


OctaneVec::float_2 ApiItemProxy::getFloat2(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_FLOAT2);
    OctaneVec::float_2 result;
    result.x = response.float2_value().x();
    result.y = response.float2_value().y();
    return result;

};


OctaneVec::float_3 ApiItemProxy::getFloat3(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_FLOAT3);
    OctaneVec::float_3 result;
    result.x = response.float3_value().x();
    result.y = response.float3_value().y();
    result.z = response.float3_value().z();
    return result;

};


OctaneVec::float_4 ApiItemProxy::getFloat4(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_FLOAT4);
    OctaneVec::float_4 result;
    result.x = response.float4_value().x();
    result.y = response.float4_value().y();
    result.z = response.float4_value().z();
    result.w = response.float4_value().w();
    return result;

};


OctaneVec::MatrixF ApiItemProxy::getMatrix(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_MATRIX);
    OctaneVec::MatrixF result;
    MatrixConverter::convertMatrixToOctane(response.matrix_value(), result);
    return result;

};


std::string ApiItemProxy::getString(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
auto response = callGetByName(*this, strName, octaneapi::ATTR_ID_STRING);
    return response.string_value();

};


std::vector<bool> ApiItemProxy::getBoolArray(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<bool> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_BOOL);
    result.reserve(response.bool_array().data_size());
    for (auto v : response.bool_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<int> ApiItemProxy::getIntArray(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<int> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_INT);
    result.reserve(response.int_array().data_size());
    for (auto v : response.int_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::int32_2> ApiItemProxy::getInt2Array(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<OctaneVec::int32_2> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_INT2);
    result.reserve(response.int2_array().data_size());
    for (const auto & e : response.int2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<OctaneVec::int32_3> ApiItemProxy::getInt3Array(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<OctaneVec::int32_3> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_INT3);
    result.reserve(response.int3_array().data_size());
    for (const auto & e : response.int3_array().data())
    {
        result.push_back({e.x(), e.y(), e.z()});
    }
    return result;

};


std::vector<OctaneVec::int32_4> ApiItemProxy::getInt4Array(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<OctaneVec::int32_4> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_INT4);
    result.reserve(response.int4_array().data_size());
    for (const auto & e : response.int4_array().data())
    {
        result.push_back({e.x(), e.y(), e.z(), e.w()});
    }
    return result;

};


std::vector<long> ApiItemProxy::getLongArray(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<long> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_LONG);
    result.reserve(response.long_array().data_size());
    for (auto v : response.long_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::int64_2> ApiItemProxy::getLong2Array(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<OctaneVec::int64_2> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_LONG2);
    result.reserve(response.long2_array().data_size());
    for (const auto & e : response.long2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<float> ApiItemProxy::getFloatArray(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<float> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_FLOAT);
    result.reserve(response.float_array().data_size());
    for (auto v : response.float_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::float_2> ApiItemProxy::getFloat2Array(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<OctaneVec::float_2> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_FLOAT2);
    result.reserve(response.float2_array().data_size());
    for (const auto & e : response.float2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<OctaneVec::float_3> ApiItemProxy::getFloat3Array(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<OctaneVec::float_3> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_FLOAT3);
    result.reserve(response.float3_array().data_size());
    for (const auto & e : response.float3_array().data())
    {
        result.push_back({e.x(), e.y(), e.z()});
    }
    return result;

};


std::vector<OctaneVec::float_4> ApiItemProxy::getFloat4Array(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<OctaneVec::float_4> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_FLOAT4);
    result.reserve(response.float4_array().data_size());
    for (const auto & e : response.float4_array().data())
    {
        result.push_back({e.x(), e.y(), e.z(), e.w()});
    }
    return result;

};


std::vector<Octane::MatrixF> ApiItemProxy::getMatrixArray(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<OctaneVec::MatrixF> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_MATRIX);
    result.reserve(response.matrix_array().data_size());
    for (const auto & e : response.matrix_array().data())
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(e, m);
        result.push_back(m);
    }
    return result;

};


std::vector<std::string> ApiItemProxy::getStringArray(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<std::string> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_STRING);
    result.reserve(response.string_array().data_size());
    for (auto & s : response.string_array().data())
    {
        result.push_back(s);
    }
    return result;

};


std::vector<uint8_t> ApiItemProxy::getByteArray(
            const char *                              name
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
std::vector<uint8_t> result;
    auto response = callGetArrayByName(*this, strName, octaneapi::ATTR_ID_BYTE);
    const std::string & bytes = response.byte_array().data();
    result.assign(bytes.begin(), bytes.end());
    return result;

};


bool ApiItemProxy::getBoolIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_BOOL);
    return response.bool_value();
};


int32_t ApiItemProxy::getIntIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_INT);
    return response.int_value();

};


OctaneVec::int32_2 ApiItemProxy::getInt2Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_INT2);
    OctaneVec::int32_2 result;
    result.x = response.int2_value().x();
    result.y = response.int2_value().y();
    return result;

};


OctaneVec::int32_3 ApiItemProxy::getInt3Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_INT3);
    OctaneVec::int32_3 result;
    result.x = response.int3_value().x();
    result.y = response.int3_value().y();
    result.z = response.int3_value().z();
    return result;

};


OctaneVec::int32_4 ApiItemProxy::getInt4Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_INT4);
    OctaneVec::int32_4 result;
    result.x = response.int4_value().x();
    result.y = response.int4_value().y();
    result.z = response.int4_value().z();
    result.w = response.int4_value().w();
    return result;

};


int64_t ApiItemProxy::getLongIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_LONG);
    return response.long_value();

};


OctaneVec::int64_2 ApiItemProxy::getLong2Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_LONG2);
    OctaneVec::int64_2 result;
    result.x = response.long2_value().x();
    result.y = response.long2_value().y();
    return result;

};


float ApiItemProxy::getFloatIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_FLOAT);
    return response.float_value();

};


OctaneVec::float_2 ApiItemProxy::getFloat2Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_FLOAT2);
    OctaneVec::float_2 result;
    result.x = response.float2_value().x();
    result.y = response.float2_value().y();
    return result;

};


OctaneVec::float_3 ApiItemProxy::getFloat3Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_FLOAT3);
    OctaneVec::float_3 result;
    result.x = response.float3_value().x();
    result.y = response.float3_value().y();
    result.z = response.float3_value().z();
    return result;

};


OctaneVec::float_4 ApiItemProxy::getFloat4Ix(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_FLOAT4);
    OctaneVec::float_4 result;
    result.x = response.float4_value().x();
    result.y = response.float4_value().y();
    result.z = response.float4_value().z();
    result.w = response.float4_value().w();
    return result;

};


OctaneVec::MatrixF ApiItemProxy::getMatrixIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_MATRIX);
    OctaneVec::MatrixF result;
    MatrixConverter::convertMatrixToOctane(response.matrix_value(), result);
    return result;

};


std::string ApiItemProxy::getStringIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
auto response = callGetByIx(*this, index, octaneapi::ATTR_ID_STRING);
    return response.string_value();

};


std::vector<bool> ApiItemProxy::getBoolArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<bool> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_BOOL);
    result.reserve(response.bool_array().data_size());
    for (auto v : response.bool_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<int> ApiItemProxy::getIntArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<int> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_INT);
    result.reserve(response.int_array().data_size());
    for (auto v : response.int_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::int32_2> ApiItemProxy::getInt2ArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::int32_2> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_INT2);
    result.reserve(response.int2_array().data_size());
    for (const auto & e : response.int2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<OctaneVec::int32_3> ApiItemProxy::getInt3ArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::int32_3> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_INT3);
    result.reserve(response.int3_array().data_size());
    for (const auto & e : response.int3_array().data())
    {
        result.push_back({e.x(), e.y(), e.z()});
    }
    return result;

};


std::vector<OctaneVec::int32_4> ApiItemProxy::getInt4ArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::int32_4> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_INT4);
    result.reserve(response.int4_array().data_size());
    for (const auto & e : response.int4_array().data())
    {
        result.push_back({e.x(), e.y(), e.z(), e.w()});
    }
    return result;

};


std::vector<long> ApiItemProxy::getLongArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<long> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_LONG);
    result.reserve(response.long_array().data_size());
    for (auto v : response.long_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::int64_2> ApiItemProxy::getLong2ArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::int64_2> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_LONG2);
    result.reserve(response.long2_array().data_size());
    for (const auto & e : response.long2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<float> ApiItemProxy::getFloatArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<float> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_FLOAT);
    result.reserve(response.float_array().data_size());
    for (auto v : response.float_array().data())
    {
        result.push_back(v);
    }
    return result;

};


std::vector<OctaneVec::float_2> ApiItemProxy::getFloat2ArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::float_2> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_FLOAT2);
    result.reserve(response.float2_array().data_size());
    for (const auto & e : response.float2_array().data())
    {
        result.push_back({e.x(), e.y()});
    }
    return result;

};


std::vector<OctaneVec::float_3> ApiItemProxy::getFloat3ArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::float_3> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_FLOAT3);
    result.reserve(response.float3_array().data_size());
    for (const auto & e : response.float3_array().data())
    {
        result.push_back({e.x(), e.y(), e.z()});
    }
    return result;

};


std::vector<OctaneVec::float_4> ApiItemProxy::getFloat4ArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::float_4> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_FLOAT4);
    result.reserve(response.float4_array().data_size());
    for (const auto & e : response.float4_array().data())
    {
        result.push_back({e.x(), e.y(), e.z(), e.w()});
    }
    return result;

};


std::vector<Octane::MatrixF> ApiItemProxy::getMatrixArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<OctaneVec::MatrixF> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_MATRIX);
    result.reserve(response.matrix_array().data_size());
    for (const auto & e : response.matrix_array().data())
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(e, m);
        result.push_back(m);
    }
    return result;

};


std::vector<std::string> ApiItemProxy::getStringArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<std::string> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_STRING);
    result.reserve(response.string_array().data_size());
    for (auto & s : response.string_array().data())
    {
        result.push_back(s);
    }
    return result;

};


std::vector<uint8_t> ApiItemProxy::getByteArrayIx(
            const uint32_t                            index
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
std::vector<uint8_t> result;
    auto response = callGetArrayByIx(*this, index, octaneapi::ATTR_ID_BYTE);
    const std::string & bytes = response.byte_array().data();
    result.assign(bytes.begin(), bytes.end());
    return result;

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    request.set_bool_value(value);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    request.set_int_value(value);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    auto * v = request.mutable_int2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_3 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    auto * v = request.mutable_int3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_4 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    auto * v = request.mutable_int4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const int64_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    request.set_long_value(value);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::int64_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    auto * v = request.mutable_long2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    request.set_float_value(value);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    auto * v = request.mutable_float2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_3 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    auto * v = request.mutable_float3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_4 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    auto * v = request.mutable_float4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    MatrixConverter::convertMatrixToProto(value, *request.mutable_matrix_value());
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const char *                              value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIDRequest request;
    request.set_string_value(value);
    auto response = callSetByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const bool *                              arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const int32_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::int32_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const int64_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::int64_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const float *                             arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::float_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const OctaneVec::MatrixF *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(arr[i], *m);
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const char *const *                       arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i] ? arr[i] : "");
    }
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const Octane::AttributeId                 id,
            const uint8_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIDRequest request;
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(arr), size);
    auto response = callSetArrayByAttrID(*this, id, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    request.set_bool_value(value);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    request.set_int_value(value);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::int32_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    auto * v = request.mutable_int2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::int32_3 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    auto * v = request.mutable_int3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::int32_4 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    auto * v = request.mutable_int4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const int64_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    request.set_long_value(value);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::int64_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    auto * v = request.mutable_long2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    request.set_float_value(value);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::float_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    auto * v = request.mutable_float2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::float_3 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    auto * v = request.mutable_float3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::float_4 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    auto * v = request.mutable_float4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    MatrixConverter::convertMatrixToProto(value, *request.mutable_matrix_value());
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const char *                              value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setValueByNameRequest request;
    request.set_string_value(value);
    auto response = callSetByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const bool *                              arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const int32_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::int32_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::int32_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::int32_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const int64_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::int64_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const float *                             arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::float_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::float_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::float_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const OctaneVec::MatrixF *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(arr[i], *m);
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const char *const *                       arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i] ? arr[i] : "");
    }
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::set(
            const char *                              name,
            const uint8_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setArrayByNameRequest request;
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(arr), size);
    auto response = callSetArrayByName(*this, strName, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const bool                                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    request.set_bool_value(value);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const int32_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    request.set_int_value(value);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::int32_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    auto * v = request.mutable_int2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::int32_3 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    auto * v = request.mutable_int3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::int32_4 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    auto * v = request.mutable_int4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const int64_t                             value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    request.set_long_value(value);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::int64_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    auto * v = request.mutable_long2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const float                               value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    request.set_float_value(value);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::float_2 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    auto * v = request.mutable_float2_value();
    v->set_x(value.x);
    v->set_y(value.y);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::float_3 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    auto * v = request.mutable_float3_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::float_4 &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    auto * v = request.mutable_float4_value();
    v->set_x(value.x);
    v->set_y(value.y);
    v->set_z(value.z);
    v->set_w(value.w);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::MatrixF &                value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    MatrixConverter::convertMatrixToProto(value, *request.mutable_matrix_value());
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const char *                              value,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setValueByIxRequest request;
    request.set_string_value(value);
    auto response = callSetByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const bool *                              arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const int32_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::int32_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::int32_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::int32_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const int64_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::int64_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const float *                             arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::float_2 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::float_3 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::float_4 *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const OctaneVec::MatrixF *                arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < size; ++i)
    {
        auto * m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(arr[i], *m);
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const char *const *                       arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < size; ++i)
    {
        arrMsg->add_data(arr[i] ? arr[i] : "");
    }
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::setIx(
            const uint32_t                            index,
            const uint8_t *                           arr,
            const size_t                              size,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setArrayByIxRequest request;
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(arr), size);
    auto response = callSetArrayByIx(*this, index, request);

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<bool> &                       values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_BOOL , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.bool_array().data_size());
    for (int i = 0; i < response.bool_array().data_size(); ++i)
    {
        values.push_back(response.bool_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<int> &                        values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_INT , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int_array().data_size());
    for (int i = 0; i < response.int_array().data_size(); ++i)
    {
        values.push_back(response.int_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_INT2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int2_array().data_size());
    for (int i = 0; i < response.int2_array().data_size(); ++i)
    {
        values.push_back({response.int2_array().data(i).x(), response.int2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_3> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_INT3 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int3_array().data_size());
    for (int i = 0; i < response.int3_array().data_size(); ++i)
    {
        values.push_back({response.int3_array().data(i).x(), response.int3_array().data(i).y(), response.int3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_4> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_INT4 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int4_array().data_size());
    for (int i = 0; i < response.int4_array().data_size(); ++i)
    {
        values.push_back({response.int4_array().data(i).x(), response.int4_array().data(i).y(), response.int4_array().data(i).z(), response.int4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<long> &                       values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_LONG , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.long_array().data_size());
    for (int i = 0; i < response.long_array().data_size(); ++i)
    {
        values.push_back(response.long_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int64_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_LONG2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.long2_array().data_size());
    for (int i = 0; i < response.long2_array().data_size(); ++i)
    {
        values.push_back({response.long2_array().data(i).x(), response.long2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<float> &                      values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_FLOAT , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float_array().data_size());
    for (int i = 0; i < response.float_array().data_size(); ++i)
    {
        values.push_back(response.float_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_FLOAT2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float2_array().data_size());
    for (int i = 0; i < response.float2_array().data_size(); ++i)
    {
        values.push_back({response.float2_array().data(i).x(), response.float2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_3> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_FLOAT3 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float3_array().data_size());
    for (int i = 0; i < response.float3_array().data_size(); ++i)
    {
        values.push_back({response.float3_array().data(i).x(), response.float3_array().data(i).y(), response.float3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_4> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_FLOAT4 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float4_array().data_size());
    for (int i = 0; i < response.float4_array().data_size(); ++i)
    {
        values.push_back({response.float4_array().data(i).x(), response.float4_array().data(i).y(), response.float4_array().data(i).z(), response.float4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<Octane::MatrixF> &            values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_MATRIX , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.matrix_array().data_size());
    for (int i = 0; i < response.matrix_array().data_size(); ++i)
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(response.matrix_array().data(i), m);
        values.push_back(m);
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<std::string> &                values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_STRING , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.string_array().data_size());
    for (int i = 0; i < response.string_array().data_size(); ++i)
    {
        values.push_back(response.string_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            std::vector<uint8_t> &                    values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_BYTE , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    const std::string & data = response.byte_array().data();
    values.assign(data.begin(), data.end());

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<bool> &                       arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_BOOL, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.bool_array().data_size());
    for (int i = 0; i < response.bool_array().data_size(); ++i)
    {
        arr.push_back(response.bool_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<int> &                        arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_INT, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int_array().data_size());
    for (int i = 0; i < response.int_array().data_size(); ++i)
    {
        arr.push_back(response.int_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_INT2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int2_array().data_size());
    for (int i = 0; i < response.int2_array().data_size(); ++i)
    {
        arr.push_back({response.int2_array().data(i).x(), response.int2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_3> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_INT3, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int3_array().data_size());
    for (int i = 0; i < response.int3_array().data_size(); ++i)
    {
        arr.push_back({response.int3_array().data(i).x(), response.int3_array().data(i).y(), response.int3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_4> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_INT4, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int4_array().data_size());
    for (int i = 0; i < response.int4_array().data_size(); ++i)
    {
        arr.push_back({response.int4_array().data(i).x(), response.int4_array().data(i).y(), response.int4_array().data(i).z(), response.int4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<long> &                       arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_LONG, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.long_array().data_size());
    for (int i = 0; i < response.long_array().data_size(); ++i)
    {
        arr.push_back(response.long_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int64_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_LONG2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.long2_array().data_size());
    for (int i = 0; i < response.long2_array().data_size(); ++i)
    {
        arr.push_back({response.long2_array().data(i).x(), response.long2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<float> &                      arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_FLOAT, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float_array().data_size());
    for (int i = 0; i < response.float_array().data_size(); ++i)
    {
        arr.push_back(response.float_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_FLOAT2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float2_array().data_size());
    for (int i = 0; i < response.float2_array().data_size(); ++i)
    {
        arr.push_back({response.float2_array().data(i).x(), response.float2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_3> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_FLOAT3, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float3_array().data_size());
    for (int i = 0; i < response.float3_array().data_size(); ++i)
    {
        arr.push_back({response.float3_array().data(i).x(), response.float3_array().data(i).y(), response.float3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_4> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_FLOAT4, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float4_array().data_size());
    for (int i = 0; i < response.float4_array().data_size(); ++i)
    {
        arr.push_back({response.float4_array().data(i).x(), response.float4_array().data(i).y(), response.float4_array().data(i).z(), response.float4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<Octane::MatrixF> &            arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_MATRIX, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.matrix_array().data_size());
    for (int i = 0; i < response.matrix_array().data_size(); ++i)
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(response.matrix_array().data(i), m);
        arr.push_back(m);
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<std::string> &                arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_STRING, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.string_array().data_size());
    for (int i = 0; i < response.string_array().data_size(); ++i)
    {
        arr.push_back(response.string_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const Octane::AttributeId                 id,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<uint8_t> &                    arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByAttr(*this, id, octaneapi::ATTR_ID_BYTE, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    const std::string& data = response.byte_array().data();
    arr.assign(data.begin(), data.end());

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<bool> &                       values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_BOOL , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.bool_array().data_size());
    for (int i = 0; i < response.bool_array().data_size(); ++i)
    {
        values.push_back(response.bool_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<int> &                        values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_INT , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int_array().data_size());
    for (int i = 0; i < response.int_array().data_size(); ++i)
    {
        values.push_back(response.int_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_INT2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int2_array().data_size());
    for (int i = 0; i < response.int2_array().data_size(); ++i)
    {
        values.push_back({response.int2_array().data(i).x(), response.int2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_3> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_INT3 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int3_array().data_size());
    for (int i = 0; i < response.int3_array().data_size(); ++i)
    {
        values.push_back({response.int3_array().data(i).x(), response.int3_array().data(i).y(), response.int3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_4> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_INT4 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int4_array().data_size());
    for (int i = 0; i < response.int4_array().data_size(); ++i)
    {
        values.push_back({response.int4_array().data(i).x(), response.int4_array().data(i).y(), response.int4_array().data(i).z(), response.int4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<long> &                       values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_LONG , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.long_array().data_size());
    for (int i = 0; i < response.long_array().data_size(); ++i)
    {
        values.push_back(response.long_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int64_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_LONG2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.long2_array().data_size());
    for (int i = 0; i < response.long2_array().data_size(); ++i)
    {
        values.push_back({response.long2_array().data(i).x(), response.long2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<float> &                      values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_FLOAT , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float_array().data_size());
    for (int i = 0; i < response.float_array().data_size(); ++i)
    {
        values.push_back(response.float_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_FLOAT2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float2_array().data_size());
    for (int i = 0; i < response.float2_array().data_size(); ++i)
    {
        values.push_back({response.float2_array().data(i).x(), response.float2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_3> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_FLOAT3 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float3_array().data_size());
    for (int i = 0; i < response.float3_array().data_size(); ++i)
    {
        values.push_back({response.float3_array().data(i).x(), response.float3_array().data(i).y(), response.float3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_4> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_FLOAT4 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float4_array().data_size());
    for (int i = 0; i < response.float4_array().data_size(); ++i)
    {
        values.push_back({response.float4_array().data(i).x(), response.float4_array().data(i).y(), response.float4_array().data(i).z(), response.float4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<Octane::MatrixF> &            values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_MATRIX , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.matrix_array().data_size());
    for (int i = 0; i < response.matrix_array().data_size(); ++i)
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(response.matrix_array().data(i), m);
        values.push_back(m);
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<std::string> &                values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_STRING , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.string_array().data_size());
    for (int i = 0; i < response.string_array().data_size(); ++i)
    {
        values.push_back(response.string_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            std::vector<uint8_t> &                    values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_BYTE , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    const std::string & data = response.byte_array().data();
    values.assign(data.begin(), data.end());

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<bool> &                       arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_BOOL, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.bool_array().data_size());
    for (int i = 0; i < response.bool_array().data_size(); ++i)
    {
        arr.push_back(response.bool_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<int> &                        arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_INT, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int_array().data_size());
    for (int i = 0; i < response.int_array().data_size(); ++i)
    {
        arr.push_back(response.int_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_INT2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int2_array().data_size());
    for (int i = 0; i < response.int2_array().data_size(); ++i)
    {
        arr.push_back({response.int2_array().data(i).x(), response.int2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_3> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_INT3, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int3_array().data_size());
    for (int i = 0; i < response.int3_array().data_size(); ++i)
    {
        arr.push_back({response.int3_array().data(i).x(), response.int3_array().data(i).y(), response.int3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_4> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_INT4, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int4_array().data_size());
    for (int i = 0; i < response.int4_array().data_size(); ++i)
    {
        arr.push_back({response.int4_array().data(i).x(), response.int4_array().data(i).y(), response.int4_array().data(i).z(), response.int4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<long> &                       arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_LONG, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.long_array().data_size());
    for (int i = 0; i < response.long_array().data_size(); ++i)
    {
        arr.push_back(response.long_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int64_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_LONG2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.long2_array().data_size());
    for (int i = 0; i < response.long2_array().data_size(); ++i)
    {
        arr.push_back({response.long2_array().data(i).x(), response.long2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<float> &                      arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_FLOAT, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float_array().data_size());
    for (int i = 0; i < response.float_array().data_size(); ++i)
    {
        arr.push_back(response.float_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_FLOAT2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float2_array().data_size());
    for (int i = 0; i < response.float2_array().data_size(); ++i)
    {
        arr.push_back({response.float2_array().data(i).x(), response.float2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_3> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_FLOAT3, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float3_array().data_size());
    for (int i = 0; i < response.float3_array().data_size(); ++i)
    {
        arr.push_back({response.float3_array().data(i).x(), response.float3_array().data(i).y(), response.float3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_4> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_FLOAT4, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float4_array().data_size());
    for (int i = 0; i < response.float4_array().data_size(); ++i)
    {
        arr.push_back({response.float4_array().data(i).x(), response.float4_array().data(i).y(), response.float4_array().data(i).z(), response.float4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<Octane::MatrixF> &            arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_MATRIX, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.matrix_array().data_size());
    for (int i = 0; i < response.matrix_array().data_size(); ++i)
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(response.matrix_array().data(i), m);
        arr.push_back(m);
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<std::string> &                arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_STRING, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.string_array().data_size());
    for (int i = 0; i < response.string_array().data_size(); ++i)
    {
        arr.push_back(response.string_array().data(i));
    }

};


void ApiItemProxy::getAnim(
            const char *                              name,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<uint8_t> &                    arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByName(*this, strName, octaneapi::ATTR_ID_BYTE, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    const std::string& data = response.byte_array().data();
    arr.assign(data.begin(), data.end());

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<bool> &                       values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_BOOL , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.bool_array().data_size());
    for (int i = 0; i < response.bool_array().data_size(); ++i)
    {
        values.push_back(response.bool_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<int> &                        values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_INT , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int_array().data_size());
    for (int i = 0; i < response.int_array().data_size(); ++i)
    {
        values.push_back(response.int_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_INT2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int2_array().data_size());
    for (int i = 0; i < response.int2_array().data_size(); ++i)
    {
        values.push_back({response.int2_array().data(i).x(), response.int2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_3> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_INT3 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int3_array().data_size());
    for (int i = 0; i < response.int3_array().data_size(); ++i)
    {
        values.push_back({response.int3_array().data(i).x(), response.int3_array().data(i).y(), response.int3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int32_4> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_INT4 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.int4_array().data_size());
    for (int i = 0; i < response.int4_array().data_size(); ++i)
    {
        values.push_back({response.int4_array().data(i).x(), response.int4_array().data(i).y(), response.int4_array().data(i).z(), response.int4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<long> &                       values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_LONG , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.long_array().data_size());
    for (int i = 0; i < response.long_array().data_size(); ++i)
    {
        values.push_back(response.long_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::int64_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_LONG2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.long2_array().data_size());
    for (int i = 0; i < response.long2_array().data_size(); ++i)
    {
        values.push_back({response.long2_array().data(i).x(), response.long2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<float> &                      values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_FLOAT , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float_array().data_size());
    for (int i = 0; i < response.float_array().data_size(); ++i)
    {
        values.push_back(response.float_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_2> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_FLOAT2 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float2_array().data_size());
    for (int i = 0; i < response.float2_array().data_size(); ++i)
    {
        values.push_back({response.float2_array().data(i).x(), response.float2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_3> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_FLOAT3 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float3_array().data_size());
    for (int i = 0; i < response.float3_array().data_size(); ++i)
    {
        values.push_back({response.float3_array().data(i).x(), response.float3_array().data(i).y(), response.float3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<OctaneVec::float_4> &         values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_FLOAT4 , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.float4_array().data_size());
    for (int i = 0; i < response.float4_array().data_size(); ++i)
    {
        values.push_back({response.float4_array().data(i).x(), response.float4_array().data(i).y(), response.float4_array().data(i).z(), response.float4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<Octane::MatrixF> &            values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_MATRIX , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.matrix_array().data_size());
    for (int i = 0; i < response.matrix_array().data_size(); ++i)
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(response.matrix_array().data(i), m);
        values.push_back(m);
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<std::string> &                values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_STRING , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    values.reserve(response.string_array().data_size());
    for (int i = 0; i < response.string_array().data_size(); ++i)
    {
        values.push_back(response.string_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            std::vector<uint8_t> &                    values
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_BYTE , false);
    ApiTimeSamplingConverter::convert(response.times(), times);
    values.clear();
    const std::string & data = response.byte_array().data();
    values.assign(data.begin(), data.end());

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<bool> &                       arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_BOOL, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.bool_array().data_size());
    for (int i = 0; i < response.bool_array().data_size(); ++i)
    {
        arr.push_back(response.bool_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<int> &                        arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_INT, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int_array().data_size());
    for (int i = 0; i < response.int_array().data_size(); ++i)
    {
        arr.push_back(response.int_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_INT2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int2_array().data_size());
    for (int i = 0; i < response.int2_array().data_size(); ++i)
    {
        arr.push_back({response.int2_array().data(i).x(), response.int2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_3> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_INT3, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int3_array().data_size());
    for (int i = 0; i < response.int3_array().data_size(); ++i)
    {
        arr.push_back({response.int3_array().data(i).x(), response.int3_array().data(i).y(), response.int3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int32_4> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_INT4, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.int4_array().data_size());
    for (int i = 0; i < response.int4_array().data_size(); ++i)
    {
        arr.push_back({response.int4_array().data(i).x(), response.int4_array().data(i).y(), response.int4_array().data(i).z(), response.int4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<long> &                       arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_LONG, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.long_array().data_size());
    for (int i = 0; i < response.long_array().data_size(); ++i)
    {
        arr.push_back(response.long_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::int64_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_LONG2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.long2_array().data_size());
    for (int i = 0; i < response.long2_array().data_size(); ++i)
    {
        arr.push_back({response.long2_array().data(i).x(), response.long2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<float> &                      arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_FLOAT, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float_array().data_size());
    for (int i = 0; i < response.float_array().data_size(); ++i)
    {
        arr.push_back(response.float_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_2> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_FLOAT2, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float2_array().data_size());
    for (int i = 0; i < response.float2_array().data_size(); ++i)
    {
        arr.push_back({response.float2_array().data(i).x(), response.float2_array().data(i).y()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_3> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_FLOAT3, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float3_array().data_size());
    for (int i = 0; i < response.float3_array().data_size(); ++i)
    {
        arr.push_back({response.float3_array().data(i).x(), response.float3_array().data(i).y(), response.float3_array().data(i).z()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<OctaneVec::float_4> &         arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_FLOAT4, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.float4_array().data_size());
    for (int i = 0; i < response.float4_array().data_size(); ++i)
    {
        arr.push_back({response.float4_array().data(i).x(), response.float4_array().data(i).y(), response.float4_array().data(i).z(), response.float4_array().data(i).w()});
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<Octane::MatrixF> &            arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_MATRIX, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.matrix_array().data_size());
    for (int i = 0; i < response.matrix_array().data_size(); ++i)
    {
        OctaneVec::MatrixF m;
        MatrixConverter::convertMatrixToOctane(response.matrix_array().data(i), m);
        arr.push_back(m);
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<std::string> &                arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_STRING, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    arr.reserve(response.string_array().data_size());
    for (int i = 0; i < response.string_array().data_size(); ++i)
    {
        arr.push_back(response.string_array().data(i));
    }

};


void ApiItemProxy::getAnimIx(
            const uint32_t                            index,
            Octane::ApiTimeSampling &                 times,
            size_t &                                  numTimes,
            std::vector<uint8_t> &                    arr
            ) const
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic helper that wraps gRPC
    octaneapi::ApiItem::getAnimArrayResponse response;
    response = callGetAnimByIx(*this, index, octaneapi::ATTR_ID_BYTE, true);
    ApiTimeSamplingConverter::convert(response.times(), times);
    numTimes = response.has_num_time_samples() ? static_cast<size_t>(response.num_time_samples()) : 0;
    arr.clear();
    const std::string& data = response.byte_array().data();
    arr.assign(data.begin(), data.end());

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const bool *                              values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const int32_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
        e->set_w(values[i].w);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const int64_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int64_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const float *                             values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
        e->set_w(values[i].w);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::MatrixF *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(values[i], *m);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const char *const *                       values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i] ? values[i] : "");
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const uint8_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(values), numValues);
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const bool *                              arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int32_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int64_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int64_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const float *                             arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::MatrixF *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(arr[i], *m);
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const char *const *                       arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i] ? arr[i] : "");
    }
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const Octane::AttributeId                 id,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const uint8_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIDRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(arr), arrSize);
    auto response = callSetAnimByAttr(*this, id, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const bool *                              values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const int32_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
        e->set_w(values[i].w);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const int64_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int64_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const float *                             values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
        e->set_w(values[i].w);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::MatrixF *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(values[i], *m);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const char *const *                       values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i] ? values[i] : "");
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const uint8_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(values), numValues);
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const bool *                              arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int32_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int64_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int64_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const float *                             arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::MatrixF *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(arr[i], *m);
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const char *const *                       arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i] ? arr[i] : "");
    }
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnim(
            const char *                              name,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const uint8_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    std::string strName = (name == nullptr ? "" : name);
    octaneapi::ApiItem::setAnimByNameRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(arr), arrSize);
    auto response = callSetAnimByName(*this, strName, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const bool *                              values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const int32_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int32_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
        e->set_w(values[i].w);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const int64_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::int64_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const float *                             values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i]);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_2 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_3 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::float_4 *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(values[i].x);
        e->set_y(values[i].y);
        e->set_z(values[i].z);
        e->set_w(values[i].w);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const OctaneVec::MatrixF *                values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        auto* m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(values[i], *m);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const char *const *                       values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < numValues; ++i)
    {
        arrMsg->add_data(values[i] ? values[i] : "");
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const uint8_t *                           values,
            const size_t                              numValues,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_evaluate(evaluate);
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(values), numValues);
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const bool *                              arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_bool_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int32_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int3_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int32_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_int4_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const int64_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::int64_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_long2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const float *                             arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i]);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_2 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float2_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_3 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float3_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::float_4 *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_float4_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* e = arrMsg->add_data();
        e->set_x(arr[i].x);
        e->set_y(arr[i].y);
        e->set_z(arr[i].z);
        e->set_w(arr[i].w);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const OctaneVec::MatrixF *                arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_matrix_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        auto* m = arrMsg->add_data();
        MatrixConverter::convertMatrixToProto(arr[i], *m);
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const char *const *                       arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    auto * arrMsg = request.mutable_string_array();
    for (size_t i = 0; i < arrSize; ++i)
    {
        arrMsg->add_data(arr[i] ? arr[i] : "");
    }
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::setAnimIx(
            const uint32_t                            index,
            const Octane::ApiTimeSampling &           times,
            const size_t                              numTimes,
            const uint8_t *                           arr,
            const size_t                              arrSize,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    // Call the generic set() helper that wraps gRPC
    octaneapi::ApiItem::setAnimByIxRequest request;
    ApiTimeSamplingConverter::convert(times, *request.mutable_times());
    request.set_num_time_samples(static_cast<uint32_t>(numTimes));
    request.set_evaluate(evaluate);
    request.mutable_byte_array()->set_data(reinterpret_cast<const char*>(arr), arrSize);
    auto response = callSetAnimByIx(*this, index, request);

};


void ApiItemProxy::clearAnim(
            const Octane::AttributeId                 id
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::clearAnimRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearAnim(context.get(), request, &response);

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


void ApiItemProxy::clearAnim(
            const char *                              name
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::clearAnim1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearAnim1(context.get(), request, &response);

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


void ApiItemProxy::clearAnimIx(
            const uint32_t                            index
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::clearAnimIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearAnimIx(context.get(), request, &response);

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


bool ApiItemProxy::isAnimated(
            const Octane::AttributeId                 id
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isAnimatedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
        idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isAnimatedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isAnimated(context.get(), request, &response);

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


bool ApiItemProxy::isAnimated(
            const char *                              name
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isAnimated1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isAnimated1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isAnimated1(context.get(), request, &response);

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


bool ApiItemProxy::isAnimatedIx(
            const uint32_t                            index
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::isAnimatedIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::isAnimatedIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->isAnimatedIx(context.get(), request, &response);

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


void ApiItemProxy::evaluate()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::evaluateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->evaluate(context.get(), request, &response);

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


void ApiItemProxy::expand()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::expandRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->expand(context.get(), request, &response);

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


ApiItemProxy ApiItemProxy::expandOutOfPin()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::expandOutOfPinRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::expandOutOfPinResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->expandOutOfPin(context.get(), request, &response);

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


bool ApiItemProxy::collapse()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::collapseRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiItem::collapseResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->collapse(context.get(), request, &response);

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


void ApiItemProxy::dumpAttributes(
            const char *                              directory
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiItem::dumpAttributesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'directory' [in] parameter to the request packet.
    std::string * directoryIn = new std::string();
    *directoryIn = checkString(directory);
    request.set_allocated_directory(directoryIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiItemService::Stub> stub =
        octaneapi::ApiItemService::NewStub(getGRPCSettings().getChannel());
    status = stub->dumpAttributes(context.get(), request, &response);

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




void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            bool &                                    value
            ) const
{
    value = getBool(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            int32_t &                                 value
            ) const
{
    value = getInt(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            OctaneVec::int32_2 &                      value
            ) const
{
    value = getInt2(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            OctaneVec::int32_3 &                      value
            ) const
{
    value = getInt3(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            OctaneVec::int32_4 &                      value
            ) const
{
    value = getInt4(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            int64_t &                                 value
            ) const
{
    value = getLong(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            OctaneVec::int64_2 &                      value
            ) const
{
     value = getLong2(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            float &                                   value
            ) const
{
     value = getFloat(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            OctaneVec::float_2 &                      value
            ) const
{
     value = getFloat2(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            OctaneVec::float_3 &                      value
            ) const
{
    value = getFloat3(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            OctaneVec::float_4 &                      value
            ) const
{
    value = getFloat4(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            OctaneVec::MatrixF &                      value
            ) const
{
    value = getMatrix(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::string &                             value
            ) const
{
    value = getString(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<bool> &                       arr
            ) const
{
    arr = getBoolArray(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<int> &                        arr
            ) const
{
    arr = getIntArray(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::int32_2> &         arr
            ) const
{
    arr = getInt2Array(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::int32_3> &         arr
            ) const
{
    arr = getInt3Array(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::int32_4> &         arr
            ) const
{
    arr = getInt4Array(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<long> &                       arr
            ) const
{
    arr = getLongArray(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::int64_2> &         arr
            ) const
{
    arr = getLong2Array(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<float> &                      arr
            ) const
{
    arr = getFloatArray(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::float_2> &         arr
            ) const
{
    arr = getFloat2Array(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::float_3> &         arr
            ) const
{
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<OctaneVec::float_4> &         arr
            ) const
{
    arr = getFloat4Array(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<Octane::MatrixF> &            arr
            ) const
{
    arr = getMatrixArray(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<std::string> &                arr
            ) const
{
    arr = getStringArray(id);
}


void ApiItemProxy::get(
            const Octane::AttributeId                 id,
            std::vector<uint8_t> &                    arr
            ) const
{
    arr = getByteArray(id);
}


void ApiItemProxy::get(
            const char *                              name,
            bool &                                    value
            ) const
{
    value = getBool(name);
}


void ApiItemProxy::get(
            const char *                              name,
            int32_t &                                 value
            ) const
{
    value = getInt(name);
}


void ApiItemProxy::get(
            const char *                              name,
            OctaneVec::int32_2 &                      value
            ) const
{
    value = getInt2(name);
}


void ApiItemProxy::get(
            const char *                              name,
            OctaneVec::int32_3 &                      value
            ) const
{
    value = getInt3(name);
}


void ApiItemProxy::get(
            const char *                              name,
            OctaneVec::int32_4 &                      value
            ) const
{
    value = getInt4(name);
}


void ApiItemProxy::get(
            const char *                              name,
            int64_t &                                 value
            ) const
{
    value = getLong(name);
}


void ApiItemProxy::get(
            const char *                              name,
            OctaneVec::int64_2 &                      value
            ) const
{
    value = getLong2(name);
}


void ApiItemProxy::get(
            const char *                              name,
            float &                                   value
            ) const
{
    value = getFloat(name);
}


void ApiItemProxy::get(
            const char *                              name,
            OctaneVec::float_2 &                      value
            ) const
{
    value = getFloat2(name);
}


void ApiItemProxy::get(
            const char *                              name,
            OctaneVec::float_3 &                      value
            ) const
{
    value = getFloat3(name);
}


void ApiItemProxy::get(
            const char *                              name,
            OctaneVec::float_4 &                      value
            ) const
{
    value = getFloat4(name);
}


void ApiItemProxy::get(
            const char *                              name,
            OctaneVec::MatrixF &                      value
            ) const
{
    value = getMatrix(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::string &                             value
            ) const
{
    value = getString(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<bool> &                       arr
            ) const
{
    arr = getBoolArray(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<int> &                        arr
            ) const
{
    arr = getIntArray(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<OctaneVec::int32_2> &         arr
            ) const
{
    arr = getInt2Array(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<OctaneVec::int32_3> &         arr
            ) const
{
    arr = getInt3Array(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<OctaneVec::int32_4> &         arr
            ) const
{
    arr = getInt4Array(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<long> &                       arr
            ) const
{
    arr = getLongArray(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<OctaneVec::int64_2> &         arr
            ) const
{
    arr = getLong2Array(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<float> &                      arr
            ) const
{
    arr = getFloatArray(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<OctaneVec::float_2> &         arr
            ) const
{
    arr = getFloat2Array(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<OctaneVec::float_3> &         arr
            ) const
{
    arr = getFloat3Array(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<OctaneVec::float_4> &         arr
            ) const
{
    arr = getFloat4Array(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<Octane::MatrixF> &            arr
            ) const
{
    arr = getMatrixArray(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<std::string> &                arr
            ) const
{
    arr = getStringArray(name);
}


void ApiItemProxy::get(
            const char *                              name,
            std::vector<uint8_t> &                    arr
            ) const
{
    arr = getByteArray(name);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            bool &                                    value
            ) const
{
    value = getBoolIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            int32_t &                                 value
            ) const
{
    value = getBoolIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            OctaneVec::int32_2 &                      value
            ) const
{
    value = getInt2Ix(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            OctaneVec::int32_3 &                      value
            ) const
{
    value = getInt3Ix(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            OctaneVec::int32_4 &                      value
            ) const
{
    value = getInt4Ix(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            int64_t &                                 value
            ) const
{
    value = getLongIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            OctaneVec::int64_2 &                      value
            ) const
{
    value = getLong2Ix(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            float &                                   value
            ) const
{
    value = getFloatIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            OctaneVec::float_2 &                      value
            ) const
{
    value = getFloat2Ix(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            OctaneVec::float_3 &                      value
            ) const
{
    value = getFloat3Ix(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            OctaneVec::float_4 &                      value
            ) const
{
    value = getFloat4Ix(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            OctaneVec::MatrixF &                      value
            ) const
{
    value = getMatrixIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::string &                             value
            ) const
{
    value = getStringIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<bool> &                       arr
            ) const
{
    arr = getBoolArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<int> &                        arr
            ) const
{
    arr = getIntArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::int32_2> &         arr
            ) const
{
    arr = getInt2ArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::int32_3> &         arr
            ) const
{
    arr = getInt3ArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::int32_4> &         arr
            ) const
{
    arr = getInt4ArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<long> &                       arr
            ) const
{
    arr = getLongArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::int64_2> &         arr
            ) const
{
    arr = getLong2ArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<float> &                      arr
            ) const
{
    arr = getFloatArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::float_2> &         arr
            ) const
{
    arr = getFloat2ArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::float_3> &         arr
            ) const
{
    arr = getFloat3ArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<OctaneVec::float_4> &         arr
            ) const
{
    arr = getFloat4ArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<Octane::MatrixF> &            arr
            ) const
{
    arr = getMatrixArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<std::string> &                arr
            ) const
{
    arr = getStringArrayIx(index);
}


void ApiItemProxy::getIx(
            const uint32_t                            index,
            std::vector<uint8_t> &                    arr
            ) const
{
    arr = getByteArrayIx(index);
}


} //end of namespace
