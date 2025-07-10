// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct NetRenderSettings; }
namespace octaneapi { class NetRenderSettings; }

class ApiNodeInfoProxy;
class NetRenderSettingsConverter
{
public:
    static void convert(
        const octaneapi::NetRenderSettings & in,
        Octane::NetRenderSettings & out);

    static void convert(
        const Octane::NetRenderSettings & in,
        octaneapi::NetRenderSettings & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
