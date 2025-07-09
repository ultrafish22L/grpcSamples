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
class ApiCommandModuleInfoProxy;
class ApiWorkPaneModuleInfoProxy;
class ApiNodeGraphModuleInfoProxy;


#include "apimodule.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiModuleGlobal
class ApiModuleGlobalProxy : public GRPCBase
{
public:
    static bool registerCommandModule(
            const ApiCommandModuleInfoProxy &         moduleInfo
            );

    static bool registerWorkPaneModule(
            const ApiWorkPaneModuleInfoProxy &        moduleInfo
            );

    static bool registerNodeGraphModule(
            const ApiNodeGraphModuleInfoProxy &       moduleInfo
            );

    static bool registerStaticCommandModule(
            const ApiCommandModuleInfoProxy &         moduleInfo
            );

    static bool registerStaticWorkPaneModule(
            const ApiWorkPaneModuleInfoProxy &        moduleInfo
            );

    static bool registerStaticNodeGraphModule(
            const ApiNodeGraphModuleInfoProxy &       moduleInfo
            );

private:
    static GRPCSettings & getGRPCSettings();
};
