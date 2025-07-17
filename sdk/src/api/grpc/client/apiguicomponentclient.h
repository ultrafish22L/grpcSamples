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
class ApiMouseListenerProxy;


#include "apiguicomponent.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiGuiComponent
class ApiGuiComponentProxy : public GRPCBase
{
public:
    /// Adds a component as a child component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addChildComponent(
            ApiGuiComponentProxy &   child
            );

    /// Removes the passed in component as child component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void removeChildComponent(
            ApiGuiComponentProxy &   child
            );

    /// Sets the size of this component in pixel.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setSize(
            const int                                 width,
            const int                                 height
            );

    /// Returns the width of this component in pixels.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int width() const;

    /// Returns the height of this component in pixels.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int height() const;

    /// Sets the position of the top-left corner relative to the bounds of the parent component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setTopLeftPosition(
            const int                                 x,
            const int                                 y
            );

    /// Returns the x-position of this component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int xPosition() const;

    /// Returns the y-position of this component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    int yPosition() const;

    /// Enables/disables this component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setEnabled(
            const bool   enabled
            );

    /// Checks if this component is enabled/disabled.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isEnabled() const;

    /// Sets the tooltip for this component. Not all components support tooltips and for them,
    /// this function is a no-operation. The ones that support tooltips are: buttons, combo boxes,
    /// progress bar, text editor and numeric box.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setTooltip(
            const char *   tooltip
            );

    /// Returns the tooltip. When the component doesn't support a tooltip, an empty string is
    /// returned.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string tooltip() const;

    /// Add a mouse listener to this component
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void addMouseListener(
            ApiMouseListenerProxy *                   newListener,
            bool                                      wantsEventsForAllNestedChildComponents
            );

    /// Remove a mouse listener from this component
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void removeMouseListener(
            ApiMouseListenerProxy *   listenerToRemove
            );

private:
    static GRPCSettings & getGRPCSettings();
};
