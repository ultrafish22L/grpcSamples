// Copyright (C) 2025 OTOY NZ Ltd.
// Stub for clientcallbackmgr.h

#pragma once

// Simplified stub for client callback manager
class ClientCallbackMgr {
public:
    static ClientCallbackMgr& getInstance() {
        static ClientCallbackMgr instance;
        return instance;
    }
    
    void initialize() {}
    void shutdown() {}
};