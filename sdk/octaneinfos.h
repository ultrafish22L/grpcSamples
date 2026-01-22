// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

// Octane includes
#include "octaneenums.h"
#include "octaneids.h"
#include "octanematrix.h"
#include "octanevectypes.h"
#include "octaneversion.h"



namespace Octane
{

/// Contains static information about node graphs.
struct ApiNodeGraphInfo
{
    /// The type ID of the node graph.
    NodeGraphType mType;
    /// Description of this graph type. Can be the empty string but it is always a valid pointer.
    const char *  mDescription;
    /// The output type that is created by default.
    NodePinType   mOutType;
    /// The category name that is used to group/sort this graph type.
    ///
    /// If mIsHidden is true, this does not contain any '|' characters. If mIsHidden is false, this
    /// starts with a '|' character, and may contain more '|' characters to separate subcategory
    /// path components.
    ///
    /// Each subcategory path component (or the entire category name if there are no '|' characters)
    /// may include a prefix (that starts and ends with '!') for sorting purposes. This prefix
    /// should be kept for any alphabetical sorting operations, but must be removed using
    /// removeCategorySortPrefix before displaying the string anywhere user-visible.
    const char *  mCategory;
    /// The default name of a graph of this type.
    const char *  mDefaultName;
    /// TRUE if graphs of this type can be inspected or opened.
    bool          mIsInspectable;
    /// TRUE if graphs of this type should be allowed to be created by the API.
    bool          mIsCreatableByApi;
    /// TRUE if graphs of this type should be hidden from users' view, but still
    /// displayed as normal if created by the API.
    bool          mIsHidden;
    /// TRUE if this graph is a scripted graph (which includes built-in scripted graphs).
    bool          mIsScripted;
    /// TRUE if this is a module node graph.
    bool          mIsModule;
    /// TRUE if this node graph is populated when constructed.
    bool          mIsPopulatedAtConstruction;
    /// Number of attributes defined for this node type, including deprecated ones.
    /// Use ApiNode::attrCount() to get a the attribute count of a node.
    uint32_t      mAttributeInfoCount;
};


/// Describes a compatibility mode of something (currently only used for node types).
///
/// As an example, if the functionality of a node type was changed twice, in 2020.1 and 2021.1 (with
/// no change in 2020.2), the node type should have the following three compatibility modes:
/// {
///     // Modes are listed in reverse chronological order. When we next add a new mode (say, in
///     // 2022.2), we'll add the mode here with the name "Latest (2022.2)", rename "Latest
///     // (2021.1)" to "2021.1 compatibility mode" and give it a description, and update the
///     // description of 2020.1 compatibility mode to clarify whether the differences apply in
///     // addition to the differences from 2021.1 compatibility mode (they probably do).
///
///     // The first entry always represents the current Octane behavior, so it isn't really a
///     // "compatibility mode", but it's still listed here. The description of the first entry is
///     // always null, and the name is "Latest (X)" instead of "X compatibility mode".
///     ApiCompatibilityModeInfo{
///         ocsVersion(11, 0, 0, 0),
///         "Latest (2021.1)",
///         nullptr},
///
///     // Each compatibility mode is versioned by when it was introduced and named after the stable
///     // version in which it was introduced.
///     ApiCompatibilityModeInfo{
///         ocsVersion(8, 0, 0, 0),
///         "2020.1 compatibility mode",
///         "Widgets only grunt on Tuesdays."},
///
///     // The last entry represents the oldest compatibility mode, which always has a start version
///     // of zero because it represents the behavior at the dawn of time. The name of this mode can
///     // be a fairly arbitrary choice of version - anything from 1.0 to the stable version
///     // immediately preceding the second-oldest compatibility mode might make the most sense.
///     ApiCompatibilityModeInfo{
///         0,
///         "2019.1 compatibility mode",
///         "Odd-numbered chunks are ignored. This applies in addition to 2020.2 compatibility mode"
///         " behavior."},
/// }
class OCTANEAPI_DECL ApiCompatibilityModeInfo final
{
public:

    /// Creates a compatibility mode.
    ///
    /// @param startVersion
    ///     The first version of Octane that has this behavior, i.e. the version where this
    ///     compatibility mode was added.
    ///
    ///     Example: 11.0.0.0, for a change made in 2021.1 (anything > 10.2.17.0 (2020.2.5 stable)
    ///     and <= 11.0.0.14 (2021.1 stable) could be correct depending on when the behavior
    ///     actually changed during development).
    ///
    ///     Must be <= OCTANE_VERSION.
    /// @param name
    ///     The name of the compatibility mode. This should be in the form "Latest (X)" or "X
    ///     compatibility mode" (or "X compatibility mode (details)" in special cases), where X is
    ///     the first stable version (major or minor) of Octane that has this behavior.
    ///
    ///     Example: "2021.1 compatibility mode", for a change made in 2021.1 stable (regardless of
    ///     where in the XB/RC cycle the change was made).
    ///
    ///     Must not be null. Must point to a string literal that will never be modified or
    ///     deallocated.
    /// @param description
    ///     A brief description of how this behavior differs from the behavior of the current
    ///     version of Octane, or null if there is no difference because this mode represents the
    ///     current version of Octane.
    ///
    ///     When there are multiple compatibility modes the differences will almost always stack;
    ///     each mode should fully describe how it differs from the latest functionality (often by
    ///     mentioning that the differences are in addition to those of the next newer mode). This
    ///     should use present tense (not future or past tense), start with a capital letter and end
    ///     with a full stop, e.g. "Opacity is ignored when a mask is present.".
    ///
    ///     If not null, must point to a string literal that will never be modified or deallocated.
    ApiCompatibilityModeInfo(
        Octane::VersionT startVersion,
        const char * name,
        const char * description);

    /// Gets the first version of Octane that has this behavior, i.e. the version where this
    /// compatibility mode was added.
    ///
    /// @return
    ///     The start version, which will always be less than or equal to OCTANE_VERSION.
    Octane::VersionT startVersion() const;

    /// Gets the name of the compatibility mode.
    ///
    /// @return
    ///     The name, which is not null. The pointer points to a string literal that will never be
    ///     modified or deallocated.
    const char * name() const;

    /// Gets a brief description of how this behavior differs from the behavior of the current
    /// version of Octane.
    ///
    /// @return
    ///     The description, or null if this mode doesn't have a description because it represents
    ///     the current version of Octane. If not null, the pointer points to a string literal that
    ///     will never be modified or deallocated.
    const char * description() const;

private:

    Octane::VersionT mStartVersion;

    const char * mName;

    const char * mDescription;

};


/// A list of compatibility modes associated with something (currently only used for node types).
class OCTANEAPI_DECL ApiCompatibilityModeInfoSet final
{
public:

    /// Creates an empty set of compatibility mode infos.
    ApiCompatibilityModeInfoSet();

    /// Creates a set of compatibility mode infos from an existing array.
    ///
    /// @param infos
    ///     If count is zero, this is meaningless and may be null. If count is not zero, this must
    ///     not be null and must point to a static array that will never be modified or deallocated.
    ///
    ///     Modes must appear in order of strictly decreasing start version, and the last mode (if
    ///     there is one) must have a start version of zero.
    ///
    ///     The first mode (if there is one) represents the behavior of the current version of
    ///     Octane and so must have a null description. All subsequent modes (if there are any) must
    ///     have descriptions describing how their behavior differs from the current version.
    /// @param count
    ///     The number of compatibility modes.
    ApiCompatibilityModeInfoSet(
        const ApiCompatibilityModeInfo * infos,
        uint32_t count);

    /// Gets the number of compatibility modes.
    ///
    /// @return
    ///     The number of modes in this list, which may be zero.
    uint32_t size() const;

    /// Gets the info for one of the compatibility modes.
    ///
    /// @param index
    ///     The index of the mode for which to get the info. Must be less than size().
    /// @return
    ///     The info. Refers to an object that will never be modified or deallocated.
    const ApiCompatibilityModeInfo & info(
        uint32_t index) const;

private:

    const ApiCompatibilityModeInfo * mInfos;
    uint32_t mCount;

};


/// A set of TextureValueType enum options (typically extracted from a uint32_t bit-field).
struct OCTANEAPI_DECL ApiTextureValueTypeSet final
{
    /// Creates a set of texture value types by extracting them from being encoded in a provided 32-wide bit-field.
    ///
    /// @param bitfield
    ///     A 32-wide bit field, encoding texture value types (single bit per TextureValueType enum option).
    ApiTextureValueTypeSet(
        uint32_t bitfield = 0);

    /// Gets the number of texture value types.
    ///
    /// @return
    ///     The number of texture value types, which may be zero.
    uint32_t size() const;

    /// Gets the TextureValueType at a given index (TEXTURE_VALUE_TYPE_UNKNOWN if out of bounds).
    ///
    /// @param index
    ///     The index of a TextureValueType.
    /// @return
    ///     The TextureValueType at a given index (TEXTURE_VALUE_TYPE_UNKNOWN if out of bounds).
    TextureValueType at(
        uint32_t index) const;

    /// Checks if a given TextureValueType is included in the set.
    ///
    /// @param index
    ///     The index of a TextureValueType.
    /// @return
    ///     TRUE if the given TextureValueType is included in the set, FALSE otherwise.
    bool contains(
        TextureValueType textureValueType) const;

    /// Return the bitfield encoding all the texture value types in the set.
    ///
    /// @return
    ///     A 32-wide bit field, encoding texture value types (single bit per TextureValueType enum option).
    uint32_t bitField() const;

private:
    
    uint32_t mBitField;
    uint32_t mCount;
};


/// Static metadata about texture node value types of output and inputs and how they may change dynamically
struct ApiTextureNodeTypeInfo
{
    /// A specific configuration of value types of a texture node's output and texture inputs
    struct Configuration
    {
        /// Holds parameters that control what the texture types of output and inputs are resolved to in the configuration
        struct Parameters
        {
            /// A selected texture value type of the node's output (TEXTURE_VALUE_TYPE_UNKNOWN if unselectable)
            TextureValueType mOutputValueType;
            /// A selected texture value type of the node's main texture inputs (TEXTURE_VALUE_TYPE_UNKNOWN if unselectable)
            TextureValueType mInputValueType;
            /// Whether the node has the texture value types of it's secondary inputs toggled or not
            bool             mIsInputValueTypeToggled;
        };
        
        
        /// Holds the resolved texture value types of the node's output and texture inputs in the configuration
        struct Interface
        {
            /// The resolved texture value type of the node's output
            TextureValueType   mOutputValueType;
            /// The resolved texture value type of each of the node's texture pins
            TextureValueType * mInputValueTypes;
            /// The pin ids of the node's texture pins, corresponding to the input value types
            PinId            * mInputPinIds;
            /// The number of typed texture pins in the texture node
            uint32_t           mInputPinCount;
        };
        
        /// The type of node this configuration is for
        NodeType mNodeType;
        /// The parameters that control what the texture types of output and inputs are resolved to in the configuration
        Parameters mParameters;
        /// The resolved texture value types of the node's output and texture inputs in the configuration
        Interface mInterface;
    };

    /// Find the configuration that the typed texture node would switch to when set to given configuration parameters
    ///
    /// @param [in] configurationParameters
    ///     The texture value type selections the typed texture node would be set to in the desired configuration
    /// @return
    ///     A pointer to the matching node configuration (nullptr if not found)
    OCTANEAPI_DECL const Configuration * findConfiguration(
        const Configuration::Parameters & configurationParameters) const;

    /// Find the configuration that has the given node interface of texture value types of output and inputs
    ///
    /// @param [in]  configurationInterface
    ///     The types of output and inputs a typed texture node would have in the desired configuration
    /// @param [in]  considerAutoTypeConversion
    ///     Whether to consider inputs/output texture value types as equivalent when they can be trivially casted across
    /// @return
    ///     A pointer to the matching node configuration (nullptr if not found)
    OCTANEAPI_DECL const Configuration * findConfiguration(
        const Configuration::Interface & configurationInterface,
        bool                             considerAutoTypeConversion = false) const;
    
    /// Signify if the typed texture node's output type is static, derived from the input type, or can be set directly.
    TextureNodeTypeMode mOutputMode;
    /// Signify if the typed texture node's input type is static, derived from the output type, or can be set directly.
    TextureNodeTypeMode mInputMode;
    /// Signify is the typed texture node's secondary texture inputs value type can be toggled by the node.
    bool mCanToggleValueTypesOfPins;
    /// The texture output's static texture value type, if there is one defined, otherwise TEXTURE_VALUE_TYPE_UNKNOWN
    TextureValueType mStaticOutputValueType;
    /// The texture value types that can be set for the primary input(s)
    ApiTextureValueTypeSet mInputValueTypes;
    /// The texture value types that can be set for the output
    ApiTextureValueTypeSet mOutputValueTypes;
    /// How many distinct configurations the node has for texture inputs and/or output value types
    uint32_t mConfigurationsCount;
    /// The possible configurations the node has for texture inputs and/or output value types
    Configuration * mConfigurations;
};


/// Static metadata about texture pin value types and how they may change dynamically in its typed texture node
struct ApiTexturePinTypeInfo
{
    /// Get the texture value type of a pin for given configuration parameters
    ///
    /// @param[in]  configurationParameters
    ///     The parameters of a specific texture node type configuration
    /// @return
    ///     A texture value type for the pin
    OCTANEAPI_DECL TextureValueType getTextureValueType(
        const ApiTextureNodeTypeInfo::Configuration::Parameters & configurationParameters) const;
    
    /// Signify whether its value type is static or affected by the node's primary input/output.
    TexturePinValueTypeMode mMode;
    /// The static or distinct texture value type of the texture pin, TEXTURE_VALUE_TYPE_UNKNOWN if it has none.
    TextureValueType mValueType;
    /// The texture value type of the texture pin when its node toggles secondary texture input value types.
    /// When set to TEXTURE_VALUE_TYPE_UNKNOWN it means the pin can never have its texture value type toggled.
    TextureValueType mValueTypeWhenToggled;
    /// Whether the texture node the pin belongs to has its input texture value typed derived from its output value type
    bool mNodeInputTypesAreDerivedFromOutputType;
};


/// Contains all static info about a particular node type.
///
/// Static infos don't take the version into account, so for a given node type and
/// index the calls ApiInfo::nodePinInfo(type, index) and ApiNode::pinInfo(index) can return
/// different infos. The latter is the recommended way to query information about what pins
/// are there on a particular node.
struct ApiNodeInfo
{
    /// The type ID of the node.
    NodeType     mType;
    /// Description of this node type. Can be the empty string but it is always a valid pointer.
    const char * mDescription;
    /// The output type, i.e. node pin type this node can be connected to.
    /// If it's PT_UNKNOWN, this node can't be connected to another pin.
    NodePinType  mOutType;
    /// The color of the node (ARGB encoded) - derived from the color of the output type.
    uint32_t     mNodeColor;
    /// TRUE if this is a linker node, which links nodes between nested node graphs.
    bool         mIsLinker;
    /// TRUE if this is an output linker node, otherwise it's either an input linker node (if
    /// mIsLinker is TRUE) or no linker node at all. If mIsLinker is FALSE, mIsOutputLinker can
    /// be ignored.
    bool         mIsOutputLinker;
    /// If set to TRUE the default value can be set in the value attribute.
    bool         mTakesPinDefaultValue;
    /// TRUE if nodes of this type should be hidden from users, but still shown
    /// as normal if created by the API.
    bool         mIsHidden;
    /// TRUE if nodes of this type should be allowed to be created by the API.
    bool         mIsCreatableByApi;
    /// If TRUE, this node wraps a built-in script graph.
    bool         mIsScriptGraphWrapper;
    /// TRUE if the node outputs a texture and has typed texture output and/or inputs, FALSE otherwise
    bool         mIsTypedTextureNode;
    /// The category name that is used to group/sort this node type.
    ///
    /// If mIsHidden is true, this does not contain any '|' characters. If mIsHidden is false, this
    /// starts with a '|' character, and may contain more '|' characters to separate subcategory
    /// path components.
    ///
    /// Each subcategory path component (or the entire category name if there are no '|' characters)
    /// may include a prefix (that starts and ends with '!') for sorting purposes. This prefix
    /// should be kept for any alphabetical sorting operations, but must be removed using
    /// removeCategorySortPrefix before displaying the string anywhere user-visible.
    const char * mCategory;
    /// The default name of a node of this type.
    const char * mDefaultName;
    /// Number of attributes defined for this node type, including deprecated ones.
    /// Use ApiNode::attrCount() to get a the attribute count of a node.
    uint32_t     mAttributeInfoCount;
    /// Number of static pins defined for this node type, including deprecated ones.
    /// Use ApiNode::staticPinCount() to get the number of static pins of a node.
    uint32_t     mPinInfoCount;
    /// ID of the attribute defining the number of (movable) inputs. A value != A_UNKNOWN indicates
    /// that this node has movable inputs and mMovableInputPinCount will be >= 1.
    /// If set to A_UNKNOWN, the node doesn't have any movable inputs and mMovableInputPinCount will
    /// be 0.
    AttributeId  mMovableInputCountAttribute;
    /// The number of dynamic pins per movable input or 0 if the node doesn't have movable inputs.
    uint32_t     mMovableInputPinCount;
    /// The pin structure of each movable input, or MOVABLE_INPUT_FORMAT_NONE if this node doesn't
    /// have movable inputs. Movable inputs can be moved from one node to another if and only if
    /// both nodes have the same movable input format.
    MovableInputFormat mMovableInputFormat;
    /// What each movable input is, e.g. "layer". This is used to build things like tooltips, e.g.
    /// "Delete layer.". Null if the node doesn't have movable inputs.
    const char * mMovableInputName;
    /// Static metadata related to texture nodes with typed inputs and/or output
    const ApiTextureNodeTypeInfo * mTexNodeTypeInfo;
    /// Description of the compatibility modes of the node.
    ApiCompatibilityModeInfoSet mCompatibilityModeInfos;
    /// Version when this node type was introduced. This will be zero for all nodes introduced
    /// before 11.0.0.10.
    VersionT     mMinVersion;
};


/// Contains info about a particular attribute.
struct ApiAttributeInfo
{
    /// The identifier of the attribute.
    AttributeId   mId;
    /// The type of data stored in the attribute.
    AttributeType mType;
    /// TRUE if the attribute stores an array (in which case the default values should be ignored).
    bool          mIsArray;
    /// If this attribute stores a package file name, the corresponding file name attribute ID will
    /// be stored here. Otherwise it will be A_UNKNOWN.
    AttributeId   mFileNameAttribute;
    /// If this attribute stores a file name with package support, the corresponding package
    /// attribute ID will be stored here. Otherwise it will be A_UNKNOWN.
    AttributeId   mPackageAttribute;
    /// Some English description of the attribute.
    const char *  mDescription;
    /// Will contain the default value, if this is an integer/bool attribute.
    int32_4       mDefaultInts;
    /// Will contain the default value, if this is an long attribute.
    int64_2       mDefaultLongs;
    /// Will contain the default value, if this is a float attribute.
    float_4       mDefaultFloats;
    /// Will contain the default value, if this is a string/filename attribute.
    const char *  mDefaultString;
    /// The minimum Octane version that supports this attribute.
    VersionT      mMinVersion;
    /// The Octane version that dropped this attribute.
    VersionT      mEndVersion;

    /// fast version validity check
    inline bool isValidFor(
        const VersionT version = OCTANE_VERSION) const
    {
        return ((version >= mMinVersion) && (version < mEndVersion));
    }
};


/// Stores static information for pins of type PT_BIT_MASK.
struct ApiBitMaskPinInfo
{
    /// Represents a bit index identified by some meaningfull name.
    struct Label 
    {
        /// full name of a bit index.
        const char * mName;
        /// short name of a bit index used in the compact node stack view.
        const char * mShortName;
    };

    /// Array of the bit label (Can be NULL).
    const Label * mLabels;
    /// Number of bit values.
    uint32_t      mLabelCount;
    /// Default bit mask value.
    int32_t       mDefaultValue; 
};


/// Stores static information for pins of type PT_BOOL.
struct ApiBoolPinInfo
{
    bool mDefaultValue;
};


/// Stores static information for pins of type PT_ENUM.
struct ApiEnumPinInfo
{
    /// Special enumeration value for a line separator in the UI.
    static const int32_t SEPARATOR_LINE = 0x80000000;
    /// Special enumeration value for a vertical whitespace separator in the UI.
    static const int32_t SEPARATOR_SPACE = 0x80000001;

    /// Represents an enum value identified by some meaningful name.
    struct Value
    {
        /// Actual enumeration value.
        int32_t      mValue;
        /// Label of the enumeration value.
        const char * mLabel;
    };

    /// Array of the enum values (Can be NULL).
    const Value * mValues;
    /// Number of enum values.
    uint32_t      mValueCount;
    /// Default enum value.
    int32_t       mDefaultValue;
};


/// Stores static information for pins of type PT_FLOAT.
struct ApiFloatPinInfo
{
    /// The basic data type that is used for float pins and their defaults.
    typedef float_4 DataT;

    /// The maximum dimension of the data that can be read through a float pin.
    static const uint32_t MAX_DIMS = DataT::DIM_COUNT;

    /// Describes the properties of one dimension.
    struct DimInfo
    {
        const char * mName;
        float        mMinValue;
        float        mMaxValue;
        float        mSliderMinValue;
        float        mSliderMaxValue;
        float        mSliderStep;
    };

    /// The number of dimensions the pin requires (up to 3).
    uint8_t mDimCount;
    /// The dimension descriptions.
    DimInfo mDimInfos[MAX_DIMS];
    /// The default value of the pin.
    DataT   mDefaultValue;
    /// TRUE if the user interface should use sliders for this pin.
    bool    mUseSliders;
    /// TRUE if the user interface should allow a logarithmic slider interface.
    bool    mAllowLog;
    /// TRUE if the user interface should use a logarithmic slider interface (if possible).
    bool    mDefaultIsLog;
    /// TRUE if the user interface display percentages
    bool    mDisplayPercentages;
    /// TRUE if the user interface should allow changes to all three components which keep the
    /// aspect ratio.
    bool    mUseAspectRatio;
    /// TRUE if a colour swatch should be displayed.
    bool    mIsColor;
    /// TRUE if the user interface should display the sign even for positive values.
    bool    mAlwaysDisplaySign;
};


/// Stores static information for pins of type PT_INT.
struct ApiIntPinInfo 
{
    /// The basic data type that is used for int pins and their defaults.
    typedef int32_4 DataT;

    /// The maximum dimension of the data that can be read through an int pin.
    static const uint32_t MAX_DIMS = DataT::DIM_COUNT;

    /// Describes the properties of one dimension.
    struct DimInfo
    {
        const char * mName;
        int32_t      mMinValue;
        int32_t      mMaxValue;
        int32_t      mSliderMinValue;
        int32_t      mSliderMaxValue;
        int32_t      mSliderStep;
    };

    /// The number of dimensions the pin requires (up to 3).
    uint8_t mDimCount;
    /// The dimension descriptions.
    DimInfo mDimInfos[MAX_DIMS];
    /// Teh default value of the pin.
    DataT   mDefaultValue;
    /// TRUE if the user interface should use sliders for this pin.
    bool    mUseSliders;
    /// TRUE if the user interface should allow a logarithmic slider interface.
    bool    mAllowLog;
    /// TRUE if the user interface should use a logarithmic slider interface (if possible).
    bool    mDefaultIsLog;
    /// TRUE if a colour swatch should be displayed.
    bool    mIsColor;
    /// TRUE if the user interface should display the sign even for positive values.
    bool    mAlwaysDisplaySign;
};


/// Stores static information for pins of type PT_OCIO_COLOR_SPACE.
struct ApiOcioColorSpacePinInfo
{
    /// The default non-OCIO color space, or NAMED_COLOR_SPACE_OTHER. Must not be
    /// NAMED_COLOR_SPACE_OCIO.
    NamedColorSpace mDefaultColorSpace;
    /// The text to show for NAMED_COLOR_SPACE_OTHER, or null to not show that option.
    const char *    mOtherText;
    /// Whether to show text regarding which color spaces are usable for which file types.
    bool            mShowFileTypeHints;
    /// Whether NAMED_COLOR_SPACE_LINEAR_SRGB includes legacy gamma.
    bool            mLinearSrgbUsesLegacyGamma;
};


/// Stores static information for pins of type PT_OCIO_LOOK.
struct ApiOcioLookPinInfo
{
    /// Whether the look will be applied to an OCIO view rather than an OCIO color space. If this is
    /// true an extra "use view look(s)" option will be shown (and be the default).
    bool mForView;
};


/// Stores static information for pins of type PT_OCIO_VIEW.
struct ApiOcioViewPinInfo
{
    // No customization options for this pin type yet.
};


/// Stores static information for pins of type PT_PROJECTION.
struct ApiProjectionPinInfo
{
    /// If TRUE, the projection coordinates are generated in the same way as for 2D image textures.
    /// If FALSE, they do not use the additional transformations applied to image textures.
    bool mUseImageProjection;
};


/// Stores static information for pins of type PT_STRING.
struct ApiStringPinInfo
{
    /// The default text in this node pin
    const char *        mDefaultValue;
    /// if mIsFile is true, this text gives the file name patterns, separated by a semicolon (;)
    const char *        mFilePatterns;
    /// List of values to choose from.
    const char *const * mValues;
    /// Amount of values
    size_t              mValueCount;
    /// if mIsFile is false and mMultiLine is true, this should allow entry of multiple lines of
    /// text.
    bool                mMultiLine;
    /// if true the interface should allow browsing for a file
    bool                mIsFile;
    /// if true the interface should allow browsing for a file which doesn't exist yet.
    bool                mForSaving;
    /// if a list of values is given, determines if users may enter a value which is not in
    /// the list.
    bool                mAllowCustomValue;
    /// If true, update the attribute for every keystroke while typing. If false, wait until enter
    /// is pressed (multiline only) or the text box loses focus. Only relevant if a list of values
    /// is not given.
    bool                mUpdateWhileTyping;
};


/// Stores static information for pins of type PT_TEXTURE.
struct ApiTexturePinInfo
{
    /// The basic data type that is used for texture node values.
    typedef float_4 DataT;

    /// The minimum value the pin accepts.
    float mMinValue;
    /// The maximum value the pin accepts.
    float mMaxValue;
    /// The minimum slider value that should be displayed for texture nodes connected with this pin.
    float mSliderMinValue;
    /// The maximum slider value that should be displayed for texture nodes connected with this pin.
    float mSliderMaxValue;
    /// The default RGB values of the texture pin. 
    /// Float texture pins have all three components set to the same value.
    DataT mDefaultValue;
    /// Set to TRUE if the pin is used to fetch a spectrum.
    /// FALSE if we only need a float texture.
    /// Only makes sense for texture pins of material/emitter/medium nodes.
    bool  mUsesSpectrum;
    /// TRUE if the user interface should allow a logarithmic slider interface.
    bool  mAllowLog;
    /// TRUE if the user interface should use a logarithmic slider interface (if possible).
    bool  mDefaultIsLog;
    /// TRUE if the user interface should display percentages.
    bool  mDisplayPercentages;
    /// TRUE if the user interface should display the sign even for positive values.
    bool  mAlwaysDisplaySign;
};


/// Stores static information for pins of type PT_TRANSFORM.
struct ApiTransformPinInfo
{
    /// Represents transformation value boundaries used for the UI.
    struct Bounds
    {
        double mDefaultValue;
        double mMinValue;
        double mMaxValue;
    };

    /// The default value for this pin
    MatrixF mDefaultValue;
    /// The dimension of the transformation.
    uint8_t mDimCount;
    /// Boundaries for the scale values in the UI.
    Bounds  mScaleBounds;
    /// Boundaries for the rotation values (in degrees) in the UI.
    Bounds  mRotationBounds;
    /// Boundaries for the translation values in the UI.
    Bounds  mTranslationBounds;
    /// Flags this transformation as a UVW transform. Doing so causes the transforms from any
    /// parent `UVW transform` nodes to be premultiplied to this matrix.
    bool    mIsUvwTransform;
};



/// Stores static information of a particular pin.
struct ApiNodePinInfo
{
    /// An ID that is unique for each static pin of a node. Dynamic pins all have id P_UNKNOWN.
    PinId                            mId;
    /// The pin type.
    NodePinType                      mType;
    /// TRUE if the pin-info is for a texture pin with a type info
    bool mIsTypedTexturePin;
    /// The name of this pin, if it's a static pin. For dynamic pins, it will be "".
    const char *                     mStaticName;
    /// The label of this pin, if it's a static pin. For dynamic pins, it will be "".
    const char *                     mStaticLabel;
    /// A description of the pin which can be used for example as tooltip.
    const char *                     mDescription;
    /// Name of the group this pin belongs to. For dynamic pins or pins without a group
    /// this shall be an empty string.
    const char *                     mGroupName;
    /// The color of the pin (ARGB encoded).
    uint32_t                         mPinColor;
    /// The type of the default node that should be used or NT_UNKNOWN if no default should be
    /// created.
    NodeType                         mDefaultNodeType;
    /// The minimum Octane version that supports this pin.
    VersionT                         mMinVersion;
    /// The Octane version that dropped this pin.
    VersionT                         mEndVersion;
    /// Only valid for PT_BOOL, null otherwise.
    const ApiBoolPinInfo *           mBoolInfo;
    /// Only valid for PT_FLOAT, null otherwise.
    const ApiFloatPinInfo *          mFloatInfo;
    /// Only valid for PT_INT, null otherwise.
    const ApiIntPinInfo *            mIntInfo;
    /// Only valid for PT_ENUM, null otherwise.
    const ApiEnumPinInfo *           mEnumInfo;
    /// Only valid for PT_OCIO_COLOR_SPACE, null otherwise.
    const ApiOcioColorSpacePinInfo * mOcioColorSpaceInfo;
    /// Only valid for PT_OCIO_LOOK, null otherwise.
    const ApiOcioLookPinInfo *       mOcioLookInfo;
    /// Only valid for PT_OCIO_VIEW, null otherwise.
    const ApiOcioViewPinInfo *       mOcioViewInfo;
    /// Only valid for PT_PROJECTION, null otherwise.
    const ApiProjectionPinInfo *     mProjectionInfo;
    /// Only valid for PT_TEXTURE, null otherwise.
    const ApiTexturePinInfo *        mTexInfo;
    /// Only valid for PT_TEXTURE carrying type information, null otherwise.
    const ApiTexturePinTypeInfo *    mTexTypeInfo;
    /// Only valid for PT_TRANSFORM, null otherwise.
    const ApiTransformPinInfo *      mTransformInfo;
    /// Only valid for PT_STRING, null otherwise.
    const ApiStringPinInfo *         mStringInfo;
    /// Only valid for PT_BIT_MASK, null otherwise.
    const ApiBitMaskPinInfo *        mBitMaskInfo;


    /// fast version validity check
    inline bool isValidFor(
        const VersionT version = OCTANE_VERSION) const
    {
        return ((version >= mMinVersion) && (version < mEndVersion));
    }
};


/// Removes any sort prefix from a category name, to produce the raw string to display. This is a
/// no-op if the given category name doesn't contain any sort prefix.
///
/// This function returns the category string unchanged if the log flag showCategorySortPrefixes is
/// enabled.
///
/// @param category
///     The category string. May be empty. May be null.
/// @return
///     The same category string that was given, unless it's non-null, starts with a '!' character
///     and contains another '!' character (somewhere before next '|' character if there is one). In
///     that case, the returned pointer points into the same array but advanced to the character
///     after the second '!'.
OCTANEAPI_DECL const char * removeCategorySortPrefix(
    const char * category);

}   // namespace Octane
