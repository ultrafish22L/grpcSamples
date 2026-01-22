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


#include "apiimagebuffer.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiImageBuffer
class ApiImageBufferProxy : public GRPCBase
{
public:
    /// Creates an empty image buffer
        /// @param[in] size
        ///     The image size in pixels
        /// @param[in] type
        ///     The image buffer type
        /// @param[in] containsAlpha
        ///     Set to false if we definitely know the opacity of the entire image is 100%. Ignored
        ///     for image types without an alpha channel
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiImageBufferProxy create(
            const OctaneVec::uint32_2                 size,
            const Octane::ImageType                   type,
            const bool                                containsAlpha
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiImageBufferProxy create(
            const uint8_t *const                      buffer,
            const uint32_t                            bufferSize,
            const OctaneVec::uint32_2                 imgDim,
            const Octane::ImageType                   type
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiImageBufferProxy load(
            const char *const                         fileName,
            const Octane::ImageColorType              loadType,
            const Octane::ImageChannelType            targType,
            const char *const                         layerName
            );

    /// Loads an image from encoded data(for instance, from a memory block of a png file)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiImageBufferProxy load(
            const void *const                         data,
            const size_t                              length,
            const Octane::ImageColorType              loadType,
            const Octane::ImageChannelType            targType,
            const char *const                         layerName
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiImageBufferProxy convertTo(
            const ApiImageBufferProxy *const          srcImg,
            const Octane::ImageType                   destType,
            const bool                                forceCopy
            );

    /// Destroys the ApiImageBuffer object created by create()
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Returns the bytes per pixel
        ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     The number of bytes of a pixel
        ///     NOTE: for a BC1 compressed image, this value will be 0.5byte/pixel
    float bytesPerPixel() const;

    /// Returns the bytes per pixel channel
    /// @param[out] status
    ///     Contains the status of the gRPC call
    float bytesPerChannel() const;

    /// Returns the number of channels of a pixel
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint8_t channelCount() const;

    /// Returns the dimensions of the image in pixels
    /// @param[out] status
    ///     Contains the status of the gRPC call
    OctaneVec::uint32_2 size() const;

    /// Returns the size in bytes of the image data
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t sizeInBytes() const;

    /// Returns the image buffer's type
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::ImageType type() const;

    /// Returns the image source information string
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string sourceInfo() const;

    /// TRUE if the image can wrap in horizontal direction.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool canWrapX() const;

    /// TRUE if the image can wrap in vertical direction.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool canWrapY() const;

    /// TRUE if the image has Y down (currently only for BC compressed images).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool needsFlip() const;

    /// TRUE for a transparent image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasAlpha() const;

    /// TRUE for a chormatic image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasColor() const;

    /// TRUE for a compressed image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isCompressed() const;

    /// Checks if this image has data.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isEmpty() const;

    /// TRUE for a 16bits Hdr image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isHalf() const;

    /// TRUE for a Hdr image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isHdr() const;

    /// TRUE for a single channel image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isMono() const;

    /// TRUE is the given pixel location is valid
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isPixelValid(
            const OctaneVec::uint32_2   pos
            ) const;

    /// Compresses this image buffer
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in] compressType
        ///     The type, to which we want this image buffer to be compressed
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void compress(
            const Octane::ApiImageBuffer::ImageCompressType   compressType
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setPixelLdr(
            const OctaneVec::uint32_2                 pos,
            const uint8_t *const                      value
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setPixelHalf(
            const OctaneVec::uint32_2                 pos,
            const Octane::half_t *const               value
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setPixelHdr(
            const OctaneVec::uint32_2                 pos,
            const float *const                        value
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     TRUE:  if the region copy succeeded
        ///     FALSE: if the region copy failed
    bool copyRegion(
            const ApiImageBufferProxy *const          srcImg,
            const Octane::ApiImageBuffer::RegionRect  regionRect,
            const OctaneVec::uint32_2                 destPos,
            bool                                      blend
            );

    /// eliminates the alpha channel by multiplying the color channels by the alpha channel, and
        /// setting the alpha channel to 1.0
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void compositeOnBlack();

    /// vertical flip (in place)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void flipVertical();

    /// Convert the current image bufer to another type
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in] destType
        ///     The type this image will be converted to
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void convert(
            const Octane::ImageType   destType
            );

    /// Applies gaussian filter to the image
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in] radius
        ///     The number of nearest pixels to use for this filtering
        ///     It should be greater than zero and higher the value slower the operation
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void applyGaussianFilter(
            const uint8_t   radius
            );

    /// Applies Box filter to the image. A faster algorithm than gaussian filter
        /// NOTE: Only works for uncompressed images
        ///
        /// @param[in] radius
        ///     The number of nearest pixels to use for this filtering
        ///     It should be greater than zero and higher the value slower the operation
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void applyBoxFilter(
            const uint8_t   radius
            );

    /// Applies level correction to the image
        /// NOTE: the image must be un-compressed image and have float channels
        ///
        /// @param[in] gamma
        ///     The Gamma factor
        /// @param[in] levels
        ///     The interval where the input value range (0, 1) will be mapped
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void applyLevels(
            const float                               gamma,
            const OctaneVec::float_2                  levels
            );

    /// Compares this image to another image, and puts the difference in this image
        ///
        /// @param[in] otherImg
        ///     The other image, which must have the same type and size as this one
        /// @param[in] compareAlpha
        ///     TRUE telling the alpha channel will be compared
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void compareValues(
            const ApiImageBufferProxy *const          otherImg,
            const bool                                compareAlpha
            );

    /// Compares this image to another image, and returns the mean square error for it
        ///
        /// @param[in]  otherImg
        ///     The other image, which must have the same type and size as this one
        /// @param[in]  clampValues
        ///     If set to TRUE, the channel values will be clamped at 1.
        /// @param[out] error
        ///     The mean square error
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     TRUE:  if the calculation is successful
        ///     FALSE: if it is failed
    bool calculateMeanSquareError(
            const ApiImageBufferProxy *const          otherImg,
            const bool                                clampValues,
            double &                                  error
            ) const;

    /// Saves an image to disk.
        /// Compressed images are saved as DDS, HDR images are saved as EXR and LDR images are saved as PNG
        /// NOTE:  The correct extension is added to the path (if it didn't exist yet)
        ///
        /// @param[in]  fileName
        ///     The full path of the file into which the image shall be stored
        /// @param[in]  metadata
        ///     Metadata table to store in the output file
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     TRUE if the image was saved successfully, FALSE if not
    bool save(
            const char *const                         fileName,
            const Octane::ApiImageBuffer::MetaDataList *const metaData
            ) const;

    /// Starts saving an image to disk on a background thread
        /// Compressed images are saved as DDS, HDR images are saved as EXR and LDR images are saved as PNG
        /// NOTE:  The correct extension is added to the path (if it didn't exist yet)
        ///
        /// @param[in]  fileName
        ///     The full path of the file into which the image shall be stored
        /// @param[in]  metadata
        ///     Metadata table to store in the output file
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     TRUE if the saving job started successfully, FALSE if not
    bool saveAsync(
            const char *const                         fileName,
            const Octane::ApiImageBuffer::MetaDataList *const metaData
            ) const;

    /// Gets the constant reference to the memory location of a pixel
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string pixelAddr(
            const OctaneVec::uint32_2   pos
            ) const;

    /// Gets the mutable reference to the memory location of a pixel
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string pixelAddr(
            const OctaneVec::uint32_2   pos
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
