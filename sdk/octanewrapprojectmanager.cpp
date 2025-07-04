// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanewrapprojectmanager.h"

using namespace OctaneWrap;


static void internalNewCallback(
    void *privateData)
{
    ProjectManagerObserver *me = static_cast<ProjectManagerObserver*>(privateData);
    me->onProjectNew();
}


ProjectManagerObserver::ProjectManagerObserver()
{
    mOnProjectNew = internalNewCallback;
    mUserData     = this;
}
