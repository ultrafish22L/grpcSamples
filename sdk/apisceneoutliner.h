// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef __APISCENEOUTLINER_H_
#define __APISCENEOUTLINER_H_

// library includes
#include "apiguicomponent.h"

namespace Octane
{

//-------------------------------------------------------------------------------------------------
/// Scene outliner component for use through the API.
class OCTANEAPI_DECL ApiSceneOutliner : public ApiGuiComponent
{
public:

    static ApiSceneOutliner * create();

    void destroy();

private:

    ApiSceneOutliner();
};

}

#endif // #ifndef __APISCENEOUTLINER_H_