// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apitexteditorclient.h"
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
#include "apitexteditor.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiTextEditorProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiTextEditorProxy ApiTextEditorProxy::create(
            const unsigned int                        nbOfLines,
            GRPCTextEditorChangedCallbackT           callback,
            void *                                    privateData
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextEditor::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nbOfLines' [in] parameter to the request packet.
    uint32_t nboflinesIn;
    nboflinesIn = nbOfLines;
    request.set_nboflines(nboflinesIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::TextEditorChangedCallbackT * callbackIn = new octaneapi::TextEditorChangedCallbackT();
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
    octaneapi::ApiTextEditor::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextEditorService::Stub> stub =
        octaneapi::ApiTextEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCTextEditorChangedCallback( response.callbackid(), callback);
        CallbackStorage::registerGRPCTextEditorChangedCallback( response.callbackid(), callback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiTextEditorProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
        return retVal;
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
        ApiTextEditorProxy retVal;
        return retVal;
    }
};


void ApiTextEditorProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextEditor::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextEditor);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextEditorService::Stub> stub =
        octaneapi::ApiTextEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->destroy(context.get(), request, &response);

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


std::string ApiTextEditorProxy::text() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextEditor::textRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextEditor);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextEditor::textResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextEditorService::Stub> stub =
        octaneapi::ApiTextEditorService::NewStub(getGRPCSettings().getChannel());
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


bool ApiTextEditorProxy::isEmpty() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextEditor::isEmptyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextEditor);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextEditor::isEmptyResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextEditorService::Stub> stub =
        octaneapi::ApiTextEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->isEmpty(context.get(), request, &response);

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


void ApiTextEditorProxy::setText(
            const char *                              newText,
            const bool                                sendEvent
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextEditor::setTextRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextEditor);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newText' [in] parameter to the request packet.
    std::string * newtextIn = new std::string();
    *newtextIn = checkString(newText);
    request.set_allocated_newtext(newtextIn);

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
    std::unique_ptr<octaneapi::ApiTextEditorService::Stub> stub =
        octaneapi::ApiTextEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->setText(context.get(), request, &response);

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


void ApiTextEditorProxy::clear()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextEditor::clearRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextEditor);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextEditorService::Stub> stub =
        octaneapi::ApiTextEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->clear(context.get(), request, &response);

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


void ApiTextEditorProxy::setReadOnly(
            const bool                                shouldBeReadOnly
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextEditor::setReadOnlyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextEditor);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'shouldBeReadOnly' [in] parameter to the request packet.
    bool shouldbereadonlyIn;
    shouldbereadonlyIn = shouldBeReadOnly;
    request.set_shouldbereadonly(shouldbereadonlyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextEditorService::Stub> stub =
        octaneapi::ApiTextEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->setReadOnly(context.get(), request, &response);

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


bool ApiTextEditorProxy::isReadOnly() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTextEditor::isReadOnlyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextEditor);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTextEditor::isReadOnlyResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTextEditorService::Stub> stub =
        octaneapi::ApiTextEditorService::NewStub(getGRPCSettings().getChannel());
    status = stub->isReadOnly(context.get(), request, &response);

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


} //end of namespace
