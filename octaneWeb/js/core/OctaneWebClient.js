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
                
        this.proxyUrl = 'http://localhost:51023';
        this.eventSystem = eventSystem;
        this.scene = { tree: [], map: new Map(), connections: new Map()}
        this.isSyncing = false;

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
            this.emit('ui:renderStateUpdate', this.renderState);
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
     * Find node data directly from scene list
    */
    lookupItem(handle, onlyTop = false) {

        // Search recursively through scene
        const findRecursively = (items, level, onlyTop) => {
            for (const item of items) {
                if (item.handle == handle) {
                    return item;
                }
                if (!onlyTop) {
                    if (item.children && item.children.length > 0) {
                        const found = findRecursively(item.children);
                        if (found) return found;
                    }
                }
            }
            return null;
        };
        return findRecursively(this.scene.tree, onlyTop);
    }
    
        /**
     * Find node data directly from scene list
    */
    lookupItemType(type) {

        // Search recursively through scene
        const findRecursively = (items) => {
            for (const item of items) {
                if (item.nodeInfo?.type == type  || item.graphInfo?.type == type) {
                    return item;
                }
                if (item.children && item.children.length > 0) {
                    const found = findRecursively(item.children);
                    if (found) return found;
                }
            }
            return null;
        };
        return findRecursively(this.scene.tree);
    }

    /**
     * ASYNCHRONOUS function that loads scene tree
     * UI loads immediately, then updates when scene data is ready
     */
    async syncScene(handle) {
        try {
            if (this.isSyncing) {
                return;
            }
            window.debugConsole.log( 'Loading Octane scene...', handle);

            this.isSyncing = true;

            let item;
            if (handle) {
                syncSceneRecurse(handle, this.scene.tree);               
                this.isSyncing = false;
                item = this.lookupItem(handle);
            }
            else {
//                this.scene = { tree: this.syncSceneRecurse(), map: new Map(), connections: new Map() }
                this.syncSceneRecurse(null, this.scene.tree);
                this.isSyncing = false;
                this.eventSystem.emit('sceneDataLoaded', this.scene);
                item = this.lookupItemType("NT_RENDERTARGET");
            }
            if (item) {
                this.eventSystem.emit('sceneNodeSelected', item.handle);
            }
            console.log("");
            console.log(JSON.stringify(this.scene.tree, null, 2));
            
        } catch (error) {
            console.error('❌ Failed syncScene(): ', error);
            
            // Clear stored scene data and notify other components
            this.scene = { tree:[], map: new Map() }
            this.isSyncing = false;
            this.eventSystem.emit('sceneDataLoaded', this.scene);
        }
    }

    getDestination(nodeData) {

        if (!nodeData) {
            return null;
        }
        let response = window.octaneClient.makeApiCall(
            'ApiNode/destinationNodes', 
            nodeData.handle);
        const handle = response.data.nodes.handle

        // Get the size of the item array
        response = window.octaneClient.makeApiCall(
            'ApiNodeArray/size1', 
            handle,
        );
        if (!response.success) {
            throw new Error('NodeGraphEditor.getNodeOutputs Failed ApiNodeArray/size1');
        }
        const size = response.data.result;

        const outputs = [];
        for (let i = 0; i < size; i++) {
            // get it
            response = window.octaneClient.makeApiCall(
                'ApiNodeArray/get1', 
                handle,
                {index: i},
            ); 
            if (!response.success) {
                throw new Error('Failed ApiNodeArray/get1');
            }
            const node = this.scene.map[response.data.result.handle];

            if (node) {
                console.log('getDestination: ', nodeData.name, nodeData.handle, '->', node.name, node.handle);

                const dest = node; //node.level > 1 ? this.getDestination(node) : node;
                return dest;
            }
        }
    }


    /**
     * SYNCHRONOUS scene tree loading with blocking API calls
     * STRUCTURED DEBUGGING: Isolate exactly where Octane crashes
     * @returns {Array} Scene tree array
     */
    syncSceneRecurse(itemHandle, sceneItems, isGraph, level = 0) {
        let response;
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
                response = this.makeApiCall(
                    'ApiProjectManager/rootNodeGraph'
                );
                if (!response.success) {
                    throw new Error('Failed ApiProjectManager/rootNodeGraph');
                }
                itemHandle = response.data.result.handle;
                // is it a graph or node?
                response = this.makeApiCall(
                    'ApiItem/isGraph', 
                    itemHandle 
                );
                if (!response.success) {
                    throw new Error('Failed ApiItem/isGraph');
                }
                isGraph = response.data.result;
            }
            if (isGraph)
            {
                // Get owned items
                response = this.makeApiCall(
                    'ApiNodeGraph/getOwnedItems', 
                    itemHandle,
                );
                if (!response.success) {
                    throw new Error('Failed ApiNodeGraph/getOwnedItems');
                }
                const ownedItemsHandle = response.data.list.handle

                // Get the size of the item array
                response = this.makeApiCall(
                    'ApiItemArray/size', 
                    ownedItemsHandle,
                );
                if (!response.success) {
                    throw new Error('Failed ApiItemArray/size');
                }
                const size = response.data.result;

                for (let i = 0; i < size; i++) {
                    // get it
                    response = this.makeApiCall(
                        'ApiItemArray/get', 
                        ownedItemsHandle,
                        {index: i},
                    );
                    if (!response.success) {
                        throw new Error('Failed ApiItemArray/get');
                    }
                    // will recurse to syncSceneRecurse()
                    this.addSceneItem(sceneItems, response.data.result, null, level);
                }
//                sceneItems.sort((a, b) => a.handle - b.handle); 

                if (level == 1) {
                    sceneItems.forEach((item) => {
                        this.addItemChildren(sceneItems, item)                        
                    });
                }
                return sceneItems
            }
            // its a node
            response = this.makeApiCall(
                'ApiNode/pinCount', 
                itemHandle
            );
            if (!response.success) {
                throw new Error('Failed ApiNode/pinCount');
            }
            const pinCount = response.data.result;
//            window.debugConsole.log( `pinCount = ${pinCount} nodeInfo.pinInfoCount = ${nodeInfo.pinInfoCount}`);  

            for (let i = 0; i < pinCount; i++) {
                // Get the pin connected node
                response = this.makeApiCall(
                    'ApiNode/connectedNodeIx', 
                    itemHandle,
                    { pinIx: i, enterWrapperNode: true },
                );
                if (!response.success) {
                    throw new Error('Failed ApiNode/connectedNodeIx');
                }        
                const connectedNode = response.data.result;
//                console.log(JSON.stringify(connectedNode, null, 2));

                if (connectedNode == null) {
                    continue;
                }
//                const topNode = this.lookupItem(connectedNode.handle, true);
//                if (topNode) {
//                    console.log("DEST ->", JSON.stringify(topNode, null, 2));
//                }
/*                
                // Get the pin label
                response = this.makeApiCall(
                    'ApiNode/pinLabelIx', 
                    itemHandle,
                    {index: i},
                );
                if (!response.success) {
                    throw new Error('Failed ApiNode/pinLabelIx');
                }
                let pinInfo = { staticLabel: response.data.result, index:i };

                // Get the pin type
                response = this.makeApiCall(
                    'ApiNode/pinTypeIx', 
                    itemHandle,
                    {index: i},
                );
                if (!response.success) {
                    throw new Error('Failed ApiNode/pinTypeIx');
                }
                pinInfo.type = response.data.result;
//                window.debugConsole.log( 'pinInfo.type', pinInfo.type);

//                pinInfo.type = window.OctaneTypes.NodePinType[pinInfo.type];
//                window.debugConsole.log( 'pinInfo.type', pinInfo.type);
*/
                // Get the pin info handle
                response = this.makeApiCall(
                    'ApiNode/pinInfoIx', 
                    itemHandle,
                    {index: i},
                );
                if (!response.success) {
                    throw new Error('Failed ApiNode/pinInfoIx');
                }
                // Get the pin info 
                response = this.makeApiCall(
                    'ApiNodePinInfoEx/getApiNodePinInfo', 
                    response.data.result.handle
                );
                if (!response.success) {
                    throw new Error('Failed ApiNodePinInfoEx/getApiNodePinInfo');
                }
                let pinInfo = response.data.nodePinInfo;
                pinInfo.ix = i;

                // will recurse to syncSceneRecurse()
                this.addSceneItem(sceneItems, connectedNode, pinInfo, level);
            }
        } catch (error) {
            console.error('❌ Failed syncSceneRecurse(): ', error);
        }
//        sceneItems.sort((a, b) => a.handle - b.handle); 
        return sceneItems;
    }
    
        
    /**

     */
    addSceneItem(sceneItems, item, pinInfo, level = 0) { 

        let itemName = item.name || pinInfo?.staticLabel;
        let outType = pinInfo?.outType;
        let graphInfo;
        let nodeInfo;
        let isGraph = false;

        if (pinInfo) {
            console.log("pinInfo", JSON.stringify(pinInfo));
        }
        if (item && item.handle) {
            const existing = this.scene.map[item.handle];
            if (existing && existing.handle && existing.level == 1)
            {
                const dest = this.getDestination(existing);
                const connect = { 
                    output: existing,
                    pinInfo: pinInfo,
                    input: dest,
                }
                if (this.scene.connections == null) {
                    this.scene.connections = new Map();
                }
                this.scene.connections.set(existing.handle, connect);
                console.log("Connect", connect.output.name, connect.output.handle, connect.pinInfo.staticLabel, "->", connect.input.name, connect.input.handle);
                console.log("Connections", this.scene.connections.size);

                sceneItems.push(existing);
                return;
            }
            else {
                try {
                let response;
                
                // basic item params
                // name
                response = this.makeApiCall(
                    'ApiItem/name',
                    item.handle
                );
                if (!response.success) {
                    throw new Error('Failed GenericNodeRenderer.addSceneItem() ApiItem/name');
                }
                itemName = response.data.result;

                // outtype
                response = this.makeApiCall(
                    'ApiItem/outType',
                    item.handle
                );
                if (!response.success) {
                    throw new Error('Failed to get item outType');
                }
                outType = response.data.result;

                // is it a graph or node?
                response = this.makeApiCall(
                    'ApiItem/isGraph', 
                    item.handle 
                );
                if (!response.success) {
                    throw new Error('Failed ApiItem/isGraph');
                }
                isGraph = response.data.result;
                if (isGraph) {
                    // its a graph
                    response = this.makeApiCall(
                        'ApiNodeGraph/info1', 
                        item.handle,
                    );
                    if (!response.success) {
                        throw new Error('Failed ApiNodeGraph/info1');
                    }
                    graphInfo = response.data.result;
                }
                else {
                    // its a node
                    response = this.makeApiCall(
                        'ApiNode/info', 
                        item.handle,
                    );
                    if (!response.success) {
                        throw new Error('Failed ApiNode/info');
                    }
                    nodeInfo = response.data.result
                }

            } catch (error) {
                console.error('❌ Failed addSceneItem(): ', error);
            }
            }
        }
        const icon = window.OctaneIconMapper?.getNodeIcon(outType);

        const entry = {
            level: level,
            name: itemName,
            handle: item.handle,
            outType: outType,
            graphInfo: graphInfo,
            nodeInfo: nodeInfo,
            pinInfo: pinInfo,
            icon: icon,
//            attrInfo: attrInfo,
//            children: children,
        };
        // save it
        sceneItems.push( entry );

        if (item && item.handle) {
            this.scene.map[item.handle] = entry;
            
            if (level > 1)
            {
                this.addItemChildren(sceneItems, item)
            }
        }
    }

    addItemChildren(sceneItems, item) { 

        let iitem = this.scene.map[item.handle];
        const children = this.syncSceneRecurse(iitem.handle, null, iitem.graphInfo != null, iitem.level);
        iitem['children'] = children;

        let attrInfo = null;
        if (children.length == 0) {
            try {        
                // end node, get value's attribute
                const response = this.makeApiCall(
                    'ApiItem/attrInfo', 
                    item.handle,
                    { id: window.OctaneTypes.AttributeId.A_VALUE },
                );
                if (!response.success) {
                    throw new Error('Failed GenericNodeRenderer.addSceneItem(): ApiItem/attrInfo');
                }
                iitem['attrInfo'] = response.data.result;

            } catch (error) {
                console.error('❌ Failed addSceneItem(): ', error);
            }
            window.debugConsole.log( `${iitem.level == 1 ? "TopNode" : "EndNode"} ${iitem.handle} ${iitem.name} ${iitem.outType} ${iitem.attrInfo ? iitem.attrInfo.type : ""}`);            
        }
        else {
            window.debugConsole.log( `${iitem.level == 1 ? "TopNode" : "ParNode"} ${iitem.handle} ${iitem.name} ${iitem.outType} ${iitem.pinInfo ? iitem.pinInfo.type : ""}`);            
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
            const response = await this.makeApiCall('/octane/render/start', {
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
            const response = await this.makeApiCall('/octane/render/stop', {
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
            const response = await this.makeApiCall('/octane/render/progress', {
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
            const response = await this.makeApiCall('/octane/render/settings', {
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
            const response = await this.makeApiCall('LiveLink/GetCamera');
            
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
            const response = await this.makeApiCall('LiveLink/SetCamera', {
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
            const response = await this.makeApiCall('LiveLink/SetCamera', {
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
            const response = await this.makeApiCall('LiveLink/SetCamera', {
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


    // ==================== GRPC CALLS ====================

    /**
     * call octane
     */
    async makeApiCallAsync(servicePath, handle, request = {}) {

        return this.makeApiCall(servicePath, handle, request, true);
    }

    /**
     * call octane
     */
    makeApiCall(servicePath, handle,  request = {}, doAsync = false) {

        try {
            // Build request data
            const [serviceName, methodName] = servicePath.split('/');
            
            if (typeof handle !== "string") {
                request = handle;
            }
            else {
                // Add objectPtr if handle is provided and service needs it
                // Determine the correct type for this service
                const objectPtrType = window.OctaneTypes.ObjectType[serviceName];
        
                if (objectPtrType !== undefined) {
                    request.objectPtr = {
                        handle: handle,
                        type: objectPtrType
                    };
                }
            }
            request = JSON.stringify(request);
            window.debugConsole.logLevel(!this.isSyncing ? 2:1, `makeApiCall(): ${servicePath}`, request);
            
            const url = `${this.proxyUrl}/${servicePath}`;
            const xhr = new XMLHttpRequest();
            xhr.open('POST', url, doAsync); // false = synchronous
            xhr.setRequestHeader('Content-Type', 'application/json');
            xhr.send(request);
            
            if (xhr.status !== 200 && xhr.status !== 0) {
                throw new Error(`HTTP ${xhr.status}: ${xhr.statusText}`);
            }
            const response = xhr.responseText ? JSON.parse(xhr.responseText) : {};
            window.debugConsole.logLevel(!this.isSyncing ? 2:1, `response`, JSON.stringify(response, null, 2));

            return response;
            
        } catch (error) {
            console.error(`❌ makeApiCall() failed: ${servicePath}:`, error);
//            throw error;
            return false;
        }
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
    window.octaneClient = OctaneWebClient;
}

