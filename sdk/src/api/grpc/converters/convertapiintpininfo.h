// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiIntPinInfo; }
namespace octaneapi { class ApiIntPinInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiIntPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiIntPinInfo & in,
        Octane::ApiIntPinInfo & out);

    static void convert(
        const Octane::ApiIntPinInfo & in,
        octaneapi::ApiIntPinInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
