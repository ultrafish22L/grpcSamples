// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_TEXT_EDITOR_H_
#define _API_TEXT_EDITOR_H_ 1

#include "apiguicomponent.h"
#include "octanetypes.h"

namespace Octane
{
    
//--------------------------------------------------------------------------------------------------
/// Text input field.
class OCTANEAPI_DECL ApiTextEditor : public ApiGuiComponent
{
    OCTANEAPI_NO_COPY(ApiTextEditor);

public:

    /// types
    typedef void (*TextEditorChangedCallbackT)(ApiTextEditor&, void*);

    /// Creates a new text editor.
    ///
    /// @param[in]  nbOfLines
    ///     Number of lines in the text editor.
    /// @param[in]  callback
    ///     Called when the text editor changes.
    /// @param[in]  privateData
    ///     Private data passed back into the callback.
    /// @return
    ///     Pointer to a text editor.
    static ApiTextEditor* create(
        const unsigned int         nbOfLines,
        TextEditorChangedCallbackT callback,
        void                       *privateData);

    /// Destroys this text editor.
    void destroy();

    /// Returns the text the user typed in the text editor.
    const char* text() const;

    /// Returns TRUE if there's no text in the text editor.
    bool isEmpty() const;

    /// Sets the text in the text editor.
    ///
    /// @param[in]  newText
    ///     New text that replaces the existing text.
    /// @param[in]  sendEvent
    ///     TRUE to call the change callback for this event.
    void setText(
        const char *newText,
        const bool sendEvent);

    /// Clears the text in the text editor.
    void clear();

    /// Changes the text editor to read only mode.
    void setReadOnly(
        const bool shouldBeReadOnly);

    /// Returns true if the editor is in read-only mode.
    bool isReadOnly() const;

private:

    ApiTextEditor();
};

} // namespace Octane


#endif // #ifndef _API_TEXT_EDITOR_H_
