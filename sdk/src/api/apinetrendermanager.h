// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_NET_RENDER_MANAGER_H_
#define _API_NET_RENDER_MANAGER_H_  1

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#include "apiarray.h"
#include "octaneenums.h"
#include "octanenet.h"
#include "octanetypes.h"

namespace Octane
{

struct NetDaemonInfo;
struct NetRenderSettings;

/// API for controlling network rendering. Network rendering works with 1 master
/// (either the standalone or a plugin) and several render nodes (a special build of Octane).
/// Concepts:
/// - network master:
///     A master listens on the network for incoming render node connections. When a render node
///     connects, the master will distribute it some work to do.
/// - network render node:
///     When a render node starts, it tries to connect to a master it received via the command line.
///     The render node will just stop if it cannot connect to the master. All render nodes do is
///     wait for masters to assign them some work. A render node that's working for one master
///     cannot work for another master.
/// - network daemon:
///     The daemons are there for configuration convenience. IN PRINCIPLE WE DON'T NEED A DAEMON
///     FOR NETWORK RENDERING TO WORK. A daemon is a process that runs all the time on the PC where
///     the render node is located. It's like the render node's personal agent. The daemon will:
///         - start a render node telling it to work for a master
///         - stop the render node working for a master
///         - monitor the render node and make sure it hasn't crashed
/// - master discovery (a.k.a. master beacon)
///     This is a thread on the master that broadcasts a periodic beacon message that is picked
///     up by the daemons on the network. When a daemon picks up a master baecon, it will inform
///     the master about the render node it is managing (e.g. it will tell if the render node is
///     still availabe, how many GPUs it has available, ...)
///
/// This API is not thread safe!
class OCTANEAPI_DECL ApiNetRenderManager
{
public:

    ///--- Master configuration ---

    /// Configures network rendering. Network rendering can only be configured
    /// when network rendering is disabled! Also, calling this function will not automatically
    /// enable the network rendering, which needs to be done explicitly via enable().
    ///
    /// @param[in]  settings
    ///     New network rendering settings.
    /// @return
    ///     TRUE if configuration was successful, FALSE if the configuration
    ///     failed (check to logs to figure out what happened).
    static bool configure(
        const NetRenderSettings &settings);

    /// Returns the current net render configuration.
    /// NOTE: The arrays in the returned structure stay valid until the next call of this function.
    static NetRenderSettings configuration();

    /// Enables/disables network rendering.
    static void enable(
        const bool enable);

    /// Returns TRUE if network rendering is supported in this build.
    static bool isSupported();

    /// Checks if network rendering is enabled.
    static bool isEnabled();

    /// Stores the current network rendering configuration in the application preferences.
    static void saveConfiguration();

    /// Opens a modal dialog to allow the user to set the network render configuration. When the
    /// the function returns, the dialog has been closed already and the settings have been stored
    /// in the Octane application preferences.
    static void openOctanePreferences();


    ///--- Network interfaces ---
 
    /// Returns the number of network interfaces available on this computer.
    static size_t networkInterfaceCount();

    /// Retrieves info about a specific network interface on this computer.
    ///
    /// @param[in]  interfaceIx
    ///     interface index in [0,networkInterfaceCount()-1]
    /// @return
    ///     network interface info
    static NetInterfaceInfo networkInterface(
        const size_t subnetIx);


    ///--- Network status ---

    typedef void (*OnStatusUpdateT)(
        const NetRenderStatus &status,
        void                  *userData);

    /// Registers a status update called. Called every time the status of
    /// network rendering is updated.
    ///
    /// @param[in]  callback
    ///     callback function, set this to NULL if your not interested in
    ///     updates anymore
    /// @param[in]  userData
    ///     optional user data provided back with the callback.
    static void setNetStatusListener(
        OnStatusUpdateT callback,
        void            *userData=NULL);

    /// Returns the current net render status. You can use this function to poll the status, but
    /// it's recommended to use the callback wherever possible.
    static NetRenderStatus status();


    ///--- Daemon management ---

    typedef void(*OnDaemonUpdateT)(
        const ApiArray<const NetDaemonInfo*> &daemonInfoArray,
        void                                 *user);

    /// Register a daemon listeners. Called every time a daemon appears,
    /// disappears or changes it's state.
    ///
    /// @param[in]  callback
    ///     callback function
    /// @param[in]  userData
    ///     optional user data provided back with the callback
    static void setDaemonListener(
        OnDaemonUpdateT callback,
        void            *userData=NULL);

    /// Binds a daemon to this master. This means that we are going to use the
    /// render node on the daemon's PC to do some render work for us. Network rendering
    /// needs to be enabled to do this!
    ///
    /// @param[in]  ipAddress
    ///     Ip address of the daemon.
    /// @return
    ///     TRUE on success, FALSE on failure.
    static bool bindDaemon(
        const IPv4T ipAddress);

    /// Unbinds a daemon from this master. This means that we allow the render node on
    /// the daemon's PC to do some work for another master. Network rendering needs
    /// to be enabled to do this!
    static void unbindDaemon(
        const IPv4T ipAddress);

    /// Steals a daemon. The daemon will disconnect from its master and tries to bind it
    /// for us. Network rendering needs to be enabled to do this!
    ///
    /// @param[in]  ipAddress
    ///     Ip address of the daemon.
    /// @return
    ///     TRUE on success, FALSE if we cannot bind or it is already bound to us.
    static bool stealDaemon(
        const IPv4T ipAddress);
};

} // namespace Octane

#endif  // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#endif // #ifndef _API_NET_RENDER_MANAGER_H_
