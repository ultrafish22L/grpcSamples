// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apimoduleglobalclient.h"
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
#include "apicommandmoduleinfoclient.h"
#include "apiworkpanemoduleinfoclient.h"
#include "apinodegraphmoduleinfoclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiModuleGlobalProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiModuleGlobalProxy::registerCommandModule(
            const ApiCommandModuleInfoProxy &         moduleInfo
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleGlobal::registerCommandModuleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * moduleinfoIn = new octaneapi::ObjectRef();
    moduleinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCommandModuleInfo);
    moduleinfoIn->set_handle(moduleInfo.getObjectHandle());
    request.set_allocated_moduleinfo(moduleinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleGlobal::registerCommandModuleResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleGlobalService::Stub> stub =
        octaneapi::ApiModuleGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->registerCommandModule(context.get(), request, &response);

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


bool ApiModuleGlobalProxy::registerWorkPaneModule(
            const ApiWorkPaneModuleInfoProxy &        moduleInfo
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleGlobal::registerWorkPaneModuleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * moduleinfoIn = new octaneapi::ObjectRef();
    moduleinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiWorkPaneModuleInfo);
    moduleinfoIn->set_handle(moduleInfo.getObjectHandle());
    request.set_allocated_moduleinfo(moduleinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleGlobal::registerWorkPaneModuleResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleGlobalService::Stub> stub =
        octaneapi::ApiModuleGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->registerWorkPaneModule(context.get(), request, &response);

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


bool ApiModuleGlobalProxy::registerNodeGraphModule(
            const ApiNodeGraphModuleInfoProxy &       moduleInfo
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleGlobal::registerNodeGraphModuleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * moduleinfoIn = new octaneapi::ObjectRef();
    moduleinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);
    moduleinfoIn->set_handle(moduleInfo.getObjectHandle());
    request.set_allocated_moduleinfo(moduleinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleGlobal::registerNodeGraphModuleResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleGlobalService::Stub> stub =
        octaneapi::ApiModuleGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->registerNodeGraphModule(context.get(), request, &response);

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


bool ApiModuleGlobalProxy::registerStaticCommandModule(
            const ApiCommandModuleInfoProxy &         moduleInfo
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleGlobal::registerStaticCommandModuleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * moduleinfoIn = new octaneapi::ObjectRef();
    moduleinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCommandModuleInfo);
    moduleinfoIn->set_handle(moduleInfo.getObjectHandle());
    request.set_allocated_moduleinfo(moduleinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleGlobal::registerStaticCommandModuleResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleGlobalService::Stub> stub =
        octaneapi::ApiModuleGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->registerStaticCommandModule(context.get(), request, &response);

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


bool ApiModuleGlobalProxy::registerStaticWorkPaneModule(
            const ApiWorkPaneModuleInfoProxy &        moduleInfo
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleGlobal::registerStaticWorkPaneModuleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * moduleinfoIn = new octaneapi::ObjectRef();
    moduleinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiWorkPaneModuleInfo);
    moduleinfoIn->set_handle(moduleInfo.getObjectHandle());
    request.set_allocated_moduleinfo(moduleinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleGlobal::registerStaticWorkPaneModuleResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleGlobalService::Stub> stub =
        octaneapi::ApiModuleGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->registerStaticWorkPaneModule(context.get(), request, &response);

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


bool ApiModuleGlobalProxy::registerStaticNodeGraphModule(
            const ApiNodeGraphModuleInfoProxy &       moduleInfo
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleGlobal::registerStaticNodeGraphModuleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleInfo' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * moduleinfoIn = new octaneapi::ObjectRef();
    moduleinfoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraphModuleInfo);
    moduleinfoIn->set_handle(moduleInfo.getObjectHandle());
    request.set_allocated_moduleinfo(moduleinfoIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleGlobal::registerStaticNodeGraphModuleResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleGlobalService::Stub> stub =
        octaneapi::ApiModuleGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->registerStaticNodeGraphModule(context.get(), request, &response);

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


} //end of namespace
