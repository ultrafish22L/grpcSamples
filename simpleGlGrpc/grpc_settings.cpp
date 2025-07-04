#include "grpc_settings.h"

GRPCSettings& GRPCSettings::getInstance() {
    static GRPCSettings instance;
    return instance;
}

void GRPCSettings::setServerAddress(const std::string& address) {
    serverAddress = address;
#ifdef GRPC_ENABLED
    // Reset channel when address changes
    channel.reset();
#endif
}

std::string GRPCSettings::getServerAddress() const {
    return serverAddress;
}

#ifdef GRPC_ENABLED
std::shared_ptr<grpc::Channel> GRPCSettings::getChannel() {
    if (!channel) {
        channel = grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials());
    }
    return channel;
}
#endif