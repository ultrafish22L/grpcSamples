// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apicachesclient.h"
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
#include "apicaches.grpc.pb.h"
#include "apinodeclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiCachesProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


uint64_t ApiCachesProxy::getMeshletCacheSize()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::getMeshletCacheSizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::getMeshletCacheSizeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMeshletCacheSize(context.get(), request, &response);

    uint64_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint64_t resultOut = response.result();
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


uint64_t ApiCachesProxy::getMeshletCacheUsedSize()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::getMeshletCacheUsedSizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::getMeshletCacheUsedSizeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMeshletCacheUsedSize(context.get(), request, &response);

    uint64_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint64_t resultOut = response.result();
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


void ApiCachesProxy::clearMeshletCache()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::clearMeshletCacheRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearMeshletCache(context.get(), request, &response);

    if (status.ok())
    {
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
};


bool ApiCachesProxy::hasMeshletCacheFile(
            ApiNodeProxy *                            meshNode
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::hasMeshletCacheFileRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'meshNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * meshnodeIn = new octaneapi::ObjectRef();
    meshnodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    meshnodeIn->set_handle(meshNode->getObjectHandle());
    request.set_allocated_meshnode(meshnodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::hasMeshletCacheFileResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->hasMeshletCacheFile(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'meshNode' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef meshNodeOut = response.meshnode();
        meshNode->attachObjectHandle(meshNodeOut.handle());
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


Octane::CacheStatus ApiCachesProxy::checkMeshletBuildStatus(
            ApiNodeProxy *                            meshNode
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::checkMeshletBuildStatusRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'meshNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * meshnodeIn = new octaneapi::ObjectRef();
    meshnodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    meshnodeIn->set_handle(meshNode->getObjectHandle());
    request.set_allocated_meshnode(meshnodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::checkMeshletBuildStatusResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->checkMeshletBuildStatus(context.get(), request, &response);

    Octane::CacheStatus retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::CacheStatus resultOut = response.result();
        retVal = static_cast<Octane::CacheStatus>(resultOut);

        /////////////////////////////////////////////////////////////////////
        // Process 'meshNode' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef meshNodeOut = response.meshnode();
        meshNode->attachObjectHandle(meshNodeOut.handle());
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


bool ApiCachesProxy::clearMeshletCacheFileForNode(
            ApiNodeProxy *                            meshNode
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::clearMeshletCacheFileForNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'meshNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * meshnodeIn = new octaneapi::ObjectRef();
    meshnodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    meshnodeIn->set_handle(meshNode->getObjectHandle());
    request.set_allocated_meshnode(meshnodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::clearMeshletCacheFileForNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearMeshletCacheFileForNode(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'meshNode' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef meshNodeOut = response.meshnode();
        meshNode->attachObjectHandle(meshNodeOut.handle());
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


uint64_t ApiCachesProxy::getVirtualTextureCacheSize()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::getVirtualTextureCacheSizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::getVirtualTextureCacheSizeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->getVirtualTextureCacheSize(context.get(), request, &response);

    uint64_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint64_t resultOut = response.result();
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


uint64_t ApiCachesProxy::getVirtualTextureCacheUsedSize()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::getVirtualTextureCacheUsedSizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::getVirtualTextureCacheUsedSizeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->getVirtualTextureCacheUsedSize(context.get(), request, &response);

    uint64_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint64_t resultOut = response.result();
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


void ApiCachesProxy::pruneVirtualTextureCache(
            uint64_t                                  maximumSize
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::pruneVirtualTextureCacheRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'maximumSize' [in] parameter to the request packet.
    uint64_t maximumsizeIn;
    maximumsizeIn = maximumSize;
    request.set_maximumsize(maximumsizeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->pruneVirtualTextureCache(context.get(), request, &response);

    if (status.ok())
    {
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
};


Octane::CacheStatus ApiCachesProxy::checkVirtualTextureStatus(
            ApiNodeProxy *                            node
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::checkVirtualTextureStatusRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    nodeIn->set_handle(node->getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::checkVirtualTextureStatusResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->checkVirtualTextureStatus(context.get(), request, &response);

    Octane::CacheStatus retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::CacheStatus resultOut = response.result();
        retVal = static_cast<Octane::CacheStatus>(resultOut);

        /////////////////////////////////////////////////////////////////////
        // Process 'node' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef nodeOut = response.node();
        node->attachObjectHandle(nodeOut.handle());
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


bool ApiCachesProxy::clearVirtualTextureCacheForNode(
            ApiNodeProxy *                            node
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCaches::clearVirtualTextureCacheForNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    nodeIn->set_handle(node->getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCaches::clearVirtualTextureCacheForNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCachesService::Stub> stub =
        octaneapi::ApiCachesService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearVirtualTextureCacheForNode(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'node' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef nodeOut = response.node();
        node->attachObjectHandle(nodeOut.handle());
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
