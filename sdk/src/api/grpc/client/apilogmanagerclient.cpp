// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apilogmanagerclient.h"
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
#include "apilogmanager.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiLogManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiLogManagerProxy::registerLogCallbackProc(
            Octane::ApiLogManager::ApiLogCallbackProc * proc
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::registerLogCallbackProcRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'proc' [in] parameter to the request packet.
    octaneapi::ApiLogCallbackProc * procIn = new octaneapi::ApiLogCallbackProc();
    // setup callback function proc
        procIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_proc(procIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLogManager::registerLogCallbackProcResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->registerLogCallbackProc(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        // set callback Id CallbackStorage::registerApiLogCallbackProc( response.callbackid(), proc);
        CallbackStorage::registerApiLogCallbackProc( response.callbackid(), proc);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
    return retVal;
};


bool ApiLogManagerProxy::unregisterLogCallbackProc(
            Octane::ApiLogManager::ApiLogCallbackProc * proc
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::unregisterLogCallbackProcRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'proc' [in] parameter to the request packet.
    octaneapi::ApiLogCallbackProc * procIn = new octaneapi::ApiLogCallbackProc();
    // setup callback function proc
        procIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_proc(procIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLogManager::unregisterLogCallbackProcResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->unregisterLogCallbackProc(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        // set callback Id CallbackStorage::registerApiLogCallbackProc( response.callbackid(), proc);
        CallbackStorage::registerApiLogCallbackProc( response.callbackid(), proc);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
    return retVal;
};


void ApiLogManagerProxy::openOctaneLogWindow()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::openOctaneLogWindowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->openOctaneLogWindow(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


void ApiLogManagerProxy::log(
            const char *                              text
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::logRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'text' [in] parameter to the request packet.
    std::string * textIn = new std::string();
    *textIn = checkString(text);
    request.set_allocated_text(textIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->log(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


void ApiLogManagerProxy::logError(
            const char *                              errorMsg
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::logErrorRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'errorMsg' [in] parameter to the request packet.
    std::string * errormsgIn = new std::string();
    *errormsgIn = checkString(errorMsg);
    request.set_allocated_errormsg(errormsgIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->logError(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


void ApiLogManagerProxy::logFmt(
            const char *                              fmt
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::logFmtRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fmt' [in] parameter to the request packet.
    std::string * fmtIn = new std::string();
    *fmtIn = checkString(fmt);
    request.set_allocated_fmt(fmtIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->logFmt(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


void ApiLogManagerProxy::logErrorFmt(
            const char *                              fmt
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::logErrorFmtRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fmt' [in] parameter to the request packet.
    std::string * fmtIn = new std::string();
    *fmtIn = checkString(fmt);
    request.set_allocated_fmt(fmtIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->logErrorFmt(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


bool ApiLogManagerProxy::isFlagRegistered(
            const char *const                         name
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::isFlagRegisteredRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLogManager::isFlagRegisteredResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->isFlagRegistered(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
    return retVal;
};


int ApiLogManagerProxy::setFlag(
            const char *const                         name,
            const int                                 value
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::setFlagRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLogManager::setFlagResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->setFlag(context.get(), request, &response);

    int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
        retVal = resultOut;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
    return retVal;
};


int ApiLogManagerProxy::__registerLogFlag(
            int &                                     flag,
            const char *                              prefix,
            const char *                              name,
            const char *                              description
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::__registerLogFlagRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'flag' [in] parameter to the request packet.
    int32_t flagIn;
    flagIn = flag;
    request.set_flag(flagIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'prefix' [in] parameter to the request packet.
    std::string * prefixIn = new std::string();
    *prefixIn = checkString(prefix);
    request.set_allocated_prefix(prefixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string();
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'description' [in] parameter to the request packet.
    std::string * descriptionIn = new std::string();
    *descriptionIn = checkString(description);
    request.set_allocated_description(descriptionIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiLogManager::__registerLogFlagResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->__registerLogFlag(context.get(), request, &response);

    int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
        retVal = resultOut;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
    return retVal;
};


void ApiLogManagerProxy::__logFmtPrefix(
            const char *                              prefix,
            const char *                              fmt
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::__logFmtPrefixRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'prefix' [in] parameter to the request packet.
    std::string * prefixIn = new std::string();
    *prefixIn = checkString(prefix);
    request.set_allocated_prefix(prefixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'fmt' [in] parameter to the request packet.
    std::string * fmtIn = new std::string();
    *fmtIn = checkString(fmt);
    request.set_allocated_fmt(fmtIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiLogManagerService::Stub> stub =
        octaneapi::ApiLogManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->__logFmtPrefix(context.get(), request, &response);

    if (status.ok())
    {
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
};


} //end of namespace
