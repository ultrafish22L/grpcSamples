// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiOcioColorSpacePinInfo; }
namespace octaneapi { class ApiOcioColorSpacePinInfo; }

struct ApiNodeInfoProxy;
class ApiOcioColorSpacePinInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiOcioColorSpacePinInfo & in,
        Octane::ApiOcioColorSpacePinInfo & out);

    static void convert(
        const Octane::ApiOcioColorSpacePinInfo & in,
        octaneapi::ApiOcioColorSpacePinInfo & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
