// Copyright (C) 2025 OTOY NZ Ltd.

// application includes
#include "texnodemodel.h"
// myself
#include "appwindow.h"
#include "apiselectionmanagerclient.h"

AppWindow::AppWindow(
    TexNodeModel &model)
:
    OctaneWrap::Window("TexCommander"),
    mTexNodeModel(model),
    mGridLayout(new OctaneWrap::GridLayout),
    mTableTitle(NULL),
    mTable(NULL),
    mLoadButton(NULL),
    mDeleteButton(NULL)
{
    // setup the gui
    int row = 0;
    mGridLayout->startSetup();
    {
        // title above the table
        mTableTitle = new OctaneWrap::TitleComponent("Texture nodes");
        mGridLayout->add(*mTableTitle, 0, row);
        mGridLayout->setRowElasticity(row, 0.f);
        ++row;

        // table with the texture overview
        std::vector<std::string> headers;
        headers.push_back("Node name");
        headers.push_back("Image source");
        mTable = new OctaneWrap::Table(model, headers, true);
        mTexNodeModel.setTable(mTable);
        mTable->setSize(480, 640);
        mGridLayout->add(*mTable, 0, row);
        ++row;

        // nested button grid
        mGridLayout->startNestedGrid(0, row, 0, row, 0, 0);
        {
            int col = 0;

            mLoadButton = new OctaneWrap::TextButton("Load...");
            mGridLayout->add(*mLoadButton, col, 0);
            mLoadButton->addListener(*this);
            ++col;

            mDeleteButton = new OctaneWrap::TextButton("Delete");
            mGridLayout->add(*mDeleteButton, col, 0);
            mDeleteButton->addListener(*this);
            ++col;

            mGridLayout->setElasticityForAllCols(0.f);
        }
        mGridLayout->endNestedGrid();
        mGridLayout->setRowElasticity(row, 0.f);
    }
    mGridLayout->endSetup();

    addContentComponent(*mGridLayout);
    setSize(mGridLayout->width(), mGridLayout->height());

    // listen for selection changes
    ApiSelectionManagerProxy::addSelectionObserver(*this);
}


AppWindow::~AppWindow()
{
    mTexNodeModel.setTable(NULL);

    // stop listening for selection changes
    ApiSelectionManagerProxy::removeSelectionObserver(*this);

    // delete components
    delete mTableTitle;
    delete mTable;
    delete mLoadButton;
    delete mDeleteButton;
}


void AppWindow::buttonClicked(
    OctaneWrap::TextButton &button)
{
    // load some images
    if (&button == mLoadButton)
    {
        OctaneWrap::FileChooser fileChooser("Select image files", "", "*.png;*.jpg;*.gif;*.exr");
        if (fileChooser.browseForMultipleFilesToOpen())
        {
            std::vector<std::string> results = fileChooser.results();
            for (size_t i=0; i<results.size(); ++i)
            {
                mTexNodeModel.addTextureNode(results[i]);
            }
        }
    }
    // delete the selected texture
    else if (&button == mDeleteButton)
    {
        mTexNodeModel.deleteTextureNode(mTable->lastRowSelected());
    }
}


void AppWindow::onSelectionChanged()
{
    // nothing selected
    if (ApiSelectionManagerProxy::selectedItemCount() == 0)
    {
        mTable->deselectAllRows();
        return;
    }

    // figure out the current selection
    //Octane::ApiArray<Octane::ApiItem*> selectedItemsArray;
    std::vector<ApiItemProxy> selectedItemsArray;
    ApiSelectionManagerProxy::getSelection(selectedItemsArray);

    std::vector<ApiItemProxy*> selectedItems;
    for (auto & t : selectedItemsArray)
    {
        selectedItems.push_back(&t);
    }

   // std::vector<ApiItemProxy*> selectedItems = OctaneWrap::toVector(selectedItemsArray);
    Octane::ApiArray<ApiItemProxy*> selectedItemsApiArray(selectedItems.data(), selectedItems.size());
    //ApiSelectionManagerProxy::deleteSelectionArray(selectedItemsApiArray, status);

    // select the first selected image texture
    for (size_t i=0; i<selectedItems.size(); ++i)
    {
        if (selectedItems[i]->isNode() 
            && selectedItems[i]->toNode().type() == Octane::NT_TEX_IMAGE)
        {
            mTable->selectRow(mTexNodeModel.rowForNode(selectedItems[i]->toNode()));
            break;
        }
    }
}
