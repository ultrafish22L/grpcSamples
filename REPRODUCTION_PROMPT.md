# OTOY WebGL-Octane LiveLink Sync - Complete Reproduction Prompt

## 🎨 USER EXPERIENCE REQUIREMENTS

### Visual Design Philosophy
Create a **professional 3D rendering application** that matches the aesthetic standards of industry-leading software like Octane Render. The interface should feel **immediately familiar** to 3D artists and developers while being **approachable** for newcomers.

### Primary Application Interface (Web-based)
**Overall Layout:**
- **Full-height design** where both the 3D viewport and activity log utilize the complete vertical space of the browser window
- **Professional light theme** with clean white backgrounds, subtle gray borders, and strategic use of OTOY's signature red color (#e74c3c) for interactive elements
- **Responsive design** that gracefully adapts from desktop monitors down to mobile phones
- **Fixed header** containing branding and essential connection controls that remains visible during scrolling

**Branding and Identity:**
- **Official Octane Render logo** prominently displayed in the header, linking to the official Octane forum
- **OTOY.com styling** with authentic color palette, typography, and visual hierarchy
- **Professional typography** using system fonts that match OTOY's web presence
- **Consistent iconography** using emoji for immediate visual recognition (📷 📸 🔄 🎬 📂 🫖)

**3D Viewport Experience:**
- **Interactive WebGL cube** that responds immediately to mouse input with smooth, professional-grade camera controls
- **Left mouse drag**: Orbit camera around the object with natural momentum
- **Right mouse drag**: Pan the camera view smoothly in screen space
- **Mouse wheel**: Zoom in/out with appropriate speed and limits
- **Auto-rotation toggle** that smoothly starts/stops automatic rotation when enabled
- **60fps performance** with real-time frame rate display for technical users

**Activity Logging System:**
- **Real-time operation log** with timestamps showing exactly what the system is doing
- **Emoji-based status indicators** for immediate visual feedback (🗒️ info, ✅ success, ❌ error, 📤 outgoing, 📥 incoming)
- **Scrollable history** that maintains context while showing the most recent activity
- **Professional formatting** with consistent spacing and clear visual hierarchy
- **Technical transparency** showing connection health, response times, and system status

**Connection and Control Interface:**
- **Visual connection toggle** with clear on/off states and immediate feedback
- **Server address input** with sensible defaults and validation
- **Function buttons** for testing Octane integration (camera get/set, mesh discovery, model loading)
- **Real-time status indicators** showing connection health, FPS, response times, and error counts
- **Debug controls** that can be toggled for advanced users without cluttering the main interface

### Secondary Applications (Desktop C++)
**Visual Standards:**
- **1200x800 window** with professional dark theme matching 3D software conventions
- **Interactive 3D cube** with identical mouse controls to the web version
- **Professional lighting** with realistic Phong shading and appropriate material properties
- **Cross-platform native dialogs** for file operations that feel natural on each operating system
- **Smooth performance** with consistent frame rates and responsive input handling

### Development and Testing Interface
**Mock Server Feedback:**
- **Comprehensive logging** with emoji indicators and detailed operation tracking
- **Performance statistics** showing call counts, response times, and system health
- **Error simulation capabilities** for testing edge cases and error handling
- **Development-friendly output** that helps developers understand system behavior

## 🔧 TECHNICAL IMPLEMENTATION REQUIREMENTS

### Repository Structure and Organization
```
grpcSamples/
├── html/                          # Web application (primary focus)
│   ├── index.html                 # Main application entry point
│   ├── livelink.js                # Custom gRPC-Web client (zero dependencies)
│   ├── shared.js                  # Common utilities and helper functions
│   ├── webgl-utils.js             # WebGL rendering classes and 3D utilities
│   ├── otoy-theme.css             # Professional OTOY branding and styling
│   ├── README.md                  # Comprehensive documentation with quickstart
│   └── start_proxy.{sh,bat}       # Platform-specific proxy startup scripts
├── proxy/                         # HTTP-to-gRPC translation layer
│   ├── grpc_proxy.py              # Python aiohttp server with CORS support
│   ├── livelink_pb2.py            # Generated protobuf Python bindings
│   └── livelink_pb2_grpc.py       # Generated gRPC Python service stubs
├── mock_octane/                   # Development mock server
│   ├── mock_octane_server.py      # Python gRPC server simulating Octane
│   ├── README.md                  # Mock server documentation
│   └── start_mock_octane.{sh,bat} # Platform-specific startup scripts
├── shared/                        # C++ shared libraries (header-only)
│   ├── camera_system.h            # Camera controls and input handling
│   ├── model_loader.h             # 3D model loading (OBJ/PLY/STL support)
│   ├── file_dialog.h              # Cross-platform native file dialogs
│   └── protos/                    # Generated protobuf C++ headers
├── simpleGL/                      # Standalone C++ 3D viewer
│   ├── main.cpp                   # OpenGL application with file loading
│   └── CMakeLists.txt             # Build configuration
├── simpleGlGrpc/                  # C++ viewer with gRPC network sync
│   ├── main.cpp                   # OpenGL + gRPC client application
│   └── CMakeLists.txt             # Build configuration with gRPC
├── simpleGlSdk/                   # C++ viewer with full Octane SDK
│   ├── main.cpp                   # OpenGL + Octane SDK integration
│   └── CMakeLists.txt             # Build configuration with SDK
├── sdk/                           # Octane SDK wrapper library
│   ├── octane*.h                  # Core SDK headers and type definitions
│   ├── octanewrap*.{h,cpp}        # C++ wrapper classes for SDK
│   └── grpc-examples/             # SDK integration examples
├── third_party/                   # External dependencies
│   ├── grpc/                      # gRPC framework (submodule)
│   ├── protobuf/                  # Protocol buffers (submodule)
│   ├── glfw/                      # Window management (submodule)
│   ├── glew/                      # OpenGL extensions (submodule)
│   └── glm/                       # Mathematics library (submodule)
├── test_models/                   # Sample 3D models for testing
│   ├── simple_triangle.ply        # Basic PLY format test model
│   └── simple_triangle.stl        # Basic STL format test model
├── ORBX/                          # Octane scene files
│   └── teapot.orbx                # Sample Octane scene
├── CMakeLists.txt                 # Root build configuration
├── QUICKSTART.md                  # Simple setup instructions
├── OPENHANDS.md                   # AI development transparency
└── start_development_servers.{sh,bat} # Complete development environment startup
```

### Core Web Application Implementation (html/)

**index.html Structure:**
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>🔗 OTOY WebGL-Octane LiveLink Sync</title>
    <link rel="stylesheet" href="otoy-theme.css">
</head>
<body>
    <!-- Fixed Header with Branding and Connection Controls -->
    <header class="header-bar">
        <div class="otoy-branding">
            <a href="https://render.otoy.com" target="_blank">
                <img src="https://render.otoy.com/forum/styles/Milk_v2_Compact/theme/images/navbar_logo.svg" 
                     alt="Octane Render" class="otoy-logo">
            </a>
            <h1>WebGL LiveLink 🔗</h1>
        </div>
        <div class="connection-controls">
            <input type="text" id="serverAddress" value="http://127.0.0.1:51023">
            <label class="switch">
                <input type="checkbox" id="connectionToggle" onchange="toggleConnection()">
                <span class="slider"></span>
            </label>
        </div>
    </header>

    <!-- Function Controls -->
    <section class="controls-section">
        <div class="livelink-controls">
            <button onclick="testGetCamera()">📷</button>
            <button onclick="setCamera()">📸</button>
            <button onclick="resetCamera()">🔄</button>
            <button onclick="testGetMeshes()">🎬</button>
            <button onclick="loadModel()">📂</button>
            <button onclick="testLoadTeapot()">🫖</button>
        </div>
        <div class="view-controls">
            <label class="switch">
                <input type="checkbox" id="autoRotateToggle" checked>
                <span class="slider"></span>
            </label>
            <label class="switch">
                <input type="checkbox" id="cameraSyncToggle" checked>
                <span class="slider"></span>
            </label>
        </div>
    </section>

    <!-- Main Content: 3D Viewport and Activity Log -->
    <main class="main-content">
        <div class="canvas-container">
            <canvas id="webglCanvas"></canvas>
        </div>
        <div class="activity-panel">
            <div class="activity-header">ACTIVITY LOG</div>
            <div class="activity-log" id="activityLog"></div>
            <div class="activity-controls">
                <button onclick="clearLog()">🗑️</button>
                <button onclick="saveLog()">💾</button>
                <button onclick="showStats()">📊</button>
            </div>
        </div>
    </main>

    <!-- Footer with Performance Stats -->
    <footer class="footer">
        <div class="stats-bar">
            <span>FPS: <span id="fpsCounter">60</span></span>
            <span>Frame: <span id="frameTime">16ms</span></span>
            <span>Response: <span id="responseTime">0ms</span></span>
            <span>Sync: <span id="syncRate">0/s</span></span>
            <span>Errors: <span id="errorCount">0</span></span>
        </div>
        <div class="otoy-footer">
            <div class="status-indicator">All Systems Ready</div>
            <div class="copyright">
                © OTOY Inc. – 2020 All Rights Reserved.
                <a href="https://otoy.com/terms">Terms & Conditions</a> |
                <a href="https://otoy.com/privacy">OTOY Privacy Policy</a>
            </div>
        </div>
    </footer>

    <script src="shared.js"></script>
    <script src="webgl-utils.js"></script>
    <script src="livelink.js"></script>
    <script>
        // Application initialization and main logic
    </script>
</body>
</html>
```

**livelink.js - Custom gRPC-Web Client:**
```javascript
class SimpleEventEmitter {
    constructor() {
        this.events = {};
    }
    
    on(event, callback) {
        if (!this.events[event]) this.events[event] = [];
        this.events[event].push(callback);
    }
    
    emit(event, data) {
        if (this.events[event]) {
            this.events[event].forEach(callback => callback(data));
        }
    }
}

class LiveLinkClient extends SimpleEventEmitter {
    constructor(serverUrl = 'http://127.0.0.1:8080') {
        super();
        this.serverUrl = serverUrl;
        this.isConnected = false;
        this.stats = {
            totalCalls: 0,
            successfulCalls: 0,
            failedCalls: 0,
            averageResponseTime: 0,
            lastResponseTime: 0
        };
    }

    async makeRequest(endpoint, data = {}) {
        const startTime = performance.now();
        this.stats.totalCalls++;
        
        try {
            const response = await fetch(`${this.serverUrl}/${endpoint}`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'X-Call-Id': `call-${Date.now()}-${Math.random().toString(36).substr(2, 9)}`
                },
                body: JSON.stringify(data)
            });

            const responseTime = performance.now() - startTime;
            this.stats.lastResponseTime = responseTime;
            this.updateAverageResponseTime(responseTime);

            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }

            const result = await response.json();
            this.stats.successfulCalls++;
            this.emit('response', { endpoint, data, result, responseTime });
            return result;

        } catch (error) {
            const responseTime = performance.now() - startTime;
            this.stats.failedCalls++;
            this.emit('error', { endpoint, data, error, responseTime });
            throw error;
        }
    }

    async connect() {
        try {
            await this.makeRequest('connect');
            this.isConnected = true;
            this.emit('connected');
            return true;
        } catch (error) {
            this.isConnected = false;
            this.emit('disconnected');
            throw error;
        }
    }

    async setCamera(cameraState) {
        return await this.makeRequest('setCamera', { camera: cameraState });
    }

    async getCamera() {
        return await this.makeRequest('getCamera');
    }

    async getMeshes() {
        return await this.makeRequest('getMeshes');
    }

    getStats() {
        return { ...this.stats };
    }

    updateAverageResponseTime(newTime) {
        const totalSuccessful = this.stats.successfulCalls;
        if (totalSuccessful === 1) {
            this.stats.averageResponseTime = newTime;
        } else {
            this.stats.averageResponseTime = 
                (this.stats.averageResponseTime * (totalSuccessful - 1) + newTime) / totalSuccessful;
        }
    }
}
```

**webgl-utils.js - WebGL Rendering System:**
```javascript
class WebGLRenderer {
    constructor(canvas) {
        this.canvas = canvas;
        this.gl = canvas.getContext('webgl2') || canvas.getContext('webgl');
        if (!this.gl) {
            throw new Error('WebGL not supported');
        }
        
        this.camera = {
            position: [0, 0, 5],
            rotation: [0, 0],
            zoom: 1.0
        };
        
        this.setupWebGL();
        this.createShaders();
        this.createGeometry();
        this.setupEventListeners();
    }

    setupWebGL() {
        const gl = this.gl;
        gl.enable(gl.DEPTH_TEST);
        gl.enable(gl.CULL_FACE);
        gl.cullFace(gl.BACK);
        gl.clearColor(0.2, 0.2, 0.2, 1.0);
    }

    createShaders() {
        const vertexShaderSource = `
            attribute vec3 a_position;
            attribute vec3 a_normal;
            
            uniform mat4 u_modelViewMatrix;
            uniform mat4 u_projectionMatrix;
            uniform mat3 u_normalMatrix;
            
            varying vec3 v_normal;
            varying vec3 v_position;
            
            void main() {
                vec4 position = u_modelViewMatrix * vec4(a_position, 1.0);
                v_position = position.xyz;
                v_normal = u_normalMatrix * a_normal;
                gl_Position = u_projectionMatrix * position;
            }
        `;

        const fragmentShaderSource = `
            precision mediump float;
            
            varying vec3 v_normal;
            varying vec3 v_position;
            
            uniform vec3 u_lightDirection;
            uniform vec3 u_lightColor;
            uniform vec3 u_materialColor;
            
            void main() {
                vec3 normal = normalize(v_normal);
                vec3 lightDir = normalize(-u_lightDirection);
                
                float lambertian = max(dot(normal, lightDir), 0.0);
                float specular = 0.0;
                
                if (lambertian > 0.0) {
                    vec3 viewDir = normalize(-v_position);
                    vec3 reflectDir = reflect(-lightDir, normal);
                    float specAngle = max(dot(reflectDir, viewDir), 0.0);
                    specular = pow(specAngle, 32.0);
                }
                
                vec3 ambient = 0.1 * u_materialColor;
                vec3 diffuse = lambertian * u_lightColor * u_materialColor;
                vec3 spec = specular * u_lightColor;
                
                gl_FragColor = vec4(ambient + diffuse + spec, 1.0);
            }
        `;

        this.program = this.createProgram(vertexShaderSource, fragmentShaderSource);
        this.setupUniforms();
    }

    createGeometry() {
        this.cubeGeometry = new CubeGeometry(this.gl);
    }

    render() {
        const gl = this.gl;
        
        gl.viewport(0, 0, this.canvas.width, this.canvas.height);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        
        gl.useProgram(this.program);
        
        // Update matrices based on camera
        this.updateMatrices();
        
        // Render cube
        this.cubeGeometry.render(gl, this.program);
    }

    handleResize() {
        const displayWidth = this.canvas.clientWidth;
        const displayHeight = this.canvas.clientHeight;
        
        if (this.canvas.width !== displayWidth || this.canvas.height !== displayHeight) {
            this.canvas.width = displayWidth;
            this.canvas.height = displayHeight;
        }
    }
}

class CubeGeometry {
    constructor(gl) {
        this.gl = gl;
        this.createBuffers();
    }

    createBuffers() {
        const gl = this.gl;
        
        // Cube vertices with normals
        const vertices = new Float32Array([
            // Front face
            -1, -1,  1,  0,  0,  1,
             1, -1,  1,  0,  0,  1,
             1,  1,  1,  0,  0,  1,
            -1,  1,  1,  0,  0,  1,
            // Back face
            -1, -1, -1,  0,  0, -1,
            -1,  1, -1,  0,  0, -1,
             1,  1, -1,  0,  0, -1,
             1, -1, -1,  0,  0, -1,
            // Top face
            -1,  1, -1,  0,  1,  0,
            -1,  1,  1,  0,  1,  0,
             1,  1,  1,  0,  1,  0,
             1,  1, -1,  0,  1,  0,
            // Bottom face
            -1, -1, -1,  0, -1,  0,
             1, -1, -1,  0, -1,  0,
             1, -1,  1,  0, -1,  0,
            -1, -1,  1,  0, -1,  0,
            // Right face
             1, -1, -1,  1,  0,  0,
             1,  1, -1,  1,  0,  0,
             1,  1,  1,  1,  0,  0,
             1, -1,  1,  1,  0,  0,
            // Left face
            -1, -1, -1, -1,  0,  0,
            -1, -1,  1, -1,  0,  0,
            -1,  1,  1, -1,  0,  0,
            -1,  1, -1, -1,  0,  0
        ]);

        const indices = new Uint16Array([
            0,  1,  2,    0,  2,  3,    // front
            4,  5,  6,    4,  6,  7,    // back
            8,  9,  10,   8,  10, 11,   // top
            12, 13, 14,   12, 14, 15,   // bottom
            16, 17, 18,   16, 18, 19,   // right
            20, 21, 22,   20, 22, 23    // left
        ]);

        this.vertexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.vertexBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

        this.indexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indexBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);

        this.indexCount = indices.length;
    }

    render(gl, program) {
        gl.bindBuffer(gl.ARRAY_BUFFER, this.vertexBuffer);
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indexBuffer);

        const positionLocation = gl.getAttribLocation(program, 'a_position');
        const normalLocation = gl.getAttribLocation(program, 'a_normal');

        gl.enableVertexAttribArray(positionLocation);
        gl.vertexAttribPointer(positionLocation, 3, gl.FLOAT, false, 24, 0);

        gl.enableVertexAttribArray(normalLocation);
        gl.vertexAttribPointer(normalLocation, 3, gl.FLOAT, false, 24, 12);

        gl.drawElements(gl.TRIANGLES, this.indexCount, gl.UNSIGNED_SHORT, 0);
    }
}
```

**otoy-theme.css - Professional OTOY Styling:**
```css
/* OTOY Professional Theme - Light Design */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
    background-color: #ffffff;
    color: #333333;
    height: 100vh;
    display: flex;
    flex-direction: column;
    overflow: hidden;
}

/* Header Styling */
.header-bar {
    background: linear-gradient(135deg, #f8f9fa 0%, #e9ecef 100%);
    border-bottom: 2px solid #dee2e6;
    padding: 12px 20px;
    flex-shrink: 0;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

.header-content {
    display: flex;
    justify-content: space-between;
    align-items: center;
    max-width: 1400px;
    margin: 0 auto;
}

.otoy-branding {
    display: flex;
    align-items: center;
    gap: 12px;
}

.otoy-logo {
    height: 32px;
    width: auto;
    transition: opacity 0.2s ease;
}

.otoy-logo:hover {
    opacity: 0.8;
}

.otoy-branding h1 {
    font-size: 1.5rem;
    font-weight: 600;
    color: #2c3e50;
    margin: 0;
}

/* Connection Controls */
.connection-controls {
    display: flex;
    align-items: center;
    gap: 15px;
}

#serverAddress {
    padding: 8px 12px;
    border: 2px solid #ced4da;
    border-radius: 6px;
    font-size: 14px;
    width: 200px;
    background: white;
    transition: border-color 0.2s ease;
}

#serverAddress:focus {
    outline: none;
    border-color: #e74c3c;
    box-shadow: 0 0 0 3px rgba(231, 76, 60, 0.1);
}

/* Switch Styling */
.switch {
    position: relative;
    display: inline-block;
    width: 50px;
    height: 24px;
}

.switch input {
    opacity: 0;
    width: 0;
    height: 0;
}

.slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: #ccc;
    transition: 0.3s;
    border-radius: 24px;
}

.slider:before {
    position: absolute;
    content: "";
    height: 18px;
    width: 18px;
    left: 3px;
    bottom: 3px;
    background-color: white;
    transition: 0.3s;
    border-radius: 50%;
}

input:checked + .slider {
    background-color: #e74c3c;
}

input:checked + .slider:before {
    transform: translateX(26px);
}

/* Controls Section */
.controls-section {
    background: #f8f9fa;
    border-bottom: 1px solid #dee2e6;
    padding: 12px 20px;
    flex-shrink: 0;
}

.controls-content {
    display: flex;
    justify-content: space-between;
    align-items: center;
    max-width: 1400px;
    margin: 0 auto;
}

.livelink-controls {
    display: flex;
    gap: 8px;
}

.icon-btn {
    background: white;
    border: 2px solid #dee2e6;
    border-radius: 6px;
    padding: 8px 12px;
    font-size: 16px;
    cursor: pointer;
    transition: all 0.2s ease;
    min-width: 44px;
    height: 40px;
}

.icon-btn:hover {
    background: #e74c3c;
    border-color: #e74c3c;
    color: white;
    transform: translateY(-1px);
}

/* Main Content Layout */
.main-content {
    display: flex;
    flex: 1;
    min-height: 0;
}

.canvas-container {
    flex: 1;
    background: white;
    border-right: 1px solid #dee2e6;
    position: relative;
}

#webglCanvas {
    width: 100%;
    height: 100%;
    display: block;
    cursor: grab;
}

#webglCanvas:active {
    cursor: grabbing;
}

.activity-panel {
    width: 400px;
    background: #f8f9fa;
    display: flex;
    flex-direction: column;
    border-left: 1px solid #dee2e6;
}

.activity-header {
    background: #e9ecef;
    padding: 12px 16px;
    font-weight: 600;
    color: #495057;
    border-bottom: 1px solid #dee2e6;
    font-size: 14px;
    letter-spacing: 0.5px;
}

.activity-log {
    flex: 1;
    overflow-y: auto;
    padding: 8px;
    font-family: 'Monaco', 'Menlo', 'Ubuntu Mono', monospace;
    font-size: 12px;
    line-height: 1.4;
    background: white;
}

.log-entry {
    padding: 4px 8px;
    margin: 2px 0;
    border-radius: 4px;
    display: flex;
    align-items: flex-start;
    gap: 8px;
}

.log-entry.info {
    background: #f8f9fa;
    border-left: 3px solid #6c757d;
}

.log-entry.success {
    background: #d4edda;
    border-left: 3px solid #28a745;
}

.log-entry.error {
    background: #f8d7da;
    border-left: 3px solid #dc3545;
}

/* Footer Styling */
.footer {
    background: #f8f9fa;
    border-top: 1px solid #dee2e6;
    flex-shrink: 0;
}

.stats-bar {
    padding: 8px 20px;
    display: flex;
    gap: 20px;
    font-size: 12px;
    color: #6c757d;
    background: #e9ecef;
    border-bottom: 1px solid #dee2e6;
}

.stats-bar span {
    display: flex;
    align-items: center;
    gap: 4px;
}

.otoy-footer {
    padding: 12px 20px;
    display: flex;
    justify-content: space-between;
    align-items: center;
    background: #2c3e50;
    color: white;
    font-size: 12px;
}

.status-indicator {
    color: #27ae60;
    font-weight: 600;
}

.copyright a {
    color: #e74c3c;
    text-decoration: none;
}

.copyright a:hover {
    text-decoration: underline;
}

/* Responsive Design */
@media (max-width: 768px) {
    .main-content {
        flex-direction: column;
    }
    
    .activity-panel {
        width: 100%;
        height: 300px;
    }
    
    .controls-content {
        flex-direction: column;
        gap: 12px;
    }
    
    .header-content {
        flex-direction: column;
        gap: 12px;
    }
}
```

### Python Infrastructure Implementation

**proxy/grpc_proxy.py - HTTP-to-gRPC Translation:**
```python
import asyncio
import json
import logging
import time
from aiohttp import web, ClientSession
from aiohttp_cors import setup as cors_setup, ResourceOptions
import grpc
from livelink_pb2_grpc import LiveLinkServiceStub
from livelink_pb2 import CameraState, Empty

class GrpcProxy:
    def __init__(self, grpc_host='localhost', grpc_port=51023, http_port=8080):
        self.grpc_host = grpc_host
        self.grpc_port = grpc_port
        self.http_port = http_port
        self.app = web.Application()
        self.setup_routes()
        self.setup_cors()
        self.setup_logging()

    def setup_logging(self):
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s - %(levelname)s - %(message)s'
        )
        self.logger = logging.getLogger(__name__)

    def setup_routes(self):
        self.app.router.add_post('/connect', self.handle_connect)
        self.app.router.add_post('/setCamera', self.handle_set_camera)
        self.app.router.add_post('/getCamera', self.handle_get_camera)
        self.app.router.add_post('/getMeshes', self.handle_get_meshes)

    def setup_cors(self):
        cors = cors_setup(self.app, defaults={
            "*": ResourceOptions(
                allow_credentials=True,
                expose_headers="*",
                allow_headers="*",
                allow_methods="*"
            )
        })
        for route in list(self.app.router.routes()):
            cors.add(route)

    async def get_grpc_stub(self):
        channel = grpc.aio.insecure_channel(f'{self.grpc_host}:{self.grpc_port}')
        return LiveLinkServiceStub(channel)

    async def handle_connect(self, request):
        start_time = time.time()
        call_id = request.headers.get('X-Call-Id', 'unknown')
        
        try:
            self.logger.info(f"📤 [{call_id}] Connect request")
            
            stub = await self.get_grpc_stub()
            response = await stub.Connect(Empty())
            
            response_time = (time.time() - start_time) * 1000
            self.logger.info(f"📥 [{call_id}] Connect successful ({response_time:.1f}ms)")
            
            return web.json_response({
                'success': True,
                'message': 'Connected to Octane LiveLink',
                'responseTime': response_time
            })
            
        except Exception as e:
            response_time = (time.time() - start_time) * 1000
            self.logger.error(f"❌ [{call_id}] Connect failed: {str(e)} ({response_time:.1f}ms)")
            
            return web.json_response({
                'success': False,
                'error': str(e),
                'responseTime': response_time
            }, status=500)

    async def handle_set_camera(self, request):
        start_time = time.time()
        call_id = request.headers.get('X-Call-Id', 'unknown')
        
        try:
            data = await request.json()
            camera_data = data.get('camera', {})
            
            self.logger.info(f"📤 [{call_id}] SetCamera request: {camera_data}")
            
            stub = await self.get_grpc_stub()
            camera_state = CameraState(
                position_x=camera_data.get('position', [0, 0, 0])[0],
                position_y=camera_data.get('position', [0, 0, 0])[1],
                position_z=camera_data.get('position', [0, 0, 0])[2],
                rotation_x=camera_data.get('rotation', [0, 0])[0],
                rotation_y=camera_data.get('rotation', [0, 0])[1],
                zoom=camera_data.get('zoom', 1.0)
            )
            
            response = await stub.SetCamera(camera_state)
            
            response_time = (time.time() - start_time) * 1000
            self.logger.info(f"📥 [{call_id}] SetCamera successful ({response_time:.1f}ms)")
            
            return web.json_response({
                'success': True,
                'message': 'Camera updated',
                'responseTime': response_time
            })
            
        except Exception as e:
            response_time = (time.time() - start_time) * 1000
            self.logger.error(f"❌ [{call_id}] SetCamera failed: {str(e)} ({response_time:.1f}ms)")
            
            return web.json_response({
                'success': False,
                'error': str(e),
                'responseTime': response_time
            }, status=500)

    async def run(self):
        runner = web.AppRunner(self.app)
        await runner.setup()
        site = web.TCPSite(runner, '0.0.0.0', self.http_port)
        await site.start()
        
        self.logger.info(f"🚀 gRPC Proxy server started on port {self.http_port}")
        self.logger.info(f"🔗 Proxying to gRPC server at {self.grpc_host}:{self.grpc_port}")
        
        try:
            await asyncio.Future()  # Run forever
        except KeyboardInterrupt:
            self.logger.info("🛑 Shutting down proxy server")

if __name__ == '__main__':
    proxy = GrpcProxy()
    asyncio.run(proxy.run())
```

**mock_octane/mock_octane_server.py - Development Mock Server:**
```python
import asyncio
import grpc
import logging
import time
from concurrent import futures
from livelink_pb2_grpc import LiveLinkServiceServicer, add_LiveLinkServiceServicer_to_server
from livelink_pb2 import CameraState, Empty, MeshList, Mesh

class MockOctaneServer(LiveLinkServiceServicer):
    def __init__(self):
        self.setup_logging()
        self.stats = {
            'start_time': time.time(),
            'get_camera_calls': 0,
            'set_camera_calls': 0,
            'get_meshes_calls': 0,
            'total_calls': 0
        }
        self.current_camera = CameraState(
            position_x=0.0, position_y=0.0, position_z=5.0,
            rotation_x=0.0, rotation_y=0.0, zoom=1.0
        )

    def setup_logging(self):
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s - %(levelname)s - %(message)s'
        )
        self.logger = logging.getLogger(__name__)

    async def Connect(self, request, context):
        self.stats['total_calls'] += 1
        self.logger.info("🔗 Client connected to mock Octane server")
        return Empty()

    async def SetCamera(self, request, context):
        self.stats['set_camera_calls'] += 1
        self.stats['total_calls'] += 1
        
        self.current_camera = request
        self.logger.info(f"📸 Camera updated: pos=({request.position_x:.2f}, {request.position_y:.2f}, {request.position_z:.2f}), "
                        f"rot=({request.rotation_x:.2f}, {request.rotation_y:.2f}), zoom={request.zoom:.2f}")
        
        return Empty()

    async def GetCamera(self, request, context):
        self.stats['get_camera_calls'] += 1
        self.stats['total_calls'] += 1
        
        self.logger.info(f"📷 Camera requested: returning current state")
        return self.current_camera

    async def GetMeshes(self, request, context):
        self.stats['get_meshes_calls'] += 1
        self.stats['total_calls'] += 1
        
        # Return mock mesh data
        meshes = [
            Mesh(name="Cube", vertex_count=8, face_count=12),
            Mesh(name="Sphere", vertex_count=482, face_count=960),
            Mesh(name="Teapot", vertex_count=1178, face_count=2256)
        ]
        
        self.logger.info(f"🎬 Meshes requested: returning {len(meshes)} meshes")
        return MeshList(meshes=meshes)

    def print_stats(self):
        uptime = time.time() - self.stats['start_time']
        self.logger.info(f"📊 Mock Octane Server Statistics:")
        self.logger.info(f"   Uptime: {uptime:.1f}s")
        self.logger.info(f"   GetCamera calls: {self.stats['get_camera_calls']}")
        self.logger.info(f"   SetCamera calls: {self.stats['set_camera_calls']}")
        self.logger.info(f"   GetMeshes calls: {self.stats['get_meshes_calls']}")
        self.logger.info(f"   Total calls: {self.stats['total_calls']}")

async def serve():
    server = grpc.aio.server(futures.ThreadPoolExecutor(max_workers=10))
    mock_service = MockOctaneServer()
    add_LiveLinkServiceServicer_to_server(mock_service, server)
    
    listen_addr = '[::]:51023'
    server.add_insecure_port(listen_addr)
    
    logging.info(f"🎭 Mock Octane server starting on {listen_addr}")
    await server.start()
    
    # Print stats every 30 seconds
    async def stats_printer():
        while True:
            await asyncio.sleep(30)
            mock_service.print_stats()
    
    asyncio.create_task(stats_printer())
    
    try:
        await server.wait_for_termination()
    except KeyboardInterrupt:
        logging.info("🛑 Shutting down mock server")
        await server.stop(5)

if __name__ == '__main__':
    asyncio.run(serve())
```

### C++ Desktop Applications Implementation

**simpleGL/main.cpp - Standalone 3D Viewer:**
```cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "../shared/camera_system.h"
#include "../shared/model_loader.h"
#include "../shared/file_dialog.h"

class SimpleGLApp {
private:
    GLFWwindow* window;
    CameraSystem camera;
    ModelLoader modelLoader;
    GLuint shaderProgram;
    GLuint VAO, VBO, EBO;
    
    // Cube geometry
    std::vector<float> vertices = {
        // positions          // normals
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        // ... (complete cube vertices)
    };
    
    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,   // back face
        4, 5, 6, 6, 7, 4,   // front face
        // ... (complete cube indices)
    };

public:
    SimpleGLApp() : camera(glm::vec3(0.0f, 0.0f, 5.0f)) {}

    bool initialize() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }

        // Configure GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window
        window = glfwCreateWindow(1200, 800, "Simple OpenGL Viewer", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);
        
        // Set callbacks
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetCursorPosCallback(window, mouseCallback);
        glfwSetScrollCallback(window, scrollCallback);
        glfwSetKeyCallback(window, keyCallback);

        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            return false;
        }

        // Configure OpenGL
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Create shaders and geometry
        createShaders();
        createGeometry();

        return true;
    }

    void createShaders() {
        const char* vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aNormal;
            
            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;
            uniform mat3 normalMatrix;
            
            out vec3 FragPos;
            out vec3 Normal;
            
            void main() {
                FragPos = vec3(model * vec4(aPos, 1.0));
                Normal = normalMatrix * aNormal;
                gl_Position = projection * view * vec4(FragPos, 1.0);
            }
        )";

        const char* fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            
            in vec3 FragPos;
            in vec3 Normal;
            
            uniform vec3 lightPos;
            uniform vec3 lightColor;
            uniform vec3 objectColor;
            uniform vec3 viewPos;
            
            void main() {
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
                vec3 viewDir = normalize(viewPos - FragPos);
                vec3 reflectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
                vec3 specular = specularStrength * spec * lightColor;
                
                vec3 result = (ambient + diffuse + specular) * objectColor;
                FragColor = vec4(result, 1.0);
            }
        )";

        // Compile and link shaders (implementation details...)
        shaderProgram = compileShaderProgram(vertexShaderSource, fragmentShaderSource);
    }

    void createGeometry() {
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
    }

    void render() {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Set matrices
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

        setUniformMatrix4fv("model", model);
        setUniformMatrix4fv("view", view);
        setUniformMatrix4fv("projection", projection);

        // Set lighting uniforms
        setUniformVec3("lightPos", glm::vec3(2.0f, 2.0f, 2.0f));
        setUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        setUniformVec3("objectColor", glm::vec3(0.3f, 0.5f, 0.8f));
        setUniformVec3("viewPos", camera.getPosition());

        // Render cube
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    void run() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            camera.update();
            render();
            glfwSwapBuffers(window);
        }
    }

    // Callback functions
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
        SimpleGLApp* app = static_cast<SimpleGLApp*>(glfwGetWindowUserPointer(window));
        app->camera.processMouseMovement(xpos, ypos);
    }

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        SimpleGLApp* app = static_cast<SimpleGLApp*>(glfwGetWindowUserPointer(window));
        app->camera.processMouseScroll(yoffset);
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        SimpleGLApp* app = static_cast<SimpleGLApp*>(glfwGetWindowUserPointer(window));
        
        if (action == GLFW_PRESS) {
            switch (key) {
                case GLFW_KEY_L:
                    app->loadModel();
                    break;
                case GLFW_KEY_R:
                    app->camera.reset();
                    break;
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, true);
                    break;
            }
        }
    }

    void loadModel() {
        std::string filename = FileDialog::openFile("Load 3D Model", {
            {"OBJ Files", "*.obj"},
            {"PLY Files", "*.ply"},
            {"STL Files", "*.stl"},
            {"All Files", "*.*"}
        });
        
        if (!filename.empty()) {
            if (modelLoader.loadModel(filename)) {
                std::cout << "Model loaded successfully: " << filename << std::endl;
                // Update geometry with loaded model data
                updateGeometry(modelLoader.getVertices(), modelLoader.getIndices());
            } else {
                std::cerr << "Failed to load model: " << filename << std::endl;
            }
        }
    }

    ~SimpleGLApp() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(shaderProgram);
        glfwTerminate();
    }
};

int main() {
    SimpleGLApp app;
    
    if (!app.initialize()) {
        return -1;
    }
    
    std::cout << "Simple OpenGL Viewer" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Mouse: Orbit camera" << std::endl;
    std::cout << "  Scroll: Zoom" << std::endl;
    std::cout << "  L: Load model" << std::endl;
    std::cout << "  R: Reset camera" << std::endl;
    std::cout << "  ESC: Exit" << std::endl;
    
    app.run();
    return 0;
}
```

### Build System Configuration

**CMakeLists.txt - Root Build Configuration:**
```cmake
cmake_minimum_required(VERSION 3.10)
project(grpcSamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/shared)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# Add subdirectories
add_subdirectory(third_party)
add_subdirectory(shared)
add_subdirectory(simpleGL)
add_subdirectory(simpleGlGrpc)
add_subdirectory(simpleGlSdk)

# Platform-specific configurations
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# Debug/Release configurations
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3")
```

### Development Environment Scripts

**start_development_servers.sh - Complete Environment Startup:**
```bash
#!/bin/bash

echo "🚀 Starting OTOY WebGL-Octane LiveLink Development Environment"

# Function to check if port is in use
check_port() {
    if lsof -Pi :$1 -sTCP:LISTEN -t >/dev/null 2>&1; then
        echo "⚠️  Port $1 is already in use"
        return 1
    fi
    return 0
}

# Function to start service in background
start_service() {
    local name=$1
    local command=$2
    local port=$3
    local log_file=$4
    
    echo "🔄 Starting $name on port $port..."
    
    if check_port $port; then
        eval "$command" > "$log_file" 2>&1 &
        local pid=$!
        echo $pid > "${name,,}.pid"
        echo "✅ $name started (PID: $pid)"
        sleep 2
        
        if kill -0 $pid 2>/dev/null; then
            echo "✅ $name is running successfully"
        else
            echo "❌ $name failed to start"
            cat "$log_file"
        fi
    else
        echo "❌ Cannot start $name - port $port is in use"
    fi
}

# Start mock Octane server
start_service "Mock-Octane" "cd mock_octane && python3 mock_octane_server.py" 51023 "mock_octane/mock_octane.log"

# Start gRPC proxy
start_service "gRPC-Proxy" "cd proxy && python3 grpc_proxy.py" 8080 "proxy/proxy.log"

# Start web server
start_service "Web-Server" "cd html && python3 -m http.server 51313" 51313 "html/server.log"

echo ""
echo "🌐 Development Environment Ready!"
echo "📱 Web Application: http://localhost:51313"
echo "🔗 gRPC Proxy: http://localhost:8080"
echo "🎭 Mock Octane: grpc://localhost:51023"
echo ""
echo "📋 Log Files:"
echo "   Mock Octane: mock_octane/mock_octane.log"
echo "   gRPC Proxy: proxy/proxy.log"
echo "   Web Server: html/server.log"
echo ""
echo "🛑 To stop all services: ./stop_development_servers.sh"
```

## 💡 POTENTIAL IMPROVEMENTS

### Enhanced Features
1. **Advanced 3D Models**: Support for more complex file formats (FBX, GLTF, DAE)
2. **Material System**: PBR material support with texture loading and editing
3. **Animation Support**: Keyframe animation and timeline controls
4. **Scene Graph**: Hierarchical object management with transform inheritance
5. **Lighting System**: Multiple light types (directional, point, spot) with shadows

### Performance Optimizations
1. **WebGL 2.0 Features**: Instanced rendering, uniform buffer objects, transform feedback
2. **Level of Detail**: Automatic LOD system for complex models
3. **Frustum Culling**: Visibility culling for large scenes
4. **Texture Streaming**: Progressive texture loading for large assets
5. **Worker Threads**: Background processing for model loading and calculations

### User Experience Enhancements
1. **Drag & Drop**: Direct file dropping onto the 3D viewport
2. **Undo/Redo System**: Complete action history with state management
3. **Keyboard Shortcuts**: Comprehensive hotkey system for power users
4. **Touch Support**: Enhanced mobile and tablet interaction
5. **VR/AR Support**: WebXR integration for immersive viewing

### Development Tools
1. **Scene Inspector**: Real-time scene graph visualization and editing
2. **Performance Profiler**: Detailed rendering and network performance analysis
3. **Debug Visualizations**: Wireframe, normals, bounding boxes, lighting debug
4. **Asset Pipeline**: Automated model optimization and conversion tools
5. **Plugin System**: Extensible architecture for custom functionality

### Integration Capabilities
1. **Cloud Storage**: Direct integration with cloud storage providers
2. **Version Control**: Git-like versioning for 3D scenes and assets
3. **Collaboration**: Real-time multi-user editing and viewing
4. **Export Options**: Multiple output formats for different use cases
5. **API Extensions**: RESTful API for external tool integration
