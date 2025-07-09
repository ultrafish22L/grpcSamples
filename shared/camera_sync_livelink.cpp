#include "camera_sync_livelink.h"
#include <iostream>

CameraSyncLiveLink::CameraSyncLiveLink()
    : m_connected(false)
    , m_cachedPosition(0.0f, 0.0f, 5.0f)
    , m_cachedTarget(0.0f, 0.0f, 0.0f)
    , m_cachedUp(0.0f, 1.0f, 0.0f)
    , m_cachedFov(45.0f)
{
}

CameraSyncLiveLink::~CameraSyncLiveLink() {
    disconnect();
}

bool CameraSyncLiveLink::connectToServer(const std::string& serverAddress) {
    try {
        std::cout << "Connecting to LiveLink gRPC server at: " << serverAddress << std::endl;
        
        // Create gRPC channel
        m_channel = grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials());
        if (!m_channel) {
            std::cerr << "Failed to create gRPC channel" << std::endl;
            return false;
        }

        // Create LiveLink service stub
        m_stub = livelinkapi::LiveLinkService::NewStub(m_channel);
        if (!m_stub) {
            std::cerr << "Failed to create LiveLink service stub" << std::endl;
            return false;
        }

        // Test connection by trying to get camera state
        grpc::ClientContext context;
        livelinkapi::Empty request;
        livelinkapi::CameraState response;
        
        auto status = m_stub->GetCamera(&context, request, &response);
        if (status.ok()) {
            m_connected = true;
            std::cout << "Successfully connected to LiveLink server" << std::endl;
            return true;
        } else {
            std::cerr << "Failed to connect to LiveLink server: " << status.error_message() << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception during LiveLink connection: " << e.what() << std::endl;
        return false;
    }
}

void CameraSyncLiveLink::disconnect() {
    if (m_connected) {
        std::cout << "Disconnecting from LiveLink gRPC server..." << std::endl;
        m_stub.reset();
        m_channel.reset();
        m_connected = false;
    }
}

bool CameraSyncLiveLink::isConnected() const {
    return m_connected;
}

bool CameraSyncLiveLink::setCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, float fov) {
    if (!m_connected || !m_stub) {
        m_cachedPosition = position;
        m_cachedTarget = target;
        m_cachedUp = up;
        if (fov > 0.0f) m_cachedFov = fov;
        return false;
    }

    try {
        grpc::ClientContext context;
        livelinkapi::CameraState request;
        livelinkapi::Empty response;

        // Set position
        glmToVec3(position, request.mutable_position());
        
        // Set target
        glmToVec3(target, request.mutable_target());
        
        // Set up vector
        glmToVec3(up, request.mutable_up());
        
        // Set FOV if provided
        if (fov > 0.0f) {
            request.set_fov(fov);
        }

        auto status = m_stub->SetCamera(&context, request, &response);
        bool success = status.ok();
        
        if (success) {
            m_cachedPosition = position;
            m_cachedTarget = target;
            m_cachedUp = up;
            if (fov > 0.0f) m_cachedFov = fov;
        }
        
        logGrpcStatus("SetCamera", success);
        return success;
    } catch (const std::exception& e) {
        std::cerr << "Exception in setCamera: " << e.what() << std::endl;
        return false;
    }
}

bool CameraSyncLiveLink::setCameraPosition(const glm::vec3& position) {
    if (!m_connected || !m_stub) {
        m_cachedPosition = position;
        return false;
    }

    try {
        grpc::ClientContext context;
        livelinkapi::CameraState request;
        livelinkapi::Empty response;

        glmToVec3(position, request.mutable_position());

        auto status = m_stub->SetCamera(&context, request, &response);
        bool success = status.ok();
        
        if (success) {
            m_cachedPosition = position;
        }
        
        logGrpcStatus("SetCameraPosition", success);
        return success;
    } catch (const std::exception& e) {
        std::cerr << "Exception in setCameraPosition: " << e.what() << std::endl;
        return false;
    }
}

bool CameraSyncLiveLink::setCameraTarget(const glm::vec3& target) {
    if (!m_connected || !m_stub) {
        m_cachedTarget = target;
        return false;
    }

    try {
        grpc::ClientContext context;
        livelinkapi::CameraState request;
        livelinkapi::Empty response;

        glmToVec3(target, request.mutable_target());

        auto status = m_stub->SetCamera(&context, request, &response);
        bool success = status.ok();
        
        if (success) {
            m_cachedTarget = target;
        }
        
        logGrpcStatus("SetCameraTarget", success);
        return success;
    } catch (const std::exception& e) {
        std::cerr << "Exception in setCameraTarget: " << e.what() << std::endl;
        return false;
    }
}

bool CameraSyncLiveLink::setCameraUp(const glm::vec3& up) {
    if (!m_connected || !m_stub) {
        m_cachedUp = up;
        return false;
    }

    try {
        grpc::ClientContext context;
        livelinkapi::CameraState request;
        livelinkapi::Empty response;

        glmToVec3(up, request.mutable_up());

        auto status = m_stub->SetCamera(&context, request, &response);
        bool success = status.ok();
        
        if (success) {
            m_cachedUp = up;
        }
        
        logGrpcStatus("SetCameraUp", success);
        return success;
    } catch (const std::exception& e) {
        std::cerr << "Exception in setCameraUp: " << e.what() << std::endl;
        return false;
    }
}

bool CameraSyncLiveLink::setCameraFov(float fov) {
    if (!m_connected || !m_stub) {
        m_cachedFov = fov;
        return false;
    }

    try {
        grpc::ClientContext context;
        livelinkapi::CameraState request;
        livelinkapi::Empty response;

        request.set_fov(fov);

        auto status = m_stub->SetCamera(&context, request, &response);
        bool success = status.ok();
        
        if (success) {
            m_cachedFov = fov;
        }
        
        logGrpcStatus("SetCameraFov", success);
        return success;
    } catch (const std::exception& e) {
        std::cerr << "Exception in setCameraFov: " << e.what() << std::endl;
        return false;
    }
}

bool CameraSyncLiveLink::getCamera(glm::vec3& position, glm::vec3& target, glm::vec3& up, float& fov) {
    if (!m_connected || !m_stub) {
        position = m_cachedPosition;
        target = m_cachedTarget;
        up = m_cachedUp;
        fov = m_cachedFov;
        return false;
    }

    try {
        grpc::ClientContext context;
        livelinkapi::Empty request;
        livelinkapi::CameraState response;

        auto status = m_stub->GetCamera(&context, request, &response);
        bool success = status.ok();
        
        if (success) {
            if (response.has_position()) {
                position = vec3ToGlm(response.position());
                m_cachedPosition = position;
            } else {
                position = m_cachedPosition;
            }
            
            if (response.has_target()) {
                target = vec3ToGlm(response.target());
                m_cachedTarget = target;
            } else {
                target = m_cachedTarget;
            }
            
            if (response.has_up()) {
                up = vec3ToGlm(response.up());
                m_cachedUp = up;
            } else {
                up = m_cachedUp;
            }
            
            if (response.has_fov()) {
                fov = response.fov();
                m_cachedFov = fov;
            } else {
                fov = m_cachedFov;
            }
        } else {
            position = m_cachedPosition;
            target = m_cachedTarget;
            up = m_cachedUp;
            fov = m_cachedFov;
        }
        
        logGrpcStatus("GetCamera", success);
        return success;
    } catch (const std::exception& e) {
        std::cerr << "Exception in getCamera: " << e.what() << std::endl;
        position = m_cachedPosition;
        target = m_cachedTarget;
        up = m_cachedUp;
        fov = m_cachedFov;
        return false;
    }
}

bool CameraSyncLiveLink::getMeshList(std::vector<MeshInfo>& meshes) {
    if (!m_connected || !m_stub) {
        return false;
    }

    try {
        grpc::ClientContext context;
        livelinkapi::Empty request;
        livelinkapi::MeshList response;

        auto status = m_stub->GetMeshes(&context, request, &response);
        bool success = status.ok();
        
        if (success) {
            meshes.clear();
            for (const auto& mesh : response.meshes()) {
                MeshInfo info;
                info.name = mesh.name();
                info.id = mesh.id();
                info.objectHandle = mesh.objecthandle();
                meshes.push_back(info);
            }
        }
        
        logGrpcStatus("GetMeshes", success);
        return success;
    } catch (const std::exception& e) {
        std::cerr << "Exception in getMeshList: " << e.what() << std::endl;
        return false;
    }
}

bool CameraSyncLiveLink::getMeshData(int32_t objectHandle, MeshData& meshData) {
    if (!m_connected || !m_stub) {
        return false;
    }

    try {
        grpc::ClientContext context;
        livelinkapi::MeshRequest request;
        livelinkapi::MeshData response;

        request.set_objecthandle(objectHandle);

        auto status = m_stub->GetMesh(&context, request, &response);
        bool success = status.ok();
        
        if (success) {
            meshData.name = response.name();
            
            // Convert positions
            meshData.positions.clear();
            for (const auto& pos : response.positions()) {
                meshData.positions.push_back(vec3ToGlm(pos));
            }
            
            // Convert normals
            meshData.normals.clear();
            for (const auto& normal : response.normals()) {
                meshData.normals.push_back(vec3ToGlm(normal));
            }
            
            // Copy indices
            meshData.vertsPerPoly.assign(response.vertsperpoly().begin(), response.vertsperpoly().end());
            meshData.polyVertIndices.assign(response.polyvertindices().begin(), response.polyvertindices().end());
            meshData.polyNormalIndices.assign(response.polynormalindices().begin(), response.polynormalindices().end());
            
            meshData.windingOrder = response.windingorder();
            
            // Convert world matrix
            if (response.has_worldmatrix()) {
                meshData.worldMatrix = matrixDToGlm(response.worldmatrix());
            } else {
                meshData.worldMatrix = glm::mat4(1.0f); // Identity matrix
            }
        }
        
        logGrpcStatus("GetMesh", success);
        return success;
    } catch (const std::exception& e) {
        std::cerr << "Exception in getMeshData: " << e.what() << std::endl;
        return false;
    }
}

void CameraSyncLiveLink::glmToVec3(const glm::vec3& glmVec, livelinkapi::Vec3* protoVec) {
    protoVec->set_x(glmVec.x);
    protoVec->set_y(glmVec.y);
    protoVec->set_z(glmVec.z);
}

glm::vec3 CameraSyncLiveLink::vec3ToGlm(const livelinkapi::Vec3& protoVec) {
    return glm::vec3(protoVec.x(), protoVec.y(), protoVec.z());
}

void CameraSyncLiveLink::glmToMatrixD(const glm::mat4& glmMat, livelinkapi::MatrixD* protoMat) {
    // GLM matrices are column-major, but we need to convert to row-major for the proto
    // glmMat[col][row] -> protoMat row
    
    auto* row0 = protoMat->mutable_row0();
    row0->set_x(glmMat[0][0]); row0->set_y(glmMat[1][0]); row0->set_z(glmMat[2][0]); row0->set_w(glmMat[3][0]);
    
    auto* row1 = protoMat->mutable_row1();
    row1->set_x(glmMat[0][1]); row1->set_y(glmMat[1][1]); row1->set_z(glmMat[2][1]); row1->set_w(glmMat[3][1]);
    
    auto* row2 = protoMat->mutable_row2();
    row2->set_x(glmMat[0][2]); row2->set_y(glmMat[1][2]); row2->set_z(glmMat[2][2]); row2->set_w(glmMat[3][2]);
}

glm::mat4 CameraSyncLiveLink::matrixDToGlm(const livelinkapi::MatrixD& protoMat) {
    // Convert from row-major proto matrix to column-major GLM matrix
    glm::mat4 result;
    
    const auto& row0 = protoMat.row0();
    const auto& row1 = protoMat.row1();
    const auto& row2 = protoMat.row2();
    
    // Set columns from rows
    result[0] = glm::vec4(row0.x(), row1.x(), row2.x(), 0.0f);
    result[1] = glm::vec4(row0.y(), row1.y(), row2.y(), 0.0f);
    result[2] = glm::vec4(row0.z(), row1.z(), row2.z(), 0.0f);
    result[3] = glm::vec4(row0.w(), row1.w(), row2.w(), 1.0f);
    
    return result;
}

void CameraSyncLiveLink::logGrpcStatus(const std::string& operation, bool success) {
    if (success) {
        std::cout << "LiveLink " << operation << " succeeded" << std::endl;
    } else {
        std::cerr << "LiveLink " << operation << " failed" << std::endl;
    }
}