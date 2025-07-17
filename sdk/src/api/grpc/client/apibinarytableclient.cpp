// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apibinarytableclient.h"
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
#include "apibinarygroupclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiBinaryTableProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiBinaryTableProxy ApiBinaryTableProxy::create()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->create1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiBinaryTableProxy retVal;
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
        ApiBinaryTableProxy retVal;
        return retVal;
    }
};


void ApiBinaryTableProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->destroy1(context.get(), request, &response);

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


bool ApiBinaryTableProxy::isEmpty() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::isEmptyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::isEmptyResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->isEmpty1(context.get(), request, &response);

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


size_t ApiBinaryTableProxy::size() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::sizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::sizeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->size1(context.get(), request, &response);

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


void ApiBinaryTableProxy::erase(
            const int32_t                             id
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::eraseRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->erase(context.get(), request, &response);

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


bool ApiBinaryTableProxy::has(
            const int32_t                             id
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::hasRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::hasResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->has(context.get(), request, &response);

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


bool ApiBinaryTableProxy::equals(
            const ApiBinaryTableProxy &               other
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::equalsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'other' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * otherIn = new octaneapi::ObjectRef();
    otherIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    otherIn->set_handle(other.getObjectHandle());
    request.set_allocated_other(otherIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::equalsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->equals1(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            bool &                                    value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::getRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::getResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            int8_t &                                  value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int8_2 &                          value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int8_3 &                          value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get3Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int8_4 &                          value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get4Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            uint8_t &                                 value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get5Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get51(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint8_2 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get6Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get61(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint8_3 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get7Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get71(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint8_4 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get8Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get81(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            int16_t &                                 value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get9Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get91(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int16_2 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get10Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get101(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int16_3 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get11Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get111(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int16_4 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get12Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get12Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get121(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            uint16_t &                                value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get13Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get13Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get131(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint16_2 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get14Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get14Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get141(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint16_3 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get15Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get15Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get151(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint16_4 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get16Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get16Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get161(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            int32_t &                                 value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get17Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get17Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get171(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int32_2 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get18Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get18Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get181(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int32_3 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get19Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get19Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get191(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int32_4 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get20Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get20Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get201(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            uint32_t &                                value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get21Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get21Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get211(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint32_2 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get22Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get22Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get221(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint32_3 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get23Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get23Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get231(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint32_4 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get24Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get24Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get241(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            int64_t &                                 value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get25Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get25Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get251(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int64_2 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get26Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get26Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get261(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int64_3 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get27Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get27Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get271(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::int64_4 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get28Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get28Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get281(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            uint64_t &                                value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get29Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get29Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get291(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint64_2 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get30Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get30Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get301(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint64_3 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get31Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get31Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get311(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::uint64_4 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get32Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get32Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get321(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            float &                                   value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get33Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get33Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get331(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::float_2 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get34Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get34Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get341(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::float_3 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get35Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get35Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get351(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::float_4 &                         value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get36Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get36Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get361(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            double &                                  value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get37Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get37Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get371(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::double_2 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get38Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get38Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get381(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::double_3 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get39Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get39Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get391(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            Octane::double_4 &                        value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get40Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get40Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get401(context.get(), request, &response);

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


bool ApiBinaryTableProxy::get(
            const int32_t                             id,
            std::string &                             value
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::get41Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::get41Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->get411(context.get(), request, &response);

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


bool ApiBinaryTableProxy::getGroup(
            const int32_t                             id,
            ApiBinaryGroupProxy *&                    group
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::getGroupRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::getGroupResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGroup1(context.get(), request, &response);

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


bool ApiBinaryTableProxy::getTable(
            const int32_t                             id,
            ApiBinaryTableProxy *&                    table
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::getTableRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int32_t idIn;
    idIn = id;
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::getTableResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->getTable1(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const bool                                value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::setRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const int8_t                              value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set1(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int8_2                      value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set2(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int8_3                      value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set3(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int8_4                      value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set4(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const uint8_t                             value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set5(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint8_2                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set6(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint8_3                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set7(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint8_4                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set8(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const int16_t                             value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set9(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int16_2                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set10(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int16_3                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set11(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int16_4                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set12Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set12(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const uint16_t                            value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set13Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set13(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint16_2                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set14Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set14(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint16_3                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set15Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set15(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint16_4                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set16Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set16(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const int32_t                             value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set17Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set17(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int32_2                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set18Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set18(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int32_3                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set19Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set19(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int32_4                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set20Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set20(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const uint32_t                            value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set21Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set21(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint32_2                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set22Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set22(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint32_3                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set23Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set23(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint32_4                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set24Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set24(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const int64_t                             value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set25Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set25(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int64_2                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set26Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set26(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int64_3                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set27Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set27(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::int64_4                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set28Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set28(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const uint64_t                            value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set29Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set29(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint64_2                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set30Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set30(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint64_3                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set31Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set31(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::uint64_4                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set32Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set32(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const float                               value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set33Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set33(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::float_2                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set34Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set34(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::float_3                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set35Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set35(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::float_4                     value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set36Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set36(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const double                              value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set37Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set37(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::double_2                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set38Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set38(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::double_3                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set39Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set39(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const Octane::double_4                    value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set40Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set40(context.get(), request, &response);

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


void ApiBinaryTableProxy::set(
            const int32_t                             id,
            const char *                              value
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::set41Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->set41(context.get(), request, &response);

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


void ApiBinaryTableProxy::setGroup(
            const int32_t                             id,
            const ApiBinaryGroupProxy &               group
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::setGroupRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->setGroup(context.get(), request, &response);

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


void ApiBinaryTableProxy::setTable(
            const int32_t                             id,
            const ApiBinaryTableProxy &               table
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::setTableRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->setTable(context.get(), request, &response);

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


bool ApiBinaryTableProxy::write(
            const char *                              path
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::writeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    std::string * pathIn = new std::string();
    *pathIn = checkString(path);
    request.set_allocated_path(pathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::writeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->write(context.get(), request, &response);

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


ApiBinaryTableProxy ApiBinaryTableProxy::read(
            const char *                              path,
            uint32_t &                                octaneVersion
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::readRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    std::string * pathIn = new std::string();
    *pathIn = checkString(path);
    request.set_allocated_path(pathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBinaryTable::readResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->read(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiBinaryTableProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());

        /////////////////////////////////////////////////////////////////////
        // Process 'octaneVersion' [out] parameter from the gRPC response packet
        uint32_t octaneVersionOut = response.octaneversion();
        octaneVersion = octaneVersionOut;
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
        ApiBinaryTableProxy retVal;
        return retVal;
    }
};


void ApiBinaryTableProxy::dump(
            const uint32_t                            indent
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBinaryTable::dumpRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
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
    std::unique_ptr<octaneapi::ApiBinaryTableService::Stub> stub =
        octaneapi::ApiBinaryTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->dump1(context.get(), request, &response);

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


