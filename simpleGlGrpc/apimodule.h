// Copyright (C) 2025 OTOY NZ Ltd.
// Stub for apimodule.h

#pragma once

#include <string>

// Simplified stub for API module
class ApiModule {
public:
    virtual ~ApiModule() = default;
    
    virtual bool initialize() { return true; }
    virtual void shutdown() {}
    virtual std::string getName() const { return "ApiModule"; }
};