// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apicheckboxclient.h"
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
#include "apicheckbox.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiCheckBoxProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiCheckBoxProxy ApiCheckBoxProxy::create(
            const char *                              text,
            GRPCCheckedCallbackT                     callback,
            void *                                    privateData
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCheckBox::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'text' [in] parameter to the request packet.
    std::string * textIn = new std::string();
    *textIn = checkString(text);
    request.set_allocated_text(textIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::CheckedCallbackT * callbackIn = new octaneapi::CheckedCallbackT();
    // setup callback function callback
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_callback(callbackIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'privateData' [in] parameter to the request packet.
    uint64_t privatedataIn;
    privatedataIn = reinterpret_cast<uint64_t>(privateData);
    request.set_privatedata(privatedataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCheckBox::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCheckBoxService::Stub> stub =
        octaneapi::ApiCheckBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCCheckedCallback( response.callbackid(), callback);
        CallbackStorage::registerGRPCCheckedCallback( response.callbackid(), callback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiCheckBoxProxy retVal;
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
        ApiCheckBoxProxy retVal;
        return retVal;
    }
};


void ApiCheckBoxProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCheckBox::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCheckBox);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCheckBoxService::Stub> stub =
        octaneapi::ApiCheckBoxService::NewStub(getGRPCSettings().getChannel());
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


void ApiCheckBoxProxy::setChecked(
            const bool                                checked,
            const bool                                sendEvent
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCheckBox::setCheckedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCheckBox);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'checked' [in] parameter to the request packet.
    bool checkedIn;
    checkedIn = checked;
    request.set_checked(checkedIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sendEvent' [in] parameter to the request packet.
    bool sendeventIn;
    sendeventIn = sendEvent;
    request.set_sendevent(sendeventIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCheckBoxService::Stub> stub =
        octaneapi::ApiCheckBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->setChecked(context.get(), request, &response);

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


bool ApiCheckBoxProxy::isChecked() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCheckBox::isCheckedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCheckBox);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCheckBox::isCheckedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCheckBoxService::Stub> stub =
        octaneapi::ApiCheckBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->isChecked(context.get(), request, &response);

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


