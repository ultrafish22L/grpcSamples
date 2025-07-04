// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apinumericboxclient.h"
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
#include "apinumericbox.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiNumericBoxProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiNumericBoxProxy ApiNumericBoxProxy::create(
            const double                              step, //// test821 //// 
            GRPCNumericBoxChangedCallbackT           callback, //// test821 //// 
            void *                                    privateData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNumericBox::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'step' [in] parameter to the request packet.
    double stepIn;
    stepIn = step;////2 const double////
    request.set_step(stepIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::NumericBoxChangedCallbackT * callbackIn = new octaneapi::NumericBoxChangedCallbackT(); //// callback type=NumericBoxChangedCallbackT;//// ////721////
    // setup callback function callback
    //int callbackCallbackId = GRPCSettings::getNextCallbackId("GRPCNumericBoxChangedCallback"); 
    //CallbackStorage::registerGRPCNumericBoxChangedCallback(callbackCallbackId, callback);
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //callbackIn->set_callbackid(callbackCallbackId);
    //if(className == "ApiNumericBox" && method.mName == "create") return true;
    request.set_allocated_callback(callbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'privateData' [in] parameter to the request packet.
    uint64_t privatedataIn;
    //// USER DATA TEST ////
    privatedataIn = reinterpret_cast<uint64_t>(privateData);
    request.set_privatedata(privatedataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNumericBox::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNumericBoxService::Stub> stub = 
        octaneapi::ApiNumericBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCNumericBoxChangedCallback( response.callbackid(), callback);
        CallbackStorage::registerGRPCNumericBoxChangedCallback( response.callbackid(), callback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiNumericBoxProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();
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
        ApiNumericBoxProxy retVal;////714////
        return retVal;
    }
};


void ApiNumericBoxProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNumericBox::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNumericBox);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNumericBoxService::Stub> stub = 
        octaneapi::ApiNumericBoxService::NewStub(getGRPCSettings().getChannel());
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


double ApiNumericBoxProxy::value() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNumericBox::valueRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNumericBox);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiNumericBox::valueResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNumericBoxService::Stub> stub = 
        octaneapi::ApiNumericBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->value(context.get(), request, &response);

    double retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        double resultOut = response.result();
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


void ApiNumericBoxProxy::setValue(
            const double                              newValue, //// test821 //// 
            const bool                                sendEvent //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNumericBox::setValueRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNumericBox);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newValue' [in] parameter to the request packet.
    double newvalueIn;
    newvalueIn = newValue;////2 const double////
    request.set_newvalue(newvalueIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sendEvent' [in] parameter to the request packet.
    bool sendeventIn;
    sendeventIn = sendEvent;////2 const bool////
    request.set_sendevent(sendeventIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNumericBoxService::Stub> stub = 
        octaneapi::ApiNumericBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->setValue(context.get(), request, &response);

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


void ApiNumericBoxProxy::setLimits(
            const double                              minimum, //// test821 //// 
            const double                              maximum, //// test821 //// 
            const double                              sliderMinimum, //// test821 //// 
            const double                              sliderMaximum //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiNumericBox::setLimitsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNumericBox);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'minimum' [in] parameter to the request packet.
    double minimumIn;
    minimumIn = minimum;////2 const double////
    request.set_minimum(minimumIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'maximum' [in] parameter to the request packet.
    double maximumIn;
    maximumIn = maximum;////2 const double////
    request.set_maximum(maximumIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sliderMinimum' [in] parameter to the request packet.
    double sliderminimumIn;
    sliderminimumIn = sliderMinimum;////2 const double////
    request.set_sliderminimum(sliderminimumIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sliderMaximum' [in] parameter to the request packet.
    double slidermaximumIn;
    slidermaximumIn = sliderMaximum;////2 const double////
    request.set_slidermaximum(slidermaximumIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiNumericBoxService::Stub> stub = 
        octaneapi::ApiNumericBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->setLimits(context.get(), request, &response);

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


