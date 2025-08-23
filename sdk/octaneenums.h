// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANEENUMS_H_
#define _OCTANEENUMS_H_ 1



namespace Octane
{

/// @no-glsl
/// The different result codes apiMode_OctaneLive_activate() may return.
enum ActivationResult
{
    /// The activation was successful.
    ACTIVATION_OK = 0,
    /// The standalone license is invalid.
    ACTIVATION_STANDALONE_LICENSE_INVALID,
    /// The plugin license is invalid.
    ACTIVATION_PLUGIN_LICENSE_INVALID,
    /// The connection to OctaneLive or the dongle failed or timed out.
    ACTIVATION_CONNECTION_FAILED,
    /// The activation could not be performed since we could not acquire the inter-process
    /// lock which guarantees that just one instance can activate at a given time.
    ACTIVATION_LOCK_ACQUIRE_FAILED,
    /// The activation was cancelled by the user. For instance the user may have closed the
    /// standalone activation dialog.
    ACTIVATION_CANCELLED,
};


/// The type of the time transform
enum AnimationTimeTransformType
{
    /// Linear time transform
    ANIMATION_TIME_TRANSFORM_LINEAR = 1
};


/// Adaptive Sampling mode for grouping nearest pixels
enum AsPixelGroupMode
{
    AS_PIXEL_GROUP_NONE = 1,
    AS_PIXEL_GROUP_2X2  = 2,
    AS_PIXEL_GROUP_4X4  = 4,
};


/// The type of analytic lights.
enum AnalyticLightType
{
    /// Quad type.
    ANALYTIC_LIGHT_QUAD         = 0,
    /// Disk type.
    ANALYTIC_LIGHT_DISK         = 1,
    /// Directional light type.
    ANALYTIC_LIGHT_DIRECTIONAL  = 2,
    /// Sphere type.
    ANALYTIC_LIGHT_SPHERE       = 3,
    /// Tube type.
    ANALYTIC_LIGHT_TUBE         = 4,
};


/// Type of animation used
enum AnimationType
{
    /// Loop through from start to finish, and wraps around
    ANIMATION_LOOP     = 1,
    /// Back-and-forth passes through the data values of the animator
    ANIMATION_PINGPONG = 2,
    /// A single pass through the data values of the animator
    ANIMATION_ONCE     = 3
};


/// Texture type for baking texture nodes.
enum BakingTextureType
{
    /// LDR texture in the sRGB color space.
    BAKING_TEXTURE_TYPE_LDR = 0,
    /// HDR texture in the linear sRGB color space.
    BAKING_TEXTURE_TYPE_HDR = 2,
};


/// Binary math operations for nodes NT_TEX_MATH_BINARY and NT_FLOAT_MATH_BINARY.
enum BinaryOperation
{
    BINARY_OP_ADD      = 0,
    BINARY_OP_ATAN2    = 1,
    BINARY_OP_CROSS    = 2,
    BINARY_OP_DIVIDE   = 3,
    BINARY_OP_DOT      = 4,
    BINARY_OP_FMOD     = 5,
    BINARY_OP_LOG_BASE = 6,
    BINARY_OP_MAX      = 7,
    BINARY_OP_MIN      = 8,
    BINARY_OP_MOD      = 9,
    BINARY_OP_MULTIPLY = 10,
    BINARY_OP_POW      = 11,
    BINARY_OP_SUBTRACT = 12,
};


/// The different border modes supported by the image texture nodes. The value is set by the enum
/// pins P_BORDER_MODE_U and P_BORDER_MODE_V.
enum BorderMode
{
    /// The image is repeated in all directions.
    BORDER_MODE_WRAP  = 0,
    /// Outside of the valid UV range, the texture is repeated
    BORDER_MODE_BLACK = 1,
    /// Outside of the valid UV range, the texture is white / 1
    BORDER_MODE_WHITE = 2,
    /// The UV coordinates are clamped to the valid range, i.e. the color at the border of the image
    /// is continued over the valid range.
    BORDER_MODE_CLAMP = 3,
    /// Outside of the valid UV range, the texture is repeated, but adjacent copies are mirror
    /// images of each other.
    BORDER_MODE_MIRROR = 4,
};


/// Flags to control which parts of a background and foreground image to include when blending two
/// images together.
enum BlendRegionMask
{
    /// No area at all.
    BLEND_REGION_MASK_NOTHING = 0,

    /// The area covered by the background but not the foreground.
    BLEND_REGION_MASK_BACKGROUND_ONLY = 0x1,

    /// The area covered by the foreground but not the background.
    BLEND_REGION_MASK_FOREGROUND_ONLY = 0x2,

    /// The intersection of the background and foreground.
    BLEND_REGION_MASK_INTERSECTION = 0x4,

    /// The area covered by the background, including any part of the background that is also
    /// covered by the foreground.
    // Note: This long line cannot be wrapped because it breaks the Lua/GLSL file generation.
    BLEND_REGION_MASK_BACKGROUND_AND_INTERSECTION = BLEND_REGION_MASK_BACKGROUND_ONLY | BLEND_REGION_MASK_INTERSECTION,

    /// The area covered by the foreground, including any part of the foreground that is also
    /// covered by the background.
    // Note: This long line cannot be wrapped because it breaks the Lua/GLSL file generation.
    BLEND_REGION_MASK_FOREGROUND_AND_INTERSECTION = BLEND_REGION_MASK_FOREGROUND_ONLY | BLEND_REGION_MASK_INTERSECTION,

    /// The union of the background and foreground.
    // Note: This long line cannot be wrapped because it breaks the Lua/GLSL file generation.
    BLEND_REGION_MASK_ALL = BLEND_REGION_MASK_BACKGROUND_ONLY | BLEND_REGION_MASK_FOREGROUND_ONLY | BLEND_REGION_MASK_INTERSECTION,

    /// The union of the background and foreground, minus the intersection.
    // Note: This long line cannot be wrapped because it breaks the Lua/GLSL file generation.
    BLEND_REGION_MASK_XOR = BLEND_REGION_MASK_BACKGROUND_ONLY | BLEND_REGION_MASK_FOREGROUND_ONLY,
};


/// Component picker operation types supported by NT_{FLOAT,INT}_COMPONENT_PICKER.
enum ComponentPickerOperation
{
    /// Selects the x-channel.
    COMPONENT_PICKER_X   = 0,
    /// Selects the y-channel.
    COMPONENT_PICKER_Y   = 1,
    /// Selects the z-channel.
    COMPONENT_PICKER_Z   = 2,
    /// Selects the maximum value.
    COMPONENT_PICKER_MAX = 3,
    /// Selects the median value.
    COMPONENT_PICKER_MED = 4,
    /// Selects the minimum value.
    COMPONENT_PICKER_MIN = 5,
};


/// The Porter-Duff composite operations with some additional variations.
enum CompositeOperation
{
    COMPOSITE_OPERATION_CLEAR             = 12,
    COMPOSITE_OPERATION_DISSOLVE          = 14,
    COMPOSITE_OPERATION_DST               = 7,
    COMPOSITE_OPERATION_DST_ATOP          = 11,
    COMPOSITE_OPERATION_DST_IN            = 9,
    COMPOSITE_OPERATION_DST_OUT           = 10,
    COMPOSITE_OPERATION_DST_OVER          = 8,
    COMPOSITE_OPERATION_MATTE             = 16,
    COMPOSITE_OPERATION_PLUS              = 15,
    COMPOSITE_OPERATION_SRC               = 0,
    COMPOSITE_OPERATION_SRC_ATOP          = 6,
    COMPOSITE_OPERATION_SRC_IN            = 4,
    COMPOSITE_OPERATION_SRC_OUT           = 5,
    COMPOSITE_OPERATION_SRC_OVER          = 1,
    COMPOSITE_OPERATION_SRC_OVER_CONJOINT = 2,
    COMPOSITE_OPERATION_SRC_OVER_DISJOINT = 3,
    COMPOSITE_OPERATION_XOR               = 13,
};


/// Blend modes for composite textures and composite AOVs.
enum BlendMode
{
    BLEND_MODE_ADD                     = 0,
    BLEND_MODE_AVERAGE                 = 1,
    BLEND_MODE_BLUE                    = 44,
    BLEND_MODE_CHROMATICITY            = 41,
    BLEND_MODE_COLOR                   = 34,
    BLEND_MODE_COLOR_BURN              = 2,
    BLEND_MODE_COLOR_DODGE             = 3,
    BLEND_MODE_DARKEN                  = 4,
    BLEND_MODE_DARKER_COLOR            = 36,
    BLEND_MODE_DARKER_COLOR_LUMINANCE  = 38,
    BLEND_MODE_DIFFERENCE              = 5,
    BLEND_MODE_DIVIDE                  = 30,
    BLEND_MODE_DIVIDE_INVERSE          = 31,
    BLEND_MODE_EXCLUDE                 = 6,
    BLEND_MODE_FREEZE                  = 45,
    BLEND_MODE_GEOMETRIC               = 25,
    BLEND_MODE_GLOW                    = 7,
    BLEND_MODE_GRAIN_EXTRACT           = 48,
    BLEND_MODE_GRAIN_MERGE             = 49,
    BLEND_MODE_GREEN                   = 43,
    BLEND_MODE_HARD_LIGHT              = 8,
    BLEND_MODE_HARD_MIX                = 9,
    BLEND_MODE_HEAT                    = 47,
    BLEND_MODE_HUE                     = 32,
    BLEND_MODE_HYPOTENUSE              = 26,
    BLEND_MODE_LEVR                    = 46,
    BLEND_MODE_LIGHTEN                 = 10,
    BLEND_MODE_LIGHTER_COLOR           = 37,
    BLEND_MODE_LIGHTER_COLOR_LUMINANCE = 39,
    BLEND_MODE_LINEAR_BURN             = 11,
    BLEND_MODE_LINEAR_DODGE            = 12,
    BLEND_MODE_LINEAR_LIGHT            = 13,
    BLEND_MODE_LUMINOSITY              = 35,
    BLEND_MODE_MULTIPLY                = 14,
    BLEND_MODE_NEGATE                  = 15,
    BLEND_MODE_NORMAL                  = 16,
    BLEND_MODE_OVERLAY                 = 17,
    BLEND_MODE_PHOENIX                 = 18,
    BLEND_MODE_PIN_LIGHT               = 19,
    BLEND_MODE_RATIO                   = 52,
    BLEND_MODE_RED                     = 42,
    BLEND_MODE_REFLECT                 = 20,
    BLEND_MODE_REORIENTED_NORMAL       = 51,
    BLEND_MODE_SATURATION              = 33,
    BLEND_MODE_SCREEN                  = 21,
    BLEND_MODE_SOFT_LIGHT              = 22,
    BLEND_MODE_SPOTLIGHT               = 27,
    BLEND_MODE_SPOTLIGHT_BLEND         = 28,
    BLEND_MODE_STAMP                   = 50,
    BLEND_MODE_SUBTRACT                = 23,
    BLEND_MODE_SUBTRACT_INVERSE        = 29,
    BLEND_MODE_VALUE                   = 40,
    BLEND_MODE_VIVID_LIGHT             = 24,

    /// Offset used for composite operations reused as blend modes.
    BLEND_MODE_COMPOSITE_OFFSET        = 1000,

    BLEND_MODE_CLEAR                   = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_CLEAR,
    BLEND_MODE_DISSOLVE                = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_DISSOLVE,
    BLEND_MODE_DST                     = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_DST,
    BLEND_MODE_DST_ATOP                = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_DST_ATOP,
    BLEND_MODE_DST_IN                  = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_DST_IN,
    BLEND_MODE_DST_OUT                 = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_DST_OUT,
    BLEND_MODE_DST_OVER                = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_DST_OVER,
    BLEND_MODE_MATTE                   = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_MATTE,
    BLEND_MODE_PLUS                    = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_PLUS,
    BLEND_MODE_SRC                     = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_SRC,
    BLEND_MODE_SRC_ATOP                = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_SRC_ATOP,
    BLEND_MODE_SRC_IN                  = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_SRC_IN,
    BLEND_MODE_SRC_OUT                 = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_SRC_OUT,
    BLEND_MODE_SRC_OVER                = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_SRC_OVER,
    BLEND_MODE_SRC_OVER_CONJOINT       = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_SRC_OVER_CONJOINT,
    BLEND_MODE_SRC_OVER_DISJOINT       = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_SRC_OVER_DISJOINT,
    BLEND_MODE_XOR                     = BLEND_MODE_COMPOSITE_OFFSET + COMPOSITE_OPERATION_XOR,

    /// Offset added to blend mode values stored in an NT_BLENDING_SETTINGS node to signify that the
    /// blend operation is not HDR.
    BLEND_MODE_SDR_OFFSET              = 2000,
};


/// TODO: to be removed
enum BrdfModel
{
    /// Distribution used in Octane until version 3.07
    BRDF_OCTANE   = 0,
    /// Beckmann distribution
    BRDF_BECKMANN = 1,
    /// GGX distribution
    BRDF_GGX      = 2,
    /// WARD distribution (this is GLOSSY ONLY)!
    BRDF_WARD     = 3
};


/// Diffuse BxDF models supported by Octane
enum BxDFDiffuseModel
{
    /// Diffuse lobe with sheen-like roughness
    BxDF_DIFFUSE_OCTANE     = 0,
    /// Lambertian diffuse lobe (cosine lobe)
    BxDF_DIFFUSE_LAMBERTIAN = 1,
    /// Oren-nayar diffuse lobe, used in diffuse material
    BxDF_DIFFUSE_OREN_NAYAR = 2
};


/// Specular BxDF models supported by Octane
enum BxDFSpecularModel
{
    /// Distribution used in Octane until version 3.07
    BxDF_SPECULAR_OCTANE               = 0,
    /// Beckmann distribution          
    BxDF_SPECULAR_BECKMANN             = 1,
    /// GGX distribution               
    BxDF_SPECULAR_GGX                  = 2,
    /// Ward distribution (this is GLOSSY ONLY)!
    BxDF_SPECULAR_WARD                 = 3,
    /// Energy preserved GGX distribution
    BxDF_SPECULAR_ENERGY_PRESERVED_GGX = 6,
    /// Student's T distribution
    BxDF_SPECULAR_STD                  = 7,
};


/// BxDF transmission types
enum BxDFTranmissionType
{
    /// Specular transmission
    BxDF_TRANSMISSION_TYPE_SPECULAR          = 0,
    /// Diffuse transmission                 
    BxDF_TRANSMISSION_TYPE_DIFFUSE           = 1,
    /// Thin wall
    BxDF_TRANSMISSION_TYPE_THINWALL          = 2,
    /// Thin wall (diffuse, non manifold)
    BxDF_TRANSMISSION_TYPE_THINWALL_DIFFUSE  = 3
};


/// BxDF selection by Universal Material
enum BxDFUniversalModel
{
    /// Distribution used in Octane until version 3.07
    /// Set to specular octane BxDF value so that we ensure these BxDF models
    /// are always 0
    BxDF_UNIVERSAL_OCTANE               = BxDF_SPECULAR_OCTANE,
    /// Beckmann distribution           
    BxDF_UNIVERSAL_BECKMANN             = BxDF_SPECULAR_BECKMANN,
    /// GGX distribution                
    BxDF_UNIVERSAL_GGX                  = BxDF_SPECULAR_GGX,
    /// Ward distribution (this is GLOSSY ONLY)!
    BxDF_UNIVERSAL_WARD                 = BxDF_SPECULAR_WARD,
    /// Lambertian diffuse
    BxDF_UNIVERSAL_LAMBERTIAN           = 5,
    /// GGX distribution
    BxDF_UNIVERSAL_ENERGY_PRESERVED_GGX = BxDF_SPECULAR_ENERGY_PRESERVED_GGX,
    /// Student's T distribution
    BxDF_UNIVERSAL_STD                  = BxDF_SPECULAR_STD
};


/// The various node system event we have.
/// For events, exactly one of these flags will be set.
enum ChangeEventType
{
    /// If set, a node item was added to an owner. Any connection changes due to the addition
    /// are implicit and not sent explicitly.
    /// Event receivers:
    ///     Observers of the owner (if the owner is a pin the observers of its parent node)
    /// Data:
    ///     - mChangedOwner      will point to the owner the item was added to. if the owner
    ///                          is a node graph it will be a pointer to the node graph.
    ///                          if the owner is a node pin, it will be a pointer to the
    ///                          parent node of the pin and mChangedOwnerPinIx will identify
    ///                          the pin itself.
    ///     - mChangedOwnerPinIx is the index of the pin that owns the added item, if the
    ///                          item was added to a pin.
    ///     - mChangedItem       will point to the item that was added.
    ITEM_ADDED = (1 << 0),

    /// If set, a node item will be deleted. Any connection changes due to the deletion are
    /// implicit and not sent explicitly, but have already been made.
    /// Event receivers:
    ///     Observers of the removed item.
    /// Data:
    ///     - mChangedOwner      will point to the owner the item was removed from or NULL
    ///                          if the removed item is a root node graph. if the owner is a
    ///                          node graph it will be a pointer to the node graph. if the
    ///                          owner is a node pin, it will be a pointer to the parent
    ///                          node of the pin and mChangedOwnerPinIx will identify the
    ///                          pin itself.
    ///     - mChangedOwnerPinIx is the index of the pin that owns the added item, if the
    ///                          item was added to a pin.
    ///     - mChangedItem       will point to the item that will be deleted. The item is
    ///                          still intact and can be accessed.
    ITEM_DELETE = (1 << 1),

    /// If set, a node pin connection got changed, but no node was added or deleted.
    /// Event receivers:
    ///     Observers of the parent node of the pin.
    /// Data:
    ///     - mChangedItem  will point to the parent node of the pin of which the connection
    ///                     was changed
    ///     - mChangedPinIx will store the index of the pin of which the connection was
    ///                     changed
    CONNECTION_CHANGED = (1 << 2),

    /// If set, a new destination was added to a node, but no node was added or deleted.
    /// Event receivers:
    ///     Observers of the node of which the destination pins got changed.
    /// Data:
    ///     - mChangedItem will point to the node to which the destination got added
    DESTINATION_ADDED = (1 << 3),

    /// If set, the dynamic node pins of a node have changed. They may have been reordered,
    /// some pins may have been added and deleted, and some may have been replaced with a
    /// pin with different pin info.
    ///
    /// Event receivers:
    ///     Observers of the node owning the dynamic pins
    /// Data:
    ///     - mChangedItem will point to the node of which the dynamic pins changed
    PINS_CHANGED = (1 << 4),

    /// If set, the attributes or value of a node item changed.
    /// Event receivers:
    ///     Observers of the changed item.
    /// Data:
    ///     - mChangedItem    will point to the changed node item.
    ///     - mChangedIndices will point to an array that contains the indices of the
    ///                       changed/dirty attributes.
    ITEM_VALUE_CHANGED = (1 << 5),

    /// If set, a node connected to an input pin (either directly
    /// or indirectly) has changed, but the attributes of the item
    /// itself haven't.
    /// 
    /// Note that a change will never trigger both ITEM_VALUE_CHANGED
    /// and ITEM_INPUT_CHANGED.
    /// 
    /// Event receivers:
    ///     Observers to any destination nodes (either directly
    ///     or indirectly) after a node has changed.
    /// Data:
    ///     - mChangedItem    will point to the node owning the pin.
    ///     - mChangedIndices will point to an array that contains the indices of the
    ///                       changed/dirty pins.
    ITEM_INPUT_CHANGED = (1 << 6),

    /// If set, the name of a node item has changed.
    /// Event receivers:
    ///     Observers of the changed item.
    /// Data:
    ///     - mChangedItem will point to the changed node item.
    ITEM_NAME_CHANGED = (1 << 7),

    /// If set, the position of a node item has changed.
    /// Event receivers:
    ///     Observers of the changed item.
    /// Data:
    ///     - mChangedItem will point to the moved node item.
    ITEM_MOVED = (1 << 8),

    /// If set, the order of the input or output linkers changed.
    /// Event receivers:
    ///     Observers of graph owning the linker nodes.
    /// Data:
    ///     - mChangedItem  will point the the moved linker node.
    ///     - mChangedOwner will point to the node graph owning the linker node.
    LINKER_ORDER_CHANGED = (1 << 9),

    /// If set, the ui operation flag of a node item has changed.
    /// Event receivers:
    ///     Observers of the changed item.
    /// Data:
    ///     - mChangedItem will point to the changed node item.
    ITEM_UI_OPERATION_FLAG_CHANGED = (1 << 10),

    /// If set, the time transform of a node graph has changed.
    /// Event receivers:
    ///     - Observers of the time graph transform changes.
    /// Data:
    ///     - mChangedItem will point to the changed node graph.
    TIME_TRANSFORM_CHANGED = (1 << 11)
};


// List of channel group
enum ChannelGroups
{
    CHANNEL_GROUP_RGBA,
    CHANNEL_GROUP_RGB,
    CHANNEL_GROUP_ALPHA,
};


/// The channel mappings supported by NT_TEX_IMAGE_ADJUSTMENT.
enum ChannelMapping
{
    CHANNEL_MAPPING_RED               = 0,
    CHANNEL_MAPPING_GREEN             = 1,
    CHANNEL_MAPPING_BLUE              = 2,
    CHANNEL_MAPPING_RED_INVERSE       = 3,
    CHANNEL_MAPPING_GREEN_INVERSE     = 4,
    CHANNEL_MAPPING_BLUE_INVERSE      = 5,
    CHANNEL_MAPPING_LUMINANCE         = 6,
    CHANNEL_MAPPING_LUMINANCE_INVERSE = 7,
    CHANNEL_MAPPING_ZERO              = 8,
    CHANNEL_MAPPING_ONE               = 9,
};


/// Types of Cinema4D noise
enum Cinema4dNoiseType
{
    C4D_NOISE_TYPE_BOX_NOISE,
    C4D_NOISE_TYPE_BLIST_TURB,
    C4D_NOISE_TYPE_BUYA,
    C4D_NOISE_TYPE_CELL_NOISE,
    C4D_NOISE_TYPE_CRANAL,
    C4D_NOISE_TYPE_DENTS,
    C4D_NOISE_TYPE_DISPL_TURB,
    C4D_NOISE_TYPE_FBM,
    C4D_NOISE_TYPE_HAMA,
    C4D_NOISE_TYPE_LUKA,
    C4D_NOISE_TYPE_MOD_NOISE,
    C4D_NOISE_TYPE_NAKI,
    C4D_NOISE_TYPE_NOISE,
    C4D_NOISE_TYPE_NUTOUS,
    C4D_NOISE_TYPE_OBER,
    C4D_NOISE_TYPE_PEZO,
    C4D_NOISE_TYPE_POXO,
    C4D_NOISE_TYPE_SEMA,
    C4D_NOISE_TYPE_STUPL,
    C4D_NOISE_TYPE_TURBULENCE,
    C4D_NOISE_TYPE_VL_NOISE,
    C4D_NOISE_TYPE_WAVY_TURB,
    C4D_NOISE_TYPE_CELL_VORONOI,
    C4D_NOISE_TYPE_DISPL_VORONOI,
    C4D_NOISE_TYPE_VORONOI1,
    C4D_NOISE_TYPE_VORONOI2,
    C4D_NOISE_TYPE_VORONOI3,
    C4D_NOISE_TYPE_ZADA,
    C4D_NOISE_TYPE_FIRE,
    C4D_NOISE_TYPE_ELECTRIC,
    C4D_NOISE_TYPE_GASEOUS,
    C4D_NOISE_TYPE_RIDGEDMULTI,
};


/// The different clay modes we currerntly support.
enum ClayMode
{
    /// Clay mode disabled, i.e. normal render.
    CLAY_MODE_NONE = 0,
    /// Clay mode with one diffuse material, plus emitters.
    CLAY_MODE_GREY,
    /// Clay mode with diffuse materials only, but textures.
    CLAY_MODE_COLOR
};


/// Color channel types used for channel selection.
enum ColorChannelType
{
    COLOR_CHANNEL_R = 0,
    COLOR_CHANNEL_G = 1,
    COLOR_CHANNEL_B = 2,
};


/// Color space used for color picking. Used in the application preferences.
enum ColorPickerSpace
{
    /// This mode allows you to enter colors in the color picker using linear sRGB color values.
    COLOR_PICKER_SPACE_LINEAR_SRGB = 1,
    /// This mode allows you to enter colors in the color picker using sRGB color values.
    COLOR_PICKER_SPACE_SRGB = 2,
};


/// Color space conversions. Different subsets are supported by NT_TEX_COLOR_SPACE_CONVERSION,
/// NT_TEX_CHANNEL_MERGE, and NT_TEX_CHANNEL_PICK.
enum ColorSpaceConversion
{
    /// No-op
    COLOR_SPACE_CONVERSION_NONE                = 0,
    /// HSV
    COLOR_SPACE_CONVERSION_LINEAR_SRGB_TO_HSV  = 1,
    COLOR_SPACE_CONVERSION_HSV_TO_LINEAR_SRGB  = 2,
    /// HSL
    COLOR_SPACE_CONVERSION_LINEAR_SRGB_TO_HSL  = 3,
    COLOR_SPACE_CONVERSION_HSL_TO_LINEAR_SRGB  = 4,
    /// sRGB
    COLOR_SPACE_CONVERSION_LINEAR_SRGB_TO_SRGB = 5,
    COLOR_SPACE_CONVERSION_SRGB_TO_LINEAR_SRGB = 6,
    /// CIE xyY
    COLOR_SPACE_CONVERSION_LINEAR_SRGB_TO_XY_Y = 7,
    COLOR_SPACE_CONVERSION_XY_Y_TO_LINEAR_SRGB = 8,
    /// CIE XYZ
    COLOR_SPACE_CONVERSION_LINEAR_SRGB_TO_XYZ  = 9,
    COLOR_SPACE_CONVERSION_XYZ_TO_LINEAR_SRGB  = 10,
};


/// Curve types that different color spaces can have. This does not fully specify the exact transfer
/// function, but gives an indication as to the general purpose of curve.
enum ColorSpaceCurveType
{
    /// Scene-linear (e.g. ACEScg).
    COLOR_SPACE_CURVE_TYPE_LINEAR = 0,
    /// Approximately perceptually uniform (e.g. sRGB).
    COLOR_SPACE_CURVE_TYPE_UNIFORM = 1,
    /// Neither of the above.
    COLOR_SPACE_CURVE_TYPE_OTHER = 2,
};


/// Comparison operations supported by the Comparison texture node (NT_TEX_COMPARE), Comparison
/// composite texture layer (NT_TEX_COMPOSITE_LAYER_COMPARISON), and value nodes
/// NT_{FLOAT,INT}_RELATIONAL_OPERATOR.
enum ComparisonOperation
{
    COMPARISON_OPERATION_LESS             = 0,
    COMPARISON_OPERATION_GREATER          = 1,
    COMPARISON_OPERATION_EQUAL            = 2,
    COMPARISON_OPERATION_NOT_EQUAL        = 3,
    COMPARISON_OPERATION_LESS_OR_EQUAL    = 4,
    COMPARISON_OPERATION_GREATER_OR_EQUAL = 5,
};


/// Result of compiling code
enum CompilationResult
{
    /// request recompile, even if the code doesn't change
    COMPILE_FORCE = 3,
    /// not compiled yet
    COMPILE_NONE = 0,
    /// Compilation succeeded
    COMPILE_SUCCESS = 1,
    /// Compilation failed
    COMPILE_FAILED = 2
};


/// Types of alpha operation available for composite system.
enum CompositeAlphaOperation
{
    COMPOSITE_ALPHA_OPERATION_BLEND_MODE        = 0,
    COMPOSITE_ALPHA_OPERATION_ALPHA_COMPOSITING = 1, 
    COMPOSITE_ALPHA_OPERATION_BACKGROUND        = 2,
    COMPOSITE_ALPHA_OPERATION_FOREGROUND        = 3,
    COMPOSITE_ALPHA_OPERATION_ONE               = 4,
    COMPOSITE_ALPHA_OPERATION_ZERO              = 5,
    /// @deprecated
    COMPOSITE_ALPHA_OPERATION_BLEND_MODE_LEGACY = 6,
};


/// Coordinate system axes used by NT_TEX_WAVE_PATTERN.
enum CoordinateAxis
{
    COORDINATE_AXIS_X = 0,
    COORDINATE_AXIS_Y = 1,
    COORDINATE_AXIS_Z = 2,
};


/// Coordinate spaces used by NT_TEX_POSITION, NT_TEX_RAY_DIRECTION and NT_TEX_NORMAL.
enum CoordinateSystem
{
    COORDINATE_SYSTEM_WORLD   = 0,
    COORDINATE_SYSTEM_CAMERA  = 1,
    COORDINATE_SYSTEM_OBJECT  = 2,
    COORDINATE_SYSTEM_TANGENT = 3,
};


/// Types of cryptomatte we can render.
enum CryptomatteType
{
    /// @deprecated
    /// This does not create stable matte IDs
    CRYPTOMATTE_MATERIAL_NODE,
    /// Mattes based on the names of material and volume nodes
    CRYPTOMATTE_MATERIAL_NODE_NAME,
    /// Mattes based on the names of material and volume input pins
    CRYPTOMATTE_MATERIAL_PIN_NAME,
    /// @deprecated
    /// This does not create stable matte IDs
    CRYPTOMATTE_OBJECT_NODE,
    /// Mattes based on the names of object layer nodes
    CRYPTOMATTE_OBJECT_NODE_NAME,
    /// Mattes based on the names of object layer input pins
    CRYPTOMATTE_OBJECT_PIN_NAME,
    /// @deprecated creates mattes based on an internal identifier
    /// (names are "Mesh_xxxxxxxx")
    /// This does not create stable matte IDs
    CRYPTOMATTE_INSTANCE,
    /// Mattes based on the name of geometry nodes
    CRYPTOMATTE_GEOMETRY_NODE_NAME,
    /// Mattes based on the render layer IDs (names are "layer-1", etc.)
    CRYPTOMATTE_RENDER_LAYER,
    /// Mattes based on the user instance IDs (names are "user-1", etc.)
    CRYPTOMATTE_USER_INSTANCE_ID,
};


/// The mode for the various curvature components used in curvature texture node
enum CurvatureModes
{
    CURVATURE_MODE_CONCAVITY = (1 << 0),
    CURVATURE_MODE_CONVEXITY = (1 << 1),
    CURVATURE_MODE_ALL       = CURVATURE_MODE_CONCAVITY | CURVATURE_MODE_CONVEXITY,
};


/// IDs we use to identify custom AOVs.
enum CustomAov
{
    CUSTOM_AOV_1 = 0,
    CUSTOM_AOV_2,
    CUSTOM_AOV_3,
    CUSTOM_AOV_4,
    CUSTOM_AOV_5,
    CUSTOM_AOV_6,
    CUSTOM_AOV_7,
    CUSTOM_AOV_8,
    CUSTOM_AOV_9,
    CUSTOM_AOV_10,
    CUSTOM_AOV_11,
    CUSTOM_AOV_12,
    CUSTOM_AOV_13,
    CUSTOM_AOV_14,
    CUSTOM_AOV_15,
    CUSTOM_AOV_16,
    CUSTOM_AOV_17,
    CUSTOM_AOV_18,
    CUSTOM_AOV_19,
    CUSTOM_AOV_20,

    // The number of custom AOVs we currently support.
    CUSTOM_AOV_COUNT,

    // Indicates a custom AOV setting that is disabled/not set. Used for example in the enum lists
    // of those custom AOV
    INVALID_CUSTOM_AOV = 0x1000,
};


/// The custom AOV channel we can write to.
enum CustomAovChannel
{
    CUSTOM_AOV_CHANNEL_ALL   = 0,
    CUSTOM_AOV_CHANNEL_RED   = 1,
    CUSTOM_AOV_CHANNEL_GREEN = 2,
    CUSTOM_AOV_CHANNEL_BLUE  = 3,
};


/// The options we have for secondary rays.
enum CustomAovSecondaryRayVisibility
{
    CUSTOM_AOV_PRIMARY_RAYS_ONLY             = 0,
    CUSTOM_AOV_ALLOW_REFLECTIONS             = 1,
    CUSTOM_AOV_ALLOW_REFRACTIONS             = 2,
    CUSTOM_AOV_ALLOW_REFLECTIONS_REFRACTIONS = CUSTOM_AOV_ALLOW_REFLECTIONS | CUSTOM_AOV_ALLOW_REFRACTIONS,
};


/// The different ways we can apply a custom curve to an RGB color.
enum CustomCurveMode
{
    /// Apply the primary sub curve, followed by the relevant secondary sub curve, to each RGB
    /// component independently. This matches what tools such as Photoshop do.
    ///
    /// This may shift luminance, saturation and hue (the latter of which is probably not expected).
    CUSTOM_CURVE_MODE_ALL_CHANNELS = 0,

    /// Apply the curve to the luminance, and scale the color so its luminance matches the curve
    /// output. This is the only mode that doesn't depend on the color space. This may result in RGB
    /// components greater than the maximum output value of the curve, so should only be used on
    /// non-tone-mapped HDR images.
    ///
    /// This may shift luminance but preserves saturation and hue.
    CUSTOM_CURVE_MODE_LUMINANCE = 1,

    /// Apply the curve to the maximum RGB component, and scale the color so its maximum RGB
    /// component matches the curve output. This means saturated colors work more like
    /// CUSTOM_CURVE_MODE_ALL_CHANNELS whereas they may end up unexpectedly bright or dark with
    /// CUSTOM_CURVE_MODE_LUMINANCE.
    ///
    /// This may shift luminance but preserves saturation and hue.
    CUSTOM_CURVE_MODE_MAX_CHANNEL = 2,

    /// Apply the curve to the smooth maximum RGB component, and scale the color so the value that
    /// was the smooth maximum RGB component becomes the curve output. This is like
    /// CUSTOM_CURVE_MODE_MAX_CHANNEL without potentially noticeable transitions in gradients of
    /// changing hue where the maximum RGB component switches from one component to another.
    ///
    /// The smooth maximum RGB component is >= the maximum RGB component and <= the given maximum
    /// HDR value.
    ///
    /// This may shift luminance but preserves saturation and hue.
    CUSTOM_CURVE_MODE_MAX_CHANNEL_SMOOTH = 3,

    /// Apply the curve to the maximum and minimum RGB components, and linearly transform the color
    /// so its maximum and minimum RGB components match the curve outputs. This is a version of
    /// CUSTOM_CURVE_MODE_MAX_CHANNEL that's more like CUSTOM_CURVE_MODE_ALL_CHANNELS in that it
    /// allows the curve to affect the saturation, but still prevents hue shifts by keeping the
    /// middle RGB component at the same proportion of the way between the minimum and maximum
    /// components.
    ///
    /// This may shift luminance and saturation but preserves hue (except for that the saturation
    /// will end up "negative", i.e. a hue shift of exactly 180 degrees, if the curve is
    /// decreasing).
    CUSTOM_CURVE_MODE_MAX_AND_MIN_CHANNELS = 4,

    /// Apply the curve to the smooth maximum and smooth minimum RGB components, and linearly
    /// transform the color so the values that were the smooth maximum and smooth minimum RGB
    /// components become the curve outputs. This is like CUSTOM_CURVE_MODE_MAX_AND_MIN_CHANNELS
    /// without potentially noticeable transitions in gradients of changing hue where the maximum or
    /// minimum RGB component switches from one component to another. This is a version of
    /// CUSTOM_CURVE_MODE_MAX_CHANNEL_SMOOTH that's more like CUSTOM_CURVE_MODE_ALL_CHANNELS in that
    /// it allows the curve to affect the saturation, but still prevents hue shifts by keeping the
    /// middle RGB component at the same proportion of the way between the minimum and maximum
    /// components.
    ///
    /// The smooth maximum RGB component is >= the maximum RGB component and <= the given maximum
    /// HDR value. The smooth minimum RGB component is >= 0 and <= the minimum RGB component.
    ///
    /// This may shift luminance and saturation but preserves hue (except for that the saturation
    /// will end up "negative", i.e. a hue shift of exactly 180 degrees, if the curve is
    /// decreasing).
    CUSTOM_CURVE_MODE_MAX_AND_MIN_CHANNELS_SMOOTH = 5,
};


/// Describes the status of a file cache
enum CacheStatus
{
    /// This item is not cached at the moment
    CACHE_NONE,
    /// Caching this item failed
    CACHE_ERROR,
    /// Caching this item was still in progress when checked
    CACHE_BUILDING,
    /// Cache finished successfully
    CACHE_FINISHED,
};


/// The different models we support in the daylight environment node. The value is set by the enum
/// pin P_MODEL.
enum DaylightModel
{
    DAYLIGHTMODEL_PREETHAM = 0,
    DAYLIGHTMODEL_OCTANE   = 1,
    DAYLIGHTMODEL_NISHITA  = 2,
    DAYLIGHTMODEL_HOSEK    = 3,
};


// Supported denoiser list
enum DenoiserType
{
    DENOISER_OCTANE_AI          = 0,
    DENOISER_OPEN_IMAGE_DENOISE = 1
};


/// Supported denoiser quality settings.
/// These are currently only used with the Open Image Denoise library.
enum DenoiserQuality
{
    /// High performance filter mode.
    DENOISER_QUALITY_FAST     = 0,
    /// Balanced quality/performance filter mode.
    DENOISER_QUALITY_BALANCED = 1,
    /// High quality filter mode.
    DENOISER_QUALITY_HIGH     = 2,

};


// Decal texture channels
enum DecalTextureIndex
{
    DECAL_TEXTURE_INDEX_NORMAL = 0,
    DECAL_TEXTURE_INDEX_1      = 1,
    DECAL_TEXTURE_INDEX_2      = 2,
    DECAL_TEXTURE_INDEX_3      = 3,
    DECAL_TEXTURE_INDEX_4      = 4,
    DECAL_TEXTURE_INDEX_5      = 5,
    DECAL_TEXTURE_INDEX_6      = 6,
    DECAL_TEXTURE_INDEX_7      = 7,
    DECAL_TEXTURE_INDEX_8      = 8,
    DECAL_TEXTURE_INDEX_9      = 9,
};


/// Global illumination modes of the direct lighting kernel.
enum DirectLightMode
{
    /// No indirect light will be calculated
    DL_GI_NONE              = 0,
    /// Calculate ambient occlusion
    DL_GI_AMBIENT_OCCLUSION = 3,
    /// Calculate pure diffuse indirect light
    DL_GI_DIFFUSE           = 4,

    //-- Deprecated values

    /// @deprecated use the ambient color texture input
    _DL_GI_AMBIENT          = 1,
    /// @deprecated use a 0 ambient occlusion distance instead
    _DL_GI_SAMPLE_AMBIENT   = 2,
};


/// Dispersion models
enum DispersionModel
{
    /// Dispersion given as the IOR at 587.56 nm (d-line) plus the Abbe number
    DISPERSION_ABBE = 1,
    /// Dispersion given as the A and B factors of the Cauchy approximation
    DISPERSION_CAUCHY = 2,
};


/// The levels of details we currently support in displacement mapping.
enum DisplacementLod
{
    DISPLACEMENT_LEVEL_256  = 8,
    DISPLACEMENT_LEVEL_512  = 9,
    DISPLACEMENT_LEVEL_1024 = 10,
    DISPLACEMENT_LEVEL_2048 = 11,
    DISPLACEMENT_LEVEL_4096 = 12,
    DISPLACEMENT_LEVEL_8192 = 13,
};


/// The direction used to displace the surface
enum DisplacementDirection
{
    /// Follow the vertex normals stored in the mesh
    DISPLACEMENT_VERTEX_NORMAL    = 1,
    /// Follow the geometric normal
    DISPLACEMENT_GEOMETRIC_NORMAL = 2,
    /// Follow the smooth normals
    DISPLACEMENT_SMOOTH_NORMAL    = 3,
};


/// Vertex displacement texture space
enum DisplacementTextureSpace
{
    /// Texture data is in object space
    DISPLACEMENT_TEXTURE_SPACE_OBJECT,
    /// Texture data is in tangent space
    DISPLACEMENT_TEXTURE_SPACE_TANGENT
};


/// Vertex displacement texture type
enum DisplacementMapType
{
    /// Vector displacement map
    DISPLACEMENT_MAP_TYPE_VECTOR,
    /// Height displacement map
    DISPLACEMENT_MAP_TYPE_HEIGHT
};


/// Vertex displacement map axes
enum DisplacementTextureAxes
{
    DISPLACEMENT_MAP_AXES_POSITIVE_XYZ = 0,
    DISPLACEMENT_MAP_AXES_POSITIVE_XZY = 1,
    DISPLACEMENT_MAP_AXES_POSITIVE_XY_NEG_Z = 2,
};


/// Distance mode used by NT_TEX_RELATIVE_DISTANCE.
enum DistanceMode
{
    DISTANCE_MODE_NORMAL   = 0,
    DISTANCE_MODE_OFFSET_X = 1,
    DISTANCE_MODE_OFFSET_Y = 2,
    DISTANCE_MODE_OFFSET_Z = 3,
};


/// states a scene export can be.
enum ExportState
{
    /// The export hasn't started yet or was reset.
    EXPORT_NOT_STARTED,
    /// The export is currently running and there have been no errors.
    EXPORTING,
    /// The export is still running but there have been errors that will result in an incorrect
    /// export.
    EXPORTING_WITH_ERRORS,
    /// The export failed and can't be finished. Check the log to get more information.
    EXPORT_FAILED,
    /// The export was finished successfully.
    EXPORT_FINISHED,
};


/// Compression type for OpenEXR file export.
enum ExrCompressionType
{
    /// no compression
    EXR_COMPRESSION_NO_COMPRESSION = 1,
    /// run length encoding (lossless)
    EXR_COMPRESSION_RLE            = 2,
    /// zlib compression, one scan line at a time (lossless)
    EXR_COMPRESSION_ZIPS           = 3,
    /// zlib compression, in blocks of 16 scan lines (lossless)
    EXR_COMPRESSION_ZIP            = 4,
    /// piz-based wavelet compression (lossless)
    EXR_COMPRESSION_PIZ            = 5,
    /// lossy 24-bit float compression (lossy)
    EXR_COMPRESSION_PXR24          = 6,
    /// lossy 4-by-4 pixel block compression (lossy)
    EXR_COMPRESSION_B44            = 7,
    /// lossy 4-by-4 pixel block compression (lossy)
    EXR_COMPRESSION_B44A           = 8,
    /// lossy DCT based compression, in blocks of 32 scanlines.
    EXR_COMPRESSION_DWAA           = 9,
    /// lossy DCT based compression, in blocks of 256 scanlines.
    EXR_COMPRESSION_DWAB           = 10
};


/// The various modes we support in the falloff texture.
enum FalloffTextureMode
{
    FALLOFF_NORMAL_VS_EYE_RAY,
    FALLOFF_NORMAL_VS_VECTOR_90DEG,
    FALLOFF_NORMAL_VS_VECTOR_180DEG,
};


/// Supported filter types
enum FilterType
{
    FILTER_TYPE_NONE,
    FILTER_TYPE_BOX,
    FILTER_TYPE_GAUSSIAN,
};


/// The noise modes for NT_TEX_FRACTAL_NOISE.
enum FractalNoiseMode
{
    FRACTAL_NOISE_MODE_SCALAR = 0,
    FRACTAL_NOISE_MODE_VECTOR = 1,
};


/// The way Gaussian splat clouds are clipped
enum GaussianSplatClipMode
{
    /// Gaussian splat cloud won't be clipped by the bounding primitive
    GAUSSIAN_SPLAT_CLIP_MODE_NONE,
    /// Gaussian splat cloud points outside of the specified clipping bounding box primitive
    /// will be excluded from rendering
    GAUSSIAN_SPLAT_CLIP_MODE_BOX,
    /// Gaussian splat cloud points outside of the specified clipping bounding ellipsoid primitive
    /// will be excluded from rendering
    GAUSSIAN_SPLAT_CLIP_MODE_ELLIPSOID
};


/// The way Gaussian splats interact with lights
enum GaussianSplatLightingMode
{
    /// Gaussian splat brightness will not be scaled by the emitter power.
    /// Note: this mode doesn't support shadows from mesh emitters.
    GAUSSIAN_SPLAT_LIGHTING_MODE_NONE,
    /// Gaussian splat brightness will be scaled by the emitter power and dimmed with distance to the light
    GAUSSIAN_SPLAT_LIGHTING_MODE_POWER,
    /// Gaussian splat brightness will be scaled by the emitter power and dimmed with distance to the light.
    /// Additionally, it will be tinted by the light color.
    GAUSSIAN_SPLAT_LIGHTING_MODE_POWER_AND_COLOR
};


/// Export formats we support
enum GeometryExportFormat
{
    GEOMETRY_FORMAT_ALEMBIC = 1,
    GEOMETRY_FORMAT_FBX     = 2
};


/// Specifies how objects in a mesh node should be treated on import. value is set in the
/// A_GEOIMP_OBJECT_LAYER_IMPORT attribute of the NT_GEO_MESH node.
enum GeometryImportObjectLayers
{
    /// don't create any object layer pins
    GEOIMP_HIDE_OBJECT_LAYERS       = 1,
    /// create a single pin treating all objects as a single object
    GEOIMP_LOAD_AS_ONE_OBJECT_LAYER = 2,
    /// create a pin for each object
    GEOIMP_LOAD_ALL_OBJECT_LAYERS   = 3,
};


/// The various units we support during the geometry import. It's basically the unit used during the
/// export of the geometry. Used in the import preference attribute A_GEOIMP_SCALE_UNIT_TYPE.
enum GeometryImportScale
{
    GEOIMP_UNIT_MILLIMETERS  =  1,
    GEOIMP_UNIT_CENTIMETERS  =  2,
    GEOIMP_UNIT_DECIMETERS   =  3,
    GEOIMP_UNIT_METERS       =  4,
    GEOIMP_UNIT_DECAMETERS   =  5,
    GEOIMP_UNIT_HECTOMETERS  =  6,
    GEOIMP_UNIT_KILOMETERS   =  7,
    GEOIMP_UNIT_INCHES       =  8,
    GEOIMP_UNIT_FEET         =  9,
    GEOIMP_UNIT_YARDS        = 10,
    GEOIMP_UNIT_FURLONGS     = 11,
    GEOIMP_UNIT_MILES        = 12,
    /// DAZ Studio unit (8 feet)
    GEOIMP_UNIT_8FOOT_DAZ    = 13,
    /// Poser Native Unit (8.6 feet)
    GEOIMP_UNIT_86FOOT_POSER = 14,
};


/// Available actions on the global light IDs mask.
enum GlobalLightIdMaskAction
{
    GLOBAL_LIGHT_ID_MASK_ACTION_ENABLE,
    GLOBAL_LIGHT_ID_MASK_ACTION_DISABLE,
};


/// IDs we use to identify global texture AOVs.
enum GlobalTexAvo
{
    GLOBAL_TEX_AOV_1 = 0,
    GLOBAL_TEX_AOV_2,
    GLOBAL_TEX_AOV_3,
    GLOBAL_TEX_AOV_4,
    GLOBAL_TEX_AOV_5,
    GLOBAL_TEX_AOV_6,
    GLOBAL_TEX_AOV_7,
    GLOBAL_TEX_AOV_8,
    GLOBAL_TEX_AOV_9,
    GLOBAL_TEX_AOV_10,
    GLOBAL_TEX_AOV_11,
    GLOBAL_TEX_AOV_12,
    GLOBAL_TEX_AOV_13,
    GLOBAL_TEX_AOV_14,
    GLOBAL_TEX_AOV_15,
    GLOBAL_TEX_AOV_16,
    GLOBAL_TEX_AOV_17,
    GLOBAL_TEX_AOV_18,
    GLOBAL_TEX_AOV_19,
    GLOBAL_TEX_AOV_20,

    GLOBAL_TEX_AOV_COUNT,
};


/// Gradient types supported by the 'Gradient generator' texture node (NT_TEX_GRADIENT_GENERATOR).
enum GradientGeneratorType
{
    GRADIENT_GENERATOR_TYPE_LINEAR     = 0,
    GRADIENT_GENERATOR_TYPE_RADIAL     = 1,
    GRADIENT_GENERATOR_TYPE_ANGULAR    = 2,
    GRADIENT_GENERATOR_TYPE_POLYGONAL  = 3,
    GRADIENT_GENERATOR_TYPE_SPIRAL     = 4,
};


/// Gradient interpolation color spaces that we support.
enum GradientInterpColorSpace
{
    /// Interpolation is performed in a scene-linear color space.
    GRADIENT_INTERP_COLOR_SPACE_LINEAR = 0,
    /// Interpolation is performed in the Oklab color space.
    GRADIENT_INTERP_COLOR_SPACE_OKLAB = 1,
};


/// Gradient interpolation methods that we support.
enum GradientInterpType
{
    GRADIENT_INTERP_NONE     = 0,
    /// Constant values
    GRADIENT_INTERP_CONSTANT = 1,
    /// Linear interpolation between control points
    GRADIENT_INTERP_LINEAR   = 2,
    /// Smooth steps between control points.
    GRADIENT_INTERP_CUBIC    = 3,
    /// Cardinal cubic spline.
    GRADIENT_INTERP_CARDINAL    = 4,
};


/// Hair gradient interpolation types. These specify how the hair segment W coordinates
/// are calculated to fetch the actual value in the gradient texture.
enum HairInterpolationType
{
    /// W is calculated using the relative vertex position in the hair they belong to
    HAIR_INTERP_LENGTH   = 0,
    /// W is calculated using the index of the vertex in the hair they belong to
    HAIR_INTERP_SEGMENTS = 1,

    /// default hair interpolation type
    HAIR_INTERP_DEFAULT  = HAIR_INTERP_LENGTH,
};


/// Hair material base color modes.
enum HairMaterialBaseColorMode
{
    /// Base color is set by albedo
    HAIR_MATERIAL_BASE_COLOR_ALBEDO                   = 0,

    /// There is no base color
    HAIR_MATERIAL_BASE_COLOR_MELANIN_PLUS_PHEOMELANIN = 1,

    /// default hair color mode type
    HAIR_MATERIAL_BASE_COLOR = HAIR_MATERIAL_BASE_COLOR_ALBEDO,
};


/// IES photometry modes
enum IesPhotometryMode
{
    /// Normalize maximum value to 1.0
    IES_MAX_1 = 1,
    /// If an IES files contains the luminous output of the lamp, normalize.
    /// by mapping (luminance / (4 * pi) candelas) to 1.0.
    /// This results in a sphere emitter having approximately the same total
    /// light output as the same emitter without this distribution.
    IES_COMPENSATE_LUMINANCE = 2,
    /// Keep values given in candelas for all IES files.
    IES_CANDELA_ABSOLUTE = 3,
};


/// Image channel types.
enum ImageChannelType
{
    /// 8-bit unsigned integer (uint8_t)
    IMAGE_CHANNEL_UINT8     = 0,
    /// 32-bit float
    IMAGE_CHANNEL_FLOAT     = 1,
    /// 16-bit float
    IMAGE_CHANNEL_HALF      = 2,
    /// BC1 compression channel
    IMAGE_CHANNEL_BC1_UNORM = 3,
    /// BC3 compression channel
    IMAGE_CHANNEL_BC3_UNORM = 4,
    /// BC4 compression channel: signed init
    IMAGE_CHANNEL_BC4_SNORM = 5,
    /// BC4 compression channel: unsigned int
    IMAGE_CHANNEL_BC4_UNORM = 6,
    /// BC6 compression channel: sign 16 bits half floating point
    IMAGE_CHANNEL_BC6_SF    = 7,
    /// BC6 compression channel: unsigned 16 bits half floating point
    IMAGE_CHANNEL_BC6_UF    = 8,
    /// BC7 compression channel: unsigned int
    IMAGE_CHANNEL_BC7_UNORM = 9,

    /// Indicate that the pixel format should be derived from the source data
    /// (special value for image loaders)
    IMAGE_CHANNEL_AUTO      = -1
};


/// Image color types.
enum ImageColorType
{
    /// Keep the source format
    IMAGE_COLOR_KEEP_SOURCE = 0,
    /// Load as RGBA color image
    IMAGE_COLOR_RGBA        = 1,
    /// Load as greyscale image
    IMAGE_COLOR_GREYSCALE   = 2,
    /// Load as RGBA and use alpha channel
    IMAGE_COLOR_ALPHA       = 3,
};


/// Filter types to use when resampling an image.
enum ImageFilterType
{
    /// Nearest neighbor (point) sampling.
    IMAGE_FILTER_NEAREST_NEIGHBOR = 0,
    /// Bilinear filtering.
    IMAGE_FILTER_BILINEAR = 1,
};


/// Ways to get a mask value from an RGBA color in the output AOV compositor and composite texture.
enum ImageMaskSource
{
    // Note: The 0x4 bit must not be set in any of these.
    /// Use the red channel as the mask value.
    IMAGE_MASK_SOURCE_R                 = 0x0,
    /// Use the green channel as the mask value.
    IMAGE_MASK_SOURCE_G                 = 0x1,
    /// Use the blue channel as the mask value.
    IMAGE_MASK_SOURCE_B                 = 0x2,
    /// Use the alpha channel as the mask value.
    IMAGE_MASK_SOURCE_A                 = 0x3,
    /// Use the luminance as the mask value.
    IMAGE_MASK_SOURCE_LUMINANCE         = 0x8,

    IMAGE_MASK_SOURCE_INVERSE_BIT       = 0x4,
    /// Use one minus the red channel as the mask value.
    IMAGE_MASK_SOURCE_INVERSE_R         = IMAGE_MASK_SOURCE_INVERSE_BIT | 0x0,
    /// Use one minus the green channel as the mask value.
    IMAGE_MASK_SOURCE_INVERSE_G         = IMAGE_MASK_SOURCE_INVERSE_BIT | 0x1,
    /// Use one minus the blue channel as the mask value.
    IMAGE_MASK_SOURCE_INVERSE_B         = IMAGE_MASK_SOURCE_INVERSE_BIT | 0x2,
    /// Use one minus the alpha channel as the mask value.
    IMAGE_MASK_SOURCE_INVERSE_A         = IMAGE_MASK_SOURCE_INVERSE_BIT | 0x3,
    /// Use one minus the luminance as the mask value.
    IMAGE_MASK_SOURCE_INVERSE_LUMINANCE = IMAGE_MASK_SOURCE_INVERSE_BIT | 0x8,

    /// Special value used only for the unblend output AOV layer node, meaning to treat the input
    /// not as a mask but as a full RGBA image.
    IMAGE_MASK_SOURCE_NO_MASK           = 0x100,
};


/// The supported image file formats for saving render results.
enum ImageSaveFormat
{
    IMAGE_SAVE_FORMAT_PNG_8   = 0,
    IMAGE_SAVE_FORMAT_PNG_16  = 1,
    IMAGE_SAVE_FORMAT_EXR_16  = 2,
    IMAGE_SAVE_FORMAT_EXR_32  = 3,
    IMAGE_SAVE_FORMAT_TIFF_8  = 4,
    IMAGE_SAVE_FORMAT_TIFF_16 = 5,
    IMAGE_SAVE_FORMAT_JPEG    = 6,
};


/// The various image types we support in the image texture node. Used in the image texture node
/// attribute A_TYPE.
enum ImageType
{
    /// 8-bit monochrome (8 bits per pixel)
    IMAGE_TYPE_LDR_MONO        = 1,
    /// 8-bit monochrome + alpha (16 bits per pixel)
    IMAGE_TYPE_LDR_MONO_ALPHA  = 4,
    /// 8-bit RGBA (32 bits per pixel)
    IMAGE_TYPE_LDR_RGBA        = 0,
    /// 32-bit float monochrome (32 bits per pixel)
    IMAGE_TYPE_HDR_MONO        = 3,
    /// 32-bit float monochrome + alpha (64 bits per pixel)
    IMAGE_TYPE_HDR_MONO_ALPHA  = 5,
    /// 32-bit float RGBA (128 bits per pixel)
    IMAGE_TYPE_HDR_RGBA        = 2,
    /// 16-bit float monochrome (16 bits per pixel)
    IMAGE_TYPE_HALF_MONO       = 7,
    /// 16-bit float monochrome + alpha (32 bits per pixel)
    IMAGE_TYPE_HALF_MONO_ALPHA = 8,
    /// 16-bit float RGBA (64 bits per pixel)
    IMAGE_TYPE_HALF_RGBA       = 6,
    /// BC compression formats
    /// BC1 unsigned normalized integer:[0, 255] -> [0.0, 1.0]
    IMAGE_TYPE_BC1_UNORM       = 9,
    /// BC3 unsigned normalized integer:[0, 255] -> [0.0, 1.0]
    IMAGE_TYPE_BC3_UNORM       = 10,
    /// BC4 signed   normalized integer:[0, 255] -> [-1.0, 1.0]
    IMAGE_TYPE_BC4_SNORM       = 11,
    /// BC4 unsigned normalized integer:[0, 255] -> [0.0, 1.0]
    IMAGE_TYPE_BC4_UNORM       = 12,
    /// BC6 signed half floating point
    IMAGE_TYPE_BC6_SHF         = 13,
    /// BC6 unsigned half floating point
    IMAGE_TYPE_BC6_UHF         = 14,
    /// BC7 unsigned normalized integer
    IMAGE_TYPE_BC7_UNORM       = 15,
};


/// Ways to import the rest attributes for fbx and alembic files
enum ImportRestAttributesMode
{
    /// Rest attributes are disabled
    IMPORT_REST_ATTRIBUTES_MODE_DISABLED            = 1,
    /// Loaded from file (only for fbx and alembic files produced in octane/plugins)
    IMPORT_REST_ATTRIBUTES_MODE_FROM_FILE           = 2,
    /// If the file is animated, the vertex data at a specified animation time will be used as
    /// rest attributes. Only supported for alembic files.
    IMPORT_REST_ATTRIBUTES_MODE_FROM_ANIMATION_TIME = 3,
    /// If the file is animated, the vertex data from bind pose will be used as rest attributes.
    /// Only supported for FBX files.
    IMPORT_REST_ATTRIBUTES_MODE_FROM_BIND_POSE      = 4
};


/// The types of data the info channels kernel can render
enum InfoChannelType
{
    /// Geometric normals
    IC_TYPE_GEOMETRIC_NORMAL    = 0,
    /// Shading normals used after interpolation and correction for too grazing angles
    IC_TYPE_SHADING_NORMAL      = 1,
    /// The position of the first intersection point
    IC_TYPE_POSITION            = 2,
    /// Z-depth of the first intersection point
    IC_TYPE_Z_DEPTH             = 3,
    /// Material node ID
    IC_TYPE_MATERIAL_ID         = 4,
    /// Texture coordinates
    IC_TYPE_UV_COORD            = 5,
    /// First tangent vector
    IC_TYPE_TANGENT_U           = 6,
    /// Wireframe display
    IC_TYPE_WIREFRAME           = 7,
    /// Smooth normals
    IC_TYPE_SMOOTH_NORMAL       = 8,
    /// Object layer node ID
    IC_TYPE_OBJECT_ID           = 9,
    /// Ambient occlussion 
    IC_TYPE_AMBIENT_OCCLUSION   = 10,
    /// 2D Motion vector 
    IC_TYPE_MOTION_VECTOR       = 11,
    /// Render layer ID
    IC_TYPE_RENDER_LAYER_ID     = 12,
    /// Render layer mask
    IC_TYPE_RENDER_LAYER_MASK   = 13,
    /// Light pass ID
    IC_TYPE_LIGHT_PASS_ID       = 14,
    /// Local normal in tangent space
    IC_TYPE_TANGENT_NORMAL      = 15,
    /// Opacity
    IC_TYPE_OPACITY             = 16,
    /// Baking group ID
    IC_TYPE_BAKING_GROUP_ID     = 17,
    /// Roughness
    IC_TYPE_ROUGHNESS           = 18,
    /// Index of Refraction
    IC_TYPE_IOR                 = 19,
    /// Diffuse filter color
    IC_TYPE_DIFFUSE_FILTER      = 20,
    /// Reflection filter color
    IC_TYPE_REFLECTION_FILTER   = 21,
    /// Refraction filter color
    IC_TYPE_REFRACTION_FILTER   = 22,
    /// Transmission filter color
    IC_TYPE_TRANSMISSION_FILTER = 23,
    /// Object layer color
    IC_TYPE_OBJECT_LAYER_COLOR  = 24,
    /// Gaussian splat
    IC_TYPE_GAUSSIAN_SPLAT      = 25,
    //-- Deprecated values

    /// @deprecated Has been replaced by @ref IC_TYPE_SMOOTH_NORMAL
    IC_TYPE_VERTEX_NORMAL = IC_TYPE_SMOOTH_NORMAL,
};


/// Modes for deciding whether or not to do pixel filtering for most info passes. 
enum InfoChannelSamplingMode
{
    /// Enables DOF and motion blur.
    IC_SAMPLING_MODE_DISTRIBUTED              = 0,
    /// Disables DOF and motion blur, but leaves pixel filtering enabled.
    IC_SAMPLING_MODE_PIXEL_FILTERING_ENABLED  = 1,
    /// Disables DOF and motion blur, and disables pixel filtering for all render passes except for 
    /// render layer mask, and ambient occlusion.
    IC_SAMPLING_MODE_PIXEL_FILTERING_DISABLED = 2
};


/// Input actions for nodes with attribute A_INPUT_ACTION. The attribute is of type AT_INT2. The first
/// component identifies the action and the second the index of the movable input which specifies
/// the input (position) this action should be applied to.
/// Be aware that a movable input can consist of multiple pins. The number can be fetched from
/// @ref ApiNodeInfo::mMovableInputPinCount.
enum InputAction
{
    /// Nothing to be done.
    INPUT_ACTION_NONE = 0,
    /// Inserts a movable input at the given index (everything currently at or after that will be
    /// moved along).
    INPUT_ACTION_INSERT,
    /// Deletes a movable input.
    INPUT_ACTION_DELETE,
    /// Moves an input up in the node stack (i.e. its pins will be moved to a *smaller* index).
    INPUT_ACTION_MOVE_UP,
    /// Moves an input down in the node stack (i.e. its pins will be moved to a *higher* index).
    INPUT_ACTION_MOVE_DOWN,
};


/// Interpolation types for NT_TEX_RANGE and NT_FLOAT_RANGE.
enum InterpolationType
{
    INTERPOLATION_TYPE_LINEAR        = 0,
    INTERPOLATION_TYPE_LINEAR_STEP   = 1,
    INTERPOLATION_TYPE_SMOOTH_STEP   = 2,
    INTERPOLATION_TYPE_SMOOTHER_STEP = 3,
    INTERPOLATION_TYPE_POSTERIZE     = 4,
};


/// All the places that a DB item can come from.
enum ItemDbOrigin
{
    ORIGIN_LIVEDB  = 0,
    ORIGIN_LOCALDB = 1,
};


/// IDs to identify light AOVs.
enum LightAov
{
    LIGHT_AOV_SUN,
    LIGHT_AOV_AMBIENT,
    LIGHT_AOV_1,
    LIGHT_AOV_2,
    LIGHT_AOV_3,
    LIGHT_AOV_4,
    LIGHT_AOV_5,
    LIGHT_AOV_6,
    LIGHT_AOV_7,
    LIGHT_AOV_8,
    LIGHT_AOV_9,
    LIGHT_AOV_10,
    LIGHT_AOV_11,
    LIGHT_AOV_12,
    LIGHT_AOV_13,
    LIGHT_AOV_14,
    LIGHT_AOV_15,
    LIGHT_AOV_16,
    LIGHT_AOV_17,
    LIGHT_AOV_18,
    LIGHT_AOV_19,
    LIGHT_AOV_20,
};


/// The flags used in emission masks.
enum LightPassMask
{
    /// sun light
    LIGHT_PASS_MASK_SUN         = (1 << 0),
    /// Environment light or AO
    LIGHT_PASS_MASK_ENVIRONMENT = (1 << 1),
    /// First light pass (1)
    LIGHT_PASS_MASK_EMIT_FIRST  = (1 << 2),
    /// Last light pass (20). Other light passes are given by the bits in between
    LIGHT_PASS_MASK_EMIT_LAST   = (1 << 21),
    /// All light passes, but no sun or environment
    LIGHT_PASS_MASK_EMIT_ALL    = 0x3ffffc,
    /// All light in the scene
    LIGHT_PASS_MASK_ALL         = 0x3fffff,
};


/// The available views for thumbnails of liveDB material and texture macros.
enum LiveDbThumbnailView
{
    /// the entire material ball
    DB_VIEW_FULL,
    /// top left corner of the material ball
    DB_VIEW_CORNER,
    /// bottom of the material ball (mainly to inspect reflections and caustics)
    DB_VIEW_BOTTOM,
    /// the amount of views (excluding the combined view)
    DB_VIEW_COUNT,
    /// all the above views, stacked on top of each other, in the same order as the enumeration
    /// values. This view is only available in one fixed small size.
    DB_VIEW_COMBINED = -1
};


/// Logical operators supported by NT_BOOL_LOGIC_OPERATOR.
enum LogicalOperator
{
    LOGICAL_OPERATOR_AND = 0,
    LOGICAL_OPERATOR_OR  = 1,
    LOGICAL_OPERATOR_XOR = 2,
    LOGICAL_OPERATOR_NOT = 3,
};


/// Type of the script
enum LuaScriptType
{
    SCRIPT_TYPE_STANDALONE = 0,
    SCRIPT_TYPE_GRAPH      = 1
};


/// Memory locations of the resources 
enum MemoryLocation
{
    MEMORY_LOCATION_DEVICE,
    MEMORY_LOCATION_OUT_OF_CORE,
    MEMORY_LOCATION_PEER_TO_PEER,
};


/// Specify how to calculate the reflectance on metallic materials
enum MetallicReflectionMode
{
    /// Artistic mode: the metallic texture directly specifies the reflectance at normal incidence
    METALLIC_ARTISTIC = 0,
    /// Artist Friendly Metallic Fresnel method (r and g parameters)
    METALLIC_ARTISTIC_N_K = 3,
    /// Use IOR: The brightness of the reflection is determined by the IOR, but the metallic texture
    /// can be used to colorize the reflection
    METALLIC_IOR = 1,
    /// RGB IOR: The reflected color is entirely determined by the IOR values   
    METALLIC_RGB_IOR = 2,
};


/// The different module types supported in the standalone.
enum ModuleType 
{
    /// invalid module type
    MODULE_TYPE_INVALID    = 0,
    /// modules that implement a command action in the standalone
    MODULE_TYPE_COMMAND    = 1,
    /// modules that implement a dockable work pane in the standalone
    MODULE_TYPE_WORK_PANE  = 2,
    /// modules that implement a module node graph in the standalone
    MODULE_TYPE_NODE_GRAPH = 3,
};


/// The shapes supported by NT_TEX_MOIRE_MOSAIC.
enum MoireMosaicShape
{
    MOIRE_MOSAIC_SHAPE_RECTANGLE  = 0,
    MOIRE_MOSAIC_SHAPE_CIRCLE     = 1,
    MOIRE_MOSAIC_SHAPE_RING       = 2,
    MOIRE_MOSAIC_SHAPE_FRAME      = 3
};


/// The different pin structures that can be moved between nodes that have movable inputs. Movable
/// inputs can be moved from one node to another if and only if both nodes have the same movable
/// input format.
enum MovableInputFormat
{
    /// No movable inputs.
    MOVABLE_INPUT_FORMAT_NONE,

    /// A single pin of type PT_OUTPUT_AOV per input.
    MOVABLE_INPUT_FORMAT_OUTPUT_AOV,

    /// A single pin of type PT_OUTPUT_AOV_LAYER per input.
    MOVABLE_INPUT_FORMAT_OUTPUT_AOV_LAYER,

    /// A single pin of type PT_TEX_COMPOSITE_LAYER per input.
    MOVABLE_INPUT_FORMAT_COMPOSITE_TEXTURE_LAYER,

    /// Three pins per input: PT_BOOL enabled, PT_MATERIAL, and PT_TEXTURE mask.
    MOVABLE_INPUT_FORMAT_COMPOSITE_MATERIAL_INPUT,

    /// A single pin of type PT_GEOMETRY per input.
    MOVABLE_INPUT_FORMAT_GEOMETRY,

    /// A single pin of type PT_MATERIAL_LAYER per input.
    MOVABLE_INPUT_FORMAT_MATERIAL_LAYER,

    /// A single pin of type PT_RENDER_PASSES per input.
    MOVABLE_INPUT_FORMAT_RENDER_PASSES,

    /// Two pins per input: PT_DISPLACEMENT, and PT_FLOAT weight.
    MOVABLE_INPUT_FORMAT_VERTEX_DISPLACEMENT_MIXER_INPUT,

    /// Two pins per input: PT_FLOAT position, and PT_TEXTURE value.
    MOVABLE_INPUT_FORMAT_GRADIENT_TEXTURE_CONTROL_POINT,

    /// Two pins per input: PT_FLOAT position, and PT_FLOAT value.
    MOVABLE_INPUT_FORMAT_VOLUME_RAMP_CONTROL_POINT,

    /// Two pins per input: PT_FLOAT position, and PT_FLOAT value.
    MOVABLE_INPUT_FORMAT_TOON_RAMP_CONTROL_POINT,

    /// A single pin of type PT_RENDER_JOB per input.
    MOVABLE_INPUT_FORMAT_RENDER_JOB,

    /// A single pin of type PT_TRACE_SET_VISIBILITY_RULE per input.
    MOVABLE_INPUT_FORMAT_TRACE_SET_VISIBILITY_RULE,
};


/// Specific color spaces that Octane knows about.
enum NamedColorSpace
{
    /// A custom color space that this enum can't identify.
    NAMED_COLOR_SPACE_OTHER = 0,

    /// The sRGB color space.
    NAMED_COLOR_SPACE_SRGB = 1,

    /// The sRGB color space with a linear transfer function.
    NAMED_COLOR_SPACE_LINEAR_SRGB = 2,

    /// The ACES2065-1 color space, which is a linear color space using the ACES AP0 primaries and a
    /// white point very close to "D60".
    NAMED_COLOR_SPACE_ACES2065_1 = 3,

    /// The ACEScg color space, which is a linear color space using the ACES AP1 primaries and a
    /// white point very close to "D60".
    NAMED_COLOR_SPACE_ACESCG = 4,

    /// The XYZ color space (with E white point).
    NAMED_COLOR_SPACE_XYZ_E = 5,

    /// A placeholder value to represent some OCIO color space. We don't have any further details
    /// about these color spaces.
    NAMED_COLOR_SPACE_OCIO = 1000,
};


/// Types of noise used by the noise texture node (NT_TEX_NOISE)
enum NoiseType
{
    NOISE_TYPE_PERLIN       = 0,
    NOISE_TYPE_TURBULENCE   = 1,
    NOISE_TYPE_CIRCULAR     = 2,
    NOISE_TYPE_CHIPS        = 3,
    NOISE_TYPE_VORONOI      = 4,
};


/// Noise types defined in OSL and used by the random map texture (NT_TEX_RANDOM_MAP)
enum NoiseTypeOsl
{
    /// A signed Perlin-like gradient noise with an output range of [-1,1].
    NOISE_TYPE_OSL_PERLIN  = 0,
    /// An unsigned Perlin-like gradient noise with an output range of (0,1).
    NOISE_TYPE_OSL_UPERLIN = 1,
    /// A discrete function that is constant on [i,i+1) for all integers i, but has a different and
    /// uncorrelated value at every integer with an output range of [0,1].
    NOISE_TYPE_OSL_CELL    = 2,
    /// A function that returns a different, uncorrelated value at every input coordinate with an
    /// output range of [0,1].
    NOISE_TYPE_OSL_HASH    = 3,
};


/// Normal types used by the Normal texture node (NT_TEX_NORMAL).
enum NormalType
{
    NORMAL_TYPE_GEOMETRIC = 0,
    NORMAL_TYPE_SMOOTH    = 1,
    NORMAL_TYPE_SHADING   = 2,
};


/// The include object mode for various texture nodes
enum ObjectIncludeMode
{
    OBJECT_INCLUDE_ALL    = 0,
    OBJECT_INCLUDE_SELF   = 1,
    OBJECT_INCLUDE_OTHERS = 2,
};


/// The RGB color space that should be used during the import of MTL files. Used in the OBJ
/// import preference attribute A_OBJIMP_COLOR_SPACE.
enum ObjImportColorSpace
{
    OBJIMP_RGB_LINEAR_SRGB = 0,
    OBJIMP_RGB_SRGB        = 1,
};


/// Categories available in the liveDB.
enum OctaneLiveCategory 
{
    OLCAT_UNDEFINED = 0,
    OLCAT_ROOT      = 1,
    OLCAT_MATERIALS = 2,
    OLCAT_TEXTURES  = 3,
    OLCAT_EMISSIONS = 4,
};


/// The different OSL types that are supported as texture value types for texture pins
enum TextureValueType
{
    TEXTURE_VALUE_TYPE_UNKNOWN = 0,
    TEXTURE_VALUE_TYPE_INT     = 1 << 0,
    TEXTURE_VALUE_TYPE_FLOAT   = 1 << 1,
    TEXTURE_VALUE_TYPE_VECTOR2 = 1 << 2,
    TEXTURE_VALUE_TYPE_VECTOR3 = 1 << 3,
    TEXTURE_VALUE_TYPE_VECTOR4 = 1 << 4,
    TEXTURE_VALUE_TYPE_COLOR4  = 1 << 5,
    TEXTURE_VALUE_TYPE_COLOR3  = 1 << 6,
    TEXTURE_VALUE_TYPE_POINT   = 1 << 7,
    TEXTURE_VALUE_TYPE_NORMAL  = 1 << 8,
    TEXTURE_VALUE_TYPE_MATRIX  = 1 << 9,
    TEXTURE_VALUE_TYPE_MATRIX3 = 1 << 10,
    TEXTURE_VALUE_TYPE_STRING  = 1 << 11,
    TEXTURE_VALUE_TYPE_BOOL    = 1 << 12
};


/// Determine if and how the node can change its texture inputs/output value types
enum TextureNodeTypeMode
{
    /// The node's texture inputs/output pins are untyped
    TEXTURE_NODE_VALUE_TYPE_MODE_NONE     = 0,
    /// The node's typed texture inputs/output have a static type provided by the node's info
    TEXTURE_NODE_VALUE_TYPE_MODE_STATIC   = 1,
    /// The node's typed texture inputs/output can have their type set
    TEXTURE_NODE_VALUE_TYPE_MODE_SETTABLE = 2,
    /// The node's typed texture inputs/output derive their types from the node's output/inputs type
    TEXTURE_NODE_VALUE_TYPE_MODE_DERIVED  = 3,
};


/// Determine if and how a texture pin gains a value type
enum TexturePinValueTypeMode
{
    /// The texture pin is untyped
    TEXTURE_PIN_VALUE_TYPE_MODE_NONE                        = 0,
    /// The texture pin has a static type provided by the pin's info and can never be changed
    TEXTURE_PIN_VALUE_TYPE_MODE_STATIC                      = 1,
    /// The texture pin has a specific type provided by the pin's info but the type can still be toggled by its node
    TEXTURE_PIN_VALUE_TYPE_MODE_SPECIFIC_AND_CAN_BE_TOGGLED = 2,
    /// The texture pin gets its type from its node (if/when toggled, the pin's info determines the toggled value type)
    TEXTURE_PIN_VALUE_TYPE_MODE_DERIVED_AND_MAY_BE_TOGGLED  = 3,
};


/// Blend inputs that the unblend output AOV layer mode can extract.
enum UnblendExtractMode
{
    UNBLEND_EXTRACT_MODE_FOREGROUND = 0,
    UNBLEND_EXTRACT_MODE_BACKGROUND = 1,
};


/// The different modes we currently support in the panoramic camera. The value is set in the
/// pin P_CAMERA_MODE of the node NT_CAM_PANORAMIC.
enum PanoramicCameraMode
{
    SPHERICAL_CAMERA      = 0,
    CYLINDRICAL_CAMERA    = 1,
    CUBE_MAPPED_CAMERA    = 2,
    CUBE_MAPPED_CAMERA_PX = 3,
    CUBE_MAPPED_CAMERA_MX = 4,
    CUBE_MAPPED_CAMERA_PY = 5,
    CUBE_MAPPED_CAMERA_MY = 6,
    CUBE_MAPPED_CAMERA_PZ = 7,
    CUBE_MAPPED_CAMERA_MZ = 8,
};


/// Choose between global space or object space addressing for textures.
enum PositionType
{
    POSITION_GLOBAL        = 1,
    POSITION_OBJECT        = 3,
    POSITION_NORMAL        = 4,
};


/// IDs of the tabs in the preferences window.
enum PreferencesTabId
{
    PREFERENCES_TAB_ID_UNKNOWN = 0,

    PREFERENCES_TAB_ID_APPLICATION              = 1,
    PREFERENCES_TAB_ID_COLOR_MANAGEMENT         = 2,
    PREFERENCES_TAB_ID_CONTROLS                 = 3,
    PREFERENCES_TAB_ID_DEVICES                  = 4,
    PREFERENCES_TAB_ID_OUT_OF_CORE              = 5,
    PREFERENCES_TAB_ID_GEOMETRY_IMPORT          = 6,
    PREFERENCES_TAB_ID_GEOMETRY_IMPORT_OBJ      = 7,
    PREFERENCES_TAB_ID_GEOMETRY_IMPORT_ALEMBIC  = 8,
    PREFERENCES_TAB_ID_GEOMETRY_IMPORT_FBX      = 9,
    PREFERENCES_TAB_ID_GEOMETRY_IMPORT_USD      = 10,
    PREFERENCES_TAB_ID_GEOMETRY_IMPORT_VDB      = 11,
    PREFERENCES_TAB_ID_IMAGE_IMPORT             = 12,
    PREFERENCES_TAB_ID_EXPORT                   = 13,
    PREFERENCES_TAB_ID_NETWORK_RENDERING        = 14,
    PREFERENCES_TAB_ID_KEYBOARD_SHORTCUTS       = 15,
    PREFERENCES_TAB_ID_MODULES                  = 16,
    PREFERENCES_TAB_ID_MATERIALX_IMPORT         = 17,
    PREFERENCES_TAB_ID_FILESYSTEM_CACHING       = 18,
    PREFERENCES_TAB_ID_GRPC_API                 = 19,
};


/// Types of premultiplied alpha in a rendered image.
enum PremultipliedAlphaType
{
    /// Color channel values have not been multiplied with alpha channel values.
    PREMULTIPLIED_ALPHA_TYPE_NONE = 0,
    /// Color channel values have been multiplied with alpha channel values before applying the
    /// output color space's transfer function.
    PREMULTIPLIED_ALPHA_TYPE_LINEARIZED = 1,
    /// Color channel values have been multiplied with alpha channel values after applying the
    /// output color space's transfer function. This should be avoided because compositing should be
    /// performed in a linear color space.
    PREMULTIPLIED_ALPHA_TYPE_ENCODED = 2,
};


/// Shape used for texture/material preview mode.
enum PreviewType
{
    PREVIEW_PLANE            = 1,
    PREVIEW_SPHERE           = 2,
    PREVIEW_PLANE_WITH_ALPHA = 3,
};


/// The primitive types we know about outside of the render core.
enum PrimitiveType
{
    PRIMITIVE_TRIANGLE = 0,
    PRIMITIVE_OLD_DISPLACEMENT_TRIANGLE,
    PRIMITIVE_DISPLACEMENT_TRIANGLE,
    PRIMITIVE_HAIR,
    PRIMITIVE_SPHERE,
    PRIMITIVE_QUAD,
    PRIMITIVE_DISK,
    PRIMITIVE_TUBE,
    PRIMITIVE_PLANE,
    PRIMITIVE_INSTANCE,
    PRIMITIVE_VOLUME,
    PRIMITIVE_GS_CLOUD,
    PRIMITIVE_VECTRON,
    /// The number of primitive types we have.
    PRIMITIVE_TYPE_COUNT,
    /// Indicates an invalid / uninitialized primitive.
    PRIMITIVE_INVALID = PRIMITIVE_TYPE_COUNT
};


/// The types of procedural effects supported by NT_TEX_PROCEDURAL_EFFECTS.
enum ProceduralEffectType
{
    PROCEDURAL_EFFECT_BLASCHKE_PRODUCT    = 11,
    PROCEDURAL_EFFECT_CANDLE_FLAME        = 20,
    PROCEDURAL_EFFECT_COMBUSTIBLE_VORONOI = 0,
    PROCEDURAL_EFFECT_FIRE_EMITTER        = 8,
    PROCEDURAL_EFFECT_FRACTAL             = 1,
    PROCEDURAL_EFFECT_FRACTAL2            = 18,
    PROCEDURAL_EFFECT_FRACTAL3            = 12,
    PROCEDURAL_EFFECT_KALEIDOSCOPE        = 2,
    PROCEDURAL_EFFECT_MIST                = 9,
    PROCEDURAL_EFFECT_NEON_STRIPES        = 3,
    PROCEDURAL_EFFECT_NOISE_SMOKE_FLOW    = 17,
    PROCEDURAL_EFFECT_PAINT_COLORS        = 4,
    PROCEDURAL_EFFECT_PAINT_COLORS2       = 15,
    PROCEDURAL_EFFECT_PARTICLES           = 5,
    PROCEDURAL_EFFECT_PORTAL              = 19,
    PROCEDURAL_EFFECT_SKINNER             = 13,
    PROCEDURAL_EFFECT_SPIRAL              = 16,
    PROCEDURAL_EFFECT_STAR_SCROLLER       = 6,
    PROCEDURAL_EFFECT_SUN_SURFACE         = 14,
    PROCEDURAL_EFFECT_TUNNEL              = 10,
    PROCEDURAL_EFFECT_WAVEY_COLORS        = 7,
};


/// When the AABB should be displayed in the reference graph
enum ReferenceAABBDisplay
{
    // AABB is never displayed
    REFERENCE_AABB_DISPLAY_NEVER = 1,
    // AABB is displayed when the reference in unloaded
    REFERENCE_AABB_DISPLAY_WHEN_UNLOADED = 2,
    // AABB is always displayed
    REFERENCE_AABB_DISPLAY_ALWAYS = 3
};


/// State of a discrete render device.
enum RenderDeviceState
{
    /// Device state is not know.
    RENDER_DEVICE_STATE_UNKNOWN       = 0,
    /// Device is not supported by Octane.
    RENDER_DEVICE_STATE_NOT_SUPPORTED = 1,
    /// Device is disabled for rendering.
    RENDER_DEVICE_STATE_DISABLED      = 2,
    /// Device is enabled for rendering.
    RENDER_DEVICE_STATE_ENABLED       = 3,
    /// Device is rendering and in a valid state.
    RENDER_DEVICE_STATE_ACTIVE_OK     = 4,
    /// Device is rendering but has failed.
    RENDER_DEVICE_STATE_ACTIVE_FAILED = 5,
};


/// The different error types we may report from render threads.
enum RenderError
{
    RENDER_ERROR_NONE = 0,
    RENDER_ERROR_NOT_ENOUGH_DEVICE_MEMORY,
    RENDER_ERROR_NOT_ENOUGH_HOST_MEMORY,
    RENDER_ERROR_KERNEL_FAILED,
    RENDER_ERROR_ACTIVATION_REQUIRED,
    RENDER_ERROR_DEVICE_UNSUPPORTED,
    RENDER_ERROR_PEER_CONNECTION_CLOSED,
    RENDER_ERROR_MODULE_LOAD_FAILED,
    RENDER_ERROR_OSL,
    RENDER_ERROR_OSL_INTERNAL,
    RENDER_ERROR_LOD_DATA,
    RENDER_ERROR_UNSPECIFIED
};


/// Render job action.
enum RenderJobAction
{
    RENDER_JOB_ACTION_NONE             = 0,
    RENDER_JOB_ACTION_START_ITERATION  = 1,
    RENDER_JOB_ACTION_FINISH_ITERATION = 2,
    RENDER_JOB_ACTION_RENDER           = 3,
};


/// Render job status.
enum RenderJobStatus
{
    RENDER_JOB_STATUS_NONE         = 0,
    RENDER_JOB_STATUS_COMPLETED    = 2,
    RENDER_JOB_STATUS_RENDER_ERROR = 3,
    RENDER_JOB_STATUS_SAVE_ERROR   = 4,
    RENDER_JOB_STATUS_SKIPPED      = 5,
    RENDER_JOB_STATUS_SCRIPT_ERROR = 6,
};


/// The render layer render modes we currently support.
enum RenderLayerMode
{
    /// The beauty passes contain the active layer only and the render layer passes (shadows,
    /// reflections...) record the side-effects of the active render layer for those samples/pixels
    /// that are not obstructed by the active render layer.
    /// Beauty passes will be transparent for those pixels which are covered by objects on the
    /// inactive layers, even if there is a an object on the active layer behind the foreground
    /// object.
    RENDER_LAYER_MODE_NORMAL               = 0,
    /// All geometry that is not on an active layer will be made invisible. No side effects
    /// will be recorded in the render layer passes, i.e. the render layer passes will be empty.
    RENDER_LAYER_MODE_HIDE_INACTIVE_LAYERs = 1,
    /// The active layer will be made invisible and the render layer passes (shadows, reflections...)
    /// record the side-effects of the active render layer. The beauty passes will be empty.
    /// This is useful to capture all side-effects without having the active layer obstructing
    /// those.
    RENDER_LAYER_MODE_ONLY_SIDE_EFFECTS    = 2,
    /// Similar to RENDER_LAYER_MODE_HIDE_INACTIVE_LAYERs All geometry that is not on an active layer
    /// will be made invisible. But side effects(shadows, reflections...)will be recorded in the render 
    /// layer passes.
    RENDER_LAYER_MODE_HIDE_FROM_CAMERA     = 3
};


/// Render pass groups
enum RenderPassGroupId
{
    RENDER_PASS_GROUP_NONE        = 0,
    RENDER_PASS_GROUP_BEAUTY      = 1,
    RENDER_PASS_GROUP_LAYER       = 2,
    RENDER_PASS_GROUP_POST_PROC   = 3,
    RENDER_PASS_GROUP_LIGHT       = 4,
    RENDER_PASS_GROUP_INFO        = 5,
    RENDER_PASS_GROUP_MATERIAL    = 6,
    RENDER_PASS_GROUP_DENOISER    = 7,
    RENDER_PASS_GROUP_CRYPTOMATTE = 8,
    RENDER_PASS_GROUP_CUSTOM      = 9,
    RENDER_PASS_GROUP_GLOBAL_TEX  = 10,

    RENDER_PASS_GROUP_DEFAULT     = RENDER_PASS_GROUP_NONE
};


/// Ids for the render passes available in Octane.
enum RenderPassId
{
    // ====== Beauty AOVs ======

    // --- Beauty AOVs ---

    RENDER_PASS_BEAUTY               = 0,
    RENDER_PASS_CAMERA_MASK          = 125,
    RENDER_PASS_EMIT                 = 1,
    RENDER_PASS_ENVIRONMENT          = 2,
    RENDER_PASS_DIFFUSE              = 3,
    RENDER_PASS_DIFFUSE_DIRECT       = 4,
    RENDER_PASS_DIFFUSE_INDIRECT     = 5,
    RENDER_PASS_DIFFUSE_FILTER       = 6,
    RENDER_PASS_REFLECTION           = 7,
    RENDER_PASS_REFLECTION_DIRECT    = 8,
    RENDER_PASS_REFLECTION_INDIRECT  = 9,
    RENDER_PASS_REFLECTION_FILTER    = 10,
    RENDER_PASS_REFRACTION           = 11,
    RENDER_PASS_REFRACTION_FILTER    = 12,
    RENDER_PASS_TRANSMISSION         = 13,
    RENDER_PASS_TRANSMISSION_FILTER  = 14,
    RENDER_PASS_SSS                  = 15,
    RENDER_PASS_VOLUME               = 35,
    RENDER_PASS_VOLUME_MASK          = 36,
    RENDER_PASS_VOLUME_EMISSION      = 37,
    RENDER_PASS_VOLUME_Z_DEPTH_FRONT = 38,
    RENDER_PASS_VOLUME_Z_DEPTH_BACK  = 39,
    RENDER_PASS_GAUSSIAN_SPLAT       = 127,
    RENDER_PASS_SHADOW               = 32,
    RENDER_PASS_IRRADIANCE           = 33,
    RENDER_PASS_LIGHT_DIRECTION      = 34,
    RENDER_PASS_POSTFX_MEDIA_MASK    = 128,
    RENDER_PASS_POSTFX_MEDIA         = 84,
    RENDER_PASS_POST_PROC            = 16,
    RENDER_PASS_NOISE_BEAUTY         = 31,
    RENDER_PASS_ALPHA                = 126,

    // --- Render layer AOVs ---

    RENDER_PASS_LAYER_SHADOWS       = 17,
    RENDER_PASS_LAYER_BLACK_SHADOWS = 18,
    RENDER_PASS_LAYER_REFLECTIONS   = 20,

    // --- Light AOVs ---

    RENDER_PASS_AMBIENT_LIGHT          = 21,
    RENDER_PASS_AMBIENT_LIGHT_DIRECT   = 54,
    RENDER_PASS_AMBIENT_LIGHT_INDIRECT = 55,
    RENDER_PASS_SUNLIGHT               = 22,
    RENDER_PASS_SUNLIGHT_DIRECT        = 56,
    RENDER_PASS_SUNLIGHT_INDIRECT      = 57,
    RENDER_PASS_LIGHT_1                = 23,
    RENDER_PASS_LIGHT_2                = 24,
    RENDER_PASS_LIGHT_3                = 25,
    RENDER_PASS_LIGHT_4                = 26,
    RENDER_PASS_LIGHT_5                = 27,
    RENDER_PASS_LIGHT_6                = 28,
    RENDER_PASS_LIGHT_7                = 29,
    RENDER_PASS_LIGHT_8                = 30,
    RENDER_PASS_LIGHT_9                = 85,
    RENDER_PASS_LIGHT_10               = 86,
    RENDER_PASS_LIGHT_11               = 87,
    RENDER_PASS_LIGHT_12               = 88,
    RENDER_PASS_LIGHT_13               = 89,
    RENDER_PASS_LIGHT_14               = 90,
    RENDER_PASS_LIGHT_15               = 91,
    RENDER_PASS_LIGHT_16               = 92,
    RENDER_PASS_LIGHT_17               = 93,
    RENDER_PASS_LIGHT_18               = 94,
    RENDER_PASS_LIGHT_19               = 95,
    RENDER_PASS_LIGHT_20               = 96,
    RENDER_PASS_LIGHT_1_DIRECT         = 58,
    RENDER_PASS_LIGHT_2_DIRECT         = 59,
    RENDER_PASS_LIGHT_3_DIRECT         = 60,
    RENDER_PASS_LIGHT_4_DIRECT         = 61,
    RENDER_PASS_LIGHT_5_DIRECT         = 62,
    RENDER_PASS_LIGHT_6_DIRECT         = 63,
    RENDER_PASS_LIGHT_7_DIRECT         = 64,
    RENDER_PASS_LIGHT_8_DIRECT         = 65,
    RENDER_PASS_LIGHT_9_DIRECT         = 97,
    RENDER_PASS_LIGHT_10_DIRECT        = 98,
    RENDER_PASS_LIGHT_11_DIRECT        = 99,
    RENDER_PASS_LIGHT_12_DIRECT        = 100,
    RENDER_PASS_LIGHT_13_DIRECT        = 101,
    RENDER_PASS_LIGHT_14_DIRECT        = 102,
    RENDER_PASS_LIGHT_15_DIRECT        = 103,
    RENDER_PASS_LIGHT_16_DIRECT        = 104,
    RENDER_PASS_LIGHT_17_DIRECT        = 105,
    RENDER_PASS_LIGHT_18_DIRECT        = 106,
    RENDER_PASS_LIGHT_19_DIRECT        = 107,
    RENDER_PASS_LIGHT_20_DIRECT        = 108,
    RENDER_PASS_LIGHT_1_INDIRECT       = 66,
    RENDER_PASS_LIGHT_2_INDIRECT       = 67,
    RENDER_PASS_LIGHT_3_INDIRECT       = 68,
    RENDER_PASS_LIGHT_4_INDIRECT       = 69,
    RENDER_PASS_LIGHT_5_INDIRECT       = 70,
    RENDER_PASS_LIGHT_6_INDIRECT       = 71,
    RENDER_PASS_LIGHT_7_INDIRECT       = 72,
    RENDER_PASS_LIGHT_8_INDIRECT       = 73,
    RENDER_PASS_LIGHT_9_INDIRECT       = 109,
    RENDER_PASS_LIGHT_10_INDIRECT      = 110,
    RENDER_PASS_LIGHT_11_INDIRECT      = 111,
    RENDER_PASS_LIGHT_12_INDIRECT      = 112,
    RENDER_PASS_LIGHT_13_INDIRECT      = 113,
    RENDER_PASS_LIGHT_14_INDIRECT      = 114,
    RENDER_PASS_LIGHT_15_INDIRECT      = 115,
    RENDER_PASS_LIGHT_16_INDIRECT      = 116,
    RENDER_PASS_LIGHT_17_INDIRECT      = 117,
    RENDER_PASS_LIGHT_18_INDIRECT      = 118,
    RENDER_PASS_LIGHT_19_INDIRECT      = 119,
    RENDER_PASS_LIGHT_20_INDIRECT      = 120,

    // --- Denoiser AOVs ---

    RENDER_PASS_BEAUTY_DENOISER_OUTPUT              = 43,
    RENDER_PASS_DIFFUSE_DIRECT_DENOISER_OUTPUT      = 44,
    RENDER_PASS_DIFFUSE_INDIRECT_DENOISER_OUTPUT    = 45,
    RENDER_PASS_REFLECTION_DIRECT_DENOISER_OUTPUT   = 46,
    RENDER_PASS_REFLECTION_INDIRECT_DENOISER_OUTPUT = 47,
    RENDER_PASS_EMISSION_DENOISER_OUTPUT            = 76,
    RENDER_PASS_REMAINDER_DENOISER_OUTPUT           = 49,
    RENDER_PASS_VOLUME_DENOISER_OUTPUT              = 74,
    RENDER_PASS_VOLUME_EMISSION_DENOISER_OUTPUT     = 75,
    RENDER_PASS_DENOISE_ALBEDO                      = 123,
    RENDER_PASS_DENOISE_NORMAL                      = 40,

    // --- Custom AOVs ---

    // Offset used for the custom AOVs.
    // Note that, although they have their own range, these are still beauty AOVs.
    RENDER_PASS_CUSTOM_OFFSET = 500,

    RENDER_PASS_CUSTOM_1  = RENDER_PASS_CUSTOM_OFFSET + 1,
    RENDER_PASS_CUSTOM_2  = RENDER_PASS_CUSTOM_OFFSET + 2,
    RENDER_PASS_CUSTOM_3  = RENDER_PASS_CUSTOM_OFFSET + 3,
    RENDER_PASS_CUSTOM_4  = RENDER_PASS_CUSTOM_OFFSET + 4,
    RENDER_PASS_CUSTOM_5  = RENDER_PASS_CUSTOM_OFFSET + 5,
    RENDER_PASS_CUSTOM_6  = RENDER_PASS_CUSTOM_OFFSET + 6,
    RENDER_PASS_CUSTOM_7  = RENDER_PASS_CUSTOM_OFFSET + 7,
    RENDER_PASS_CUSTOM_8  = RENDER_PASS_CUSTOM_OFFSET + 8,
    RENDER_PASS_CUSTOM_9  = RENDER_PASS_CUSTOM_OFFSET + 9,
    RENDER_PASS_CUSTOM_10 = RENDER_PASS_CUSTOM_OFFSET + 10,
    RENDER_PASS_CUSTOM_11 = RENDER_PASS_CUSTOM_OFFSET + 11,
    RENDER_PASS_CUSTOM_12 = RENDER_PASS_CUSTOM_OFFSET + 12,
    RENDER_PASS_CUSTOM_13 = RENDER_PASS_CUSTOM_OFFSET + 13,
    RENDER_PASS_CUSTOM_14 = RENDER_PASS_CUSTOM_OFFSET + 14,
    RENDER_PASS_CUSTOM_15 = RENDER_PASS_CUSTOM_OFFSET + 15,
    RENDER_PASS_CUSTOM_16 = RENDER_PASS_CUSTOM_OFFSET + 16,
    RENDER_PASS_CUSTOM_17 = RENDER_PASS_CUSTOM_OFFSET + 17,
    RENDER_PASS_CUSTOM_18 = RENDER_PASS_CUSTOM_OFFSET + 18,
    RENDER_PASS_CUSTOM_19 = RENDER_PASS_CUSTOM_OFFSET + 19,
    RENDER_PASS_CUSTOM_20 = RENDER_PASS_CUSTOM_OFFSET + 20,

    // The render pass ID of the last custom AOV.
    RENDER_PASS_CUSTOM_LAST = RENDER_PASS_CUSTOM_20,

    // ====== Info AOVs (identical to the info channels) ======
    
    // Offset used for the info channels enum values (don't use this)
    RENDER_PASS_INFO_OFFSET              = 1000,

    RENDER_PASS_GEOMETRIC_NORMAL         = RENDER_PASS_INFO_OFFSET + IC_TYPE_GEOMETRIC_NORMAL,
    RENDER_PASS_SHADING_NORMAL           = RENDER_PASS_INFO_OFFSET + IC_TYPE_SHADING_NORMAL,
    RENDER_PASS_POSITION                 = RENDER_PASS_INFO_OFFSET + IC_TYPE_POSITION,
    RENDER_PASS_Z_DEPTH                  = RENDER_PASS_INFO_OFFSET + IC_TYPE_Z_DEPTH,
    RENDER_PASS_MATERIAL_ID              = RENDER_PASS_INFO_OFFSET + IC_TYPE_MATERIAL_ID,
    RENDER_PASS_UV_COORD                 = RENDER_PASS_INFO_OFFSET + IC_TYPE_UV_COORD,
    RENDER_PASS_TANGENT_U                = RENDER_PASS_INFO_OFFSET + IC_TYPE_TANGENT_U,
    RENDER_PASS_WIREFRAME                = RENDER_PASS_INFO_OFFSET + IC_TYPE_WIREFRAME,
    RENDER_PASS_SMOOTH_NORMAL            = RENDER_PASS_INFO_OFFSET + IC_TYPE_SMOOTH_NORMAL,
    RENDER_PASS_OBJECT_ID                = RENDER_PASS_INFO_OFFSET + IC_TYPE_OBJECT_ID,
    RENDER_PASS_BAKING_GROUP_ID          = RENDER_PASS_INFO_OFFSET + IC_TYPE_BAKING_GROUP_ID,
    RENDER_PASS_AMBIENT_OCCLUSION        = RENDER_PASS_INFO_OFFSET + IC_TYPE_AMBIENT_OCCLUSION,
    RENDER_PASS_MOTION_VECTOR            = RENDER_PASS_INFO_OFFSET + IC_TYPE_MOTION_VECTOR,
    RENDER_PASS_RENDER_LAYER_ID          = RENDER_PASS_INFO_OFFSET + IC_TYPE_RENDER_LAYER_ID,
    RENDER_PASS_RENDER_LAYER_MASK        = RENDER_PASS_INFO_OFFSET + IC_TYPE_RENDER_LAYER_MASK,
    RENDER_PASS_LIGHT_PASS_ID            = RENDER_PASS_INFO_OFFSET + IC_TYPE_LIGHT_PASS_ID,
    RENDER_PASS_TANGENT_NORMAL           = RENDER_PASS_INFO_OFFSET + IC_TYPE_TANGENT_NORMAL,
    RENDER_PASS_OPACITY                  = RENDER_PASS_INFO_OFFSET + IC_TYPE_OPACITY,
    RENDER_PASS_ROUGHNESS                = RENDER_PASS_INFO_OFFSET + IC_TYPE_ROUGHNESS,
    RENDER_PASS_IOR                      = RENDER_PASS_INFO_OFFSET + IC_TYPE_IOR,
    RENDER_PASS_DIFFUSE_FILTER_INFO      = RENDER_PASS_INFO_OFFSET + IC_TYPE_DIFFUSE_FILTER,
    RENDER_PASS_REFLECTION_FILTER_INFO   = RENDER_PASS_INFO_OFFSET + IC_TYPE_REFLECTION_FILTER,
    RENDER_PASS_REFRACTION_FILTER_INFO   = RENDER_PASS_INFO_OFFSET + IC_TYPE_REFRACTION_FILTER,
    RENDER_PASS_TRANSMISSION_FILTER_INFO = RENDER_PASS_INFO_OFFSET + IC_TYPE_TRANSMISSION_FILTER,
    RENDER_PASS_OBJECT_LAYER_COLOR       = RENDER_PASS_INFO_OFFSET + IC_TYPE_OBJECT_LAYER_COLOR,
    RENDER_PASS_GAUSSIAN_SPLAT_INFO      = RENDER_PASS_INFO_OFFSET + IC_TYPE_GAUSSIAN_SPLAT,

    // --- Global texture AOVs ---

    // 
    RENDER_PASS_GLOBAL_TEX_OFFSET = 1100,

    RENDER_PASS_GLOBAL_TEX_1  = RENDER_PASS_GLOBAL_TEX_OFFSET + 1,
    RENDER_PASS_GLOBAL_TEX_2  = RENDER_PASS_GLOBAL_TEX_OFFSET + 2,
    RENDER_PASS_GLOBAL_TEX_3  = RENDER_PASS_GLOBAL_TEX_OFFSET + 3,
    RENDER_PASS_GLOBAL_TEX_4  = RENDER_PASS_GLOBAL_TEX_OFFSET + 4,
    RENDER_PASS_GLOBAL_TEX_5  = RENDER_PASS_GLOBAL_TEX_OFFSET + 5,
    RENDER_PASS_GLOBAL_TEX_6  = RENDER_PASS_GLOBAL_TEX_OFFSET + 6,
    RENDER_PASS_GLOBAL_TEX_7  = RENDER_PASS_GLOBAL_TEX_OFFSET + 7,
    RENDER_PASS_GLOBAL_TEX_8  = RENDER_PASS_GLOBAL_TEX_OFFSET + 8,
    RENDER_PASS_GLOBAL_TEX_9  = RENDER_PASS_GLOBAL_TEX_OFFSET + 9,
    RENDER_PASS_GLOBAL_TEX_10 = RENDER_PASS_GLOBAL_TEX_OFFSET + 10,
    RENDER_PASS_GLOBAL_TEX_11 = RENDER_PASS_GLOBAL_TEX_OFFSET + 11,
    RENDER_PASS_GLOBAL_TEX_12 = RENDER_PASS_GLOBAL_TEX_OFFSET + 12,
    RENDER_PASS_GLOBAL_TEX_13 = RENDER_PASS_GLOBAL_TEX_OFFSET + 13,
    RENDER_PASS_GLOBAL_TEX_14 = RENDER_PASS_GLOBAL_TEX_OFFSET + 14,
    RENDER_PASS_GLOBAL_TEX_15 = RENDER_PASS_GLOBAL_TEX_OFFSET + 15,
    RENDER_PASS_GLOBAL_TEX_16 = RENDER_PASS_GLOBAL_TEX_OFFSET + 16,
    RENDER_PASS_GLOBAL_TEX_17 = RENDER_PASS_GLOBAL_TEX_OFFSET + 17,
    RENDER_PASS_GLOBAL_TEX_18 = RENDER_PASS_GLOBAL_TEX_OFFSET + 18,
    RENDER_PASS_GLOBAL_TEX_19 = RENDER_PASS_GLOBAL_TEX_OFFSET + 19,
    RENDER_PASS_GLOBAL_TEX_20 = RENDER_PASS_GLOBAL_TEX_OFFSET + 20,

    // The render pass ID of the last custom AOV.
    RENDER_PASS_GLOBAL_TEX_LAST = RENDER_PASS_GLOBAL_TEX_20,


    // ====== Cryptomatte AOVs ======
    // Although not considered beauty passes, they are rendered and exported
    // together with the beauty passes
    
    /// Offset where cryptomatte AOV IDs start
    RENDER_PASS_CRYPTOMATTE_OFFSET = 2000,

    // Material IDs
    RENDER_PASS_CRYPTOMATTE_MATERIAL_NODE_NAME = RENDER_PASS_CRYPTOMATTE_OFFSET + 1,
    RENDER_PASS_CRYPTOMATTE_MATERIAL_NODE      = RENDER_PASS_CRYPTOMATTE_OFFSET + 6,
    RENDER_PASS_CRYPTOMATTE_MATERIAL_PIN_NAME  = RENDER_PASS_CRYPTOMATTE_OFFSET + 2,
    // Object layer IDs
    RENDER_PASS_CRYPTOMATTE_OBJECT_NODE_NAME   = RENDER_PASS_CRYPTOMATTE_OFFSET + 3,
    RENDER_PASS_CRYPTOMATTE_OBJECT_NODE        = RENDER_PASS_CRYPTOMATTE_OFFSET + 4,
    RENDER_PASS_CRYPTOMATTE_OBJECT_PIN_NAME    = RENDER_PASS_CRYPTOMATTE_OFFSET + 7,
    RENDER_PASS_CRYPTOMATTE_RENDER_LAYER       = RENDER_PASS_CRYPTOMATTE_OFFSET + 9,
    // Instance IDs
    RENDER_PASS_CRYPTOMATTE_INSTANCE           = RENDER_PASS_CRYPTOMATTE_OFFSET + 5,
    RENDER_PASS_CRYPTOMATTE_GEOMETRY_NODE_NAME = RENDER_PASS_CRYPTOMATTE_OFFSET + 8,
    RENDER_PASS_CRYPTOMATTE_USER_INSTANCE_ID   = RENDER_PASS_CRYPTOMATTE_OFFSET + 10,

    // limit to identify cryptomatte passes
    RENDER_PASS_CRYPTOMATTE_LAST   = 4999,

    // ====== Other ======

    /// Used for uninitialized render pass IDs.
    RENDER_PASS_UNKNOWN = 5000,


    ///===== Output AOVs =====

    // All render pass IDs equal or larger than this are considered Output AOVs.
    RENDER_PASS_OUTPUT_AOV_IDS_OFFSET = 10000,

    // ====== Deprecated values ======

    // @deprecated Has been replaced by @ref RENDER_PASS_SMOOTH_NORMAL
    RENDER_PASS_VERTEX_NORMAL = RENDER_PASS_SMOOTH_NORMAL,
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL1 = 11000,         
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL2 = 11001,         
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL3 = 11002,         
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL4 = 11003,         
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL5 = 11004,         
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL6 = 11005,         
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL7 = 11006,         
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL8 = 11007,         
    // @deprecated It was used for normalized info output AOV
    RENDER_PASS_OUTPUT_AOV_IDS_INTERNAL9 = 11008,
};


/// The state the render target can be in.
enum RenderState
{
    /// The render target hasn't started rendering yet or was stopped (i.e. no render threads are
    /// running).
    RSTATE_STOPPED = 0,
    /// The render target hasn't started rendering yet because it is waiting for pending render
    /// data.
    RSTATE_WAITING_FOR_DATA,
    /// The render target is happily rendering along.
    RSTATE_RENDERING,
    /// The render target is paused and nothing is happening right now.
    RSTATE_PAUSED,
    /// The render target has rendered all samples per pixel or no render target node was specified
    /// yet.
    RSTATE_FINISHED,
};


/// Categories of a resource allocation
enum ResourceCategory
{
    RESOURCE_CATEGORY_GEOMETRY = 0,
    RESOURCE_CATEGORY_IMAGES,
    RESOURCE_CATEGORY_RUN_TIME,
    RESOURCE_CATEGORY_NODE_SYSTEM,
    RESOURCE_CATEGORY_FILM_BUFFER,
    RESOURCE_CATEGORY_COMPOSITOR,

    RESOURCE_CATEGORY_COUNT,
    RESOURCE_CATEGORY_UNKNOWN = RESOURCE_CATEGORY_COUNT,
};


/// All film response curves currently supported.
enum ResponseCurveId
{
    // Agfa
    CURVE_AGFACOLOR_FUTURA_100CD      = 99,
    CURVE_AGFACOLOR_FUTURA_200CD      = 100,
    CURVE_AGFACOLOR_FUTURA_400CD      = 101,
    CURVE_AGFACOLOR_FUTURA_II_100CD   = 102,
    CURVE_AGFACOLOR_FUTURA_II_200CD   = 103,
    CURVE_AGFACOLOR_FUTURA_II_400CD   = 104,
    CURVE_AGFACOLOR_HDC_100_PLUSCD    = 105,
    CURVE_AGFACOLOR_HDC_200_PLUSCD    = 106,
    CURVE_AGFACOLOR_HDC_400_PLUSCD    = 107,
    CURVE_AGFACOLOR_OPTIMA_II_100CD   = 108,
    CURVE_AGFACOLOR_OPTIMA_II_200CD   = 109,
    CURVE_AGFACOLOR_ULTRA_050CD       = 110,
    CURVE_AGFACOLOR_VISTA_100CD       = 111,
    CURVE_AGFACOLOR_VISTA_200CD       = 112,
    CURVE_AGFACOLOR_VISTA_400CD       = 113,
    CURVE_AGFACOLOR_VISTA_800CD       = 114,
    CURVE_AGFACHROME_CT_PRECISA_100CD = 115,
    CURVE_AGFACHROME_CT_PRECISA_200CD = 116,
    CURVE_AGFACHROME_RSX2_050CD       = 117,
    CURVE_AGFACHROME_RSX2_100CD       = 118,
    CURVE_AGFACHROME_RSX2_200CD       = 119,
    // Eastman-Kodak group
    CURVE_ADVANTIX_100CD              = 201,
    CURVE_ADVANTIX_200CD              = 202,
    CURVE_ADVANTIX_400CD              = 203,
    CURVE_GOLD_100CD                  = 204,
    CURVE_GOLD_200CD                  = 205,
    CURVE_MAX_ZOOM_800CD              = 206,
    CURVE_PORTRA_100TCD               = 207,
    CURVE_PORTRA_160NCCD              = 208,
    CURVE_PORTRA_160VCCD              = 209,
    CURVE_PORTRA_800CD                = 210,
    CURVE_PORTRA_400VCCD              = 211,
    CURVE_PORTRA_400NCCD              = 212,
    CURVE_EKTACHROME_100_PLUSCD       = 213,
    CURVE_EKTACHROME_320TCD           = 214,
    CURVE_EKTACHROME_400XCD           = 215,
    CURVE_EKTACHROME_64CD             = 216,
    CURVE_EKTACHROME_64TCD            = 217,
    CURVE_EKTACHROME_E100SCD          = 218,
    CURVE_EKTACHROME_100CD            = 219,
    CURVE_KODACHROME_200CD            = 220,
    CURVE_KODACHROME_25               = 221,
    CURVE_KODACHROME_64CD             = 222,
    // Misc group
    CURVE_F125CD                      = 301,
    CURVE_F250CD                      = 302,
    CURVE_F400CD                      = 303,
    CURVE_FCICD                       = 304,
    CURVE_DSCS315_1                   = 305,
    CURVE_DSCS315_2                   = 306,
    CURVE_DSCS315_3                   = 307,
    CURVE_DSCS315_4                   = 308,
    CURVE_DSCS315_5                   = 309,
    CURVE_DSCS315_6                   = 310,
    CURVE_FP2900Z                     = 311,
    /// Don't use a film curve
    CURVE_LINEAR                      = 400,
    CURVE_SRGB                        = 401,
    CURVE_GAMMA1_8                    = 402,
    CURVE_GAMMA2_2                    = 403,
};


/// Round edges modes.
enum RoundEdgesMode
{
    /// Rounded edges are disabled.
    ROUND_EDGES_MODE_OFF              = 0,
    /// Fast round edges mode
    ROUND_EDGES_MODE_FAST             = 1,
    /// Accurate round edges mode, convex and concave edges.
    ROUND_EDGES_MODE_ACCURATE         = 2,
    /// Accurate round edges mode, convex edges only.
    ROUND_EDGES_MODE_ACCURATE_CONVEX  = 3,
    /// Accurate round edges mode, concave edges only.
    ROUND_EDGES_MODE_ACCURATE_CONCAVE = 4,
};


/// Rounding modes supported by NT_FLOAT_TO_INT.
enum RoundingMode
{
    /// Round closest, with half values rounded away from zero.
    ROUNDING_MODE_ROUND = 0,
    /// Round toward negative infinity.
    ROUNDING_MODE_FLOOR = 1,
    /// Round toward positive infinity.
    ROUNDING_MODE_CEIL  = 2,
    /// Round toward zero.
    ROUNDING_MODE_TRUNC = 3,
};


/// The sampler types we currently provide.
enum SamplerType
{
    SAMPLER_QMC            = 0,
    SAMPLER_BEST_CANDIDATE = 1,
};


/// Choose what to execute in a scripted graph
enum ScriptExecuteType
{
    /// Default value
    SCRIPT_EX_NONE    = 0,
    /// Run the evaluation function again
    SCRIPT_EX_EVAL    = 1,
    /// Reinitialize the scripted graph
    SCRIPT_EX_INIT    = 2,
    /// Run only the onTrigger function in the graph.
    SCRIPT_EX_TRIGGER = 3
};


/// Type of a graphics API surface shared with Octane for input/output.
enum SharedSurfaceType
{
    /// No surface.
    SHARED_SURFACE_TYPE_NONE,
    /// A D3D11 texture (Windows only).
    SHARED_SURFACE_TYPE_D3D11,
};


/// How to align the shutter interval to the current time stamp
enum ShutterIntervalAlignment
{
    /// The shutter interval ends at the current time stamp
    SHUTTER_INTERVAL_BEFORE    = 1,
    /// The current time stamp is halfway the shutter interval
    SHUTTER_INTERVAL_SYMMETRIC = 2,
    /// The shutter interval starts at the current time stamp
    SHUTTER_INTERVAL_AFTER     = 3,
};


/// Simulated lenses
enum SimulatedLens
{
    /// 100mm film lens
    LENS_FILM_100MM = 2,
    /// 58mm f/1.5 portrait lens
    LENS_PORTRAIT_58MM = 3,
    /// 100mm Petzval lens
    LENS_PETZVAL_100MM = 4,
    /// 28mm f/2.8 wide angle
    LENS_WIDE_28MM = 5,
    /// 14.2mm f/2.8 fish eye
    LENS_FISHEYE_14MM = 6,
    /// 85mm Petzval lens
    LENS_PETZVAL_85MM = 7,
    /// 40mm f/2.0 film lens
    LENS_FILM_40MM = 8,
    /// 50mm f/1.25 lens
    LENS_LENS_50MM_F125 = 9,
    /// 58mm f/1.5 Double Gauss lens
    LENS_GAUSS_58MM = 10,
    /// 50mm f/1.4 lens
    LENS_LENS_50MM_F140 = 11,
    /// 50mm f/2.0 lens
    LENS_LENS_50MM_F200 = 12,
    /// 35mm f/2.8 retrofocus lens
    LENS_RETROFOCUS_35MM = 13,
    /// 16mm f/2.8 180deg fisheye
    LENS_FISHEYE_16MM = 14,
    /// 35mm f/1.8 lens
    LENS_LENS_35MM_F180 = 15,
    /// 31mm anastigmatic lens
    LENS_ANASTIGMATIC_31MM = 16,
    /// 100mm magnifying glass
    LENS_SIMPLE_100MM = 1,
};


/// Settings for spotlight orientation
enum SpotlightOrientation
{
    SPOTLIGHT_NORMAL  = 1,
    SPOTLIGHT_DIRECTION = 2,
    SPOTLIGHT_DIRECTION_OBJECT = 3,
    SPOTLIGHT_TARGET = 4,
    SPOTLIGHT_TARGET_OBJECT = 5,
};


/// Different stereo rendering modes we support for the thinlens camera.
enum StereoMode
{
    /// The view of the left and right eye are shifted to keep the target position in center.
    STEREO_MODE_OFF_AXIS = 1,
    /// The left and right eyes have the same orientation.
    STEREO_MODE_PARALLEL = 2,
};


/// The output for stereo rendering.
enum StereoOutput
{
    /// Stereo output is disabled.
    STEREO_OUTPUT_DISABLED     = 0,
    /// Stereo rendering for the left eye.
    STEREO_OUTPUT_LEFT_EYE     = 1,
    /// Stereo rendering for the right eye.
    STEREO_OUTPUT_RIGHT_EYE    = 2,
    /// Stereo rendering for both eyes (side-by-side, half horizontal resolution for each eye).
    STEREO_OUTPUT_SIDE_BY_SIDE = 3,
    /// Anaglyphic stereo rendering.
    STEREO_OUTPUT_ANAGLYPHIC   = 4,
    /// Stereo rendering for both eyes (top-bottom, half vertical resolution for each eye).
    STEREO_OUTPUT_OVER_UNDER   = 5,
};


/// Boundary interpolation rules used by the openSubdiv library.
/// see http://graphics.pixar.com/opensubdiv/docs/subdivision_surfaces.html#boundary-interpolation-rules
enum SubDivSchemeType
{
    SUBDIV_CATMARK         = 1,
    /// TRI_SUB_SMOOTH Triangle subdivision rule for Catmull-Clark subdivision
    SUBDIV_CATMARK_SMOOTH  = 4,
    SUBDIV_LOOP            = 2,
    SUBDIV_BILINEAR        = 3
};


/// Per-vertex interpolation rules used by the openSubdiv library.
/// see http://graphics.pixar.com/opensubdiv/docs/subdivision_surfaces.html#boundary-interpolation-rules
/// 
/// openSubdiv 2.x used the same enum for face-varying interpolation options, 3.x uses a separate
/// enum. See SubDivFVarInterpolateBoundary.
enum SubDivInterpolateBoundary
{
    SUBDIV_BOUNDARY_NONE          = 1,
    SUBDIV_BOUNDARY_EDGEONLY      = 2,
    SUBDIV_BOUNDARY_EDGEANDCORNER = 3,

    //-- Deprecated values

    /// @deprecated used by openSubdiv 2 for face-varying interpolation
    SUBDIV_BOUNDARY_ALWAYSSHARP   = 4,
};


/// Face-varying interpolation rules used by the openSubdiv library.
/// see http://graphics.pixar.com/opensubdiv/docs/subdivision_surfaces.html#face-varying-interpolation-rules
///
/// The weird mapping of SubDivInterpolateBoundary values is a consequence of the different
/// handling between openSubdiv 2.x and 3.x
/// see http://graphics.pixar.com/opensubdiv/docs/compatibility.html#compatibility-with-opensubdiv-2-x
enum SubDivFVarInterpolateBoundary
{
    SUBDIV_FVAR_LINEAR_NONE          = SUBDIV_BOUNDARY_EDGEONLY,
    // new option in OpenSubdiv 3
    SUBDIV_FVAR_LINEAR_CORNERS_ONLY  = 5,
    // OpenSubdiv 3 has two variants for this one, with rather non-descript names.
    // We keep the old way of using A_SUBD_FVR_PROPAGATE_CORNERS to distinguish those 2.
    SUBDIV_FVAR_LINEAR_CORNERS_PLUS  = SUBDIV_BOUNDARY_EDGEANDCORNER,
    SUBDIV_FVAR_LINEAR_BOUNDARIES    = SUBDIV_BOUNDARY_ALWAYSSHARP,
    SUBDIV_FVAR_LINEAR_ALL           = SUBDIV_BOUNDARY_NONE,
};


/// The subsampling modes we currently support.
enum SubSampleMode
{
    /// no sub/up-sampling
    SUBSAMPLEMODE_NONE = 1 << 0,

    /// sub-sampling modes
    SUBSAMPLEMODE_2X2  = 1 << 1,
    SUBSAMPLEMODE_4X4  = 1 << 2,
};


/// Compression type for TIFF file export.
enum TiffCompressionType
{
    /// no compression
    TIFF_COMPRESSION_NO_COMPRESSION = 1,
    /// zlib compression
    TIFF_COMPRESSION_DEFLATE        = 2,
    /// lzw compression
    TIFF_COMPRESSION_LZW            = 3,
    /// packbits compression
    TIFF_COMPRESSION_PACK_BITS      = 4
};


/// The tile patterns supported by NT_TEX_TILE_PATTERNS.
enum TilePatternType
{
    TILE_PATTERN_BRICKS      = 0,
    TILE_PATTERN_FANCY_TILES = 1,
    TILE_PATTERN_HEXAGONS    = 2,
    TILE_PATTERN_SCALES      = 3,
    TILE_PATTERN_TRIANGLES   = 4,
    TILE_PATTERN_VORONOI     = 5,
};


/// The different types of time events.
enum TimeEventType
{
    /// A root node graph was set to a different time.
    GRAPH_TIME_CHANGED      = 0,
    /// The total animated time interval of a root node graph has changed.
    GRAPH_INTERVAL_CHANGED  = 1,
    /// The rendered frame rate has changed.
    FRAME_RATE_CHANGED      = 2,
};


/// The different orders by which camera response curve, gamma and custom LUT are applied.
enum TonemapOrder
{
    TM_ORDER_RESPONSE_GAMMA_LUT = 0,
    TM_ORDER_GAMMA_RESPONSE_LUT = 1,
    TM_ORDER_LUT_RESPONSE_GAMMA = 2,
    TM_ORDER_LUT_GAMMA_RESPONSE = 3,
    TM_ORDER_RESPONSE_LUT_GAMMA = 4,
    TM_ORDER_GAMMA_LUT_RESPONSE = 5,
};


/// The different tonemap result buffer formats we support.
enum TonemapBufferType
{
    /// LDR tonemapping resulting in uint8_t per channel (should only be used when outputting in a
    /// non-linear color space).
    TONEMAP_BUFFER_TYPE_LDR = 0,
    /// HDR tonemapping resulting in float per channel.
    TONEMAP_BUFFER_TYPE_HDR_FLOAT = 1,
    /// Same as TONEMAP_BUFFER_TYPE_HDR_FLOAT but the results are converted to half (16-bit)
    /// floating point. This is only supported on macOS/iOS.
    TONEMAP_BUFFER_TYPE_HDR_HALF = 2,

    TONEMAP_BUFFER_TYPE_COUNT
};


/// Lighting modes for toon materials
enum ToonLightMode
{
    /// Use toon light sources
    TOON_LIGHT_SOURCES  = 0,
    /// Use camera light source
    TOON_LIGHT_CAMERA = 1
};


/// The types of light path bounce that can occur at a geometry object for the purposes of updating
/// the set of trace sets that are visible for future hits in the path.
///
/// These values are used as bit indices for bit masks in NT_TRACE_SET_VISIBILITY_RULE nodes.
enum TraceSetBounceType
{
    /// Specular (or glossy) reflection bounces.
    TRACE_SET_BOUNCE_TYPE_REFLECTION = 0,
    /// Specular (or glossy) transmission bounces.
    TRACE_SET_BOUNCE_TYPE_REFRACTION = 1,
    /// Diffuse bounces (reflection or transmission).
    TRACE_SET_BOUNCE_TYPE_DIFFUSE = 2,
    /// Direct light bounces (also used for ambient occlusion).
    TRACE_SET_BOUNCE_TYPE_SHADOW = 3,

    TRACE_SET_BOUNCE_TYPE_COUNT = 4
};


/// The types of geometry hit that can occur in a light path after a bounce that updated the set of
/// visible trace sets.
///
/// These values are used as bit indices for bit masks in NT_TRACE_SET_VISIBILITY_RULE nodes.
enum TraceSetFutureHits
{
    /// The very next hit after the bounce in question.
    TRACE_SET_FUTURE_HITS_NEXT_HIT = 0,
    /// All hits after the bounce in question, except for the very next one.
    TRACE_SET_FUTURE_HITS_HITS_AFTER_NEXT_HIT = 1,

    TRACE_SET_FUTURE_HITS_COUNT = 2
};


/// UI general operation flags 
enum UIOperationsFlag
{
    UI_OPERATION_DELETABLE = 1 << 0,
    UI_OPERATION_RENAMABLE = 1 << 2,
    UI_OPERATION_ALL       = UI_OPERATION_DELETABLE | UI_OPERATION_RENAMABLE
};


/// Unary math operations for nodes NT_TEX_MATH_UNARY and NT_FLOAT_MATH_UNARY.
enum UnaryOperation
{
    UNARY_OP_ABS          = 0,
    UNARY_OP_ACOS         = 1,
    UNARY_OP_ASIN         = 2,
    UNARY_OP_ATAN         = 3,
    UNARY_OP_CEIL         = 4,
    UNARY_OP_COS          = 5,
    UNARY_OP_COSH         = 6,
    UNARY_OP_DEGREES      = 7,
    UNARY_OP_EXP          = 8,
    UNARY_OP_EXP2         = 9,
    UNARY_OP_EXPM1        = 10,
    UNARY_OP_FLOOR        = 11,
    UNARY_OP_FRAC         = 12,
    UNARY_OP_INVERSE_SQRT = 13,
    UNARY_OP_INVERT       = 14,
    UNARY_OP_LENGTH       = 30,
    UNARY_OP_LOG          = 15,
    UNARY_OP_LOG2         = 16,
    UNARY_OP_LOG10        = 17,
    UNARY_OP_LOGB         = 18,
    UNARY_OP_NEGATE       = 19,
    UNARY_OP_NORMALIZE    = 31,
    UNARY_OP_RADIANS      = 20,
    UNARY_OP_RECIPROCAL   = 21,
    UNARY_OP_ROUND        = 22,
    UNARY_OP_SIGN         = 23,
    UNARY_OP_SIN          = 24,
    UNARY_OP_SINH         = 25,
    UNARY_OP_SQRT         = 26,
    UNARY_OP_TAN          = 27,
    UNARY_OP_TANH         = 28,
    UNARY_OP_TRUNC        = 29,
};


/// The aperture shapes available for the universal camera.
enum UniversalCamApertureShape
{
    UNIVERSAL_CAM_APERTURE_CIRCULAR  = 1,
    UNIVERSAL_CAM_APERTURE_POLYGONAL = 2,
    UNIVERSAL_CAM_APERTURE_NOTCHED   = 3,
    UNIVERSAL_CAM_APERTURE_CUSTOM    = 4,
};


/// The cubemap layouts available for the universal camera.
enum UniversalCamCubemapLayout
{
    UNIVERSAL_CAM_CUBEMAP_6X1 = 1,
    UNIVERSAL_CAM_CUBEMAP_3X2 = 2,
    UNIVERSAL_CAM_CUBEMAP_2X3 = 3,
    UNIVERSAL_CAM_CUBEMAP_1X6 = 4,
};


/// The projection types available for the universal camera fisheye.
enum UniversalCamFisheyeProjection
{
    UNIVERSAL_CAM_FISHEYE_STEREOGRAPHIC = 1,
    UNIVERSAL_CAM_FISHEYE_EQUIDISTANT   = 2,
    UNIVERSAL_CAM_FISHEYE_EQUISOLID     = 3,
    UNIVERSAL_CAM_FISHEYE_ORTHOGRAPHIC  = 4,
};


/// The fisheye types available for the universal camera.
enum UniversalCamFisheyeType
{
    UNIVERSAL_CAM_FISHEYE_CIRCULAR   = 1,
    UNIVERSAL_CAM_FISHEYE_FULL_FRAME = 2,
};


/// The modes of the universal camera.
enum UniversalCamMode
{
    UNIVERSAL_CAM_THINLENS        = 1,
    UNIVERSAL_CAM_ORTHOGRAPHIC    = 2,
    UNIVERSAL_CAM_FISHEYE         = 3,
    UNIVERSAL_CAM_EQUIRECTANGULAR = 4,
    UNIVERSAL_CAM_CUBEMAP         = 5,
};


/// The upsampling modes we currently support.
enum UpSampleMode
{
    /// no up-sampling
    UPSAMPLEMODE_NONE = 1 << 0,

    /// up-sampling modes
    UPSAMPLEMODE_2X2  = 1 << 1,
    UPSAMPLEMODE_4X4  = 1 << 2,
};


/// Supported up sampler types.
enum UpSamplerType
{
    // None.
    UPSAMPLER_NONE       = 0,
    // Linearly up-scale input image/buffer.
    UPSAMPLER_LINEAR     = 1,
    // The old AI up-sampler.
    UPSAMPLER_LEGACY_AI  = 2,
    // DLSS from nvidia. Upscaling and denoising are enabled.
    // Ray reconstruction nor frame generation are not enabled.
    UPSAMPLER_DLSS       = 3,
    // DLSS from nvidia. Upscaling, denoising and ray reconstruction are enabled.
    // Frame generation is not enabled.
    UPSAMPLER_DLSS_RR    = 4,
    // FSR3 from AMD's fidelity-fx sdk. Upscaling and denoising are enabled.
    // Frame interpolation(generation) is not enabled.
    UPSAMPLER_FSR        = 5,
};


/// Up sample's source percentage (per side).
enum UpSampleSourcePercentage
{
    // 100%
    UPSAMPLE_SOURCE_PERCENTAGE_100,
    // 66.66% (2/3)
    UPSAMPLE_SOURCE_PERCENTAGE_66,
    // 50%
    UPSAMPLE_SOURCE_PERCENTAGE_50,
    // 33.33% (1/3)
    UPSAMPLE_SOURCE_PERCENTAGE_33,
    // 25%
    UPSAMPLE_SOURCE_PERCENTAGE_25,
};


/// The types of USD display purposes.
enum UsdDisplayPurpose
{
    // A prim with purpose "render" are generally used for a final quality render.
    USD_DISPLAY_PURPOSE_RENDER = 1 << 0,
    // A prim with purpose "proxy" are generally used for a light weight render for testing.
    USD_DISPLAY_PURPOSE_PROXY  = 1 << 1,
    // A prim with purpose "guides" are generally used to display helper guides.
    // support to the guides are limited in octane.
    USD_DISPLAY_PURPOSE_GUIDE  = 1 << 2,
};


/// Grid channels that can be read from a VDB
enum VdbGridIds
{
    VDB_GRID_USE_NAME   = 0,
    VDB_GRID_SCATTER    = 1,
    VDB_GRID_ABSORPTION = 2,
    VDB_GRID_EMISSION   = 3,
    VDB_GRID_VELOCITY_X = 4,
    VDB_GRID_VELOCITY_Y = 5,
    VDB_GRID_VELOCITY_Z = 6,
    /// Read the velocity as a vector.
    VDB_GRID_VELOCITY   = 7,
};


/// Circle type for Vectron cylinder and sphere.
enum VectronCircleType
{
    CIRCLE_TYPE_CIRCLE  = 0,
    CIRCLE_TYPE_SLICE   = 1,
    CIRCLE_TYPE_SEGMENT = 2,
    CIRCLE_TYPE_ARC     = 3,
};


/// Edge type for SDF primitives.
enum VectronEdgeType
{
    /// No fillet or chamfer.
    EDGE_TYPE_SHARP   = 0,
    /// Fillet (round).
    EDGE_TYPE_FILLET  = 1,
    /// Chamfer.
    EDGE_TYPE_CHAMFER = 2,
};


/// Virtual texturing modes
enum VirtualTexturingMode
{
    /// Image is not loaded as LOD tiles
    VIRTUAL_TEX_OFF = 0,
    /// Image is loaded as LOD tiles, with scaling suitable for albedo
    VIRTUAL_TEX_ALBEDO = 1,
    /// Image is loaded as LOD tiles, with scaling suitable for normal maps
    VIRTUAL_TEX_NORMALS = 2,
};


/// Standard volume emission types.
enum VolumeEmissionType
{
    VOLUME_EMISSION_NONE       = 0,
    VOLUME_EMISSION_CHANNEL    = 1,
    VOLUME_EMISSION_DENSITY    = 2,
    VOLUME_EMISSION_BLACK_BODY = 3,
};


/// Volume voxel data interpolation modes.
enum VolumeInterpolationType
{
    VOLUME_INTERPOLATION_CLOSEST   = 0,
    VOLUME_INTERPOLATION_TRILINEAR = 1,
    VOLUME_INTERPOLATION_TRICUBIC  = 2,
};


/// Volume sampling methods.
enum VolumeSampling
{
    /// Originally, volume rendered with artefacts very often when overlapped.
    VOLUME_SAMPLING_LEGACY   = 0,
    /// A new method was introduced, which behaved better with overlaps, but was harder
    /// to control especially for scattering.
    VOLUME_SAMPLING_2018     = 1,
    /// A newer method was introduced, which combines the better overlap behaviors,
    /// with scattering that was easier to control.
    VOLUME_SAMPLING_IMPROVED = 2,
};


/// Waveforms supported by NT_TEX_WAVE_PATTERN.
enum Waveform
{
    WAVEFORM_SINE   = 0,
    WAVEFORM_SQUARE = 1,
    WAVEFORM_SAW    = 2,
};


/// The different border modes supported by the 'W coordinate' texture node (NT_TEX_W). The value is
/// set by the enum pin P_BORDER_MODE_W_COORD.
enum WCoordinateBorderMode
{
    /// The W coordinate value is passed through unchanged.
    W_COORDINATE_BORDER_MODE_NONE   = 0,
    /// W coordinate values outside of [0,1] are wrapped so the output falls into this range.
    W_COORDINATE_BORDER_MODE_WRAP   = 1,
    /// W coordinate values outside of [0,1] are mapped into that range such that adjacent values
    /// mirror each other, e.g. a value of 1.01 is mapped to 0.99.
    W_COORDINATE_BORDER_MODE_MIRROR = 2,
    /// The W coordinate is clamped to range [0,1].
    W_COORDINATE_BORDER_MODE_CLAMP  = 3,
};


/// Different light spectra that can be considered "white" inside the rendering engine.
enum WhiteLightSpectrum
{
    /// A flat light spectrum.
    WHITE_LIGHT_SPECTRUM_FLAT = 0,
    /// A D65 daylight spectrum.
    WHITE_LIGHT_SPECTRUM_D65 = 1,
};


/// Polygon winding order.
enum WindingOrder
{
    WINDING_COUNTERCLOCKWISE = 1,
    WINDING_CLOCKWISE        = 2,
    // If set the winding order will be loaded from the geometry file.
    WINDING_AUTO             = 3
};


//--------------------------------------------------------------------------------------------------
// Scatter modules
// NOTE: The following enums are copy-pasted from scattersurfaceenums.h and scattervolumeenums.h.

//--------------------
// ScatterSurface

/// Scatter modes supported for scattering on polygons in the Scatter on surface node.
enum ScatterSurfacePolygonMode
{
    SCATTER_SURFACE_POLYGON_MODE_VERTICES,
    SCATTER_SURFACE_POLYGON_MODE_CENTERS,
    SCATTER_SURFACE_POLYGON_MODE_BYAREA,
    SCATTER_SURFACE_POLYGON_MODE_BYDENSITYMAP,
    SCATTER_SURFACE_POLYGON_MODE_EDGEPOSITION,
    SCATTER_SURFACE_POLYGON_MODE_EDGESPACING,
    SCATTER_SURFACE_POLYGON_MODE_DISABLED,
};


/// Scatter modes supported for scattering on particles in the Scatter on surface node.
enum ScatterSurfaceParticleMode
{
    SCATTER_SURFACE_PARTICLE_MODE_CENTERS,
    SCATTER_SURFACE_PARTICLE_MODE_DISABLED,
};


/// Scatter modes supported for scattering on hairs in the Scatter on surface node.
enum ScatterSurfaceHairMode
{
    SCATTER_SURFACE_HAIR_MODE_VERTICES,
    SCATTER_SURFACE_HAIR_MODE_POSITION,
    SCATTER_SURFACE_HAIR_MODE_SPACING,
    SCATTER_SURFACE_HAIR_MODE_DISABLED,
};


/// Selection strategy used when scattering multiple source objects on a surface.
enum ScatterSurfaceSelectionMode
{
    SCATTER_SURFACE_SELECTION_MODE_SEQUENTIAL,
    SCATTER_SURFACE_SELECTION_MODE_RANDOM,
    SCATTER_SURFACE_SELECTION_MODE_MAP,
};


/// Orientation priority used for orienting scattered instances on a surface when their up and front
/// vectors are not orthogonal.
enum ScatterSurfaceOrientationPriority
{
    SCATTER_SURFACE_ORIENTATION_PRIORITY_UP,
    SCATTER_SURFACE_ORIENTATION_PRIORITY_FRONT,
};


/// Type of reference data used to orient instances up or front vectors when scattering on a surface.
enum ScatterSurfaceReferenceType
{
    SCATTER_SURFACE_REFERENCE_TYPE_DIRECTION,
    SCATTER_SURFACE_REFERENCE_TYPE_POINT,
};


/// Type of transform applied to instances scattered on surfaces.
enum ScatterSurfaceTransformType
{
    SCATTER_SURFACE_TRANSFORM_TYPE_FIXED,
    SCATTER_SURFACE_TRANSFORM_TYPE_RANDOM_INDEPENDENT,
    SCATTER_SURFACE_TRANSFORM_TYPE_RANDOM_COUPLED,
    SCATTER_SURFACE_TRANSFORM_TYPE_MAP,
};


//--------------------
// ScatterVolume

/// Selection strategy used when scattering multiple source objects in a volume.
enum ScatterVolumeSelectionMode
{
    SCATTER_VOLUME_SELECTION_MODE_SEQUENTIAL,
    SCATTER_VOLUME_SELECTION_MODE_RANDOM,
    SCATTER_VOLUME_SELECTION_MODE_MAP,
};


/// Shaping function used to sculpt the dense grid of instances for scatter in volume.
enum ScatterVolumeShape
{
    SCATTER_VOLUME_SHAPE_BOX,
    SCATTER_VOLUME_SHAPE_SPHERE,
    SCATTER_VOLUME_SHAPE_CYLINDER,
    SCATTER_VOLUME_SHAPE_CONE,
};


/// Orientation priority used for orienting scattered instances when their up and front vectors are
/// not orthogonal.
enum ScatterVolumeOrientationPriority
{
    SCATTER_VOLUME_ORIENTATION_PRIORITY_UP,
    SCATTER_VOLUME_ORIENTATION_PRIORITY_FRONT,
};


/// Type of reference data used to orient instances up or front vectors when scattering.
enum ScatterVolumeReferenceType
{
    SCATTER_VOLUME_REFERENCE_TYPE_DIRECTION,
    SCATTER_VOLUME_REFERENCE_TYPE_POINT,
};


/// Type of transform applied to instances scattered on surfaces.
enum ScatterVolumeTransformType
{
    SCATTER_VOLUME_TRANSFORM_TYPE_FIXED,
    SCATTER_VOLUME_TRANSFORM_TYPE_RANDOM_INDEPENDENT,
    SCATTER_VOLUME_TRANSFORM_TYPE_RANDOM_COUPLED,
    SCATTER_VOLUME_TRANSFORM_TYPE_MAP,
};


};  //namespace Octane


#endif  // #ifndef _OCTANEENUMS_H_
