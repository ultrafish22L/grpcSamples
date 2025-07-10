// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ImageExportSettings; }
namespace octaneapi { class ImageExportSettings; }

class ApiNodeInfoProxy;
class ImageExportSettingsConverter
{
public:
    static void convert(
        const octaneapi::ImageExportSettings & in,
        Octane::ImageExportSettings & out);

    static void convert(
        const Octane::ImageExportSettings & in,
        octaneapi::ImageExportSettings & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
