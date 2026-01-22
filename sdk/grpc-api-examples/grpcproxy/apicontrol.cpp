// Copyright (C) 2026 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////
//myself
#include "apicontrol.h"
// applicatrion
#include "callbackservice.h"
#include "control.grpc.pb.h"
#include "grpcsettings.h"
// sytyem
#include <cassert>
#include <grpcpp/grpcpp.h>


namespace OctaneGRPC
{
std::function<void()> ApiControlService::sBlockingOperationCallbackFunc;

GRPCSettings& ApiControlService::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiControlService::callBlockingFunc()
{
    if (sBlockingOperationCallbackFunc)
    {
        sBlockingOperationCallbackFunc();
    }
}


void ApiControlService::setBlockingFunc(
    std::function<void()> callbackFunc)
{
    sBlockingOperationCallbackFunc = callbackFunc;
}


bool ApiControlService::startBlockingOperation(
    const std::string& uniqueModuleId,
    const std::string& message,
    std::function<void()> callbackFunc)
{
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiControl::StartBlockingRequest request;
    request.set_message(message);
    request.set_uniquemoduleid(uniqueModuleId);

    // Make the call to the server
    octaneapi::ApiControl::ControlResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiControlService::Stub> stub =
        octaneapi::ApiControlService::NewStub(getGRPCSettings().getChannel());

    setBlockingFunc(callbackFunc);

    grpc::Status status = stub->startBlockingOperation(context.get(), request, &response);
    if (!status.ok())
    {
        switch (status.error_code())
        {
        case grpc::StatusCode::INVALID_ARGUMENT:
            throw std::invalid_argument(status.error_message());
        default:
            throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
        }
        return false;
    }
    return true;
}


bool ApiControlService::setApiLogPath(
    bool                 saveLogsToTxtFile,
    const std::string& filePath)
{
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiControl::ApiLogRequest request;
    request.set_savetotextfile(saveLogsToTxtFile);
    request.set_filepath(filePath);

    // Make the call to the server
    octaneapi::ApiControl::ControlResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiControlService::Stub> stub =
        octaneapi::ApiControlService::NewStub(getGRPCSettings().getChannel());

    grpc::Status status = stub->setApiLogFilePath(context.get(), request, &response);
    if (!status.ok())
    {
        switch (status.error_code())
        {
        case grpc::StatusCode::INVALID_ARGUMENT:
            throw std::invalid_argument(status.error_message());
        default:
            throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
        }
        return false;
    }
    return true;
}

}// namespace OctaneGRPC;