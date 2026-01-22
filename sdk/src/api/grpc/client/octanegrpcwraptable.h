// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_TABLE_H_
#define _OCTANE_WRAP_TABLE_H_   1

// system includes
#include <string>
#include <vector>
// application includes
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apitableclient.h"

namespace Octane
{
class ApiTable;
}

namespace OctaneWrap
{

//--------------------------------------------------------------------------------------------------
/// Interface for a data model.
class TableModel
{
public:    

    /// Returns the number of rows in the table.
    virtual int numRows() =0;

    /// Returns the string data for the passed in cell.
    virtual std::string cellData(
        const int row,
        const int column) =0;

    /// Called when the selection changes in the table.
    ///
    /// @param[in]  lastRowSelected
    ///     The last row that the user selected. If no rows are selected, this shall be -1.
    virtual void onSelectionChange(
        const int lastRowSelected) =0;
};



//--------------------------------------------------------------------------------------------------
/// Component to display tabular data. Wraps the ApiTable. The data is driven by an object that
/// implements the table model.
class Table : public GuiComponent
{
    OCTANEAPI_NO_COPY(Table);

public:

    /// Creates a new table.
    /// 
    /// @param[in]  model
    ///     Model that populates the table. This model should stay valid for the lifetime of this
    ///     table.
    /// @param[in]  columnHeaders
    ///     List of strings that will be the column titles.
    /// @param[in]  headerVisible
    ///     TRUE to display the header, FALSE to hide it.
    Table(
        TableModel                     &model,
        const std::vector<std::string> &columnHeaders,
        const bool                     headerVisible);

    /// Destructs this table.
    virtual ~Table();

    /// Updates the content of the table. This needs to be called every time something in the data
    /// changes because otherwise the table won't refresh.
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
    void selectRow(
        const int  rowNumber,
        const bool dontScrollToShowThisRow = false,
        const bool deselectOthersFirst     = true);

    /// Selects a set of rows. This will add these rows to the current selection, so you might
    /// need to clear the current selection first with deselectAllRows().
    ///
    /// @param[in] firstRow
    ///     The first row to select (inclusive).
    /// @param[in] lastRow
    ///     The last row to select (inclusive).
    void selectRangeOfRows(
        const int firstRow,
        const int lastRow);

    /// Deselects a row. If it's not currently selected, this will do nothing.
    void deselectRow(
        const int rowNumber);

    /// Deselects any currently selected rows.
    void deselectAllRows();

    /// Selects or deselects a row.  If the row's currently selected, this deselects it,
    /// and vice-versa.
    void flipRowSelection(
        const int rowNumber);

    /// Checks whether a row is selected.
    bool isRowSelected(
        const int rowNumber) const;

    /// Returns the number of rows that are currently selected.
    int numSelectedRows() const;

    /// Returns the row number of a selected row.  This will return the row number of the
    /// Nth selected row. The row numbers returned will be sorted in order from low to high.
    ///
    /// @param[in] index
    ///     the index of the selected row to return, (from 0 to getNumSelectedRows() - 1)
    /// @return
    ///     the row number, or -1 if the index was out of range or if there aren't any rows
    ///     selected
    int selectedRow(
        const int index = 0) const;

    /// Returns the last row that the user selected.  This isn't the same as the highest row
    /// number that is currently selected - if the user had multiply-selected rows 10, 5 and then
    /// 6 in that order, this would return 6. If nothing is selected, it will return -1.
    int lastRowSelected() const;

private:

    /// The API table we are wrapping.
    OctaneGRPC::ApiTableProxy   mApiTable;
    /// Data driver for this table.
    TableModel       &mModel;
    /// Stores the last returned cell data.
    std::string      mLastCellData; 

    static int numRowsCallback(
        void *privateData);

    static const char* cellDataCallback(
        const int row,
        const int column,
        void      *privateData);

    static void selectionChangedCallback(
        const int lastRowSelected,
        void      *privateData);
};

} // namespace Octane


#endif // #ifndef _OCTANE_WRAP_TABLE_H_
