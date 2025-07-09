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


#include "apimouselistener.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiMouseEvent
class ApiMouseEventProxy : public GRPCBase
{
public:
    static ApiMouseEventProxy make(            );

private:
    static GRPCSettings & getGRPCSettings();
};
