// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneimageexport.grpc.pb.h"
#include <functional>
#include "octaneimageexport.h"
namespace octaneapi { class ImageExportSettings_ImageExportSettings_ExrExportSettings; }
struct ApiNodeInfoProxy;
class ImageExportSettings_ImageExportSettings_ExrExportSettingsConverter
{
public:
    static void convert(
        const octaneapi::ImageExportSettings_ImageExportSettings_ExrExportSettings & in,
        Octane::ImageExportSettings::ExrExportSettings & out);

    static void convert(
        const Octane::ImageExportSettings::ExrExportSettings & in,
        octaneapi::ImageExportSettings_ImageExportSettings_ExrExportSettings & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
