// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apitexturepintypeinfoclient.h"
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
#include "convertapitexturenodetypeinfo_configuration_parameters.h"


GRPCSettings & ApiTexturePinTypeInfoProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


Octane::TextureValueType ApiTexturePinTypeInfoProxy::getTextureValueType(
            const Octane::ApiTextureNodeTypeInfo::Configuration::Parameters & configurationParameters //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTexturePinTypeInfo::getTextureValueTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'configurationParameters' [in] parameter to the request packet.
    octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters * configurationparametersIn = new octaneapi::ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration_ApiTextureNodeTypeInfo_Configuration_Parameters(); //// configurationParameters type=ApiTextureNodeTypeInfo.ApiTextureNodeTypeInfo_Configuration.ApiTextureNodeTypeInfo_Configuration_Parameters;//// ////721////
    // Using Converter 5, type = const ApiTextureNodeTypeInfo::Configuration::Parameters &, protoType = ApiTextureNodeTypeInfo.ApiTextureNodeTypeInfo_Configuration.ApiTextureNodeTypeInfo_Configuration_Parameters
    ApiTextureNodeTypeInfo_Configuration_ParametersConverter::convert(configurationParameters, *configurationparametersIn); //// Convert Called type 1a =ApiTextureNodeTypeInfo.ApiTextureNodeTypeInfo_Configuration.ApiTextureNodeTypeInfo_Configuration_Parameters////
    request.set_allocated_configurationparameters(configurationparametersIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTexturePinTypeInfo::getTextureValueTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTexturePinTypeInfoService::Stub> stub = 
        octaneapi::ApiTexturePinTypeInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getTextureValueType(context.get(), request, &response);

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


