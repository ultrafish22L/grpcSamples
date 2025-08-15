#include "shared_rendering.h"

using namespace SharedUtils;

const char* vertexShaderSourceCube = R"(
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

const char* fragmentShaderSourceCube = R"(
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
    const char* vertexShaderSourceQuad = R"(
    #version 450

    layout(location = 0) in vec3 pos;
    layout(location = 1) in vec2 uv_in;

    out vec3 color;
    out vec2 uv;

    void main() {
	    gl_Position = vec4(pos, 1.0);
	    color = vec3(1.0);
	    uv = uv_in;    
    }
    )";

    const char* fragmentShaderSourceQuad = R"(
    #version 450

    in vec3 color;
    in vec2 uv;
    uniform sampler2D tex;

    out vec4 frag_color;

    void main() {
        vec4 tcolor = texture( tex, uv);
    //	frag_color = vec4(color, 1.0);
	    frag_color = tcolor;
    }
    )";

RendererGl::RendererGl()
{
    // Initialize cube vertices (position + normal)
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

    // define a quad to render the texture on
    shaderInfoQuad.vertices = {
         1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
         1.0f, -1.0f,  0.0f, 1.0f, 1.0f,
    };
    shaderInfoQuad.indices = {
        0, 1, 2,
        2, 3, 0,
    };
}
    
/**
    * Initialize the renderer - create shaders, buffers, etc.
    */
bool RendererGl::initialize() {
    std::cout << "Initializing RendererGl..." << std::endl;
        
    // Enable depth testing and other modern OpenGL features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); // Anti-aliasing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create and compile shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSourceCube);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSourceCube);
        
    if (vertexShader == 0 || fragmentShader == 0) {
        std::cerr << "Failed to compile shaders" << std::endl;
        return false;
    }
        
    // Create shader program
    shaderInfoCube.shaderProgram = glCreateProgram();
    glAttachShader(shaderInfoCube.shaderProgram, vertexShader);
    glAttachShader(shaderInfoCube.shaderProgram, fragmentShader);
    glLinkProgram(shaderInfoCube.shaderProgram);
        
    // Check for linking errors
    GLint success;
    glGetProgramiv(shaderInfoCube.shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderInfoCube.shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        return false;
    }
        
    // Clean up individual shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
        
    // Get uniform locations
    shaderInfoCube.viewLoc = glGetUniformLocation(shaderInfoCube.shaderProgram, "view");
    shaderInfoCube.projLoc = glGetUniformLocation(shaderInfoCube.shaderProgram, "projection");
    shaderInfoCube.modelLoc = glGetUniformLocation(shaderInfoCube.shaderProgram, "model");
    shaderInfoCube.viewPosLoc = glGetUniformLocation(shaderInfoCube.shaderProgram, "viewPos");
    shaderInfoCube.timeLoc = glGetUniformLocation(shaderInfoCube.shaderProgram, "time");
        
    // Create VAO, VBO, EBO
    glGenVertexArrays(1, &shaderInfoCube.VAO);
    glGenBuffers(1, &shaderInfoCube.VBO);
    glGenBuffers(1, &shaderInfoCube.EBO);
        
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


    // Create and compile shaders
    vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSourceQuad);
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSourceQuad);

    if (vertexShader == 0 || fragmentShader == 0) {
        std::cerr << "Failed to compile shaders" << std::endl;
        return false;
    }

    // Create shader program
    shaderInfoQuad.shaderProgram = glCreateProgram();
    glAttachShader(shaderInfoQuad.shaderProgram, vertexShader);
    glAttachShader(shaderInfoQuad.shaderProgram, fragmentShader);
    glLinkProgram(shaderInfoQuad.shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderInfoQuad.shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderInfoQuad.shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        return false;
    }

    // Clean up individual shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create VAO, VBO, EBO
    glGenVertexArrays(1, &shaderInfoQuad.VAO);
    glBindVertexArray(shaderInfoQuad.VAO);

    glGenBuffers(1, &shaderInfoQuad.EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderInfoQuad.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shaderInfoQuad.indices.size(), shaderInfoQuad.indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &shaderInfoQuad.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, shaderInfoQuad.VBO);
    glBufferData(GL_ARRAY_BUFFER, shaderInfoQuad.vertices.size(), shaderInfoQuad.vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(shaderInfoQuad.VBO);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, shaderInfoQuad.VBO);
    glBufferData(GL_ARRAY_BUFFER, shaderInfoQuad.vertices.size() * sizeof(float), shaderInfoQuad.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderInfoQuad.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shaderInfoQuad.indices.size() * sizeof(unsigned int), shaderInfoQuad.indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    std::cout << "RendererGl initialized successfully" << std::endl;
    return true;
}
    
/**
    * Render the scene
    */
void RendererGl::renderCube(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos, float time) {
    glUseProgram(shaderInfoCube.shaderProgram);
        
    // Set uniforms
    glUniformMatrix4fv(shaderInfoCube.viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shaderInfoCube.projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(shaderInfoCube.viewPosLoc, 1, glm::value_ptr(viewPos));
    glUniform1f(shaderInfoCube.timeLoc, time);
        
    // Create model matrix (rotate the cube)
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, time * 0.001f, glm::vec3(0.5f, 1.0f, 0.0f));
    glUniformMatrix4fv(shaderInfoCube.modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
    // Render the cube
    glBindVertexArray(shaderInfoCube.VAO);
    glDrawElements(GL_TRIANGLES, shaderInfoCube.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
    

/**
    * Render the scene
    */
void RendererGl::renderQuad(GLuint tex) {
    glDisable(GL_DEPTH_TEST);
#if 1
    if (tex != 0)
    {
        // render the textured quad
        glUseProgram(shaderInfoQuad.shaderProgram);
        GL_CHECK_ERROR(__FILE__, __LINE__);

        glActiveTexture(GL_TEXTURE0);
        GL_CHECK_ERROR(__FILE__, __LINE__); 
        
        glBindTexture(GL_TEXTURE_2D, tex);
        GL_CHECK_ERROR(__FILE__, __LINE__); 
        
        glBindVertexArray(shaderInfoQuad.VAO);
        GL_CHECK_ERROR(__FILE__, __LINE__);

        glDrawElements(GL_TRIANGLES, shaderInfoQuad.indices.size(), GL_UNSIGNED_INT, 0);
        GL_CHECK_ERROR(__FILE__, __LINE__);

        glBindVertexArray(0);
    }
#else
    // blit
    GLint restoreFramebuffer = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &restoreFramebuffer);

    // Regular framebuffer
    GLenum e;
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebufferGL);
    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureNameGL, 0);
    e = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
    if (e == GL_FRAMEBUFFER_COMPLETE)
    {
        glBindTexture(GL_TEXTURE_2D, mTextureNameGL);

        glBlitFramebuffer(0, 0, mWidth, mHeight,
            0, 0, mWidth, mHeight,
            GL_COLOR_BUFFER_BIT,
            GL_NEAREST);
    }
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, restoreFramebuffer);
#endif
}

/**
    * Clean up resources
    */
void RendererGl::cleanup() {

    shaderInfoCube.cleanup();
    shaderInfoQuad.cleanup();
}

const char* RendererGl::GlErrorString(GLenum error)
{
    switch (error)
    {
    case GL_NO_ERROR:						return "GL_NO_ERROR";
    case GL_INVALID_ENUM:					return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:					return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:				return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION:	return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY:					return "GL_OUT_OF_MEMORY";
    default: return "unknown";
    }
}
//--------------------------------------------------------------------------------	

bool  RendererGl::GLCheckErrors(const char* file, int line)
{
    bool ret = false;
    for (int i = 0; i < 10; i++)
    {
        const GLenum error = glGetError();
        if (error == GL_NO_ERROR)
        {
            break;
        }
        std::cout << "GL error on line " << line << " in " << GlErrorString(error) << std::endl;
        ret = true;
    }
    return ret;
}
