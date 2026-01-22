// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apidiagnosticsclient.h"
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
#include "apidiagnostics.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiDiagnosticsProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiDiagnosticsProxy::diagnosticCommand(
            const uint32_t                            commandType,
            const uint32_t                            delayInSeconds
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiDiagnostics::diagnosticCommandRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'commandType' [in] parameter to the request packet.
    uint32_t commandtypeIn;
    commandtypeIn = commandType;
    request.set_commandtype(commandtypeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'delayInSeconds' [in] parameter to the request packet.
    uint32_t delayinsecondsIn;
    delayinsecondsIn = delayInSeconds;
    request.set_delayinseconds(delayinsecondsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiDiagnosticsService::Stub> stub =
        octaneapi::ApiDiagnosticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->diagnosticCommand(context.get(), request, &response);

    if (status.ok())
    {
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
};


} //end of namespace
