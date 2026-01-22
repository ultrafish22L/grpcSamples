// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include "apiocioconfigloader.h"
#include "octaneenums.h"

namespace Octane
{

/// Reacts to changes to local preferences to load the appropriate OCIO config and keep track of the
/// current OCIO context.
class OCTANEAPI_DECL ApiOcioContextManager final
{
public:

    /// Guesses the best values to use for the intermediate color space based on the names of color
    /// spaces in the OCIO config.
    ///
    /// @param config
    ///     The OCIO config to select a color space from. This pointer needs to remain valid for as
    ///     long as the value returned in guessedOcioName will be used. Must not be null.
    /// @param[out] guessedOctaneValue
    ///     The guessed Octane half of the intermediate color space. Only modified if this function
    ///     function returns true.
    /// @param[out] guessedOcioName
    ///     The guessed OCIO half of the intermediate color space. Only modified if this function
    ///     returns true. This pointer will remain valid until the config is destroyed. Will not be
    ///     set to null (but will remain null if was was initially null and this function fails).
    /// @return
    ///     True if the guess succeeded. False if no suitable intermediate color space was found.
    static bool guessIntermediateColorSpace(
        const ApiOcioConfig *config,
        NamedColorSpace &guessedOctaneValue,
        const char *&guessedOcioName);


    /// Callback to be called when the current OCIO context changes.
    ///
    /// @param config
    ///     The config of the current context, or null if there is no config loaded. This pointer is
    ///     only valid for the duration of this call; to use the context longer than that, clone()
    ///     the result (and make sure to destroy() the clone when done).
    /// @param contextUsableForConversion
    ///     Whether the current context is suitable for use by the renderer for color conversions.
    ///     This is true only when there is a config loaded and that config contains a color space
    ///     with the chosen intermediate color space OCIO name.
    /// @param privateData
    ///     The private data pointer that was passed to addCallback when this callback was
    ///     registered.
    typedef void (*CallbackT)(
        ApiOcioConfig *config,
        bool contextUsableForConversion,
        void *privateData);


    /// @return
    ///     The created context manager. This must be destroyed with destroy(). Will not be null.
    static ApiOcioContextManager *create();


    /// Must not be called from a callback function. After this method returns, callbacks will no
    /// longer be called.
    void destroy();

    /// Registers a callback to be called when the current OCIO context changes. Callbacks will be
    /// called in no particular order. The same callback can be registered multiple times; it will
    /// be called for each registration.
    ///
    /// The callback will be called immediately with the current state.
    ///
    /// Must not be called from a callback function.
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
    /// Must not be called from a callback function. After this method returns, the given callback
    /// will no longer be called.
    ///
    /// @param callback
    ///     The function that was passed to addCallback.
    /// @param privateData
    ///     The private data pointer that was passed to addCallback.
    void removeCallback(
        CallbackT callback,
        void *privateData);

    /// Gets the filename of the default config to use if it is not overridden by local preferences.
    /// This filename comes from the "OCIO" environment variable.
    ///
    /// @return
    ///     Will not be null. This pointer remains valid until this context manager is destroyed.
    const char *getDefaultConfigFilename() const;

    /// Gets the most recent config filename that we tried to load.
    ///
    /// @return
    ///     Will not be null. This pointer remains valid until the next time any local preferences
    ///     are changed, or this context manager is destroyed, whichever comes first.
    const char *getLastConfigLoadFilename() const;

    /// Gets the config of the current context, if there is a config loaded.
    ///
    /// @return
    ///     If there is a config loaded, a newly created config wrapper (must be destroyed with
    ///     destroy()). Null otherwise.
    ApiOcioConfig *createConfig() const;

    /// Gets whether the current context is suitable for use by the renderer for color conversions.
    /// This is true only when there is a config loaded and that config contains a color space with
    /// the chosen intermediate color space OCIO name.
    bool getContextUsableForConversion() const;

    /// Sets the current config. This should only be called when the local preferences are about to
    /// be changed so that this config will be the one loaded. This allows the load to be prevented
    /// in the case where the config has already been loaded elsewhere.
    ///
    /// @param filename
    ///     The filename of the config file. Must not be null.
    /// @param config
    ///     The config that was loaded from that filename, or null if loading a config from that
    ///     filename failed.
    void donateConfig(
        const char *filename,
        const ApiOcioConfig *config);

    /// This should be called after calling donateConfig and changing local preferences, to handle
    /// the case where the local preferences technically didn't change (because filenames etc. are
    /// the same), but the donated config was loaded from a newer version of the same file that has
    /// been modified on disk. This prevents continuing to use a stale config even though we loaded
    /// a newer version and tried to donate it.
    void handlePendingConfigDonation();

private:

    ApiOcioContextManager();

    ApiOcioContextManager(
        const ApiOcioContextManager &other);

    ApiOcioContextManager &operator=(
        const ApiOcioContextManager &other);

    ~ApiOcioContextManager();

};

}
