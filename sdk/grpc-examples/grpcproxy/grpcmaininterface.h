// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once
#include <string>

// interface used to simplfy Module development. New modules can implement this interface.
class GRPCMainInterface
{
public:

    // called by octane when loading the module
    virtual void start(
        const std::string & callbackSourse,
        const bool          displayEnglish,
        const int           secondLanguage) = 0;

    // called by octane when unloading the module
    virtual void stop() = 0;

    // return true to indicate that the module is able to be loaded
    virtual bool isReady() = 0;
};


