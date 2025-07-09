// Copyright (C) 2025 OTOY NZ Ltd.

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
class ApiCustomCurveEditorControllerProxy_Drawer;


#include "apicustomcurveeditorcontroller.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiCustomCurveEditorController
class ApiCustomCurveEditorControllerProxy : public GRPCBase
{
public:
    /// Sets the position and size of the editor within some parent.
    ///
    /// @param position
    ///     The position of the editor. This has no meaning to this class itself, except that all
    ///     other coordinates used for input and output must/will include this offset.
    /// @param size
    ///     The size of the editor.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setBounds(
            OctaneVec::int32_2                        position,
            OctaneVec::int32_2                        size
            );

    /// Called when a button that works with the editor is clicked. This should be called on logical
    /// button click, which would normally be mouse down + mouse up, or spacebar.
    ///
    /// @param button
    ///     The button that was clicked.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void onButtonClick(
            Octane::ApiCustomCurveEditorController::Button button
            );

    /// Called when a key that works with the editor is pressed when the editor has keyboard focus.
    /// This should be called on key down, including key repeat.
    ///
    /// @param key
    ///     The key that was pressed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void onKeyPress(
            Octane::ApiCustomCurveEditorController::Key key
            );

    /// Called when the mouse is moved. If this controller currently thinks a mouse button is down
    /// (i.e. between a call to onMouseDown that returned true and the corresponding onMouseUp),
    /// this should be called for every mouse movement regardless of where the mouse is. Otherwise,
    /// this only needs to be called when the mouse moves to a position that's potentially over the
    /// editor.
    ///
    /// @param mousePosition
    ///     The new mouse position.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void onMouseMove(
            OctaneVec::float_2                        mousePosition
            );

    /// Called when the mouse is moved to a position that's definitely not over the editor, so the
    /// last given position is no longer valid.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void onMouseExit(            );

    /// Called when a mouse button is pressed when the mouse is at a position that's potentially
    /// over the editor.
    ///
    /// @param mousePosition
    ///     The mouse position.
    /// @param leftButton
    ///     True if the mouse button that went down is the (logical) left mouse button. False if
    ///     it's some other button.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     True if this controller handled the event; false if it was not handled because it
    ///     occurred outside the clickable bounds of the editor and it can be propagated to a parent
    ///     or whatever is "behind" the editor.
    bool onMouseDown(
            OctaneVec::float_2                        mousePosition,
            bool                                      leftButton
            );

    /// Called when a mouse button is released. If the corresponding press caused a call to
    /// onMouseDown that returned true, this must be called on release, regardless of where the
    /// mouse is now. Otherwise this does not need to be (but still may be) called.
    ///
    /// @param mousePosition
    ///     The mouse position.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void onMouseUp(
            OctaneVec::float_2                        mousePosition
            );

    /// Draws the editor, using the provided drawer.
    ///
    /// @param drawer
    ///     The drawer to use to do the actual drawing. This will not be accessed after this
    ///     function returns.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void draw(
            ApiCustomCurveEditorControllerProxy_Drawer &drawer
            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
