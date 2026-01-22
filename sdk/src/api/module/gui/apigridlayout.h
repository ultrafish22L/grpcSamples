// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_GRID_LAYOUT_H_
#define _API_GRID_LAYOUT_H_ 1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// Arranges it's child components into a resizable grid layout. The grid itself is not visible.
/// The grids arranges cells in rows or columns. Cells can be empty or components can occupy
/// multiple grid cells. Cells can also contain nested grids.
///
/// The grid can stretch beyond it's initial size but it cannot shrink beyond it's initial size.
/// You should setup the grid with the minimum initial size of the components. 
class OCTANEAPI_DECL ApiGridLayout : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiGridLayout);

public:

    /// Creates a new ApiGridLayout or returns a NULL pointer when creation failed.
    static ApiGridLayout* create();

    /// Destroys the component created with create().
    void destroy();

    /// Starts the set up phase, where components can be added to the grid.
    ///
    /// @param[in]  borderX  (optional)
    ///     The horizontal margin that should be used left and right around the grid. If negative
    ///     (default), the window margin of the look and feel is used.
    /// @param[in]  borderY  (optional)
    ///     The vertical margin that should be used top and bottom around the grid. If negative
    ///     (default), the window margin of the look and feel is used.
    /// @param[in]  paddingX  (optional)
    ///     The default padding that will be used between columns. If the value is negative
    ///     (default) the standard padding of the look and feel will be used.
    /// @param[in]  paddingY
    ///     The default padding that will be used between rows . If the value is negative
    ///     (default) the standard padding of the look and feel will be used.
    void startSetup(
        const int borderX  = -1,
        const int borderY  = -1,
        const int paddingX = -1,
        const int paddingY = -1);

    /// Creates the initial layout and resizes the parent component accordingly. After that, no
    /// components can be added anymore.
    void endSetup();

    /// Adds a new component to a grid cell.
    ///
    /// @param[in]  child
    ///     The component to add. The layout will NOT take ownership of the component. I.e. the
    ///     component must stay valid as long as the layout stores this component.
    /// @param[in]  cellX
    ///     The row of the grid cell where the component will be placed. The grid will be
    ///     automatically extended if necessary.
    /// @param[in]  cellY
    ///     The column of the grid cell where the component will be placed. The grid will be
    ///     automatically extended if necessary.
    void add(
        ApiGuiComponent &child,
        const uint32_t  cellX,
        const uint32_t  cellY);

    /// Add a new empty grid cell. This will make sure that the dimensions of the grid are extended
    /// to fit this cell.
    ///
    /// @param[in]  cellX
    ///     The row of the empty grid cell. The grid will be automatically extended if necessary.
    /// @param[in]  cellY
    ///     The column of the empty grid cell. The grid will be automatically extended if necessary.
    void addEmpty(
        const uint32_t cellX,
        const uint32_t cellY);

    /// Adds a new component spanning multiple cells of the grid.
    ///
    /// @param[in]  child
    ///     Component to add in the span.
    /// @param[in]  minCellX
    ///     The first column of the span.
    /// @param[in]  minCellY
    ///     The first row of the span.
    /// @param[in]  maxCellX
    ///     The last column of the span.
    /// @param[in]  maxCellY
    ///     The last row of the span.
    void addSpan(
        ApiGuiComponent &child,
        const uint32_t  minCellX,
        const uint32_t  minCellY,
        const uint32_t  maxCellX,
        const uint32_t  maxCellY);

    /// Sets a minimum start size for a cell during the layout setup.
    void setStartSize(
        const uint32_t cellX,
        const uint32_t cellY,
        const int      sizeX,
        const int      sizeY);

    /// Sets the stretch factor of a row.
    ///
    /// @param[in]  rowIx
    ///     The index of the rowIx.
    /// @param[in]  elasticity
    ///     The elasticity (must be >= 0).
    void setRowElasticity(
        const uint32_t rowIx,
        const float    elasticity);

    /// Sets the stretch factor of a column.
    ///
    /// @param[in]  columnIx
    ///     The index of the column.
    /// @param[in]  elasticity
    ///     The elasticity (must be >= 0).
    void setColElasticity(
        const uint32_t columnIx,
        const float    elasticity);

    /// Sets the elasticity for all the rows in the grid (which is the current active grid, i.e.
    /// this can be a sub-grid).
    void setElasticityForAllRows(
        const float elasticity);

    /// Sets the elasticity for all the colums in the grid (which is the current active grid, i.e.
    /// this can be a sub-grid).
    void setElasticityForAllCols(
        const float elasticity);

    /// Starts a new nested grid. All components that will be added after startNestedGrid() will
    /// go into the nest grid until endNestedGrid() has been called.
    ///
    /// @param[in]  minCellX
    ///     The row of the start of the cell range the nested grid will be placed in.
    /// @param[in]  minCellY
    ///     The column of the start of the cell range the nested grid will be placed in.
    /// @param[in]  maxCellX
    ///     The row of the end of the cell range the nested grid will be placed in.
    /// @param[in]  maxCellY
    ///     The column of the end of the cell range the nested grid will be placed in.
    /// @param[in]  borderX  (optional)
    ///     The horizontal margin that should be used left and right around the grid. If negative
    ///     (default), the window margin of the look and feel is used.
    /// @param[in]  borderY  (optional)
    ///     The vertical margin that should be used top and bottom around the grid. If negative
    ///     (default), the window margin of the look and feel is used.
    /// @param[in]  paddingX  (optional)
    ///     The default padding that will be used between columns. If the value is negative or
    ///     not specified the standard padding of the look and feel will be used.
    /// @param[in]  paddingY
    ///     The default padding that will be used between rows. If the value is negative or
    ///     not specified the standard padding of the look and feel will be used.
    void startNestedGrid(
        const uint32_t minCellX,
        const uint32_t minCellY,
        const uint32_t maxCellX,
        const uint32_t maxCellY,
        const int      borderX = -1,
        const int      borderY = -1,
        const int      paddingX = -1,
        const int      paddingY = -1);

    /// Finishes the current nested grid and switches the context back to the parent grid.
    void endNestedGrid();

    /// Returns the current width of the grid in pixels.
    int width() const;

    /// Returns the current height of the grid in pixels.
    int height() const;

private:

    /// Create via the create() function.
    ApiGridLayout();
};

} // namespace Octane


#endif // #ifndef _API_GRID_LAYOUT_H_
