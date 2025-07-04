// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#include "grpcmaininterface.h"

class GRPCModuleBase;

class EmptyModule : public GRPCMainInterface
{
public:

    EmptyModule(GRPCModuleBase * main);

    // called by octane when loading the module
    virtual void start(
        const std::string & callbackSourse,
        const bool          displayEnglish,
        const int           secondLanguage) override;

    // called by octane when unloading the module
    virtual void stop() override;

    // return true to indicate that the module is able to be loaded
    virtual bool isReady() override;

private:

    GRPCModuleBase * mModuleBase = nullptr;
};