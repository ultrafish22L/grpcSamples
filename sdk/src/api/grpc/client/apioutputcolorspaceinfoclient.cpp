// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apioutputcolorspaceinfoclient.h"
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
#include "apioutputcolorspaceinfo.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiOutputColorSpaceInfoProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiOutputColorSpaceInfoProxy ApiOutputColorSpaceInfoProxy::createKnownColorSpace(
            Octane::NamedColorSpace                   colorSpace,
            bool                                      forceToneMapping
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOutputColorSpaceInfo::createKnownColorSpaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'forceToneMapping' [in] parameter to the request packet.
    bool forcetonemappingIn;
    forcetonemappingIn = forceToneMapping;
    request.set_forcetonemapping(forcetonemappingIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOutputColorSpaceInfo::createKnownColorSpaceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOutputColorSpaceInfoService::Stub> stub =
        octaneapi::ApiOutputColorSpaceInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->createKnownColorSpace(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiOutputColorSpaceInfoProxy retVal;
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
        ApiOutputColorSpaceInfoProxy retVal;
        return retVal;
    }
};


ApiOutputColorSpaceInfoProxy ApiOutputColorSpaceInfoProxy::createOcioColorSpace(
            const char *                              colorSpaceName,
            const char *                              lookName,
            bool                                      forceToneMapping,
            Octane::ColorSpaceCurveType               curveType
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOutputColorSpaceInfo::createOcioColorSpaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpaceName' [in] parameter to the request packet.
    std::string * colorspacenameIn = new std::string();
    *colorspacenameIn = checkString(colorSpaceName);
    request.set_allocated_colorspacename(colorspacenameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'lookName' [in] parameter to the request packet.
    std::string * looknameIn = new std::string();
    *looknameIn = checkString(lookName);
    request.set_allocated_lookname(looknameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'forceToneMapping' [in] parameter to the request packet.
    bool forcetonemappingIn;
    forcetonemappingIn = forceToneMapping;
    request.set_forcetonemapping(forcetonemappingIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'curveType' [in] parameter to the request packet.
    octaneapi::ColorSpaceCurveType curvetypeIn;
    curvetypeIn = static_cast<octaneapi::ColorSpaceCurveType>(curveType);
    request.set_curvetype(curvetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOutputColorSpaceInfo::createOcioColorSpaceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOutputColorSpaceInfoService::Stub> stub =
        octaneapi::ApiOutputColorSpaceInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->createOcioColorSpace(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiOutputColorSpaceInfoProxy retVal;
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
        ApiOutputColorSpaceInfoProxy retVal;
        return retVal;
    }
};


ApiOutputColorSpaceInfoProxy ApiOutputColorSpaceInfoProxy::createOcioView(
            const char *                              displayName,
            const char *                              viewName,
            bool                                      useViewLook,
            const char *                              lookName,
            bool                                      forceToneMapping,
            Octane::ColorSpaceCurveType               curveType
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOutputColorSpaceInfo::createOcioViewRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'displayName' [in] parameter to the request packet.
    std::string * displaynameIn = new std::string();
    *displaynameIn = checkString(displayName);
    request.set_allocated_displayname(displaynameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'viewName' [in] parameter to the request packet.
    std::string * viewnameIn = new std::string();
    *viewnameIn = checkString(viewName);
    request.set_allocated_viewname(viewnameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'useViewLook' [in] parameter to the request packet.
    bool useviewlookIn;
    useviewlookIn = useViewLook;
    request.set_useviewlook(useviewlookIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'lookName' [in] parameter to the request packet.
    std::string * looknameIn = new std::string();
    *looknameIn = checkString(lookName);
    request.set_allocated_lookname(looknameIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'forceToneMapping' [in] parameter to the request packet.
    bool forcetonemappingIn;
    forcetonemappingIn = forceToneMapping;
    request.set_forcetonemapping(forcetonemappingIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'curveType' [in] parameter to the request packet.
    octaneapi::ColorSpaceCurveType curvetypeIn;
    curvetypeIn = static_cast<octaneapi::ColorSpaceCurveType>(curveType);
    request.set_curvetype(curvetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOutputColorSpaceInfo::createOcioViewResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOutputColorSpaceInfoService::Stub> stub =
        octaneapi::ApiOutputColorSpaceInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->createOcioView(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiOutputColorSpaceInfoProxy retVal;
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
        ApiOutputColorSpaceInfoProxy retVal;
        return retVal;
    }
};


ApiOutputColorSpaceInfoProxy ApiOutputColorSpaceInfoProxy::createUseImagerSettings(
            Octane::NamedColorSpace                   nonOcioColorSpace
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOutputColorSpaceInfo::createUseImagerSettingsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nonOcioColorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace nonociocolorspaceIn;
    nonociocolorspaceIn = static_cast<octaneapi::NamedColorSpace>(nonOcioColorSpace);
    request.set_nonociocolorspace(nonociocolorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOutputColorSpaceInfo::createUseImagerSettingsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOutputColorSpaceInfoService::Stub> stub =
        octaneapi::ApiOutputColorSpaceInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->createUseImagerSettings(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiOutputColorSpaceInfoProxy retVal;
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
        ApiOutputColorSpaceInfoProxy retVal;
        return retVal;
    }
};


void ApiOutputColorSpaceInfoProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOutputColorSpaceInfo::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOutputColorSpaceInfoService::Stub> stub =
        octaneapi::ApiOutputColorSpaceInfoService::NewStub(getGRPCSettings().getChannel());
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


ApiOutputColorSpaceInfoProxy ApiOutputColorSpaceInfoProxy::clone() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOutputColorSpaceInfo::cloneRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOutputColorSpaceInfo::cloneResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOutputColorSpaceInfoService::Stub> stub =
        octaneapi::ApiOutputColorSpaceInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->clone(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiOutputColorSpaceInfoProxy retVal;
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
        ApiOutputColorSpaceInfoProxy retVal;
        return retVal;
    }
};


bool ApiOutputColorSpaceInfoProxy::equals(
            const ApiOutputColorSpaceInfoProxy *      other
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiOutputColorSpaceInfo::equalsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'other' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * otherIn = new octaneapi::ObjectRef();
    otherIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOutputColorSpaceInfo);
    otherIn->set_handle(other->getObjectHandle());
    request.set_allocated_other(otherIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiOutputColorSpaceInfo::equalsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiOutputColorSpaceInfoService::Stub> stub =
        octaneapi::ApiOutputColorSpaceInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->equals(context.get(), request, &response);

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


