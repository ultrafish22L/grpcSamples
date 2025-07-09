/**
 * LiveLink.js - Browser-compatible gRPC-Web client for Octane LiveLink
 * Provides HTTP/gRPC-Web communication with Octane's LiveLink service
 */

class LiveLinkClient {
    constructor(serverUrl = 'http://127.0.0.1:51023') {
        this.serverUrl = serverUrl;
        this.connected = false;
        this.requestId = 0;
        this.pendingRequests = new Map();
        this.eventListeners = new Map();
        
        // Connection state
        this.connectionState = 'disconnected'; // 'disconnected', 'connecting', 'connected', 'error'
        this.lastError = null;
        this.reconnectAttempts = 0;
        this.maxReconnectAttempts = 5;
        this.reconnectDelay = 1000; // ms
        this.autoReconnect = true;
        
        // Performance tracking
        this.callCount = 0;
        this.lastCallTime = 0;
        this.avgResponseTime = 0;
    }

    /**
     * Test connection to the Octane LiveLink server
     */
    async connect() {
        if (this.connected || this.connectionState === 'connecting') {
            return Promise.resolve();
        }

        return new Promise(async (resolve, reject) => {
            try {
                this.autoReconnect = true; // Re-enable auto-reconnect
                this.connectionState = 'connecting';
                this.emit('connectionStateChanged', 'connecting');
                
                console.log('Testing gRPC connection to:', this.serverUrl);
                
                // Test connection with a simple health check
                const response = await fetch(`${this.serverUrl}/health`);
                if (!response.ok) {
                    throw new Error(`HTTP ${response.status}: ${response.statusText}`);
                }
                const healthData = await response.json();
                
                if (healthData && healthData.status === 'ok') {
                    console.log('gRPC proxy connection test successful');
                    this.connected = true;
                    this.connectionState = 'connected';
                    this.reconnectAttempts = 0;
                    this.emit('connectionStateChanged', 'connected');
                    this.emit('connected');
                    resolve();
                } else {
                    throw new Error('Proxy health check failed');
                }
                
            } catch (error) {
                console.error('gRPC connection test failed:', error);
                this.connectionState = 'error';
                this.lastError = error;
                this.emit('connectionStateChanged', 'error');
                this.emit('error', this.lastError);
                
                // Disable auto-reconnect on initial connection failure
                if (this.reconnectAttempts === 0) {
                    this.autoReconnect = false;
                }
                reject(this.lastError);
            }
        });
    }

    /**
     * Disconnect from the server
     */
    disconnect() {
        this.autoReconnect = false; // Disable auto-reconnect
        this.connected = false;
        this.connectionState = 'disconnected';
        this.emit('connectionStateChanged', 'disconnected');
        this.emit('disconnected');
    }

    /**
     * Make a HTTP request to the gRPC proxy
     */
    async makeGrpcRequest(method, data, options = {}) {
        const requestId = ++this.requestId;
        const startTime = Date.now();
        
        try {
            const response = await fetch(`${this.serverUrl}/${method}`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Accept': 'application/json',
                    ...options.headers
                },
                body: JSON.stringify(data),
                mode: 'cors'
            });

            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }

            const responseData = await response.json();
            
            // Update performance stats
            const responseTime = Date.now() - startTime;
            this.updateStats(responseTime, JSON.stringify(data).length, JSON.stringify(responseData).length);
            
            if (responseData.success) {
                return responseData.data;
            } else {
                throw new Error(responseData.error || 'Unknown error');
            }
            
        } catch (error) {
            console.error(`gRPC request failed for ${method}:`, error);
            throw error;
        }
    }



    /**
     * Update performance statistics
     */
    updateStats(responseTime, bytesSent, bytesReceived) {
        this.callCount++;
        this.lastCallTime = responseTime;
        this.avgResponseTime = (this.avgResponseTime * (this.callCount - 1) + responseTime) / this.callCount;
    }

    /**
     * Set camera position and orientation
     */
    async setCamera(position, target, up) {
        const cameraData = {
            position: { x: position.x, y: position.y, z: position.z },
            target: { x: target.x, y: target.y, z: target.z },
            up: { x: up.x, y: up.y, z: up.z }
        };
        
        return this.makeGrpcRequest('LiveLinkService/SetCamera', cameraData);
    }

    /**
     * Get current camera state
     */
    async getCamera() {
        return this.makeGrpcRequest('LiveLinkService/GetCamera', {});
    }

    /**
     * Get list of available meshes
     */
    async getMeshes() {
        return this.makeGrpcRequest('LiveLinkService/GetMeshes', {});
    }

    /**
     * Get specific mesh data
     */
    async getMesh(meshId) {
        return this.makeGrpcRequest('LiveLinkService/GetMesh', { meshId });
    }

    /**
     * Event system
     */
    on(event, callback) {
        if (!this.eventListeners.has(event)) {
            this.eventListeners.set(event, []);
        }
        this.eventListeners.get(event).push(callback);
    }

    off(event, callback) {
        if (this.eventListeners.has(event)) {
            const listeners = this.eventListeners.get(event);
            const index = listeners.indexOf(callback);
            if (index > -1) {
                listeners.splice(index, 1);
            }
        }
    }

    emit(event, data) {
        if (this.eventListeners.has(event)) {
            this.eventListeners.get(event).forEach(callback => {
                try {
                    callback(data);
                } catch (error) {
                    console.error(`Error in event listener for ${event}:`, error);
                }
            });
        }
    }

    /**
     * Get connection statistics
     */
    getStats() {
        return {
            connected: this.connected,
            connectionState: this.connectionState,
            callCount: this.callCount,
            lastCallTime: this.lastCallTime,
            avgResponseTime: this.avgResponseTime,
            reconnectAttempts: this.reconnectAttempts
        };
    }
}

/**
 * LiveLinkManager - High-level interface for LiveLink operations
 */
class LiveLinkManager {
    constructor(serverUrl) {
        this.client = new LiveLinkClient(serverUrl);
        this.demoMode = false;
        this.syncEnabled = false;
        this.syncInterval = null;
        
        // Demo data
        this.demoCamera = {
            position: { x: 0, y: 0, z: 5 },
            target: { x: 0, y: 0, z: 0 },
            up: { x: 0, y: 1, z: 0 }
        };
        
        this.demoMeshes = [
            { id: 'teapot', name: 'Utah Teapot', vertices: 1024, faces: 2048 },
            { id: 'sphere', name: 'Sphere', vertices: 512, faces: 1024 },
            { id: 'cube', name: 'Cube', vertices: 8, faces: 12 }
        ];
    }

    /**
     * Connect to LiveLink server
     */
    async connect() {
        try {
            await this.client.connect();
            this.demoMode = false;
            return { success: true, mode: 'live' };
        } catch (error) {
            console.warn('Live connection failed, enabling demo mode:', error.message);
            this.demoMode = true;
            return { success: true, mode: 'demo', error: error.message };
        }
    }

    /**
     * Disconnect from server
     */
    disconnect() {
        this.client.disconnect();
        this.stopSync();
    }

    /**
     * Set camera position
     */
    async setCamera(position, target, up) {
        if (this.demoMode) {
            this.demoCamera = { position, target, up };
            return { success: true, mode: 'demo' };
        }
        
        try {
            const result = await this.client.setCamera(position, target, up);
            return { success: true, mode: 'live', data: result };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }

    /**
     * Get camera state
     */
    async getCamera() {
        if (this.demoMode) {
            return { success: true, mode: 'demo', data: this.demoCamera };
        }
        
        try {
            const result = await this.client.getCamera();
            return { success: true, mode: 'live', data: result };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }

    /**
     * Get available meshes
     */
    async getMeshes() {
        if (this.demoMode) {
            return { success: true, mode: 'demo', data: this.demoMeshes };
        }
        
        try {
            const result = await this.client.getMeshes();
            return { success: true, mode: 'live', data: result };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }

    /**
     * Get specific mesh
     */
    async getMesh(meshId) {
        if (this.demoMode) {
            const mesh = this.demoMeshes.find(m => m.id === meshId);
            return { success: true, mode: 'demo', data: mesh || null };
        }
        
        try {
            const result = await this.client.getMesh(meshId);
            return { success: true, mode: 'live', data: result };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }

    /**
     * Start camera synchronization
     */
    startSync(callback, interval = 100) {
        if (this.syncInterval) {
            this.stopSync();
        }
        
        this.syncEnabled = true;
        this.syncInterval = setInterval(async () => {
            if (callback && this.syncEnabled) {
                const camera = await this.getCamera();
                if (camera.success) {
                    callback(camera.data);
                }
            }
        }, interval);
    }

    /**
     * Stop camera synchronization
     */
    stopSync() {
        this.syncEnabled = false;
        if (this.syncInterval) {
            clearInterval(this.syncInterval);
            this.syncInterval = null;
        }
    }

    /**
     * Get connection and performance stats
     */
    getStats() {
        const clientStats = this.client.getStats();
        return {
            ...clientStats,
            demoMode: this.demoMode,
            syncEnabled: this.syncEnabled
        };
    }

    /**
     * Event forwarding
     */
    on(event, callback) {
        this.client.on(event, callback);
    }

    off(event, callback) {
        this.client.off(event, callback);
    }
}

// Export for use in HTML pages
if (typeof window !== 'undefined') {
    window.LiveLinkClient = LiveLinkClient;
    window.LiveLinkManager = LiveLinkManager;
}