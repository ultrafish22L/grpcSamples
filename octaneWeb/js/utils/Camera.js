/**
 * Camera System for Octane Integration
 * 
 * Centralized camera management system that handles:
 * - Spherical coordinate system for intuitive camera controls
 * - Mouse interaction (orbit, pan, zoom)
 * - Coordinate system conversions (spherical ↔ cartesian)
 * - Synchronization with Octane service
 * - Throttled updates for performance
 * 
 * Coordinate System:
 * - Spherical: (radius, theta, phi) where theta=azimuth, phi=elevation
 * - Cartesian: (x, y, z) world coordinates
 * - Center: Target point the camera looks at
 * 
 * Mouse Controls:
 * - Right Click + Drag: Orbit camera around target
 * - Left Click + Drag: Pan camera target
 * - Mouse Wheel: Zoom in/out (adjust radius)
 */
class Camera {
    /**
     * Initialize camera system
     * @param {Object} client - OctaneWebClient instance for API calls
     * @param {Object} options - Camera configuration options
     */
    constructor(client, options = {}) {
        this.client = client;
        
        // Camera state in spherical coordinates
        this.state = {
            // Spherical coordinates (intuitive for orbit controls)
            radius: options.radius || 20.0,        // Distance from target
            theta: options.theta || 0.0,           // Azimuth angle (horizontal rotation)
            phi: options.phi || 0.0,               // Elevation angle (vertical rotation)
            center: options.center || [0.0, 0.0, 0.0], // Target point (what camera looks at)
            
            // Camera settings
            fov: options.fov || 45.0,              // Field of view
            sensitivity: options.sensitivity || 0.01, // Mouse sensitivity
            zoomSpeed: options.zoomSpeed || 0.1    // Zoom sensitivity
        };
        
        // Mouse interaction state
        this.mouse = {
            dragging: false,    // Right-click orbit mode
            panning: false,     // Left-click pan mode
            lastX: 0,          // Last mouse X position
            lastY: 0           // Last mouse Y position
        };
        
        // Synchronization settings
        this.sync = {
            enabled: true,              // Enable/disable Octane sync
            throttle: 50,              // Minimum time between sync calls (ms)
            lastSyncTime: 0,           // Last sync timestamp
            syncCount: 0               // Total sync operations performed
        };
        
        // Event listeners for cleanup
        this.eventListeners = [];
        
        console.log('Camera system initialized');
    }
    
    /**
     * Initialize camera from Octane's current state
     * Queries Octane for current camera position/target and updates internal state
     */
    async initializeFromOctane() {
        try {
            const position = await this.client.getCameraPosition();
            const target = await this.client.getCameraTarget();
            
            if (position && target) {
                // Update target (center point)
                this.state.center = [target.x, target.y, target.z];
                
                // Calculate spherical coordinates from cartesian position
                const dx = position.x - target.x;
                const dy = position.y - target.y;
                const dz = position.z - target.z;
                
                this.state.radius = Math.sqrt(dx*dx + dy*dy + dz*dz);
                this.state.theta = Math.atan2(dz, dx);
                this.state.phi = Math.asin(dy / this.state.radius);
                
                console.log(`Camera initialized from Octane: radius=${this.state.radius.toFixed(2)}, theta=${this.state.theta.toFixed(2)}, phi=${this.state.phi.toFixed(2)}`);
                return true;
            }
        } catch (error) {
            console.warn(' Failed to initialize camera from Octane:', error);
            return false;
        }
    }
    
    /**
     * Convert spherical coordinates to cartesian position
     * Uses consistent coordinate system across all viewport implementations
     * @returns {Array} [x, y, z] camera position in world coordinates
     */
    getCartesianPosition() {
        const x = this.state.center[0] + this.state.radius * Math.sin(this.state.theta) * Math.cos(this.state.phi);
        const y = this.state.center[1] + this.state.radius * Math.sin(this.state.phi);
        const z = this.state.center[2] + this.state.radius * Math.cos(this.state.theta) * Math.cos(this.state.phi);
        
        return [x, y, z];
    }
    
    /**
     * Get camera target position
     * @returns {Array} [x, y, z] target position (center point)
     */
    getTarget() {
        return [...this.state.center];
    }
    
    /**
     * Setup mouse event handlers for camera control
     * @param {HTMLElement} element - DOM element to attach mouse events to
     */
    setupMouseControls(element) {
        // Store element reference for cleanup
        this.controlElement = element;
        
        // Mouse down - start drag operation
        const onMouseDown = (e) => {
            if (e.button === 2) { // Right button = PAN
                this.mouse.panning = true;
                element.style.cursor = 'move';
            } else if (e.button === 0) { // Left button = ORBIT
                this.mouse.dragging = true;
                element.style.cursor = 'grabbing';
            }
            
            this.mouse.lastX = e.clientX;
            this.mouse.lastY = e.clientY;
            e.preventDefault();
        };
        
        // Mouse move - handle drag operations
        const onMouseMove = (e) => {
            if (this.mouse.dragging || this.mouse.panning) {
                const deltaX = e.clientX - this.mouse.lastX;
                const deltaY = e.clientY - this.mouse.lastY;
                
                if (this.mouse.dragging) {
                    // RIGHT CLICK: Orbit camera around target
                    this.orbitCamera(deltaX, deltaY);
                } else if (this.mouse.panning) {
                    // LEFT CLICK: Pan camera target
                    this.panCamera(deltaX, deltaY);
                }
                
                this.mouse.lastX = e.clientX;
                this.mouse.lastY = e.clientY;
                
                // Sync with Octane (throttled)
                this.syncToOctane();
            }
        };
        
        // Mouse up - end drag operation
        const onMouseUp = () => {
            this.mouse.dragging = false;
            this.mouse.panning = false;
            element.style.cursor = 'grab';

//            this.syncToOctane();
        };
        
        // Mouse wheel - zoom camera
        const onWheel = (e) => {
            this.zoomCamera(e.deltaY);
            this.syncToOctane();
            e.preventDefault();
        };
        
        // Prevent context menu
        const onContextMenu = (e) => e.preventDefault();
        
        // Attach event listeners
        element.addEventListener('mousedown', onMouseDown);
        element.addEventListener('mousemove', onMouseMove);
        element.addEventListener('mouseup', onMouseUp);
        element.addEventListener('wheel', onWheel);
        element.addEventListener('contextmenu', onContextMenu);
        
        // Store listeners for cleanup
        this.eventListeners = [
            { element, event: 'mousedown', handler: onMouseDown },
            { element, event: 'mousemove', handler: onMouseMove },
            { element, event: 'mouseup', handler: onMouseUp },
            { element, event: 'wheel', handler: onWheel },
            { element, event: 'contextmenu', handler: onContextMenu }
        ];
        
        console.log('Mouse controls attached to camera system');
    }
    
    /**
     * Orbit camera around target point
     * @param {number} deltaX - Horizontal mouse movement
     * @param {number} deltaY - Vertical mouse movement
     */
    orbitCamera(deltaX, deltaY) {
        // Update spherical coordinates
        this.state.theta += deltaX * this.state.sensitivity;
        this.state.phi += deltaY * this.state.sensitivity;
        
        // Clamp phi to prevent gimbal lock
        this.state.phi = Math.max(-Math.PI/2 + 0.1, Math.min(Math.PI/2 - 0.1, this.state.phi));
        
        // console.log(`Orbiting: theta=${this.state.theta.toFixed(2)}, phi=${this.state.phi.toFixed(2)}`);
    }
    
    /**
     * Pan camera target (move what the camera is looking at)
     * @param {number} deltaX - Horizontal mouse movement
     * @param {number} deltaY - Vertical mouse movement
     */
    panCamera(deltaX, deltaY) {
        // Calculate right and up vectors for camera-relative panning
        const right = [
            Math.cos(this.state.theta + Math.PI/2),
            0,
            Math.sin(this.state.theta + Math.PI/2)
        ];
        const up = [0, 1, 0];
        
        // Pan speed scales with distance from target
        const panSpeed = this.state.radius * 0.001;
        
        // Update target position
        this.state.center[0] -= right[0] * deltaX * panSpeed;
        this.state.center[1] += up[1] * deltaY * panSpeed;
        this.state.center[2] -= right[2] * deltaX * panSpeed;
        
        console.log(`Panning: center=[${this.state.center.map(v => v.toFixed(2)).join(', ')}]`);
    }
    
    /**
     * Zoom camera (adjust distance from target)
     * @param {number} delta - Mouse wheel delta
     */
    zoomCamera(delta) {
        const oldRadius = this.state.radius;
        this.state.radius *= (1 + delta * this.state.zoomSpeed * 0.001);
        this.state.radius = Math.max(0.1, Math.min(1000, this.state.radius));
        
        console.log(`Zooming: ${oldRadius.toFixed(2)} → ${this.state.radius.toFixed(2)}`);
    }
    
    /**
     * Synchronize camera state with Octane
     * Throttled to prevent excessive API calls
     */
    async syncToOctane() {
        if (!this.sync.enabled) return;
        if (!this.client.isReady()) return;
        
        // Throttle sync calls
        const now = Date.now();
        if (now - this.sync.lastSyncTime < this.sync.throttle) return;
        
        try {
            // Get current camera position in cartesian coordinates
            const position = this.getCartesianPosition();
            const target = this.getTarget();
            
            // Update Octane camera
            if (await this.client.setCameraPositionAndTarget(position[0], position[1], position[2], target[0], target[1], target[2])) {
                
                // Trigger Octane display update
                await this.triggerOctaneUpdate();
                
                this.sync.lastSyncTime = now;
                this.sync.syncCount++;
                
                console.log(`Camera synced: pos=[${position.map(v => v.toFixed(2)).join(', ')}], target=[${target.map(v => v.toFixed(2)).join(', ')}]`);
            }
            
        } catch (error) {
            console.warn(' Camera sync error:', error);
        }
    }
    
    /**
     * Trigger Octane display update via ApiChangeManager::update()
     * This is critical for refreshing Octane's display after camera changes
     */
    async triggerOctaneUpdate() {
        try {
//            const result = window.grpcApi.makeApiCall('ApiChangeManager/update');            
        } catch (error) {
            // Don't log connection errors as they're expected when Octane is not running
            if (!error.message.includes('Connection') && !error.message.includes('Network')) {
                console.warn(' Failed to trigger Octane update:', error);
            }
        }
    }
    
    /**
     * Get camera statistics for debugging
     * @returns {Object} Camera state information
     */
    getStats() {
        const position = this.getCartesianPosition();
        return {
            position: position,
            target: this.getTarget(),
            radius: this.state.radius,
            theta: this.state.theta,
            phi: this.state.phi,
            syncCount: this.sync.syncCount,
            lastSyncTime: this.sync.lastSyncTime
        };
    }
    
    /**
     * Enable/disable camera synchronization with Octane
     * @param {boolean} enabled - Whether to sync camera changes
     */
    setSyncEnabled(enabled) {
        this.sync.enabled = enabled;
        console.log(`Camera sync ${enabled ? 'enabled' : 'disabled'}`);
    }
    
    /**
     * Update camera sensitivity
     * @param {number} sensitivity - Mouse sensitivity multiplier
     */
    setSensitivity(sensitivity) {
        this.state.sensitivity = sensitivity;
        console.log(`Camera sensitivity set to ${sensitivity}`);
    }
    
    /**
     * Clean up event listeners and resources
     */
    destroy() {
        // Remove event listeners
        this.eventListeners.forEach(({ element, event, handler }) => {
            element.removeEventListener(event, handler);
        });
        this.eventListeners = [];
        
        // Reset cursor
        if (this.controlElement) {
            this.controlElement.style.cursor = '';
        }
        
        console.log('Camera system destroyed');
    }
}

// Register Camera class globally
if (typeof window !== 'undefined') {
    window.Camera = Camera;
    console.log('Camera class registered globally');
}