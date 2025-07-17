// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apitextbuttonclient.h"
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
#include "apitextbutton.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiTextButtonProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiTextButtonProxy ApiTextButtonProxy::create(
            const char *                              text,
            GRPCButtonClickedCallbackT               clickCallback,
            void *                                    privateData
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextButton::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'text' [in] parameter to the request packet.
    std::string * textIn = new std::string();
    *textIn = checkString(text);
    request.set_allocated_text(textIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'clickCallback' [in] parameter to the request packet.
    octaneapi::ButtonClickedCallbackT * clickcallbackIn = new octaneapi::ButtonClickedCallbackT();
    // setup callback function clickCallback
    clickcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_clickcallback(clickcallbackIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'privateData' [in] parameter to the request packet.
    uint64_t privatedataIn;
    privatedataIn = reinterpret_cast<uint64_t>(privateData);
    request.set_privatedata(privatedataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextButton::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextButtonService::Stub> stub =
        octaneapi::ApiTextButtonService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCButtonClickedCallback( response.callbackid(), clickCallback);
        CallbackStorage::registerGRPCButtonClickedCallback( response.callbackid(), clickCallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiTextButtonProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
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
        ApiTextButtonProxy retVal;
        return retVal;
    }
};


void ApiTextButtonProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextButton::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextButton);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextButtonService::Stub> stub =
        octaneapi::ApiTextButtonService::NewStub(getGRPCSettings().getChannel());
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


void ApiTextButtonProxy::setText(
            const char *                              text
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextButton::setTextRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextButton);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

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
    std::unique_ptr<octaneapi::ApiTextButtonService::Stub> stub =
        octaneapi::ApiTextButtonService::NewStub(getGRPCSettings().getChannel());
    status = stub->setText(context.get(), request, &response);

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


std::string ApiTextButtonProxy::text() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextButton::textRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextButton);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextButton::textResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextButtonService::Stub> stub =
        octaneapi::ApiTextButtonService::NewStub(getGRPCSettings().getChannel());
    status = stub->text(context.get(), request, &response);

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


