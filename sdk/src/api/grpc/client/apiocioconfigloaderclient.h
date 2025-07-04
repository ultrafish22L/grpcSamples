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
class ApiOcioConfigProxy;


#include "apiocioconfigloader.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiOcioConfigLoader
class ApiOcioConfigLoaderProxy : public GRPCBase
{
public:
        /// @param[out] status
    ///     Contains the status of the gRPC call
/// @return
    ///     The created config loader. This must be destroyed with destroy(). Will not be null.
    static ApiOcioConfigLoaderProxy create(            );

    /// Must not be called from a callback function. If there is a callback currently being called,
    /// will block until it returns. After this method returns, callbacks will no longer be called.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy(            );

    /// Registers a callback to be called when the state of loading an OCIO config changes.
    /// Callbacks will be called in no particular order. The same callback can be registered
    /// multiple times; it will be called for each registration.
    ///
    /// The callback will be called immediately with the current state before any asynchronous
    /// calls.
    ///
    /// The initial state of the config loader is that there is no config loaded.
    ///
    /// Must not be called from a callback function. If there is a callback currently being called,
    /// will block until it returns.
    ///
    /// @param callback
    ///     The function to call with the current state now and with the new state whenever the
    ///     state changes.
    /// @param privateData
    ///     The private data pointer to be passed to the callback whenever it is called. This isn't
    ///     otherwise used and may be any value, including null.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addCallback(
            GRPCCallback1T                           callback,
            void *                                    privateData
            );

    /// Deregisters a callback that was registered with addCallback. If the same callback with the
    /// same private data pointer was registered multiple times, this will only remove one of the
    /// registrations. It is safe to try to remove a callback that was never added; this does
    /// nothing.
    ///
    /// Must not be called from a callback function. If there is a callback currently being called,
    /// will block until it returns. After this method returns, the given callback will no longer be
    /// called.
    ///
    /// @param callback
    ///     The function that was passed to addCallback.
    /// @param privateData
    ///     The private data pointer that was passed to addCallback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void removeCallback(
            GRPCCallback1T                           callback,
            void *                                    privateData
            );

    /// Starts loading a config file. This will cancel any load that is currently in progress.
    ///
    /// Callbacks will be called when the state changes, if it changes. If the filename matches the
    /// previous call to this function, the state won't change. Otherwise, the state will change
    /// immediately to loading (unless it was already loading) and then later on to either success
    /// or failure.
    ///
    /// Must not be called from a callback function. May synchronously call callbacks.
    ///
    /// @param filename
    ///     The path to the config file to load, or an empty string to unload any config. Must not
    ///     be null.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void load(
            const char *                              filename
            );

    /// Gets the current config. This is the config from an arbitrary point in time between when
    /// this function was called and when it returned; it may no longer reflect the current state
    /// after this function returns.
    ///
    /// Must not be called from a callback function.
    ///
    /// @param waitIfLoading
    ///     This parameter only has an effect if we are currently loading a config. In that case, if
    ///     this is false, this function will return null, and if this is true, this function will
    ///     block until the load either succeeds (will return the loaded config) or fails (will
    ///     return null). In the case where this function blocks, all listeners are guaranteed to
    ///     have been notified of the load finishing before this function returns.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The current config (must be destroyed with destroy()), or null if there is no config.
    ApiOcioConfigProxy createConfig(
            bool                                      waitIfLoading
            );

private:
    static GRPCSettings & getGRPCSettings();
};
