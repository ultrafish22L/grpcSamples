// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct NetRenderStatus; }
namespace octaneapi { class NetRenderStatus; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class NetRenderStatusConverter
{
public:
    static void convert(
        const octaneapi::NetRenderStatus & in,
        Octane::NetRenderStatus & out);

    static void convert(
        const Octane::NetRenderStatus & in,
        octaneapi::NetRenderStatus & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
