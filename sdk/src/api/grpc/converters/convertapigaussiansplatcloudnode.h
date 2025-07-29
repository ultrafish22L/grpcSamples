// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiGaussianSplatCloudNode; }
namespace octaneapi { class ApiGaussianSplatCloudNode; }

struct ApiNodeInfoProxy;
class ApiGaussianSplatCloudNodeConverter
{
public:
    static void convert(
        const octaneapi::ApiGaussianSplatCloudNode & in,
        Octane::ApiGaussianSplatCloudNode & out);

    static void convert(
        const Octane::ApiGaussianSplatCloudNode & in,
        octaneapi::ApiGaussianSplatCloudNode & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
