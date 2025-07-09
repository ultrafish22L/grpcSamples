// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_NODE_ARRAY_H_
#define _API_NODE_ARRAY_H_  1

#include "octanetypes.h"


namespace Octane
{

class ApiNode;

//--------------------------------------------------------------------------------------------------
/// Array of ApiNode pointers.
class OCTANEAPI_DECL ApiNodeArray
{
    OCTANEAPI_NO_COPY(ApiNodeArray);

public:

    /// Creates an empty item list.
    ApiNodeArray();

    /// Destroys this list.
    ~ApiNodeArray();

    /// Returns the size of the item list.
    size_t size() const;
        
    /// Returns the item at the given index (or NULL).
    ApiNode* get(
        const size_t index) const;

    /// Returns the internal array (owned by this object).
    ApiNode** items();

    /// Begin function for range-based for loop
    ApiNode* const* begin();

    /// End function for range-based for loop
    ApiNode* const* end();

    /// Begin function for constant range-based for loop
    const ApiNode* const* begin() const;

    /// End function for constant range-based for loop
    const ApiNode* const* end() const;

    /// Init function (only used internally).
    void init(
        const size_t size);

private:

    /// List of items.
    ApiNode **mNodes;
    /// Size of the list of items.
    size_t  mSize; 
};

} // namespace Octane


#endif // #ifndef _API_NODE_ARRAY_H_
