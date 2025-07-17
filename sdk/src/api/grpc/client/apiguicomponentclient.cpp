// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apiguicomponentclient.h"
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
#include "apiguicomponent.grpc.pb.h"
#include "apimouselistenerclient.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiGuiComponentProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


void ApiGuiComponentProxy::addChildComponent(
            ApiGuiComponentProxy &                    child
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::addChildComponentRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
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
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->addChildComponent(context.get(), request, &response);

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


void ApiGuiComponentProxy::removeChildComponent(
            ApiGuiComponentProxy &                    child
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::removeChildComponentRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
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
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeChildComponent(context.get(), request, &response);

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


void ApiGuiComponentProxy::setSize(
            const int                                 width,
            const int                                 height
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::setSizeRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'width' [in] parameter to the request packet.
    int32_t widthIn;
    widthIn = width;
    request.set_width(widthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'height' [in] parameter to the request packet.
    int32_t heightIn;
    heightIn = height;
    request.set_height(heightIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->setSize(context.get(), request, &response);

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


int ApiGuiComponentProxy::width() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::widthRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGuiComponent::widthResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
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


int ApiGuiComponentProxy::height() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::heightRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGuiComponent::heightResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
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


void ApiGuiComponentProxy::setTopLeftPosition(
            const int                                 x,
            const int                                 y
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::setTopLeftPositionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'x' [in] parameter to the request packet.
    int32_t xIn;
    xIn = x;
    request.set_x(xIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'y' [in] parameter to the request packet.
    int32_t yIn;
    yIn = y;
    request.set_y(yIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->setTopLeftPosition(context.get(), request, &response);

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


int ApiGuiComponentProxy::xPosition() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::xPositionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGuiComponent::xPositionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->xPosition(context.get(), request, &response);

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


int ApiGuiComponentProxy::yPosition() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::yPositionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGuiComponent::yPositionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->yPosition(context.get(), request, &response);

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


void ApiGuiComponentProxy::setEnabled(
            const bool                                enabled
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::setEnabledRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'enabled' [in] parameter to the request packet.
    bool enabledIn;
    enabledIn = enabled;
    request.set_enabled(enabledIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->setEnabled(context.get(), request, &response);

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


bool ApiGuiComponentProxy::isEnabled() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::isEnabledRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGuiComponent::isEnabledResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->isEnabled(context.get(), request, &response);

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


void ApiGuiComponentProxy::setTooltip(
            const char *                              tooltip
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::setTooltipRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'tooltip' [in] parameter to the request packet.
    std::string * tooltipIn = new std::string();
    *tooltipIn = checkString(tooltip);
    request.set_allocated_tooltip(tooltipIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->setTooltip(context.get(), request, &response);

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


std::string ApiGuiComponentProxy::tooltip() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::tooltipRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiGuiComponent::tooltipResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->tooltip(context.get(), request, &response);

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


void ApiGuiComponentProxy::addMouseListener(
            ApiMouseListenerProxy *                   newListener,
            bool                                      wantsEventsForAllNestedChildComponents
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::addMouseListenerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newListener' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * newlistenerIn = new octaneapi::ObjectRef();
    newlistenerIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMouseListener);
    newlistenerIn->set_handle(newListener->getObjectHandle());
    request.set_allocated_newlistener(newlistenerIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'wantsEventsForAllNestedChildComponents' [in] parameter to the request packet.
    bool wantseventsforallnestedchildcomponentsIn;
    wantseventsforallnestedchildcomponentsIn = wantsEventsForAllNestedChildComponents;
    request.set_wantseventsforallnestedchildcomponents(wantseventsforallnestedchildcomponentsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->addMouseListener(context.get(), request, &response);

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


void ApiGuiComponentProxy::removeMouseListener(
            ApiMouseListenerProxy *                   listenerToRemove
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiGuiComponent::removeMouseListenerRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'listenerToRemove' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * listenertoremoveIn = new octaneapi::ObjectRef();
    listenertoremoveIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiMouseListener);
    listenertoremoveIn->set_handle(listenerToRemove->getObjectHandle());
    request.set_allocated_listenertoremove(listenertoremoveIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiGuiComponentService::Stub> stub =
        octaneapi::ApiGuiComponentService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeMouseListener(context.get(), request, &response);

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


