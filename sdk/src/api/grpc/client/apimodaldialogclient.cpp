// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apimodaldialogclient.h"
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
#include "apimodaldialog.grpc.pb.h"
#include "apiguicomponentclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiModalDialogProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiModalDialogProxy ApiModalDialogProxy::create(
            const char *                              dialogTitle
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string();
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModalDialog::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiModalDialogProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());
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
        ApiModalDialogProxy retVal;
        return retVal;
    }
};


void ApiModalDialogProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModalDialog);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
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


void ApiModalDialogProxy::addContentComponent(
            ApiGuiComponentProxy &                    contentComponent
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::addContentComponentRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModalDialog);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'contentComponent' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * contentcomponentIn = new octaneapi::ObjectRef();
    contentcomponentIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    contentcomponentIn->set_handle(contentComponent.getObjectHandle());
    request.set_allocated_contentcomponent(contentcomponentIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
    status = stub->addContentComponent(context.get(), request, &response);

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


int ApiModalDialogProxy::show()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModalDialog);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModalDialog::showResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
    status = stub->show(context.get(), request, &response);

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


void ApiModalDialogProxy::close(
            const int                                 retValue
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::closeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModalDialog);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'retValue' [in] parameter to the request packet.
    int32_t retvalueIn;
    retvalueIn = retValue;
    request.set_retvalue(retvalueIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
    status = stub->close(context.get(), request, &response);

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


void ApiModalDialogProxy::showInfoMessageDialog(
            const char *                              dialogTitle,
            const char *                              infoMessage
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showInfoMessageDialogRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string();
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'infoMessage' [in] parameter to the request packet.
    std::string * infomessageIn = new std::string();
    *infomessageIn = checkString(infoMessage);
    request.set_allocated_infomessage(infomessageIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
    status = stub->showInfoMessageDialog(context.get(), request, &response);

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


void ApiModalDialogProxy::showErrorMessageDialog(
            const char *                              dialogTitle,
            const char *                              errorMessage
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showErrorMessageDialogRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string();
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'errorMessage' [in] parameter to the request packet.
    std::string * errormessageIn = new std::string();
    *errormessageIn = checkString(errorMessage);
    request.set_allocated_errormessage(errormessageIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
    status = stub->showErrorMessageDialog(context.get(), request, &response);

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


bool ApiModalDialogProxy::showOkCancelDialog(
            const char *                              dialogTitle,
            const char *                              message,
            const char *                              okButtonText,
            const char *                              cancelButtonText
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showOkCancelDialogRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string();
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'message' [in] parameter to the request packet.
    std::string * messageIn = new std::string();
    *messageIn = checkString(message);
    request.set_allocated_message(messageIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'okButtonText' [in] parameter to the request packet.
    std::string * okbuttontextIn = new std::string();
    *okbuttontextIn = checkString(okButtonText);
    request.set_allocated_okbuttontext(okbuttontextIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cancelButtonText' [in] parameter to the request packet.
    std::string * cancelbuttontextIn = new std::string();
    *cancelbuttontextIn = checkString(cancelButtonText);
    request.set_allocated_cancelbuttontext(cancelbuttontextIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModalDialog::showOkCancelDialogResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
    status = stub->showOkCancelDialog(context.get(), request, &response);

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


Octane::ApiModalDialog::DialogResult ApiModalDialogProxy::showYesNoCancelDialog(
            const char *                              dialogTitle,
            const char *                              message,
            const char *                              yesButtonText,
            const char *                              noButtonText,
            const char *                              cancelButtonText
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showYesNoCancelDialogRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string();
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'message' [in] parameter to the request packet.
    std::string * messageIn = new std::string();
    *messageIn = checkString(message);
    request.set_allocated_message(messageIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'yesButtonText' [in] parameter to the request packet.
    std::string * yesbuttontextIn = new std::string();
    *yesbuttontextIn = checkString(yesButtonText);
    request.set_allocated_yesbuttontext(yesbuttontextIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'noButtonText' [in] parameter to the request packet.
    std::string * nobuttontextIn = new std::string();
    *nobuttontextIn = checkString(noButtonText);
    request.set_allocated_nobuttontext(nobuttontextIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cancelButtonText' [in] parameter to the request packet.
    std::string * cancelbuttontextIn = new std::string();
    *cancelbuttontextIn = checkString(cancelButtonText);
    request.set_allocated_cancelbuttontext(cancelbuttontextIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModalDialog::showYesNoCancelDialogResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModalDialogService::Stub> stub =
        octaneapi::ApiModalDialogService::NewStub(getGRPCSettings().getChannel());
    status = stub->showYesNoCancelDialog(context.get(), request, &response);

    Octane::ApiModalDialog::DialogResult retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiModalDialog_DialogResult resultOut = response.result();
        retVal = static_cast<Octane::ApiModalDialog::DialogResult>(resultOut);
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
