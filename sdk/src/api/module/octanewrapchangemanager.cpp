// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "octanewrapchangemanager.h"

using namespace OctaneWrap;


//--------------------------------------------------------------------------------------------------
// Implementation of NodeItemObserver.

static void internalOnChange(
    const Octane::ApiChangeManager::ChangeEvent &event,
    void                                        *privateData)
{
    static_cast<NodeItemObserver*>(privateData)->onNodeItemChange(event);    
}


NodeItemObserver::NodeItemObserver()
{
    mCallback = internalOnChange;
    mUserData = this;
}



//--------------------------------------------------------------------------------------------------
// Implementation of TimeObserver.

static void internalOnTimeChange(
    const Octane::ApiChangeManager::TimeEvent &event,
    void                                      *privateData)
{
    static_cast<TimeObserver*>(privateData)->onTimeChanged(event);
}


TimeObserver::TimeObserver()
{
    mCallback = internalOnTimeChange;
    mUserData = this;
}
