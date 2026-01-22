// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiMouseWheelDetails; }
namespace octaneapi { class ApiMouseWheelDetails; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiMouseWheelDetailsConverter
{
public:
    static void convert(
        const octaneapi::ApiMouseWheelDetails & in,
        Octane::ApiMouseWheelDetails & out);

    static void convert(
        const Octane::ApiMouseWheelDetails & in,
        octaneapi::ApiMouseWheelDetails & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
