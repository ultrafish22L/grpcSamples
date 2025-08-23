// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapirendercloudmanager_apirendercloudmanager_subscriptioninfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apirendercloudmanager.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apirendercloudmanager.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

namespace OctaneGRPC
{

void ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfoConverter::convert(
    const octaneapi::ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfo & in,
    Octane::ApiRenderCloudManager::SubscriptionInfo & out)
{

    // Found structure 4 SubscriptionInfo
    // from proto type = const octaneapi::ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfo &,
        //to octane type = Octane::ApiRenderCloudManager::SubscriptionInfo &
    // list out parameters
    //cl=SubscriptionInfo, field.mName = subscribed field.mType = bool, protoType=bool
    out.mSubscribed = in.subscribed();////simple 3////
    //cl=SubscriptionInfo, field.mName = availableCreditBalance field.mType = float, protoType=float
    out.mAvailableCreditBalance = in.availablecreditbalance();////simple 3////
    //cl=SubscriptionInfo, field.mName = availableRndrBalance field.mType = float, protoType=float
    out.mAvailableRndrBalance = in.availablerndrbalance();////simple 3////
    // all fields resolved OK;
}


void ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfoConverter::convert(
    const Octane::ApiRenderCloudManager::SubscriptionInfo & in,
    octaneapi::ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfo & out)
{

    // Found structure 3 SubscriptionInfo
    // from octane type = const Octane::ApiRenderCloudManager::SubscriptionInfo &,
        //to proto type = octaneapi::ApiRenderCloudManager_ApiRenderCloudManager_SubscriptionInfo &
    // list out parameters
    out.set_subscribed(in.mSubscribed);////simple 4b////
    out.set_availablecreditbalance(in.mAvailableCreditBalance);////simple 4b////
    out.set_availablerndrbalance(in.mAvailableRndrBalance);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
