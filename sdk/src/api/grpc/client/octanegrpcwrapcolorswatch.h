// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_COLOR_SWATCH_H_
#define _OCTANE_WRAP_COLOR_SWATCH_H_    1

// system includes
#include <vector>
// api includes
#include "apicolor.h"
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apicolorswatchclient.h"

namespace Octane
{
    class ApiColorSwatch;
}

namespace OctaneWrap
{
class ColorSwatch;

//--------------------------------------------------------------------------------------------------
/// Interface for listeners of the color swatch.
class ColorSwatchListener
{
public:

    /// Called after the value of the swatch changed.
    virtual void swatchValueChanged(
        OctaneWrap::ColorSwatch &swatch) =0;
};


//--------------------------------------------------------------------------------------------------
/// Convenience wrapper around ApiColorSwatch.
class ColorSwatch : public GuiComponent
{
    OCTANEAPI_NO_COPY(ColorSwatch);

public:

    /// Constructs a new color swatch.
    ///
    /// @param[in]  disableGammaCorrection
    ///     TRUE if the colour picker should not apply any gamma correction. The value returned by
    ///     color() will also not be gamma corrected.
    ColorSwatch(
        const bool disableGammaCorrection);

    /// Destructor.
    virtual ~ColorSwatch();

    /// Adds a listener for color changes.
    void addListener(
        ColorSwatchListener &listener);

    /// Removes an existing listener.
    void removeListener(
        ColorSwatchListener &listener);

    /// Set the color displayed in the color swatch.
    void setColor(
        const Octane::ApiColorHdr &color);

    /// Returns the color selected in the color swatch.
    Octane::ApiColorHdr color() const;

private:

    /// internally wrapped api swatch
    OctaneGRPC::ApiColorSwatchProxy   mApiColorSwatch;
    /// list of listeners for value changes in this color swatch.
    std::vector<ColorSwatchListener*> mListeners;

    /// internal C-style callback
    static void internalChangeCallback(
        OctaneGRPC::ApiColorSwatchProxy    &swatch,
        void                   *privateData);
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_COLOR_SWATCH_H_
