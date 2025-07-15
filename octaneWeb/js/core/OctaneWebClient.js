/**
 * OctaneWeb gRPC Client
 * Extended gRPC client for complete Octane API coverage
 * Builds upon the existing LiveLinkClient from livelink.js
 */

class OctaneWebClient extends LiveLinkClient {
    constructor(serverUrl) {
        super(serverUrl);
        
        // Extended state management
        this.sceneState = {
            objects: new Map(),
            hierarchy: [],
            selection: new Set(),
            cameras: new Map(),
            lights: new Map(),
            materials: new Map(),
            textures: new Map()
        };
        
        this.nodeGraphState = {
            nodes: new Map(),
            connections: new Map(),
            selectedNodes: new Set(),
            clipboard: null
        };
        
        this.renderState = {
            isRendering: false,
            progress: 0,
            samples: 0,
            renderTime: 0,
            resolution: { width: 1920, height: 1080 },
            renderTarget: null
        };
        
        // Event handlers for extended functionality
        this.setupExtendedEventHandlers();
        
        // Auto-sync intervals
        this.syncIntervals = {
            scene: null,
            render: null,
            nodeGraph: null
        };
    }
    
    /**
     * Setup extended event handlers for OctaneWeb functionality
     */
    setupExtendedEventHandlers() {
        // Scene synchronization events
        this.on('sceneChanged', (data) => {
            this.updateSceneState(data);
            this.emit('ui:sceneUpdate', this.sceneState);
        });
        
        // Node graph events
        this.on('nodeGraphChanged', (data) => {
            this.updateNodeGraphState(data);
            this.emit('ui:nodeGraphUpdate', this.nodeGraphState);
        });
        
        // Render events
        this.on('renderProgress', (data) => {
            this.updateRenderState(data);
            this.emit('ui:renderUpdate', this.renderState);
        });
        
        // Selection events
        this.on('selectionChanged', (data) => {
            this.sceneState.selection.clear();
            if (data.selectedObjects) {
                data.selectedObjects.forEach(id => this.sceneState.selection.add(id));
            }
            this.emit('ui:selectionUpdate', this.sceneState.selection);
        });
    }
    
    /**
     * Connect to Octane with extended initialization
     */
    async connect() {
        try {
            // Call parent connect method
            await super.connect();
            
            // Initialize extended functionality
            await this.initializeExtendedFeatures();
            
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
    
    /**
     * Initialize extended features after connection
     */
    async initializeExtendedFeatures() {
        try {
            // Get initial scene state
            await this.syncSceneHierarchy();
            
            // Get initial node graph
            await this.syncNodeGraph();
            
            // Get render settings
            await this.syncRenderSettings();
            
            // Get camera list
            await this.syncCameras();
            
            console.log('OctaneWeb extended features initialized');
            
        } catch (error) {
            console.error('Failed to initialize extended features:', error);
            throw error;
        }
    }
    
    // ==================== SCENE MANAGEMENT ====================
    
    /**
     * Synchronize complete scene hierarchy
     */
    async syncSceneHierarchy() {
        try {
            const response = await this.makeRequest('/octane/scene/hierarchy', {
                method: 'GET'
            });
            
            if (response.success && response.data) {
                this.updateSceneHierarchy(response.data);
                this.emit('ui:sceneHierarchyUpdate', this.sceneState.hierarchy);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to sync scene hierarchy:', error);
            throw error;
        }
    }
    
    /**
     * Get object details by ID
     */
    async getObjectDetails(objectId) {
        try {
            const response = await this.makeRequest('/octane/scene/object', {
                method: 'POST',
                data: { objectId }
            });
            
            if (response.success && response.data) {
                this.sceneState.objects.set(objectId, response.data);
                this.emit('ui:objectUpdate', { objectId, data: response.data });
            }
            
            return response;
            
        } catch (error) {
            console.error(`Failed to get object details for ${objectId}:`, error);
            throw error;
        }
    }
    
    /**
     * Update object properties
     */
    async updateObjectProperties(objectId, properties) {
        try {
            const response = await this.makeRequest('/octane/scene/object/update', {
                method: 'POST',
                data: { objectId, properties }
            });
            
            if (response.success) {
                // Update local state
                const existingObject = this.sceneState.objects.get(objectId) || {};
                this.sceneState.objects.set(objectId, { ...existingObject, ...properties });
                this.emit('ui:objectUpdate', { objectId, data: properties });
            }
            
            return response;
            
        } catch (error) {
            console.error(`Failed to update object ${objectId}:`, error);
            throw error;
        }
    }
    
    /**
     * Select objects in scene
     */
    async selectObjects(objectIds) {
        try {
            const response = await this.makeRequest('/octane/scene/select', {
                method: 'POST',
                data: { objectIds }
            });
            
            if (response.success) {
                this.sceneState.selection.clear();
                objectIds.forEach(id => this.sceneState.selection.add(id));
                this.emit('ui:selectionUpdate', this.sceneState.selection);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to select objects:', error);
            throw error;
        }
    }
    
    // ==================== NODE GRAPH MANAGEMENT ====================
    
    /**
     * Synchronize node graph
     */
    async syncNodeGraph() {
        try {
            const response = await this.makeRequest('/octane/nodegraph/sync', {
                method: 'GET'
            });
            
            if (response.success && response.data) {
                this.updateNodeGraphState(response.data);
                this.emit('ui:nodeGraphUpdate', this.nodeGraphState);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to sync node graph:', error);
            throw error;
        }
    }
    
    /**
     * Create new node
     */
    async createNode(nodeType, position) {
        try {
            const response = await this.makeRequest('/octane/nodegraph/node/create', {
                method: 'POST',
                data: { nodeType, position }
            });
            
            if (response.success && response.data) {
                const nodeId = response.data.nodeId;
                this.nodeGraphState.nodes.set(nodeId, response.data);
                this.emit('ui:nodeCreated', response.data);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to create node:', error);
            throw error;
        }
    }
    
    /**
     * Delete node
     */
    async deleteNode(nodeId) {
        try {
            const response = await this.makeRequest('/octane/nodegraph/node/delete', {
                method: 'POST',
                data: { nodeId }
            });
            
            if (response.success) {
                this.nodeGraphState.nodes.delete(nodeId);
                this.nodeGraphState.selectedNodes.delete(nodeId);
                this.emit('ui:nodeDeleted', { nodeId });
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to delete node:', error);
            throw error;
        }
    }
    
    /**
     * Connect nodes
     */
    async connectNodes(outputNodeId, outputSocket, inputNodeId, inputSocket) {
        try {
            const response = await this.makeRequest('/octane/nodegraph/connect', {
                method: 'POST',
                data: { outputNodeId, outputSocket, inputNodeId, inputSocket }
            });
            
            if (response.success && response.data) {
                const connectionId = response.data.connectionId;
                this.nodeGraphState.connections.set(connectionId, response.data);
                this.emit('ui:nodesConnected', response.data);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to connect nodes:', error);
            throw error;
        }
    }
    
    /**
     * Update node parameter
     */
    async updateNodeParameter(nodeId, parameterName, value) {
        try {
            const response = await this.makeRequest('/octane/nodegraph/node/parameter', {
                method: 'POST',
                data: { nodeId, parameterName, value }
            });
            
            if (response.success) {
                // Update local node state
                const node = this.nodeGraphState.nodes.get(nodeId);
                if (node) {
                    if (!node.parameters) node.parameters = {};
                    node.parameters[parameterName] = value;
                    this.emit('ui:nodeParameterUpdate', { nodeId, parameterName, value });
                }
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to update node parameter:', error);
            throw error;
        }
    }
    
    // ==================== RENDER MANAGEMENT ====================
    
    /**
     * Start rendering
     */
    async startRender(settings = {}) {
        try {
            const response = await this.makeRequest('/octane/render/start', {
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
            const response = await this.makeRequest('/octane/render/stop', {
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
            const response = await this.makeRequest('/octane/render/progress', {
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
            const response = await this.makeRequest('/octane/render/settings', {
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
            const response = await this.makeRequest('/octane/cameras/list', {
                method: 'GET'
            });
            
            if (response.success && response.data) {
                this.sceneState.cameras.clear();
                response.data.forEach(camera => {
                    this.sceneState.cameras.set(camera.id, camera);
                });
                this.emit('ui:camerasUpdate', this.sceneState.cameras);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to sync cameras:', error);
            throw error;
        }
    }
    
    // ==================== AUTO-SYNC MANAGEMENT ====================
    
    /**
     * Start auto-sync intervals
     */
    startAutoSync() {
        // Scene sync every 5 seconds
        this.syncIntervals.scene = setInterval(() => {
            if (this.isConnected) {
                this.syncSceneHierarchy().catch(console.error);
            }
        }, 5000);
        
        // Render progress sync every 1 second when rendering
        this.syncIntervals.render = setInterval(() => {
            if (this.isConnected && this.renderState.isRendering) {
                this.getRenderProgress().catch(console.error);
            }
        }, 1000);
        
        // Node graph sync every 10 seconds
        this.syncIntervals.nodeGraph = setInterval(() => {
            if (this.isConnected) {
                this.syncNodeGraph().catch(console.error);
            }
        }, 10000);
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
        this.sceneState.hierarchy = hierarchyData;
        
        // Flatten hierarchy to update objects map
        const flattenHierarchy = (nodes) => {
            nodes.forEach(node => {
                this.sceneState.objects.set(node.id, node);
                if (node.children) {
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
        if (data.nodes) {
            this.nodeGraphState.nodes.clear();
            data.nodes.forEach(node => {
                this.nodeGraphState.nodes.set(node.id, node);
            });
        }
        
        if (data.connections) {
            this.nodeGraphState.connections.clear();
            data.connections.forEach(conn => {
                this.nodeGraphState.connections.set(conn.id, conn);
            });
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

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = OctaneWebClient;
} else if (typeof window !== 'undefined') {
    window.OctaneWebClient = OctaneWebClient;
}