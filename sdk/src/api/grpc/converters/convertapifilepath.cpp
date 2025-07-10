// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapifilepath.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
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
#ifdef NO_PCH
#include "apimodulenodegraph.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apimodulenodegraph.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
class ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiFilePathConverter::convert(
    const octaneapi::ApiFilePath & in,
    Octane::ApiFilePath & out)
{

    // Found structure 1 ApiFilePath
    // from proto type = const octaneapi::ApiFilePath &,
        //to octane type = Octane::ApiFilePath &
    // list out parameters
    //cl=ApiFilePath, field.mName = package field.mType = const char *, protoType=string
    out.mPackage =  (char*)StringManager::getInstance().addString(in.package());
    //cl=ApiFilePath, field.mName = fileName field.mType = const char *, protoType=string
    out.mFileName =  (char*)StringManager::getInstance().addString(in.filename());
    // all fields resolved OK;
}


void ApiFilePathConverter::convert(
    const Octane::ApiFilePath & in,
    octaneapi::ApiFilePath & out)
{

    // Found structure 1 ApiFilePath
    // from octane type = const Octane::ApiFilePath &,
        //to proto type = octaneapi::ApiFilePath &
    // list out parameters

    std::string * packageStr = new std::string();////approved//// 
    *packageStr = StringManager::checkString(in.mPackage);
    out.set_allocated_package(packageStr);

    std::string * fileNameStr = new std::string();////approved//// 
    *fileNameStr = StringManager::checkString(in.mFileName);
    out.set_allocated_filename(fileNameStr);
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
