// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef OCTANEVERSION_H_
#define OCTANEVERSION_H_

#if !defined(__CUDACC__) && !defined(__GLSL__)
# include <cstdint>
#endif


// on MacOS and IOS, it is now known as Octane X. Everywhere else, it is still known as 
// OctaneRender.
#if defined(__APPLE__)
# define OCTANE_PRODUCT_NAME "Octane X"
#else
# define OCTANE_PRODUCT_NAME "OctaneRender"
#endif


/// The official version string.
#define OCTANE_VERSION_STRING   "2026.1 Alpha 5"

/// The copyright string used in octane.rc
#define OCTANE_COPYRIGHT_YEARS_STRING "2010-2025"

/// The major part of the current Octane version.
#define OCTANE_VERSION_MAJOR    15
/// The minor part of the current Octane version.
#define OCTANE_VERSION_MINOR    0
/// The patch level of the current Octane version.
#define OCTANE_VERSION_PATCH    0
/// The revision of the current Octane version.
#define OCTANE_VERSION_REVISION 5

/// The version number used in the Windows resource files.
#define OCTANE_WINRC_VERSION    OCTANE_VERSION_MAJOR,OCTANE_VERSION_MINOR,OCTANE_VERSION_PATCH,OCTANE_VERSION_REVISION
/// Calculates the version number from octane version numbers. Please note that 
/// the factors here are used in CMakeLists as well, in case they ever change.
#define OCS_VERSION(MAJOR, MINOR, PATCH, REVISION) (MAJOR * 1000000u + MINOR * 10000u + PATCH * 100u + REVISION)

/// The current Octane version number.
#define OCTANE_VERSION      OCS_VERSION(OCTANE_VERSION_MAJOR, OCTANE_VERSION_MINOR, OCTANE_VERSION_PATCH, OCTANE_VERSION_REVISION)


#ifndef __GLSL__
namespace Octane
{
#if __cpp_constexpr
#define OCT_CONSTEXPR constexpr
#else
#define OCT_CONSTEXPR
#endif


/// The type that is used to store an Octane version.
typedef uint32_t VersionT;


/// Calculates the version number from the major, minor, patch and revision parts.
#ifdef __CUDACC__
__device__
#endif
inline OCT_CONSTEXPR Octane::VersionT ocsVersion(
    const uint32_t major,
    const uint32_t minor,
    const uint32_t patch = 0,
    const uint32_t revision = 0)
{
    return OCS_VERSION(major, minor, patch, revision);
}


inline OCT_CONSTEXPR uint32_t getVersionMajor   (const Octane::VersionT version)  { return version / 1000000u; }
inline OCT_CONSTEXPR uint32_t getVersionMinor   (const Octane::VersionT version)  { return (version / 10000u) % 100u; }
inline OCT_CONSTEXPR uint32_t getVersionPatch   (const Octane::VersionT version)  { return (version / 100u) % 100u; }
inline OCT_CONSTEXPR uint32_t getVersionRevision(const Octane::VersionT version)  { return version % 100u; }

#undef OCT_CONSTEXPR

} // namespace Octane

  /// Version value used as placeholder if the beginngin of a version
  /// range precedes the introduction of that range.
# define OCTANE_VERSION_DAWN_OF_TIME  ((Octane::VersionT)0)
  /// The maximum version possible.
# define OCTANE_MAX_VERSION  (~(Octane::VersionT)0)

#endif  // #ifndef __GLSL__


#endif // #ifndef __OCTANEVERSION_H__
