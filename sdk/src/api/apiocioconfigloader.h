// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"


namespace Octane
{

class ApiOcioConfig;

/// Loads OCIO configs asynchronously.
///
/// All methods in this class must only be called on the main thread unless otherwise specified.
class OCTANEAPI_DECL ApiOcioConfigLoader final
{
public:

    /// Callback to be called when the state of loading an OCIO config changes. There are three
    /// states that can be reported: loading, failure (not loading but no config) and success (not
    /// loading and have a config).
    ///
    /// Will be called on an arbitrary thread (which may be the main thread). Must not lock any
    /// mutex that is locked around any access to the config loader. Will not be called multiple
    /// times concurrently.
    ///
    /// @param loading
    ///     True if we are currently loading a config, false otherwise.
    /// @param config
    ///     The config that was loaded, if there was a config filename to load and we finished
    ///     loading it successfully. Null otherwise (i.e. there was no filename, or we're currently
    ///     loading, or loading failed). This pointer is only valid for the duration of this call;
    ///     to use the config longer than that, clone() the result (and make sure to destroy() the
    ///     clone when done).
    /// @param privateData
    ///     The private data pointer that was passed to addCallback when this callback was
    ///     registered.
    typedef void (*CallbackT)(
        bool loading,
        ApiOcioConfig *config,
        void *privateData);


    /// @return
    ///     The created config loader. This must be destroyed with destroy(). Will not be null.
    static ApiOcioConfigLoader *create();


    /// Must not be called from a callback function. If there is a callback currently being called,
    /// will block until it returns. After this method returns, callbacks will no longer be called.
    void destroy();

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
    void addCallback(
        CallbackT callback,
        void *privateData);

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
    void removeCallback(
        CallbackT callback,
        void *privateData);

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
    void load(
        const char *filename);

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
    /// @return
    ///     The current config (must be destroyed with destroy()), or null if there is no config.
    ApiOcioConfig *createConfig(
        bool waitIfLoading);

private:

    ApiOcioConfigLoader();

    ApiOcioConfigLoader(
        const ApiOcioConfigLoader &other);

    ApiOcioConfigLoader &operator=(
        const ApiOcioConfigLoader &other);

    ~ApiOcioConfigLoader();

};

}
