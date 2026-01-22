// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertrenderpassexport.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"

#include "octanerenderpasses.h"
#include "octaneenums.grpc.pb.h"
#include "octanerenderpasses.grpc.pb.h"
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

void RenderPassExportConverter::convert(
    const Octane::RenderPassExport & in,
    octaneapi::RenderPassExport & out)
{

    // Found structure 1 RenderPassExport
    // from octane type = const Octane::RenderPassExport &,
        //to proto type = octaneapi::RenderPassExport &
    // list out parameters
    out.set_renderpassid( static_cast<octaneapi::RenderPassId>(in.mRenderPassId)); // enum 2

    std::string * exportNameStr = new std::string();////approved//// 
    *exportNameStr = StringManager::checkString(in.mExportName);
    out.set_allocated_exportname(exportNameStr);
    // all fields resolved OK;
}


void RenderPassExportConverter::convert(
    const octaneapi::RenderPassExport & in,
    Octane::RenderPassExport & out)
{

    // Found structure 1 RenderPassExport
    // from proto type = const octaneapi::RenderPassExport &,
        //to octane type = Octane::RenderPassExport &
    // list out parameters
    //cl=RenderPassExport, field.mName = renderPassId field.mType = Octane::RenderPassId, protoType=RenderPassId
    out.mRenderPassId = static_cast<Octane::RenderPassId>(in.renderpassid());// enum 1 
    //cl=RenderPassExport, field.mName = exportName field.mType = const char *, protoType=string
    out.mExportName =  (char*)StringManager::getInstance().addString(in.exportname());
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
