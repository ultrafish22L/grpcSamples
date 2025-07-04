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
class ApiGuiComponentProxy;
#include "apiguicomponentclient.h"


#include "apigridlayout.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiGridLayout
class ApiGridLayoutProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new ApiGridLayout or returns a NULL pointer when creation failed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static ApiGridLayoutProxy create(            );

    /// Destroys the component created with create().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy(            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void startSetup(
            const int                                 borderX,
            const int                                 borderY,
            const int                                 paddingX,
            const int                                 paddingY
            );

    /// Creates the initial layout and resizes the parent component accordingly. After that, no
    /// components can be added anymore.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void endSetup(            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void add(
            ApiGuiComponentProxy &                    child,
            const uint32_t                            cellX,
            const uint32_t                            cellY
            );

    /// Add a new empty grid cell. This will make sure that the dimensions of the grid are extended
    /// to fit this cell.
    ///
    /// @param[in]  cellX
    ///     The row of the empty grid cell. The grid will be automatically extended if necessary.
    /// @param[in]  cellY
    ///     The column of the empty grid cell. The grid will be automatically extended if necessary.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addEmpty(
            const uint32_t                            cellX,
            const uint32_t                            cellY
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addSpan(
            ApiGuiComponentProxy &                    child,
            const uint32_t                            minCellX,
            const uint32_t                            minCellY,
            const uint32_t                            maxCellX,
            const uint32_t                            maxCellY
            );

    /// Sets a minimum start size for a cell during the layout setup.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setStartSize(
            const uint32_t                            cellX,
            const uint32_t                            cellY,
            const int                                 sizeX,
            const int                                 sizeY
            );

    /// Sets the stretch factor of a row.
    ///
    /// @param[in]  rowIx
    ///     The index of the rowIx.
    /// @param[in]  elasticity
    ///     The elasticity (must be >= 0).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setRowElasticity(
            const uint32_t                            rowIx,
            const float                               elasticity
            );

    /// Sets the stretch factor of a column.
    ///
    /// @param[in]  columnIx
    ///     The index of the column.
    /// @param[in]  elasticity
    ///     The elasticity (must be >= 0).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setColElasticity(
            const uint32_t                            columnIx,
            const float                               elasticity
            );

    /// Sets the elasticity for all the rows in the grid (which is the current active grid, i.e.
    /// this can be a sub-grid).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setElasticityForAllRows(
            const float                               elasticity
            );

    /// Sets the elasticity for all the colums in the grid (which is the current active grid, i.e.
    /// this can be a sub-grid).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setElasticityForAllCols(
            const float                               elasticity
            );

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
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void startNestedGrid(
            const uint32_t                            minCellX,
            const uint32_t                            minCellY,
            const uint32_t                            maxCellX,
            const uint32_t                            maxCellY,
            const int                                 borderX,
            const int                                 borderY,
            const int                                 paddingX,
            const int                                 paddingY
            );

    /// Finishes the current nested grid and switches the context back to the parent grid.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void endNestedGrid(            );

    /// Returns the current width of the grid in pixels.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int width(            ) const;

    /// Returns the current height of the grid in pixels.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int height(            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
