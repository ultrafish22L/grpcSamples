// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "renderresultstatisticsclient.h"
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
#include "octanerenderpasses.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & RenderResultStatisticsProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void RenderResultStatisticsProxy::clear()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::clearRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->clear(context.get(), request, &response);

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


OctaneVec::uint32_2 RenderResultStatisticsProxy::internalFilmResolution() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::internalFilmResolutionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::RenderResultStatistics::internalFilmResolutionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->internalFilmResolution(context.get(), request, &response);

    OctaneVec::uint32_2 retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::uint32_2 resultOut = response.result();
        retVal.x = resultOut.x();
        retVal.y = resultOut.y();
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


Octane::ImageChannelType RenderResultStatisticsProxy::channelType() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::channelTypeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::RenderResultStatistics::channelTypeResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->channelType(context.get(), request, &response);

    Octane::ImageChannelType retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ImageChannelType resultOut = response.result();
        retVal = static_cast<Octane::ImageChannelType>(resultOut);
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


uint32_t RenderResultStatisticsProxy::samplesPerPixel(
            const Octane::RenderPassId                renderPassId
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::samplesPerPixelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::RenderResultStatistics::samplesPerPixelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->samplesPerPixel(context.get(), request, &response);

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


uint32_t RenderResultStatisticsProxy::maxSamplesPerPixel(
            const Octane::RenderPassId                renderPassId
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::maxSamplesPerPixelRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::RenderResultStatistics::maxSamplesPerPixelResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->maxSamplesPerPixel(context.get(), request, &response);

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


double RenderResultStatisticsProxy::samplesPerSecond(
            const Octane::RenderPassId                renderPassId
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::samplesPerSecondRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::RenderResultStatistics::samplesPerSecondResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->samplesPerSecond(context.get(), request, &response);

    double retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        double resultOut = response.result();
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


double RenderResultStatisticsProxy::progress(
            const Octane::RenderPassId                renderPassId
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::progressRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::RenderResultStatistics::progressResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->progress(context.get(), request, &response);

    double retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        double resultOut = response.result();
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


bool RenderResultStatisticsProxy::started(
            const Octane::RenderPassId                renderPassId
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::startedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::RenderResultStatistics::startedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->started(context.get(), request, &response);

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


bool RenderResultStatisticsProxy::finished(
            const Octane::RenderPassId                renderPassId
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::RenderResultStatistics::finishedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'renderPassId' [in] parameter to the request packet.
    octaneapi::RenderPassId renderpassidIn;
    renderpassidIn = static_cast<octaneapi::RenderPassId>(renderPassId);
    request.set_renderpassid(renderpassidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::RenderResultStatistics::finishedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::RenderResultStatisticsService::Stub> stub =
        octaneapi::RenderResultStatisticsService::NewStub(getGRPCSettings().getChannel());
    status = stub->finished(context.get(), request, &response);

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


