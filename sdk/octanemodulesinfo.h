// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_MODULE_INFOS_H_
#define _OCTANE_MODULE_INFOS_H_


// Octane includes
#include "octaneids.h"
#include "octaneenums.h"
#include "octaneversion.h"

namespace Octane
{

/// Contains static information about a external octane module.
struct ApiOctaneModuleInfo
{
    /// Unique id identifying the module.
    Octane::ModuleIdT  mModuleId;
    /// Type of the module.
    Octane::ModuleType mType;
    /// Maximum number of instances that can be created for this module.
    uint32_t           mMaxInstances;
    /// Version number of the module.
    Octane::VersionT   mVersionNumber;
    /// Short name for this module.
    const char *       mShortName;
    /// Describes what this module is all about.
    const char *       mDescription;
    /// whether this command can be displayed in the menu bar
    bool               mCanDisplayInMenu;
};

}

#endif // #ifndef _OCTANE_MODULE_INFOS_H_
