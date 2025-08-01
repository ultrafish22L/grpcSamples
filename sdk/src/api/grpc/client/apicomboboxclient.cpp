// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apicomboboxclient.h"
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
#include "apicombobox.grpc.pb.h"
#include "apicomboboxitemclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiComboBoxProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiComboBoxProxy ApiComboBoxProxy::create(
            const Octane::ApiComboBoxItem *           items,
            const size_t                              nbOfItems,
            GRPCComboBoxChangedCallbackT             callback,
            void *                                    privateData
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiComboBox::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'items' [in] parameter to the request packet.
    octaneapi::ComboItemArrayT * itemsIn = new octaneapi::ComboItemArrayT();
    for (size_t h = 0; h < nbOfItems; h++)
    {
        auto item = itemsIn->add_data();
        item->set_id(items[h].mId);
        item->set_text(items[h].mText);
    }
    request.set_allocated_items(itemsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'nbOfItems' [in] parameter to the request packet.
    uint32_t nbofitemsIn;
    nbofitemsIn = static_cast<uint32_t>(nbOfItems);
    request.set_nbofitems(nbofitemsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'callback' [in] parameter to the request packet.
    octaneapi::ComboBoxChangedCallbackT * callbackIn = new octaneapi::ComboBoxChangedCallbackT();
    // setup callback function callback
    callbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    request.set_allocated_callback(callbackIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'privateData' [in] parameter to the request packet.
    uint64_t privatedataIn;
    privatedataIn = reinterpret_cast<uint64_t>(privateData);
    request.set_privatedata(privatedataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiComboBox::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiComboBoxService::Stub> stub =
        octaneapi::ApiComboBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCComboBoxChangedCallback( response.callbackid(), callback);
        CallbackStorage::registerGRPCComboBoxChangedCallback( response.callbackid(), callback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiComboBoxProxy retVal;
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
        ApiComboBoxProxy retVal;
        return retVal;
    }
};


void ApiComboBoxProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiComboBox::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiComboBox);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiComboBoxService::Stub> stub =
        octaneapi::ApiComboBoxService::NewStub(getGRPCSettings().getChannel());
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


void ApiComboBoxProxy::setSelectedId(
            const int                                 newItemId,
            const bool                                sendEvent
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiComboBox::setSelectedIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiComboBox);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newItemId' [in] parameter to the request packet.
    int32_t newitemidIn;
    newitemidIn = newItemId;
    request.set_newitemid(newitemidIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'sendEvent' [in] parameter to the request packet.
    bool sendeventIn;
    sendeventIn = sendEvent;
    request.set_sendevent(sendeventIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiComboBoxService::Stub> stub =
        octaneapi::ApiComboBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->setSelectedId(context.get(), request, &response);

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


int ApiComboBoxProxy::selectedId() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiComboBox::selectedIdRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiComboBox);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiComboBox::selectedIdResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiComboBoxService::Stub> stub =
        octaneapi::ApiComboBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->selectedId(context.get(), request, &response);

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


std::string ApiComboBoxProxy::text() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiComboBox::textRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiComboBox);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiComboBox::textResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiComboBoxService::Stub> stub =
        octaneapi::ApiComboBoxService::NewStub(getGRPCSettings().getChannel());
    status = stub->text(context.get(), request, &response);

    std::string retVal;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        std::string resultOut = response.result();
        // param.mType = const char *
        retVal =  resultOut;
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


