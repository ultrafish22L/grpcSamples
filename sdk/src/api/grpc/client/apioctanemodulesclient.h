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
class ApiOctaneModuleInfoProxy;


#include "apioctanemodules.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiOctaneModules
class ApiOctaneModulesProxy : public GRPCBase
{
public:
    /// A directory from which modules will be loaded. The alternate method to
    /// get application preference node and set the path in the A_MODULES_DIRECTORY 
    /// attribute 
    ///
    /// NOTE: Modules are loaded only at start. so if a new path is set then you will have
    /// to restart the octane/app in order to load new modules.
    ///
    /// @param[in] newPath
    ///     The new modules directory
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns
    ///     Return TRUE if the directory is set successfully. Otherwise FALSE.
    ///     FALSE means the newPath not exist.
    static bool setDirectory(
            const char *                              newPath
            );

    /// The current directory where the octane loads modules from.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::string getDirectory(            );

    /// Returns module information for the moduleId
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiOctaneModuleInfoProxy getModuleInfo(
            const Octane::ModuleIdT                   moduleId
            );

    /// Return list of all available ids of node graph modules
    /// Note: To create a module nodegraph pass the module id
    /// to the ApiNodeGraph::Create function
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::vector<Octane::ModuleIdT> getNodegraphModules(            );

    /// Return list of all available ids of command modules
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static std::vector<Octane::ModuleIdT> getCommandModules(            );

    /// Execute a command module.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns
    ///     Returns TRUE if the command was successfully executed.
    ///     Otherwise FALSE.
    static bool runCommandModule(
            const Octane::ModuleIdT                   moduleId
            );

private:
    static GRPCSettings & getGRPCSettings();
};
