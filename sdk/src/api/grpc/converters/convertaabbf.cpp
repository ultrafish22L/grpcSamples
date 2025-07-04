// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertaabbf.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"

#include "common.grpc.pb.h"
#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

void AABBFConverter::convert(
    const octaneapi::AABBF & in,
    Octane::AABBF & out)
{

    // Ensure exactly 3 elements are provided for both repeated fields.
    if(in.pmin_size() != 3 && in.pmax_size() != 3)
    {
        return;
    }
    for (int i = 0; i < 3; ++i)
    {
        out.pmin[i] = in.pmin(i);
        out.pmax[i] = in.pmax(i);
    }
}


void AABBFConverter::convert(
    const Octane::AABBF & in,
    octaneapi::AABBF & out)
{

    out.clear_pmin();
    out.clear_pmax();
    // Fill the repeated fields with exactly 3 values.
    for (int i = 0; i < 3; ++i)
    {
        out.add_pmin(in.pmin[i]);
    }
    for (int i = 0; i < 3; ++i)
    {
        out.add_pmax(in.pmax[i]);
    }
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
