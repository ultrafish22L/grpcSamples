// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: apibase64.proto

#include "apibase64.pb.h"
#include "apibase64.grpc.pb.h"

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

static const char* ApiBase64Service_method_names[] = {
  "/octaneapi.ApiBase64Service/encode",
  "/octaneapi.ApiBase64Service/decode",
};

std::unique_ptr< ApiBase64Service::Stub> ApiBase64Service::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ApiBase64Service::Stub> stub(new ApiBase64Service::Stub(channel, options));
  return stub;
}

ApiBase64Service::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_encode_(ApiBase64Service_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_decode_(ApiBase64Service_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ApiBase64Service::Stub::encode(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_encodeRequest& request, ::octaneapi::ApiBase64_encodeResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiBase64_encodeRequest, ::octaneapi::ApiBase64_encodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_encode_, context, request, response);
}

void ApiBase64Service::Stub::async::encode(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_encodeRequest* request, ::octaneapi::ApiBase64_encodeResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiBase64_encodeRequest, ::octaneapi::ApiBase64_encodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_encode_, context, request, response, std::move(f));
}

void ApiBase64Service::Stub::async::encode(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_encodeRequest* request, ::octaneapi::ApiBase64_encodeResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_encode_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiBase64_encodeResponse>* ApiBase64Service::Stub::PrepareAsyncencodeRaw(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_encodeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiBase64_encodeResponse, ::octaneapi::ApiBase64_encodeRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_encode_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiBase64_encodeResponse>* ApiBase64Service::Stub::AsyncencodeRaw(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_encodeRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncencodeRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiBase64Service::Stub::decode(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_decodeRequest& request, ::octaneapi::ApiBase64_decodeResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiBase64_decodeRequest, ::octaneapi::ApiBase64_decodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_decode_, context, request, response);
}

void ApiBase64Service::Stub::async::decode(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_decodeRequest* request, ::octaneapi::ApiBase64_decodeResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiBase64_decodeRequest, ::octaneapi::ApiBase64_decodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_decode_, context, request, response, std::move(f));
}

void ApiBase64Service::Stub::async::decode(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_decodeRequest* request, ::octaneapi::ApiBase64_decodeResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_decode_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiBase64_decodeResponse>* ApiBase64Service::Stub::PrepareAsyncdecodeRaw(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_decodeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiBase64_decodeResponse, ::octaneapi::ApiBase64_decodeRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_decode_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiBase64_decodeResponse>* ApiBase64Service::Stub::AsyncdecodeRaw(::grpc::ClientContext* context, const ::octaneapi::ApiBase64_decodeRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdecodeRaw(context, request, cq);
  result->StartCall();
  return result;
}

ApiBase64Service::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiBase64Service_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiBase64Service::Service, ::octaneapi::ApiBase64_encodeRequest, ::octaneapi::ApiBase64_encodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiBase64Service::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiBase64_encodeRequest* req,
             ::octaneapi::ApiBase64_encodeResponse* resp) {
               return service->encode(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiBase64Service_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiBase64Service::Service, ::octaneapi::ApiBase64_decodeRequest, ::octaneapi::ApiBase64_decodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiBase64Service::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiBase64_decodeRequest* req,
             ::octaneapi::ApiBase64_decodeResponse* resp) {
               return service->decode(ctx, req, resp);
             }, this)));
}

ApiBase64Service::Service::~Service() {
}

::grpc::Status ApiBase64Service::Service::encode(::grpc::ServerContext* context, const ::octaneapi::ApiBase64_encodeRequest* request, ::octaneapi::ApiBase64_encodeResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiBase64Service::Service::decode(::grpc::ServerContext* context, const ::octaneapi::ApiBase64_decodeRequest* request, ::octaneapi::ApiBase64_decodeResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace octaneapi

