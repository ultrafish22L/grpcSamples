// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apibase64client.h"
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
#include "apibase64.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiBase64Proxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiBase64Proxy::encode(
            const char *                              data, //// test821 //// 
            const size_t                              size, //// test821 //// 
            Octane::CharArrayT &                      encoded, //// test821 //// 
            const bool                                useBase64Url //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBase64::encodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'data' [in] parameter to the request packet.
    std::string * dataIn = new std::string(); //// data type=string;//// ////721////
    *dataIn = checkString(data);
    request.set_allocated_data(dataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'size' [in] parameter to the request packet.
    uint32_t sizeIn;
    sizeIn = static_cast<uint32_t>(size);////2 const size_t////
    request.set_size(sizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'useBase64Url' [in] parameter to the request packet.
    bool usebase64urlIn;
    usebase64urlIn = useBase64Url;////2 const bool////
    request.set_usebase64url(usebase64urlIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBase64::encodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBase64Service::Stub> stub = 
        octaneapi::ApiBase64Service::NewStub(getGRPCSettings().getChannel());
    status = stub->encode(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'encoded' [out] parameter from the gRPC response packet
        std::string encodedOut = response.encoded();
        // param.mType = Octane::CharArrayT &
        encoded = Octane::CharArrayT(StringManager::getInstance().addString(encodedOut), encodedOut.length()); ////string mgr////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiBase64Proxy::decode(
            const char *                              data, //// test821 //// 
            const size_t                              size, //// test821 //// 
            Octane::CharArrayT &                      decoded, //// test821 //// 
            const bool                                useBase64Url //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiBase64::decodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'data' [in] parameter to the request packet.
    std::string * dataIn = new std::string(); //// data type=string;//// ////721////
    *dataIn = checkString(data);
    request.set_allocated_data(dataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'size' [in] parameter to the request packet.
    uint32_t sizeIn;
    sizeIn = static_cast<uint32_t>(size);////2 const size_t////
    request.set_size(sizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'useBase64Url' [in] parameter to the request packet.
    bool usebase64urlIn;
    usebase64urlIn = useBase64Url;////2 const bool////
    request.set_usebase64url(usebase64urlIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiBase64::decodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiBase64Service::Stub> stub = 
        octaneapi::ApiBase64Service::NewStub(getGRPCSettings().getChannel());
    status = stub->decode(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'decoded' [out] parameter from the gRPC response packet
        std::string decodedOut = response.decoded();
        // param.mType = Octane::CharArrayT &
        decoded = Octane::CharArrayT(StringManager::getInstance().addString(decodedOut), decodedOut.length()); ////string mgr////
    }
    else
    {
        if (!status.ok())
        {
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


