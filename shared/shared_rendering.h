#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

namespace ModernRendering {

/**
 * Modern OpenGL renderer for 3D graphics
 * Provides a simple interface for rendering 3D scenes with modern OpenGL
 */
class ModernRenderer {
private:
    GLuint shaderProgram;
    GLuint VAO, VBO, EBO;
    GLuint viewLoc, projLoc, modelLoc, viewPosLoc, timeLoc;
    
    // Cube vertices with positions and normals
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormal;
        
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        uniform vec3 viewPos;
        uniform float time;
        
        out vec3 FragPos;
        out vec3 Normal;
        out vec3 ViewPos;
        out float Time;
        
        void main() {
            FragPos = vec3(model * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(model))) * aNormal;
            ViewPos = viewPos;
            Time = time;
            
            gl_Position = projection * view * vec4(FragPos, 1.0);
        }
    )";
    
    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        
        in vec3 FragPos;
        in vec3 Normal;
        in vec3 ViewPos;
        in float Time;
        
        void main() {
            // Simple lighting calculation
            vec3 lightPos = vec3(2.0, 2.0, 2.0);
            vec3 lightColor = vec3(1.0, 1.0, 1.0);
            
            // Ambient
            float ambientStrength = 0.1;
            vec3 ambient = ambientStrength * lightColor;
            
            // Diffuse
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;
            
            // Specular
            float specularStrength = 0.5;
            vec3 viewDir = normalize(ViewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
            vec3 specular = specularStrength * spec * lightColor;
            
            // Color based on normal and time for visual interest
            vec3 baseColor = vec3(0.5 + 0.5 * sin(Time * 0.001), 
                                  0.5 + 0.5 * cos(Time * 0.001), 
                                  0.8);
            
            vec3 result = (ambient + diffuse + specular) * baseColor;
            FragColor = vec4(result, 1.0);
        }
    )";

public:
    ModernRenderer() : shaderProgram(0), VAO(0), VBO(0), EBO(0) {
        // Initialize cube vertices (position + normal)
        vertices = {
            // Front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            
            // Back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            
            // Left face
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
            
            // Right face
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
            
            // Top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            
            // Bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f
        };
        
        indices = {
            // Front face
            0, 1, 2, 2, 3, 0,
            // Back face
            4, 5, 6, 6, 7, 4,
            // Left face
            8, 9, 10, 10, 11, 8,
            // Right face
            12, 13, 14, 14, 15, 12,
            // Top face
            16, 17, 18, 18, 19, 16,
            // Bottom face
            20, 21, 22, 22, 23, 20
        };
    }
    
    ~ModernRenderer() {
        cleanup();
    }
    
    /**
     * Initialize the renderer - create shaders, buffers, etc.
     */
    bool initialize() {
        std::cout << "Initializing ModernRenderer..." << std::endl;
        
        // Create and compile shaders
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        
        if (vertexShader == 0 || fragmentShader == 0) {
            std::cerr << "Failed to compile shaders" << std::endl;
            return false;
        }
        
        // Create shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        
        // Check for linking errors
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cerr << "Shader program linking failed: " << infoLog << std::endl;
            return false;
        }
        
        // Clean up individual shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        // Get uniform locations
        viewLoc = glGetUniformLocation(shaderProgram, "view");
        projLoc = glGetUniformLocation(shaderProgram, "projection");
        modelLoc = glGetUniformLocation(shaderProgram, "model");
        viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
        timeLoc = glGetUniformLocation(shaderProgram, "time");
        
        // Create VAO, VBO, EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glBindVertexArray(0);
        
        std::cout << "ModernRenderer initialized successfully" << std::endl;
        return true;
    }
    
    /**
     * Render the scene
     */
    void render(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos, float time) {
        glUseProgram(shaderProgram);
        
        // Set uniforms
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPos));
        glUniform1f(timeLoc, time);
        
        // Create model matrix (rotate the cube)
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, time * 0.001f, glm::vec3(0.5f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        // Render the cube
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
    /**
     * Clean up resources
     */
    void cleanup() {
        if (VAO) {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }
        if (VBO) {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }
        if (EBO) {
            glDeleteBuffers(1, &EBO);
            EBO = 0;
        }
        if (shaderProgram) {
            glDeleteProgram(shaderProgram);
            shaderProgram = 0;
        }
    }
    
    /**
     * Load a new model with vertices and indices
     */
    template<typename VertexType>
    void loadModel(const std::vector<VertexType>& newVertices, const std::vector<unsigned int>& newIndices, const std::string& modelName = "loaded_model") {
        // Convert vertices to flat array format (position + normal)
        vertices.clear();
        vertices.reserve(newVertices.size() * 6); // 3 for position + 3 for normal
        
        for (const auto& vertex : newVertices) {
            // Add position
            vertices.push_back(vertex.position.x);
            vertices.push_back(vertex.position.y);
            vertices.push_back(vertex.position.z);
            // Add normal
            vertices.push_back(vertex.normal.x);
            vertices.push_back(vertex.normal.y);
            vertices.push_back(vertex.normal.z);
        }
        
        indices = newIndices;
        
        // Update buffers if OpenGL is initialized
        if (VAO != 0) {
            updateBuffers();
        }
        
        std::cout << "Loaded model: " << modelName << " with " << newVertices.size() << " vertices and " << indices.size()/3 << " triangles" << std::endl;
    }
    
    /**
     * Load a new model with flat vertex array and indices
     */
    void loadModel(const std::vector<float>& newVertices, const std::vector<unsigned int>& newIndices, const std::string& modelName = "loaded_model") {
        vertices = newVertices;
        indices = newIndices;
        
        // Update buffers if OpenGL is initialized
        if (VAO != 0) {
            updateBuffers();
        }
        
        std::cout << "Loaded model: " << modelName << " with " << vertices.size()/6 << " vertices and " << indices.size()/3 << " triangles" << std::endl;
    }
    
    /**
     * Reset to default cube geometry
     */
    void resetToCube() {
        // Reset to default cube vertices and indices
        vertices = {
            // Front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            
            // Back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            
            // Left face
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
            
            // Right face
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
            
            // Top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            
            // Bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f
        };
        
        indices = {
            // Front face
            0, 1, 2, 2, 3, 0,
            // Back face
            4, 5, 6, 6, 7, 4,
            // Left face
            8, 9, 10, 10, 11, 8,
            // Right face
            12, 13, 14, 14, 15, 12,
            // Top face
            16, 17, 18, 18, 19, 16,
            // Bottom face
            20, 21, 22, 22, 23, 20
        };
        
        // Update buffers if OpenGL is initialized
        if (VAO != 0) {
            updateBuffers();
        }
        
        std::cout << "Reset to default cube geometry" << std::endl;
    }

private:
    /**
     * Update OpenGL buffers with current vertex and index data
     */
    void updateBuffers() {
        if (VAO == 0) return;
        
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glBindVertexArray(0);
    }
    GLuint compileShader(GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "Shader compilation failed: " << infoLog << std::endl;
            return 0;
        }
        
        return shader;
    }
};

} // namespace ModernRendering