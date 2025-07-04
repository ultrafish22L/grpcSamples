// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apiworkpanemoduleinfoclient.h"
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
#include "apimodule.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiWorkPaneModuleInfoProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiWorkPaneModuleInfoProxy ApiWorkPaneModuleInfoProxy::create(
            const Octane::ModuleIdT                   moduleId, //// test821 //// 
            const char *                              fullName, //// test821 //// 
            const char *                              description, //// test821 //// 
            const char *                              author, //// test821 //// 
            const Octane::VersionT                    versionNumber //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiWorkPaneModuleInfo::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleId' [in] parameter to the request packet.
    octaneapi::ModuleIdT * moduleidIn = new octaneapi::ModuleIdT(); //// moduleId type=ModuleIdT;//// ////721////
    //// ModuleIdT TEST////
    moduleidIn->set_id(moduleId);
    request.set_allocated_moduleid(moduleidIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullName' [in] parameter to the request packet.
    std::string * fullnameIn = new std::string(); //// fullName type=string;//// ////721////
    *fullnameIn = checkString(fullName);
    request.set_allocated_fullname(fullnameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'description' [in] parameter to the request packet.
    std::string * descriptionIn = new std::string(); //// description type=string;//// ////721////
    *descriptionIn = checkString(description);
    request.set_allocated_description(descriptionIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'author' [in] parameter to the request packet.
    std::string * authorIn = new std::string(); //// author type=string;//// ////721////
    *authorIn = checkString(author);
    request.set_allocated_author(authorIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'versionNumber' [in] parameter to the request packet.
    uint32_t versionnumberIn;
    versionnumberIn = versionNumber;////2 const Octane::VersionT////
    request.set_versionnumber(versionnumberIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiWorkPaneModuleInfo::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiWorkPaneModuleInfoService::Stub> stub = 
        octaneapi::ApiWorkPaneModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->create2(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiWorkPaneModuleInfoProxy retVal;
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
        ApiWorkPaneModuleInfoProxy retVal;////714////
        return retVal;
    }
};


void ApiWorkPaneModuleInfoProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiWorkPaneModuleInfo::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiWorkPaneModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiWorkPaneModuleInfoService::Stub> stub = 
        octaneapi::ApiWorkPaneModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->destroy2(context.get(), request, &response);

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


void ApiWorkPaneModuleInfoProxy::setInitFunction(
            GRPCInitFuncT                            func //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiWorkPaneModuleInfo::setInitFunctionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiWorkPaneModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::InitFuncT * funcIn = new octaneapi::InitFuncT(); //// func type=InitFuncT;//// ////721////
    // setup callback function func
    //int funcCallbackId = GRPCSettings::getNextCallbackId("GRPCInitFunc"); 
    //CallbackStorage::registerGRPCInitFunc(funcCallbackId, func);
    funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //funcIn->set_callbackid(funcCallbackId);
    //if(className == "ApiWorkPaneModuleInfo" && method.mName == "setInitFunction") return true;
    request.set_allocated_func(funcIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiWorkPaneModuleInfo::setInitFunctionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiWorkPaneModuleInfoService::Stub> stub = 
        octaneapi::ApiWorkPaneModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInitFunction(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCInitFunc( response.callbackid(), func);
        CallbackStorage::registerGRPCInitFunc( response.callbackid(), func);
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


void ApiWorkPaneModuleInfoProxy::setCleanupFunction(
            const Octane::ApiWorkPaneModuleInfo::CleanupFuncT func //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiWorkPaneModuleInfo::setCleanupFunctionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiWorkPaneModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::CleanupFuncT * funcIn = new octaneapi::CleanupFuncT(); //// func type=CleanupFuncT;//// ////721////
    // setup callback function func
    //int funcCallbackId = GRPCSettings::getNextCallbackId("CleanupFunc"); 
    //CallbackStorage::registerCleanupFunc(funcCallbackId, func);
    funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //funcIn->set_callbackid(funcCallbackId);
    //if(className == "ApiWorkPaneModuleInfo" && method.mName == "setCleanupFunction") return true;
    request.set_allocated_func(funcIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiWorkPaneModuleInfo::setCleanupFunctionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiWorkPaneModuleInfoService::Stub> stub = 
        octaneapi::ApiWorkPaneModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setCleanupFunction(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerCleanupFunc( response.callbackid(), func);
        CallbackStorage::registerCleanupFunc( response.callbackid(), func);
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


void ApiWorkPaneModuleInfoProxy::setWorkPaneToolbarIds(
            const Octane::ModuleIdT *const            toolbarModuleIds, //// test821 //// 
            const size_t                              size //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiWorkPaneModuleInfo::setWorkPaneToolbarIdsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiWorkPaneModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'toolbarModuleIds' [in] parameter to the request packet.
    octaneapi::ApiArrayModuleIdT * toolbarmoduleidsIn = new octaneapi::ApiArrayModuleIdT(); //// toolbarModuleIds type=ApiArrayModuleIdT;//// ////721////
    //// Client Array Type F ////
    //// param.mProtoCppType = ApiArrayModuleIdT param.mType = const Octane::ModuleIdT *const ////
    for (size_t h = 0; h < size; h++)
    {
        auto item = toolbarmoduleidsIn->add_data();
        item->set_id(toolbarModuleIds[h]);
    }
    request.set_allocated_toolbarmoduleids(toolbarmoduleidsIn);//// 6215 ////

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
    std::unique_ptr<octaneapi::ApiWorkPaneModuleInfoService::Stub> stub = 
        octaneapi::ApiWorkPaneModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setWorkPaneToolbarIds(context.get(), request, &response);

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


