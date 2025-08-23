// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_IMAGE_H_
#define _OCTANE_WRAP_IMAGE_H_   1

// system includes
#include <string>
// api includes
#include "apiimage.h"
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h" 
#include "apiimageclient.h"

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Wraps ApiImage.
class Image
{
    OCTANEAPI_NO_COPY(Image);
    friend class ImageComponent;

public:

    /// Loads an image from a file.
    ///
    /// @param[in]  fullPath
    ///     Full path to the file on disk.
    /// @return
    ///     Pointer to the image or NULL if the image could not be loaded.
    static Image* loadFromFile(
        const std::string &fullPath);

    /// Loads an image from an in-memory image file, i.e. the provided data needs to be in one of
    /// the following file formats: GIF, JPEG, PNG
    ///
    /// @param[in]  imageData
    ///     Pointer to the in-memory data.
    /// @param[in]  sizeInBytes
    ///     Size of the data in bytes.
    /// @return
    ///     Pointer to the image or NULL if the image could not be loaded.
    static Image* loadFromMemory(
        const void   *imageData,
        const size_t  sizeInBytes);

    /// Creates a new image.
    ///
    /// @param[in]  Octane::ApiImage::PixelFormat
    ///     Pixel format.
    /// @param[in]  width
    ///     Width of the image in pixels.
    /// @param[in]  height
    ///     Height of the image in pixels.
    /// @param[in]  clear
    ///     TRUE to clear all the values to 0. FALSE leaves them unitialized.
    Image(
        const Octane::ApiImage::PixelFormat pixelFormat,
        const int                           width,
        const int                           height,
        const bool                          clear);

    /// Creates a new image and initializes it with the provided data.
    ///
    /// @param[in]  Octane::ApiImage::PixelFormat
    ///     Pixel format.
    /// @param[in]  width
    ///     Width of the image in pixels.
    /// @param[in]  height
    ///     Height of the image in pixels.
    /// @param[in]  data
    ///     Pointer to the data the image will be initialized with. If NULL, the image will be
    ///     uninitialized.
    Image(
        const Octane::ApiImage::PixelFormat pixelFormat,
        const int                           width,
        const int                           height,
        const void *const                   data);

    /// Destructor.
    virtual ~Image();

    /// Returns the width of this image.
    int width() const;

    /// Returns the height of this image.
    int height() const;

    /// Returns this image's pixel format.
    Octane::ApiImage::PixelFormat pixelFormat() const;

    /// TRUE if the image's format is ARGB.
    bool isARGB() const;

    /// True if the image's format is RGB.
    bool isRGB() const;

    /// TRUE if the image's format is a single-channel alpha map.
    bool isSingleChannel() const;

    /// TRUE if the image contains an alpha-channel.
    bool hasAlphaChannel() const;
    
    /// Clears a section of the image with a given color.  This won't do any alpha-blending,
    /// it just sets all pixels in the image to the given color (which may be non-opaque if the
    /// image has an alpha channel).
    void clear(
        const int                 x,
        const int                 y,
        const int                 width,
        const int                 height,
        const Octane::ApiColorLdr color);

    /// Updates the content of the instance. The provided data must match the current size and format.
    ///
    /// @param[in]  imageData
    ///     Pointer to the image data buffer that needs to be large enough to fit an image of the
    ///     current size and format. If NULL, no changes are made.
    void updateTo(
        const void *const imageData, const int size);

    /// Returns the color of one of the pixels in the image.
    Octane::ApiColorLdr pixelAt(
        const int x,
        const int y) const;

    /// Sets the color of one of the image's pixels.
    void setPixelAt(
        const int                 x,
        const int                 y,
        const Octane::ApiColorLdr color);

    /// Changes the opacity of a pixel. The multiplier must be in the range 0 to 1.0, the current
    /// alpha at the given coordinates will be multiplied by this value.
    void multiplyAlphaAt(
        const int   x,
        const int   y,
        const float multiplier);

    /// Changes the overall opacity of the image.
    void multiplyAllAlphas(
        const float amountToMultiplyBy);

    /// Changes all the colors to be shades of grey, based on their current luminosity.
    void desaturate();

    /// Returns the wrapped image.
    OctaneGRPC::ApiImageProxy * wrappedImage();

    /// Returns the wrapped image. const version
    const OctaneGRPC::ApiImageProxy * wrappedImage() const;

private:

    OctaneGRPC::ApiImageProxy mApiImage;

    Image(
        OctaneGRPC::ApiImageProxy & apiImage);
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_IMAGE_H_
