// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: apireferencegraph.proto

#include "apireferencegraph.pb.h"
#include "apireferencegraph.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace octaneapi {

static const char* ApiReferenceGraphService_method_names[] = {
  "/octaneapi.ApiReferenceGraphService/create",
  "/octaneapi.ApiReferenceGraphService/obtain",
  "/octaneapi.ApiReferenceGraphService/hasAabbData",
  "/octaneapi.ApiReferenceGraphService/totalAabbEntries",
  "/octaneapi.ApiReferenceGraphService/fetchAllBounds",
  "/octaneapi.ApiReferenceGraphService/totalAabbEntriesForOutput",
  "/octaneapi.ApiReferenceGraphService/fetchBoundsForOutput",
};

std::unique_ptr< ApiReferenceGraphService::Stub> ApiReferenceGraphService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ApiReferenceGraphService::Stub> stub(new ApiReferenceGraphService::Stub(channel, options));
  return stub;
}

ApiReferenceGraphService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_create_(ApiReferenceGraphService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_obtain_(ApiReferenceGraphService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_hasAabbData_(ApiReferenceGraphService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_totalAabbEntries_(ApiReferenceGraphService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_fetchAllBounds_(ApiReferenceGraphService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_totalAabbEntriesForOutput_(ApiReferenceGraphService_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_fetchBoundsForOutput_(ApiReferenceGraphService_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ApiReferenceGraphService::Stub::create(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_createRequest& request, ::octaneapi::ApiReferenceGraph_createResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiReferenceGraph_createRequest, ::octaneapi::ApiReferenceGraph_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_create_, context, request, response);
}

void ApiReferenceGraphService::Stub::async::create(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_createRequest* request, ::octaneapi::ApiReferenceGraph_createResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiReferenceGraph_createRequest, ::octaneapi::ApiReferenceGraph_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_create_, context, request, response, std::move(f));
}

void ApiReferenceGraphService::Stub::async::create(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_createRequest* request, ::octaneapi::ApiReferenceGraph_createResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_create_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_createResponse>* ApiReferenceGraphService::Stub::PrepareAsynccreateRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_createRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiReferenceGraph_createResponse, ::octaneapi::ApiReferenceGraph_createRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_create_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_createResponse>* ApiReferenceGraphService::Stub::AsynccreateRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_createRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccreateRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiReferenceGraphService::Stub::obtain(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_obtainRequest& request, ::octaneapi::ApiReferenceGraph_obtainResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiReferenceGraph_obtainRequest, ::octaneapi::ApiReferenceGraph_obtainResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_obtain_, context, request, response);
}

void ApiReferenceGraphService::Stub::async::obtain(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_obtainRequest* request, ::octaneapi::ApiReferenceGraph_obtainResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiReferenceGraph_obtainRequest, ::octaneapi::ApiReferenceGraph_obtainResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_obtain_, context, request, response, std::move(f));
}

void ApiReferenceGraphService::Stub::async::obtain(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_obtainRequest* request, ::octaneapi::ApiReferenceGraph_obtainResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_obtain_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_obtainResponse>* ApiReferenceGraphService::Stub::PrepareAsyncobtainRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_obtainRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiReferenceGraph_obtainResponse, ::octaneapi::ApiReferenceGraph_obtainRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_obtain_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_obtainResponse>* ApiReferenceGraphService::Stub::AsyncobtainRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_obtainRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncobtainRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiReferenceGraphService::Stub::hasAabbData(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_hasAabbDataRequest& request, ::octaneapi::ApiReferenceGraph_hasAabbDataResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiReferenceGraph_hasAabbDataRequest, ::octaneapi::ApiReferenceGraph_hasAabbDataResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_hasAabbData_, context, request, response);
}

void ApiReferenceGraphService::Stub::async::hasAabbData(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_hasAabbDataRequest* request, ::octaneapi::ApiReferenceGraph_hasAabbDataResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiReferenceGraph_hasAabbDataRequest, ::octaneapi::ApiReferenceGraph_hasAabbDataResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_hasAabbData_, context, request, response, std::move(f));
}

void ApiReferenceGraphService::Stub::async::hasAabbData(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_hasAabbDataRequest* request, ::octaneapi::ApiReferenceGraph_hasAabbDataResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_hasAabbData_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_hasAabbDataResponse>* ApiReferenceGraphService::Stub::PrepareAsynchasAabbDataRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_hasAabbDataRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiReferenceGraph_hasAabbDataResponse, ::octaneapi::ApiReferenceGraph_hasAabbDataRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_hasAabbData_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_hasAabbDataResponse>* ApiReferenceGraphService::Stub::AsynchasAabbDataRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_hasAabbDataRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynchasAabbDataRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiReferenceGraphService::Stub::totalAabbEntries(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest& request, ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest, ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_totalAabbEntries_, context, request, response);
}

void ApiReferenceGraphService::Stub::async::totalAabbEntries(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest* request, ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest, ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_totalAabbEntries_, context, request, response, std::move(f));
}

void ApiReferenceGraphService::Stub::async::totalAabbEntries(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest* request, ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_totalAabbEntries_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse>* ApiReferenceGraphService::Stub::PrepareAsynctotalAabbEntriesRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse, ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_totalAabbEntries_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse>* ApiReferenceGraphService::Stub::AsynctotalAabbEntriesRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynctotalAabbEntriesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiReferenceGraphService::Stub::fetchAllBounds(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest& request, ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest, ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_fetchAllBounds_, context, request, response);
}

void ApiReferenceGraphService::Stub::async::fetchAllBounds(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest* request, ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest, ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_fetchAllBounds_, context, request, response, std::move(f));
}

void ApiReferenceGraphService::Stub::async::fetchAllBounds(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest* request, ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_fetchAllBounds_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse>* ApiReferenceGraphService::Stub::PrepareAsyncfetchAllBoundsRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse, ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_fetchAllBounds_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse>* ApiReferenceGraphService::Stub::AsyncfetchAllBoundsRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncfetchAllBoundsRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiReferenceGraphService::Stub::totalAabbEntriesForOutput(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest& request, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_totalAabbEntriesForOutput_, context, request, response);
}

void ApiReferenceGraphService::Stub::async::totalAabbEntriesForOutput(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest* request, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_totalAabbEntriesForOutput_, context, request, response, std::move(f));
}

void ApiReferenceGraphService::Stub::async::totalAabbEntriesForOutput(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest* request, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_totalAabbEntriesForOutput_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse>* ApiReferenceGraphService::Stub::PrepareAsynctotalAabbEntriesForOutputRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_totalAabbEntriesForOutput_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse>* ApiReferenceGraphService::Stub::AsynctotalAabbEntriesForOutputRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynctotalAabbEntriesForOutputRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiReferenceGraphService::Stub::fetchBoundsForOutput(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest& request, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_fetchBoundsForOutput_, context, request, response);
}

void ApiReferenceGraphService::Stub::async::fetchBoundsForOutput(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest* request, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_fetchBoundsForOutput_, context, request, response, std::move(f));
}

void ApiReferenceGraphService::Stub::async::fetchBoundsForOutput(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest* request, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_fetchBoundsForOutput_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse>* ApiReferenceGraphService::Stub::PrepareAsyncfetchBoundsForOutputRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_fetchBoundsForOutput_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse>* ApiReferenceGraphService::Stub::AsyncfetchBoundsForOutputRaw(::grpc::ClientContext* context, const ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncfetchBoundsForOutputRaw(context, request, cq);
  result->StartCall();
  return result;
}

ApiReferenceGraphService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiReferenceGraphService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiReferenceGraphService::Service, ::octaneapi::ApiReferenceGraph_createRequest, ::octaneapi::ApiReferenceGraph_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiReferenceGraphService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiReferenceGraph_createRequest* req,
             ::octaneapi::ApiReferenceGraph_createResponse* resp) {
               return service->create(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiReferenceGraphService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiReferenceGraphService::Service, ::octaneapi::ApiReferenceGraph_obtainRequest, ::octaneapi::ApiReferenceGraph_obtainResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiReferenceGraphService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiReferenceGraph_obtainRequest* req,
             ::octaneapi::ApiReferenceGraph_obtainResponse* resp) {
               return service->obtain(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiReferenceGraphService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiReferenceGraphService::Service, ::octaneapi::ApiReferenceGraph_hasAabbDataRequest, ::octaneapi::ApiReferenceGraph_hasAabbDataResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiReferenceGraphService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiReferenceGraph_hasAabbDataRequest* req,
             ::octaneapi::ApiReferenceGraph_hasAabbDataResponse* resp) {
               return service->hasAabbData(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiReferenceGraphService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiReferenceGraphService::Service, ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest, ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiReferenceGraphService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest* req,
             ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse* resp) {
               return service->totalAabbEntries(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiReferenceGraphService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiReferenceGraphService::Service, ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest, ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiReferenceGraphService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest* req,
             ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse* resp) {
               return service->fetchAllBounds(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiReferenceGraphService_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiReferenceGraphService::Service, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiReferenceGraphService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest* req,
             ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse* resp) {
               return service->totalAabbEntriesForOutput(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiReferenceGraphService_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiReferenceGraphService::Service, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiReferenceGraphService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest* req,
             ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse* resp) {
               return service->fetchBoundsForOutput(ctx, req, resp);
             }, this)));
}

ApiReferenceGraphService::Service::~Service() {
}

::grpc::Status ApiReferenceGraphService::Service::create(::grpc::ServerContext* context, const ::octaneapi::ApiReferenceGraph_createRequest* request, ::octaneapi::ApiReferenceGraph_createResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiReferenceGraphService::Service::obtain(::grpc::ServerContext* context, const ::octaneapi::ApiReferenceGraph_obtainRequest* request, ::octaneapi::ApiReferenceGraph_obtainResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiReferenceGraphService::Service::hasAabbData(::grpc::ServerContext* context, const ::octaneapi::ApiReferenceGraph_hasAabbDataRequest* request, ::octaneapi::ApiReferenceGraph_hasAabbDataResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiReferenceGraphService::Service::totalAabbEntries(::grpc::ServerContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesRequest* request, ::octaneapi::ApiReferenceGraph_totalAabbEntriesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiReferenceGraphService::Service::fetchAllBounds(::grpc::ServerContext* context, const ::octaneapi::ApiReferenceGraph_fetchAllBoundsRequest* request, ::octaneapi::ApiReferenceGraph_fetchAllBoundsResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiReferenceGraphService::Service::totalAabbEntriesForOutput(::grpc::ServerContext* context, const ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputRequest* request, ::octaneapi::ApiReferenceGraph_totalAabbEntriesForOutputResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiReferenceGraphService::Service::fetchBoundsForOutput(::grpc::ServerContext* context, const ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputRequest* request, ::octaneapi::ApiReferenceGraph_fetchBoundsForOutputResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace octaneapi

