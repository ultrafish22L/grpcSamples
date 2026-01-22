// Copyright (C) 2026 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apimousewheeldetailsclient.h"
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
#include "apimouselistener.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"
#include "convertapimousewheeldetails.h"


namespace OctaneGRPC
{


GRPCSettings & ApiMouseWheelDetailsProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


Octane::ApiMouseWheelDetails ApiMouseWheelDetailsProxy::make()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMouseWheelDetails::makeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMouseWheelDetails::makeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMouseWheelDetailsService::Stub> stub =
        octaneapi::ApiMouseWheelDetailsService::NewStub(getGRPCSettings().getChannel());
    status = stub->make1(context.get(), request, &response);

    Octane::ApiMouseWheelDetails retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ApiMouseWheelDetails resultOut = response.result();
        // Using Converter 7, type = Octane::ApiMouseWheelDetails, protoType = ApiMouseWheelDetails
        ApiMouseWheelDetailsConverter::convert(resultOut, retVal); // 22 Convert Called type 4 =ApiMouseWheelDetails;
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
