// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"
#include "apiguicomponentclient.h"


#include "apicombobox.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiComboBox
class ApiComboBoxProxy : public ApiGuiComponentProxy
{
public:
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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the combo box.
    static ApiComboBoxProxy create(
            const Octane::ApiComboBoxItem *           items,
            const size_t                              nbOfItems,
            GRPCComboBoxChangedCallbackT             callback,
            void *                                    privateData
            );

    /// Destroys this combo box.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Sets one of the items to be the current selection.  This will set the ComboBox's text to
    /// that of the item that matches this ID.
    ///
    /// @param[in]  newItemId
    ///     the new item to select
    /// @param[in]  sendEvent
    ///     TRUE to send a change event for this combo box.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setSelectedId(
            const int                                 newItemId,
            const bool                                sendEvent
            );

    /// Returns the ID of the item that's currently shown in the box. If no item is selected, this
    /// will return 0.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int selectedId() const;

    /// Returns the text of the item currently selected in the combo box or an empty string if
    /// nothing is selected.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string text() const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
