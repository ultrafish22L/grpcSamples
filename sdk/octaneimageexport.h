// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#include "octaneenums.h"

namespace Octane
{

/// The bit depths at which we can save an image file.
enum SaveImageBitDepth
{
    SAVE_IMAGE_BIT_DEPTH_INT_8,
    SAVE_IMAGE_BIT_DEPTH_INT_16,
    SAVE_IMAGE_BIT_DEPTH_FLOAT_16,
    SAVE_IMAGE_BIT_DEPTH_FLOAT_32,
};


/// The types of image file we can save.
enum SaveImageFileType
{
    SAVE_IMAGE_FILE_TYPE_PNG,
    SAVE_IMAGE_FILE_TYPE_EXR,
    SAVE_IMAGE_FILE_TYPE_TIFF,
    SAVE_IMAGE_FILE_TYPE_JPEG,
};



/// This structure represents settings used to save files of different formats.
/// Since formats have different sets of settings, each set of settings is
/// represented by a separate struct/member, e.g. ExrExportSettings/mExrSettings.
struct OCTANEAPI_DECL ImageExportSettings
{
    static const ExrCompressionType DEFAULT_EXR_COMPRESSION = EXR_COMPRESSION_ZIP;
    static const ExrCompressionType DEFAULT_DEEP_EXR_COMPRESSION = EXR_COMPRESSION_ZIPS;
    static const float DEFAULT_EXR_COMPRESSION_LEVEL;
    static const TiffCompressionType DEFAULT_TIFF_COMPRESSION = TIFF_COMPRESSION_LZW;
    static const float DEFAULT_JPEG_QUALITY;

    /// Settings for the EXR image export
    struct OCTANEAPI_DECL ExrExportSettings
    {
        ExrCompressionType mCompressionType;
        float mCompressionLevel;

        ExrExportSettings();
    };

    /// Settings for the TIFF image export
    struct OCTANEAPI_DECL TiffExportSettings
    {
        TiffCompressionType mCompressionType;

        TiffExportSettings();
    };

    /// Settings for the JPEG image export
    struct OCTANEAPI_DECL JpegExportSettings
    {
        float mQuality;

        JpegExportSettings();
    };

    /// Returns extension for the type
    /// 
    /// @param type
    ///     the type of the image
    /// @return
    ///     the returned extension is lowercase, doesn't include dot
    static const char * getExtension(
        SaveImageFileType type);

    /// Returns number of bits per component for bit depth
    /// 
    /// @param bitDepth 
    ///     the bit depth enum value
    static uint32_t getBitsPerComponent(
        const SaveImageBitDepth bitDepth);

    /// Returns number of bits per component for image format
    /// 
    /// @param format 
    ///     the image save format
    static uint32_t getBitsPerComponent(
        const ImageSaveFormat format);

    /// Returns bit depth of the format
    /// 
    /// @param format
    ///     the image save format
    static SaveImageBitDepth getBitDepth(
        const ImageSaveFormat format);

    /// Returns image save format from file type and bit depth
    ///
    /// @param type 
    ///     the type of the image
    /// @param bitDepth 
    ///     the bit depth enum value
    static ImageSaveFormat getFormat(
        const SaveImageFileType type,
        const SaveImageBitDepth bitDepth);

    /// Returns image file type from the format
    /// 
    /// @param format 
    ///     the image save format
    static SaveImageFileType getType(
        const ImageSaveFormat format);

    /// Creates ImageExportSettings from a set parameters used in older version of the API
    /// @param imageSaveFormat 
    ///     the image save format
    /// @param premultipliedAlphaType 
    ///     Premultiplied alpha setting
    /// @param exrCompressionType 
    ///     compression type for EXR format
    /// @param exrCompressionLevel 
    ///     compression level for EXR format
    /// @return 
    static ImageExportSettings makeFromOldSettings(
        const ImageSaveFormat        imageSaveFormat,
        const PremultipliedAlphaType premultipliedAlphaType,
        const ExrCompressionType     exrCompressionType,
        const float                  exrCompressionLevel);

    /// Creates ImageExportSettings from ImageSaveFormat
    /// Any additional settings are set to the default values
    /// 
    /// @param imageSaveFormat 
    ///     the image save format
    /// @param premultipliedAlphaType
    ///     Premultiplied alpha setting. This should be PREMULTIPLIED_ALPHA_TYPE_NONE when saving
    ///     PNG files, because PNG files are never premultiplied according to the PNG specification.
    static ImageExportSettings makeFromImageSaveFormat(
        const ImageSaveFormat        imageSaveFormat,
        const PremultipliedAlphaType premultipliedAlphaType);

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
    static ImageExportSettings makeExr(
        const SaveImageBitDepth  bitDepth,
        const bool               premultipliedAlpha,
        const ExrCompressionType compressionType,
        const float              compressionLevel = DEFAULT_EXR_COMPRESSION_LEVEL);

    /// Creates ImageExportSettings for writing TIFF format
    /// 
    /// @param bitDepth 
    ///     the bit depth enum value
    /// @param premultipliedAlphaType 
    ///     Premultiplied alpha setting
    /// @param compressionType 
    ///     compression type for TIFF format
    static ImageExportSettings makeTiff(
        const SaveImageBitDepth      bitDepth,
        const PremultipliedAlphaType premultipliedAlphaType,
        const TiffCompressionType    compressionType);

    /// Creates ImageExportSettings for writing PNG format
    /// 
    /// @param bitDepth 
    ///     the bit depth enum value
    static ImageExportSettings makePng(
        const SaveImageBitDepth bitDepth);

    /// Creates ImageExportSettings for writing JPEG format
    /// 
    /// @param quality 
    ///     the JPEG compression quality. Valid range is [1..100].
    static ImageExportSettings makeJpeg(
        const float quality);

    ImageExportSettings();

public:

    SaveImageFileType mFileType;
    ImageSaveFormat mFormat;
    PremultipliedAlphaType mPremultipliedAlphaType;
    ExrExportSettings mExrSettings;
    TiffExportSettings mTiffSettings;
    JpegExportSettings mJpegSettings;

private:

    /// Constructs ImageExportSettings object from format
    ///
    /// @param type 
    ///     the type of the image
    /// @param bitDepth 
    ///     the bit depth enum value
    /// @param premultipliedAlphaType 
    ///     Premultiplied alpha setting
    explicit ImageExportSettings(
        ImageSaveFormat        format,
        PremultipliedAlphaType premultipliedAlphaType = PREMULTIPLIED_ALPHA_TYPE_NONE);

    /// Constructs ImageExportSettings object from type and bit depth
    ///
    /// @param type 
    ///     the type of the image
    /// @param bitDepth 
    ///     the bit depth enum value
    /// @param premultipliedAlphaType 
    ///     Premultiplied alpha setting
    ImageExportSettings(
        const SaveImageFileType      type,
        const SaveImageBitDepth      bitDepth,
        const PremultipliedAlphaType premultipliedAlphaType = PREMULTIPLIED_ALPHA_TYPE_NONE);

};

}
