// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apioctanemodulesclient.h"
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
#include "apioctanemodules.grpc.pb.h"
#include "apioctanemoduleinfoclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiOctaneModulesProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiOctaneModulesProxy::setDirectory(
            const char *                              newPath
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOctaneModules::setDirectoryRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'newPath' [in] parameter to the request packet.
    std::string * newpathIn = new std::string();
    *newpathIn = checkString(newPath);
    request.set_allocated_newpath(newpathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOctaneModules::setDirectoryResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOctaneModulesService::Stub> stub =
        octaneapi::ApiOctaneModulesService::NewStub(getGRPCSettings().getChannel());
    status = stub->setDirectory(context.get(), request, &response);

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


std::string ApiOctaneModulesProxy::getDirectory()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOctaneModules::getDirectoryRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOctaneModules::getDirectoryResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOctaneModulesService::Stub> stub =
        octaneapi::ApiOctaneModulesService::NewStub(getGRPCSettings().getChannel());
    status = stub->getDirectory(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


ApiOctaneModuleInfoProxy ApiOctaneModulesProxy::getModuleInfo(
            const Octane::ModuleIdT                   moduleId
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOctaneModules::getModuleInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleId' [in] parameter to the request packet.
    octaneapi::ModuleIdT * moduleidIn = new octaneapi::ModuleIdT();
    moduleidIn->set_id(moduleId);
    request.set_allocated_moduleid(moduleidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOctaneModules::getModuleInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOctaneModulesService::Stub> stub =
        octaneapi::ApiOctaneModulesService::NewStub(getGRPCSettings().getChannel());
    status = stub->getModuleInfo(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiOctaneModuleInfoProxy retVal;
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
        ApiOctaneModuleInfoProxy retVal;
        return retVal;
    }
};


std::vector<Octane::ModuleIdT> ApiOctaneModulesProxy::getNodegraphModules()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOctaneModules::getNodegraphModulesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOctaneModules::getNodegraphModulesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOctaneModulesService::Stub> stub =
        octaneapi::ApiOctaneModulesService::NewStub(getGRPCSettings().getChannel());
    status = stub->getNodegraphModules(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayModuleIdT resultOut = response.result();
        std::vector<Octane::ModuleIdT> retVal;
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            retVal.push_back(resultOut.data(i).id());
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


std::vector<Octane::ModuleIdT> ApiOctaneModulesProxy::getCommandModules()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOctaneModules::getCommandModulesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOctaneModules::getCommandModulesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOctaneModulesService::Stub> stub =
        octaneapi::ApiOctaneModulesService::NewStub(getGRPCSettings().getChannel());
    status = stub->getCommandModules(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayModuleIdT resultOut = response.result();
        std::vector<Octane::ModuleIdT> retVal;
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            retVal.push_back(resultOut.data(i).id());
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


bool ApiOctaneModulesProxy::runCommandModule(
            const Octane::ModuleIdT                   moduleId
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOctaneModules::runCommandModuleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleId' [in] parameter to the request packet.
    octaneapi::ModuleIdT * moduleidIn = new octaneapi::ModuleIdT();
    moduleidIn->set_id(moduleId);
    request.set_allocated_moduleid(moduleidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOctaneModules::runCommandModuleResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOctaneModulesService::Stub> stub =
        octaneapi::ApiOctaneModulesService::NewStub(getGRPCSettings().getChannel());
    status = stub->runCommandModule(context.get(), request, &response);

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


