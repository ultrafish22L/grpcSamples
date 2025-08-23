// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { class ApiCompatibilityModeInfo; }
namespace octaneapi { class ApiCompatibilityModeInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiCompatibilityModeInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiCompatibilityModeInfo & in,
        Octane::ApiCompatibilityModeInfo & out);

    static void convert(
        const Octane::ApiCompatibilityModeInfo & in,
        octaneapi::ApiCompatibilityModeInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
