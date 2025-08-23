// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitimesampling.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apinodesystem_1.grpc.pb.h"
#include "apinodesystem_3.grpc.pb.h"
#include "apinodesystem_5.grpc.pb.h"
#include "apinodesystem_6.grpc.pb.h"
#include "apinodesystem_7.grpc.pb.h"
#include "apinodesystem_8.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apinodesystem.h"

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

void ApiTimeSamplingConverter::convert(
    const Octane::ApiTimeSampling & in,
    octaneapi::ApiTimeSampling & out)
{

    // Found structure 1 ApiTimeSampling
    // from octane type = const Octane::ApiTimeSampling &,
        //to proto type = octaneapi::ApiTimeSampling &
    // list out parameters
   // 1D array
    //TEST 89rr765 
    octaneapi::TimeArrayT * patternOut = new octaneapi::TimeArrayT;////approved////
    for(size_t h = 0; h < in.mPatternSize; h++)
    {
        auto item = patternOut->add_data();
        item->set_value(in.mPattern[h]);
    }
    out.set_allocated_pattern(patternOut);
    out.set_patternsize(static_cast<uint32_t>(in.mPatternSize));////simple 4////

    octaneapi::TimeT * periodOut = new octaneapi::TimeT;////approved////
    periodOut->set_value(in.mPeriod);
    out.set_allocated_period(periodOut);////TimeT////
    out.set_animationtype( static_cast<octaneapi::AnimationType>(in.mAnimationType)); // enum 2

    octaneapi::TimeT * endTimeOut = new octaneapi::TimeT;////approved////
    endTimeOut->set_value(in.mEndTime);
    out.set_allocated_endtime(endTimeOut);////TimeT////
    // all fields resolved OK;
}


void ApiTimeSamplingConverter::convert(
    const octaneapi::ApiTimeSampling & in,
    Octane::ApiTimeSampling & out)
{

    // Found structure 1 ApiTimeSampling
    // from proto type = const octaneapi::ApiTimeSampling &,
        //to octane type = Octane::ApiTimeSampling &
    // list out parameters
    //cl=ApiTimeSampling, field.mName = pattern field.mType = const Octane::TimeT *, protoType=TimeArrayT
    //TEST 89765 
    Octane::TimeT * patternTemp = new Octane::TimeT[in.pattern().data_size()];////221////
    // Store the array for auto deletion. The pointer returned to the caller will be valid until the next time this function is called.
    ObjectStore::getInstance().addPointer<Octane::TimeT>("pattern", patternTemp);
    for(int h = 0; h < in.pattern().data_size(); h++)
    {
        patternTemp[h] = static_cast<Octane::TimeT>(in.pattern().data(h).value());
    }
    // memory leak
    out.mPattern = patternTemp;
    //cl=ApiTimeSampling, field.mName = patternSize field.mType = size_t, protoType=uint32
    out.mPatternSize = in.patternsize();////simple 3////
    //cl=ApiTimeSampling, field.mName = period field.mType = Octane::TimeT, protoType=TimeT
    out.mPeriod = in.period().value();////TimeT////
    //cl=ApiTimeSampling, field.mName = animationType field.mType = Octane::AnimationType, protoType=AnimationType
    out.mAnimationType = static_cast<Octane::AnimationType>(in.animationtype());// enum 1 
    //cl=ApiTimeSampling, field.mName = endTime field.mType = Octane::TimeT, protoType=TimeT
    out.mEndTime = in.endtime().value();////TimeT////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
