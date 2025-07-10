// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneimageexport.grpc.pb.h"
#include <functional>
#include "octaneimageexport.h"
namespace octaneapi { class ImageExportSettings_ImageExportSettings_JpegExportSettings; }
class ApiNodeInfoProxy;
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
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
