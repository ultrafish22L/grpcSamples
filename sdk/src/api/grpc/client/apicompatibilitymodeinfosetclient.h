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


#include "octaneinfos.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiCompatibilityModeInfoSet
class ApiCompatibilityModeInfoSetProxy : public GRPCBase
{
public:
    /// Gets the number of compatibility modes.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The number of modes in this list, which may be zero.
    uint32_t size() const;

    /// Gets the info for one of the compatibility modes.
    ///
    /// @param index
    ///     The index of the mode for which to get the info. Must be less than size().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The info. Refers to an object that will never be modified or deallocated.
    const Octane::ApiCompatibilityModeInfo info(
            uint32_t   index
            ) const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
