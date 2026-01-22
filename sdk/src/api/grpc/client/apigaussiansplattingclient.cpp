// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apigaussiansplattingclient.h"
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
#include "apigaussiansplatting.grpc.pb.h"
#include "apinodeclient.h"
#include "apinodegraphclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiGaussianSplattingProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiNodeProxy ApiGaussianSplattingProxy::create(
            ApiNodeGraphProxy &                       ownerGraph
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGaussianSplatting::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'ownerGraph' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * ownergraphIn = new octaneapi::ObjectRef();
    ownergraphIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph);
    ownergraphIn->set_handle(ownerGraph.getObjectHandle());
    request.set_allocated_ownergraph(ownergraphIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGaussianSplatting::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGaussianSplattingService::Stub> stub =
        octaneapi::ApiGaussianSplattingService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNodeProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());
        return retVal;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
        ApiNodeProxy retVal;
        return retVal;
    }
};


bool ApiGaussianSplattingProxy::setAttributesFromPly(
            ApiNodeProxy &                            gaussianSplatNode,
            const uint32_t                            numberOfPoints,
            const float *                             x,
            const float *                             y,
            const float *                             z,
            const float *                             opacity,
            const float *                             scale0,
            const float *                             scale1,
            const float *                             scale2,
            const float *                             rot0,
            const float *                             rot1,
            const float *                             rot2,
            const float *                             rot3,
            const float *                             dc0,
            const float *                             dc1,
            const float *                             dc2,
            const uint32_t                            numberOfRestAttributes,
            const float *const *                      restAttributePointers,
            const bool                                evaluate
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGaussianSplatting::setAttributesFromPlyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'gaussianSplatNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * gaussiansplatnodeIn = new octaneapi::ObjectRef();
    gaussiansplatnodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    gaussiansplatnodeIn->set_handle(gaussianSplatNode.getObjectHandle());
    request.set_allocated_gaussiansplatnode(gaussiansplatnodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'numberOfPoints' [in] parameter to the request packet.
    uint32_t numberofpointsIn;
    numberofpointsIn = numberOfPoints;
    request.set_numberofpoints(numberofpointsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    octaneapi::FloatArrayT * xIn = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        xIn->add_data(static_cast<float>(x[h]));
    }
    request.set_allocated_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    octaneapi::FloatArrayT * yIn = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        yIn->add_data(static_cast<float>(y[h]));
    }
    request.set_allocated_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'z' [in] parameter to the request packet.
    octaneapi::FloatArrayT * zIn = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        zIn->add_data(static_cast<float>(z[h]));
    }
    request.set_allocated_z(zIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'opacity' [in] parameter to the request packet.
    octaneapi::FloatArrayT * opacityIn = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        opacityIn->add_data(static_cast<float>(opacity[h]));
    }
    request.set_allocated_opacity(opacityIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'scale0' [in] parameter to the request packet.
    octaneapi::FloatArrayT * scale0In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        scale0In->add_data(static_cast<float>(scale0[h]));
    }
    request.set_allocated_scale0(scale0In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'scale1' [in] parameter to the request packet.
    octaneapi::FloatArrayT * scale1In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        scale1In->add_data(static_cast<float>(scale1[h]));
    }
    request.set_allocated_scale1(scale1In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'scale2' [in] parameter to the request packet.
    octaneapi::FloatArrayT * scale2In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        scale2In->add_data(static_cast<float>(scale2[h]));
    }
    request.set_allocated_scale2(scale2In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rot0' [in] parameter to the request packet.
    octaneapi::FloatArrayT * rot0In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        rot0In->add_data(static_cast<float>(rot0[h]));
    }
    request.set_allocated_rot0(rot0In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rot1' [in] parameter to the request packet.
    octaneapi::FloatArrayT * rot1In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        rot1In->add_data(static_cast<float>(rot1[h]));
    }
    request.set_allocated_rot1(rot1In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rot2' [in] parameter to the request packet.
    octaneapi::FloatArrayT * rot2In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        rot2In->add_data(static_cast<float>(rot2[h]));
    }
    request.set_allocated_rot2(rot2In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rot3' [in] parameter to the request packet.
    octaneapi::FloatArrayT * rot3In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        rot3In->add_data(static_cast<float>(rot3[h]));
    }
    request.set_allocated_rot3(rot3In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'dc0' [in] parameter to the request packet.
    octaneapi::FloatArrayT * dc0In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        dc0In->add_data(static_cast<float>(dc0[h]));
    }
    request.set_allocated_dc0(dc0In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'dc1' [in] parameter to the request packet.
    octaneapi::FloatArrayT * dc1In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        dc1In->add_data(static_cast<float>(dc1[h]));
    }
    request.set_allocated_dc1(dc1In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'dc2' [in] parameter to the request packet.
    octaneapi::FloatArrayT * dc2In = new octaneapi::FloatArrayT();
    for (int h = 0; h < numberOfPoints; h++)
    {
        dc2In->add_data(static_cast<float>(dc2[h]));
    }
    request.set_allocated_dc2(dc2In);

    /////////////////////////////////////////////////////////////////////
    // Add the 'numberOfRestAttributes' [in] parameter to the request packet.
    uint32_t numberofrestattributesIn;
    numberofrestattributesIn = numberOfRestAttributes;
    request.set_numberofrestattributes(numberofrestattributesIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'restAttributePointers' [in] parameter to the request packet.
    for (uint32_t attr = 0; attr < numberOfRestAttributes; ++attr)
    {
        // Create a new FloatArray message
        auto * array = request.add_restattributepointers();
        for (uint32_t i = 0; i < numberOfPoints; ++i)
        {
            array->add_data(restAttributePointers[attr][i]);
        }
    }

    /////////////////////////////////////////////////////////////////////
    // Add the 'evaluate' [in] parameter to the request packet.
    bool evaluateIn;
    evaluateIn = evaluate;
    request.set_evaluate(evaluateIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGaussianSplatting::setAttributesFromPlyResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGaussianSplattingService::Stub> stub =
        octaneapi::ApiGaussianSplattingService::NewStub(getGRPCSettings().getChannel());
    status = stub->setAttributesFromPly(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
    return retVal;
};


bool ApiGaussianSplattingProxy::exportAsSpz(
            const ApiNodeProxy &                      gaussianSplatNode,
            const char *                              fileName
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGaussianSplatting::exportAsSpzRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'gaussianSplatNode' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * gaussiansplatnodeIn = new octaneapi::ObjectRef();
    gaussiansplatnodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    gaussiansplatnodeIn->set_handle(gaussianSplatNode.getObjectHandle());
    request.set_allocated_gaussiansplatnode(gaussiansplatnodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'fileName' [in] parameter to the request packet.
    std::string * filenameIn = new std::string();
    *filenameIn = checkString(fileName);
    request.set_allocated_filename(filenameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGaussianSplatting::exportAsSpzResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGaussianSplattingService::Stub> stub =
        octaneapi::ApiGaussianSplattingService::NewStub(getGRPCSettings().getChannel());
    status = stub->exportAsSpz(context.get(), request, &response);

    bool retVal = false;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        bool resultOut = response.result();
        retVal = resultOut;
    }
    else if (!status.ok())
    {
       switch (status.error_code())
       {
           case grpc::StatusCode::INVALID_ARGUMENT:
               throw std::invalid_argument(status.error_message());
           default:
               throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
       }
    }
    return retVal;
};


} //end of namespace
