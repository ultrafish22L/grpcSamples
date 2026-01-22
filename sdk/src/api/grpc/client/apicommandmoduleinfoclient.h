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
namespace OctaneGRPC
{
    class ApiImageProxy;
}


#include "apimodule.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiCommandModuleInfo
class ApiCommandModuleInfoProxy : public GRPCBase
{
public:
    /// Creates info for Api command module
    ///
    /// @param[in]  moduleId
    ///     Unique ID for this module. should start from 1000101.
    /// @param[in]  fullName
    ///     Name with categories that will be used to group it in the user interface.
    ///     Must have at least one category to display it in the module menu
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
    static ApiCommandModuleInfoProxy create(
            const Octane::ModuleIdT                   moduleId,
            const char *const                         fullName,
            const char *const                         description,
            const char *const                         author,
            const Octane::VersionT                    versionNumber
            );

    /// Destroys a ApiCommandModuleInfo object created by create().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Function to set the command module run function. The run function will be called every time
    /// the command is executed.(mandatory)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setRunFunction(
            CommandModuleRunFuncT   func
            );

    /// Function to set icon for a command module. (optional)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setIcon(
            const ApiImageProxy *const   icon
            );

    /// Function to assign shortcut key for a command module. (optional)
    ///
    /// @param[in]  shortcutGroupName
    ///     Shortcut group which its belong to.
    /// @param[in]  shortcutKeyCode
    ///     A code that represents the key - this value must be one of special constants listed above
    ///     or an 8-bit character code such as a letter (case is ignored) digit like 'a','c','v'..etc,
    ///     or a simple key like "," or ".".
    ///     Only works when this command is associated with the Api work pane.
    /// @param[in]  shortcutModifierKeyFlag
    ///     The modifiers to associate with the shortcut Keycode. The value is a combination of
    ///     KeyModifierFlag bitwise or-ed together or 0 if no modifier is required.
    ///     Only used when the passed in shortcutKey is not -1.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void assignShortcutKey(
            const char *const                         shortcutGroupName,
            const int                                 shortcutKeyCode,
            const int                                 shortcutModifierKeyFlag
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
