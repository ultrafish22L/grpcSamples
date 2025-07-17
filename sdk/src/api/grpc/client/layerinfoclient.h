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


#include "apiimageinfo.h"


class Convert;

class GRPCSettings;

/// Proxy class for LayerInfo
class LayerInfoProxy : public GRPCBase
{
public:
    /// Checks if the current layer has alpha data
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool hasTransparency() const;

    /// Checks if the current layer is gray scale data
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isGrayscale() const;

    /// Gets the name of this layer
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string name() const;

    /// Gets the type of this layer's data
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::ImageType type() const;

    /// Gets the preferred BC compression type.
        ///
        /// @param[in] needHQ
        ///     A flag indicating if the high quality option needs to be returned
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::ImageType prefCompressType(
            const bool   needHQ
            ) const;

private:
    static GRPCSettings & getGRPCSettings();
};
