// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apidbmaterialmanagerclient.h"
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
#include "apidbmaterialmanager.grpc.pb.h"
#include "apinodeclient.h"
#include "apinodegraphclient.h"
#include "apidbmaterialmanager_dbcategoryarrayclient.h"
#include "apidbmaterialmanager_dbmaterialarrayclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiDBMaterialManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiDBMaterialManagerProxy::getCategories(
            ApiDBMaterialManagerProxy_DBCategoryArray &list
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::getCategoriesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::getCategoriesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManagerService::Stub> stub =
        octaneapi::ApiDBMaterialManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->getCategories(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'list' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef listOut = response.list();
        list.attachObjectHandle(listOut.handle());
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


bool ApiDBMaterialManagerProxy::getMaterials(
            const int                                 categoryId,
            ApiDBMaterialManagerProxy_DBMaterialArray &list
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::getMaterialsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'categoryId' [in] parameter to the request packet.
    int32_t categoryidIn;
    categoryidIn = categoryId;
    request.set_categoryid(categoryidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::getMaterialsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManagerService::Stub> stub =
        octaneapi::ApiDBMaterialManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMaterials(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'list' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef listOut = response.list();
        list.attachObjectHandle(listOut.handle());
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


std::unique_ptr<uint8_t> ApiDBMaterialManagerProxy::getMaterialPreview(
            const int                                 materialId,
            const uint32_t                            requestedSize,
            Octane::LiveDbThumbnailView               view,
            Octane::uint32_2 &                        size
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::getMaterialPreviewRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'materialId' [in] parameter to the request packet.
    int32_t materialidIn;
    materialidIn = materialId;
    request.set_materialid(materialidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'requestedSize' [in] parameter to the request packet.
    uint32_t requestedsizeIn;
    requestedsizeIn = requestedSize;
    request.set_requestedsize(requestedsizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'view' [in] parameter to the request packet.
    octaneapi::LiveDbThumbnailView viewIn;
        viewIn = static_cast<octaneapi::LiveDbThumbnailView>(view);
    request.set_view(viewIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::getMaterialPreviewResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManagerService::Stub> stub =
        octaneapi::ApiDBMaterialManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMaterialPreview(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::Buffer resultOut = response.result();
        auto retVal = std::make_unique<uint8_t>(resultOut.data().size());
        memcpy(retVal.get(), resultOut.data().data(), resultOut.data().size());

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        octaneapi::uint32_2 sizeOut = response.size();
        size.x = sizeOut.x();
        size.y = sizeOut.y();
        return retVal;
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
       return nullptr;
    }
};


bool ApiDBMaterialManagerProxy::downloadMaterial(
            const int                                 materialId,
            ApiNodeGraphProxy &                       destinationGraph,
            ApiNodeProxy **                           outputNode
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::downloadMaterialRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'materialId' [in] parameter to the request packet.
    int32_t materialidIn;
    materialidIn = materialId;
    request.set_materialid(materialidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'destinationGraph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * destinationgraphIn = new octaneapi::ObjectRef();
    destinationgraphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);
    destinationgraphIn->set_handle(destinationGraph.getObjectHandle());
    request.set_allocated_destinationgraph(destinationgraphIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::downloadMaterialResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManagerService::Stub> stub =
        octaneapi::ApiDBMaterialManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->downloadMaterial(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'outputNode' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef outputNodeOut = response.outputnode();
        (*outputNode)->attachObjectHandle(outputNodeOut.handle());
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


ApiNodeProxy ApiDBMaterialManagerProxy::downloadMaterial(
            const int                                 materialId,
            const char *                              assetPath
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::downloadMaterial1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'materialId' [in] parameter to the request packet.
    int32_t materialidIn;
    materialidIn = materialId;
    request.set_materialid(materialidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetPath' [in] parameter to the request packet.
    std::string * assetpathIn = new std::string();
    *assetpathIn = checkString(assetPath);
    request.set_allocated_assetpath(assetpathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::downloadMaterial1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManagerService::Stub> stub =
        octaneapi::ApiDBMaterialManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->downloadMaterial1(context.get(), request, &response);

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
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
        ApiNodeProxy retVal;
        return retVal;
    }
};


} //end of namespace
