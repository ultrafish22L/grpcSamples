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


#include "apicustomcurveeditorcontroller.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiCustomCurveEditorController_Drawer
class ApiCustomCurveEditorControllerProxy_Drawer : public GRPCBase
{
public:
    /// Sets the color and opacity to use for future drawing commands. This will always be
        /// called before the first drawing command in a draw operation.
        ///
        /// @param color
        ///     The color to use.
        /// @param opacity
        ///     The opacity to use. This will always be in the range [0, 1].
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setColor(
            Octane::ApiCustomCurveEditorController::Drawer::Color color,
            float                                     opacity
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setClipRegionAndFillBackground(
            OctaneVec::int32_2                        position,
            OctaneVec::int32_2                        size,
            int                                       cornerRadius
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void drawRectangle(
            OctaneVec::int32_2                        position,
            OctaneVec::int32_2                        size
            );

    /// Fills a rectangle.
        ///
        /// Notes to potentially make implementation easier: The opacity will always be 1 when this
        /// is called.
        ///
        /// @param position
        ///     The top left corner of the rectangle.
        /// @param size
        ///     The size of the rectangle.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void fillRectangle(
            OctaneVec::int32_2                        position,
            OctaneVec::int32_2                        size
            );

    /// Fills a circle.
        ///
        /// @param center
        ///     The center of the circle.
        /// @param radius
        ///     The radius of the circle.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void fillCircle(
            OctaneVec::float_2                        center,
            float                                     radius
            );

    /// Starts building a path to be drawn later when finishPath is called. Every call to this
        /// will have a matching call to finishPath, and no functions except lineTo and cubicTo will
        /// be called between this and the matching call to finishPath.
        ///
        /// @param point
        ///     The initial "previous" point of the path.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void startPath(
            OctaneVec::float_2                        point
            );

    /// Adds to the current path a line from the previous point to the given end point, and then
        /// sets the previous point to the end point of the line.
        ///
        /// @param point
        ///     The end point of the line.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void lineTo(
            OctaneVec::float_2                        point
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void cubicBezierTo(
            OctaneVec::float_2                        controlPoint0,
            OctaneVec::float_2                        controlPoint1,
            OctaneVec::float_2                        point
            );

    /// Draws the path that has been built up by calls to startPath/lineTo/cubicTo, and clears
        /// the path ready to possibly start a new one from scratch.
        ///
        /// @param thickness
        ///     The thickness of the path.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void finishPath(
            float                                     thickness
            );

private:
    static GRPCSettings & getGRPCSettings();
};
