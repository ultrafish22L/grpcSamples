// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_COMBO_BOX_H_
#define _API_COMBO_BOX_H_   1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Item that goes into a combo box.
struct OCTANEAPI_DECL ApiComboBoxItem
{
    /// Unique ID for the combo box item. Id should be larger than 0.
    int        mId;
    /// Text displayed in the combo box when this item is selected.
    const char *mText;

    /// Creates a new combo box item.
    inline ApiComboBoxItem(
        const int  id,
        const char *text);
};



inline ApiComboBoxItem::ApiComboBoxItem(
    const int  id,
    const char *text)
:
    mId(id),
    mText(text)
{}


//--------------------------------------------------------------------------------------------------
/// Combo box.
class OCTANEAPI_DECL ApiComboBox : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiComboBox);

public:

    /// Types
    typedef void (*ComboBoxChangedCallbackT)(ApiComboBox&, void*);

    /// Creates a new combo box.
    ///
    /// @param[in]  items
    ///     Array of items that populate the combo box.
    /// @param[in]  nbOfItems
    ///     The number of items in the items array.
    /// @param[in]  callback
    ///     Callback function, called when the user changes the selected item in the combo box.
    /// @param[in]  privateData
    ///     Private data passed back into the callback.
    /// @return
    ///     Pointer to the combo box.
    static ApiComboBox* create(
        const ApiComboBoxItem    *items,
        const size_t             nbOfItems,
        ComboBoxChangedCallbackT callback,
        void                     *privateData);

    /// Destroys this combo box.
    void destroy();

    /// Sets one of the items to be the current selection.  This will set the ComboBox's text to 
    /// that of the item that matches this ID.
    ///
    /// @param[in]  newItemId
    ///     the new item to select
    /// @param[in]  sendEvent
    ///     TRUE to send a change event for this combo box.
    void setSelectedId(
        const int  newItemId,
        const bool sendEvent);

    /// Returns the ID of the item that's currently shown in the box. If no item is selected, this
    /// will return 0.
    int selectedId() const;

    /// Returns the text of the item currently selected in the combo box or an empty string if
    /// nothing is selected.
    const char* text() const;
};


} // namespace Octane

#endif // #ifndef _API_COMBO_BOX_H_
