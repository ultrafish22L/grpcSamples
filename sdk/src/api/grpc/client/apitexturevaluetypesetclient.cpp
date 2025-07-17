// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apitexturevaluetypesetclient.h"
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
#include "octaneinfos.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiTextureValueTypeSetProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


uint32_t ApiTextureValueTypeSetProxy::size() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextureValueTypeSet::sizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextureValueTypeSet::sizeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextureValueTypeSetService::Stub> stub =
        octaneapi::ApiTextureValueTypeSetService::NewStub(getGRPCSettings().getChannel());
    status = stub->size1(context.get(), request, &response);

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


Octane::TextureValueType ApiTextureValueTypeSetProxy::at(
            uint32_t                                  index
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextureValueTypeSet::atRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextureValueTypeSet::atResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextureValueTypeSetService::Stub> stub =
        octaneapi::ApiTextureValueTypeSetService::NewStub(getGRPCSettings().getChannel());
    status = stub->at(context.get(), request, &response);

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


bool ApiTextureValueTypeSetProxy::contains(
            Octane::TextureValueType                  textureValueType
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextureValueTypeSet::containsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'textureValueType' [in] parameter to the request packet.
    octaneapi::TextureValueType texturevaluetypeIn;
    texturevaluetypeIn = static_cast<octaneapi::TextureValueType>(textureValueType);
    request.set_texturevaluetype(texturevaluetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextureValueTypeSet::containsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextureValueTypeSetService::Stub> stub =
        octaneapi::ApiTextureValueTypeSetService::NewStub(getGRPCSettings().getChannel());
    status = stub->contains(context.get(), request, &response);

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


uint32_t ApiTextureValueTypeSetProxy::bitField() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextureValueTypeSet::bitFieldRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextureValueTypeSet::bitFieldResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextureValueTypeSetService::Stub> stub =
        octaneapi::ApiTextureValueTypeSetService::NewStub(getGRPCSettings().getChannel());
    status = stub->bitField(context.get(), request, &response);

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


