// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace octaneapi { class ReferencePackageExportSettings; }
namespace Octane { struct ReferencePackageExportSettings; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

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

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
