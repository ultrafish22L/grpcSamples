/**
 * Common WebGL and 3D Utilities
 * Shared utilities for WebGL applications that integrate with Octane LiveLink
 * Contains common rendering patterns, camera synchronization helpers, and mesh utilities
 */

/**
 * WebGL Rendering Utilities
 * Common patterns for WebGL rendering with Octane integration
 */
class WebGLRenderer {
    constructor(canvas) {
        this.canvas = canvas;
        this.gl = null;
        this.initialized = false;
    }

    /**
     * Initialize WebGL context with common settings
     */
    async initialize() {
        this.gl = this.canvas.getContext('webgl2');
        if (!this.gl) {
            throw new Error('WebGL 2.0 not supported');
        }

        // Configure common WebGL state
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.enable(this.gl.CULL_FACE);
        this.gl.cullFace(this.gl.BACK);
        this.gl.clearColor(0.1, 0.1, 0.2, 1.0);

        this.initialized = true;
        return this.gl;
    }

    /**
     * Resize canvas and update viewport
     */
    resize() {
        if (!this.initialized) return;

        const displayWidth = this.canvas.clientWidth;
        const displayHeight = this.canvas.clientHeight;

        if (this.canvas.width !== displayWidth || this.canvas.height !== displayHeight) {
            this.canvas.width = displayWidth;
            this.canvas.height = displayHeight;
            this.gl.viewport(0, 0, displayWidth, displayHeight);
        }
    }

    /**
     * Clear buffers with default settings
     */
    clear() {
        if (!this.initialized) return;
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);
    }
}

/**
 * Camera Synchronization Utilities
 * Helpers for synchronizing cameras between WebGL and Octane
 */
class CameraSyncUtils {
    /**
     * Convert WebGL camera to Octane camera format
     */
    static webglToOctane(camera) {
        const position = camera.getPosition();
        return {
            position: { x: position[0], y: position[1], z: position[2] },
            target: { x: camera.center[0], y: camera.center[1], z: camera.center[2] },
            up: { x: 0, y: 1, z: 0 },
            fov: 45.0
        };
    }

    /**
     * Convert Octane camera to WebGL camera format
     */
    static octaneToWebgl(octaneCamera) {
        return {
            position: [octaneCamera.position.x, octaneCamera.position.y, octaneCamera.position.z],
            target: [octaneCamera.target.x, octaneCamera.target.y, octaneCamera.target.z],
            up: [octaneCamera.up.x, octaneCamera.up.y, octaneCamera.up.z],
            fov: octaneCamera.fov
        };
    }

    /**
     * Generate random camera position for testing
     */
    static generateRandomCamera() {
        return {
            position: { 
                x: Math.random() * 10 - 5, 
                y: Math.random() * 10 - 5, 
                z: 5 
            },
            target: { x: 0, y: 0, z: 0 },
            up: { x: 0, y: 1, z: 0 },
            fov: 45
        };
    }
}

/**
 * Mesh Data Utilities
 * Helpers for working with mesh data from Octane
 */
class MeshDataUtils {
    /**
     * Validate mesh data structure
     */
    static validateMeshData(meshData) {
        if (!meshData) return false;
        if (!meshData.positions || !Array.isArray(meshData.positions)) return false;
        if (meshData.positions.length === 0) return false;
        return true;
    }

    /**
     * Get mesh statistics
     */
    static getMeshStats(meshData) {
        if (!this.validateMeshData(meshData)) {
            return { vertices: 0, faces: 0, valid: false };
        }

        const vertexCount = meshData.positions.length / 3; // Assuming 3 components per vertex
        const faceCount = meshData.vertsPerPoly ? meshData.vertsPerPoly.length : 0;

        return {
            vertices: vertexCount,
            faces: faceCount,
            valid: true,
            hasNormals: !!(meshData.normals && meshData.normals.length > 0),
            hasUVs: !!(meshData.uvs && meshData.uvs.length > 0)
        };
    }

    /**
     * Convert Octane mesh data to WebGL buffers
     */
    static createWebGLBuffers(gl, meshData) {
        if (!this.validateMeshData(meshData)) {
            throw new Error('Invalid mesh data');
        }

        const buffers = {};

        // Position buffer
        buffers.position = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, buffers.position);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(meshData.positions), gl.STATIC_DRAW);

        // Normal buffer (if available)
        if (meshData.normals && meshData.normals.length > 0) {
            buffers.normal = gl.createBuffer();
            gl.bindBuffer(gl.ARRAY_BUFFER, buffers.normal);
            gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(meshData.normals), gl.STATIC_DRAW);
        }

        // UV buffer (if available)
        if (meshData.uvs && meshData.uvs.length > 0) {
            buffers.uv = gl.createBuffer();
            gl.bindBuffer(gl.ARRAY_BUFFER, buffers.uv);
            gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(meshData.uvs), gl.STATIC_DRAW);
        }

        // Index buffer (if available)
        if (meshData.indices && meshData.indices.length > 0) {
            buffers.index = gl.createBuffer();
            gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffers.index);
            gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(meshData.indices), gl.STATIC_DRAW);
        }

        return buffers;
    }
}

/**
 * Performance Monitoring for WebGL Applications
 * Specialized performance tracking for 3D applications
 */
class WebGLPerformanceMonitor {
    constructor() {
        this.frameCount = 0;
        this.lastTime = 0;
        this.fps = 0;
        this.frameTime = 0;
        this.renderTime = 0;
        this.startTime = Date.now();
    }

    /**
     * Update performance metrics
     */
    update(currentTime) {
        this.frameCount++;
        
        if (this.lastTime > 0) {
            this.frameTime = currentTime - this.lastTime;
            
            // Calculate FPS every 60 frames
            if (this.frameCount % 60 === 0) {
                this.fps = Math.round(1000 / this.frameTime);
            }
        }
        
        this.lastTime = currentTime;
    }

    /**
     * Measure render time
     */
    startRender() {
        this.renderStartTime = performance.now();
    }

    /**
     * End render time measurement
     */
    endRender() {
        if (this.renderStartTime) {
            this.renderTime = performance.now() - this.renderStartTime;
        }
    }

    /**
     * Get performance statistics
     */
    getStats() {
        return {
            fps: this.fps,
            frameTime: this.frameTime,
            renderTime: this.renderTime,
            frameCount: this.frameCount,
            uptime: Date.now() - this.startTime
        };
    }

    /**
     * Update DOM elements with performance stats
     */
    updateDisplay(elementIds) {
        const stats = this.getStats();
        
        if (elementIds.fps) {
            const fpsElement = document.getElementById(elementIds.fps);
            if (fpsElement) fpsElement.textContent = stats.fps;
        }
        
        if (elementIds.frameTime) {
            const frameTimeElement = document.getElementById(elementIds.frameTime);
            if (frameTimeElement) frameTimeElement.textContent = `${stats.frameTime.toFixed(1)}ms`;
        }
        
        if (elementIds.renderTime) {
            const renderTimeElement = document.getElementById(elementIds.renderTime);
            if (renderTimeElement) renderTimeElement.textContent = `${stats.renderTime.toFixed(1)}ms`;
        }
    }
}

/**
 * Octane Integration Helpers
 * Common patterns for integrating WebGL applications with Octane LiveLink
 */
class OctaneIntegrationUtils {
    /**
     * Setup standard event handlers for LiveLink client
     */
    static setupLiveLinkEvents(client, logger, onConnected, onDisconnected, onError) {
        if (!client || !logger) return;

        // Remove existing listeners
        if (client.removeAllListeners) {
            client.removeAllListeners();
        }

        // Forward log messages from LiveLink client to activity log
        client.on('log', (logEntry) => {
            const displayMessage = logEntry.cleanMessage || logEntry.message;
            logger.log(displayMessage, logEntry.level);
        });

        // Connection state events
        client.on('connected', () => {
            logger.log('✅ Connected to Octane LiveLink!', 'success');
            if (onConnected) onConnected();
        });

        client.on('disconnected', () => {
            logger.log('Disconnected from server', 'info');
            if (onDisconnected) onDisconnected();
        });

        client.on('error', (error) => {
            logger.log(`❌ Connection error: ${error.message}`, 'error');
            if (onError) onError(error);
        });
    }

    /**
     * Standard UI update for connection state
     */
    static updateConnectionUI(connected, buttonIds) {
        // Update button states
        if (buttonIds.connect) {
            const connectBtn = document.getElementById(buttonIds.connect);
            if (connectBtn) connectBtn.disabled = connected;
        }

        if (buttonIds.disconnect) {
            const disconnectBtn = document.getElementById(buttonIds.disconnect);
            if (disconnectBtn) disconnectBtn.disabled = !connected;
        }

        // Update operation buttons
        if (buttonIds.operations && Array.isArray(buttonIds.operations)) {
            buttonIds.operations.forEach(btnId => {
                const btn = document.getElementById(btnId);
                if (btn) btn.disabled = !connected;
            });
        }

        // Update status display
        if (buttonIds.statusText) {
            const statusText = document.getElementById(buttonIds.statusText);
            if (statusText) {
                statusText.textContent = connected ? 'Connected' : 'Disconnected';
            }
        }

        if (buttonIds.statusSection) {
            const statusSection = document.getElementById(buttonIds.statusSection);
            if (statusSection) {
                statusSection.className = connected 
                    ? 'status-section status-connected' 
                    : 'status-section status-disconnected';
            }
        }
    }
}

/**
 * Animation and Timing Utilities
 * Helpers for smooth animations and timing in WebGL applications
 */
class AnimationUtils {
    /**
     * Smooth interpolation between two values
     */
    static lerp(a, b, t) {
        return a + (b - a) * t;
    }

    /**
     * Smooth interpolation between two 3D vectors
     */
    static lerpVector3(a, b, t) {
        return [
            this.lerp(a[0], b[0], t),
            this.lerp(a[1], b[1], t),
            this.lerp(a[2], b[2], t)
        ];
    }

    /**
     * Easing functions
     */
    static easeInOut(t) {
        return t * t * (3.0 - 2.0 * t);
    }

    static easeInOutCubic(t) {
        return t < 0.5 ? 4 * t * t * t : 1 - Math.pow(-2 * t + 2, 3) / 2;
    }

    /**
     * Create smooth camera transition
     */
    static createCameraTransition(fromCamera, toCamera, duration = 1000) {
        const startTime = Date.now();
        
        return {
            update: function() {
                const elapsed = Date.now() - startTime;
                const t = Math.min(elapsed / duration, 1.0);
                const easedT = AnimationUtils.easeInOutCubic(t);
                
                return {
                    position: AnimationUtils.lerpVector3(fromCamera.position, toCamera.position, easedT),
                    target: AnimationUtils.lerpVector3(fromCamera.target, toCamera.target, easedT),
                    up: AnimationUtils.lerpVector3(fromCamera.up, toCamera.up, easedT),
                    fov: AnimationUtils.lerp(fromCamera.fov, toCamera.fov, easedT),
                    complete: t >= 1.0
                };
            }
        };
    }
}