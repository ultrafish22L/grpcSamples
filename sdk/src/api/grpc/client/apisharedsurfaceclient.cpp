// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apisharedsurfaceclient.h"
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
#include "apisharedsurface.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiSharedSurfaceProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiSharedSurfaceProxy ApiSharedSurfaceProxy::createD3D11(
            uint64_t                                  adapterLuid,
            void *                                    handle
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSharedSurface::createD3D11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'adapterLuid' [in] parameter to the request packet.
    uint64_t adapterluidIn;
    adapterluidIn = adapterLuid;
    request.set_adapterluid(adapterluidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'handle' [in] parameter to the request packet.
    uint64_t handleIn;
    handleIn = reinterpret_cast<uint64_t>(handle);
    request.set_handle(handleIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSharedSurface::createD3D11Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSharedSurfaceService::Stub> stub =
        octaneapi::ApiSharedSurfaceService::NewStub(getGRPCSettings().getChannel());
    status = stub->createD3D11(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiSharedSurfaceProxy retVal;
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
        ApiSharedSurfaceProxy retVal;
        return retVal;
    }
};


bool ApiSharedSurfaceProxy::equals(
            const ApiSharedSurfaceProxy *             a,
            const ApiSharedSurfaceProxy *             b
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSharedSurface::equalsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'a' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * aIn = new octaneapi::ObjectRef();
    aIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    aIn->set_handle(a->getObjectHandle());
    request.set_allocated_a(aIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'b' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * bIn = new octaneapi::ObjectRef();
    bIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    bIn->set_handle(b->getObjectHandle());
    request.set_allocated_b(bIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSharedSurface::equalsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSharedSurfaceService::Stub> stub =
        octaneapi::ApiSharedSurfaceService::NewStub(getGRPCSettings().getChannel());
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


bool ApiSharedSurfaceProxy::isLessThan(
            const ApiSharedSurfaceProxy *             a,
            const ApiSharedSurfaceProxy *             b
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSharedSurface::isLessThanRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'a' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * aIn = new octaneapi::ObjectRef();
    aIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    aIn->set_handle(a->getObjectHandle());
    request.set_allocated_a(aIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'b' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * bIn = new octaneapi::ObjectRef();
    bIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    bIn->set_handle(b->getObjectHandle());
    request.set_allocated_b(bIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSharedSurface::isLessThanResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSharedSurfaceService::Stub> stub =
        octaneapi::ApiSharedSurfaceService::NewStub(getGRPCSettings().getChannel());
    status = stub->isLessThan(context.get(), request, &response);

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


size_t ApiSharedSurfaceProxy::hash(
            const ApiSharedSurfaceProxy *             surface
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSharedSurface::hashRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'surface' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * surfaceIn = new octaneapi::ObjectRef();
    surfaceIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    surfaceIn->set_handle(surface->getObjectHandle());
    request.set_allocated_surface(surfaceIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSharedSurface::hashResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSharedSurfaceService::Stub> stub =
        octaneapi::ApiSharedSurfaceService::NewStub(getGRPCSettings().getChannel());
    status = stub->hash(context.get(), request, &response);

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


void ApiSharedSurfaceProxy::release()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSharedSurface::releaseRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSharedSurfaceService::Stub> stub =
        octaneapi::ApiSharedSurfaceService::NewStub(getGRPCSettings().getChannel());
    status = stub->release(context.get(), request, &response);

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


ApiSharedSurfaceProxy ApiSharedSurfaceProxy::clone() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSharedSurface::cloneRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSharedSurface::cloneResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSharedSurfaceService::Stub> stub =
        octaneapi::ApiSharedSurfaceService::NewStub(getGRPCSettings().getChannel());
    status = stub->clone(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiSharedSurfaceProxy retVal;
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
        ApiSharedSurfaceProxy retVal;
        return retVal;
    }
};


Octane::SharedSurfaceType ApiSharedSurfaceProxy::getType() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSharedSurface::getTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSharedSurface::getTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSharedSurfaceService::Stub> stub =
        octaneapi::ApiSharedSurfaceService::NewStub(getGRPCSettings().getChannel());
    status = stub->getType(context.get(), request, &response);

    Octane::SharedSurfaceType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::SharedSurfaceType resultOut = response.result();
        retVal = static_cast<Octane::SharedSurfaceType>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


uint64_t ApiSharedSurfaceProxy::getD3D11AdapterLuid() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSharedSurface::getD3D11AdapterLuidRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSharedSurface::getD3D11AdapterLuidResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSharedSurfaceService::Stub> stub =
        octaneapi::ApiSharedSurfaceService::NewStub(getGRPCSettings().getChannel());
    status = stub->getD3D11AdapterLuid(context.get(), request, &response);

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


} //end of namespace
