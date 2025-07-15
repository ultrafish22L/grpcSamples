/**
 * WebGL Renderer Utility
 * Enhanced WebGL rendering for the viewport
 */

class WebGLRenderer {
    constructor(canvas) {
        this.canvas = canvas;
        this.gl = null;
        this.programs = new Map();
        this.buffers = new Map();
        this.textures = new Map();
        this.camera = {
            position: [0, 0, 5],
            target: [0, 0, 0],
            up: [0, 1, 0],
            fov: 45,
            near: 0.1,
            far: 1000
        };
        
        this.initialize();
    }
    
    initialize() {
        this.gl = this.canvas.getContext('webgl') || this.canvas.getContext('experimental-webgl');
        
        if (!this.gl) {
            throw new Error('WebGL not supported');
        }
        
        // Setup WebGL state
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.enable(this.gl.CULL_FACE);
        this.gl.clearColor(0.16, 0.16, 0.16, 1.0);
        
        // Create default shaders
        this.createDefaultShaders();
        
        // Create basic geometry
        this.createBasicGeometry();
        
        console.log('WebGL renderer initialized');
    }
    
    createDefaultShaders() {
        // Basic vertex shader
        const vertexShaderSource = `
            attribute vec3 a_position;
            attribute vec3 a_normal;
            attribute vec2 a_texCoord;
            
            uniform mat4 u_modelMatrix;
            uniform mat4 u_viewMatrix;
            uniform mat4 u_projectionMatrix;
            uniform mat3 u_normalMatrix;
            
            varying vec3 v_normal;
            varying vec2 v_texCoord;
            varying vec3 v_worldPosition;
            
            void main() {
                vec4 worldPosition = u_modelMatrix * vec4(a_position, 1.0);
                v_worldPosition = worldPosition.xyz;
                v_normal = u_normalMatrix * a_normal;
                v_texCoord = a_texCoord;
                
                gl_Position = u_projectionMatrix * u_viewMatrix * worldPosition;
            }
        `;
        
        // Basic fragment shader
        const fragmentShaderSource = `
            precision mediump float;
            
            varying vec3 v_normal;
            varying vec2 v_texCoord;
            varying vec3 v_worldPosition;
            
            uniform vec3 u_lightPosition;
            uniform vec3 u_lightColor;
            uniform vec3 u_materialColor;
            uniform float u_materialShininess;
            uniform vec3 u_cameraPosition;
            
            void main() {
                vec3 normal = normalize(v_normal);
                vec3 lightDir = normalize(u_lightPosition - v_worldPosition);
                vec3 viewDir = normalize(u_cameraPosition - v_worldPosition);
                vec3 reflectDir = reflect(-lightDir, normal);
                
                // Ambient
                vec3 ambient = 0.1 * u_lightColor;
                
                // Diffuse
                float diff = max(dot(normal, lightDir), 0.0);
                vec3 diffuse = diff * u_lightColor;
                
                // Specular
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_materialShininess);
                vec3 specular = spec * u_lightColor;
                
                vec3 result = (ambient + diffuse + specular) * u_materialColor;
                gl_FragColor = vec4(result, 1.0);
            }
        `;
        
        const program = this.createShaderProgram(vertexShaderSource, fragmentShaderSource);
        this.programs.set('basic', program);
    }
    
    createShaderProgram(vertexSource, fragmentSource) {
        const vertexShader = this.createShader(this.gl.VERTEX_SHADER, vertexSource);
        const fragmentShader = this.createShader(this.gl.FRAGMENT_SHADER, fragmentSource);
        
        const program = this.gl.createProgram();
        this.gl.attachShader(program, vertexShader);
        this.gl.attachShader(program, fragmentShader);
        this.gl.linkProgram(program);
        
        if (!this.gl.getProgramParameter(program, this.gl.LINK_STATUS)) {
            console.error('Shader program link error:', this.gl.getProgramInfoLog(program));
            this.gl.deleteProgram(program);
            return null;
        }
        
        return program;
    }
    
    createShader(type, source) {
        const shader = this.gl.createShader(type);
        this.gl.shaderSource(shader, source);
        this.gl.compileShader(shader);
        
        if (!this.gl.getShaderParameter(shader, this.gl.COMPILE_STATUS)) {
            console.error('Shader compile error:', this.gl.getShaderInfoLog(shader));
            this.gl.deleteShader(shader);
            return null;
        }
        
        return shader;
    }
    
    createBasicGeometry() {
        // Create a cube
        const cubeVertices = new Float32Array([
            // Front face
            -1, -1,  1,  0,  0,  1,  0, 0,
             1, -1,  1,  0,  0,  1,  1, 0,
             1,  1,  1,  0,  0,  1,  1, 1,
            -1,  1,  1,  0,  0,  1,  0, 1,
            
            // Back face
            -1, -1, -1,  0,  0, -1,  1, 0,
            -1,  1, -1,  0,  0, -1,  1, 1,
             1,  1, -1,  0,  0, -1,  0, 1,
             1, -1, -1,  0,  0, -1,  0, 0,
            
            // Top face
            -1,  1, -1,  0,  1,  0,  0, 1,
            -1,  1,  1,  0,  1,  0,  0, 0,
             1,  1,  1,  0,  1,  0,  1, 0,
             1,  1, -1,  0,  1,  0,  1, 1,
            
            // Bottom face
            -1, -1, -1,  0, -1,  0,  1, 1,
             1, -1, -1,  0, -1,  0,  0, 1,
             1, -1,  1,  0, -1,  0,  0, 0,
            -1, -1,  1,  0, -1,  0,  1, 0,
            
            // Right face
             1, -1, -1,  1,  0,  0,  1, 0,
             1,  1, -1,  1,  0,  0,  1, 1,
             1,  1,  1,  1,  0,  0,  0, 1,
             1, -1,  1,  1,  0,  0,  0, 0,
            
            // Left face
            -1, -1, -1, -1,  0,  0,  0, 0,
            -1, -1,  1, -1,  0,  0,  1, 0,
            -1,  1,  1, -1,  0,  0,  1, 1,
            -1,  1, -1, -1,  0,  0,  0, 1
        ]);
        
        const cubeIndices = new Uint16Array([
            0,  1,  2,    0,  2,  3,    // front
            4,  5,  6,    4,  6,  7,    // back
            8,  9,  10,   8,  10, 11,   // top
            12, 13, 14,   12, 14, 15,   // bottom
            16, 17, 18,   16, 18, 19,   // right
            20, 21, 22,   20, 22, 23    // left
        ]);
        
        this.createBuffer('cube', cubeVertices, cubeIndices);
    }
    
    createBuffer(name, vertices, indices) {
        const vertexBuffer = this.gl.createBuffer();
        this.gl.bindBuffer(this.gl.ARRAY_BUFFER, vertexBuffer);
        this.gl.bufferData(this.gl.ARRAY_BUFFER, vertices, this.gl.STATIC_DRAW);
        
        const indexBuffer = this.gl.createBuffer();
        this.gl.bindBuffer(this.gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
        this.gl.bufferData(this.gl.ELEMENT_ARRAY_BUFFER, indices, this.gl.STATIC_DRAW);
        
        this.buffers.set(name, {
            vertex: vertexBuffer,
            index: indexBuffer,
            vertexCount: vertices.length / 8, // 8 components per vertex (pos + normal + texCoord)
            indexCount: indices.length
        });
    }
    
    render(objects = []) {
        // Clear canvas
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);
        
        // Update viewport
        this.gl.viewport(0, 0, this.canvas.width, this.canvas.height);
        
        // Calculate matrices
        const projectionMatrix = this.createProjectionMatrix();
        const viewMatrix = this.createViewMatrix();
        
        // Use basic shader program
        const program = this.programs.get('basic');
        if (!program) return;
        
        this.gl.useProgram(program);
        
        // Set uniforms
        this.setUniform(program, 'u_projectionMatrix', projectionMatrix);
        this.setUniform(program, 'u_viewMatrix', viewMatrix);
        this.setUniform(program, 'u_lightPosition', [5, 5, 5]);
        this.setUniform(program, 'u_lightColor', [1, 1, 1]);
        this.setUniform(program, 'u_cameraPosition', this.camera.position);
        
        // Render default cube if no objects provided
        if (objects.length === 0) {
            this.renderCube(program);
        } else {
            objects.forEach(obj => this.renderObject(program, obj));
        }
    }
    
    renderCube(program) {
        const buffer = this.buffers.get('cube');
        if (!buffer) return;
        
        // Model matrix (identity for now)
        const modelMatrix = this.createIdentityMatrix();
        this.setUniform(program, 'u_modelMatrix', modelMatrix);
        this.setUniform(program, 'u_normalMatrix', this.createNormalMatrix(modelMatrix));
        this.setUniform(program, 'u_materialColor', [0.7, 0.7, 0.9]);
        this.setUniform(program, 'u_materialShininess', 32.0);
        
        // Bind buffers and set attributes
        this.gl.bindBuffer(this.gl.ARRAY_BUFFER, buffer.vertex);
        this.gl.bindBuffer(this.gl.ELEMENT_ARRAY_BUFFER, buffer.index);
        
        const stride = 8 * 4; // 8 floats * 4 bytes
        
        // Position attribute
        const positionLocation = this.gl.getAttribLocation(program, 'a_position');
        this.gl.enableVertexAttribArray(positionLocation);
        this.gl.vertexAttribPointer(positionLocation, 3, this.gl.FLOAT, false, stride, 0);
        
        // Normal attribute
        const normalLocation = this.gl.getAttribLocation(program, 'a_normal');
        this.gl.enableVertexAttribArray(normalLocation);
        this.gl.vertexAttribPointer(normalLocation, 3, this.gl.FLOAT, false, stride, 3 * 4);
        
        // Texture coordinate attribute
        const texCoordLocation = this.gl.getAttribLocation(program, 'a_texCoord');
        this.gl.enableVertexAttribArray(texCoordLocation);
        this.gl.vertexAttribPointer(texCoordLocation, 2, this.gl.FLOAT, false, stride, 6 * 4);
        
        // Draw
        this.gl.drawElements(this.gl.TRIANGLES, buffer.indexCount, this.gl.UNSIGNED_SHORT, 0);
    }
    
    renderObject(program, object) {
        // TODO: Implement object rendering
        console.log('Rendering object:', object);
    }
    
    setUniform(program, name, value) {
        const location = this.gl.getUniformLocation(program, name);
        if (!location) return;
        
        if (Array.isArray(value)) {
            if (value.length === 16) {
                this.gl.uniformMatrix4fv(location, false, value);
            } else if (value.length === 9) {
                this.gl.uniformMatrix3fv(location, false, value);
            } else if (value.length === 3) {
                this.gl.uniform3fv(location, value);
            } else if (value.length === 2) {
                this.gl.uniform2fv(location, value);
            }
        } else {
            this.gl.uniform1f(location, value);
        }
    }
    
    createProjectionMatrix() {
        const aspect = this.canvas.width / this.canvas.height;
        const fovRadians = this.camera.fov * Math.PI / 180;
        
        return this.perspective(fovRadians, aspect, this.camera.near, this.camera.far);
    }
    
    createViewMatrix() {
        return this.lookAt(this.camera.position, this.camera.target, this.camera.up);
    }
    
    createIdentityMatrix() {
        return new Float32Array([
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ]);
    }
    
    createNormalMatrix(modelMatrix) {
        // Extract 3x3 matrix and invert/transpose
        const m = modelMatrix;
        return new Float32Array([
            m[0], m[1], m[2],
            m[4], m[5], m[6],
            m[8], m[9], m[10]
        ]);
    }
    
    perspective(fov, aspect, near, far) {
        const f = Math.tan(Math.PI * 0.5 - 0.5 * fov);
        const rangeInv = 1.0 / (near - far);
        
        return new Float32Array([
            f / aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (near + far) * rangeInv, -1,
            0, 0, near * far * rangeInv * 2, 0
        ]);
    }
    
    lookAt(eye, target, up) {
        const zAxis = this.normalize(this.subtract(eye, target));
        const xAxis = this.normalize(this.cross(up, zAxis));
        const yAxis = this.normalize(this.cross(zAxis, xAxis));
        
        return new Float32Array([
            xAxis[0], xAxis[1], xAxis[2], 0,
            yAxis[0], yAxis[1], yAxis[2], 0,
            zAxis[0], zAxis[1], zAxis[2], 0,
            eye[0], eye[1], eye[2], 1
        ]);
    }
    
    normalize(v) {
        const length = Math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        return length > 0 ? [v[0] / length, v[1] / length, v[2] / length] : [0, 0, 0];
    }
    
    subtract(a, b) {
        return [a[0] - b[0], a[1] - b[1], a[2] - b[2]];
    }
    
    cross(a, b) {
        return [
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]
        ];
    }
    
    updateCamera(position, target, up) {
        this.camera.position = position || this.camera.position;
        this.camera.target = target || this.camera.target;
        this.camera.up = up || this.camera.up;
    }
    
    resize(width, height) {
        this.canvas.width = width;
        this.canvas.height = height;
        this.gl.viewport(0, 0, width, height);
    }
    
    destroy() {
        // Clean up WebGL resources
        this.programs.forEach(program => {
            this.gl.deleteProgram(program);
        });
        
        this.buffers.forEach(buffer => {
            this.gl.deleteBuffer(buffer.vertex);
            this.gl.deleteBuffer(buffer.index);
        });
        
        this.textures.forEach(texture => {
            this.gl.deleteTexture(texture);
        });
        
        this.programs.clear();
        this.buffers.clear();
        this.textures.clear();
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = WebGLRenderer;
} else if (typeof window !== 'undefined') {
    window.WebGLRenderer = WebGLRenderer;
}