/**
 * WebGL utilities for 3D rendering
 * Contains common shaders, matrix operations, and WebGL setup functions
 */

// Matrix operations utility
class MatrixUtils {
    static createPerspectiveMatrix(fov, aspect, near, far) {
        const f = 1.0 / Math.tan(fov / 2);
        const rangeInv = 1 / (near - far);
        
        return new Float32Array([
            f / aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (near + far) * rangeInv, -1,
            0, 0, near * far * rangeInv * 2, 0
        ]);
    }

    static createLookAtMatrix(eye, center, up) {
        const zAxis = this.normalize(this.subtract(eye, center));
        const xAxis = this.normalize(this.cross(up, zAxis));
        const yAxis = this.cross(zAxis, xAxis);

        return new Float32Array([
            xAxis[0], yAxis[0], zAxis[0], 0,
            xAxis[1], yAxis[1], zAxis[1], 0,
            xAxis[2], yAxis[2], zAxis[2], 0,
            -this.dot(xAxis, eye), -this.dot(yAxis, eye), -this.dot(zAxis, eye), 1
        ]);
    }

    static createIdentityMatrix() {
        return new Float32Array([
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ]);
    }

    static createTranslationMatrix(x, y, z) {
        return new Float32Array([
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            x, y, z, 1
        ]);
    }

    static createRotationMatrix(angleX, angleY, angleZ) {
        const cx = Math.cos(angleX), sx = Math.sin(angleX);
        const cy = Math.cos(angleY), sy = Math.sin(angleY);
        const cz = Math.cos(angleZ), sz = Math.sin(angleZ);

        return new Float32Array([
            cy * cz, -cy * sz, sy, 0,
            cx * sz + sx * sy * cz, cx * cz - sx * sy * sz, -sx * cy, 0,
            sx * sz - cx * sy * cz, sx * cz + cx * sy * sz, cx * cy, 0,
            0, 0, 0, 1
        ]);
    }

    static multiply(a, b) {
        const result = new Float32Array(16);
        for (let i = 0; i < 4; i++) {
            for (let j = 0; j < 4; j++) {
                result[i * 4 + j] = 
                    a[i * 4 + 0] * b[0 * 4 + j] +
                    a[i * 4 + 1] * b[1 * 4 + j] +
                    a[i * 4 + 2] * b[2 * 4 + j] +
                    a[i * 4 + 3] * b[3 * 4 + j];
            }
        }
        return result;
    }

    static transpose(matrix) {
        return new Float32Array([
            matrix[0], matrix[4], matrix[8],
            matrix[1], matrix[5], matrix[9],
            matrix[2], matrix[6], matrix[10]
        ]);
    }

    // Vector operations
    static subtract(a, b) {
        return [a[0] - b[0], a[1] - b[1], a[2] - b[2]];
    }

    static cross(a, b) {
        return [
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]
        ];
    }

    static dot(a, b) {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }

    static normalize(v) {
        const length = Math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        return length > 0 ? [v[0] / length, v[1] / length, v[2] / length] : [0, 0, 0];
    }
}

// Shader utilities
class ShaderUtils {
    static getStandardVertexShader() {
        return `#version 300 es
            precision highp float;
            
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aNormal;
            layout (location = 2) in vec3 aColor;
            
            uniform mat4 uModel;
            uniform mat4 uView;
            uniform mat4 uProjection;
            uniform mat3 uNormalMatrix;
            
            out vec3 vFragPos;
            out vec3 vNormal;
            out vec3 vVertexColor;
            
            void main() {
                vFragPos = vec3(uModel * vec4(aPos, 1.0));
                vNormal = uNormalMatrix * aNormal;
                vVertexColor = aColor;
                
                gl_Position = uProjection * uView * vec4(vFragPos, 1.0);
            }
        `;
    }

    static getStandardFragmentShader() {
        return `#version 300 es
            precision highp float;
            
            in vec3 vFragPos;
            in vec3 vNormal;
            in vec3 vVertexColor;
            
            uniform vec3 uLightPos;
            uniform vec3 uLightColor;
            uniform vec3 uViewPos;
            uniform float uTime;
            
            out vec4 FragColor;
            
            void main() {
                // Ambient lighting
                float ambientStrength = 0.3;
                vec3 ambient = ambientStrength * uLightColor;
                
                // Diffuse lighting
                vec3 norm = normalize(vNormal);
                vec3 lightDir = normalize(uLightPos - vFragPos);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = diff * uLightColor;
                
                // Specular lighting
                float specularStrength = 0.8;
                vec3 viewDir = normalize(uViewPos - vFragPos);
                vec3 reflectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
                vec3 specular = specularStrength * spec * uLightColor;
                
                // Combine lighting with vertex color
                vec3 result = (ambient + diffuse + specular) * vVertexColor;
                
                // Add subtle animation based on time
                float pulse = 0.95 + 0.05 * sin(uTime * 2.0);
                result *= pulse;
                
                FragColor = vec4(result, 1.0);
            }
        `;
    }

    static getSkyboxVertexShader() {
        return `#version 300 es
            precision highp float;
            
            layout (location = 0) in vec3 aPos;
            
            uniform mat4 uView;
            uniform mat4 uProjection;
            
            out vec3 vTexCoord;
            
            void main() {
                vTexCoord = aPos;
                
                // Remove translation from view matrix for skybox
                mat4 rotView = mat4(mat3(uView));
                vec4 clipPos = uProjection * rotView * vec4(aPos, 1.0);
                
                // Ensure skybox is always at far plane
                gl_Position = clipPos.xyww;
            }
        `;
    }

    static getSkyboxFragmentShader() {
        return `#version 300 es
            precision highp float;
            
            in vec3 vTexCoord;
            uniform float uTime;
            
            out vec4 FragColor;
            
            void main() {
                // Create a simple gradient skybox
                vec3 direction = normalize(vTexCoord);
                
                // Sky gradient from horizon to zenith
                float t = direction.y * 0.5 + 0.5;
                vec3 skyColor = mix(vec3(0.5, 0.7, 1.0), vec3(0.1, 0.3, 0.8), t);
                
                // Add some subtle animation
                skyColor += 0.1 * sin(uTime * 0.5 + direction.x * 2.0) * vec3(1.0, 0.8, 0.6);
                
                FragColor = vec4(skyColor, 1.0);
            }
        `;
    }

    static createShader(gl, type, source) {
        const shader = gl.createShader(type);
        gl.shaderSource(shader, source);
        gl.compileShader(shader);
        
        if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
            const error = gl.getShaderInfoLog(shader);
            gl.deleteShader(shader);
            throw new Error(`Shader compilation error: ${error}`);
        }
        
        return shader;
    }

    static createProgram(gl, vertexShader, fragmentShader) {
        const program = gl.createProgram();
        gl.attachShader(program, vertexShader);
        gl.attachShader(program, fragmentShader);
        gl.linkProgram(program);
        
        if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
            const error = gl.getProgramInfoLog(program);
            gl.deleteProgram(program);
            throw new Error(`Program linking error: ${error}`);
        }
        
        return program;
    }
}

// Geometry utilities
class GeometryUtils {
    static createCubeGeometry() {
        // Cube vertices with normals and colors
        const vertices = new Float32Array([
            // Front face (red)
            -1, -1,  1,  0,  0,  1,  1,  0,  0,
             1, -1,  1,  0,  0,  1,  1,  0,  0,
             1,  1,  1,  0,  0,  1,  1,  0,  0,
            -1,  1,  1,  0,  0,  1,  1,  0,  0,
            
            // Back face (green)
            -1, -1, -1,  0,  0, -1,  0,  1,  0,
            -1,  1, -1,  0,  0, -1,  0,  1,  0,
             1,  1, -1,  0,  0, -1,  0,  1,  0,
             1, -1, -1,  0,  0, -1,  0,  1,  0,
            
            // Top face (blue)
            -1,  1, -1,  0,  1,  0,  0,  0,  1,
            -1,  1,  1,  0,  1,  0,  0,  0,  1,
             1,  1,  1,  0,  1,  0,  0,  0,  1,
             1,  1, -1,  0,  1,  0,  0,  0,  1,
            
            // Bottom face (yellow)
            -1, -1, -1,  0, -1,  0,  1,  1,  0,
             1, -1, -1,  0, -1,  0,  1,  1,  0,
             1, -1,  1,  0, -1,  0,  1,  1,  0,
            -1, -1,  1,  0, -1,  0,  1,  1,  0,
            
            // Right face (magenta)
             1, -1, -1,  1,  0,  0,  1,  0,  1,
             1,  1, -1,  1,  0,  0,  1,  0,  1,
             1,  1,  1,  1,  0,  0,  1,  0,  1,
             1, -1,  1,  1,  0,  0,  1,  0,  1,
            
            // Left face (cyan)
            -1, -1, -1, -1,  0,  0,  0,  1,  1,
            -1, -1,  1, -1,  0,  0,  0,  1,  1,
            -1,  1,  1, -1,  0,  0,  0,  1,  1,
            -1,  1, -1, -1,  0,  0,  0,  1,  1
        ]);

        const indices = new Uint16Array([
            0,  1,  2,    0,  2,  3,    // front
            4,  5,  6,    4,  6,  7,    // back
            8,  9,  10,   8,  10, 11,   // top
            12, 13, 14,   12, 14, 15,   // bottom
            16, 17, 18,   16, 18, 19,   // right
            20, 21, 22,   20, 22, 23    // left
        ]);

        return { vertices, indices };
    }

    static createSkyboxGeometry() {
        const vertices = new Float32Array([
            // Positions only for skybox
            -1.0,  1.0, -1.0,
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0,

            -1.0, -1.0,  1.0,
            -1.0, -1.0, -1.0,
            -1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0,
            -1.0,  1.0,  1.0,
            -1.0, -1.0,  1.0,

             1.0, -1.0, -1.0,
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0, -1.0,
             1.0, -1.0, -1.0,

            -1.0, -1.0,  1.0,
            -1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0, -1.0,  1.0,
            -1.0, -1.0,  1.0,

            -1.0,  1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            -1.0,  1.0, -1.0,

            -1.0, -1.0, -1.0,
            -1.0, -1.0,  1.0,
             1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0
        ]);

        return { vertices };
    }
}

// Camera controller
class CameraController {
    constructor() {
        this.radius = 5.0;
        this.theta = 0.0;  // horizontal angle
        this.phi = 0.0;    // vertical angle
        this.center = [0.0, 0.0, 0.0];
        this.autoRotate = true;
        this.rotationSpeed = 0.5;
    }

    update(deltaTime) {
        if (this.autoRotate) {
            this.theta += this.rotationSpeed * deltaTime;
        }
    }

    getPosition() {
        const x = this.center[0] + this.radius * Math.sin(this.theta) * Math.cos(this.phi);
        const y = this.center[1] + this.radius * Math.sin(this.phi);
        const z = this.center[2] + this.radius * Math.cos(this.theta) * Math.cos(this.phi);
        return [x, y, z];
    }

    getViewMatrix() {
        const eye = this.getPosition();
        const up = [0, 1, 0];
        return MatrixUtils.createLookAtMatrix(eye, this.center, up);
    }

    handleMouseMove(deltaX, deltaY, isDragging, isPanning) {
        if (isDragging) {
            this.theta += deltaX * 0.01;
            this.phi = Math.max(-Math.PI/2 + 0.1, Math.min(Math.PI/2 - 0.1, this.phi + deltaY * 0.01));
            this.autoRotate = false; // Stop auto-rotation when user interacts
        } else if (isPanning) {
            // Implement panning logic here if needed
        }
    }

    handleWheel(deltaY) {
        this.radius = Math.max(1.0, Math.min(20.0, this.radius + deltaY * 0.01));
    }

    setFromOctaneCamera(position, target, up, fov) {
        // Convert Octane camera to our spherical coordinates
        const direction = MatrixUtils.subtract(position, target);
        this.radius = Math.sqrt(MatrixUtils.dot(direction, direction));
        this.center = [...target];
        
        // Calculate spherical coordinates
        this.theta = Math.atan2(direction[0], direction[2]);
        this.phi = Math.asin(direction[1] / this.radius);
        
        this.autoRotate = false; // Stop auto-rotation when syncing
    }
}

// Export utilities to global scope
window.MatrixUtils = MatrixUtils;
window.ShaderUtils = ShaderUtils;
window.GeometryUtils = GeometryUtils;
window.CameraController = CameraController;

console.log('WebGL utilities loaded successfully');