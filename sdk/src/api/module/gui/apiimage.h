// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_IMAGE_H_
#define _API_IMAGE_H_   1

#include "apicolor.h"
#include "octaneenums.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Fixed size bitmap in 24-bit RGB or 32-bit pre-multiplied ARGB. Images can be added to the
/// user interface by wrapping them in a ApiImageComponent.
class OCTANEAPI_DECL ApiImage
{
    OCTANEAPI_NO_COPY(ApiImage);

public:

    enum PixelFormat
    {
        /// Invalid pixel format
        PIXEL_FORMAT_INVALID = 0,
        /// Each pixel is a 3-byte packed RGB color value in the order B, G, R.
        PIXEL_FORMAT_BGR     = 1,
        /// Each pixel is a 4-byte RGBA color value with pre-multiplied alpha and in the order A, B, G, R.
        PIXEL_FORMAT_ABGR    = 2,
        /// Each pixel is a 1-byte greyscale value.
        PIXEL_FORMAT_SINGLE  = 3, 
    };

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
    /// @return
    ///     Pointer to the newly created image.
    static ApiImage* create(
        const PixelFormat pixelFormat,
        const int         width,
        const int         height,
        const bool        clear);

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
    /// @return
    ///     Pointer to the newly created image.
    static ApiImage* create(
        const PixelFormat pixelFormat,
        const int         width,
        const int         height,
        const void *const data);

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
    /// @return
    ///     TRUE if the operation was successful, FALSE if not.
    static bool saveToFile(
        const char *const fullPath,
        const bool        destHasAlpha,
        const int         width,
        const int         height,
        const void *const buffer,
        Octane::ImageType pixelFormat,
        const bool        isYPointUp);

    /// Loads an image from a file, which needs to be of one of the following formats:
    /// GIF, JPEG, PNG
    ///
    /// @param[in]  fullPath
    ///     Full path to the file on disk.
    /// @return
    ///     Pointer to the image or NULL if the image could not be loaded.
    static ApiImage* loadFromFile(
        const char *fullPath);

    /// Loads an image from an in-memory image file, i.e. the provided data needs to be in one of
    /// the following file formats: GIF, JPEG, PNG
    ///
    /// @param[in]  imageData
    ///     Pointer to the in-memory data.
    /// @param[in]  sizeInBytes
    ///     Size of the data in bytes.
    /// @return
    ///     Pointer to the image or NULL if the image could not be loaded.
    static ApiImage* loadFromMemory(
        const void   *imageData,
        const size_t sizeInBytes);

    /// Destroys the image created by create.
    void destroy();

    /// Returns the width of this image.
    int width() const;

    /// Returns the height of this image.
    int height() const;

    /// Returns this image's pixel format.
    PixelFormat pixelFormat() const;

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
        const int         x,
        const int         y,
        const int         width,
        const int         height,
        const ApiColorLdr color);

    /// Updates the content of the instance. The provided data must match the current size and format.
    ///
    /// @param[in]  imageData
    ///     Pointer to the image data buffer that needs to be large enough to fit an image of the
    ///     current size and format. If set to NULL, it will have no effect.
    void updateTo(
        const void *const imageData);

    /// Returns the color of one of the pixels in the image.
    ApiColorLdr pixelAt(
        const int x,
        const int y) const;

    /// Sets the color of one of the image's pixels.
    void setPixelAt(
        const int         x,
        const int         y,
        const ApiColorLdr color);

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

    /// Resize this image.
    void resize(
        const int newWidth,
        const int newHeight);

private:

    ApiImage();
};

} // namespace Octane


#endif // #ifndef _API_IMAGE_H_
