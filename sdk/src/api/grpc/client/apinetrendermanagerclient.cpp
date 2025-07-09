// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apinetrendermanagerclient.h"
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
#include "apinetrendermanager.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertnetinterfaceinfo.h"
#include "convertnetrendersettings.h"
#include "convertnetrenderstatus.h"


GRPCSettings & ApiNetRenderManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiNetRenderManagerProxy::configure(
            const Octane::NetRenderSettings &         settings //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::configureRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'settings' [in] parameter to the request packet.
    octaneapi::NetRenderSettings * settingsIn = new octaneapi::NetRenderSettings(); //// settings type=NetRenderSettings;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    NetRenderSettingsConverter::convert(settings, *settingsIn); //// Convert Called type 1c =NetRenderSettings ////
    request.set_allocated_settings(settingsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::configureResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->configure(context.get(), request, &response);

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


Octane::NetRenderSettings ApiNetRenderManagerProxy::configuration()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::configurationRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::configurationResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->configuration(context.get(), request, &response);

    Octane::NetRenderSettings retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NetRenderSettings resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        NetRenderSettingsConverter::convert(resultOut, retVal); ////Convert Called type 5223 =NetRenderSettings;////
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


void ApiNetRenderManagerProxy::enable(
            const bool                                enable //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::enableRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'enable' [in] parameter to the request packet.
    bool enableIn;
    enableIn = enable;////2 const bool////
    request.set_enable(enableIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->enable(context.get(), request, &response);

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


bool ApiNetRenderManagerProxy::isSupported()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::isSupportedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::isSupportedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->isSupported(context.get(), request, &response);

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


bool ApiNetRenderManagerProxy::isEnabled()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::isEnabledRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::isEnabledResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->isEnabled(context.get(), request, &response);

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


void ApiNetRenderManagerProxy::saveConfiguration()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::saveConfigurationRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveConfiguration(context.get(), request, &response);

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


void ApiNetRenderManagerProxy::openOctanePreferences()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::openOctanePreferencesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->openOctanePreferences(context.get(), request, &response);

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


size_t ApiNetRenderManagerProxy::networkInterfaceCount()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::networkInterfaceCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::networkInterfaceCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->networkInterfaceCount(context.get(), request, &response);

    size_t retVal = 0;
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


Octane::NetInterfaceInfo ApiNetRenderManagerProxy::networkInterface(
            const size_t                              subnetIx //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::networkInterfaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'subnetIx' [in] parameter to the request packet.
    uint32_t subnetixIn;
    subnetixIn = static_cast<uint32_t>(subnetIx);////2 const size_t////
    request.set_subnetix(subnetixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::networkInterfaceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->networkInterface(context.get(), request, &response);

    Octane::NetInterfaceInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NetInterfaceInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        NetInterfaceInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =NetInterfaceInfo;////
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


void ApiNetRenderManagerProxy::setNetStatusListener(
            Octane::ApiNetRenderManager::OnStatusUpdateT callback, //// test821 //// 
            void *                                    userData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::setNetStatusListenerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::OnStatusUpdateT * callbackIn = new octaneapi::OnStatusUpdateT(); //// callback type=OnStatusUpdateT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("OnStatusUpdate"); 
    //CallbackStorage::registerOnStatusUpdate(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiNetRenderManager" && method.mName == "setNetStatusListener") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::setNetStatusListenerResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->setNetStatusListener(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnStatusUpdate( response.callbackid(), callback);
        CallbackStorage::registerOnStatusUpdate( response.callbackid(), callback);
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


Octane::NetRenderStatus ApiNetRenderManagerProxy::status()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::statusRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::statusResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->status(context.get(), request, &response);

    Octane::NetRenderStatus retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NetRenderStatus resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        NetRenderStatusConverter::convert(resultOut, retVal); ////Convert Called type 5223 =NetRenderStatus;////
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


void ApiNetRenderManagerProxy::setDaemonListener(
            Octane::ApiNetRenderManager::OnDaemonUpdateT callback, //// test821 //// 
            void *                                    userData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::setDaemonListenerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::OnDaemonUpdateT * callbackIn = new octaneapi::OnDaemonUpdateT(); //// callback type=OnDaemonUpdateT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("OnDaemonUpdate"); 
    //CallbackStorage::registerOnDaemonUpdate(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiNetRenderManager" && method.mName == "setDaemonListener") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'userData' [in] parameter to the request packet.
    uint64_t userdataIn;
    //// USER DATA TEST ////
    userdataIn = reinterpret_cast<uint64_t>(userData);
    request.set_userdata(userdataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::setDaemonListenerResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->setDaemonListener(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerOnDaemonUpdate( response.callbackid(), callback);
        CallbackStorage::registerOnDaemonUpdate( response.callbackid(), callback);
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


bool ApiNetRenderManagerProxy::bindDaemon(
            const Octane::IPv4T                       ipAddress //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::bindDaemonRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'ipAddress' [in] parameter to the request packet.
    uint32_t ipaddressIn;
    ipaddressIn = ipAddress;////2 const Octane::IPv4T////
    request.set_ipaddress(ipaddressIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::bindDaemonResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->bindDaemon(context.get(), request, &response);

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


void ApiNetRenderManagerProxy::unbindDaemon(
            const Octane::IPv4T                       ipAddress //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::unbindDaemonRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'ipAddress' [in] parameter to the request packet.
    uint32_t ipaddressIn;
    ipaddressIn = ipAddress;////2 const Octane::IPv4T////
    request.set_ipaddress(ipaddressIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->unbindDaemon(context.get(), request, &response);

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


bool ApiNetRenderManagerProxy::stealDaemon(
            const Octane::IPv4T                       ipAddress //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNetRenderManager::stealDaemonRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'ipAddress' [in] parameter to the request packet.
    uint32_t ipaddressIn;
    ipaddressIn = ipAddress;////2 const Octane::IPv4T////
    request.set_ipaddress(ipaddressIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNetRenderManager::stealDaemonResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNetRenderManagerService::Stub> stub = 
        octaneapi::ApiNetRenderManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->stealDaemon(context.get(), request, &response);

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


