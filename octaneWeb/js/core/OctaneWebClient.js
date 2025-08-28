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
    constructor(eventSystem, serverUrl) {
        super(serverUrl);
                
        this.eventSystem = eventSystem;
        this.scene = { tree: [], map: new Map()}

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
//            this.startAutoSync();
            
            this.emit('connected');
            return true;
            
        } catch (error) {
            console.error('OctaneWeb connection failed:', error);
            this.emit('connectionError', error);
//            throw error;
            return false;
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
        
        this.emit('disconnected');
    }
    
    getScene() {
        return this.scene;
    }
    
    /**
     * ASYNCHRONOUS function that loads scene tree
     * UI loads immediately, then updates when scene data is ready
     */
    async loadSceneTree() {
        console.log('createOctaneWebClient.loadSceneTree() called');
        
        try {
            console.log('Starting SYNCHRONOUS scene tree loading sequence...');

            this.scene = { tree: this.loadSceneTreeSync()};
            this.eventSystem.emit('sceneDataLoaded', this.scene);
            
        } catch (error) {
            console.error('❌ Failed loadSceneTree(): ', error);
            
            // Clear stored scene data and notify other components
            this.scene = { tree:[]}
            this.eventSystem.emit('sceneDataLoaded', this.scene);
        }
    }

    /**
     * SYNCHRONOUS scene tree loading with blocking API calls
     * STRUCTURED DEBUGGING: Isolate exactly where Octane crashes
     * @returns {Array} Scene tree array
     */
    loadSceneTreeSync(itemHandle, sceneItems, isGraph, level = 0) {
        let result;
//        if (level >= 3)
//            return scene;
        level = level + 1;

        if (sceneItems == null) {
            sceneItems = [];
        }
        try {
            if (itemHandle == null)
            {
                // first call, get the root
                result = window.grpcApi.makeApiCall(
                    'ApiProjectManager/rootNodeGraph'
                );
                if (!result.success) {
                    throw new Error('Failed ApiProjectManager/rootNodeGraph');
                }
                itemHandle = result.data.result.handle;
                // is it a graph or node?
                result = window.grpcApi.makeApiCall(
                    'ApiItem/isGraph', 
                    itemHandle 
                );
                if (!result.success) {
                    throw new Error('Failed ApiItem/isGraph');
                }
                isGraph = result.data.result;
            }
            if (isGraph)
            {
                // Get owned items
                result = window.grpcApi.makeApiCall(
                    'ApiNodeGraph/getOwnedItems', 
                    itemHandle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodeGraph/getOwnedItems');
                }
                const ownedItemsHandle = result.data.list.handle

                // Get the size of the item array
                result = window.grpcApi.makeApiCall(
                    'ApiItemArray/size', 
                    ownedItemsHandle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiItemArray/size');
                }
                const size = result.data.result;

                for (let i = 0; i < size; i++) {
                    // get it
                    result = window.grpcApi.makeApiCall(
                        'ApiItemArray/get', 
                        ownedItemsHandle,
                        {index: i},
                    );
                    if (!result.success) {
                        throw new Error('Failed ApiItemArray/get');
                    }
                    // will recurse to loadSceneTreeSync()
                    this.addSceneItem(sceneItems, result.data.result, null, level);
                }
//                sceneItems.sort((a, b) => a.handle - b.handle); 

                return sceneItems
            }
            // its a node
            result = window.grpcApi.makeApiCall(
                'ApiNode/pinCount', 
                itemHandle
            );
            if (!result.success) {
                throw new Error('Failed ApiNode/pinCount');
            }
            const pinCount = result.data.result;
//            console.log(`pinCount = ${pinCount} nodeInfo.pinInfoCount = ${nodeInfo.pinInfoCount}`);  

            for (let i = 0; i < pinCount; i++) {
                // Get the pin connected node
                result = window.grpcApi.makeApiCall(
                    'ApiNode/connectedNodeIx', 
                    itemHandle,
                    { pinIx: i, enterWrapperNode: true },
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/connectedNodeIx');
                }        
                const connectedNode = result.data.result;

                if (connectedNode == null) {
                    continue;
                }
                // Get the pin label
                result = window.grpcApi.makeApiCall(
                    'ApiNode/pinLabelIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinLabelIx');
                }
                let pinInfo = { staticLabel: result.data.result, index:i };

                // Get the pin type
                result = window.grpcApi.makeApiCall(
                    'ApiNode/pinTypeIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinTypeIx');
                }
                pinInfo.parent = itemHandle;
                pinInfo.type = result.data.result;

//                console.log('pinInfo.type', pinInfo.type);

//                pinInfo.type = window.OctaneTypes.NodePinType[pinInfo.type];
//                console.log('pinInfo.type', pinInfo.type);
/*                
                // Get the pin info handle
                result = window.grpcApi.makeApiCall(
                    'ApiNode/pinInfoIx', 
                    itemHandle,
                    {index: i},
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/pinInfoIx');
                }

                console.log('before ApiNodePinInfoEx/getApiNodePinInfo', result.data.result.handle);

                // Get the pin info 
                result = window.grpcApi.makeApiCall(
                    'ApiNodePinInfoEx/getApiNodePinInfo', 
                    result.data.result.handle
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodePinInfoEx/getApiNodePinInfo');
                }
                console.log('pinInfo ', JSON.stringify(result, null, 2));
                pinInfo = result.data.result;
*/
                // will recurse to loadSceneTreeSync()
                this.addSceneItem(sceneItems, connectedNode, pinInfo, level);
            }
        } catch (error) {
            console.error('❌ Failed loadSceneTreeSync(): ', error);
        }
//        sceneItems.sort((a, b) => a.handle - b.handle); 
        return sceneItems;
    }
    
        
    /**

     */
    addSceneItem(sceneItems, item, pinInfo, level = 0) { 

        let itemName;
        let outType;
        let graphInfo;
        let nodeInfo;
        let isGraph;

        if (!item || !item.handle)
            return;

        try {
            let result;
            
            // basic item params
            // name
            result = window.grpcApi.makeApiCall(
                'ApiItem/name',
                item.handle
            );
            if (!result.success) {
                throw new Error('Failed GenericNodeRenderer.addSceneItem()');
            }
            itemName = result.data.result;

            // outtype
            result = window.grpcApi.makeApiCall(
                'ApiItem/outType',
                item.handle
            );
            if (!result.success) {
                throw new Error('Failed to get item outType');
            }
            outType = result.data.result;

            if (pinInfo != null && pinInfo.staticLabel != "") {
                itemName = pinInfo.staticLabel;
            }
            console.log(`addSceneItem = ${itemName}`);  

            // is it a graph or node?
            result = window.grpcApi.makeApiCall(
                'ApiItem/isGraph', 
                item.handle 
            );
            if (!result.success) {
                throw new Error('Failed ApiItem/isGraph');
            }
            isGraph = result.data.result;
            if (isGraph) {
                // its a graph
                result = window.grpcApi.makeApiCall(
                    'ApiNodeGraph/info1', 
                    item.handle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiNodeGraph/info1');
                }
                graphInfo = result.data.result;
                console.log(`graphInfo = `, JSON.stringify(graphInfo, null, 2));  
            }
            else {
                // its a node
                result = window.grpcApi.makeApiCall(
                    'ApiNode/info', 
                    item.handle,
                );
                if (!result.success) {
                    throw new Error('Failed ApiNode/info');
                }
                nodeInfo = result.data.result
                console.log(`nodeInfo = `, JSON.stringify(nodeInfo, null, 2));  
            }

        } catch (error) {
            console.error('❌ Failed addSceneItem(): ', error);
        }
        let children = this.loadSceneTreeSync(item.handle, null, isGraph, level);

        let attrInfo = null;
        if (children.length == 0) {
            try {        
                // end node, get value's attribute
                const result = window.grpcApi.makeApiCall(
                    'ApiItem/attrInfo', 
                    item.handle,
                    { id: window.OctaneTypes.AttributeId.A_VALUE },
                );
                if (!result.success) {
                    throw new Error('Failed GenericNodeRenderer.addSceneItem(): ApiItem/attrInfo');
                }
                attrInfo = result.data.result;

            } catch (error) {
                console.error('❌ Failed addSceneItem(): ', error);
            }
            console.log(`EndNode    ${item.handle} ${itemName} ${outType} ${attrInfo?.type}`);            
        }
        else {
            console.log(`ParentNode ${item.handle} ${itemName} ${outType} ${pinInfo?.type}`);            
        }
       
        const icon = window.OctaneIconMapper?.getNodeIcon(outType);

        if (pinInfo) {
            pinInfo.pinColor = window.OctaneIconMapper?.gePinColor(outType);
        }
        const entry = {
            name: itemName,
            handle: item.handle,
            outType: outType,
            graphInfo: graphInfo,
            nodeInfo: nodeInfo,
            attrInfo: attrInfo,
            pinInfo: pinInfo,
            children: children,
            icon: icon,
        };

        // save it
        sceneItems.push( entry );
        this.scene.map[item.handle] = entry;
    }

    // ==================== GRPC CALL OVERRIDE ====================

    /**
     * Override makeGrpcCall to handle both parent class signature and extended signature
     */
    async makeGrpcCall(servicePath, request = {}) {
        const result = window.grpcApi.makeApiCall(servicePath, null, request);            
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
            const response = await this.makeGrpcCall('LiveLink/GetCamera');
            
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
                this.log(`Synced camera: ${JSON.stringify(camera, null, 2)}`);
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
            const response = await this.makeGrpcCall('LiveLink/SetCamera', {
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
            const response = await this.makeGrpcCall('LiveLink/SetCamera', {
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
            const response = await this.makeGrpcCall('LiveLink/SetCamera', {
                position: { x: posX, y: posY, z: posZ },
                target: { x: targetX, y: targetY, z: targetZ }
            });
            
            if (response.success) {
                this.log(`Camera updated: pos=[${posX.toFixed(2)}, ${posY.toFixed(2)}, ${posZ.toFixed(2)}], target=[${targetX.toFixed(2)}, ${targetY.toFixed(2)}, ${targetZ.toFixed(2)}]`);
            }
            return response.succes;
            
        } catch (error) {
            console.error('Failed to set camera position and target:', error);
//            throw error;
            return false;
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