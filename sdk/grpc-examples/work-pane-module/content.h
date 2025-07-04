// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _CONTENT_H_
#define _CONTENT_H_ 1


// API includes
#include "octanegrpcwrappers.h"



//--------------------------------------------------------------------------------------------------
/// This class populates the passed in grid with random components. This is a very contrived 
/// example demonstrating how to use the different gui components.
class MainContent : public OctaneWrap::WorkPaneModule,
                    public OctaneWrap::ButtonListener,
                    public OctaneWrap::ColorSwatchListener,
                    public OctaneWrap::NumericBoxListener,
                    public OctaneWrap::TextEditorListener,
                    public OctaneWrap::CheckBoxListener,
                    public OctaneWrap::ComboBoxListener,
                    public OctaneWrap::MouseListener
{
public:

    // save button callback
    static bool toolbarSaveButtonClicked(
        void * userdata);

    // load button callback
    static bool toolbarLoadButtonClicked(
        void * userdata);

    // reload button callback
    static bool toolbarReloadButtonClicked(
        void * userdata);

    /// Constructor
    MainContent();

    /// Destructor.
    virtual ~MainContent();

    /// Function to handle the save button click call from the tool bar
    void onToolbarSaveButton();
    
    /// Function to handle the refresh button click call from the tool bar
    void onToolbarRefreshButton();
    
    /// Function to handle the open button click call from the tool bar
    void onToolbarOpenButton();

    //-- Implementation of OctaneWrap::WorkPaneModule --
    
    virtual void onInit(
        ApiGridLayoutProxy & parentGrid) override;

    //-- Implementation of ButtonListener --

    virtual void buttonClicked(
        OctaneWrap::TextButton & button) override;

    //-- Implementation of ColorSwatchListener --
 
    virtual void swatchValueChanged(
        OctaneWrap::ColorSwatch & swatch) override;

    //-- Implementation of NumericBoxListener --

    virtual void valueChanged(
        OctaneWrap::NumericBox & NumericBox) override;

    //-- Implementation of TextEditorListener --

    virtual void textChanged(
        OctaneWrap::TextEditor & TextEditor) override;

    //-- Implementation of CheckBoxListener --

    virtual void onClicked(
        OctaneWrap::CheckBox & checkBox) override;

    //-- Implementation of ComboBoxListener --

    virtual void comboBoxChanged(
        OctaneWrap::ComboBox & comboBox) override;

    //-- Implementation of MouseListener --

    virtual void mouseDoubleClick(
        const GRPCApiMouseEventData & event) override;

private:

    // image
    OctaneWrap::Image *                    mLogoImage;
    // test image
    OctaneWrap::Image*                     mTestImage;
    // test image counter
    uint32_t                               mTestImageCounter;
    // image component
    OctaneWrap::ImageComponent *           mImageComponent; 
    // Text editor
    OctaneWrap::TextEditor *               mNotesEditor;
    // file name with full path 
    std::string                            mFilename;
    // mix of random components
    std::vector<OctaneWrap::GuiComponent*> mComponents;

};



#endif // #ifndef _CONTENT_H_
