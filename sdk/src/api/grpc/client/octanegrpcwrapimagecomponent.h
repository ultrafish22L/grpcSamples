// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_IMAGE_COMPONENT_H_
#define _OCTANE_WRAP_IMAGE_COMPONENT_H_ 1

#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apiimagecomponentclient.h"

namespace Octane
{
class ApiImageComponent;
}

namespace OctaneWrap
{
class Image;

//--------------------------------------------------------------------------------------------------
/// Wraps ApiImageComponent
class ImageComponent : public GuiComponent
{
public:

    /// Creates an image component.
    ///
    /// @param[in]  image
    ///     Image to place in the component. The image should stay alive until this image
    ///     component is destroyed.
    ImageComponent(
        Image & image);

    /// Destructs this image component
    virtual ~ImageComponent();

    /// Assigns a new image to the component.
    void updateTo(
        const Image & image);

private:

    ApiImageComponentProxy mApiImageComponent;
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_IMAGE_COMPONENT_H_
