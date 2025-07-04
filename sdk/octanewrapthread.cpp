// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanewrapthread.h"

using namespace OctaneWrap;


Thread::Thread(
    const std::string &name)
:
    mApiThread(NULL)
{
    mApiThread = Octane::ApiThread::create(name.c_str(), internalThreadRunFunction, this);
}


Thread::~Thread()
{
    if (isThreadRunning())
    {
        stopThread(-1);
    }

    mApiThread->destroy();
}


void Thread::startThread()
{
    mApiThread->startThread();
}


bool Thread::stopThread(
    const int timeOutMilliseconds)
{
    return mApiThread->stopThread(timeOutMilliseconds);
}


bool Thread::isThreadRunning() const
{
    return mApiThread->isThreadRunning();
}


void Thread::signalThreadShouldExit()
{
    mApiThread->signalThreadShouldExit();
}


bool Thread::threadShouldExit() const
{
    return mApiThread->threadShouldExit();
}


bool Thread::waitForThreadToExit(
    const int timeOutMilliseconds) const
{
    return mApiThread->waitForThreadToExit(timeOutMilliseconds);
}


void Thread::sleep(
    const int milliseconds)
{
    Octane::ApiThread::sleep(milliseconds);
}


void Thread::yield()
{
    Octane::ApiThread::yield();
}


bool Thread::wait(
    const int timeOutMilliseconds) const
{
    return mApiThread->wait(timeOutMilliseconds);
}


void Thread::notify() const
{
    mApiThread->notify();
}


void* Thread::callFunctionOnMessageThread(   
    Octane::ApiThread::MainThreadCallT functionToCall,
    void                               *privateData)
{
    return mApiThread->callFunctionOnMessageThread(functionToCall, privateData);
}


void Thread::internalThreadRunFunction(
    void *privateData)
{
    static_cast<Thread*>(privateData)->run();
}


bool Thread::isThisTheMessageThread()
{
    return Octane::ApiThread::isThisTheMessageThread();
}
