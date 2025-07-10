// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "apirender.h"
namespace octaneapi { class ApiArrayApiRenderImage; }
class ApiNodeInfoProxy;
class ApiArrayApiRenderImageConverter
{
public:
    static void convert(
        const octaneapi::ApiArrayApiRenderImage & in,
        Octane::ApiArray<Octane::ApiRenderImage> & out);

    static void convert(
        const Octane::ApiArray<Octane::ApiRenderImage> & in,
        octaneapi::ApiArrayApiRenderImage & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
