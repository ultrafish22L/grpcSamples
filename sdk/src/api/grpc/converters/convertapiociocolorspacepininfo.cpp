// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapiociocolorspacepininfo.h"
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

void ApiOcioColorSpacePinInfoConverter::convert(
    const octaneapi::ApiOcioColorSpacePinInfo & in,
    Octane::ApiOcioColorSpacePinInfo & out)
{

    // Found structure 1 ApiOcioColorSpacePinInfo
    // from proto type = const octaneapi::ApiOcioColorSpacePinInfo &,
        //to octane type = Octane::ApiOcioColorSpacePinInfo &
    // list out parameters
    //cl=ApiOcioColorSpacePinInfo, field.mName = isValid field.mType = bool, protoType=bool
    //cl=ApiOcioColorSpacePinInfo, field.mName = defaultColorSpace field.mType = Octane::NamedColorSpace, protoType=NamedColorSpace
    out.mDefaultColorSpace = static_cast<Octane::NamedColorSpace>(in.defaultcolorspace());// enum 1 
    //cl=ApiOcioColorSpacePinInfo, field.mName = otherText field.mType = const char *, protoType=string
    out.mOtherText =  (char*)StringManager::getInstance().addString(in.othertext());
    //cl=ApiOcioColorSpacePinInfo, field.mName = showFileTypeHints field.mType = bool, protoType=bool
    out.mShowFileTypeHints = in.showfiletypehints();////simple 3////
    //cl=ApiOcioColorSpacePinInfo, field.mName = linearSrgbUsesLegacyGamma field.mType = bool, protoType=bool
    out.mLinearSrgbUsesLegacyGamma = in.linearsrgbuseslegacygamma();////simple 3////
    // all fields resolved OK;
}


void ApiOcioColorSpacePinInfoConverter::convert(
    const Octane::ApiOcioColorSpacePinInfo & in,
    octaneapi::ApiOcioColorSpacePinInfo & out)
{

    // Found structure 1 ApiOcioColorSpacePinInfo
    // from octane type = const Octane::ApiOcioColorSpacePinInfo &,
        //to proto type = octaneapi::ApiOcioColorSpacePinInfo &
    // list out parameters
    out.set_isvalid(true);////mDummy 4////
    out.set_defaultcolorspace( static_cast<octaneapi::NamedColorSpace>(in.mDefaultColorSpace)); // enum 2

    std::string * otherTextStr = new std::string();////approved//// 
    *otherTextStr = StringManager::checkString(in.mOtherText);
    out.set_allocated_othertext(otherTextStr);
    out.set_showfiletypehints(in.mShowFileTypeHints);////simple 4b////
    out.set_linearsrgbuseslegacygamma(in.mLinearSrgbUsesLegacyGamma);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
