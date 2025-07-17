// Copyright (C) 2025 OTOY NZ Ltd.

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


#include "apitable.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiTable
class ApiTableProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new table.
    ///
    /// @param[in]  columnHeaders
    ///     Array of strings, each string is a header for a column. There will be as many columns
    ///     in the table as there are strings passed in.
    /// @param[in]  columnHeadersLength
    ///     Length of the columnHeadersLength array.
    /// @param[in]  headerVisible
    ///     TRUE to make the table header visible.
    /// @param[in]  numRowsCallback
    ///     This callback must return how many rows there are currently in the table.
    /// @param[in]  contentForCellCallback
    ///     This should return the string content for a cell.
    /// @param[in]  selectionChangedCallback
    ///     Called when the user changes the row selection.
    /// @param[in]  privateData
    ///     Private module data, passed back untouched in the callbacks.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the newly created table. Do not delete this pointer but use destroy.
    static ApiTableProxy create(
            const char *                              columnHeaders[],
            const size_t                              columnHeadersLength,
            const bool                                headerVisible,
            Octane::ApiTable::NumRowsCallbackT        numRowsCallback,
            Octane::ApiTable::ContentCallbackT        contentForCellCallback,
            Octane::ApiTable::SelectionChangedCallbackT selectionChangedCallback,
            void *                                    privateData
            );

    /// Destroys this table.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Updates the content of the table. This needs to be called every time something in the data
    /// changes because otherwise the table won't refresh.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void updateContent();

    /// Selects a row.  If the row is already selected, this won't do anything.
    ///
    ///  @param[in] rowNumber
    ///     The row to select.
    ///  @param[in] dontScrollToShowThisRow
    ///     Iff true, the list's position won't change; if false and the selected row is
    ///     off-screen, it'll scroll to make sure that row is on-screen.
    /// @param[in] deselectOthersFirst
    ///     If true and there are multiple selections, these will first be deselected before this
    ///     item is selected
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void selectRow(
            const int                                 rowNumber,
            const bool                                dontScrollToShowThisRow,
            const bool                                deselectOthersFirst
            );

    /// Selects a set of rows. This will add these rows to the current selection, so you might
    /// need to clear the current selection first with deselectAllRows().
    ///
    /// @param[in] firstRow
    ///     The first row to select (inclusive).
    /// @param[in] lastRow
    ///     The last row to select (inclusive).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void selectRangeOfRows(
            const int                                 firstRow,
            const int                                 lastRow
            );

    /// Deselects a row. If it's not currently selected, this will do nothing.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void deselectRow(
            const int   rowNumber
            );

    /// Deselects any currently selected rows.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void deselectAllRows();

    /// Selects or deselects a row.  If the row's currently selected, this deselects it,
    /// and vice-versa.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void flipRowSelection(
            const int   rowNumber
            );

    /// Checks whether a row is selected.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isRowSelected(
            const int   rowNumber
            ) const;

    /// Returns the number of rows that are currently selected.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int numSelectedRows() const;

    /// Returns the row number of a selected row.  This will return the row number of the
    /// Nth selected row. The row numbers returned will be sorted in order from low to high.
    ///
    /// @param[in] index
    ///     the index of the selected row to return, (from 0 to getNumSelectedRows() - 1)
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     the row number, or -1 if the index was out of range or if there aren't any rows
    ///     selected
    int selectedRow(
            const int   index
            ) const;

    /// Returns the last row that the user selected.  This isn't the same as the highest row
    /// number that is currently selected - if the user had multiply-selected rows 10, 5 and then
    /// 6 in that order, this would return 6. If nothing is selected, it will return -1.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int lastRowSelected() const;

private:
    static GRPCSettings & getGRPCSettings();
};
