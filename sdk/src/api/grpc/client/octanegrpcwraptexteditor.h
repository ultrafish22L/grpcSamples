// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_TEXT_EDITOR_H_
#define _OCTANE_WRAP_TEXT_EDITOR_H_   1

// system includes
#include <string>
#include <vector>
// api includes
#include "octanetypes.h"
#include "octanegrpcwrapguicomponent.h"
#include "apitexteditorclient.h"

namespace Octane
{
    class ApiTextEditor;
}

namespace OctaneWrap
{

class TextEditor;

//--------------------------------------------------------------------------------------------------
/// Interface for text editor listeners.
class TextEditorListener
{
public:

    virtual void textChanged(
        OctaneWrap::TextEditor &textEditor) =0;
};



//--------------------------------------------------------------------------------------------------
/// Convenience wrapper for ApiTextEditor.
class TextEditor : public GuiComponent
{
    OCTANEAPI_NO_COPY(TextEditor);

public:

    /// Creates a text editor.
    ///
    /// @param[in]  nbOfLines
    ///     Number of lines in the editor.
    TextEditor(
        const unsigned int nbOfLines);

    /// Destructs this text editor.
    virtual ~TextEditor();

    /// Returns the text the user typed in the text editor.
    std::string text() const;

    /// Returns TRUE if there's no text in the text editor.
    bool isEmpty() const;

    /// Sets the text in the text editor.
    ///
    /// @param[in]  newText
    ///     New text that replaces the existing text.
    /// @param[in]  sendEvent
    ///     TRUE to call the change callback for this event.
    void setText(
        const std::string &newText,
        const bool        sendEvent);

    /// Clears the text in the text editor.
    void clear();

    /// Changes the text editor to read only mode.
    void setReadOnly(
        const bool shouldBeReadOnly);

    /// Returns true if the editor is in read-only mode.
    bool isReadOnly() const;

    /// Adds a listener.
    void addListener(
        TextEditorListener &listener);

    /// Removes a listener.
    void removeListener(
        TextEditorListener &listener);

private:

    /// Wrapped TextEditor
    OctaneGRPC::ApiTextEditorProxy   mApiTextEditor;
    /// List of listeners.
    std::vector<TextEditorListener*> mListeners;

    /// internal C callback
    static void onTextChanged(
        OctaneGRPC::ApiTextEditorProxy & TextEditor,
        void *                           privateData);
};

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_TEXT_EDITOR_H_
