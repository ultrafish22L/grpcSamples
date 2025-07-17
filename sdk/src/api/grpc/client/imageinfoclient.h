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
class LayerInfoProxy;


#include "apiimageinfo.h"


class Convert;

class GRPCSettings;

/// Proxy class for ImageInfo
class ImageInfoProxy : public GRPCBase
{
public:
    /// Initializes the current ImageInfo object with the image file at the given path
        ///
        /// @param[in] pathUTF8
        ///     Absolute path to the image file, which is supposed to be encoded in UTF8.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void initFromFile(
            const char *const   pathUTF8
            );

    /// Initializes the current ImageInfo object from the given buffer with the given length
        ///
        /// @param[in] data
        ///     The data buffer pointer
        /// @param[in] length
        ///     The length of the data buffer
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void initFromBuffer(
            const void *const                         data,
            const size_t                              length
            );

    /// Gets the layer info using the given layer index
        ///
        /// @param[in] layerIx
        ///     The index of the layer
    /// @param[out] status
    ///     Contains the status of the gRPC call
        /// @return
        ///     SUCCESS, the pointer to the matching layer info
        ///     FAILED , null pointer
    LayerInfoProxy layerInfo(
            const uint32_t   layerIx
            ) const;

    /// Gets the layer count of the current image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t layerCount() const;

    /// Gets the size of the image in pixel
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::uint32_2 size() const;

    /// Checks if the current image is a HDR image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isHdr() const;

    /// Checks if the current image is compressed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isCompressed() const;

private:
    static GRPCSettings & getGRPCSettings();
};
