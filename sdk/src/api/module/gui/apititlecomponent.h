// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_TITLE_COMPONENT_H_
#define _API_TITLE_COMPONENT_H_ 1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Gui title, these components should be inserted in the grid to separate logical chunks.
class OCTANEAPI_DECL ApiTitleComponent : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiTitleComponent);

public:

    /// Creates a new title component.
    ///
    /// @param[in]  text
    ///     Text that appears in the title component.
    /// @return
    ///     Returns a pointer to the newly created title component.
    static ApiTitleComponent* create(
        const char *text);

    /// Destroys this title component.
    void destroy();

private:

    ApiTitleComponent();
};

} // namespace Octane


#endif // #ifndef _API_TITLE_COMPONENT_H_
