// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apimoduledataclient.h"
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
#include "apimoduledata.grpc.pb.h"
#include "apibinarytableclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiModuleDataProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiBinaryTableProxy ApiModuleDataProxy::loadApplicationData(
            const Octane::ModuleIdT                   moduleId,
            uint32_t &                                octaneVersion
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleData::loadApplicationDataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleId' [in] parameter to the request packet.
    octaneapi::ModuleIdT * moduleidIn = new octaneapi::ModuleIdT();
    moduleidIn->set_id(moduleId);
    request.set_allocated_moduleid(moduleidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleData::loadApplicationDataResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleDataService::Stub> stub =
        octaneapi::ApiModuleDataService::NewStub(getGRPCSettings().getChannel());
    status = stub->loadApplicationData(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiBinaryTableProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());

        /////////////////////////////////////////////////////////////////////
        // Process 'octaneVersion' [out] parameter from the gRPC response packet
        uint32_t octaneVersionOut = response.octaneversion();
        octaneVersion = octaneVersionOut;
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
        ApiBinaryTableProxy retVal;
        return retVal;
    }
};


bool ApiModuleDataProxy::storeApplicationData(
            const Octane::ModuleIdT                   moduleId,
            const ApiBinaryTableProxy &               table
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiModuleData::storeApplicationDataRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'moduleId' [in] parameter to the request packet.
    octaneapi::ModuleIdT * moduleidIn = new octaneapi::ModuleIdT();
    moduleidIn->set_id(moduleId);
    request.set_allocated_moduleid(moduleidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'table' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * tableIn = new octaneapi::ObjectRef();
    tableIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiBinaryTable);
    tableIn->set_handle(table.getObjectHandle());
    request.set_allocated_table(tableIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiModuleData::storeApplicationDataResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiModuleDataService::Stub> stub =
        octaneapi::ApiModuleDataService::NewStub(getGRPCSettings().getChannel());
    status = stub->storeApplicationData(context.get(), request, &response);

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


} //end of namespace
