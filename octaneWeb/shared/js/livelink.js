/**
 * LiveLink gRPC-Web Client
 * Custom implementation for connecting to Octane Render via gRPC-Web
 */

/**
 * Simple event emitter for client events
 */
class SimpleEventEmitter {
    constructor() {
        this.listeners = new Map();
    }
    
    on(event, callback) {
        if (!this.listeners.has(event)) {
            this.listeners.set(event, []);
        }
        this.listeners.get(event).push(callback);
    }
    
    emit(event, ...args) {
        if (this.listeners.has(event)) {
            this.listeners.get(event).forEach(callback => {
                try {
                    callback(...args);
                } catch (error) {
                    console.error('Event listener error:', error);
                }
            });
        }
    }
    
    removeAllListeners(event) {
        if (event) {
            // Remove listeners for specific event
            this.listeners.delete(event);
        } else {
            // Remove all listeners for all events
            this.listeners.clear();
        }
    }
    
    removeListener(event, callback) {
        if (this.listeners.has(event)) {
            const callbacks = this.listeners.get(event);
            const index = callbacks.indexOf(callback);
            if (index > -1) {
                callbacks.splice(index, 1);
                if (callbacks.length === 0) {
                    this.listeners.delete(event);
                }
            }
        }
    }
}

/**
 * LiveLink Client for gRPC-Web communication with Octane
 */
class LiveLinkClient extends SimpleEventEmitter {
    constructor(serverUrl = 'http://localhost:51023') {
        super();
        this.serverUrl = serverUrl;
        this.connected = false;
        this.connectionState = 'disconnected';
        this.lastError = null;
        
        // Performance tracking
        this.callCount = 0;
        this.lastCallTime = 0;
        this.avgResponseTime = 0;
        this.errorCount = 0;
        
        // Sync tracking for camera operations
        this.syncCallCount = 0;
        this.lastSyncTime = Date.now();
        this.syncRate = 0;
        
        // Enhanced debugging
        this.debugMode = true;
        this.connectionAttempts = 0;
        this.lastConnectionAttempt = null;
        this.connectionHistory = [];
        this.errorHistory = [];
        
        this.log('LiveLinkClient created', {
            serverUrl: serverUrl,
            timestamp: new Date().toISOString(),
            userAgent: navigator.userAgent,
            location: window.location.href
        });
    }

    /**
     * Enhanced logging method with detailed debugging information
     */
    log(message, details = {}, level = 'info') {
        const timestamp = new Date().toISOString();
        const logEntry = {
            timestamp,
            level,
            message,
            details,
            connectionState: this.connectionState,
            serverUrl: this.serverUrl
        };
        
        // Console logging with color coding
        const colors = {
            error: 'color: #ff4444; font-weight: bold;',
            warn: 'color: #ffaa00; font-weight: bold;',
            info: 'color: #4444ff;',
            debug: 'color: #888888;',
            success: 'color: #44ff44; font-weight: bold;'
        };
        
        // Only log to console for errors and warnings (performance optimization)
        if (level === 'error' || level === 'warn') {
            // Note: Using console.log here is intentional for debug output
            console.log(`%c[${timestamp}] ${level.toUpperCase()}: ${message}`, colors[level] || colors.info, details);
        }
        
        // Create clean activity monitor message (time only, no date)
        const timeOnly = new Date().toLocaleTimeString('en-US', { 
            hour12: true, 
            hour: 'numeric', 
            minute: '2-digit', 
            second: '2-digit' 
        });
        
        // Check if message already has a timestamp to avoid duplication
        const hasTimestamp = message.match(/^\[\d{1,2}:\d{2}:\d{2}\s*(AM|PM)?\]/);
        const cleanMessage = hasTimestamp ? message : `[${timeOnly}] ${message}`;

        // Emit clean message for activity monitor UI
        this.emit('log', {
            ...logEntry,
            cleanMessage: cleanMessage,
            displayMessage: cleanMessage
        });
        this.emit('debug', cleanMessage, details);
        
        // Store error history
        if (level === 'error') {
            this.errorHistory.push(logEntry);
            if (this.errorHistory.length > 50) {
                this.errorHistory.shift(); // Keep last 50 errors
            }
        }
    }

    /**
     * Get detailed system information for debugging
     */
    getSystemInfo() {
        return {
            timestamp: new Date().toISOString(),
            userAgent: navigator.userAgent,
            platform: navigator.platform,
            language: navigator.language,
            cookieEnabled: navigator.cookieEnabled,
            onLine: navigator.onLine,
            connection: navigator.connection ? {
                effectiveType: navigator.connection.effectiveType,
                downlink: navigator.connection.downlink,
                rtt: navigator.connection.rtt
            } : 'not available',
            location: {
                href: window.location.href,
                protocol: window.location.protocol,
                host: window.location.host,
                port: window.location.port
            },
            screen: {
                width: screen.width,
                height: screen.height,
                colorDepth: screen.colorDepth
            }
        };
    }

    /**
     * Parse URL and validate server address
     */
    validateServerUrl(url) {
        try {
            const parsed = new URL(url);
            const validation = {
                valid: true,
                protocol: parsed.protocol,
                hostname: parsed.hostname,
                port: parsed.port || (parsed.protocol === 'https:' ? '443' : '80'),
                pathname: parsed.pathname,
                issues: []
            };

            // Check for common issues
            if (parsed.protocol !== 'http:' && parsed.protocol !== 'https:') {
                validation.issues.push(`Unsupported protocol: ${parsed.protocol}. Use http: or https:`);
            }
            
            if (parsed.hostname === 'localhost' || parsed.hostname === '127.0.0.1') {
                validation.issues.push('Using localhost/127.0.0.1 - ensure server is running locally');
            }
            
            if (!parsed.port && parsed.hostname !== 'localhost' && parsed.hostname !== '127.0.0.1') {
                validation.issues.push('No port specified - using default port');
            }

            return validation;
        } catch (error) {
            return {
                valid: false,
                error: error.message,
                issues: [`Invalid URL format: ${error.message}`]
            };
        }
    }

    /**
     * Connect to the Octane gRPC server
     */
    async connect() {
        this.connectionAttempts++;
        this.lastConnectionAttempt = new Date().toISOString();
        
        this.log('Connection attempt started', {
            attempt: this.connectionAttempts,
            serverUrl: this.serverUrl,
            currentState: this.connectionState,
            systemInfo: this.getSystemInfo()
        });
        
        // Validate server URL
        const urlValidation = this.validateServerUrl(this.serverUrl);
        if (!urlValidation.valid) {
            const error = new Error(`Invalid server URL: ${urlValidation.error}`);
            this.log('URL validation failed', urlValidation, 'error');
            throw error;
        }
        
        if (urlValidation.issues.length > 0) {
            this.log('URL validation warnings', { issues: urlValidation.issues }, 'warn');
        }
        
        if (this.connected || this.connectionState === 'connecting') {
            this.log('Connection already established or in progress', {
                connected: this.connected,
                state: this.connectionState
            }, 'warn');
            return Promise.resolve();
        }

        return new Promise((resolve, reject) => {
            try {
                this.connectionState = 'connecting';
                this.emit('connectionStateChanged', 'connecting');
                this.log('Connection state changed to connecting');
                
                // Test connection with comprehensive error handling
                this.testConnection().then(() => {
                    this.connected = true;
                    this.connectionState = 'connected';
                    
                    const connectionInfo = {
                        attempt: this.connectionAttempts,
                        serverUrl: this.serverUrl,
                        timestamp: new Date().toISOString(),
                        duration: Date.now() - new Date(this.lastConnectionAttempt).getTime()
                    };
                    
                    this.connectionHistory.push(connectionInfo);
                    if (this.connectionHistory.length > 20) {
                        this.connectionHistory.shift(); // Keep last 20 connections
                    }
                    
                    this.emit('connectionStateChanged', 'connected');
                    this.emit('connected');
                    this.log('Connection successful', connectionInfo, 'success');
                    resolve();
                }).catch((error) => {
                    this.handleConnectionError(error, reject);
                });
                
            } catch (error) {
                this.handleConnectionError(error, reject);
            }
        });
    }

    /**
     * Handle connection errors with detailed logging
     */
    handleConnectionError(error, reject) {
        this.lastError = error;
        this.connectionState = 'error';
        
        const errorDetails = {
            message: error.message,
            name: error.name,
            stack: error.stack,
            attempt: this.connectionAttempts,
            serverUrl: this.serverUrl,
            timestamp: new Date().toISOString(),
            systemInfo: this.getSystemInfo()
        };
        
        // Analyze error type and provide specific guidance
        const errorAnalysis = this.analyzeConnectionError(error);
        errorDetails.analysis = errorAnalysis;
        
        this.log('Connection failed', errorDetails, 'error');
        
        this.emit('connectionStateChanged', 'error');
        this.emit('error', error);
        
        if (reject) {
            reject(error);
        }
    }

    /**
     * Analyze connection errors and provide troubleshooting guidance
     */
    analyzeConnectionError(error) {
        const analysis = {
            errorType: 'unknown',
            likelyCause: 'Unknown error',
            suggestions: []
        };
        
        const message = error.message.toLowerCase();
        
        if (message.includes('net::err_connection_refused')) {
            analysis.errorType = 'connection_refused';
            analysis.likelyCause = 'Server is not running or not accepting connections';
            analysis.suggestions = [
                'Verify Octane Render is running',
                'Check if LiveLink server is enabled in Octane settings',
                'Verify the port number (common ports: 8080, 9090, 50051, 51022)',
                'Check firewall settings'
            ];
        } else if (message.includes('net::err_invalid_http_response')) {
            analysis.errorType = 'invalid_http_response';
            analysis.likelyCause = 'Server is running but not responding with valid HTTP';
            analysis.suggestions = [
                'Server might be running raw gRPC instead of gRPC-Web',
                'Try using a gRPC-Web proxy (octane_proxy.py)',
                'Verify server supports gRPC-Web protocol',
                'Check if server is configured for HTTP/2'
            ];
        } else if (message.includes('net::err_connection_timed_out')) {
            analysis.errorType = 'timeout';
            analysis.likelyCause = 'Connection timeout - server not responding';
            analysis.suggestions = [
                'Server might be overloaded or slow to respond',
                'Check network connectivity',
                'Try a different server address',
                'Increase timeout settings if available'
            ];
        } else if (message.includes('net::err_name_not_resolved')) {
            analysis.errorType = 'dns_error';
            analysis.likelyCause = 'Cannot resolve server hostname';
            analysis.suggestions = [
                'Check server hostname spelling',
                'Try using IP address instead of hostname',
                'Check DNS settings',
                'Verify network connectivity'
            ];
        } else if (message.includes('cors')) {
            analysis.errorType = 'cors_error';
            analysis.likelyCause = 'Cross-Origin Resource Sharing (CORS) policy violation';
            analysis.suggestions = [
                'Server needs to allow CORS for web browsers',
                'Use a proxy server that handles CORS',
                'Run the web page from the same origin as the server'
            ];
        } else if (message.includes('fetch')) {
            analysis.errorType = 'fetch_error';
            analysis.likelyCause = 'Network request failed';
            analysis.suggestions = [
                'Check network connectivity',
                'Verify server URL is correct',
                'Try refreshing the page',
                'Check browser console for more details'
            ];
        }
        
        return analysis;
    }

    /**
     * Test connection to the server
     */
    async testConnection() {
        const startTime = Date.now();
        const testUrl = this.serverUrl + '/health';
        
        this.log('Testing connection', {
            url: testUrl,
            method: 'GET'
        });
        
        return new Promise((resolve, reject) => {
            try {
                const controller = new AbortController();
                const timeoutId = setTimeout(() => {
                    controller.abort();
                    const error = new Error('Connection test timeout after 10 seconds');
                    this.log('Connection test timeout', { 
                        url: testUrl, 
                        duration: Date.now() - startTime 
                    }, 'error');
                    reject(error);
                }, 10000);
                
                // Create a simple test request
                console.log('🔍 Starting fetch request to:', testUrl);
                fetch(testUrl, {
                    method: 'GET',
                    signal: controller.signal
                }).then(response => {
                    console.log('✅ Fetch response received:', response.status, response.statusText);
                    clearTimeout(timeoutId);
                    const duration = Date.now() - startTime;
                    
                    const responseDetails = {
                        status: response.status,
                        statusText: response.statusText,
                        headers: Object.fromEntries(response.headers.entries()),
                        url: response.url,
                        duration: duration,
                        ok: response.ok,
                        redirected: response.redirected,
                        type: response.type
                    };
                    
                    this.log('Connection test response received', responseDetails);
                    
                    // Analyze response to determine if server is compatible
                    if (response.status === 0) {
                        const error = new Error('Network error - server may not be running');
                        this.log('Network error detected', responseDetails, 'error');
                        reject(error);
                    } else if (response.status >= 200 && response.status < 300) {
                        this.log('Connection test successful', responseDetails, 'success');
                        resolve();
                    } else if (response.status === 404) {
                        this.log('Service endpoint not found - server may not support LiveLink', responseDetails, 'warn');
                        // Still resolve as server is reachable
                        resolve();
                    } else if (response.status >= 400 && response.status < 500) {
                        this.log('Client error response - server reachable but request invalid', responseDetails, 'warn');
                        // Still resolve as server is reachable
                        resolve();
                    } else if (response.status >= 500) {
                        this.log('Server error response - server reachable but has internal error', responseDetails, 'error');
                        // 500 errors indicate proxy can't connect to Octane - treat as connection failure
                        const error = new Error(`Server error: ${response.status} ${response.statusText} - Octane may not be running`);
                        reject(error);
                    } else {
                        this.log('Unexpected response status', responseDetails, 'warn');
                        resolve();
                    }
                    
                }).catch(error => {
                    console.error('❌ Fetch request failed:', error);
                    clearTimeout(timeoutId);
                    const duration = Date.now() - startTime;
                    
                    if (error.name === 'AbortError') {
                        // Timeout already handled above
                        return;
                    }
                    
                    const errorDetails = {
                        message: error.message,
                        name: error.name,
                        stack: error.stack,
                        duration: duration,
                        url: testUrl
                    };
                    
                    this.log('Connection test failed', errorDetails, 'error');
                    reject(error);
                });
                
            } catch (error) {
                const errorDetails = {
                    message: error.message,
                    name: error.name,
                    stack: error.stack,
                    url: testUrl
                };
                
                this.log('Connection test exception', errorDetails, 'error');
                reject(error);
            }
        });
    }

    /**
     * Disconnect from the server
     */
    async disconnect() {
        this.connected = false;
        this.connectionState = 'disconnected';
        this.emit('connectionStateChanged', 'disconnected');
        this.emit('disconnected');
        this.emit('debug', 'Disconnected');
    }

    /**
     * Check if client is ready for operations
     */
    isReady() {
        return this.connected && this.connectionState === 'connected';
    }

    /**
     * Get connection state
     */
    getConnectionState() {
        return this.connectionState;
    }

    /**
     * Get performance stats
     */
    getStats() {
        return {
            callCount: this.callCount,
            avgResponseTime: this.avgResponseTime,
            lastCallTime: this.lastCallTime,
            connected: this.connected,
            connectionState: this.connectionState,
            connectionAttempts: this.connectionAttempts,
            errorCount: this.errorCount,
            syncRate: this.syncRate
        };
    }

    /**
     * Make a gRPC-Web call (simplified HTTP-based implementation)
     */
    async makeGrpcCall(method, request) {
        const startTime = Date.now();
        const callId = `${method}_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
        this.callCount++;
        
        const url = `${this.serverUrl}/LiveLinkService/${method}`;
        
        this.log(`gRPC call started: ${method}`, {
            callId: callId,
            method: method,
            url: url,
            request: request,
            callNumber: this.callCount,
            connectionState: this.connectionState
        });
        
        try {
            if (!this.isReady()) {
                throw new Error(`Client not ready for gRPC calls. State: ${this.connectionState}`);
            }
            
            const controller = new AbortController();
            const timeoutId = setTimeout(() => {
                controller.abort();
                this.log(`gRPC call timeout: ${method}`, { callId, duration: Date.now() - startTime }, 'error');
            }, 30000); // 30 second timeout
            
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/grpc-web+proto',
                    'Accept': 'application/grpc-web+proto',
                    'X-Call-ID': callId
                },
                body: JSON.stringify(request),
                signal: controller.signal
            });
            
            clearTimeout(timeoutId);
            const responseTime = Date.now() - startTime;
            this.lastCallTime = responseTime;
            this.avgResponseTime = ((this.avgResponseTime * (this.callCount - 1)) + responseTime) / this.callCount;
            
            const responseDetails = {
                callId: callId,
                status: response.status,
                statusText: response.statusText,
                headers: Object.fromEntries(response.headers.entries()),
                url: response.url,
                duration: responseTime,
                ok: response.ok,
                redirected: response.redirected,
                type: response.type
            };
            
            this.log(`gRPC response received: ${method}`, responseDetails);
            
            if (!response.ok) {
                const errorText = await response.text().catch(() => 'Unable to read error response');
                const error = new Error(`gRPC call failed: ${response.status} ${response.statusText}`);
                error.status = response.status;
                error.statusText = response.statusText;
                error.responseText = errorText;
                error.callId = callId;
                
                this.log(`gRPC call failed: ${method}`, {
                    callId: callId,
                    error: error.message,
                    status: response.status,
                    statusText: response.statusText,
                    responseText: errorText,
                    duration: responseTime
                }, 'error');
                
                this.errorCount++;
                throw error;
            }
            
            let result;
            try {
                const responseText = await response.text();
                result = JSON.parse(responseText);
                
                // Commented out to reduce log spam - only log in console
                // this.log(`gRPC call successful: ${method}`, {
                //     callId: callId,
                //     duration: responseTime,
                //     responseSize: responseText.length,
                //     resultKeys: Object.keys(result || {})
                // }, 'success');
                // Console logging removed for performance (high-frequency camera sync operations)
                // Debug logging disabled for performance
                
                // Log specific Octane data (without large data blocks)
                if (result && result.success && result.data) {
                    this.logOctaneResponse(method, result.data);
                }
                
            } catch (parseError) {
                this.log(`gRPC response parse error: ${method}`, {
                    callId: callId,
                    parseError: parseError.message,
                    duration: responseTime
                }, 'error');
                
                this.errorCount++;
                throw new Error(`Failed to parse gRPC response: ${parseError.message}`);
            }
            
            return result;
            
        } catch (error) {
            const responseTime = Date.now() - startTime;
            this.lastCallTime = responseTime;
            
            if (error.name === 'AbortError') {
                const timeoutError = new Error(`gRPC call timeout: ${method} (${responseTime}ms)`);
                timeoutError.callId = callId;
                timeoutError.timeout = true;
                throw timeoutError;
            }
            
            // Enhance error with call context
            error.callId = callId;
            error.method = method;
            error.url = url;
            error.duration = responseTime;
            
            this.log(`gRPC call exception: ${method}`, {
                callId: callId,
                error: error.message,
                name: error.name,
                stack: error.stack,
                duration: responseTime,
                method: method,
                url: url
            }, 'error');
            
            this.errorCount++;
            throw error;
        }
    }

    /**
     * Set camera state in Octane
     */
    async setCamera(cameraState) {
        const request = {
            position: cameraState.position || { x: 0, y: 0, z: 5 },
            target: cameraState.target || { x: 0, y: 0, z: 0 },
            up: cameraState.up || { x: 0, y: 1, z: 0 },
            fov: cameraState.fov || 45
        };
        
        // Track sync calls for rate calculation
        this.syncCallCount++;
        this.updateSyncRate();
        
        const result = await this.makeGrpcCall('SetCamera', request);
        return result && result.success ? result.data : null;
    }

    /**
     * Get current camera state from Octane
     */
    async getCamera() {
        const request = {};
        const result = await this.makeGrpcCall('GetCamera', request);
        return result && result.success ? result.data : null;
    }

    /**
     * Get list of available meshes from Octane
     */
    async getMeshes() {
        const request = {};
        const result = await this.makeGrpcCall('GetMeshes', request);
        return result && result.success ? result.data : null;
    }

    /**
     * Get mesh data for a specific mesh
     */
    async getMeshData(meshId) {
        const request = { objecthandle: meshId };
        const result = await this.makeGrpcCall('GetMesh', request);
        return result && result.success ? result.data : null;
    }

    /**
     * Get mesh data by object handle (alias for getMeshData)
     */
    async getMesh(meshId) {
        return this.getMeshData(meshId);
    }

    /**
     * Update sync rate calculation
     */
    updateSyncRate() {
        const now = Date.now();
        const timeDiff = (now - this.lastSyncTime) / 1000; // Convert to seconds
        
        // Calculate sync rate over the last 5 seconds
        if (timeDiff >= 5) {
            this.syncRate = this.syncCallCount / timeDiff;
            this.syncCallCount = 0;
            this.lastSyncTime = now;
        }
    }

    /**
     * Log Octane response data (without large data blocks)
     */
    logOctaneResponse(method, data) {
        switch (method) {
            case 'GetCamera':
                if (data.position && data.target) {
                    const cameraInfo = {
                        position: `(${data.position.x?.toFixed(2)}, ${data.position.y?.toFixed(2)}, ${data.position.z?.toFixed(2)})`,
                        target: `(${data.target.x?.toFixed(2)}, ${data.target.y?.toFixed(2)}, ${data.target.z?.toFixed(2)})`,
                        up: data.up ? `(${data.up.x?.toFixed(2)}, ${data.up.y?.toFixed(2)}, ${data.up.z?.toFixed(2)})` : 'N/A',
                        fov: data.fov?.toFixed(2) || 'N/A'
                    };
                    // Console logging removed for performance optimization
                    // Camera data logging disabled for performance
                    
                    // Also log to Activity Log
                    this.log(`🎥 Camera Data Retrieved:`, cameraInfo, 'success');
                    this.log(`Position: ${cameraInfo.position}`, {}, 'info');
                    this.log(`Target: ${cameraInfo.target}`, {}, 'info');
                    this.log(`Up: ${cameraInfo.up}`, {}, 'info');
                    this.log(`FOV: ${cameraInfo.fov}°`, {}, 'info');
                }
                break;
                
            case 'GetMeshes':
                if (Array.isArray(data)) {
                    // Log mesh count to activity log instead of console
                    this.log(`🔺 Octane Meshes Data: ${data.length} meshes found`, {}, 'success');
                    
                    // Log to Activity Log
                    this.log(`🔺 Meshes Retrieved: ${data.length} meshes found`, {}, 'success');
                    
                    if (data.length === 0) {
                        this.log(`No meshes found in scene`, {}, 'warning');
                    } else {
                        data.slice(0, 10).forEach((mesh, index) => { // Show first 10 meshes
                            // For mesh list, we only have basic info (name, id) - no geometry data yet
                            const meshInfo = `${index + 1}. ${mesh.name || mesh.id || 'Unnamed'} (ID: ${mesh.id || 'unknown'})`;
                            // Mesh details logged to activity log instead of console
                            this.log(`${meshInfo}`, {}, 'info');
                        });
                        
                        if (data.length > 10) {
                            this.log(`... and ${data.length - 10} more meshes`, {}, 'info');
                        }
                    }
                }
                break;
                
            case 'GetMesh':
                if (data.name || data.positions) {
                    // Calculate actual vertex and face counts from mesh data structure
                    const vertexCount = data.positions ? data.positions.length : 0;
                    const faceCount = data.vertsPerPoly ? data.vertsPerPoly.length : 0;
                    
                    const meshInfo = {
                        name: data.name || 'Unnamed Mesh',
                        vertices: vertexCount,
                        faces: faceCount,
                        hasNormals: data.normals && data.normals.length > 0,
                        hasIndices: data.polyVertIndices && data.polyVertIndices.length > 0
                    };
                    // Mesh data logged to activity log instead of console
                    this.log(`🔺 Octane Mesh Data:`, meshInfo, 'success');
                    
                    // Log to Activity Log
                    this.log(`🔺 Mesh Data Retrieved: ${meshInfo.name}`, {}, 'success');
                    this.log(`Vertices: ${meshInfo.vertices}`, {}, 'info');
                    this.log(`Faces: ${meshInfo.faces}`, {}, 'info');
                    if (meshInfo.hasNormals) this.log(`✓ Has vertex normals`, {}, 'info');
                    if (meshInfo.hasIndices) this.log(`✓ Has polygon indices`, {}, 'info');
                } else {
                    this.log(`No mesh data received`, {}, 'warning');
                }
                break;
                
            case 'SetCamera':
                // Console logging removed for performance (high-frequency camera sync operations)
                // SetCamera success logging disabled for performance
                this.log(`🎥 Camera position updated successfully`, {}, 'success');
                break;
                
            default:
                const responseInfo = typeof data === 'object' ? Object.keys(data) : data;
                // Generic response logging moved to activity log
                this.log(`📦 Octane ${method} Response:`, responseInfo, 'info');
                this.log(`📦 ${method} Response: ${JSON.stringify(responseInfo)}`, {}, 'info');
        }
    }

    /**
     * Get comprehensive debugging information
     */
    getDebugInfo() {
        return {
            client: {
                serverUrl: this.serverUrl,
                connected: this.connected,
                connectionState: this.connectionState,
                connectionAttempts: this.connectionAttempts,
                lastConnectionAttempt: this.lastConnectionAttempt,
                debugMode: this.debugMode
            },
            performance: {
                callCount: this.callCount,
                lastCallTime: this.lastCallTime,
                avgResponseTime: this.avgResponseTime
            },
            history: {
                connectionHistory: this.connectionHistory.slice(-5), // Last 5 connections
                errorHistory: this.errorHistory.slice(-10) // Last 10 errors
            },
            lastError: this.lastError ? {
                message: this.lastError.message,
                name: this.lastError.name,
                stack: this.lastError.stack
            } : null,
            systemInfo: this.getSystemInfo()
        };
    }

    /**
     * Export debug information as downloadable JSON
     */
    exportDebugInfo() {
        const debugInfo = this.getDebugInfo();
        const blob = new Blob([JSON.stringify(debugInfo, null, 2)], { type: 'application/json' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = `livelink-debug-${new Date().toISOString().replace(/[:.]/g, '-')}.json`;
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
        
        this.log('Debug information exported', { filename: a.download });
    }

    /**
     * Clear debug history
     */
    clearDebugHistory() {
        this.connectionHistory = [];
        this.errorHistory = [];
        this.log('Debug history cleared');
    }
}

/**
 * LiveLink Manager for handling client instances
 */
class LiveLinkManager {
    constructor() {
        this.client = null;
        this.defaultServerUrl = 'http://127.0.0.1:51024';
    }

    /**
     * Get or create the LiveLink client
     */
    getClient(serverUrl = null) {
        const targetUrl = serverUrl || this.defaultServerUrl;
        
        // Create new client if none exists or if server URL changed
        if (!this.client || this.client.serverUrl !== targetUrl) {
            if (this.client) {
                // Disconnect old client if it exists
                this.client.disconnect();
            }
            this.client = new LiveLinkClient(targetUrl);
        }
        return this.client;
    }

    /**
     * Connect to Octane LiveLink service
     */
    async connect(serverUrl = null) {
        const client = this.getClient(serverUrl);
        return client.connect();
    }

    /**
     * Disconnect from Octane LiveLink service
     */
    async disconnect() {
        if (this.client) {
            await this.client.disconnect();
            this.client = null;
        }
    }

    /**
     * Get current client instance
     */
    getCurrentClient() {
        return this.client;
    }
}

// Create global instance
const liveLinkManager = new LiveLinkManager();

// Export for use in HTML pages
if (typeof window !== 'undefined') {
    window.LiveLinkClient = LiveLinkClient;
    window.LiveLinkManager = LiveLinkManager;
    window.liveLinkManager = liveLinkManager;
}

// Export for Node.js/module systems
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        LiveLinkClient,
        LiveLinkManager,
        liveLinkManager
    };
}