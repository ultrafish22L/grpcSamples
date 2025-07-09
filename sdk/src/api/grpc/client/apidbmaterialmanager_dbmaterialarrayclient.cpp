// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apidbmaterialmanager_dbmaterialarrayclient.h"
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
#include "apidbmaterialmanager_dbmaterialclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiDBMaterialManagerProxy_DBMaterialArray::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiDBMaterialManagerProxy_DBMaterialArray::init(
            const size_t                              size //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBMaterialArray::initRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_DBMaterialArray);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'size' [in] parameter to the request packet.
    uint32_t sizeIn;
    sizeIn = static_cast<uint32_t>(size);////2 const size_t////
    request.set_size(sizeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManager_DBMaterialArrayService::Stub> stub = 
        octaneapi::ApiDBMaterialManager_DBMaterialArrayService::NewStub(getGRPCSettings().getChannel());
    status = stub->init1(context.get(), request, &response);

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


void ApiDBMaterialManagerProxy_DBMaterialArray::free()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBMaterialArray::freeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_DBMaterialArray);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManager_DBMaterialArrayService::Stub> stub = 
        octaneapi::ApiDBMaterialManager_DBMaterialArrayService::NewStub(getGRPCSettings().getChannel());
    status = stub->free1(context.get(), request, &response);

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


std::vector<Octane::ApiDBMaterialManager::DBMaterial> ApiDBMaterialManagerProxy_DBMaterialArray::getMaterial()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBMaterialArray::getMaterialRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_DBMaterialArray);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBMaterialArray::getMaterialResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManager_DBMaterialArrayService::Stub> stub = 
        octaneapi::ApiDBMaterialManager_DBMaterialArrayService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMaterial(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiDBMaterialManager_MaterialArray resultOut = response.result();
        //// special case for MaterialArray ////
        //// param.mProtoCppType = MaterialArray param.mType = Octane::ApiDBMaterialManager::DBMaterial * ////
        std::vector<Octane::ApiDBMaterialManager::DBMaterial> retVal;
        retVal.reserve(resultOut.materials_size());////215////
        for (int i = 0; i < resultOut.materials_size(); i++)
        {
            Octane::ApiDBMaterialManager::DBMaterial material;
            material.mID = resultOut.materials(i).id();
            material.mCategoryID = resultOut.materials(i).categoryid();
            strncpy(material.mName, resultOut.materials(i).name().c_str(), sizeof(material.mName) - 1);
            material.mName[sizeof(material.mName) - 1] = '\0';
            strncpy(material.mCopyright, resultOut.materials(i).copyright().c_str(), sizeof(material.mCopyright) - 1);
            material.mCopyright[sizeof(material.mCopyright) - 1] = '\0';
            strncpy(material.mNickname, resultOut.materials(i).nickname().c_str(), sizeof(material.mNickname) - 1);
            material.mNickname[sizeof(material.mNickname) - 1] = '\0';
            retVal.push_back(material);
        }
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


size_t ApiDBMaterialManagerProxy_DBMaterialArray::getCount() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBMaterialArray::getCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_DBMaterialArray);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBMaterialArray::getCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManager_DBMaterialArrayService::Stub> stub = 
        octaneapi::ApiDBMaterialManager_DBMaterialArrayService::NewStub(getGRPCSettings().getChannel());
    status = stub->getCount1(context.get(), request, &response);

    size_t retVal = 0;
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


