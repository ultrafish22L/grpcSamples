// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"

#ifdef OCTANE_INTERNAL
#include "color/ocioconfig.h"
#endif


namespace Octane
{

/// Represents a loaded OCIO config, and allows access to the roles, color spaces, displays and
/// looks it defines.
class OCTANEAPI_DECL ApiOcioConfig final
{
public:

    /// Loads an OCIO config. This method may take a few seconds or more to execute.
    ///
    /// @param filename
    ///     The filename of the config file to load, or null to use the OCIO environment variable.
    /// @return
    ///     The loaded config (must be destroyed with destroy()), or null if loading failed.
    static ApiOcioConfig *create(
        const char *filename);


    void destroy();

    /// @return
    ///     The cloned OCIO config (must be destroyed with destroy()). Will not be null.
    ApiOcioConfig *clone() const;

    /// Gets the number of roles in the config.
    size_t getRoleCount() const;

    /// Gets the name of a role.
    ///
    /// @param roleIndex
    ///     The index of the role. Must be less than getRoleCount().
    /// @return
    ///     The name of the role. Will not be null. This pointer remains valid until this object is
    ///     destroyed.
    const char *getRoleName(
        size_t roleIndex) const;

    /// Gets the name of the color space for which a role is an alias.
    ///
    /// @param roleIndex
    ///     The index of the role. Must be less than getRoleCount().
    /// @return
    ///     The name of the color space for which the role is an alias. Will not be null. This
    ///     pointer remains valid until this object is destroyed.
    const char *getRoleColorSpaceName(
        size_t roleIndex) const;

    /// Gets the number of color spaces in the config.
    size_t getColorSpaceCount() const;

    /// Gets the name of a color space.
    ///
    /// @param colorSpaceIndex
    ///     The index of the color space. Must be less than getColorSpaceCount().
    /// @return
    ///     The name of the color space. Will not be null. This pointer remains valid until this
    ///     object is destroyed.
    const char *getColorSpaceName(
        size_t colorSpaceIndex) const;

    /// Gets the number of components the family of a color space has.
    ///
    /// @param colorSpaceIndex
    ///     The index of the color space. Must be less than getColorSpaceCount().
    /// @return
    ///     The number of components the family of the color space has.
    size_t getColorSpaceFamilyComponentCount(
        size_t colorSpaceIndex) const;

    /// Gets a component of the family of a color space.
    ///
    /// @param colorSpaceIndex
    ///     The index of the color space. Must be less than getColorSpaceCount().
    /// @param familyComponentIndex
    ///     The index of the family component. Must be less than
    ///     getColorSpaceFamilyComponentCount(colorSpaceIndex).
    /// @return
    ///     The family component. Will not be null. This pointer remains valid until this object is
    ///     destroyed.
    const char *getColorSpaceFamilyComponent(
        size_t colorSpaceIndex,
        size_t familyComponentIndex) const;

    /// Gets the number of displays in the config.
    size_t getDisplayCount() const;

    /// Gets the name of a display.
    ///
    /// @param displayIndex
    ///     The index of the display. Must be less than getDisplayCount().
    /// @return
    ///     The name of the display. Will not be null. This pointer remains valid until this object
    ///     is destroyed.
    const char *getDisplayName(
        size_t displayIndex) const;

    /// Gets the number of views a display has.
    ///
    /// @param displayIndex
    ///     The index of the display. Must be less than getDisplayCount().
    /// @return
    ///     The number of views the display has.
    size_t getDisplayViewCount(
        size_t displayIndex) const;

    /// Gets the name of a view.
    ///
    /// @param displayIndex
    ///     The index of the display. Must be less than getDisplayCount().
    /// @param viewIndex
    ///     The index of the view. Must be less than getDisplayViewCount(displayIndex).
    /// @return
    ///     The name of the view. Will not be null. This pointer remains valid until this object is
    ///     destroyed.
    const char *getDisplayViewName(
        size_t displayIndex,
        size_t viewIndex) const;

    /// Gets the number of looks in the config.
    size_t getLookCount() const;

    /// Gets the name of a look.
    ///
    /// @param lookIndex
    ///     The index of the look. Must be less than getLookCount().
    /// @return
    ///     The name of the look. Will not be null. This pointer remains valid until this object is
    ///     destroyed.
    const char *getLookName(
        size_t lookIndex) const;


#ifdef OCTANE_INTERNAL
    static ApiOcioConfig *createFromConfig(
        std::shared_ptr<const OcioConfig> config);


    std::shared_ptr<const OcioConfig> getConfig() const;
#endif


private:

    ApiOcioConfig();

    ApiOcioConfig(
        const ApiOcioConfig &other);

    ApiOcioConfig &operator=(
        const ApiOcioConfig &other);

    ~ApiOcioConfig();

};

}
