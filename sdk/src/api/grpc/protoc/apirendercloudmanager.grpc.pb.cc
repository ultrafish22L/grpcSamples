// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: apirendercloudmanager.proto

#include "apirendercloudmanager.pb.h"
#include "apirendercloudmanager.grpc.pb.h"

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

static const char* ApiRenderCloudManagerService_method_names[] = {
  "/octaneapi.ApiRenderCloudManagerService/userSubscriptionInfo",
  "/octaneapi.ApiRenderCloudManagerService/uploadCurrentProject",
  "/octaneapi.ApiRenderCloudManagerService/uploadRootNodeGraph",
  "/octaneapi.ApiRenderCloudManagerService/newRenderTask",
};

std::unique_ptr< ApiRenderCloudManagerService::Stub> ApiRenderCloudManagerService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ApiRenderCloudManagerService::Stub> stub(new ApiRenderCloudManagerService::Stub(channel, options));
  return stub;
}

ApiRenderCloudManagerService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_userSubscriptionInfo_(ApiRenderCloudManagerService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_uploadCurrentProject_(ApiRenderCloudManagerService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_uploadRootNodeGraph_(ApiRenderCloudManagerService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_newRenderTask_(ApiRenderCloudManagerService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ApiRenderCloudManagerService::Stub::userSubscriptionInfo(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest& request, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_userSubscriptionInfo_, context, request, response);
}

void ApiRenderCloudManagerService::Stub::async::userSubscriptionInfo(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest* request, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_userSubscriptionInfo_, context, request, response, std::move(f));
}

void ApiRenderCloudManagerService::Stub::async::userSubscriptionInfo(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest* request, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_userSubscriptionInfo_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse>* ApiRenderCloudManagerService::Stub::PrepareAsyncuserSubscriptionInfoRaw(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_userSubscriptionInfo_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse>* ApiRenderCloudManagerService::Stub::AsyncuserSubscriptionInfoRaw(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncuserSubscriptionInfoRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiRenderCloudManagerService::Stub::uploadCurrentProject(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest& request, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_uploadCurrentProject_, context, request, response);
}

void ApiRenderCloudManagerService::Stub::async::uploadCurrentProject(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest* request, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_uploadCurrentProject_, context, request, response, std::move(f));
}

void ApiRenderCloudManagerService::Stub::async::uploadCurrentProject(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest* request, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_uploadCurrentProject_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse>* ApiRenderCloudManagerService::Stub::PrepareAsyncuploadCurrentProjectRaw(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_uploadCurrentProject_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse>* ApiRenderCloudManagerService::Stub::AsyncuploadCurrentProjectRaw(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncuploadCurrentProjectRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiRenderCloudManagerService::Stub::uploadRootNodeGraph(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest& request, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_uploadRootNodeGraph_, context, request, response);
}

void ApiRenderCloudManagerService::Stub::async::uploadRootNodeGraph(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest* request, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_uploadRootNodeGraph_, context, request, response, std::move(f));
}

void ApiRenderCloudManagerService::Stub::async::uploadRootNodeGraph(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest* request, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_uploadRootNodeGraph_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse>* ApiRenderCloudManagerService::Stub::PrepareAsyncuploadRootNodeGraphRaw(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_uploadRootNodeGraph_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse>* ApiRenderCloudManagerService::Stub::AsyncuploadRootNodeGraphRaw(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncuploadRootNodeGraphRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiRenderCloudManagerService::Stub::newRenderTask(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest& request, ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest, ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_newRenderTask_, context, request, response);
}

void ApiRenderCloudManagerService::Stub::async::newRenderTask(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest* request, ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest, ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_newRenderTask_, context, request, response, std::move(f));
}

void ApiRenderCloudManagerService::Stub::async::newRenderTask(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest* request, ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_newRenderTask_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse>* ApiRenderCloudManagerService::Stub::PrepareAsyncnewRenderTaskRaw(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse, ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_newRenderTask_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse>* ApiRenderCloudManagerService::Stub::AsyncnewRenderTaskRaw(::grpc::ClientContext* context, const ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncnewRenderTaskRaw(context, request, cq);
  result->StartCall();
  return result;
}

ApiRenderCloudManagerService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiRenderCloudManagerService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiRenderCloudManagerService::Service, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiRenderCloudManagerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest* req,
             ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse* resp) {
               return service->userSubscriptionInfo(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiRenderCloudManagerService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiRenderCloudManagerService::Service, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiRenderCloudManagerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest* req,
             ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse* resp) {
               return service->uploadCurrentProject(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiRenderCloudManagerService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiRenderCloudManagerService::Service, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiRenderCloudManagerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest* req,
             ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse* resp) {
               return service->uploadRootNodeGraph(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiRenderCloudManagerService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiRenderCloudManagerService::Service, ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest, ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiRenderCloudManagerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest* req,
             ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse* resp) {
               return service->newRenderTask(ctx, req, resp);
             }, this)));
}

ApiRenderCloudManagerService::Service::~Service() {
}

::grpc::Status ApiRenderCloudManagerService::Service::userSubscriptionInfo(::grpc::ServerContext* context, const ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoRequest* request, ::octaneapi::ApiRenderCloudManager_userSubscriptionInfoResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiRenderCloudManagerService::Service::uploadCurrentProject(::grpc::ServerContext* context, const ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectRequest* request, ::octaneapi::ApiRenderCloudManager_uploadCurrentProjectResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiRenderCloudManagerService::Service::uploadRootNodeGraph(::grpc::ServerContext* context, const ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphRequest* request, ::octaneapi::ApiRenderCloudManager_uploadRootNodeGraphResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiRenderCloudManagerService::Service::newRenderTask(::grpc::ServerContext* context, const ::octaneapi::ApiRenderCloudManager_newRenderTaskRequest* request, ::octaneapi::ApiRenderCloudManager_newRenderTaskResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace octaneapi

