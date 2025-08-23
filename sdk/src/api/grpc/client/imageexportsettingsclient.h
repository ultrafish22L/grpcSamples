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


#include "octaneimageexport.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ImageExportSettings
class ImageExportSettingsProxy : public GRPCBase
{
public:
    /// Returns extension for the type
    ///
    /// @param type
    ///     the type of the image
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     the returned extension is lowercase, doesn't include dot
    static std::string getExtension(
            Octane::SaveImageFileType   type
            );

    /// Returns number of bits per component for bit depth
    ///
    /// @param bitDepth
    ///     the bit depth enum value
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint32_t getBitsPerComponent(
            const Octane::SaveImageBitDepth   bitDepth
            );

    /// Returns number of bits per component for image format
    ///
    /// @param format
    ///     the image save format
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static uint32_t getBitsPerComponent(
            const Octane::ImageSaveFormat   format
            );

    /// Returns bit depth of the format
    ///
    /// @param format
    ///     the image save format
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::SaveImageBitDepth getBitDepth(
            const Octane::ImageSaveFormat   format
            );

    /// Returns image save format from file type and bit depth
    ///
    /// @param type
    ///     the type of the image
    /// @param bitDepth
    ///     the bit depth enum value
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ImageSaveFormat getFormat(
            const Octane::SaveImageFileType           type,
            const Octane::SaveImageBitDepth           bitDepth
            );

    /// Returns image file type from the format
    ///
    /// @param format
    ///     the image save format
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::SaveImageFileType getType(
            const Octane::ImageSaveFormat   format
            );

    /// Creates ImageExportSettings from a set parameters used in older version of the API
    /// @param imageSaveFormat
    ///     the image save format
    /// @param premultipliedAlphaType
    ///     Premultiplied alpha setting
    /// @param exrCompressionType
    ///     compression type for EXR format
    /// @param exrCompressionLevel
    ///     compression level for EXR format
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    static Octane::ImageExportSettings makeFromOldSettings(
            const Octane::ImageSaveFormat             imageSaveFormat,
            const Octane::PremultipliedAlphaType      premultipliedAlphaType,
            const Octane::ExrCompressionType          exrCompressionType,
            const float                               exrCompressionLevel
            );

    /// Creates ImageExportSettings from ImageSaveFormat
    /// Any additional settings are set to the default values
    ///
    /// @param imageSaveFormat
    ///     the image save format
    /// @param premultipliedAlphaType
    ///     Premultiplied alpha setting. This should be PREMULTIPLIED_ALPHA_TYPE_NONE when saving
    ///     PNG files, because PNG files are never premultiplied according to the PNG specification.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ImageExportSettings makeFromImageSaveFormat(
            const Octane::ImageSaveFormat             imageSaveFormat,
            const Octane::PremultipliedAlphaType      premultipliedAlphaType
            );

    /// Creates ImageExportSettings for writing EXR format
    ///
    /// @param bitDepth
    ///     the bit depth enum value
    /// @param premultipliedAlpha
    ///     Whether the image should have premultiplied alpha
    /// @param compressionType
    ///     compression type for EXR format
    /// @param compressionLevel
    ///     compression level for EXR format
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ImageExportSettings makeExr(
            const Octane::SaveImageBitDepth           bitDepth,
            const bool                                premultipliedAlpha,
            const Octane::ExrCompressionType          compressionType,
            const float                               compressionLevel
            );

    /// Creates ImageExportSettings for writing TIFF format
    ///
    /// @param bitDepth
    ///     the bit depth enum value
    /// @param premultipliedAlphaType
    ///     Premultiplied alpha setting
    /// @param compressionType
    ///     compression type for TIFF format
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ImageExportSettings makeTiff(
            const Octane::SaveImageBitDepth           bitDepth,
            const Octane::PremultipliedAlphaType      premultipliedAlphaType,
            const Octane::TiffCompressionType         compressionType
            );

    /// Creates ImageExportSettings for writing PNG format
    ///
    /// @param bitDepth
    ///     the bit depth enum value
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ImageExportSettings makePng(
            const Octane::SaveImageBitDepth   bitDepth
            );

    /// Creates ImageExportSettings for writing JPEG format
    ///
    /// @param quality
    ///     the JPEG compression quality. Valid range is [1..100].
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::ImageExportSettings makeJpeg(
            const float   quality
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
