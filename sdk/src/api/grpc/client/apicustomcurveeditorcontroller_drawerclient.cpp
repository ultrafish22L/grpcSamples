// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apicustomcurveeditorcontroller_drawerclient.h"
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
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiCustomCurveEditorControllerProxy_Drawer::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiCustomCurveEditorControllerProxy_Drawer::setColor(
            Octane::ApiCustomCurveEditorController::Drawer::Color color,
            float                                     opacity
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::setColorRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'color' [in] parameter to the request packet.
    octaneapi::ApiCustomCurveEditorController_ApiCustomCurveEditorController_Drawer_Color colorIn;
    colorIn = static_cast<octaneapi::ApiCustomCurveEditorController_ApiCustomCurveEditorController_Drawer_Color>(color);
    request.set_color(colorIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'opacity' [in] parameter to the request packet.
    float opacityIn;
    opacityIn = opacity;
    request.set_opacity(opacityIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->setColor(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy_Drawer::setClipRegionAndFillBackground(
            OctaneVec::int32_2                        position,
            OctaneVec::int32_2                        size,
            int                                       cornerRadius
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::setClipRegionAndFillBackgroundRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
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
    // Add the 'cornerRadius' [in] parameter to the request packet.
    int32_t cornerradiusIn;
    cornerradiusIn = cornerRadius;
    request.set_cornerradius(cornerradiusIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->setClipRegionAndFillBackground(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy_Drawer::drawRectangle(
            OctaneVec::int32_2                        position,
            OctaneVec::int32_2                        size
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::drawRectangleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
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
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->drawRectangle(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy_Drawer::fillRectangle(
            OctaneVec::int32_2                        position,
            OctaneVec::int32_2                        size
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::fillRectangleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
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
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->fillRectangle(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy_Drawer::fillCircle(
            OctaneVec::float_2                        center,
            float                                     radius
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::fillCircleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'center' [in] parameter to the request packet.
    octaneapi::float_2 * centerIn = new octaneapi::float_2();
    (*centerIn).set_x(center.x);
    (*centerIn).set_y(center.y);
    request.set_allocated_center(centerIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'radius' [in] parameter to the request packet.
    float radiusIn;
    radiusIn = radius;
    request.set_radius(radiusIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->fillCircle(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy_Drawer::startPath(
            OctaneVec::float_2                        point
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::startPathRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'point' [in] parameter to the request packet.
    octaneapi::float_2 * pointIn = new octaneapi::float_2();
    (*pointIn).set_x(point.x);
    (*pointIn).set_y(point.y);
    request.set_allocated_point(pointIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->startPath(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy_Drawer::lineTo(
            OctaneVec::float_2                        point
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::lineToRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'point' [in] parameter to the request packet.
    octaneapi::float_2 * pointIn = new octaneapi::float_2();
    (*pointIn).set_x(point.x);
    (*pointIn).set_y(point.y);
    request.set_allocated_point(pointIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->lineTo(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy_Drawer::cubicBezierTo(
            OctaneVec::float_2                        controlPoint0,
            OctaneVec::float_2                        controlPoint1,
            OctaneVec::float_2                        point
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::cubicBezierToRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'controlPoint0' [in] parameter to the request packet.
    octaneapi::float_2 * controlpoint0In = new octaneapi::float_2();
    (*controlpoint0In).set_x(controlPoint0.x);
    (*controlpoint0In).set_y(controlPoint0.y);
    request.set_allocated_controlpoint0(controlpoint0In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'controlPoint1' [in] parameter to the request packet.
    octaneapi::float_2 * controlpoint1In = new octaneapi::float_2();
    (*controlpoint1In).set_x(controlPoint1.x);
    (*controlpoint1In).set_y(controlPoint1.y);
    request.set_allocated_controlpoint1(controlpoint1In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'point' [in] parameter to the request packet.
    octaneapi::float_2 * pointIn = new octaneapi::float_2();
    (*pointIn).set_x(point.x);
    (*pointIn).set_y(point.y);
    request.set_allocated_point(pointIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->cubicBezierTo(context.get(), request, &response);

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


void ApiCustomCurveEditorControllerProxy_Drawer::finishPath(
            float                                     thickness
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Drawer::finishPathRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Drawer);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'thickness' [in] parameter to the request packet.
    float thicknessIn;
    thicknessIn = thickness;
    request.set_thickness(thicknessIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_DrawerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_DrawerService::NewStub(getGRPCSettings().getChannel());
    status = stub->finishPath(context.get(), request, &response);

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


