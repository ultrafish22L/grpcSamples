// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apisceneexporterclient.h"
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
#include "apisceneexporter.grpc.pb.h"
#include "apinodeclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertreferencepackageexportsettings.h"


GRPCSettings & ApiSceneExporterProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiSceneExporterProxy::isSupported()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSceneExporter::isSupportedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSceneExporter::isSupportedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSceneExporterService::Stub> stub = 
        octaneapi::ApiSceneExporterService::NewStub(getGRPCSettings().getChannel());
    status = stub->isSupported(context.get(), request, &response);

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


ApiSceneExporterProxy ApiSceneExporterProxy::create(
            const char *const                         sceneFile, //// test821 //// 
            ApiNodeProxy* const                       rootNodes[], //// test821 //// 
            const size_t                              rootNodesSize, //// test821 //// 
            const Octane::TimeT                       timeSamplesPeriod, //// test821 //// 
            const Octane::TimeT *const                timeSamples, //// test821 //// 
            const size_t                              timeSamplesSize, //// test821 //// 
            const Octane::GeometryExportFormat        geometryFormat, //// test821 //// 
            const Octane::ReferencePackageExportSettings * referencePackageSettings //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSceneExporter::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'sceneFile' [in] parameter to the request packet.
    std::string * scenefileIn = new std::string(); //// sceneFile type=string;//// ////721////
    *scenefileIn = checkString(sceneFile);
    request.set_allocated_scenefile(scenefileIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'rootNodes' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * rootnodesIn = new octaneapi::ObjectRefArrayT(); //// rootNodes type=ObjectRefArrayT;//// ////721////
    //// Client Array Type C////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = Octane::ApiNode *const [] ////
    for (size_t h = 0; h < rootNodesSize; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = rootnodesIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////4////
         item->set_handle(rootNodes[h]->getObjectHandle());
    }
    request.set_allocated_rootnodes(rootnodesIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'rootNodesSize' [in] parameter to the request packet.
    uint32_t rootnodessizeIn;
    rootnodessizeIn = static_cast<uint32_t>(rootNodesSize);////2 const size_t////
    request.set_rootnodessize(rootnodessizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'timeSamplesPeriod' [in] parameter to the request packet.
    octaneapi::TimeT * timesamplesperiodIn = new octaneapi::TimeT(); //// timeSamplesPeriod type=TimeT;//// ////721////
    ////TimeT TEST ////
    timesamplesperiodIn->set_value(static_cast<float>(timeSamplesPeriod));
    request.set_allocated_timesamplesperiod(timesamplesperiodIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'timeSamples' [in] parameter to the request packet.
    octaneapi::TimeArrayT * timesamplesIn = new octaneapi::TimeArrayT(); //// timeSamples type=TimeArrayT;//// ////721////
    //// Client Array Type E////
    //// param.mProtoCppType = TimeArrayT param.mType = const Octane::TimeT *const ////
    for (size_t h = 0; h < timeSamplesSize; h++)
    {
        auto item = timesamplesIn->add_data();
        item->set_value(timeSamples[h]);
    }
    request.set_allocated_timesamples(timesamplesIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'timeSamplesSize' [in] parameter to the request packet.
    uint32_t timesamplessizeIn;
    timesamplessizeIn = static_cast<uint32_t>(timeSamplesSize);////2 const size_t////
    request.set_timesamplessize(timesamplessizeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'geometryFormat' [in] parameter to the request packet.
    octaneapi::GeometryExportFormat geometryformatIn;
    geometryformatIn = static_cast<octaneapi::GeometryExportFormat>(geometryFormat);
    request.set_geometryformat(geometryformatIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'referencePackageSettings' [in] parameter to the request packet.
    octaneapi::ReferencePackageExportSettings * referencepackagesettingsIn = new octaneapi::ReferencePackageExportSettings(); //// referencePackageSettings type=ReferencePackageExportSettings;//// ////721////
    //// ApiFilePath/ApiTimeSampling/RenderPassExport TEST////
    ReferencePackageExportSettingsConverter::convert(*referencePackageSettings, *referencepackagesettingsIn); //// Convert Called type 1c =ReferencePackageExportSettings ////
    request.set_allocated_referencepackagesettings(referencepackagesettingsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSceneExporter::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSceneExporterService::Stub> stub = 
        octaneapi::ApiSceneExporterService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiSceneExporterProxy retVal;
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
        ApiSceneExporterProxy retVal;////714////
        return retVal;
    }
};


void ApiSceneExporterProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSceneExporter::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSceneExporter);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSceneExporterService::Stub> stub = 
        octaneapi::ApiSceneExporterService::NewStub(getGRPCSettings().getChannel());
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


Octane::ExportState ApiSceneExporterProxy::state() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSceneExporter::stateRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSceneExporter);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSceneExporter::stateResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSceneExporterService::Stub> stub = 
        octaneapi::ApiSceneExporterService::NewStub(getGRPCSettings().getChannel());
    status = stub->state(context.get(), request, &response);

    Octane::ExportState retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ExportState resultOut = response.result();
        retVal = static_cast<Octane::ExportState>(resultOut);
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


void ApiSceneExporterProxy::exportSample(
            const Octane::TimeSpanT                   interval //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSceneExporter::exportSampleRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSceneExporter);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'interval' [in] parameter to the request packet.
    octaneapi::TimeSpanT * intervalIn = new octaneapi::TimeSpanT(); //// interval type=TimeSpanT;//// ////721////
    //// TimeSpanT TEST////
    intervalIn->mutable_begin()->set_value(static_cast<float>(interval.begin));
    intervalIn->mutable_end()->set_value(static_cast<float>(interval.end));
    request.set_allocated_interval(intervalIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSceneExporterService::Stub> stub = 
        octaneapi::ApiSceneExporterService::NewStub(getGRPCSettings().getChannel());
    status = stub->exportSample(context.get(), request, &response);

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


uint32_t ApiSceneExporterProxy::sampleIx() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSceneExporter::sampleIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSceneExporter);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSceneExporter::sampleIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSceneExporterService::Stub> stub = 
        octaneapi::ApiSceneExporterService::NewStub(getGRPCSettings().getChannel());
    status = stub->sampleIx(context.get(), request, &response);

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


bool ApiSceneExporterProxy::finish(
            const float                               framesPerSecond, //// test821 //// 
            const bool                                deleteUnconnectedNodes, //// test821 //// 
            const bool                                createOcsString //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSceneExporter::finishRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSceneExporter);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'framesPerSecond' [in] parameter to the request packet.
    float framespersecondIn;
    framespersecondIn = framesPerSecond;////2 const float////
    request.set_framespersecond(framespersecondIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'deleteUnconnectedNodes' [in] parameter to the request packet.
    bool deleteunconnectednodesIn;
    deleteunconnectednodesIn = deleteUnconnectedNodes;////2 const bool////
    request.set_deleteunconnectednodes(deleteunconnectednodesIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'createOcsString' [in] parameter to the request packet.
    bool createocsstringIn;
    createocsstringIn = createOcsString;////2 const bool////
    request.set_createocsstring(createocsstringIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSceneExporter::finishResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSceneExporterService::Stub> stub = 
        octaneapi::ApiSceneExporterService::NewStub(getGRPCSettings().getChannel());
    status = stub->finish(context.get(), request, &response);

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


std::string ApiSceneExporterProxy::ocsString() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSceneExporter::ocsStringRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSceneExporter);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSceneExporter::ocsStringResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSceneExporterService::Stub> stub = 
        octaneapi::ApiSceneExporterService::NewStub(getGRPCSettings().getChannel());
    status = stub->ocsString(context.get(), request, &response);

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


