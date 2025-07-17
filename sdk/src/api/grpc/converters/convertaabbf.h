// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneaabb.h"
namespace octaneapi { class AABBF; }
class ApiNodeInfoProxy;
class AABBFConverter
{
public:
    static void convert(
        const octaneapi::AABBF & in,
        Octane::AABBF & out);

    static void convert(
        const Octane::AABBF & in,
        octaneapi::AABBF & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
