// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneimageexport.grpc.pb.h"
#include <functional>
#include "octaneimageexport.h"
namespace octaneapi { class ImageExportSettings_ImageExportSettings_JpegExportSettings; }
namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ImageExportSettings_ImageExportSettings_JpegExportSettingsConverter
{
public:
    static void convert(
        const octaneapi::ImageExportSettings_ImageExportSettings_JpegExportSettings & in,
        Octane::ImageExportSettings::JpegExportSettings & out);

    static void convert(
        const Octane::ImageExportSettings::JpegExportSettings & in,
        octaneapi::ImageExportSettings_ImageExportSettings_JpegExportSettings & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
