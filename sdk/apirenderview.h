// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef __APIRENDERVIEW_H__
#define __APIRENDERVIEW_H__

#include "apiguicomponent.h"

class SplitPaneComponent;
class WorkPaneComponent;

namespace Octane
{

//--------------------------------------------------------------------------------------------------
class OCTANEAPI_DECL ApiRenderView : public Octane::ApiGuiComponent
{

public:

    void destroy();

    static ApiRenderView* create(
        void *privateData);

private:

    /// Creates a render view component.
    ApiRenderView();
};

}

#endif
