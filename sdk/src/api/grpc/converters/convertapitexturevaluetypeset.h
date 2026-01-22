// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiTextureValueTypeSet; }
namespace octaneapi { class ApiTextureValueTypeSet; }

namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiTextureValueTypeSetConverter
{
public:
    static void convert(
        const octaneapi::ApiTextureValueTypeSet & in,
        Octane::ApiTextureValueTypeSet & out);

    static void convert(
        const Octane::ApiTextureValueTypeSet & in,
        octaneapi::ApiTextureValueTypeSet & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
