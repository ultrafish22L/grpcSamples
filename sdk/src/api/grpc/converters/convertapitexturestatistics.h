// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiTextureStatistics; }
namespace octaneapi { class ApiTextureStatistics; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiTextureStatisticsConverter
{
public:
    static void convert(
        const octaneapi::ApiTextureStatistics & in,
        Octane::ApiTextureStatistics & out);

    static void convert(
        const Octane::ApiTextureStatistics & in,
        octaneapi::ApiTextureStatistics & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
