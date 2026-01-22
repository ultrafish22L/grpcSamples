// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertimageexportsettings_imageexportsettings_exrexportsettings.h"
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

void ImageExportSettings_ImageExportSettings_ExrExportSettingsConverter::convert(
    const octaneapi::ImageExportSettings_ImageExportSettings_ExrExportSettings & in,
    Octane::ImageExportSettings::ExrExportSettings & out)
{

    // Found structure 4 ExrExportSettings
    // from proto type = const octaneapi::ImageExportSettings_ImageExportSettings_ExrExportSettings &,
        //to octane type = Octane::ImageExportSettings::ExrExportSettings &
    // list out parameters
    //cl=ExrExportSettings, field.mName = compressionType field.mType = Octane::ExrCompressionType, protoType=ExrCompressionType
    out.mCompressionType = static_cast<Octane::ExrCompressionType>(in.compressiontype());// enum 1 
    //cl=ExrExportSettings, field.mName = compressionLevel field.mType = float, protoType=float
    out.mCompressionLevel = in.compressionlevel();////simple 3////
    // all fields resolved OK;
}


void ImageExportSettings_ImageExportSettings_ExrExportSettingsConverter::convert(
    const Octane::ImageExportSettings::ExrExportSettings & in,
    octaneapi::ImageExportSettings_ImageExportSettings_ExrExportSettings & out)
{

    // Found structure 3 ExrExportSettings
    // from octane type = const Octane::ImageExportSettings::ExrExportSettings &,
        //to proto type = octaneapi::ImageExportSettings_ImageExportSettings_ExrExportSettings &
    // list out parameters
    out.set_compressiontype( static_cast<octaneapi::ExrCompressionType>(in.mCompressionType)); // enum 2
    out.set_compressionlevel(in.mCompressionLevel);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
