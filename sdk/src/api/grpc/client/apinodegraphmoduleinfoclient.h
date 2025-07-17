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


#include "apimodule.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiNodeGraphModuleInfo
class ApiNodeGraphModuleInfoProxy : public GRPCBase
{
public:
    /// Creates info for Api node graph module
    /// @param[in]  moduleId
    ///     Unique ID for this module. should start from 1000100
    /// @param[in]  fullName
    ///     Name with categories that will appear in the user interface.
    ///     Must have at least one category to display it in the Windows menu
    ///     eg: "|Octane examples|Hello world" or |Hello world.
    ///     and "Hello world" this will not be shown in the menu, can be used for internal commands
    /// @param[in]  description
    ///     Describes what the module node graph does.
    /// @param[in]  author
    ///     Name of the author for this module.
    /// @param[in]  versionNumber
    ///     Version number of the module.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiNodeGraphModuleInfoProxy create(
            const Octane::ModuleIdT                   moduleId,
            const char *const                         fullName,
            const char *const                         description,
            const char *const                         author,
            const Octane::VersionT                    versionNumber
            );

    /// Destroys a ApiNodeGraphModuleInfo object created by create().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Function to set the create function callback for a node graph module. (mandatory)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setCreateFunction(
            GRPCCreateFuncT   func
            );

    /// Function to set the destroy function callback for a node graph module. (mandatory)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setDestroyFunction(
            const Octane::ApiNodeGraphModuleInfo::DestroyFuncT   func
            );

    /// Function to set the evaluate function callback for a node graph module. (mandatory)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setOnEvaluateFunction(
            const Octane::ApiNodeGraphModuleInfo::OnEvaluateFuncT   func
            );

    /// Sets the function to call when the user clicks the trigger button in the node inspector.
    /// (optional) The trigger button will not be displayed if this callback is not set.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setOnTriggerFunction(
            const Octane::ApiNodeGraphModuleInfo::OnTriggerFuncT   func
            );

    /// Sets the output type of the node graph.
    /// (optional) The default output type is PT_UNKNOWN.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setOutType(
            const Octane::NodePinType   outType
            );

private:
    static GRPCSettings & getGRPCSettings();
};
