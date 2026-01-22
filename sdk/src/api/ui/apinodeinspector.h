// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef __APINODEINSPECTOR_H__
#define __APINODEINSPECTOR_H__

// library includes
#include "apiguicomponent.h"
#include "apinodesystem.h"


namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Node inspector that can be used from the API
class OCTANEAPI_DECL ApiNodeInspector : public Octane::ApiGuiComponent
{
    
public:

    void destroy();

    static ApiNodeInspector* create();

private:

    /// Creates a node inspector
    ApiNodeInspector();
};

}

#endif
