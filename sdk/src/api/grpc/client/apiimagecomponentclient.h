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
class ApiImageProxy;
#include "apiguicomponentclient.h"


#include "apiimagecomponent.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiImageComponent
class ApiImageComponentProxy : public ApiGuiComponentProxy
{
public:
    /// Creates an image component.
    ///
    /// @param[in]  image
    ///     Image to place in the component. The image should stay alive until this image
    ///     component is destroyed.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Pointer to the newly created image component.
    static ApiImageComponentProxy create(
            const ApiImageProxy &                     image
            );

    /// Destroys this image component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy(            );

    /// Assigns a new image to the component.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void updateTo(
            const ApiImageProxy &                     image
            );

private:
    static GRPCSettings & getGRPCSettings();
};
