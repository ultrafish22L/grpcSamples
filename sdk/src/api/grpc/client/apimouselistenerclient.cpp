// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apimouselistenerclient.h"
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


GRPCSettings & ApiMouseListenerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiMouseListenerProxy ApiMouseListenerProxy::create(
            GRPCMouseEventCallbackT                  mouseEventsCallback, //// test821 //// 
            void *                                    privateData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMouseListener::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'mouseEventsCallback' [in] parameter to the request packet.
    octaneapi::MouseEventCallbackT * mouseeventscallbackIn = new octaneapi::MouseEventCallbackT(); //// mouseEventsCallback type=MouseEventCallbackT;//// ////721////
    // setup callback function mouseEventsCallback
    //int mouseEventsCallbackCallbackId = GRPCSettings::getNextCallbackId("GRPCMouseEventCallback"); 
    //CallbackStorage::registerGRPCMouseEventCallback(mouseEventsCallbackCallbackId, mouseEventsCallback);
    mouseeventscallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //mouseeventscallbackIn->set_callbackid(mouseEventsCallbackCallbackId);
    //if(className == "ApiMouseListener" && method.mName == "create") return true;
    request.set_allocated_mouseeventscallback(mouseeventscallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'privateData' [in] parameter to the request packet.
    uint64_t privatedataIn;
    //// USER DATA TEST ////
    privatedataIn = reinterpret_cast<uint64_t>(privateData);
    request.set_privatedata(privatedataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiMouseListener::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMouseListenerService::Stub> stub = 
        octaneapi::ApiMouseListenerService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCMouseEventCallback( response.callbackid(), mouseEventsCallback);
        CallbackStorage::registerGRPCMouseEventCallback( response.callbackid(), mouseEventsCallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiMouseListenerProxy retVal;
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
        ApiMouseListenerProxy retVal;////714////
        return retVal;
    }
};


void ApiMouseListenerProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiMouseListener::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMouseListener);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiMouseListenerService::Stub> stub = 
        octaneapi::ApiMouseListenerService::NewStub(getGRPCSettings().getChannel());
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


