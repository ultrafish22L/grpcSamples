// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_CHANGE_MANANGER_H_
#define _OCTANE_WRAP_CHANGE_MANANGER_H_ 1

#include "apichangemanager.h"

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Interface for observers of the node system.
struct NodeItemObserver : public Octane::ApiChangeManager::Observer
{
public:

    NodeItemObserver();

    virtual void onNodeItemChange(
        const Octane::ApiChangeManager::ChangeEvent &event) =0;
};



//--------------------------------------------------------------------------------------------------
/// Interface for time observers.
struct TimeObserver : public Octane::ApiChangeManager::TimeObserver
{
public:

    TimeObserver();

    virtual void onTimeChanged(
        const Octane::ApiChangeManager::TimeEvent &event) =0;
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_CHANGE_MANANGER_H_
