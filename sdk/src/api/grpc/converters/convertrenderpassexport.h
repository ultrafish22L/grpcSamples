// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace octaneapi { class RenderPassExport; }
namespace Octane { struct RenderPassExport; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class RenderPassExportConverter
{
public:
    static void convert(
        const Octane::RenderPassExport & in,
        octaneapi::RenderPassExport & out);

    static void convert(
        const octaneapi::RenderPassExport & in,
        Octane::RenderPassExport & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
