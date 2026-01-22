// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_IMAGE_COMPONENT_H_
#define _API_IMAGE_COMPONENT_H_ 1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

class ApiImage;

//--------------------------------------------------------------------------------------------------
/// Component that displays an image. The component will have the same size as the image.
class OCTANEAPI_DECL ApiImageComponent : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiImageComponent);

public:

    /// Creates an image component.
    ///
    /// @param[in]  image
    ///     Image to place in the component. The image should stay alive until this image
    ///     component is destroyed.
    /// @return
    ///     Pointer to the newly created image component.
    static ApiImageComponent* create(
        const ApiImage & image);

    /// Destroys this image component.
    void destroy();

    /// Assigns a new image to the component.
    void updateTo(
        const ApiImage & image);

private:

    ApiImageComponent();
};

} // namespace Octane


#endif // #ifndef _API_IMAGE_COMPONENT_H_
