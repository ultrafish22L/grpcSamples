// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

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


GRPCSettings & ApiSelectionManagerProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


bool ApiSelectionManagerProxy::isItemSelected(
            const ApiItemProxy &                      item //// last param ////
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
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();////761////
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////5////
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


bool ApiSelectionManagerProxy::isPinSelected(
            const ApiNodeProxy &                      node, //// test821 //// 
            const Octane::PinId                       pinId //// last param ////
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
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();////761////
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
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


bool ApiSelectionManagerProxy::isPinSelected(
            const ApiNodeProxy &                      node, //// test821 //// 
            const char *                              pinName //// last param ////
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
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();////761////
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    nodeIn->set_handle(node.getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinName' [in] parameter to the request packet.
    std::string * pinnameIn = new std::string(); //// pinName type=string;//// ////721////
    *pinnameIn = checkString(pinName);
    request.set_allocated_pinname(pinnameIn);//// 6215 ////

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


bool ApiSelectionManagerProxy::isPinSelectedIx(
            const ApiNodeProxy &                      node, //// test821 //// 
            const uint32_t                            pinIx //// last param ////
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
    octaneapi::ObjectRef * nodeIn = new octaneapi::ObjectRef();////761////
    nodeIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNode);////5////
    nodeIn->set_handle(node.getObjectHandle());
    request.set_allocated_node(nodeIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'pinIx' [in] parameter to the request packet.
    uint32_t pinixIn;
    pinixIn = pinIx;////2 const uint32_t////
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


void ApiSelectionManagerProxy::getSelection(
            std::vector<ApiItemProxy> &               selectedItems //// last param ////
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
        ////UNTESTED client array code 1////
        selectedItems.reserve(selectedItemsOut.data_size());
        for (int i = 0; i < selectedItemsOut.data_size(); i++)
        {
            //// using unique_ptr 2 ////
            ApiItemProxy item;
            item.attachObjectHandle(selectedItemsOut.data().Get(i).handle()); ////211b////
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
            std::vector<ApiPinSelectionProxy> &       selectedPins //// last param ////
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
            ////param.mProtoCppType = PinSelectionArrayT param.mType = ApiArray<Octane::ApiSelectionManager::PinSelection> & ////
            ////special case PinSelectionArrayT 2////
            ApiPinSelectionProxy item;//// 217 ////
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
            Octane::ApiArray<ApiItemProxy *>          selectedItems, //// test821 //// 
            Octane::ApiArray<ApiPinSelectionProxy *>  selectedPins, //// test821 //// 
            const bool                                selectDestPins //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::setSelectionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectedItems' [in] parameter to the request packet.
    octaneapi::ObjectRefArrayT * selecteditemsIn = new octaneapi::ObjectRefArrayT(); //// selectedItems type=ObjectRefArrayT;//// ////721////
    //// Client Array Type B////
    //// param.mProtoCppType = ObjectRefArrayT param.mType = const ApiArray<Octane::ApiItem *> & ////
    for (int h = 0; h < selectedItems.mSize; h++)
    {
         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto item = selecteditemsIn->add_data();
         item->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////6////
         item->set_handle(selectedItems.mData[h]->getObjectHandle());
    }
    request.set_allocated_selecteditems(selecteditemsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectedPins' [in] parameter to the request packet.
    octaneapi::PinSelectionArrayT * selectedpinsIn = new octaneapi::PinSelectionArrayT(); //// selectedPins type=PinSelectionArrayT;//// ////721////
    //// Client Array Type B////
    //// param.mProtoCppType = PinSelectionArrayT param.mType = const ApiArray<Octane::ApiSelectionManager::PinSelection> & ////
    for (int h = 0; h < selectedPins.mSize; h++)
    {
         //// special case PinSelectionArrayT 1////
         auto item = selectedpinsIn->add_data();
         item->set_pinindex(selectedPins.mData[h]->mPinIndex);

         // The proxy object contains the ID of the remote object. Pass this ID to the server
         // using a `ObjectRef` object.
         auto node = new octaneapi::ObjectRef();
         node->set_handle(selectedPins.mData[h]->mNode.getObjectHandle());
         item->set_allocated_node(node);
    }
    request.set_allocated_selectedpins(selectedpinsIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectDestPins' [in] parameter to the request packet.
    bool selectdestpinsIn;
    selectdestpinsIn = selectDestPins;////2 const bool////
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
            const ApiItemProxy &                      item, //// test821 //// 
            const bool                                selectDestPins //// last param ////
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
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();////761////
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////5////
    itemIn->set_handle(item.getObjectHandle());
    request.set_allocated_item(itemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectDestPins' [in] parameter to the request packet.
    bool selectdestpinsIn;
    selectdestpinsIn = selectDestPins;////2 const bool////
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
            ApiPinSelectionProxy                      pinSelection, //// test821 //// 
            const bool                                selectConnectedItem //// last param ////
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
    octaneapi::ObjectRef * pinselectionIn = new octaneapi::ObjectRef();////761////
    pinselectionIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSelectionManager_PinSelection);////5////
    pinselectionIn->set_handle(pinSelection.getObjectHandle());
    request.set_allocated_pinselection(pinselectionIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectConnectedItem' [in] parameter to the request packet.
    bool selectconnecteditemIn;
    selectconnecteditemIn = selectConnectedItem;////2 const bool////
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
            const ApiItemProxy &                      item //// last param ////
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
    octaneapi::ObjectRef * itemIn = new octaneapi::ObjectRef();////761////
    itemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////5////
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
            ApiPinSelectionProxy                      pin //// last param ////
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
    octaneapi::ObjectRef * pinIn = new octaneapi::ObjectRef();////761////
    pinIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiSelectionManager_PinSelection);////5////
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
            const ApiItemProxy &                      oldItem, //// test821 //// 
            const ApiItemProxy &                      newItem //// last param ////
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
    octaneapi::ObjectRef * olditemIn = new octaneapi::ObjectRef();////761////
    olditemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////5////
    olditemIn->set_handle(oldItem.getObjectHandle());
    request.set_allocated_olditem(olditemIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'newItem' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * newitemIn = new octaneapi::ObjectRef();////761////
    newitemIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);////5////
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
            GRPCSelectionManagerObserver             observer //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::addSelectionObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCSelectionManagerObserverT * observerIn = new octaneapi::GRPCSelectionManagerObserverT(); //// observer type=GRPCSelectionManagerObserverT;//// ////721////
    // setup observer function observer
    //int observerCallbackId = GRPCSettings::getNextCallbackId("GRPCSelectionManagerObserver"); 
    //CallbackStorage::registerGRPCSelectionManagerObserver(observerCallbackId, observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //observerIn->set_callbackid(observerCallbackId);
    observerIn->set_userdata(reinterpret_cast<uint64_t>(observer.mUserData));
    //if(className == "ApiSelectionManager" && method.mName == "addSelectionObserver") return true;
    request.set_allocated_observer(observerIn);//// 6215 ////

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
            GRPCSelectionManagerObserver             observer //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiSelectionManager::removeSelectionObserverRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'observer' [in] parameter to the request packet.
    octaneapi::GRPCSelectionManagerObserverT * observerIn = new octaneapi::GRPCSelectionManagerObserverT(); //// observer type=GRPCSelectionManagerObserverT;//// ////721////
    // remove observer function observer
    int observerCallbackId = CallbackStorage::unregisterGRPCSelectionManagerObserver(observer.mCallback);
    //octaneapi::OnChangeT * observerchangeT = new octaneapi::OnChangeT();
    //observerchangeT->set_callbackid(observerCallbackId);
    observerIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    observerIn->set_callbackid(observerCallbackId);
    request.set_allocated_observer(observerIn);//// 6215 ////

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


