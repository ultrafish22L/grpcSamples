// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneenums.grpc.pb.h"
#include "octanerenderpasses.grpc.pb.h"
#include "apirender.h"
#include "octaneenums.h"
#include "octanerenderpasses.h"
namespace Octane { struct RenderResultStatistics; }
namespace octaneapi { class RenderResultStatistics; }

struct ApiNodeInfoProxy;
class RenderResultStatisticsConverter
{
public:
    static void convert(
        const octaneapi::RenderResultStatistics & in,
        Octane::RenderResultStatistics & out);

    static void convert(
        const Octane::RenderResultStatistics & in,
        octaneapi::RenderResultStatistics & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
