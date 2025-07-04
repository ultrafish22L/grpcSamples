// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: apiimagecomponent.proto

#include "apiimagecomponent.pb.h"
#include "apiimagecomponent.grpc.pb.h"

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

static const char* ApiImageComponentService_method_names[] = {
  "/octaneapi.ApiImageComponentService/create",
  "/octaneapi.ApiImageComponentService/destroy",
  "/octaneapi.ApiImageComponentService/updateTo",
};

std::unique_ptr< ApiImageComponentService::Stub> ApiImageComponentService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ApiImageComponentService::Stub> stub(new ApiImageComponentService::Stub(channel, options));
  return stub;
}

ApiImageComponentService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_create_(ApiImageComponentService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_destroy_(ApiImageComponentService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_updateTo_(ApiImageComponentService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ApiImageComponentService::Stub::create(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_createRequest& request, ::octaneapi::ApiImageComponent_createResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiImageComponent_createRequest, ::octaneapi::ApiImageComponent_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_create_, context, request, response);
}

void ApiImageComponentService::Stub::async::create(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_createRequest* request, ::octaneapi::ApiImageComponent_createResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiImageComponent_createRequest, ::octaneapi::ApiImageComponent_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_create_, context, request, response, std::move(f));
}

void ApiImageComponentService::Stub::async::create(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_createRequest* request, ::octaneapi::ApiImageComponent_createResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_create_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiImageComponent_createResponse>* ApiImageComponentService::Stub::PrepareAsynccreateRaw(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_createRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiImageComponent_createResponse, ::octaneapi::ApiImageComponent_createRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_create_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiImageComponent_createResponse>* ApiImageComponentService::Stub::AsynccreateRaw(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_createRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccreateRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiImageComponentService::Stub::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_destroyRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiImageComponent_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_destroy_, context, request, response);
}

void ApiImageComponentService::Stub::async::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_destroyRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiImageComponent_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_destroy_, context, request, response, std::move(f));
}

void ApiImageComponentService::Stub::async::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_destroyRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_destroy_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiImageComponentService::Stub::PrepareAsyncdestroyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_destroyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiImageComponent_destroyRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_destroy_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiImageComponentService::Stub::AsyncdestroyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_destroyRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdestroyRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiImageComponentService::Stub::updateTo(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_updateToRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiImageComponent_updateToRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_updateTo_, context, request, response);
}

void ApiImageComponentService::Stub::async::updateTo(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_updateToRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiImageComponent_updateToRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_updateTo_, context, request, response, std::move(f));
}

void ApiImageComponentService::Stub::async::updateTo(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_updateToRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_updateTo_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiImageComponentService::Stub::PrepareAsyncupdateToRaw(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_updateToRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiImageComponent_updateToRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_updateTo_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiImageComponentService::Stub::AsyncupdateToRaw(::grpc::ClientContext* context, const ::octaneapi::ApiImageComponent_updateToRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncupdateToRaw(context, request, cq);
  result->StartCall();
  return result;
}

ApiImageComponentService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiImageComponentService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiImageComponentService::Service, ::octaneapi::ApiImageComponent_createRequest, ::octaneapi::ApiImageComponent_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiImageComponentService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiImageComponent_createRequest* req,
             ::octaneapi::ApiImageComponent_createResponse* resp) {
               return service->create(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiImageComponentService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiImageComponentService::Service, ::octaneapi::ApiImageComponent_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiImageComponentService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiImageComponent_destroyRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->destroy(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiImageComponentService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiImageComponentService::Service, ::octaneapi::ApiImageComponent_updateToRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiImageComponentService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiImageComponent_updateToRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->updateTo(ctx, req, resp);
             }, this)));
}

ApiImageComponentService::Service::~Service() {
}

::grpc::Status ApiImageComponentService::Service::create(::grpc::ServerContext* context, const ::octaneapi::ApiImageComponent_createRequest* request, ::octaneapi::ApiImageComponent_createResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiImageComponentService::Service::destroy(::grpc::ServerContext* context, const ::octaneapi::ApiImageComponent_destroyRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiImageComponentService::Service::updateTo(::grpc::ServerContext* context, const ::octaneapi::ApiImageComponent_updateToRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace octaneapi

