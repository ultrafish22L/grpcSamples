// Copyright (C) 2025 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapgridlayout.h"
// application includes
#include "apigridlayout.h"

using namespace OctaneWrap;


GridLayout::GridLayout()
//:
//    mApiGridLayout(NULL)
{
    mApiGridLayout = ApiGridLayoutProxy::create();
    mComponent     = &mApiGridLayout;
}


GridLayout::~GridLayout()
{
    mApiGridLayout.destroy();
    //mApiGridLayout = NULL;
}


void GridLayout::startSetup(
    const int borderX,
    const int borderY,
    const int paddingX,
    const int paddingY)
{
    mApiGridLayout.startSetup(borderX, borderY, paddingX, paddingY);
}


void GridLayout::endSetup()
{
    mApiGridLayout.endSetup();
}


void GridLayout::add(
    GuiComponent   &child,
    const uint32_t cellX,
    const uint32_t cellY)
{
    mApiGridLayout.add(*child.wrappedComponent(), cellX, cellY);
}


void GridLayout::addEmpty(
    const uint32_t cellX,
    const uint32_t cellY)
{
    mApiGridLayout.addEmpty(cellX, cellY);
}


void GridLayout::addSpan(
    GuiComponent   &child,
    const uint32_t minCellX,
    const uint32_t minCellY,
    const uint32_t maxCellX,
    const uint32_t maxCellY)
{
    mApiGridLayout.addSpan(*child.wrappedComponent(), minCellX, minCellY, maxCellX, maxCellY);
}


void GridLayout::setStartSize(
    const uint32_t cellX,
    const uint32_t cellY,
    const int      sizeX,
    const int      sizeY)
{
    mApiGridLayout.setStartSize(cellX, cellY, sizeX, sizeY);
}


void GridLayout::setRowElasticity(
    const uint32_t rowIx,
    const float    elasticity)
{
    mApiGridLayout.setRowElasticity(rowIx, elasticity);
}


void GridLayout::setColElasticity(
    const uint32_t columnIx,
    const float    elasticity)
{
    mApiGridLayout.setColElasticity(columnIx, elasticity);
}


void GridLayout::setElasticityForAllRows(
    const float elasticity)
{
    mApiGridLayout.setElasticityForAllRows(elasticity);
}


void GridLayout::setElasticityForAllCols(
    const float elasticity)
{
    mApiGridLayout.setElasticityForAllCols(elasticity);
}


void GridLayout::startNestedGrid(
    const uint32_t minCellX,
    const uint32_t minCellY,
    const uint32_t maxCellX,
    const uint32_t maxCellY,
    const int      borderX,
    const int      borderY,
    const int      paddingX,
    const int      paddingY)
{
    mApiGridLayout.startNestedGrid(minCellX,
                                    minCellY,
                                    maxCellX,
                                    maxCellY,
                                    borderX,
                                    borderY,
                                    paddingX,
                                    paddingY
                                    );
}


void GridLayout::endNestedGrid()
{
    mApiGridLayout.endNestedGrid();
}


int GridLayout::width() const
{
    return mApiGridLayout.width();
}


int GridLayout::height() const
{
    return mApiGridLayout.height();
}
