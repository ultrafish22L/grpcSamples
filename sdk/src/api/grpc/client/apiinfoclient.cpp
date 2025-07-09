// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apiinfoclient.h"
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
#include "apiinfo.grpc.pb.h"
#include "apinodepininfoclient.h"
#include "apiitemclient.h"
#include "apinodeclient.h"
#include "apiimageclient.h"
#include "apiattributeinfoclient.h"
#include "../grpcapinodeinfo.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapiattributeinfo.h"
#include "convertapinodegraphinfo.h"
#include "convertapinodeinfo.h"
#include "convertapirenderpassinfo.h"


GRPCSettings & ApiInfoProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


int ApiInfoProxy::octaneVersion()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::octaneVersionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::octaneVersionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->octaneVersion(context.get(), request, &response);

    int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
        retVal = resultOut;////jan////
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


std::string ApiInfoProxy::octaneName()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::octaneNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::octaneNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->octaneName(context.get(), request, &response);

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


bool ApiInfoProxy::isDemoVersion()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::isDemoVersionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::isDemoVersionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->isDemoVersion(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
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


bool ApiInfoProxy::isSubscriptionVersion()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::isSubscriptionVersionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::isSubscriptionVersionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->isSubscriptionVersion(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////
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


int ApiInfoProxy::tierIdx()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::tierIdxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::tierIdxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->tierIdx(context.get(), request, &response);

    int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
        retVal = resultOut;////jan////
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


std::string ApiInfoProxy::osVersionInfo()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::osVersionInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::osVersionInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->osVersionInfo(context.get(), request, &response);

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


std::string ApiInfoProxy::driverVersionInfo()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::driverVersionInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::driverVersionInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->driverVersionInfo(context.get(), request, &response);

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


void ApiInfoProxy::cpuInfo(
            std::string &                             cpuVendor, //// test821 //// 
            std::string &                             cpuModel, //// test821 //// 
            uint32_t &                                clockSpeedMhz, //// test821 //// 
            uint32_t &                                nbCores //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::cpuInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::cpuInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->cpuInfo(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'cpuVendor' [out] parameter from the gRPC response packet
        std::string cpuVendorOut = response.cpuvendor();
        // param.mType = const char **
        cpuVendor =  cpuVendorOut;////ex string mgr////

        /////////////////////////////////////////////////////////////////////
        // Process 'cpuModel' [out] parameter from the gRPC response packet
        std::string cpuModelOut = response.cpumodel();
        // param.mType = const char **
        cpuModel =  cpuModelOut;////ex string mgr////

        /////////////////////////////////////////////////////////////////////
        // Process 'clockSpeedMhz' [out] parameter from the gRPC response packet
        uint32_t clockSpeedMhzOut = response.clockspeedmhz();
        clockSpeedMhz = clockSpeedMhzOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'nbCores' [out] parameter from the gRPC response packet
        uint32_t nbCoresOut = response.nbcores();
        nbCores = nbCoresOut;//// SECOND////
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
};


std::string ApiInfoProxy::texCacheFolder()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::texCacheFolderRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::texCacheFolderResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->texCacheFolder(context.get(), request, &response);

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


void ApiInfoProxy::getAttributeTypes(
            std::vector<Octane::AttributeType> &      attributeTypes, //// test821 //// 
            size_t &                                  size //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAttributeTypesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getAttributeTypesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAttributeTypes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'attributeTypes' [out] parameter from the gRPC response packet
        octaneapi::AttributeTypeArrayT attributeTypesOut = response.attributetypes();
        // UNTESTED client array code 2
        //// param.mProtoCppType = AttributeTypeArrayT param.mType = const Octane::AttributeType *& retType = void ////
        attributeTypes.clear();
        attributeTypes.reserve(attributeTypesOut.data_size());/*214*/
        for (int i = 0; i < attributeTypesOut.data_size(); i++)
        {
            attributeTypes.push_back(static_cast<Octane::AttributeType>(attributeTypesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint32_t sizeOut = response.size();
        size = sizeOut;//// SECOND////
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
};


void ApiInfoProxy::getPinTypes(
            std::vector<Octane::NodePinType> &        pinTypes, //// test821 //// 
            size_t &                                  size //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinTypesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getPinTypesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinTypes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'pinTypes' [out] parameter from the gRPC response packet
        octaneapi::NodePinTypeArrayT pinTypesOut = response.pintypes();
        // UNTESTED client array code 2
        //// param.mProtoCppType = NodePinTypeArrayT param.mType = const Octane::NodePinType *& retType = void ////
        pinTypes.clear();
        pinTypes.reserve(pinTypesOut.data_size());/*214*/
        for (int i = 0; i < pinTypesOut.data_size(); i++)
        {
            pinTypes.push_back(static_cast<Octane::NodePinType>(pinTypesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint32_t sizeOut = response.size();
        size = sizeOut;//// SECOND////
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
};


void ApiInfoProxy::getGraphTypes(
            std::vector<Octane::NodeGraphType> &      graphTypes, //// test821 //// 
            size_t &                                  size //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getGraphTypesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getGraphTypesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGraphTypes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'graphTypes' [out] parameter from the gRPC response packet
        octaneapi::NodeGraphTypeArrayT graphTypesOut = response.graphtypes();
        // UNTESTED client array code 2
        //// param.mProtoCppType = NodeGraphTypeArrayT param.mType = const Octane::NodeGraphType *& retType = void ////
        graphTypes.clear();
        graphTypes.reserve(graphTypesOut.data_size());/*214*/
        for (int i = 0; i < graphTypesOut.data_size(); i++)
        {
            graphTypes.push_back(static_cast<Octane::NodeGraphType>(graphTypesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint32_t sizeOut = response.size();
        size = sizeOut;//// SECOND////
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
};


void ApiInfoProxy::getNodeTypes(
            std::vector<Octane::NodeType> &           nodesTypes, //// test821 //// 
            size_t &                                  size //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getNodeTypesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getNodeTypesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getNodeTypes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'nodesTypes' [out] parameter from the gRPC response packet
        octaneapi::NodeTypeArrayT nodesTypesOut = response.nodestypes();
        // UNTESTED client array code 2
        //// param.mProtoCppType = NodeTypeArrayT param.mType = const Octane::NodeType *& retType = void ////
        nodesTypes.clear();
        nodesTypes.reserve(nodesTypesOut.data_size());/*214*/
        for (int i = 0; i < nodesTypesOut.data_size(); i++)
        {
            nodesTypes.push_back(static_cast<Octane::NodeType>(nodesTypesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint32_t sizeOut = response.size();
        size = sizeOut;//// SECOND////
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
};


const ApiNodeInfoProxy ApiInfoProxy::nodeInfo(
            const Octane::NodeType                    type //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::nodeInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
    typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::nodeInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->nodeInfo(context.get(), request, &response);

    ApiNodeInfoProxy retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiNodeInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiNodeInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiNodeInfo;////
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


const Octane::ApiNodeGraphInfo ApiInfoProxy::graphInfo(
            Octane::NodeGraphType                     type //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::graphInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeGraphType typeIn;
    typeIn = static_cast<octaneapi::NodeGraphType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::graphInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->graphInfo(context.get(), request, &response);

    Octane::ApiNodeGraphInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiNodeGraphInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiNodeGraphInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiNodeGraphInfo;////
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


ApiImageProxy ApiInfoProxy::nodeIconImage(
            const Octane::NodeType                    nodeType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::nodeIconImageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeType' [in] parameter to the request packet.
    octaneapi::NodeType nodetypeIn;
    nodetypeIn = static_cast<octaneapi::NodeType>(nodeType);
    request.set_nodetype(nodetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::nodeIconImageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->nodeIconImage(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiImageProxy retVal;
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
        ApiImageProxy retVal;////714////
        return retVal;
    }
};


ApiImageProxy ApiInfoProxy::graphIconImage(
            const Octane::NodeGraphType               nodeGraphType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::graphIconImageRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeGraphType' [in] parameter to the request packet.
    octaneapi::NodeGraphType nodegraphtypeIn;
    nodegraphtypeIn = static_cast<octaneapi::NodeGraphType>(nodeGraphType);
    request.set_nodegraphtype(nodegraphtypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::graphIconImageResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->graphIconImage(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiImageProxy retVal;
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
        ApiImageProxy retVal;////714////
        return retVal;
    }
};


const Octane::ApiAttributeInfo ApiInfoProxy::attributeInfo(
            Octane::NodeType                          type, //// test821 //// 
            Octane::AttributeId                       attrId //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::attributeInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
    typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'attrId' [in] parameter to the request packet.
    octaneapi::AttributeId attridIn;
    attridIn = static_cast<octaneapi::AttributeId>(attrId);
    request.set_attrid(attridIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::attributeInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->attributeInfo(context.get(), request, &response);

    Octane::ApiAttributeInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiAttributeInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiAttributeInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiAttributeInfo;////
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


const Octane::ApiAttributeInfo ApiInfoProxy::attributeInfo(
            Octane::NodeType                          type, //// test821 //// 
            uint32_t                                  attrIx //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::attributeInfo1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
    typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'attrIx' [in] parameter to the request packet.
    uint32_t attrixIn;
    attrixIn = attrIx;////2 uint32_t////
    request.set_attrix(attrixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::attributeInfo1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->attributeInfo1(context.get(), request, &response);

    Octane::ApiAttributeInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiAttributeInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiAttributeInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiAttributeInfo;////
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


const Octane::ApiAttributeInfo ApiInfoProxy::attributeInfo(
            Octane::NodeGraphType                     type, //// test821 //// 
            uint32_t                                  attrIx //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::attributeInfo2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeGraphType typeIn;
    typeIn = static_cast<octaneapi::NodeGraphType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'attrIx' [in] parameter to the request packet.
    uint32_t attrixIn;
    attrixIn = attrIx;////2 uint32_t////
    request.set_attrix(attrixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::attributeInfo2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->attributeInfo2(context.get(), request, &response);

    Octane::ApiAttributeInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiAttributeInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiAttributeInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiAttributeInfo;////
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


ApiNodePinInfoProxy ApiInfoProxy::nodePinInfo(
            Octane::NodeType                          nodeType, //// test821 //// 
            uint32_t                                  pinIx //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::nodePinInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'nodeType' [in] parameter to the request packet.
    octaneapi::NodeType nodetypeIn;
    nodetypeIn = static_cast<octaneapi::NodeType>(nodeType);
    request.set_nodetype(nodetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;////2 uint32_t////
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::nodePinInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->nodePinInfo(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodePinInfoProxy retVal;
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
        ApiNodePinInfoProxy retVal;////714////
        return retVal;
    }
};


std::string ApiInfoProxy::getAttributeTypeName(
            Octane::AttributeType                     type //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAttributeTypeNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::AttributeType typeIn;
    typeIn = static_cast<octaneapi::AttributeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getAttributeTypeNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAttributeTypeName(context.get(), request, &response);

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


std::string ApiInfoProxy::getPinTypeName(
            Octane::NodePinType                       type //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinTypeNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodePinType typeIn;
    typeIn = static_cast<octaneapi::NodePinType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getPinTypeNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinTypeName(context.get(), request, &response);

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


uint32_t ApiInfoProxy::getPinTypeColor(
            Octane::NodePinType                       type //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinTypeColorRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodePinType typeIn;
    typeIn = static_cast<octaneapi::NodePinType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getPinTypeColorResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinTypeColor(context.get(), request, &response);

    uint32_t retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        uint32_t resultOut = response.result();
        retVal = resultOut;////jan////
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


std::string ApiInfoProxy::getGraphTypeName(
            Octane::NodeGraphType                     type //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getGraphTypeNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeGraphType typeIn;
    typeIn = static_cast<octaneapi::NodeGraphType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getGraphTypeNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getGraphTypeName(context.get(), request, &response);

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


std::string ApiInfoProxy::getNodeTypeName(
            Octane::NodeType                          type //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getNodeTypeNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'type' [in] parameter to the request packet.
    octaneapi::NodeType typeIn;
    typeIn = static_cast<octaneapi::NodeType>(type);
    request.set_type(typeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getNodeTypeNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getNodeTypeName(context.get(), request, &response);

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


std::string ApiInfoProxy::getItemTypeName(
            const ApiItemProxy &                      item //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getItemTypeNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'item' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();////761////
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////5////
    itemIn->set_handle(item.getObjectHandle());
    request.set_allocated_item(itemIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getItemTypeNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getItemTypeName(context.get(), request, &response);

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


std::string ApiInfoProxy::getAttributeName(
            Octane::AttributeId                       id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAttributeNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
    idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getAttributeNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAttributeName(context.get(), request, &response);

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


Octane::AttributeId ApiInfoProxy::getAttributeId(
            const char *                              attributeName //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAttributeIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'attributeName' [in] parameter to the request packet.
    std::string * attributenameIn = new std::string(); //// attributeName type=string;//// ////721////
    *attributenameIn = checkString(attributeName);
    request.set_allocated_attributename(attributenameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getAttributeIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAttributeId(context.get(), request, &response);

    Octane::AttributeId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::AttributeId resultOut = response.result();
        retVal = static_cast<Octane::AttributeId>(resultOut);
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


std::string ApiInfoProxy::getAttributeIdName(
            Octane::AttributeId                       id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAttributeIdNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::AttributeId idIn;
    idIn = static_cast<octaneapi::AttributeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getAttributeIdNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAttributeIdName(context.get(), request, &response);

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


std::string ApiInfoProxy::getAttributeIdName(
            const char *                              attributeName //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAttributeIdName1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'attributeName' [in] parameter to the request packet.
    std::string * attributenameIn = new std::string(); //// attributeName type=string;//// ////721////
    *attributenameIn = checkString(attributeName);
    request.set_allocated_attributename(attributenameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getAttributeIdName1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAttributeIdName1(context.get(), request, &response);

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


std::string ApiInfoProxy::getPinName(
            Octane::PinId                             id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
    idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getPinNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinName(context.get(), request, &response);

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


Octane::PinId ApiInfoProxy::getPinId(
            const char *                              pinName //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string(); //// pinName type=string;//// ////721////
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getPinIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinId(context.get(), request, &response);

    Octane::PinId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::PinId resultOut = response.result();
        retVal = static_cast<Octane::PinId>(resultOut);
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


std::string ApiInfoProxy::getPinIdName(
            Octane::PinId                             id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinIdNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::PinId idIn;
    idIn = static_cast<octaneapi::PinId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getPinIdNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinIdName(context.get(), request, &response);

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


std::string ApiInfoProxy::getPinIdName(
            const char *                              pinName //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinIdName1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string(); //// pinName type=string;//// ////721////
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getPinIdName1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getPinIdName1(context.get(), request, &response);

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


std::string ApiInfoProxy::getTextureValueTypeName(
            Octane::TextureValueType                  textureValueType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getTextureValueTypeNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'textureValueType' [in] parameter to the request packet.
    octaneapi::TextureValueType texturevaluetypeIn;
    texturevaluetypeIn = static_cast<octaneapi::TextureValueType>(textureValueType);
    request.set_texturevaluetype(texturevaluetypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getTextureValueTypeNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getTextureValueTypeName(context.get(), request, &response);

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


Octane::TextureValueType ApiInfoProxy::getTextureValueTypeForOslType(
            const char *                              oslType //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getTextureValueTypeForOslTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'oslType' [in] parameter to the request packet.
    std::string * osltypeIn = new std::string(); //// oslType type=string;//// ////721////
    *osltypeIn = checkString(oslType);
    request.set_allocated_osltype(osltypeIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getTextureValueTypeForOslTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getTextureValueTypeForOslType(context.get(), request, &response);

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


void ApiInfoProxy::getCompatibleTypes(
            Octane::NodePinType                       outType, //// test821 //// 
            std::vector<Octane::NodeGraphType>        compatGraphs, //// test821 //// 
            size_t &                                  compatGraphsSize, //// test821 //// 
            std::vector<Octane::NodeType>             compatNodes, //// test821 //// 
            size_t &                                  compatNodesSize //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getCompatibleTypesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'outType' [in] parameter to the request packet.
    octaneapi::NodePinType outtypeIn;
    outtypeIn = static_cast<octaneapi::NodePinType>(outType);
    request.set_outtype(outtypeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getCompatibleTypesResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getCompatibleTypes(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'compatGraphs' [out] parameter from the gRPC response packet
        octaneapi::NodeGraphTypeArrayT compatGraphsOut = response.compatgraphs();
        // UNTESTED client array code 2
        //// param.mProtoCppType = NodeGraphTypeArrayT param.mType = Octane::NodeGraphType *& retType = void ////
        compatGraphs.clear();
        compatGraphs.reserve(compatGraphsOut.data_size());/*214*/
        for (int i = 0; i < compatGraphsOut.data_size(); i++)
        {
            compatGraphs.push_back(static_cast<Octane::NodeGraphType>(compatGraphsOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'compatGraphsSize' [out] parameter from the gRPC response packet
        uint32_t compatGraphsSizeOut = response.compatgraphssize();
        compatGraphsSize = compatGraphsSizeOut;//// SECOND////

        /////////////////////////////////////////////////////////////////////
        // Process 'compatNodes' [out] parameter from the gRPC response packet
        octaneapi::NodeTypeArrayT compatNodesOut = response.compatnodes();
        // UNTESTED client array code 2
        //// param.mProtoCppType = NodeTypeArrayT param.mType = Octane::NodeType *& retType = void ////
        compatNodes.clear();
        compatNodes.reserve(compatNodesOut.data_size());/*214*/
        for (int i = 0; i < compatNodesOut.data_size(); i++)
        {
            compatNodes.push_back(static_cast<Octane::NodeType>(compatNodesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'compatNodesSize' [out] parameter from the gRPC response packet
        uint32_t compatNodesSizeOut = response.compatnodessize();
        compatNodesSize = compatNodesSizeOut;//// SECOND////
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
};


const Octane::ApiRenderPassInfo ApiInfoProxy::renderPassInfo(
            Octane::RenderPassId                      id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::renderPassInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::RenderPassId idIn;
    idIn = static_cast<octaneapi::RenderPassId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::renderPassInfoResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderPassInfo(context.get(), request, &response);

    Octane::ApiRenderPassInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiRenderPassInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiRenderPassInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiRenderPassInfo;////
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


std::string ApiInfoProxy::renderPassBlendingModeName(
            Octane::BlendingModeId                    id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::renderPassBlendingModeNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::BlendingModeId idIn;
    idIn = static_cast<octaneapi::BlendingModeId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::renderPassBlendingModeNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderPassBlendingModeName(context.get(), request, &response);

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


std::vector<Octane::RenderPassId> ApiInfoProxy::getAllRenderPassIds(
            size_t &                                  length //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAllRenderPassIdsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getAllRenderPassIdsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAllRenderPassIds(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiArrayRenderPassId resultOut = response.result();
        std::vector<Octane::RenderPassId> retVal;////218////
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            //// param.mProtoCppType = ApiArrayRenderPassId param.mType = const Octane::RenderPassId * ////
            retVal.push_back(static_cast<Octane::RenderPassId>(resultOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'length' [out] parameter from the gRPC response packet
        uint32_t lengthOut = response.length();
        length = lengthOut;//// SECOND////
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


Octane::RenderPassId ApiInfoProxy::getRenderPassIdFromRenderAovNode(
            const ApiNodeProxy &                      node //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getRenderPassIdFromRenderAovNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();////761////
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    nodeIn->set_handle(node.getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getRenderPassIdFromRenderAovNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderPassIdFromRenderAovNode(context.get(), request, &response);

    Octane::RenderPassId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::RenderPassId resultOut = response.result();
        retVal = static_cast<Octane::RenderPassId>(resultOut);
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


const Octane::ApiRenderPassInfo ApiInfoProxy::getRenderAovInfoFromRenderAovNode(
            const ApiNodeProxy &                      node //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getRenderAovInfoFromRenderAovNodeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();////761////
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    nodeIn->set_handle(node.getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::getRenderAovInfoFromRenderAovNodeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->getRenderAovInfoFromRenderAovNode(context.get(), request, &response);

    Octane::ApiRenderPassInfo retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiRenderPassInfo resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiRenderPassInfoConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiRenderPassInfo;////
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


std::string ApiInfoProxy::renderPassName(
            Octane::RenderPassId                      id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::renderPassNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::RenderPassId idIn;
    idIn = static_cast<octaneapi::RenderPassId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::renderPassNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderPassName(context.get(), request, &response);

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


std::string ApiInfoProxy::renderPassShortName(
            Octane::RenderPassId                      id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::renderPassShortNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::RenderPassId idIn;
    idIn = static_cast<octaneapi::RenderPassId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::renderPassShortNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderPassShortName(context.get(), request, &response);

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


Octane::PinId ApiInfoProxy::renderPassIdToPinId(
            Octane::RenderPassId                      id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::renderPassIdToPinIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::RenderPassId idIn;
    idIn = static_cast<octaneapi::RenderPassId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::renderPassIdToPinIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderPassIdToPinId(context.get(), request, &response);

    Octane::PinId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::PinId resultOut = response.result();
        retVal = static_cast<Octane::PinId>(resultOut);
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


std::string ApiInfoProxy::renderPassGroupName(
            Octane::RenderPassGroupId                 id //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::renderPassGroupNameRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'id' [in] parameter to the request packet.
    octaneapi::RenderPassGroupId idIn;
    idIn = static_cast<octaneapi::RenderPassGroupId>(id);
    request.set_id(idIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::renderPassGroupNameResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->renderPassGroupName(context.get(), request, &response);

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


Octane::RenderPassId ApiInfoProxy::pinIdToRenderPassId(
            Octane::PinId                             pinId //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::pinIdToRenderPassIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
    pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::pinIdToRenderPassIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->pinIdToRenderPassId(context.get(), request, &response);

    Octane::RenderPassId retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::RenderPassId resultOut = response.result();
        retVal = static_cast<Octane::RenderPassId>(resultOut);
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


bool ApiInfoProxy::findPinIdForRenderPassId(
            Octane::RenderPassId                      renderPassId, //// test821 //// 
            Octane::PinId &                           pinId //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::findPinIdForRenderPassIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::findPinIdForRenderPassIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->findPinIdForRenderPassId(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'pinId' [out] parameter from the gRPC response packet
        octaneapi::PinId pinIdOut = response.pinid();
        pinId = static_cast<Octane::PinId>(pinIdOut);
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


bool ApiInfoProxy::findRenderPassIdForPinId(
            Octane::PinId                             pinId, //// test821 //// 
            Octane::RenderPassId &                    renderPassId //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::findRenderPassIdForPinIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
    pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiInfo::findRenderPassIdForPinIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiInfoService::Stub> stub = 
        octaneapi::ApiInfoService::NewStub(getGRPCSettings().getChannel());
    status = stub->findRenderPassIdForPinId(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'renderPassId' [out] parameter from the gRPC response packet
        octaneapi::RenderPassId renderPassIdOut = response.renderpassid();
        renderPassId = static_cast<Octane::RenderPassId>(renderPassIdOut);
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


