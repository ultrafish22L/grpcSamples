// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiGeometryStatistics; }
namespace octaneapi { class ApiGeometryStatistics; }

struct ApiNodeInfoProxy;
class ApiGeometryStatisticsConverter
{
public:
    static void convert(
        const octaneapi::ApiGeometryStatistics & in,
        Octane::ApiGeometryStatistics & out);

    static void convert(
        const Octane::ApiGeometryStatistics & in,
        octaneapi::ApiGeometryStatistics & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
