// Copyright (C) 2025 OTOY NZ Ltd.

// application includes
#include "octanewraputil.h"
// myself
#include "octanewrapinfos.h"

using namespace OctaneWrap;


//--------------------------------------------------------------------------------------------------
// OctaneWrap::NodePinInfo

NodePinInfo::NodePinInfo(
    const Octane::NodePinType type,
    const char                *name,
    const Octane::NodeType    defaultNodeType,
    const char                *description,
    const char                *groupName)
{
    mId = Octane::P_UNKNOWN;
    mType = type;
    mStaticName = name;
    mStaticLabel = nullptr; // TODO
    mDescription = description;
    mGroupName = groupName;
    mPinColor = 0xff808080u;
    mDefaultNodeType = defaultNodeType;
    mIsTypedTexturePin = false;
    mMinVersion = 0;
    mMinVersion = OCTANE_MAX_VERSION;
    mBoolInfo = nullptr;
    mFloatInfo = nullptr;
    mIntInfo = nullptr;
    mEnumInfo = nullptr;
    mProjectionInfo = nullptr;
    mTexInfo = nullptr;
    mTexTypeInfo = nullptr;
    mTransformInfo = nullptr;
    mStringInfo = nullptr;
    mBitMaskInfo = nullptr;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType              type,
    const char* const                      name,
    const Octane::ApiBitMaskPinInfo* const bitMaskInfo,
    const Octane::NodeType                 defaultNodeType,
    const char* const                      description,
    const char* const                      groupName)
:
    NodePinInfo{ type, name, defaultNodeType, description, groupName }
{
    mBitMaskInfo = bitMaskInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType      type,
    const char *                   name,
    const Octane::ApiBoolPinInfo * boolInfo,
    const Octane::NodeType         defaultNodeType,
    const char *                   description,
    const char *                   groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mBoolInfo = boolInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType      type,
    const char *                   name,
    const Octane::ApiEnumPinInfo * enumInfo,
    const Octane::NodeType         defaultNodeType,
    const char *                   description,
    const char *                   groupName)
:
    NodePinInfo{ type, name, defaultNodeType, description, groupName }
{
    mEnumInfo = enumInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType       type,
    const char *                    name,
    const Octane::ApiFloatPinInfo * floatInfo,
    const Octane::NodeType          defaultNodeType,
    const char *                    description,
    const char *                    groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mFloatInfo = floatInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType     type,
    const char *                  name,
    const Octane::ApiIntPinInfo * intInfo,
    const Octane::NodeType        defaultNodeType,
    const char *                  description,
    const char *                  groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mIntInfo = intInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType                type,
    const char *                             name,
    const Octane::ApiOcioColorSpacePinInfo * ocioColorSpaceInfo,
    const Octane::NodeType                   defaultNodeType,
    const char *                             description,
    const char *                             groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mOcioColorSpaceInfo = ocioColorSpaceInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType          type,
    const char *                       name,
    const Octane::ApiOcioLookPinInfo * ocioLookInfo,
    const Octane::NodeType             defaultNodeType,
    const char *                       description,
    const char *                       groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mOcioLookInfo = ocioLookInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType          type,
    const char *                       name,
    const Octane::ApiOcioViewPinInfo * ocioViewInfo,
    const Octane::NodeType             defaultNodeType,
    const char *                       description,
    const char *                       groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mOcioViewInfo = ocioViewInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType                 type,
    const char *const                         name,
    const Octane::ApiProjectionPinInfo *const projectionInfo,
    const Octane::NodeType                    defaultNodeType,
    const char *const                         description,
    const char *const                         groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mProjectionInfo = projectionInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType        type,
    const char *                     name,
    const Octane::ApiStringPinInfo * stringInfo,
    const Octane::NodeType           defaultNodeType,
    const char *                     description,
    const char *                     groupName)
:
    NodePinInfo{ type, name, defaultNodeType, description, groupName }
{
    mStringInfo = stringInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType         type,
    const char *                      name,
    const Octane::ApiTexturePinInfo * texInfo,
    const Octane::NodeType            defaultNodeType,
    const char *                      description,
    const char *                      groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mTexInfo = texInfo;
}


NodePinInfo::NodePinInfo(
    const Octane::NodePinType           type,
    const char *                        name,
    const Octane::ApiTransformPinInfo * transformInfo,
    const Octane::NodeType              defaultNodeType,
    const char *                        description,
    const char *                        groupName)
:
    NodePinInfo{type, name, defaultNodeType, description, groupName}
{
    mTransformInfo = transformInfo;
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::BitMaskPinInfo


BitMaskPinInfo::BitMaskPinInfo(
    const LabelT * bitLabels,
    const size_t   bitLabelCount,
    const int32_t  defaultValue)
{
    mLabels       = bitLabels;
    mLabelCount   = (uint32_t)bitLabelCount;
    mDefaultValue = defaultValue;
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::BoolPinInfo


BoolPinInfo::BoolPinInfo(
    const bool defaultValue)
{
    mDefaultValue = defaultValue;
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::EnumPinInfo


EnumPinInfo::EnumPinInfo(
    const ValueT * enumValues,
    const size_t   enumValueCount,
    const int32_t  defaultValue)
{
    mValues       = enumValues;
    mValueCount   = (uint32_t)enumValueCount;
    mDefaultValue = defaultValue;
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::FloatPinInfoBase


FloatPinInfoBase::FloatPinInfoBase(
    const uint8_t dimCount,
    const DataT   &defaultValues,
    const bool    useSliders,
    const int     options)
{
    // init the base class members.
    mDimCount           = clamp<uint8_t>(dimCount, 0, MAX_DIMS);
    mDefaultValue       = defaultValues;
    mUseSliders         = useSliders;
    mAllowLog           = (options & ALLOW_LOG);
    mDisplayPercentages = (options & DISPLAY_PERCENTAGES);
    mDefaultIsLog       = mAllowLog && (options & DEFAULT_IS_LOG);
    mUseAspectRatio     = (options & USE_ASPECT_RATIO);
    mIsColor            = false;
    mAlwaysDisplaySign  = (options & ALWAYS_DISPLAY_SIGN);

    // clear dimension infos that will not be defined by the child class
    for (uint8_t i=mDimCount; i<MAX_DIMS; ++i)
    {
        mDimInfos[i].mName           = nullptr;
        mDimInfos[i].mMinValue       = 0;
        mDimInfos[i].mMaxValue       = 0;
        mDimInfos[i].mSliderMinValue = 0;
        mDimInfos[i].mSliderMaxValue = 0;
        mDimInfos[i].mSliderStep     = 0.001f;
    }
}


bool FloatPinInfoBase::useSliders(
    const float minValue,
    const float maxValue,
    const float sliderMinValue,
    const float sliderMaxValue)
{
    const float actualSliderMin = std::max(minValue, sliderMinValue);
    const float actualSliderMax = std::min(maxValue, sliderMaxValue);
    return (actualSliderMin < actualSliderMax) &&
           (actualSliderMin > -std::numeric_limits<float>::max()) &&
           (actualSliderMax <  std::numeric_limits<float>::max());
}



//--------------------------------------------------------------------------------------------------
// Initializers for Octane::ApiFloatPinInfo


FloatPinInfo::FloatPinInfo(
    const float defaultValue,
    const float minValue,
    const float maxValue,
    const int   options,
    const float sliderMinValue,
    const float sliderMaxValue,
    const float sliderStep)
:
    FloatPinInfoBase(1,
                     DataT::make(defaultValue),
                     useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue),
                     options)
{
    OCTANE_API_ASSERT(mUseSliders || !mAllowLog,
                      "no logarithmic sliders possible, if sliders are disabled");
    mDimInfos[0].mName           = "";
    mDimInfos[0].mMinValue       = minValue;
    mDimInfos[0].mMaxValue       = maxValue;
    mDimInfos[0].mSliderMinValue = std::max(minValue, sliderMinValue);
    mDimInfos[0].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
    mDimInfos[0].mSliderStep     = sliderStep;
}


FloatXyPinInfo::FloatXyPinInfo(
    const float defaultX,
    const float defaultY,
    const float minValue,
    const float maxValue,
    const int   options,
    const float sliderMinValue,
    const float sliderMaxValue,
    const float sliderStep)
:
    FloatPinInfoBase(2,
                     DataT::make(defaultX, defaultY),
                     useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue),
                     options)
{
    OCTANE_API_ASSERT(mUseSliders || !mAllowLog,
                      "no logarithmic sliders possible, if sliders are disabled");
    mDimInfos[0].mName = "X";
    mDimInfos[1].mName = "Y";
    for (uint8_t i=0; i<2; ++i)
    {
        mDimInfos[i].mMinValue       = minValue;
        mDimInfos[i].mMaxValue       = maxValue;
        mDimInfos[i].mSliderMinValue = std::max(minValue, sliderMinValue);
        mDimInfos[i].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
        mDimInfos[i].mSliderStep     = sliderStep;
    }
}


FloatXyzPinInfo::FloatXyzPinInfo(
    const float defaultX,
    const float defaultY,
    const float defaultZ,
    const float minValue,
    const float maxValue,
    const int   options,
    const float sliderMinValue,
    const float sliderMaxValue,
    const float sliderStep)
:
    FloatPinInfoBase(3,
                     DataT::make(defaultX, defaultY, defaultZ),
                     useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue),
                     options)
{
    OCTANE_API_ASSERT(mUseSliders || !mAllowLog,
                      "no logarithmic sliders possible, if sliders are disabled");

    mDimInfos[0].mName = "X";
    mDimInfos[1].mName = "Y";
    mDimInfos[2].mName = "Z";
    for (uint8_t i=0; i<3; ++i)
    {
        mDimInfos[i].mMinValue       = minValue;
        mDimInfos[i].mMaxValue       = maxValue;
        mDimInfos[i].mSliderMinValue = std::max(minValue, sliderMinValue);
        mDimInfos[i].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
        mDimInfos[i].mSliderStep     = sliderStep;
    }
}


FloatRotPinInfo::FloatRotPinInfo(
    const float defaultX,
    const float defaultY,
    const float defaultZ,
    const float sliderStep)
:
    FloatPinInfoBase(3, DataT::make(defaultX, defaultY, defaultZ), true, 0)
{
        mDimInfos[0].mName = "X";
        mDimInfos[1].mName = "Y";
        mDimInfos[2].mName = "Z";
        for (uint8_t i=0; i<3; ++i)
        {
            mDimInfos[i].mMinValue       = -360;
            mDimInfos[i].mMaxValue       =  360;
            mDimInfos[i].mSliderMinValue = -360;
            mDimInfos[i].mSliderMaxValue =  360;
            mDimInfos[i].mSliderStep     = sliderStep;
        }
}


FloatRgbPinInfo::FloatRgbPinInfo(
    const float defaultR,
    const float defaultG,
    const float defaultB,
    const float sliderStep)
:
    FloatPinInfoBase(3, DataT::make(defaultR, defaultG, defaultB), true, 0)

{
    mIsColor           = true;
    mDimInfos[0].mName = "R";
    mDimInfos[1].mName = "G";
    mDimInfos[2].mName = "B";
    for (uint8_t i=0; i<3; ++i)
    {
        mDimInfos[i].mMinValue       = 0;
        mDimInfos[i].mMaxValue       = 1;
        mDimInfos[i].mSliderMinValue = 0;
        mDimInfos[i].mSliderMaxValue = 1;
        mDimInfos[i].mSliderStep     = sliderStep;
    }
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::IntPinInfoBase


IntPinInfoBase::IntPinInfoBase(
    const uint8_t dimCount,
    const DataT   &defaultValues,
    const bool    useSliders,
    const int     options)
{
    // init base class members
    mDimCount          = clamp<uint8_t>(dimCount, 0, MAX_DIMS);
    mDefaultValue      = defaultValues;
    mUseSliders        = useSliders && !(options & DISABLE_SLIDER);
    mAllowLog          = (options & ALLOW_LOG);
    mDefaultIsLog      = mAllowLog && (options & DEFAULT_IS_LOG);
    mIsColor           = false;
    mAlwaysDisplaySign = (options & ALWAYS_DISPLAY_SIGN);

    // clear dimension infos that will not be defined by the child class
    for (uint8_t i=mDimCount; i<MAX_DIMS; ++i)
    {
        mDimInfos[i].mName           = nullptr;
        mDimInfos[i].mMinValue       = 0;
        mDimInfos[i].mMaxValue       = 0;
        mDimInfos[i].mSliderMinValue = 0;
        mDimInfos[i].mSliderMaxValue = 0;
        mDimInfos[i].mSliderStep     = 1;
    }
}


void IntPinInfoBase::setRange(
    const int32_t minValue,
    const int32_t maxValue,
    const int32_t sliderMinValue,
    const int32_t sliderMaxValue)
{
    for (uint8_t i = 0; i<mDimCount; ++i)
    {
        mDimInfos[i].mMinValue = minValue;
        mDimInfos[i].mMaxValue = maxValue;
        mDimInfos[i].mSliderMinValue = std::max(minValue, sliderMinValue);
        mDimInfos[i].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
    }
    mUseSliders = useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue);
}


bool IntPinInfoBase::useSliders(
    const int32_t minValue,
    const int32_t maxValue,
    const int32_t sliderMinValue,
    const int32_t sliderMaxValue)
{
    const int32_t actualSliderMin = std::max(minValue, sliderMinValue);
    const int32_t actualSliderMax = std::min(maxValue, sliderMaxValue);
    return (actualSliderMin < actualSliderMax) &&
           (actualSliderMin > std::numeric_limits<int32_t>::min()) &&
           (actualSliderMax < std::numeric_limits<int32_t>::max());
}



//--------------------------------------------------------------------------------------------------
// Initializers for Octane::ApiIntPinInfo


IntPinInfo::IntPinInfo(
        const int32_t defaultValue,
        const int32_t minValue,
        const int32_t maxValue,
        const int     options,
        const int32_t sliderMinValue,
        const int32_t sliderMaxValue,
        const int32_t sliderStep)
:
    IntPinInfoBase(1,
                   DataT::make(defaultValue),
                   useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue),
                   options)
{
    OCTANE_API_ASSERT(mUseSliders || !mAllowLog,
                      "No logarithmic sliders possible, if sliders are disabled");

    mDimInfos[0].mName           = "";
    mDimInfos[0].mMinValue       = minValue;
    mDimInfos[0].mMaxValue       = maxValue;
    mDimInfos[0].mSliderMinValue = std::max(minValue, sliderMinValue);
    mDimInfos[0].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
    mDimInfos[0].mSliderStep     = std::max(1, sliderStep);
}


IntXyPinInfo::IntXyPinInfo(
    const int32_t defaultX,
    const int32_t defaultY,
    const int32_t minValue,
    const int32_t maxValue,
    const int     options,
    const int32_t sliderMinValue,
    const int32_t sliderMaxValue,
    const int32_t sliderStep)
:
    IntPinInfoBase(2,
                   DataT::make(defaultX, defaultY),
                   useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue),
                   options)
{
    OCTANE_API_ASSERT(mUseSliders || !mAllowLog,
                      "No logarithmic sliders possible, if sliders are disabled");

    mDimInfos[0].mName = "X";
    mDimInfos[1].mName = "Y";
    for (uint8_t i=0; i<2; ++i)
    {
        mDimInfos[i].mMinValue       = minValue;
        mDimInfos[i].mMaxValue       = maxValue;
        mDimInfos[i].mSliderMinValue = std::max(minValue, sliderMinValue);
        mDimInfos[i].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
        mDimInfos[i].mSliderStep     = std::max(1, sliderStep);
    }
}


IntXyzPinInfo::IntXyzPinInfo(
    const int32_t defaultX,
    const int32_t defaultY,
    const int32_t defaultZ,
    const int32_t minValue,
    const int32_t maxValue,
    const int     options,
    const int32_t sliderMinValue,
    const int32_t sliderMaxValue,
    const int32_t sliderStep)
:
    IntPinInfoBase(3,
                   DataT::make(defaultX, defaultY, defaultZ),
                   useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue),
                   options)
{
    OCTANE_API_ASSERT(mUseSliders || !mAllowLog,
                      "No logarithmic sliders possible, if sliders are disabled");

    mDimInfos[0].mName = "X";
    mDimInfos[1].mName = "Y";
    mDimInfos[2].mName = "Z";
    for (uint8_t i=0; i<3; ++i)
    {
        mDimInfos[i].mMinValue       = minValue;
        mDimInfos[i].mMaxValue       = maxValue;
        mDimInfos[i].mSliderMinValue = std::max(minValue, sliderMinValue);
        mDimInfos[i].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
        mDimInfos[i].mSliderStep     = std::max(1, sliderStep);
    }
}


IntSizeXyPinInfo::IntSizeXyPinInfo(
    const int32_t defaultX,
    const int32_t defaultY,
    const int32_t minValue,
    const int32_t maxValue,
    const int     options,
    const int32_t sliderMinValue,
    const int32_t sliderMaxValue,
    const int32_t sliderStep)
:
    IntPinInfoBase(2,
                   DataT::make(defaultX, defaultY),
                   useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue),
                   options)
{
    OCTANE_API_ASSERT(mUseSliders || !mAllowLog,
                      "No logarithmic sliders possible, if sliders are disabled");

    mDimInfos[0].mName = "Width";
    mDimInfos[1].mName = "Height";
    for (uint8_t i=0; i<2; ++i)
    {
        mDimInfos[i].mMinValue       = minValue;
        mDimInfos[i].mMaxValue       = maxValue;
        mDimInfos[i].mSliderMinValue = std::max(minValue, sliderMinValue);
        mDimInfos[i].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
        mDimInfos[i].mSliderStep     = std::max(1, sliderStep);
    }
}


IntSizeXyzPinInfo::IntSizeXyzPinInfo(
    const int32_t defaultX,
    const int32_t defaultY,
    const int32_t defaultZ,
    const int32_t minValue,
    const int32_t maxValue,
    const int     options,
    const int32_t sliderMinValue,
    const int32_t sliderMaxValue,
    const int32_t sliderStep)
:
    IntPinInfoBase(3,
                   DataT::make(defaultX, defaultY, defaultZ),
                   useSliders(minValue, maxValue, sliderMinValue, sliderMaxValue),
                   options)
{
    OCTANE_API_ASSERT(mUseSliders || !mAllowLog,
                      "No logarithmic sliders possible, if sliders are disabled");

    mDimInfos[0].mName = "X";
    mDimInfos[1].mName = "Y";
    mDimInfos[2].mName = "Z";
    for (uint8_t i=0; i<3; ++i)
    {
        mDimInfos[i].mMinValue       = minValue;
        mDimInfos[i].mMaxValue       = maxValue;
        mDimInfos[i].mSliderMinValue = std::max(minValue, sliderMinValue);
        mDimInfos[i].mSliderMaxValue = std::min(maxValue, sliderMaxValue);
        mDimInfos[i].mSliderStep     = std::max(1, sliderStep);
    }
}


IntRgbPinInfo::IntRgbPinInfo(
    const uint8_t defaultR,
    const uint8_t defaultG,
    const uint8_t defaultB)
:
    IntPinInfoBase(3, DataT::make(defaultR, defaultG, defaultB), true, 0)
{
    mIsColor           = true;
    mDimInfos[0].mName = "R";
    mDimInfos[1].mName = "G";
    mDimInfos[2].mName = "B";
    for (uint8_t i=0; i<3; ++i)
    {
        mDimInfos[i].mMinValue       = 0;
        mDimInfos[i].mMaxValue       = 255;
        mDimInfos[i].mSliderMinValue = 0;
        mDimInfos[i].mSliderMaxValue = 255;
        mDimInfos[i].mSliderStep     = 1;
    }
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::OcioColorSpacePinInfo


OcioColorSpacePinInfo::OcioColorSpacePinInfo(
    const Octane::NamedColorSpace defaultColorSpace,
    const char *const otherText,
    const bool showFileTypeHints,
    const bool linearSrgbUsesLegacyGamma)
{
    mDefaultColorSpace = defaultColorSpace;
    mOtherText = otherText;
    mShowFileTypeHints = showFileTypeHints;
    mLinearSrgbUsesLegacyGamma = linearSrgbUsesLegacyGamma;
}


//--------------------------------------------------------------------------------------------------
// OctaneWrap::OcioLookPinInfo


OcioLookPinInfo::OcioLookPinInfo(
    const bool forView)
{
    mForView = forView;
}


//--------------------------------------------------------------------------------------------------
// OctaneWrap::OcioViewPinInfo


OcioViewPinInfo::OcioViewPinInfo()
{
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::ProjectionPinInfo


ProjectionPinInfo::ProjectionPinInfo(
    const bool useImageProjection)
{
    mUseImageProjection = useImageProjection;
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::StringPinInfo


StringPinInfo::StringPinInfo(
    const char * defaultValue,
    const int    options)
{
    mDefaultValue      = defaultValue;
    mFilePatterns      = "*";
    mIsFile            = (options & StringPinInfo::FILENAME);
    mForSaving         = mIsFile && (options & StringPinInfo::FOR_SAVING);
    mMultiLine         = (options & StringPinInfo::MULTILINE);
    mUpdateWhileTyping = (options & StringPinInfo::UPDATE_WHILE_TYPING);
    mValues            = nullptr;
    mValueCount        = 0;
}


//--------------------------------------------------------------------------------------------------
// OctaneWrap::TexturePinInfoBase


TexturePinInfoBase::TexturePinInfoBase(
    const float           minValue,
    const float           maxValue,
    const float           sliderMinValue,
    const float           sliderMaxValue,
    const Octane::float_3 defaultValue,
    const bool            usesSpectrum,
    const int             options,
    const float           defaultOpacity)
{
    // init base class members.
    mMinValue           = minValue;
    mMaxValue           = maxValue;
    mSliderMinValue     = sliderMinValue;
    mSliderMaxValue     = sliderMaxValue;
    mDefaultValue.xyz() = defaultValue;
    mDefaultValue.w     = defaultOpacity;
    mUsesSpectrum       = usesSpectrum;
    mAllowLog           = (options & ALLOW_LOG);
    mDefaultIsLog       = mAllowLog && (options & DEFAULT_IS_LOG);
    mDisplayPercentages = (options & DISPLAY_PERCENTAGES);
    mAlwaysDisplaySign  = (options & ALWAYS_DISPLAY_SIGN);
}



//--------------------------------------------------------------------------------------------------
// Initializers for Octane::ApiTexturePinInfo


ColorTexPin::ColorTexPin(
    const Octane::float_3 defaultRgb,
    const float           defaultA)
:
    TexturePinInfoBase(
        std::numeric_limits<float>::lowest(),
        std::numeric_limits<float>::max(),
        0.0f,
        1.0f,
        defaultRgb,
        true,
        NO_OPTIONS,
        defaultA)
{
}


ColorTexPin::ColorTexPin(
    const float defaultRgb,
    const float defaultA)
:
    ColorTexPin(Octane::float_3::make(defaultRgb, defaultRgb, defaultRgb), defaultA)
{
}


ColorTexPin::ColorTexPin(
    const float defaultR,
    const float defaultG,
    const float defaultB,
    const float defaultA)
:
    ColorTexPin(Octane::float_3::make(defaultR, defaultG, defaultB), defaultA)
{
}


FloatTexPin::FloatTexPin(
    const float defaultValue,
    const bool  clampValue,
    const int   options)
:
    TexturePinInfoBase(
        clampValue ? 0.0f : std::numeric_limits<float>::lowest(),
        clampValue ? 1.0f : std::numeric_limits<float>::max(),
        0.0f,
        1.0f,
        Octane::float_3::make(defaultValue, defaultValue, defaultValue),
        false,
        options)
{
}


FloatTexPin::FloatTexPin(
    const float           defaultValue,
    const Octane::float_2 range,
    const Octane::float_2 sliderRange,
    const int             options)
:
    TexturePinInfoBase(
        range.x,
        range.y,
        std::max(sliderRange.x, range.x),
        std::min(sliderRange.y, range.y),
        Octane::float_3::make(defaultValue, defaultValue, defaultValue),
        false,
        options,
        defaultValue)
{
}



//--------------------------------------------------------------------------------------------------
// OctaneWrap::TransformPinInfo


TransformPinInfo::TransformPinInfo(
    const uint8_t         dimCount,
    const Octane::MatrixF defaultValue,
    const bool            isUvwTransform)
{
    static const Bounds cDefScaleBounds = { 1 , 0.001 , 1000 };
    static const Bounds cDefRotBounds   = { 0 , -360  , 360  };
    static const Bounds cDefTransBounds = { 0 , -1000 , 1000 };

    OCTANE_API_ASSERT(dimCount == 2 || dimCount == 3, "Octane only support 2D and 3D transforms.");
    mDimCount          = dimCount;
    mScaleBounds       = cDefScaleBounds;
    mRotationBounds    = cDefRotBounds;
    mTranslationBounds = cDefTransBounds;
    mDefaultValue      = defaultValue;
    mIsUvwTransform    = isUvwTransform;
}
