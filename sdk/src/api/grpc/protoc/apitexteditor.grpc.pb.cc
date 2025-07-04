// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: apitexteditor.proto

#include "apitexteditor.pb.h"
#include "apitexteditor.grpc.pb.h"

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

static const char* ApiTextEditorService_method_names[] = {
  "/octaneapi.ApiTextEditorService/create",
  "/octaneapi.ApiTextEditorService/destroy",
  "/octaneapi.ApiTextEditorService/text",
  "/octaneapi.ApiTextEditorService/isEmpty",
  "/octaneapi.ApiTextEditorService/setText",
  "/octaneapi.ApiTextEditorService/clear",
  "/octaneapi.ApiTextEditorService/setReadOnly",
  "/octaneapi.ApiTextEditorService/isReadOnly",
};

std::unique_ptr< ApiTextEditorService::Stub> ApiTextEditorService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ApiTextEditorService::Stub> stub(new ApiTextEditorService::Stub(channel, options));
  return stub;
}

ApiTextEditorService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_create_(ApiTextEditorService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_destroy_(ApiTextEditorService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_text_(ApiTextEditorService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_isEmpty_(ApiTextEditorService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_setText_(ApiTextEditorService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_clear_(ApiTextEditorService_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_setReadOnly_(ApiTextEditorService_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_isReadOnly_(ApiTextEditorService_method_names[7], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ApiTextEditorService::Stub::create(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_createRequest& request, ::octaneapi::ApiTextEditor_createResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiTextEditor_createRequest, ::octaneapi::ApiTextEditor_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_create_, context, request, response);
}

void ApiTextEditorService::Stub::async::create(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_createRequest* request, ::octaneapi::ApiTextEditor_createResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiTextEditor_createRequest, ::octaneapi::ApiTextEditor_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_create_, context, request, response, std::move(f));
}

void ApiTextEditorService::Stub::async::create(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_createRequest* request, ::octaneapi::ApiTextEditor_createResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_create_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiTextEditor_createResponse>* ApiTextEditorService::Stub::PrepareAsynccreateRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_createRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiTextEditor_createResponse, ::octaneapi::ApiTextEditor_createRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_create_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiTextEditor_createResponse>* ApiTextEditorService::Stub::AsynccreateRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_createRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccreateRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiTextEditorService::Stub::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_destroyRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiTextEditor_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_destroy_, context, request, response);
}

void ApiTextEditorService::Stub::async::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_destroyRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiTextEditor_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_destroy_, context, request, response, std::move(f));
}

void ApiTextEditorService::Stub::async::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_destroyRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_destroy_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiTextEditorService::Stub::PrepareAsyncdestroyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_destroyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiTextEditor_destroyRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_destroy_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiTextEditorService::Stub::AsyncdestroyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_destroyRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdestroyRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiTextEditorService::Stub::text(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_textRequest& request, ::octaneapi::ApiTextEditor_textResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiTextEditor_textRequest, ::octaneapi::ApiTextEditor_textResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_text_, context, request, response);
}

void ApiTextEditorService::Stub::async::text(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_textRequest* request, ::octaneapi::ApiTextEditor_textResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiTextEditor_textRequest, ::octaneapi::ApiTextEditor_textResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_text_, context, request, response, std::move(f));
}

void ApiTextEditorService::Stub::async::text(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_textRequest* request, ::octaneapi::ApiTextEditor_textResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_text_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiTextEditor_textResponse>* ApiTextEditorService::Stub::PrepareAsynctextRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_textRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiTextEditor_textResponse, ::octaneapi::ApiTextEditor_textRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_text_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiTextEditor_textResponse>* ApiTextEditorService::Stub::AsynctextRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_textRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynctextRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiTextEditorService::Stub::isEmpty(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isEmptyRequest& request, ::octaneapi::ApiTextEditor_isEmptyResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiTextEditor_isEmptyRequest, ::octaneapi::ApiTextEditor_isEmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_isEmpty_, context, request, response);
}

void ApiTextEditorService::Stub::async::isEmpty(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isEmptyRequest* request, ::octaneapi::ApiTextEditor_isEmptyResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiTextEditor_isEmptyRequest, ::octaneapi::ApiTextEditor_isEmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_isEmpty_, context, request, response, std::move(f));
}

void ApiTextEditorService::Stub::async::isEmpty(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isEmptyRequest* request, ::octaneapi::ApiTextEditor_isEmptyResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_isEmpty_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiTextEditor_isEmptyResponse>* ApiTextEditorService::Stub::PrepareAsyncisEmptyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isEmptyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiTextEditor_isEmptyResponse, ::octaneapi::ApiTextEditor_isEmptyRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_isEmpty_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiTextEditor_isEmptyResponse>* ApiTextEditorService::Stub::AsyncisEmptyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isEmptyRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncisEmptyRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiTextEditorService::Stub::setText(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setTextRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiTextEditor_setTextRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_setText_, context, request, response);
}

void ApiTextEditorService::Stub::async::setText(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setTextRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiTextEditor_setTextRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_setText_, context, request, response, std::move(f));
}

void ApiTextEditorService::Stub::async::setText(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setTextRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_setText_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiTextEditorService::Stub::PrepareAsyncsetTextRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setTextRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiTextEditor_setTextRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_setText_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiTextEditorService::Stub::AsyncsetTextRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setTextRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncsetTextRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiTextEditorService::Stub::clear(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_clearRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiTextEditor_clearRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_clear_, context, request, response);
}

void ApiTextEditorService::Stub::async::clear(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_clearRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiTextEditor_clearRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_clear_, context, request, response, std::move(f));
}

void ApiTextEditorService::Stub::async::clear(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_clearRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_clear_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiTextEditorService::Stub::PrepareAsyncclearRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_clearRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiTextEditor_clearRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_clear_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiTextEditorService::Stub::AsyncclearRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_clearRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncclearRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiTextEditorService::Stub::setReadOnly(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setReadOnlyRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiTextEditor_setReadOnlyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_setReadOnly_, context, request, response);
}

void ApiTextEditorService::Stub::async::setReadOnly(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setReadOnlyRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiTextEditor_setReadOnlyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_setReadOnly_, context, request, response, std::move(f));
}

void ApiTextEditorService::Stub::async::setReadOnly(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setReadOnlyRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_setReadOnly_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiTextEditorService::Stub::PrepareAsyncsetReadOnlyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setReadOnlyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiTextEditor_setReadOnlyRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_setReadOnly_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiTextEditorService::Stub::AsyncsetReadOnlyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_setReadOnlyRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncsetReadOnlyRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiTextEditorService::Stub::isReadOnly(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isReadOnlyRequest& request, ::octaneapi::ApiTextEditor_isReadOnlyResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiTextEditor_isReadOnlyRequest, ::octaneapi::ApiTextEditor_isReadOnlyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_isReadOnly_, context, request, response);
}

void ApiTextEditorService::Stub::async::isReadOnly(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isReadOnlyRequest* request, ::octaneapi::ApiTextEditor_isReadOnlyResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiTextEditor_isReadOnlyRequest, ::octaneapi::ApiTextEditor_isReadOnlyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_isReadOnly_, context, request, response, std::move(f));
}

void ApiTextEditorService::Stub::async::isReadOnly(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isReadOnlyRequest* request, ::octaneapi::ApiTextEditor_isReadOnlyResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_isReadOnly_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiTextEditor_isReadOnlyResponse>* ApiTextEditorService::Stub::PrepareAsyncisReadOnlyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isReadOnlyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiTextEditor_isReadOnlyResponse, ::octaneapi::ApiTextEditor_isReadOnlyRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_isReadOnly_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiTextEditor_isReadOnlyResponse>* ApiTextEditorService::Stub::AsyncisReadOnlyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiTextEditor_isReadOnlyRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncisReadOnlyRaw(context, request, cq);
  result->StartCall();
  return result;
}

ApiTextEditorService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiTextEditorService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiTextEditorService::Service, ::octaneapi::ApiTextEditor_createRequest, ::octaneapi::ApiTextEditor_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiTextEditorService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiTextEditor_createRequest* req,
             ::octaneapi::ApiTextEditor_createResponse* resp) {
               return service->create(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiTextEditorService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiTextEditorService::Service, ::octaneapi::ApiTextEditor_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiTextEditorService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiTextEditor_destroyRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->destroy(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiTextEditorService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiTextEditorService::Service, ::octaneapi::ApiTextEditor_textRequest, ::octaneapi::ApiTextEditor_textResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiTextEditorService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiTextEditor_textRequest* req,
             ::octaneapi::ApiTextEditor_textResponse* resp) {
               return service->text(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiTextEditorService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiTextEditorService::Service, ::octaneapi::ApiTextEditor_isEmptyRequest, ::octaneapi::ApiTextEditor_isEmptyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiTextEditorService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiTextEditor_isEmptyRequest* req,
             ::octaneapi::ApiTextEditor_isEmptyResponse* resp) {
               return service->isEmpty(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiTextEditorService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiTextEditorService::Service, ::octaneapi::ApiTextEditor_setTextRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiTextEditorService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiTextEditor_setTextRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->setText(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiTextEditorService_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiTextEditorService::Service, ::octaneapi::ApiTextEditor_clearRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiTextEditorService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiTextEditor_clearRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->clear(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiTextEditorService_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiTextEditorService::Service, ::octaneapi::ApiTextEditor_setReadOnlyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiTextEditorService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiTextEditor_setReadOnlyRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->setReadOnly(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiTextEditorService_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiTextEditorService::Service, ::octaneapi::ApiTextEditor_isReadOnlyRequest, ::octaneapi::ApiTextEditor_isReadOnlyResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiTextEditorService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiTextEditor_isReadOnlyRequest* req,
             ::octaneapi::ApiTextEditor_isReadOnlyResponse* resp) {
               return service->isReadOnly(ctx, req, resp);
             }, this)));
}

ApiTextEditorService::Service::~Service() {
}

::grpc::Status ApiTextEditorService::Service::create(::grpc::ServerContext* context, const ::octaneapi::ApiTextEditor_createRequest* request, ::octaneapi::ApiTextEditor_createResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiTextEditorService::Service::destroy(::grpc::ServerContext* context, const ::octaneapi::ApiTextEditor_destroyRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiTextEditorService::Service::text(::grpc::ServerContext* context, const ::octaneapi::ApiTextEditor_textRequest* request, ::octaneapi::ApiTextEditor_textResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiTextEditorService::Service::isEmpty(::grpc::ServerContext* context, const ::octaneapi::ApiTextEditor_isEmptyRequest* request, ::octaneapi::ApiTextEditor_isEmptyResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiTextEditorService::Service::setText(::grpc::ServerContext* context, const ::octaneapi::ApiTextEditor_setTextRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiTextEditorService::Service::clear(::grpc::ServerContext* context, const ::octaneapi::ApiTextEditor_clearRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiTextEditorService::Service::setReadOnly(::grpc::ServerContext* context, const ::octaneapi::ApiTextEditor_setReadOnlyRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiTextEditorService::Service::isReadOnly(::grpc::ServerContext* context, const ::octaneapi::ApiTextEditor_isReadOnlyRequest* request, ::octaneapi::ApiTextEditor_isReadOnlyResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace octaneapi

