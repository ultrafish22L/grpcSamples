// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiFilePath; }
namespace octaneapi { class ApiFilePath; }

struct ApiNodeInfoProxy;
class ApiFilePathConverter
{
public:
    static void convert(
        const octaneapi::ApiFilePath & in,
        Octane::ApiFilePath & out);

    static void convert(
        const Octane::ApiFilePath & in,
        octaneapi::ApiFilePath & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
