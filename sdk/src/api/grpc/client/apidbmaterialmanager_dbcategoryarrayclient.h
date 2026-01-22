// Copyright (C) 2026 OTOY NZ Ltd.

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


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiDBMaterialManager_DBCategoryArray
class ApiDBMaterialManagerProxy_DBCategoryArray : public GRPCBase
{
public:
    /// Initializes this array with size elements.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void init(
            const size_t   size
            );

    /// Destroys all the elements in this array.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void free();

    /// Returns the internal array of categories.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::vector<Octane::ApiDBMaterialManager::DBCategory> getCategory();

    /// Returns the number of categories.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t getCount() const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
