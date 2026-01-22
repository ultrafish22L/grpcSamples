// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertimageexportsettings_imageexportsettings_tiffexportsettings.h"
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

void ImageExportSettings_ImageExportSettings_TiffExportSettingsConverter::convert(
    const octaneapi::ImageExportSettings_ImageExportSettings_TiffExportSettings & in,
    Octane::ImageExportSettings::TiffExportSettings & out)
{

    // Found structure 4 TiffExportSettings
    // from proto type = const octaneapi::ImageExportSettings_ImageExportSettings_TiffExportSettings &,
        //to octane type = Octane::ImageExportSettings::TiffExportSettings &
    // list out parameters
    //cl=TiffExportSettings, field.mName = compressionType field.mType = Octane::TiffCompressionType, protoType=TiffCompressionType
    out.mCompressionType = static_cast<Octane::TiffCompressionType>(in.compressiontype());// enum 1 
    // all fields resolved OK;
}


void ImageExportSettings_ImageExportSettings_TiffExportSettingsConverter::convert(
    const Octane::ImageExportSettings::TiffExportSettings & in,
    octaneapi::ImageExportSettings_ImageExportSettings_TiffExportSettings & out)
{

    // Found structure 3 TiffExportSettings
    // from octane type = const Octane::ImageExportSettings::TiffExportSettings &,
        //to proto type = octaneapi::ImageExportSettings_ImageExportSettings_TiffExportSettings &
    // list out parameters
    out.set_compressiontype( static_cast<octaneapi::TiffCompressionType>(in.mCompressionType)); // enum 2
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
