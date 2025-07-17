// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once


#include "octaneenums.h"
#include "octanetypes.h"
#include "octanevectypes.h"


namespace Octane
{

    typedef uint16_2    half_2;
    typedef uint16_4    half_4;


    class OCTANEAPI_DECL ApiImageBuffer
    {
        OCTANEAPI_NO_COPY(ApiImageBuffer);


    public:
        // The all supported compressed types
        enum ImageCompressType
        {
            /// BC compression formats
            /// BC1 unsigned normalized integer:[0, 255] -> [0.0, 1.0]
            BC1_UNORM   = Octane::IMAGE_TYPE_BC1_UNORM,
            /// BC3 unsigned normalized integer:[0, 255] -> [0.0, 1.0]
            BC3_UNORM   = Octane::IMAGE_TYPE_BC3_UNORM,
            /// BC4 signed   normalized integer:[0, 255] -> [-1.0, 1.0]
            BC4_SNORM   = Octane::IMAGE_TYPE_BC4_SNORM,
            /// BC4 unsigned normalized integer:[0, 255] -> [0.0, 1.0]
            BC4_UNORM   = Octane::IMAGE_TYPE_BC4_UNORM,
            /// BC6 signed half floating point
            BC6_SHF     = Octane::IMAGE_TYPE_BC6_SHF,
            /// BC6 unsigned half floating point
            BC6_UHF     = Octane::IMAGE_TYPE_BC6_UHF,
            /// BC7 unsigned normalized integer
            BC7_UNORM   = Octane::IMAGE_TYPE_BC7_UNORM,
        };

        /// Meta-data stored in the image file, if this image buffer is written out to a file
        struct MetaData
        {
            /// the pointer to the key string
            const char* const mKey;
            /// the pointer to the key value string
            const char* const mValue;
        };

        /// List of of meta-data
        struct MetaDataList
        {
            /// the number of meta-data stored in the list
            const uint32_t        mDataSize;
            /// the pointer to the first meta-data in the list
            const MetaData* const mData;
        };

        /// rectange defining a region in the image
        struct RegionRect
        {
            /// the origin of the region
            uint32_2 mOrigin;
            /// the size of the region
            uint32_2 mSize;
        };


        /// Creates an empty image buffer
        /// @param[in] size
        ///     The image size in pixels
        /// @param[in] type
        ///     The image buffer type
        /// @param[in] containsAlpha
        ///     Set to false if we definitely know the opacity of the entire image is 100%. Ignored
        ///     for image types without an alpha channel
        static ApiImageBuffer* create(
            const uint32_2  size,
            const ImageType type,
            const bool      containsAlpha = true);

        /// Creates an image buffer using the given data
        ///
        /// @param[in] buffer
        ///     The data buffer
        /// @param[in] bufferSize
        ///     The number of bytes stored in the above data buffer
        /// @param[in] imgDim
        ///     The image size in pixels
        /// @param[in] type
        ///     The image buffer type.
        static ApiImageBuffer* create(
            const uint8_t* const buffer,
            const uint32_t       bufferSize,
            const uint32_2       imgDim,
            const ImageType      type);

        /// Loads an image from file
        /// @param[in] fileName
        ///     File to load
        /// @param[in] loadType
        ///     Indicate what is the type of the image data will be loaded in before conversion and
        ///      compression
        ///     see Octane::ImageColorType
        /// @param[in] targType
        ///     Indicate which channel format to be used after conversion and compression:
        ///      - float or half: always use this format for HDR images
        ///      - auto: choose depending on the source image data: if the source is half precision
        ///              float or 16-bit integer data, then load as half
        ///      - other types: compress the loaded image
        /// @param[in] layerName
        ///     The name of the image layer (could be empty).
        static ApiImageBuffer* load(
            const char* const      fileName,
            const ImageColorType   loadType,
            const ImageChannelType targType,
            const char* const      layerName = "");

        /// Loads an image from encoded data(for instance, from a memory block of a png file)
        static ApiImageBuffer* load(
            const void* const      data,
            const size_t           length,
            const ImageColorType   loadType,
            const ImageChannelType targType,
            const char* const      layerName = "");

        /// Convert the source image buffer to another one using the destination type
        /// NOTE: Only works for uncompressed images
        /// Meta data (like wrapping and alpha flags) are copied to the returned image
        ///
        /// @param[in] srcImg
        ///     The source image buffer instance
        /// @param[in] destType
        ///     The type this image will be converted to
        /// @param[in] forceCopy
        ///     If true, a copy is returned even if the type is the same. If false and the
        ///     requested type is the same as this type, a ref to this image is returned
        static ApiImageBuffer* convertTo(
            const ApiImageBuffer *const srcImg,
            const ImageType             destType,
            const bool                  forceCopy = false);

        /// Destroys the ApiImageBuffer object created by create()
        void destroy();

        /// Returns the bytes per pixel
        ///
        /// @return
        ///     The number of bytes of a pixel
        ///     NOTE: for a BC1 compressed image, this value will be 0.5byte/pixel
        float bytesPerPixel() const;

        /// Returns the bytes per pixel channel
        float bytesPerChannel() const;

        /// Returns the number of channels of a pixel
        uint8_t channelCount() const;

        /// Returns the dimensions of the image in pixels
        uint32_2 size() const;

        /// Returns the size in bytes of the image data
        size_t sizeInBytes() const;

        /// Returns the image buffer's type
        ImageType type() const;

        /// Returns the image source information string
        const char* sourceInfo() const;

        /// TRUE if the image can wrap in horizontal direction.
        bool canWrapX() const;

        /// TRUE if the image can wrap in vertical direction.
        bool canWrapY() const;

        /// TRUE if the image has Y down (currently only for BC compressed images).
        bool needsFlip() const;

        /// TRUE for a transparent image
        bool hasAlpha() const;

        /// TRUE for a chormatic image
        bool hasColor() const;

        /// TRUE for a compressed image
        bool isCompressed() const;

        /// Checks if this image has data.
        bool isEmpty() const;

        /// TRUE for a 16bits Hdr image
        bool isHalf() const;

        /// TRUE for a Hdr image
        bool isHdr() const;

        /// TRUE for a single channel image
        bool isMono() const;

        /// TRUE is the given pixel location is valid
        bool isPixelValid(
            const uint32_2 pos) const;

        /// Returns the pointer to the first component of a pixel in a Ldr image buffer
        /// NOTE: This assumes that the buffer represents a un-compressed Ldr image and
        ///       image that goes bottom-to-top (y points down)
        ///
        /// @param[in] pos
        ///     the pixel coordinate
        /// @return
        ///     the pointer to the first component of a pixel value, if the image is Ldr and
        ///     the pixel location is valid
        ///     nullptr, if the image is Hdr or the pixel location is invalid
        const uint8_t* getPixelLdr(
            const uint32_2 pos) const;

        /// Returns the pointer to the first component of a pixel in a 16bits Hdr image buffer
        /// NOTE: This assumes that the buffer represents a 16bits un-compressed Hdr image and
        ///       image that goes bottom-to-top (y points down)
        ///
        /// @param[in] pos
        ///     the pixel coordinate
        /// @return
        ///     the pointer to the first component of a pixel value, if the image is 16bits Hdr and
        ///     the pixel location is valid
        ///     nullptr, if the image is not 16bits Hdr or the pixel location is invalid
        const half_t* getPixelHalf(
            const uint32_2 pos) const;

        /// Returns the pointer to the first component of a pixel in a 32bits Hdr image buffer
        /// NOTE: This assumes that the buffer represents 32bits un-compressed Hdr image and
        ///       image that goes bottom-to-top (y points down)
        ///
        /// @param[in] pos
        ///     the pixel coordinate
        /// @return
        ///     the pointer to the first component of a pixel value, if the image is 32bits Hdr and
        ///     the pixel location is valid
        ///     nullptr, if the image is not 32bits Hdr or the pixel location is invalid
        const float* getPixelHdr(
            const uint32_2 pos) const;

        /// Returns the pixel buffer of this image as a constant C-array
        /// This is only a raw byte array and it's up to the caller 
        /// how to interpret these bytes based on the image type
        const void* buffer() const;

        /// Returns the mutable reference to the pixel buffer of this image
        void* buffer();

        /// Compresses this image buffer
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in] compressType
        ///     The type, to which we want this image buffer to be compressed
        void compress(
            const ImageCompressType compressType);

        /// Modifies a pixel in a Ldr image buffer
        /// NOTE: This assumes that the buffer represents a un-compressed Ldr image and
        ///       image that goes bottom-to-top (y points down)
        ///
        /// @param[in] pos
        ///     the pixel coordinate
        /// @param[in]  value 
        ///     the pointer to the first component of a Ldr pixel value
        ///     this must be an instance of the pixel type corresponding
        ///     to the type of this image (eg. a uint8_4 for a LDR RGBA image)
        void setPixelLdr(
            const uint32_2       pos,
            const uint8_t *const value);

        /// Modifies a pixel in a 16bits Hdr image buffer
        /// NOTE: This assumes that the buffer represents a 16bits un-compressed Hdr image and
        ///       image that goes bottom-to-top (y points down)
        ///
        /// @param[in] pos
        ///     the pixel coordinate
        /// @param[in]  value 
        ///     the pointer to the first component of a 16bits Hdr pixel value
        ///     this must be an instance of the pixel type corresponding
        ///     to the type of this image (eg. a uint8_4 for a LDR RGBA image)
        void setPixelHalf(
            const uint32_2      pos,
            const half_t* const value);

        /// Modifies a pixel in a 326bits Hdr image buffer
        /// NOTE: This assumes that the buffer represents a 32bits un-compressed Hdr image and
        ///       image that goes bottom-to-top (y points down)
        ///
        /// @param[in] pos
        ///     the pixel coordinate
        /// @param[in]  value 
        ///     the pointer to the first component of a 32bits Hdr pixel value
        ///     this must be an instance of the pixel type corresponding
        ///     to the type of this image (eg. a uint8_4 for a LDR RGBA image)
        void setPixelHdr(
            const uint32_2     pos,
            const float* const value);

        /// Fills a region in this image buffer with the given colour
        /// NOTE: Only works for uncompressed Ldr or 32bits Hdr images
        ///      (blending is not supported for half-precision images)
        ///
        /// @param[in]  regionRect
        ///     the origin and size of the region
        /// @param[in]  value 
        ///     the pointer to the first component of the color value
        ///     this must point to an instance of the pixel type corresponding
        ///     to the type of this image (eg. a uint8_4 for a LDR RGBA image)
        /// @param[in]  blend
        ///     if true, the color is composited using alpha blending. if false, the region is
        ///     simply filled with that color (and opacity).
        /// @return
        ///     TRUE:  if fill succeeded
        ///     FALSE: if fill failed
        bool fill(
            const RegionRect  regionRect,
            const void* const value,
            const bool        blend);

        /// Copies a region from another ImageBuffer. The type of the images must match
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in]  srcImg
        ///     the source image to copy
        /// @param[in]  regionRect
        ///     the origin and size of the region to copy (in the source image)
        /// @param[in]  destPos
        ///     the topleft corner in this image where the image is to be copied
        /// @param[in]  blend
        ///     if true, the image is composited using alpha blending. if false, the data (including
        ///     the alpha channel) is copied
        /// @return
        ///     TRUE:  if the region copy succeeded
        ///     FALSE: if the region copy failed
        bool copyRegion(
            const ApiImageBuffer *const srcImg,
            const RegionRect            regionRect,
            const uint32_2              destPos,
            bool                        blend);

        /// eliminates the alpha channel by multiplying the color channels by the alpha channel, and
        /// setting the alpha channel to 1.0
        void compositeOnBlack();

        /// vertical flip (in place)
        void flipVertical();

        /// Convert the current image bufer to another type
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in] destType
        ///     The type this image will be converted to
        void convert(
            const ImageType destType);

        /// Applies gaussian filter to the image
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in] radius
        ///     The number of nearest pixels to use for this filtering
        ///     It should be greater than zero and higher the value slower the operation
        void applyGaussianFilter(
            const uint8_t radius);

        /// Applies Box filter to the image. A faster algorithm than gaussian filter
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in] radius
        ///     The number of nearest pixels to use for this filtering
        ///     It should be greater than zero and higher the value slower the operation
        void applyBoxFilter(
            const uint8_t radius);

        /// Applies level correction to the image
        /// NOTE: the image must be un-compressed image and have float channels
        ///
        /// @param[in] gamma
        ///     The Gamma factor
        /// @param[in] levels
        ///     The interval where the input value range (0, 1) will be mapped
        void applyLevels(
            const float   gamma,
            const float_2 levels);

        /// Compares this image to another image, and puts the difference in this image
        ///
        /// @param[in] otherImg
        ///     The other image, which must have the same type and size as this one
        /// @param[in] compareAlpha
        ///     TRUE telling the alpha channel will be compared
        void compareValues(
            const ApiImageBuffer* const otherImg,
            const bool                  compareAlpha);

        /// Compares this image to another image, and returns the mean square error for it
        ///
        /// @param[in]  otherImg
        ///     The other image, which must have the same type and size as this one
        /// @param[in]  clampValues
        ///     If set to TRUE, the channel values will be clamped at 1.
        /// @param[out] error
        ///     The mean square error
        /// @return
        ///     TRUE:  if the calculation is successful
        ///     FALSE: if it is failed
        bool calculateMeanSquareError(
            const ApiImageBuffer *const otherImg,
            const bool                  clampValues,
            double &                    error) const;

        /// Saves an image to disk.
        /// Compressed images are saved as DDS, HDR images are saved as EXR and LDR images are saved as PNG
        /// NOTE:  The correct extension is added to the path (if it didn't exist yet)
        ///
        /// @param[in]  fileName
        ///     The full path of the file into which the image shall be stored
        /// @param[in]  metadata
        ///     Metadata table to store in the output file
        /// @return
        ///     TRUE if the image was saved successfully, FALSE if not
        bool save(
            const char* const         fileName,
            const MetaDataList* const metaData = nullptr) const;

        /// Starts saving an image to disk on a background thread
        /// Compressed images are saved as DDS, HDR images are saved as EXR and LDR images are saved as PNG
        /// NOTE:  The correct extension is added to the path (if it didn't exist yet)
        ///
        /// @param[in]  fileName
        ///     The full path of the file into which the image shall be stored
        /// @param[in]  metadata
        ///     Metadata table to store in the output file
        /// @return
        ///     TRUE if the saving job started successfully, FALSE if not
        bool saveAsync(
            const char* const         fileName,
            const MetaDataList* const metaData = nullptr) const;


    private:
        /// Gets the constant reference to the memory location of a pixel
        const char* pixelAddr(
            const uint32_2 pos) const;

        /// Gets the mutable reference to the memory location of a pixel
        char* pixelAddr(
            const uint32_2 pos);
    };

}