// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once


// library includes
#include "octaneenums.h"
#include "octanetypes.h"
#include "octanevectypes.h"


namespace Octane
{

    class OCTANEAPI_DECL LayerInfo
    {
        OCTANEAPI_NO_COPY(LayerInfo);


    public:

        LayerInfo();

        LayerInfo(
            const char *const layerName,
            Octane::ImageType layerType,
            const bool        hasAlpha);

        ~LayerInfo();

        /// Checks if the current layer has alpha data
        bool hasTransparency() const;

        /// Checks if the current layer is gray scale data
        bool isGrayscale() const;

        /// Gets the name of this layer
        const char* name() const;

        /// Gets the type of this layer's data
        Octane::ImageType type() const;

        /// Gets the preferred BC compression type.
        ///
        /// @param[in] needHQ
        ///     A flag indicating if the high quality option needs to be returned
        Octane::ImageType prefCompressType(
            const bool needHQ) const;

        /// Gets all supported compression types
        ///
        /// @param[out] entryCount
        ///     The count of supported types
        /// NOTE: if the layer is already compressed, it will be 0
        /// @return
        ///     An array of supported compression types
        /// NOTE: if the layer is already compressed, it will be NULL
        const Octane::ImageType* allCompressTypes(
            uint32_t *entryCount) const;

        /// Gets all supported compression info string
        ///
        /// @param[out] entryCount
        ///     The count of supported types
        /// NOTE: if the layer is already compressed, it will be 0
        /// @return
        ///     An array of supported compression types info
        /// NOTE: if the layer is already compressed, it will be NULL
        const char *const * allCompressInfo(
            uint32_t *entryCount) const;

    private:

        const char *const       mName;
        const Octane::ImageType mType;
        const bool              mHasTransparancy;
    };

    class OCTANEAPI_DECL ImageInfo
    {
        OCTANEAPI_NO_COPY(ImageInfo);


    public:

        /// Constructor
        ImageInfo();

        /// Initializes the current ImageInfo object with the image file at the given path
        ///
        /// @param[in] pathUTF8
        ///     Absolute path to the image file, which is supposed to be encoded in UTF8.
        void initFromFile(
            const char *const pathUTF8);

        /// Initializes the current ImageInfo object from the given buffer with the given length
        ///
        /// @param[in] data
        ///     The data buffer pointer
        /// @param[in] length
        ///     The length of the data buffer
        void initFromBuffer(
            const void *const data,
            const size_t      length);

        /// Destroys the instance.
        ~ImageInfo();

        /// Gets the layer info using the given layer index
        ///
        /// @param[in] layerIx
        ///     The index of the layer
        /// @return
        ///     SUCCESS, the pointer to the matching layer info
        ///     FAILED , null pointer
        const LayerInfo* layerInfo(
            const uint32_t layerIx = 0) const;

        /// Gets the layer count of the current image
        uint32_t layerCount() const;

        /// Gets the size of the image in pixel
        Octane::uint32_2 size() const;

        /// Checks if the current image is a HDR image
        bool isHdr() const;

        /// Checks if the current image is compressed.
        bool isCompressed() const;


    private:

        LayerInfo        *mLayerInfos;
        uint32_t         mLayerCount;
        Octane::uint32_2 mSize;
        bool             mIsHdr;
        bool             mIsCompressed;
    };


} // namespace Octane
