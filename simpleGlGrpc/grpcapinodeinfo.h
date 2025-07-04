// Copyright (C) 2025 OTOY NZ Ltd.
// Stub for grpcapinodeinfo.h

#pragma once

#include "grpc_stubs.h"

// Simplified stub for gRPC API node info
class GRPCApiNodeInfo {
public:
    virtual ~GRPCApiNodeInfo() = default;
    
    virtual bool isValid() const { return true; }
    virtual std::string getName() const { return "NodeInfo"; }
};