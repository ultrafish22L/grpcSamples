// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitransformpininfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "octaneinfos.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "octaneinfos.h"

#include "convertapitransformpininfo_apitransformpininfo_bounds.h"
#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
class ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiTransformPinInfoConverter::convert(
    const octaneapi::ApiTransformPinInfo & in,
    Octane::ApiTransformPinInfo & out)
{

    // Found structure 1 ApiTransformPinInfo
    // from proto type = const octaneapi::ApiTransformPinInfo &,
        //to octane type = Octane::ApiTransformPinInfo &
    // list out parameters
    //cl=ApiTransformPinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiTransformPinInfo, field.mName = defaultValue field.mType = OctaneVec::MatrixF, protoType=MatrixF
    out.mDefaultValue;// = in.defaultvalue();
    // unresolved Type = OctaneVec::MatrixF
    //cl=ApiTransformPinInfo, field.mName = dimCount field.mType = uint8_t, protoType=uint32
    out.mDimCount = in.dimcount();////simple 3////
    //cl=ApiTransformPinInfo, field.mName = scaleBounds field.mType = Octane::ApiTransformPinInfo::Bounds, protoType=Bounds
    ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter::convert(in.scalebounds(), out.mScaleBounds);
    //cl=ApiTransformPinInfo, field.mName = rotationBounds field.mType = Octane::ApiTransformPinInfo::Bounds, protoType=Bounds
    ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter::convert(in.rotationbounds(), out.mRotationBounds);
    //cl=ApiTransformPinInfo, field.mName = translationBounds field.mType = Octane::ApiTransformPinInfo::Bounds, protoType=Bounds
    ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter::convert(in.translationbounds(), out.mTranslationBounds);
    //cl=ApiTransformPinInfo, field.mName = isUvwTransform field.mType = bool, protoType=bool
    out.mIsUvwTransform = in.isuvwtransform();////simple 3////
    // unresolved fields;
    // assert(false);
}


void ApiTransformPinInfoConverter::convert(
    const Octane::ApiTransformPinInfo & in,
    octaneapi::ApiTransformPinInfo & out)
{

    // Found structure 1 ApiTransformPinInfo
    // from octane type = const Octane::ApiTransformPinInfo &,
        //to proto type = octaneapi::ApiTransformPinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
   // out.defaultvalue;//// = out.mDefaultValue();//type = OctaneVec::MatrixF////
    //unresolved Type = OctaneVec::MatrixF
    out.set_dimcount(in.mDimCount);////simple 4b////
    ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter::convert(in.mScaleBounds, *(out.mutable_scalebounds()));
    ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter::convert(in.mRotationBounds, *(out.mutable_rotationbounds()));
    ApiTransformPinInfo_ApiTransformPinInfo_BoundsConverter::convert(in.mTranslationBounds, *(out.mutable_translationbounds()));
    out.set_isuvwtransform(in.mIsUvwTransform);////simple 4b////
    // unresolved fields;
    // assert(false);
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
