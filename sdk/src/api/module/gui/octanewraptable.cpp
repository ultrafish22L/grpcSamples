// Copyright (C) 2026 OTOY NZ Ltd.

// application includes
#include "apitable.h"
// myself
#include "octanewraptable.h"

using namespace OctaneWrap;

//--------------------------------------------------------------------------------------------------
// Implementation of Table.

Table::Table(
    TableModel                     &model,
    const std::vector<std::string> &columnHeaders,
    const bool                     headerVisible)
:
    mApiTable(NULL),
    mModel(model)
{
    std::vector<const char*> cHeaders(columnHeaders.size(), NULL);
    for (size_t i=0; i<columnHeaders.size(); ++i)
    {
        cHeaders[i] = columnHeaders[i].c_str();
    }

    mApiTable = Octane::ApiTable::create(cHeaders.data(),
                                         columnHeaders.size(),
                                         headerVisible,
                                         numRowsCallback,
                                         cellDataCallback,
                                         selectionChangedCallback,
                                         this);
    mComponent = mApiTable;
}


Table::~Table()
{
    mApiTable->destroy();
    mApiTable = NULL;
}


void Table::updateContent()
{
    mApiTable->updateContent();
}


void Table::selectRow(
    const int  rowNumber,
    const bool dontScrollToShowThisRow,
    const bool deselectOthersFirst)
{
    mApiTable->selectRow(rowNumber, dontScrollToShowThisRow, deselectOthersFirst);
}


void Table::selectRangeOfRows(
    const int firstRow,
    const int lastRow)
{
    mApiTable->selectRangeOfRows(firstRow, lastRow);
}


void Table::deselectRow(
    const int rowNumber)
{
    mApiTable->deselectRow(rowNumber);
}


void Table::deselectAllRows()
{
    mApiTable->deselectAllRows();
}


void Table::flipRowSelection(
    const int rowNumber)
{
    mApiTable->flipRowSelection(rowNumber);
}


bool Table::isRowSelected(
    const int rowNumber) const
{
    return mApiTable->isRowSelected(rowNumber);
}


int Table::numSelectedRows() const
{
    return mApiTable->numSelectedRows();
}


int Table::selectedRow(
    const int index) const
{
    return mApiTable->selectedRow(index);
}


int Table::lastRowSelected() const
{
    return mApiTable->lastRowSelected();
}


int Table::numRowsCallback(
    void *privateData)
{
    return static_cast<Table*>(privateData)->mModel.numRows();
}


const char* Table::cellDataCallback(
    const int row,
    const int column,
    void      *privateData)
{
    Table* table = static_cast<Table*>(privateData);
    table->mLastCellData = table->mModel.cellData(row, column);
    return table->mLastCellData.c_str();
}


void Table::selectionChangedCallback(
    const int lastRowSelected,
    void      *privateData)
{
    return static_cast<Table*>(privateData)->mModel.onSelectionChange(lastRowSelected);
}
