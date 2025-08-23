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


#include "apiimage.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiImage
class ApiImageProxy : public GRPCBase
{
public:
    /// Creates a new image.
    ///
    /// @param[in]  pixelFormat
    ///     Pixel format.
    /// @param[in]  width
    ///     Width of the image in pixels.
    /// @param[in]  height
    ///     Height of the image in pixels.
    /// @param[in]  clear
    ///     TRUE to clear all the values to 0. FALSE leaves them unitialized.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the newly created image.
    static ApiImageProxy create(
            const Octane::ApiImage::PixelFormat       pixelFormat,
            const int                                 width,
            const int                                 height,
            const bool                                clear
            );

    /// Creates a new image and initializes it with the provided data.
    ///
    /// @param[in]  pixelFormat
    ///     Pixel format.
    /// @param[in]  width
    ///     Width of the image in pixels.
    /// @param[in]  height
    ///     Height of the image in pixels.
    /// @param[in]  data
    ///     Pointer to the data the image will be initialized with. If NULL, the image will be
    ///     uninitialized.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the newly created image.
    static ApiImageProxy create(
            const Octane::ApiImage::PixelFormat       pixelFormat,
            const int                                 width,
            const int                                 height,
            const void *const                         data
            );

    /// Writes this ApiImage into a file.
    ///
    /// @param[in]  fullPath
    ///     Full path to the output file.
    /// @param[in] destHasAlpha
    ///     TRUE if the alpha channel should be saved
    /// @param[in]  width
    ///     Width of the image in pixels.
    /// @param[in]  height
    ///     Height of the image in pixels.
    /// @param[in] buffer
    ///     Raw data buffer containing all image data using the given pixel format
    /// @param[in]  pixelFormat
    ///     Pixel data format in the buffer.
    /// @param[in] isYPointUp
    ///     Set to TRUE if the image data represents an image going from bottom to top and to FALSE
    ///     if it's going from top to bottom.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the operation was successful, FALSE if not.
    static bool saveToFile(
            const char *const                         fullPath,
            const bool                                destHasAlpha,
            const int                                 width,
            const int                                 height,
            const void *const                         buffer,
            Octane::ImageType                         pixelFormat,
            const bool                                isYPointUp
            );

    /// Loads an image from a file, which needs to be of one of the following formats:
    /// GIF, JPEG, PNG
    ///
    /// @param[in]  fullPath
    ///     Full path to the file on disk.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the image or NULL if the image could not be loaded.
    static ApiImageProxy loadFromFile(
            const char *   fullPath
            );

    /// Loads an image from an in-memory image file, i.e. the provided data needs to be in one of
    /// the following file formats: GIF, JPEG, PNG
    ///
    /// @param[in]  imageData
    ///     Pointer to the in-memory data.
    /// @param[in]  sizeInBytes
    ///     Size of the data in bytes.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the image or NULL if the image could not be loaded.
    static ApiImageProxy loadFromMemory(
            const void *                              imageData,
            const size_t                              sizeInBytes
            );

    /// Destroys the image created by create.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Returns the width of this image.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int width() const;

    /// Returns the height of this image.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int height() const;

    /// Returns this image's pixel format.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::ApiImage::PixelFormat pixelFormat() const;

    /// TRUE if the image's format is ARGB.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isARGB() const;

    /// True if the image's format is RGB.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isRGB() const;

    /// TRUE if the image's format is a single-channel alpha map.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isSingleChannel() const;

    /// TRUE if the image contains an alpha-channel.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasAlphaChannel() const;

    /// Clears a section of the image with a given color.  This won't do any alpha-blending,
    /// it just sets all pixels in the image to the given color (which may be non-opaque if the
    /// image has an alpha channel).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clear(
            const int                                 x,
            const int                                 y,
            const int                                 width,
            const int                                 height,
            const Octane::ApiColorLdr                 color
            );

    /// Updates the content of the instance. The provided data must match the current size and format.
    ///
    /// @param[in]  imageData
    ///     Pointer to the image data buffer that needs to be large enough to fit an image of the
    ///     current size and format. If set to NULL, it will have no effect.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void updateTo(
            const void *const                         imageData,
            int                                       imageDataSize
            );

    /// Returns the color of one of the pixels in the image.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::ApiColorLdr pixelAt(
            const int                                 x,
            const int                                 y
            ) const;

    /// Sets the color of one of the image's pixels.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setPixelAt(
            const int                                 x,
            const int                                 y,
            const Octane::ApiColorLdr                 color
            );

    /// Changes the opacity of a pixel. The multiplier must be in the range 0 to 1.0, the current
    /// alpha at the given coordinates will be multiplied by this value.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void multiplyAlphaAt(
            const int                                 x,
            const int                                 y,
            const float                               multiplier
            );

    /// Changes the overall opacity of the image.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void multiplyAllAlphas(
            const float   amountToMultiplyBy
            );

    /// Changes all the colors to be shades of grey, based on their current luminosity.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void desaturate();

    /// Resize this image.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void resize(
            const int                                 newWidth,
            const int                                 newHeight
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
