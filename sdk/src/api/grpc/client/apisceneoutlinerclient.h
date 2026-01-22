// Copyright (C) 2026 OTOY NZ Ltd.

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
#include "apiguicomponentclient.h"


#include "apisceneoutliner.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiSceneOutliner
class ApiSceneOutlinerProxy : public ApiGuiComponentProxy
{
public:
    static ApiSceneOutlinerProxy create();

    void destroy();

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
