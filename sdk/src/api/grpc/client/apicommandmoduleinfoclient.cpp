// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apicommandmoduleinfoclient.h"
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
#include "apiimageclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiCommandModuleInfoProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiCommandModuleInfoProxy ApiCommandModuleInfoProxy::create(
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
    octaneapi::ApiCommandModuleInfo::createRequest request;

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
    octaneapi::ApiCommandModuleInfo::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCommandModuleInfoService::Stub> stub =
        octaneapi::ApiCommandModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiCommandModuleInfoProxy retVal;
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
        ApiCommandModuleInfoProxy retVal;
        return retVal;
    }
};


void ApiCommandModuleInfoProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCommandModuleInfo::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCommandModuleInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCommandModuleInfoService::Stub> stub =
        octaneapi::ApiCommandModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->destroy(context.get(), request, &response);

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


void ApiCommandModuleInfoProxy::setRunFunction(
            CommandModuleRunFuncT                     func
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCommandModuleInfo::setRunFunctionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCommandModuleInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'func' [in] parameter to the request packet.
    octaneapi::CommandModuleRunFuncT * funcIn = new octaneapi::CommandModuleRunFuncT();
    // setup callback function func
        funcIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_func(funcIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCommandModuleInfo::setRunFunctionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCommandModuleInfoService::Stub> stub =
        octaneapi::ApiCommandModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setRunFunction(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerCommandModuleRunFunc( response.callbackid(), func);
        CallbackStorage::registerCommandModuleRunFunc( response.callbackid(), func);
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


void ApiCommandModuleInfoProxy::setIcon(
            const ApiImageProxy *const                icon
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCommandModuleInfo::setIconRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCommandModuleInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'icon' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * iconIn = new octaneapi::ObjectRef();
    iconIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);
    iconIn->set_handle(icon->getObjectHandle());
    request.set_allocated_icon(iconIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCommandModuleInfoService::Stub> stub =
        octaneapi::ApiCommandModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->setIcon(context.get(), request, &response);

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


void ApiCommandModuleInfoProxy::assignShortcutKey(
            const char *const                         shortcutGroupName,
            const int                                 shortcutKeyCode,
            const int                                 shortcutModifierKeyFlag
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCommandModuleInfo::assignShortcutKeyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCommandModuleInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'shortcutGroupName' [in] parameter to the request packet.
    std::string * shortcutgroupnameIn = new std::string();
    *shortcutgroupnameIn = checkString(shortcutGroupName);
    request.set_allocated_shortcutgroupname(shortcutgroupnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'shortcutKeyCode' [in] parameter to the request packet.
    int32_t shortcutkeycodeIn;
    shortcutkeycodeIn = shortcutKeyCode;
    request.set_shortcutkeycode(shortcutkeycodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'shortcutModifierKeyFlag' [in] parameter to the request packet.
    int32_t shortcutmodifierkeyflagIn;
    shortcutmodifierkeyflagIn = shortcutModifierKeyFlag;
    request.set_shortcutmodifierkeyflag(shortcutmodifierkeyflagIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCommandModuleInfoService::Stub> stub =
        octaneapi::ApiCommandModuleInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->assignShortcutKey(context.get(), request, &response);

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
