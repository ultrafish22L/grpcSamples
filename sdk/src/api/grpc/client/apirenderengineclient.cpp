// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apirenderengineclient.h"
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
#include "apirender.grpc.pb.h"
#include "apinodeclient.h"
#include "apinodegraphclient.h"
#include "apioutputcolorspaceinfoclient.h"
#include "apisharedsurfaceclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapiarrayapirenderimage.h"
#include "convertapidevicememoryusage.h"
#include "convertapideviceresourcestatistics.h"
#include "convertapidevicesharedsurfaceinfo.h"
#include "convertapigeometrystatistics.h"
#include "convertapiarrayapirenderimage.h"
#include "convertapitexturestatistics.h"
#include "convertrenderresultstatistics.h"
#include "convertimageexportsettings.h"
#include "convertrenderpassexport.h"


GRPCSettings & ApiRenderEngineProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiRenderEngineProxy::setRenderTargetNode(
            ApiNodeProxy *                            targetNode //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setRenderTargetNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'targetNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * targetnodeIn = new octaneapi::ObjectRef();////761////
    targetnodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    targetnodeIn->set_handle(targetNode->getObjectHandle());
    request.set_allocated_targetnode(targetnodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setRenderTargetNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setRenderTargetNode(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


ApiNodeProxy ApiRenderEngineProxy::getRenderTargetNode()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRenderTargetNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRenderTargetNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderTargetNode(context.get(), request, &response);

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
        ApiNodeProxy retVal;////714////
        return retVal;
    }
};


ApiNodeProxy ApiRenderEngineProxy::getRenderGeometryNode()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRenderGeometryNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRenderGeometryNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderGeometryNode(context.get(), request, &response);

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
        ApiNodeProxy retVal;////714////
        return retVal;
    }
};


ApiNodeProxy ApiRenderEngineProxy::getRenderCameraNode()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRenderCameraNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRenderCameraNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderCameraNode(context.get(), request, &response);

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
        ApiNodeProxy retVal;////714////
        return retVal;
    }
};


void ApiRenderEngineProxy::setRenderRegion(
            const bool                                active, //// test821 //// 
            const OctaneVec::uint32_2                 regionMin, //// test821 //// 
            const OctaneVec::uint32_2                 regionMax, //// test821 //// 
            const uint32_t                            featherWidth //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setRenderRegionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'active' [in] parameter to the request packet.
    bool activeIn;
    activeIn = active;////2 const bool////
    request.set_active(activeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'regionMin' [in] parameter to the request packet.
    octaneapi::uint32_2 * regionminIn = new octaneapi::uint32_2(); //// regionMin type=uint32_2;//// ////721////
    (*regionminIn).set_x(regionMin.x);
    (*regionminIn).set_y(regionMin.y);
    request.set_allocated_regionmin(regionminIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'regionMax' [in] parameter to the request packet.
    octaneapi::uint32_2 * regionmaxIn = new octaneapi::uint32_2(); //// regionMax type=uint32_2;//// ////721////
    (*regionmaxIn).set_x(regionMax.x);
    (*regionmaxIn).set_y(regionMax.y);
    request.set_allocated_regionmax(regionmaxIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'featherWidth' [in] parameter to the request packet.
    uint32_t featherwidthIn;
    featherwidthIn = featherWidth;////2 const uint32_t////
    request.set_featherwidth(featherwidthIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setRenderRegion(context.get(), request, &response);

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


void ApiRenderEngineProxy::getRenderRegion(
            bool &                                    active, //// test821 //// 
            OctaneVec::uint32_2 &                     regionMin, //// test821 //// 
            OctaneVec::uint32_2 &                     regionMax, //// test821 //// 
            uint32_t &                                featherWidth //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRenderRegionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRenderRegionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderRegion(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'active' [out] parameter from the gRPC response packet
        bool activeOut = response.active();
        active = activeOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'regionMin' [out] parameter from the gRPC response packet
        octaneapi::uint32_2 regionMinOut = response.regionmin();
        regionMin.x = regionMinOut.x();
        regionMin.y = regionMinOut.y();

        /////////////////////////////////////////////////////////////////////
        // Process 'regionMax' [out] parameter from the gRPC response packet
        octaneapi::uint32_2 regionMaxOut = response.regionmax();
        regionMax.x = regionMaxOut.x();
        regionMax.y = regionMaxOut.y();

        /////////////////////////////////////////////////////////////////////
        // Process 'featherWidth' [out] parameter from the gRPC response packet
        uint32_t featherWidthOut = response.featherwidth();
        featherWidth = featherWidthOut;//// SECOND////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setAsyncTonemapParams(
            Octane::TonemapBufferType                 bufferType, //// test821 //// 
            bool                                      cryptomatteFalseColor, //// test821 //// 
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setAsyncTonemapParamsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'bufferType' [in] parameter to the request packet.
    octaneapi::TonemapBufferType buffertypeIn;
    buffertypeIn = static_cast<octaneapi::TonemapBufferType>(bufferType);
    request.set_buffertype(buffertypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cryptomatteFalseColor' [in] parameter to the request packet.
    bool cryptomattefalsecolorIn;
    cryptomattefalsecolorIn = cryptomatteFalseColor;////2 bool////
    request.set_cryptomattefalsecolor(cryptomattefalsecolorIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * colorspaceinfoIn = new octaneapi::ObjectRef();////761////
    colorspaceinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);////5////
    colorspaceinfoIn->set_handle(colorSpaceInfo->getObjectHandle());
    request.set_allocated_colorspaceinfo(colorspaceinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
    premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setAsyncTonemapParams(context.get(), request, &response);

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


void ApiRenderEngineProxy::setAsyncTonemapParams(
            Octane::TonemapBufferType                 bufferType, //// test821 //// 
            bool                                      cryptomatteFalseColor, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setAsyncTonemapParams1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'bufferType' [in] parameter to the request packet.
    octaneapi::TonemapBufferType buffertypeIn;
    buffertypeIn = static_cast<octaneapi::TonemapBufferType>(bufferType);
    request.set_buffertype(buffertypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cryptomatteFalseColor' [in] parameter to the request packet.
    bool cryptomattefalsecolorIn;
    cryptomattefalsecolorIn = cryptomatteFalseColor;////2 bool////
    request.set_cryptomattefalsecolor(cryptomattefalsecolorIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
    premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setAsyncTonemapParams1(context.get(), request, &response);

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


Octane::TonemapBufferType ApiRenderEngineProxy::asyncTonemapBufferType()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::asyncTonemapBufferTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::asyncTonemapBufferTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->asyncTonemapBufferType(context.get(), request, &response);

    Octane::TonemapBufferType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::TonemapBufferType resultOut = response.result();
        retVal = static_cast<Octane::TonemapBufferType>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::asyncTonemapCryptomatteFalseColor()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::asyncTonemapCryptomatteFalseColorRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::asyncTonemapCryptomatteFalseColorResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->asyncTonemapCryptomatteFalseColor(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


ApiOutputColorSpaceInfoProxy ApiRenderEngineProxy::asyncTonemapOutputColorSpaceInfo()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::asyncTonemapOutputColorSpaceInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::asyncTonemapOutputColorSpaceInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->asyncTonemapOutputColorSpaceInfo(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiOutputColorSpaceInfoProxy retVal;
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
        ApiOutputColorSpaceInfoProxy retVal;////714////
        return retVal;
    }
};


Octane::NamedColorSpace ApiRenderEngineProxy::asyncTonemapColorSpace()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::asyncTonemapColorSpaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::asyncTonemapColorSpaceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->asyncTonemapColorSpace(context.get(), request, &response);

    Octane::NamedColorSpace retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NamedColorSpace resultOut = response.result();
        retVal = static_cast<Octane::NamedColorSpace>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


Octane::PremultipliedAlphaType ApiRenderEngineProxy::asyncTonemapPremultipliedAlphaType()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::asyncTonemapPremultipliedAlphaTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::asyncTonemapPremultipliedAlphaTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->asyncTonemapPremultipliedAlphaType(context.get(), request, &response);

    Octane::PremultipliedAlphaType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::PremultipliedAlphaType resultOut = response.result();
        retVal = static_cast<Octane::PremultipliedAlphaType>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::setAsyncTonemapRenderPasses(
            const Octane::ApiArray<Octane::RenderPassId> & tonemapPasses //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setAsyncTonemapRenderPassesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'tonemapPasses' [in] parameter to the request packet.
    octaneapi::ApiArrayRenderPassId * tonemappassesIn = new octaneapi::ApiArrayRenderPassId(); //// tonemapPasses type=ApiArrayRenderPassId;//// ////721////
    //// Client Array Type B////
    //// param.mProtoCppType = ApiArrayRenderPassId param.mType = const ApiArray<Octane::RenderPassId> & ////
    for (int h = 0; h < tonemapPasses.mSize; h++)
    {
        tonemappassesIn->add_data(static_cast<octaneapi::RenderPassId>(tonemapPasses.mData[h]));
    }
    request.set_allocated_tonemappasses(tonemappassesIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setAsyncTonemapRenderPassesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setAsyncTonemapRenderPasses(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::asyncTonemapRenderPasses(
            Octane::ApiArray<Octane::RenderPassId> &  tonemapPasses //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::asyncTonemapRenderPassesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'tonemapPasses' [in] parameter to the request packet.
    octaneapi::ApiArrayRenderPassId * tonemappassesIn = new octaneapi::ApiArrayRenderPassId(); //// tonemapPasses type=ApiArrayRenderPassId;//// ////721////
    //// Client Array Type B////
    //// param.mProtoCppType = ApiArrayRenderPassId param.mType = ApiArray<Octane::RenderPassId> & ////
    for (int h = 0; h < tonemapPasses.mSize; h++)
    {
        tonemappassesIn->add_data(static_cast<octaneapi::RenderPassId>(tonemapPasses.mData[h]));
    }
    request.set_allocated_tonemappasses(tonemappassesIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->asyncTonemapRenderPasses(context.get(), request, &response);

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


void ApiRenderEngineProxy::getEnabledAovs(
            const ApiNodeProxy *const                 renderTargetNode, //// test821 //// 
            std::vector<Octane::RenderPassId> &       aovIds //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getEnabledAovsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderTargetNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * rendertargetnodeIn = new octaneapi::ObjectRef();////761////
    rendertargetnodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    rendertargetnodeIn->set_handle(renderTargetNode->getObjectHandle());
    request.set_allocated_rendertargetnode(rendertargetnodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getEnabledAovsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getEnabledAovs(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'aovIds' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayRenderPassId aovIdsOut = response.aovids();
        aovIds.reserve(aovIdsOut.data_size());
        for (int i = 0; i < aovIdsOut.data_size(); i++)
        {
            //// param.mProtoCppType = ApiArrayRenderPassId param.mType = ApiArray<Octane::RenderPassId> & ////
            aovIds.push_back(static_cast<Octane::RenderPassId>(aovIdsOut.data(i)));
        }
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::freeTonemapPasses(
            Octane::ApiArray<Octane::RenderPassId> &  tonemapPasses //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::freeTonemapPassesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'tonemapPasses' [in] parameter to the request packet.
    octaneapi::ApiArrayRenderPassId * tonemappassesIn = new octaneapi::ApiArrayRenderPassId(); //// tonemapPasses type=ApiArrayRenderPassId;//// ////721////
    //// Client Array Type B////
    //// param.mProtoCppType = ApiArrayRenderPassId param.mType = ApiArray<Octane::RenderPassId> & ////
    for (int h = 0; h < tonemapPasses.mSize; h++)
    {
        tonemappassesIn->add_data(static_cast<octaneapi::RenderPassId>(tonemapPasses.mData[h]));
    }
    request.set_allocated_tonemappasses(tonemappassesIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->freeTonemapPasses(context.get(), request, &response);

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


Octane::RenderPassId ApiRenderEngineProxy::displayRenderPassId()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::displayRenderPassIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::displayRenderPassIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->displayRenderPassId(context.get(), request, &response);

    Octane::RenderPassId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::RenderPassId resultOut = response.result();
        retVal = static_cast<Octane::RenderPassId>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setSubSampleMode(
            const Octane::SubSampleMode               mode //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setSubSampleModeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'mode' [in] parameter to the request packet.
    octaneapi::SubSampleMode modeIn;
    modeIn = static_cast<octaneapi::SubSampleMode>(mode);
    request.set_mode(modeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setSubSampleMode(context.get(), request, &response);

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


Octane::SubSampleMode ApiRenderEngineProxy::getSubSampleMode()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getSubSampleModeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getSubSampleModeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getSubSampleMode(context.get(), request, &response);

    Octane::SubSampleMode retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::SubSampleMode resultOut = response.result();
        retVal = static_cast<Octane::SubSampleMode>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setClayMode(
            const Octane::ClayMode                    mode //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setClayModeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'mode' [in] parameter to the request packet.
    octaneapi::ClayMode modeIn;
    modeIn = static_cast<octaneapi::ClayMode>(mode);
    request.set_mode(modeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setClayMode(context.get(), request, &response);

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


Octane::ClayMode ApiRenderEngineProxy::clayMode()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::clayModeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::clayModeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->clayMode(context.get(), request, &response);

    Octane::ClayMode retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ClayMode resultOut = response.result();
        retVal = static_cast<Octane::ClayMode>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


float ApiRenderEngineProxy::fps()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::fpsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::fpsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->fps(context.get(), request, &response);

    float retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        float resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setFps(
            const float                               fps //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setFpsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fps' [in] parameter to the request packet.
    float fpsIn;
    fpsIn = fps;////2 const float////
    request.set_fps(fpsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setFps(context.get(), request, &response);

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


bool ApiRenderEngineProxy::isCompiling()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isCompilingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isCompilingResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isCompiling(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::isCompressingTextures()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isCompressingTexturesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isCompressingTexturesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isCompressingTextures(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::hasPendingRenderData()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::hasPendingRenderDataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::hasPendingRenderDataResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasPendingRenderData(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


Octane::CLevelT ApiRenderEngineProxy::getCurrentChangeLevel()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getCurrentChangeLevelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getCurrentChangeLevelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getCurrentChangeLevel(context.get(), request, &response);

    Octane::CLevelT retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::CLevelT resultOut = response.result();
        ////Octane::CLevelT TEST ////
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


Octane::CLevelT ApiRenderEngineProxy::getRenderImageChangeLevel()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRenderImageChangeLevelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRenderImageChangeLevelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderImageChangeLevel(context.get(), request, &response);

    Octane::CLevelT retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::CLevelT resultOut = response.result();
        ////Octane::CLevelT TEST ////
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


Octane::CLevelT ApiRenderEngineProxy::getRenderRestartedChangeLevel()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRenderRestartedChangeLevelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRenderRestartedChangeLevelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderRestartedChangeLevel(context.get(), request, &response);

    Octane::CLevelT retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::CLevelT resultOut = response.result();
        ////Octane::CLevelT TEST ////
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


void ApiRenderEngineProxy::setAsyncUpdateCallback(
            Octane::ApiRenderEngine::AsyncUpdateCallbackT callback, //// test821 //// 
            void *                                    userData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setAsyncUpdateCallbackRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::AsyncUpdateCallbackT * callbackIn = new octaneapi::AsyncUpdateCallbackT(); //// callback type=AsyncUpdateCallbackT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("AsyncUpdateCallback"); 
    //CallbackStorage::registerAsyncUpdateCallback(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiRenderEngine" && method.mName == "setAsyncUpdateCallback") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setAsyncUpdateCallbackResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setAsyncUpdateCallback(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerAsyncUpdateCallback( response.callbackid(), callback);
        CallbackStorage::registerAsyncUpdateCallback( response.callbackid(), callback);
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::updatesAreAsync()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::updatesAreAsyncRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::updatesAreAsyncResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->updatesAreAsync(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::isImageReady()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isImageReadyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isImageReadyResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isImageReady(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::resetImageReady()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::resetImageReadyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->resetImageReady(context.get(), request, &response);

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


bool ApiRenderEngineProxy::isRenderFailure()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isRenderFailureRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isRenderFailureResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isRenderFailure(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::resetRenderFailure()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::resetRenderFailureRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->resetRenderFailure(context.get(), request, &response);

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


void ApiRenderEngineProxy::setOnTileBlendedCallback(
            Octane::ApiRenderEngine::OnTileBlendedCallbackT callback, //// test821 //// 
            void *                                    userData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setOnTileBlendedCallbackRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::OnTileBlendedCallbackT * callbackIn = new octaneapi::OnTileBlendedCallbackT(); //// callback type=OnTileBlendedCallbackT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("OnTileBlendedCallback"); 
    //CallbackStorage::registerOnTileBlendedCallback(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiRenderEngine" && method.mName == "setOnTileBlendedCallback") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setOnTileBlendedCallbackResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOnTileBlendedCallback(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnTileBlendedCallback( response.callbackid(), callback);
        CallbackStorage::registerOnTileBlendedCallback( response.callbackid(), callback);
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setOnNewStatisticsCallback(
            Octane::ApiRenderEngine::OnNewStatisticsCallbackT callback, //// test821 //// 
            void *                                    userData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setOnNewStatisticsCallbackRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::OnNewStatisticsCallbackT * callbackIn = new octaneapi::OnNewStatisticsCallbackT(); //// callback type=OnNewStatisticsCallbackT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("OnNewStatisticsCallback"); 
    //CallbackStorage::registerOnNewStatisticsCallback(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiRenderEngine" && method.mName == "setOnNewStatisticsCallback") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setOnNewStatisticsCallbackResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOnNewStatisticsCallback(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnNewStatisticsCallback( response.callbackid(), callback);
        CallbackStorage::registerOnNewStatisticsCallback( response.callbackid(), callback);
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setOnNewImageCallback(
            Octane::ApiRenderEngine::OnNewImageCallbackT callback, //// test821 //// 
            void *                                    userData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setOnNewImageCallbackRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::OnNewImageCallbackT * callbackIn = new octaneapi::OnNewImageCallbackT(); //// callback type=OnNewImageCallbackT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("OnNewImageCallback"); 
    //CallbackStorage::registerOnNewImageCallback(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiRenderEngine" && method.mName == "setOnNewImageCallback") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setOnNewImageCallbackResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOnNewImageCallback(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnNewImageCallback( response.callbackid(), callback);
        CallbackStorage::registerOnNewImageCallback( response.callbackid(), callback);
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setOnOcioErrorCallback(
            Octane::ApiRenderEngine::OnOcioErrorCallbackT callback, //// test821 //// 
            void *                                    userData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setOnOcioErrorCallbackRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::OnOcioErrorCallbackT * callbackIn = new octaneapi::OnOcioErrorCallbackT(); //// callback type=OnOcioErrorCallbackT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("OnOcioErrorCallback"); 
    //CallbackStorage::registerOnOcioErrorCallback(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiRenderEngine" && method.mName == "setOnOcioErrorCallback") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setOnOcioErrorCallbackResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOnOcioErrorCallback(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnOcioErrorCallback( response.callbackid(), callback);
        CallbackStorage::registerOnOcioErrorCallback( response.callbackid(), callback);
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setOnRenderFailureCallback(
            Octane::ApiRenderEngine::OnRenderFailureCallbackT callback, //// test821 //// 
            void *                                    userData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setOnRenderFailureCallbackRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::OnRenderFailureCallbackT * callbackIn = new octaneapi::OnRenderFailureCallbackT(); //// callback type=OnRenderFailureCallbackT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("OnRenderFailureCallback"); 
    //CallbackStorage::registerOnRenderFailureCallback(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiRenderEngine" && method.mName == "setOnRenderFailureCallback") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setOnRenderFailureCallbackResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOnRenderFailureCallback(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnRenderFailureCallback( response.callbackid(), callback);
        CallbackStorage::registerOnRenderFailureCallback( response.callbackid(), callback);
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setForceCallbacksInRenderThreads(
            const bool                                enabled //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setForceCallbacksInRenderThreadsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'enabled' [in] parameter to the request packet.
    bool enabledIn;
    enabledIn = enabled;////2 const bool////
    request.set_enabled(enabledIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setForceCallbacksInRenderThreads(context.get(), request, &response);

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


bool ApiRenderEngineProxy::grabRenderResult(
            Octane::ApiArray<Octane::ApiRenderImage> & renderImages //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::grabRenderResultRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::grabRenderResultResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->grabRenderResult(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'renderImages' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayApiRenderImage renderImagesOut = response.renderimages();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiArrayApiRenderImageConverter::convert(renderImagesOut, renderImages); ////Convert Called type 5223 =ApiArrayApiRenderImage;////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::releaseRenderResult()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::releaseRenderResultRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->releaseRenderResult(context.get(), request, &response);

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


bool ApiRenderEngineProxy::synchronousTonemap(
            const Octane::RenderPassId *              passes, //// test821 //// 
            size_t                                    passesLength, //// test821 //// 
            Octane::TonemapBufferType                 bufferType, //// test821 //// 
            bool                                      cryptomatteFalseColor, //// test821 //// 
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType, //// test821 //// 
            Octane::ApiArray<Octane::ApiRenderImage> & results //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::synchronousTonemapRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'passes' [in] parameter to the request packet.
    octaneapi::ApiArrayRenderPassId * passesIn = new octaneapi::ApiArrayRenderPassId(); //// passes type=ApiArrayRenderPassId;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = ApiArrayRenderPassId param.mType = const Octane::RenderPassId * ////
    for (size_t h = 0; h < passesLength; h++)
    {
        passesIn->add_data(static_cast<octaneapi::RenderPassId>(passes[h]));
    }
    request.set_allocated_passes(passesIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesLength' [in] parameter to the request packet.
    uint32_t passeslengthIn;
    passeslengthIn = static_cast<uint32_t>(passesLength);////2 size_t////
    request.set_passeslength(passeslengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'bufferType' [in] parameter to the request packet.
    octaneapi::TonemapBufferType buffertypeIn;
    buffertypeIn = static_cast<octaneapi::TonemapBufferType>(bufferType);
    request.set_buffertype(buffertypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cryptomatteFalseColor' [in] parameter to the request packet.
    bool cryptomattefalsecolorIn;
    cryptomattefalsecolorIn = cryptomatteFalseColor;////2 bool////
    request.set_cryptomattefalsecolor(cryptomattefalsecolorIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * colorspaceinfoIn = new octaneapi::ObjectRef();////761////
    colorspaceinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);////5////
    colorspaceinfoIn->set_handle(colorSpaceInfo->getObjectHandle());
    request.set_allocated_colorspaceinfo(colorspaceinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
    premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::synchronousTonemapResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->synchronousTonemap(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'results' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayApiRenderImage resultsOut = response.results();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiArrayApiRenderImageConverter::convert(resultsOut, results); ////Convert Called type 5223 =ApiArrayApiRenderImage;////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::synchronousTonemap(
            const Octane::RenderPassId *              passes, //// test821 //// 
            size_t                                    passesLength, //// test821 //// 
            Octane::TonemapBufferType                 bufferType, //// test821 //// 
            bool                                      cryptomatteFalseColor, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType, //// test821 //// 
            Octane::ApiArray<Octane::ApiRenderImage> & results //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::synchronousTonemap1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'passes' [in] parameter to the request packet.
    octaneapi::ApiArrayRenderPassId * passesIn = new octaneapi::ApiArrayRenderPassId(); //// passes type=ApiArrayRenderPassId;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = ApiArrayRenderPassId param.mType = const Octane::RenderPassId * ////
    for (size_t h = 0; h < passesLength; h++)
    {
        passesIn->add_data(static_cast<octaneapi::RenderPassId>(passes[h]));
    }
    request.set_allocated_passes(passesIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesLength' [in] parameter to the request packet.
    uint32_t passeslengthIn;
    passeslengthIn = static_cast<uint32_t>(passesLength);////2 size_t////
    request.set_passeslength(passeslengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'bufferType' [in] parameter to the request packet.
    octaneapi::TonemapBufferType buffertypeIn;
    buffertypeIn = static_cast<octaneapi::TonemapBufferType>(bufferType);
    request.set_buffertype(buffertypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cryptomatteFalseColor' [in] parameter to the request packet.
    bool cryptomattefalsecolorIn;
    cryptomattefalsecolorIn = cryptomatteFalseColor;////2 bool////
    request.set_cryptomattefalsecolor(cryptomattefalsecolorIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
    premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::synchronousTonemap1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->synchronousTonemap1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'results' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayApiRenderImage resultsOut = response.results();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiArrayApiRenderImageConverter::convert(resultsOut, results); ////Convert Called type 5223 =ApiArrayApiRenderImage;////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::synchronousTonemapAllRenderPasses(
            Octane::TonemapBufferType                 bufferType, //// test821 //// 
            bool                                      cryptomatteFalseColor, //// test821 //// 
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType, //// test821 //// 
            Octane::ApiArray<Octane::ApiRenderImage> & results //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::synchronousTonemapAllRenderPassesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'bufferType' [in] parameter to the request packet.
    octaneapi::TonemapBufferType buffertypeIn;
    buffertypeIn = static_cast<octaneapi::TonemapBufferType>(bufferType);
    request.set_buffertype(buffertypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cryptomatteFalseColor' [in] parameter to the request packet.
    bool cryptomattefalsecolorIn;
    cryptomattefalsecolorIn = cryptomatteFalseColor;////2 bool////
    request.set_cryptomattefalsecolor(cryptomattefalsecolorIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * colorspaceinfoIn = new octaneapi::ObjectRef();////761////
    colorspaceinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);////5////
    colorspaceinfoIn->set_handle(colorSpaceInfo->getObjectHandle());
    request.set_allocated_colorspaceinfo(colorspaceinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
    premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::synchronousTonemapAllRenderPassesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->synchronousTonemapAllRenderPasses(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'results' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayApiRenderImage resultsOut = response.results();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiArrayApiRenderImageConverter::convert(resultsOut, results); ////Convert Called type 5223 =ApiArrayApiRenderImage;////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::synchronousTonemapAllRenderPasses(
            Octane::TonemapBufferType                 bufferType, //// test821 //// 
            bool                                      cryptomatteFalseColor, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType, //// test821 //// 
            Octane::ApiArray<Octane::ApiRenderImage> & results //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::synchronousTonemapAllRenderPasses1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'bufferType' [in] parameter to the request packet.
    octaneapi::TonemapBufferType buffertypeIn;
    buffertypeIn = static_cast<octaneapi::TonemapBufferType>(bufferType);
    request.set_buffertype(buffertypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cryptomatteFalseColor' [in] parameter to the request packet.
    bool cryptomattefalsecolorIn;
    cryptomattefalsecolorIn = cryptomatteFalseColor;////2 bool////
    request.set_cryptomattefalsecolor(cryptomattefalsecolorIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlphaType' [in] parameter to the request packet.
    octaneapi::PremultipliedAlphaType premultipliedalphatypeIn;
    premultipliedalphatypeIn = static_cast<octaneapi::PremultipliedAlphaType>(premultipliedAlphaType);
    request.set_premultipliedalphatype(premultipliedalphatypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::synchronousTonemapAllRenderPasses1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->synchronousTonemapAllRenderPasses1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'results' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayApiRenderImage resultsOut = response.results();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiArrayApiRenderImageConverter::convert(resultsOut, results); ////Convert Called type 5223 =ApiArrayApiRenderImage;////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::freeRenderImages(
            Octane::ApiArray<Octane::ApiRenderImage> & results //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::freeRenderImagesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'results' [in] parameter to the request packet.
    octaneapi::ApiArrayApiRenderImage * resultsIn = new octaneapi::ApiArrayApiRenderImage(); //// results type=ApiArrayApiRenderImage;//// ////721////
    // Using Converter 5, type = ApiArray<Octane::ApiRenderImage> &, protoType = ApiArrayApiRenderImage
    ApiArrayApiRenderImageConverter::convert(results, *resultsIn); //// Convert Called type 1a =ApiArrayApiRenderImage////
    request.set_allocated_results(resultsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::freeRenderImagesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->freeRenderImages(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'results' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayApiRenderImage resultsOut = response.results();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiArrayApiRenderImageConverter::convert(resultsOut, results); ////Convert Called type 5223 =ApiArrayApiRenderImage;////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::getRenderStatistics(
            Octane::RenderResultStatistics &          statistics //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRenderStatisticsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRenderStatisticsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderStatistics(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'statistics' [out] parameter from the gRPC response packet
        octaneapi::RenderResultStatistics statisticsOut = response.statistics();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        RenderResultStatisticsConverter::convert(statisticsOut, statistics); ////Convert Called type 5223 =RenderResultStatistics;////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::getRenderResultStatistics(
            Octane::RenderResultStatistics &          statistics //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRenderResultStatisticsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRenderResultStatisticsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderResultStatistics(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'statistics' [out] parameter from the gRPC response packet
        octaneapi::RenderResultStatistics statisticsOut = response.statistics();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        RenderResultStatisticsConverter::convert(statisticsOut, statistics); ////Convert Called type 5223 =RenderResultStatistics;////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveImage(
            Octane::RenderPassId                      renderPassId, //// test821 //// 
            const char *                              fullPath, //// test821 //// 
            Octane::ImageSaveFormat                   imageSaveFormat, //// test821 //// 
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType, //// test821 //// 
            Octane::ExrCompressionType                exrCompressionType, //// test821 //// 
            float                                     exrCompressionLevel, //// test821 //// 
            bool                                      asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveImageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string(); //// fullPath type=string;//// ////721////
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageSaveFormat' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat imagesaveformatIn;
    imagesaveformatIn = static_cast<octaneapi::ImageSaveFormat>(imageSaveFormat);
    request.set_imagesaveformat(imagesaveformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * colorspaceinfoIn = new octaneapi::ObjectRef();////761////
    colorspaceinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);////5////
    colorspaceinfoIn->set_handle(colorSpaceInfo->getObjectHandle());
    request.set_allocated_colorspaceinfo(colorspaceinfoIn);

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
    exrcompressionlevelIn = exrCompressionLevel;////2 float////
    request.set_exrcompressionlevel(exrcompressionlevelIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveImageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveImage(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveImage(
            Octane::RenderPassId                      renderPassId, //// test821 //// 
            const char *                              fullPath, //// test821 //// 
            Octane::ImageSaveFormat                   imageSaveFormat, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType, //// test821 //// 
            Octane::ExrCompressionType                exrCompressionType, //// test821 //// 
            float                                     exrCompressionLevel, //// test821 //// 
            bool                                      asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveImage1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string(); //// fullPath type=string;//// ////721////
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageSaveFormat' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat imagesaveformatIn;
    imagesaveformatIn = static_cast<octaneapi::ImageSaveFormat>(imageSaveFormat);
    request.set_imagesaveformat(imagesaveformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

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
    exrcompressionlevelIn = exrCompressionLevel;////2 float////
    request.set_exrcompressionlevel(exrcompressionlevelIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveImage1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveImage1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveImage(
            Octane::RenderPassId                      renderPassId, //// test821 //// 
            const char *                              fullPath, //// test821 //// 
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo, //// test821 //// 
            const Octane::ImageExportSettings &       exportSettings, //// test821 //// 
            bool                                      asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveImage2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string(); //// fullPath type=string;//// ////721////
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * colorspaceinfoIn = new octaneapi::ObjectRef();////761////
    colorspaceinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);////5////
    colorspaceinfoIn->set_handle(colorSpaceInfo->getObjectHandle());
    request.set_allocated_colorspaceinfo(colorspaceinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'exportSettings' [in] parameter to the request packet.
    octaneapi::ImageExportSettings * exportsettingsIn = new octaneapi::ImageExportSettings(); //// exportSettings type=ImageExportSettings;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    ImageExportSettingsConverter::convert(exportSettings, *exportsettingsIn); //// Convert Called type 1c =ImageExportSettings ////
    request.set_allocated_exportsettings(exportsettingsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveImage2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveImage2(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveRenderPasses(
            const char *                              outputDirectory, //// test821 //// 
            const Octane::RenderPassExport *          passesToExport, //// test821 //// 
            size_t                                    passesToExportLength, //// test821 //// 
            Octane::ImageSaveFormat                   imageSaveFormat, //// test821 //// 
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType, //// test821 //// 
            Octane::ExrCompressionType                exrCompressionType, //// test821 //// 
            float                                     exrCompressionLevel, //// test821 //// 
            const char *const *                       metadata, //// test821 //// 
            size_t                                    metadataLength, //// test821 //// 
            bool                                      asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveRenderPassesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'outputDirectory' [in] parameter to the request packet.
    std::string * outputdirectoryIn = new std::string(); //// outputDirectory type=string;//// ////721////
    *outputdirectoryIn = checkString(outputDirectory);
    request.set_allocated_outputdirectory(outputdirectoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExport' [in] parameter to the request packet.
    octaneapi::RenderPassExport * passestoexportIn = new octaneapi::RenderPassExport(); //// passesToExport type=RenderPassExport;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    RenderPassExportConverter::convert(*passesToExport, *passestoexportIn); //// Convert Called type 1c =RenderPassExport ////
    request.set_allocated_passestoexport(passestoexportIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExportLength' [in] parameter to the request packet.
    uint32_t passestoexportlengthIn;
    passestoexportlengthIn = static_cast<uint32_t>(passesToExportLength);////2 size_t////
    request.set_passestoexportlength(passestoexportlengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageSaveFormat' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat imagesaveformatIn;
    imagesaveformatIn = static_cast<octaneapi::ImageSaveFormat>(imageSaveFormat);
    request.set_imagesaveformat(imagesaveformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * colorspaceinfoIn = new octaneapi::ObjectRef();////761////
    colorspaceinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);////5////
    colorspaceinfoIn->set_handle(colorSpaceInfo->getObjectHandle());
    request.set_allocated_colorspaceinfo(colorspaceinfoIn);

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
    exrcompressionlevelIn = exrCompressionLevel;////2 float////
    request.set_exrcompressionlevel(exrcompressionlevelIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadata' [in] parameter to the request packet.
    octaneapi::StringArrayT * metadataIn = new octaneapi::StringArrayT(); //// metadata type=StringArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = StringArrayT param.mType = const char *const * ////
    for (size_t h = 0; h < metadataLength; h++)
    {
        metadataIn->add_data(static_cast<std::string>(metadata[h]));
    }
    request.set_allocated_metadata(metadataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadataLength' [in] parameter to the request packet.
    uint32_t metadatalengthIn;
    metadatalengthIn = static_cast<uint32_t>(metadataLength);////2 size_t////
    request.set_metadatalength(metadatalengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveRenderPassesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveRenderPasses(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveRenderPasses(
            const char *                              outputDirectory, //// test821 //// 
            const Octane::RenderPassExport *          passesToExport, //// test821 //// 
            size_t                                    passesToExportLength, //// test821 //// 
            Octane::ImageSaveFormat                   imageSaveFormat, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            Octane::PremultipliedAlphaType            premultipliedAlphaType, //// test821 //// 
            Octane::ExrCompressionType                exrCompressionType, //// test821 //// 
            float                                     exrCompressionLevel, //// test821 //// 
            const char *const *                       metadata, //// test821 //// 
            size_t                                    metadataLength, //// test821 //// 
            bool                                      asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveRenderPasses1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'outputDirectory' [in] parameter to the request packet.
    std::string * outputdirectoryIn = new std::string(); //// outputDirectory type=string;//// ////721////
    *outputdirectoryIn = checkString(outputDirectory);
    request.set_allocated_outputdirectory(outputdirectoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExport' [in] parameter to the request packet.
    octaneapi::RenderPassExport * passestoexportIn = new octaneapi::RenderPassExport(); //// passesToExport type=RenderPassExport;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    RenderPassExportConverter::convert(*passesToExport, *passestoexportIn); //// Convert Called type 1c =RenderPassExport ////
    request.set_allocated_passestoexport(passestoexportIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExportLength' [in] parameter to the request packet.
    uint32_t passestoexportlengthIn;
    passestoexportlengthIn = static_cast<uint32_t>(passesToExportLength);////2 size_t////
    request.set_passestoexportlength(passestoexportlengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageSaveFormat' [in] parameter to the request packet.
    octaneapi::ImageSaveFormat imagesaveformatIn;
    imagesaveformatIn = static_cast<octaneapi::ImageSaveFormat>(imageSaveFormat);
    request.set_imagesaveformat(imagesaveformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

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
    exrcompressionlevelIn = exrCompressionLevel;////2 float////
    request.set_exrcompressionlevel(exrcompressionlevelIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadata' [in] parameter to the request packet.
    octaneapi::StringArrayT * metadataIn = new octaneapi::StringArrayT(); //// metadata type=StringArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = StringArrayT param.mType = const char *const * ////
    for (size_t h = 0; h < metadataLength; h++)
    {
        metadataIn->add_data(static_cast<std::string>(metadata[h]));
    }
    request.set_allocated_metadata(metadataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadataLength' [in] parameter to the request packet.
    uint32_t metadatalengthIn;
    metadatalengthIn = static_cast<uint32_t>(metadataLength);////2 size_t////
    request.set_metadatalength(metadatalengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveRenderPasses1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveRenderPasses1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveRenderPasses(
            const char *                              outputDirectory, //// test821 //// 
            const Octane::RenderPassExport *          passesToExport, //// test821 //// 
            size_t                                    passesToExportLength, //// test821 //// 
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo, //// test821 //// 
            const Octane::ImageExportSettings &       exportSettings, //// test821 //// 
            const char *const *                       metadata, //// test821 //// 
            size_t                                    metadataLength, //// test821 //// 
            bool                                      asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveRenderPasses2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'outputDirectory' [in] parameter to the request packet.
    std::string * outputdirectoryIn = new std::string(); //// outputDirectory type=string;//// ////721////
    *outputdirectoryIn = checkString(outputDirectory);
    request.set_allocated_outputdirectory(outputdirectoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExport' [in] parameter to the request packet.
    octaneapi::RenderPassExport * passestoexportIn = new octaneapi::RenderPassExport(); //// passesToExport type=RenderPassExport;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    RenderPassExportConverter::convert(*passesToExport, *passestoexportIn); //// Convert Called type 1c =RenderPassExport ////
    request.set_allocated_passestoexport(passestoexportIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExportLength' [in] parameter to the request packet.
    uint32_t passestoexportlengthIn;
    passestoexportlengthIn = static_cast<uint32_t>(passesToExportLength);////2 size_t////
    request.set_passestoexportlength(passestoexportlengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * colorspaceinfoIn = new octaneapi::ObjectRef();////761////
    colorspaceinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);////5////
    colorspaceinfoIn->set_handle(colorSpaceInfo->getObjectHandle());
    request.set_allocated_colorspaceinfo(colorspaceinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'exportSettings' [in] parameter to the request packet.
    octaneapi::ImageExportSettings * exportsettingsIn = new octaneapi::ImageExportSettings(); //// exportSettings type=ImageExportSettings;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    ImageExportSettingsConverter::convert(exportSettings, *exportsettingsIn); //// Convert Called type 1c =ImageExportSettings ////
    request.set_allocated_exportsettings(exportsettingsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadata' [in] parameter to the request packet.
    octaneapi::StringArrayT * metadataIn = new octaneapi::StringArrayT(); //// metadata type=StringArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = StringArrayT param.mType = const char *const * ////
    for (size_t h = 0; h < metadataLength; h++)
    {
        metadataIn->add_data(static_cast<std::string>(metadata[h]));
    }
    request.set_allocated_metadata(metadataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadataLength' [in] parameter to the request packet.
    uint32_t metadatalengthIn;
    metadatalengthIn = static_cast<uint32_t>(metadataLength);////2 size_t////
    request.set_metadatalength(metadatalengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveRenderPasses2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveRenderPasses2(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveRenderPassesMultiExr(
            const char *                              fullPath, //// test821 //// 
            const Octane::RenderPassExport *          passesToExport, //// test821 //// 
            const size_t                              passesToExportLength, //// test821 //// 
            bool                                      useHalf, //// test821 //// 
            const ApiOutputColorSpaceInfoProxy *      colorSpaceInfo, //// test821 //// 
            bool                                      premultipliedAlpha, //// test821 //// 
            const Octane::ExrCompressionType          compressionType, //// test821 //// 
            const float                               exrCompressionLevel, //// test821 //// 
            const char *const *                       metadata, //// test821 //// 
            const size_t                              metadataLength, //// test821 //// 
            const bool                                asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveRenderPassesMultiExrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string(); //// fullPath type=string;//// ////721////
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExport' [in] parameter to the request packet.
    octaneapi::RenderPassExport * passestoexportIn = new octaneapi::RenderPassExport(); //// passesToExport type=RenderPassExport;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    RenderPassExportConverter::convert(*passesToExport, *passestoexportIn); //// Convert Called type 1c =RenderPassExport ////
    request.set_allocated_passestoexport(passestoexportIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExportLength' [in] parameter to the request packet.
    uint32_t passestoexportlengthIn;
    passestoexportlengthIn = static_cast<uint32_t>(passesToExportLength);////2 const size_t////
    request.set_passestoexportlength(passestoexportlengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'useHalf' [in] parameter to the request packet.
    bool usehalfIn;
    usehalfIn = useHalf;////2 bool////
    request.set_usehalf(usehalfIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * colorspaceinfoIn = new octaneapi::ObjectRef();////761////
    colorspaceinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);////5////
    colorspaceinfoIn->set_handle(colorSpaceInfo->getObjectHandle());
    request.set_allocated_colorspaceinfo(colorspaceinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlpha' [in] parameter to the request packet.
    bool premultipliedalphaIn;
    premultipliedalphaIn = premultipliedAlpha;////2 bool////
    request.set_premultipliedalpha(premultipliedalphaIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'compressionType' [in] parameter to the request packet.
    octaneapi::ExrCompressionType compressiontypeIn;
    compressiontypeIn = static_cast<octaneapi::ExrCompressionType>(compressionType);
    request.set_compressiontype(compressiontypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'exrCompressionLevel' [in] parameter to the request packet.
    float exrcompressionlevelIn;
    exrcompressionlevelIn = exrCompressionLevel;////2 const float////
    request.set_exrcompressionlevel(exrcompressionlevelIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadata' [in] parameter to the request packet.
    octaneapi::StringArrayT * metadataIn = new octaneapi::StringArrayT(); //// metadata type=StringArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = StringArrayT param.mType = const char *const * ////
    for (size_t h = 0; h < metadataLength; h++)
    {
        metadataIn->add_data(static_cast<std::string>(metadata[h]));
    }
    request.set_allocated_metadata(metadataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadataLength' [in] parameter to the request packet.
    uint32_t metadatalengthIn;
    metadatalengthIn = static_cast<uint32_t>(metadataLength);////2 const size_t////
    request.set_metadatalength(metadatalengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 const bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveRenderPassesMultiExrResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveRenderPassesMultiExr(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveRenderPassesMultiExr(
            const char *                              fullPath, //// test821 //// 
            const Octane::RenderPassExport *          passesToExport, //// test821 //// 
            const size_t                              passesToExportLength, //// test821 //// 
            bool                                      useHalf, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            bool                                      premultipliedAlpha, //// test821 //// 
            const Octane::ExrCompressionType          compressionType, //// test821 //// 
            const float                               exrCompressionLevel, //// test821 //// 
            const char *const *                       metadata, //// test821 //// 
            const size_t                              metadataLength, //// test821 //// 
            const bool                                asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveRenderPassesMultiExr1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string(); //// fullPath type=string;//// ////721////
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExport' [in] parameter to the request packet.
    octaneapi::RenderPassExport * passestoexportIn = new octaneapi::RenderPassExport(); //// passesToExport type=RenderPassExport;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    RenderPassExportConverter::convert(*passesToExport, *passestoexportIn); //// Convert Called type 1c =RenderPassExport ////
    request.set_allocated_passestoexport(passestoexportIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExportLength' [in] parameter to the request packet.
    uint32_t passestoexportlengthIn;
    passestoexportlengthIn = static_cast<uint32_t>(passesToExportLength);////2 const size_t////
    request.set_passestoexportlength(passestoexportlengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'useHalf' [in] parameter to the request packet.
    bool usehalfIn;
    usehalfIn = useHalf;////2 bool////
    request.set_usehalf(usehalfIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'premultipliedAlpha' [in] parameter to the request packet.
    bool premultipliedalphaIn;
    premultipliedalphaIn = premultipliedAlpha;////2 bool////
    request.set_premultipliedalpha(premultipliedalphaIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'compressionType' [in] parameter to the request packet.
    octaneapi::ExrCompressionType compressiontypeIn;
    compressiontypeIn = static_cast<octaneapi::ExrCompressionType>(compressionType);
    request.set_compressiontype(compressiontypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'exrCompressionLevel' [in] parameter to the request packet.
    float exrcompressionlevelIn;
    exrcompressionlevelIn = exrCompressionLevel;////2 const float////
    request.set_exrcompressionlevel(exrcompressionlevelIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadata' [in] parameter to the request packet.
    octaneapi::StringArrayT * metadataIn = new octaneapi::StringArrayT(); //// metadata type=StringArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = StringArrayT param.mType = const char *const * ////
    for (size_t h = 0; h < metadataLength; h++)
    {
        metadataIn->add_data(static_cast<std::string>(metadata[h]));
    }
    request.set_allocated_metadata(metadataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadataLength' [in] parameter to the request packet.
    uint32_t metadatalengthIn;
    metadatalengthIn = static_cast<uint32_t>(metadataLength);////2 const size_t////
    request.set_metadatalength(metadatalengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 const bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveRenderPassesMultiExr1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveRenderPassesMultiExr1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveRenderPassesDeepExr(
            const char *                              fullPath, //// test821 //// 
            const Octane::RenderPassExport *          passesToExport, //// test821 //// 
            const size_t                              passesToExportLength, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            const Octane::ExrCompressionType          compressionType, //// test821 //// 
            const char *const *                       metadata, //// test821 //// 
            const size_t                              metadataLength, //// test821 //// 
            const bool                                asynchronous //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveRenderPassesDeepExrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string(); //// fullPath type=string;//// ////721////
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExport' [in] parameter to the request packet.
    octaneapi::RenderPassExport * passestoexportIn = new octaneapi::RenderPassExport(); //// passesToExport type=RenderPassExport;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    RenderPassExportConverter::convert(*passesToExport, *passestoexportIn); //// Convert Called type 1c =RenderPassExport ////
    request.set_allocated_passestoexport(passestoexportIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'passesToExportLength' [in] parameter to the request packet.
    uint32_t passestoexportlengthIn;
    passestoexportlengthIn = static_cast<uint32_t>(passesToExportLength);////2 const size_t////
    request.set_passestoexportlength(passestoexportlengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'compressionType' [in] parameter to the request packet.
    octaneapi::ExrCompressionType compressiontypeIn;
    compressiontypeIn = static_cast<octaneapi::ExrCompressionType>(compressionType);
    request.set_compressiontype(compressiontypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadata' [in] parameter to the request packet.
    octaneapi::StringArrayT * metadataIn = new octaneapi::StringArrayT(); //// metadata type=StringArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = StringArrayT param.mType = const char *const * ////
    for (size_t h = 0; h < metadataLength; h++)
    {
        metadataIn->add_data(static_cast<std::string>(metadata[h]));
    }
    request.set_allocated_metadata(metadataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'metadataLength' [in] parameter to the request packet.
    uint32_t metadatalengthIn;
    metadatalengthIn = static_cast<uint32_t>(metadataLength);////2 const size_t////
    request.set_metadatalength(metadatalengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'asynchronous' [in] parameter to the request packet.
    bool asynchronousIn;
    asynchronousIn = asynchronous;////2 const bool////
    request.set_asynchronous(asynchronousIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveRenderPassesDeepExrResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveRenderPassesDeepExr(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::deepImageEnabled(
            const ApiNodeProxy *                      renderTargetNode, //// test821 //// 
            uint32_t &                                maxDepthSamples, //// test821 //// 
            uint32_t &                                samplesBeforeCanSave //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deepImageEnabledRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderTargetNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * rendertargetnodeIn = new octaneapi::ObjectRef();////761////
    rendertargetnodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    rendertargetnodeIn->set_handle(renderTargetNode->getObjectHandle());
    request.set_allocated_rendertargetnode(rendertargetnodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deepImageEnabledResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deepImageEnabled(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'maxDepthSamples' [out] parameter from the gRPC response packet
        uint32_t maxDepthSamplesOut = response.maxdepthsamples();
        maxDepthSamples = maxDepthSamplesOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'samplesBeforeCanSave' [out] parameter from the gRPC response packet
        uint32_t samplesBeforeCanSaveOut = response.samplesbeforecansave();
        samplesBeforeCanSave = samplesBeforeCanSaveOut;//// SECOND////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::deepImageEnabled()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deepImageEnabled1Request request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deepImageEnabled1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deepImageEnabled1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::deepPassesEnabled()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deepPassesEnabledRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deepPassesEnabledResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deepPassesEnabled(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::canSaveDeepImage()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::canSaveDeepImageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::canSaveDeepImageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->canSaveDeepImage(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveDeepImage(
            const char *                              fullPath, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            const bool                                saveAsync //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveDeepImageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullPath' [in] parameter to the request packet.
    std::string * fullpathIn = new std::string(); //// fullPath type=string;//// ////721////
    *fullpathIn = checkString(fullPath);
    request.set_allocated_fullpath(fullpathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'saveAsync' [in] parameter to the request packet.
    bool saveasyncIn;
    saveasyncIn = saveAsync;////2 const bool////
    request.set_saveasync(saveasyncIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveDeepImageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveDeepImage(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::saveRenderState(
            const char *const                         renderStateFileName, //// test821 //// 
            const char *const                         customProjectFileName, //// test821 //// 
            const float                               customProjectTime, //// test821 //// 
            const uint32_t                            customVersion, //// test821 //// 
            const void *const                         customData, //// test821 //// 
            const uint32_t                            customDataSize //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveRenderStateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderStateFileName' [in] parameter to the request packet.
    std::string * renderstatefilenameIn = new std::string(); //// renderStateFileName type=string;//// ////721////
    *renderstatefilenameIn = checkString(renderStateFileName);
    request.set_allocated_renderstatefilename(renderstatefilenameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'customProjectFileName' [in] parameter to the request packet.
    std::string * customprojectfilenameIn = new std::string(); //// customProjectFileName type=string;//// ////721////
    *customprojectfilenameIn = checkString(customProjectFileName);
    request.set_allocated_customprojectfilename(customprojectfilenameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'customProjectTime' [in] parameter to the request packet.
    float customprojecttimeIn;
    customprojecttimeIn = customProjectTime;////2 const float////
    request.set_customprojecttime(customprojecttimeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'customVersion' [in] parameter to the request packet.
    uint32_t customversionIn;
    customversionIn = customVersion;////2 const uint32_t////
    request.set_customversion(customversionIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'customData' [in] parameter to the request packet.
    uint64_t customdataIn;
    //// USER DATA TEST ////
    customdataIn = reinterpret_cast<uint64_t>(customData);
    request.set_customdata(customdataIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'customDataSize' [in] parameter to the request packet.
    uint32_t customdatasizeIn;
    customdatasizeIn = customDataSize;////2 const uint32_t////
    request.set_customdatasize(customdatasizeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::saveRenderStateResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveRenderState(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::loadRenderState(
            const char *const                         renderStateFileName, //// test821 //// 
            GRPCLoadRenderStateProjectT              loadProjectCallback, //// test821 //// 
            void *const                               privateCallbackData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::loadRenderStateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderStateFileName' [in] parameter to the request packet.
    std::string * renderstatefilenameIn = new std::string(); //// renderStateFileName type=string;//// ////721////
    *renderstatefilenameIn = checkString(renderStateFileName);
    request.set_allocated_renderstatefilename(renderstatefilenameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'loadProjectCallback' [in] parameter to the request packet.
    octaneapi::LoadRenderStateProjectT * loadprojectcallbackIn = new octaneapi::LoadRenderStateProjectT(); //// loadProjectCallback type=LoadRenderStateProjectT;//// ////721////
    // setup callback function loadProjectCallback
    //int loadProjectCallbackCallbackId = GRPCSettings::getNextCallbackId("GRPCLoadRenderStateProject"); 
    //CallbackStorage::registerGRPCLoadRenderStateProject(loadProjectCallbackCallbackId, loadProjectCallback);
    loadprojectcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //loadprojectcallbackIn->set_callbackid(loadProjectCallbackCallbackId);
    //if(className == "ApiRenderEngine" && method.mName == "loadRenderState") return true;
    request.set_allocated_loadprojectcallback(loadprojectcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'privateCallbackData' [in] parameter to the request packet.
    uint64_t privatecallbackdataIn;
    //// USER DATA TEST ////
    privatecallbackdataIn = reinterpret_cast<uint64_t>(privateCallbackData);
    request.set_privatecallbackdata(privatecallbackdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::loadRenderStateResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->loadRenderState(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCLoadRenderStateProject( response.callbackid(), loadProjectCallback);
        CallbackStorage::registerGRPCLoadRenderStateProject( response.callbackid(), loadProjectCallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::previewMaterial(
            const ApiNodeProxy *                      node, //// test821 //// 
            const unsigned int                        sizeX, //// test821 //// 
            const unsigned int                        sizeY, //// test821 //// 
            const unsigned int                        maxSamples, //// test821 //// 
            const float                               objectSize, //// test821 //// 
            const Octane::PreviewType                 type, //// test821 //// 
            unsigned char *                           buffer //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::previewMaterialRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();////761////
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    nodeIn->set_handle(node->getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sizeX' [in] parameter to the request packet.
    uint32_t sizexIn;
    sizexIn = sizeX;////2 const unsigned int////
    request.set_sizex(sizexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sizeY' [in] parameter to the request packet.
    uint32_t sizeyIn;
    sizeyIn = sizeY;////2 const unsigned int////
    request.set_sizey(sizeyIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'maxSamples' [in] parameter to the request packet.
    uint32_t maxsamplesIn;
    maxsamplesIn = maxSamples;////2 const unsigned int////
    request.set_maxsamples(maxsamplesIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectSize' [in] parameter to the request packet.
    float objectsizeIn;
    objectsizeIn = objectSize;////2 const float////
    request.set_objectsize(objectsizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::PreviewType typeIn;
    typeIn = static_cast<octaneapi::PreviewType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::previewMaterialResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->previewMaterial(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'buffer' [out] parameter from the gRPC response packet
        std::string bufferOut = response.buffer();
        ////special case for previewMaterial////
        ////buffer is preallocated;////
        memcpy(buffer, bufferOut.c_str(), response.buffer().length());
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::previewMaterialHdr(
            const ApiNodeProxy *const                 node, //// test821 //// 
            const uint32_t                            sizeX, //// test821 //// 
            const uint32_t                            sizeY, //// test821 //// 
            const uint32_t                            maxSamples, //// test821 //// 
            const float                               objectSize, //// test821 //// 
            const Octane::PreviewType                 type, //// test821 //// 
            float *const                              buffer, //// test821 //// 
            const bool                                linear //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::previewMaterialHdrRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();////761////
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    nodeIn->set_handle(node->getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sizeX' [in] parameter to the request packet.
    uint32_t sizexIn;
    sizexIn = sizeX;////2 const uint32_t////
    request.set_sizex(sizexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sizeY' [in] parameter to the request packet.
    uint32_t sizeyIn;
    sizeyIn = sizeY;////2 const uint32_t////
    request.set_sizey(sizeyIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'maxSamples' [in] parameter to the request packet.
    uint32_t maxsamplesIn;
    maxsamplesIn = maxSamples;////2 const uint32_t////
    request.set_maxsamples(maxsamplesIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectSize' [in] parameter to the request packet.
    float objectsizeIn;
    objectsizeIn = objectSize;////2 const float////
    request.set_objectsize(objectsizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::PreviewType typeIn;
    typeIn = static_cast<octaneapi::PreviewType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linear' [in] parameter to the request packet.
    bool linearIn;
    linearIn = linear;////2 const bool////
    request.set_linear(linearIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::previewMaterialHdrResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->previewMaterialHdr(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'buffer' [out] parameter from the gRPC response packet
        octaneapi::FloatArrayT bufferOut = response.buffer();
        for (int i = 0; i < bufferOut.data_size(); i++)
        {
            buffer[i] = static_cast<float>(bufferOut.data(i));
        }
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::previewMaterial(
            const ApiNodeProxy *const                 node, //// test821 //// 
            const OctaneVec::uint32_2                 size, //// test821 //// 
            const OctaneVec::float_4                  crop, //// test821 //// 
            const uint32_t                            maxSamples, //// test821 //// 
            const float                               objectSize, //// test821 //// 
            const Octane::PreviewType                 type, //// test821 //// 
            Octane::TonemapBufferType                 bufferType, //// test821 //// 
            Octane::NamedColorSpace                   colorSpace, //// test821 //// 
            void *const                               buffer //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::previewMaterial1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();////761////
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    nodeIn->set_handle(node->getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'size' [in] parameter to the request packet.
    octaneapi::uint32_2 * sizeIn = new octaneapi::uint32_2(); //// size type=uint32_2;//// ////721////
    (*sizeIn).set_x(size.x);
    (*sizeIn).set_y(size.y);
    request.set_allocated_size(sizeIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'crop' [in] parameter to the request packet.
    octaneapi::float_4 * cropIn = new octaneapi::float_4(); //// crop type=float_4;//// ////721////
    (*cropIn).set_x(crop.x);
    (*cropIn).set_y(crop.y);
    (*cropIn).set_z(crop.z);
    (*cropIn).set_w(crop.w);
    request.set_allocated_crop(cropIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'maxSamples' [in] parameter to the request packet.
    uint32_t maxsamplesIn;
    maxsamplesIn = maxSamples;////2 const uint32_t////
    request.set_maxsamples(maxsamplesIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectSize' [in] parameter to the request packet.
    float objectsizeIn;
    objectsizeIn = objectSize;////2 const float////
    request.set_objectsize(objectsizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::PreviewType typeIn;
    typeIn = static_cast<octaneapi::PreviewType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'bufferType' [in] parameter to the request packet.
    octaneapi::TonemapBufferType buffertypeIn;
    buffertypeIn = static_cast<octaneapi::TonemapBufferType>(bufferType);
    request.set_buffertype(buffertypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::previewMaterial1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->previewMaterial1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'buffer' [out] parameter from the gRPC response packet
        octaneapi::Buffer bufferOut = response.buffer();
        ////special case for previewMaterial1////
        ////buffer is preallocated;////
        memcpy(buffer, bufferOut.data().data(), bufferOut.data().size());
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::getMemoryUsage(
            const uint32_t                            deviceIx, //// test821 //// 
            Octane::ApiDeviceMemoryUsage &            memUsage //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getMemoryUsageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'deviceIx' [in] parameter to the request packet.
    uint32_t deviceixIn;
    deviceixIn = deviceIx;////2 const uint32_t////
    request.set_deviceix(deviceixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getMemoryUsageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMemoryUsage(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'memUsage' [out] parameter from the gRPC response packet
        octaneapi::ApiDeviceMemoryUsage memUsageOut = response.memusage();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiDeviceMemoryUsageConverter::convert(memUsageOut, memUsage); ////Convert Called type 5223 =ApiDeviceMemoryUsage;////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::getResourceStatistics(
            const unsigned int                        deviceIx, //// test821 //// 
            const Octane::MemoryLocation              memoryLocation, //// test821 //// 
            Octane::ApiDeviceResourceStatistics &     resourceStats //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getResourceStatisticsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'deviceIx' [in] parameter to the request packet.
    uint32_t deviceixIn;
    deviceixIn = deviceIx;////2 const unsigned int////
    request.set_deviceix(deviceixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'memoryLocation' [in] parameter to the request packet.
    octaneapi::MemoryLocation memorylocationIn;
    memorylocationIn = static_cast<octaneapi::MemoryLocation>(memoryLocation);
    request.set_memorylocation(memorylocationIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getResourceStatisticsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getResourceStatistics(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'resourceStats' [out] parameter from the gRPC response packet
        octaneapi::ApiDeviceResourceStatistics resourceStatsOut = response.resourcestats();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiDeviceResourceStatisticsConverter::convert(resourceStatsOut, resourceStats); ////Convert Called type 5223 =ApiDeviceResourceStatistics;////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::getGeometryStatistics(
            Octane::ApiGeometryStatistics &           stats //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getGeometryStatisticsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getGeometryStatisticsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGeometryStatistics(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'stats' [out] parameter from the gRPC response packet
        octaneapi::ApiGeometryStatistics statsOut = response.stats();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiGeometryStatisticsConverter::convert(statsOut, stats); ////Convert Called type 5223 =ApiGeometryStatistics;////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::getTexturesStatistics(
            Octane::ApiTextureStatistics &            textureStats //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getTexturesStatisticsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getTexturesStatisticsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getTexturesStatistics(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'textureStats' [out] parameter from the gRPC response packet
        octaneapi::ApiTextureStatistics textureStatsOut = response.texturestats();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiTextureStatisticsConverter::convert(textureStatsOut, textureStats); ////Convert Called type 5223 =ApiTextureStatistics;////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::getSceneBounds(
            Octane::float_3 &                         bboxMin, //// test821 //// 
            Octane::float_3 &                         bboxMax //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getSceneBoundsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getSceneBoundsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getSceneBounds(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'bboxMin' [out] parameter from the gRPC response packet
        octaneapi::float_3 bboxMinOut = response.bboxmin();
        bboxMin.x = bboxMinOut.x();
        bboxMin.y = bboxMinOut.y();
        bboxMin.z = bboxMinOut.z();

        /////////////////////////////////////////////////////////////////////
        // Process 'bboxMax' [out] parameter from the gRPC response packet
        octaneapi::float_3 bboxMaxOut = response.bboxmax();
        bboxMax.x = bboxMaxOut.x();
        bboxMax.y = bboxMaxOut.y();
        bboxMax.z = bboxMaxOut.z();
    }
    else
    {
        if (!status.ok())
        {
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


unsigned int ApiRenderEngineProxy::getDeviceCount()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getDeviceCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getDeviceCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getDeviceCount(context.get(), request, &response);

    unsigned int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint32_t resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


int ApiRenderEngineProxy::getDeviceComputeModel(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getDeviceComputeModelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getDeviceComputeModelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getDeviceComputeModel(context.get(), request, &response);

    int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


std::string ApiRenderEngineProxy::getDeviceName(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getDeviceNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getDeviceNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getDeviceName(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::isSupportedDevice(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isSupportedDeviceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isSupportedDeviceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isSupportedDevice(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::deviceCanRender(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deviceCanRenderRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deviceCanRenderResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deviceCanRender(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::deviceCanDenoise(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deviceCanDenoiseRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deviceCanDenoiseResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deviceCanDenoise(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::deviceSupportsHardwareRayTracing(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deviceSupportsHardwareRayTracingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deviceSupportsHardwareRayTracingResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deviceSupportsHardwareRayTracing(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


Octane::ApiDeviceSharedSurfaceInfo ApiRenderEngineProxy::deviceSharedSurfaceInfo(
            uint32_t                                  index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deviceSharedSurfaceInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deviceSharedSurfaceInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deviceSharedSurfaceInfo(context.get(), request, &response);

    Octane::ApiDeviceSharedSurfaceInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiDeviceSharedSurfaceInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiDeviceSharedSurfaceInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiDeviceSharedSurfaceInfo;////
    }
    else
    {
        if (!status.ok())
        {
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


std::vector<OctaneVec::uint32_2> ApiRenderEngineProxy::getAvailablePeerToPeerPairs(
            uint32_t &                                count //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getAvailablePeerToPeerPairsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getAvailablePeerToPeerPairsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAvailablePeerToPeerPairs(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::Uint2ArrayT resultOut = response.result();
        std::vector<OctaneVec::uint32_2> retVal;////9//// 
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            const octaneapi::uint32_2 & item = resultOut.data(i);
            Octane::uint32_2 data;
            data.x = item.x();
            data.y = item.y();
            retVal.push_back(data);
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'count' [out] parameter from the gRPC response packet
        uint32_t countOut = response.count();
        count = countOut;//// SECOND////
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
        return {};
    }
};


bool ApiRenderEngineProxy::setDevicesActivity(
            const uint32_t *const                     renderDeviceIxs, //// test821 //// 
            const uint32_t                            renderDeviceCount, //// test821 //// 
            const uint32_t *const                     deviceIxsUsingPriority, //// test821 //// 
            const uint32_t                            deviceCountUsingPriority, //// test821 //// 
            const int32_t                             imageDeviceIx, //// test821 //// 
            const uint32_t *const                     denoiseDeviceIxs, //// test821 //// 
            const uint32_t                            denoiseDeviceCount, //// test821 //// 
            const Octane::uint32_2 *const             peerToPeerGroups, //// test821 //// 
            const uint32_t                            peerToPeerGroupCount, //// test821 //// 
            const bool                                useMetalRayTracing //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setDevicesActivityRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderDeviceIxs' [in] parameter to the request packet.
    octaneapi::UintArrayT * renderdeviceixsIn = new octaneapi::UintArrayT(); //// renderDeviceIxs type=UintArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = UintArrayT param.mType = const uint32_t *const ////
    for (uint32_t h = 0; h < renderDeviceCount; h++)
    {
        renderdeviceixsIn->add_data(static_cast<uint32_t>(renderDeviceIxs[h]));
    }
    request.set_allocated_renderdeviceixs(renderdeviceixsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderDeviceCount' [in] parameter to the request packet.
    uint32_t renderdevicecountIn;
    renderdevicecountIn = renderDeviceCount;////2 const uint32_t////
    request.set_renderdevicecount(renderdevicecountIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'deviceIxsUsingPriority' [in] parameter to the request packet.
    octaneapi::UintArrayT * deviceixsusingpriorityIn = new octaneapi::UintArrayT(); //// deviceIxsUsingPriority type=UintArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = UintArrayT param.mType = const uint32_t *const ////
    for (uint32_t h = 0; h < deviceCountUsingPriority; h++)
    {
        deviceixsusingpriorityIn->add_data(static_cast<uint32_t>(deviceIxsUsingPriority[h]));
    }
    request.set_allocated_deviceixsusingpriority(deviceixsusingpriorityIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'deviceCountUsingPriority' [in] parameter to the request packet.
    uint32_t devicecountusingpriorityIn;
    devicecountusingpriorityIn = deviceCountUsingPriority;////2 const uint32_t////
    request.set_devicecountusingpriority(devicecountusingpriorityIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'imageDeviceIx' [in] parameter to the request packet.
    int32_t imagedeviceixIn;
    imagedeviceixIn = imageDeviceIx;////2 const int32_t////
    request.set_imagedeviceix(imagedeviceixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'denoiseDeviceIxs' [in] parameter to the request packet.
    octaneapi::UintArrayT * denoisedeviceixsIn = new octaneapi::UintArrayT(); //// denoiseDeviceIxs type=UintArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = UintArrayT param.mType = const uint32_t *const ////
    for (uint32_t h = 0; h < denoiseDeviceCount; h++)
    {
        denoisedeviceixsIn->add_data(static_cast<uint32_t>(denoiseDeviceIxs[h]));
    }
    request.set_allocated_denoisedeviceixs(denoisedeviceixsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'denoiseDeviceCount' [in] parameter to the request packet.
    uint32_t denoisedevicecountIn;
    denoisedevicecountIn = denoiseDeviceCount;////2 const uint32_t////
    request.set_denoisedevicecount(denoisedevicecountIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'peerToPeerGroups' [in] parameter to the request packet.
    octaneapi::Uint2ArrayT * peertopeergroupsIn = new octaneapi::Uint2ArrayT(); //// peerToPeerGroups type=Uint2ArrayT;//// ////721////
    for (uint32_t h = 0; h < peerToPeerGroupCount; h++)
    {
        octaneapi::uint32_2 * item = peertopeergroupsIn->add_data();
        item->set_x(peerToPeerGroups[h].x);
        item->set_y(peerToPeerGroups[h].y);
    }
    request.set_allocated_peertopeergroups(peertopeergroupsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'peerToPeerGroupCount' [in] parameter to the request packet.
    uint32_t peertopeergroupcountIn;
    peertopeergroupcountIn = peerToPeerGroupCount;////2 const uint32_t////
    request.set_peertopeergroupcount(peertopeergroupcountIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'useMetalRayTracing' [in] parameter to the request packet.
    bool usemetalraytracingIn;
    usemetalraytracingIn = useMetalRayTracing;////2 const bool////
    request.set_usemetalraytracing(usemetalraytracingIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::setDevicesActivityResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setDevicesActivity(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::isDeviceUsedForRendering(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isDeviceUsedForRenderingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isDeviceUsedForRenderingResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDeviceUsedForRendering(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::deviceUsesPriority(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deviceUsesPriorityRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deviceUsesPriorityResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deviceUsesPriority(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::deviceUsesHardwareRayTracing(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::deviceUsesHardwareRayTracingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::deviceUsesHardwareRayTracingResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->deviceUsesHardwareRayTracing(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


int32_t ApiRenderEngineProxy::imageDeviceIndex()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::imageDeviceIndexRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::imageDeviceIndexResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->imageDeviceIndex(context.get(), request, &response);

    int32_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::isDeviceUsedForDenoising(
            const uint32_t                            index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isDeviceUsedForDenoisingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = index;////2 const uint32_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isDeviceUsedForDenoisingResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDeviceUsedForDenoising(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


Octane::ApiRenderEngine::RenderPriority ApiRenderEngineProxy::renderPriority()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::renderPriorityRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::renderPriorityResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderPriority(context.get(), request, &response);

    Octane::ApiRenderEngine::RenderPriority retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiRenderEngine_RenderPriority resultOut = response.result();
        retVal = static_cast<Octane::ApiRenderEngine::RenderPriority>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setRenderPriority(
            const Octane::ApiRenderEngine::RenderPriority priority //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setRenderPriorityRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'priority' [in] parameter to the request packet.
    octaneapi::ApiRenderEngine_RenderPriority priorityIn;
    priorityIn = static_cast<octaneapi::ApiRenderEngine_RenderPriority>(priority);
    request.set_priority(priorityIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setRenderPriority(context.get(), request, &response);

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


std::vector<OctaneVec::uint32_2> ApiRenderEngineProxy::currentPeerToPeerGroups(
            uint32_t &                                groupCount //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::currentPeerToPeerGroupsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'groupCount' [in] parameter to the request packet.
    uint32_t groupcountIn;
    groupcountIn = groupCount;////2 uint32_t &////
    request.set_groupcount(groupcountIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::currentPeerToPeerGroupsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->currentPeerToPeerGroups(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::Uint2ArrayT resultOut = response.result();
        std::vector<OctaneVec::uint32_2> retVal;////9//// 
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            const octaneapi::uint32_2 & item = resultOut.data(i);
            Octane::uint32_2 data;
            data.x = item.x();
            data.y = item.y();
            retVal.push_back(data);
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'groupCount' [out] parameter from the gRPC response packet
        uint32_t groupCountOut = response.groupcount();
        groupCount = groupCountOut;//// SECOND////
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
        return {};
    }
};


bool ApiRenderEngineProxy::hardwareRayTracingEnabled()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::hardwareRayTracingEnabledRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::hardwareRayTracingEnabledResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->hardwareRayTracingEnabled(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::openDeviceSettings()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::openDeviceSettingsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->openDeviceSettings(context.get(), request, &response);

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


Octane::RenderDeviceState ApiRenderEngineProxy::renderDeviceState(
            const unsigned int                        deviceIx //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::renderDeviceStateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'deviceIx' [in] parameter to the request packet.
    uint32_t deviceixIn;
    deviceixIn = deviceIx;////2 const unsigned int////
    request.set_deviceix(deviceixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::renderDeviceStateResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderDeviceState(context.get(), request, &response);

    Octane::RenderDeviceState retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::RenderDeviceState resultOut = response.result();
        retVal = static_cast<Octane::RenderDeviceState>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


Octane::RenderError ApiRenderEngineProxy::renderDeviceErrorCode(
            const unsigned int                        deviceIx //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::renderDeviceErrorCodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'deviceIx' [in] parameter to the request packet.
    uint32_t deviceixIn;
    deviceixIn = deviceIx;////2 const unsigned int////
    request.set_deviceix(deviceixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::renderDeviceErrorCodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderDeviceErrorCode(context.get(), request, &response);

    Octane::RenderError retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::RenderError resultOut = response.result();
        retVal = static_cast<Octane::RenderError>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
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


std::string ApiRenderEngineProxy::errorcodeToString(
            const Octane::RenderError                 code //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::errorcodeToStringRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'code' [in] parameter to the request packet.
    octaneapi::RenderError codeIn;
    codeIn = static_cast<octaneapi::RenderError>(code);
    request.set_code(codeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::errorcodeToStringResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->errorcodeToString(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
    }
    else
    {
        if (!status.ok())
        {
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


std::string ApiRenderEngineProxy::renderDeviceErrorMessage(
            const unsigned int                        deviceIx //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::renderDeviceErrorMessageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'deviceIx' [in] parameter to the request packet.
    uint32_t deviceixIn;
    deviceixIn = deviceIx;////2 const unsigned int////
    request.set_deviceix(deviceixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::renderDeviceErrorMessageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderDeviceErrorMessage(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::saveRenderDeviceConfig()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::saveRenderDeviceConfigRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveRenderDeviceConfig(context.get(), request, &response);

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


bool ApiRenderEngineProxy::outOfCoreEnabled()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::outOfCoreEnabledRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::outOfCoreEnabledResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->outOfCoreEnabled(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::enableOutOfCore(
            uint64_t                                  limit //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::enableOutOfCoreRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'limit' [in] parameter to the request packet.
    uint64_t limitIn;
    limitIn = limit;////2 uint64_t////
    request.set_limit(limitIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->enableOutOfCore(context.get(), request, &response);

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


void ApiRenderEngineProxy::disableOutOfCore()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::disableOutOfCoreRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->disableOutOfCore(context.get(), request, &response);

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


void ApiRenderEngineProxy::getOutOfCoreMemoryUsage(
            uint64_t &                                usedOutOfCore, //// test821 //// 
            uint64_t &                                maxOutOfCore, //// test821 //// 
            uint64_t &                                usedByOctane, //// test821 //// 
            uint64_t &                                totalUsed, //// test821 //// 
            uint64_t &                                totalRam //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getOutOfCoreMemoryUsageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getOutOfCoreMemoryUsageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getOutOfCoreMemoryUsage(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'usedOutOfCore' [out] parameter from the gRPC response packet
        uint64_t usedOutOfCoreOut = response.usedoutofcore();
        usedOutOfCore = usedOutOfCoreOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'maxOutOfCore' [out] parameter from the gRPC response packet
        uint64_t maxOutOfCoreOut = response.maxoutofcore();
        maxOutOfCore = maxOutOfCoreOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'usedByOctane' [out] parameter from the gRPC response packet
        uint64_t usedByOctaneOut = response.usedbyoctane();
        usedByOctane = usedByOctaneOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'totalUsed' [out] parameter from the gRPC response packet
        uint64_t totalUsedOut = response.totalused();
        totalUsed = totalUsedOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'totalRam' [out] parameter from the gRPC response packet
        uint64_t totalRamOut = response.totalram();
        totalRam = totalRamOut;//// SECOND////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setGpuHeadroom(
            uint64_t                                  gpuHeadroom //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setGpuHeadroomRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'gpuHeadroom' [in] parameter to the request packet.
    uint64_t gpuheadroomIn;
    gpuheadroomIn = gpuHeadroom;////2 uint64_t////
    request.set_gpuheadroom(gpuheadroomIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setGpuHeadroom(context.get(), request, &response);

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


uint64_t ApiRenderEngineProxy::getGpuHeadroom()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getGpuHeadroomRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getGpuHeadroomResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGpuHeadroom(context.get(), request, &response);

    uint64_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint64_t resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::setCoreLimit(
            const uint32_t                            maxCores //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setCoreLimitRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'maxCores' [in] parameter to the request packet.
    uint32_t maxcoresIn;
    maxcoresIn = maxCores;////2 const uint32_t////
    request.set_maxcores(maxcoresIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setCoreLimit(context.get(), request, &response);

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


void ApiRenderEngineProxy::disableCoreLimit()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::disableCoreLimitRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->disableCoreLimit(context.get(), request, &response);

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


int64_t ApiRenderEngineProxy::registerInputSharedSurface(
            const ApiSharedSurfaceProxy *             surface //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::registerInputSharedSurfaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'surface' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * surfaceIn = new octaneapi::ObjectRef();////761////
    surfaceIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSharedSurface);////5////
    surfaceIn->set_handle(surface->getObjectHandle());
    request.set_allocated_surface(surfaceIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::registerInputSharedSurfaceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->registerInputSharedSurface(context.get(), request, &response);

    int64_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int64_t resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::unregisterInputSharedSurface(
            int64_t                                   id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::unregisterInputSharedSurfaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    int64_t idIn;
    idIn = id;////2 int64_t////
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->unregisterInputSharedSurface(context.get(), request, &response);

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


void ApiRenderEngineProxy::triggerAsyncTonemap(
            bool                                      force //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::triggerAsyncTonemapRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'force' [in] parameter to the request packet.
    bool forceIn;
    forceIn = force;////2 bool////
    request.set_force(forceIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->triggerAsyncTonemap(context.get(), request, &response);

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


void ApiRenderEngineProxy::setSharedSurfaceOutputType(
            Octane::SharedSurfaceType                 type, //// test821 //// 
            bool                                      realTime //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::setSharedSurfaceOutputTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::SharedSurfaceType typeIn;
    typeIn = static_cast<octaneapi::SharedSurfaceType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'realTime' [in] parameter to the request packet.
    bool realtimeIn;
    realtimeIn = realTime;////2 bool////
    request.set_realtime(realtimeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->setSharedSurfaceOutputType(context.get(), request, &response);

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


Octane::SharedSurfaceType ApiRenderEngineProxy::getSharedSurfaceOutputType()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getSharedSurfaceOutputTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getSharedSurfaceOutputTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getSharedSurfaceOutputType(context.get(), request, &response);

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


bool ApiRenderEngineProxy::getRealTime()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getRealTimeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getRealTimeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRealTime(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::pauseRendering()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::pauseRenderingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->pauseRendering(context.get(), request, &response);

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


void ApiRenderEngineProxy::continueRendering()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::continueRenderingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->continueRendering(context.get(), request, &response);

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


bool ApiRenderEngineProxy::isRenderingPaused()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isRenderingPausedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isRenderingPausedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isRenderingPaused(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::restartRendering()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::restartRenderingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->restartRendering(context.get(), request, &response);

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


void ApiRenderEngineProxy::stopRendering()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::stopRenderingRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->stopRendering(context.get(), request, &response);

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


unsigned int ApiRenderEngineProxy::pick(
            const unsigned int                        x, //// test821 //// 
            const unsigned int                        y, //// test821 //// 
            const bool                                filterDuplicateMaterialPins, //// test821 //// 
            GRPCPickIntersection &                   intersections, //// test821 //// 
            const unsigned int                        intersectionsSize //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::pickRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    uint32_t xIn;
    xIn = x;////2 const unsigned int////
    request.set_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    uint32_t yIn;
    yIn = y;////2 const unsigned int////
    request.set_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'filterDuplicateMaterialPins' [in] parameter to the request packet.
    bool filterduplicatematerialpinsIn;
    filterduplicatematerialpinsIn = filterDuplicateMaterialPins;////2 const bool////
    request.set_filterduplicatematerialpins(filterduplicatematerialpinsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'intersectionsSize' [in] parameter to the request packet.
    uint32_t intersectionssizeIn;
    intersectionssizeIn = intersectionsSize;////2 const unsigned int////
    request.set_intersectionssize(intersectionssizeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::pickResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->pick(context.get(), request, &response);

    unsigned int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint32_t resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'intersections' [out] parameter from the gRPC response packet
        octaneapi::ApiRenderEngine_ApiRenderEngine_PickIntersection intersectionsOut = response.intersections();
        //// ::PickIntersection Client TEST 2////
        intersections.mNode;
        intersections.mMaterialPinIx = intersectionsOut.materialpinix();
        intersections.mDepth = intersectionsOut.depth();
        intersections.mPosition = { 
            intersectionsOut.position().x(),
            intersectionsOut.position().y(),
            intersectionsOut.position().z() };
        intersections.mGeometricNormal = { 
            intersectionsOut.geometricnormal().x(),
            intersectionsOut.geometricnormal().y(),
            intersectionsOut.geometricnormal().z() };
        intersections.mSmoothedNormal = { 
            intersectionsOut.smoothednormal().x(),
            intersectionsOut.smoothednormal().y(),
            intersectionsOut.smoothednormal().z() };
        intersections.mPrimitiveType = static_cast<Octane::PrimitiveType>(intersectionsOut.primitivetype());
        if (intersectionsOut.primitivevertices().data_size() == 3) 
        { 
            for(int h = 0; h < 3; h++) 
            { 
                intersections.mPrimitiveVertices[h] = { 
                    intersectionsOut.primitivevertices().data(h).x(),
                    intersectionsOut.primitivevertices().data(h).y(),
                    intersectionsOut.primitivevertices().data(h).z() };
            } 
        } 
        else 
        { 
            assert(false);
        } 
        intersections.mPositionOnPrimitive = { 
            intersectionsOut.positiononprimitive().x(),
            intersectionsOut.positiononprimitive().y(),
            intersectionsOut.positiononprimitive().z() };
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::pickWhitePoint(
            const unsigned int                        x, //// test821 //// 
            const unsigned int                        y, //// test821 //// 
            OctaneVec::float_3 &                      whitePoint //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::pickWhitePointRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    uint32_t xIn;
    xIn = x;////2 const unsigned int////
    request.set_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    uint32_t yIn;
    yIn = y;////2 const unsigned int////
    request.set_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::pickWhitePointResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->pickWhitePoint(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'whitePoint' [out] parameter from the gRPC response packet
        octaneapi::float_3 whitePointOut = response.whitepoint();
        whitePoint.x = whitePointOut.x();
        whitePoint.y = whitePointOut.y();
        whitePoint.z = whitePointOut.z();
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::pickImagerWhitePoint(
            OctaneVec::uint32_2                       position, //// test821 //// 
            OctaneVec::float_3 &                      whitePoint //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::pickImagerWhitePointRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'position' [in] parameter to the request packet.
    octaneapi::uint32_2 * positionIn = new octaneapi::uint32_2(); //// position type=uint32_2;//// ////721////
    (*positionIn).set_x(position.x);
    (*positionIn).set_y(position.y);
    request.set_allocated_position(positionIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::pickImagerWhitePointResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->pickImagerWhitePoint(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'whitePoint' [out] parameter from the gRPC response packet
        octaneapi::float_3 whitePointOut = response.whitepoint();
        whitePoint.x = whitePointOut.x();
        whitePoint.y = whitePointOut.y();
        whitePoint.z = whitePointOut.z();
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::isOutputAovWhitePointPickable(
            uint32_t                                  outputAovIndex, //// test821 //// 
            uint32_t                                  nodeUniqueId //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::isOutputAovWhitePointPickableRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'outputAovIndex' [in] parameter to the request packet.
    uint32_t outputaovindexIn;
    outputaovindexIn = outputAovIndex;////2 uint32_t////
    request.set_outputaovindex(outputaovindexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeUniqueId' [in] parameter to the request packet.
    uint32_t nodeuniqueidIn;
    nodeuniqueidIn = nodeUniqueId;////2 uint32_t////
    request.set_nodeuniqueid(nodeuniqueidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::isOutputAovWhitePointPickableResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->isOutputAovWhitePointPickable(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::pickOutputAovWhitePoint(
            OctaneVec::uint32_2                       position, //// test821 //// 
            uint32_t                                  outputAovIndex, //// test821 //// 
            uint32_t                                  nodeUniqueId, //// test821 //// 
            OctaneVec::float_3 &                      whitePoint //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::pickOutputAovWhitePointRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'position' [in] parameter to the request packet.
    octaneapi::uint32_2 * positionIn = new octaneapi::uint32_2(); //// position type=uint32_2;//// ////721////
    (*positionIn).set_x(position.x);
    (*positionIn).set_y(position.y);
    request.set_allocated_position(positionIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'outputAovIndex' [in] parameter to the request packet.
    uint32_t outputaovindexIn;
    outputaovindexIn = outputAovIndex;////2 uint32_t////
    request.set_outputaovindex(outputaovindexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeUniqueId' [in] parameter to the request packet.
    uint32_t nodeuniqueidIn;
    nodeuniqueidIn = nodeUniqueId;////2 uint32_t////
    request.set_nodeuniqueid(nodeuniqueidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::pickOutputAovWhitePointResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->pickOutputAovWhitePoint(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'whitePoint' [out] parameter from the gRPC response packet
        octaneapi::float_3 whitePointOut = response.whitepoint();
        whitePoint.x = whitePointOut.x();
        whitePoint.y = whitePointOut.y();
        whitePoint.z = whitePointOut.z();
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::pickCryptomatteMatte(
            unsigned int                              x, //// test821 //// 
            unsigned int                              y, //// test821 //// 
            Octane::RenderPassId                      pass, //// test821 //// 
            std::string &                             matteName, //// test821 //// 
            unsigned int &                            matteNameBufferSize //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::pickCryptomatteMatteRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    uint32_t xIn;
    xIn = x;////2 unsigned int////
    request.set_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    uint32_t yIn;
    yIn = y;////2 unsigned int////
    request.set_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pass' [in] parameter to the request packet.
    octaneapi::RenderPassId passIn;
    passIn = static_cast<octaneapi::RenderPassId>(pass);
    request.set_pass(passIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::pickCryptomatteMatteResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->pickCryptomatteMatte(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'matteName' [out] parameter from the gRPC response packet
        std::string matteNameOut = response.mattename();
        // param.mType = char *
        matteName =  matteNameOut;////ex string mgr////

        /////////////////////////////////////////////////////////////////////
        // Process 'matteNameBufferSize' [out] parameter from the gRPC response packet
        uint32_t matteNameBufferSizeOut = response.mattenamebuffersize();
        matteNameBufferSize = matteNameBufferSizeOut;//// SECOND////
    }
    else
    {
        if (!status.ok())
        {
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


bool ApiRenderEngineProxy::modifyCryptomatteMatteSelection(
            const char *                              inputText, //// test821 //// 
            const char *                              matteName, //// test821 //// 
            bool                                      add, //// test821 //// 
            std::string &                             outputText, //// test821 //// 
            unsigned int &                            outputTextBufferSize //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::modifyCryptomatteMatteSelectionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'inputText' [in] parameter to the request packet.
    std::string * inputtextIn = new std::string(); //// inputText type=string;//// ////721////
    *inputtextIn = checkString(inputText);
    request.set_allocated_inputtext(inputtextIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'matteName' [in] parameter to the request packet.
    std::string * mattenameIn = new std::string(); //// matteName type=string;//// ////721////
    *mattenameIn = checkString(matteName);
    request.set_allocated_mattename(mattenameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'add' [in] parameter to the request packet.
    bool addIn;
    addIn = add;////2 bool////
    request.set_add(addIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::modifyCryptomatteMatteSelectionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->modifyCryptomatteMatteSelection(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'outputText' [out] parameter from the gRPC response packet
        std::string outputTextOut = response.outputtext();
        // param.mType = char *
        outputText =  outputTextOut;////ex string mgr////

        /////////////////////////////////////////////////////////////////////
        // Process 'outputTextBufferSize' [out] parameter from the gRPC response packet
        uint32_t outputTextBufferSizeOut = response.outputtextbuffersize();
        outputTextBufferSize = outputTextBufferSizeOut;//// SECOND////
    }
    else
    {
        if (!status.ok())
        {
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


std::string ApiRenderEngineProxy::toString(
            const Octane::ApiRenderEngine::RenderPriority priority //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::toStringRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'priority' [in] parameter to the request packet.
    octaneapi::ApiRenderEngine_RenderPriority priorityIn;
    priorityIn = static_cast<octaneapi::ApiRenderEngine_RenderPriority>(priority);
    request.set_priority(priorityIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::toStringResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->toString(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
    }
    else
    {
        if (!status.ok())
        {
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


void ApiRenderEngineProxy::getDevicePciIds(
            const unsigned int                        deviceIx, //// test821 //// 
            uint64_t &                                pciBusId, //// test821 //// 
            uint64_t &                                pciDeviceId //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRenderEngine::getDevicePciIdsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'deviceIx' [in] parameter to the request packet.
    uint32_t deviceixIn;
    deviceixIn = deviceIx;////2 const unsigned int////
    request.set_deviceix(deviceixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRenderEngine::getDevicePciIdsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRenderEngineService::Stub> stub = 
        octaneapi::ApiRenderEngineService::NewStub(getGRPCSettings().getChannel());
    status = stub->getDevicePciIds(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'pciBusId' [out] parameter from the gRPC response packet
        uint64_t pciBusIdOut = response.pcibusid();
        pciBusId = pciBusIdOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'pciDeviceId' [out] parameter from the gRPC response packet
        uint64_t pciDeviceIdOut = response.pcideviceid();
        pciDeviceId = pciDeviceIdOut;//// SECOND////
    }
    else
    {
        if (!status.ok())
        {
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


