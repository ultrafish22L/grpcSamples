/**
 * WebGL utilities for 3D rendering
 * Contains common shaders, matrix operations, WebGL setup functions, and 3D renderer
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

    static createModelMatrix(translation, rotation, scale) {
        // Create individual transformation matrices
        const T = this.createTranslationMatrix(translation[0], translation[1], translation[2]);
        const Rx = this.createRotationXMatrix(rotation[0]);
        const Ry = this.createRotationYMatrix(rotation[1]);
        const Rz = this.createRotationZMatrix(rotation[2]);
        const S = this.createScaleMatrix(scale[0], scale[1], scale[2]);
        
        // Combine: T * Rz * Ry * Rx * S
        let result = this.multiply(T, Rz);
        result = this.multiply(result, Ry);
        result = this.multiply(result, Rx);
        result = this.multiply(result, S);
        
        return result;
    }

    static createRotationXMatrix(angle) {
        const c = Math.cos(angle);
        const s = Math.sin(angle);
        return new Float32Array([
            1, 0, 0, 0,
            0, c, s, 0,
            0, -s, c, 0,
            0, 0, 0, 1
        ]);
    }

    static createRotationYMatrix(angle) {
        const c = Math.cos(angle);
        const s = Math.sin(angle);
        return new Float32Array([
            c, 0, -s, 0,
            0, 1, 0, 0,
            s, 0, c, 0,
            0, 0, 0, 1
        ]);
    }

    static createRotationZMatrix(angle) {
        const c = Math.cos(angle);
        const s = Math.sin(angle);
        return new Float32Array([
            c, s, 0, 0,
            -s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ]);
    }

    static createScaleMatrix(x, y, z) {
        return new Float32Array([
            x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
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

    static inverse(matrix) {
        // Simple 4x4 matrix inverse (for transformation matrices)
        const m = matrix;
        const inv = new Float32Array(16);
        
        inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
        inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
        inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
        inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
        inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
        inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
        inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
        inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
        inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
        inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
        inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
        inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
        inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
        inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
        inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
        inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
        
        const det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
        if (det === 0) return this.createIdentityMatrix();
        
        const detInv = 1.0 / det;
        for (let i = 0; i < 16; i++) {
            inv[i] *= detInv;
        }
        
        return inv;
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
                // Create a stable professional gradient skybox
                vec3 direction = normalize(vTexCoord);
                
                // Professional dark gradient from horizon to zenith
                float t = direction.y * 0.5 + 0.5;
                vec3 skyColor = mix(vec3(0.08, 0.08, 0.12), vec3(0.02, 0.02, 0.08), t);
                
                // Add very subtle static variation based on direction (no animation)
                skyColor += 0.02 * (sin(direction.x * 3.0) + cos(direction.z * 2.0)) * vec3(0.1, 0.1, 0.15);
                
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
            // Skybox cube with inward-facing triangles (clockwise winding)
            // Front face (z = -1)
            -1.0, -1.0, -1.0,
            -1.0,  1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0, -1.0, -1.0,
            -1.0, -1.0, -1.0,

            // Back face (z = 1)
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0,

            // Left face (x = -1)
            -1.0, -1.0,  1.0,
            -1.0,  1.0,  1.0,
            -1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0,
            -1.0, -1.0, -1.0,
            -1.0, -1.0,  1.0,

            // Right face (x = 1)
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0, -1.0,  1.0,
             1.0, -1.0, -1.0,

            // Top face (y = 1)
            -1.0,  1.0, -1.0,
            -1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0,

            // Bottom face (y = -1)
            -1.0, -1.0,  1.0,
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0, -1.0,  1.0,
            -1.0, -1.0,  1.0
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
        this.rotationSpeed = 0.5;
    }

    update(deltaTime) {
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
    }
}

/**
 * Simple WebGL Renderer for 3D visualization
 * Simplified version that works with the index.html connection pattern
 */
class SimpleWebGLRenderer {
    constructor(gl, logger) {
        this.gl = gl;
        this.logger = logger;
        this.canvas = gl.canvas; // Store canvas reference for resizing
        this.program = null;
        this.buffers = {};
        this.camera = {
            position: [0, 0, 5],
            target: [0, 0, 0],
            up: [0, 1, 0],
            fov: 45
        };
        this.rotation = { x: 0, y: 0 };
        this.zoom = 1.0;
        
        // Set up resize handling
        this.setupResize();
    }

    setupResize() {
        // Bind the resize function to maintain 'this' context
        this.resizeCanvas = this.resizeCanvas.bind(this);
        
        // Call resize initially
        this.resizeCanvas();
        
        // Set up resize listener
        window.addEventListener('resize', this.resizeCanvas);
        
        // Also listen for container size changes (using ResizeObserver if available)
        if (window.ResizeObserver) {
            this.resizeObserver = new ResizeObserver(() => {
                this.resizeCanvas();
            });
            this.resizeObserver.observe(this.canvas.parentElement);
        }
    }

    resizeCanvas() {
        const canvas = this.canvas;
        const gl = this.gl;
        
        // Get the actual display size of the canvas in CSS pixels
        const displayWidth = canvas.clientWidth;
        const displayHeight = canvas.clientHeight;
        
        // Check if the canvas drawing buffer size needs to be updated
        if (canvas.width !== displayWidth || canvas.height !== displayHeight) {
            // Resize the WebGL drawing buffer to match the display size
            canvas.width = displayWidth;
            canvas.height = displayHeight;
            
            // Update the WebGL viewport
            gl.viewport(0, 0, displayWidth, displayHeight);
            
            // Log the resize for debugging
            this.logger.log(`Canvas resized to ${displayWidth}x${displayHeight}`, 'info');
        }
    }

    init() {
        const gl = this.gl;
        
        // Simple WebGL 1.0 compatible shaders
        const vertexShaderSource = `
            attribute vec4 aVertexPosition;
            
            uniform mat4 uModelViewMatrix;
            uniform mat4 uProjectionMatrix;
            
            void main() {
                gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
            }
        `;
        
        const fragmentShaderSource = `
            precision mediump float;
            
            void main() {
                // Bright red for maximum visibility
                gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
            }
        `;
        
        // Create shaders
        const vertexShader = this.createShader(gl.VERTEX_SHADER, vertexShaderSource);
        const fragmentShader = this.createShader(gl.FRAGMENT_SHADER, fragmentShaderSource);
        
        // Create program
        this.program = gl.createProgram();
        gl.attachShader(this.program, vertexShader);
        gl.attachShader(this.program, fragmentShader);
        gl.linkProgram(this.program);
        
        if (!gl.getProgramParameter(this.program, gl.LINK_STATUS)) {
            throw new Error('Shader program failed to link: ' + gl.getProgramInfoLog(this.program));
        }
        
        // Get attribute and uniform locations
        this.programInfo = {
            attribLocations: {
                vertexPosition: gl.getAttribLocation(this.program, 'aVertexPosition'),
            },
            uniformLocations: {
                projectionMatrix: gl.getUniformLocation(this.program, 'uProjectionMatrix'),
                modelViewMatrix: gl.getUniformLocation(this.program, 'uModelViewMatrix'),
            },
        };
        
        // Debug: Check if locations were found
        // Debug logging disabled for production
        
        if (this.programInfo.attribLocations.vertexPosition === -1) {
            console.error('aVertexPosition attribute not found in shader');
        }
        
        // Create default cube geometry
        this.createCubeGeometry();
        
        // Enable depth testing
        gl.enable(gl.DEPTH_TEST);
        gl.depthFunc(gl.LEQUAL);
        
        this.logger.log('WebGL renderer initialized', 'success');
    }

    createShader(type, source) {
        const gl = this.gl;
        const shader = gl.createShader(type);
        gl.shaderSource(shader, source);
        gl.compileShader(shader);
        
        if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
            gl.deleteShader(shader);
            throw new Error('Shader compilation error: ' + gl.getShaderInfoLog(shader));
        }
        
        return shader;
    }

    createCubeGeometry() {
        const gl = this.gl;
        
        // Cube vertices
        const positions = [
            // Front face
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            
            // Back face
            -1.0, -1.0, -1.0,
            -1.0,  1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0, -1.0, -1.0,
            
            // Top face
            -1.0,  1.0, -1.0,
            -1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0, -1.0,
            
            // Bottom face
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0, -1.0,  1.0,
            -1.0, -1.0,  1.0,
            
            // Right face
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0,  1.0,  1.0,
             1.0, -1.0,  1.0,
            
            // Left face
            -1.0, -1.0, -1.0,
            -1.0, -1.0,  1.0,
            -1.0,  1.0,  1.0,
            -1.0,  1.0, -1.0,
        ];
        
        // Cube normals
        const normals = [
            // Front
             0.0,  0.0,  1.0,
             0.0,  0.0,  1.0,
             0.0,  0.0,  1.0,
             0.0,  0.0,  1.0,
            
            // Back
             0.0,  0.0, -1.0,
             0.0,  0.0, -1.0,
             0.0,  0.0, -1.0,
             0.0,  0.0, -1.0,
            
            // Top
             0.0,  1.0,  0.0,
             0.0,  1.0,  0.0,
             0.0,  1.0,  0.0,
             0.0,  1.0,  0.0,
            
            // Bottom
             0.0, -1.0,  0.0,
             0.0, -1.0,  0.0,
             0.0, -1.0,  0.0,
             0.0, -1.0,  0.0,
            
            // Right
             1.0,  0.0,  0.0,
             1.0,  0.0,  0.0,
             1.0,  0.0,  0.0,
             1.0,  0.0,  0.0,
            
            // Left
            -1.0,  0.0,  0.0,
            -1.0,  0.0,  0.0,
            -1.0,  0.0,  0.0,
            -1.0,  0.0,  0.0,
        ];
        
        // Cube indices
        const indices = [
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23,   // left
        ];
        
        // Create buffers
        this.buffers.position = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.buffers.position);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);
        
        // Debug: Log vertex data
        // Debug logging disabled for production
        
        this.buffers.normal = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.buffers.normal);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
        
        this.buffers.indices = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.buffers.indices);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
        
        this.indexCount = indices.length;
        
        // Debug: Log index data
        // Debug logging disabled for production
    }

    updateProjection(width, height) {
        this.projectionMatrix = MatrixUtils.createPerspectiveMatrix(
            this.camera.fov * Math.PI / 180, 
            width / height, 
            0.01, 
            100.0
        );
    }

    render() {
        const gl = this.gl;
        
        // Clear canvas with transparent background (no background rendering)
        gl.clearColor(0.0, 0.0, 0.0, 0.0);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        
        // Update projection matrix with current canvas dimensions
        this.updateProjection(this.canvas.width, this.canvas.height);
        
        // Debug: Log render call occasionally
        if (Math.random() < 0.01) { // Log 1% of frames
            // Debug logging disabled for production
        }
        
        // Use shader program
        gl.useProgram(this.program);
        
        // Create model-view matrix
        const modelViewMatrix = MatrixUtils.createLookAtMatrix(
            this.camera.position, 
            this.camera.target, 
            this.camera.up
        );
        
        // Update camera position based on rotation and zoom
        const radius = 5.0 * this.zoom;
        const x = radius * Math.sin(this.rotation.y) * Math.cos(this.rotation.x);
        const y = radius * Math.sin(this.rotation.x);
        const z = radius * Math.cos(this.rotation.y) * Math.cos(this.rotation.x);
        
        const cameraPos = [x, y, z];
        const target = [0, 0, 0];
        const up = [0, 1, 0];

        // Recreate model-view matrix with updated camera position
        const updatedModelViewMatrix = MatrixUtils.createLookAtMatrix(cameraPos, target, up);
        
        // Set uniforms
        if (!this.projectionMatrix) {
            console.error('Projection matrix not initialized');
            return;
        }
        
        // Debug: Log matrices occasionally
        if (Math.random() < 0.01) {
            // Matrix debug logging disabled for production
        }
        
        gl.uniformMatrix4fv(this.programInfo.uniformLocations.projectionMatrix, false, this.projectionMatrix);
        gl.uniformMatrix4fv(this.programInfo.uniformLocations.modelViewMatrix, false, updatedModelViewMatrix);
        
        // Bind position buffer
        gl.bindBuffer(gl.ARRAY_BUFFER, this.buffers.position);
        gl.vertexAttribPointer(this.programInfo.attribLocations.vertexPosition, 3, gl.FLOAT, false, 0, 0);
        gl.enableVertexAttribArray(this.programInfo.attribLocations.vertexPosition);
        
        // Bind index buffer and draw
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.buffers.indices);
        
        // Debug: Log draw call details occasionally
        if (Math.random() < 0.01) { // Log 1% of frames
            // Draw call debug logging disabled for production
        }
        
        gl.drawElements(gl.TRIANGLES, this.indexCount, gl.UNSIGNED_SHORT, 0);
        
        // Debug: Check for WebGL errors
        const error = gl.getError();
        if (error !== gl.NO_ERROR) {
            console.error('WebGL error during draw:', error);
        }
    }

    rotateCamera(deltaX, deltaY = 0) {
        this.rotation.y += deltaX;
        this.rotation.x += deltaY;
        
        // Clamp X rotation
        this.rotation.x = Math.max(-Math.PI/2, Math.min(Math.PI/2, this.rotation.x));
    }

    zoomCamera(delta) {
        this.zoom *= (1 + delta);
        this.zoom = Math.max(0.1, Math.min(10.0, this.zoom));
    }

    resetCamera() {
        this.camera.position = [0, 0, 5];
        this.camera.target = [0, 0, 0];
        this.camera.up = [0, 1, 0];
        this.rotation = { x: 0, y: 0 };
        this.zoom = 1.0;
    }

    getCameraState() {
        return {
            position: { x: this.camera.position[0], y: this.camera.position[1], z: this.camera.position[2] },
            target: { x: this.camera.target[0], y: this.camera.target[1], z: this.camera.target[2] },
            up: { x: this.camera.up[0], y: this.camera.up[1], z: this.camera.up[2] },
            fov: this.camera.fov
        };
    }

    setCameraFromOctane(cameraData) {
        if (cameraData.position) {
            this.camera.position = [cameraData.position.x, cameraData.position.y, cameraData.position.z];
        }
        if (cameraData.target) {
            this.camera.target = [cameraData.target.x, cameraData.target.y, cameraData.target.z];
        }
        if (cameraData.up) {
            this.camera.up = [cameraData.up.x, cameraData.up.y, cameraData.up.z];
        }
        if (cameraData.fov) {
            this.camera.fov = cameraData.fov;
        }
    }

    loadMeshData(meshData) {
        // Future enhancement: Implement mesh loading from Octane data
        // This will allow loading 3D models directly from Octane's mesh data
        this.logger.log('Mesh loading not yet implemented', 'info');
    }

    loadModelFile(file) {
        // Future enhancement: Implement model file loading (OBJ, PLY, STL)
        // This will allow loading 3D models from local files
        this.logger.log('Model file loading not yet implemented', 'info');
    }

    cleanup() {
        // Remove resize event listener
        if (this.resizeCanvas) {
            window.removeEventListener('resize', this.resizeCanvas);
        }
        
        // Disconnect resize observer
        if (this.resizeObserver) {
            this.resizeObserver.disconnect();
        }
    }
}

/**
 * Mouse controls utility for 3D viewers
 */
class MouseControls {
    constructor(canvas, renderer, logger) {
        this.canvas = canvas;
        this.renderer = renderer;
        this.logger = logger;
        this.mouseDown = false;
        this.lastMouseX = 0;
        this.lastMouseY = 0;
        
        this.setupEventListeners();
    }
    
    setupEventListeners() {
        this.canvas.addEventListener('mousedown', (e) => {
            this.mouseDown = true;
            this.lastMouseX = e.clientX;
            this.lastMouseY = e.clientY;
        });

        this.canvas.addEventListener('mouseup', () => {
            this.mouseDown = false;
        });

        this.canvas.addEventListener('mousemove', (e) => {
            if (this.mouseDown && this.renderer) {
                const deltaX = e.clientX - this.lastMouseX;
                const deltaY = e.clientY - this.lastMouseY;
                
                this.renderer.rotateCamera(deltaX * 0.01, deltaY * 0.01);
                
                this.lastMouseX = e.clientX;
                this.lastMouseY = e.clientY;
            }
        });

        this.canvas.addEventListener('wheel', (e) => {
            if (this.renderer) {
                this.renderer.zoomCamera(e.deltaY * 0.001);
            }
            e.preventDefault();
        });
    }
}

/**
 * Camera synchronization utility
 */
class CameraSyncManager {
    constructor(renderer, client, logger) {
        this.renderer = renderer;
        this.client = client;
        this.logger = logger;
        this.syncEnabled = false;
        this.lastSyncTime = 0;
        this.syncCount = 0;
        this.syncRate = 0;
    }
    
    enable() {
        this.syncEnabled = true;
        this.logger.log('Camera sync enabled', 'info');
    }
    
    disable() {
        this.syncEnabled = false;
        this.logger.log('Camera sync disabled', 'info');
    }
    
    toggle() {
        if (this.syncEnabled) {
            this.disable();
        } else {
            this.enable();
        }
        return this.syncEnabled;
    }
    
    async syncToOctane() {
        if (!this.syncEnabled || !this.client || !this.client.connected) {
            return;
        }
        
        const now = Date.now();
        if (now - this.lastSyncTime < 100) return; // Limit to 10 FPS sync rate
        
        try {
            if (this.renderer) {
                const cameraState = this.renderer.getCameraState();
                await this.client.setCamera(cameraState);
                
                this.syncCount++;
                this.lastSyncTime = now;
                
                // Update sync rate display
                if (this.syncCount % 10 === 0) {
                    this.syncRate = Math.round(10000 / (now - (this.lastSyncTime - 1000)));
                }
            }
        } catch (error) {
            this.logger.log(`Camera sync error: ${error.message}`, 'error');
        }
    }
    
    getSyncRate() {
        return this.syncEnabled ? this.syncRate : 0;
    }
}

// Export utilities to global scope
window.MatrixUtils = MatrixUtils;
window.ShaderUtils = ShaderUtils;
window.GeometryUtils = GeometryUtils;
window.CameraController = CameraController;
window.SimpleWebGLRenderer = SimpleWebGLRenderer;
window.MouseControls = MouseControls;
window.CameraSyncManager = CameraSyncManager;

// WebGL utilities module loaded successfully