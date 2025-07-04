// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apimaterialxglobalclient.h"
#include <cassert>
#include <stdexcept>
#include "octanerenderpasses.h"
#include "octaneimageexport.h"
#include "octaneinfos.h"
#include "octaneids.h"
#include "octanenet.h"
#include "octanemodulesinfo.h"
#include "octanereferenceexport.h"
#include <grpcpp/grpcpp.h>
#include "apimaterialx.grpc.pb.h"
#include "apinodegraphclient.h"
#include "apitexturenodetypeinfoclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapitexturenodetypeinfo_apitexturenodetypeinfo_configuration.h"
#include "convertapitexturenodetypeinfo_configuration_interface.h"


GRPCSettings & ApiMaterialXGlobalProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiNodeGraphProxy ApiMaterialXGlobalProxy::importMaterialXFile(
            const char *                              materialXFilePath, //// test821 //// 
            const ApiNodeGraphProxy *                 parentNodeGraph, //// test821 //// 
            const bool                                useNativeMaterialXNodes //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::importMaterialXFileRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'materialXFilePath' [in] parameter to the request packet.
    std::string * materialxfilepathIn = new std::string(); //// materialXFilePath type=string;//// ////721////
    *materialxfilepathIn = checkString(materialXFilePath);
    request.set_allocated_materialxfilepath(materialxfilepathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'parentNodeGraph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * parentnodegraphIn = new octaneapi::ObjectRef();////761////
    parentnodegraphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);////5////
    parentnodegraphIn->set_handle(parentNodeGraph->getObjectHandle());
    request.set_allocated_parentnodegraph(parentnodegraphIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'useNativeMaterialXNodes' [in] parameter to the request packet.
    bool usenativematerialxnodesIn;
    usenativematerialxnodesIn = useNativeMaterialXNodes;////2 const bool////
    request.set_usenativematerialxnodes(usenativematerialxnodesIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::importMaterialXFileResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->importMaterialXFile(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeGraphProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());
        return retVal;
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
        ApiNodeGraphProxy retVal;////714////
        return retVal;
    }
};


std::vector<std::string> ApiMaterialXGlobalProxy::getAllMxNodeCategories()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getAllMxNodeCategoriesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getAllMxNodeCategoriesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAllMxNodeCategories(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::StringArrayT resultOut = response.result();
        std::vector<std::string> retVal;////218////
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            //// param.mProtoCppType = StringArrayT param.mType = const Octane::StringArrayT ////
            retVal.push_back(resultOut.data(i));
        }
        return retVal;
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
        return {};
    }
};


std::string ApiMaterialXGlobalProxy::getMxNodeCategory(
            Octane::NodeType                          nodeType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getMxNodeCategoryRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeType' [in] parameter to the request packet.
    octaneapi::NodeType nodetypeIn;
    nodetypeIn = static_cast<octaneapi::NodeType>(nodeType);
    request.set_nodetype(nodetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getMxNodeCategoryResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMxNodeCategory(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


std::string ApiMaterialXGlobalProxy::getMxNodeCategory(
            Octane::NodeGraphType                     nodeGraphType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getMxNodeCategory1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeGraphType' [in] parameter to the request packet.
    octaneapi::NodeGraphType nodegraphtypeIn;
    nodegraphtypeIn = static_cast<octaneapi::NodeGraphType>(nodeGraphType);
    request.set_nodegraphtype(nodegraphtypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getMxNodeCategory1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMxNodeCategory1(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


std::string ApiMaterialXGlobalProxy::getMxValueType(
            Octane::TextureValueType                  textureValueType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getMxValueTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'textureValueType' [in] parameter to the request packet.
    octaneapi::TextureValueType texturevaluetypeIn;
    texturevaluetypeIn = static_cast<octaneapi::TextureValueType>(textureValueType);
    request.set_texturevaluetype(texturevaluetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getMxValueTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMxValueType(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


Octane::TextureValueType ApiMaterialXGlobalProxy::getTextureValueType(
            const char *                              mxValueTypeName //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getTextureValueTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'mxValueTypeName' [in] parameter to the request packet.
    std::string * mxvaluetypenameIn = new std::string(); //// mxValueTypeName type=string;//// ////721////
    *mxvaluetypenameIn = checkString(mxValueTypeName);
    request.set_allocated_mxvaluetypename(mxvaluetypenameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getTextureValueTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getTextureValueType(context.get(), request, &response);

    Octane::TextureValueType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::TextureValueType resultOut = response.result();
        retVal = static_cast<Octane::TextureValueType>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


std::string ApiMaterialXGlobalProxy::getMxColorSpace(
            Octane::NamedColorSpace                   colorSpace //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getMxColorSpaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'colorSpace' [in] parameter to the request packet.
    octaneapi::NamedColorSpace colorspaceIn;
    colorspaceIn = static_cast<octaneapi::NamedColorSpace>(colorSpace);
    request.set_colorspace(colorspaceIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getMxColorSpaceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMxColorSpace(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;////ex string mgr////
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


Octane::NamedColorSpace ApiMaterialXGlobalProxy::getNamedColorSpace(
            const char *                              mxColorSpace //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getNamedColorSpaceRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'mxColorSpace' [in] parameter to the request packet.
    std::string * mxcolorspaceIn = new std::string(); //// mxColorSpace type=string;//// ////721////
    *mxcolorspaceIn = checkString(mxColorSpace);
    request.set_allocated_mxcolorspace(mxcolorspaceIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getNamedColorSpaceResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getNamedColorSpace(context.get(), request, &response);

    Octane::NamedColorSpace retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NamedColorSpace resultOut = response.result();
        retVal = static_cast<Octane::NamedColorSpace>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


std::vector<Octane::NodeType> ApiMaterialXGlobalProxy::getNodeTypes(
            const char *                              mxNodeCategory //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getNodeTypesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'mxNodeCategory' [in] parameter to the request packet.
    std::string * mxnodecategoryIn = new std::string(); //// mxNodeCategory type=string;//// ////721////
    *mxnodecategoryIn = checkString(mxNodeCategory);
    request.set_allocated_mxnodecategory(mxnodecategoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getNodeTypesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getNodeTypes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NodeTypeArrayT resultOut = response.result();
        // UNTESTED client array code 2
        //// param.mProtoCppType = NodeTypeArrayT param.mType = ApiArray<Octane::NodeType> retType = std::vector<Octane::NodeType> ////
        std::vector<Octane::NodeType> retVal;
        retVal.reserve(resultOut.data_size());/*214*/
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            retVal.push_back(static_cast<Octane::NodeType>(resultOut.data(i)));
        }
        return retVal;
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
        return {};
    }
};


Octane::NodeGraphType ApiMaterialXGlobalProxy::getGraphType(
            const char *                              mxNodeCategory //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getGraphTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'mxNodeCategory' [in] parameter to the request packet.
    std::string * mxnodecategoryIn = new std::string(); //// mxNodeCategory type=string;//// ////721////
    *mxnodecategoryIn = checkString(mxNodeCategory);
    request.set_allocated_mxnodecategory(mxnodecategoryIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getGraphTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGraphType(context.get(), request, &response);

    Octane::NodeGraphType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::NodeGraphType resultOut = response.result();
        retVal = static_cast<Octane::NodeGraphType>(resultOut);
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
    }
    return retVal;
};


std::vector<Octane::ApiMaterialX::MxInput> ApiMaterialXGlobalProxy::getMxInputNamesAndPinIds(
            Octane::NodeType                          nodeType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getMxInputNamesAndPinIdsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeType' [in] parameter to the request packet.
    octaneapi::NodeType nodetypeIn;
    nodetypeIn = static_cast<octaneapi::NodeType>(nodeType);
    request.set_nodetype(nodetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getMxInputNamesAndPinIdsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getMxInputNamesAndPinIds(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayMxInputT resultOut = response.result();
        std::vector<Octane::ApiMaterialX::MxInput> retVal;////218////
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            //// param.mProtoCppType = ApiArrayMxInputT param.mType = const ApiArray<Octane::ApiMaterialX::MxInput> ////
            // special ApiArrayMxInputT
            retVal.push_back( 
                {
                    StringManager::getInstance().addString(resultOut.data(i).mxinputname()),
                    static_cast<Octane::PinId>(resultOut.data(i).pinid())
                }
            );
        }
        return retVal;
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
        return {};
    }
};


std::vector<std::string> ApiMaterialXGlobalProxy::getGraphMxInputNames(
            Octane::NodeGraphType                     nodeGraphType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getGraphMxInputNamesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeGraphType' [in] parameter to the request packet.
    octaneapi::NodeGraphType nodegraphtypeIn;
    nodegraphtypeIn = static_cast<octaneapi::NodeGraphType>(nodeGraphType);
    request.set_nodegraphtype(nodegraphtypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getGraphMxInputNamesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGraphMxInputNames(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::StringArrayT resultOut = response.result();
        std::vector<std::string> retVal;////218////
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            //// param.mProtoCppType = StringArrayT param.mType = const Octane::StringArrayT ////
            retVal.push_back(resultOut.data(i));
        }
        return retVal;
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
        return {};
    }
};


std::vector<std::string> ApiMaterialXGlobalProxy::getGraphMxOutputNames(
            Octane::NodeGraphType                     nodeGraphType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMaterialXGlobal::getGraphMxOutputNamesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeGraphType' [in] parameter to the request packet.
    octaneapi::NodeGraphType nodegraphtypeIn;
    nodegraphtypeIn = static_cast<octaneapi::NodeGraphType>(nodeGraphType);
    request.set_nodegraphtype(nodegraphtypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMaterialXGlobal::getGraphMxOutputNamesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMaterialXGlobalService::Stub> stub = 
        octaneapi::ApiMaterialXGlobalService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGraphMxOutputNames(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::StringArrayT resultOut = response.result();
        std::vector<std::string> retVal;////218////
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            //// param.mProtoCppType = StringArrayT param.mType = const Octane::StringArrayT ////
            retVal.push_back(resultOut.data(i));
        }
        return retVal;
    }
    else
    {
        if (!status.ok())
        {
            switch (status.error_code())
            {
                case grpc::StatusCode::INVALID_ARGUMENT:
                    throw std::invalid_argument(status.error_message());
                default:
                    throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
        }
        return {};
    }
};


