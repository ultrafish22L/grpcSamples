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
#include "apiguicomponentclient.h"


#include "apitexteditor.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiTextEditor
class ApiTextEditorProxy : public ApiGuiComponentProxy
{
public:
    /// Creates a new text editor.
    ///
    /// @param[in]  nbOfLines
    ///     Number of lines in the text editor.
    /// @param[in]  callback
    ///     Called when the text editor changes.
    /// @param[in]  privateData
    ///     Private data passed back into the callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to a text editor.
    static ApiTextEditorProxy create(
            const unsigned int                        nbOfLines,
            GRPCTextEditorChangedCallbackT           callback,
            void *                                    privateData
            );

    /// Destroys this text editor.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy(            );

    /// Returns the text the user typed in the text editor.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string text(            ) const;

    /// Returns TRUE if there's no text in the text editor.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isEmpty(            ) const;

    /// Sets the text in the text editor.
    ///
    /// @param[in]  newText
    ///     New text that replaces the existing text.
    /// @param[in]  sendEvent
    ///     TRUE to call the change callback for this event.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setText(
            const char *                              newText,
            const bool                                sendEvent
            );

    /// Clears the text in the text editor.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void clear(            );

    /// Changes the text editor to read only mode.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setReadOnly(
            const bool                                shouldBeReadOnly
            );

    /// Returns true if the editor is in read-only mode.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isReadOnly(            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
