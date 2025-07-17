// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apipackageclient.h"
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
#include "apipackage.grpc.pb.h"
#include "apifilenameclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiPackageProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiPackageProxy::freeArray(
            Octane::StringArrayT &                    stringArray
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiPackage::freeArrayRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'stringArray' [in] parameter to the request packet.
    octaneapi::StringArrayT * stringarrayIn = new octaneapi::StringArrayT();
    for (int h = 0; h < stringArray.mSize; h++)
    {
        stringarrayIn->add_data(stringArray.mData[h]);
    }
    request.set_allocated_stringarray(stringarrayIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiPackageService::Stub> stub =
        octaneapi::ApiPackageService::NewStub(getGRPCSettings().getChannel());
    status = stub->freeArray(context.get(), request, &response);

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


ApiPackageProxy ApiPackageProxy::open(
            const char *const                         packagePath
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiPackage::openRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'packagePath' [in] parameter to the request packet.
    std::string * packagepathIn = new std::string();
    *packagepathIn = checkString(packagePath);
    request.set_allocated_packagepath(packagepathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiPackage::openResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiPackageService::Stub> stub =
        octaneapi::ApiPackageService::NewStub(getGRPCSettings().getChannel());
    status = stub->open(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiPackageProxy retVal;
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
        ApiPackageProxy retVal;
        return retVal;
    }
};


void ApiPackageProxy::close()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiPackage::closeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiPackage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiPackageService::Stub> stub =
        octaneapi::ApiPackageService::NewStub(getGRPCSettings().getChannel());
    status = stub->close(context.get(), request, &response);

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


void ApiPackageProxy::getFileList(
            std::vector<std::string> &                fileList,
            const char *const                         regExpr
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiPackage::getFileListRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiPackage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'regExpr' [in] parameter to the request packet.
    std::string * regexprIn = new std::string();
    *regexprIn = checkString(regExpr);
    request.set_allocated_regexpr(regexprIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiPackage::getFileListResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiPackageService::Stub> stub =
        octaneapi::ApiPackageService::NewStub(getGRPCSettings().getChannel());
    status = stub->getFileList(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'fileList' [out] parameter from the gRPC response packet
        octaneapi::StringArrayT fileListOut = response.filelist();
        fileList.reserve(fileListOut.data_size());
        for (int i = 0; i < fileListOut.data_size(); i++)
        {
            fileList.push_back(fileListOut.data(i));
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


bool ApiPackageProxy::fileExists(
            const char *const                         path
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiPackage::fileExistsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiPackage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    std::string * pathIn = new std::string();
    *pathIn = checkString(path);
    request.set_allocated_path(pathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiPackage::fileExistsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiPackageService::Stub> stub =
        octaneapi::ApiPackageService::NewStub(getGRPCSettings().getChannel());
    status = stub->fileExists(context.get(), request, &response);

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


bool ApiPackageProxy::fileExists(
            const ApiFileNameProxy &                  path
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiPackage::fileExists1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiPackage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * pathIn = new octaneapi::ObjectRef();
    pathIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiFileName);
    pathIn->set_handle(path.getObjectHandle());
    request.set_allocated_path(pathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiPackage::fileExists1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiPackageService::Stub> stub =
        octaneapi::ApiPackageService::NewStub(getGRPCSettings().getChannel());
    status = stub->fileExists1(context.get(), request, &response);

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


bool ApiPackageProxy::readFile(
            const char *const                         path,
            std::vector<uint8_t> &                    data
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiPackage::readFileRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiPackage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    std::string * pathIn = new std::string();
    *pathIn = checkString(path);
    request.set_allocated_path(pathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiPackage::readFileResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiPackageService::Stub> stub =
        octaneapi::ApiPackageService::NewStub(getGRPCSettings().getChannel());
    status = stub->readFile(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'data' [out] parameter from the gRPC response packet
        octaneapi::ByteArrayT dataOut = response.data();
        size_t len = dataOut.data().size();
        data.resize(len);
        std::memcpy(data.data(), dataOut.data().data(), len);
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


bool ApiPackageProxy::readFile(
            const ApiFileNameProxy &                  path,
            std::vector<uint8_t> &                    data
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiPackage::readFile1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiPackage);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * pathIn = new octaneapi::ObjectRef();
    pathIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiFileName);
    pathIn->set_handle(path.getObjectHandle());
    request.set_allocated_path(pathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiPackage::readFile1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiPackageService::Stub> stub =
        octaneapi::ApiPackageService::NewStub(getGRPCSettings().getChannel());
    status = stub->readFile1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'data' [out] parameter from the gRPC response packet
        octaneapi::ByteArrayT dataOut = response.data();
        size_t len = dataOut.data().size();
        data.resize(len);
        std::memcpy(data.data(), dataOut.data().data(), len);
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


