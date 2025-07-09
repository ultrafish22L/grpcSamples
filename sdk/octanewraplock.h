// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_LOCK_H_
#define _OCTANE_WRAP_LOCK_H_    1

#include "apilock.h"
#include "octanetypes.h"

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Wraps ApiLock.
class Lock
{
    OCTANEAPI_NO_COPY(Lock);

public:

    /// Creates a new lock.
    Lock();

    /// Destructor
    ~Lock();

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

    // wrapped lock
    Octane::ApiLock * const mApiLock;
};



//--------------------------------------------------------------------------------------------------
/// Automatically locks and unlocks a mutex object. Use one of these as a local variable to
/// provide RAII-based locking of a mutex.
class ScopedLock
{
    OCTANEAPI_NO_COPY(ScopedLock);

public:

    /// Creates a scoped lock. As soon as it is created, this will acquire the lock, and
    /// when the scoped lock object is deleted, the lock will be released.  Make sure this object
    /// is created and deleted by the same thread, otherwise there are no guarantees what will
    /// happen! Best just to use it as a local stack object, rather than creating one with the
    /// new() operator.
    inline ScopedLock(
        const Lock &lock);

    /// Destructor. The lock will be released when the destructor is called.  Make sure this
    /// object is created and deleted by the same thread, otherwise there are no guarantees
    /// what will happen!
    inline ~ScopedLock();

private:

    /// wrapped lock.
    const Lock &mLock;
};



inline ScopedLock::ScopedLock(
    const Lock &lock)
:
    mLock(lock)
{
    mLock.enter();
}


inline ScopedLock::~ScopedLock()
{
    mLock.exit();
}

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_LOCK_H_
