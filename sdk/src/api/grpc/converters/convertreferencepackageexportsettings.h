// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace octaneapi { class ReferencePackageExportSettings; }
namespace Octane { struct ReferencePackageExportSettings; }

class ApiNodeInfoProxy;
class ReferencePackageExportSettingsConverter
{
public:
    static void convert(
        const Octane::ReferencePackageExportSettings & in,
        octaneapi::ReferencePackageExportSettings & out);

    static void convert(
        const octaneapi::ReferencePackageExportSettings & in,
        Octane::ReferencePackageExportSettings & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
