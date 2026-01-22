// Copyright (C) 2026 OTOY NZ Ltd.

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


#include "octaneinfos.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiTexturePinTypeInfo
class ApiTexturePinTypeInfoProxy : public GRPCBase
{
public:
    /// Get the texture value type of a pin for given configuration parameters
    ///
    /// @param[in]  configurationParameters
    ///     The parameters of a specific texture node type configuration
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     A texture value type for the pin
    Octane::TextureValueType getTextureValueType(
            const Octane::ApiTextureNodeTypeInfo::Configuration::Parameters &   configurationParameters
            ) const;

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
