// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

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


namespace OctaneGRPC
{


GRPCSettings & ApiNodeGraphModuleInfoProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiNodeGraphModuleInfoProxy ApiNodeGraphModuleInfoProxy::create(
            const Octane::ModuleIdT                   moduleId,
            const char *const                         fullName,
            const char *const                         description,
            const char *const                         author,
            const Octane::VersionT                    versionNumber
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNodeGraphModuleInfo::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleId' [in] parameter to the request packet.
    octaneapi::ModuleIdT * moduleidIn = new octaneapi::ModuleIdT();
    moduleidIn->set_id(moduleId);
    request.set_allocated_moduleid(moduleidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'fullName' [in] parameter to the request packet.
    std::string * fullnameIn = new std::string();
    *fullnameIn = checkString(fullName);
    request.set_allocated_fullname(fullnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'description' [in] parameter to the request packet.
    std::string * descriptionIn = new std::string();
    *descriptionIn = checkString(description);
    request.set_allocated_description(descriptionIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'author' [in] parameter to the request packet.
    std::string * authorIn = new std::string();
    *authorIn = checkString(author);
    request.set_allocated_author(authorIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'versionNumber' [in] parameter to the request packet.
    uint32_t versionnumberIn;
    versionnumberIn = versionNumber;
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
        ApiNodeGraphModuleInfoProxy retVal;
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);
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
            GRPCCreateFuncT                          func
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::CreateFuncT * funcIn = new octaneapi::CreateFuncT();
    // setup callback function func
        funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_func(funcIn);

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
            const Octane::ApiNodeGraphModuleInfo::DestroyFuncT func
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::DestroyFuncT * funcIn = new octaneapi::DestroyFuncT();
    // setup callback function func
        funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_func(funcIn);

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
            const Octane::ApiNodeGraphModuleInfo::OnEvaluateFuncT func
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::OnEvaluateFuncT * funcIn = new octaneapi::OnEvaluateFuncT();
    // setup callback function func
        funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_func(funcIn);

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
            const Octane::ApiNodeGraphModuleInfo::OnTriggerFuncT func
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::OnTriggerFuncT * funcIn = new octaneapi::OnTriggerFuncT();
    // setup callback function func
        funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_func(funcIn);

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
            const Octane::NodePinType                 outType
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);
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


} //end of namespace
