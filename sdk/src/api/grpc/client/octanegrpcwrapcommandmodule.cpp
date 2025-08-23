// Copyright (C) 2025 OTOY NZ Ltd.

//myself
#include "octanegrpcwrapcommandmodule.h"
// application
#include "apicommandmoduleinfoclient.h"
#include "apimoduleglobalclient.h"
#include "apiimageclient.h"

using namespace OctaneWrap;

void CommandModule::registerModule(
    const Octane::ModuleIdT                                   moduleId,
    const char *                                              fullName,
    const char *                                              description,
    const char *                                              author,
    const Octane::VersionT                                    versionNumber,
    const Octane::ApiCommandModuleInfo::CommandModuleRunFuncT runFunction,
    const OctaneGRPC::ApiImageProxy &                         icon,
    const char *                                              shortcutGroupName,
    const int                                                 shortcutKeyCode,
    const int                                                 shortcutModifierKeyFlag)
{
    OctaneGRPC::ApiCommandModuleInfoProxy info = OctaneGRPC::ApiCommandModuleInfoProxy::create(moduleId, fullName, description, author, versionNumber);
    info.setRunFunction(runFunction);

    info.setIcon(&icon);
    info.assignShortcutKey(shortcutGroupName, shortcutKeyCode, shortcutModifierKeyFlag);

    // register as dynamically linked module
    OctaneGRPC::ApiModuleGlobalProxy::registerCommandModule(info);
    info.destroy();
 }