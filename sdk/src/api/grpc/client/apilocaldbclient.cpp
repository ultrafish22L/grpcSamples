// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apilocaldbclient.h"
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
#include "apilocaldb.grpc.pb.h"
#include "apilocaldbclient.h"
#include "apilocaldb_packageclient.h"
#include "apilocaldb_categoryclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiLocalDBProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiLocalDBProxy::isSupported()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLocalDB::isSupportedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLocalDB::isSupportedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLocalDBService::Stub> stub = 
        octaneapi::ApiLocalDBService::NewStub(getGRPCSettings().getChannel());
    status = stub->isSupported(context.get(), request, &response);

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


ApiLocalDBProxy_Category ApiLocalDBProxy::root()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLocalDB::rootRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLocalDB::rootResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLocalDBService::Stub> stub = 
        octaneapi::ApiLocalDBService::NewStub(getGRPCSettings().getChannel());
    status = stub->root(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiLocalDBProxy_Category retVal;
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
        ApiLocalDBProxy_Category retVal;////714////
        return retVal;
    }
};


bool ApiLocalDBProxy::setRootDirectory(
            const char *                              newPath, //// test821 //// 
            bool                                      moveFiles //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLocalDB::setRootDirectoryRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'newPath' [in] parameter to the request packet.
    std::string * newpathIn = new std::string(); //// newPath type=string;//// ////721////
    *newpathIn = checkString(newPath);
    request.set_allocated_newpath(newpathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'moveFiles' [in] parameter to the request packet.
    bool movefilesIn;
    movefilesIn = moveFiles;////2 bool////
    request.set_movefiles(movefilesIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLocalDB::setRootDirectoryResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLocalDBService::Stub> stub = 
        octaneapi::ApiLocalDBService::NewStub(getGRPCSettings().getChannel());
    status = stub->setRootDirectory(context.get(), request, &response);

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


void ApiLocalDBProxy::addObserver(
            void *                                    opaqueData, //// test821 //// 
            Octane::ApiLocalDB::ObserverCallback *    callback //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLocalDB::addObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'opaqueData' [in] parameter to the request packet.
    uint64_t opaquedataIn;
    //// USER DATA TEST ////
    opaquedataIn = reinterpret_cast<uint64_t>(opaqueData);
    request.set_opaquedata(opaquedataIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::ObserverCallback * callbackIn = new octaneapi::ObserverCallback(); //// callback type=ObserverCallback;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("ObserverCallback"); 
    //CallbackStorage::registerObserverCallback(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiLocalDB" && method.mName == "addObserver") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLocalDB::addObserverResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLocalDBService::Stub> stub = 
        octaneapi::ApiLocalDBService::NewStub(getGRPCSettings().getChannel());
    status = stub->addObserver(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerObserverCallback( response.callbackid(), callback);
        CallbackStorage::registerObserverCallback( response.callbackid(), callback);
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


void ApiLocalDBProxy::removeObserver(
            void *                                    opaqueData, //// test821 //// 
            Octane::ApiLocalDB::ObserverCallback *    callback //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLocalDB::removeObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'opaqueData' [in] parameter to the request packet.
    uint64_t opaquedataIn;
    //// USER DATA TEST ////
    opaquedataIn = reinterpret_cast<uint64_t>(opaqueData);
    request.set_opaquedata(opaquedataIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::ObserverCallback * callbackIn = new octaneapi::ObserverCallback(); //// callback type=ObserverCallback;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("ObserverCallback"); 
    //CallbackStorage::registerObserverCallback(callbackCallbackId, callback);
    int callbackCallbackId = CallbackStorage::unregisterObserverCallback(callback);
    callbackIn->set_callbackid(callbackCallbackId);
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLocalDB::removeObserverResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLocalDBService::Stub> stub = 
        octaneapi::ApiLocalDBService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeObserver(context.get(), request, &response);

    if (status.ok())
    {
        // free callbackId
        // GRPCSettings::releaseCallbackId("ObserverCallback", response.callbackid());
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


