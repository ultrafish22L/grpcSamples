// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: apigeometryexporter.proto

#include "apigeometryexporter.pb.h"
#include "apigeometryexporter.grpc.pb.h"

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

static const char* ApiGeometryExporterService_method_names[] = {
  "/octaneapi.ApiGeometryExporterService/isSupported",
  "/octaneapi.ApiGeometryExporterService/create",
  "/octaneapi.ApiGeometryExporterService/setAspectRatio",
  "/octaneapi.ApiGeometryExporterService/setFbxOptions",
  "/octaneapi.ApiGeometryExporterService/addItem",
  "/octaneapi.ApiGeometryExporterService/writeFrame",
  "/octaneapi.ApiGeometryExporterService/writeFrame1",
  "/octaneapi.ApiGeometryExporterService/writeTimeSampling",
  "/octaneapi.ApiGeometryExporterService/createGeometryArchive",
  "/octaneapi.ApiGeometryExporterService/destroy",
};

std::unique_ptr< ApiGeometryExporterService::Stub> ApiGeometryExporterService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ApiGeometryExporterService::Stub> stub(new ApiGeometryExporterService::Stub(channel, options));
  return stub;
}

ApiGeometryExporterService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_isSupported_(ApiGeometryExporterService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_create_(ApiGeometryExporterService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_setAspectRatio_(ApiGeometryExporterService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_setFbxOptions_(ApiGeometryExporterService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_addItem_(ApiGeometryExporterService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_writeFrame_(ApiGeometryExporterService_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_writeFrame1_(ApiGeometryExporterService_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_writeTimeSampling_(ApiGeometryExporterService_method_names[7], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_createGeometryArchive_(ApiGeometryExporterService_method_names[8], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_destroy_(ApiGeometryExporterService_method_names[9], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ApiGeometryExporterService::Stub::isSupported(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_isSupportedRequest& request, ::octaneapi::ApiGeometryExporter_isSupportedResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_isSupportedRequest, ::octaneapi::ApiGeometryExporter_isSupportedResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_isSupported_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::isSupported(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_isSupportedRequest* request, ::octaneapi::ApiGeometryExporter_isSupportedResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_isSupportedRequest, ::octaneapi::ApiGeometryExporter_isSupportedResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_isSupported_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::isSupported(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_isSupportedRequest* request, ::octaneapi::ApiGeometryExporter_isSupportedResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_isSupported_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_isSupportedResponse>* ApiGeometryExporterService::Stub::PrepareAsyncisSupportedRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_isSupportedRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiGeometryExporter_isSupportedResponse, ::octaneapi::ApiGeometryExporter_isSupportedRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_isSupported_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_isSupportedResponse>* ApiGeometryExporterService::Stub::AsyncisSupportedRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_isSupportedRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncisSupportedRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::create(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createRequest& request, ::octaneapi::ApiGeometryExporter_createResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_createRequest, ::octaneapi::ApiGeometryExporter_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_create_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::create(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createRequest* request, ::octaneapi::ApiGeometryExporter_createResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_createRequest, ::octaneapi::ApiGeometryExporter_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_create_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::create(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createRequest* request, ::octaneapi::ApiGeometryExporter_createResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_create_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_createResponse>* ApiGeometryExporterService::Stub::PrepareAsynccreateRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiGeometryExporter_createResponse, ::octaneapi::ApiGeometryExporter_createRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_create_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_createResponse>* ApiGeometryExporterService::Stub::AsynccreateRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccreateRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::setAspectRatio(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setAspectRatioRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_setAspectRatioRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_setAspectRatio_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::setAspectRatio(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setAspectRatioRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_setAspectRatioRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_setAspectRatio_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::setAspectRatio(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setAspectRatioRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_setAspectRatio_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiGeometryExporterService::Stub::PrepareAsyncsetAspectRatioRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setAspectRatioRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiGeometryExporter_setAspectRatioRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_setAspectRatio_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiGeometryExporterService::Stub::AsyncsetAspectRatioRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setAspectRatioRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncsetAspectRatioRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::setFbxOptions(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_setFbxOptions_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::setFbxOptions(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_setFbxOptions_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::setFbxOptions(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_setFbxOptions_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiGeometryExporterService::Stub::PrepareAsyncsetFbxOptionsRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_setFbxOptions_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiGeometryExporterService::Stub::AsyncsetFbxOptionsRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncsetFbxOptionsRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::addItem(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_addItemRequest& request, ::octaneapi::ApiGeometryExporter_addItemResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_addItemRequest, ::octaneapi::ApiGeometryExporter_addItemResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_addItem_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::addItem(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_addItemRequest* request, ::octaneapi::ApiGeometryExporter_addItemResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_addItemRequest, ::octaneapi::ApiGeometryExporter_addItemResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_addItem_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::addItem(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_addItemRequest* request, ::octaneapi::ApiGeometryExporter_addItemResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_addItem_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_addItemResponse>* ApiGeometryExporterService::Stub::PrepareAsyncaddItemRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_addItemRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiGeometryExporter_addItemResponse, ::octaneapi::ApiGeometryExporter_addItemRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_addItem_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_addItemResponse>* ApiGeometryExporterService::Stub::AsyncaddItemRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_addItemRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncaddItemRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::writeFrame(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrameRequest& request, ::octaneapi::ApiGeometryExporter_writeFrameResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_writeFrameRequest, ::octaneapi::ApiGeometryExporter_writeFrameResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_writeFrame_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::writeFrame(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrameRequest* request, ::octaneapi::ApiGeometryExporter_writeFrameResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_writeFrameRequest, ::octaneapi::ApiGeometryExporter_writeFrameResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_writeFrame_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::writeFrame(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrameRequest* request, ::octaneapi::ApiGeometryExporter_writeFrameResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_writeFrame_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_writeFrameResponse>* ApiGeometryExporterService::Stub::PrepareAsyncwriteFrameRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiGeometryExporter_writeFrameResponse, ::octaneapi::ApiGeometryExporter_writeFrameRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_writeFrame_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_writeFrameResponse>* ApiGeometryExporterService::Stub::AsyncwriteFrameRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrameRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncwriteFrameRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::writeFrame1(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrame1Request& request, ::octaneapi::ApiGeometryExporter_writeFrame1Response* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_writeFrame1Request, ::octaneapi::ApiGeometryExporter_writeFrame1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_writeFrame1_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::writeFrame1(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrame1Request* request, ::octaneapi::ApiGeometryExporter_writeFrame1Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_writeFrame1Request, ::octaneapi::ApiGeometryExporter_writeFrame1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_writeFrame1_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::writeFrame1(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrame1Request* request, ::octaneapi::ApiGeometryExporter_writeFrame1Response* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_writeFrame1_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_writeFrame1Response>* ApiGeometryExporterService::Stub::PrepareAsyncwriteFrame1Raw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrame1Request& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiGeometryExporter_writeFrame1Response, ::octaneapi::ApiGeometryExporter_writeFrame1Request, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_writeFrame1_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_writeFrame1Response>* ApiGeometryExporterService::Stub::AsyncwriteFrame1Raw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeFrame1Request& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncwriteFrame1Raw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::writeTimeSampling(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest& request, ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest, ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_writeTimeSampling_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::writeTimeSampling(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest* request, ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest, ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_writeTimeSampling_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::writeTimeSampling(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest* request, ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_writeTimeSampling_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse>* ApiGeometryExporterService::Stub::PrepareAsyncwriteTimeSamplingRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse, ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_writeTimeSampling_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse>* ApiGeometryExporterService::Stub::AsyncwriteTimeSamplingRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncwriteTimeSamplingRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::createGeometryArchive(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest& request, ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest, ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_createGeometryArchive_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::createGeometryArchive(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest* request, ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest, ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_createGeometryArchive_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::createGeometryArchive(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest* request, ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_createGeometryArchive_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse>* ApiGeometryExporterService::Stub::PrepareAsynccreateGeometryArchiveRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse, ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_createGeometryArchive_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse>* ApiGeometryExporterService::Stub::AsynccreateGeometryArchiveRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccreateGeometryArchiveRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiGeometryExporterService::Stub::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_destroyRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiGeometryExporter_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_destroy_, context, request, response);
}

void ApiGeometryExporterService::Stub::async::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_destroyRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiGeometryExporter_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_destroy_, context, request, response, std::move(f));
}

void ApiGeometryExporterService::Stub::async::destroy(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_destroyRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_destroy_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiGeometryExporterService::Stub::PrepareAsyncdestroyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_destroyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiGeometryExporter_destroyRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_destroy_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiGeometryExporterService::Stub::AsyncdestroyRaw(::grpc::ClientContext* context, const ::octaneapi::ApiGeometryExporter_destroyRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdestroyRaw(context, request, cq);
  result->StartCall();
  return result;
}

ApiGeometryExporterService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_isSupportedRequest, ::octaneapi::ApiGeometryExporter_isSupportedResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_isSupportedRequest* req,
             ::octaneapi::ApiGeometryExporter_isSupportedResponse* resp) {
               return service->isSupported(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_createRequest, ::octaneapi::ApiGeometryExporter_createResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_createRequest* req,
             ::octaneapi::ApiGeometryExporter_createResponse* resp) {
               return service->create(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_setAspectRatioRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_setAspectRatioRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->setAspectRatio(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->setFbxOptions(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_addItemRequest, ::octaneapi::ApiGeometryExporter_addItemResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_addItemRequest* req,
             ::octaneapi::ApiGeometryExporter_addItemResponse* resp) {
               return service->addItem(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_writeFrameRequest, ::octaneapi::ApiGeometryExporter_writeFrameResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_writeFrameRequest* req,
             ::octaneapi::ApiGeometryExporter_writeFrameResponse* resp) {
               return service->writeFrame(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_writeFrame1Request, ::octaneapi::ApiGeometryExporter_writeFrame1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_writeFrame1Request* req,
             ::octaneapi::ApiGeometryExporter_writeFrame1Response* resp) {
               return service->writeFrame1(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest, ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest* req,
             ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse* resp) {
               return service->writeTimeSampling(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[8],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest, ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest* req,
             ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse* resp) {
               return service->createGeometryArchive(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiGeometryExporterService_method_names[9],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiGeometryExporterService::Service, ::octaneapi::ApiGeometryExporter_destroyRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiGeometryExporterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiGeometryExporter_destroyRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->destroy(ctx, req, resp);
             }, this)));
}

ApiGeometryExporterService::Service::~Service() {
}

::grpc::Status ApiGeometryExporterService::Service::isSupported(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_isSupportedRequest* request, ::octaneapi::ApiGeometryExporter_isSupportedResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::create(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_createRequest* request, ::octaneapi::ApiGeometryExporter_createResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::setAspectRatio(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_setAspectRatioRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::setFbxOptions(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_setFbxOptionsRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::addItem(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_addItemRequest* request, ::octaneapi::ApiGeometryExporter_addItemResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::writeFrame(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_writeFrameRequest* request, ::octaneapi::ApiGeometryExporter_writeFrameResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::writeFrame1(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_writeFrame1Request* request, ::octaneapi::ApiGeometryExporter_writeFrame1Response* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::writeTimeSampling(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_writeTimeSamplingRequest* request, ::octaneapi::ApiGeometryExporter_writeTimeSamplingResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::createGeometryArchive(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_createGeometryArchiveRequest* request, ::octaneapi::ApiGeometryExporter_createGeometryArchiveResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiGeometryExporterService::Service::destroy(::grpc::ServerContext* context, const ::octaneapi::ApiGeometryExporter_destroyRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace octaneapi

