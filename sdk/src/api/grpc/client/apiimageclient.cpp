// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apiimageclient.h"
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
#include "apiimage.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiImageProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiImageProxy ApiImageProxy::create(
            const Octane::ApiImage::PixelFormat       pixelFormat,
            const int                                 width,
            const int                                 height,
            const bool                                clear
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pixelFormat' [in] parameter to the request packet.
    octaneapi::ApiImage_PixelFormat pixelformatIn;
        pixelformatIn = static_cast<octaneapi::ApiImage_PixelFormat>(pixelFormat);
    request.set_pixelformat(pixelformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'width' [in] parameter to the request packet.
    int32_t widthIn;
    widthIn = width;
    request.set_width(widthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'height' [in] parameter to the request packet.
    int32_t heightIn;
    heightIn = height;
    request.set_height(heightIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'clear' [in] parameter to the request packet.
    bool clearIn;
    clearIn = clear;
    request.set_clear(clearIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiImageProxy retVal;
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
        ApiImageProxy retVal;
        return retVal;
    }
};


ApiImageProxy ApiImageProxy::create(
            const Octane::ApiImage::PixelFormat       pixelFormat,
            const int                                 width,
            const int                                 height,
            const void *const                         data
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::create1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pixelFormat' [in] parameter to the request packet.
    octaneapi::ApiImage_PixelFormat pixelformatIn;
        pixelformatIn = static_cast<octaneapi::ApiImage_PixelFormat>(pixelFormat);
    request.set_pixelformat(pixelformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'width' [in] parameter to the request packet.
    int32_t widthIn;
    widthIn = width;
    request.set_width(widthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'height' [in] parameter to the request packet.
    int32_t heightIn;
    heightIn = height;
    request.set_height(heightIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'data' [in] parameter to the request packet.
    uint64_t dataIn;
    dataIn = reinterpret_cast<uint64_t>(data);
    request.set_data(dataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::create1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->create1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiImageProxy retVal;
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
        ApiImageProxy retVal;
        return retVal;
    }
};


bool ApiImageProxy::saveToFile(
            const char *const                         fullPath,
            const bool                                destHasAlpha,
            const int                                 width,
            const int                                 height,
            const void *const                         buffer,
            Octane::ImageType                         pixelFormat,
            const bool                                isYPointUp
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::saveToFileRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string();
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'destHasAlpha' [in] parameter to the request packet.
    bool desthasalphaIn;
    desthasalphaIn = destHasAlpha;
    request.set_desthasalpha(desthasalphaIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'width' [in] parameter to the request packet.
    int32_t widthIn;
    widthIn = width;
    request.set_width(widthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'height' [in] parameter to the request packet.
    int32_t heightIn;
    heightIn = height;
    request.set_height(heightIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'buffer' [in] parameter to the request packet.
    octaneapi::Buffer * bufferIn = new octaneapi::Buffer();
    // BUFFER TEST 1 : buffer
    size_t bufSize = 0;
    switch (pixelFormat)
    {
        case Octane::IMAGE_TYPE_LDR_RGBA:
        {
            bufSize = width * height * (destHasAlpha ? 4 : 3);
            break;
        }
        case  Octane::IMAGE_TYPE_LDR_MONO:
        {
            bufSize = width *  height * 8;
            break;
        }
        case  Octane::IMAGE_TYPE_LDR_MONO_ALPHA:
        {
            bufSize = width *  height * (destHasAlpha ? 4 : 2);
            break;
        }
        case  Octane::IMAGE_TYPE_HDR_RGBA:
        {
            bufSize = width *  height * (destHasAlpha ? 8 : 6);
            break;
        }
        case  Octane::IMAGE_TYPE_HDR_MONO:
        {
            bufSize = width *  height * 2;
            break;
        }
        case  Octane::IMAGE_TYPE_HDR_MONO_ALPHA:
        {
            bufSize = width *  height * (destHasAlpha ? 8 : 2);
            break;
        }
        case  Octane::IMAGE_TYPE_HALF_RGBA:
        {
            bufSize = width *  height * (destHasAlpha ? 8 : 6);
            break;
        }
        case  Octane::IMAGE_TYPE_HALF_MONO:
        {
            bufSize = width *  height * 2;
            break;
        }
        case  Octane::IMAGE_TYPE_HALF_MONO_ALPHA:
        {
            bufSize = width *  height * (destHasAlpha ? 8 : 2);
            break;
        }
        default:
        {
            assert(!"Invalid image size in ApiImageProxy::saveToFile.");
        }
    };
    if (buffer && bufSize > 0)
    {
        // Copy raw data into the protobuf Buffer (using std::string's set method)
        bufferIn->set_data(reinterpret_cast<const char*>(buffer), pixelFormat);
        bufferIn->set_size(static_cast<uint32_t>(bufSize));
    }
    request.set_allocated_buffer(bufferIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pixelFormat' [in] parameter to the request packet.
    octaneapi::ImageType pixelformatIn;
        pixelformatIn = static_cast<octaneapi::ImageType>(pixelFormat);
    request.set_pixelformat(pixelformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'isYPointUp' [in] parameter to the request packet.
    bool isypointupIn;
    isypointupIn = isYPointUp;
    request.set_isypointup(isypointupIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::saveToFileResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveToFile(context.get(), request, &response);

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


ApiImageProxy ApiImageProxy::loadFromFile(
            const char *                              fullPath
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::loadFromFileRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string();
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::loadFromFileResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->loadFromFile(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiImageProxy retVal;
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
        ApiImageProxy retVal;
        return retVal;
    }
};


ApiImageProxy ApiImageProxy::loadFromMemory(
            const void *                              imageData,
            const size_t                              sizeInBytes
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::loadFromMemoryRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageData' [in] parameter to the request packet.
    octaneapi::Buffer * imagedataIn = new octaneapi::Buffer();
    // BUFFER TEST 1 : imageData
    size_t bufSize = sizeInBytes;
    if (imageData && bufSize > 0)
    {
        // Copy raw data into the protobuf Buffer (using std::string's set method)
        imagedataIn->set_data(reinterpret_cast<const char*>(imageData), sizeInBytes);
        imagedataIn->set_size(static_cast<uint32_t>(bufSize));
    }
    request.set_allocated_imagedata(imagedataIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sizeInBytes' [in] parameter to the request packet.
    uint32_t sizeinbytesIn;
    sizeinbytesIn = static_cast<uint32_t>(sizeInBytes);
    request.set_sizeinbytes(sizeinbytesIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::loadFromMemoryResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->loadFromMemory(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiImageProxy retVal;
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
        ApiImageProxy retVal;
        return retVal;
    }
};


void ApiImageProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
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


int ApiImageProxy::width() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::widthRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::widthResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->width(context.get(), request, &response);

    int retVal = 0;
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


int ApiImageProxy::height() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::heightRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::heightResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->height(context.get(), request, &response);

    int retVal = 0;
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


Octane::ApiImage::PixelFormat ApiImageProxy::pixelFormat() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::pixelFormatRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::pixelFormatResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->pixelFormat(context.get(), request, &response);

    Octane::ApiImage::PixelFormat retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiImage_PixelFormat resultOut = response.result();
        retVal = static_cast<Octane::ApiImage::PixelFormat>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiImageProxy::isARGB() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::isARGBRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::isARGBResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->isARGB(context.get(), request, &response);

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


bool ApiImageProxy::isRGB() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::isRGBRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::isRGBResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->isRGB(context.get(), request, &response);

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


bool ApiImageProxy::isSingleChannel() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::isSingleChannelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::isSingleChannelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->isSingleChannel(context.get(), request, &response);

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


bool ApiImageProxy::hasAlphaChannel() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::hasAlphaChannelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::hasAlphaChannelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasAlphaChannel(context.get(), request, &response);

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


void ApiImageProxy::clear(
            const int                                 x,
            const int                                 y,
            const int                                 width,
            const int                                 height,
            const Octane::ApiColorLdr                 color
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::clearRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    int32_t xIn;
    xIn = x;
    request.set_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    int32_t yIn;
    yIn = y;
    request.set_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'width' [in] parameter to the request packet.
    int32_t widthIn;
    widthIn = width;
    request.set_width(widthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'height' [in] parameter to the request packet.
    int32_t heightIn;
    heightIn = height;
    request.set_height(heightIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'color' [in] parameter to the request packet.
    octaneapi::ApiColorLdr * colorIn = new octaneapi::ApiColorLdr();
    colorIn->set_a(color.a);
    colorIn->set_r(color.r);
    colorIn->set_g(color.g);
    colorIn->set_b(color.b);
    request.set_allocated_color(colorIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->clear(context.get(), request, &response);

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


void ApiImageProxy::updateTo(
            const void *const                         imageData,
            int                                       imageDataSize
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::updateToRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageData' [in] parameter to the request packet.
    octaneapi::Buffer * imagedataIn = new octaneapi::Buffer();
    // BUFFER TEST 1 : imageData
    size_t bufSize = imageDataSize;
    if (imageData && bufSize > 0)
    {
        // Copy raw data into the protobuf Buffer (using std::string's set method)
        imagedataIn->set_data(reinterpret_cast<const char*>(imageData), imageDataSize);
        imagedataIn->set_size(static_cast<uint32_t>(bufSize));
    }
    request.set_allocated_imagedata(imagedataIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageDataSize' [in] parameter to the request packet.
    int32_t imagedatasizeIn;
    imagedatasizeIn = imageDataSize;
    request.set_imagedatasize(imagedatasizeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->updateTo(context.get(), request, &response);

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


Octane::ApiColorLdr ApiImageProxy::pixelAt(
            const int                                 x,
            const int                                 y
            ) const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::pixelAtRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    int32_t xIn;
    xIn = x;
    request.set_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    int32_t yIn;
    yIn = y;
    request.set_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiImage::pixelAtResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->pixelAt(context.get(), request, &response);

    Octane::ApiColorLdr retVal(1, 0, 0, 1);
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiColorLdr resultOut = response.result();
        retVal.a = resultOut.a();
        retVal.r = resultOut.r();
        retVal.g = resultOut.g();
        retVal.b = resultOut.b();
    }
    else
    {
        if (!status.ok())
        {
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


void ApiImageProxy::setPixelAt(
            const int                                 x,
            const int                                 y,
            const Octane::ApiColorLdr                 color
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::setPixelAtRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    int32_t xIn;
    xIn = x;
    request.set_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    int32_t yIn;
    yIn = y;
    request.set_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'color' [in] parameter to the request packet.
    octaneapi::ApiColorLdr * colorIn = new octaneapi::ApiColorLdr();
    colorIn->set_a(color.a);
    colorIn->set_r(color.r);
    colorIn->set_g(color.g);
    colorIn->set_b(color.b);
    request.set_allocated_color(colorIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->setPixelAt(context.get(), request, &response);

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


void ApiImageProxy::multiplyAlphaAt(
            const int                                 x,
            const int                                 y,
            const float                               multiplier
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::multiplyAlphaAtRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    int32_t xIn;
    xIn = x;
    request.set_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    int32_t yIn;
    yIn = y;
    request.set_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'multiplier' [in] parameter to the request packet.
    float multiplierIn;
    multiplierIn = multiplier;
    request.set_multiplier(multiplierIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->multiplyAlphaAt(context.get(), request, &response);

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


void ApiImageProxy::multiplyAllAlphas(
            const float                               amountToMultiplyBy
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::multiplyAllAlphasRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'amountToMultiplyBy' [in] parameter to the request packet.
    float amounttomultiplybyIn;
    amounttomultiplybyIn = amountToMultiplyBy;
    request.set_amounttomultiplyby(amounttomultiplybyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->multiplyAllAlphas(context.get(), request, &response);

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


void ApiImageProxy::desaturate()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::desaturateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->desaturate(context.get(), request, &response);

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


void ApiImageProxy::resize(
            const int                                 newWidth,
            const int                                 newHeight
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiImage::resizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newWidth' [in] parameter to the request packet.
    int32_t newwidthIn;
    newwidthIn = newWidth;
    request.set_newwidth(newwidthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newHeight' [in] parameter to the request packet.
    int32_t newheightIn;
    newheightIn = newHeight;
    request.set_newheight(newheightIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiImageService::Stub> stub =
        octaneapi::ApiImageService::NewStub(getGRPCSettings().getChannel());
    status = stub->resize(context.get(), request, &response);

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
