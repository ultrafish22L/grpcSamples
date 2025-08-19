/**
 * OctaneWeb gRPC Client
 * 
 * Extended gRPC client providing complete Octane LiveLink API coverage for
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
 * - Extends LiveLinkClient from livelink.js for base gRPC functionality
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
        this.setupExtendedEventHandlers();
        
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
     * Extended initialization is handled by individual components as needed
     */
    async initializeExtendedFeatures() {
        try {
            // Extended initialization is handled by individual components
            // SceneOutliner handles scene data loading
            // NodeInspector handles node graph synchronization
            // RenderViewport handles render state management
            
        } catch (error) {
            console.error('Failed to initialize extended features:', error);
            throw error;
        }
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
            
            // For LiveLink methods, use LiveLinkService
            if (['SetCamera', 'GetCamera', 'GetMeshes'].includes(method)) {
                serviceName = 'LiveLinkService';
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
        // console.log(`\n🌐 === gRPC CALL STARTED ===`);
        // console.log(`🌐 Service: ${serviceName}`);
        // console.log(`🌐 Method: ${methodName}`);
        // console.log(`🌐 Call ID: ${callId}`);
        // console.log(`🌐 Call Number: ${this.callCount}`);
        // console.log(`🌐 Connection State: ${this.connectionState}`);
        // console.log(`🌐 Request:`, actualRequest);
        // console.log(`🌐 Request JSON:`, JSON.stringify(actualRequest, null, 2));
        
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
            
            // console.log(`🌐 Request Body:`, requestBody);
            // console.log(`🌐 Request Body JSON:`, JSON.stringify(requestBody, null, 2));

            const controller = new AbortController();
            const timeoutId = setTimeout(() => {
                controller.abort();
                this.log(`gRPC call timeout: ${serviceName}.${methodName}`, { callId, duration: Date.now() - startTime }, 'error');
            }, 30000); // 30 second timeout

            // Use direct service endpoint instead of /api
            const url = `${this.serverUrl}/${serviceName}/${methodName}`;
            const body = JSON.stringify(actualRequest || {});
            
            // console.log(`🌐 LOCKIT: Making fetch request to: ${url}`);
            // console.log(`🌐 LOCKIT: Request body: ${body}`);
            // console.log(`🌐 LOCKIT: Headers:`, {
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
            
            // console.log(`🌐 LOCKIT: Response status: ${response.status}`);
            // console.log(`🌐 LOCKIT: Response ok: ${response.ok}`);

            clearTimeout(timeoutId);

            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }

            const result = await response.json();
            const duration = Date.now() - startTime;

            // Enhanced response logging (disabled for performance)
            // console.log(`\n📥 === gRPC RESPONSE RECEIVED ===`);
            // console.log(`📥 Method: ${method}`);
            // console.log(`📥 Call ID: ${callId}`);
            // console.log(`📥 Duration: ${duration}ms`);
            // console.log(`📥 HTTP Status: ${response.status} ${response.statusText}`);
            // console.log(`📥 Success: ${result.success}`);
            // console.log(`📥 Data Size: ${JSON.stringify(result).length} bytes`);
            // console.log(`📥 Result:`, result);
            // console.log(`📥 Result JSON:`, JSON.stringify(result, null, 2));
            
            // if (result.success && result.data) {
            //     console.log(`📥 Response Data:`, result.data);
            //     console.log(`📥 Response Data JSON:`, JSON.stringify(result.data, null, 2));
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
            // Get the root node graph
            const rootResponse = await this.makeGrpcCall('ApiProjectManager/rootNodeGraph', {});
            
            if (!rootResponse.success || !rootResponse.data) {
                console.error('❌ Failed to get root node graph:', rootResponse);
                return { success: false, error: 'Failed to get root node graph' };
            }
            
            // Extract ObjectRef from response
            const rootObjectRef = rootResponse.data.objectRef || rootResponse.data.result;
            if (!rootObjectRef) {
                console.error('❌ No objectRef in rootNodeGraph response');
                return { success: false, error: 'No objectRef in root response' };
            }
            
            // Step 2: Recursively build the scene tree
            const sceneHierarchy = await this.buildSceneTreeRecursive(rootObjectRef, 'Root');
            
            if (sceneHierarchy) {
                // Update scene state
                this.sceneState.hierarchy = [sceneHierarchy];
                
                // Emit scene update event
                this.emit('ui:sceneUpdate', this.sceneState);
                this.emit('ui:sceneHierarchyUpdate', [sceneHierarchy]);
                
                return { success: true, hierarchy: [sceneHierarchy] };
            } else {
                console.error('❌ Failed to build scene tree');
                return { success: false, error: 'Failed to build scene tree' };
            }
            
        } catch (error) {
            console.error('❌ Error loading scene data:', error);
        }
    }
    
    /**
     * Recursively build scene tree from Octane node graph
     */
    async buildSceneTreeRecursive(objectRef, name = 'Node', depth = 0) {
        try {
            console.log(`${'  '.repeat(depth)}📊 NAME ${name}: ${objectRef}`);
            // Name - FIXED: Use handle from ObjectPtr and set correct type for ApiItem
            try {
                const response = await this.makeGrpcCall('ApiItem/name', {
                    objectPtr: {
                        handle: objectRef.handle,
                        type: objectRef.type  // Use original type for ApiItem calls
                    }
                });
                console.log(`${'  '.repeat(depth)}📊 name() API result for ${name}: ${response}`);
                if (response.success && response.data && response.data.result) {
                    name = response.data.result;  // Update name with real result
                }
            } catch (error) {
                console.warn(`${'  '.repeat(depth)}⚠️ name() API failed for ${name}:`, error);
            }
            console.log(`${'  '.repeat(depth)}🌿 Building node: ${name} (handle=${objectRef.handle})`);
            
            // Create the node structure
            const node = {
                id: `node_${objectRef.handle}`,
                name: name,
                type: 'group',
                visible: true,
                children: [],
                objectRef: objectRef
            };
            // Check if this is a node graph - use known graph types as fallback
            console.log(`${'  '.repeat(depth)}🔍 Checking if ${name} is a graph (type ${objectRef.type})...`);
            
            let isGraph = false;
            
            // For unknown types, try the API call - FIXED: Use handle and correct type
            try {
                const isGraphResponse = await this.makeGrpcCall('ApiItem/isGraph', {
                    objectPtr: {
                        handle: objectRef.handle,
                        type: objectRef.type  // Use original type for ApiItem calls
                    }
                });
                isGraph = isGraphResponse.success && isGraphResponse.data.result;
                console.log(`${'  '.repeat(depth)}📊 isGraph API result for ${name}: ${isGraph}`);
            } catch (error) {
                console.warn(`${'  '.repeat(depth)}⚠️ isGraph API failed for ${name}, assuming not a graph:`, error);
                isGraph = false;
            }

            if (isGraph) {
                console.log(`${'  '.repeat(depth)}📤 Getting owned items for ${name} (graph supports children)...`);
                
                try {
                    // Convert to graph reference using toGraph() - with fallback for known types
                    let graphRef = null;
                    
                    // For unknown types, try the API conversion
                    console.log(`${'  '.repeat(depth)}🔄 Converting ${name} to graph reference via API...`);
                    const toGraphResponse = await this.makeGrpcCall('ApiItem/toGraph', {
                        objectPtr: objectRef
                    });
                    
                    if (!toGraphResponse.success || !toGraphResponse.data.result) {
                        console.warn(`${'  '.repeat(depth)}⚠️ Failed to convert ${name} to graph reference`);
                        return node;
                    }
                    
                    graphRef = toGraphResponse.data.result;
                    
                    console.log(`${'  '.repeat(depth)}📊 Graph reference:`, graphRef);
                    
                    const itemsResponse = await this.makeGrpcCall('ApiNodeGraph/getOwnedItems', {
                        objectPtr: graphRef
                    });
                
                console.log(`${'  '.repeat(depth)}📥 getOwnedItems response:`, JSON.stringify(itemsResponse, null, 2));
                
                if (itemsResponse.success && itemsResponse.data && itemsResponse.data.list) {
                    const itemsArrayRef = itemsResponse.data.list;
                    console.log(`${'  '.repeat(depth)}📋 Got items array: handle=${itemsArrayRef.objectHandle}, type=${itemsArrayRef.type}`);
                    
                    // Step 2: Get the actual items from the array using ApiItemArray/items
                    try {
                        console.log(`${'  '.repeat(depth)}📤 Getting items from array...`);
                        
                        const arrayItemsResponse = await this.makeGrpcCall('ApiItemArray/items', {
                            objectPtr: {
                                objectHandle: itemsArrayRef.objectHandle,
                                type: itemsArrayRef.type
                            }
                        });
                        
                        console.log(`${'  '.repeat(depth)}📥 Array items response:`, JSON.stringify(arrayItemsResponse, null, 2));
                        
                        // Extract items from the nested response structure
                        let items = null;
                        if (arrayItemsResponse.success && arrayItemsResponse.data) {
                            // Try different possible response structures
                            if (arrayItemsResponse.data.result && arrayItemsResponse.data.result.data) {
                                items = arrayItemsResponse.data.result.data;
                            } else if (arrayItemsResponse.data.items) {
                                items = arrayItemsResponse.data.items;
                            } else if (Array.isArray(arrayItemsResponse.data)) {
                                items = arrayItemsResponse.data;
                            }
                        }
                        
                        console.log(`${'  '.repeat(depth)}🔍 Debug items extraction:`, {
                            items: items,
                            isArray: Array.isArray(items),
                            length: items ? items.length : 'null',
                            type: typeof items
                        });
                        
                        // More detailed debugging
                        console.log(`${'  '.repeat(depth)}🔍 Detailed condition check:`, {
                            'items truthy': !!items,
                            'is array': Array.isArray(items),
                            'length > 0': items && items.length > 0,
                            'full condition': items && Array.isArray(items) && items.length > 0
                        });
                        
                        if (items && Array.isArray(items) && items.length > 0) {
                            console.log(`${'  '.repeat(depth)}✅ Found ${items.length} child items in array:`, items);
                            
                            // Recursively process each child item
                            for (let i = 0; i < items.length && depth < 5; i++) { // Limit depth to prevent infinite recursion
                                const item = items[i];
                                console.log(`${'  '.repeat(depth)}🔍 Processing item ${i + 1}:`, item);
                                
                                // Create objectRef from the item data
                                let objectRef = null;
                                if (item.objectRef) {
                                    objectRef = item.objectRef;
                                } else if (item.objectHandle && item.type) {
                                    // Convert item to objectRef format
                                    objectRef = {
                                        objectHandle: item.objectHandle,
                                        type: item.type
                                    };
                                }
                                
                                if (objectRef) {
                                    const childName = item.name || `Node_${objectRef.objectHandle}`;
                                    console.log(`${'  '.repeat(depth)}🌿 Recursing into child: ${childName} (handle=${objectRef.objectHandle}, type=${objectRef.type})`);
                                    
                                    const childNode = await this.buildSceneTreeRecursive(objectRef, childName, depth + 1);
                                    if (childNode) {
                                        node.children.push(childNode);
                                    }
                                } else {
                                    console.log(`${'  '.repeat(depth)}⚠️ Item ${i + 1} has no valid objectRef:`, item);
                                }
                            }
                        } else {
                            console.log(`${'  '.repeat(depth)}ℹ️ No items found in array`);
                        }
                        
                    } catch (arrayError) {
                        console.warn(`${'  '.repeat(depth)}⚠️ Failed to get items from array:`, arrayError);
                    }
                    
                } else {
                    console.log(`${'  '.repeat(depth)}ℹ️ No items array found for ${name}`);
                }
                
                } catch (error) {
                    console.warn(`${'  '.repeat(depth)}⚠️ Failed to get owned items for ${name}:`, error);
                }
            } else {
                // Check if this is a node - try API call with fallback
                console.log(`${'  '.repeat(depth)}🔍 Checking if ${name} is a node (type ${objectRef.type})...`);
                
                let isNode = false;
                
                // Try the API call first - FIXED: Use handle and correct type
                try {
                    const isNodeResponse = await this.makeGrpcCall('octaneapi.ApiItem/isNode', {
                        objectPtr: {
                            handle: objectRef.handle,
                            type: objectRef.type  // Use original type for ApiItem calls
                        }
                    });
                    isNode = isNodeResponse.success && isNodeResponse.data.result;
                    console.log(`${'  '.repeat(depth)}📊 isNode API result for ${name}: ${isNode}`);
                } catch (error) {
                    console.warn(`${'  '.repeat(depth)}⚠️ isNode API failed for ${name}:`, error);
                    // Fallback: assume non-graph types might be nodes (except known leaf types)
                    const knownLeafTypes = [16]; // ApiItem base type
                    isNode = !knownLeafTypes.includes(objectRef.type);
                    console.log(`${'  '.repeat(depth)}📊 Fallback isNode result for ${name}: ${isNode}`);
                }
                
                if (isNode) {
                    // Convert to node reference using toNode() - with fallback
                    let nodeRef = null;
                    
                    try {
                        console.log(`${'  '.repeat(depth)}🔄 Converting ${name} to node reference via API...`);
                        const toNodeResponse = await this.makeGrpcCall('octaneapi.ApiItem/toNode', {
                            objectPtr: {
                                handle: objectRef.handle,
                                type: objectRef.type  // Use original type for ApiItem calls
                            }
                        });
                        
                        if (toNodeResponse.success && toNodeResponse.data.result) {
                            nodeRef = toNodeResponse.data.result;
                        }
                    } catch (error) {
                        console.warn(`${'  '.repeat(depth)}⚠️ toNode API failed, using direct reference:`, error);
                        nodeRef = objectRef; // Fallback to direct reference
                    }
                    
                    if (nodeRef) {
                        console.log(`${'  '.repeat(depth)}📌 ApiNode: ${name} - checking pins for owned items`);
                        await this.processNodePins(nodeRef, node, name, depth);
                    } else {
                        console.warn(`${'  '.repeat(depth)}⚠️ Failed to get node reference for ${name}`);
                    }
                } else {
                    console.log(`${'  '.repeat(depth)}📄 Plain ApiItem: ${name} - leaf object`);
                }
            }
            
            return node;
            
        } catch (error) {
            console.error(`${'  '.repeat(depth)}❌ Error building node ${name}:`, error);
            return null;
        }
    }

    async processNodePins(objectRef, node, name, depth) {
        try {
            const indent = '  '.repeat(depth);
            console.log(`${indent}📍 Getting pin count for node ${name}...`);
            
            // Check if OctaneTypes is available
            if (!window.OctaneTypes || !window.OctaneTypes.createObjectPtr) {
                console.error('❌ OctaneTypes not loaded - ensure js/constants/OctaneTypes.js is loaded before components');
                return [];
            }
            
            // First get the pin count for this node - FIXED: Use handle and ApiNode type
            const pinCountResponse = await this.makeGrpcCall('octaneapi.ApiNode/pinCount', {
                objectPtr: window.OctaneTypes.createObjectPtr(objectRef.handle, window.OctaneTypes.ApiNode)
            });

            console.log(`${indent}📥 Pin count response:`, JSON.stringify(pinCountResponse, null, 2));

            if (pinCountResponse.success && pinCountResponse.data && pinCountResponse.data.count > 0) {
                const pinCount = pinCountResponse.data.count;
                console.log(`${indent}📍 Node ${name} has ${pinCount} pins`);
                
                // Iterate through each pin to get owned items
                for (let pinIndex = 0; pinIndex < pinCount && depth < 5; pinIndex++) {
                    try {
                        console.log(`${indent}  📎 Checking pin ${pinIndex} for owned item...`);
                        
                        const ownedItemResponse = await this.makeGrpcCall('octaneapi.ApiNode/ownedItemIx', {
                            objectPtr: window.OctaneTypes.createObjectPtr(objectRef.handle, window.OctaneTypes.ApiNode),
                            pinIndex: pinIndex
                        });

                        console.log(`${indent}  📥 Pin ${pinIndex} owned item response:`, JSON.stringify(ownedItemResponse, null, 2));

                        if (ownedItemResponse.success && ownedItemResponse.data && ownedItemResponse.data.item) {
                            const ownedItem = ownedItemResponse.data.item;
                            console.log(`${indent}  📎 Pin ${pinIndex} owns item:`, ownedItem);
                            
                            // Create objectRef for the owned item - FIXED: Use handle format
                            const childObjectRef = {
                                handle: ownedItem.handle || ownedItem.objectHandle,
                                type: ownedItem.type
                            };
                            
                            const childName = `Pin${pinIndex}_${ownedItem.handle || ownedItem.objectHandle}`;
                            console.log(`${indent}  🌿 Recursing into pin-owned item: ${childName}`);
                            
                            const childNode = await this.buildSceneTreeRecursive(childObjectRef, childName, depth + 1);
                            if (childNode) {
                                node.children.push(childNode);
                            }
                        } else {
                            console.log(`${indent}  📎 Pin ${pinIndex} has no owned item`);
                        }
                    } catch (pinError) {
                        // This is normal for unconnected pins
                        console.log(`${indent}  ⚠️ Pin ${pinIndex} error (normal for unconnected pins):`, pinError.message);
                    }
                }
            } else {
                console.log(`${indent}📍 Node ${name} has no pins or pin count unavailable`);
            }
        } catch (error) {
            console.error(`${'  '.repeat(depth)}❌ Error processing pins for ${name}:`, error);
        }
    }
    
    /**
     * Convert mesh data to scene hierarchy format
     */
    convertMeshesToHierarchy(meshData) {
        // Handle different possible mesh data formats
        let meshes = [];
        
        if (Array.isArray(meshData)) {
            meshes = meshData;
        } else if (meshData.meshes && Array.isArray(meshData.meshes)) {
            meshes = meshData.meshes;
        } else if (typeof meshData === 'object') {
            // Single mesh object
            meshes = [meshData];
        }
        
        // Convert to hierarchy format
        return meshes.map((mesh, index) => ({
            id: mesh.id || `mesh_${index}`,
            name: mesh.name || `Mesh ${index + 1}`,
            type: 'mesh',
            visible: mesh.visible !== false,
            children: [],
            properties: {
                vertices: mesh.vertices || 0,
                faces: mesh.faces || 0,
                material: mesh.material || 'Default'
            }
        }));
    }
    
    /**
     * Synchronize complete scene hierarchy
     */
    async syncSceneHierarchy() {
        try {
            // Use the parent class's makeGrpcCall method
            const response = await this.makeGrpcCall('ApiProjectManager/buildSceneTree', {});
            
            if (response.success && response.data) {
                this.updateSceneHierarchy(response.data);
                this.emit('ui:sceneHierarchyUpdate', this.sceneState.hierarchy);
            }
            
            return response;
            
        } catch (error) {
            console.error('Failed to sync scene hierarchy:', error);
            // Don't throw error, just log it for now since this is extended functionality
            return { success: false, error: error.message };
        }
    }
    
    /**
     * Build complete scene tree from Octane project
     */
    async buildSceneTree() {
        try {
            const response = await this.makeGrpcCall('octaneapi.ApiProjectManager/buildSceneTree', {});
            
            if (response.success && response.data && response.data.success) {
                this.updateSceneHierarchy(response.data.hierarchy);
                this.emit('ui:sceneUpdate', this.sceneState);
                this.emit('ui:sceneHierarchyUpdate', this.sceneState.hierarchy);
                return response.data;
            } else {
                throw new Error(response.data?.error || 'Failed to build scene tree');
            }
            
        } catch (error) {
            console.error('Failed to build scene tree:', error);
            throw error;
        }
    }
    
    /**
     * Get object details by ID
     */
    async getObjectDetails(objectId) {
        try {
            const response = await this.makeGrpcCall('getSceneObject', {
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
            const response = await this.makeGrpcCall('/octane/scene/object/update', {
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
            const response = await this.makeGrpcCall('/octane/scene/select', {
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
            const response = await this.makeGrpcCall('ApiProjectManager/rootNodeGraph', {});
            
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
            const response = await this.makeGrpcCall('/octane/nodegraph/node/create', {
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
            const response = await this.makeGrpcCall('/octane/nodegraph/node/delete', {
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
            const response = await this.makeGrpcCall('/octane/nodegraph/connect', {
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
            const response = await this.makeGrpcCall('/octane/nodegraph/node/parameter', {
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
        // Scene sync every 5 seconds
        // TODO: implement proper scene tree method
        // this.syncIntervals.scene = setInterval(() => {
        //     if (this.isConnected) {
        //         this.syncSceneHierarchy().catch(console.error);
        //     }
        // }, 5000);
        
        // Render progress sync every 1 second when rendering
        this.syncIntervals.render = setInterval(() => {
            if (this.isConnected && this.renderState.isRendering) {
                this.getRenderProgress().catch(console.error);
            }
        }, 1000);
        
        // Node graph sync every 10 seconds
        // TODO: implement proper node graph method
        // this.syncIntervals.nodeGraph = setInterval(() => {
        //     if (this.isConnected) {
        //         this.syncNodeGraph().catch(console.error);
        //     }
        // }, 10000);
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