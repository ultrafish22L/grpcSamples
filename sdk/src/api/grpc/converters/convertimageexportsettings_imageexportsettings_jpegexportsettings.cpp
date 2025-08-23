// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertimageexportsettings_imageexportsettings_jpegexportsettings.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"

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

void ImageExportSettings_ImageExportSettings_JpegExportSettingsConverter::convert(
    const octaneapi::ImageExportSettings_ImageExportSettings_JpegExportSettings & in,
    Octane::ImageExportSettings::JpegExportSettings & out)
{

    // Found structure 4 JpegExportSettings
    // from proto type = const octaneapi::ImageExportSettings_ImageExportSettings_JpegExportSettings &,
        //to octane type = Octane::ImageExportSettings::JpegExportSettings &
    // list out parameters
    //cl=JpegExportSettings, field.mName = quality field.mType = float, protoType=float
    out.mQuality = in.quality();////simple 3////
    // all fields resolved OK;
}


void ImageExportSettings_ImageExportSettings_JpegExportSettingsConverter::convert(
    const Octane::ImageExportSettings::JpegExportSettings & in,
    octaneapi::ImageExportSettings_ImageExportSettings_JpegExportSettings & out)
{

    // Found structure 3 JpegExportSettings
    // from octane type = const Octane::ImageExportSettings::JpegExportSettings &,
        //to proto type = octaneapi::ImageExportSettings_ImageExportSettings_JpegExportSettings &
    // list out parameters
    out.set_quality(in.mQuality);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
