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
#include "apiinfoclient.h"


#include "apithread.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiThread
class ApiThreadProxy : public GRPCBase
{
public:
    /// Creates a new thread. Creation will not run the thread, use startThread() to do that.
    ///
    /// @param[in]  threadName
    ///     Name of the thread.
    /// @param[in]  runFunction
    ///     Run fuction that is executed when the thread is started.
    /// @param[in]  userData
    ///     Private user data passed unmodified back into the run function.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the thread object. Should be disposed of via a call to destroy.
    static ApiThreadProxy create(
            const char *                              threadName,
            Octane::ApiThread::RunFunctionT           runFunction,
            void *                                    userData
            );

    /// Destroys this thread. Stop the thread BEFORE calling this method.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy(            );

    /// Starts the thread running. This will cause the thread's run() method to be called by a
    /// new thread. If this thread is already running, startThread() won't do anything.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void startThread(            );

    /// Attempts to stop the thread running.
    ///
    /// This method will cause the threadShouldExit() method to return true
    /// and call notify() in case the thread is currently waiting.
    ///
    /// Hopefully the thread will then respond to this by exiting cleanly, and
    /// the stopThread method will wait for a given time-period for this to
    /// happen.
    ///
    /// If the thread is stuck and fails to respond after the time-out, it gets
    /// forcibly killed, which is a very bad thing to happen, as it could still
    /// be holding locks, etc. which are needed by other parts of your program.
    ///
    /// @param[in] timeOutMilliseconds
    ///     The number of milliseconds to wait for the thread to finish before killing it by force.
    ///      A negative value in here will wait forever.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the thread was cleanly stopped before the timeout, or false if it had to be
    ///     killed by force.
    bool stopThread(
            const int                                 timeOutMilliseconds
            );

    /// Returns TRUE if the thread is currently active.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isThreadRunning(            ) const;

    /// Sets a flag to tell the thread it should stop.
    ///
    /// Calling this means that the threadShouldExit() method will then return true.
    /// The thread should be regularly checking this to see whether it should exit.
    ///
    /// If your thread makes use of wait(), you might want to call notify() after calling
    /// this method, to interrupt any waits that might be in progress, and allow it
    /// to reach a point where it can exit.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void signalThreadShouldExit(            );

    /// Checks whether the thread has been told to stop running.
    ///
    /// Threads need to check this regularly, and if it returns true, they should
    /// return from their run() method at the first possible opportunity.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool threadShouldExit(            ) const;

    /// Waits for the thread to stop.
    ///
    ///  This will waits until isThreadRunning() is false or until a timeout expires.
    ///
    ///  @param[in] timeOutMilliseconds
    ///     the time to wait, in milliseconds. If this value is less than zero, it will wait
    ///     forever.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    ///  @return
    ///     TRUE if the thread exits, or FALSE if the timeout expires first.
    bool waitForThreadToExit(
            const int                                 timeOutMilliseconds
            ) const;

    /// This can be called from any thread that needs to pause.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void sleep(
            const int                                 milliseconds
            );

    /// Yields the calling thread's current time-slot.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static void yield(            );

        /// @param[out] status
    ///     Contains the status of the gRPC call
/// @return 
    ///     TRUE if the event has been signalled, FALSE if the timeout expires.
    bool wait(
            const int                                 timeOutMilliseconds
            ) const;

    /// Wakes up the thread. If the thread has called the wait() method, this will wake it up.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void notify(            ) const;

    /// Calls the passed in function in the message thread (also referred to as the main thread).
    /// This function will block until the function was called.
    ///
    /// @param[in]  functionToCall
    ///     Function to call on the mesage thread.
    /// @param[in]  privateData
    ///     Private data passed back into the function call.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Returned void* from the function call.
    static void * callFunctionOnMessageThread(
            Octane::ApiThread::MainThreadCallT        functionToCall,
            void *                                    privateData
            );

    /// Returns TRUE if the caller-thread is the message thread.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isThisTheMessageThread(            );

private:
    static GRPCSettings & getGRPCSettings();
};
