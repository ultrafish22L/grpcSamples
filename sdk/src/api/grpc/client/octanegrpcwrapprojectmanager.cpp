// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapprojectmanager.h"

using namespace OctaneWrap;


static void internalNewCallback(
    void *privateData)
{
    ProjectManagerObserver *me = static_cast<ProjectManagerObserver*>(privateData);
    if (me)
    {
        me->onProjectNew();
    }
}


ProjectManagerObserver::ProjectManagerObserver()
{
    mCallback     = internalNewCallback;
    mUserData     = this;
}
