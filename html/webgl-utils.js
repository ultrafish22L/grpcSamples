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

/**
 * Simple WebGL Renderer for 3D visualization
 * Simplified version that works with the grpc_test.html connection pattern
 */
class SimpleWebGLRenderer {
    constructor(gl, logger) {
        this.gl = gl;
        this.logger = logger;
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
    }

    init() {
        const gl = this.gl;
        
        // Simple WebGL 1.0 compatible shaders
        const vertexShaderSource = `
            attribute vec4 aVertexPosition;
            attribute vec3 aVertexNormal;
            
            uniform mat4 uModelViewMatrix;
            uniform mat4 uProjectionMatrix;
            uniform mat4 uNormalMatrix;
            
            varying vec3 vNormal;
            varying vec3 vPosition;
            
            void main() {
                gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
                vNormal = (uNormalMatrix * vec4(aVertexNormal, 0.0)).xyz;
                vPosition = (uModelViewMatrix * aVertexPosition).xyz;
            }
        `;
        
        const fragmentShaderSource = `
            precision mediump float;
            
            varying vec3 vNormal;
            varying vec3 vPosition;
            
            void main() {
                vec3 normal = normalize(vNormal);
                vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
                float diff = max(dot(normal, lightDir), 0.0);
                
                vec3 color = vec3(0.2, 0.6, 1.0);
                vec3 ambient = color * 0.3;
                vec3 diffuse = color * diff * 0.7;
                
                gl_FragColor = vec4(ambient + diffuse, 1.0);
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
                vertexNormal: gl.getAttribLocation(this.program, 'aVertexNormal'),
            },
            uniformLocations: {
                projectionMatrix: gl.getUniformLocation(this.program, 'uProjectionMatrix'),
                modelViewMatrix: gl.getUniformLocation(this.program, 'uModelViewMatrix'),
                normalMatrix: gl.getUniformLocation(this.program, 'uNormalMatrix'),
            },
        };
        
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
        
        this.buffers.normal = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.buffers.normal);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
        
        this.buffers.indices = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.buffers.indices);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
        
        this.indexCount = indices.length;
    }

    updateProjection(width, height) {
        this.projectionMatrix = MatrixUtils.createPerspectiveMatrix(
            this.camera.fov * Math.PI / 180, 
            width / height, 
            0.1, 
            100.0
        );
    }

    render() {
        const gl = this.gl;
        
        // Clear canvas
        gl.clearColor(0.1, 0.1, 0.1, 1.0);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        
        // Use shader program
        gl.useProgram(this.program);
        
        // Create model-view matrix
        const modelViewMatrix = MatrixUtils.createLookAtMatrix(
            this.camera.position, 
            this.camera.target, 
            this.camera.up
        );
        
        // Apply rotation and zoom
        MatrixUtils.rotateMatrix(modelViewMatrix, this.rotation.x, [1, 0, 0]);
        MatrixUtils.rotateMatrix(modelViewMatrix, this.rotation.y, [0, 1, 0]);
        MatrixUtils.scaleMatrix(modelViewMatrix, [this.zoom, this.zoom, this.zoom]);
        
        // Create normal matrix
        const normalMatrix = MatrixUtils.invertMatrix(modelViewMatrix);
        MatrixUtils.transposeMatrix(normalMatrix);
        
        // Set uniforms
        gl.uniformMatrix4fv(this.programInfo.uniformLocations.projectionMatrix, false, this.projectionMatrix);
        gl.uniformMatrix4fv(this.programInfo.uniformLocations.modelViewMatrix, false, modelViewMatrix);
        gl.uniformMatrix4fv(this.programInfo.uniformLocations.normalMatrix, false, normalMatrix);
        
        // Bind position buffer
        gl.bindBuffer(gl.ARRAY_BUFFER, this.buffers.position);
        gl.vertexAttribPointer(this.programInfo.attribLocations.vertexPosition, 3, gl.FLOAT, false, 0, 0);
        gl.enableVertexAttribArray(this.programInfo.attribLocations.vertexPosition);
        
        // Bind normal buffer
        gl.bindBuffer(gl.ARRAY_BUFFER, this.buffers.normal);
        gl.vertexAttribPointer(this.programInfo.attribLocations.vertexNormal, 3, gl.FLOAT, false, 0, 0);
        gl.enableVertexAttribArray(this.programInfo.attribLocations.vertexNormal);
        
        // Bind index buffer and draw
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.buffers.indices);
        gl.drawElements(gl.TRIANGLES, this.indexCount, gl.UNSIGNED_SHORT, 0);
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
        // TODO: Implement mesh loading from Octane data
        this.logger.log('Mesh loading not yet implemented', 'info');
    }

    loadModelFile(file) {
        // TODO: Implement model file loading
        this.logger.log('Model file loading not yet implemented', 'info');
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

console.log('WebGL utilities loaded successfully');