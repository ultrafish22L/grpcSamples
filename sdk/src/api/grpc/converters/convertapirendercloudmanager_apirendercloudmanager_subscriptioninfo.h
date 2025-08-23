// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "apirendercloudmanager.h"
namespace octaneapi { class ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfo; }
namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfoConverter
{
public:
    static void convert(
        const octaneapi::ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfo & in,
        Octane::ApiRenderCloudManager::SubscriptionInfo & out);

    static void convert(
        const Octane::ApiRenderCloudManager::SubscriptionInfo & in,
        octaneapi::ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfo & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
