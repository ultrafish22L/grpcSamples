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


#include "octaneinfos.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiCompatibilityModeInfo
class ApiCompatibilityModeInfoProxy : public GRPCBase
{
public:
    /// Gets the first version of Octane that has this behavior, i.e. the version where this
    /// compatibility mode was added.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The start version, which will always be less than or equal to OCTANE_VERSION.
    Octane::VersionT startVersion() const;

    /// Gets the name of the compatibility mode.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The name, which is not null. The pointer points to a string literal that will never be
    ///     modified or deallocated.
    std::string name() const;

    /// Gets a brief description of how this behavior differs from the behavior of the current
    /// version of Octane.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The description, or null if this mode doesn't have a description because it represents
    ///     the current version of Octane. If not null, the pointer points to a string literal that
    ///     will never be modified or deallocated.
    std::string description() const;

private:
    static GRPCSettings & getGRPCSettings();
};
