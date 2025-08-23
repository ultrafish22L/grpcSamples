// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapchangemanager.h"

using namespace OctaneWrap;


//--------------------------------------------------------------------------------------------------
// Implementation of NodeItemObserver.

static void internalOnChange(
    const OctaneGRPC::GRPCChangeManagerChangeEvent &event,
    void                               *privateData)
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
    const OctaneGRPC::GRPCChangeManagerTimeChangeEvent &event,
    void                                      *privateData)
{
    static_cast<TimeObserver*>(privateData)->onTimeChanged(event);
}


TimeObserver::TimeObserver()
{
    mCallback = internalOnTimeChange;
    mUserData = this;
}
