/**
 * gRPC API Helper
 * Simplifies gRPC API calls by automatically determining ObjectPtr types
 * based on service/method names and handling common request patterns
 */

class GrpcApiHelper {
    constructor(proxyUrl = 'http://localhost:51023') {
        this.proxyUrl = proxyUrl;
        
        // Service class to ObjectPtr type mapping
        // Maps gRPC service class names to the correct ObjectRef.ObjectType
        this.serviceTypeMap = {
            // Services that don't need objectPtr
            'ApiProjectManager': null,
            
            // Core object types
            'ApiNodeGraph': window.OctaneTypes?.CommonTypes?.NODE_GRAPH,        // 20
            'ApiRootNodeGraph': window.OctaneTypes?.CommonTypes?.ROOT_NODE_GRAPH, // 18
            'ApiNode': window.OctaneTypes?.CommonTypes?.NODE,                   // 17
            'ApiItem': window.OctaneTypes?.ObjectType?.ApiItem,                 // 16
            'ApiItemArray': window.OctaneTypes?.ObjectType?.ApiItemArray,       // 31
            
            // Additional service types (add as needed)
            'ApiNodeArray': window.OctaneTypes?.ObjectType?.ApiNodeArray,       // 34
            'ApiPackage': window.OctaneTypes?.ObjectType?.ApiPackage,           // 37
            'ApiRenderImage': window.OctaneTypes?.ObjectType?.ApiRenderImage,   // 38
            'ApiSceneExporter': window.OctaneTypes?.ObjectType?.ApiSceneExporter, // 39
            'ApiMainWindow': window.OctaneTypes?.ObjectType?.ApiMainWindow,     // 42
            'ApiSceneOutliner': window.OctaneTypes?.ObjectType?.ApiSceneOutliner, // 51
            'ApiNodeGraphEditor': window.OctaneTypes?.ObjectType?.ApiNodeGraphEditor, // 52
        };
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
            
            // Extract service name from servicePath (e.g., 'ApiNodeGraph' from 'ApiNodeGraph/getOwnedItems')
            const serviceName = servicePath.split('/')[0];
            
            // Determine the correct ObjectPtr type for this service
            const objectPtrType = this.serviceTypeMap[serviceName];
            
            // Build the request data
            let requestData = { ...additionalData };
            
            // Add objectPtr if handle is provided and type is known
            if (handle !== null && objectPtrType !== undefined) {
                if (objectPtrType === null) {
                    // Some services don't need objectPtr (like ApiProjectManager)
                    console.log(`🔧 API Call: ${servicePath} (no objectPtr needed)`);
                } else {
                    const objectPtr = window.OctaneTypes.createObjectPtr(handle, objectPtrType);
                    requestData.objectPtr = objectPtr;
                    
                    const typeName = window.OctaneTypes.getObjectTypeName(objectPtrType);
                    console.log(`🔧 API Call: ${servicePath} with ObjectPtr(handle=${handle}, type=${objectPtrType}/${typeName})`);
                }
            } else if (handle !== null) {
                console.warn(`⚠️ Unknown service: ${serviceName} - using handle without type`);
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
     * Add or update a service type mapping
     * @param {string} serviceName - Service class name (e.g., 'ApiNodeGraph')
     * @param {number|null} objectPtrType - ObjectPtr type or null if not needed
     */
    addServiceMapping(serviceName, objectPtrType) {
        this.serviceTypeMap[serviceName] = objectPtrType;
        console.log(`✅ Added service mapping: ${serviceName} -> ${objectPtrType}`);
    }
    
    /**
     * Get the ObjectPtr type for a service
     * @param {string} serviceName - Service class name (e.g., 'ApiNodeGraph')
     * @returns {number|null|undefined} ObjectPtr type
     */
    getServiceType(serviceName) {
        return this.serviceTypeMap[serviceName];
    }
    
    /**
     * List all known service mappings
     * @returns {Object} Service type mappings
     */
    getServiceMappings() {
        return { ...this.serviceTypeMap };
    }
    
    /**
     * Make a SYNCHRONOUS gRPC API call (blocks until complete)
     * Use this for sequential operations that depend on previous results
     * @param {string} servicePath - Service/method path (e.g., 'ApiItem/name')
     * @param {string} handle - Object handle (optional for some services)
     * @param {Object} additionalData - Additional request data (optional)
     * @returns {Object} Response data (not a Promise)
     */
    makeApiCallSync(servicePath, handle = null, additionalData = {}) {
        console.log(`🔒 SYNC API Call: ${servicePath} (handle: ${handle})`);
        
        try {
            // Build request data using the same logic as async version
            const [serviceName, methodName] = servicePath.split('/');
            const serviceType = this.getServiceType(serviceName);
            
            let requestData = { ...additionalData };
            
            // Add objectPtr if handle is provided and service needs it
            if (handle && serviceType !== null && serviceType !== undefined) {
                requestData.objectPtr = {
                    handle: handle.toString(),
                    type: serviceType
                };
            }
            
            if (handle) {
                console.log(`🔧 SYNC API Call: ${servicePath} with handle ${handle} (type: ${serviceType})`);
            } else {
                console.log(`🔧 SYNC API Call: ${servicePath} (no handle provided)`);
            }
            
            // Make SYNCHRONOUS HTTP request using XMLHttpRequest
            const url = `${this.proxyUrl}/${servicePath}`;
            console.log(`📤 SYNC Calling: ${url}`, requestData);
            
            const xhr = new XMLHttpRequest();
            xhr.open('POST', url, false); // false = synchronous
            xhr.setRequestHeader('Content-Type', 'application/json');
            xhr.send(JSON.stringify(requestData));
            
            if (xhr.status !== 200) {
                throw new Error(`HTTP ${xhr.status}: ${xhr.statusText}`);
            }
            
            const result = JSON.parse(xhr.responseText);
            console.log(`📥 SYNC Response from ${servicePath}:`, result);
            
            return result;
            
        } catch (error) {
            console.error(`❌ SYNC API call failed for ${servicePath}:`, error);
            throw error;
        }
    }
}

// Create global instance
window.grpcApi = new GrpcApiHelper();

// Log successful loading
console.log('✅ GrpcApiHelper loaded successfully');
console.log(`📋 Known service mappings: ${Object.keys(window.grpcApi.serviceTypeMap).length} services`);