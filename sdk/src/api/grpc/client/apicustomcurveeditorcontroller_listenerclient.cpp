// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apicustomcurveeditorcontroller_listenerclient.h"
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


namespace OctaneGRPC
{


GRPCSettings & ApiCustomCurveEditorControllerProxy_Listener::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiCustomCurveEditorControllerProxy_Listener::onVisualChange(
            bool                                      subCurveButtonsVisible,
            Octane::ApiCustomCurveEditorController::Button activeSubCurveButton,
            bool                                      deleteSelectedPointButtonEnabled,
            Octane::ApiCustomCurveEditorController::MouseCursorType mouseCursorType
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiCustomCurveEditorController::ApiCustomCurveEditorController_Listener::onVisualChangeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCustomCurveEditorController_Listener);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'subCurveButtonsVisible' [in] parameter to the request packet.
    bool subcurvebuttonsvisibleIn;
    subcurvebuttonsvisibleIn = subCurveButtonsVisible;
    request.set_subcurvebuttonsvisible(subcurvebuttonsvisibleIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'activeSubCurveButton' [in] parameter to the request packet.
    octaneapi::ApiCustomCurveEditorController_Button activesubcurvebuttonIn;
        activesubcurvebuttonIn = static_cast<octaneapi::ApiCustomCurveEditorController_Button>(activeSubCurveButton);
    request.set_activesubcurvebutton(activesubcurvebuttonIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'deleteSelectedPointButtonEnabled' [in] parameter to the request packet.
    bool deleteselectedpointbuttonenabledIn;
    deleteselectedpointbuttonenabledIn = deleteSelectedPointButtonEnabled;
    request.set_deleteselectedpointbuttonenabled(deleteselectedpointbuttonenabledIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'mouseCursorType' [in] parameter to the request packet.
    octaneapi::ApiCustomCurveEditorController_MouseCursorType mousecursortypeIn;
        mousecursortypeIn = static_cast<octaneapi::ApiCustomCurveEditorController_MouseCursorType>(mouseCursorType);
    request.set_mousecursortype(mousecursortypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiCustomCurveEditorController_ListenerService::Stub> stub =
        octaneapi::ApiCustomCurveEditorController_ListenerService::NewStub(getGRPCSettings().getChannel());
    status = stub->onVisualChange(context.get(), request, &response);

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


} //end of namespace
