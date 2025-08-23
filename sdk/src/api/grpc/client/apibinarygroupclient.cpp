// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apibinarygroupclient.h"
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
#include "apibinaryfile.grpc.pb.h"
#include "apibinarytableclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiBinaryGroupProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiBinaryGroupProxy ApiBinaryGroupProxy::create()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiBinaryGroupProxy retVal;
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
        ApiBinaryGroupProxy retVal;
        return retVal;
    }
};


void ApiBinaryGroupProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
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


bool ApiBinaryGroupProxy::isEmpty() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::isEmptyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::isEmptyResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->isEmpty(context.get(), request, &response);

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


size_t ApiBinaryGroupProxy::size() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::sizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::sizeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->size(context.get(), request, &response);

    size_t retVal = 0;
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


void ApiBinaryGroupProxy::popFront()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::popFrontRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->popFront(context.get(), request, &response);

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


void ApiBinaryGroupProxy::popBack()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::popBackRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->popBack(context.get(), request, &response);

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


int32_t ApiBinaryGroupProxy::getId(
            const size_t                              ix
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::getIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::getIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->getId(context.get(), request, &response);

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


bool ApiBinaryGroupProxy::equals(
            const ApiBinaryGroupProxy &               other
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::equalsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'other' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * otherIn = new octaneapi::ObjectRef();
    otherIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    otherIn->set_handle(other.getObjectHandle());
    request.set_allocated_other(otherIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::equalsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->equals(context.get(), request, &response);

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


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            bool &                                    value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::getRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::getResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            int8_t &                                  value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int8_2 &                          value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get2(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int8_2 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int8_3 &                          value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get3Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get3(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int8_3 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int8_4 &                          value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get4Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get4(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int8_4 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            uint8_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get5Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get5(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        uint32_t valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint8_2 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get6Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get6(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint8_2 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint8_3 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get7Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get7(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint8_3 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint8_4 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get8Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get8(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint8_4 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            int16_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get9Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get9(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int16_2 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get10Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get10(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int16_2 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int16_3 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get11Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get11(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int16_3 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int16_4 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get12Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get12Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get12(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int16_4 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            uint16_t &                                value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get13Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get13Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get13(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        uint32_t valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint16_2 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get14Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get14Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get14(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint16_2 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint16_3 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get15Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get15Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get15(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint16_3 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint16_4 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get16Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get16Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get16(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint16_4 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            int32_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get17Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get17Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get17(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int32_2 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get18Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get18Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get18(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int32_3 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get19Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get19Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get19(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int32_4 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get20Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get20Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get20(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            uint32_t &                                value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get21Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get21Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get21(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        uint32_t valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint32_2 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get22Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get22Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get22(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint32_2 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint32_3 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get23Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get23Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get23(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint32_3 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint32_4 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get24Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get24Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get24(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint32_4 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            int64_t &                                 value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get25Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get25Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get25(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        int64_t valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int64_2 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get26Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get26Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get26(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int64_2 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int64_3 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get27Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get27Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get27(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int64_3 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::int64_4 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get28Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get28Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get28(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int64_4 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            uint64_t &                                value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get29Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get29Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get29(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        uint64_t valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint64_2 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get30Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get30Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get30(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint64_2 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint64_3 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get31Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get31Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get31(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint64_3 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::uint64_4 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get32Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get32Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get32(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::uint64_4 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            float &                                   value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get33Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get33Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get33(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::float_2 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get34Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get34Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get34(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::float_3 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get35Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get35Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get35(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::float_4 &                         value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get36Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get36Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get36(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            double &                                  value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get37Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get37Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get37(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        double valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::double_2 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get38Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get38Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get38(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::double_2 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::double_3 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get39Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get39Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get39(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::double_3 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            Octane::double_4 &                        value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get40Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get40Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get40(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::double_4 valueOut = response.value();
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
    return retVal;
};


bool ApiBinaryGroupProxy::get(
            const size_t                              ix,
            std::string &                             value
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::get41Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::get41Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->get41(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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
    return retVal;
};


bool ApiBinaryGroupProxy::getGroup(
            const size_t                              ix,
            ApiBinaryGroupProxy *&                    group
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::getGroupRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::getGroupResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGroup(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'group' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef groupOut = response.group();
        group->attachObjectHandle(groupOut.handle());
    }
    else
    {
        if (!status.ok())
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


bool ApiBinaryGroupProxy::getTable(
            const size_t                              ix,
            ApiBinaryTableProxy *&                    table
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::getTableRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = static_cast<uint32_t>(ix);
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryGroup::getTableResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->getTable(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'table' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef tableOut = response.table();
        table->attachObjectHandle(tableOut.handle());
    }
    else
    {
        if (!status.ok())
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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const bool                                value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::addRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    bool valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const int8_t                              value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add1(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int8_2                      value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int8_2 * valueIn = new octaneapi::int8_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add2(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int8_3                      value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int8_3 * valueIn = new octaneapi::int8_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add3(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int8_4                      value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int8_4 * valueIn = new octaneapi::int8_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add4(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const uint8_t                             value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    uint32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add5(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint8_2                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint8_2 * valueIn = new octaneapi::uint8_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add6(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint8_3                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint8_3 * valueIn = new octaneapi::uint8_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add7(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint8_4                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint8_4 * valueIn = new octaneapi::uint8_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add8(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const int16_t                             value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add9(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int16_2                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int16_2 * valueIn = new octaneapi::int16_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add10(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int16_3                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int16_3 * valueIn = new octaneapi::int16_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add11(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int16_4                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add12Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int16_4 * valueIn = new octaneapi::int16_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add12(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const uint16_t                            value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add13Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    uint32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add13(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint16_2                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add14Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint16_2 * valueIn = new octaneapi::uint16_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add14(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint16_3                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add15Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint16_3 * valueIn = new octaneapi::uint16_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add15(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint16_4                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add16Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint16_4 * valueIn = new octaneapi::uint16_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add16(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const int32_t                             value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add17Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add17(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int32_2                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add18Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_2 * valueIn = new octaneapi::int32_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add18(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int32_3                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add19Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_3 * valueIn = new octaneapi::int32_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add19(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int32_4                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add20Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
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
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add20(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const uint32_t                            value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add21Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    uint32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add21(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint32_2                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add22Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint32_2 * valueIn = new octaneapi::uint32_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add22(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint32_3                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add23Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint32_3 * valueIn = new octaneapi::uint32_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add23(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint32_4                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add24Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint32_4 * valueIn = new octaneapi::uint32_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add24(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const int64_t                             value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add25Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int64_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add25(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int64_2                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add26Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int64_2 * valueIn = new octaneapi::int64_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add26(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int64_3                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add27Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int64_3 * valueIn = new octaneapi::int64_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add27(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::int64_4                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add28Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int64_4 * valueIn = new octaneapi::int64_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add28(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const uint64_t                            value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add29Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    uint64_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add29(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint64_2                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add30Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint64_2 * valueIn = new octaneapi::uint64_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add30(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint64_3                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add31Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint64_3 * valueIn = new octaneapi::uint64_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add31(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::uint64_4                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add32Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::uint64_4 * valueIn = new octaneapi::uint64_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add32(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const float                               value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add33Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    float valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add33(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::float_2                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add34Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_2 * valueIn = new octaneapi::float_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add34(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::float_3                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add35Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_3 * valueIn = new octaneapi::float_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add35(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::float_4                     value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add36Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
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
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add36(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const double                              value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add37Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    double valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add37(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::double_2                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add38Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::double_2 * valueIn = new octaneapi::double_2();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add38(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::double_3                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add39Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::double_3 * valueIn = new octaneapi::double_3();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add39(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const Octane::double_4                    value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add40Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::double_4 * valueIn = new octaneapi::double_4();
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add40(context.get(), request, &response);

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


void ApiBinaryGroupProxy::add(
            const int32_t                             id,
            const char *                              value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::add41Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    std::string * valueIn = new std::string();
    *valueIn = checkString(value);
    request.set_allocated_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->add41(context.get(), request, &response);

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


void ApiBinaryGroupProxy::addGroup(
            const int32_t                             id,
            const ApiBinaryGroupProxy &               group
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::addGroupRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'group' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * groupIn = new octaneapi::ObjectRef();
    groupIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    groupIn->set_handle(group.getObjectHandle());
    request.set_allocated_group(groupIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->addGroup(context.get(), request, &response);

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


void ApiBinaryGroupProxy::addTable(
            const int32_t                             id,
            const ApiBinaryTableProxy &               table
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::addTableRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'table' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * tableIn = new octaneapi::ObjectRef();
    tableIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    tableIn->set_handle(table.getObjectHandle());
    request.set_allocated_table(tableIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->addTable(context.get(), request, &response);

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


void ApiBinaryGroupProxy::dump(
            const uint32_t                            indent
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryGroup::dumpRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryGroup);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'indent' [in] parameter to the request packet.
    uint32_t indentIn;
    indentIn = indent;
    request.set_indent(indentIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryGroupService::Stub> stub =
        octaneapi::ApiBinaryGroupService::NewStub(getGRPCSettings().getChannel());
    status = stub->dump(context.get(), request, &response);

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


} //end of namespace
