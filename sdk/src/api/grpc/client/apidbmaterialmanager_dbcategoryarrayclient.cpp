// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apidbmaterialmanager_dbcategoryarrayclient.h"
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
#include "apidbmaterialmanager_dbcategoryclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiDBMaterialManagerProxy_DBCategoryArray::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiDBMaterialManagerProxy_DBCategoryArray::init(
            const size_t                              size
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBCategoryArray::initRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_DBCategoryArray);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'size' [in] parameter to the request packet.
    uint32_t sizeIn;
    sizeIn = static_cast<uint32_t>(size);
    request.set_size(sizeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManager_DBCategoryArrayService::Stub> stub =
        octaneapi::ApiDBMaterialManager_DBCategoryArrayService::NewStub(getGRPCSettings().getChannel());
    status = stub->init(context.get(), request, &response);

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


void ApiDBMaterialManagerProxy_DBCategoryArray::free()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBCategoryArray::freeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_DBCategoryArray);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManager_DBCategoryArrayService::Stub> stub =
        octaneapi::ApiDBMaterialManager_DBCategoryArrayService::NewStub(getGRPCSettings().getChannel());
    status = stub->free(context.get(), request, &response);

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


std::vector<Octane::ApiDBMaterialManager::DBCategory> ApiDBMaterialManagerProxy_DBCategoryArray::getCategory()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBCategoryArray::getCategoryRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_DBCategoryArray);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBCategoryArray::getCategoryResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManager_DBCategoryArrayService::Stub> stub =
        octaneapi::ApiDBMaterialManager_DBCategoryArrayService::NewStub(getGRPCSettings().getChannel());
    status = stub->getCategory(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiDBMaterialManager_CategoryArray resultOut = response.result();
        std::vector<Octane::ApiDBMaterialManager::DBCategory> retVal;
        retVal.reserve(resultOut.categories_size());
        for (int i = 0; i < resultOut.categories_size(); i++)
        {
            Octane::ApiDBMaterialManager::DBCategory category;
            category.mID = resultOut.categories(i).id();
            strncpy(category.mName, resultOut.categories(i).name().c_str(), sizeof(category.mName) - 1);
            category.mName[sizeof(category.mName) - 1] = '\0';
            category.mParentID = resultOut.categories(i).parentid();
            category.mTypeID = static_cast<Octane::OctaneLiveCategory>(resultOut.categories(i).typeid_());
            retVal.push_back(category);
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


size_t ApiDBMaterialManagerProxy_DBCategoryArray::getCount() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBCategoryArray::getCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_DBCategoryArray);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiDBMaterialManager::ApiDBMaterialManager_DBCategoryArray::getCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDBMaterialManager_DBCategoryArrayService::Stub> stub =
        octaneapi::ApiDBMaterialManager_DBCategoryArrayService::NewStub(getGRPCSettings().getChannel());
    status = stub->getCount(context.get(), request, &response);

    size_t retVal = 0;
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


} //end of namespace
