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

/// Proxy class for ApiWorkPaneModuleInfo
class ApiWorkPaneModuleInfoProxy : public GRPCBase
{
public:
    /// Creates info for Api work pane
    ///
    /// @param[in]  moduleId
    ///     Unique ID for this module. should start from 1000100
    /// @param[in]  fullName
    ///     Name with categories that will appear in the user interface.
    ///     Must have at least one category to display it in the Windows menu
    ///     eg: "|Octane examples|Hello world" or |Hello world.
    ///     and "Hello world" this will not be shown in the menu, can be used for internal commands
    /// @param[in]  description
    ///     Describes what the work pane module does.
    /// @param[in]  author
    ///     Name of the author for this module.
    /// @param[in]  versionNumber
    ///     Version number of the module.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiWorkPaneModuleInfoProxy create(
            const Octane::ModuleIdT                   moduleId,
            const char *                              fullName,
            const char *                              description,
            const char *                              author,
            const Octane::VersionT                    versionNumber
            );

    /// Destroys a ApiWorkPaneModuleInfo object created by create().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Function to set the workpane module create function. (mandatory)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setInitFunction(
            GRPCInitFuncT   func
            );

    /// Function to set the workpane module destroy function. (mandatory)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setCleanupFunction(
            const Octane::ApiWorkPaneModuleInfo::CleanupFuncT   func
            );

    /// Function to a set list of command modules ids that will be displayed in the toolbar
    /// of work pane module. (optional)
    ///
    /// @param[in] toolbarModuleIds
    ///      List containing command module ids.
    /// @param[in] size
    ///      Size of the toolbarModuleIds.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setWorkPaneToolbarIds(
            const Octane::ModuleIdT *const            toolbarModuleIds,
            const size_t                              size
            );

private:
    static GRPCSettings & getGRPCSettings();
};
