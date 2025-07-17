// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"
class ApiNodeProxy;


#include "apinodesystem.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiNodeArray
class ApiNodeArrayProxy : public GRPCBase
{
public:
    /// Returns the size of the item list.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t size() const;

    /// Returns the item at the given index (or NULL).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ApiNodeProxy get(
            const size_t   index
            ) const;

    /// Returns the internal array (owned by this object).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::vector<ApiNodeProxy> items();

    /// Init function (only used internally).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void init(
            const size_t   size
            );

private:
    static GRPCSettings & getGRPCSettings();
};
