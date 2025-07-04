// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef OCTANE_AABB_H__
#define OCTANE_AABB_H__


// library includes
#include <cfloat>
// application includes
#include "octanevectypes.h"
#include "octanematrix.h"


namespace OctaneVec
{

template<typename ST, uint32_t DIM>
struct DimensionTraits;


template<typename ST>
struct DimensionTraits<ST, 2>
{
    typedef Vec2<ST>   VectorT;
    typedef Matrix<ST> MatrixT;
};



template<typename ST>
struct DimensionTraits<ST, 3>
{
    typedef Vec3<ST>   VectorT;
    typedef Matrix<ST> MatrixT;
};



/// This type represents an axis-aligned bounding box structure
///
/// @param ST
///     Template type used to store coordinate values
/// @param DIM
///     Number of dimensions of the bounding box
///
template <typename ST, size_t DIM>
struct AABB
{
    typedef ST                                         ScalarT;
    typedef typename DimensionTraits<ST, DIM>::VectorT VectorT;
    typedef typename DimensionTraits<ST, DIM>::MatrixT MatrixT;

    static const size_t DIMENSIONS = DIM;

    VectorT pmin;
    VectorT pmax;

    // --- construction ---

    inline static AABB make(
        const VectorT &pmin,
        const VectorT &pmax);

    static inline AABB empty();

    static inline AABB zero();

    // --- comparison ---
    
    inline bool operator==(
        const AABB &aabb) const;

    inline bool operator!=(
        const AABB &aabb) const;

    // --- properties ---

    inline bool isEmpty() const;

    inline bool isFinite() const;

    inline VectorT center() const;

    inline ST axisCenter(int axis) const;

    inline VectorT getExtent() const;

    inline ST getAxisExtent(
        int axis) const;

    inline ST getVolume() const;

    inline ST halfArea() const;

    inline int getLongestSide() const;

    // --- operations ---

    bool contains(
        const VectorT &p) const;

    /// Returns TRUE if this box fully contains the other box
    bool contains(
        const AABB &other) const;

    AABB<ST,DIM> transformed(
        const MatrixT &m) const;

    // --- extending ---

    inline void extend(
        const VectorT &v);
    
    inline void extend(
        const AABB &aabb);

    inline void extendIfNonZero(
        const AABB &aabb);

    inline AABB& intersect(
        const AABB &aabb);

    void repairEmpty();

    void extend(
        const MatrixT &m,
        const VectorT &p);
    
    void extend(
        const MatrixT &m,
        const AABB    &aabb);

    inline void expand(
        const ST margin);

    // operator aliases

    // extending
    inline AABB &operator+=(
        const VectorT &other);

    inline AABB &operator+=(
        const AABB &other);

    // intersection
    inline AABB &operator^=(
        const AABB &other);

    // type cast operator for dimension changes
    template<size_t DIM2>
    operator AABB<ST, DIM2>() const;
};



namespace detail
{

template<typename ST>
inline bool isEmpty(
    const AABB<ST, 2> &aabb)
{
    return aabb.pmin.x > aabb.pmax.x ||
           aabb.pmin.y > aabb.pmax.y ||
           aabb.pmin == aabb.pmax;
}


template<typename ST>
inline bool isEmpty(
    const AABB<ST, 3> &aabb)
{
    return aabb.pmin.x > aabb.pmax.x ||
           aabb.pmin.y > aabb.pmax.y ||
           aabb.pmin.z > aabb.pmax.z ||
           aabb.pmin == aabb.pmax;
}


template<typename ST>
inline ST halfArea(
    const typename AABB<ST, 2>::VectorT &e)
{
    return (e.x * e.y) / ST(2);
}


template<typename ST>
inline ST halfArea(
    const typename AABB<ST, 3>::VectorT &e)
{
    return e.x * e.y + e.y * e.z + e.z * e.x;
}


template<typename ST>
inline ST getLongestSide(
    const typename AABB<ST, 2>::VectorT& e)
{
    int longest = (e.x < e.y) ? 1 : 0;
    return longest;
}


template<typename ST>
inline ST getLongestSide(
    const typename AABB<ST, 3>::VectorT& e)
{
    int longest = (e.x < e.y) ? 1 : 0;
    if (e[longest] < e.z) { longest = 2; }
    return longest;
}


template<typename ST>
inline bool contains(
    const AABB<ST, 2>                   &aabb,
    const typename AABB<ST, 2>::VectorT &p)
{
    return aabb.pmin.x <= p.x && p.x <= aabb.pmax.x &&
           aabb.pmin.y <= p.y && p.y <= aabb.pmax.y;
}


template<typename ST>
inline bool contains(
    const AABB<ST, 3>                   &aabb,
    const typename AABB<ST, 3>::VectorT &p)
{
    return aabb.pmin.x <= p.x && p.x <= aabb.pmax.x &&
           aabb.pmin.y <= p.y && p.y <= aabb.pmax.y &&
           aabb.pmin.z <= p.z && p.z <= aabb.pmax.z;
}


template<typename ST>
inline bool contains(
    const AABB<ST, 2> &aabb,
    const AABB<ST, 2> &other)
{
    return aabb.pmin.x <= other.pmin.x && other.pmax.x <= aabb.pmax.x &&
           aabb.pmin.y <= other.pmin.y && other.pmax.y <= aabb.pmax.y;
}


template<typename ST>
inline bool contains(
    const AABB<ST, 3> &aabb,
    const AABB<ST, 3> &other)
{
    return aabb.pmin.x <= other.pmin.x && other.pmax.x <= aabb.pmax.x &&
           aabb.pmin.y <= other.pmin.y && other.pmax.y <= aabb.pmax.y &&
           aabb.pmin.z <= other.pmin.z && other.pmax.z <= aabb.pmax.z;
}


template<typename ST>
inline void expand(
    AABB<ST, 2> &aabb,
    const ST    margin)
{
    aabb.pmin.x -= margin;
    aabb.pmin.y -= margin;
    aabb.pmax.x += margin;
    aabb.pmax.y += margin;
}


template<typename ST>
inline void expand(
    AABB<ST, 3> &aabb,
    const ST    margin)
{
    aabb.pmin.x -= margin;
    aabb.pmin.y -= margin;
    aabb.pmin.z -= margin;
    aabb.pmax.x += margin;
    aabb.pmax.y += margin;
    aabb.pmax.z += margin;
}


template<typename ST>
void extend(
    AABB<ST, 2>                         &aabb,
    const typename AABB<ST, 2>::MatrixT &m,
    const AABB<ST, 2>                   &other)
{
    typedef typename AABB<ST, 2>::VectorT VectorT;

    if (!other.isEmpty())
    {
        // Just look at the 4 corners of the bounding box
        aabb.extend(m, other.pmin);
        aabb.extend(m, VectorT::make(other.pmax.x, other.pmin.y));
        aabb.extend(m, VectorT::make(other.pmin.x, other.pmax.y));
        aabb.extend(m, other.pmax);
    }
}


template<typename ST>
void extend(
    AABB<ST, 3>                         &aabb,
    const typename AABB<ST, 3>::MatrixT &m,
    const AABB<ST, 3>                   &other)
{
    typedef typename AABB<ST, 3>::VectorT VectorT;

    if (!other.isEmpty())
    {
        // Just look at the 8 corners of the bounding box
        aabb.extend(m, other.pmin);
        aabb.extend(m, VectorT::make(other.pmax.x, other.pmin.y, other.pmin.z));
        aabb.extend(m, VectorT::make(other.pmin.x, other.pmax.y, other.pmin.z));
        aabb.extend(m, VectorT::make(other.pmax.x, other.pmax.y, other.pmin.z));
        aabb.extend(m, VectorT::make(other.pmin.x, other.pmin.y, other.pmax.z));
        aabb.extend(m, VectorT::make(other.pmax.x, other.pmin.y, other.pmax.z));
        aabb.extend(m, VectorT::make(other.pmin.x, other.pmax.y, other.pmax.z));
        aabb.extend(m, other.pmax);
    }
}


template<typename ST>
inline AABB<ST, 2>& assign(
    const AABB<ST, 3> &src,
    AABB<ST, 2>       &dst)
{
    // ignore z coordinate
    dst.pmin = AABB<ST, 2>::VectorT::make(src.pmin.x , src.pmin.y);
    dst.pmax = AABB<ST, 2>::VectorT::make(src.pmax.x , src.pmax.y);
    return dst;
}


template<typename ST>
inline AABB<ST, 3>& assign(
    const AABB<ST, 2> &src,
    AABB<ST, 3>       &dst)
{
    // set z coordinate to zero
    dst.pmin = AABB<ST, 3>::VectorT::make(src.pmin.x , src.pmin.y, 0);
    dst.pmax = AABB<ST, 3>::VectorT::make(src.pmax.x , src.pmax.y, 0);
    return dst;
}


}   // namespace detail


typedef AABB<float,  2> AABRF;
typedef AABB<double, 2> AABRD;

typedef AABB<float,  3> AABBF;
typedef AABB<double, 3> AABBD;



template<typename ST, size_t DIM>
inline AABB<ST, DIM> AABB<ST, DIM>::make(
    const typename AABB<ST, DIM>::VectorT &pmin,
    const typename AABB<ST, DIM>::VectorT &pmax)
{
    const AABB tmp = { pmin, pmax};
    return tmp;
}


template<typename ST, size_t DIM>
inline AABB<ST, DIM> AABB<ST, DIM>::zero()
{
    const AABB tmp = { VectorT::makeWith(0), VectorT::makeWith(0) };
    return tmp;
}


template<typename ST, size_t DIM>
inline AABB<ST, DIM> AABB<ST, DIM>::empty()
{
    const AABB tmp = {
        VectorT::makeWith( std::numeric_limits<ST>::max()),
        VectorT::makeWith(-std::numeric_limits<ST>::max())
    };

    return tmp;
}


template<typename ST, size_t DIM>
inline bool AABB<ST, DIM>::operator==(
    const AABB<ST, DIM> &aabb) const
{
    return pmax == aabb.pmax && pmin == aabb.pmin;
}


template<typename ST, size_t DIM>
inline bool AABB<ST, DIM>::operator!=(
    const AABB<ST, DIM> &aabb) const
{
    return !(*this == aabb);
}


template<typename ST, size_t DIM>
inline bool AABB<ST, DIM>::isEmpty() const
{
    return detail::isEmpty(*this);
}


template<typename ST, size_t DIM>
inline bool AABB<ST, DIM>::isFinite() const
{
    return Octane::isFinite(pmin) && Octane::isFinite(pmax);
}


template<typename ST, size_t DIM>
inline typename AABB<ST, DIM>::VectorT AABB<ST, DIM>::center() const
{
    return .5f * (pmax + pmin);
}


template<typename ST, size_t DIM>
inline ST AABB<ST, DIM>::axisCenter(
    int axis) const
{
    return .5f * (pmax[axis] + pmin[axis]);
}


template<typename ST, size_t DIM>
inline typename AABB<ST, DIM>::VectorT AABB<ST, DIM>::getExtent() const
{
    return pmax - pmin;
}


template<typename ST, size_t DIM>
inline ST AABB<ST, DIM>::getAxisExtent(int axis) const
{
    return pmax[axis] - pmin[axis];
}


template<typename ST, size_t DIM>
inline ST AABB<ST, DIM>::getVolume() const
{
    return reduceMul(getExtent());
}


template<typename ST, size_t DIM>
inline ST AABB<ST, DIM>::halfArea() const
{
    const VectorT e = getExtent();

    return detail::halfArea<ST>(e);
}


template<typename ST, size_t DIM>
inline int AABB<ST, DIM>::getLongestSide() const
{
    const VectorT e = getExtent();
    int longest = detail::getLongestSide<ST>(e);
    return longest;
}


template<typename ST, size_t DIM>
bool AABB<ST, DIM>::contains(
    const typename AABB<ST, DIM>::VectorT &p) const
{
    return detail::contains(*this, p);
}


template<typename ST, size_t DIM>
bool AABB<ST, DIM>::contains(
    const AABB<ST, DIM> &other) const
{
    return detail::contains(*this, other);
}


template<typename ST, size_t DIM>
AABB<ST, DIM> AABB<ST, DIM>::transformed(
    const typename AABB<ST, DIM>::MatrixT &m) const
{
    AABB aabb = empty();
    aabb.extend(m, *this);
    return aabb;
}


template<typename ST, size_t DIM>
inline void AABB<ST, DIM>::extend(
    const typename AABB<ST, DIM>::VectorT &v)
{
    pmin = min(pmin, v);
    pmax = max(pmax, v);
}


template<typename ST, size_t DIM>
inline void AABB<ST, DIM>::extend(
    const AABB<ST, DIM> &aabb)
{
    pmin = min(pmin, aabb.pmin);
    pmax = max(pmax, aabb.pmax);
}


template<typename ST, size_t DIM>
inline void AABB<ST, DIM>::extendIfNonZero(
    const AABB<ST, DIM> &aabb)
{
    if (aabb != zero()) { extend(aabb); }
}


template<typename ST, size_t DIM>
inline void AABB<ST, DIM>::repairEmpty()
{
    pmin = min(pmin, pmax);
    pmax = max(pmin, pmax);
}


template<typename ST, size_t DIM>
inline AABB<ST, DIM>& AABB<ST, DIM>::intersect(
    const AABB<ST, DIM> &aabb)
{
    pmin = max(pmin, aabb.pmin);
    pmax = min(pmax, aabb.pmax);
    return *this;
}


template<typename ST, size_t DIM>
void AABB<ST, DIM>::extend(
    const typename AABB<ST, DIM>::MatrixT &m,
    const typename AABB<ST, DIM>::VectorT &p)
{
    extend(multiplyP(m, p));
}


template<typename ST, size_t DIM>
void AABB<ST, DIM>::extend(
    const typename AABB<ST, DIM>::MatrixT &m,
    const AABB<ST, DIM>                   &aabb)
{
    detail::extend(*this, m, aabb);
}


template<typename ST, size_t DIM>
inline void AABB<ST, DIM>::expand(
    const ST margin)
{
    detail::expand(*this, margin);
}


template<typename ST, size_t DIM>
inline AABB<ST, DIM> &AABB<ST, DIM>::operator+=(
    const typename AABB<ST, DIM>::VectorT &other)
{
    extend(other);
    return *this;
}


template<typename ST, size_t DIM>
inline AABB<ST, DIM> &AABB<ST, DIM>::operator+=(
    const AABB<ST, DIM> &other)
{
    extend(other);
    return *this;
}


template<typename ST, size_t DIM>
inline AABB<ST,DIM>& AABB<ST, DIM>::operator^=(
    const AABB<ST, DIM> &other)
{
    return intersect(other);
}


template<typename ST, size_t DIM>
template<size_t DIM2>
AABB<ST, DIM>::operator AABB<ST, DIM2>() const
{
    AABB<ST, DIM2> dst;
    return detail::assign(*this, dst);
}


}   // namespace OctaneVec

namespace Octane {
    using namespace OctaneVec;
}


template<typename ST, size_t DIM>
bool compareAABBAxis(
    const OctaneVec::AABB<ST, DIM> &a,
    const OctaneVec::AABB<ST, DIM> &b,
    int                         axis)
{
    const ST sa = a.pmin[axis] + a.pmax[axis];
    const ST sb = b.pmin[axis] + b.pmax[axis];
    return sa < sb;
}


#endif // #ifndef OCTANE_AABB_H__
