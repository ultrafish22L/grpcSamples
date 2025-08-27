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
     * Make a SYNCHRONOUS gRPC API call (blocks until complete)
     * Use this for sequential operations that depend on previous results
     * @param {string} servicePath - Service/method path (e.g., 'ApiItem/name')
     * @param {string} handle - Object handle (optional for some services)
     * @param {Object} additionalData - Additional request data (optional)
     * @returns {Object} Response data (not a Promise)
     */
    makeApiCall(servicePath, handle = null, additionalData = {}) {
        
        try {
            // Check if OctaneTypes is available
            if (!window.OctaneTypes) {
                throw new Error('OctaneTypes not loaded - ensure js/constants/OctaneTypes.js is loaded');
            }            
            // Build request data
            const [serviceName, methodName] = servicePath.split('/');
            
            let requestData = additionalData;
            // Add objectPtr if handle is provided and service needs it
            if (handle !== null) {

                // Determine the correct ObjectPtr type for this service
                const objectPtrType = window.OctaneTypes.ObjectType[serviceName];
        
                if (objectPtrType !== undefined) {
                    requestData.objectPtr = {
                        handle: handle,
                        type: objectPtrType
                    };
                }
            }
            // Make SYNCHRONOUS HTTP request using XMLHttpRequest
            const url = `${this.proxyUrl}/${servicePath}`;
            
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
//            throw error;
            return { success: false }
        }
    }
}

// Create global instance
window.grpcApi = new GrpcApiHelper();

// Log successful loading
console.log('GrpcApiHelper loaded successfully');
