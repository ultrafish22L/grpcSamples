// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiBitMaskPinInfo; }
namespace octaneapi { class ApiBitMaskPinInfo; }

class ApiNodeInfoProxy;
class ApiBitMaskPinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiBitMaskPinInfo & in,
        Octane::ApiBitMaskPinInfo & out);

    static void convert(
        const Octane::ApiBitMaskPinInfo & in,
        octaneapi::ApiBitMaskPinInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
