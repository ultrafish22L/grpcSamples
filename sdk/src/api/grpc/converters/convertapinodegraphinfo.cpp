// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapinodegraphinfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apiinfo.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apiinfo.h"
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

void ApiNodeGraphInfoConverter::convert(
    const octaneapi::ApiNodeGraphInfo & in,
    Octane::ApiNodeGraphInfo & out)
{

    // Found structure 1 ApiNodeGraphInfo
    // from proto type = const octaneapi::ApiNodeGraphInfo &,
        //to octane type = Octane::ApiNodeGraphInfo &
    // list out parameters
    //cl=ApiNodeGraphInfo, field.mName = type field.mType = Octane::NodeGraphType, protoType=NodeGraphType
    out.mType = static_cast<Octane::NodeGraphType>(in.type());// enum 1 
    //cl=ApiNodeGraphInfo, field.mName = description field.mType = const char *, protoType=string
    out.mDescription =  (char*)StringManager::getInstance().addString(in.description());
    //cl=ApiNodeGraphInfo, field.mName = outType field.mType = Octane::NodePinType, protoType=NodePinType
    out.mOutType = static_cast<Octane::NodePinType>(in.outtype());// enum 1 
    //cl=ApiNodeGraphInfo, field.mName = category field.mType = const char *, protoType=string
    out.mCategory =  (char*)StringManager::getInstance().addString(in.category());
    //cl=ApiNodeGraphInfo, field.mName = defaultName field.mType = const char *, protoType=string
    out.mDefaultName =  (char*)StringManager::getInstance().addString(in.defaultname());
    //cl=ApiNodeGraphInfo, field.mName = isInspectable field.mType = bool, protoType=bool
    out.mIsInspectable = in.isinspectable();////simple 3////
    //cl=ApiNodeGraphInfo, field.mName = isCreatableByApi field.mType = bool, protoType=bool
    out.mIsCreatableByApi = in.iscreatablebyapi();////simple 3////
    //cl=ApiNodeGraphInfo, field.mName = isHidden field.mType = bool, protoType=bool
    out.mIsHidden = in.ishidden();////simple 3////
    //cl=ApiNodeGraphInfo, field.mName = isScripted field.mType = bool, protoType=bool
    out.mIsScripted = in.isscripted();////simple 3////
    //cl=ApiNodeGraphInfo, field.mName = isModule field.mType = bool, protoType=bool
    out.mIsModule = in.ismodule();////simple 3////
    //cl=ApiNodeGraphInfo, field.mName = isPopulatedAtConstruction field.mType = bool, protoType=bool
    out.mIsPopulatedAtConstruction = in.ispopulatedatconstruction();////simple 3////
    //cl=ApiNodeGraphInfo, field.mName = attributeInfoCount field.mType = uint32_t, protoType=uint32
    out.mAttributeInfoCount = in.attributeinfocount();////simple 3////
    // all fields resolved OK;
}


void ApiNodeGraphInfoConverter::convert(
    const Octane::ApiNodeGraphInfo & in,
    octaneapi::ApiNodeGraphInfo & out)
{

    // Found structure 1 ApiNodeGraphInfo
    // from octane type = const Octane::ApiNodeGraphInfo &,
        //to proto type = octaneapi::ApiNodeGraphInfo &
    // list out parameters
    out.set_type( static_cast<octaneapi::NodeGraphType>(in.mType)); // enum 2

    std::string * descriptionStr = new std::string();////approved//// 
    *descriptionStr = StringManager::checkString(in.mDescription);
    out.set_allocated_description(descriptionStr);
    out.set_outtype( static_cast<octaneapi::NodePinType>(in.mOutType)); // enum 2

    std::string * categoryStr = new std::string();////approved//// 
    *categoryStr = StringManager::checkString(in.mCategory);
    out.set_allocated_category(categoryStr);

    std::string * defaultNameStr = new std::string();////approved//// 
    *defaultNameStr = StringManager::checkString(in.mDefaultName);
    out.set_allocated_defaultname(defaultNameStr);
    out.set_isinspectable(in.mIsInspectable);////simple 4b////
    out.set_iscreatablebyapi(in.mIsCreatableByApi);////simple 4b////
    out.set_ishidden(in.mIsHidden);////simple 4b////
    out.set_isscripted(in.mIsScripted);////simple 4b////
    out.set_ismodule(in.mIsModule);////simple 4b////
    out.set_ispopulatedatconstruction(in.mIsPopulatedAtConstruction);////simple 4b////
    out.set_attributeinfocount(in.mAttributeInfoCount);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
