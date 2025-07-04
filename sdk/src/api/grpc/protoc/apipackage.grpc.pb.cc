// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: apipackage.proto

#include "apipackage.pb.h"
#include "apipackage.grpc.pb.h"

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

static const char* ApiPackageService_method_names[] = {
  "/octaneapi.ApiPackageService/freeArray",
  "/octaneapi.ApiPackageService/open",
  "/octaneapi.ApiPackageService/close",
  "/octaneapi.ApiPackageService/getFileList",
  "/octaneapi.ApiPackageService/fileExists",
  "/octaneapi.ApiPackageService/fileExists1",
  "/octaneapi.ApiPackageService/readFile",
  "/octaneapi.ApiPackageService/readFile1",
};

std::unique_ptr< ApiPackageService::Stub> ApiPackageService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ApiPackageService::Stub> stub(new ApiPackageService::Stub(channel, options));
  return stub;
}

ApiPackageService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_freeArray_(ApiPackageService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_open_(ApiPackageService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_close_(ApiPackageService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_getFileList_(ApiPackageService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_fileExists_(ApiPackageService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_fileExists1_(ApiPackageService_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_readFile_(ApiPackageService_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_readFile1_(ApiPackageService_method_names[7], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ApiPackageService::Stub::freeArray(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_freeArrayRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiPackage_freeArrayRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_freeArray_, context, request, response);
}

void ApiPackageService::Stub::async::freeArray(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_freeArrayRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiPackage_freeArrayRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_freeArray_, context, request, response, std::move(f));
}

void ApiPackageService::Stub::async::freeArray(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_freeArrayRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_freeArray_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiPackageService::Stub::PrepareAsyncfreeArrayRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_freeArrayRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiPackage_freeArrayRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_freeArray_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiPackageService::Stub::AsyncfreeArrayRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_freeArrayRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncfreeArrayRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiPackageService::Stub::open(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_openRequest& request, ::octaneapi::ApiPackage_openResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiPackage_openRequest, ::octaneapi::ApiPackage_openResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_open_, context, request, response);
}

void ApiPackageService::Stub::async::open(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_openRequest* request, ::octaneapi::ApiPackage_openResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiPackage_openRequest, ::octaneapi::ApiPackage_openResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_open_, context, request, response, std::move(f));
}

void ApiPackageService::Stub::async::open(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_openRequest* request, ::octaneapi::ApiPackage_openResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_open_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_openResponse>* ApiPackageService::Stub::PrepareAsyncopenRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_openRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiPackage_openResponse, ::octaneapi::ApiPackage_openRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_open_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_openResponse>* ApiPackageService::Stub::AsyncopenRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_openRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncopenRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiPackageService::Stub::close(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_closeRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiPackage_closeRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_close_, context, request, response);
}

void ApiPackageService::Stub::async::close(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_closeRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiPackage_closeRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_close_, context, request, response, std::move(f));
}

void ApiPackageService::Stub::async::close(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_closeRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_close_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiPackageService::Stub::PrepareAsynccloseRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_closeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::octaneapi::ApiPackage_closeRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_close_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* ApiPackageService::Stub::AsynccloseRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_closeRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccloseRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiPackageService::Stub::getFileList(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_getFileListRequest& request, ::octaneapi::ApiPackage_getFileListResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiPackage_getFileListRequest, ::octaneapi::ApiPackage_getFileListResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_getFileList_, context, request, response);
}

void ApiPackageService::Stub::async::getFileList(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_getFileListRequest* request, ::octaneapi::ApiPackage_getFileListResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiPackage_getFileListRequest, ::octaneapi::ApiPackage_getFileListResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_getFileList_, context, request, response, std::move(f));
}

void ApiPackageService::Stub::async::getFileList(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_getFileListRequest* request, ::octaneapi::ApiPackage_getFileListResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_getFileList_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_getFileListResponse>* ApiPackageService::Stub::PrepareAsyncgetFileListRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_getFileListRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiPackage_getFileListResponse, ::octaneapi::ApiPackage_getFileListRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_getFileList_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_getFileListResponse>* ApiPackageService::Stub::AsyncgetFileListRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_getFileListRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncgetFileListRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiPackageService::Stub::fileExists(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExistsRequest& request, ::octaneapi::ApiPackage_fileExistsResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiPackage_fileExistsRequest, ::octaneapi::ApiPackage_fileExistsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_fileExists_, context, request, response);
}

void ApiPackageService::Stub::async::fileExists(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExistsRequest* request, ::octaneapi::ApiPackage_fileExistsResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiPackage_fileExistsRequest, ::octaneapi::ApiPackage_fileExistsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_fileExists_, context, request, response, std::move(f));
}

void ApiPackageService::Stub::async::fileExists(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExistsRequest* request, ::octaneapi::ApiPackage_fileExistsResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_fileExists_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_fileExistsResponse>* ApiPackageService::Stub::PrepareAsyncfileExistsRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExistsRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiPackage_fileExistsResponse, ::octaneapi::ApiPackage_fileExistsRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_fileExists_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_fileExistsResponse>* ApiPackageService::Stub::AsyncfileExistsRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExistsRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncfileExistsRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiPackageService::Stub::fileExists1(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExists1Request& request, ::octaneapi::ApiPackage_fileExists1Response* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiPackage_fileExists1Request, ::octaneapi::ApiPackage_fileExists1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_fileExists1_, context, request, response);
}

void ApiPackageService::Stub::async::fileExists1(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExists1Request* request, ::octaneapi::ApiPackage_fileExists1Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiPackage_fileExists1Request, ::octaneapi::ApiPackage_fileExists1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_fileExists1_, context, request, response, std::move(f));
}

void ApiPackageService::Stub::async::fileExists1(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExists1Request* request, ::octaneapi::ApiPackage_fileExists1Response* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_fileExists1_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_fileExists1Response>* ApiPackageService::Stub::PrepareAsyncfileExists1Raw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExists1Request& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiPackage_fileExists1Response, ::octaneapi::ApiPackage_fileExists1Request, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_fileExists1_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_fileExists1Response>* ApiPackageService::Stub::AsyncfileExists1Raw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_fileExists1Request& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncfileExists1Raw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiPackageService::Stub::readFile(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFileRequest& request, ::octaneapi::ApiPackage_readFileResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiPackage_readFileRequest, ::octaneapi::ApiPackage_readFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_readFile_, context, request, response);
}

void ApiPackageService::Stub::async::readFile(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFileRequest* request, ::octaneapi::ApiPackage_readFileResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiPackage_readFileRequest, ::octaneapi::ApiPackage_readFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_readFile_, context, request, response, std::move(f));
}

void ApiPackageService::Stub::async::readFile(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFileRequest* request, ::octaneapi::ApiPackage_readFileResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_readFile_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_readFileResponse>* ApiPackageService::Stub::PrepareAsyncreadFileRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiPackage_readFileResponse, ::octaneapi::ApiPackage_readFileRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_readFile_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_readFileResponse>* ApiPackageService::Stub::AsyncreadFileRaw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFileRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncreadFileRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ApiPackageService::Stub::readFile1(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFile1Request& request, ::octaneapi::ApiPackage_readFile1Response* response) {
  return ::grpc::internal::BlockingUnaryCall< ::octaneapi::ApiPackage_readFile1Request, ::octaneapi::ApiPackage_readFile1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_readFile1_, context, request, response);
}

void ApiPackageService::Stub::async::readFile1(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFile1Request* request, ::octaneapi::ApiPackage_readFile1Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::octaneapi::ApiPackage_readFile1Request, ::octaneapi::ApiPackage_readFile1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_readFile1_, context, request, response, std::move(f));
}

void ApiPackageService::Stub::async::readFile1(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFile1Request* request, ::octaneapi::ApiPackage_readFile1Response* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_readFile1_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_readFile1Response>* ApiPackageService::Stub::PrepareAsyncreadFile1Raw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFile1Request& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::octaneapi::ApiPackage_readFile1Response, ::octaneapi::ApiPackage_readFile1Request, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_readFile1_, context, request);
}

::grpc::ClientAsyncResponseReader< ::octaneapi::ApiPackage_readFile1Response>* ApiPackageService::Stub::AsyncreadFile1Raw(::grpc::ClientContext* context, const ::octaneapi::ApiPackage_readFile1Request& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncreadFile1Raw(context, request, cq);
  result->StartCall();
  return result;
}

ApiPackageService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiPackageService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiPackageService::Service, ::octaneapi::ApiPackage_freeArrayRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiPackageService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiPackage_freeArrayRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->freeArray(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiPackageService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiPackageService::Service, ::octaneapi::ApiPackage_openRequest, ::octaneapi::ApiPackage_openResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiPackageService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiPackage_openRequest* req,
             ::octaneapi::ApiPackage_openResponse* resp) {
               return service->open(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiPackageService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiPackageService::Service, ::octaneapi::ApiPackage_closeRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiPackageService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiPackage_closeRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->close(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiPackageService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiPackageService::Service, ::octaneapi::ApiPackage_getFileListRequest, ::octaneapi::ApiPackage_getFileListResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiPackageService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiPackage_getFileListRequest* req,
             ::octaneapi::ApiPackage_getFileListResponse* resp) {
               return service->getFileList(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiPackageService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiPackageService::Service, ::octaneapi::ApiPackage_fileExistsRequest, ::octaneapi::ApiPackage_fileExistsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiPackageService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiPackage_fileExistsRequest* req,
             ::octaneapi::ApiPackage_fileExistsResponse* resp) {
               return service->fileExists(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiPackageService_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiPackageService::Service, ::octaneapi::ApiPackage_fileExists1Request, ::octaneapi::ApiPackage_fileExists1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiPackageService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiPackage_fileExists1Request* req,
             ::octaneapi::ApiPackage_fileExists1Response* resp) {
               return service->fileExists1(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiPackageService_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiPackageService::Service, ::octaneapi::ApiPackage_readFileRequest, ::octaneapi::ApiPackage_readFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiPackageService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiPackage_readFileRequest* req,
             ::octaneapi::ApiPackage_readFileResponse* resp) {
               return service->readFile(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ApiPackageService_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ApiPackageService::Service, ::octaneapi::ApiPackage_readFile1Request, ::octaneapi::ApiPackage_readFile1Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ApiPackageService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::octaneapi::ApiPackage_readFile1Request* req,
             ::octaneapi::ApiPackage_readFile1Response* resp) {
               return service->readFile1(ctx, req, resp);
             }, this)));
}

ApiPackageService::Service::~Service() {
}

::grpc::Status ApiPackageService::Service::freeArray(::grpc::ServerContext* context, const ::octaneapi::ApiPackage_freeArrayRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiPackageService::Service::open(::grpc::ServerContext* context, const ::octaneapi::ApiPackage_openRequest* request, ::octaneapi::ApiPackage_openResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiPackageService::Service::close(::grpc::ServerContext* context, const ::octaneapi::ApiPackage_closeRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiPackageService::Service::getFileList(::grpc::ServerContext* context, const ::octaneapi::ApiPackage_getFileListRequest* request, ::octaneapi::ApiPackage_getFileListResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiPackageService::Service::fileExists(::grpc::ServerContext* context, const ::octaneapi::ApiPackage_fileExistsRequest* request, ::octaneapi::ApiPackage_fileExistsResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiPackageService::Service::fileExists1(::grpc::ServerContext* context, const ::octaneapi::ApiPackage_fileExists1Request* request, ::octaneapi::ApiPackage_fileExists1Response* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiPackageService::Service::readFile(::grpc::ServerContext* context, const ::octaneapi::ApiPackage_readFileRequest* request, ::octaneapi::ApiPackage_readFileResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ApiPackageService::Service::readFile1(::grpc::ServerContext* context, const ::octaneapi::ApiPackage_readFile1Request* request, ::octaneapi::ApiPackage_readFile1Response* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace octaneapi

