// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiTransformPinInfo; }
namespace octaneapi { class ApiTransformPinInfo; }

class ApiNodeInfoProxy;
class ApiTransformPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiTransformPinInfo & in,
        Octane::ApiTransformPinInfo & out);

    static void convert(
        const Octane::ApiTransformPinInfo & in,
        octaneapi::ApiTransformPinInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
