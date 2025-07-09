#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>

namespace SharedUtils {

/**
 * 3D Model data structure
 */
struct ModelData {
    std::vector<float> vertices;  // Interleaved: position(3) + normal(3) + color(3)
    std::vector<unsigned int> indices;
    std::string name;
    bool isValid = false;
    
    void clear() {
        vertices.clear();
        indices.clear();
        name.clear();
        isValid = false;
    }
    
    size_t getVertexCount() const {
        return vertices.size() / 9; // 9 floats per vertex (pos + normal + color)
    }
    
    size_t getTriangleCount() const {
        return indices.size() / 3;
    }
};

/**
 * 3D Model loader supporting OBJ, PLY, and STL formats
 */
class ModelLoader {
public:
    /**
     * Load a 3D model from file
     * @param filename Path to the model file
     * @return ModelData structure with loaded data
     */
    static ModelData loadModel(const std::string& filename);
    
    /**
     * Get the base filename without path and extension
     * @param filepath Full file path
     * @return Base filename
     */
    static std::string getBaseName(const std::string& filepath);

private:
    static ModelData loadOBJ(const std::string& filename);
    static ModelData loadPLY(const std::string& filename);
    static ModelData loadSTL(const std::string& filename);
    
    static glm::vec3 calculateNormal(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3);
    static glm::vec3 generateVertexColor(const glm::vec3& position);
    static void generateNormals(std::vector<glm::vec3>& positions, std::vector<unsigned int>& indices, std::vector<glm::vec3>& normals);
};

// Implementation
inline ModelData ModelLoader::loadModel(const std::string& filename) {
    if (filename.empty()) {
        std::cerr << "Error: Empty filename provided" << std::endl;
        return ModelData{};
    }
    
    // Check if file exists
    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << "Error: Cannot open file: " << filename << std::endl;
        return ModelData{};
    }
    file.close();
    
    // Determine file format by extension
    std::string ext = filename.substr(filename.find_last_of('.'));
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    ModelData model;
    
    if (ext == ".obj") {
        model = loadOBJ(filename);
    } else if (ext == ".ply") {
        model = loadPLY(filename);
    } else if (ext == ".stl") {
        model = loadSTL(filename);
    } else {
        std::cerr << "Error: Unsupported file format: " << ext << std::endl;
        return ModelData{};
    }
    
    if (model.isValid) {
        model.name = getBaseName(filename);
        std::cout << "Successfully loaded model: " << model.name 
                  << " (" << model.getVertexCount() << " vertices, " 
                  << model.getTriangleCount() << " triangles)" << std::endl;
    }
    
    return model;
}

inline std::string ModelLoader::getBaseName(const std::string& filepath) {
    size_t lastSlash = filepath.find_last_of("/\\");
    size_t lastDot = filepath.find_last_of('.');
    
    size_t start = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
    size_t end = (lastDot == std::string::npos) ? filepath.length() : lastDot;
    
    return filepath.substr(start, end - start);
}

inline ModelData ModelLoader::loadOBJ(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open OBJ file: " << filename << std::endl;
        return ModelData{};
    }
    
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        
        if (prefix == "v") {
            // Vertex position
            float x, y, z;
            iss >> x >> y >> z;
            positions.push_back(glm::vec3(x, y, z));
        } else if (prefix == "vn") {
            // Vertex normal
            float x, y, z;
            iss >> x >> y >> z;
            normals.push_back(glm::normalize(glm::vec3(x, y, z)));
        } else if (prefix == "f") {
            // Face
            std::string vertex1, vertex2, vertex3;
            iss >> vertex1 >> vertex2 >> vertex3;
            
            // Parse vertex indices (handle format: v/vt/vn or v//vn or v)
            auto parseVertex = [](const std::string& vertexStr) -> unsigned int {
                size_t firstSlash = vertexStr.find('/');
                if (firstSlash == std::string::npos) {
                    return std::stoi(vertexStr) - 1; // OBJ indices are 1-based
                } else {
                    return std::stoi(vertexStr.substr(0, firstSlash)) - 1;
                }
            };
            
            indices.push_back(parseVertex(vertex1));
            indices.push_back(parseVertex(vertex2));
            indices.push_back(parseVertex(vertex3));
        }
    }
    
    file.close();
    
    if (positions.empty()) {
        std::cerr << "Error: No vertices found in OBJ file" << std::endl;
        return ModelData{};
    }
    
    // Generate normals if not provided
    if (normals.empty()) {
        normals.resize(positions.size(), glm::vec3(0.0f));
        generateNormals(positions, indices, normals);
    }
    
    // Create interleaved vertex data
    ModelData model;
    model.vertices.reserve(positions.size() * 9);
    
    for (size_t i = 0; i < positions.size(); ++i) {
        const glm::vec3& pos = positions[i];
        const glm::vec3& normal = (i < normals.size()) ? normals[i] : glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3 color = generateVertexColor(pos);
        
        // Position
        model.vertices.push_back(pos.x);
        model.vertices.push_back(pos.y);
        model.vertices.push_back(pos.z);
        
        // Normal
        model.vertices.push_back(normal.x);
        model.vertices.push_back(normal.y);
        model.vertices.push_back(normal.z);
        
        // Color
        model.vertices.push_back(color.r);
        model.vertices.push_back(color.g);
        model.vertices.push_back(color.b);
    }
    
    model.indices = indices;
    model.isValid = true;
    
    return model;
}

inline ModelData ModelLoader::loadPLY(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open PLY file: " << filename << std::endl;
        return ModelData{};
    }
    
    std::string line;
    int vertexCount = 0;
    int faceCount = 0;
    bool inHeader = true;
    
    // Parse header
    while (std::getline(file, line) && inHeader) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        
        if (token == "element") {
            std::string elementType;
            int count;
            iss >> elementType >> count;
            
            if (elementType == "vertex") {
                vertexCount = count;
            } else if (elementType == "face") {
                faceCount = count;
            }
        } else if (token == "end_header") {
            inHeader = false;
        }
    }
    
    if (vertexCount == 0) {
        std::cerr << "Error: No vertices specified in PLY header" << std::endl;
        return ModelData{};
    }
    
    std::vector<glm::vec3> positions;
    std::vector<unsigned int> indices;
    
    // Read vertices
    for (int i = 0; i < vertexCount; ++i) {
        if (!std::getline(file, line)) break;
        
        std::istringstream iss(line);
        float x, y, z;
        iss >> x >> y >> z;
        positions.push_back(glm::vec3(x, y, z));
    }
    
    // Read faces
    for (int i = 0; i < faceCount; ++i) {
        if (!std::getline(file, line)) break;
        
        std::istringstream iss(line);
        int numVertices;
        iss >> numVertices;
        
        if (numVertices == 3) {
            unsigned int v1, v2, v3;
            iss >> v1 >> v2 >> v3;
            indices.push_back(v1);
            indices.push_back(v2);
            indices.push_back(v3);
        }
    }
    
    file.close();
    
    if (positions.empty()) {
        std::cerr << "Error: No vertices loaded from PLY file" << std::endl;
        return ModelData{};
    }
    
    // Generate normals
    std::vector<glm::vec3> normals(positions.size(), glm::vec3(0.0f));
    generateNormals(positions, indices, normals);
    
    // Create interleaved vertex data
    ModelData model;
    model.vertices.reserve(positions.size() * 9);
    
    for (size_t i = 0; i < positions.size(); ++i) {
        const glm::vec3& pos = positions[i];
        const glm::vec3& normal = normals[i];
        const glm::vec3 color = generateVertexColor(pos);
        
        // Position
        model.vertices.push_back(pos.x);
        model.vertices.push_back(pos.y);
        model.vertices.push_back(pos.z);
        
        // Normal
        model.vertices.push_back(normal.x);
        model.vertices.push_back(normal.y);
        model.vertices.push_back(normal.z);
        
        // Color
        model.vertices.push_back(color.r);
        model.vertices.push_back(color.g);
        model.vertices.push_back(color.b);
    }
    
    model.indices = indices;
    model.isValid = true;
    
    return model;
}

inline ModelData ModelLoader::loadSTL(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open STL file: " << filename << std::endl;
        return ModelData{};
    }
    
    std::vector<glm::vec3> positions;
    std::vector<unsigned int> indices;
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        
        if (token == "vertex") {
            float x, y, z;
            iss >> x >> y >> z;
            positions.push_back(glm::vec3(x, y, z));
            indices.push_back(positions.size() - 1);
        }
    }
    
    file.close();
    
    if (positions.empty()) {
        std::cerr << "Error: No vertices found in STL file" << std::endl;
        return ModelData{};
    }
    
    // Generate normals
    std::vector<glm::vec3> normals(positions.size(), glm::vec3(0.0f));
    generateNormals(positions, indices, normals);
    
    // Create interleaved vertex data
    ModelData model;
    model.vertices.reserve(positions.size() * 9);
    
    for (size_t i = 0; i < positions.size(); ++i) {
        const glm::vec3& pos = positions[i];
        const glm::vec3& normal = normals[i];
        const glm::vec3 color = generateVertexColor(pos);
        
        // Position
        model.vertices.push_back(pos.x);
        model.vertices.push_back(pos.y);
        model.vertices.push_back(pos.z);
        
        // Normal
        model.vertices.push_back(normal.x);
        model.vertices.push_back(normal.y);
        model.vertices.push_back(normal.z);
        
        // Color
        model.vertices.push_back(color.r);
        model.vertices.push_back(color.g);
        model.vertices.push_back(color.b);
    }
    
    model.indices = indices;
    model.isValid = true;
    
    return model;
}

inline glm::vec3 ModelLoader::calculateNormal(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3) {
    glm::vec3 edge1 = v2 - v1;
    glm::vec3 edge2 = v3 - v1;
    return glm::normalize(glm::cross(edge1, edge2));
}

inline glm::vec3 ModelLoader::generateVertexColor(const glm::vec3& position) {
    // Generate procedural colors based on position
    float r = 0.5f + 0.5f * sin(position.x * 2.0f);
    float g = 0.5f + 0.5f * sin(position.y * 2.0f + 2.0f);
    float b = 0.5f + 0.5f * sin(position.z * 2.0f + 4.0f);
    return glm::vec3(r, g, b);
}

inline void ModelLoader::generateNormals(std::vector<glm::vec3>& positions, std::vector<unsigned int>& indices, std::vector<glm::vec3>& normals) {
    // Initialize normals to zero
    std::fill(normals.begin(), normals.end(), glm::vec3(0.0f));
    
    // Calculate face normals and accumulate
    for (size_t i = 0; i < indices.size(); i += 3) {
        if (i + 2 < indices.size()) {
            unsigned int i1 = indices[i];
            unsigned int i2 = indices[i + 1];
            unsigned int i3 = indices[i + 2];
            
            if (i1 < positions.size() && i2 < positions.size() && i3 < positions.size()) {
                glm::vec3 normal = calculateNormal(positions[i1], positions[i2], positions[i3]);
                normals[i1] += normal;
                normals[i2] += normal;
                normals[i3] += normal;
            }
        }
    }
    
    // Normalize accumulated normals
    for (auto& normal : normals) {
        if (glm::length(normal) > 0.0f) {
            normal = glm::normalize(normal);
        } else {
            normal = glm::vec3(0.0f, 1.0f, 0.0f); // Default up vector
        }
    }
}

} // namespace SharedUtils