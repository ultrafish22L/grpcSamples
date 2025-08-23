// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_COMMAND_MODULE_H_
#define _OCTANE_WRAP_COMMAND_MODULE_H_ 1
// system
#include <functional>
//api includes
#include "apimodulenodegraph.h"
#include "apimodule.h"

namespace OctaneGRPC
{
    class ApiImageProxy;
}

namespace OctaneWrap
{

    class CommandModule
    {

    public:

        /// Register info for command module
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
        /// @param[in]  runFunction
        ///     This function will be called when this command module executed.
        /// @param[in]  icon
        ///     Icon related to this command module.
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
        static void registerModule(
            const Octane::ModuleIdT                                   moduleId,
            const char *                                              fullName,
            const char *                                              description,
            const char *                                              author,
            const Octane::VersionT                                    versionNumber,
            const Octane::ApiCommandModuleInfo::CommandModuleRunFuncT runFunction,
            const OctaneGRPC::ApiImageProxy &                         icon,
            const char *                                              shortcutGroupName       = nullptr,
            const int                                                 shortcutKeyCode         = -1,
            const int                                                 shortcutModifierKeyFlag = 0);
    };

} // namespace OctaneWrap


#endif // _OCTANE_WRAP_COMMAND_MODULE_H_
