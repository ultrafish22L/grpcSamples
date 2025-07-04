// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_TITLE_COMPONENT_H_
#define _OCTANE_WRAP_TITLE_COMPONENT_H_ 1

// system includes
#include <string>
// api includes
#include "octanetypes.h"
#include "octanewrapguicomponent.h"

namespace Octane
{
class ApiTitleComponent;
}

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Wraps ApiTitleComponent
class TitleComponent : public GuiComponent
{
    OCTANEAPI_NO_COPY(TitleComponent);

public:

    /// Create a new title component 
    /// 
    /// @param[in]  text
    ///     Text to appear on the title component.
    TitleComponent(
        const std::string &text);

    /// Destruct this component.
    virtual ~TitleComponent();

private:

    Octane::ApiTitleComponent *mApiTitleComponent;
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_TITLE_COMPONENT_H_
