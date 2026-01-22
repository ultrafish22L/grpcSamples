// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_UTIL_H_
#define _OCTANE_WRAP_UTIL_H_    1

// system includes
#include <vector>
// api includes
#include "apiarray.h"

//--------------------------------------------------------------------------------------------------
/// In debug builds (NDEBUG not defined) of the module this will check the condition. When the
/// condition is false, this will log out an error and assert. In release builds (NDEBUG) it will
/// be compiled out.
#ifndef NDEBUG
#   define OCTANE_API_ASSERT(condition, fmt, ...) OctaneWrap::__debugAssert(__FILE__, __LINE__, (condition), (fmt), ##__VA_ARGS__)
#else
#   define OCTANE_API_ASSERT(condition, fmt, ...)
#endif

/// Determines the size of a 1D C array in elements.
#define ARRAY_WIDTH(a)  (sizeof(a) / sizeof(a[0]))


namespace OctaneWrap
{


//--------------------------------------------------------------------------------------------------
/// This header contains various utility functions that *should* make dealing with the API from 
/// within the module easier.


/// Converts a std::vector<T> into an Octane::ApiArray<T>.
template <typename T>
inline Octane::ApiArray<T> fromVector(
    const std::vector<T> &vec)
{
    return Octane::ApiArray<T>(vec.data(), vec.size());
}


/// Converts an Octane::ApiArray<T> into a std::vector<T>.
template <typename T>
inline std::vector<T> toVector(
    const Octane::ApiArray<T> &array)
{
    return std::vector<T>(array.mData, array.mData + array.mSize);
}


/// Deletes a pointer and assigns null to it.
template <typename T>
inline void deleteAndZero(
    T *&ptr)
{
    delete ptr;
    ptr = NULL;
}


/// Clamps v between [min .. max].
template <class T>
inline T clamp(
    const T v,
    const T minV,
    const T maxV)
{
    return (v < minV) ? minV : ((v > maxV) ? maxV : v);
}


/// Wrapped via API_ASSERT, you should not use this directly.
void __debugAssert(
    const char *filename,
    const int  lineNb,
    const bool condition,
    const char *fmt,
    ...);

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_UTIL_H_
