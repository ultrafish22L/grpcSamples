// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertimageexportsettings.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "octaneimageexport.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneimageexport.h"

#include "octaneimageexport.h"
#include "convertimageexportsettings_imageexportsettings_exrexportsettings.h"
#include "convertimageexportsettings_imageexportsettings_jpegexportsettings.h"
#include "convertimageexportsettings_imageexportsettings_tiffexportsettings.h"
#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

namespace OctaneGRPC
{

void ImageExportSettingsConverter::convert(
    const octaneapi::ImageExportSettings & in,
    Octane::ImageExportSettings & out)
{

    // Found structure 1 ImageExportSettings
    // from proto type = const octaneapi::ImageExportSettings &,
        //to octane type = Octane::ImageExportSettings &
    // list out parameters
    //cl=ImageExportSettings, field.mName = fileType field.mType = Octane::SaveImageFileType, protoType=SaveImageFileType
    out.mFileType = static_cast<Octane::SaveImageFileType>(in.filetype());// enum 1 
    //cl=ImageExportSettings, field.mName = format field.mType = Octane::ImageSaveFormat, protoType=ImageSaveFormat
    out.mFormat = static_cast<Octane::ImageSaveFormat>(in.format());// enum 1 
    //cl=ImageExportSettings, field.mName = premultipliedAlphaType field.mType = Octane::PremultipliedAlphaType, protoType=PremultipliedAlphaType
    out.mPremultipliedAlphaType = static_cast<Octane::PremultipliedAlphaType>(in.premultipliedalphatype());// enum 1 
    //cl=ImageExportSettings, field.mName = exrSettings field.mType = Octane::ImageExportSettings::ExrExportSettings, protoType=ExrExportSettings
    ImageExportSettings_ImageExportSettings_ExrExportSettingsConverter::convert( in.exrsettings(), out.mExrSettings );
    //cl=ImageExportSettings, field.mName = tiffSettings field.mType = Octane::ImageExportSettings::TiffExportSettings, protoType=TiffExportSettings
    ImageExportSettings_ImageExportSettings_TiffExportSettingsConverter::convert( in.tiffsettings(), out.mTiffSettings );
    //cl=ImageExportSettings, field.mName = jpegSettings field.mType = Octane::ImageExportSettings::JpegExportSettings, protoType=JpegExportSettings
    ImageExportSettings_ImageExportSettings_JpegExportSettingsConverter::convert( in.jpegsettings(), out.mJpegSettings );
    // all fields resolved OK;
}


void ImageExportSettingsConverter::convert(
    const Octane::ImageExportSettings & in,
    octaneapi::ImageExportSettings & out)
{

    // Found structure 1 ImageExportSettings
    // from octane type = const Octane::ImageExportSettings &,
        //to proto type = octaneapi::ImageExportSettings &
    // list out parameters
    out.set_filetype( static_cast<octaneapi::SaveImageFileType>(in.mFileType)); // enum 2
    out.set_format( static_cast<octaneapi::ImageSaveFormat>(in.mFormat)); // enum 2
    out.set_premultipliedalphatype( static_cast<octaneapi::PremultipliedAlphaType>(in.mPremultipliedAlphaType)); // enum 2
    octaneapi::ImageExportSettings_ImageExportSettings_ExrExportSettings * exrSettingsOut = 
         new octaneapi::ImageExportSettings_ImageExportSettings_ExrExportSettings;
    ImageExportSettings_ImageExportSettings_ExrExportSettingsConverter::convert( in.mExrSettings, *exrSettingsOut);
    out.set_allocated_exrsettings(exrSettingsOut);
    octaneapi::ImageExportSettings_ImageExportSettings_TiffExportSettings * tiffSettingsOut = 
         new octaneapi::ImageExportSettings_ImageExportSettings_TiffExportSettings;
    ImageExportSettings_ImageExportSettings_TiffExportSettingsConverter::convert( in.mTiffSettings, *tiffSettingsOut);
    out.set_allocated_tiffsettings(tiffSettingsOut);
    octaneapi::ImageExportSettings_ImageExportSettings_JpegExportSettings * jpegSettingsOut = 
         new octaneapi::ImageExportSettings_ImageExportSettings_JpegExportSettings;
    ImageExportSettings_ImageExportSettings_JpegExportSettingsConverter::convert( in.mJpegSettings, *jpegSettingsOut);
    out.set_allocated_jpegsettings(jpegSettingsOut);
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
