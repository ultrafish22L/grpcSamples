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
    class ApiLocalDBProxy ;
    class ApiLocalDBProxy_Category;
    class ApiLocalDBProxy_Package;
}


#include "apilocaldb.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiLocalDB
class ApiLocalDBProxy : public GRPCBase
{
public:
    /// Tells whether @ref ApiLocalDb is supported by this build
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isSupported();

    /// Returns the root category of the local DB
    ///
    /// @note The returned category must be freed using free()
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     the root category or a NULL pointer if there was an error, in which case
    ///     there should have been additional error messages on the log.
    static ApiLocalDBProxy_Category root();

    /// Moves the localDb folder to a new location. This call will also update the
    /// preferences node.
    ///
    /// This will raise a CATEGORY_REFRESH event for root if the directory is changed.
    ///
    /// @param[in] newPath
    ///     The new localDB directory
    /// @param[in] moveFiles
    ///     if true, move all existing packages to the new location. If the original
    ///     folder is empty after this operation it will be deleted.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     true if the operation was successful, false if the new location is not writable or
    ///     there was an error in which case there should have been additional error messages
    ///     on the log.
    static bool setRootDirectory(
            const char *                              newPath,
            bool                                      moveFiles
            );

    /// Add an observer to receive change notifications for localDB updates
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void addObserver(
            void *                                    opaqueData,
            Octane::ApiLocalDB::ObserverCallback *    callback
            );

    /// Remove an observer to receive change notifications for localDB updates
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void removeObserver(
            void *                                    opaqueData,
            Octane::ApiLocalDB::ObserverCallback *    callback
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
