/**
 * Render Viewport Component
 * 3D viewport for scene rendering and camera controls
 */

class RenderViewport extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        this.canvas = element;
        this.gl = null;
        this.camera = { x: 0, y: 0, z: 5, rotX: 0, rotY: 0 };
        this.isDragging = false;
        this.lastMousePos = { x: 0, y: 0 };
        this.renderState = {};
    }
    
    async onInitialize() {
        this.initWebGL();
        this.setupControls();
        this.startRenderLoop();
    }
    
    setupEventListeners() {
        // Listen for render updates
        this.client.on('ui:renderUpdate', (renderState) => {
            this.updateRender(renderState);
        });
        
        // Mouse controls
        this.addEventListener(this.canvas, 'mousedown', this.handleMouseDown.bind(this));
        this.addEventListener(this.canvas, 'mousemove', this.handleMouseMove.bind(this));
        this.addEventListener(this.canvas, 'mouseup', this.handleMouseUp.bind(this));
        this.addEventListener(this.canvas, 'wheel', this.handleWheel.bind(this));
        
        // Touch controls for mobile
        this.addEventListener(this.canvas, 'touchstart', this.handleTouchStart.bind(this));
        this.addEventListener(this.canvas, 'touchmove', this.handleTouchMove.bind(this));
        this.addEventListener(this.canvas, 'touchend', this.handleTouchEnd.bind(this));
    }
    
    initWebGL() {
        this.gl = this.canvas.getContext('webgl') || this.canvas.getContext('experimental-webgl');
        
        if (!this.gl) {
            console.error('WebGL not supported');
            this.showWebGLError();
            return;
        }
        
        // Setup WebGL
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.clearColor(0.16, 0.16, 0.16, 1.0); // Match Octane viewport background
        
        console.log('WebGL initialized');
    }
    
    setupControls() {
        // Prevent context menu on right-click
        this.addEventListener(this.canvas, 'contextmenu', (e) => {
            e.preventDefault();
        });
    }
    
    startRenderLoop() {
        const render = () => {
            this.render3D();
            requestAnimationFrame(render);
        };
        requestAnimationFrame(render);
    }
    
    render3D() {
        if (!this.gl) return;
        
        // Clear canvas
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);
        
        // TODO: Implement 3D rendering
        // For now, just clear with background color
    }
    
    updateRender(renderState) {
        this.renderState = renderState;
        // TODO: Update viewport with render data
    }
    
    handleMouseDown(e) {
        this.isDragging = true;
        this.lastMousePos = { x: e.clientX, y: e.clientY };
        this.canvas.style.cursor = 'grabbing';
    }
    
    handleMouseMove(e) {
        if (!this.isDragging) return;
        
        const deltaX = e.clientX - this.lastMousePos.x;
        const deltaY = e.clientY - this.lastMousePos.y;
        
        if (e.buttons === 1) { // Left mouse button - rotate
            this.camera.rotY += deltaX * 0.01;
            this.camera.rotX += deltaY * 0.01;
        } else if (e.buttons === 2) { // Right mouse button - pan
            this.camera.x -= deltaX * 0.01;
            this.camera.y += deltaY * 0.01;
        }
        
        this.lastMousePos = { x: e.clientX, y: e.clientY };
        this.updateCameraInOctane();
    }
    
    handleMouseUp(e) {
        this.isDragging = false;
        this.canvas.style.cursor = 'default';
    }
    
    handleWheel(e) {
        e.preventDefault();
        const delta = e.deltaY > 0 ? 1.1 : 0.9;
        this.camera.z *= delta;
        this.updateCameraInOctane();
    }
    
    handleTouchStart(e) {
        e.preventDefault();
        if (e.touches.length === 1) {
            this.isDragging = true;
            this.lastMousePos = { x: e.touches[0].clientX, y: e.touches[0].clientY };
        }
    }
    
    handleTouchMove(e) {
        e.preventDefault();
        if (!this.isDragging || e.touches.length !== 1) return;
        
        const deltaX = e.touches[0].clientX - this.lastMousePos.x;
        const deltaY = e.touches[0].clientY - this.lastMousePos.y;
        
        this.camera.rotY += deltaX * 0.01;
        this.camera.rotX += deltaY * 0.01;
        
        this.lastMousePos = { x: e.touches[0].clientX, y: e.touches[0].clientY };
        this.updateCameraInOctane();
    }
    
    handleTouchEnd(e) {
        e.preventDefault();
        this.isDragging = false;
    }
    
    async updateCameraInOctane() {
        if (!this.client.isConnected) return;
        
        // Convert camera to Octane format
        const position = [this.camera.x, this.camera.y, this.camera.z];
        const target = [0, 0, 0]; // Look at origin
        const up = [0, 1, 0];
        
        try {
            await this.client.setCamera(position, target, up, 45);
        } catch (error) {
            console.error('Failed to update camera in Octane:', error);
        }
    }
    
    handleResize() {
        if (!this.canvas) return;
        
        const rect = this.canvas.getBoundingClientRect();
        this.canvas.width = rect.width;
        this.canvas.height = rect.height;
        
        if (this.gl) {
            this.gl.viewport(0, 0, rect.width, rect.height);
        }
    }
    
    showWebGLError() {
        this.canvas.style.display = 'none';
        const errorDiv = document.createElement('div');
        errorDiv.className = 'webgl-error';
        errorDiv.innerHTML = `
            <div style="padding: 20px; text-align: center; color: var(--octane-text-muted);">
                <h3>WebGL Not Supported</h3>
                <p>Your browser does not support WebGL, which is required for 3D rendering.</p>
                <p>Please update your browser or enable WebGL in your browser settings.</p>
            </div>
        `;
        this.canvas.parentNode.appendChild(errorDiv);
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = RenderViewport;
} else if (typeof window !== 'undefined') {
    window.RenderViewport = RenderViewport;
}