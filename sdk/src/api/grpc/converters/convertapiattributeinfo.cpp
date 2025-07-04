// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapiattributeinfo.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apiinfo.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apiinfo.h"
#ifdef NO_PCH
#include "apinodesystem_1.grpc.pb.h"
#include "apinodesystem_2.grpc.pb.h"
#include "apinodesystem_3.grpc.pb.h"
#include "apinodesystem_4.grpc.pb.h"
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

void ApiAttributeInfoConverter::convert(
    const octaneapi::ApiAttributeInfo & in,
    Octane::ApiAttributeInfo & out)
{

    // Found structure 1 ApiAttributeInfo
    // from proto type = const octaneapi::ApiAttributeInfo &,
        //to octane type = Octane::ApiAttributeInfo &
    // list out parameters
    //cl=ApiAttributeInfo, field.mName = id field.mType = Octane::AttributeId, protoType=AttributeId
    out.mId = static_cast<Octane::AttributeId>(in.id());// enum 1 
    //cl=ApiAttributeInfo, field.mName = type field.mType = Octane::AttributeType, protoType=AttributeType
    out.mType = static_cast<Octane::AttributeType>(in.type());// enum 1 
    //cl=ApiAttributeInfo, field.mName = isArray field.mType = bool, protoType=bool
    out.mIsArray = in.isarray();////simple 3////
    //cl=ApiAttributeInfo, field.mName = fileNameAttribute field.mType = Octane::AttributeId, protoType=AttributeId
    out.mFileNameAttribute = static_cast<Octane::AttributeId>(in.filenameattribute());// enum 1 
    //cl=ApiAttributeInfo, field.mName = packageAttribute field.mType = Octane::AttributeId, protoType=AttributeId
    out.mPackageAttribute = static_cast<Octane::AttributeId>(in.packageattribute());// enum 1 
    //cl=ApiAttributeInfo, field.mName = description field.mType = const char *, protoType=string
    out.mDescription =  (char*)StringManager::getInstance().addString(in.description());
    //cl=ApiAttributeInfo, field.mName = defaultInts field.mType = OctaneVec::int32_4, protoType=int32_4
    out.mDefaultInts = {
       in.defaultints().x(),
       in.defaultints().y(),
       in.defaultints().z(),
       in.defaultints().w() };
    //cl=ApiAttributeInfo, field.mName = defaultLongs field.mType = OctaneVec::int64_2, protoType=int64_2
    out.mDefaultLongs = {
       in.defaultlongs().x(),
       in.defaultlongs().y() };
    //cl=ApiAttributeInfo, field.mName = defaultFloats field.mType = OctaneVec::float_4, protoType=float_4
    out.mDefaultFloats = {
       in.defaultfloats().x(),
       in.defaultfloats().y(),
       in.defaultfloats().z(),
       in.defaultfloats().w() };
    //cl=ApiAttributeInfo, field.mName = defaultString field.mType = const char *, protoType=string
    out.mDefaultString =  (char*)StringManager::getInstance().addString(in.defaultstring());
    //cl=ApiAttributeInfo, field.mName = minVersion field.mType = Octane::VersionT, protoType=uint32
    out.mMinVersion = in.minversion();////VersionT////
    //cl=ApiAttributeInfo, field.mName = endVersion field.mType = Octane::VersionT, protoType=uint32
    out.mEndVersion = in.endversion();////VersionT////
    // all fields resolved OK;
}


void ApiAttributeInfoConverter::convert(
    const Octane::ApiAttributeInfo & in,
    octaneapi::ApiAttributeInfo & out)
{

    // Found structure 1 ApiAttributeInfo
    // from octane type = const Octane::ApiAttributeInfo &,
        //to proto type = octaneapi::ApiAttributeInfo &
    // list out parameters
    out.set_id( static_cast<octaneapi::AttributeId>(in.mId)); // enum 2
    out.set_type( static_cast<octaneapi::AttributeType>(in.mType)); // enum 2
    out.set_isarray(in.mIsArray);////simple 4b////
    out.set_filenameattribute( static_cast<octaneapi::AttributeId>(in.mFileNameAttribute)); // enum 2
    out.set_packageattribute( static_cast<octaneapi::AttributeId>(in.mPackageAttribute)); // enum 2

    std::string * descriptionStr = new std::string();////approved//// 
    *descriptionStr = StringManager::checkString(in.mDescription);
    out.set_allocated_description(descriptionStr);

    octaneapi::int32_4 * defaultIntsOut = new octaneapi::int32_4;////approved////
    defaultIntsOut->set_x(in.mDefaultInts.x);
    defaultIntsOut->set_y(in.mDefaultInts.y);
    defaultIntsOut->set_z(in.mDefaultInts.z);
    defaultIntsOut->set_w(in.mDefaultInts.w);
    out.set_allocated_defaultints(defaultIntsOut);

    octaneapi::int64_2 * defaultLongsOut = new octaneapi::int64_2;////approved////
    defaultLongsOut->set_x(in.mDefaultLongs.x);
    defaultLongsOut->set_y(in.mDefaultLongs.y);
    out.set_allocated_defaultlongs(defaultLongsOut);

    octaneapi::float_4 * defaultFloatsOut = new octaneapi::float_4;////approved////
    defaultFloatsOut->set_x(in.mDefaultFloats.x);
    defaultFloatsOut->set_y(in.mDefaultFloats.y);
    defaultFloatsOut->set_z(in.mDefaultFloats.z);
    defaultFloatsOut->set_w(in.mDefaultFloats.w);
    out.set_allocated_defaultfloats(defaultFloatsOut);

    std::string * defaultStringStr = new std::string();////approved//// 
    *defaultStringStr = StringManager::checkString(in.mDefaultString);
    out.set_allocated_defaultstring(defaultStringStr);
    out.set_minversion(in.mMinVersion);////VersionT//
    out.set_endversion(in.mEndVersion);////VersionT//
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
