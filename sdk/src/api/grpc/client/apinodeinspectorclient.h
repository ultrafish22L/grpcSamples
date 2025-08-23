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
#include "apiguicomponentclient.h"


#include "apinodeinspector.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiNodeInspector
class ApiNodeInspectorProxy : public ApiGuiComponentProxy
{
public:
    void destroy();

    static ApiNodeInspectorProxy create();

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
