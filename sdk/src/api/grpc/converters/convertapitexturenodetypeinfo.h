// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiTextureNodeTypeInfo; }
namespace octaneapi { class ApiTextureNodeTypeInfo; }

struct ApiNodeInfoProxy;
class ApiTextureNodeTypeInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiTextureNodeTypeInfo & in,
        Octane::ApiTextureNodeTypeInfo & out);

    static void convert(
        const Octane::ApiTextureNodeTypeInfo & in,
        octaneapi::ApiTextureNodeTypeInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
