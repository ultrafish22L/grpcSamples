// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"


#include "apicustomcurveeditorcontroller.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiCustomCurveEditorController_Listener
class ApiCustomCurveEditorControllerProxy_Listener : public GRPCBase
{
public:
    /// Called when the editor needs to be redrawn, or any of the values passed as arguments
        /// have changed since this was last called. This should call draw (or request draw to be
        /// called soon) every time, and also update the state of buttons and the mouse cursor if
        /// they have changed.
        ///
        /// This will always be called on the same thread that's calling functions on the controller
        /// or making changes to the node.
        ///
        /// @param subCurveButtonsVisible
        ///     If true, the four "select sub curve" buttons should be visible (and enabled). If
        ///     false, they should be invisible.
        /// @param activeSubCurveButton
        ///     If subCurveButtonsVisible is true, this is the one of them that should be
        ///     highlighted in some way because it corresponds to the sub curve currently being
        ///     edited. Otherwise, this will always be SelectSubCurvePrimary and can be ignored.
        /// @param deleteSelectedPointButtonEnabled
        ///     If true, the "delete selected point" button should be enabled. If false, it should
        ///     be disabled because there is no point selected (but still visible, unless your UI
        ///     style calls for disabled buttons to always be invisible).
        /// @param mouseCursorType
        ///     The type of mouse cursor that should be used when the mouse is over the editor.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void onVisualChange(
            bool                                      subCurveButtonsVisible,
            Octane::ApiCustomCurveEditorController::Button activeSubCurveButton,
            bool                                      deleteSelectedPointButtonEnabled,
            Octane::ApiCustomCurveEditorController::MouseCursorType mouseCursorType
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
