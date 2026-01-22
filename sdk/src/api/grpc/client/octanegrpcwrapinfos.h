// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef OCTANE_WRAP_MODULE_NODE_GRAPH_H
#define OCTANE_WRAP_MODULE_NODE_GRAPH_H 1


#include "octaneinfos.h"



namespace OctaneWrap
{
    //----------------------------------------------------------------------------------------------
    /// Sets up an ApiNodePinInfo that can be used to define input and output linkers of module node
    /// graphs.
    struct NodePinInfo : public Octane::ApiNodePinInfo
    {
        NodePinInfo(
            const Octane::NodePinType type,
            const char *const         name,
            const Octane::NodeType    defaultNodeType = Octane::NT_UNKNOWN,
            const char *const         description = nullptr,
            const char *const         groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType              type,
            const char* const                      name,
            const Octane::ApiBitMaskPinInfo* const bitMaskInfo,
            const Octane::NodeType                 defaultNodeType = Octane::NT_UNKNOWN,
            const char* const                      description = nullptr,
            const char* const                      groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType           type,
            const char *const                   name,
            const Octane::ApiBoolPinInfo *const boolInfo,
            const Octane::NodeType              defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                   description = nullptr,
            const char *const                   groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType           type,
            const char* const                   name,
            const Octane::ApiEnumPinInfo *const enumInfo,
            const Octane::NodeType              defaultNodeType = Octane::NT_UNKNOWN,
            const char* const                   description = nullptr,
            const char* const                   groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType            type,
            const char *const                    name,
            const Octane::ApiFloatPinInfo *const floatInfo,
            const Octane::NodeType               defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                    description = nullptr,
            const char *const                    groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType          type,
            const char *const                  name,
            const Octane::ApiIntPinInfo *const intInfo,
            const Octane::NodeType             defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                   description = nullptr,
            const char *const                   groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType           type,
            const char *const                   name,
            const Octane::ApiOcioColorSpacePinInfo *ocioColorSpaceInfo,
            const Octane::NodeType              defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                   description = nullptr,
            const char *const                   groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType           type,
            const char *const                   name,
            const Octane::ApiOcioLookPinInfo *  ocioLookInfo,
            const Octane::NodeType              defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                   description = nullptr,
            const char *const                   groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType           type,
            const char *const                   name,
            const Octane::ApiOcioViewPinInfo *  ocioViewInfo,
            const Octane::NodeType              defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                   description = nullptr,
            const char *const                   groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType                 type,
            const char *const                         name,
            const Octane::ApiProjectionPinInfo *const projectionInfo,
            const Octane::NodeType                    defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                         description = nullptr,
            const char *const                         groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType             type,
            const char* const                     name,
            const Octane::ApiStringPinInfo* const stringInfo,
            const Octane::NodeType                defaultNodeType = Octane::NT_UNKNOWN,
            const char* const                     description = nullptr,
            const char* const                     groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType              type,
            const char *const                      name,
            const Octane::ApiTexturePinInfo *const texInfo,
            const Octane::NodeType                 defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                      description = nullptr,
            const char *const                      groupName = nullptr);

        NodePinInfo(
            const Octane::NodePinType                type,
            const char *const                        name,
            const Octane::ApiTransformPinInfo *const transformInfo,
            const Octane::NodeType                   defaultNodeType = Octane::NT_UNKNOWN,
            const char *const                        description = nullptr,
            const char *const                        groupName = nullptr);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiBitMaskPinInfo used for pins of type PT_BIT_MASK.


    /// Initializes an Octane::ApiBitMaskPinInfo.
    struct BitMaskPinInfo : public Octane::ApiBitMaskPinInfo
    {
        typedef ApiBitMaskPinInfo::Label LabelT;

        /// Creates info for PT_BIT_MASK.
        ///
        /// @param[in]  bitLabels
        ///     An array of ApiBitMaskPinInfo::Label structures. The caller stays owner of the array
        ///     and the array needs to stay valid until this instance is destroyed.
        /// @param[in]  bitLabelCount
        ///     The size of the labels array.
        /// @param[in]  defaultValue
        ///     The default bit mask value.
        BitMaskPinInfo(
            const LabelT* bitLabels,
            const size_t  bitLabelCount,
            const int32_t defaultValue);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiBoolPinInfo used for pins of type PT_BOOL.


    /// Initializes an Octane::ApiBoolPinInfo.
    struct BoolPinInfo : public Octane::ApiBoolPinInfo
    {
        explicit BoolPinInfo(
            const bool defaultValue);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiEnumPinInfo used for pins of type PT_ENUM.


    /// Initializes an Octane::ApiEnumPinInfo.
    struct EnumPinInfo : public Octane::ApiEnumPinInfo
    {
        typedef ApiEnumPinInfo::Value ValueT;

        /// Constructor that initializes the data members.
        ///
        /// @param[in]  enumValues
        ///     An array of ApiEnumPinInfo::Value structures. The caller stays owner of the array
        ///     and the array needs to stay valid until this instance is destroyed.
        /// @param[in]  enumValueCount
        ///     The size of the enum value array.
        /// @param[in]  defaultValue
        ///     The default value, must be a value of value array.
        EnumPinInfo(
            const ValueT * enumValues,
            const size_t   enumValueCount,
            const int32_t  defaultValue);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initializes an Octane::ApiFloatPinInfo used for pins of type PT_FLOAT.


    /// Base class for all initializers for Octane::ApiFloatPinInfo.
    struct FloatPinInfoBase : public Octane::ApiFloatPinInfo
    {
        enum Options
        {
            /// Useful to increase readability.
            NO_OPTIONS          = 0,
            /// Allows the UI to display the node slider using a logarithmic scale.
            ALLOW_LOG           = (1 << 0),
            /// If ALLOW_LOG is set, the UI will choose the logarithmic scale as default.
            DEFAULT_IS_LOG      = (1 << 1),
            /// If USE_ASPECT_RATIO is set, the UI should offer an option to easily change all
            /// components by the same ratio.
            USE_ASPECT_RATIO    = (1 << 2),
            /// If DISPLAY_PERCENTAGE is set, the UI will display percentages in the node stack.
            DISPLAY_PERCENTAGES = (1 << 3),
            /// If ALWAYS_DISPLAY_SIGN is set, the UI will display a "+" sign for positive values.
            ALWAYS_DISPLAY_SIGN = (1 << 4),
        };

        /// Initializes most of the members (except mDimInfos) - used by the child classes.
        FloatPinInfoBase(
            const uint8_t dimCount,
            const DataT   &defaultValues,
            const bool    useSliders,
            const int     options);

        /// Returns TRUE if the UI should display sliders for these min/max settings.
        static bool useSliders(
            const float minValue,
            const float maxValue,
            const float sliderMinValue,
            const float sliderMaxValue);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 1D float pin.
    struct FloatPinInfo : public FloatPinInfoBase
    {
        FloatPinInfo(
            const float defaultValue,
            const float minValue = -std::numeric_limits<float>::max(),
            const float maxValue =  std::numeric_limits<float>::max(),
            const int   options = NO_OPTIONS,
            const float sliderMinValue = -std::numeric_limits<float>::max(),
            const float sliderMaxValue =  std::numeric_limits<float>::max(),
            const float sliderStep = 0.001f);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 2D float pin.
    struct FloatXyPinInfo : public FloatPinInfoBase
    {
        FloatXyPinInfo(
            const float defaultX,
            const float defaultY,
            const float minValue = -std::numeric_limits<float>::max(),
            const float maxValue =  std::numeric_limits<float>::max(),
            const int   options = NO_OPTIONS,
            const float sliderMinValue = -std::numeric_limits<float>::max(),
            const float sliderMaxValue =  std::numeric_limits<float>::max(),
            const float sliderStep = 0.001f);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 3D float pin.
    struct FloatXyzPinInfo : public FloatPinInfoBase
    {
        FloatXyzPinInfo(
            const float defaultX,
            const float defaultY,
            const float defaultZ,
            const float minValue = -std::numeric_limits<float>::max(),
            const float maxValue =  std::numeric_limits<float>::max(),
            const int   options = NO_OPTIONS,
            const float sliderMinValue = -std::numeric_limits<float>::max(),
            const float sliderMaxValue =  std::numeric_limits<float>::max(),
            const float sliderStep = 0.001f);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 3D rotation float pin.
    struct FloatRotPinInfo : public FloatPinInfoBase
    {
        FloatRotPinInfo(
            const float defaultX,
            const float defaultY,
            const float defaultZ,
            const float sliderStep = 0.1f);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a color float pin.
    struct FloatRgbPinInfo : public FloatPinInfoBase
    {
        FloatRgbPinInfo(
            const float defaultR,
            const float defaultG,
            const float defaultB,
            const float sliderStep = 0.001f);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiIntPinInfo used for pins of type PT_INT.


    /// Base class for all initializers for Octane::ApiIntPinInfo.
    struct IntPinInfoBase : public Octane::ApiIntPinInfo
    {
        enum Options
        {
            /// Useful to increase readability.
            NO_OPTIONS          = 0,
            /// Allows the UI to display the node slider using a logarithmic scale.
            ALLOW_LOG           = (1 << 0),
            /// If ALLOW_LOG is set, the UI will choose the logarithmic scale as default.
            DEFAULT_IS_LOG      = (1 << 1),
            /// If DISABLE_SLIDER is set, the UI will show a numeric box without slider.
            DISABLE_SLIDER      = (1 << 2),
            // Note: Skipping (1 << 3) to keep shared options consistent with FloatPinInfo.
            /// If ALWAYS_DISPLAY_SIGN is set, the UI will display a "+" sign for positive values.
            ALWAYS_DISPLAY_SIGN = (1 << 4),
        };

        /// Initializes most of the members (except mDimInfos) - used by the child classes.
        IntPinInfoBase(
            const uint8_t dimCount,
            const DataT   &defaultValues,
            const bool    useSliders,
            const int     options);

        /// Sets the ranges for all dimensions.
        void setRange(
            const int32_t minValue = std::numeric_limits<int32_t>::min(),
            const int32_t maxValue = std::numeric_limits<int32_t>::max(),
            const int32_t sliderMinValue = std::numeric_limits<int32_t>::min(),
            const int32_t sliderMaxValue = std::numeric_limits<int32_t>::max());

        /// Returns TRUE if the UI should display sliders for these min/max settings.
        static bool useSliders(
            const int32_t minValue,
            const int32_t maxValue,
            const int32_t sliderMinValue,
            const int32_t sliderMaxValue);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 1D integer pin.
    struct IntPinInfo : public IntPinInfoBase
    {
        IntPinInfo(
            const int32_t defaultValue,
            const int32_t minValue = std::numeric_limits<int32_t>::min(),
            const int32_t maxValue = std::numeric_limits<int32_t>::max(),
            const int     options = NO_OPTIONS,
            const int32_t sliderMinValue = std::numeric_limits<int32_t>::min(),
            const int32_t sliderMaxValue = std::numeric_limits<int32_t>::max(),
            const int32_t sliderStep = 1);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 2D integer pin.
    struct IntXyPinInfo : public IntPinInfoBase
    {
        IntXyPinInfo(
            const int32_t defaultX,
            const int32_t defaultY,
            const int32_t minValue = std::numeric_limits<int32_t>::min(),
            const int32_t maxValue = std::numeric_limits<int32_t>::max(),
            const int     options = NO_OPTIONS,
            const int32_t sliderMinValue = std::numeric_limits<int32_t>::min(),
            const int32_t sliderMaxValue = std::numeric_limits<int32_t>::max(),
            const int32_t sliderStep = 1);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 3D integer pin.
    struct IntXyzPinInfo : public IntPinInfoBase
    {
        IntXyzPinInfo(
            const int32_t defaultX,
            const int32_t defaultY,
            const int32_t defaultZ,
            const int32_t minValue = std::numeric_limits<int32_t>::min(),
            const int32_t maxValue = std::numeric_limits<int32_t>::max(),
            const int     options = NO_OPTIONS,
            const int32_t sliderMinValue = std::numeric_limits<int32_t>::min(),
            const int32_t sliderMaxValue = std::numeric_limits<int32_t>::max(),
            const int32_t sliderStep = 1);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 2D resolution pin.
    struct IntSizeXyPinInfo : public IntPinInfoBase
    {
        IntSizeXyPinInfo(
            const int32_t defaultX,
            const int32_t defaultY,
            const int32_t minValue = 0,
            const int32_t maxValue = std::numeric_limits<int32_t>::max(),
            const int     options = NO_OPTIONS,
            const int32_t sliderMinValue = 0,
            const int32_t sliderMaxValue = std::numeric_limits<int32_t>::max(),
            const int32_t sliderStep = 1);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a 3D resolution pin.
    struct IntSizeXyzPinInfo : public IntPinInfoBase
    {
        IntSizeXyzPinInfo(
            const int32_t defaultX,
            const int32_t defaultY,
            const int32_t defaultZ,
            const int32_t minValue = 0,
            const int32_t maxValue = std::numeric_limits<int32_t>::max(),
            const int     options = NO_OPTIONS,
            const int32_t sliderMinValue = 0,
            const int32_t sliderMaxValue = std::numeric_limits<int32_t>::max(),
            const int32_t sliderStep = 1);
    };


    /// Initializes the Octane::ApiFloatPinInfo for a integer color pin.
    struct IntRgbPinInfo : public IntPinInfoBase
    {
        IntRgbPinInfo(
            const uint8_t defaultR,
            const uint8_t defaultG,
            const uint8_t defaultB);
    };


    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiOcioColorSpacePinInfo used for pins of type
    // PT_OCIO_COLOR_SPACE.


    /// Initializes an Octane::ApiOcioColorSpacePinInfo.
    struct OcioColorSpacePinInfo final : public Octane::ApiOcioColorSpacePinInfo
    {
        OcioColorSpacePinInfo(
            Octane::NamedColorSpace defaultColorSpace,
            const char *otherText,
            bool showFileTypeHints,
            bool linearSrgbUsesLegacyGamma);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiOcioLookPinInfo used for pins of type PT_OCIO_LOOK.


    /// Initializes an Octane::ApiOcioLookPinInfo.
    struct OcioLookPinInfo final : public Octane::ApiOcioLookPinInfo
    {
        explicit OcioLookPinInfo(
            bool forView);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiOcioViewPinInfo used for pins of type PT_OCIO_VIEW.


    /// Initializes an Octane::ApiOcioViewPinInfo.
    struct OcioViewPinInfo final : public Octane::ApiOcioViewPinInfo
    {
        OcioViewPinInfo();
    };


    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiProjectionPinInfo used for pins of type PT_PROJECTION.


    /// Initializes an Octane::ApiProjectionPinInfo.
    struct ProjectionPinInfo : public Octane::ApiProjectionPinInfo
    {
        explicit ProjectionPinInfo(
            const bool useImageProjection);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiStringPinInfo used for pins of type PT_STRING.


    /// Initializes an Octane::ApiStringPinInfo.
    struct StringPinInfo : public Octane::ApiStringPinInfo
    {
        enum Options
        {
            /// Useful to increase readability.
            NO_OPTIONS          = 0,
            /// The UI should allow new lines in the string. If not set only a single line is
            /// expected.
            MULTILINE           = 1 << 0,
            /// The value represents a file path or file name.
            /// If FOR_SAVING is not set, then the value should be an existing file.
            FILENAME            = 1 << 1,
            /// The value should be a file name for a new file.
            FOR_SAVING          = 1 << 2,
            /// If values are given, still allow users to enter custom values.
            ALLOW_CUSTOM_VALUE  = 1 << 3,
            /// Update the attribute for every keystroke while typing, rather than waiting until enter
            /// is pressed (single line only) or the text box loses focus. Only relevant if a list of
            /// values is not given.
            UPDATE_WHILE_TYPING = 1 << 4,
        };


        /// Constructs a new StringPinInfo
        ///
        /// @param[in]  defaultValue
        ///     The default value string. The caller stays owner of the string and the string should
        ///     stay valid until this instance is destroyed.
        /// @param[in]  options
        ///     One or more options of the enum.
        explicit StringPinInfo(
            const char *defaultValue = "",
            const int  options = NO_OPTIONS);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiTexturePinInfo used for pins of type PT_TEXTURE.


    /// Base class for all initializers for Octane::ApiTexturePinInfo.
    struct TexturePinInfoBase : public Octane::ApiTexturePinInfo
    {
        enum Options
        {
            /// Useful to increase readability.
            NO_OPTIONS = 0,
            /// Allows the UI to display the node slider using a logarithmic scale.
            ALLOW_LOG = (1 << 0),
            /// If ALLOW_LOG is set, the UI will choose the logarithmic scale as default.
            DEFAULT_IS_LOG = (1 << 1),
            // Note: Skipping (1 << 2) to keep shared options consistent with FloatPinInfo.
            /// If DISPLAY_PERCENTAGE is set, the UI will display percentages in the node stack.
            DISPLAY_PERCENTAGES = (1 << 3),
            /// If ALWAYS_DISPLAY_SIGN is set, the UI will display a "+" sign for positive values.
            ALWAYS_DISPLAY_SIGN = (1 << 4),
        };

        TexturePinInfoBase(
            float           minValue,
            float           maxValue,
            float           sliderMinValue,
            float           sliderMaxValue,
            Octane::float_3 defaultValue,
            bool            usesSpectrum,
            int             options,
            float           defaultOpacity = 1.0f);
    };


    /// Initializes the Octane::ApiTexturePinInfo for a color texture pin.
    struct ColorTexPin : public TexturePinInfoBase
    {
        explicit ColorTexPin(
            const Octane::float_3 defaultRgb,
            const float           defaultA = 1.0f);

        explicit ColorTexPin(
            const float defaultRgb,
            const float defaultA = 1.0f);

        ColorTexPin(
            const float defaultR,
            const float defaultG,
            const float defaultB,
            const float defaultA = 1.0f);
    };


    /// Initializes the Octane::ApiTexturePinInfo for a greyscale texture pin.
    struct FloatTexPin : public TexturePinInfoBase
    {
        explicit FloatTexPin(
            const float defaultValue,
            const bool  clampValue = false,
            const int   options = NO_OPTIONS);

        FloatTexPin(
            const float           defaultValue,
            const Octane::float_2 range,
            const Octane::float_2 sliderRange = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max() },
            const int             options = NO_OPTIONS);
    };



    //----------------------------------------------------------------------------------------------
    // Helpers to initialize an Octane::ApiTransformPinInfo used for pins of type PT_TRANSFORM.


    /// Initializes an Octane::ApiTransformPinInfo.
    struct TransformPinInfo : public Octane::ApiTransformPinInfo
    {
        explicit TransformPinInfo(
            const uint8_t         dimCount = 3,
            const Octane::MatrixF defaultValue = Octane::MatrixF::identity(),
            const bool            isUvwTransform = false);
    };


} // namespace OctaneWrap



#endif // #ifndef OCTANE_WRAP_MODULE_NODE_GRAPH_H
