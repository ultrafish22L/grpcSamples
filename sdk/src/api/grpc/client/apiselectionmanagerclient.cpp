// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apiselectionmanagerclient.h"
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
#include "apiselectionmanager.grpc.pb.h"
#include "apinodeclient.h"
#include "apiitemclient.h"
#include "grpcchangeevents.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


namespace OctaneGRPC
{


GRPCSettings & ApiSelectionManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiSelectionManagerProxy::isItemSelected(
            const ApiItemProxy &                      item
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::isItemSelectedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'item' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    itemIn->set_handle(item.getObjectHandle());
    request.set_allocated_item(itemIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::isItemSelectedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->isItemSelected(context.get(), request, &response);

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


bool ApiSelectionManagerProxy::isPinSelected(
            const ApiNodeProxy &                      node,
            const Octane::PinId                       pinId
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::isPinSelectedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    nodeIn->set_handle(node.getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinId' [in] parameter to the request packet.
    octaneapi::PinId pinidIn;
        pinidIn = static_cast<octaneapi::PinId>(pinId);
    request.set_pinid(pinidIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::isPinSelectedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->isPinSelected(context.get(), request, &response);

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


bool ApiSelectionManagerProxy::isPinSelected(
            const ApiNodeProxy &                      node,
            const char *                              pinName
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::isPinSelected1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    nodeIn->set_handle(node.getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string();
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::isPinSelected1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->isPinSelected1(context.get(), request, &response);

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


bool ApiSelectionManagerProxy::isPinSelectedIx(
            const ApiNodeProxy &                      node,
            const uint32_t                            pinIx
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::isPinSelectedIxRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'node' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);
    nodeIn->set_handle(node.getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;
    request.set_pinix(pinixIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::isPinSelectedIxResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->isPinSelectedIx(context.get(), request, &response);

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


size_t ApiSelectionManagerProxy::selectedItemCount()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::selectedItemCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::selectedItemCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->selectedItemCount(context.get(), request, &response);

    size_t retVal = 0;
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


size_t ApiSelectionManagerProxy::selectedPinCount()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::selectedPinCountRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::selectedPinCountResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->selectedPinCount(context.get(), request, &response);

    size_t retVal = 0;
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


void ApiSelectionManagerProxy::getSelection(
            std::vector<ApiItemProxy> &               selectedItems
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::getSelectionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::getSelectionResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->getSelection(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'selectedItems' [out] parameter from the gRPC response packet
        octaneapi::ObjectRefArrayT selectedItemsOut = response.selecteditems();
        selectedItems.reserve(selectedItemsOut.data_size());
        for (int i = 0; i < selectedItemsOut.data_size(); i++)
        {
            ApiItemProxy item;
            item.attachObjectHandle(selectedItemsOut.data().Get(i).handle());
            selectedItems.push_back(item);
        }
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


void ApiSelectionManagerProxy::getSelection(
            std::vector<ApiPinSelectionProxy> &       selectedPins
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::getSelection1Request request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::getSelection1Response response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->getSelection1(context.get(), request, &response);

    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'selectedPins' [out] parameter from the gRPC response packet
        octaneapi::PinSelectionArrayT selectedPinsOut = response.selectedpins();
        for (int i = 0; i < selectedPinsOut.data_size(); i++)
        {
            ApiPinSelectionProxy item;
            item.mPinIndex = selectedPinsOut.data(i).pinindex();
            item.mNode.attachObjectHandle(selectedPinsOut.data(i).node().handle());
            selectedPins.push_back(std::move(item));
        }
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


void ApiSelectionManagerProxy::clearSelection()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::clearSelectionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->clearSelection(context.get(), request, &response);

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


void ApiSelectionManagerProxy::setSelection(
            Octane::ApiArray<ApiItemProxy *>          selectedItems,
            Octane::ApiArray<ApiPinSelectionProxy *>  selectedPins,
            const bool                                selectDestPins
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::setSelectionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectedItems' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * selecteditemsIn = new octaneapi::ObjectRefArrayT();
    for (int h = 0; h < selectedItems.mSize; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = selecteditemsIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
         item->set_handle(selectedItems.mData[h]->getObjectHandle());
    }
    request.set_allocated_selecteditems(selecteditemsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectedPins' [in] parameter to the request packet.
    octaneapi::PinSelectionArrayT * selectedpinsIn = new octaneapi::PinSelectionArrayT();
    for (int h = 0; h < selectedPins.mSize; h++)
    {
         auto item = selectedpinsIn->add_data();
         item->set_pinindex(selectedPins.mData[h]->mPinIndex);

         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
             auto node = new octaneapi::ObjectRef();
         node->set_handle(selectedPins.mData[h]->mNode.getObjectHandle());
         item->set_allocated_node(node);
    }
    request.set_allocated_selectedpins(selectedpinsIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectDestPins' [in] parameter to the request packet.
    bool selectdestpinsIn;
    selectdestpinsIn = selectDestPins;
    request.set_selectdestpins(selectdestpinsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->setSelection(context.get(), request, &response);

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


void ApiSelectionManagerProxy::select(
            const ApiItemProxy &                      item,
            const bool                                selectDestPins
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::selectRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'item' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    itemIn->set_handle(item.getObjectHandle());
    request.set_allocated_item(itemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectDestPins' [in] parameter to the request packet.
    bool selectdestpinsIn;
    selectdestpinsIn = selectDestPins;
    request.set_selectdestpins(selectdestpinsIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->select(context.get(), request, &response);

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


void ApiSelectionManagerProxy::select(
            ApiPinSelectionProxy                      pinSelection,
            const bool                                selectConnectedItem
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::select1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinSelection' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * pinselectionIn = new octaneapi::ObjectRef();
    pinselectionIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSelectionManager_PinSelection);
    pinselectionIn->set_handle(pinSelection.getObjectHandle());
    request.set_allocated_pinselection(pinselectionIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectConnectedItem' [in] parameter to the request packet.
    bool selectconnecteditemIn;
    selectconnecteditemIn = selectConnectedItem;
    request.set_selectconnecteditem(selectconnecteditemIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->select1(context.get(), request, &response);

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


void ApiSelectionManagerProxy::deselect(
            const ApiItemProxy &                      item
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::deselectRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'item' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    itemIn->set_handle(item.getObjectHandle());
    request.set_allocated_item(itemIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->deselect(context.get(), request, &response);

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


void ApiSelectionManagerProxy::deselect(
            ApiPinSelectionProxy                      pin
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::deselect1Request request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'pin' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * pinIn = new octaneapi::ObjectRef();
    pinIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSelectionManager_PinSelection);
    pinIn->set_handle(pin.getObjectHandle());
    request.set_allocated_pin(pinIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->deselect1(context.get(), request, &response);

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


void ApiSelectionManagerProxy::swapSelection(
            const ApiItemProxy &                      oldItem,
            const ApiItemProxy &                      newItem
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::swapSelectionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'oldItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * olditemIn = new octaneapi::ObjectRef();
    olditemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    olditemIn->set_handle(oldItem.getObjectHandle());
    request.set_allocated_olditem(olditemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * newitemIn = new octaneapi::ObjectRef();
    newitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);
    newitemIn->set_handle(newItem.getObjectHandle());
    request.set_allocated_newitem(newitemIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->swapSelection(context.get(), request, &response);

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


void ApiSelectionManagerProxy::addSelectionObserver(
            GRPCSelectionManagerObserver             observer
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::addSelectionObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCSelectionManagerObserverT * observerIn = new octaneapi::GRPCSelectionManagerObserverT();
    // setup observer function observer
    //int observerCallbackId = GRPCSettings::getNextCallbackId("GRPCSelectionManagerObserver");
    //CallbackStorage::registerGRPCSelectionManagerObserver(observerCallbackId, observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //observerIn->set_callbackid(observerCallbackId);
observerIn->set_userdata(reinterpret_cast<uint64_t>(observer.mUserData));
    //if(className == "ApiSelectionManager" && method.mName == "addSelectionObserver") return true;
    request.set_allocated_observer(observerIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiSelectionManager::addSelectionObserverResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->addSelectionObserver(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerGRPCSelectionManagerObserver( response.callbackid(), observer.mCallback);
        CallbackStorage::registerGRPCSelectionManagerObserver( response.callbackid(), observer.mCallback);
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


void ApiSelectionManagerProxy::removeSelectionObserver(
            GRPCSelectionManagerObserver             observer
            )
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::removeSelectionObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCSelectionManagerObserverT * observerIn = new octaneapi::GRPCSelectionManagerObserverT();
    // remove observer function observer
    int observerCallbackId = CallbackStorage::unregisterGRPCSelectionManagerObserver(observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
   observerIn->set_callbackid(observerCallbackId);
    request.set_allocated_observer(observerIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiSelectionManagerService::Stub> stub =
        octaneapi::ApiSelectionManagerService::NewStub(getGRPCSettings().getChannel());
    status = stub->removeSelectionObserver(context.get(), request, &response);

    if (status.ok())
    {
        // free callbackId
        // GRPCSettings::releaseCallbackId("GRPCSelectionManagerObserver", response.callbackid());
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


} //end of namespace
