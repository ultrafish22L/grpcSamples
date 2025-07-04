// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _APP_WINDOW_H_
#define _APP_WINDOW_H_  1


// API includes
#include "octanegrpcwrappers.h"


class TexNodeModel;



//--------------------------------------------------------------------------------------------------
/// TexCommander application window.
class AppWindow : public OctaneWrap::Window,
                  public OctaneWrap::ButtonListener,
                  public OctaneWrap::SelectionObserver
{
public:

    /// Creates a new application window displaying the passed in tex node model.
    AppWindow(
        TexNodeModel &model);

    /// Destructor.
    virtual ~AppWindow();

    //-- Implementation of OctaneWrap::ButtonListener --

    virtual void buttonClicked(
        OctaneWrap::TextButton &button) override;

    //-- Implementation of OctaneWrap::SelectionManager --

    virtual void onSelectionChanged() override;

private:

    /// Reference to the table mode (not owned).
    TexNodeModel               &mTexNodeModel;
    /// Grid layout that holds it all together.
    OctaneWrap::GridLayout     *mGridLayout;
    /// Title that is above the table
    OctaneWrap::TitleComponent *mTableTitle;
    /// Table that displays the image textures of the current project.
    OctaneWrap::Table          *mTable;
    /// Button to load new textures.
    OctaneWrap::TextButton     *mLoadButton;
    /// Button to delete the selected texture.
    OctaneWrap::TextButton     *mDeleteButton;
};



#endif // #ifndef _APP_WINDOW_H_
