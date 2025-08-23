// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"
/*
namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}




namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiNodeInfo
class ApiNodeInfoProxy : public GRPCBase
{
public:
    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
*/