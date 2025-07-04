// Generated stub gRPC header
#pragma once
#include <grpcpp/grpcpp.h>
#include "camera_control.pb.h"

namespace camera_control {

class CameraControlService final {
public:
    class StubInterface {
    public:
        virtual ~StubInterface() {}
    };
    
    class Stub : public StubInterface {
    public:
        Stub(std::shared_ptr<grpc::ChannelInterface> channel) {}
    };
    
    static std::unique_ptr<Stub> NewStub(std::shared_ptr<grpc::ChannelInterface> channel) {
        return std::make_unique<Stub>(channel);
    }
};

} // namespace camera_control
