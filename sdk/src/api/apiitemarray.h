// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_ITEM_ARRAY_H_
#define _API_ITEM_ARRAY_H_  1

#include "octanetypes.h"


namespace Octane
{

class ApiItem;

//--------------------------------------------------------------------------------------------------
/// Array of node items.
class OCTANEAPI_DECL ApiItemArray
{
    OCTANEAPI_NO_COPY(ApiItemArray);

public:

    /// Creates an empty item list.
    ApiItemArray();

    /// Destroys this list.
    ~ApiItemArray();

    /// Returns the size of the item list.
    size_t size() const;
        
    /// Returns the item at the given index. Returns a nullptr if the index is out-of-bounds.
    ApiItem* get(
        const size_t index) const;

    /// Returns the internal array (owned by this object).
    ApiItem** items();

    /// Begin function for range-based for loop
    ApiItem* const* begin();

    /// End function for range-based for loop
    ApiItem* const* end();

    /// Begin function for constant range-based for loop
    const ApiItem* const* begin() const;

    /// End function for constant range-based for loop
    const ApiItem* const* end() const;

    /// Init function (only used internally).
    void init(
        const size_t size);

private:

    /// List of items.
    ApiItem **mItems;
    /// Size of the list of items.
    size_t  mSize; 
};

} // namespace Octane


#endif // #ifndef _API_ITEM_ARRAY_H_
