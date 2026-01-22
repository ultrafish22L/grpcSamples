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
namespace OctaneGRPC
{
    class ApiBinaryTableProxy;
}


#include "apimoduledata.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiModuleData
class ApiModuleDataProxy : public GRPCBase
{
public:
    /// Loads application data stored for this module.
    ///
    /// @param[in]  moduleId
    ///     Id of the module loading the data.
    /// @param[out] octaneVersion
    ///     Version of Octane used to store the data.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to loaded data. If there was no data stored for the module, an empty table is
    ///     returned. A null pointer is returned when the table could not be loaded. The returned
    ///     data should be disposed of via destroy().
    static ApiBinaryTableProxy loadApplicationData(
            const Octane::ModuleIdT                   moduleId,
            uint32_t &                                octaneVersion
            );

    /// Stores application data. The application data that was already stored for this module is
    /// overwritten.
    ///
    /// @param[in]  moduleId
    ///     Id of the module storing the data.
    /// @param[in]  table
    ///     Table with the data.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE when the data was saved successfully, FALSE otherwise.
    static bool storeApplicationData(
            const Octane::ModuleIdT                   moduleId,
            const ApiBinaryTableProxy &               table
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
