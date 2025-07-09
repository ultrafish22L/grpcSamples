/**
 * LiveLink.js - Browser-compatible gRPC-Web client for Octane LiveLink
 * Provides real-time communication with Octane Render via gRPC-Web
 * 
 * This version uses gRPC-Web instead of WebSocket for direct communication
 * with Octane's gRPC server through a gRPC-Web proxy.
 */

// Import gRPC-Web generated stubs
// Note: In a real browser environment, you would use ES6 imports or script tags
// For now, we'll access them from the global scope after loading via script tags

class LiveLinkClient {
    constructor(serverUrl = 'http://127.0.0.1:8080') {
        this.serverUrl = serverUrl;
        this.client = null;
        this.connected = false;
        this.eventListeners = new Map();
        
        // Connection state
        this.connectionState = 'disconnected'; // 'disconnected', 'connecting', 'connected', 'error'
        this.lastError = null;
        
        // Performance tracking
        this.callCount = 0;
        this.lastCallTime = 0;
        this.avgResponseTime = 0;
        
        // Camera synchronization
        this.cameraSyncActive = false;
        this.cameraSyncInterval = null;
        this.cameraSyncCallback = null;
    }

    /**
     * Connect to the Octane gRPC server via gRPC-Web
     */
    async connect() {
        if (this.connected || this.connectionState === 'connecting') {
            return Promise.resolve();
        }

        return new Promise((resolve, reject) => {
            try {
                this.connectionState = 'connecting';
                this.emit('connectionStateChanged', 'connecting');
                
                console.log('Attempting gRPC-Web connection to:', this.serverUrl);
                
                // Try to create gRPC-Web client
                try {
                    // Check if gRPC-Web generated classes are available
                    if (typeof proto === 'undefined' || 
                        !proto.livelinkapi || 
                        !proto.livelinkapi.LiveLinkServiceClient) {
                        
                        const error = new Error('gRPC-Web generated classes not found. Make sure to include the generated JavaScript files in your HTML.');
                        console.error(error.message);
                        this.lastError = error;
                        this.connectionState = 'error';
                        this.emit('connectionStateChanged', 'error');
                        this.emit('error', error);
                        reject(error);
                        return;
                    }
                    
                    console.log('Creating gRPC-Web client...');
                    this.client = new proto.livelinkapi.LiveLinkServiceClient(this.serverUrl);
                    
                    // Test connection with a simple call
                    this.testConnection().then(() => {
                        this.connected = true;
                        this.connectionState = 'connected';
                        this.emit('connectionStateChanged', 'connected');
                        this.emit('connected');
                        console.log('gRPC-Web connection established');
                        resolve();
                    }).catch((error) => {
                        console.error('gRPC-Web connection test failed:', error);
                        this.lastError = error;
                        this.connectionState = 'error';
                        this.emit('connectionStateChanged', 'error');
                        this.emit('error', error);
                        reject(error);
                    });
                    
                } catch (error) {
                    console.error('gRPC-Web client creation failed:', error);
                    this.lastError = error;
                    this.connectionState = 'error';
                    this.emit('connectionStateChanged', 'error');
                    this.emit('error', error);
                    reject(error);
                }
                
            } catch (error) {
                console.error('Connection error:', error);
                this.lastError = error;
                this.connectionState = 'error';
                this.emit('connectionStateChanged', 'error');
                this.emit('error', error);
                reject(error);
            }
        });
    }



    /**
     * Test gRPC-Web connection with a simple call
     */
    async testConnection() {
        if (!this.client) {
            throw new Error('No gRPC client available');
        }

        return new Promise((resolve, reject) => {
            try {
                // Create an empty request for testing
                const request = new proto.livelinkapi.Empty();
                
                // Try to call a simple method (like GetCamera)
                this.client.getCamera(request, {}, (err, response) => {
                    if (err) {
                        reject(err);
                    } else {
                        resolve(response);
                    }
                });
                
                // Set a timeout for the test
                setTimeout(() => {
                    reject(new Error('Connection test timeout'));
                }, 5000);
                
            } catch (error) {
                reject(error);
            }
        });
    }

    /**
     * Disconnect from the server
     */
    async disconnect() {
        if (!this.connected) {
            return;
        }

        // Stop camera sync if active
        if (this.cameraSyncActive) {
            this.cameraSyncActive = false;
            if (this.cameraSyncInterval) {
                clearInterval(this.cameraSyncInterval);
                this.cameraSyncInterval = null;
            }
            this.cameraSyncCallback = null;
        }

        this.connected = false;
        this.connectionState = 'disconnected';
        this.client = null;
        this.emit('connectionStateChanged', 'disconnected');
        this.emit('disconnected');
    }

    /**
     * Make a gRPC call with proper error handling
     */
    async makeGrpcCall(methodName, request) {
        const startTime = Date.now();
        this.callCount++;
        
        if (!this.client) {
            const error = new Error('No gRPC client available. Make sure to connect first.');
            this.lastError = error;
            throw error;
        }
        
        console.log(`gRPC call: ${methodName}`, request);
        
        return new Promise((resolve, reject) => {
            try {
                this.client[methodName](request, {}, (err, response) => {
                    if (err) {
                        console.error(`gRPC call failed: ${methodName}`, err);
                        this.lastError = err;
                        this.updatePerformanceStats(startTime);
                        reject(err);
                    } else {
                        this.updatePerformanceStats(startTime);
                        resolve(response);
                    }
                });
            } catch (error) {
                console.error(`gRPC call exception: ${methodName}`, error);
                this.lastError = error;
                this.updatePerformanceStats(startTime);
                reject(error);
            }
        });
    }

    /**
     * Update performance statistics
     */
    updatePerformanceStats(startTime) {
        const responseTime = Date.now() - startTime;
        this.lastCallTime = responseTime;
        this.avgResponseTime = (this.avgResponseTime * (this.callCount - 1) + responseTime) / this.callCount;
    }

    // ===== LiveLink Service Methods =====

    /**
     * Set camera state in Octane
     */
    async setCamera(cameraState) {
        const request = this.createCameraStateMessage(cameraState);
        return this.makeGrpcCall('setCamera', request);
    }

    /**
     * Get current camera state from Octane
     */
    async getCamera() {
        const request = new proto.livelinkapi.Empty();
        return this.makeGrpcCall('getCamera', request);
    }

    /**
     * Get list of available meshes from Octane
     */
    async getMeshes() {
        const request = new proto.livelinkapi.Empty();
        return this.makeGrpcCall('getMeshes', request);
    }

    /**
     * Get mesh data by ID
     */
    async getMesh(meshId) {
        const request = new proto.livelinkapi.MeshRequest();
        request.setObjecthandle(meshId);
        return this.makeGrpcCall('getMesh', request);
    }

    // ===== Helper Methods =====

    /**
     * Create a CameraState protobuf message from JavaScript object
     */
    createCameraStateMessage(cameraState) {
        // Create a proper protobuf message
        const message = new proto.livelinkapi.CameraState();
        
        if (cameraState.position) {
            const pos = new proto.livelinkapi.Vec3();
            pos.setX(cameraState.position.x || 0);
            pos.setY(cameraState.position.y || 0);
            pos.setZ(cameraState.position.z || 0);
            message.setPosition(pos);
        }
        
        if (cameraState.target) {
            const target = new proto.livelinkapi.Vec3();
            target.setX(cameraState.target.x || 0);
            target.setY(cameraState.target.y || 0);
            target.setZ(cameraState.target.z || 0);
            message.setTarget(target);
        }
        
        if (cameraState.up) {
            const up = new proto.livelinkapi.Vec3();
            up.setX(cameraState.up.x || 0);
            up.setY(cameraState.up.y || 1);
            up.setZ(cameraState.up.z || 0);
            message.setUp(up);
        }
        
        if (cameraState.fov !== undefined) {
            message.setFov(cameraState.fov);
        }
        
        return message;
    }

    /**
     * Toggle camera synchronization
     */
    toggleCameraSync(getCameraCallback) {
        if (!this.connected) {
            console.warn('Cannot toggle camera sync: not connected');
            return false;
        }

        this.cameraSyncActive = !this.cameraSyncActive;
        
        if (this.cameraSyncActive) {
            // Start camera sync interval
            this.cameraSyncCallback = getCameraCallback;
            this.cameraSyncInterval = setInterval(() => {
                if (this.cameraSyncCallback) {
                    const cameraState = this.cameraSyncCallback();
                    this.setCamera(cameraState).catch(error => {
                        console.error('Camera sync error:', error);
                    });
                }
            }, 100); // Sync every 100ms
            
            console.log('Camera synchronization started');
        } else {
            // Stop camera sync
            if (this.cameraSyncInterval) {
                clearInterval(this.cameraSyncInterval);
                this.cameraSyncInterval = null;
            }
            this.cameraSyncCallback = null;
            console.log('Camera synchronization stopped');
        }
        
        return this.cameraSyncActive;
    }

    /**
     * Get connection statistics
     */
    getStats() {
        return {
            connected: this.connected,
            connectionState: this.connectionState,
            serverUrl: this.serverUrl,
            callCount: this.callCount,
            lastCallTime: this.lastCallTime,
            avgResponseTime: Math.round(this.avgResponseTime),
            lastError: this.lastError ? this.lastError.message : null,
            cameraSyncActive: this.cameraSyncActive || false
        };
    }

    /**
     * Check if the client is ready for requests
     */
    isReady() {
        return this.connected && this.client;
    }

    // ===== Event System =====

    /**
     * Add event listener
     */
    on(event, callback) {
        if (!this.eventListeners.has(event)) {
            this.eventListeners.set(event, []);
        }
        this.eventListeners.get(event).push(callback);
    }

    /**
     * Remove event listener
     */
    off(event, callback) {
        if (this.eventListeners.has(event)) {
            const listeners = this.eventListeners.get(event);
            const index = listeners.indexOf(callback);
            if (index > -1) {
                listeners.splice(index, 1);
            }
        }
    }

    /**
     * Emit event to all listeners
     */
    emit(event, data) {
        if (this.eventListeners.has(event)) {
            this.eventListeners.get(event).forEach(callback => {
                try {
                    callback(data);
                } catch (error) {
                    console.error('Event listener error:', error);
                }
            });
        }
    }
}

// ===== LiveLink Manager (Singleton) =====

class LiveLinkManager {
    constructor() {
        this.client = null;
        this.defaultServerUrl = 'http://127.0.0.1:8080'; // gRPC-Web proxy URL
    }

    /**
     * Get or create the LiveLink client
     */
    getClient(serverUrl = null) {
        if (!this.client) {
            this.client = new LiveLinkClient(serverUrl || this.defaultServerUrl);
        }
        return this.client;
    }

    /**
     * Connect to Octane LiveLink service
     */
    async connect(serverUrl = null) {
        const client = this.getClient(serverUrl);
        await client.connect();
        return client;
    }

    /**
     * Disconnect from service
     */
    async disconnect() {
        if (this.client) {
            await this.client.disconnect();
        }
    }

    /**
     * Get current client instance
     */
    getCurrentClient() {
        return this.client;
    }
}

// Create global instance
const liveLinkManager = new LiveLinkManager();

// Export for use in HTML pages
if (typeof window !== 'undefined') {
    window.LiveLinkClient = LiveLinkClient;
    window.LiveLinkManager = LiveLinkManager;
    window.liveLinkManager = liveLinkManager;
}

// Export for Node.js/module systems
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        LiveLinkClient,
        LiveLinkManager,
        liveLinkManager
    };
}