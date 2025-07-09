// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertreferencepackageexportsettings.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"

#include "octanereferenceexport.grpc.pb.h"
#include "octanereferenceexport.h"
#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

void ReferencePackageExportSettingsConverter::convert(
    const Octane::ReferencePackageExportSettings & in,
    octaneapi::ReferencePackageExportSettings & out)
{

    // Found structure 1 ReferencePackageExportSettings
    // from octane type = const Octane::ReferencePackageExportSettings &,
        //to proto type = octaneapi::ReferencePackageExportSettings &
    // list out parameters
    out.set_mergescatterinstances(in.mMergeScatterInstances);////simple 4b////
    out.set_includeinstancepercentage(in.mIncludeInstancePercentage);////simple 4b////
    out.set_ignoresmallobjectpercentage(in.mIgnoreSmallObjectPercentage);////simple 4b////
    out.set_exportanimation(in.mExportAnimation);////simple 4b////
    out.set_animationframerate(in.mAnimationFramerate);////simple 4b////
    out.set_enablecustomanimationtimespan(in.mEnableCustomAnimationTimespan);////simple 4b////

    octaneapi::TimeSpanT * customAnimationTimespanOut = new octaneapi::TimeSpanT;////approved////
    customAnimationTimespanOut->mutable_begin()->set_value(in.mCustomAnimationTimespan.begin);
    customAnimationTimespanOut->mutable_end()->set_value(in.mCustomAnimationTimespan.end);
    out.set_allocated_customanimationtimespan(customAnimationTimespanOut);
    out.set_exportnestedreferencegraphs(in.mExportNestedReferenceGraphs);////simple 4b////
    // all fields resolved OK;
}


void ReferencePackageExportSettingsConverter::convert(
    const octaneapi::ReferencePackageExportSettings & in,
    Octane::ReferencePackageExportSettings & out)
{

    // Found structure 1 ReferencePackageExportSettings
    // from proto type = const octaneapi::ReferencePackageExportSettings &,
        //to octane type = Octane::ReferencePackageExportSettings &
    // list out parameters
    //cl=ReferencePackageExportSettings, field.mName = mergeScatterInstances field.mType = bool, protoType=bool
    out.mMergeScatterInstances = in.mergescatterinstances();////simple 3////
    //cl=ReferencePackageExportSettings, field.mName = includeInstancePercentage field.mType = float, protoType=float
    out.mIncludeInstancePercentage = in.includeinstancepercentage();////simple 3////
    //cl=ReferencePackageExportSettings, field.mName = ignoreSmallObjectPercentage field.mType = float, protoType=float
    out.mIgnoreSmallObjectPercentage = in.ignoresmallobjectpercentage();////simple 3////
    //cl=ReferencePackageExportSettings, field.mName = exportAnimation field.mType = bool, protoType=bool
    out.mExportAnimation = in.exportanimation();////simple 3////
    //cl=ReferencePackageExportSettings, field.mName = animationFramerate field.mType = float, protoType=float
    out.mAnimationFramerate = in.animationframerate();////simple 3////
    //cl=ReferencePackageExportSettings, field.mName = enableCustomAnimationTimespan field.mType = bool, protoType=bool
    out.mEnableCustomAnimationTimespan = in.enablecustomanimationtimespan();////simple 3////
    //cl=ReferencePackageExportSettings, field.mName = customAnimationTimespan field.mType = Octane::TimeSpanT, protoType=TimeSpanT

    const octaneapi::TimeSpanT & customAnimationTimespanRef = in.customanimationtimespan();
    out.mCustomAnimationTimespan.begin = customAnimationTimespanRef.begin().value();
    out.mCustomAnimationTimespan.end   = customAnimationTimespanRef.end().value();
    //cl=ReferencePackageExportSettings, field.mName = exportNestedReferenceGraphs field.mType = bool, protoType=bool
    out.mExportNestedReferenceGraphs = in.exportnestedreferencegraphs();////simple 3////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
