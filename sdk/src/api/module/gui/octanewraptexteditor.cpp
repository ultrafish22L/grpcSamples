// Copyright (C) 2026 OTOY NZ Ltd.

// system includes
#include <algorithm>
// application includes
#include "apitexteditor.h"
// myself
#include "octanewraptexteditor.h"

using namespace OctaneWrap;


TextEditor::TextEditor(
    const unsigned int nbOfLines)
:
    mApiTextEditor(NULL)
{
    mApiTextEditor = Octane::ApiTextEditor::create(nbOfLines, onTextChanged, this);
    mComponent     = mApiTextEditor;
}


TextEditor::~TextEditor()
{
    mApiTextEditor->destroy();
    mApiTextEditor = NULL;
}


std::string TextEditor::text() const
{
    return std::string(mApiTextEditor->text());
}


bool TextEditor::isEmpty() const
{
    return mApiTextEditor->isEmpty();
}


void TextEditor::setText(
    const std::string &newText,
    const bool        sendEvent)
{
    mApiTextEditor->setText(newText.c_str(), sendEvent);
}


void TextEditor::clear()
{
    mApiTextEditor->clear();
}


void TextEditor::setReadOnly(
    const bool shouldBeReadOnly)
{
    mApiTextEditor->setReadOnly(shouldBeReadOnly);
}


bool TextEditor::isReadOnly() const
{
    return mApiTextEditor->isReadOnly();
}
 

void TextEditor::addListener(
    TextEditorListener &listener)
{
    mListeners.push_back(&listener);
}


void TextEditor::removeListener(
    TextEditorListener &listener)
{
    mListeners.erase(std::find(mListeners.begin(), mListeners.end(), &listener));
}


void TextEditor::onTextChanged(
    Octane::ApiTextEditor &textEditor,
    void                  *privateData)
{
    TextEditor *myEditor = static_cast<TextEditor*>(privateData);
    // notify listeners
    for (size_t i=0; i<myEditor->mListeners.size(); ++i)
    {
        myEditor->mListeners[i]->textChanged(*myEditor);
    }
}
