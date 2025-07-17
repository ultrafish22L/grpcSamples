// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitexturevaluetypeset.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "octaneinfos.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneinfos.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
class ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiTextureValueTypeSetConverter::convert(
    const octaneapi::ApiTextureValueTypeSet & in,
    Octane::ApiTextureValueTypeSet & out)
{

    // Found structure 1 ApiTextureValueTypeSet
    // from proto type = const octaneapi::ApiTextureValueTypeSet &,
        //to octane type = Octane::ApiTextureValueTypeSet &
    // list out parameters
    // all fields resolved OK;
}


void ApiTextureValueTypeSetConverter::convert(
    const Octane::ApiTextureValueTypeSet & in,
    octaneapi::ApiTextureValueTypeSet & out)
{

    // Found structure 1 ApiTextureValueTypeSet
    // from octane type = const Octane::ApiTextureValueTypeSet &,
        //to proto type = octaneapi::ApiTextureValueTypeSet &
    // list out parameters
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
