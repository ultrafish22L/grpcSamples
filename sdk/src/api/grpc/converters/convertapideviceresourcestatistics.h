// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiDeviceResourceStatistics; }
namespace octaneapi { class ApiDeviceResourceStatistics; }

class ApiNodeInfoProxy;
class ApiDeviceResourceStatisticsConverter
{
public:
    static void convert(
        const octaneapi::ApiDeviceResourceStatistics & in,
        Octane::ApiDeviceResourceStatistics & out);

    static void convert(
        const Octane::ApiDeviceResourceStatistics & in,
        octaneapi::ApiDeviceResourceStatistics & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
