// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apicustomcurveeditorcontrollerclient.h"
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
#include "apicustomcurveeditorcontroller.grpc.pb.h"
#include "apicustomcurveeditorcontroller_drawerclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiCustomCurveEditorControllerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiCustomCurveEditorControllerProxy::setBounds(
            OctaneVec::int32_2                        position,
            OctaneVec::int32_2                        size
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::setBoundsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'position' [in] parameter to the request packet.
    octaneapi::int32_2 * positionIn = new octaneapi::int32_2();
    (*positionIn).set_x(position.x);
    (*positionIn).set_y(position.y);
    request.set_allocated_position(positionIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'size' [in] parameter to the request packet.
    octaneapi::int32_2 * sizeIn = new octaneapi::int32_2();
    (*sizeIn).set_x(size.x);
    (*sizeIn).set_y(size.y);
    request.set_allocated_size(sizeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorControllerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorControllerService::NewStub(getGRPCSettings().getChannel());
    status = stub->setBounds(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy::onButtonClick(
            Octane::ApiCustomCurveEditorController::Button button
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::onButtonClickRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'button' [in] parameter to the request packet.
    octaneapi::ApiCustomCurveEditorController_Button buttonIn;
    buttonIn = static_cast<octaneapi::ApiCustomCurveEditorController_Button>(button);
    request.set_button(buttonIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorControllerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorControllerService::NewStub(getGRPCSettings().getChannel());
    status = stub->onButtonClick(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy::onKeyPress(
            Octane::ApiCustomCurveEditorController::Key key
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::onKeyPressRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'key' [in] parameter to the request packet.
    octaneapi::ApiCustomCurveEditorController_Key keyIn;
    keyIn = static_cast<octaneapi::ApiCustomCurveEditorController_Key>(key);
    request.set_key(keyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorControllerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorControllerService::NewStub(getGRPCSettings().getChannel());
    status = stub->onKeyPress(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy::onMouseMove(
            OctaneVec::float_2                        mousePosition
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::onMouseMoveRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'mousePosition' [in] parameter to the request packet.
    octaneapi::float_2 * mousepositionIn = new octaneapi::float_2();
    (*mousepositionIn).set_x(mousePosition.x);
    (*mousepositionIn).set_y(mousePosition.y);
    request.set_allocated_mouseposition(mousepositionIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorControllerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorControllerService::NewStub(getGRPCSettings().getChannel());
    status = stub->onMouseMove(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy::onMouseExit()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::onMouseExitRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorControllerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorControllerService::NewStub(getGRPCSettings().getChannel());
    status = stub->onMouseExit(context.get(), request, &response);

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


bool ApiCustomCurveEditorControllerProxy::onMouseDown(
            OctaneVec::float_2                        mousePosition,
            bool                                      leftButton
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::onMouseDownRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'mousePosition' [in] parameter to the request packet.
    octaneapi::float_2 * mousepositionIn = new octaneapi::float_2();
    (*mousepositionIn).set_x(mousePosition.x);
    (*mousepositionIn).set_y(mousePosition.y);
    request.set_allocated_mouseposition(mousepositionIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'leftButton' [in] parameter to the request packet.
    bool leftbuttonIn;
    leftbuttonIn = leftButton;
    request.set_leftbutton(leftbuttonIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiCustomCurveEditorController::onMouseDownResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorControllerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorControllerService::NewStub(getGRPCSettings().getChannel());
    status = stub->onMouseDown(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy::onMouseUp(
            OctaneVec::float_2                        mousePosition
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::onMouseUpRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'mousePosition' [in] parameter to the request packet.
    octaneapi::float_2 * mousepositionIn = new octaneapi::float_2();
    (*mousepositionIn).set_x(mousePosition.x);
    (*mousepositionIn).set_y(mousePosition.y);
    request.set_allocated_mouseposition(mousepositionIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorControllerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorControllerService::NewStub(getGRPCSettings().getChannel());
    status = stub->onMouseUp(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy::draw(
            ApiCustomCurveEditorControllerProxy_Drawer &drawer
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::drawRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'drawer' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * drawerIn = new octaneapi::ObjectRef();
    drawerIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
    drawerIn->set_handle(drawer.getObjectHandle());
    request.set_allocated_drawer(drawerIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorControllerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorControllerService::NewStub(getGRPCSettings().getChannel());
    status = stub->draw(context.get(), request, &response);

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


