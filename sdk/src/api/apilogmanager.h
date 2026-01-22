// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_LOG_MANAGER_H_
#define _API_LOG_MANAGER_H_ 1

#include "octanetypes.h"


namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Controls Octane's logging system. Plugins can write their own messages to the log or receive
/// messages from the Octane log. Logging is controlled via log flags and a file named
/// "octane_log_flags.txt", to see all the available flags just put "logFlags" into the file.
/// This class is thread-safe.
class OCTANEAPI_DECL ApiLogManager
{
public:

    enum LogMessageType
    {
        LOG_INFO = 0,
        LOG_ERROR = 1,
    };

    /// type for a log message callback
    typedef void (ApiLogCallbackProc)(LogMessageType type, const char *message);

    /// Registers a callback that gets called every time there is a log message. You can use this
    /// mechanism to display the log messages in your own code.
    static bool registerLogCallbackProc(
        ApiLogCallbackProc *proc);

    /// Removes a previously registered log callback.
    static bool unregisterLogCallbackProc(
        ApiLogCallbackProc *proc);

    /// Opens the Octane log into a separate window. There can be only a single log window so
    /// calling this function multiple times when the log window is already open has no effect.
    static void openOctaneLogWindow();

    /// Writes the specified text to the Octane log. A line feed is added automatically.
    static void log(
        const char *text);

    /// Writes the specified text to the Octane log. A line feed is added automatically.
    static void logError(
        const char *errorMsg);

    /// Writes the specified text to the Octane log. A line feed is added automatically.
    /// Takes printf style formatting parameters. WARNING: the formatted string can be
    /// maximum 1000 chars.
    static void logFmt(
        const char *fmt,
        ...);

    /// Writes the specified text to the Octane log. A line feed is added automatically.
    /// Takes printf style formatting parameters. WARNING: the formatted string can be
    /// maximum 1000 chars.
    static void logErrorFmt(
        const char *fmt,
        ...);

    /// Returns TRUE if a flag with the passed in name was registered.
    static bool isFlagRegistered(
        const char *const name);

    /// Sets a log flag to the specified value. The flag is specified by name.
    /// Must be called for all flags before starting the log.
    ///
    /// @param[in]  name
    ///     Name of the flag to update
    /// @param[in]  flagsDirectory
    ///     Value the flag will be updated to
    /// @returns 
    ///     The value the flag used to have before
    static int setFlag(
        const char *const name,
        const int         value);


    //-- PRIVATE PARTS --

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
    /// @return
    ///     Value of the log flag. 0 when disabled, 1 when the log flag was found in
    ///     "octane_log_flags.txt".
    static int __registerLogFlag(
        int        &flag,
        const char *prefix,
        const char *name,
        const char *description);

    /// You should not call this function directly. Use the API_RLOG macro instead.
    static void __logFmtPrefix(
        const char *prefix,
        const char *fmt,
        ...);
};

} // namespace Octane



//--------------------------------------------------------------------------------------------------
/// Shorthand notation macros.

#define API_LOG(fmt, ...)   \
    Octane::ApiLogManager::logFmt(fmt, ##__VA_ARGS__)

#define API_ERROR(fmt, ...) \
    Octane::ApiLogManager::logErrorFmt(fmt, ##__VA_ARGS__)


//--------------------------------------------------------------------------------------------------
/// You can use below macros to define new log flags for your own module/plugin. RLOG flags are
/// always enabled, DLOG flags are only enabled in debug builds (and you should NOT release a
/// plugin/module with these flags enabled).

/// Declares a your new release log flag. You need to use this macro before you can use your own log
/// flags in the code. For example:
///
/// API_RLOG_DECLARE(myLogFlag, "myPrefix", "logs the actions of my module");
///
/// @param[in]  flag
///     Name of the log flag. The name of this log flag must not class with any log flags that
///     are declared elsewhere. If it does, the API will not accept the log flag.
/// @param[in]  prefix
///     String that is used as a prefix for each log line. Only used when prefix logging is enabled
///     in octane_log_flags.txt.
/// @param[in]  description
///     Describes what your log flag does.
#define API_RLOG_DECLARE(flag, prefix, description)                                             \
    const char * __API_RLOG_PREFIX_##flag = prefix;                                             \
    int          __API_RLOG_FLAG_##flag =                                                       \
        Octane::ApiLogManager::__registerLogFlag(__API_RLOG_FLAG_##flag, #prefix, #flag, description);

/// Use to use a release log flag that is declared in a different compilation unit.
#define API_RLOG_USE(flag)                                                                      \
    extern const char * __API_RLOG_PREFIX_##flag;                                               \
    extern int          __API_RLOG_FLAG_##flag;

/// The value of the release log flag.
#define API_RLOG_FLAG(flag)                                                                     \
    ((const int)__API_RLOG_FLAG_##flag)

/// Log some formatted text for the specified release log flag.
#define API_RLOG(flag, fmt, ...)                                                                \
{                                                                                               \
    if (API_RLOG_FLAG(flag))                                                                    \
    {                                                                                           \
        Octane::ApiLogManager::__logFmtPrefix(__API_RLOG_PREFIX_##flag, fmt, ##__VA_ARGS__);    \
    }                                                                                           \
}


#if defined(NDEBUG)

// DLOG flags, they work exactly the same as RLOG flags but are compiled out when the NDEBUG macro
// is defined.

/// 0 in release builds and 1 in debug builds.
# define API_DLOG_ENABLED           0
/// Compiled out in debug builds.
# define API_DLOG_DECLARE(flag, prefix, description)
/// Compiled out in debug builds.
# define API_DLOG_USE(flag)
/// Compiled out in debug builds.
# define API_DLOG_FLAG(flag)        0
/// Compiled out in debug builds.
# define API_DLOG(flag, fmt, ...)

#else // #if defined(NDEBUG)

/// 0 in release builds and 1 in debug builds.
# define API_DLOG_ENABLED    1

/// Declares a your new debug log flag. You need to use this macro before you can use your own log
/// flags in the code. For example:
///
/// API_DLOG_DECLARE(myLogFlag, "myPrefix", "logs the actions of my module");
///
/// @param[in]  flag
///     Name of the log flag. The name of this log flag must not class with any log flags that
///     are declared elsewhere. If it does, the API will not accept the log flag.
/// @param[in]  prefix
///     String that is used as a prefix for each log line. Only used when prefix logging is enabled
///     in octane_log_flags.txt.
/// @param[in]  description
///     Describes what your log flag does.
# define API_DLOG_DECLARE(flag, prefix, description)                                            \
    const char * __API_DLOG_PREFIX_##flag = prefix;                                             \
    int          __API_DLOG_FLAG_##flag =                                                       \
        Octane::ApiLogManager::__registerLogFlag(__API_DLOG_FLAG_##flag, #prefix, #flag, description);

/// Use to use a debug log flag that is declared in a different compilation unit.
# define API_DLOG_USE(flag)                                                                     \
    extern const char * __API_DLOG_PREFIX_##flag;                                               \
    extern int          __API_DLOG_FLAG_##flag;

/// The value of the debug log flag.
# define API_DLOG_FLAG(flag)                                                                    \
    ((const int)__API_DLOG_FLAG_##flag)

/// Log some formatted text.
# define API_DLOG(flag, fmt, ...)                                                               \
    {                                                                                           \
        if (API_DLOG_FLAG(flag))                                                                \
        {                                                                                       \
            Octane::ApiLogManager::__logFmtPrefix(__API_DLOG_PREFIX_##flag, fmt, ##__VA_ARGS__);\
        }                                                                                       \
    }

#endif // #if defined(NDEBUG)


#endif // #ifndef _API_LOG_MANAGER_H_
