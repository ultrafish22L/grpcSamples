// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_PROJECT_MANAGER_H_
#define _OCTANE_WRAP_PROJECT_MANAGER_H_ 1
// system
#include <functional>
// application
#include "apiprojectmanager.h"
#include "apiprojectmanagerclient.h"
#include "grpcchangeevents.h"

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Interface for observers of the project manager
struct ProjectManagerObserver : public GRPCProjectManagerObserver
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
