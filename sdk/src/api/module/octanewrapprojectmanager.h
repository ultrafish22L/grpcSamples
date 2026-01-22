// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_PROJECT_MANAGER_H_
#define _OCTANE_WRAP_PROJECT_MANAGER_H_ 1

#include "apiprojectmanager.h"

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Interface for observers of the project manager
struct ProjectManagerObserver : public Octane::ApiProjectManager::Observer
{
public:

    ///
    ProjectManagerObserver();

    /// Called after a new project is created and before the old project is deleted.
    /// ApiProjectManager functions will reference the new project at this point.
    virtual void onProjectNew() =0;
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_PROJECT_MANAGER_H_
