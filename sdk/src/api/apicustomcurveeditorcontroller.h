// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include "octanevectypes.h"


namespace Octane
{

class ApiNode;

/// Handles all the logic for a custom curve editor UI component, while abstracting out the input
/// and drawing so it can be used with any UI framework.
///
/// Coordinate system:
///   * X increases to the right, Y increases down.
///   * Integer coordinates are at pixel corners; if setBounds is called with position = (5, 5) and
///     size = (10, 10) then the top left corner of the top left pixel of the editor is (5.0, 5.0)
///     and the bottom right corner of the bottom right pixel of the editor is (15.0, 15.0).
///   * All coordinates used on the interface are logical pixels; if you are working with physical
///     pixels on a high-DPI screen then you should divide all coordinates passed to this class by
///     the pixel scale factor and multiply all coordinates passed back during drawing by the pixel
///     scale factor.
class OCTANEAPI_DECL ApiCustomCurveEditorController final
{
public:

    /// Identifies a button that works with the editor.
    enum class Button
    {
        /// The button to make the primary sub curve active. This button should only be visible
        /// sometimes; see Listener::onVisualChange.
        ///
        /// Suggested icon: A white S-shaped curve.
        /// Suggested tooltip: "Edit primary sub curve".
        SelectSubCurvePrimary,
        /// The button to make the secondary red sub curve active. This button should only be
        /// visible sometimes; see Listener::onVisualChange.
        ///
        /// Suggested icon: A red S-shaped curve, slightly smaller than the primary one.
        /// Suggested tooltip: "Edit red secondary sub curve".
        SelectSubCurveSecondaryRed,
        /// The button to make the secondary green sub curve active. This button should only be
        /// visible sometimes; see Listener::onVisualChange.
        ///
        /// Suggested icon: A green S-shaped curve, slightly smaller than the primary one.
        /// Suggested tooltip: "Edit green secondary sub curve".
        SelectSubCurveSecondaryGreen,
        /// The button to make the secondary blue sub curve active. This button should only be
        /// visible sometimes; see Listener::onVisualChange.
        ///
        /// Suggested icon: A blue S-shaped curve, slightly smaller than the primary one.
        /// Suggested tooltip: "Edit blue secondary sub curve".
        SelectSubCurveSecondaryBlue,
        /// The button to delete any selected control point. This button should only be enabled
        /// sometimes; see Listener::onVisualChange.
        ///
        /// Suggested icon: A diagonal straight line, with a filled circle in the middle with a
        /// small minus symbol next to it.
        /// Suggested tooltip: "Delete control point".
        DeletePoint,
        /// The button to reset control points. This button should always be enabled.
        ///
        /// Suggested icon: A diagonal straight line, with an unfilled circle at each end.
        /// Suggested tooltip: "Reset curve".
        Reset,
    };

    /// Identifies a key that works with the editor.
    enum class Key
    {
        /// The delete key.
        Delete,
        /// The up arrow key.
        Up,
        /// The down arrow key.
        Down,
        /// The left arrow key.
        Left,
        /// The right arrow key.
        Right,
    };

    /// Identifies a mouse cursor appearance to use when the mouse is over the editor.
    enum class MouseCursorType
    {
        /// The normal/default cursor, e.g. an arrow.
        Normal,
        /// The cursor to use when clicking will add a new control point, e.g. crosshairs.
        PlacePoint,
        /// The cursor to use when clicking/dragging will select/move an existing control point,
        /// e.g. a four-way resize/move arrow.
        MovePoint,
    };

    /// Listener interface to be informed of changes to the editor state.
    class Listener
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
        virtual void onVisualChange(
            bool subCurveButtonsVisible,
            Button activeSubCurveButton,
            bool deleteSelectedPointButtonEnabled,
            MouseCursorType mouseCursorType) = 0;

    };

    /// Interface passed to draw to receive drawing commands to actually draw the editor. All
    /// functions on this will always be called during a call to draw, on the same thread that's
    /// calling draw.
    class Drawer
    {
    public:

        /// Identifies a color that can be used.
        enum class Color
        {
            /// Color of the background that fills the visual bounds of the editor.
            ///
            /// Suggested color (8-bit sRGB): #252525.
            Background,
            /// Color of the lines making up the grid that covers the logical bounds of the editor.
            ///
            /// Suggested color (8-bit sRGB): #333333.
            Grid,
            /// Color of the primary sub curve and any dots on it. This should be the same color as
            /// the "select primary sub curve" button icon.
            ///
            /// Suggested color (8-bit sRGB): #ffffff.
            SubCurvePrimary,
            /// Color of the secondary red sub curve and any dots on it. This should be the same
            /// color as the "select secondary red sub curve" button icon.
            ///
            /// Suggested color (8-bit sRGB): #ff0000.
            SubCurveSecondaryRed,
            /// Color of the secondary green sub curve and any dots on it. This should be the same
            /// color as the "select secondary green sub curve" button icon.
            ///
            /// Suggested color (8-bit sRGB): #00ff00.
            SubCurveSecondaryGreen,
            /// Color of the secondary blue sub curve and any dots on it. This should be the same
            /// color as the "select secondary blue sub curve" button icon.
            ///
            /// Suggested color (8-bit sRGB): #2663ff. (#0000ff is a dark color which is very hard
            /// to see on a gray background so we can take some creative liberty with the color.
            /// This lies on a straight line in the Oklab color space between sRGB blue and white.)
            SubCurveSecondaryBlue,
        };


        /// Sets the color and opacity to use for future drawing commands. This will always be
        /// called before the first drawing command in a draw operation.
        ///
        /// @param color
        ///     The color to use.
        /// @param opacity
        ///     The opacity to use. This will always be in the range [0, 1].
        virtual void setColor(
            Color color,
            float opacity) = 0;

        /// Sets the clip region to an antialiased rounded rectangle (if possible; if not then an
        /// aliased rounded rectangle or just a non-rounded rectangle is OK) and then fills with the
        /// current color. All future drawing commands in the draw operation must have no effect on
        /// pixels outside the clip region.
        ///
        /// Notes to potentially make implementation easier: This will be called no more than once
        /// per draw operation, and will be the first function called (except for setColor). If this
        /// is not called then no other functions will be. The opacity will always be 1 when this is
        /// called.
        ///
        /// @param position
        ///     The top left corner of the clip region.
        /// @param size
        ///     The size of the clip region.
        /// @param cornerRadius
        ///     Radius of the rounded corners of the clip region.
        virtual void setClipRegionAndFillBackground(
            int32_2 position,
            int32_2 size,
            int cornerRadius) = 0;

        /// Draws the border of a rectangle, one pixel thick. The thickness is inset into the
        /// rectangle, that is, if size is (3, 3) eight pixels will be colored and one in the middle
        /// left untouched.
        ///
        /// Notes to potentially make implementation easier: The opacity will always be 1 when this
        /// is called.
        ///
        /// @param position
        ///     The top left corner of the rectangle.
        /// @param size
        ///     The size of the rectangle.
        virtual void drawRectangle(
            int32_2 position,
            int32_2 size) = 0;

        /// Fills a rectangle.
        ///
        /// Notes to potentially make implementation easier: The opacity will always be 1 when this
        /// is called.
        ///
        /// @param position
        ///     The top left corner of the rectangle.
        /// @param size
        ///     The size of the rectangle.
        virtual void fillRectangle(
            int32_2 position,
            int32_2 size) = 0;

        /// Fills a circle.
        ///
        /// @param center
        ///     The center of the circle.
        /// @param radius
        ///     The radius of the circle.
        virtual void fillCircle(
            float_2 center,
            float radius) = 0;

        /// Starts building a path to be drawn later when finishPath is called. Every call to this
        /// will have a matching call to finishPath, and no functions except lineTo and cubicTo will
        /// be called between this and the matching call to finishPath.
        ///
        /// @param point
        ///     The initial "previous" point of the path.
        virtual void startPath(
            float_2 point) = 0;

        /// Adds to the current path a line from the previous point to the given end point, and then
        /// sets the previous point to the end point of the line.
        ///
        /// @param point
        ///     The end point of the line.
        virtual void lineTo(
            float_2 point) = 0;

        /// Adds to the current path a cubic Bezier curve from the previous point to the given end
        /// point (using the two given control points), and then sets the previous point to the end
        /// point of the curve.
        ///
        /// @param controlPoint0
        ///     The first control point.
        /// @param controlPoint1
        ///     The second control point.
        /// @param point
        ///     The end point of the curve.
        virtual void cubicBezierTo(
            float_2 controlPoint0,
            float_2 controlPoint1,
            float_2 point) = 0;

        /// Draws the path that has been built up by calls to startPath/lineTo/cubicTo, and clears
        /// the path ready to possibly start a new one from scratch.
        ///
        /// @param thickness
        ///     The thickness of the path.
        virtual void finishPath(
            float thickness) = 0;

    };


    /// Starts the controller watching for changes to the node and calls the listener with initial
    /// values.
    ///
    /// @param node
    ///     The node holding the custom curve to edit. This must be of node type
    ///     NT_OUTPUT_AOV_LAYER_APPLY_CUSTOM_CURVE or NT_TEX_COMPOSITE_LAYER_APPLY_CUSTOM_CURVE.
    ///     This reference must remain valid until after this object is destroyed.
    /// @param listener
    ///     The listener to be notified of visual changes. This will be called for the first time
    ///     before this constructor returns. This reference must remain valid until after this
    ///     object is destroyed.
    ApiCustomCurveEditorController(
        ApiNode & node,
        Listener & listener);

    /// Does not call the listener. This listener will not be called after this.
    ~ApiCustomCurveEditorController();

    /// Sets the position and size of the editor within some parent.
    ///
    /// @param position
    ///     The position of the editor. This has no meaning to this class itself, except that all
    ///     other coordinates used for input and output must/will include this offset.
    /// @param size
    ///     The size of the editor.
    void setBounds(
        int32_2 position,
        int32_2 size);

    /// Called when a button that works with the editor is clicked. This should be called on logical
    /// button click, which would normally be mouse down + mouse up, or spacebar.
    ///
    /// @param button
    ///     The button that was clicked.
    void onButtonClick(
        Button button);

    /// Called when a key that works with the editor is pressed when the editor has keyboard focus.
    /// This should be called on key down, including key repeat.
    ///
    /// @param key
    ///     The key that was pressed.
    void onKeyPress(
        Key key);

    /// Called when the mouse is moved. If this controller currently thinks a mouse button is down
    /// (i.e. between a call to onMouseDown that returned true and the corresponding onMouseUp),
    /// this should be called for every mouse movement regardless of where the mouse is. Otherwise,
    /// this only needs to be called when the mouse moves to a position that's potentially over the
    /// editor.
    ///
    /// @param mousePosition
    ///     The new mouse position.
    void onMouseMove(
        float_2 mousePosition);

    /// Called when the mouse is moved to a position that's definitely not over the editor, so the
    /// last given position is no longer valid.
    void onMouseExit();

    /// Called when a mouse button is pressed when the mouse is at a position that's potentially
    /// over the editor.
    ///
    /// @param mousePosition
    ///     The mouse position.
    /// @param leftButton
    ///     True if the mouse button that went down is the (logical) left mouse button. False if
    ///     it's some other button.
    /// @return
    ///     True if this controller handled the event; false if it was not handled because it
    ///     occurred outside the clickable bounds of the editor and it can be propagated to a parent
    ///     or whatever is "behind" the editor.
    bool onMouseDown(
        float_2 mousePosition,
        bool leftButton);

    /// Called when a mouse button is released. If the corresponding press caused a call to
    /// onMouseDown that returned true, this must be called on release, regardless of where the
    /// mouse is now. Otherwise this does not need to be (but still may be) called.
    ///
    /// @param mousePosition
    ///     The mouse position.
    void onMouseUp(
        float_2 mousePosition);

    /// Draws the editor, using the provided drawer.
    ///
    /// @param drawer
    ///     The drawer to use to do the actual drawing. This will not be accessed after this
    ///     function returns.
    void draw(
        Drawer & drawer) const;

private:

    ApiCustomCurveEditorController(
        const ApiCustomCurveEditorController & other);

    ApiCustomCurveEditorController & operator=(
        const ApiCustomCurveEditorController & other);


    void *const mInternal;

};

}
