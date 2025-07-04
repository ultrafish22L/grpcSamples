// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

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


GRPCSettings & ApiModalDialogProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiModalDialogProxy ApiModalDialogProxy::create(
            const char *                              dialogTitle //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string(); //// dialogTitle type=string;//// ////721////
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);//// 6215 ////

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
        ApiModalDialogProxy retVal;////714////
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModalDialog);////5////
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


void ApiModalDialogProxy::addContentComponent(
            ApiGuiComponentProxy &                    contentComponent //// last param ////
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModalDialog);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'contentComponent' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * contentcomponentIn = new octaneapi::ObjectRef();////761////
    contentcomponentIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);////5////
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModalDialog);////5////
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


void ApiModalDialogProxy::close(
            const int                                 retValue //// last param ////
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
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModalDialog);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'retValue' [in] parameter to the request packet.
    int32_t retvalueIn;
    retvalueIn = retValue;////2 const int////
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


void ApiModalDialogProxy::showInfoMessageDialog(
            const char *                              dialogTitle, //// test821 //// 
            const char *                              infoMessage //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showInfoMessageDialogRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string(); //// dialogTitle type=string;//// ////721////
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'infoMessage' [in] parameter to the request packet.
    std::string * infomessageIn = new std::string(); //// infoMessage type=string;//// ////721////
    *infomessageIn = checkString(infoMessage);
    request.set_allocated_infomessage(infomessageIn);//// 6215 ////

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


void ApiModalDialogProxy::showErrorMessageDialog(
            const char *                              dialogTitle, //// test821 //// 
            const char *                              errorMessage //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showErrorMessageDialogRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string(); //// dialogTitle type=string;//// ////721////
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'errorMessage' [in] parameter to the request packet.
    std::string * errormessageIn = new std::string(); //// errorMessage type=string;//// ////721////
    *errormessageIn = checkString(errorMessage);
    request.set_allocated_errormessage(errormessageIn);//// 6215 ////

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


bool ApiModalDialogProxy::showOkCancelDialog(
            const char *                              dialogTitle, //// test821 //// 
            const char *                              message, //// test821 //// 
            const char *                              okButtonText, //// test821 //// 
            const char *                              cancelButtonText //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showOkCancelDialogRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string(); //// dialogTitle type=string;//// ////721////
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'message' [in] parameter to the request packet.
    std::string * messageIn = new std::string(); //// message type=string;//// ////721////
    *messageIn = checkString(message);
    request.set_allocated_message(messageIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'okButtonText' [in] parameter to the request packet.
    std::string * okbuttontextIn = new std::string(); //// okButtonText type=string;//// ////721////
    *okbuttontextIn = checkString(okButtonText);
    request.set_allocated_okbuttontext(okbuttontextIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'cancelButtonText' [in] parameter to the request packet.
    std::string * cancelbuttontextIn = new std::string(); //// cancelButtonText type=string;//// ////721////
    *cancelbuttontextIn = checkString(cancelButtonText);
    request.set_allocated_cancelbuttontext(cancelbuttontextIn);//// 6215 ////

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


Octane::ApiModalDialog::DialogResult ApiModalDialogProxy::showYesNoCancelDialog(
            const char *                              dialogTitle, //// test821 //// 
            const char *                              message, //// test821 //// 
            const char *                              yesButtonText, //// test821 //// 
            const char *                              noButtonText, //// test821 //// 
            const char *                              cancelButtonText //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModalDialog::showYesNoCancelDialogRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'dialogTitle' [in] parameter to the request packet.
    std::string * dialogtitleIn = new std::string(); //// dialogTitle type=string;//// ////721////
    *dialogtitleIn = checkString(dialogTitle);
    request.set_allocated_dialogtitle(dialogtitleIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'message' [in] parameter to the request packet.
    std::string * messageIn = new std::string(); //// message type=string;//// ////721////
    *messageIn = checkString(message);
    request.set_allocated_message(messageIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'yesButtonText' [in] parameter to the request packet.
    std::string * yesbuttontextIn = new std::string(); //// yesButtonText type=string;//// ////721////
    *yesbuttontextIn = checkString(yesButtonText);
    request.set_allocated_yesbuttontext(yesbuttontextIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'noButtonText' [in] parameter to the request packet.
    std::string * nobuttontextIn = new std::string(); //// noButtonText type=string;//// ////721////
    *nobuttontextIn = checkString(noButtonText);
    request.set_allocated_nobuttontext(nobuttontextIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'cancelButtonText' [in] parameter to the request packet.
    std::string * cancelbuttontextIn = new std::string(); //// cancelButtonText type=string;//// ////721////
    *cancelbuttontextIn = checkString(cancelButtonText);
    request.set_allocated_cancelbuttontext(cancelbuttontextIn);//// 6215 ////

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


