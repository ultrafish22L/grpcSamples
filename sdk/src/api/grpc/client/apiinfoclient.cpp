// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

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


namespace OctaneGRPC
{


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
        retVal = resultOut;
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
        retVal =  resultOut;
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
        retVal = resultOut;
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
        retVal = resultOut;
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
        retVal = resultOut;
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
        retVal =  resultOut;
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
        retVal =  resultOut;
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
            std::string &                             cpuVendor,
            std::string &                             cpuModel,
            uint32_t &                                clockSpeedMhz,
            uint32_t &                                nbCores
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
        cpuVendor =  cpuVendorOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'cpuModel' [out] parameter from the gRPC response packet
        std::string cpuModelOut = response.cpumodel();
        // param.mType = const char **
        cpuModel =  cpuModelOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'clockSpeedMhz' [out] parameter from the gRPC response packet
        uint32_t clockSpeedMhzOut = response.clockspeedmhz();
        clockSpeedMhz = clockSpeedMhzOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'nbCores' [out] parameter from the gRPC response packet
        uint32_t nbCoresOut = response.nbcores();
        nbCores = nbCoresOut;
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
        retVal =  resultOut;
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
            std::vector<Octane::AttributeType> &      attributeTypes,
            size_t &                                  size
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
        attributeTypes.clear();
        attributeTypes.reserve(attributeTypesOut.data_size());/*214*/
        for (int i = 0; i < attributeTypesOut.data_size(); i++)
        {
            attributeTypes.push_back(static_cast<Octane::AttributeType>(attributeTypesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint32_t sizeOut = response.size();
        size = sizeOut;
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
            std::vector<Octane::NodePinType> &        pinTypes,
            size_t &                                  size
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
        pinTypes.clear();
        pinTypes.reserve(pinTypesOut.data_size());/*214*/
        for (int i = 0; i < pinTypesOut.data_size(); i++)
        {
            pinTypes.push_back(static_cast<Octane::NodePinType>(pinTypesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint32_t sizeOut = response.size();
        size = sizeOut;
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
            std::vector<Octane::NodeGraphType> &      graphTypes,
            size_t &                                  size
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
        graphTypes.clear();
        graphTypes.reserve(graphTypesOut.data_size());/*214*/
        for (int i = 0; i < graphTypesOut.data_size(); i++)
        {
            graphTypes.push_back(static_cast<Octane::NodeGraphType>(graphTypesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint32_t sizeOut = response.size();
        size = sizeOut;
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
            std::vector<Octane::NodeType> &           nodesTypes,
            size_t &                                  size
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
        nodesTypes.clear();
        nodesTypes.reserve(nodesTypesOut.data_size());/*214*/
        for (int i = 0; i < nodesTypesOut.data_size(); i++)
        {
            nodesTypes.push_back(static_cast<Octane::NodeType>(nodesTypesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint32_t sizeOut = response.size();
        size = sizeOut;
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
            const Octane::NodeType                    type
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
        ApiNodeInfoConverter::convert(resultOut, retVal);
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
            Octane::NodeGraphType                     type
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
        ApiNodeGraphInfoConverter::convert(resultOut, retVal);
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
            const Octane::NodeType                    nodeType
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
        ApiImageProxy retVal;
        return retVal;
    }
};


ApiImageProxy ApiInfoProxy::graphIconImage(
            const Octane::NodeGraphType               nodeGraphType
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
        ApiImageProxy retVal;
        return retVal;
    }
};


const Octane::ApiAttributeInfo ApiInfoProxy::attributeInfo(
            Octane::NodeType                          type,
            Octane::AttributeId                       attrId
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
        ApiAttributeInfoConverter::convert(resultOut, retVal);
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
            Octane::NodeType                          type,
            uint32_t                                  attrIx
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
    attrixIn = attrIx;
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
        ApiAttributeInfoConverter::convert(resultOut, retVal);
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
            Octane::NodeGraphType                     type,
            uint32_t                                  attrIx
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
    attrixIn = attrIx;
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
        ApiAttributeInfoConverter::convert(resultOut, retVal);
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
            Octane::NodeType                          nodeType,
            uint32_t                                  pinIx
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
    pinixIn = pinIx;
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
        ApiNodePinInfoProxy retVal;
        return retVal;
    }
};


std::string ApiInfoProxy::getAttributeTypeName(
            Octane::AttributeType                     type
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
        retVal =  resultOut;
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
            Octane::NodePinType                       type
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
        retVal =  resultOut;
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
            Octane::NodePinType                       type
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
        retVal = resultOut;
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
            Octane::NodeGraphType                     type
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
        retVal =  resultOut;
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
            Octane::NodeType                          type
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
        retVal =  resultOut;
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
            const ApiItemProxy &                      item
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
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
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
        retVal =  resultOut;
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
            Octane::AttributeId                       id
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
        retVal =  resultOut;
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
            const char *                              attributeName
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAttributeIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'attributeName' [in] parameter to the request packet.
    std::string * attributenameIn = new std::string();
    *attributenameIn = checkString(attributeName);
    request.set_allocated_attributename(attributenameIn);

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
            Octane::AttributeId                       id
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
        retVal =  resultOut;
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
            const char *                              attributeName
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getAttributeIdName1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'attributeName' [in] parameter to the request packet.
    std::string * attributenameIn = new std::string();
    *attributenameIn = checkString(attributeName);
    request.set_allocated_attributename(attributenameIn);

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
        retVal =  resultOut;
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
            Octane::PinId                             id
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
        retVal =  resultOut;
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
            const char *                              pinName
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

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
            Octane::PinId                             id
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
        retVal =  resultOut;
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
            const char *                              pinName
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getPinIdName1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

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
        retVal =  resultOut;
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
            Octane::TextureValueType                  textureValueType
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
        retVal =  resultOut;
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
            const char *                              oslType
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiInfo::getTextureValueTypeForOslTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'oslType' [in] parameter to the request packet.
    std::string * osltypeIn = new std::string();
    *osltypeIn = checkString(oslType);
    request.set_allocated_osltype(osltypeIn);

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
            Octane::NodePinType                       outType,
            std::vector<Octane::NodeGraphType>        compatGraphs,
            size_t &                                  compatGraphsSize,
            std::vector<Octane::NodeType>             compatNodes,
            size_t &                                  compatNodesSize
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
        compatGraphs.clear();
        compatGraphs.reserve(compatGraphsOut.data_size());/*214*/
        for (int i = 0; i < compatGraphsOut.data_size(); i++)
        {
            compatGraphs.push_back(static_cast<Octane::NodeGraphType>(compatGraphsOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'compatGraphsSize' [out] parameter from the gRPC response packet
        uint32_t compatGraphsSizeOut = response.compatgraphssize();
        compatGraphsSize = compatGraphsSizeOut;

        /////////////////////////////////////////////////////////////////////
        // Process 'compatNodes' [out] parameter from the gRPC response packet
        octaneapi::NodeTypeArrayT compatNodesOut = response.compatnodes();
        // UNTESTED client array code 2
        compatNodes.clear();
        compatNodes.reserve(compatNodesOut.data_size());/*214*/
        for (int i = 0; i < compatNodesOut.data_size(); i++)
        {
            compatNodes.push_back(static_cast<Octane::NodeType>(compatNodesOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'compatNodesSize' [out] parameter from the gRPC response packet
        uint32_t compatNodesSizeOut = response.compatnodessize();
        compatNodesSize = compatNodesSizeOut;
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
            Octane::RenderPassId                      id
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
        ApiRenderPassInfoConverter::convert(resultOut, retVal);
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
            size_t &                                  length
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
        std::vector<Octane::RenderPassId> retVal;
        retVal.reserve(resultOut.data_size());
        for (int i = 0; i < resultOut.data_size(); i++)
        {
            retVal.push_back(static_cast<Octane::RenderPassId>(resultOut.data(i)));
        }

        /////////////////////////////////////////////////////////////////////
        // Process 'length' [out] parameter from the gRPC response packet
        uint32_t lengthOut = response.length();
        length = lengthOut;
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
            const ApiNodeProxy &                      node
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
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
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
            const ApiNodeProxy &                      node
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
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
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
        ApiRenderPassInfoConverter::convert(resultOut, retVal);
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
            Octane::RenderPassId                      id
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
        retVal =  resultOut;
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
            Octane::RenderPassId                      id
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
        retVal =  resultOut;
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
            Octane::RenderPassId                      id
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
            Octane::RenderPassGroupId                 id
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
        retVal =  resultOut;
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
            Octane::PinId                             pinId
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
            Octane::RenderPassId                      renderPassId,
            Octane::PinId &                           pinId
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
        retVal = resultOut;

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
            Octane::PinId                             pinId,
            Octane::RenderPassId &                    renderPassId
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
        retVal = resultOut;

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


} //end of namespace
