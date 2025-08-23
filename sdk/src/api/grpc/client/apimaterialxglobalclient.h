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
namespace OctaneGRPC
{
    class ApiNodeGraphProxy;
    class ApiTextureNodeTypeInfoProxy;
}


#include "apimaterialx.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiMaterialXGlobal
class ApiMaterialXGlobalProxy : public GRPCBase
{
public:
    static ApiNodeGraphProxy importMaterialXFile(
            const char *                              materialXFilePath,
            const ApiNodeGraphProxy *                 parentNodeGraph,
            const bool                                useNativeMaterialXNodes
            );

    static std::vector<std::string> getAllMxNodeCategories();

    static std::string getMxNodeCategory(
            Octane::NodeType   nodeType
            );

    static std::string getMxNodeCategory(
            Octane::NodeGraphType   nodeGraphType
            );

    static std::string getMxValueType(
            Octane::TextureValueType   textureValueType
            );

    static Octane::TextureValueType getTextureValueType(
            const char *   mxValueTypeName
            );

    static std::string getMxColorSpace(
            Octane::NamedColorSpace   colorSpace
            );

    static Octane::NamedColorSpace getNamedColorSpace(
            const char *   mxColorSpace
            );

    static std::vector<Octane::NodeType> getNodeTypes(
            const char *   mxNodeCategory
            );

    static Octane::NodeGraphType getGraphType(
            const char *   mxNodeCategory
            );

    static std::vector<Octane::ApiMaterialX::MxInput> getMxInputNamesAndPinIds(
            Octane::NodeType   nodeType
            );

    static std::vector<std::string> getGraphMxInputNames(
            Octane::NodeGraphType   nodeGraphType
            );

    static std::vector<std::string> getGraphMxOutputNames(
            Octane::NodeGraphType   nodeGraphType
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
