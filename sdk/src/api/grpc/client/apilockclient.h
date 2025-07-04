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


#include "apilock.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiLock
class ApiLockProxy : public GRPCBase
{
public:
    /// Creates a new lock. Should be destroyed via destroy().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiLockProxy create(            );

    /// Destroys this lock.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy(            );

    /// Acquires the lock. If the lock is already held by the caller thread, the method returns
    /// immediately. If the lock is currently held by another thread, this will wait until it
    /// becomes free.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void enter(            ) const;

    /// Attempts to lock this critical section without blocking.  This method behaves identically
    /// to CriticalSection::enter, except that the caller thread does not wait if the lock is
    /// currently held by another thread but returns false immediately.
    ///
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     FALSE if the lock is currently held by another thread, TRUE otherwise.
    bool tryEnter(            ) const;

    /// Releases the lock. If the caller thread hasn't got the lock, this can have unpredictable
    /// results. If the enter() method has been called multiple times by the thread, each call
    /// must be matched by a call to exit() before other threads will be allowed to take over the
    /// lock.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void exit(            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
