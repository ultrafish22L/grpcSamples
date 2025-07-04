// Copyright (C) 2025 OTOY NZ Ltd.
// Stub for gRPC settings and basic types

#pragma once

#ifdef OCTANE_GRPC_ENABLED
#include "src/api/grpc/grpcsettings.h"
#else
// Stub implementation when gRPC is not available
#include <memory>
#include <string>

namespace grpc {
    class Channel;
}

class GRPCSettings {
public:
    static GRPCSettings& getInstance() {
        static GRPCSettings instance;
        return instance;
    }
    
    void setServerAddress(const std::string& address) {
        m_serverAddress = address;
    }
    
    void setUniqueString(const std::string& uniqueStr) {
        m_uniqueString = uniqueStr;
    }
    
    std::shared_ptr<grpc::Channel> getChannel() {
        // Return null when gRPC is not enabled
        return nullptr;
    }
    
private:
    std::string m_serverAddress;
    std::string m_uniqueString;
};
#endif