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

/// Proxy class for ApiMouseWheelDetails
class ApiMouseWheelDetailsProxy : public GRPCBase
{
public:
    static Octane::ApiMouseWheelDetails make();

private:
    static GRPCSettings & getGRPCSettings();
};
