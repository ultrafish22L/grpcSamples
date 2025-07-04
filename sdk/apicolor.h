// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_COLOR_H_
#define _API_COLOR_H_   1

#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Represents a RGBA color.
template <typename T>
struct OCTANEAPI_DECL ApiColor
{
    T b;
    T g;
    T r;
    T a;

    inline ApiColor(
        const T r,
        const T g,
        const T b,
        const T a);
};


template <typename T>
inline ApiColor<T>::ApiColor(
    const T r,
    const T g,
    const T b,
    const T a)
:
    b(b), g(g), r(r), a(a)
{}


// types
typedef ApiColor<unsigned char> ApiColorLdr;
typedef ApiColor<float>         ApiColorHdr;


} // namespace Octane


#endif // #ifndef _API_COLOR_H_
