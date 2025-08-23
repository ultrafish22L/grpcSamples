// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apigridlayoutclient.h"
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
#include "apigridlayout.grpc.pb.h"
#include "apiguicomponentclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiGridLayoutProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiGridLayoutProxy ApiGridLayoutProxy::create()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGridLayout::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiGridLayoutProxy retVal;
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
        ApiGridLayoutProxy retVal;
        return retVal;
    }
};


void ApiGridLayoutProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->destroy(context.get(), request, &response);

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


void ApiGridLayoutProxy::startSetup(
            const int                                 borderX,
            const int                                 borderY,
            const int                                 paddingX,
            const int                                 paddingY
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::startSetupRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'borderX' [in] parameter to the request packet.
    int32_t borderxIn;
    borderxIn = borderX;
    request.set_borderx(borderxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'borderY' [in] parameter to the request packet.
    int32_t borderyIn;
    borderyIn = borderY;
    request.set_bordery(borderyIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'paddingX' [in] parameter to the request packet.
    int32_t paddingxIn;
    paddingxIn = paddingX;
    request.set_paddingx(paddingxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'paddingY' [in] parameter to the request packet.
    int32_t paddingyIn;
    paddingyIn = paddingY;
    request.set_paddingy(paddingyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->startSetup(context.get(), request, &response);

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


void ApiGridLayoutProxy::endSetup()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::endSetupRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->endSetup(context.get(), request, &response);

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


void ApiGridLayoutProxy::add(
            ApiGuiComponentProxy &                    child,
            const uint32_t                            cellX,
            const uint32_t                            cellY
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::addRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'child' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * childIn = new octaneapi::ObjectRef();
    childIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    childIn->set_handle(child.getObjectHandle());
    request.set_allocated_child(childIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cellX' [in] parameter to the request packet.
    uint32_t cellxIn;
    cellxIn = cellX;
    request.set_cellx(cellxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cellY' [in] parameter to the request packet.
    uint32_t cellyIn;
    cellyIn = cellY;
    request.set_celly(cellyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->add(context.get(), request, &response);

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


void ApiGridLayoutProxy::addEmpty(
            const uint32_t                            cellX,
            const uint32_t                            cellY
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::addEmptyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cellX' [in] parameter to the request packet.
    uint32_t cellxIn;
    cellxIn = cellX;
    request.set_cellx(cellxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cellY' [in] parameter to the request packet.
    uint32_t cellyIn;
    cellyIn = cellY;
    request.set_celly(cellyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->addEmpty(context.get(), request, &response);

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


void ApiGridLayoutProxy::addSpan(
            ApiGuiComponentProxy &                    child,
            const uint32_t                            minCellX,
            const uint32_t                            minCellY,
            const uint32_t                            maxCellX,
            const uint32_t                            maxCellY
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::addSpanRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'child' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * childIn = new octaneapi::ObjectRef();
    childIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    childIn->set_handle(child.getObjectHandle());
    request.set_allocated_child(childIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'minCellX' [in] parameter to the request packet.
    uint32_t mincellxIn;
    mincellxIn = minCellX;
    request.set_mincellx(mincellxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'minCellY' [in] parameter to the request packet.
    uint32_t mincellyIn;
    mincellyIn = minCellY;
    request.set_mincelly(mincellyIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'maxCellX' [in] parameter to the request packet.
    uint32_t maxcellxIn;
    maxcellxIn = maxCellX;
    request.set_maxcellx(maxcellxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'maxCellY' [in] parameter to the request packet.
    uint32_t maxcellyIn;
    maxcellyIn = maxCellY;
    request.set_maxcelly(maxcellyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->addSpan(context.get(), request, &response);

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


void ApiGridLayoutProxy::setStartSize(
            const uint32_t                            cellX,
            const uint32_t                            cellY,
            const int                                 sizeX,
            const int                                 sizeY
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::setStartSizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cellX' [in] parameter to the request packet.
    uint32_t cellxIn;
    cellxIn = cellX;
    request.set_cellx(cellxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'cellY' [in] parameter to the request packet.
    uint32_t cellyIn;
    cellyIn = cellY;
    request.set_celly(cellyIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sizeX' [in] parameter to the request packet.
    int32_t sizexIn;
    sizexIn = sizeX;
    request.set_sizex(sizexIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sizeY' [in] parameter to the request packet.
    int32_t sizeyIn;
    sizeyIn = sizeY;
    request.set_sizey(sizeyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->setStartSize(context.get(), request, &response);

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


void ApiGridLayoutProxy::setRowElasticity(
            const uint32_t                            rowIx,
            const float                               elasticity
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::setRowElasticityRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rowIx' [in] parameter to the request packet.
    uint32_t rowixIn;
    rowixIn = rowIx;
    request.set_rowix(rowixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'elasticity' [in] parameter to the request packet.
    float elasticityIn;
    elasticityIn = elasticity;
    request.set_elasticity(elasticityIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->setRowElasticity(context.get(), request, &response);

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


void ApiGridLayoutProxy::setColElasticity(
            const uint32_t                            columnIx,
            const float                               elasticity
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::setColElasticityRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'columnIx' [in] parameter to the request packet.
    uint32_t columnixIn;
    columnixIn = columnIx;
    request.set_columnix(columnixIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'elasticity' [in] parameter to the request packet.
    float elasticityIn;
    elasticityIn = elasticity;
    request.set_elasticity(elasticityIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->setColElasticity(context.get(), request, &response);

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


void ApiGridLayoutProxy::setElasticityForAllRows(
            const float                               elasticity
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::setElasticityForAllRowsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'elasticity' [in] parameter to the request packet.
    float elasticityIn;
    elasticityIn = elasticity;
    request.set_elasticity(elasticityIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->setElasticityForAllRows(context.get(), request, &response);

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


void ApiGridLayoutProxy::setElasticityForAllCols(
            const float                               elasticity
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::setElasticityForAllColsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'elasticity' [in] parameter to the request packet.
    float elasticityIn;
    elasticityIn = elasticity;
    request.set_elasticity(elasticityIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->setElasticityForAllCols(context.get(), request, &response);

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


void ApiGridLayoutProxy::startNestedGrid(
            const uint32_t                            minCellX,
            const uint32_t                            minCellY,
            const uint32_t                            maxCellX,
            const uint32_t                            maxCellY,
            const int                                 borderX,
            const int                                 borderY,
            const int                                 paddingX,
            const int                                 paddingY
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::startNestedGridRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'minCellX' [in] parameter to the request packet.
    uint32_t mincellxIn;
    mincellxIn = minCellX;
    request.set_mincellx(mincellxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'minCellY' [in] parameter to the request packet.
    uint32_t mincellyIn;
    mincellyIn = minCellY;
    request.set_mincelly(mincellyIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'maxCellX' [in] parameter to the request packet.
    uint32_t maxcellxIn;
    maxcellxIn = maxCellX;
    request.set_maxcellx(maxcellxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'maxCellY' [in] parameter to the request packet.
    uint32_t maxcellyIn;
    maxcellyIn = maxCellY;
    request.set_maxcelly(maxcellyIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'borderX' [in] parameter to the request packet.
    int32_t borderxIn;
    borderxIn = borderX;
    request.set_borderx(borderxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'borderY' [in] parameter to the request packet.
    int32_t borderyIn;
    borderyIn = borderY;
    request.set_bordery(borderyIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'paddingX' [in] parameter to the request packet.
    int32_t paddingxIn;
    paddingxIn = paddingX;
    request.set_paddingx(paddingxIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'paddingY' [in] parameter to the request packet.
    int32_t paddingyIn;
    paddingyIn = paddingY;
    request.set_paddingy(paddingyIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->startNestedGrid(context.get(), request, &response);

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


void ApiGridLayoutProxy::endNestedGrid()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::endNestedGridRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->endNestedGrid(context.get(), request, &response);

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


int ApiGridLayoutProxy::width() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::widthRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGridLayout::widthResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->width(context.get(), request, &response);

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


int ApiGridLayoutProxy::height() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGridLayout::heightRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGridLayout::heightResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGridLayoutService::Stub> stub =
        octaneapi::ApiGridLayoutService::NewStub(getGRPCSettings().getChannel());
    status = stub->height(context.get(), request, &response);

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


} //end of namespace
