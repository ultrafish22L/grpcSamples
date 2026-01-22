// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiNodeGraphInfo; }
namespace octaneapi { class ApiNodeGraphInfo; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiNodeGraphInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiNodeGraphInfo & in,
        Octane::ApiNodeGraphInfo & out);

    static void convert(
        const Octane::ApiNodeGraphInfo & in,
        octaneapi::ApiNodeGraphInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
