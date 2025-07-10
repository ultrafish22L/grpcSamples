// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_TYPES_H_
#define _OCTANE_TYPES_H_ 1


#ifdef _WIN32
// Make sure cmath and cstdint define macros we rely on.
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
// visual C++ requires math.h, instead of cmath for M_PI etc.
#include <math.h>
#endif

// system includes
#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>



//--------------------------------------------------------------------------------------------------
// Unclutter the global namespace.

#ifdef min
#   undef min
#endif
#ifdef max
#   undef max
#endif

// sanity check
#ifndef INT32_MAX
#   error "cstdint was included, but didn't define limit macros"
#endif
#ifndef M_PI
#   error "cmath was included, but didn't define M_PI"
#endif



//--------------------------------------------------------------------------------------------------
// Our own, cross-platform, absolute value functions


inline int16_t oabs(const int16_t x) { return (int16_t)abs((int)x); }
inline int32_t oabs(const int32_t x) { return (int32_t)abs((int)x); }
inline float   oabs(const float   x) { return fabs(x); }
inline double  oabs(const double  x) { return fabs(x); }


// cross-platform isfinite function
inline bool oisfinite(
    const float x)
{
#if defined(_MSC_VER) && _MSC_VER < 1900
    return (_finitef(x) != 0);
#else
    return std::isfinite(x);
#endif // defined(_MSC_VER) && _MSC_VER <= 1600
}


inline bool oisfinite(
    const double x)
{
#if defined(_MSC_VER) && _MSC_VER < 1900
    return (_finite(x) != 0);
#else
    return std::isfinite(x);
#endif
}



//--------------------------------------------------------------------------------------------------
/// OCTANEAPI_DECL is used to decorate API functions which are then either exported or imported -
/// depending on which side of the API you are operating.
#if defined(_WIN32)
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#   if defined(OCTANE_DLLEXPORT) || defined(OCTANE_STANDALONE)
#       define OCTANEAPI_DECL __declspec(dllexport)
#   else
#       define OCTANEAPI_DECL __declspec(dllimport)
#   endif
#elif defined(__GNUC__) || defined(__clang__)
#   if defined(OCTANE_DLLEXPORT) || defined(OCTANE_STANDALONE)
#       define OCTANEAPI_DECL __attribute__ ((visibility("default")))
#   else
#       define OCTANEAPI_DECL
#   endif
#endif



//--------------------------------------------------------------------------------------------------
/// Used to indicate deprecated functions, classes, types.
#ifdef _WIN32
#   define OCTANE_DEPRECATED __declspec(deprecated)
#else
#   define OCTANE_DEPRECATED __attribute__((deprecated))
#endif



//--------------------------------------------------------------------------------------------------
/// Instances of classes with this macro in the declaration can't by copied.
#define OCTANEAPI_NO_COPY(classType)                                                            \
    private: classType(const classType &other);                                                 \
             void operator=(const classType &other);


namespace Octane
{



//--------------------------------------------------------------------------------------------------
// Platform independent types


typedef uint8_t  bool_t;
typedef int32_t  enum_t;
typedef uint16_t half_t;

/// The type used to store a plugin id.
typedef int32_t ModuleIdT;

/// The data type used for tracking change levels.
typedef uint64_t CLevelT;



} // namespace Octane



#endif // #ifndef _OCTANE_TYPES_H_
