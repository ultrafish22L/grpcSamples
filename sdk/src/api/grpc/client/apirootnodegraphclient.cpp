// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apirootnodegraphclient.h"
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
#include "apinodesystem_1.grpc.pb.h"
#include "apinodesystem_2.grpc.pb.h"
#include "apinodesystem_3.grpc.pb.h"
#include "apinodesystem_4.grpc.pb.h"
#include "apinodesystem_5.grpc.pb.h"
#include "apinodesystem_6.grpc.pb.h"
#include "apinodesystem_7.grpc.pb.h"
#include "apinodesystem_8.grpc.pb.h"
#include "apinodeclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiRootNodeGraphProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiRootNodeGraphProxy ApiRootNodeGraphProxy::create(
            const Octane::VersionT                    version //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'version' [in] parameter to the request packet.
    uint32_t versionIn;
    versionIn = version;////2 const Octane::VersionT////
    request.set_version(versionIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->create2(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiRootNodeGraphProxy retVal;
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
        ApiRootNodeGraphProxy retVal;////714////
        return retVal;
    }
};


void ApiRootNodeGraphProxy::init(
            const Octane::VersionT                    version //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::initRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'version' [in] parameter to the request packet.
    uint32_t versionIn;
    versionIn = version;////2 const Octane::VersionT////
    request.set_version(versionIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->init2(context.get(), request, &response);

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


void ApiRootNodeGraphProxy::convertAndEvaluate()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::convertAndEvaluateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->convertAndEvaluate(context.get(), request, &response);

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


Octane::TimeSpanT ApiRootNodeGraphProxy::animationTimeSpan() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::animationTimeSpanRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::animationTimeSpanResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->animationTimeSpan(context.get(), request, &response);

    Octane::TimeSpanT retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::TimeSpanT resultOut = response.result();
        //// Octane::TimeSpanT TEST//// 
        retVal.begin = resultOut.begin().value();
        retVal.end   = resultOut.end().value();
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


void ApiRootNodeGraphProxy::updateTime(
            const Octane::TimeT                       time //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::updateTimeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'time' [in] parameter to the request packet.
    octaneapi::TimeT * timeIn = new octaneapi::TimeT(); //// time type=TimeT;//// ////721////
    ////TimeT TEST ////
    timeIn->set_value(static_cast<float>(time));
    request.set_allocated_time(timeIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->updateTime(context.get(), request, &response);

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


bool ApiRootNodeGraphProxy::importFromFile(
            const char *                              path, //// test821 //// 
            Octane::VersionT &                        ocsVersion, //// test821 //// 
            Octane::AssetMissingCallbackT             assetMissingCallback, //// test821 //// 
            void *                                    assetsMissingCallbackUserData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::importFromFileRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    std::string * pathIn = new std::string(); //// path type=string;//// ////721////
    *pathIn = checkString(path);
    request.set_allocated_path(pathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetMissingCallback' [in] parameter to the request packet.
    octaneapi::AssetMissingCallbackT * assetmissingcallbackIn = new octaneapi::AssetMissingCallbackT(); //// assetMissingCallback type=AssetMissingCallbackT;//// ////721////
    // setup callback function assetMissingCallback
    //int assetMissingCallbackCallbackId = GRPCSettings::getNextCallbackId("AssetMissingCallback"); 
    //CallbackStorage::registerAssetMissingCallback(assetMissingCallbackCallbackId, assetMissingCallback);
    assetmissingcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //assetmissingcallbackIn->set_callbackid(assetMissingCallbackCallbackId);
    //if(className == "ApiRootNodeGraph" && method.mName == "importFromFile") return true;
    request.set_allocated_assetmissingcallback(assetmissingcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetsMissingCallbackUserData' [in] parameter to the request packet.
    uint64_t assetsmissingcallbackuserdataIn;
    //// USER DATA TEST ////
    assetsmissingcallbackuserdataIn = reinterpret_cast<uint64_t>(assetsMissingCallbackUserData);
    request.set_assetsmissingcallbackuserdata(assetsmissingcallbackuserdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::importFromFileResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->importFromFile(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        // set callback Id CallbackStorage::registerAssetMissingCallback( response.callbackid(), assetMissingCallback);
        CallbackStorage::registerAssetMissingCallback( response.callbackid(), assetMissingCallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();

        /////////////////////////////////////////////////////////////////////
        // Process 'ocsVersion' [out] parameter from the gRPC response packet
        uint32_t ocsVersionOut = response.ocsversion();
        ocsVersion = ocsVersionOut;//// SECOND////
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


bool ApiRootNodeGraphProxy::importOcsFromMemory(
            const char *                              baseDirectory, //// test821 //// 
            Octane::VersionT &                        ocsVersion, //// test821 //// 
            const char *                              xml, //// test821 //// 
            const size_t                              xmlLength, //// test821 //// 
            Octane::AssetMissingCallbackT             assetMissingCallback, //// test821 //// 
            void *                                    assetsMissingCallbackUserData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::importOcsFromMemoryRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'baseDirectory' [in] parameter to the request packet.
    std::string * basedirectoryIn = new std::string(); //// baseDirectory type=string;//// ////721////
    *basedirectoryIn = checkString(baseDirectory);
    request.set_allocated_basedirectory(basedirectoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'xml' [in] parameter to the request packet.
    std::string * xmlIn = new std::string(); //// xml type=string;//// ////721////
    *xmlIn = checkString(xml);
    request.set_allocated_xml(xmlIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'xmlLength' [in] parameter to the request packet.
    uint32_t xmllengthIn;
    xmllengthIn = static_cast<uint32_t>(xmlLength);////2 const size_t////
    request.set_xmllength(xmllengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetMissingCallback' [in] parameter to the request packet.
    octaneapi::AssetMissingCallbackT * assetmissingcallbackIn = new octaneapi::AssetMissingCallbackT(); //// assetMissingCallback type=AssetMissingCallbackT;//// ////721////
    // setup callback function assetMissingCallback
    //int assetMissingCallbackCallbackId = GRPCSettings::getNextCallbackId("AssetMissingCallback"); 
    //CallbackStorage::registerAssetMissingCallback(assetMissingCallbackCallbackId, assetMissingCallback);
    assetmissingcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //assetmissingcallbackIn->set_callbackid(assetMissingCallbackCallbackId);
    //if(className == "ApiRootNodeGraph" && method.mName == "importOcsFromMemory") return true;
    request.set_allocated_assetmissingcallback(assetmissingcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetsMissingCallbackUserData' [in] parameter to the request packet.
    uint64_t assetsmissingcallbackuserdataIn;
    //// USER DATA TEST ////
    assetsmissingcallbackuserdataIn = reinterpret_cast<uint64_t>(assetsMissingCallbackUserData);
    request.set_assetsmissingcallbackuserdata(assetsmissingcallbackuserdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::importOcsFromMemoryResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->importOcsFromMemory(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        // set callback Id CallbackStorage::registerAssetMissingCallback( response.callbackid(), assetMissingCallback);
        CallbackStorage::registerAssetMissingCallback( response.callbackid(), assetMissingCallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();

        /////////////////////////////////////////////////////////////////////
        // Process 'ocsVersion' [out] parameter from the gRPC response packet
        uint32_t ocsVersionOut = response.ocsversion();
        ocsVersion = ocsVersionOut;//// SECOND////
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


bool ApiRootNodeGraphProxy::importOrbxFromCallback(
            const char *                              baseDirectory, //// test821 //// 
            Octane::VersionT &                        ocsVersion, //// test821 //// 
            Octane::ApiRootNodeGraph::NextChunkCallbackT getOrbxChunkCallback, //// test821 //// 
            void *                                    orbxChunkCallbackUserData, //// test821 //// 
            Octane::AssetMissingCallbackT             assetMissingCallback, //// test821 //// 
            void *                                    assetMissingCallbackUserData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::importOrbxFromCallbackRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'baseDirectory' [in] parameter to the request packet.
    std::string * basedirectoryIn = new std::string(); //// baseDirectory type=string;//// ////721////
    *basedirectoryIn = checkString(baseDirectory);
    request.set_allocated_basedirectory(basedirectoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'getOrbxChunkCallback' [in] parameter to the request packet.
    octaneapi::NextChunkCallbackT * getorbxchunkcallbackIn = new octaneapi::NextChunkCallbackT(); //// getOrbxChunkCallback type=NextChunkCallbackT;//// ////721////
    // setup callback function getOrbxChunkCallback
    //int getOrbxChunkCallbackCallbackId = GRPCSettings::getNextCallbackId("NextChunkCallback"); 
    //CallbackStorage::registerNextChunkCallback(getOrbxChunkCallbackCallbackId, getOrbxChunkCallback);
    getorbxchunkcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //getorbxchunkcallbackIn->set_callbackid(getOrbxChunkCallbackCallbackId);
    //if(className == "ApiRootNodeGraph" && method.mName == "importOrbxFromCallback") return true;
    request.set_allocated_getorbxchunkcallback(getorbxchunkcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'orbxChunkCallbackUserData' [in] parameter to the request packet.
    uint64_t orbxchunkcallbackuserdataIn;
    //// USER DATA TEST ////
    orbxchunkcallbackuserdataIn = reinterpret_cast<uint64_t>(orbxChunkCallbackUserData);
    request.set_orbxchunkcallbackuserdata(orbxchunkcallbackuserdataIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetMissingCallback' [in] parameter to the request packet.
    octaneapi::AssetMissingCallbackT * assetmissingcallbackIn = new octaneapi::AssetMissingCallbackT(); //// assetMissingCallback type=AssetMissingCallbackT;//// ////721////
    // setup callback function assetMissingCallback
    //int assetMissingCallbackCallbackId = GRPCSettings::getNextCallbackId("AssetMissingCallback"); 
    //CallbackStorage::registerAssetMissingCallback(assetMissingCallbackCallbackId, assetMissingCallback);
    assetmissingcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //assetmissingcallbackIn->set_callbackid(assetMissingCallbackCallbackId);
    //if(className == "ApiRootNodeGraph" && method.mName == "importOrbxFromCallback") return true;
    request.set_allocated_assetmissingcallback(assetmissingcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetMissingCallbackUserData' [in] parameter to the request packet.
    uint64_t assetmissingcallbackuserdataIn;
    //// USER DATA TEST ////
    assetmissingcallbackuserdataIn = reinterpret_cast<uint64_t>(assetMissingCallbackUserData);
    request.set_assetmissingcallbackuserdata(assetmissingcallbackuserdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::importOrbxFromCallbackResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->importOrbxFromCallback(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        // set callback Id CallbackStorage::registerNextChunkCallback( response.callbackid(), getOrbxChunkCallback);
        CallbackStorage::registerNextChunkCallback( response.callbackid(), getOrbxChunkCallback);
        // set callback Id CallbackStorage::registerAssetMissingCallback( response.callbackid2(), assetMissingCallback);
        CallbackStorage::registerAssetMissingCallback( response.callbackid2(), assetMissingCallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId2' [out] parameter from the gRPC response packet
        int32_t callbackId2Out = response.callbackid2();

        /////////////////////////////////////////////////////////////////////
        // Process 'ocsVersion' [out] parameter from the gRPC response packet
        uint32_t ocsVersionOut = response.ocsversion();
        ocsVersion = ocsVersionOut;//// SECOND////
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


bool ApiRootNodeGraphProxy::importOrbxFromMemory(
            const char *                              baseDirectory, //// test821 //// 
            Octane::VersionT &                        ocsVersion, //// test821 //// 
            const void *                              orbxData, //// test821 //// 
            const size_t                              dataSize, //// test821 //// 
            Octane::AssetMissingCallbackT             assetMissingCallback, //// test821 //// 
            void *                                    assetsMissingCallbackUserData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::importOrbxFromMemoryRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'baseDirectory' [in] parameter to the request packet.
    std::string * basedirectoryIn = new std::string(); //// baseDirectory type=string;//// ////721////
    *basedirectoryIn = checkString(baseDirectory);
    request.set_allocated_basedirectory(basedirectoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'orbxData' [in] parameter to the request packet.
    octaneapi::Buffer * orbxdataIn = new octaneapi::Buffer(); //// orbxData type=Buffer;//// ////721////
    // BUFFER TEST 1 : orbxData
    size_t bufSize = dataSize;
    if (orbxData && bufSize > 0)
    {
        // Copy raw data into the protobuf Buffer (using std::string's set method)
        orbxdataIn->set_data(reinterpret_cast<const char*>(orbxData), dataSize);
        orbxdataIn->set_size(static_cast<uint32_t>(bufSize));
    }
    request.set_allocated_orbxdata(orbxdataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'dataSize' [in] parameter to the request packet.
    uint32_t datasizeIn;
    datasizeIn = static_cast<uint32_t>(dataSize);////2 const size_t////
    request.set_datasize(datasizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetMissingCallback' [in] parameter to the request packet.
    octaneapi::AssetMissingCallbackT * assetmissingcallbackIn = new octaneapi::AssetMissingCallbackT(); //// assetMissingCallback type=AssetMissingCallbackT;//// ////721////
    // setup callback function assetMissingCallback
    //int assetMissingCallbackCallbackId = GRPCSettings::getNextCallbackId("AssetMissingCallback"); 
    //CallbackStorage::registerAssetMissingCallback(assetMissingCallbackCallbackId, assetMissingCallback);
    assetmissingcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //assetmissingcallbackIn->set_callbackid(assetMissingCallbackCallbackId);
    //if(className == "ApiRootNodeGraph" && method.mName == "importOrbxFromMemory") return true;
    request.set_allocated_assetmissingcallback(assetmissingcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetsMissingCallbackUserData' [in] parameter to the request packet.
    uint64_t assetsmissingcallbackuserdataIn;
    //// USER DATA TEST ////
    assetsmissingcallbackuserdataIn = reinterpret_cast<uint64_t>(assetsMissingCallbackUserData);
    request.set_assetsmissingcallbackuserdata(assetsmissingcallbackuserdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::importOrbxFromMemoryResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->importOrbxFromMemory(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        // set callback Id CallbackStorage::registerAssetMissingCallback( response.callbackid(), assetMissingCallback);
        CallbackStorage::registerAssetMissingCallback( response.callbackid(), assetMissingCallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();

        /////////////////////////////////////////////////////////////////////
        // Process 'ocsVersion' [out] parameter from the gRPC response packet
        uint32_t ocsVersionOut = response.ocsversion();
        ocsVersion = ocsVersionOut;//// SECOND////
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


bool ApiRootNodeGraphProxy::exportToFile(
            const char *                              filePath, //// test821 //// 
            bool                                      useRelativePaths //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::exportToFileRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'filePath' [in] parameter to the request packet.
    std::string * filepathIn = new std::string(); //// filePath type=string;//// ////721////
    *filepathIn = checkString(filePath);
    request.set_allocated_filepath(filepathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'useRelativePaths' [in] parameter to the request packet.
    bool userelativepathsIn;
    userelativepathsIn = useRelativePaths;////2 bool////
    request.set_userelativepaths(userelativepathsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::exportToFileResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->exportToFile(context.get(), request, &response);

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


std::string ApiRootNodeGraphProxy::exportToString(
            const char *                              baseDirectory, //// test821 //// 
            bool                                      useRelativePaths //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::exportToStringRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'baseDirectory' [in] parameter to the request packet.
    std::string * basedirectoryIn = new std::string(); //// baseDirectory type=string;//// ////721////
    *basedirectoryIn = checkString(baseDirectory);
    request.set_allocated_basedirectory(basedirectoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'useRelativePaths' [in] parameter to the request packet.
    bool userelativepathsIn;
    userelativepathsIn = useRelativePaths;////2 bool////
    request.set_userelativepaths(userelativepathsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::exportToStringResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->exportToString(context.get(), request, &response);

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


uint32_t ApiRootNodeGraphProxy::referenceGraphCount() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::referenceGraphCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiRootNodeGraph::referenceGraphCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->referenceGraphCount(context.get(), request, &response);

    uint32_t retVal = 0;
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


void ApiRootNodeGraphProxy::loadAllReferences()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::loadAllReferencesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->loadAllReferences(context.get(), request, &response);

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


void ApiRootNodeGraphProxy::unloadAllReferences()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiRootNodeGraph::unloadAllReferencesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiRootNodeGraphService::Stub> stub = 
        octaneapi::ApiRootNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->unloadAllReferences(context.get(), request, &response);

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


