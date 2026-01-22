// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "imageexportsettingsclient.h"
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
#include "octaneimageexport.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertimageexportsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ImageExportSettingsProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


std::string ImageExportSettingsProxy::getExtension(
            Octane::SaveImageFileType                 type
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::getExtensionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::SaveImageFileType typeIn;
        typeIn = static_cast<octaneapi::SaveImageFileType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::getExtensionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->getExtension(context.get(), request, &response);

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


uint32_t ImageExportSettingsProxy::getBitsPerComponent(
            const Octane::SaveImageBitDepth           bitDepth
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::getBitsPerComponentRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'bitDepth' [in] parameter to the request packet.
    octaneapi::SaveImageBitDepth bitdepthIn;
        bitdepthIn = static_cast<octaneapi::SaveImageBitDepth>(bitDepth);
    request.set_bitdepth(bitdepthIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::getBitsPerComponentResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->getBitsPerComponent(context.get(), request, &response);

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


uint32_t ImageExportSettingsProxy::getBitsPerComponent(
            const Octane::ImageSaveFormat             format
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::getBitsPerComponent1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'format' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat formatIn;
        formatIn = static_cast<octaneapi::ImageSaveFormat>(format);
    request.set_format(formatIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::getBitsPerComponent1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->getBitsPerComponent1(context.get(), request, &response);

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


Octane::SaveImageBitDepth ImageExportSettingsProxy::getBitDepth(
            const Octane::ImageSaveFormat             format
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::getBitDepthRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'format' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat formatIn;
        formatIn = static_cast<octaneapi::ImageSaveFormat>(format);
    request.set_format(formatIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::getBitDepthResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->getBitDepth(context.get(), request, &response);

    Octane::SaveImageBitDepth retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::SaveImageBitDepth resultOut = response.result();
        retVal = static_cast<Octane::SaveImageBitDepth>(resultOut);
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


Octane::ImageSaveFormat ImageExportSettingsProxy::getFormat(
            const Octane::SaveImageFileType           type,
            const Octane::SaveImageBitDepth           bitDepth
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::getFormatRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::SaveImageFileType typeIn;
        typeIn = static_cast<octaneapi::SaveImageFileType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'bitDepth' [in] parameter to the request packet.
    octaneapi::SaveImageBitDepth bitdepthIn;
        bitdepthIn = static_cast<octaneapi::SaveImageBitDepth>(bitDepth);
    request.set_bitdepth(bitdepthIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::getFormatResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->getFormat(context.get(), request, &response);

    Octane::ImageSaveFormat retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ImageSaveFormat resultOut = response.result();
        retVal = static_cast<Octane::ImageSaveFormat>(resultOut);
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


Octane::SaveImageFileType ImageExportSettingsProxy::getType(
            const Octane::ImageSaveFormat             format
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::getTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'format' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat formatIn;
        formatIn = static_cast<octaneapi::ImageSaveFormat>(format);
    request.set_format(formatIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::getTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->getType(context.get(), request, &response);

    Octane::SaveImageFileType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::SaveImageFileType resultOut = response.result();
        retVal = static_cast<Octane::SaveImageFileType>(resultOut);
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


Octane::ImageExportSettings ImageExportSettingsProxy::makeFromOldSettings(
            const Octane::ImageSaveFormat             imageSaveFormat,
            const Octane::PremultipliedAlphaType      premultipliedAlphaType,
            const Octane::ExrCompressionType          exrCompressionType,
            const float                               exrCompressionLevel
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::makeFromOldSettingsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageSaveFormat' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat imagesaveformatIn;
        imagesaveformatIn = static_cast<octaneapi::ImageSaveFormat>(imageSaveFormat);
    request.set_imagesaveformat(imagesaveformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
        premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'exrCompressionType' [in] parameter to the request packet.
    octaneapi::ExrCompressionType exrcompressiontypeIn;
        exrcompressiontypeIn = static_cast<octaneapi::ExrCompressionType>(exrCompressionType);
    request.set_exrcompressiontype(exrcompressiontypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'exrCompressionLevel' [in] parameter to the request packet.
    float exrcompressionlevelIn;
    exrcompressionlevelIn = exrCompressionLevel;
    request.set_exrcompressionlevel(exrcompressionlevelIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::makeFromOldSettingsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->makeFromOldSettings(context.get(), request, &response);

    Octane::ImageExportSettings retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ImageExportSettings resultOut = response.result();
        ImageExportSettingsConverter::convert(resultOut, retVal);
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


Octane::ImageExportSettings ImageExportSettingsProxy::makeFromImageSaveFormat(
            const Octane::ImageSaveFormat             imageSaveFormat,
            const Octane::PremultipliedAlphaType      premultipliedAlphaType
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::makeFromImageSaveFormatRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageSaveFormat' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat imagesaveformatIn;
        imagesaveformatIn = static_cast<octaneapi::ImageSaveFormat>(imageSaveFormat);
    request.set_imagesaveformat(imagesaveformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
        premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::makeFromImageSaveFormatResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->makeFromImageSaveFormat(context.get(), request, &response);

    Octane::ImageExportSettings retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ImageExportSettings resultOut = response.result();
        ImageExportSettingsConverter::convert(resultOut, retVal);
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


Octane::ImageExportSettings ImageExportSettingsProxy::makeExr(
            const Octane::SaveImageBitDepth           bitDepth,
            const bool                                premultipliedAlpha,
            const Octane::ExrCompressionType          compressionType,
            const float                               compressionLevel
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::makeExrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'bitDepth' [in] parameter to the request packet.
    octaneapi::SaveImageBitDepth bitdepthIn;
        bitdepthIn = static_cast<octaneapi::SaveImageBitDepth>(bitDepth);
    request.set_bitdepth(bitdepthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlpha' [in] parameter to the request packet.
    bool premultipliedalphaIn;
    premultipliedalphaIn = premultipliedAlpha;
    request.set_premultipliedalpha(premultipliedalphaIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'compressionType' [in] parameter to the request packet.
    octaneapi::ExrCompressionType compressiontypeIn;
        compressiontypeIn = static_cast<octaneapi::ExrCompressionType>(compressionType);
    request.set_compressiontype(compressiontypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'compressionLevel' [in] parameter to the request packet.
    float compressionlevelIn;
    compressionlevelIn = compressionLevel;
    request.set_compressionlevel(compressionlevelIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::makeExrResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->makeExr(context.get(), request, &response);

    Octane::ImageExportSettings retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ImageExportSettings resultOut = response.result();
        ImageExportSettingsConverter::convert(resultOut, retVal);
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


Octane::ImageExportSettings ImageExportSettingsProxy::makeTiff(
            const Octane::SaveImageBitDepth           bitDepth,
            const Octane::PremultipliedAlphaType      premultipliedAlphaType,
            const Octane::TiffCompressionType         compressionType
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::makeTiffRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'bitDepth' [in] parameter to the request packet.
    octaneapi::SaveImageBitDepth bitdepthIn;
        bitdepthIn = static_cast<octaneapi::SaveImageBitDepth>(bitDepth);
    request.set_bitdepth(bitdepthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
        premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'compressionType' [in] parameter to the request packet.
    octaneapi::TiffCompressionType compressiontypeIn;
        compressiontypeIn = static_cast<octaneapi::TiffCompressionType>(compressionType);
    request.set_compressiontype(compressiontypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::makeTiffResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->makeTiff(context.get(), request, &response);

    Octane::ImageExportSettings retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ImageExportSettings resultOut = response.result();
        ImageExportSettingsConverter::convert(resultOut, retVal);
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


Octane::ImageExportSettings ImageExportSettingsProxy::makePng(
            const Octane::SaveImageBitDepth           bitDepth
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::makePngRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'bitDepth' [in] parameter to the request packet.
    octaneapi::SaveImageBitDepth bitdepthIn;
        bitdepthIn = static_cast<octaneapi::SaveImageBitDepth>(bitDepth);
    request.set_bitdepth(bitdepthIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::makePngResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->makePng(context.get(), request, &response);

    Octane::ImageExportSettings retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ImageExportSettings resultOut = response.result();
        ImageExportSettingsConverter::convert(resultOut, retVal);
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


Octane::ImageExportSettings ImageExportSettingsProxy::makeJpeg(
            const float                               quality
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ImageExportSettings::makeJpegRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'quality' [in] parameter to the request packet.
    float qualityIn;
    qualityIn = quality;
    request.set_quality(qualityIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ImageExportSettings::makeJpegResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ImageExportSettingsService::Stub> stub =
        octaneapi::ImageExportSettingsService::NewStub(getGRPCSettings().getChannel());
    status = stub->makeJpeg(context.get(), request, &response);

    Octane::ImageExportSettings retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ImageExportSettings resultOut = response.result();
        ImageExportSettingsConverter::convert(resultOut, retVal);
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
