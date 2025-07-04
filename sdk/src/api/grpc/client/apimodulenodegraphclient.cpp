// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apimodulenodegraphclient.h"
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
#include "apimodulenodegraph.grpc.pb.h"
#include "apinodepininfoclient.h"
#include "apinodeclient.h"
#include "apiimageclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapifilepath.h"


GRPCSettings & ApiModuleNodeGraphProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiModuleNodeGraphProxy::setInputLinkers(
            const ApiNodePinInfoProxy *const          inputInfos, //// test821 //// 
            const uint32_t                            inputInfosCount, //// test821 //// 
            const OctaneVec::uint32_2                 range //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputLinkersRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'inputInfos' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * inputinfosIn = new octaneapi::ObjectRefArrayT(); //// inputInfos type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = const Octane::ApiNodePinInfo *const ////
    for (uint32_t h = 0; h < inputInfosCount; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = inputinfosIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodePinInfo);////4////
         item->set_handle(inputInfos[h].getObjectHandle());
    }
    request.set_allocated_inputinfos(inputinfosIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'inputInfosCount' [in] parameter to the request packet.
    uint32_t inputinfoscountIn;
    inputinfoscountIn = inputInfosCount;////2 const uint32_t////
    request.set_inputinfoscount(inputinfoscountIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'range' [in] parameter to the request packet.
    octaneapi::uint32_2 * rangeIn = new octaneapi::uint32_2(); //// range type=uint32_2;//// ////721////
    (*rangeIn).set_x(range.x);
    (*rangeIn).set_y(range.y);
    request.set_allocated_range(rangeIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputLinkers(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setOutputLinkers(
            const ApiNodePinInfoProxy *const          outputInfos, //// test821 //// 
            const uint32_t                            outputInfosCount, //// test821 //// 
            const OctaneVec::uint32_2                 range //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setOutputLinkersRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'outputInfos' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * outputinfosIn = new octaneapi::ObjectRefArrayT(); //// outputInfos type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = const Octane::ApiNodePinInfo *const ////
    for (uint32_t h = 0; h < outputInfosCount; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = outputinfosIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodePinInfo);////4////
         item->set_handle(outputInfos[h].getObjectHandle());
    }
    request.set_allocated_outputinfos(outputinfosIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'outputInfosCount' [in] parameter to the request packet.
    uint32_t outputinfoscountIn;
    outputinfoscountIn = outputInfosCount;////2 const uint32_t////
    request.set_outputinfoscount(outputinfoscountIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'range' [in] parameter to the request packet.
    octaneapi::uint32_2 * rangeIn = new octaneapi::uint32_2(); //// range type=uint32_2;//// ////721////
    (*rangeIn).set_x(range.x);
    (*rangeIn).set_y(range.y);
    request.set_allocated_range(rangeIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setOutputLinkers(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::insertLinkers(
            const ApiNodePinInfoProxy *const          infos, //// test821 //// 
            const uint32_t                            infosCount, //// test821 //// 
            const uint32_t                            ix, //// test821 //// 
            const bool                                isInputLinkers //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::insertLinkersRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'infos' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * infosIn = new octaneapi::ObjectRefArrayT(); //// infos type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = const Octane::ApiNodePinInfo *const ////
    for (uint32_t h = 0; h < infosCount; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = infosIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodePinInfo);////4////
         item->set_handle(infos[h].getObjectHandle());
    }
    request.set_allocated_infos(infosIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'infosCount' [in] parameter to the request packet.
    uint32_t infoscountIn;
    infoscountIn = infosCount;////2 const uint32_t////
    request.set_infoscount(infoscountIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'ix' [in] parameter to the request packet.
    uint32_t ixIn;
    ixIn = ix;////2 const uint32_t////
    request.set_ix(ixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'isInputLinkers' [in] parameter to the request packet.
    bool isinputlinkersIn;
    isinputlinkersIn = isInputLinkers;////2 const bool////
    request.set_isinputlinkers(isinputlinkersIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->insertLinkers(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::removeLinkers(
            const ApiNodePinInfoProxy *const          infos, //// test821 //// 
            const OctaneVec::uint32_2                 range, //// test821 //// 
            const bool                                isInputLinkers //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::removeLinkersRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'infos' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * infosIn = new octaneapi::ObjectRefArrayT(); //// infos type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = const Octane::ApiNodePinInfo *const ////
    for (size_t h = range.x; h < range.y; ++h)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = infosIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodePinInfo);////4////
         item->set_handle(infos[h].getObjectHandle());
    }
    request.set_allocated_infos(infosIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'range' [in] parameter to the request packet.
    octaneapi::uint32_2 * rangeIn = new octaneapi::uint32_2(); //// range type=uint32_2;//// ////721////
    (*rangeIn).set_x(range.x);
    (*rangeIn).set_y(range.y);
    request.set_allocated_range(rangeIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'isInputLinkers' [in] parameter to the request packet.
    bool isinputlinkersIn;
    isinputlinkersIn = isInputLinkers;////2 const bool////
    request.set_isinputlinkers(isinputlinkersIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeLinkers(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputInfo(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const ApiNodePinInfoProxy &               info //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputInfoRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'info' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * infoIn = new octaneapi::ObjectRef();////761////
    infoIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodePinInfo);////5////
    infoIn->set_handle(info.getObjectHandle());
    request.set_allocated_info(infoIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputInfo(context.get(), request, &response);

    if (status.ok())
    {
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


bool ApiModuleNodeGraphProxy::inputWasChanged(
            const ApiNodeProxy *const                 linkerNode //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::inputWasChangedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::inputWasChangedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->inputWasChanged(context.get(), request, &response);

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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            bool &                                    value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValueRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValueResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        bool valueOut = response.value();
        value = valueOut;//// SECOND////
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            float &                                   value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        float valueOut = response.value();
        value = valueOut;//// SECOND////
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            OctaneVec::float_2 &                      value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue2Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue2(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_2 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            OctaneVec::float_3 &                      value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue3Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue3(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_3 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            OctaneVec::float_4 &                      value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue4Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue4(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::float_4 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
        value.w = valueOut.w();
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            int32_t &                                 value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue5Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue5(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        int32_t valueOut = response.value();
        value = valueOut;//// SECOND////
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            OctaneVec::int32_2 &                      value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue6Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue6(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_2 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            OctaneVec::int32_3 &                      value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue7Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue7(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_3 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            OctaneVec::int32_4 &                      value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue8Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue8(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::int32_4 valueOut = response.value();
        value.x = valueOut.x();
        value.y = valueOut.y();
        value.z = valueOut.z();
        value.w = valueOut.w();
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            OctaneVec::MatrixF &                      value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue9Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue9(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::MatrixF valueOut = response.value();
    //// ::MatrixF TEST 2////
    MatrixConverter::convertMatrixToOctane(valueOut, value);
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            std::string &                             value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue10Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue10(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        std::string valueOut = response.value();
        // param.mType = const char *&
        value =  valueOut;////ex string mgr////
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


bool ApiModuleNodeGraphProxy::getInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            Octane::ApiFilePath &                     value //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getInputValue11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getInputValue11Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getInputValue11(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'value' [out] parameter from the gRPC response packet
        octaneapi::ApiFilePath valueOut = response.value();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiFilePathConverter::convert(valueOut, value); ////Convert Called type 5223 =ApiFilePath;////
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const bool                                value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValueRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    bool valueIn;
    valueIn = value;////2 const bool////
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const float                               value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    float valueIn;
    valueIn = value;////2 const float////
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue1(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const OctaneVec::float_2                  value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue2Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_2 * valueIn = new octaneapi::float_2(); //// value type=float_2;//// ////721////
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue2(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const OctaneVec::float_3                  value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue3Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_3 * valueIn = new octaneapi::float_3(); //// value type=float_3;//// ////721////
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue3(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const OctaneVec::float_4                  value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue4Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::float_4 * valueIn = new octaneapi::float_4(); //// value type=float_4;//// ////721////
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue4(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const int32_t                             value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue5Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    int32_t valueIn;
    valueIn = value;////2 const int32_t////
    request.set_value(valueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue5(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const OctaneVec::int32_2                  value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue6Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_2 * valueIn = new octaneapi::int32_2(); //// value type=int32_2;//// ////721////
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue6(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const OctaneVec::int32_3                  value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue7Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_3 * valueIn = new octaneapi::int32_3(); //// value type=int32_3;//// ////721////
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue7(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const OctaneVec::int32_4                  value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue8Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::int32_4 * valueIn = new octaneapi::int32_4(); //// value type=int32_4;//// ////721////
    (*valueIn).set_x(value.x);
    (*valueIn).set_y(value.y);
    (*valueIn).set_z(value.z);
    (*valueIn).set_w(value.w);
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue8(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const OctaneVec::MatrixF                  value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue9Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::MatrixF * valueIn = new octaneapi::MatrixF(); //// value type=MatrixF;//// ////721////
    //// ::MatrixF TEST////
    MatrixConverter::convertMatrixToProto(value, *valueIn);
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue9(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const char *                              value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue10Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    std::string * valueIn = new std::string(); //// value type=string;//// ////721////
    *valueIn = checkString(value);
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue10(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setInputValue(
            const ApiNodeProxy *const                 linkerNode, //// test821 //// 
            const Octane::ApiFilePath                 value, //// test821 //// 
            const bool                                evaluate //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setInputValue11Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'linkerNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * linkernodeIn = new octaneapi::ObjectRef();////761////
    linkernodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    linkernodeIn->set_handle(linkerNode->getObjectHandle());
    request.set_allocated_linkernode(linkernodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'value' [in] parameter to the request packet.
    octaneapi::ApiFilePath * valueIn = new octaneapi::ApiFilePath(); //// value type=ApiFilePath;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    ApiFilePathConverter::convert(value, *valueIn); //// Convert Called type 1c =ApiFilePath ////
    request.set_allocated_value(valueIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;////2 const bool////
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setInputValue11(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::reset()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::resetRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->reset(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setEvaluateTimeChanges(
            const bool                                shouldEvaluate, //// test821 //// 
            const OctaneVec::float_2                  timeInterval //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setEvaluateTimeChangesRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'shouldEvaluate' [in] parameter to the request packet.
    bool shouldevaluateIn;
    shouldevaluateIn = shouldEvaluate;////2 const bool////
    request.set_shouldevaluate(shouldevaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'timeInterval' [in] parameter to the request packet.
    octaneapi::float_2 * timeintervalIn = new octaneapi::float_2(); //// timeInterval type=float_2;//// ////721////
    (*timeintervalIn).set_x(timeInterval.x);
    (*timeintervalIn).set_y(timeInterval.y);
    request.set_allocated_timeinterval(timeintervalIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setEvaluateTimeChanges(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setIcon(
            const ApiImageProxy *                     image //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setIconRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'image' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * imageIn = new octaneapi::ObjectRef();////761////
    imageIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);////5////
    imageIn->set_handle(image->getObjectHandle());
    request.set_allocated_image(imageIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setIcon(context.get(), request, &response);

    if (status.ok())
    {
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


bool ApiModuleNodeGraphProxy::wasTimeChanged() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::wasTimeChangedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::wasTimeChangedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->wasTimeChanged(context.get(), request, &response);

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


size_t ApiModuleNodeGraphProxy::appendAsset(
            const Octane::ApiFilePath &               filePath //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::appendAssetRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'filePath' [in] parameter to the request packet.
    octaneapi::ApiFilePath * filepathIn = new octaneapi::ApiFilePath(); //// filePath type=ApiFilePath;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    ApiFilePathConverter::convert(filePath, *filepathIn); //// Convert Called type 1c =ApiFilePath ////
    request.set_allocated_filepath(filepathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::appendAssetResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->appendAsset(context.get(), request, &response);

    size_t retVal = 0;
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


void ApiModuleNodeGraphProxy::removeAsset(
            const size_t                              index //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::removeAssetRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = static_cast<uint32_t>(index);////2 const size_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeAsset(context.get(), request, &response);

    if (status.ok())
    {
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


Octane::ApiFilePath ApiModuleNodeGraphProxy::getAsset(
            const size_t                              index //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getAssetRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = static_cast<uint32_t>(index);////2 const size_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getAssetResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAsset(context.get(), request, &response);

    Octane::ApiFilePath retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiFilePath resultOut = response.result();
        //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST 2////
        ApiFilePathConverter::convert(resultOut, retVal); ////Convert Called type 5223 =ApiFilePath;////
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


size_t ApiModuleNodeGraphProxy::getAssetCount() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getAssetCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getAssetCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getAssetCount(context.get(), request, &response);

    size_t retVal = 0;
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


bool ApiModuleNodeGraphProxy::readAsset(
            const size_t                              index, //// test821 //// 
            std::string &                             data, //// test821 //// 
            uint64_t &                                size //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::readAssetRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    uint32_t indexIn;
    indexIn = static_cast<uint32_t>(index);////2 const size_t////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::readAssetResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->readAsset(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'data' [out] parameter from the gRPC response packet
        std::string dataOut = response.data();
        // param.mType = const char *&
        data =  dataOut;////ex string mgr////

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint64_t sizeOut = response.size();
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
    return retVal;
};


bool ApiModuleNodeGraphProxy::readAsset(
            const Octane::ApiFilePath &               path, //// test821 //// 
            std::string &                             data, //// test821 //// 
            uint64_t &                                size //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::readAsset1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'path' [in] parameter to the request packet.
    octaneapi::ApiFilePath * pathIn = new octaneapi::ApiFilePath(); //// path type=ApiFilePath;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    ApiFilePathConverter::convert(path, *pathIn); //// Convert Called type 1c =ApiFilePath ////
    request.set_allocated_path(pathIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::readAsset1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->readAsset1(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;////jan////

        /////////////////////////////////////////////////////////////////////
        // Process 'data' [out] parameter from the gRPC response packet
        std::string dataOut = response.data();
        // param.mType = const char *&
        data =  dataOut;////ex string mgr////

        /////////////////////////////////////////////////////////////////////
        // Process 'size' [out] parameter from the gRPC response packet
        uint64_t sizeOut = response.size();
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
    return retVal;
};


void ApiModuleNodeGraphProxy::removeAllAssets()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::removeAllAssetsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeAllAssets(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setSaveData(
            const char *                              data //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setSaveDataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'data' [in] parameter to the request packet.
    std::string * dataIn = new std::string(); //// data type=string;//// ////721////
    *dataIn = checkString(data);
    request.set_allocated_data(dataIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setSaveData(context.get(), request, &response);

    if (status.ok())
    {
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


std::string ApiModuleNodeGraphProxy::getSaveData()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::getSaveDataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::getSaveDataResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->getSaveData(context.get(), request, &response);

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


void ApiModuleNodeGraphProxy::setCustomData(
            void *                                    data //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setCustomDataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'data' [in] parameter to the request packet.
    uint64_t dataIn;
    //// USER DATA TEST ////
    dataIn = reinterpret_cast<uint64_t>(data);
    request.set_data(dataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setCustomData(context.get(), request, &response);

    if (status.ok())
    {
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


bool ApiModuleNodeGraphProxy::isTriggerEnabled() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::isTriggerEnabledRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleNodeGraph::isTriggerEnabledResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->isTriggerEnabled(context.get(), request, &response);

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


void ApiModuleNodeGraphProxy::trigger() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::triggerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->trigger(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setTriggerButtonIcon(
            const ApiImageProxy *                     image //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setTriggerButtonIconRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'image' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * imageIn = new octaneapi::ObjectRef();////761////
    imageIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiImage);////5////
    imageIn->set_handle(image->getObjectHandle());
    request.set_allocated_image(imageIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setTriggerButtonIcon(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setTriggerButtonTooltip(
            const char *                              tooltip //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setTriggerButtonTooltipRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'tooltip' [in] parameter to the request packet.
    std::string * tooltipIn = new std::string(); //// tooltip type=string;//// ////721////
    *tooltipIn = checkString(tooltip);
    request.set_allocated_tooltip(tooltipIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setTriggerButtonTooltip(context.get(), request, &response);

    if (status.ok())
    {
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


void ApiModuleNodeGraphProxy::setProgressState(
            bool                                      progressBarVisible, //// test821 //// 
            float                                     progress, //// test821 //// 
            const char *                              statusText //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleNodeGraph::setProgressStateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'progressBarVisible' [in] parameter to the request packet.
    bool progressbarvisibleIn;
    progressbarvisibleIn = progressBarVisible;////2 bool////
    request.set_progressbarvisible(progressbarvisibleIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'progress' [in] parameter to the request packet.
    float progressIn;
    progressIn = progress;////2 float////
    request.set_progress(progressIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'statusText' [in] parameter to the request packet.
    std::string * statustextIn = new std::string(); //// statusText type=string;//// ////721////
    *statustextIn = checkString(statusText);
    request.set_allocated_statustext(statustextIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleNodeGraphService::Stub> stub = 
        octaneapi::ApiModuleNodeGraphService::NewStub(getGRPCSettings().getChannel());
    status = stub->setProgressState(context.get(), request, &response);

    if (status.ok())
    {
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


