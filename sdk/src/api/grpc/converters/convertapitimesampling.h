// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "apitimesampling.h"
namespace octaneapi { class ApiTimeSampling; }
namespace Octane { struct ApiTimeSampling; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiTimeSamplingConverter
{
public:
    static void convert(
        const Octane::ApiTimeSampling & in,
        octaneapi::ApiTimeSampling & out);

    static void convert(
        const octaneapi::ApiTimeSampling & in,
        Octane::ApiTimeSampling & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
