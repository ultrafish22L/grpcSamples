// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#include "octanetime.h"

namespace Octane
{

/// Settings for saving bounding box data into the orbx package to be used with a reference graph.
/// The main use case for these bounding boxes is to display geometry bounds in the host application
/// viewport or in the octane viewport when the reference graph is unloaded. 
/// See ApiReferenceGraph and the attributes of GT_REFERENCE node graph.
struct OCTANEAPI_DECL ReferencePackageExportSettings
{
    static const bool  DEFAULT_MERGE_SCATTER_INSTANCES = false;
    static const float DEFAULT_INCLUDE_INSTANCE_PERCENTAGE; // = 100.0f
    static const float DEFAULT_IGNORE_SMALL_OBJECT_PERCENTAGE; // = 1.0f
    static const bool  DEFAULT_EXPORT_ANIMATION = true;
    static const float DEFAULT_ANIMATION_FRAMERATE; // = 10.0f
    static const bool  DEFAULT_ENABLE_CUSTOM_ANIMATION_TIMESPAN = false;
    static const TimeSpanT DEFAULT_CUSTOM_ANIMATION_TIMESPAN; // = TimeSpan::make(0, 0)
    static const bool  DEFAULT_EXPORT_CHILD_REFERENCE_GRAPHS = false;

    /// all instances inside scatter nodes will be merged into a combined 
    /// bounding box.
    bool mMergeScatterInstances;

    /// The percentage of the instances to be included into
    /// the package bounding box data. E.g. 25 means 1 out of 4
    /// instances will be included.
    /// The valid range is 0..100.
    float mIncludeInstancePercentage;

    /// If the size of the object bounds related to the scene size is smaller than this percentage
    /// it will be skipped.
    float mIgnoreSmallObjectPercentage;

    /// When set to true, the exported bounds will be animated.
    bool mExportAnimation;

    /// The framerate of the bounds animation.
    /// The valid range is 1..30.
    float mAnimationFramerate;

    /// When set to true, the bounds animation will be sampled within the custom time range
    /// specified by mCustomAnimationTimespan field.
    /// If false, the whole scene animation time span will be exported.
    bool mEnableCustomAnimationTimespan;

    /// The value of the custom animation start and end time to use when
    /// mEnableCustomAnimationTimespan is set to true.
    TimeSpanT mCustomAnimationTimespan;

    /// If true, the child reference graphs bounds will be exported
    bool mExportNestedReferenceGraphs;

    /// Default constructor
    ReferencePackageExportSettings();
};

}
