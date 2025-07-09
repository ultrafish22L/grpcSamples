// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "apitimesampling.h"
namespace Octane { struct ApiTimeSampling; }
namespace octaneapi { class ApiTimeSampling; }

class ApiNodeInfoProxy;
class ApiTimeSamplingConverter
{
public:
    static void convert(
        const octaneapi::ApiTimeSampling & in,
        Octane::ApiTimeSampling & out);

    static void convert(
        const Octane::ApiTimeSampling & in,
        octaneapi::ApiTimeSampling & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
