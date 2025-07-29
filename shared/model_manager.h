#pragma once

#include "model_loader.h"
#include "file_dialog.h"
#include "shared_rendering.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>

namespace SharedUtils {

/**
 * Vertex structure compatible with ModernRenderer
 */
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
};

/**
 * Model management system for handling cube and custom models
 */
class ModelManager {
public:
    /**
     * Initialize the model manager with a renderer
     */
    void initialize(ModernRendering::ModernRenderer* renderer);
    
    /**
     * Load a model from file dialog
     */
    void loadModelFromDialog();
    
    /**
     * Load a model from specific file path
     */
    bool loadModelFromFile(const std::string& filename);
    
    /**
     * Reset to default cube
     */
    void resetToDefaultCube();
    
    /**
     * Update window title with current model name
     */
    void updateWindowTitle(GLFWwindow* window, const std::string& appName = "3D Model Viewer");
    
    /**
     * Check if a custom model is currently loaded
     */
    bool hasCustomModel() const { return m_hasCustomModel; }
    
    /**
     * Get current model name
     */
    const std::string& getCurrentModelName() const { return m_currentModelName; }
    
    /**
     * Get current model data
     */
    const ModelData& getCurrentModelData() const { return m_currentModel; }

private:
    ModernRendering::ModernRenderer* m_renderer = nullptr;
    ModelData m_currentModel;
    std::string m_currentModelName = "cube";
    bool m_hasCustomModel = false;
    
    void printModelInfo(const ModelData& model);
};

// Implementation
inline void ModelManager::initialize(ModernRendering::ModernRenderer* renderer) {
    m_renderer = renderer;
    m_hasCustomModel = false;
    m_currentModelName = "cube";
}

inline void ModelManager::loadModelFromDialog() {
    std::string filename = FileDialog::openFile();
    if (!filename.empty()) {
        loadModelFromFile(filename);
    }
}

inline bool ModelManager::loadModelFromFile(const std::string& filename) {
    if (!m_renderer) {
        std::cerr << "Error: Renderer not initialized" << std::endl;
        return false;
    }
    
    if (!FileDialog::isSupportedModelFile(filename)) {
        std::cerr << "Error: Unsupported file format: " << filename << std::endl;
        return false;
    }
    
    std::cout << "Loading model: " << filename << std::endl;
    
    ModelData model = ModelLoader::loadModel(filename);
    if (!model.isValid) {
        std::cerr << "Error: Failed to load model from " << filename << std::endl;
        return false;
    }
    
    // Convert flat float array to Vertex structures
    std::vector<Vertex> vertices;
    vertices.reserve(model.getVertexCount());
    
    for (size_t i = 0; i < model.vertices.size(); i += 9) {
        Vertex vertex;
        vertex.position = glm::vec3(model.vertices[i], model.vertices[i+1], model.vertices[i+2]);
        vertex.normal = glm::vec3(model.vertices[i+3], model.vertices[i+4], model.vertices[i+5]);
        vertex.color = glm::vec3(model.vertices[i+6], model.vertices[i+7], model.vertices[i+8]);
        vertices.push_back(vertex);
    }
    
    // Update renderer with new model
    m_renderer->loadModel(vertices, model.indices, model.name);
    
    // Update state
    m_currentModel = model;
    m_currentModelName = model.name;
    m_hasCustomModel = true;
    
    printModelInfo(model);
    
    return true;
}

inline void ModelManager::resetToDefaultCube() {
    if (!m_renderer) {
        std::cerr << "Error: Renderer not initialized" << std::endl;
        return;
    }
    
    m_renderer->resetToCube();
    m_hasCustomModel = false;
    m_currentModelName = "cube";
    m_currentModel.clear();
    
    std::cout << "Reset to default cube" << std::endl;
}

inline void ModelManager::updateWindowTitle(GLFWwindow* window, const std::string& appName) {
    if (!window) return;
    
    std::string title;
    if (m_hasCustomModel) {
        title = "🎯 " + appName + " - " + m_currentModelName + " (" + 
                std::to_string(m_currentModel.getVertexCount()) + " vertices, " +
                std::to_string(m_currentModel.getTriangleCount()) + " triangles)";
    } else {
        title = "🚀 " + appName + " - " + m_currentModelName + " (Default Cube)";
    }
    
    glfwSetWindowTitle(window, title.c_str());
}

inline void ModelManager::printModelInfo(const ModelData& model) {
    std::cout << "=== Model Information ===" << std::endl;
    std::cout << "Name: " << model.name << std::endl;
    std::cout << "Vertices: " << model.getVertexCount() << std::endl;
    std::cout << "Triangles: " << model.getTriangleCount() << std::endl;
    std::cout << "Data size: " << model.vertices.size() << " floats, " 
              << model.indices.size() << " indices" << std::endl;
    std::cout << "=========================" << std::endl;
}

} // namespace SharedUtils