// Copyright (C) 2025 OTOY NZ Ltd.

// system includes
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <vector>
// module includes
#include "octanelogo.h"
// myself
#include "content.h"

#include "apibase64client.h"
#include "apilogmanagerclient.h"
#include "grpcmouseevent.h"

// create a log flag
//API_DLOG_DECLARE(gui, "module", "module example logging");



bool MainContent::toolbarSaveButtonClicked(
    void * userdata)
{
    if (userdata)
    {
        static_cast<MainContent*>(userdata)->onToolbarSaveButton();
    }
    return true;
}


bool MainContent::toolbarLoadButtonClicked(
    void * userdata)
{
    if (userdata)
    {
        static_cast<MainContent*>(userdata)->onToolbarOpenButton();
    }
    return true;
}


bool MainContent::toolbarReloadButtonClicked(
    void * userdata)
{
    if (userdata)
    {
        static_cast<MainContent*>(userdata)->onToolbarRefreshButton();
    }
    return true;
}


MainContent::MainContent()
:
    mLogoImage(nullptr),
    mTestImage(nullptr),
    mTestImageCounter(0),
    mImageComponent(nullptr)
{}


MainContent::~MainContent()
{
    delete mLogoImage;
    // delete all the components
    for (size_t i=0; i<mComponents.size(); ++i)
    {
        delete mComponents[i];
    }
    mComponents.clear();
}


void MainContent::onToolbarSaveButton()
{
    // selecting the file from the disk
    if (mFilename.empty())
    {
        OctaneWrap::FileChooser chooser("Save Notes","", "*.txt");
        if (chooser.browseForFileToSave(true))
        {
           mFilename = chooser.result();
        }
    }

    // write the data to the file
    if (!mFilename.empty())
    {
        std::fstream file;
        file.open(mFilename.c_str(), std::fstream::out);
        file<< mNotesEditor->text().c_str();
        file.close();
    }
    onToolbarRefreshButton();
}


void MainContent::onToolbarRefreshButton()
{
    // read the data from the file
    if (!mFilename.empty())
    {
        std::ifstream file;
        file.open(mFilename.c_str());
        if (file.is_open())
        {
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            mNotesEditor->setText(content, false);
            file.close();
        }
    }
}


void MainContent::onToolbarOpenButton()
{
    // open a file
    OctaneWrap::FileChooser chooser("Save Notes","", "*.txt");
    if (chooser.browseForFileToSave(false))
    {
         mFilename = chooser.result();
    }
    // refresh the notes text editor
    onToolbarRefreshButton(); 
}


void MainContent::onInit(
    ApiGridLayoutProxy & parentGrid)
{
     // use all the components we have
    parentGrid.startSetup(-1, -1, -1, -1);
    {
        int row = 0;

        // create text button
        mComponents.push_back(new OctaneWrap::Label("Text button: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        OctaneWrap::TextButton *textButton = new OctaneWrap::TextButton("Button");
        textButton->addListener(*this);
        mComponents.push_back(textButton);
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // create numeric box
        mComponents.push_back(new OctaneWrap::Label("Numeric box: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        OctaneWrap::NumericBox *numericBox = new OctaneWrap::NumericBox(1);
        numericBox->addListener(*this);
        mComponents.push_back(numericBox);
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // create text editor
        mComponents.push_back(new OctaneWrap::Label("Text editor: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        OctaneWrap::TextEditor *editor = new OctaneWrap::TextEditor(1);
        editor->addListener(*this);
        mComponents.push_back(editor);
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // create check box
        mComponents.push_back(new OctaneWrap::Label("Check box: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        OctaneWrap::CheckBox *checkBox = new OctaneWrap::CheckBox("Check me out");
        checkBox->addListener(*this);
        mComponents.push_back(checkBox);
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // create progress bar
        mComponents.push_back(new OctaneWrap::Label("Progress bar: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        OctaneWrap::ProgressBar *bar = new OctaneWrap::ProgressBar();
        bar->setProgress(0.5);
        bar->setText("progress bar");
        mComponents.push_back(bar);
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // create title component
        mComponents.push_back(new OctaneWrap::Label("Title component: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        mComponents.push_back(new OctaneWrap::TitleComponent("Title component"));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // create image component (can fail)
        {

            Octane::CharArrayT decoded;
            if (ApiBase64Proxy::decode(gOctaneLogo, gOctaneLogoSize, decoded, false))
            {
                mLogoImage = OctaneWrap::Image::loadFromMemory(decoded.mData, decoded.mSize);
                if (!mLogoImage)
                {
                    ApiLogManagerProxy::logError("failed to create image");
                }
            }
            else
            {
                ApiLogManagerProxy::logError("failed to decode logo");
            }

            //ApiBase64Proxy::cleanupResult(decoded);

            // only create the image component if the image was created
            if (mLogoImage)
            {
                mComponents.push_back(new OctaneWrap::Label("Image component: "));
                parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
                mImageComponent = new OctaneWrap::ImageComponent(*mLogoImage);
                mImageComponent->setTooltip("double-click will change the image");
                mImageComponent->addMouseListener(this);
                mComponents.push_back(mImageComponent);
                parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
                ++row;

                // create uninitialized test image, based on the size of the logo image
                mTestImage = new OctaneWrap::Image(
                    Octane::ApiImage::PIXEL_FORMAT_ABGR, mLogoImage->width(), mLogoImage->height(), false);
            }
        }

        // create color swatch
        mComponents.push_back(new OctaneWrap::Label("Color swatch: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        OctaneWrap::ColorSwatch *swatch = new OctaneWrap::ColorSwatch(false);
        swatch->addListener(*this);
        mComponents.push_back(swatch);
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // create combo box
        mComponents.push_back(new OctaneWrap::Label("Combo box: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        std::vector<OctaneWrap::ComboBoxItem> items;
        items.push_back(OctaneWrap::ComboBoxItem(1, "Cinema4D"));
        items.push_back(OctaneWrap::ComboBoxItem(2, "3DS Max"));
        items.push_back(OctaneWrap::ComboBoxItem(3, "Maya"));
        items.push_back(OctaneWrap::ComboBoxItem(4, "Houdini"));
        items.push_back(OctaneWrap::ComboBoxItem(5, "LightWave"));
        items.push_back(OctaneWrap::ComboBoxItem(6, "Modo"));
        OctaneWrap::ComboBox *box = new OctaneWrap::ComboBox(items);
        box->setSelectedId(1, false);
        box->addListener(*this);
        mComponents.push_back(box);
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // create notes text editor
        mComponents.push_back(new OctaneWrap::Label("Notes: "));
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 0, row);
        mNotesEditor = new OctaneWrap::TextEditor(10);
        mNotesEditor->setText(
            "The text in this editor will be saved to disk, If the save button in the toolbar " 
            "is pressed.", false);
        mNotesEditor->addListener(*this);
        mComponents.push_back(mNotesEditor);
        parentGrid.add(*(mComponents.back())->wrappedComponent(), 1, row);
        ++row;

        // only stretch the second column
        parentGrid.setColElasticity(0, 0.f);
        parentGrid.setElasticityForAllRows(0.f);
    }
    parentGrid.endSetup();
}


void MainContent::buttonClicked(
    OctaneWrap::TextButton & button)
{

    // test the file chooser
    OctaneWrap::FileChooser chooser("File chooser test");
    if (chooser.browseForFileToOpen())
    {
        OctaneWrap::FileName fileName(chooser.result());

        // lets do some more test
        fileName = fileName.getParent();
        fileName += "testing.cpp";

        fileName = OctaneWrap::FileName("/home/thomas") + OctaneWrap::FileName("/dev/test.txt");
    }
}


void MainContent::swatchValueChanged(
    OctaneWrap::ColorSwatch & swatch)
{
    Octane::ApiColorHdr color = swatch.color();
  //  API_DLOG(gui, "swatch changed to color: (%f, %f, %f, %f)", color.r, color.g, color.b, color.a);
}


void MainContent::valueChanged(
    OctaneWrap::NumericBox & numericBox)
{
    //API_DLOG(gui, "numeric box value changed: %f", numericBox.value());
}


void MainContent::textChanged(
    OctaneWrap::TextEditor & textEditor)
{
    //API_DLOG(gui, "text editor text changed: '%s'", textEditor.text().c_str());
}


void MainContent::onClicked(
    OctaneWrap::CheckBox & checkBox)
{
    //API_DLOG(gui, "check box state: %d", checkBox.isChecked());
}


void MainContent::comboBoxChanged(
    OctaneWrap::ComboBox & comboBox)
{
    //API_DLOG(gui, "combo box selected item: '%s'", comboBox.text().c_str());
}


void MainContent::mouseDoubleClick(
    const GRPCApiMouseEventData & eventdata)
{
    // double click on the image component causes it to switch between different ApiImages
    if (eventdata.mEventComponent && eventdata.mEventComponent == mImageComponent->wrappedComponent())
    {
        ++mTestImageCounter;
        // odd counter -> show test image (with gradient)
        if (mTestImageCounter & 1)
        {
            // update test image to gradient based on the second bit of the counter
            std::vector<uint8_t> buffer(4u * mTestImage->width() * mTestImage->height());
            uint32_t channelX, channelY, channelZ;
            if (mTestImageCounter & 2)
            {
                channelX = 2;   // -> red
                channelY = 1;   // -> green
                channelZ = 0;   // -> blue
            }
            else
            {
                channelX = 0;   // -> blue
                channelY = 1;   // -> green
                channelZ = 2;   // -> red
            }
            
            // update test image
            uint8_t * dstP = buffer.data();
            for (uint32_t y=0, height=mTestImage->height(); y<height; ++y)
            {
                for (uint32_t x=0, width=mTestImage->width(); x<width; ++x, dstP+=4)
                {
                    const float xVal = (float)x / width;
                    const float yVal = (float)y / height;
                    const float alpha = std::max(xVal, yVal);
                    dstP[channelX] = (uint8_t)(xVal * alpha * 255);
                    dstP[channelY] = (uint8_t)(yVal * alpha * 255);
                    dstP[channelZ] = 0;
                    dstP[3] = (uint8_t)(alpha * 255);
                }
            }
            
            mTestImage->updateTo(buffer.data(), buffer.size());
            mImageComponent->updateTo(*mTestImage);
        }
        // even counter -> show logo image
        else
        {
            mImageComponent->updateTo(*mLogoImage);
        }
    }
}


// base 64-encoded octane logo
