// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_LOCK_H_
#define _API_LOCK_H_    1

#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Provides mutual exclusion.
class OCTANEAPI_DECL ApiLock
{
    OCTANEAPI_NO_COPY(ApiLock);

public:

    /// Creates a new lock. Should be destroyed via destroy().
    static ApiLock* create();

    /// Destroys this lock.
    void destroy();

    /// Acquires the lock. If the lock is already held by the caller thread, the method returns
    /// immediately. If the lock is currently held by another thread, this will wait until it
    /// becomes free.
    void enter() const;

    /// Attempts to lock this critical section without blocking.  This method behaves identically
    /// to CriticalSection::enter, except that the caller thread does not wait if the lock is
    /// currently held by another thread but returns false immediately.
    ///
    /// @return
    ///     FALSE if the lock is currently held by another thread, TRUE otherwise.
    bool tryEnter() const;

    /// Releases the lock. If the caller thread hasn't got the lock, this can have unpredictable
    /// results. If the enter() method has been called multiple times by the thread, each call
    /// must be matched by a call to exit() before other threads will be allowed to take over the
    /// lock.
    void exit() const;

private:

    ApiLock();
};

} // namespace Octane


#endif // #ifndef _API_LOCK_H_
