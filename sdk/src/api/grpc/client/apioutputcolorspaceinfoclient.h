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


#include "apioutputcolorspaceinfo.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiOutputColorSpaceInfo
class ApiOutputColorSpaceInfoProxy : public GRPCBase
{
public:
    /// Makes an info to produce output in a known color space.
    ///
    /// @param colorSpace
    ///     Must not be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param forceToneMapping
    ///     Whether to apply Octane's built-in tone mapping if colorSpace is not
    ///     NAMED_COLOR_SPACE_SRGB. This may produce undesirable results due to an intermediate
    ///     reduction to the sRGB color space.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created info (must be destroyed with destroy()). Will not be null.
    static ApiOutputColorSpaceInfoProxy createKnownColorSpace(
            Octane::NamedColorSpace                   colorSpace,
            bool                                      forceToneMapping
            );

    /// Makes an info to produce output in an OCIO color space.
    ///
    /// @param colorSpaceName
    ///     The name of the OCIO color space or role to use. Must not be null.
    /// @param lookName
    ///     The name of the OCIO look to apply, or empty or null to apply no look.
    /// @param forceToneMapping
    ///     Whether to apply Octane's built-in tone mapping (before applying any OCIO look(s)). This
    ///     may produce undesirable results due to an intermediate reduction to the sRGB color
    ///     space.
    /// @param curveType
    ///     The curve type that the color space should be considered to have. For beauty passes,
    ///     this only affects metadata/statistics and whether upsampling is enabled (the upsampler
    ///     only works with approximately perceptually uniform image data). Since we don't know the
    ///     details of any OCIO color spaces this should be based on the expected usage of the
    ///     output (e.g. displaying on an SDR monitor -> UNIFORM, saving to a PNG file -> UNIFORM,
    ///     saving to an EXR file -> LINEAR). For info passes, which bypass OCIO, this determines
    ///     whether the output will be transformed into a 0-1 range appropriate to be interpreted as
    ///     being in a perceptually uniform color space.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created info (must be destroyed with destroy()). Will not be null.
    static ApiOutputColorSpaceInfoProxy createOcioColorSpace(
            const char *                              colorSpaceName,
            const char *                              lookName,
            bool                                      forceToneMapping,
            Octane::ColorSpaceCurveType               curveType
            );

    /// Makes an info to produce output using an OCIO view.
    ///
    /// @param displayName
    ///     The name of the OCIO display containing the view to use. Must not be null.
    /// @param viewName
    ///     The name of the OCIO view to use. Must not be null.
    /// @param useViewLook
    ///     Whether to use the view's default look(s) instead of the look specified by lookName.
    /// @param lookName
    ///     If useViewLook is true, this value is ignored. Otherwise, the name of the OCIO look to
    ///     apply, or empty or null to apply no look.
    /// @param forceToneMapping
    ///     Whether to apply Octane's built-in tone mapping (before applying any OCIO look(s)). This
    ///     may produce undesirable results due to an intermediate reduction to the sRGB color
    ///     space.
    /// @param curveType
    ///     The curve type that the color space should be considered to have. For beauty passes,
    ///     this only affects metadata/statistics and whether upsampling is enabled (the upsampler
    ///     only works with approximately perceptually uniform image data). Since we don't know the
    ///     details of any OCIO color spaces this should be based on the expected usage of the
    ///     output (e.g. displaying on an SDR monitor -> UNIFORM, saving to a PNG file -> UNIFORM,
    ///     saving to an EXR file -> LINEAR). For info passes, which bypass OCIO, this determines
    ///     whether the output will be transformed into a 0-1 range appropriate to be interpreted as
    ///     being in a perceptually uniform color space.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created info (must be destroyed with destroy()). Will not be null.
    static ApiOutputColorSpaceInfoProxy createOcioView(
            const char *                              displayName,
            const char *                              viewName,
            bool                                      useViewLook,
            const char *                              lookName,
            bool                                      forceToneMapping,
            Octane::ColorSpaceCurveType               curveType
            );

    /// Makes an info to produce output in whatever is specified in the imager node of the render
    /// target being rendered. This could be a known color space or an OCIO view.
    ///
    /// @param nonOcioColorSpace
    ///     The known color space to use if the imager node isn't set to use an OCIO view. Must not
    ///     be NAMED_COLOR_SPACE_OCIO or NAMED_COLOR_SPACE_OTHER.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created info (must be destroyed with destroy()). Will not be null.
    static ApiOutputColorSpaceInfoProxy createUseImagerSettings(
            Octane::NamedColorSpace   nonOcioColorSpace
            );

    void destroy();

        /// @param[out] status
    ///     Contains the status of the gRPC call
/// @return
    ///     The cloned info (must be destroyed with destroy()). Will not be null.
    ApiOutputColorSpaceInfoProxy clone() const;

    /// Returns whether two ApiOutputColorSpaceInfo instances are equivalent.
    ///
    /// @param other
    ///     The instance to compare against, or null to always return false.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool equals(
            const ApiOutputColorSpaceInfoProxy *   other
            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
