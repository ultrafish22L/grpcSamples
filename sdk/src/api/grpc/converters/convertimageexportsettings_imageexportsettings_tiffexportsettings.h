// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// application includes
#include <functional>
#include "octaneimageexport.grpc.pb.h"
#include <functional>
#include "octaneimageexport.h"
namespace octaneapi { class ApiTextureNodeTypeInfo_ApiTextureNodeTypeInfo_Configuration; }
namespace OctaneGRPC
{
    struct ApiNodeInfoProxy;
}
namespace OctaneGRPC
{

class ImageExportSettings_ImageExportSettings_TiffExportSettingsConverter
{
public:
    static void convert(
        const octaneapi::ImageExportSettings_ImageExportSettings_TiffExportSettings & in,
        Octane::ImageExportSettings::TiffExportSettings & out);

    static void convert(
        const Octane::ImageExportSettings::TiffExportSettings & in,
        octaneapi::ImageExportSettings_ImageExportSettings_TiffExportSettings & out);
};

} //namespace OctaneGRPC;
#endif // if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
