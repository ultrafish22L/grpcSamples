# OctaneWeb Application Reproduction Prompt

## 🚨 CRITICAL NETWORKING SETUP FOR OPENHANDS

**Docker Container Isolation**: OpenHands containers cannot access host localhost services by default.

**Essential Configuration for gRPC Proxy Access:**
```bash
export SANDBOX_USE_HOST_NETWORK=true
```

**Docker-in-Docker Alternative:**
```bash
export SANDBOX_LOCAL_RUNTIME_URL="http://host.docker.internal"
# Then update proxy URLs to use host.docker.internal:8080
```

**Common Connection Issues:**
- `Connection refused` to localhost:8080 (gRPC proxy)
- `Network unreachable` errors in browser console
- Timeout errors in activity log

**Full networking documentation**: `OPENHANDS_LOCALHOST_NETWORKING.md`

## User Experience Requirements (Non-Technical)

### Visual Design and Professional Branding
Create a **professional web-based 3D application** that matches the quality and aesthetics of desktop 3D software like Blender, Maya, or Cinema 4D. The application should feel like a legitimate professional tool, not a web demo.

**Branding Requirements:**
- **OTOY Octane Render branding** with official logo and color scheme
- **Dark theme** (#2c3e50 background) with red accents (#e74c3c)
- **Professional typography** using system fonts (Segoe UI, Roboto, sans-serif)
- **Industry-standard iconography** for 3D operations (camera, geometry, lights)
- **Cohesive visual language** that feels familiar to 3D artists

### Application Layout and Interface Design

#### Overall Layout Structure
```
┌─────────────────────────────────────────────────────────────────┐
│ [OTOY Logo] WebGL LiveLink 🔗    [Server: 127.0.0.1:51023] [●] │ ← Header Bar
├─────────────────────────────────────────────────────────────────┤
│ [📷][📸][🔄][🎬][📂][🫖]  [🧊 Auto-Rotate] [🔗 Camera Sync]    │ ← Control Bar
├──────────────┬──────────────────────────┬─────────────────────────┤
│              │                          │                         │
│  SCENE       │                          │     ACTIVITY LOG        │
│  OUTLINER    │     3D WEBGL VIEWPORT    │                         │
│              │                          │  📤 [10:15:23] Sending  │
│ ▼ Scene      │     [Interactive 3D      │     GetCamera request   │
│   ▼ Geometry │      Cube with Mouse     │  📥 [10:15:23] Camera   │
│     □ Cube   │      Camera Controls]    │     position received   │
│     ○ Sphere │                          │  ✅ [10:15:24] Scene    │
│   ▶ Lights   │                          │     data loaded         │
│   ▶ Cameras  │                          │                         │
│              │                          │  [🗑️][💾][📊]          │
├──────────────┴──────────────────────────┴─────────────────────────┤
│ FPS: 60 | Frame: 17ms | Response: 12ms | Sync: 30/s | Errors: 0  │ ← Status Bar
│                    ● All Systems Operational                       │
└─────────────────────────────────────────────────────────────────┘
```

#### Scene Outliner Panel (Left Side)
**Visual Requirements:**
- **Hierarchical tree structure** with proper indentation (20px per level)
- **Expand/collapse triangles** (▼ expanded, ▶ collapsed) that respond to clicks
- **Node type icons** (□ for geometry, ○ for lights, 📷 for cameras, 🎨 for materials)
- **Visibility toggle icons** (👁️ visible, 👁️‍🗨️ hidden) for each node
- **Selection highlighting** (blue background #3498db when selected)
- **Hover effects** (subtle background change #34495e on hover)
- **Professional tree styling** with connecting lines and proper spacing

**Interaction Requirements:**
- **Click triangle** to expand/collapse node children
- **Click node name** to select node (highlight in blue)
- **Click eye icon** to toggle visibility in Octane
- **Right-click node** to show context menu for node operations
- **Smooth animations** for expand/collapse (200ms ease-in-out)

**Data Structure:**
```
Scene Root
├── Geometry
│   ├── Cube_001 (visible)
│   ├── Sphere_002 (hidden)
│   └── Plane_003 (visible)
├── Lights
│   ├── Sun_Light (visible)
│   └── Area_Light (visible)
└── Cameras
    └── Camera_001 (visible)
```

#### 3D WebGL Viewport (Center)
**Visual Requirements:**
- **Full-height canvas** that utilizes all available vertical space
- **Interactive 3D scene** with basic geometry (cube, sphere, plane)
- **Smooth camera controls** with mouse orbit, pan, zoom
- **Professional 3D rendering** with proper lighting and shading
- **Real-time performance** maintaining 60 FPS

**Interaction Requirements:**
- **Left mouse drag**: Orbit camera around scene center
- **Right mouse drag**: Pan camera horizontally and vertically
- **Mouse wheel**: Zoom in/out smoothly
- **Touch support**: Full touch controls for mobile devices
- **Keyboard shortcuts**: WASD for camera movement (optional)

**Technical Requirements:**
- **WebGL 2.0 support** with automatic fallback to WebGL 1.0
- **Proper matrix math** for 3D transformations
- **Efficient rendering** with minimal draw calls
- **Responsive canvas** that adapts to window resizing

#### Activity Log Panel (Right Side)
**Visual Requirements:**
- **Real-time scrolling log** with automatic scroll-to-bottom
- **Emoji indicators** for different message types:
  - 📤 Outgoing API requests
  - 📥 Incoming API responses  
  - ✅ Successful operations
  - ❌ Errors and failures
  - 🗒️ General information
- **Timestamp formatting** [HH:MM:SS] in 24-hour format
- **Color-coded messages** (green for success, red for errors, white for info)
- **Monospace font** for technical details
- **Scrollable history** with smooth scrolling

**Content Requirements:**
- **API call logging**: Show all gRPC requests and responses
- **Connection status**: Log connection attempts, successes, failures
- **Performance metrics**: Response times, FPS updates, sync rates
- **User actions**: Log user interactions (node selection, visibility changes)
- **Error details**: Comprehensive error messages with context

#### Header and Control Bars
**Header Bar Requirements:**
- **OTOY logo** (clickable link to render.otoy.com)
- **Application title** "WebGL LiveLink 🔗"
- **Server address input** with validation
- **Connection status LED** (🟡 ready, 🟢 connected, 🔴 error)
- **Connection toggle switch** for connect/disconnect

**Control Bar Requirements:**
- **Action buttons** with tooltips:
  - 📷 Get Camera (retrieve current camera state)
  - 📸 Set Camera (apply camera to Octane)
  - 🔄 Sync Camera (toggle real-time sync)
  - 🎬 Start Animation (future feature)
  - 📂 Load Scene (load 3D model file)
  - 🫖 Render (trigger Octane render)
- **Toggle switches** with labels:
  - 🧊 Auto-Rotate (automatically rotate 3D model)
  - 🔗 Camera Sync (sync camera with Octane in real-time)

#### Status Bar (Bottom)
**Performance Metrics:**
- **FPS**: Current frames per second
- **Frame**: Frame render time in milliseconds
- **Response**: Average API response time
- **Sync**: Camera sync rate per second
- **Errors**: Total error count

**System Status:**
- **Status indicator** with three states:
  - 🟡 "All Systems Ready" (ready to connect)
  - 🟢 "All Systems Operational" (connected and working)
  - 🔴 "Connection Error" (problems detected)

### Node Graph Editor Requirements

#### Right-Click Context Menu System
**Visual Requirements:**
- **Professional context menu** with dark background (#34495e)
- **Hierarchical menu structure** organized by node categories
- **Hover-triggered submenus** that appear as popups
- **Proper menu positioning** that stays within viewport bounds
- **Smooth animations** for menu appearance and submenu transitions

**Menu Structure:**
```
Right-click on Scene Outliner Node:
├── Create Node ▶
│   ├── Geometry ▶
│   │   ├── Cube
│   │   ├── Sphere  
│   │   ├── Plane
│   │   └── Cylinder
│   ├── Lights ▶
│   │   ├── Sun Light
│   │   ├── Area Light
│   │   └── Point Light
│   ├── Materials ▶
│   │   ├── Diffuse Material
│   │   ├── Glossy Material
│   │   └── Emission Material
│   └── Cameras ▶
│       └── Camera
├── Duplicate Node
├── Delete Node
└── Properties
```

**Interaction Requirements:**
- **Right-click** on any scene outliner node to show context menu
- **Hover** over "Create Node" to show submenu with categories
- **Hover** over category (e.g., "Geometry") to show specific node types
- **Click** on specific node type to create that node in Octane
- **Click outside** menu to close
- **Escape key** to close menu

### Responsive Design Requirements

#### Desktop Layout (1200px+)
- **Three-panel layout**: Scene outliner (300px) | 3D viewport (flexible) | Activity log (400px)
- **Full-height panels** utilizing entire viewport height
- **Fixed header and control bars** that don't scroll
- **Resizable panels** with drag handles between sections

#### Tablet Layout (768px - 1199px)
- **Two-panel layout**: 3D viewport (60%) | Activity log (40%)
- **Collapsible scene outliner** accessible via hamburger menu
- **Touch-optimized controls** with larger touch targets
- **Simplified control bar** with essential buttons only

#### Mobile Layout (< 768px)
- **Single-panel layout** with tabbed interface
- **Tabs**: 3D View | Scene | Activity Log
- **Full-screen 3D viewport** when in 3D View tab
- **Touch camera controls** optimized for mobile
- **Simplified UI** with essential features only

### Accessibility Requirements
- **High contrast support** for users with visual impairments
- **Keyboard navigation** for all interactive elements
- **Screen reader compatibility** with proper ARIA labels
- **Reduced motion support** for users with motion sensitivity
- **Touch accessibility** with minimum 44px touch targets

### Performance Requirements
- **60 FPS rendering** in 3D viewport under normal conditions
- **Sub-100ms API response** times for typical operations
- **Smooth animations** for all UI transitions
- **Efficient memory usage** with proper cleanup of resources
- **Fast startup time** (< 2 seconds to fully loaded)

## Technical Implementation Details

### File Structure
```
octaneWeb/
├── index.html                 # Main application entry point
├── css/
│   ├── main.css              # Core application styles
│   └── otoy-theme.css        # OTOY branding and color scheme
├── js/
│   ├── OctaneWebClient.js    # gRPC-Web client implementation
│   ├── SceneOutliner.js      # Hierarchical scene tree component
│   ├── NodeGraphEditor.js    # Context menu and node creation
│   ├── DebugConsole.js       # Development debug console (Ctrl-D)
│   └── CacheBuster.js        # Development cache management
├── shared/
│   ├── webgl-utils.js        # WebGL rendering utilities
│   └── shared.js             # Common helper functions
└── assets/
    ├── octane-logo.svg       # OTOY logo
    └── icons/                # UI icons and graphics
```

### Core JavaScript Classes

#### OctaneWebClient.js
```javascript
class OctaneWebClient {
    constructor(serverUrl) {
        this.serverUrl = serverUrl;
        this.connected = false;
        this.callId = 0;
    }
    
    async connect() {
        // Test connection to proxy server
        // Set up event listeners for connection state
        // Initialize API call infrastructure
    }
    
    async getCamera() {
        // Make GetCamera gRPC call via HTTP proxy
        // Return camera position, rotation, FOV
    }
    
    async setCamera(position, rotation, fov) {
        // Make SetCamera gRPC call via HTTP proxy
        // Update Octane camera state
    }
    
    async getSceneData() {
        // Make GetMeshes or buildSceneTree gRPC call
        // Return hierarchical scene data
    }
    
    async createNode(nodeType, parentId) {
        // Make CreateNode gRPC call
        // Return new node information
    }
}
```

#### SceneOutliner.js
```javascript
class SceneOutliner {
    constructor(containerId, client) {
        this.container = document.getElementById(containerId);
        this.client = client;
        this.sceneData = null;
        this.selectedNode = null;
    }
    
    render(sceneData) {
        // Transform flat API data to hierarchical structure
        // Generate DOM elements for tree view
        // Attach event listeners for interactions
    }
    
    renderNode(node, level) {
        // Create DOM element for single node
        // Add expand/collapse triangle
        // Add node icon and name
        // Add visibility toggle
        // Apply proper indentation
    }
    
    handleNodeClick(nodeId) {
        // Select node (highlight in blue)
        // Update selected node state
        // Trigger selection events
    }
    
    handleVisibilityToggle(nodeId) {
        // Toggle node visibility in Octane
        // Update UI to reflect new state
    }
    
    handleExpandCollapse(nodeId) {
        // Toggle node expanded state
        // Animate expand/collapse transition
        // Update triangle icon
    }
}
```

#### NodeGraphEditor.js
```javascript
class NodeGraphEditor {
    constructor(sceneOutliner, client) {
        this.sceneOutliner = sceneOutliner;
        this.client = client;
        this.contextMenu = null;
    }
    
    showContextMenu(event, nodeId) {
        // Create context menu DOM element
        // Position menu at mouse location
        // Populate with node-specific options
        // Handle viewport boundary constraints
    }
    
    createNodeTypeMenu() {
        // Generate hierarchical menu structure
        // Organize by Geometry, Lights, Materials, Cameras
        // Create hover-triggered submenus
    }
    
    async createNode(nodeType, parentId) {
        // Call client.createNode()
        // Update scene outliner with new node
        // Log operation in activity log
    }
    
    hideContextMenu() {
        // Remove context menu from DOM
        // Clean up event listeners
    }
}
```

#### WebGL Rendering (shared/webgl-utils.js)
```javascript
class WebGLRenderer {
    constructor(canvasId) {
        this.canvas = document.getElementById(canvasId);
        this.gl = this.initWebGL();
        this.shaderProgram = this.createShaderProgram();
        this.camera = new Camera();
    }
    
    initWebGL() {
        // Try WebGL 2.0, fallback to WebGL 1.0
        // Set up WebGL context with proper settings
    }
    
    createShaderProgram() {
        // Compile vertex and fragment shaders
        // Link shader program
        // Set up attribute and uniform locations
    }
    
    render() {
        // Clear canvas
        // Set up camera matrices
        // Render 3D geometry
        // Handle animations
    }
    
    handleMouseInput(event) {
        // Convert mouse coordinates to 3D camera movement
        // Update camera position/rotation
        // Trigger re-render
    }
}

class Camera {
    constructor() {
        this.position = [5, 3, 8];
        this.rotation = [0, 0, 0];
        this.fov = 45;
    }
    
    getViewMatrix() {
        // Calculate view matrix from position/rotation
    }
    
    getProjectionMatrix(aspect) {
        // Calculate projection matrix from FOV and aspect ratio
    }
    
    orbit(deltaX, deltaY) {
        // Orbit camera around scene center
    }
    
    pan(deltaX, deltaY) {
        // Pan camera horizontally and vertically
    }
    
    zoom(delta) {
        // Zoom camera in/out
    }
}
```

### CSS Styling Requirements

#### Main Styles (css/main.css)
```css
/* Professional dark theme */
body {
    background-color: #2c3e50;
    color: #ecf0f1;
    font-family: 'Segoe UI', 'Roboto', sans-serif;
    margin: 0;
    padding: 0;
}

/* Three-panel layout */
.main-container {
    display: grid;
    grid-template-columns: 300px 1fr 400px;
    grid-template-rows: auto auto 1fr auto;
    height: 100vh;
}

/* Scene outliner styling */
.scene-outliner {
    background-color: #34495e;
    border-right: 1px solid #7f8c8d;
    overflow-y: auto;
}

.tree-node {
    padding: 4px 8px;
    cursor: pointer;
    user-select: none;
}

.tree-node:hover {
    background-color: #4a5f7a;
}

.tree-node.selected {
    background-color: #3498db;
}

.tree-node-content {
    display: flex;
    align-items: center;
    gap: 8px;
}

.tree-triangle {
    width: 12px;
    text-align: center;
    cursor: pointer;
}

.tree-icon {
    width: 16px;
    text-align: center;
}

/* 3D viewport styling */
.webgl-viewport {
    background-color: #1a252f;
    position: relative;
}

.webgl-canvas {
    width: 100%;
    height: 100%;
    display: block;
}

/* Activity log styling */
.activity-log {
    background-color: #2c3e50;
    border-left: 1px solid #7f8c8d;
    display: flex;
    flex-direction: column;
}

.log-content {
    flex: 1;
    overflow-y: auto;
    padding: 8px;
    font-family: 'Consolas', 'Monaco', monospace;
    font-size: 12px;
}

.log-entry {
    margin-bottom: 4px;
    word-wrap: break-word;
}

.log-entry.success { color: #2ecc71; }
.log-entry.error { color: #e74c3c; }
.log-entry.info { color: #ecf0f1; }

/* Context menu styling */
.context-menu {
    position: fixed;
    background-color: #34495e;
    border: 1px solid #7f8c8d;
    border-radius: 4px;
    box-shadow: 0 4px 12px rgba(0, 0, 0, 0.3);
    z-index: 1000;
    min-width: 180px;
}

.context-menu-item {
    padding: 8px 16px;
    cursor: pointer;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.context-menu-item:hover {
    background-color: #4a5f7a;
}

.context-submenu {
    position: absolute;
    left: 100%;
    top: 0;
    background-color: #34495e;
    border: 1px solid #7f8c8d;
    border-radius: 4px;
    box-shadow: 0 4px 12px rgba(0, 0, 0, 0.3);
    min-width: 160px;
}
```

#### OTOY Theme (css/otoy-theme.css)
```css
/* OTOY brand colors and styling */
:root {
    --otoy-red: #e74c3c;
    --otoy-dark: #2c3e50;
    --otoy-light: #ecf0f1;
    --otoy-accent: #3498db;
}

.otoy-logo {
    height: 32px;
    width: auto;
}

.connection-led {
    width: 12px;
    height: 12px;
    border-radius: 50%;
    display: inline-block;
    margin-left: 8px;
}

.connection-led.ready { background-color: #f39c12; }
.connection-led.connected { background-color: #2ecc71; }
.connection-led.error { background-color: #e74c3c; }

.control-button {
    background-color: #34495e;
    border: 1px solid #7f8c8d;
    color: #ecf0f1;
    padding: 8px 12px;
    border-radius: 4px;
    cursor: pointer;
    font-size: 16px;
}

.control-button:hover {
    background-color: #4a5f7a;
}

.control-button:disabled {
    opacity: 0.5;
    cursor: not-allowed;
}

.toggle-switch {
    position: relative;
    display: inline-block;
    width: 48px;
    height: 24px;
}

.toggle-switch input {
    opacity: 0;
    width: 0;
    height: 0;
}

.toggle-slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: #7f8c8d;
    transition: 0.3s;
    border-radius: 24px;
}

.toggle-slider:before {
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

input:checked + .toggle-slider {
    background-color: var(--otoy-red);
}

input:checked + .toggle-slider:before {
    transform: translateX(24px);
}
```

### Development Tools Implementation

#### Cache Busting (js/CacheBuster.js)
```javascript
class CacheBuster {
    constructor() {
        this.version = this.generateVersion();
        this.showIndicator();
    }
    
    generateVersion() {
        return new Date().toISOString().replace(/[:.]/g, '-').slice(0, -5);
    }
    
    showIndicator() {
        const indicator = document.createElement('div');
        indicator.textContent = `🔄 DEV v${this.version}`;
        indicator.style.cssText = `
            position: fixed;
            top: 10px;
            left: 10px;
            background: rgba(0,0,0,0.7);
            color: white;
            padding: 4px 8px;
            border-radius: 4px;
            font-size: 12px;
            z-index: 9999;
        `;
        document.body.appendChild(indicator);
    }
    
    bustCache(url) {
        return `${url}?v=${this.version}`;
    }
}
```

#### Debug Console (js/DebugConsole.js)
```javascript
class DebugConsole {
    constructor() {
        this.visible = false;
        this.logs = [];
        this.createConsole();
        this.setupKeyboardShortcut();
        this.interceptConsole();
    }
    
    createConsole() {
        this.console = document.createElement('div');
        this.console.style.cssText = `
            position: fixed;
            bottom: 0;
            left: 0;
            right: 0;
            height: 300px;
            background: rgba(0,0,0,0.9);
            color: #00ff00;
            font-family: monospace;
            font-size: 12px;
            padding: 10px;
            overflow-y: auto;
            z-index: 10000;
            display: none;
        `;
        document.body.appendChild(this.console);
    }
    
    setupKeyboardShortcut() {
        document.addEventListener('keydown', (e) => {
            if (e.ctrlKey && e.key === 'd') {
                e.preventDefault();
                this.toggle();
            }
        });
    }
    
    toggle() {
        this.visible = !this.visible;
        this.console.style.display = this.visible ? 'block' : 'none';
    }
    
    interceptConsole() {
        const originalLog = console.log;
        const originalError = console.error;
        const originalWarn = console.warn;
        
        console.log = (...args) => {
            this.addLog('LOG', args);
            originalLog.apply(console, args);
        };
        
        console.error = (...args) => {
            this.addLog('ERROR', args);
            originalError.apply(console, args);
        };
        
        console.warn = (...args) => {
            this.addLog('WARN', args);
            originalWarn.apply(console, args);
        };
    }
    
    addLog(type, args) {
        const timestamp = new Date().toLocaleTimeString();
        const message = args.map(arg => 
            typeof arg === 'object' ? JSON.stringify(arg) : String(arg)
        ).join(' ');
        
        const logEntry = `[${timestamp}] ${type}: ${message}`;
        this.logs.push(logEntry);
        
        if (this.visible) {
            this.updateDisplay();
        }
    }
    
    updateDisplay() {
        this.console.innerHTML = this.logs
            .slice(-100) // Keep last 100 logs
            .map(log => `<div>${log}</div>`)
            .join('');
        this.console.scrollTop = this.console.scrollHeight;
    }
}
```

### API Integration Requirements

#### Proxy Server Communication
The web application communicates with Octane via a Python proxy server that translates HTTP requests to gRPC calls:

```javascript
// Example API call structure
async makeGrpcCall(service, method, data = {}) {
    const callId = ++this.callId;
    const url = `${this.serverUrl}/${method}`;
    
    const response = await fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'X-Call-Id': callId.toString()
        },
        body: JSON.stringify(data)
    });
    
    if (!response.ok) {
        throw new Error(`HTTP ${response.status}: ${response.statusText}`);
    }
    
    return await response.json();
}
```

#### Required API Endpoints
- `GetCamera` - Retrieve current camera state from Octane
- `SetCamera` - Update camera position in Octane
- `GetMeshes` - Get list of geometry in scene
- `buildSceneTree` - Get hierarchical scene structure
- `CreateNode` - Create new node in Octane scene
- `SetNodeVisibility` - Toggle node visibility
- `GetNodeProperties` - Retrieve node properties

### Error Handling and Resilience

#### Connection Management
```javascript
class ConnectionManager {
    constructor(client) {
        this.client = client;
        this.retryCount = 0;
        this.maxRetries = 5;
        this.retryDelay = 1000; // Start with 1 second
    }
    
    async connectWithRetry() {
        try {
            await this.client.connect();
            this.retryCount = 0;
            this.retryDelay = 1000;
            return true;
        } catch (error) {
            if (this.retryCount < this.maxRetries) {
                this.retryCount++;
                this.retryDelay *= 2; // Exponential backoff
                
                setTimeout(() => {
                    this.connectWithRetry();
                }, this.retryDelay);
            }
            return false;
        }
    }
}
```

#### Graceful Degradation
- **Offline Mode**: Show cached scene data when connection unavailable
- **Mock Data**: Provide sample scene structure for demonstration
- **Error Messages**: Clear, actionable error messages for users
- **Retry Logic**: Automatic reconnection with exponential backoff

### Testing and Quality Assurance

#### Browser Compatibility
- **Chrome 80+**: Full WebGL 2.0 support
- **Firefox 75+**: Full WebGL 2.0 support  
- **Safari 13+**: WebGL 1.0 fallback
- **Edge 80+**: Full WebGL 2.0 support

#### Mobile Support
- **iOS Safari**: Touch controls and responsive layout
- **Android Chrome**: Full functionality with touch optimization
- **Performance**: Maintain 30+ FPS on mobile devices

#### Accessibility Testing
- **Screen Readers**: NVDA, JAWS, VoiceOver compatibility
- **Keyboard Navigation**: Tab order and keyboard shortcuts
- **High Contrast**: Windows High Contrast mode support
- **Reduced Motion**: Respect prefers-reduced-motion setting

This reproduction prompt provides comprehensive requirements for creating a professional-quality web application that integrates with Octane Render via gRPC, with detailed specifications for both user experience and technical implementation.