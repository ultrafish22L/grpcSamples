// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapinodepininfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "octaneinfos.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneinfos.h"

#include "convertapitransformpininfo.h"
#include "convertapitexturepininfo.h"
#include "convertapitexturenodetypeinfo.h"
#include "convertapitexturepintypeinfo.h"
#include "convertapistringpininfo.h"
#include "convertapiprojectionpininfo.h"
#include "convertapiocioviewpininfo.h"
#include "convertapiociolookpininfo.h"
#include "convertapiociocolorspacepininfo.h"
#include "convertapiboolpininfo.h"
#include "convertapifloatpininfo.h"
#include "convertapiintpininfo.h"
#include "convertapienumpininfo.h"
#include "convertapitransformpininfo.h"
#include "convertapibitmaskpininfo.h"
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

void ApiNodePinInfoConverter::convert(
    const octaneapi::ApiNodePinInfo & in,
    Octane::ApiNodePinInfo & out)
{

    // Found structure 1 ApiNodePinInfo
    // from proto type = const octaneapi::ApiNodePinInfo &,
        //to octane type = Octane::ApiNodePinInfo &
    // list out parameters
    //cl=ApiNodePinInfo, field.mName = id field.mType = Octane::PinId, protoType=PinId
    out.mId = static_cast<Octane::PinId>(in.id());// enum 1 
    //cl=ApiNodePinInfo, field.mName = type field.mType = Octane::NodePinType, protoType=NodePinType
    out.mType = static_cast<Octane::NodePinType>(in.type());// enum 1 
    //cl=ApiNodePinInfo, field.mName = isTypedTexturePin field.mType = bool, protoType=bool
    out.mIsTypedTexturePin = in.istypedtexturepin();////simple 3////
    //cl=ApiNodePinInfo, field.mName = staticName field.mType = const char *, protoType=string
    out.mStaticName =  (char*)StringManager::getInstance().addString(in.staticname());
    //cl=ApiNodePinInfo, field.mName = staticLabel field.mType = const char *, protoType=string
    out.mStaticLabel =  (char*)StringManager::getInstance().addString(in.staticlabel());
    //cl=ApiNodePinInfo, field.mName = description field.mType = const char *, protoType=string
    out.mDescription =  (char*)StringManager::getInstance().addString(in.description());
    //cl=ApiNodePinInfo, field.mName = groupName field.mType = const char *, protoType=string
    out.mGroupName =  (char*)StringManager::getInstance().addString(in.groupname());
    //cl=ApiNodePinInfo, field.mName = pinColor field.mType = uint32_t, protoType=uint32
    out.mPinColor = in.pincolor();////simple 3////
    //cl=ApiNodePinInfo, field.mName = defaultNodeType field.mType = Octane::NodeType, protoType=NodeType
    out.mDefaultNodeType = static_cast<Octane::NodeType>(in.defaultnodetype());// enum 1 
    //cl=ApiNodePinInfo, field.mName = minVersion field.mType = Octane::VersionT, protoType=uint32
    out.mMinVersion = in.minversion();////VersionT////
    //cl=ApiNodePinInfo, field.mName = endVersion field.mType = Octane::VersionT, protoType=uint32
    out.mEndVersion = in.endversion();////VersionT////
    //cl=ApiNodePinInfo, field.mName = boolInfo field.mType = const Octane::ApiBoolPinInfo *, protoType=ApiBoolPinInfo

    if(in.boolinfo().isvalid())//33335//
    {
        Octane::ApiBoolPinInfo * boolinfo = new Octane::ApiBoolPinInfo();
        ApiBoolPinInfoConverter::convert(in.boolinfo(), *boolinfo);//33335//
        out.mBoolInfo = boolinfo;
    }
    else 
    {
        out.mBoolInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = floatInfo field.mType = const Octane::ApiFloatPinInfo *, protoType=ApiFloatPinInfo

    if(in.floatinfo().isvalid())//33335//
    {
        Octane::ApiFloatPinInfo * floatinfo = new Octane::ApiFloatPinInfo();
        ApiFloatPinInfoConverter::convert(in.floatinfo(), *floatinfo);//33335//
        out.mFloatInfo = floatinfo;
    }
    else 
    {
        out.mFloatInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = intInfo field.mType = const Octane::ApiIntPinInfo *, protoType=ApiIntPinInfo

    if(in.intinfo().isvalid())//33335//
    {
        Octane::ApiIntPinInfo * intinfo = new Octane::ApiIntPinInfo();
        ApiIntPinInfoConverter::convert(in.intinfo(), *intinfo);//33335//
        out.mIntInfo = intinfo;
    }
    else 
    {
        out.mIntInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = enumInfo field.mType = const Octane::ApiEnumPinInfo *, protoType=ApiEnumPinInfo

    if(in.enuminfo().isvalid())//33335//
    {
        Octane::ApiEnumPinInfo * enuminfo = new Octane::ApiEnumPinInfo();
        ApiEnumPinInfoConverter::convert(in.enuminfo(), *enuminfo);//33335//
        out.mEnumInfo = enuminfo;
    }
    else 
    {
        out.mEnumInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = ocioColorSpaceInfo field.mType = const Octane::ApiOcioColorSpacePinInfo *, protoType=ApiOcioColorSpacePinInfo

    if(in.ociocolorspaceinfo().isvalid())//33335//
    {
        Octane::ApiOcioColorSpacePinInfo * ociocolorspaceinfo = new Octane::ApiOcioColorSpacePinInfo();
        ApiOcioColorSpacePinInfoConverter::convert(in.ociocolorspaceinfo(), *ociocolorspaceinfo);//33335//
        out.mOcioColorSpaceInfo = ociocolorspaceinfo;
    }
    else 
    {
        out.mOcioColorSpaceInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = ocioLookInfo field.mType = const Octane::ApiOcioLookPinInfo *, protoType=ApiOcioLookPinInfo

    if(in.ociolookinfo().isvalid())//33335//
    {
        Octane::ApiOcioLookPinInfo * ociolookinfo = new Octane::ApiOcioLookPinInfo();
        ApiOcioLookPinInfoConverter::convert(in.ociolookinfo(), *ociolookinfo);//33335//
        out.mOcioLookInfo = ociolookinfo;
    }
    else 
    {
        out.mOcioLookInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = ocioViewInfo field.mType = const Octane::ApiOcioViewPinInfo *, protoType=ApiOcioViewPinInfo

    if(in.ocioviewinfo().isvalid())//33335//
    {
        Octane::ApiOcioViewPinInfo * ocioviewinfo = new Octane::ApiOcioViewPinInfo();
        ApiOcioViewPinInfoConverter::convert(in.ocioviewinfo(), *ocioviewinfo);//33335//
        out.mOcioViewInfo = ocioviewinfo;
    }
    else 
    {
        out.mOcioViewInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = projectionInfo field.mType = const Octane::ApiProjectionPinInfo *, protoType=ApiProjectionPinInfo

    if(in.projectioninfo().isvalid())//33335//
    {
        Octane::ApiProjectionPinInfo * projectioninfo = new Octane::ApiProjectionPinInfo();
        ApiProjectionPinInfoConverter::convert(in.projectioninfo(), *projectioninfo);//33335//
        out.mProjectionInfo = projectioninfo;
    }
    else 
    {
        out.mProjectionInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = texInfo field.mType = const Octane::ApiTexturePinInfo *, protoType=ApiTexturePinInfo

    if(in.texinfo().isvalid())//33335//
    {
        Octane::ApiTexturePinInfo * texinfo = new Octane::ApiTexturePinInfo();
        ApiTexturePinInfoConverter::convert(in.texinfo(), *texinfo);//33335//
        out.mTexInfo = texinfo;
    }
    else 
    {
        out.mTexInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = texTypeInfo field.mType = const Octane::ApiTexturePinTypeInfo *, protoType=ApiTexturePinTypeInfo

    if(in.textypeinfo().isvalid())//33335//
    {
        Octane::ApiTexturePinTypeInfo * textypeinfo = new Octane::ApiTexturePinTypeInfo();
        ApiTexturePinTypeInfoConverter::convert(in.textypeinfo(), *textypeinfo);//33335//
        out.mTexTypeInfo = textypeinfo;
    }
    else 
    {
        out.mTexTypeInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = transformInfo field.mType = const Octane::ApiTransformPinInfo *, protoType=ApiTransformPinInfo

    if(in.transforminfo().isvalid())//33335//
    {
        Octane::ApiTransformPinInfo * transforminfo = new Octane::ApiTransformPinInfo();
        ApiTransformPinInfoConverter::convert(in.transforminfo(), *transforminfo);//33335//
        out.mTransformInfo = transforminfo;
    }
    else 
    {
        out.mTransformInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = stringInfo field.mType = const Octane::ApiStringPinInfo *, protoType=ApiStringPinInfo

    if(in.stringinfo().isvalid())//33335//
    {
        Octane::ApiStringPinInfo * stringinfo = new Octane::ApiStringPinInfo();
        ApiStringPinInfoConverter::convert(in.stringinfo(), *stringinfo);//33335//
        out.mStringInfo = stringinfo;
    }
    else 
    {
        out.mStringInfo = nullptr;
    }
    //cl=ApiNodePinInfo, field.mName = bitMaskInfo field.mType = const Octane::ApiBitMaskPinInfo *, protoType=ApiBitMaskPinInfo

    if(in.bitmaskinfo().isvalid())//33335//
    {
        Octane::ApiBitMaskPinInfo * bitmaskinfo = new Octane::ApiBitMaskPinInfo();
        ApiBitMaskPinInfoConverter::convert(in.bitmaskinfo(), *bitmaskinfo);//33335//
        out.mBitMaskInfo = bitmaskinfo;
    }
    else 
    {
        out.mBitMaskInfo = nullptr;
    }
    // all fields resolved OK;
}


void ApiNodePinInfoConverter::convert(
    const Octane::ApiNodePinInfo & in,
    octaneapi::ApiNodePinInfo & out)
{

    // Found structure 1 ApiNodePinInfo
    // from octane type = const Octane::ApiNodePinInfo &,
        //to proto type = octaneapi::ApiNodePinInfo &
    // list out parameters
    out.set_id( static_cast<octaneapi::PinId>(in.mId)); // enum 2
    out.set_type( static_cast<octaneapi::NodePinType>(in.mType)); // enum 2
    out.set_istypedtexturepin(in.mIsTypedTexturePin);////simple 4b////

    std::string * staticNameStr = new std::string();////approved//// 
    *staticNameStr = StringManager::checkString(in.mStaticName);
    out.set_allocated_staticname(staticNameStr);

    std::string * staticLabelStr = new std::string();////approved//// 
    *staticLabelStr = StringManager::checkString(in.mStaticLabel);
    out.set_allocated_staticlabel(staticLabelStr);

    std::string * descriptionStr = new std::string();////approved//// 
    *descriptionStr = StringManager::checkString(in.mDescription);
    out.set_allocated_description(descriptionStr);

    std::string * groupNameStr = new std::string();////approved//// 
    *groupNameStr = StringManager::checkString(in.mGroupName);
    out.set_allocated_groupname(groupNameStr);
    out.set_pincolor(in.mPinColor);////simple 4b////
    out.set_defaultnodetype( static_cast<octaneapi::NodeType>(in.mDefaultNodeType)); // enum 2
    out.set_minversion(in.mMinVersion);////VersionT//
    out.set_endversion(in.mEndVersion);////VersionT//
    if(in.mBoolInfo)
    {
        // convert test{
        ApiBoolPinInfoConverter::convert(*(in.mBoolInfo), *(out.mutable_boolinfo())); //756475//
        out.mutable_boolinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_boolinfo()->set_isvalid(false);
    }
    if(in.mFloatInfo)
    {
        // convert test{
        ApiFloatPinInfoConverter::convert(*(in.mFloatInfo), *(out.mutable_floatinfo())); //756475//
        out.mutable_floatinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_floatinfo()->set_isvalid(false);
    }
    if(in.mIntInfo)
    {
        // convert test{
        ApiIntPinInfoConverter::convert(*(in.mIntInfo), *(out.mutable_intinfo())); //756475//
        out.mutable_intinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_intinfo()->set_isvalid(false);
    }
    if(in.mEnumInfo)
    {
        // convert test{
        ApiEnumPinInfoConverter::convert(*(in.mEnumInfo), *(out.mutable_enuminfo())); //756475//
        out.mutable_enuminfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_enuminfo()->set_isvalid(false);
    }
    if(in.mOcioColorSpaceInfo)
    {
        // convert test{
        ApiOcioColorSpacePinInfoConverter::convert(*(in.mOcioColorSpaceInfo), *(out.mutable_ociocolorspaceinfo())); //756475//
        out.mutable_ociocolorspaceinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_ociocolorspaceinfo()->set_isvalid(false);
    }
    if(in.mOcioLookInfo)
    {
        // convert test{
        ApiOcioLookPinInfoConverter::convert(*(in.mOcioLookInfo), *(out.mutable_ociolookinfo())); //756475//
        out.mutable_ociolookinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_ociolookinfo()->set_isvalid(false);
    }
    if(in.mOcioViewInfo)
    {
        // convert test{
        ApiOcioViewPinInfoConverter::convert(*(in.mOcioViewInfo), *(out.mutable_ocioviewinfo())); //756475//
        out.mutable_ocioviewinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_ocioviewinfo()->set_isvalid(false);
    }
    if(in.mProjectionInfo)
    {
        // convert test{
        ApiProjectionPinInfoConverter::convert(*(in.mProjectionInfo), *(out.mutable_projectioninfo())); //756475//
        out.mutable_projectioninfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_projectioninfo()->set_isvalid(false);
    }
    if(in.mTexInfo)
    {
        // convert test{
        ApiTexturePinInfoConverter::convert(*(in.mTexInfo), *(out.mutable_texinfo())); //756475//
        out.mutable_texinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_texinfo()->set_isvalid(false);
    }
    if(in.mTexTypeInfo)
    {
        // convert test{
        ApiTexturePinTypeInfoConverter::convert(*(in.mTexTypeInfo), *(out.mutable_textypeinfo())); //756475//
        out.mutable_textypeinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_textypeinfo()->set_isvalid(false);
    }
    if(in.mTransformInfo)
    {
        // convert test{
        ApiTransformPinInfoConverter::convert(*(in.mTransformInfo), *(out.mutable_transforminfo())); //756475//
        out.mutable_transforminfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_transforminfo()->set_isvalid(false);
    }
    if(in.mStringInfo)
    {
        // convert test{
        ApiStringPinInfoConverter::convert(*(in.mStringInfo), *(out.mutable_stringinfo())); //756475//
        out.mutable_stringinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_stringinfo()->set_isvalid(false);
    }
    if(in.mBitMaskInfo)
    {
        // convert test{
        ApiBitMaskPinInfoConverter::convert(*(in.mBitMaskInfo), *(out.mutable_bitmaskinfo())); //756475//
        out.mutable_bitmaskinfo()->set_isvalid(true);
    }
    else
    {
        out.mutable_bitmaskinfo()->set_isvalid(false);
    }
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
