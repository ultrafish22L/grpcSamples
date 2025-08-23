// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertnetrenderstatus.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apinetrendermanager.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apinetrendermanager.h"

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

void NetRenderStatusConverter::convert(
    const octaneapi::NetRenderStatus & in,
    Octane::NetRenderStatus & out)
{

    // Found structure 1 NetRenderStatus
    // from proto type = const octaneapi::NetRenderStatus &,
        //to octane type = Octane::NetRenderStatus &
    // list out parameters
    //cl=NetRenderStatus, field.mName = netSlaveCount field.mType = unsigned int, protoType=uint32
    out.mNetSlaveCount = in.netslavecount();////simple 3////
    //cl=NetRenderStatus, field.mName = updatingNetSlaveCount field.mType = unsigned int, protoType=uint32
    out.mUpdatingNetSlaveCount = in.updatingnetslavecount();////simple 3////
    //cl=NetRenderStatus, field.mName = updatedNetSlaveCount field.mType = unsigned int, protoType=uint32
    out.mUpdatedNetSlaveCount = in.updatednetslavecount();////simple 3////
    //cl=NetRenderStatus, field.mName = pendingSize field.mType = size_t, protoType=uint32
    out.mPendingSize = in.pendingsize();////simple 3////
    //cl=NetRenderStatus, field.mName = totalSize field.mType = size_t, protoType=uint32
    out.mTotalSize = in.totalsize();////simple 3////
    //cl=NetRenderStatus, field.mName = netGpuCount field.mType = unsigned int, protoType=uint32
    out.mNetGpuCount = in.netgpucount();////simple 3////
    //cl=NetRenderStatus, field.mName = inUseNetGpuCount field.mType = unsigned int, protoType=uint32
    out.mInUseNetGpuCount = in.inusenetgpucount();////simple 3////
    //cl=NetRenderStatus, field.mName = canRenderUsingRenderNodes field.mType = bool, protoType=bool
    out.mCanRenderUsingRenderNodes = in.canrenderusingrendernodes();////simple 3////
    // all fields resolved OK;
}


void NetRenderStatusConverter::convert(
    const Octane::NetRenderStatus & in,
    octaneapi::NetRenderStatus & out)
{

    // Found structure 1 NetRenderStatus
    // from octane type = const Octane::NetRenderStatus &,
        //to proto type = octaneapi::NetRenderStatus &
    // list out parameters
    out.set_netslavecount(in.mNetSlaveCount);////simple 4b////
    out.set_updatingnetslavecount(in.mUpdatingNetSlaveCount);////simple 4b////
    out.set_updatednetslavecount(in.mUpdatedNetSlaveCount);////simple 4b////
    out.set_pendingsize(static_cast<uint32_t>(in.mPendingSize));////simple 4////
    out.set_totalsize(static_cast<uint32_t>(in.mTotalSize));////simple 4////
    out.set_netgpucount(in.mNetGpuCount);////simple 4b////
    out.set_inusenetgpucount(in.mInUseNetGpuCount);////simple 4b////
    out.set_canrenderusingrendernodes(in.mCanRenderUsingRenderNodes);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
