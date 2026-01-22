// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "framerangetclient.h"
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
#include "octanetime.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & FrameRangeTProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


Octane::FrameRangeT FrameRangeTProxy::make(
            const int32_t                             begin,
            const int32_t                             end
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::FrameRangeT::makeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'begin' [in] parameter to the request packet.
    int32_t beginIn;
    beginIn = begin;
    request.set_begin(beginIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'end' [in] parameter to the request packet.
    int32_t endIn;
    endIn = end;
    request.set_end(endIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::FrameRangeT::makeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::FrameRangeTService::Stub> stub =
        octaneapi::FrameRangeTService::NewStub(getGRPCSettings().getChannel());
    status = stub->make(context.get(), request, &response);

    Octane::FrameRangeT retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::FrameRangeT resultOut = response.result();
        // Using Converter 7, type = Octane::FrameRangeT, protoType = FrameRangeT
        FrameRangeTConverter::convert(resultOut, retVal); // 22 Convert Called type 4 =FrameRangeT;
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


uint32_t FrameRangeTProxy::count() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::FrameRangeT::countRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_FrameRangeT);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::FrameRangeT::countResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::FrameRangeTService::Stub> stub =
        octaneapi::FrameRangeTService::NewStub(getGRPCSettings().getChannel());
    status = stub->count(context.get(), request, &response);

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


} //end of namespace
