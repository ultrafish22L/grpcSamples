// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapirenderpassinfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apiinfo.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apiinfo.h"

#include "octanerenderpasses.h"
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

void ApiRenderPassInfoConverter::convert(
    const octaneapi::ApiRenderPassInfo & in,
    Octane::ApiRenderPassInfo & out)
{

    // Found structure 1 ApiRenderPassInfo
    // from proto type = const octaneapi::ApiRenderPassInfo &,
        //to octane type = Octane::ApiRenderPassInfo &
    // list out parameters
    //cl=ApiRenderPassInfo, field.mName = renderPassId field.mType = Octane::RenderPassId, protoType=RenderPassId
    out.mRenderPassId = static_cast<Octane::RenderPassId>(in.renderpassid());// enum 1 
    //cl=ApiRenderPassInfo, field.mName = nodeType field.mType = Octane::NodeType, protoType=NodeType
    out.mNodeType = static_cast<Octane::NodeType>(in.nodetype());// enum 1 
    //cl=ApiRenderPassInfo, field.mName = subType field.mType = Octane::enum_t, protoType=enum_t
    //TES84565388 

    const octaneapi::enum_t & subTypeRef = in.subtype();
    out.mSubType = subTypeRef.id();
    //cl=ApiRenderPassInfo, field.mName = pinId field.mType = Octane::PinId, protoType=PinId
    out.mPinId = static_cast<Octane::PinId>(in.pinid());// enum 1 
    //cl=ApiRenderPassInfo, field.mName = name field.mType = const char *, protoType=string
    out.mName =  (char*)StringManager::getInstance().addString(in.name());
    //cl=ApiRenderPassInfo, field.mName = exrLayerName field.mType = const char *, protoType=string
    out.mExrLayerName =  (char*)StringManager::getInstance().addString(in.exrlayername());
    //cl=ApiRenderPassInfo, field.mName = shortName field.mType = const char *, protoType=string
    out.mShortName =  (char*)StringManager::getInstance().addString(in.shortname());
    //cl=ApiRenderPassInfo, field.mName = description field.mType = const char *, protoType=string
    out.mDescription =  (char*)StringManager::getInstance().addString(in.description());
    //cl=ApiRenderPassInfo, field.mName = category field.mType = const char *, protoType=string
    out.mCategory =  (char*)StringManager::getInstance().addString(in.category());
    //cl=ApiRenderPassInfo, field.mName = isInfoPass field.mType = bool, protoType=bool
    out.mIsInfoPass = in.isinfopass();////simple 3////
    //cl=ApiRenderPassInfo, field.mName = isGreyscale field.mType = bool, protoType=bool
    out.mIsGreyscale = in.isgreyscale();////simple 3////
    //cl=ApiRenderPassInfo, field.mName = renderPassGroupId field.mType = Octane::RenderPassGroupId, protoType=RenderPassGroupId
    out.mRenderPassGroupId = static_cast<Octane::RenderPassGroupId>(in.renderpassgroupid());// enum 1 
    // all fields resolved OK;
}


void ApiRenderPassInfoConverter::convert(
    const Octane::ApiRenderPassInfo & in,
    octaneapi::ApiRenderPassInfo & out)
{

    // Found structure 1 ApiRenderPassInfo
    // from octane type = const Octane::ApiRenderPassInfo &,
        //to proto type = octaneapi::ApiRenderPassInfo &
    // list out parameters
    out.set_renderpassid( static_cast<octaneapi::RenderPassId>(in.mRenderPassId)); // enum 2
    out.set_nodetype( static_cast<octaneapi::NodeType>(in.mNodeType)); // enum 2
    //TEST123123 

    octaneapi::enum_t * subTypeOut = new octaneapi::enum_t;////133//approved////
    subTypeOut->set_id(in.mSubType);
    out.set_allocated_subtype(subTypeOut);
    out.set_pinid( static_cast<octaneapi::PinId>(in.mPinId)); // enum 2

    std::string * nameStr = new std::string();////approved//// 
    *nameStr = StringManager::checkString(in.mName);
    out.set_allocated_name(nameStr);

    std::string * exrLayerNameStr = new std::string();////approved//// 
    *exrLayerNameStr = StringManager::checkString(in.mExrLayerName);
    out.set_allocated_exrlayername(exrLayerNameStr);

    std::string * shortNameStr = new std::string();////approved//// 
    *shortNameStr = StringManager::checkString(in.mShortName);
    out.set_allocated_shortname(shortNameStr);

    std::string * descriptionStr = new std::string();////approved//// 
    *descriptionStr = StringManager::checkString(in.mDescription);
    out.set_allocated_description(descriptionStr);

    std::string * categoryStr = new std::string();////approved//// 
    *categoryStr = StringManager::checkString(in.mCategory);
    out.set_allocated_category(categoryStr);
    out.set_isinfopass(in.mIsInfoPass);////simple 4b////
    out.set_isgreyscale(in.mIsGreyscale);////simple 4b////
    out.set_renderpassgroupid( static_cast<octaneapi::RenderPassGroupId>(in.mRenderPassGroupId)); // enum 2
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
