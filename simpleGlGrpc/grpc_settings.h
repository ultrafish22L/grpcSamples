#pragma once

#include <string>
#include <memory>

#ifdef GRPC_ENABLED
#include <grpcpp/grpcpp.h>
#endif

class GRPCSettings {
public:
    static GRPCSettings& getInstance();
    
    void setServerAddress(const std::string& address);
    std::string getServerAddress() const;
    
#ifdef GRPC_ENABLED
    std::shared_ptr<grpc::Channel> getChannel();
#endif

private:
    GRPCSettings() = default;
    std::string serverAddress = "localhost:50051";
    
#ifdef GRPC_ENABLED
    std::shared_ptr<grpc::Channel> channel;
#endif
};