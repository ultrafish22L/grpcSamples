// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapinodeinfo.h"
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
#ifdef NO_PCH
#include "octaneinfos.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneinfos.h"

#include "convertapitexturenodetypeinfo.h"
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

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
void ApiNodeInfoConverter::convert(
    const octaneapi::ApiNodeInfo & in,
    ApiNodeInfoProxy & out)
{

    // Found structure 1 ApiNodeInfo
    // from proto type = const octaneapi::ApiNodeInfo &,
        //to octane type = ApiNodeInfoProxy &
    // list out parameters
    //cl=ApiNodeInfo, field.mName = type field.mType = Octane::NodeType, protoType=NodeType
    out.mType = static_cast<Octane::NodeType>(in.type());// enum 1 
    //cl=ApiNodeInfo, field.mName = description field.mType = const char *, protoType=string
    out.mDescription =  (char*)StringManager::getInstance().addString(in.description());
    //cl=ApiNodeInfo, field.mName = outType field.mType = Octane::NodePinType, protoType=NodePinType
    out.mOutType = static_cast<Octane::NodePinType>(in.outtype());// enum 1 
    //cl=ApiNodeInfo, field.mName = nodeColor field.mType = uint32_t, protoType=uint32
    out.mNodeColor = in.nodecolor();////simple 3////
    //cl=ApiNodeInfo, field.mName = isLinker field.mType = bool, protoType=bool
    out.mIsLinker = in.islinker();////simple 3////
    //cl=ApiNodeInfo, field.mName = isOutputLinker field.mType = bool, protoType=bool
    out.mIsOutputLinker = in.isoutputlinker();////simple 3////
    //cl=ApiNodeInfo, field.mName = takesPinDefaultValue field.mType = bool, protoType=bool
    out.mTakesPinDefaultValue = in.takespindefaultvalue();////simple 3////
    //cl=ApiNodeInfo, field.mName = isHidden field.mType = bool, protoType=bool
    out.mIsHidden = in.ishidden();////simple 3////
    //cl=ApiNodeInfo, field.mName = isCreatableByApi field.mType = bool, protoType=bool
    out.mIsCreatableByApi = in.iscreatablebyapi();////simple 3////
    //cl=ApiNodeInfo, field.mName = isScriptGraphWrapper field.mType = bool, protoType=bool
    out.mIsScriptGraphWrapper = in.isscriptgraphwrapper();////simple 3////
    //cl=ApiNodeInfo, field.mName = isTypedTextureNode field.mType = bool, protoType=bool
    out.mIsTypedTextureNode = in.istypedtexturenode();////simple 3////
    //cl=ApiNodeInfo, field.mName = category field.mType = const char *, protoType=string
    out.mCategory =  (char*)StringManager::getInstance().addString(in.category());
    //cl=ApiNodeInfo, field.mName = defaultName field.mType = const char *, protoType=string
    out.mDefaultName =  (char*)StringManager::getInstance().addString(in.defaultname());
    //cl=ApiNodeInfo, field.mName = attributeInfoCount field.mType = uint32_t, protoType=uint32
    out.mAttributeInfoCount = in.attributeinfocount();////simple 3////
    //cl=ApiNodeInfo, field.mName = pinInfoCount field.mType = uint32_t, protoType=uint32
    out.mPinInfoCount = in.pininfocount();////simple 3////
    //cl=ApiNodeInfo, field.mName = movableInputCountAttribute field.mType = Octane::AttributeId, protoType=AttributeId
    out.mMovableInputCountAttribute = static_cast<Octane::AttributeId>(in.movableinputcountattribute());// enum 1 
    //cl=ApiNodeInfo, field.mName = movableInputPinCount field.mType = uint32_t, protoType=uint32
    out.mMovableInputPinCount = in.movableinputpincount();////simple 3////
    //cl=ApiNodeInfo, field.mName = movableInputFormat field.mType = Octane::MovableInputFormat, protoType=MovableInputFormat
    out.mMovableInputFormat = static_cast<Octane::MovableInputFormat>(in.movableinputformat());// enum 1 
    //cl=ApiNodeInfo, field.mName = movableInputName field.mType = const char *, protoType=string
    out.mMovableInputName =  (char*)StringManager::getInstance().addString(in.movableinputname());
    //cl=ApiNodeInfo, field.mName = texNodeTypeInfo field.mType = const Octane::ApiTextureNodeTypeInfo *, protoType=ApiTextureNodeTypeInfo

    if(in.texnodetypeinfo().isvalid())//33335//
    {
        Octane::ApiTextureNodeTypeInfo * texnodetypeinfo = new Octane::ApiTextureNodeTypeInfo();
        ApiTextureNodeTypeInfoConverter::convert(in.texnodetypeinfo(), *texnodetypeinfo);//33335//
        out.mTexNodeTypeInfo = texnodetypeinfo;
    }
    else 
    {
        out.mTexNodeTypeInfo = nullptr;
    }
    //cl=ApiNodeInfo, field.mName = compatibilityModeInfos field.mType = Octane::ApiCompatibilityModeInfoSet, protoType=ApiCompatibilityModeInfoSetArrayT
    //TEST 11 

  //  const octaneapi::ApiCompatibilityModeInfoSetArrayT & compatibilityModeInfosRef = in.compatibilitymodeinfos();
   // out.mCompatibilityModeInfos = compatibilityModeInfosRef.id();
    //cl=ApiNodeInfo, field.mName = minVersion field.mType = Octane::VersionT, protoType=uint32
    out.mMinVersion = in.minversion();////VersionT////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#if defined(OCTANE_STANDALONE) || defined(OCTANE_DLLEXPORT) 
void ApiNodeInfoConverter::convert(
    const Octane::ApiNodeInfo & in,
    octaneapi::ApiNodeInfo & out)
{

    // Found structure 1 ApiNodeInfo
    // from octane type = const Octane::ApiNodeInfo &,
        //to proto type = octaneapi::ApiNodeInfo &
    // list out parameters
    out.set_type( static_cast<octaneapi::NodeType>(in.mType)); // enum 2

    std::string * descriptionStr = new std::string();////approved//// 
    *descriptionStr = StringManager::checkString(in.mDescription);
    out.set_allocated_description(descriptionStr);
    out.set_outtype( static_cast<octaneapi::NodePinType>(in.mOutType)); // enum 2
    out.set_nodecolor(in.mNodeColor);////simple 4b////
    out.set_islinker(in.mIsLinker);////simple 4b////
    out.set_isoutputlinker(in.mIsOutputLinker);////simple 4b////
    out.set_takespindefaultvalue(in.mTakesPinDefaultValue);////simple 4b////
    out.set_ishidden(in.mIsHidden);////simple 4b////
    out.set_iscreatablebyapi(in.mIsCreatableByApi);////simple 4b////
    out.set_isscriptgraphwrapper(in.mIsScriptGraphWrapper);////simple 4b////
    out.set_istypedtexturenode(in.mIsTypedTextureNode);////simple 4b////

    std::string * categoryStr = new std::string();////approved//// 
    *categoryStr = StringManager::checkString(in.mCategory);
    out.set_allocated_category(categoryStr);

    std::string * defaultNameStr = new std::string();////approved//// 
    *defaultNameStr = StringManager::checkString(in.mDefaultName);
    out.set_allocated_defaultname(defaultNameStr);
    out.set_attributeinfocount(in.mAttributeInfoCount);////simple 4b////
    out.set_pininfocount(in.mPinInfoCount);////simple 4b////
    out.set_movableinputcountattribute( static_cast<octaneapi::AttributeId>(in.mMovableInputCountAttribute)); // enum 2
    out.set_movableinputpincount(in.mMovableInputPinCount);////simple 4b////
    out.set_movableinputformat( static_cast<octaneapi::MovableInputFormat>(in.mMovableInputFormat)); // enum 2

    std::string * movableInputNameStr = new std::string();////approved//// 
    *movableInputNameStr = StringManager::checkString(in.mMovableInputName);
    out.set_allocated_movableinputname(movableInputNameStr);
    if(in.mTexNodeTypeInfo)
    {
        // convert test{
        ApiTextureNodeTypeInfoConverter::convert(*(in.mTexNodeTypeInfo), *(out.mutable_texnodetypeinfo())); //756475//
        out.mutable_texnodetypeinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_texnodetypeinfo()->set_isvalid(false);
    }
    ////TEST 22 ///
    octaneapi::ApiCompatibilityModeInfoSetArrayT * compatibilityModeInfosOut = new octaneapi::ApiCompatibilityModeInfoSetArrayT;////134//approved////
    // out.compatibilityModeInfos = compatibilityModeInfosRef.id();
    for (uint32_t h = 0; h < in.mCompatibilityModeInfos.size(); h++)
    {
        auto mode = compatibilityModeInfosOut->add_infos();
        auto itemSrc = in.mCompatibilityModeInfos.info(h);
        std::string * description = new std::string();
        *description = StringManager::checkString(itemSrc.description());
        mode->set_allocated_description(description);
        std::string * name = new std::string();
        *name = StringManager::checkString(itemSrc.name());
        mode->set_allocated_name(name);
        mode->set_startversion(itemSrc.startVersion());
    }
    out.set_minversion(in.mMinVersion);////VersionT//
    // all fields resolved OK;
}


#endif // #if defined(OCTANE_STANDALONE) || defined(OCTANE_DLLEXPORT) 
} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
