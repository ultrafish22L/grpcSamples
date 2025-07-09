// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

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


GRPCSettings & ApiLogManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiLogManagerProxy::registerLogCallbackProc(
            Octane::ApiLogManager::ApiLogCallbackProc * proc //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::registerLogCallbackProcRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'proc' [in] parameter to the request packet.
    octaneapi::ApiLogCallbackProc * procIn = new octaneapi::ApiLogCallbackProc(); //// proc type=ApiLogCallbackProc;//// ////721////
    // setup callback function proc
    //int procCallbackId = GRPCSettings::getNextCallbackId("ApiLogCallbackProc"); 
    //CallbackStorage::registerApiLogCallbackProc(procCallbackId, proc);
    procIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //procIn->set_callbackid(procCallbackId);
    //if(className == "ApiLogManager" && method.mName == "registerLogCallbackProc") return true;
    request.set_allocated_proc(procIn);//// 6215 ////

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
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
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


bool ApiLogManagerProxy::unregisterLogCallbackProc(
            Octane::ApiLogManager::ApiLogCallbackProc * proc //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::unregisterLogCallbackProcRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'proc' [in] parameter to the request packet.
    octaneapi::ApiLogCallbackProc * procIn = new octaneapi::ApiLogCallbackProc(); //// proc type=ApiLogCallbackProc;//// ////721////
    // setup callback function proc
    //int procCallbackId = GRPCSettings::getNextCallbackId("ApiLogCallbackProc"); 
    //CallbackStorage::registerApiLogCallbackProc(procCallbackId, proc);
    procIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //procIn->set_callbackid(procCallbackId);
    //if(className == "ApiLogManager" && method.mName == "unregisterLogCallbackProc") return true;
    request.set_allocated_proc(procIn);//// 6215 ////

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
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
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


void ApiLogManagerProxy::log(
            const char *                              text //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::logRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'text' [in] parameter to the request packet.
    std::string * textIn = new std::string(); //// text type=string;//// ////721////
    *textIn = checkString(text);
    request.set_allocated_text(textIn);//// 6215 ////

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


void ApiLogManagerProxy::logError(
            const char *                              errorMsg //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::logErrorRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'errorMsg' [in] parameter to the request packet.
    std::string * errormsgIn = new std::string(); //// errorMsg type=string;//// ////721////
    *errormsgIn = checkString(errorMsg);
    request.set_allocated_errormsg(errormsgIn);//// 6215 ////

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


void ApiLogManagerProxy::logFmt(
            const char *                              fmt //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::logFmtRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fmt' [in] parameter to the request packet.
    std::string * fmtIn = new std::string(); //// fmt type=string;//// ////721////
    *fmtIn = checkString(fmt);
    request.set_allocated_fmt(fmtIn);//// 6215 ////

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


void ApiLogManagerProxy::logErrorFmt(
            const char *                              fmt //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::logErrorFmtRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'fmt' [in] parameter to the request packet.
    std::string * fmtIn = new std::string(); //// fmt type=string;//// ////721////
    *fmtIn = checkString(fmt);
    request.set_allocated_fmt(fmtIn);//// 6215 ////

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


bool ApiLogManagerProxy::isFlagRegistered(
            const char *const                         name //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::isFlagRegisteredRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string(); //// name type=string;//// ////721////
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);//// 6215 ////

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


int ApiLogManagerProxy::setFlag(
            const char *const                         name, //// test821 //// 
            const int                                 value //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::setFlagRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string(); //// name type=string;//// ////721////
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;////2 const int////
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


int ApiLogManagerProxy::__registerLogFlag(
            int &                                     flag, //// test821 //// 
            const char *                              prefix, //// test821 //// 
            const char *                              name, //// test821 //// 
            const char *                              description //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::__registerLogFlagRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'flag' [in] parameter to the request packet.
    int32_t flagIn;
    flagIn = flag;////2 int &////
    request.set_flag(flagIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'prefix' [in] parameter to the request packet.
    std::string * prefixIn = new std::string(); //// prefix type=string;//// ////721////
    *prefixIn = checkString(prefix);
    request.set_allocated_prefix(prefixIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'name' [in] parameter to the request packet.
    std::string * nameIn = new std::string(); //// name type=string;//// ////721////
    *nameIn = checkString(name);
    request.set_allocated_name(nameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'description' [in] parameter to the request packet.
    std::string * descriptionIn = new std::string(); //// description type=string;//// ////721////
    *descriptionIn = checkString(description);
    request.set_allocated_description(descriptionIn);//// 6215 ////

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


void ApiLogManagerProxy::__logFmtPrefix(
            const char *                              prefix, //// test821 //// 
            const char *                              fmt //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiLogManager::__logFmtPrefixRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'prefix' [in] parameter to the request packet.
    std::string * prefixIn = new std::string(); //// prefix type=string;//// ////721////
    *prefixIn = checkString(prefix);
    request.set_allocated_prefix(prefixIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'fmt' [in] parameter to the request packet.
    std::string * fmtIn = new std::string(); //// fmt type=string;//// ////721////
    *fmtIn = checkString(fmt);
    request.set_allocated_fmt(fmtIn);//// 6215 ////

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


