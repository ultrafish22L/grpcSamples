// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_ANIMATION_TIME_TRANSFORM_H_
#define _API_ANIMATION_TIME_TRANSFORM_H_ 1

#include "octaneenums.h"
#include "octanetime.h"

namespace Octane
{

/// Transforms animation time of the ApiNodeGraph's owned items.
/// Multiple ApiNodeGraphs in the ownership hierarchy can have time transforms.
class OCTANEAPI_DECL ApiAnimationTimeTransform
{
    OCTANEAPI_NO_COPY(ApiAnimationTimeTransform);

public:

    /// Returns the type of this time transform. Can be used to cast it to the actual type.
    AnimationTimeTransformType type() const;

};



/// Time transform that allows offsetting and scaling the animation
class OCTANEAPI_DECL ApiLinearTimeTransform : public ApiAnimationTimeTransform
{
    OCTANEAPI_NO_COPY(ApiLinearTimeTransform);

public:

    /// The delay of the animation start time in seconds
    float delay() const;

    /// The scale of the animation playback speed (default is 1).
    float speedUp() const;

    /// Returns TRUE when custom interval is enabled.
    /// The animation outside this interval will be cut out. 
    bool customIntervalEnabled() const;

    /// Returns interval of the animation that should be played.
    /// It is untransformed local time of the animation in seconds.
    TimeSpanT customInterval() const;

};

}

#endif
