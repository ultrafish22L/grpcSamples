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


#include "apilogmanager.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiLogManager
class ApiLogManagerProxy : public GRPCBase
{
public:
    /// Registers a callback that gets called every time there is a log message. You can use this
    /// mechanism to display the log messages in your own code.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool registerLogCallbackProc(
            Octane::ApiLogManager::ApiLogCallbackProc *   proc
            );

    /// Removes a previously registered log callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool unregisterLogCallbackProc(
            Octane::ApiLogManager::ApiLogCallbackProc *   proc
            );

    /// Opens the Octane log into a separate window. There can be only a single log window so
    /// calling this function multiple times when the log window is already open has no effect.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void openOctaneLogWindow();

    /// Writes the specified text to the Octane log. A line feed is added automatically.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void log(
            const char *   text
            );

    /// Writes the specified text to the Octane log. A line feed is added automatically.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void logError(
            const char *   errorMsg
            );

    /// Writes the specified text to the Octane log. A line feed is added automatically.
    /// Takes printf style formatting parameters. WARNING: the formatted string can be
    /// maximum 1000 chars.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void logFmt(
            const char *   fmt
            );

    /// Writes the specified text to the Octane log. A line feed is added automatically.
    /// Takes printf style formatting parameters. WARNING: the formatted string can be
    /// maximum 1000 chars.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void logErrorFmt(
            const char *   fmt
            );

    /// Returns TRUE if a flag with the passed in name was registered.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isFlagRegistered(
            const char *const   name
            );

    /// Sets a log flag to the specified value. The flag is specified by name.
    /// Must be called for all flags before starting the log.
    ///
    /// @param[in]  name
    ///     Name of the flag to update
    /// @param[in]  flagsDirectory
    ///     Value the flag will be updated to
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @returns
    ///     The value the flag used to have before
    static int setFlag(
            const char *const                         name,
            const int                                 value
            );

    /// Registers a new log flag. You should not call this function but use the API_RLOG_DECLARE
    /// macro.
    ///
    /// @param[in]  flag
    ///     Reference to the logging flag variable.
    /// @param[in]  prefix
    ///     Prefix string for log lines that correspond to this flag.
    /// @param[in]  name
    ///     Name of the log flag.
    /// @param[in]  description
    ///     Description of the log flag.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Value of the log flag. 0 when disabled, 1 when the log flag was found in
    ///     "octane_log_flags.txt".
    static int __registerLogFlag(
            int &                                     flag,
            const char *                              prefix,
            const char *                              name,
            const char *                              description
            );

    /// You should not call this function directly. Use the API_RLOG macro instead.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void __logFmtPrefix(
            const char *                              prefix,
            const char *                              fmt
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
