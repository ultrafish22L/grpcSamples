// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apinodegraphmoduleinfoclient.h"
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


GRPCSettings & ApiNodeGraphModuleInfoProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiNodeGraphModuleInfoProxy ApiNodeGraphModuleInfoProxy::create(
            const Octane::ModuleIdT                   moduleId, //// test821 //// 
            const char *const                         fullName, //// test821 //// 
            const char *const                         description, //// test821 //// 
            const char *const                         author, //// test821 //// 
            const Octane::VersionT                    versionNumber //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphModuleInfo::createRequest request;

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
    octaneapi::ApiNodeGraphModuleInfo::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphModuleInfoService::Stub> stub = 
        octaneapi::ApiNodeGraphModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->create1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeGraphModuleInfoProxy retVal;
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
        ApiNodeGraphModuleInfoProxy retVal;////714////
        return retVal;
    }
};


void ApiNodeGraphModuleInfoProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphModuleInfo::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphModuleInfoService::Stub> stub = 
        octaneapi::ApiNodeGraphModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->destroy1(context.get(), request, &response);

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


void ApiNodeGraphModuleInfoProxy::setCreateFunction(
            GRPCCreateFuncT                          func //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphModuleInfo::setCreateFunctionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::CreateFuncT * funcIn = new octaneapi::CreateFuncT(); //// func type=CreateFuncT;//// ////721////
    // setup callback function func
    //int funcCallbackId = GRPCSettings::getNextCallbackId("GRPCCreateFunc"); 
    //CallbackStorage::registerGRPCCreateFunc(funcCallbackId, func);
    funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //funcIn->set_callbackid(funcCallbackId);
    //if(className == "ApiNodeGraphModuleInfo" && method.mName == "setCreateFunction") return true;
    request.set_allocated_func(funcIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraphModuleInfo::setCreateFunctionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphModuleInfoService::Stub> stub = 
        octaneapi::ApiNodeGraphModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setCreateFunction(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCCreateFunc( response.callbackid(), func);
        CallbackStorage::registerGRPCCreateFunc( response.callbackid(), func);
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


void ApiNodeGraphModuleInfoProxy::setDestroyFunction(
            const Octane::ApiNodeGraphModuleInfo::DestroyFuncT func //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphModuleInfo::setDestroyFunctionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::DestroyFuncT * funcIn = new octaneapi::DestroyFuncT(); //// func type=DestroyFuncT;//// ////721////
    // setup callback function func
    //int funcCallbackId = GRPCSettings::getNextCallbackId("DestroyFunc"); 
    //CallbackStorage::registerDestroyFunc(funcCallbackId, func);
    funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //funcIn->set_callbackid(funcCallbackId);
    //if(className == "ApiNodeGraphModuleInfo" && method.mName == "setDestroyFunction") return true;
    request.set_allocated_func(funcIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraphModuleInfo::setDestroyFunctionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphModuleInfoService::Stub> stub = 
        octaneapi::ApiNodeGraphModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setDestroyFunction(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerDestroyFunc( response.callbackid(), func);
        CallbackStorage::registerDestroyFunc( response.callbackid(), func);
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


void ApiNodeGraphModuleInfoProxy::setOnEvaluateFunction(
            const Octane::ApiNodeGraphModuleInfo::OnEvaluateFuncT func //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphModuleInfo::setOnEvaluateFunctionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::OnEvaluateFuncT * funcIn = new octaneapi::OnEvaluateFuncT(); //// func type=OnEvaluateFuncT;//// ////721////
    // setup callback function func
    //int funcCallbackId = GRPCSettings::getNextCallbackId("OnEvaluateFunc"); 
    //CallbackStorage::registerOnEvaluateFunc(funcCallbackId, func);
    funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //funcIn->set_callbackid(funcCallbackId);
    //if(className == "ApiNodeGraphModuleInfo" && method.mName == "setOnEvaluateFunction") return true;
    request.set_allocated_func(funcIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraphModuleInfo::setOnEvaluateFunctionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphModuleInfoService::Stub> stub = 
        octaneapi::ApiNodeGraphModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOnEvaluateFunction(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnEvaluateFunc( response.callbackid(), func);
        CallbackStorage::registerOnEvaluateFunc( response.callbackid(), func);
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


void ApiNodeGraphModuleInfoProxy::setOnTriggerFunction(
            const Octane::ApiNodeGraphModuleInfo::OnTriggerFuncT func //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphModuleInfo::setOnTriggerFunctionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::OnTriggerFuncT * funcIn = new octaneapi::OnTriggerFuncT(); //// func type=OnTriggerFuncT;//// ////721////
    // setup callback function func
    //int funcCallbackId = GRPCSettings::getNextCallbackId("OnTriggerFunc"); 
    //CallbackStorage::registerOnTriggerFunc(funcCallbackId, func);
    funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //funcIn->set_callbackid(funcCallbackId);
    //if(className == "ApiNodeGraphModuleInfo" && method.mName == "setOnTriggerFunction") return true;
    request.set_allocated_func(funcIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNodeGraphModuleInfo::setOnTriggerFunctionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphModuleInfoService::Stub> stub = 
        octaneapi::ApiNodeGraphModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOnTriggerFunction(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnTriggerFunc( response.callbackid(), func);
        CallbackStorage::registerOnTriggerFunc( response.callbackid(), func);
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


void ApiNodeGraphModuleInfoProxy::setOutType(
            const Octane::NodePinType                 outType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphModuleInfo::setOutTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'outType' [in] parameter to the request packet.
    octaneapi::NodePinType outtypeIn;
    outtypeIn = static_cast<octaneapi::NodePinType>(outType);
    request.set_outtype(outtypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNodeGraphModuleInfoService::Stub> stub = 
        octaneapi::ApiNodeGraphModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOutType(context.get(), request, &response);

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


