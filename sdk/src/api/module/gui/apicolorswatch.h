// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_COLOR_SWATCH_H_
#define _API_COLOR_SWATCH_H_    1

#include "apicolor.h"
#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Color swatch that allows the user to pick a color.
class OCTANEAPI_DECL ApiColorSwatch : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiColorSwatch);

public:

    /// types
    typedef void (*ColorChangedT)(ApiColorSwatch&, void*);

    /// Creates a new color swatch.
    ///
    /// @param[in]  disableGammaCorrection
    ///     TRUE if the colour picker should not apply any gamma correction. The value returned by
    ///     color() will also not be gamma corrected.
    /// @param[in]  changeCallback
    ///     Callback called when the color in the swatch changes.
    /// @param[in]  privateData
    ///     Private data passed back unchanged in the callback.
    /// @return
    ///     Pointer to the new color swatch.
    static ApiColorSwatch* create(
        const bool    disableGammaCorrection,
        ColorChangedT changeCallback,
        void          *privateData);

    /// Destroys this color swatch.
    void destroy();

    /// Set the color displayed in the color swatch.
    void setColor(
        const ApiColorHdr &color);

    /// Returns the color selected in the color swatch.
    ApiColorHdr color() const;

private:

    ApiColorSwatch();
};

} // namespace Octane


#endif // #ifndef _API_COLOR_SWATCH_H_
