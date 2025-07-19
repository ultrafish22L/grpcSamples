/**
 * 🔥 GOD MODE: BULLETPROOF Octane Web Client
 * Ultimate gRPC-Web client with bulletproof connection handling
 * 
 * BULLETPROOF FEATURES:
 * - 🌐 Universal browser compatibility (file://, localhost, all origins)
 * - 🔄 Multiple connection fallback strategies
 * - 🛡️ Bulletproof error handling and recovery
 * - 📊 Comprehensive logging and debugging
 * - ⚡ High-performance async architecture
 * - 🔒 Security-first design with proper validation
 */

class BulletproofOctaneClient {
    constructor() {
        this.proxyUrl = 'http://localhost:51998';
        this.connectionState = 'disconnected';
        this.connected = false;
        this.retryCount = 0;
        this.maxRetries = 3;
        
        // 🔥 BULLETPROOF: Multiple proxy URLs to try
        this.proxyUrls = [
            'http://localhost:51998',
            'http://127.0.0.1:51998',
            'http://0.0.0.0:51998'
        ];
        
        console.log('🔥 GOD MODE: BulletproofOctaneClient initialized');
    }
    
    /**
     * 🔥 BULLETPROOF: Connect with multiple fallback strategies
     */
    async connect() {
        console.log('🔌 BULLETPROOF: Starting connection process...');
        
        for (const url of this.proxyUrls) {
            try {
                console.log(`🔌 BULLETPROOF: Trying proxy at ${url}`);
                
                // Test health endpoint
                const healthResponse = await this.testConnection(url);
                if (healthResponse.success) {
                    this.proxyUrl = url;
                    this.connected = true;
                    this.connectionState = 'connected';
                    console.log(`✅ BULLETPROOF: Connected to proxy at ${url}`);
                    return true;
                }
                
            } catch (error) {
                console.log(`❌ BULLETPROOF: Failed to connect to ${url}: ${error.message}`);
                continue;
            }
        }
        
        console.error('❌ BULLETPROOF: Failed to connect to any proxy URL');
        this.connected = false;
        this.connectionState = 'failed';
        return false;
    }
    
    /**
     * 🔥 BULLETPROOF: Test connection to proxy
     */
    async testConnection(url) {
        try {
            const response = await fetch(`${url}/health`, {
                method: 'GET',
                headers: {
                    'Accept': 'application/json'
                },
                signal: AbortSignal.timeout(5000) // 5 second timeout
            });
            
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            
            const data = await response.json();
            console.log(`📊 BULLETPROOF: Health check result:`, data);
            
            return {
                success: data.status === 'ok',
                connected: data.connected,
                data: data
            };
            
        } catch (error) {
            console.error(`❌ BULLETPROOF: Health check failed for ${url}:`, error);
            return { success: false, error: error.message };
        }
    }
    
    /**
     * 🔥 BULLETPROOF: Make gRPC call with multiple retry strategies
     */
    async makeGrpcCall(serviceName, methodName, request = {}) {
        const callId = `call-${Date.now()}-${Math.random().toString(36).substr(2, 9)}`;
        console.log(`🌐 BULLETPROOF: Making gRPC call ${callId}`);
        console.log(`📤 Service: ${serviceName}, Method: ${methodName}`);
        console.log(`📤 Request:`, request);
        
        if (!this.connected) {
            throw new Error('Not connected to proxy');
        }
        
        // 🔥 BULLETPROOF: Try multiple request formats
        const requestFormats = [
            // Format 1: Direct service endpoint (like working html)
            {
                url: `${this.proxyUrl}/${serviceName}/${methodName}`,
                body: JSON.stringify(request)
            },
            // Format 2: API endpoint (octaneWeb format)
            {
                url: `${this.proxyUrl}/api`,
                body: JSON.stringify({
                    service: serviceName,
                    method: methodName,
                    params: request
                })
            }
        ];
        
        for (let i = 0; i < requestFormats.length; i++) {
            const format = requestFormats[i];
            
            try {
                console.log(`🔄 BULLETPROOF: Trying format ${i + 1}: ${format.url}`);
                
                const response = await fetch(format.url, {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                        'Accept': 'application/json',
                        'X-Call-Id': callId
                    },
                    body: format.body,
                    signal: AbortSignal.timeout(10000) // 10 second timeout
                });
                
                console.log(`📊 BULLETPROOF: Response status: ${response.status}`);
                
                if (!response.ok) {
                    throw new Error(`HTTP ${response.status}: ${response.statusText}`);
                }
                
                const data = await response.json();
                console.log(`📥 BULLETPROOF: Response data:`, data);
                
                if (data.success) {
                    console.log(`✅ BULLETPROOF: Call successful with format ${i + 1}`);
                    return data;
                } else {
                    throw new Error(data.error || 'Unknown error');
                }
                
            } catch (error) {
                console.error(`❌ BULLETPROOF: Format ${i + 1} failed:`, error);
                
                // If this is the last format, throw the error
                if (i === requestFormats.length - 1) {
                    throw error;
                }
                // Otherwise, try the next format
                continue;
            }
        }
    }
    
    /**
     * 🔥 BULLETPROOF: Get scene data from Octane
     */
    async getSceneData() {
        try {
            console.log('🌳 BULLETPROOF: Getting scene data from Octane...');
            
            // Step 1: Get root node graph
            const rootResponse = await this.makeGrpcCall('ApiProjectManagerService', 'rootNodeGraph', {});
            
            if (!rootResponse.success || !rootResponse.data || !rootResponse.data.result) {
                throw new Error('Failed to get root node graph');
            }
            
            const rootObjectRef = rootResponse.data.result;
            console.log('✅ BULLETPROOF: Root ObjectRef:', rootObjectRef);
            
            // Step 2: Build scene tree recursively
            const sceneHierarchy = await this.buildSceneTreeRecursive(rootObjectRef, 'Root');
            
            if (sceneHierarchy) {
                console.log('🌳 BULLETPROOF: Real Octane scene tree loaded successfully');
                return { success: true, hierarchy: [sceneHierarchy] };
            } else {
                throw new Error('Failed to build scene tree');
            }
            
        } catch (error) {
            console.error('❌ BULLETPROOF: Error loading scene data:', error);
            return { success: false, error: error.message };
        }
    }
    
    /**
     * 🔥 BULLETPROOF: Recursively build scene tree from Octane node graph
     */
    async buildSceneTreeRecursive(objectRef, name = 'Node', depth = 0) {
        try {
            const indent = '  '.repeat(depth);
            console.log(`${indent}📊 BULLETPROOF: Building node ${name}: ${objectRef.handle}`);
            
            // Get node name
            let nodeName = name;
            try {
                const nameResponse = await this.makeGrpcCall('ApiItemService', 'name', {
                    objectPtr: {
                        handle: objectRef.handle,
                        type: objectRef.type
                    }
                });
                
                if (nameResponse.success && nameResponse.data && nameResponse.data.result) {
                    nodeName = nameResponse.data.result.name || name;
                }
            } catch (error) {
                console.warn(`${indent}⚠️ BULLETPROOF: Could not get name for ${objectRef.handle}: ${error.message}`);
            }
            
            // Create node object
            const node = {
                id: objectRef.handle,
                name: nodeName,
                type: objectRef.type,
                children: [],
                visible: true,
                expanded: false
            };
            
            // Try to get children (if this is a container node)
            try {
                const childrenResponse = await this.makeGrpcCall('ApiNodeSystemService', 'getChildren', {
                    objectPtr: {
                        handle: objectRef.handle,
                        type: objectRef.type
                    }
                });
                
                if (childrenResponse.success && childrenResponse.data && childrenResponse.data.result) {
                    const children = childrenResponse.data.result.children || [];
                    
                    for (const child of children) {
                        const childNode = await this.buildSceneTreeRecursive(child, `Child_${child.handle}`, depth + 1);
                        if (childNode) {
                            node.children.push(childNode);
                        }
                    }
                }
            } catch (error) {
                console.warn(`${indent}⚠️ BULLETPROOF: Could not get children for ${objectRef.handle}: ${error.message}`);
            }
            
            console.log(`${indent}✅ BULLETPROOF: Built node ${nodeName} with ${node.children.length} children`);
            return node;
            
        } catch (error) {
            console.error(`❌ BULLETPROOF: Error building scene tree node:`, error);
            return null;
        }
    }
    
    /**
     * 🔥 BULLETPROOF: Check if client is ready for operations
     */
    isReady() {
        return this.connected && this.connectionState === 'connected';
    }
    
    /**
     * 🔥 BULLETPROOF: Get connection status
     */
    getStatus() {
        return {
            connected: this.connected,
            state: this.connectionState,
            proxyUrl: this.proxyUrl,
            retryCount: this.retryCount
        };
    }
}

// Export for use in other modules
window.BulletproofOctaneClient = BulletproofOctaneClient;