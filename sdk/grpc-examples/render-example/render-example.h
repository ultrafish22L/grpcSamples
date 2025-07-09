// Copyright (C) 2025 OTOY NZ Ltd.

#include <iostream>
#include <memory>
#include <thread>
#include <grpcpp/grpcpp.h>
#include "callback.grpc.pb.h"  // Generated stub

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReaderWriter;
using grpc::Status;

using namespace octaneapi;
class GRPCAPIEvents
{
public:
    GRPCAPIEvents(std::shared_ptr<grpc::Channel> channel)
        : mStub(StreamCallbackService::NewStub(channel)) {}

    void initConnection();

    void waitForEvents();

    void shutdown();

private:
    std::unique_ptr<StreamCallbackService::Stub> mStub;
    std::unique_ptr<grpc::ClientContext> mContext;
    std::unique_ptr<grpc::ClientReader<StreamCallbackRequest>> mStream;
    std::thread mReaderThread;
    std::atomic<bool> mShutdownRequested = false;
    void HandleCallback(
        const StreamCallbackRequest & request);
};