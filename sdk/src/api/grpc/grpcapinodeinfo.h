// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
#include "octaneinfos.h"
#include "grpcbase.h"

namespace OctaneGRPC
{
    class GRPCSettings;

    struct ApiNodeInfoProxy : public Octane::ApiNodeInfo, GRPCBase
    {
        std::vector<Octane::ApiCompatibilityModeInfo> mCompatibilityModeInfos;

        GRPCSettings& getGRPCSettings();
    };
} // namespace OctaneGRPC

#endif //#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)