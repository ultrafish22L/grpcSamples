// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#include "grpcmaininterface.h"
#include "apimodule.h"

class GRPCModuleBase;
class ApiImageProxy;

class TexCommanderModule : public GRPCMainInterface
{
public:

    TexCommanderModule(GRPCModuleBase * main);

    // called by octane when loading the module
    virtual void start(
        const std::string & callbackSourse,
        const bool          displayEnglish,
        const int           secondLanguage) override;

    // called by octane when unloading the module
    virtual void stop() override;

    // return true to indicate that the module is able to be loaded
    virtual bool isReady() override;

    GRPCModuleBase * mModuleBase = nullptr;

    void registerModule(
        const Octane::ModuleIdT                                   moduleId,
        const char *                                              fullName,
        const char *                                              description,
        const char *                                              author,
        const Octane::VersionT                                    versionNumber,
        const Octane::ApiCommandModuleInfo::CommandModuleRunFuncT runFunction,
        const ApiImageProxy &                                     icon,
        const char *                                              shortcutGroupName = nullptr,
        const int                                                 shortcutKeyCode = -1,
        const int                                                 shortcutModifierKeyFlag = 0);
};