#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

namespace SharedUtils {

#define GL_CHECK_ERROR(file, line)	SharedUtils::RendererGl::GLCheckErrors(file, line)

    /**
     * Modern OpenGL renderer for 3D graphics
     * Provides a simple interface for rendering 3D scenes with modern OpenGL
     */
    class RendererGl {
    private:

        struct shaderInfo
        {
            GLuint viewLoc = 0;
            GLuint projLoc = 0;
            GLuint modelLoc = 0;
            GLuint viewPosLoc = 0;
            GLuint timeLoc = 0;

            GLuint shaderProgram = 0;
            GLuint VAO  = 0;
            GLuint VBO  = 0;
            GLuint EBO  = 0;

            // Cube vertices with positions and normals
            std::vector<float> vertices;
            std::vector<unsigned int> indices;

            void cleanup()
            {
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
        };

        shaderInfo shaderInfoCube;
        shaderInfo shaderInfoQuad;

    public:
        RendererGl();

        ~RendererGl() {
            cleanup();
        }

        /**
         * Initialize the renderer - create shaders, buffers, etc.
         */
        bool initialize();
        
        /**
         * Render the scene
         */
        void renderCube(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos, float time);

        /**
         * Render the scene
         */
        void renderQuad(GLuint tex);

        /**
         * Clean up resources
         */
        void cleanup();


        static const char* GlErrorString(GLenum error);
        static bool GLCheckErrors(const char* file, int line);


        /**
         * Load a new model with vertices and indices
         */
        template<typename VertexType>
        void loadModel(const std::vector<VertexType>& newVertices, const std::vector<unsigned int>& newIndices, const std::string& modelName = "loaded_model") {
            // Convert vertices to flat array format (position + normal)
            shaderInfoCube.vertices.clear();
            shaderInfoCube.vertices.reserve(newVertices.size() * 6); // 3 for position + 3 for normal

            for (const auto& vertex : newVertices) {
                // Add position
                shaderInfoCube.vertices.push_back(vertex.position.x);
                shaderInfoCube.vertices.push_back(vertex.position.y);
                shaderInfoCube.vertices.push_back(vertex.position.z);
                // Add normal
                shaderInfoCube.vertices.push_back(vertex.normal.x);
                shaderInfoCube.vertices.push_back(vertex.normal.y);
                shaderInfoCube.vertices.push_back(vertex.normal.z);
            }

            shaderInfoCube.indices = newIndices;

            // Update buffers if OpenGL is initialized
            if (shaderInfoCube.VAO != 0) {
                updateBuffers();
            }

            std::cout << "Loaded model: " << modelName << " with " << newVertices.size() << " vertices and " << shaderInfoCube.indices.size() / 3 << " triangles" << std::endl;
        }

        /**
         * Load a new model with flat vertex array and indices
         */
        void loadModel(const std::vector<float>& newVertices, const std::vector<unsigned int>& newIndices, const std::string& modelName = "loaded_model") {
            shaderInfoCube.vertices = newVertices;
            shaderInfoCube.indices = newIndices;

            // Update buffers if OpenGL is initialized
            if (shaderInfoCube.VAO != 0) {
                updateBuffers();
            }

            std::cout << "Loaded model: " << modelName << " with " << shaderInfoCube.vertices.size() / 6 << " vertices and " << shaderInfoCube.indices.size() / 3 << " triangles" << std::endl;
        }

        /**
         * Reset to default cube geometry
         */
        void resetToCube() {
            // Reset to default cube vertices and indices
            shaderInfoCube.vertices = {
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

            shaderInfoCube.indices = {
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
            if (shaderInfoCube.VAO != 0) {
                updateBuffers();
            }

            std::cout << "Reset to default cube geometry" << std::endl;
        }

    private:
        /**
         * Update OpenGL buffers with current vertex and index data
         */
        void updateBuffers() {
            if (shaderInfoCube.VAO == 0) return;

            glBindVertexArray(shaderInfoCube.VAO);

            glBindBuffer(GL_ARRAY_BUFFER, shaderInfoCube.VBO);
            glBufferData(GL_ARRAY_BUFFER, shaderInfoCube.vertices.size() * sizeof(float), shaderInfoCube.vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderInfoCube.EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, shaderInfoCube.indices.size() * sizeof(unsigned int), shaderInfoCube.indices.data(), GL_STATIC_DRAW);

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

};