// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanewraplock.h"

using namespace OctaneWrap;

Lock::Lock()
:
    mApiLock(Octane::ApiLock::create())
{}


Lock::~Lock()
{
    mApiLock->destroy();
}


void Lock::enter() const
{
    mApiLock->enter();
}


bool Lock::tryEnter() const
{
    return mApiLock->tryEnter();
}


void Lock::exit() const
{
    return mApiLock->exit();
}
