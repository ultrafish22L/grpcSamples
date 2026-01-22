// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_ARRAY_H_
#define _API_ARRAY_H_   1

#include "octanematrix.h"
#include "octanetypes.h"
#include "octanevectypes.h"


namespace Octane
{

//--------------------------------------------------------------------------------------------------

/// Represents an array of elements passed into the API, or returned from the API
///
/// Functions which return an ApiArray will also specify if the returned array has to be freed
/// by the caller, or in other cases how long the data will remain valid.
///
/// Generally for data inside the node system, the data will remain valid until the underlying
/// node item is destroyed, or until the data in the attribute is set to a different array.
template <class T>
struct ApiArray
{
    const T *mData;
    size_t  mSize;

    inline ApiArray()
    :
        mData(NULL),
        mSize(0)
    {}

    inline ApiArray(
        const T      *data,
        const size_t size)
    :
        mData(data),
        mSize(size)
    {}
};


/// Provides the start iterator for iterating this array in a range based loop
/// (via Koenig lookup)
template <class T>
inline const T* begin(
    const ApiArray<T> a)
{
    return a.mData;
}


/// Provides the end iterator for iterating this array in a range based loop
template <class T>
inline const T* end(
    const ApiArray<T> a)
{
    return a.mData + a.mSize;
}


// The numerical array types we currently store in attributes.
typedef ApiArray<bool   >     BoolArrayT;
typedef ApiArray<int32_t>     IntArrayT;
typedef ApiArray<int32_2>     Int2ArrayT;
typedef ApiArray<int32_3>     Int3ArrayT;
typedef ApiArray<int32_4>     Int4ArrayT;
typedef ApiArray<int64_t>     LongArrayT;
typedef ApiArray<int64_2>     Long2ArrayT;
typedef ApiArray<float>       FloatArrayT;
typedef ApiArray<float_2>     Float2ArrayT;
typedef ApiArray<float_3>     Float3ArrayT;
typedef ApiArray<float_4>     Float4ArrayT;
typedef ApiArray<MatrixF>     MatrixArrayT;
typedef ApiArray<const char*> StringArrayT;
typedef ApiArray<uint8_t>     ByteArrayT;
typedef ApiArray<uint32_t>    UIntArrayT;
typedef ApiArray<char>        CharArrayT;



} // namespace Octane


#endif // #ifndef _API_ARRAY_H_
