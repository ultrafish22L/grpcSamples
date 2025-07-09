#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "camera_sync_base.h"

#include <grpcpp/grpcpp.h>
#include "generated/livelink.grpc.pb.h"
#include "generated/livelink.pb.h"

class CameraSyncLiveLink : public CameraSyncBase {
public:
    CameraSyncLiveLink();
    ~CameraSyncLiveLink();

    // Connection management
    bool connectToServer(const std::string& serverAddress) override;
    void disconnect() override;
    bool isConnected() const override;

    // Camera operations
    bool setCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, float fov = 0.0f) override;
    bool setCameraPosition(const glm::vec3& position) override;
    bool setCameraTarget(const glm::vec3& target) override;
    bool setCameraUp(const glm::vec3& up) override;
    bool setCameraFov(float fov) override;
    
    // Get camera state
    bool getCamera(glm::vec3& position, glm::vec3& target, glm::vec3& up, float& fov) override;

    // Mesh operations
    struct MeshInfo {
        std::string name;
        int32_t id;
        int64_t objectHandle;
    };

    struct MeshData {
        std::string name;
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<uint32_t> vertsPerPoly;
        std::vector<uint32_t> polyVertIndices;
        std::vector<uint32_t> polyNormalIndices;
        int32_t windingOrder;
        glm::mat4 worldMatrix;
    };

    bool getMeshList(std::vector<MeshInfo>& meshes);
    bool getMeshData(int32_t objectHandle, MeshData& meshData);

private:
    std::shared_ptr<grpc::Channel> m_channel;
    std::unique_ptr<livelinkapi::LiveLinkService::Stub> m_stub;
    
    // Helper functions for conversion
    void glmToVec3(const glm::vec3& glmVec, livelinkapi::Vec3* protoVec);
    glm::vec3 vec3ToGlm(const livelinkapi::Vec3& protoVec);
    void glmToMatrixD(const glm::mat4& glmMat, livelinkapi::MatrixD* protoMat);
    glm::mat4 matrixDToGlm(const livelinkapi::MatrixD& protoMat);
    
    // Error handling
    void logGrpcStatus(const std::string& operation, bool success);
    
    bool m_connected;
    
    // Cached values for when gRPC is disabled
    glm::vec3 m_cachedPosition;
    glm::vec3 m_cachedTarget;
    glm::vec3 m_cachedUp;
    float m_cachedFov;
};