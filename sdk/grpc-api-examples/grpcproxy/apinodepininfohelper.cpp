// Copyright (C) 2025 OTOY NZ Ltd.

////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
////////////////////////////////////////////////////////////////////////////

#include "apinodepininfoclient.h"
#include "apinodepininfohelper.h"
#include <cassert>
#include "octaneinfos.h"
#include <grpcpp/grpcpp.h>
#include "common.grpc.pb.h"
#include "apinodepininfohelper.grpc.pb.h"
#include "grpcsettings.h"
#include "convertapinodepininfo.h"
#include "callbackservice.h"

namespace OctaneGRPC
{
    std::function<void()> ApiNodePinInfoExService::mBlockingOperationCallback;

    GRPCSettings& ApiNodePinInfoExService::getGRPCSettings()
    {
        return GRPCSettings::getInstance();
    }


    std::vector<ApiNodePinInfoProxy> ApiNodePinInfoExService::createApiNodePinInfoArray(
        const ApiNodePinInfo* items,
        const int              count)
    {
        /////////////////////////////////////////////////////////////////////
        // Define the request packet to send to the gRPC server.
        octaneapi::ApiNodePinInfoEx::CreateNodePinInfoArrayRequest request;

        for (int h = 0; h < count; h++)
        {
            auto nodePinInfoSrv = request.add_nodepininfo();
            ApiNodePinInfoConverter::convert(items[h], *nodePinInfoSrv);
        }

        // Make the call to the server
        octaneapi::ApiNodePinInfoEx::CreateNodePinInfoArrayResponse response;
        std::shared_ptr<grpc::ClientContext> context;
        context = std::make_unique<grpc::ClientContext>();
        std::unique_ptr<octaneapi::ApiNodePinInfoExService::Stub> stub =
            octaneapi::ApiNodePinInfoExService::NewStub(getGRPCSettings().getChannel());

        grpc::Status status = stub->createApiNodePinInfoArray(context.get(), request, &response);
        std::vector<ApiNodePinInfoProxy> results;
        if (status.ok())
        {
            int count = response.nodepininforefs_size();
            for (int i = 0; i < count; ++i)
            {
                ApiNodePinInfoProxy proxy;
                assert(response.nodepininforefs(i).handle() != 0);
                proxy.attachObjectHandle(response.nodepininforefs(i).handle());
                results.push_back(proxy);
            }
        }
        else
        {
            throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
        }
        return results;
    };


    ApiNodePinInfoProxy ApiNodePinInfoExService::createApiNodePinInfo(
        const Octane::ApiNodePinInfo& nodePinInfo)
    {
        /////////////////////////////////////////////////////////////////////
        // Define the request packet to send to the gRPC server.
        octaneapi::ApiNodePinInfoEx::CreateNodePinInfoRequest request;
        ApiNodePinInfoProxy ret;

        octaneapi::ApiNodePinInfo* nodePinInfoGrpc = new octaneapi::ApiNodePinInfo();
        ApiNodePinInfoConverter::convert(nodePinInfo, *nodePinInfoGrpc);
        request.set_allocated_nodepininfo(nodePinInfoGrpc);

        // Make the call to the server
        octaneapi::ApiNodePinInfoEx::CreateNodePinInfoResponse response;
        std::shared_ptr<grpc::ClientContext> context;
        context = std::make_unique<grpc::ClientContext>();
        std::unique_ptr<octaneapi::ApiNodePinInfoExService::Stub> stub =
            octaneapi::ApiNodePinInfoExService::NewStub(getGRPCSettings().getChannel());
        grpc::Status status = stub->createApiNodePinInfo(context.get(), request, &response);

        if (status.ok())
        {
            if (response.nodepininforef().handle() == 0)
            {
                throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
            }
            ret.attachObjectHandle(response.nodepininforef().handle());
            // new octaneapi::ObjectRef();////approved////
            // uint64_t resultHandle = objMgr.addPointer(apiResult);////2////
            // resultout->set_handle(resultHandle);
            // resultout->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem); ////11////
            // response->set_allocated_result(resultout);
        }
        else
        {
            throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
        }
        return ret;
    };


    bool ApiNodePinInfoExService::deleteApiNodePinInfo(
        const ApiNodePinInfoProxy& nodePinInfo)
    {
        /////////////////////////////////////////////////////////////////////
        // Define the request packet to send to the gRPC server.
        octaneapi::ApiNodePinInfoEx::DeleteNodePinInfoRequest request;
        bool ret = false;

        octaneapi::ApiNodePinInfo* nodePinInfoGrpc = new octaneapi::ApiNodePinInfo();
        //request.set_allocated_nodepininfo()

        // Make the call to the server
        octaneapi::ApiNodePinInfoEx::DeleteNodePinInfoResponse response;
        std::shared_ptr<grpc::ClientContext> context;
        context = std::make_unique<grpc::ClientContext>();
        std::unique_ptr<octaneapi::ApiNodePinInfoExService::Stub> stub =
            octaneapi::ApiNodePinInfoExService::NewStub(getGRPCSettings().getChannel());
        grpc::Status status = stub->deleteApiNodePinInfo(context.get(), request, &response);

        if (status.ok())
        {
            ret = response.success();
        }
        else
        {
            throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
        }
        return ret;
    }


    bool ApiNodePinInfoExService::updateApiNodePinInfo(
        const ApiNodePinInfoProxy& nodePinInfoProxy,
        const Octane::ApiNodePinInfo& nodePinInfo)
    {
        /////////////////////////////////////////////////////////////////////
        // Define the request packet to send to the gRPC server.
        octaneapi::ApiNodePinInfoEx::UpdateNodePinInfoRequest request;
        bool ret = false;

        octaneapi::ApiNodePinInfo* nodePinInfoGrpc = new octaneapi::ApiNodePinInfo();
        ApiNodePinInfoConverter::convert(nodePinInfo, *nodePinInfoGrpc);
        request.set_allocated_nodepininfo(nodePinInfoGrpc);

        // set the object reference so the server knows which object to update
        octaneapi::ObjectRef* objref = new octaneapi::ObjectRef();
        objref->set_handle(nodePinInfoProxy.getObjectHandle());
        objref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodePinInfo);
        request.set_allocated_nodepininforef(objref);

        // Make the call to the server
        octaneapi::ApiNodePinInfoEx::UpdateNodePinInfoResponse response;
        std::shared_ptr<grpc::ClientContext> context;
        context = std::make_unique<grpc::ClientContext>();
        std::unique_ptr<octaneapi::ApiNodePinInfoExService::Stub> stub =
            octaneapi::ApiNodePinInfoExService::NewStub(getGRPCSettings().getChannel());
        grpc::Status status = stub->updateApiNodePinInfo(context.get(), request, &response);

        if (status.ok())
        {
            ret = response.success();
        }
        else
        {
            throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
        }

        return ret;
    }


    bool ApiNodePinInfoExService::getApiNodePinInfo(
        const ApiNodePinInfoProxy& nodePinInfoProxy,
        Octane::ApiNodePinInfo& nodePinInfo)
    {
        /////////////////////////////////////////////////////////////////////
        // Define the request packet to send to the gRPC server.
        octaneapi::ApiNodePinInfoEx::GetNodePinInfoRequest request;
        bool ret = false;

        // set the object reference so the server knows which object to retrieve
        octaneapi::ObjectRef* objref = new octaneapi::ObjectRef();
        objref->set_handle(nodePinInfoProxy.getObjectHandle());
        objref->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodePinInfo);
        request.set_allocated_nodepininforef(objref);

        // Make the call to the server
        octaneapi::ApiNodePinInfoEx::GetNodePinInfoResponse response;
        std::shared_ptr<grpc::ClientContext> context;
        context = std::make_unique<grpc::ClientContext>();
        std::unique_ptr<octaneapi::ApiNodePinInfoExService::Stub> stub =
            octaneapi::ApiNodePinInfoExService::NewStub(getGRPCSettings().getChannel());
        grpc::Status status = stub->getApiNodePinInfo(context.get(), request, &response);

        if (status.ok())
        {
            ret = response.success();
            ApiNodePinInfoConverter::convert(response.nodepininfo(), nodePinInfo);
        }
        else
        {
            throw std::runtime_error("gRPC error (" + std::to_string(status.error_code()) + "): " + status.error_message());
        }

        return ret;
    }
}// namespace OctaneGRPC