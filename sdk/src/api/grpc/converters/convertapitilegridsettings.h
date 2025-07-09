// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
namespace Octane { struct ApiTileGridSettings; }
namespace octaneapi { class ApiTileGridSettings; }

struct ApiNodeInfoProxy;
class ApiTileGridSettingsConverter
{
public:
    static void convert(
        const octaneapi::ApiTileGridSettings & in,
        Octane::ApiTileGridSettings & out);

    static void convert(
        const Octane::ApiTileGridSettings & in,
        octaneapi::ApiTileGridSettings & out);
};
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
