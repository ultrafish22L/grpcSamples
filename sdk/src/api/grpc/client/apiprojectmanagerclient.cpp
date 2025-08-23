// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apiprojectmanagerclient.h"
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
#include "apiprojectmanager.grpc.pb.h"
#include "apinodeclient.h"
#include "apirootnodegraphclient.h"
#include "grpcchangeevents.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertreferencepackageexportsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiProjectManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiProjectManagerProxy::isValid()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::isValidRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::isValidResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->isValid(context.get(), request, &response);

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


ApiRootNodeGraphProxy ApiProjectManagerProxy::rootNodeGraph()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::rootNodeGraphRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::rootNodeGraphResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->rootNodeGraph(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiRootNodeGraphProxy retVal;
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
        ApiRootNodeGraphProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiProjectManagerProxy::applicationPreferences()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::applicationPreferencesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::applicationPreferencesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->applicationPreferences(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeProxy retVal;
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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiProjectManagerProxy::projectSettings()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::projectSettingsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::projectSettingsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->projectSettings(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeProxy retVal;
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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiProjectManagerProxy::projectMetadata()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::projectMetadataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::projectMetadataResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->projectMetadata(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeProxy retVal;
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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiProjectManagerProxy::previewRenderTarget()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::previewRenderTargetRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::previewRenderTargetResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->previewRenderTarget(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeProxy retVal;
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
        ApiNodeProxy retVal;
        return retVal;
    }
};


ApiNodeProxy ApiProjectManagerProxy::materialBall()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::materialBallRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::materialBallResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->materialBall(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeProxy retVal;
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
        ApiNodeProxy retVal;
        return retVal;
    }
};


std::string ApiProjectManagerProxy::getCurrentProject()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::getCurrentProjectRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::getCurrentProjectResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->getCurrentProject(context.get(), request, &response);

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


bool ApiProjectManagerProxy::resetProject()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::resetProjectRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::resetProjectResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->resetProject(context.get(), request, &response);

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


bool ApiProjectManagerProxy::loadProject(
            const char *                              projectPath,
            Octane::AssetMissingCallbackT             assetMissingcallback,
            void *                                    assetMissinguserData,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::loadProjectRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'projectPath' [in] parameter to the request packet.
    std::string * projectpathIn = new std::string();
    *projectpathIn = checkString(projectPath);
    request.set_allocated_projectpath(projectpathIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetMissingcallback' [in] parameter to the request packet.
    octaneapi::AssetMissingCallbackT * assetmissingcallbackIn = new octaneapi::AssetMissingCallbackT();
    // setup callback function assetMissingcallback
        assetmissingcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_assetmissingcallback(assetmissingcallbackIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'assetMissinguserData' [in] parameter to the request packet.
    uint64_t assetmissinguserdataIn;
    assetmissinguserdataIn = reinterpret_cast<uint64_t>(assetMissinguserData);
    request.set_assetmissinguserdata(assetmissinguserdataIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::loadProjectResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->loadProject(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        // set callback Id CallbackStorage::registerAssetMissingCallback( response.callbackid(), assetMissingcallback);
        CallbackStorage::registerAssetMissingCallback( response.callbackid(), assetMissingcallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;

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


bool ApiProjectManagerProxy::loadedFromPackage()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::loadedFromPackageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::loadedFromPackageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->loadedFromPackage(context.get(), request, &response);

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


Octane::VersionT ApiProjectManagerProxy::loadedOcsVersion()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::loadedOcsVersionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::loadedOcsVersionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->loadedOcsVersion(context.get(), request, &response);

    Octane::VersionT retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint32_t resultOut = response.result();
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


bool ApiProjectManagerProxy::saveProject()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::saveProjectRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::saveProjectResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveProject(context.get(), request, &response);

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


bool ApiProjectManagerProxy::saveProjectAs(
            const char *                              path
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::saveProjectAsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    std::string * pathIn = new std::string();
    *pathIn = checkString(path);
    request.set_allocated_path(pathIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::saveProjectAsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveProjectAs(context.get(), request, &response);

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


bool ApiProjectManagerProxy::saveProjectAsReferencePackage(
            const char *                              path,
            const Octane::ReferencePackageExportSettings & referencePackageSettings
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::saveProjectAsReferencePackageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    std::string * pathIn = new std::string();
    *pathIn = checkString(path);
    request.set_allocated_path(pathIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'referencePackageSettings' [in] parameter to the request packet.
    octaneapi::ReferencePackageExportSettings * referencepackagesettingsIn = new octaneapi::ReferencePackageExportSettings();
    ReferencePackageExportSettingsConverter::convert(referencePackageSettings, *referencepackagesettingsIn);
    request.set_allocated_referencepackagesettings(referencepackagesettingsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::saveProjectAsReferencePackageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->saveProjectAsReferencePackage(context.get(), request, &response);

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


bool ApiProjectManagerProxy::unpackPackage(
            const char *                              unpackDir,
            const char *                              packagePath,
            const char *                              unpackName
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::unpackPackageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'unpackDir' [in] parameter to the request packet.
    std::string * unpackdirIn = new std::string();
    *unpackdirIn = checkString(unpackDir);
    request.set_allocated_unpackdir(unpackdirIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'packagePath' [in] parameter to the request packet.
    std::string * packagepathIn = new std::string();
    *packagepathIn = checkString(packagePath);
    request.set_allocated_packagepath(packagepathIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'unpackName' [in] parameter to the request packet.
    std::string * unpacknameIn = new std::string();
    *unpacknameIn = checkString(unpackName);
    request.set_allocated_unpackname(unpacknameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::unpackPackageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->unpackPackage(context.get(), request, &response);

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


void ApiProjectManagerProxy::addObserver(
            GRPCProjectManagerObserver               observer
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::addObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCProjectManagerObserverT * observerIn = new octaneapi::GRPCProjectManagerObserverT();
    // setup observer function observer
    //int observerCallbackId = GRPCSettings::getNextCallbackId("GRPCProjectManagerObserver");
    //CallbackStorage::registerGRPCProjectManagerObserver(observerCallbackId, observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //observerIn->set_callbackid(observerCallbackId);
observerIn->set_userdata(reinterpret_cast<uint64_t>(observer.mUserData));
    //if(className == "ApiProjectManager" && method.mName == "addObserver") return true;
    request.set_allocated_observer(observerIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiProjectManager::addObserverResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->addObserver(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCProjectManagerObserver( response.callbackid(), observer.mCallback);
        CallbackStorage::registerGRPCProjectManagerObserver( response.callbackid(), observer.mCallback);
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


void ApiProjectManagerProxy::removeObserver(
            GRPCProjectManagerObserver               removeObserver
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiProjectManager::removeObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'removeObserver' [in] parameter to the request packet.
    octaneapi::GRPCProjectManagerObserverT * removeobserverIn = new octaneapi::GRPCProjectManagerObserverT();
    // remove observer function removeObserver
    int removeObserverCallbackId = CallbackStorage::unregisterGRPCProjectManagerObserver(removeObserver.mCallback);
    //octaneapi::OnChangeT * removeObserverchangeT = new octaneapi::OnChangeT();
    //removeObserverchangeT->set_callbackid(removeObserverCallbackId);
    removeobserverIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
   removeobserverIn->set_callbackid(removeObserverCallbackId);
    request.set_allocated_removeobserver(removeobserverIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiProjectManagerService::Stub> stub =
        octaneapi::ApiProjectManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeObserver(context.get(), request, &response);

    if (status.ok())
    {
        // free callbackId
        // GRPCSettings::releaseCallbackId("GRPCProjectManagerObserver", response.callbackid());
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
