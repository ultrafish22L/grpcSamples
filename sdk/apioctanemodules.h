// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_OCTANE_MODULES_H_
#define _API_OCTANE_MODULES_H_   1

#include "apiarray.h"

namespace Octane
{
// forward declaration
struct ApiOctaneModuleInfo;

//--------------------------------------------------------------------------------------------------
/// This class provide interface to access all octane external modules.
class OCTANEAPI_DECL ApiOctaneModules
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
    /// @returns
    ///     Return TRUE if the directory is set successfully. Otherwise FALSE.
    ///     FALSE means the newPath not exist.
    static bool setDirectory(
        const char * newPath);

    /// The current directory where the octane loads modules from.
    static const char* getDirectory();

    /// Returns module information for the moduleId
    static const ApiOctaneModuleInfo* getModuleInfo(
        const Octane::ModuleIdT moduleId);

    /// Return list of all available ids of node graph modules
    /// Note: To create a module nodegraph pass the module id
    /// to the ApiNodeGraph::Create function
    static ApiArray<Octane::ModuleIdT> getNodegraphModules();

    /// Return list of all available ids of command modules
    static ApiArray<Octane::ModuleIdT> getCommandModules();

    /// Execute a command module.
    ///
    /// @returns
    ///     Returns TRUE if the command was successfully executed.
    ///     Otherwise FALSE.
    static bool runCommandModule(
        const Octane::ModuleIdT moduleId);

};

} // namespace Octane


#endif // #infdef _API_MODULES_H_
