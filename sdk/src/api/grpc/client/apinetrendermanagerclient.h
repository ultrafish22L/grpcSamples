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


#include "apinetrendermanager.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiNetRenderManager
class ApiNetRenderManagerProxy : public GRPCBase
{
public:
    /// Configures network rendering. Network rendering can only be configured
    /// when network rendering is disabled! Also, calling this function will not automatically
    /// enable the network rendering, which needs to be done explicitly via enable().
    ///
    /// @param[in]  settings
    ///     New network rendering settings.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if configuration was successful, FALSE if the configuration
    ///     failed (check to logs to figure out what happened).
    static bool configure(
            const Octane::NetRenderSettings &   settings
            );

    /// Returns the current net render configuration.
    /// NOTE: The arrays in the returned structure stay valid until the next call of this function.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::NetRenderSettings configuration();

    /// Enables/disables network rendering.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void enable(
            const bool   enable
            );

    /// Returns TRUE if network rendering is supported in this build.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isSupported();

    /// Checks if network rendering is enabled.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isEnabled();

    /// Stores the current network rendering configuration in the application preferences.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void saveConfiguration();

    /// Opens a modal dialog to allow the user to set the network render configuration. When the
    /// the function returns, the dialog has been closed already and the settings have been stored
    /// in the Octane application preferences.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void openOctanePreferences();

    /// Returns the number of network interfaces available on this computer.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static size_t networkInterfaceCount();

    /// Retrieves info about a specific network interface on this computer.
    ///
    /// @param[in]  interfaceIx
    ///     interface index in [0,networkInterfaceCount()-1]
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     network interface info
    static Octane::NetInterfaceInfo networkInterface(
            const size_t   subnetIx
            );

    /// Registers a status update called. Called every time the status of
    /// network rendering is updated.
    ///
    /// @param[in]  callback
    ///     callback function, set this to NULL if your not interested in
    ///     updates anymore
    /// @param[in]  userData
    ///     optional user data provided back with the callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setNetStatusListener(
            Octane::ApiNetRenderManager::OnStatusUpdateT callback,
            void *                                    userData
            );

    /// Returns the current net render status. You can use this function to poll the status, but
    /// it's recommended to use the callback wherever possible.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static Octane::NetRenderStatus status();

    /// Register a daemon listeners. Called every time a daemon appears,
    /// disappears or changes it's state.
    ///
    /// @param[in]  callback
    ///     callback function
    /// @param[in]  userData
    ///     optional user data provided back with the callback
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void setDaemonListener(
            Octane::ApiNetRenderManager::OnDaemonUpdateT callback,
            void *                                    userData
            );

    /// Binds a daemon to this master. This means that we are going to use the
    /// render node on the daemon's PC to do some render work for us. Network rendering
    /// needs to be enabled to do this!
    ///
    /// @param[in]  ipAddress
    ///     Ip address of the daemon.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE on failure.
    static bool bindDaemon(
            const Octane::IPv4T   ipAddress
            );

    /// Unbinds a daemon from this master. This means that we allow the render node on
    /// the daemon's PC to do some work for another master. Network rendering needs
    /// to be enabled to do this!
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void unbindDaemon(
            const Octane::IPv4T   ipAddress
            );

    /// Steals a daemon. The daemon will disconnect from its master and tries to bind it
    /// for us. Network rendering needs to be enabled to do this!
    ///
    /// @param[in]  ipAddress
    ///     Ip address of the daemon.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE on success, FALSE if we cannot bind or it is already bound to us.
    static bool stealDaemon(
            const Octane::IPv4T   ipAddress
            );

private:
    static GRPCSettings & getGRPCSettings();
};
