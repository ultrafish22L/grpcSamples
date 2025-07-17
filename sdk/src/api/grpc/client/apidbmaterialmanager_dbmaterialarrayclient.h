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


#include "apidbmaterialmanager.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiDBMaterialManager_DBMaterialArray
class ApiDBMaterialManagerProxy_DBMaterialArray : public GRPCBase
{
public:
    /// Initializes this list with size elements.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void init(
            const size_t   size
            );

    /// Destroys all the elements in this array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void free();

    /// Returns the internal array of materials
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::vector<Octane::ApiDBMaterialManager::DBMaterial> getMaterial();

    /// Returns the number of materials.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t getCount() const;

private:
    static GRPCSettings & getGRPCSettings();
};
