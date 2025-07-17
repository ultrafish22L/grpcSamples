// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiRenderPassInfo; }
namespace octaneapi { class ApiRenderPassInfo; }

class ApiNodeInfoProxy;
class ApiRenderPassInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiRenderPassInfo & in,
        Octane::ApiRenderPassInfo & out);

    static void convert(
        const Octane::ApiRenderPassInfo & in,
        octaneapi::ApiRenderPassInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
