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
    const ApiImageProxy &                                     icon,
    const char *                                              shortcutGroupName,
    const int                                                 shortcutKeyCode,
    const int                                                 shortcutModifierKeyFlag)
{
    ApiCommandModuleInfoProxy info = ApiCommandModuleInfoProxy::create(moduleId, fullName, description, author, versionNumber);
    info.setRunFunction(runFunction);

    info.setIcon(&icon);
    info.assignShortcutKey(shortcutGroupName, shortcutKeyCode, shortcutModifierKeyFlag);

    // register as dynamically linked module
    ApiModuleGlobalProxy::registerCommandModule(info);
    info.destroy();

    //Octane::ApiCommandModuleInfo * info = Octane::ApiCommandModuleInfo::create(
    //    moduleId, fullName, description, author, versionNumber);

    //info->setRunFunction(runFunction);
    //info->setIcon(icon);
    //info->assignShortcutKey(shortcutGroupName, shortcutKeyCode, shortcutModifierKeyFlag);

    //if (isStaticallyLinked)
    //{
    //    // register as statically linked module
    //    Octane::registerStaticCommandModule(*info);
    //}
    //else
    //{
    //    // register as dynamically linked module
    //    Octane::registerCommandModule(*info);
    //}

    //info->destroy();
 }