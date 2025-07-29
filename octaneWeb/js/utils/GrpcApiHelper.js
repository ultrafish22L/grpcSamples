/**
 * gRPC API Helper
 * Simplifies gRPC API calls by automatically determining ObjectPtr types
 * based on service/method names and handling common request patterns
 */

class GrpcApiHelper {
    constructor(proxyUrl = 'http://localhost:51023') {
        this.proxyUrl = proxyUrl;
        
        // Service/method to ObjectPtr type mapping
        // This maps gRPC service methods to the correct ObjectRef.ObjectType
        this.serviceTypeMap = {
            // Project Manager - typically uses root node graph
            'ApiProjectManager/rootNodeGraph': null, // No objectPtr needed
            
            // Node Graph operations - use ApiNodeGraph type
            'ApiNodeGraph/getOwnedItems': window.OctaneTypes?.CommonTypes?.NODE_GRAPH,
            'ApiNodeGraph/name': window.OctaneTypes?.CommonTypes?.NODE_GRAPH,
            'ApiNodeGraph/setName': window.OctaneTypes?.CommonTypes?.NODE_GRAPH,
            
            // Root Node Graph operations - use ApiRootNodeGraph type  
            'ApiRootNodeGraph/getOwnedItems': window.OctaneTypes?.CommonTypes?.ROOT_NODE_GRAPH,
            'ApiRootNodeGraph/name': window.OctaneTypes?.CommonTypes?.ROOT_NODE_GRAPH,
            
            // Node operations - use ApiNode type
            'ApiNode/name': window.OctaneTypes?.CommonTypes?.NODE,
            'ApiNode/pinCount': window.OctaneTypes?.CommonTypes?.NODE,
            'ApiNode/ownedItemIx': window.OctaneTypes?.CommonTypes?.NODE,
            'ApiNode/isNode': window.OctaneTypes?.CommonTypes?.NODE,
            'ApiNode/toNode': window.OctaneTypes?.CommonTypes?.NODE,
            
            // Item operations - use ApiItem type (16)
            'ApiItem/name': window.OctaneTypes?.ObjectType?.ApiItem,
            'ApiItem/isGraph': window.OctaneTypes?.ObjectType?.ApiItem,
            'ApiItem/isNode': window.OctaneTypes?.ObjectType?.ApiItem,
            'ApiItem/toNode': window.OctaneTypes?.ObjectType?.ApiItem,
            
            // Item Array operations - use ApiItemArray type (31)
            'ApiItemArray/size': window.OctaneTypes?.ObjectType?.ApiItemArray,
            'ApiItemArray/get1': window.OctaneTypes?.ObjectType?.ApiItemArray,
            'ApiItemArray/items': window.OctaneTypes?.ObjectType?.ApiItemArray,
        };
        
        // Add prefixed versions (octaneapi.ServiceName/method)
        const prefixedMap = {};
        Object.keys(this.serviceTypeMap).forEach(key => {
            prefixedMap[`octaneapi.${key}`] = this.serviceTypeMap[key];
        });
        Object.assign(this.serviceTypeMap, prefixedMap);
    }
    
    /**
     * Make a gRPC API call with automatic ObjectPtr type resolution
     * @param {string} servicePath - Service/method path (e.g., 'ApiNodeGraph/getOwnedItems')
     * @param {string|number} handle - Object handle (can be null for some calls)
     * @param {Object} additionalData - Additional JSON data to merge into request
     * @returns {Promise<Object>} API response
     */
    async makeApiCall(servicePath, handle = null, additionalData = {}) {
        try {
            // Check if OctaneTypes is available
            if (!window.OctaneTypes) {
                throw new Error('OctaneTypes not loaded - ensure js/constants/OctaneTypes.js is loaded');
            }
            
            // Determine the correct ObjectPtr type for this service/method
            const objectPtrType = this.serviceTypeMap[servicePath];
            
            // Build the request data
            let requestData = { ...additionalData };
            
            // Add objectPtr if handle is provided and type is known
            if (handle !== null && objectPtrType !== undefined) {
                if (objectPtrType === null) {
                    // Some methods don't need objectPtr (like rootNodeGraph)
                    console.log(`🔧 API Call: ${servicePath} (no objectPtr needed)`);
                } else {
                    const objectPtr = window.OctaneTypes.createObjectPtr(handle, objectPtrType);
                    requestData.objectPtr = objectPtr;
                    
                    const typeName = window.OctaneTypes.getObjectTypeName(objectPtrType);
                    console.log(`🔧 API Call: ${servicePath} with ObjectPtr(handle=${handle}, type=${objectPtrType}/${typeName})`);
                }
            } else if (handle !== null) {
                console.warn(`⚠️ Unknown service/method: ${servicePath} - using handle without type`);
                // Fallback: create objectPtr with handle but no specific type
                requestData.objectPtr = { handle: handle };
            } else {
                console.log(`🔧 API Call: ${servicePath} (no handle provided)`);
            }
            
            // Make the HTTP request to the proxy
            const url = `${this.proxyUrl}/${servicePath}`;
            console.log(`📤 Calling: ${url}`, requestData);
            
            const response = await fetch(url, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(requestData)
            });
            
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            
            const result = await response.json();
            console.log(`📥 Response from ${servicePath}:`, result);
            
            return result;
            
        } catch (error) {
            console.error(`❌ API call failed for ${servicePath}:`, error);
            throw error;
        }
    }
    
    /**
     * Add or update a service/method type mapping
     * @param {string} servicePath - Service/method path
     * @param {number|null} objectPtrType - ObjectPtr type or null if not needed
     */
    addServiceMapping(servicePath, objectPtrType) {
        this.serviceTypeMap[servicePath] = objectPtrType;
        console.log(`✅ Added service mapping: ${servicePath} -> ${objectPtrType}`);
    }
    
    /**
     * Get the ObjectPtr type for a service/method
     * @param {string} servicePath - Service/method path
     * @returns {number|null|undefined} ObjectPtr type
     */
    getServiceType(servicePath) {
        return this.serviceTypeMap[servicePath];
    }
    
    /**
     * List all known service mappings
     * @returns {Object} Service type mappings
     */
    getServiceMappings() {
        return { ...this.serviceTypeMap };
    }
}

// Create global instance
window.grpcApi = new GrpcApiHelper();

// Log successful loading
console.log('✅ GrpcApiHelper loaded successfully');
console.log(`📋 Known service mappings: ${Object.keys(window.grpcApi.serviceTypeMap).length}`);