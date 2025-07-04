// Copyright (C) 2025 OTOY NZ Ltd.
// Stub for grpcbase.h

#pragma once

#include "grpc_stubs.h"

// Simplified base class for gRPC operations
class GRPCBase {
public:
    virtual ~GRPCBase() = default;
    
protected:
    static GRPCSettings& getGRPCSettings() {
        return GRPCSettings::getInstance();
    }
};