// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_COMBO_BOX_H_
#define _OCTANE_WRAP_COMBO_BOX_H_   1

// system includes
#include <functional>
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL // no-op
#include "octanegrpcwrapguicomponent.h"
#include "apicomboboxclient.h"
#include "apicomboboxitemclient.h"

namespace Octane
{
class ApiComboBox;
}

namespace OctaneWrap
{

class ComboBox;

//--------------------------------------------------------------------------------------------------
/// Item that populates a combo box.
struct ComboBoxItem
{
    /// Unique ID for the combo box item. Id should be larger than 0.
    int         mId;
    /// Text displayed in the combo box when this item is selected.
    std::string mText;

    /// Creates a new combo box item.
    ComboBoxItem(
        const int         id,
        const std::string &text);
};



//--------------------------------------------------------------------------------------------------
/// Interface for combo box listeners.
class ComboBoxListener
{
public:

    virtual void comboBoxChanged(
        OctaneWrap::ComboBox &comboBox) =0;
};



//--------------------------------------------------------------------------------------------------
/// Convenience wrapper for ApiComboBox.
class ComboBox : public GuiComponent
{
    OCTANEAPI_NO_COPY(ComboBox);

public:

    /// Creates a combo box.
    ///
    /// @param[in]  items
    ///     Combo box items that appear in the combo box.
    ComboBox(
        const std::vector<ComboBoxItem> &items);

    /// Destructs this combo box.
    virtual ~ComboBox();

    /// Sets one of the items to be the current selection.  This will set the combo box's text to 
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
    std::string text() const;

    /// Adds a listener.
    void addListener(
        ComboBoxListener &listener);

    /// Removes a listener.
    void removeListener(
        ComboBoxListener &listener);

private:

    /// Wrapped ComboBox
    OctaneGRPC::ApiComboBoxProxy   mApiComboBox;
    /// List of listeners.
    std::vector<ComboBoxListener*> mListeners;

    /// internal C callback
    static void onComboBoxChanged(
        OctaneGRPC::ApiComboBoxProxy & comboBox,
        void *                         privateData);
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_COMBO_BOX_H_
