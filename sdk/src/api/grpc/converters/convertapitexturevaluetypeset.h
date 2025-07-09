// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiTextureValueTypeSet; }
namespace octaneapi { class ApiTextureValueTypeSet; }

struct ApiNodeInfoProxy;
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
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
