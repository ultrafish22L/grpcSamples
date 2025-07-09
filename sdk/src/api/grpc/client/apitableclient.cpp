// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apitableclient.h"
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
#include "apitable.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiTableProxy::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


ApiTableProxy ApiTableProxy::create(
            const char *                              columnHeaders[], //// test821 //// 
            const size_t                              columnHeadersLength, //// test821 //// 
            const bool                                headerVisible, //// test821 //// 
            Octane::ApiTable::NumRowsCallbackT        numRowsCallback, //// test821 //// 
            Octane::ApiTable::ContentCallbackT        contentForCellCallback, //// test821 //// 
            Octane::ApiTable::SelectionChangedCallbackT selectionChangedCallback, //// test821 //// 
            void *                                    privateData //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::createRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'columnHeaders' [in] parameter to the request packet.
    octaneapi::StringArrayT * columnheadersIn = new octaneapi::StringArrayT(); //// columnHeaders type=StringArrayT;//// ////721////
    //// Client Array Type G ////
    //// param.mProtoCppType = StringArrayT param.mType = const char *[] ////
    for (size_t h = 0; h < columnHeadersLength; h++)
    {
        columnheadersIn->add_data(static_cast<std::string>(columnHeaders[h]));
    }
    request.set_allocated_columnheaders(columnheadersIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'columnHeadersLength' [in] parameter to the request packet.
    uint32_t columnheaderslengthIn;
    columnheaderslengthIn = static_cast<uint32_t>(columnHeadersLength);////2 const size_t////
    request.set_columnheaderslength(columnheaderslengthIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'headerVisible' [in] parameter to the request packet.
    bool headervisibleIn;
    headervisibleIn = headerVisible;////2 const bool////
    request.set_headervisible(headervisibleIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'numRowsCallback' [in] parameter to the request packet.
    octaneapi::NumRowsCallbackT * numrowscallbackIn = new octaneapi::NumRowsCallbackT(); //// numRowsCallback type=NumRowsCallbackT;//// ////721////
    // setup callback function numRowsCallback
    //int numRowsCallbackCallbackId = GRPCSettings::getNextCallbackId("NumRowsCallback"); 
    //CallbackStorage::registerNumRowsCallback(numRowsCallbackCallbackId, numRowsCallback);
    numrowscallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //numrowscallbackIn->set_callbackid(numRowsCallbackCallbackId);
    //if(className == "ApiTable" && method.mName == "create") return true;
    request.set_allocated_numrowscallback(numrowscallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'contentForCellCallback' [in] parameter to the request packet.
    octaneapi::ContentCallbackT * contentforcellcallbackIn = new octaneapi::ContentCallbackT(); //// contentForCellCallback type=ContentCallbackT;//// ////721////
    // setup callback function contentForCellCallback
    //int contentForCellCallbackCallbackId = GRPCSettings::getNextCallbackId("ContentCallback"); 
    //CallbackStorage::registerContentCallback(contentForCellCallbackCallbackId, contentForCellCallback);
    contentforcellcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //contentforcellcallbackIn->set_callbackid(contentForCellCallbackCallbackId);
    //if(className == "ApiTable" && method.mName == "create") return true;
    request.set_allocated_contentforcellcallback(contentforcellcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'selectionChangedCallback' [in] parameter to the request packet.
    octaneapi::SelectionChangedCallbackT * selectionchangedcallbackIn = new octaneapi::SelectionChangedCallbackT(); //// selectionChangedCallback type=SelectionChangedCallbackT;//// ////721////
    // setup callback function selectionChangedCallback
    //int selectionChangedCallbackCallbackId = GRPCSettings::getNextCallbackId("SelectionChangedCallback"); 
    //CallbackStorage::registerSelectionChangedCallback(selectionChangedCallbackCallbackId, selectionChangedCallback);
    selectionchangedcallbackIn->set_callbacksource( GRPCSettings::getInstance().callbackSource() );
    //selectionchangedcallbackIn->set_callbackid(selectionChangedCallbackCallbackId);
    //if(className == "ApiTable" && method.mName == "create") return true;
    request.set_allocated_selectionchangedcallback(selectionchangedcallbackIn);//// 6215 ////

    /////////////////////////////////////////////////////////////////////
    // Add the 'privateData' [in] parameter to the request packet.
    uint64_t privatedataIn;
    //// USER DATA TEST ////
    privatedataIn = reinterpret_cast<uint64_t>(privateData);
    request.set_privatedata(privatedataIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTable::createResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->create(context.get(), request, &response);

    if (status.ok())
    {
        // set callback Id CallbackStorage::registerNumRowsCallback( response.callbackid(), numRowsCallback);
        CallbackStorage::registerNumRowsCallback( response.callbackid(), numRowsCallback);
        // set callback Id CallbackStorage::registerContentCallback( response.callbackid2(), contentForCellCallback);
        CallbackStorage::registerContentCallback( response.callbackid2(), contentForCellCallback);
        // set callback Id CallbackStorage::registerSelectionChangedCallback( response.callbackid3(), selectionChangedCallback);
        CallbackStorage::registerSelectionChangedCallback( response.callbackid3(), selectionChangedCallback);
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        octaneapi::ObjectRef resultOut = response.result();
        // Create a proxy object containing the object ID reference to the remote object
        // passed to us in the 'octaneapi::ObjectRef' object.
        // using a `ObjectRef` object.
        ApiTableProxy retVal;
        retVal.attachObjectHandle(resultOut.handle());

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId' [out] parameter from the gRPC response packet
        int32_t callbackIdOut = response.callbackid();

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId2' [out] parameter from the gRPC response packet
        int32_t callbackId2Out = response.callbackid2();

        /////////////////////////////////////////////////////////////////////
        // Process 'callbackId3' [out] parameter from the gRPC response packet
        int32_t callbackId3Out = response.callbackid3();
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
        ApiTableProxy retVal;////714////
        return retVal;
    }
};


void ApiTableProxy::destroy()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::destroyRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
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


void ApiTableProxy::updateContent()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::updateContentRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->updateContent(context.get(), request, &response);

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


void ApiTableProxy::selectRow(
            const int                                 rowNumber, //// test821 //// 
            const bool                                dontScrollToShowThisRow, //// test821 //// 
            const bool                                deselectOthersFirst //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::selectRowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rowNumber' [in] parameter to the request packet.
    int32_t rownumberIn;
    rownumberIn = rowNumber;////2 const int////
    request.set_rownumber(rownumberIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'dontScrollToShowThisRow' [in] parameter to the request packet.
    bool dontscrolltoshowthisrowIn;
    dontscrolltoshowthisrowIn = dontScrollToShowThisRow;////2 const bool////
    request.set_dontscrolltoshowthisrow(dontscrolltoshowthisrowIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'deselectOthersFirst' [in] parameter to the request packet.
    bool deselectothersfirstIn;
    deselectothersfirstIn = deselectOthersFirst;////2 const bool////
    request.set_deselectothersfirst(deselectothersfirstIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->selectRow(context.get(), request, &response);

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


void ApiTableProxy::selectRangeOfRows(
            const int                                 firstRow, //// test821 //// 
            const int                                 lastRow //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::selectRangeOfRowsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'firstRow' [in] parameter to the request packet.
    int32_t firstrowIn;
    firstrowIn = firstRow;////2 const int////
    request.set_firstrow(firstrowIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'lastRow' [in] parameter to the request packet.
    int32_t lastrowIn;
    lastrowIn = lastRow;////2 const int////
    request.set_lastrow(lastrowIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->selectRangeOfRows(context.get(), request, &response);

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


void ApiTableProxy::deselectRow(
            const int                                 rowNumber //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::deselectRowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rowNumber' [in] parameter to the request packet.
    int32_t rownumberIn;
    rownumberIn = rowNumber;////2 const int////
    request.set_rownumber(rownumberIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->deselectRow(context.get(), request, &response);

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


void ApiTableProxy::deselectAllRows()
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::deselectAllRowsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->deselectAllRows(context.get(), request, &response);

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


void ApiTableProxy::flipRowSelection(
            const int                                 rowNumber //// last param ////
            )

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::flipRowSelectionRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rowNumber' [in] parameter to the request packet.
    int32_t rownumberIn;
    rownumberIn = rowNumber;////2 const int////
    request.set_rownumber(rownumberIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    google::protobuf::Empty response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->flipRowSelection(context.get(), request, &response);

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


bool ApiTableProxy::isRowSelected(
            const int                                 rowNumber //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::isRowSelectedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'rowNumber' [in] parameter to the request packet.
    int32_t rownumberIn;
    rownumberIn = rowNumber;////2 const int////
    request.set_rownumber(rownumberIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTable::isRowSelectedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->isRowSelected(context.get(), request, &response);

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


int ApiTableProxy::numSelectedRows() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::numSelectedRowsRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTable::numSelectedRowsResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->numSelectedRows(context.get(), request, &response);

    int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
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


int ApiTableProxy::selectedRow(
            const int                                 index //// last param ////
            ) const

{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::selectedRowRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Add the 'index' [in] parameter to the request packet.
    int32_t indexIn;
    indexIn = index;////2 const int////
    request.set_index(indexIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTable::selectedRowResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->selectedRow(context.get(), request, &response);

    int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
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


int ApiTableProxy::lastRowSelected() const
{
    grpc::Status status = grpc::Status::OK;
    /////////////////////////////////////////////////////////////////////
    // Define the request packet to send to the gRPC server.
    octaneapi::ApiTable::lastRowSelectedRequest request;

    /////////////////////////////////////////////////////////////////////
    // Add the 'objectPtr' [in] parameter to the request packet.
    // The proxy object contains the ID of the remote object. Pass this ID to the server
    // using a `ObjectRef` object.
    octaneapi::ObjectRef * objectptrIn = new octaneapi::ObjectRef();////761////
    objectptrIn->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTable);////5////
    objectptrIn->set_handle(getObjectHandle());
    request.set_allocated_objectptr(objectptrIn);

    /////////////////////////////////////////////////////////////////////
    // Make the call to the server
    octaneapi::ApiTable::lastRowSelectedResponse response;
    std::shared_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    std::unique_ptr<octaneapi::ApiTableService::Stub> stub = 
        octaneapi::ApiTableService::NewStub(getGRPCSettings().getChannel());
    status = stub->lastRowSelected(context.get(), request, &response);

    int retVal = 0;
    if (status.ok())
    {
        /////////////////////////////////////////////////////////////////////
        // Process 'result' [out] parameter from the gRPC response packet
        int32_t resultOut = response.result();
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


