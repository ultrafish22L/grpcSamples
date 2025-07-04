// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace octaneapi { class RenderPassExport; }
namespace Octane { struct RenderPassExport; }

struct ApiNodeInfoProxy;
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
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
