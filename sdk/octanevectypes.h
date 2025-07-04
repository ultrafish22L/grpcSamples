// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANEVECTYPES_H_
#define _OCTANEVECTYPES_H_ 1

// system includes
#include <algorithm>
#include <cmath>
#include <functional>
// library includes
#include "octanetypes.h"



// The vector types:
namespace OctaneVec
{


//--------------------------------------------------------------------------------------------------
/// Generic 2D vector class, which has the properties of a plain old data type.
template <class ST>
struct Vec2
{
    typedef ST ScalarT;

    static const uint32_t DIM_COUNT = 2;

    ST x;
    ST y;

    /// Creates an instance initializing all coordinates with the provided value
    static inline Vec2 makeWith(
        const ST val);

    /// Creates an instance initialized with (x, y).
    static inline Vec2 make(
        const ST x = 0,
        const ST y = 0);

    /// Creates an instance initialized with (v[0], v[1]).
    static inline Vec2 make(
        const ST *const v);

    /// Returns (0, 0).
    static inline Vec2 zero();

    /// Returns (1, 1).
    static inline Vec2 one();


    /// Sets all components of the vector.
    inline void set(
        const ST x,
        const ST y);

    /// Const access to a scalar value via the index of its dimension.
    inline ST operator[](
        const unsigned int dimIx) const;

    /// Non-const access to a scalar value via the index of its dimension.
    inline ST& operator[](
        const unsigned int dimIx);

    /// Returns a const pointer to the first element of the vector.
    inline const ST* ptr() const;

    /// Returns a non-const pointer to the first element of the vector.
    inline ST* ptr();

    /// Returns TRUE if this vector is equal to the other vector.
    inline bool operator==(
        const Vec2 other) const;

    /// Returns TRUE if this vector is not equal to the other vector.
    inline bool operator!=(
        const Vec2 other) const;

    /// Casts this vector to another scalar type, using standard C casts
    template <class OT>
    inline Vec2<OT> cast() const;
};


typedef Vec2<uint8_t>  uint8_2;
typedef Vec2<uint16_t> uint16_2;
typedef Vec2<uint32_t> uint32_2;
typedef Vec2<uint64_t> uint64_2;
typedef Vec2<int8_t>   int8_2;
typedef Vec2<int16_t>  int16_2;
typedef Vec2<int32_t>  int32_2;
typedef Vec2<int64_t>  int64_2;
typedef Vec2<float>    float_2;
typedef Vec2<double>   double_2;



//--------------------------------------------------------------------------------------------------
/// Generic 3D vector class, which has the properties of a plain old data type.
template <class ST>
struct Vec3
{
    typedef ST ScalarT;

    static const uint32_t DIM_COUNT = 3;

    ST x;
    ST y;
    ST z;

    /// Creates an instance initializing all coordinates with the provided value
    static inline Vec3 makeWith(
        const ST val);

    /// Creates an instance initialized with (x, y, z).
    static inline Vec3 make(
        const ST x = 0,
        const ST y = 0,
        const ST z = 0);

    /// Creates an instance initialized with (v[0], v[1], v[2]).
    static inline Vec3 make(
        const ST *const v);

    /// Returns (0, 0, 0).
    static inline Vec3 zero();

    /// Returns (1, 1, 1).
    static inline Vec3 one();


    /// Sets all components of the vector.
    inline void set(
        const ST x,
        const ST y,
        const ST z);

    /// Const access to a scalar value via the index of its dimension.
    inline ST operator[](
        const unsigned int dimIx) const;

    /// Non-const access to a scalar value via the index of its dimension.
    inline ST& operator[](
        const unsigned int dimIx);

    /// Returns a const pointer to the first element of the vector.
    inline const ST* ptr() const;

    /// Returns a non-const pointer to the first element of the vector.
    inline ST* ptr();

    inline const Vec2<ST> & xy() const;

    inline Vec2<ST> & xy();

    /// Returns TRUE if this vector is equal to the other vector.
    inline bool operator==(
        const Vec3 other) const;

    /// Returns TRUE if this vector is not equal to the other vector.
    inline bool operator!=(
        const Vec3 other) const;

    /// Casts this vector to another scalar type, using standard C casts
    template <class OT>
    inline Vec3<OT> cast() const;
};


typedef Vec3<uint8_t>  uint8_3;
typedef Vec3<uint16_t> uint16_3;
typedef Vec3<uint32_t> uint32_3;
typedef Vec3<uint64_t> uint64_3;
typedef Vec3<int8_t>   int8_3;
typedef Vec3<int16_t>  int16_3;
typedef Vec3<int32_t>  int32_3;
typedef Vec3<int64_t>  int64_3;
typedef Vec3<float>    float_3;
typedef Vec3<double>   double_3;



//--------------------------------------------------------------------------------------------------
/// Generic 4D vector class, which has the properties of a plain old data type.
template <class ST>
struct Vec4
{
    typedef ST ScalarT;

    static const uint32_t DIM_COUNT = 4;

    ST x;
    ST y;
    ST z;
    ST w;

    /// Creates an instance initializing all coordinates with the provided value
    static inline Vec4 makeWith(
        const ST val);

    /// Creates an instance initialized with (x, y, z, w).
    static inline Vec4 make(
        const ST x = 0,
        const ST y = 0,
        const ST z = 0,
        const ST w = 0);

    /// Creates an instance initialized with (v[0], v[1], v[2], v[3]).
    static inline Vec4 make(
        const ST *const v);

    /// Returns (0, 0, 0, 0).
    static inline Vec4 zero();

    /// Returns (1, 1, 1, 1).
    static inline Vec4 one();


    /// Sets all components of the vector.
    inline void set(
        const ST x,
        const ST y,
        const ST z,
        const ST w);

    /// Const access to a scalar value via the index of its dimension.
    inline ST operator[](
        const unsigned int dimIx) const;

    /// Non-const access to a scalar value via the index of its dimension.
    inline ST& operator[](
        const unsigned int dimIx);

    /// Returns a const pointer to the first element of the vector.
    inline const ST* ptr() const;

    /// Returns a non-const pointer to the first element of the vector.
    inline ST* ptr();

    inline const Vec2<ST> & xy() const;

    inline Vec2<ST> & xy();

    inline const Vec3<ST> & xyz() const;

    inline Vec3<ST> & xyz();

    /// Returns TRUE if this vector is equal to the other vector.
    inline bool operator==(
        const Vec4 other) const;

    /// Returns TRUE if this vector is not equal to the other vector.
    inline bool operator!=(
        const Vec4 other) const;

    /// Casts this vector to another scalar type, using standard C casts
    template <class OT>
    inline Vec4<OT> cast() const;
};


typedef Vec4<uint8_t>  uint8_4;
typedef Vec4<uint16_t> uint16_4;
typedef Vec4<uint32_t> uint32_4;
typedef Vec4<uint64_t> uint64_4;
typedef Vec4<int8_t>   int8_4;
typedef Vec4<int16_t>  int16_4;
typedef Vec4<int32_t>  int32_4;
typedef Vec4<int64_t>  int64_4;
typedef Vec4<float>    float_4;
typedef Vec4<double>   double_4;



//--------------------------------------------------------------------------------------------------
// Operations on Vec2

//--- Unary Operations ---

template <class ST> inline Vec2<ST> operator+(const Vec2<ST> a);
template <class ST> inline Vec2<ST> operator-(const Vec2<ST> a);
template <class ST> inline Vec2<ST> abs      (const Vec2<ST> a);
template <class ST> inline Vec2<ST> sqrt     (const Vec2<ST> a);

//--- Binary Operations ---

template <class ST> inline Vec2<ST> operator+(const Vec2<ST> a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST> operator-(const Vec2<ST> a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST> operator*(const Vec2<ST> a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST> operator*(const ST       a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST> operator*(const Vec2<ST> a,  const ST       b);
template <class ST> inline Vec2<ST> operator/(const Vec2<ST> a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST> operator/(const Vec2<ST> a,  const ST       b);
template <class ST> inline Vec2<ST> operator/(const ST       a,  const Vec2<ST> b);
/// Returns the dot product of a and b.
template <class ST> inline ST       operator%(const Vec2<ST> a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST> min      (const Vec2<ST> a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST> max      (const Vec2<ST> a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST> clamp    (const Vec2<ST> a,  const Vec2<ST> min,  const Vec2<ST> max);
template <class ST> inline Vec2<ST> clamp    (const Vec2<ST> a,  const ST       min,  const ST       max);

//--- Assignment Operations ---

template <class ST> inline Vec2<ST>& operator+=(Vec2<ST> & a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST>& operator-=(Vec2<ST> & a,  const Vec2<ST> b);
template <class ST> inline Vec2<ST>& operator*=(Vec2<ST> & a,  const ST       b);
template <class ST> inline Vec2<ST>& operator/=(Vec2<ST> & a,  const ST       b);

//--- Reduction Operations ---

template <class ST> inline ST reduceAdd(const Vec2<ST> a);
template <class ST> inline ST reduceMul(const Vec2<ST> a);
template <class ST> inline ST reduceMin(const Vec2<ST> a);
template <class ST> inline ST reduceMax(const Vec2<ST> a);

//--- Euclidian Space Operations ---

template <class ST> inline ST       dot          (const Vec2<ST> a,  const Vec2<ST> b);
template <class ST> inline ST       lengthSquared(const Vec2<ST> a);
template <class ST> inline ST       length       (const Vec2<ST> a);
template <class ST> inline Vec2<ST> normalized   (const Vec2<ST> a);

//--- Conversion Operations ---

template <class ST> inline Vec2<ST> toRadians(const Vec2<ST> a);
template <class ST> inline Vec2<ST> toDegrees(const Vec2<ST> a);
template <class ST, class DT> inline void   convert  (const Vec2<ST> src,  Vec2<DT> &dst);

//--- Interpolation Operations ---

template<class ST> inline Vec2<ST> lerp(const Vec2<ST> a,  const Vec2<ST> b,  const ST t);

//--- Floating point operations ---

inline bool isFinite(const Vec2<float>  a);
inline bool isFinite(const Vec2<double> a);



//--------------------------------------------------------------------------------------------------
// Operations on Vec3

//--- Unary Operations ---

template <class ST> inline Vec3<ST> operator+(const Vec3<ST> a);
template <class ST> inline Vec3<ST> operator-(const Vec3<ST> a);
template <class ST> inline Vec3<ST> abs      (const Vec3<ST> a);
template <class ST> inline Vec3<ST> sqrt     (const Vec3<ST> a);

//--- Binary Operations ---

template <class ST> inline Vec3<ST> operator+(const Vec3<ST> a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> operator-(const Vec3<ST> a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> operator*(const Vec3<ST> a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> operator*(const ST       a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> operator*(const Vec3<ST> a,  const ST       b);
template <class ST> inline Vec3<ST> operator/(const Vec3<ST> a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> operator/(const Vec3<ST> a,  const ST       b);
template <class ST> inline Vec3<ST> operator/(const ST       a,  const Vec3<ST> b);
/// Returns the dot product of a and b.
template <class ST> inline ST       operator%(const Vec3<ST> a,  const Vec3<ST> b);
/// Returns the cross product of a and b.
template <class ST> inline Vec3<ST> operator^(const Vec3<ST> a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> min      (const Vec3<ST> a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> max      (const Vec3<ST> a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> clamp    (const Vec3<ST> a,  const Vec3<ST> min,  const Vec3<ST> max);
template <class ST> inline Vec3<ST> clamp    (const Vec3<ST> a,  const ST       min,  const ST       max);

// returns TRUE if a and b are equal up to some small relative error
template <class ST> inline bool almostEqual(const Vec3<ST> a,  const Vec3<ST> b, const float epsilon = .00001f);

//--- Assignment Operations ---

template <class ST> inline Vec3<ST>& operator+=(Vec3<ST> &a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST>& operator-=(Vec3<ST> &a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST>& operator*=(Vec3<ST> &a,  const               ST b);
template <class ST> inline Vec3<ST>& operator/=(Vec3<ST> &a,  const               ST b);

//--- Reduction Operations ---

template <class ST> inline ST reduceAdd(const Vec3<ST> a);
template <class ST> inline ST reduceMul(const Vec3<ST> a);
template <class ST> inline ST reduceMin(const Vec3<ST> a);
template <class ST> inline ST reduceMax(const Vec3<ST> a);

//--- Euclidian Space Operations ---

template <class ST> inline ST       dot          (const Vec3<ST>  a,  const Vec3<ST> b);
template <class ST> inline Vec3<ST> cross        (const Vec3<ST>  a,  const Vec3<ST> b);
template <class ST> inline ST       lengthSquared(const Vec3<ST>  a);
template <class ST> inline ST       length       (const Vec3<ST>  a);
template <class ST> inline Vec3<ST> normalized   (const Vec3<ST>  a);
/// Rotates vector around X axis.
template <class ST> inline Vec3<ST> rotateX      (const Vec3<ST> v,  const ST radians);
/// Rotates vector around Y axis.
template <class ST> inline Vec3<ST> rotateY      (const Vec3<ST> v,  const ST radians);
/// Rotates vector around Z axis.
template <class ST> inline Vec3<ST> rotateZ      (const Vec3<ST> v,  const ST radians);
/// Rotates vector around normalized axis.
template <class ST> inline Vec3<ST> rotate       (const Vec3<ST> v,  const Vec3<ST> axis,  const ST radians);

//--- Conversion Operations ---

template <class ST> inline Vec3<ST> toRadians(const Vec3<ST> a);
template <class ST> inline Vec3<ST> toDegrees(const Vec3<ST> a);
template <class ST, class DT> inline void   convert  (const Vec3<ST> src,  Vec3<DT> &dst);

//--- Interpolation Operations ---

template <class ST> inline Vec3<ST> lerp(const Vec3<ST> a,  const Vec3<ST> b,  const ST t);

//--- Floating point operations ---

inline bool isFinite(const Vec3<float>  a);
inline bool isFinite(const Vec3<double> a);



//--------------------------------------------------------------------------------------------------
// Operations for Vec4

//--- Unary Operations ---

template <class ST> inline Vec4<ST> operator+(const Vec4<ST> a);
template <class ST> inline Vec4<ST> operator-(const Vec4<ST> a);
template <class ST> inline Vec4<ST> abs      (const Vec4<ST> a);
template <class ST> inline Vec4<ST> sqrt     (const Vec4<ST> a);

//--- Binary Operations ---

template <class ST> inline Vec4<ST> operator+(const Vec4<ST> a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST> operator-(const Vec4<ST> a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST> operator*(const Vec4<ST> a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST> operator*(const ST       a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST> operator*(const Vec4<ST> a,  const ST       b);
template <class ST> inline Vec4<ST> operator/(const Vec4<ST> a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST> operator/(const Vec4<ST> a,  const ST       b);
template <class ST> inline Vec4<ST> operator/(const ST       a,  const Vec4<ST> b);
/// Returns the dot product of a and b.
template <class ST> inline ST       operator%(const Vec4<ST> a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST> min      (const Vec4<ST> a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST> max      (const Vec4<ST> a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST> clamp    (const Vec4<ST> a,  const Vec4<ST> min,  const Vec4<ST> max);
template <class ST> inline Vec4<ST> clamp    (const Vec4<ST> a,  const ST       min,  const ST       max);

//--- Assignment Operations ---

template <class ST> inline Vec4<ST>& operator+=(Vec4<ST> &a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST>& operator-=(Vec4<ST> &a,  const Vec4<ST> b);
template <class ST> inline Vec4<ST>& operator*=(Vec4<ST> &a,  const               ST b);
template <class ST> inline Vec4<ST>& operator/=(Vec4<ST> &a,  const               ST b);

//--- Reduction Operations ---

template <class ST> inline ST reduceAdd(const Vec4<ST> a);
template <class ST> inline ST reduceMul(const Vec4<ST> a);
template <class ST> inline ST reduceMin(const Vec4<ST> a);
template <class ST> inline ST reduceMax(const Vec4<ST> a);

//--- Euclidian Space Operations ---

template <class ST> inline ST               dot       (const Vec4<ST> a,  const Vec4<ST> b);
template <class ST> inline ST               length    (const Vec4<ST> a);
template <class ST> inline Vec4<ST> normalized(const Vec4<ST> a);

//--- Conversion Operations ---

template <class ST> inline Vec4<ST> toRadians(const Vec4<ST> a);
template <class ST> inline Vec4<ST> toDegrees(const Vec4<ST> a);
template <class ST, class DT> inline void   convert  (const Vec4<ST> src,  Vec4<DT> &dst);

//--- Interpolation Operations ---

template <class ST> inline Vec4<ST> lerp(const Vec4<ST> a,  const Vec4<ST> b,  const ST t);

//--- Floating point operations ---

inline bool isFinite(const Vec4<float>  a);
inline bool isFinite(const Vec4<double> a);



//--------------------------------------------------------------------------------------------------
// Implementation of Vec2


template <class ST>
inline Vec2<ST> Vec2<ST>::makeWith(
    const ST val)
{
    return make(val, val);
}


template <class ST>
inline Vec2<ST> Vec2<ST>::make(
    const ST x,
    const ST y)
{
    const Vec2<ST> result = { x, y };
    return result;
}


template <class ST>
inline Vec2<ST> Vec2<ST>::make(
    const ST *const v)
{
    const Vec2<ST> result = { v[0], v[1] };
    return result;
}


template <class ST>
inline Vec2<ST> Vec2<ST>::zero()
{
    const Vec2<ST> result = { 0, 0 };
    return result;
}


template <class ST>
inline Vec2<ST> Vec2<ST>::one()
{
    const Vec2<ST> result = { 1, 1 };
    return result;
}


template <class ST>
inline void Vec2<ST>::set(
    const ST _x,
    const ST _y)
{
    x = _x;
    y = _y;
}


template <class ST>
inline ST Vec2<ST>::operator[](
    const unsigned int dimIx) const
{
    return (&x)[dimIx];
}


template <class ST>
inline ST& Vec2<ST>::operator[](
    const unsigned int dimIx)
{
    return (&x)[dimIx];
}


template <class ST>
inline const ST* Vec2<ST>::ptr() const
{
    return &x;
}


template <class ST>
inline ST* Vec2<ST>::ptr()
{
    return &x;
}


template <class ST>
inline bool Vec2<ST>::operator==(
    const Vec2 other) const
{
    return ((x == other.x) & (y == other.y));
}


template <class ST>
inline bool Vec2<ST>::operator!=(
    const Vec2 other) const
{
    return ((x != other.x) | (y != other.y));
}


template <class ST>
template <class OT>
inline Vec2<OT> Vec2<ST>::cast() const
{
    return Vec2<OT>::make((OT) x, (OT) y);
}


template <class ST>
inline Vec2<ST> operator+(
    const Vec2<ST> a)
{
    return a;
}


template <class ST>
inline Vec2<ST> operator-(
    const Vec2<ST> a)
{
    return Vec2<ST>::make(-a.x, -a.y);
}


template <class ST>
inline Vec2<ST> abs(
    const Vec2<ST> a)
{
    return Vec2<ST>::make(oabs(a.x), oabs(a.y));
}


template <class ST>
inline Vec2<ST> sqrt(
    const Vec2<ST> a)
{
    return Vec2<ST>::make(std::sqrt(a.x), std::sqrt(a.y));
}


template <class ST>
inline Vec2<ST> operator+(
    const Vec2<ST> a,
    const Vec2<ST> b)
{
    return Vec2<ST>::make(a.x + b.x, a.y + b.y);
}


template <class ST>
inline Vec2<ST> operator-(
    const Vec2<ST> a,
    const Vec2<ST> b)
{
    return Vec2<ST>::make(a.x - b.x, a.y - b.y);
}


template <class ST>
inline Vec2<ST> operator*(
    const Vec2<ST> a,
    const Vec2<ST> b)
{
    return Vec2<ST>::make(a.x * b.x, a.y * b.y);
}


template <class ST>
inline Vec2<ST> operator*(
    const ST               a,
    const Vec2<ST> b)
{
    return Vec2<ST>::make(a * b.x, a * b.y);
}


template <class ST>
inline Vec2<ST> operator*(
    const Vec2<ST> a,
    const ST               b)
{
    return Vec2<ST>::make(a.x * b, a.y * b);
}


template <class ST>
inline Vec2<ST> operator/(
    const Vec2<ST> a,
    const Vec2<ST> b)
{
    return Vec2<ST>::make(a.x / b.x, a.y / b.y);
}


template <class ST>
inline Vec2<ST> operator/(
    const Vec2<ST> a,
    const ST               b)
{
    return Vec2<ST>::make(a.x / b, a.y / b);
}


template <class ST>
inline Vec2<ST> operator/(
    const ST               a,
    const Vec2<ST> b)
{
    return Vec2<ST>::make(a / b.x, a / b.y);
}


template <class ST>
inline ST operator%(
    const Vec2<ST> a,
    const Vec2<ST> b)
{
    return dot(a, b);
}


template <class ST>
inline Vec2<ST> min(
    const Vec2<ST> a,
    const Vec2<ST> b)
{
    return Vec2<ST>::make(std::min(a.x, b.x), std::min(a.y, b.y));
}


template <class ST>
inline Vec2<ST> max(
    const Vec2<ST> a,
    const Vec2<ST> b)
{
    return Vec2<ST>::make(std::max(a.x, b.x), std::max(a.y, b.y));
}


template <class ST>
inline Vec2<ST> clamp(
    const Vec2<ST> a,
    const Vec2<ST> min,
    const Vec2<ST> max)
{
    return Vec2<ST>::make((a.x < min.x) ? min.x : ((a.x > max.x) ? max.x : a.x),
                                  (a.y < min.y) ? min.y : ((a.y > max.y) ? max.y : a.y));
}


template <class ST>
inline Vec2<ST> clamp(
    const Vec2<ST> a,
    const ST               min,
    const ST               max)
{
    return Vec2<ST>::make((a.x < min) ? min : ((a.x > max) ? max : a.x),
                                  (a.y < min) ? min : ((a.y > max) ? max : a.y));
}


template <class ST>
inline Vec2<ST>& operator+=(
    Vec2<ST>       &a,
    const Vec2<ST>  b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}


template <class ST>
inline Vec2<ST>& operator-=(
    Vec2<ST>       &a,
    const Vec2<ST>  b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}


template <class ST>
inline Vec2<ST>& operator*=(
    Vec2<ST> &a,
    const ST          b)
{
    a.x *= b;
    a.y *= b;
    return a;
}


template <class ST>
inline Vec2<ST>& operator/=(
    Vec2<ST> &a,
    const ST          b)
{
    a.x /= b;
    a.y /= b;
    return a;
}


template <class ST>
inline ST reduceAdd(
    const Vec2<ST> a)
{
    return a.x + a.y;
}


template <class ST>
inline ST reduceMul(
    const Vec2<ST> a)
{
    return a.x * a.y;
}


template <class ST>
inline ST reduceMin(
    const Vec2<ST> a)
{
    return std::min(a.x, a.y);
}


template <class ST>
inline ST reduceMax(
    const Vec2<ST> a)
{
    return std::max(a.x, a.y);
}


template <class ST>
inline ST dot(
    const Vec2<ST> a,
    const Vec2<ST> b)
{
    return a.x*b.x + a.y*b.y;
}


template <class ST>
inline ST lengthSquared(
    const Vec2<ST> a)
{
    return dot(a, a);
}


template <class ST>
inline ST length(
    const Vec2<ST> a)
{
    return std::sqrt(dot(a, a));
}


template <class ST>
inline Vec2<ST> normalized(
    const Vec2<ST> a)
{
    return a * (1 / std::sqrt(dot(a, a)));
}


template <class ST>
inline Vec2<ST> toRadians(
    const Vec2<ST> a)
{
    return ((ST)M_PI / 180) * a;
}


template <class ST>
inline Vec2<ST> toDegrees(
    const Vec2<ST> a)
{
    return (180 / (ST)M_PI) * a;
}


template <class ST, class DT>
inline void convert(
    const Vec2<ST> src,
    Vec2<DT>      &dst)
{
    dst.x = (DT)src.x;
    dst.y = (DT)src.y;
}


template <class ST>
inline Vec2<ST> lerp(
    const Vec2<ST> a,
    const Vec2<ST> b,
    const ST               t)
{
    // use this notation to make sure that if a == b the result is always a
    return a + (b - a) * t;
}


inline bool isFinite(
    const Vec2<float> a)
{
    return oisfinite(a.x) && oisfinite(a.y);
}


inline bool isFinite(
    const Vec2<double> a)
{
    return oisfinite(a.x) && oisfinite(a.y);
}



//--------------------------------------------------------------------------------------------------
// Implementation of Vec3


template <class ST>
inline Vec3<ST> Vec3<ST>::makeWith(
    const ST val)
{
    return make(val, val, val);
}


template <class ST>
inline Vec3<ST> Vec3<ST>::make(
    const ST x,
    const ST y,
    const ST z)
{
    Vec3<ST> result = { x, y, z };
    return result;
}


template <class ST>
inline Vec3<ST> Vec3<ST>::make(
    const ST *const v)
{
    Vec3<ST> result = { v[0], v[1], v[2] };
    return result;
}


template <class ST>
inline Vec3<ST> Vec3<ST>::zero()
{
    const Vec3<ST> result = { 0, 0, 0 };
    return result;
}


template <class ST>
inline Vec3<ST> Vec3<ST>::one()
{
    const Vec3<ST> result = { 1, 1, 1 };
    return result;
}


template <class ST>
inline void Vec3<ST>::set(
    const ST _x,
    const ST _y,
    const ST _z)
{
    x = _x;
    y = _y;
    z = _z;
}


template <class ST>
inline ST Vec3<ST>::operator[](
    const unsigned int dimIx) const
{
    return (&x)[dimIx];
}


template <class ST>
inline ST& Vec3<ST>::operator[](
    const unsigned int dimIx)
{
    return (&x)[dimIx];
}


template <class ST>
inline const ST* Vec3<ST>::ptr() const
{
    return &x;
}


template <class ST>
inline ST* Vec3<ST>::ptr()
{
    return &x;
}


template <class ST>
inline const Vec2<ST> & Vec3<ST>::xy() const
{
    return reinterpret_cast<const Vec2<ST>&>(*this);
}


template <class ST>
inline Vec2<ST> & Vec3<ST>::xy()
{
    return reinterpret_cast<Vec2<ST>&>(*this);
}


template <class ST>
inline bool Vec3<ST>::operator==(
    const Vec3 other) const
{
    return ((x == other.x) & (y == other.y) & (z == other.z));
}


template <class ST>
inline bool Vec3<ST>::operator!=(
    const Vec3 other) const
{
    return ((x != other.x) | (y != other.y) | (z != other.z));
}


template <class ST>
template <class OT>
inline Vec3<OT> Vec3<ST>::cast() const
{
    return Vec3<OT>::make((OT) x, (OT) y, (OT) z);
}


template <class ST>
inline Vec3<ST> operator+(
    const Vec3<ST> a)
{
    return a;
}


template <class ST>
inline Vec3<ST> operator-(
    const Vec3<ST> a)
{
    return Vec3<ST>::make(-a.x, -a.y, -a.z);
}


template <class ST>
inline Vec3<ST> abs(
    const Vec3<ST> a)
{
    return Vec3<ST>::make(oabs(a.x), oabs(a.y), oabs(a.z));
}


template <class ST>
inline Vec3<ST> sqrt(
    const Vec3<ST> a)
{
    return Vec3<ST>::make(std::sqrt(a.x), std::sqrt(a.y), std::sqrt(a.z));
}


template <class ST>
inline Vec3<ST> operator+(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(a.x + b.x, a.y + b.y, a.z + b.z);
}


template <class ST>
inline Vec3<ST> operator-(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(a.x - b.x, a.y - b.y, a.z - b.z);
}


template <class ST>
inline Vec3<ST> operator*(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(a.x * b.x, a.y * b.y, a.z * b.z);
}


template <class ST>
inline Vec3<ST> operator*(
    const ST               a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(a * b.x, a * b.y, a * b.z);
}


template <class ST>
inline Vec3<ST> operator*(
    const Vec3<ST> a,
    const ST               b)
{
    return Vec3<ST>::make(a.x * b, a.y * b, a.z * b);
}


template <class ST>
inline Vec3<ST> operator/(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(a.x / b.x, a.y / b.y, a.z / b.z);
}


template <class ST>
inline Vec3<ST> operator/(
    const Vec3<ST> a,
    const ST               b)
{
    return Vec3<ST>::make(a.x / b, a.y / b, a.z / b);
}


template <class ST>
inline Vec3<ST> operator/(
    const ST               a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(a / b.x, a / b.y, a / b.z);
}


template <class ST>
inline ST operator%(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return dot(a, b);
}


template <class ST>
inline Vec3<ST> operator^(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return cross(a, b);
}


template <class ST>
inline Vec3<ST>min(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}


template <class ST>
inline Vec3<ST> max(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}


template <class ST>
inline Vec3<ST> clamp(
    const Vec3<ST> a,
    const Vec3<ST> min,
    const Vec3<ST> max)
{
    return Vec3<ST>::make((a.x < min.x) ? min.x : ((a.x > max.x) ? max.x : a.x),
                                  (a.y < min.y) ? min.y : ((a.y > max.y) ? max.y : a.y),
                                  (a.z < min.z) ? min.z : ((a.z > max.z) ? max.z : a.z));
}


template <class ST>
inline Vec3<ST> clamp(
    const Vec3<ST> a,
    const ST               min,
    const ST               max)
{
    return Vec3<ST>::make((a.x < min) ? min : ((a.x > max) ? max : a.x),
                                  (a.y < min) ? min : ((a.y > max) ? max : a.y),
                                  (a.z < min) ? min : ((a.z > max) ? max : a.z));
}


template <class ST>
inline bool almostEqual(
    const Vec3<ST> a,
    const Vec3<ST> b,
    const float            epsilon)
{
    if (oabs(a.x - b.x) > oabs(a.x) * epsilon) { return false; }
    if (oabs(a.y - b.y) > oabs(a.y) * epsilon) { return false; }
    if (oabs(a.z - b.z) > oabs(a.z) * epsilon) { return false; }
    return true;
}


template <class ST>
inline Vec3<ST>& operator+=(
    Vec3<ST>      &a,
    const Vec3<ST> b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}


template <class ST>
inline Vec3<ST>& operator-=(
    Vec3<ST>      &a,
    const Vec3<ST> b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}


template <class ST>
inline Vec3<ST>& operator*=(
    Vec3<ST> &a,
    const ST          b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    return a;
}


template <class ST>
inline Vec3<ST>& operator/=(
    Vec3<ST> &a,
    const ST          b)
{
    a.x /= b;
    a.y /= b;
    a.z /= b;
    return a;
}


template <class ST>
inline ST reduceAdd(
    const Vec3<ST> a)
{
    return a.x + a.y + a.z;
}


template <class ST>
inline ST reduceMul(
    const Vec3<ST> a)
{
    return a.x * a.y * a.z;
}


template <class ST>
inline ST reduceMin(
    const Vec3<ST> a)
{
    return std::min(std::min(a.x, a.y), a.z);
}


template <class ST>
inline ST reduceMax(
    const Vec3<ST> a)
{
    return std::max(std::max(a.x, a.y), a.z);
}


template <class ST>
inline ST dot(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}


template <class ST>
inline Vec3<ST> cross(
    const Vec3<ST> a,
    const Vec3<ST> b)
{
    return Vec3<ST>::make(a.y * b.z - a.z * b.y,
                                  a.z * b.x - a.x * b.z,
                                  a.x * b.y - a.y * b.x);
}


template <class ST>
inline ST lengthSquared(
    const Vec3<ST> a)
{
    return dot(a, a);
}


template <class ST>
inline ST length(
    const Vec3<ST> a)
{
    return std::sqrt(dot(a, a));
}


template <class ST>
inline Vec3<ST> normalized(
    const Vec3<ST> a)
{
    return a * (1 / (ST)std::sqrt(dot(a, a)));
}


template <class ST>
inline Vec3<ST> rotateX(
    const Vec3<ST> v,
    const ST               radians)
{
    const ST cs = cos(radians);
    const ST sn = sin(radians);
    return Vec3<ST>::make(v.x,
                                  v.y * cs - v.z * sn,
                                  v.y * sn + v.z * cs);
}


template <class ST>
inline Vec3<ST> rotateY(
    const Vec3<ST> v,
    const ST               radians)
{
    const ST cs = cosf(radians);
    const ST sn = sinf(radians);
    return Vec3<ST>::make(v.z * sn + v.x * cs,
                                  v.y,
                                  v.z * cs - v.x * sn);
}


template <class ST>
inline Vec3<ST> rotateZ(
    const Vec3<ST> v,
    const ST               radians)
{
    const ST cs = cos(radians);
    const ST sn = sin(radians);
    return Vec3<ST>::make(v.x * cs - v.y * sn,
                                  v.x * sn + v.y * cs,
                                  v.z);
}


template <class ST>
inline Vec3<ST> rotate(
    const Vec3<ST> v,
    const Vec3<ST> axis,
    const ST               radians)
{
    const ST cs = cos(radians);
    const ST sn = sin(radians);
    // rotate using Rodrigues' rotation formula
    return v * cs + cross(axis, v) * sn + axis * dot(axis, v) * (1 - cs);
}


template <class ST>
inline Vec3<ST> toRadians(
    const Vec3<ST> a)
{
    return ((ST)M_PI / 180) * a;
}


template <class ST>
inline Vec3<ST> toDegrees(
    const Vec3<ST> a)
{
    return (180 / (ST)M_PI) * a;
}


template <class ST, class DT>
inline void convert(
    const Vec3<ST> src,
    Vec3<DT>      &dst)
{
    dst.x = (DT)src.x;
    dst.y = (DT)src.y;
    dst.z = (DT)src.z;
}


template <class ST>
inline Vec3<ST> lerp(
    const Vec3<ST> a,
    const Vec3<ST> b,
    const ST               t)
{
    // use this notation to make sure that if a == b the result is always a
    return a + (b - a) * t;
}


inline bool isFinite(
    const Vec3<float> a)
{
    return oisfinite(a.x) && oisfinite(a.y) && oisfinite(a.z);
}


inline bool isFinite(
    const Vec3<double> a)
{
    return oisfinite(a.x) && oisfinite(a.y) && oisfinite(a.z);
}



//--------------------------------------------------------------------------------------------------
// Implementation of Vec4

template <class ST>
inline Vec4<ST> Vec4<ST>::makeWith(
    const ST val)
{
    return make(val, val, val, val);
}


template <class ST>
inline Vec4<ST> Vec4<ST>::make(
    const ST x,
    const ST y,
    const ST z,
    const ST w)
{
    Vec4<ST> result = { x, y, z, w };
    return result;
}


template <class ST>
inline Vec4<ST> Vec4<ST>::make(
    const ST *const v)
{
    Vec4<ST> result = { v[0], v[1], v[2], v[3] };
    return result;
}


template <class ST>
inline Vec4<ST> Vec4<ST>::zero()
{
    const Vec4<ST> result = { 0, 0, 0, 0 };
    return result;
}


template <class ST>
inline Vec4<ST> Vec4<ST>::one()
{
    const Vec4<ST> result = { 1, 1, 1, 1 };
    return result;
}


template <class ST>
inline void Vec4<ST>::set(
    const ST _x,
    const ST _y,
    const ST _z,
    const ST _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}


template <class ST>
inline ST Vec4<ST>::operator[](
    const unsigned int dimIx) const
{
    return (&x)[dimIx];
}


template <class ST>
inline ST& Vec4<ST>::operator[](
    const unsigned int dimIx)
{
    return (&x)[dimIx];
}


template <class ST>
inline const ST* Vec4<ST>::ptr() const
{
    return &x;
}


template <class ST>
inline ST* Vec4<ST>::ptr()
{
    return &x;
}


template <class ST>
inline const Vec2<ST> & Vec4<ST>::xy() const
{
    return reinterpret_cast<const Vec2<ST>&>(*this);
}


template <class ST>
inline Vec2<ST> & Vec4<ST>::xy()
{
    return reinterpret_cast<Vec2<ST>&>(*this);
}


template <class ST>
inline const Vec3<ST> & Vec4<ST>::xyz() const
{
    return reinterpret_cast<const Vec3<ST>&>(*this);
}


template <class ST>
inline Vec3<ST> & Vec4<ST>::xyz()
{
    return reinterpret_cast<Vec3<ST>&>(*this);
}


template <class ST>
inline bool Vec4<ST>::operator==(
    const Vec4 other) const
{
    return ((x == other.x) & (y == other.y) & (z == other.z) & (w == other.w));
}


template <class ST>
inline bool Vec4<ST>::operator!=(
    const Vec4 other) const
{
    return ((x != other.x) | (y != other.y) | (z != other.z) | (w != other.w));
}


template <class ST>
template <class OT>
inline Vec4<OT> Vec4<ST>::cast() const
{
    return Vec4<OT>::make((OT) x, (OT) y, (OT) z, (OT) w);
}


template <class ST>
inline Vec4<ST> operator+(
    const Vec4<ST> a)
{
    return a;
}


template <class ST>
inline Vec4<ST> operator-(
    const Vec4<ST> a)
{
    return Vec4<ST>::make(-a.x,
                                  -a.y,
                                  -a.z,
                                  -a.w);
}


template <class ST>
inline Vec4<ST> abs(
    const Vec4<ST> a)
{
    return Vec4<ST>::make(oabs(a.x),
                                  oabs(a.y),
                                  oabs(a.z),
                                  oabs(a.w));
}


template <class ST>
inline Vec4<ST> sqrt(
    const Vec4<ST> a)
{
    return Vec4<ST>::make(std::sqrt(a.x),
                                  std::sqrt(a.y),
                                  std::sqrt(a.z),
                                  std::sqrt(a.w));
}


template <class ST>
inline Vec4<ST> operator+(
    const Vec4<ST> a,
    const Vec4<ST> b)
{
    return Vec4<ST>::make(a.x + b.x,
                                  a.y + b.y,
                                  a.z + b.z,
                                  a.w + b.w);
}


template <class ST>
inline Vec4<ST> operator-(
    const Vec4<ST> a,
    const Vec4<ST> b)
{
    return Vec4<ST>::make(a.x - b.x,
                                  a.y - b.y,
                                  a.z - b.z,
                                  a.w - b.w);
}


template <class ST>
inline Vec4<ST> operator*(
    const Vec4<ST> a,
    const Vec4<ST> b)
{
    return Vec4<ST>::make(a.x * b.x,
                                  a.y * b.y,
                                  a.z * b.z,
                                  a.w * b.w);
}


template <class ST>
inline Vec4<ST> operator*(
    const ST               a,
    const Vec4<ST> b)
{
    return Vec4<ST>::make(a * b.x,
                                  a * b.y,
                                  a * b.z,
                                  a * b.w);
}


template <class ST>
inline Vec4<ST> operator*(
    const Vec4<ST> a,
    const ST               b)
{
    return Vec4<ST>::make(a.x * b,
                                  a.y * b,
                                  a.z * b,
                                  a.w * b);
}


template <class ST>
inline Vec4<ST> operator/(
    const Vec4<ST> a,
    const Vec4<ST> b)
{
    return Vec4<ST>::make(a.x / b.x,
                                  a.y / b.y,
                                  a.z / b.z,
                                  a.w / b.w);
}


template <class ST>
inline Vec4<ST> operator/(
    const Vec4<ST> a,
    const ST               b)
{
    return Vec4<ST>::make(a.x / b,
                                  a.y / b,
                                  a.z / b,
                                  a.w / b);
}


template <class ST>
inline Vec4<ST> operator/(
    const ST               a,
    const Vec4<ST> b)
{
    return Vec4<ST>::make(a / b.x,
                                  a / b.y,
                                  a / b.z,
                                  a / b.w);
}


template <class ST>
inline ST operator%(
    const Vec4<ST> a,
    const Vec4<ST> b)
{
    return dot(a, b);
}


template <class ST>
inline Vec4<ST>min(
    const Vec4<ST> a,
    const Vec4<ST> b)
{
    return Vec4<ST>::make(std::min(a.x, b.x),
                                  std::min(a.y, b.y),
                                  std::min(a.z, b.z),
                                  std::min(a.w, b.w));
}


template <class ST>
inline Vec4<ST> max(
    const Vec4<ST> a,
    const Vec4<ST> b)
{
    return Vec4<ST>::make(std::max(a.x, b.x),
                                  std::max(a.y, b.y),
                                  std::max(a.z, b.z),
                                  std::max(a.w, b.w));
}


template <class ST>
inline Vec4<ST> clamp(
    const Vec4<ST> a,
    const Vec4<ST> min,
    const Vec4<ST> max)
{
    return Vec4<ST>::make((a.x < min.x) ? min.x : ((a.x > max.x) ? max.x : a.x),
                                  (a.y < min.y) ? min.y : ((a.y > max.y) ? max.y : a.y),
                                  (a.z < min.z) ? min.z : ((a.z > max.z) ? max.z : a.z),
                                  (a.w < min.w) ? min.w : ((a.w > max.w) ? max.w : a.w));
}


template <class ST>
inline Vec4<ST> clamp(
    const Vec4<ST> a,
    const ST               min,
    const ST               max)
{
    return Vec4<ST>::make((a.x < min) ? min : ((a.x > max) ? max : a.x),
                                  (a.y < min) ? min : ((a.y > max) ? max : a.y),
                                  (a.z < min) ? min : ((a.z > max) ? max : a.z),
                                  (a.w < min) ? min : ((a.w > max) ? max : a.w));
}


template <class ST>
inline Vec4<ST>& operator+=(
    Vec4<ST>       &a,
    const Vec4<ST>  b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}


template <class ST>
inline Vec4<ST>& operator-=(
    Vec4<ST>       &a,
    const Vec4<ST>  b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}


template <class ST>
inline Vec4<ST>& operator*=(
    Vec4<ST> &a,
    const ST          b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    a.w *= b;
    return a;
}


template <class ST>
inline Vec4<ST>& operator/=(
    Vec4<ST> &a,
    const ST          b)
{
    a.x /= b;
    a.y /= b;
    a.z /= b;
    a.w /= b;
    return a;
}


template <class ST>
inline ST reduceAdd(
    const Vec4<ST> a)
{
    return a.x + a.y + a.z + a.w;
}


template <class ST>
inline ST reduceMul(
    const Vec4<ST> a)
{
    return a.x * a.y * a.z * a.w;
}


template <class ST>
inline ST reduceMin(
    const Vec4<ST> a)
{
    return std::min(std::min(a.x, a.y), std::min(a.z, a.w));
}


template <class ST>
inline ST reduceMax(
    const Vec4<ST> a)
{
    return std::max(std::max(a.x, a.y), std::max(a.z, a.w));
}


template <class ST>
inline ST dot(
    const Vec4<ST> a,
    const Vec4<ST> b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}


template <class ST>
inline ST lengthSquared(
    const Vec4<ST> a)
{
    return dot(a, a);
}


template <class ST>
inline ST length(
    const Vec4<ST> a)
{
    return std::sqrt(dot(a, a));
}


template <class ST>
inline Vec4<ST> normalized(
    const Vec4<ST> a)
{
    return a * (1 / (ST)std::sqrt(dot(a, a)));
}


template <class ST>
inline Vec4<ST> toRadians(
    const Vec4<ST> a)
{
    return ((ST)M_PI / 180) * a;
}


template <class ST>
inline Vec4<ST> toDegrees(
    const Vec4<ST> a)
{
    return (180 / (ST)M_PI) * a;
}


template <class ST, class DT>
inline void convert(
    const Vec4<ST> src,
    Vec4<DT>      &dst)
{
    dst.x = (DT)src.x;
    dst.y = (DT)src.y;
    dst.z = (DT)src.z;
    dst.w = (DT)src.w;
}


template <class ST>
inline Vec4<ST> lerp(
    const Vec4<ST> a,
    const Vec4<ST> b,
    const ST               t)
{
    // use this notation to make sure that if a == b the result is always a
    return a + (b - a) * t;
}


inline bool isFinite(
    const Vec4<float> a)
{
    return oisfinite(a.x) && oisfinite(a.y) && oisfinite(a.z) && oisfinite(a.w);
}


inline bool isFinite(
    const Vec4<double> a)
{
    return oisfinite(a.x) && oisfinite(a.y) && oisfinite(a.z) && oisfinite(a.w);
}


}   // namespace OctaneVec


namespace std
{
    template <class ST>
    struct hash<OctaneVec::Vec2<ST>>
    {
        size_t operator()
            (const OctaneVec::Vec2<ST> & vec) const noexcept
        {
            std::hash<ST> stHash;
            auto h = stHash(vec.x);
            h ^= stHash(vec.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };

    template <class ST>
    struct hash<OctaneVec::Vec3<ST>>
    {
        size_t operator()
            (const OctaneVec::Vec3<ST> & vec) const noexcept
        {
            std::hash<ST> stHash;
            auto h = stHash(vec.x);
            h ^= stHash(vec.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= stHash(vec.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };

    template <class ST>
    struct hash<OctaneVec::Vec4<ST>>
    {
        size_t operator()
            (const OctaneVec::Vec4<ST> & vec) const noexcept
        {
            std::hash<ST> stHash;
            auto h = stHash(vec.x);
            h ^= stHash(vec.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= stHash(vec.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= stHash(vec.w) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };
}


namespace Octane {
    using namespace OctaneVec;
}


#endif  // #ifndef _OCTANEVECTYPES_H_
