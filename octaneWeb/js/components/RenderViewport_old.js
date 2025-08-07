/**
 * Render Viewport Component
 * 2D image display area with mouse-controlled camera sync to live Octane
 * Replaces WebGL viewport with simple image display for future render output
 */

class RenderViewport extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        // 2D viewport elements
        this.viewport = null;
        this.imageDisplay = null;
        this.statusOverlay = null;
        
        // Camera system for LiveLink sync
        this.camera = {
            radius: 20.0,      // Distance from target
            theta: 0.0,        // Horizontal rotation (radians)
            phi: 0.0,          // Vertical rotation (radians)
            center: [0.0, 0.0, 0.0],  // Look-at target
            fov: 45.0,         // Field of view
            sensitivity: 0.01,  // Mouse sensitivity
            zoomSpeed: 0.1     // Wheel zoom speed
        };
        
        // Mouse interaction state
        this.mouse = {
            dragging: false,
            panning: false,
            lastX: 0,
            lastY: 0
        };
        
        // LiveLink sync state
        this.syncEnabled = true;
        this.lastSyncTime = 0;
        this.syncThrottle = 50; // Minimum ms between sync calls
        this.syncCount = 0;
        
        console.log('📷 Camera initialized for LiveLink sync:', {
            radius: this.camera.radius,
            theta: this.camera.theta,
            phi: this.camera.phi,
            center: this.camera.center,
            fov: this.camera.fov
        });
    }
    
    async onInitialize() {
        console.log('🎯 Initializing 2D Render Viewport with LiveLink camera sync...');
        
        try {
            // Create 2D viewport container
            await this.create2DViewport();
            
            // Get initial camera state from Octane
            await this.syncFromOctane();
            
            // Setup mouse event handlers
            this.setupEventHandlers();
            
            console.log('✅ RenderViewport initialized successfully');
            
        } catch (error) {
            console.error('❌ Failed to initialize RenderViewport:', error);
            this.showError('Failed to initialize render viewport', error.message);
        }
    }
    
    /**
     * Create 2D viewport for image display and mouse interaction
     */
    async create2DViewport() {
        // Remove any existing content
        this.element.innerHTML = '';
        
        // Create main viewport container
        this.viewport = document.createElement('div');
        this.viewport.className = 'render-viewport-2d';
        this.viewport.style.cssText = `
            width: 100%;
            height: 100%;
            position: relative;
            background: #1a1a1a;
            border: 1px solid #333;
            cursor: grab;
            overflow: hidden;
            display: flex;
            align-items: center;
            justify-content: center;
        `;
        
        // Create image display area
        this.imageDisplay = document.createElement('div');
        this.imageDisplay.className = 'image-display';
        this.imageDisplay.style.cssText = `
            width: 100%;
            height: 100%;
            background: #2a2a2a;
            display: flex;
            align-items: center;
            justify-content: center;
            flex-direction: column;
            color: #888;
            font-family: 'Segoe UI', sans-serif;
        `;
        
        // Create placeholder content
        const icon = document.createElement('div');
        icon.style.cssText = `
            font-size: 48px;
            margin-bottom: 16px;
            opacity: 0.6;
        `;
        icon.textContent = '🖼️';
        
        const title = document.createElement('div');
        title.style.cssText = `
            font-size: 16px;
            font-weight: 500;
            margin-bottom: 8px;
            color: #aaa;
        `;
        title.textContent = 'Render Viewport';
        
        const subtitle = document.createElement('div');
        subtitle.style.cssText = `
            font-size: 12px;
            opacity: 0.7;
            text-align: center;
            line-height: 1.4;
        `;
        subtitle.innerHTML = 'Mouse drag to orbit camera<br>Mouse wheel to zoom<br>Live sync with Octane';
        
        this.imageDisplay.appendChild(icon);
        this.imageDisplay.appendChild(title);
        this.imageDisplay.appendChild(subtitle);
        
        // Create status overlay
        this.statusOverlay = document.createElement('div');
        this.statusOverlay.className = 'viewport-status';
        this.statusOverlay.style.cssText = `
            position: absolute;
            top: 8px;
            left: 8px;
            background: rgba(0, 0, 0, 0.7);
            color: #fff;
            padding: 4px 8px;
            border-radius: 4px;
            font-size: 11px;
            font-family: monospace;
            pointer-events: none;
        `;
        this.statusOverlay.textContent = 'LiveLink: Ready';
        
        // Assemble viewport
        this.viewport.appendChild(this.imageDisplay);
        this.viewport.appendChild(this.statusOverlay);
        this.element.appendChild(this.viewport);
        
        console.log('✅ 2D viewport created');
    }
        
        console.log('🖼️ Canvas element found:', {
            id: this.canvas.id,
            className: this.canvas.className,
            tagName: this.canvas.tagName,
            clientWidth: this.canvas.clientWidth,
            clientHeight: this.canvas.clientHeight,
            parentElement: this.canvas.parentElement?.className
        });
        
        // CRITICAL FIX: Remove and recreate canvas with explicit dimensions
        console.log('🔧 Removing existing canvas and creating new one...');
        if (this.canvas && this.canvas.parentElement) {
            this.canvas.parentElement.removeChild(this.canvas);
        }
        
        // Create new canvas with FORCED explicit dimensions
        this.canvas = document.createElement('canvas');
        this.canvas.id = 'render-viewport';
        this.canvas.className = 'render-viewport';
        
        // CRITICAL: Force explicit pixel dimensions - bypass CSS layout entirely
        this.canvas.width = 760;
        this.canvas.height = 297;
        this.canvas.style.width = '760px';
        this.canvas.style.height = '297px';
        this.canvas.style.display = 'block';
        this.canvas.style.position = 'relative';
        // this.canvas.style.border = '2px solid red'; // DEBUG: Make canvas boundaries visible
        this.canvas.style.backgroundColor = 'cyan'; // DEBUG: Bright background to test visibility
        
        this.element.appendChild(this.canvas);
        
        console.log('🖼️ Canvas after recreation:', {
            clientWidth: this.canvas.clientWidth,
            clientHeight: this.canvas.clientHeight,
            offsetWidth: this.canvas.offsetWidth,
            offsetHeight: this.canvas.offsetHeight,
            width: this.canvas.width,
            height: this.canvas.height
        });
        
        // CRITICAL: Force canvas CSS dimensions to match WebGL dimensions
        console.log('🔧 Forcing canvas CSS dimensions...');
        this.canvas.style.setProperty('width', '760px', 'important');
        this.canvas.style.setProperty('height', '297px', 'important');
        this.canvas.style.setProperty('display', 'block', 'important');
        this.canvas.style.setProperty('position', 'relative', 'important');
        this.canvas.style.setProperty('min-width', '760px', 'important');
        this.canvas.style.setProperty('min-height', '297px', 'important');
        this.canvas.style.setProperty('max-width', '760px', 'important');
        this.canvas.style.setProperty('max-height', '297px', 'important');
        this.canvas.style.setProperty('box-sizing', 'border-box', 'important');
        
        // Force layout recalculation multiple times
        this.canvas.offsetHeight; // Force reflow
        this.canvas.getBoundingClientRect(); // Force layout
        
        // CRITICAL: Try to force the canvas to recognize its CSS dimensions
        setTimeout(() => {
            this.canvas.style.width = '760px';
            this.canvas.style.height = '297px';
            this.canvas.offsetHeight; // Force reflow again
        }, 0);
        
        console.log('🖼️ Canvas after forced CSS dimensions:', {
            clientWidth: this.canvas.clientWidth,
            clientHeight: this.canvas.clientHeight,
            offsetWidth: this.canvas.offsetWidth,
            offsetHeight: this.canvas.offsetHeight,
            computedStyle: window.getComputedStyle(this.canvas).width + ' x ' + window.getComputedStyle(this.canvas).height
        });
        
        // CRITICAL: Initialize WebGL immediately after canvas creation
        console.log('🔧 Initializing WebGL on new canvas...');
        await this.initWebGL();
        console.log('✅ WebGL initialized on new canvas');
        
        // Wait for DOM layout to complete, then size canvas properly
        setTimeout(() => {
            this.resizeCanvas();
        }, 100);
        
        // CRITICAL FIX: Force canvas to have visible dimensions after DOM insertion
        setTimeout(() => {
            console.log('🔧 Forcing canvas dimensions after DOM insertion...');
            this.canvas.style.width = '760px !important';
            this.canvas.style.height = '380px !important';
            this.canvas.style.minWidth = '760px';
            this.canvas.style.minHeight = '380px';
            this.canvas.style.maxWidth = '760px';
            this.canvas.style.maxHeight = '380px';
            this.canvas.style.display = 'block !important';
            this.canvas.style.visibility = 'visible';
            this.canvas.style.opacity = '1';
            
            console.log('🖼️ Canvas after forced dimensions (delayed):', {
                clientWidth: this.canvas.clientWidth,
                clientHeight: this.canvas.clientHeight,
                offsetWidth: this.canvas.offsetWidth,
                offsetHeight: this.canvas.offsetHeight,
                computedStyle: window.getComputedStyle(this.canvas).width + ' x ' + window.getComputedStyle(this.canvas).height
            });
        }, 100);
        
        try {
            // Load teapot geometry (WebGL already initialized above)
            await this.loadTeapotGeometry();
            
            // Setup event handlers
            this.setupEventHandlers();
            
            // Start rendering loop
            this.startRenderLoop();
            
            console.log('✅ RenderViewport initialized successfully');
            
        } catch (error) {
            console.error('❌ Failed to initialize RenderViewport:', error);
            this.showError('Failed to initialize 3D viewport', error.message);
        }
    }
    
    /**
     * Initialize WebGL context and create shaders
     */
    async initWebGL() {
        // Check WebGL availability with explicit context attributes
        // CRITICAL FIX: Disable alpha to make WebGL content visible
        const contextAttributes = {
            alpha: false,  // CRITICAL: Disable alpha to fix invisible WebGL content
            premultipliedAlpha: false,
            preserveDrawingBuffer: true,
            antialias: true
        };
        const webgl2 = this.canvas.getContext('webgl2', contextAttributes);
        const webgl1 = this.canvas.getContext('webgl', contextAttributes);
        
        console.log('🔍 WebGL Support Check:');
        console.log('WebGL 2.0 available:', !!webgl2);
        console.log('WebGL 1.0 available:', !!webgl1);
        console.log('🎯 Context attributes:', contextAttributes);
        
        // Try WebGL 2.0 first, fall back to WebGL 1.0
        this.gl = webgl2 || webgl1;
        if (!this.gl) {
            throw new Error('WebGL not supported');
        }
        
        const version = this.gl instanceof WebGL2RenderingContext ? '2.0' : '1.0';
        console.log(`✅ Using WebGL ${version}`);
        
        // Configure WebGL state
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.enable(this.gl.CULL_FACE);
        this.gl.cullFace(this.gl.BACK);
        this.gl.clearColor(1.0, 0.0, 1.0, 1.0); // BRIGHT MAGENTA background to test WebGL
        console.log('🎨 WebGL clear color set to BRIGHT MAGENTA (1.0, 0.0, 1.0, 1.0)');
        
        // Create shaders
        await this.createShaders();
        
        // Set up viewport
        this.resizeCanvas();
        
        // CRITICAL: Force WebGL viewport to match canvas internal dimensions (not client dimensions)
        console.log('🔧 Forcing WebGL viewport to match canvas internal dimensions...');
        this.gl.viewport(0, 0, 760, 297); // Force to internal dimensions, not client dimensions
        console.log(`🎯 WebGL viewport forced to: 0,0,760,297 (internal dimensions)`);
        
        console.log('✅ WebGL initialization complete');
    }
    
    /**
     * Create shader programs for teapot rendering
     */
    async createShaders() {
        const gl = this.gl;
        
        try {
            // Main teapot shader
            const vertexSource = `
                attribute vec3 aPos;
                attribute vec3 aNormal;
                attribute vec3 aColor;
                
                uniform mat4 uModel;
                uniform mat4 uView;
                uniform mat4 uProjection;
                uniform mat3 uNormalMatrix;
                
                varying vec3 vNormal;
                varying vec3 vColor;
                varying vec3 vFragPos;
                
                void main() {
                    vec4 worldPos = uModel * vec4(aPos, 1.0);
                    vFragPos = worldPos.xyz;
                    vNormal = normalize(uNormalMatrix * aNormal);
                    vColor = aColor;
                    
                    gl_Position = uProjection * uView * worldPos;
                }
            `;
            
            const fragmentSource = `
                precision mediump float;
                
                varying vec3 vNormal;
                varying vec3 vColor;
                varying vec3 vFragPos;
                
                uniform vec3 uLightPos;
                uniform vec3 uViewPos;
                uniform float uTime;
                
                void main() {
                    // Basic Phong lighting
                    vec3 lightColor = vec3(1.0, 1.0, 1.0);
                    vec3 ambient = 0.3 * lightColor;
                    
                    vec3 norm = normalize(vNormal);
                    vec3 lightDir = normalize(uLightPos - vFragPos);
                    float diff = max(dot(norm, lightDir), 0.0);
                    vec3 diffuse = diff * lightColor;
                    
                    vec3 viewDir = normalize(uViewPos - vFragPos);
                    vec3 reflectDir = reflect(-lightDir, norm);
                    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
                    vec3 specular = 0.5 * spec * lightColor;
                    
                    // Use teapot color with lighting
                    vec3 objectColor = vec3(0.8, 0.6, 0.4); // Teapot bronze color
                    vec3 result = (ambient + diffuse + specular) * objectColor;
                    
                    gl_FragColor = vec4(result, 1.0);
                }
            `;
            
            const vertexShader = ShaderUtils.createShader(gl, gl.VERTEX_SHADER, vertexSource);
            const fragmentShader = ShaderUtils.createShader(gl, gl.FRAGMENT_SHADER, fragmentSource);
            this.shaderProgram = ShaderUtils.createProgram(gl, vertexShader, fragmentShader);
            
            // Clean up individual shaders
            gl.deleteShader(vertexShader);
            gl.deleteShader(fragmentShader);
            
            console.log('✅ Shaders created successfully');
            
        } catch (error) {
            console.error('❌ Shader creation failed:', error);
            throw new Error(`Shader creation failed: ${error.message}`);
        }
    }
    
    /**
     * Resize canvas to match container - similar to html/index.html approach
     */
    resizeCanvas() {
        if (!this.canvas || !this.element) return;
        
        console.log('🔧 Resizing canvas to match container...');
        
        const container = this.element;
        const rect = container.getBoundingClientRect();
        
        // Get container dimensions
        const width = container.clientWidth || rect.width;
        const height = container.clientHeight || rect.height;
        
        console.log('🖼️ Container dimensions:', {
            clientWidth: container.clientWidth,
            clientHeight: container.clientHeight,
            rectWidth: rect.width,
            rectHeight: rect.height,
            finalWidth: width,
            finalHeight: height
        });
        
        // Force canvas to have valid dimensions if container has zero size
        if (width <= 0 || height <= 0) {
            console.log('🔧 Container has zero dimensions, forcing canvas to 760x297...');
            width = 760;
            height = 297;
        }
        
        // Always resize if dimensions are different
        if (this.canvas.width !== width || this.canvas.height !== height) {
            console.log(`🔄 Resizing canvas from ${this.canvas.width}x${this.canvas.height} to ${width}x${height}`);
            
            // Set canvas internal dimensions
            this.canvas.width = width;
            this.canvas.height = height;
            
            // CRITICAL: Force CSS dimensions to match internal dimensions
            this.canvas.style.width = width + 'px !important';
            this.canvas.style.height = height + 'px !important';
            this.canvas.style.minWidth = width + 'px';
            this.canvas.style.minHeight = height + 'px';
            this.canvas.style.maxWidth = width + 'px';
            this.canvas.style.maxHeight = height + 'px';
            
            // Update WebGL viewport if context exists - FORCE to internal dimensions
            if (this.gl) {
                this.gl.viewport(0, 0, 760, 297); // Force to internal dimensions
                console.log(`🎯 WebGL viewport updated to: 760x297 (forced internal)`);
            }
            
            console.log('🖼️ Canvas after resize:', {
                width: this.canvas.width,
                height: this.canvas.height,
                clientWidth: this.canvas.clientWidth,
                clientHeight: this.canvas.clientHeight,
                styleWidth: this.canvas.style.width,
                styleHeight: this.canvas.style.height
            });
        } else {
            console.log('🔍 Canvas resize skipped - dimensions unchanged');
        }
    }

    /**
     * Load teapot.obj geometry from assets
     */
    async loadTeapotGeometry() {
        try {
            console.log('📦 Loading teapot.obj...');
            
            const response = await fetch('./assets/teapot.obj');
            if (!response.ok) {
                throw new Error(`Failed to load teapot.obj: ${response.status}`);
            }
            
            const objText = await response.text();
            const geometry = this.parseObjFile(objText);
            
            console.log(`✅ Teapot loaded: ${geometry.vertices.length / 9} vertices, ${geometry.indices.length} indices`);
            
            // Create WebGL buffers
            this.createTeapotBuffers(geometry);
            
        } catch (error) {
            console.error('❌ Failed to load teapot geometry:', error);
            console.error('❌ Error details:', error.message, error.stack);
            // Fallback to a simple cube if teapot loading fails
            console.log('🔄 Falling back to cube geometry...');
            const cubeGeometry = this.createCubeGeometry();
            this.createTeapotBuffers(cubeGeometry);
        }
    }
    
    /**
     * Create a simple cube geometry as fallback
     */
    createCubeGeometry() {
        // Cube vertices (position, normal, color)
        const vertices = new Float32Array([
            // Front face
            -1.0, -1.0,  1.0,   0.0,  0.0,  1.0,   1.0, 0.5, 0.0,
             1.0, -1.0,  1.0,   0.0,  0.0,  1.0,   1.0, 0.5, 0.0,
             1.0,  1.0,  1.0,   0.0,  0.0,  1.0,   1.0, 0.5, 0.0,
            -1.0,  1.0,  1.0,   0.0,  0.0,  1.0,   1.0, 0.5, 0.0,
            
            // Back face
            -1.0, -1.0, -1.0,   0.0,  0.0, -1.0,   0.5, 1.0, 0.0,
            -1.0,  1.0, -1.0,   0.0,  0.0, -1.0,   0.5, 1.0, 0.0,
             1.0,  1.0, -1.0,   0.0,  0.0, -1.0,   0.5, 1.0, 0.0,
             1.0, -1.0, -1.0,   0.0,  0.0, -1.0,   0.5, 1.0, 0.0,
            
            // Top face
            -1.0,  1.0, -1.0,   0.0,  1.0,  0.0,   0.0, 1.0, 0.5,
            -1.0,  1.0,  1.0,   0.0,  1.0,  0.0,   0.0, 1.0, 0.5,
             1.0,  1.0,  1.0,   0.0,  1.0,  0.0,   0.0, 1.0, 0.5,
             1.0,  1.0, -1.0,   0.0,  1.0,  0.0,   0.0, 1.0, 0.5,
            
            // Bottom face
            -1.0, -1.0, -1.0,   0.0, -1.0,  0.0,   1.0, 0.0, 0.5,
             1.0, -1.0, -1.0,   0.0, -1.0,  0.0,   1.0, 0.0, 0.5,
             1.0, -1.0,  1.0,   0.0, -1.0,  0.0,   1.0, 0.0, 0.5,
            -1.0, -1.0,  1.0,   0.0, -1.0,  0.0,   1.0, 0.0, 0.5,
            
            // Right face
             1.0, -1.0, -1.0,   1.0,  0.0,  0.0,   0.5, 0.0, 1.0,
             1.0,  1.0, -1.0,   1.0,  0.0,  0.0,   0.5, 0.0, 1.0,
             1.0,  1.0,  1.0,   1.0,  0.0,  0.0,   0.5, 0.0, 1.0,
             1.0, -1.0,  1.0,   1.0,  0.0,  0.0,   0.5, 0.0, 1.0,
            
            // Left face
            -1.0, -1.0, -1.0,  -1.0,  0.0,  0.0,   1.0, 1.0, 0.5,
            -1.0, -1.0,  1.0,  -1.0,  0.0,  0.0,   1.0, 1.0, 0.5,
            -1.0,  1.0,  1.0,  -1.0,  0.0,  0.0,   1.0, 1.0, 0.5,
            -1.0,  1.0, -1.0,  -1.0,  0.0,  0.0,   1.0, 1.0, 0.5
        ]);
        
        // Cube indices
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
    
    /**
     * Parse OBJ file format and convert to WebGL-ready geometry
     */
    parseObjFile(objText) {
        const lines = objText.split('\n');
        const positions = [];
        const normals = [];
        const faces = [];
        
        // Parse OBJ file
        for (const line of lines) {
            const parts = line.trim().split(/\s+/);
            
            if (parts[0] === 'v') {
                // Vertex position
                positions.push([
                    parseFloat(parts[1]),
                    parseFloat(parts[2]),
                    parseFloat(parts[3])
                ]);
            } else if (parts[0] === 'vn') {
                // Vertex normal
                normals.push([
                    parseFloat(parts[1]),
                    parseFloat(parts[2]),
                    parseFloat(parts[3])
                ]);
            } else if (parts[0] === 'f') {
                // Face (assuming triangles)
                const face = [];
                for (let i = 1; i < parts.length; i++) {
                    const indices = parts[i].split('/');
                    face.push({
                        position: parseInt(indices[0]) - 1, // OBJ is 1-indexed
                        normal: indices[2] ? parseInt(indices[2]) - 1 : -1
                    });
                }
                faces.push(face);
            }
        }
        
        // Convert to interleaved vertex format (position, normal, color)
        const vertices = [];
        const indices = [];
        let vertexIndex = 0;
        
        for (const face of faces) {
            // Convert face to triangles (assuming quads or triangles)
            if (face.length === 3) {
                // Triangle
                for (const vertex of face) {
                    const pos = positions[vertex.position];
                    const norm = vertex.normal >= 0 ? normals[vertex.normal] : [0, 1, 0];
                    
                    // Position
                    vertices.push(pos[0], pos[1], pos[2]);
                    // Normal
                    vertices.push(norm[0], norm[1], norm[2]);
                    // Color (bronze teapot color)
                    vertices.push(0.8, 0.6, 0.4);
                    
                    indices.push(vertexIndex++);
                }
            } else if (face.length === 4) {
                // Quad - split into two triangles
                const quadIndices = [0, 1, 2, 0, 2, 3];
                for (const i of quadIndices) {
                    const vertex = face[i];
                    const pos = positions[vertex.position];
                    const norm = vertex.normal >= 0 ? normals[vertex.normal] : [0, 1, 0];
                    
                    // Position
                    vertices.push(pos[0], pos[1], pos[2]);
                    // Normal
                    vertices.push(norm[0], norm[1], norm[2]);
                    // Color
                    vertices.push(0.8, 0.6, 0.4);
                    
                    indices.push(vertexIndex++);
                }
            }
        }
        
        return {
            vertices: new Float32Array(vertices),
            indices: new Uint16Array(indices)
        };
    }
    
    /**
     * Create WebGL buffers for teapot geometry
     */
    createTeapotBuffers(geometry) {
        const gl = this.gl;
        const isWebGL2 = gl instanceof WebGL2RenderingContext;
        
        this.teapotGeometry = geometry;
        
        if (isWebGL2) {
            // WebGL 2.0 with VAOs
            this.teapotVAO = gl.createVertexArray();
            gl.bindVertexArray(this.teapotVAO);
        }
        
        // Vertex buffer (position, normal, color)
        this.teapotVertexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.teapotVertexBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, geometry.vertices, gl.STATIC_DRAW);
        
        if (isWebGL2) {
            // Position attribute (location 0)
            gl.vertexAttribPointer(0, 3, gl.FLOAT, false, 9 * 4, 0);
            gl.enableVertexAttribArray(0);
            
            // Normal attribute (location 1)
            gl.vertexAttribPointer(1, 3, gl.FLOAT, false, 9 * 4, 3 * 4);
            gl.enableVertexAttribArray(1);
            
            // Color attribute (location 2)
            gl.vertexAttribPointer(2, 3, gl.FLOAT, false, 9 * 4, 6 * 4);
            gl.enableVertexAttribArray(2);
        } else {
            // Store attribute locations for WebGL 1.0
            this.aPos = gl.getAttribLocation(this.shaderProgram, 'aPos');
            this.aNormal = gl.getAttribLocation(this.shaderProgram, 'aNormal');
            this.aColor = gl.getAttribLocation(this.shaderProgram, 'aColor');
        }
        
        // Index buffer
        this.teapotIndexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.teapotIndexBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, geometry.indices, gl.STATIC_DRAW);
        
        console.log('✅ Teapot buffers created successfully');
    }
    
    /**
     * Setup event handlers for mouse interaction
     */
    setupEventHandlers() {
        // Canvas mouse events
        this.canvas.addEventListener('mousedown', (e) => this.handleMouseDown(e));
        this.canvas.addEventListener('mousemove', (e) => this.handleMouseMove(e));
        this.canvas.addEventListener('mouseup', (e) => this.handleMouseUp(e));
        this.canvas.addEventListener('wheel', (e) => this.handleWheel(e));
        this.canvas.addEventListener('contextmenu', (e) => e.preventDefault());
        
        // Window resize handler
        window.addEventListener('resize', () => {
            this.resizeCanvas();
        });
        
        console.log('✅ Event handlers setup complete');
    }
    
    /**
     * Handle mouse down events
     */
    handleMouseDown(event) {
        this.mouse.dragging = event.button === 0; // Left button
        this.mouse.panning = event.button === 2;  // Right button
        this.mouse.lastX = event.clientX;
        this.mouse.lastY = event.clientY;
        
        console.log('🖱️ Mouse down:', {
            button: event.button,
            dragging: this.mouse.dragging,
            panning: this.mouse.panning,
            x: event.clientX,
            y: event.clientY
        });
        
        if (this.mouse.dragging || this.mouse.panning) {
            this.canvas.style.cursor = this.mouse.panning ? 'move' : 'grabbing';
        }
    }
    
    /**
     * Handle mouse move events
     */
    handleMouseMove(event) {
        if (this.mouse.dragging || this.mouse.panning) {
            const deltaX = event.clientX - this.mouse.lastX;
            const deltaY = event.clientY - this.mouse.lastY;
            
            console.log('🖱️ Mouse move:', {
                deltaX,
                deltaY,
                dragging: this.mouse.dragging,
                panning: this.mouse.panning,
                cameraPosition: this.camera.getPosition()
            });
            
            this.camera.handleMouseMove(deltaX, deltaY, this.mouse.dragging, this.mouse.panning);
            
            this.mouse.lastX = event.clientX;
            this.mouse.lastY = event.clientY;
        }
    }
    
    /**
     * Handle mouse up events
     */
    handleMouseUp(event) {
        this.mouse.dragging = false;
        this.mouse.panning = false;
        this.canvas.style.cursor = 'default';
    }
    
    /**
     * Handle mouse wheel events
     */
    handleWheel(event) {
        event.preventDefault();
        this.camera.handleWheel(event.deltaY);
    }
    
    /**
     * Resize canvas to match container
     */
    resizeCanvas() {
        if (!this.canvas || !this.gl) return;
        
        const rect = this.canvas.parentElement.getBoundingClientRect();
        const displayWidth = rect.width;
        const displayHeight = rect.height;
        
        if (this.canvas.width !== displayWidth || this.canvas.height !== displayHeight) {
            this.canvas.width = displayWidth;
            this.canvas.height = displayHeight;
            this.gl.viewport(0, 0, displayWidth, displayHeight);
        }
    }
    
    /**
     * Start the rendering loop
     */
    startRenderLoop() {
        this.isRendering = true;
        this.lastFrameTime = performance.now();
        this.renderFrame();
    }
    
    /**
     * Stop the rendering loop
     */
    stopRenderLoop() {
        this.isRendering = false;
        if (this.animationFrameId) {
            cancelAnimationFrame(this.animationFrameId);
            this.animationFrameId = null;
        }
    }
    
    /**
     * Main render frame function
     */
    renderFrame() {
        if (!this.isRendering) return;
        
        const currentTime = performance.now();
        const deltaTime = currentTime - this.lastFrameTime;
        this.lastFrameTime = currentTime;
        
        // Update FPS counter
        this.updateFPS(currentTime);
        
        // Render the scene
        this.render(currentTime);
        
        // Schedule next frame
        this.animationFrameId = requestAnimationFrame(() => this.renderFrame());
    }
    
    /**
     * Update FPS counter
     */
    updateFPS(currentTime) {
        this.frameCount++;
        
        if (currentTime - this.lastFpsTime >= 1000) {
            this.currentFps = Math.round((this.frameCount * 1000) / (currentTime - this.lastFpsTime));
            this.frameCount = 0;
            this.lastFpsTime = currentTime;
            
            // Update FPS display in status bar
            const fpsElement = document.querySelector('#fps, .status-right .status-item:last-child span:last-child');
            if (fpsElement) {
                fpsElement.textContent = this.currentFps;
            }
        }
    }
    
    /**
     * Main render function
     */
    render(time) {
        const gl = this.gl;
        if (!gl) return;
        
        // Resize canvas if needed
        this.resizeCanvas();
        
        // Clear the screen
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        
        // Debug: Check if clear color is being applied (every 60 frames)
        if (this.frameCount % 60 === 0) {
            const clearColor = gl.getParameter(gl.COLOR_CLEAR_VALUE);
            console.log('🎨 Clear color applied:', clearColor);
        }
        
        // Debug info every 60 frames
        if (this.frameCount % 60 === 0) {
            console.log(`🖼️ Canvas dimensions: ${this.canvas.width}x${this.canvas.height}, client: ${this.canvas.clientWidth}x${this.canvas.clientHeight}`);
            const viewport = gl.getParameter(gl.VIEWPORT);
            console.log(`🎯 WebGL viewport: ${viewport[0]},${viewport[1]},${viewport[2]},${viewport[3]}`);
        }
        
        // Calculate matrices
        const aspect = this.canvas.width / this.canvas.height;
        const projectionMatrix = MatrixUtils.createPerspectiveMatrix(
            Math.PI / 4, // 45 degrees FOV
            aspect,
            0.1,
            100.0
        );
        
        const viewMatrix = this.camera.getViewMatrix();
        const modelMatrix = MatrixUtils.createIdentityMatrix();
        
        // Render teapot
        this.renderTeapot(projectionMatrix, viewMatrix, modelMatrix, time);
    }
    
    /**
     * Render teapot model
     */
    renderTeapot(projectionMatrix, viewMatrix, modelMatrix, time) {
        const gl = this.gl;
        const isWebGL2 = gl instanceof WebGL2RenderingContext;
        
        gl.useProgram(this.shaderProgram);
        
        if (isWebGL2 && this.teapotVAO) {
            gl.bindVertexArray(this.teapotVAO);
        } else {
            // WebGL 1.0 fallback
            gl.bindBuffer(gl.ARRAY_BUFFER, this.teapotVertexBuffer);
            gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.teapotIndexBuffer);
            
            // Set up attributes
            gl.vertexAttribPointer(this.aPos, 3, gl.FLOAT, false, 9 * 4, 0);
            gl.enableVertexAttribArray(this.aPos);
            
            gl.vertexAttribPointer(this.aNormal, 3, gl.FLOAT, false, 9 * 4, 3 * 4);
            gl.enableVertexAttribArray(this.aNormal);
            
            gl.vertexAttribPointer(this.aColor, 3, gl.FLOAT, false, 9 * 4, 6 * 4);
            gl.enableVertexAttribArray(this.aColor);
        }
        
        // Set uniforms
        const uModel = gl.getUniformLocation(this.shaderProgram, 'uModel');
        const uView = gl.getUniformLocation(this.shaderProgram, 'uView');
        const uProjection = gl.getUniformLocation(this.shaderProgram, 'uProjection');
        const uNormalMatrix = gl.getUniformLocation(this.shaderProgram, 'uNormalMatrix');
        const uLightPos = gl.getUniformLocation(this.shaderProgram, 'uLightPos');
        const uViewPos = gl.getUniformLocation(this.shaderProgram, 'uViewPos');
        const uTime = gl.getUniformLocation(this.shaderProgram, 'uTime');
        
        // Calculate normal matrix (simplified for identity model matrix)
        const normalMatrix = new Float32Array([1, 0, 0, 0, 1, 0, 0, 0, 1]);
        
        gl.uniformMatrix4fv(uModel, false, modelMatrix);
        gl.uniformMatrix4fv(uView, false, viewMatrix);
        gl.uniformMatrix4fv(uProjection, false, projectionMatrix);
        gl.uniformMatrix3fv(uNormalMatrix, false, normalMatrix);
        
        // Lighting
        const cameraPos = this.camera.getPosition();
        gl.uniform3f(uLightPos, cameraPos[0] + 2, cameraPos[1] + 2, cameraPos[2] + 2);
        gl.uniform3f(uViewPos, cameraPos[0], cameraPos[1], cameraPos[2]);
        gl.uniform1f(uTime, time * 0.001);
        
        // Draw teapot
        const indexCount = this.teapotGeometry.indices.length;
        if (indexCount > 0) {
            gl.drawElements(gl.TRIANGLES, indexCount, gl.UNSIGNED_SHORT, 0);
            
            // Debug info every 60 frames
            if (this.frameCount % 60 === 0) {
                console.log(`🎨 Rendered frame ${this.frameCount}: ${indexCount} indices, camera at [${cameraPos[0].toFixed(2)}, ${cameraPos[1].toFixed(2)}, ${cameraPos[2].toFixed(2)}]`);
                console.log(`🔺 Vertex buffer bound: ${gl.getParameter(gl.ARRAY_BUFFER_BINDING) !== null}`);
                console.log(`🔢 Index buffer bound: ${gl.getParameter(gl.ELEMENT_ARRAY_BUFFER_BINDING) !== null}`);
            }
        } else {
            console.warn('⚠️ No geometry to render - indices.length is 0');
        }
    }
    
    /**
     * Show error message in viewport
     */
    showError(title, message) {
        this.element.innerHTML = `
            <div class="viewport-error">
                <div class="error-icon">⚠️</div>
                <div class="error-title">${title}</div>
                <div class="error-message">${message}</div>
            </div>
        `;
    }
    
    /**
     * Handle component resize
     */
    handleResize() {
        this.resizeCanvas();
    }
    
    /**
     * Cleanup when component is destroyed
     */
    onDestroy() {
        this.stopRenderLoop();
        
        if (this.gl) {
            // Clean up WebGL resources
            if (this.teapotVAO) this.gl.deleteVertexArray(this.teapotVAO);
            if (this.teapotVertexBuffer) this.gl.deleteBuffer(this.teapotVertexBuffer);
            if (this.teapotIndexBuffer) this.gl.deleteBuffer(this.teapotIndexBuffer);
            if (this.shaderProgram) this.gl.deleteProgram(this.shaderProgram);
        }
        
        console.log('🧹 RenderViewport cleanup complete');
    }
}