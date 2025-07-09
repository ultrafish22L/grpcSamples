#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

// Enhanced shaders with lighting and modern effects
namespace ModernRendering {

// Vertex shader source with lighting
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec3 vertexColor;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalMatrix * aNormal;
    vertexColor = aColor;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

// Fragment shader source with Phong lighting
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 vertexColor;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform float time;

void main()
{
    // Ambient lighting
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular lighting (shiny effect)
    float specularStrength = 0.8;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;
    
    // Add subtle color variation based on time
    vec3 baseColor = vertexColor;
    baseColor += 0.1 * sin(time + FragPos.x * 2.0) * vec3(0.2, 0.3, 0.4);
    
    // Rim lighting for extra shine
    float rimPower = 2.0;
    float rim = 1.0 - max(dot(viewDir, norm), 0.0);
    rim = pow(rim, rimPower);
    vec3 rimColor = vec3(0.3, 0.6, 1.0) * rim * 0.5;
    
    vec3 result = (ambient + diffuse + specular) * baseColor + rimColor;
    FragColor = vec4(result, 1.0);
}
)";

// Skybox vertex shader
const char* skyboxVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}
)";

// Skybox fragment shader with procedural gradient
const char* skyboxFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
uniform float time;

vec3 getSkyColor(vec3 direction) {
    float y = direction.y;
    
    // Create a beautiful gradient from horizon to zenith
    vec3 horizonColor = vec3(1.0, 0.7, 0.4);  // Warm orange
    vec3 zenithColor = vec3(0.2, 0.4, 0.8);   // Deep blue
    vec3 nadirColor = vec3(0.1, 0.1, 0.2);    // Dark blue-purple
    
    // Add some dynamic color variation
    float timeOffset = sin(time * 0.1) * 0.1;
    horizonColor += vec3(timeOffset, timeOffset * 0.5, -timeOffset * 0.3);
    
    // Smooth transitions
    float t1 = smoothstep(-0.2, 0.3, y);  // Horizon to zenith
    float t2 = smoothstep(-1.0, -0.2, y); // Nadir to horizon
    
    vec3 color = mix(nadirColor, horizonColor, t2);
    color = mix(color, zenithColor, t1);
    
    // Add some stars/sparkles
    float stars = 0.0;
    vec3 starPos = direction * 50.0;
    stars += smoothstep(0.99, 1.0, sin(starPos.x * 127.1) * sin(starPos.y * 311.7) * sin(starPos.z * 74.7));
    stars *= smoothstep(0.2, 1.0, y); // Only show stars in upper hemisphere
    
    color += vec3(stars * 0.8);
    
    // Add subtle cloud-like patterns
    float clouds = sin(direction.x * 3.0 + time * 0.05) * sin(direction.z * 2.0 + time * 0.03);
    clouds = smoothstep(0.3, 0.7, clouds) * 0.1;
    clouds *= smoothstep(-0.1, 0.5, y); // Only in upper part
    
    color += vec3(clouds);
    
    return color;
}

void main()
{
    vec3 color = getSkyColor(normalize(TexCoords));
    FragColor = vec4(color, 1.0);
}
)";

// Enhanced cube vertices with positions, normals, and beautiful colors
float vertices[] = {
    // Front face (warm coral) - Normal: (0, 0, 1)
    -4.0f, -4.0f,  4.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.5f, 0.3f,
     4.0f, -4.0f,  4.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.5f, 0.3f,
     4.0f,  4.0f,  4.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.5f, 0.3f,
    -4.0f,  4.0f,  4.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.5f, 0.3f,
    
    // Back face (emerald green) - Normal: (0, 0, -1)
    -4.0f, -4.0f, -4.0f,  0.0f, 0.0f, -1.0f,  0.2f, 0.8f, 0.4f,
     4.0f, -4.0f, -4.0f,  0.0f, 0.0f, -1.0f,  0.2f, 0.8f, 0.4f,
     4.0f,  4.0f, -4.0f,  0.0f, 0.0f, -1.0f,  0.2f, 0.8f, 0.4f,
    -4.0f,  4.0f, -4.0f,  0.0f, 0.0f, -1.0f,  0.2f, 0.8f, 0.4f,
    
    // Left face (royal blue) - Normal: (-1, 0, 0)
    -4.0f, -4.0f, -4.0f,  -1.0f, 0.0f, 0.0f,  0.2f, 0.4f, 1.0f,
    -4.0f, -4.0f,  4.0f,  -1.0f, 0.0f, 0.0f,  0.2f, 0.4f, 1.0f,
    -4.0f,  4.0f,  4.0f,  -1.0f, 0.0f, 0.0f,  0.2f, 0.4f, 1.0f,
    -4.0f,  4.0f, -4.0f,  -1.0f, 0.0f, 0.0f,  0.2f, 0.4f, 1.0f,
    
    // Right face (golden yellow) - Normal: (1, 0, 0)
     4.0f, -4.0f, -4.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.8f, 0.2f,
     4.0f, -4.0f,  4.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.8f, 0.2f,
     4.0f,  4.0f,  4.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.8f, 0.2f,
     4.0f,  4.0f, -4.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.8f, 0.2f,
    
    // Top face (violet purple) - Normal: (0, 1, 0)
    -4.0f,  4.0f, -4.0f,  0.0f, 1.0f, 0.0f,  0.8f, 0.3f, 1.0f,
     4.0f,  4.0f, -4.0f,  0.0f, 1.0f, 0.0f,  0.8f, 0.3f, 1.0f,
     4.0f,  4.0f,  4.0f,  0.0f, 1.0f, 0.0f,  0.8f, 0.3f, 1.0f,
    -4.0f,  4.0f,  4.0f,  0.0f, 1.0f, 0.0f,  0.8f, 0.3f, 1.0f,
    
    // Bottom face (turquoise cyan) - Normal: (0, -1, 0)
    -4.0f, -4.0f, -4.0f,  0.0f, -1.0f, 0.0f,  0.2f, 0.9f, 0.8f,
     4.0f, -4.0f, -4.0f,  0.0f, -1.0f, 0.0f,  0.2f, 0.9f, 0.8f,
     4.0f, -4.0f,  4.0f,  0.0f, -1.0f, 0.0f,  0.2f, 0.9f, 0.8f,
    -4.0f, -4.0f,  4.0f,  0.0f, -1.0f, 0.0f,  0.2f, 0.9f, 0.8f
};

unsigned int indices[] = {
    // Front face
    0, 1, 2,   2, 3, 0,
    // Back face
    4, 5, 6,   6, 7, 4,
    // Left face
    8, 9, 10,  10, 11, 8,
    // Right face
    12, 13, 14, 14, 15, 12,
    // Top face
    16, 17, 18, 18, 19, 16,
    // Bottom face
    20, 21, 22, 22, 23, 20
};

// Skybox vertices
float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

// Utility functions
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }
    
    return shader;
}

GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}

struct ModernRenderer {
    GLuint cubeVAO, cubeVBO, cubeEBO;
    GLuint modelVAO, modelVBO, modelEBO;
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubeShaderProgram, skyboxShaderProgram;
    
    // Model data
    std::vector<float> modelVertices;
    std::vector<unsigned int> modelIndices;
    std::string currentModelName = "cube";
    bool hasCustomModel = false;
    
    // Uniform locations
    GLint cubeModelLoc, cubeViewLoc, cubeProjLoc, cubeNormalMatrixLoc;
    GLint cubeLightPosLoc, cubeLightColorLoc, cubeViewPosLoc, cubeTimeLoc;
    GLint skyboxViewLoc, skyboxProjLoc, skyboxTimeLoc;
    
    void initialize() {
        // Create shader programs
        cubeShaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
        skyboxShaderProgram = createShaderProgram(skyboxVertexShaderSource, skyboxFragmentShaderSource);
        
        // Setup cube VAO
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glGenBuffers(1, &cubeEBO);
        
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // Color attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        // Setup model VAO (initially empty)
        glGenVertexArrays(1, &modelVAO);
        glGenBuffers(1, &modelVBO);
        glGenBuffers(1, &modelEBO);
        
        // Setup skybox VAO
        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // Get uniform locations
        cubeModelLoc = glGetUniformLocation(cubeShaderProgram, "model");
        cubeViewLoc = glGetUniformLocation(cubeShaderProgram, "view");
        cubeProjLoc = glGetUniformLocation(cubeShaderProgram, "projection");
        cubeNormalMatrixLoc = glGetUniformLocation(cubeShaderProgram, "normalMatrix");
        cubeLightPosLoc = glGetUniformLocation(cubeShaderProgram, "lightPos");
        cubeLightColorLoc = glGetUniformLocation(cubeShaderProgram, "lightColor");
        cubeViewPosLoc = glGetUniformLocation(cubeShaderProgram, "viewPos");
        cubeTimeLoc = glGetUniformLocation(cubeShaderProgram, "time");
        
        skyboxViewLoc = glGetUniformLocation(skyboxShaderProgram, "view");
        skyboxProjLoc = glGetUniformLocation(skyboxShaderProgram, "projection");
        skyboxTimeLoc = glGetUniformLocation(skyboxShaderProgram, "time");
    }
    
    template<typename VertexType>
    void loadModel(const std::vector<VertexType>& vertices, const std::vector<unsigned int>& indices, const std::string& name) {
        currentModelName = name;
        hasCustomModel = true;
        
        // Convert vertices to float array
        modelVertices.clear();
        for (const auto& vertex : vertices) {
            // Position
            modelVertices.push_back(vertex.position.x);
            modelVertices.push_back(vertex.position.y);
            modelVertices.push_back(vertex.position.z);
            // Normal
            modelVertices.push_back(vertex.normal.x);
            modelVertices.push_back(vertex.normal.y);
            modelVertices.push_back(vertex.normal.z);
            // Color
            modelVertices.push_back(vertex.color.r);
            modelVertices.push_back(vertex.color.g);
            modelVertices.push_back(vertex.color.b);
        }
        
        modelIndices = indices;
        
        // Update model VAO
        glBindVertexArray(modelVAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
        glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(float), modelVertices.data(), GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelIndices.size() * sizeof(unsigned int), modelIndices.data(), GL_STATIC_DRAW);
        
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // Color attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0);
        
        std::cout << "Loaded model '" << name << "' with " << vertices.size() << " vertices and " << indices.size() << " indices" << std::endl;
    }
    
    void resetToCube() {
        hasCustomModel = false;
        currentModelName = "cube";
        std::cout << "Reset to default cube" << std::endl;
    }
    
    void render(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos, float time) {
        // === RENDER SKYBOX FIRST ===
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShaderProgram);
        
        glm::mat4 skyboxView = glm::mat4(glm::mat3(view));
        glUniformMatrix4fv(skyboxViewLoc, 1, GL_FALSE, glm::value_ptr(skyboxView));
        glUniformMatrix4fv(skyboxProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1f(skyboxTimeLoc, time);
        
        glBindVertexArray(skyboxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
        
        // === RENDER MODEL (CUBE OR CUSTOM) ===
        glUseProgram(cubeShaderProgram);
        
        glm::mat4 model = glm::mat4(1.0f);
        
        // Only rotate if showing the default cube
        if (!hasCustomModel) {
            model = glm::rotate(model, time * 0.3f, glm::vec3(0.5f, 1.0f, 0.0f));
            model = glm::rotate(model, time * 0.2f, glm::vec3(1.0f, 0.0f, 0.5f));
        }
        
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
        
        glm::vec3 lightPos = glm::vec3(
            3.0f * cos(time * 0.5f),
            2.0f + sin(time * 0.7f),
            3.0f * sin(time * 0.5f)
        );
        glm::vec3 lightColor = glm::vec3(1.0f, 0.95f, 0.8f);
        
        glUniformMatrix4fv(cubeModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(cubeViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(cubeProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix3fv(cubeNormalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(cubeLightPosLoc, 1, glm::value_ptr(lightPos));
        glUniform3fv(cubeLightColorLoc, 1, glm::value_ptr(lightColor));
        glUniform3fv(cubeViewPosLoc, 1, glm::value_ptr(viewPos));
        glUniform1f(cubeTimeLoc, time);
        
        if (hasCustomModel && !modelIndices.empty()) {
            glBindVertexArray(modelVAO);
            glDrawElements(GL_TRIANGLES, modelIndices.size(), GL_UNSIGNED_INT, 0);
        } else {
            glBindVertexArray(cubeVAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
    }
    
    void cleanup() {
        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteVertexArrays(1, &modelVAO);
        glDeleteVertexArrays(1, &skyboxVAO);
        glDeleteBuffers(1, &cubeVBO);
        glDeleteBuffers(1, &cubeEBO);
        glDeleteBuffers(1, &modelVBO);
        glDeleteBuffers(1, &modelEBO);
        glDeleteBuffers(1, &skyboxVBO);
        glDeleteProgram(cubeShaderProgram);
        glDeleteProgram(skyboxShaderProgram);
    }
};

} // namespace ModernRendering