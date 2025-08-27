/**
 * OctaneWeb gRPC Client
 * 
 * Extended gRPC client providing complete Octane API coverage for
 * real-time rendering, scene management, and parameter editing. Builds upon
 * the base LiveLinkClient with advanced state management and callback streaming.
 * 
 * Key Features:
 * - Real-time callback streaming for live rendering updates
 * - Comprehensive scene state management with hierarchical tracking
 * - Node graph state synchronization for visual editing
 * - Camera synchronization for mouse drag interactions
 * - Parameter editing with live updates to Octane
 * - Render state monitoring for production debugging
 * 
 * Architecture:
 * - Extends LiveLinkClient from.js for base gRPC functionality
 * - Maintains synchronized state maps for all Octane objects
 * - Provides high-level API methods for UI component integration
 * - Handles connection lifecycle and error recovery
 */

// Define the class after ensuring LiveLinkClient is available
function createOctaneWebClient() {
    if (typeof LiveLinkClient === 'undefined') {
        console.error('❌ LiveLinkClient not available. Make sure livelink.js is loaded first.');
        return null;
    }

    class OctaneWebClient extends LiveLinkClient {
    constructor(serverUrl) {
        super(serverUrl);
        
        // Scene state management - tracks all Octane scene objects and hierarchy
        this.sceneState = {
            objects: new Map(),        // All scene objects by ID
            hierarchy: [],             // Hierarchical scene tree structure
            selection: new Set(),      // Currently selected objects
            cameras: new Map(),        // Camera objects for viewport control
            lights: new Map(),         // Light objects for illumination
            materials: new Map(),      // Material objects for shading
            textures: new Map()        // Texture objects for material inputs
        };
        
        // Node graph state management - tracks visual node editing state
        this.nodeGraphState = {
            nodes: new Map(),          // All nodes in the visual graph
            connections: new Map(),    // Node connections and data flow
            selectedNodes: new Set(),  // Currently selected nodes
            clipboard: null            // Copy/paste buffer for nodes
        };
        
        // Render state management - tracks real-time rendering progress
        this.renderState = {
            isRendering: false,        // Current rendering status
            progress: 0,               // Render progress percentage
            samples: 0,                // Current sample count
            renderTime: 0,             // Elapsed render time
            resolution: { width: 1920, height: 1080 }, // Current render resolution
            renderTarget: null         // Active render target object
        };
        
        // Setup event handlers for extended OctaneWeb functionality
        this.setupEventHandlers();
        
        // Auto-sync intervals for periodic state updates
        this.syncIntervals = {
            scene: null,               // Scene tree synchronization timer
            render: null,              // Render progress update timer
            nodeGraph: null            // Node graph state sync timer
        };
    }
    
    /**
     * Setup extended event handlers for OctaneWeb functionality
     */
    setupEventHandlers() {

        // Render events
        this.on('renderProgress', (data) => {
            this.updateRenderState(data);
            this.emit('ui:renderUpdate', this.renderState);
        });
    }
    
    /**
     * Connect to Octane with extended initialization
     */
    async connect() {
        try {
            // Call parent connect method
            await super.connect();
            
            // Start auto-sync intervals
            this.startAutoSync();
            
            this.emit('octaneWeb:connected');
            return true;
            
        } catch (error) {
            console.error('OctaneWeb connection failed:', error);
            this.emit('octaneWeb:connectionError', error);
            throw error;
        }
    }
    
    /**
     * Disconnect with cleanup
     */
    async disconnect() {
        // Stop auto-sync intervals
        this.stopAutoSync();
        
        // Clear state
        this.clearAllState();
        
        // Call parent disconnect
        await super.disconnect();
        
        this.emit('octaneWeb:disconnected');
    }
    
    // ==================== GRPC CALL OVERRIDE ====================

    /**
     * Override makeGrpcCall to handle both parent class signature and extended signature
     */
    async makeGrpcCall(methodOrService, requestOrMethod, request = {}) {
        // Handle both signatures:
        // Parent class: makeGrpcCall(method, request)
        // Extended class: makeGrpcCall(serviceName, methodName, request)
        
        let serviceName, methodName, actualRequest;
        
        if (arguments.length === 2) {
            // Parent class signature: makeGrpcCall(method, request)
            const method = methodOrService;
            actualRequest = requestOrMethod;
            
            if (['SetCamera', 'GetCamera', 'GetMeshes'].includes(method)) {
                serviceName = 'LiveLink';
                methodName = method;
            } else {
                // For other methods, try to parse service.method format
                const parts = method.split('.');
                if (parts.length === 2) {
                    serviceName = parts[0];
                    methodName = parts[1];
                } else if (method.startsWith('/')) {
                    // Handle URL path format - extract meaningful parts
                    const pathParts = method.substring(1).split('/'); // Remove leading slash and split
                    if (pathParts.length >= 2) {
                        serviceName = pathParts[0]; // e.g., "octane"
                        methodName = pathParts.slice(1).join('/'); // e.g., "scene/select"
                    } else {
                        serviceName = pathParts[0] || 'unknown';
                        methodName = 'unknown';
                    }
                } else {
                    serviceName = method;
                    methodName = method;
                }
            }
        } else {
            // Extended class signature: makeGrpcCall(serviceName, methodName, request)
            serviceName = methodOrService;
            methodName = requestOrMethod;
            actualRequest = request;
        }

        const startTime = Date.now();
        const method = `${serviceName}.${methodName}`;
        const callId = `${serviceName}_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
        this.callCount++;

        // Enhanced logging for all gRPC calls (disabled for performance)
        console.log(`\n=== gRPC CALL STARTED ===`);
        console.log(`Service: ${serviceName}`);
        console.log(`Method: ${methodName}`);
        // console.log(`Call ID: ${callId}`);
        // console.log(`Call Number: ${this.callCount}`);
        // console.log(`Connection State: ${this.connectionState}`);
        // console.log(`Request:`, actualRequest);
        // console.log(`Request JSON:`, JSON.stringify(actualRequest, null, 2));
        
        this.log(`gRPC call started: ${serviceName}.${methodName}`, {
            callId: callId,
            originalMethod: method,
            serviceName: serviceName,
            methodName: methodName,
            request: actualRequest,
            callNumber: this.callCount,
            connectionState: this.connectionState
        });

        try {
            if (!this.isReady()) {
                throw new Error(`Client not ready for gRPC calls. State: ${this.connectionState}`);
            }

            // Create request body with actual service names
            const requestBody = {
                service: serviceName,
                method: methodName,
                params: actualRequest || {}
            };
            
            // console.log(`Request Body:`, requestBody);
            // console.log(`Request Body JSON:`, JSON.stringify(requestBody, null, 2));

            const controller = new AbortController();
            const timeoutId = setTimeout(() => {
                controller.abort();
                this.log(`gRPC call timeout: ${serviceName}.${methodName}`, { callId, duration: Date.now() - startTime }, 'error');
            }, 30000); // 30 second timeout

            // Use direct service endpoint instead of /api
            const url = `${this.serverUrl}/${serviceName}/${methodName}`;
            const body = JSON.stringify(actualRequest || {});
            
            // console.log(`LOCKIT: Making fetch request to: ${url}`);
            // console.log(`LOCKIT: Request body: ${body}`);
            // console.log(`LOCKIT: Headers:`, {
            //     'Content-Type': 'application/json',
            //     'X-Call-Id': callId
            // });
            
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'X-Call-Id': callId
                },
                body: body,
                signal: controller.signal
            });
            
            // console.log(`LOCKIT: Response status: ${response.status}`);
            // console.log(`LOCKIT: Response ok: ${response.ok}`);

            clearTimeout(timeoutId);

            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }

            const result = await response.json();
            const duration = Date.now() - startTime;

            // Enhanced response logging (disabled for performance)
            // console.log(`\n=== gRPC RESPONSE RECEIVED ===`);
            // console.log(`Method: ${method}`);
            // console.log(`Call ID: ${callId}`);
            // console.log(`Duration: ${duration}ms`);
            // console.log(`HTTP Status: ${response.status} ${response.statusText}`);
            // console.log(`Success: ${result.success}`);
            // console.log(`Data Size: ${JSON.stringify(result).length} bytes`);
            // console.log(`Result:`, result);
            // console.log(`Result JSON:`, JSON.stringify(result, null, 2));
            
            // if (result.success && result.data) {
            //     console.log(`Response Data:`, result.data);
            //     console.log(`Response Data JSON:`, JSON.stringify(result.data, null, 2));
            // }
            
            if (!result.success && result.error) {
                console.error(`❌ gRPC Error:`, result.error);
            }

            this.log(`gRPC call completed: ${method}`, {
                callId: callId,
                duration: duration,
                success: result.success,
                dataSize: JSON.stringify(result).length
            });

            return result;

        } catch (error) {
            const duration = Date.now() - startTime;
            
            // Enhanced error logging
            console.error(`\n❌ === gRPC CALL FAILED ===`);
            console.error(`❌ Method: ${method}`);
            console.error(`❌ Call ID: ${callId}`);
            console.error(`❌ Duration: ${duration}ms`);
            console.error(`❌ Error Type: ${error.constructor.name}`);
            console.error(`❌ Error Message: ${error.message}`);
            console.error(`❌ Error Stack:`, error.stack);
            console.error(`❌ Full Error:`, error);
            
            this.log(`gRPC call failed: ${method}`, {
                callId: callId,
                duration: duration,
                error: error.message
            }, 'error');
            throw error;
        }
    }

    // ==================== SCENE MANAGEMENT ====================
    
    /**
     * Get scene data using real Octane gRPC APIs via generic pass-through
     */
    async getSceneData() {
        try {

            
        } catch (error) {
            console.error('❌ Error loading scene data:', error);
        }
    }
    
    // ==================== RENDER MANAGEMENT ====================
    
    /**
     * Start rendering
     */
    async startRender(settings = {}) {
        try {
            const response = await this.makeGrpcCall('/octane/render/start', {
                method: 'POST',
                data: settings
            });
            
            if (response.success) {
                this.renderState.isRendering = true;
                this.renderState.progress = 0;
                this.renderState.samples = 0;
                this.emit('ui:renderStarted', this.renderState);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to start render:', error);
            throw error;
        }
    }
    
    /**
     * Stop rendering
     */
    async stopRender() {
        try {
            const response = await this.makeGrpcCall('/octane/render/stop', {
                method: 'POST'
            });
            
            if (response.success) {
                this.renderState.isRendering = false;
                this.emit('ui:renderStopped', this.renderState);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to stop render:', error);
            throw error;
        }
    }
    
    /**
     * Get render progress
     */
    async getRenderProgress() {
        try {
            const response = await this.makeGrpcCall('/octane/render/progress', {
                method: 'GET'
            });
            
            if (response.success && response.data) {
                this.updateRenderState(response.data);
                this.emit('ui:renderProgress', this.renderState);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to get render progress:', error);
            throw error;
        }
    }
    
    /**
     * Sync render settings
     */
    async syncRenderSettings() {
        try {
            const response = await this.makeGrpcCall('/octane/render/settings', {
                method: 'GET'
            });
            
            if (response.success && response.data) {
                this.renderState = { ...this.renderState, ...response.data };
                this.emit('ui:renderSettingsUpdate', this.renderState);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to sync render settings:', error);
            throw error;
        }
    }
    
    // ==================== CAMERA MANAGEMENT ====================
    
    /**
     * Sync all cameras
     */
    async syncCameras() {
        try {
            const response = await this.makeGrpcCall('GetCamera', {});
            
            if (response.success && response.data) {
                this.sceneState.cameras.clear();
                // GetCamera returns a single camera object, not an array
                const camera = {
                    id: 'main_camera',
                    position: response.data.position,
                    target: response.data.target,
                    up: response.data.up
                };
                this.sceneState.cameras.set(camera.id, camera);
                this.emit('ui:camerasUpdate', this.sceneState.cameras);
                this.log(`Synced camera: ${JSON.stringify(camera)}`);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to sync cameras:', error);
            throw error;
        }
    }
    
    /**
     * Set camera position
     */
    async setCameraPosition(x, y, z) {
        try {
            const response = await this.makeGrpcCall('SetCamera', {
                position: { x: x, y: y, z: z }
            });
            
            if (response.success) {
                this.log(`Camera position set: [${x.toFixed(2)}, ${y.toFixed(2)}, ${z.toFixed(2)}]`);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to set camera position:', error);
            throw error;
        }
    }
    
    /**
     * Set camera target
     */
    async setCameraTarget(x, y, z) {
        try {
            const response = await this.makeGrpcCall('SetCamera', {
                target: { x: x, y: y, z: z }
            });
            
            if (response.success) {
                this.log(`Camera target set: [${x.toFixed(2)}, ${y.toFixed(2)}, ${z.toFixed(2)}]`);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to set camera target:', error);
            throw error;
        }
    }
    
    /**
     * Set camera position and target together (more efficient)
     */
    async setCameraPositionAndTarget(posX, posY, posZ, targetX, targetY, targetZ) {
        try {
            const response = await this.makeGrpcCall('SetCamera', {
                position: { x: posX, y: posY, z: posZ },
                target: { x: targetX, y: targetY, z: targetZ }
            });
            
            if (response.success) {
                this.log(`Camera updated: pos=[${posX.toFixed(2)}, ${posY.toFixed(2)}, ${posZ.toFixed(2)}], target=[${targetX.toFixed(2)}, ${targetY.toFixed(2)}, ${targetZ.toFixed(2)}]`);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to set camera position and target:', error);
            throw error;
        }
    }
    
    // ==================== AUTO-SYNC MANAGEMENT ====================
    
    /**
     * Start auto-sync intervals
     */
    startAutoSync() {

        // Render progress sync every 1 second when rendering
        this.syncIntervals.render = setInterval(() => {
            if (this.isConnected && this.renderState.isRendering) {
                this.getRenderProgress().catch(console.error);
            }
        }, 1000);
    }
    
    /**
     * Stop auto-sync intervals
     */
    stopAutoSync() {
        Object.values(this.syncIntervals).forEach(interval => {
            if (interval) clearInterval(interval);
        });
        this.syncIntervals = { scene: null, render: null, nodeGraph: null };
    }
    
    // ==================== STATE MANAGEMENT ====================
    
    /**
     * Update scene state from server data
     */
    updateSceneState(data) {
        if (data.objects) {
            data.objects.forEach(obj => {
                this.sceneState.objects.set(obj.id, obj);
            });
        }
        
        if (data.hierarchy) {
            this.sceneState.hierarchy = data.hierarchy;
        }
        
        if (data.selection) {
            this.sceneState.selection.clear();
            data.selection.forEach(id => this.sceneState.selection.add(id));
        }
    }
    
    /**
     * Update scene hierarchy
     */
    updateSceneHierarchy(hierarchyData) {
        // Ensure hierarchyData is an array
        if (!Array.isArray(hierarchyData)) {
            console.warn('updateSceneHierarchy: hierarchyData is not an array:', hierarchyData);
            this.sceneState.hierarchy = [];
            return;
        }
        
        this.sceneState.hierarchy = hierarchyData;
        
        // Flatten hierarchy to update objects map
        const flattenHierarchy = (nodes) => {
            if (!Array.isArray(nodes)) {
                console.warn('flattenHierarchy: nodes is not an array:', nodes);
                return;
            }
            nodes.forEach(node => {
                this.sceneState.objects.set(node.id, node);
                if (node.children && Array.isArray(node.children)) {
                    flattenHierarchy(node.children);
                }
            });
        };
        
        flattenHierarchy(hierarchyData);
    }
    
    /**
     * Update node graph state
     */
    updateNodeGraphState(data) {
        if (data.nodes && Array.isArray(data.nodes)) {
            this.nodeGraphState.nodes.clear();
            data.nodes.forEach(node => {
                this.nodeGraphState.nodes.set(node.id, node);
            });
        } else if (data.nodes) {
            console.warn('updateNodeGraphState: data.nodes is not an array:', data.nodes);
        }
        
        if (data.connections && Array.isArray(data.connections)) {
            this.nodeGraphState.connections.clear();
            data.connections.forEach(conn => {
                this.nodeGraphState.connections.set(conn.id, conn);
            });
        } else if (data.connections) {
            console.warn('updateNodeGraphState: data.connections is not an array:', data.connections);
        }
    }
    
    /**
     * Update render state
     */
    updateRenderState(data) {
        this.renderState = { ...this.renderState, ...data };
    }
    
    /**
     * Clear all state
     */
    clearAllState() {
        this.sceneState.objects.clear();
        this.sceneState.hierarchy = [];
        this.sceneState.selection.clear();
        this.sceneState.cameras.clear();
        this.sceneState.lights.clear();
        this.sceneState.materials.clear();
        this.sceneState.textures.clear();
        
        this.nodeGraphState.nodes.clear();
        this.nodeGraphState.connections.clear();
        this.nodeGraphState.selectedNodes.clear();
        this.nodeGraphState.clipboard = null;
        
        this.renderState.isRendering = false;
        this.renderState.progress = 0;
        this.renderState.samples = 0;
        this.renderState.renderTime = 0;
    }
    
    // ==================== UTILITY METHODS ====================
    
    /**
     * Get current scene state
     */
    getSceneState() {
        return { ...this.sceneState };
    }
    
    /**
     * Get current node graph state
     */
    getNodeGraphState() {
        return { ...this.nodeGraphState };
    }
    
    /**
     * Get current render state
     */
    getRenderState() {
        return { ...this.renderState };
    }
    
    /**
     * Check if object is selected
     */
    isObjectSelected(objectId) {
        return this.sceneState.selection.has(objectId);
    }
    
    /**
     * Check if node is selected
     */
    isNodeSelected(nodeId) {
        return this.nodeGraphState.selectedNodes.has(nodeId);
    }
    
    /**
     * Get selected objects
     */
    getSelectedObjects() {
        return Array.from(this.sceneState.selection);
    }
    
    /**
     * Get selected nodes
     */
    getSelectedNodes() {
        return Array.from(this.nodeGraphState.selectedNodes);
    }
}

    return OctaneWebClient;
}

// Create and export the class
const OctaneWebClient = createOctaneWebClient();

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = OctaneWebClient;
} else if (typeof window !== 'undefined') {
    window.OctaneWebClient = OctaneWebClient;
}