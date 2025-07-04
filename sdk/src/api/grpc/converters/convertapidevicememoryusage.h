// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiDeviceMemoryUsage; }
namespace octaneapi { class ApiDeviceMemoryUsage; }

struct ApiNodeInfoProxy;
class ApiDeviceMemoryUsageConverter
{
public:
    static void convert(
        const octaneapi::ApiDeviceMemoryUsage & in,
        Octane::ApiDeviceMemoryUsage & out);

    static void convert(
        const Octane::ApiDeviceMemoryUsage & in,
        octaneapi::ApiDeviceMemoryUsage & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
