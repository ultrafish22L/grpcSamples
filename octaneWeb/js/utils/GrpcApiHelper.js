/**
 * gRPC API Helper
 * Simplifies gRPC API calls by automatically determining ObjectPtr types
 * based on service/method names and handling common request patterns
 */

class GrpcApiHelper {
    constructor(proxyUrl = 'http://localhost:51023') {
        this.proxyUrl = proxyUrl;
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
            // Build request data using the same logic as async version
            const [serviceName, methodName] = servicePath.split('/');
            
            // Determine the correct ObjectPtr type for this service
            const objectPtrType = window.OctaneTypes.ObjectType[serviceName];
            console.log(`SYNC API Call: ${serviceName}:${methodName} (handle: ${handle} type: ${objectPtrType})`);
            
            let requestData = { };
            
            // Add objectPtr if handle is provided and service needs it
            if (handle !== null && objectPtrType !== undefined) {
                requestData.objectPtr = {
                    handle: handle.toString(),
                    type: objectPtrType
                };
            }
            requestData = { ...requestData, ...additionalData }

            // Make SYNCHRONOUS HTTP request using XMLHttpRequest
            const url = `${this.proxyUrl}/${servicePath}`;
            console.log(`Calling: ${url}`, requestData);
            
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
     * Make a SYNCHRONOUS gRPC API call (blocks until complete)
     * Use this for sequential operations that depend on previous results
     * @param {string} servicePath - Service/method path (e.g., 'ApiItem/name')
     * @param {string} handle - Object handle (optional for some services)
     * @param {Object} additionalData - Additional request data (optional)
     * @returns {Object} Response data (not a Promise)
     */
    makeApiCallSync(servicePath, handle = null, additionalData = {}) {
        
        try {
            // Check if OctaneTypes is available
            if (!window.OctaneTypes) {
                throw new Error('OctaneTypes not loaded - ensure js/constants/OctaneTypes.js is loaded');
            }            
            // Build request data using the same logic as async version
            const [serviceName, methodName] = servicePath.split('/');
            
            // Determine the correct ObjectPtr type for this service
            const objectPtrType = window.OctaneTypes.ObjectType[serviceName];
//            console.log(`SYNC API Call: ${serviceName}:${methodName} (handle: ${handle} type: ${objectPtrType})`);
            
            let requestData = { };
            
            // Add objectPtr if handle is provided and service needs it
            if (handle !== null && objectPtrType !== undefined) {
                requestData.objectPtr = {
                    handle: handle.toString(),
                    type: objectPtrType
                };
            }
            requestData = { ...requestData, ...additionalData }

            // Make SYNCHRONOUS HTTP request using XMLHttpRequest
            const url = `${this.proxyUrl}/${servicePath}`;
//            console.log(`Calling: ${url}`, requestData);
            
            const xhr = new XMLHttpRequest();
            xhr.open('POST', url, false); // false = synchronous
            xhr.setRequestHeader('Content-Type', 'application/json');
            xhr.send(JSON.stringify(requestData));
            
            if (xhr.status !== 200) {
                throw new Error(`HTTP ${xhr.status}: ${xhr.statusText}`);
            }
            
            const result = JSON.parse(xhr.responseText);
//            console.log(`Response from ${servicePath}:`, result);
            
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
