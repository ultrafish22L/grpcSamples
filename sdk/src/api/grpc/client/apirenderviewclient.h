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


#include "apirenderview.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiRenderView
class ApiRenderViewProxy : public ApiGuiComponentProxy
{
public:
    void destroy();

    static ApiRenderViewProxy create(
            void *   privateData
            );

private:
    static GRPCSettings & getGRPCSettings();
};
