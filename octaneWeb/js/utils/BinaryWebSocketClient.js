/**
 * Binary WebSocket Client for Octane Callback Streaming
 * 
 * Optimized replacement for Server-Sent Events with base64 encoding.
 * Provides direct binary data transfer for image buffers, eliminating
 * 33% base64 overhead and reducing CPU usage.
 * 
 * Features:
 * - Binary message protocol with structured headers
 * - Direct buffer processing without base64 encoding/decoding
 * - Automatic reconnection with exponential backoff
 * - Performance monitoring and statistics
 * - Backward compatibility with existing callback handlers
 */

class BinaryWebSocketClient {
    constructor(serverUrl, eventHandler) {
        this.serverUrl = serverUrl;
        this.eventHandler = eventHandler;
        
        // WebSocket connection state
        this.websocket = null;
        this.connected = false;
        this.connecting = false;
        this.clientId = null;
        
        // Reconnection settings
        this.reconnect = {
            enabled: true,
            attempts: 0,
            maxAttempts: 10,
            baseDelay: 1000,      // 1 second base delay
            maxDelay: 30000,      // 30 second max delay
            backoffFactor: 1.5    // Exponential backoff multiplier
        };
        
        // Performance statistics
        this.stats = {
            messagesReceived: 0,
            bytesReceived: 0,
            imagesReceived: 0,
            connectionTime: 0,
            lastMessageTime: 0,
            bandwidthSaved: 0,    // Estimated bytes saved vs base64
            decodingTimeSaved: 0  // Estimated time saved vs base64 decoding
        };
        
        // Message type constants (must match server)
        this.MessageTypes = {
            CONNECTED: 1,
            NEW_IMAGE: 2,
            RENDER_FAILURE: 3,
            NEW_STATISTICS: 4,
            PROJECT_CHANGED: 5,
            PING: 6,
            ERROR: 7
        };
        
        console.log('BinaryWebSocketClient initialized');
    }
    
    /**
     * Connect to binary WebSocket stream
     */
    async connect() {
        if (this.connecting || this.connected) {
            return;
        }
        
        this.connecting = true;
        
        try {
            const wsUrl = this.serverUrl.replace('http://', 'ws://').replace('https://', 'wss://') + '/render/websocket';
            console.log(`🔌 Connecting to binary WebSocket: ${wsUrl}`);
            
            this.websocket = new WebSocket(wsUrl);
            this.websocket.binaryType = 'arraybuffer'; // Important: receive as ArrayBuffer
            
            // Connection opened
            this.websocket.onopen = (event) => {
                console.log('✅ Binary WebSocket connected');
                this.connected = true;
                this.connecting = false;
                this.reconnect.attempts = 0;
                this.stats.connectionTime = Date.now();
                
                if (this.eventHandler && this.eventHandler.onConnectionStateChange) {
                    this.eventHandler.onConnectionStateChange('connected');
                }
            };
            
            // Message received
            this.websocket.onmessage = (event) => {
                this.handleBinaryMessage(event.data);
            };
            
            // Connection closed
            this.websocket.onclose = (event) => {
                console.log(`🔌 Binary WebSocket closed: ${event.code} - ${event.reason}`);
                this.connected = false;
                this.connecting = false;
                this.clientId = null;
                
                if (this.eventHandler && this.eventHandler.onConnectionStateChange) {
                    this.eventHandler.onConnectionStateChange('disconnected');
                }
                
                // Attempt reconnection if enabled
                if (this.reconnect.enabled && this.reconnect.attempts < this.reconnect.maxAttempts) {
                    this.scheduleReconnect();
                }
            };
            
            // Connection error
            this.websocket.onerror = (error) => {
                console.error('❌ Binary WebSocket error:', error);
                this.connected = false;
                this.connecting = false;
                
                if (this.eventHandler && this.eventHandler.onConnectionStateChange) {
                    this.eventHandler.onConnectionStateChange('error');
                }
            };
            
        } catch (error) {
            console.error('❌ Failed to create WebSocket connection:', error);
            this.connecting = false;
            
            if (this.reconnect.enabled) {
                this.scheduleReconnect();
            }
        }
    }
    
    /**
     * Disconnect from WebSocket
     */
    disconnect() {
        this.reconnect.enabled = false;
        
        if (this.websocket) {
            this.websocket.close();
            this.websocket = null;
        }
        
        this.connected = false;
        this.connecting = false;
        this.clientId = null;
        
        console.log('🔌 Binary WebSocket disconnected');
    }
    
    /**
     * Schedule reconnection with exponential backoff
     */
    scheduleReconnect() {
        this.reconnect.attempts++;
        
        const delay = Math.min(
            this.reconnect.baseDelay * Math.pow(this.reconnect.backoffFactor, this.reconnect.attempts - 1),
            this.reconnect.maxDelay
        );
        
        console.log(`🔄 Scheduling reconnection attempt ${this.reconnect.attempts}/${this.reconnect.maxAttempts} in ${delay}ms`);
        
        setTimeout(() => {
            if (this.reconnect.enabled && !this.connected && !this.connecting) {
                this.connect();
            }
        }, delay);
    }
    
    /**
     * Handle incoming binary message
     */
    handleBinaryMessage(arrayBuffer) {
        try {
            this.stats.messagesReceived++;
            this.stats.bytesReceived += arrayBuffer.byteLength;
            this.stats.lastMessageTime = Date.now();
            
            // Parse binary message header
            const message = this.unpackBinaryMessage(arrayBuffer);
            
            // Handle different message types
            switch (message.type) {
                case this.MessageTypes.CONNECTED:
                    this.handleConnectedMessage(message);
                    break;
                    
                case this.MessageTypes.NEW_IMAGE:
                    this.handleNewImageMessage(message);
                    break;
                    
                case this.MessageTypes.RENDER_FAILURE:
                    this.handleRenderFailureMessage(message);
                    break;
                    
                case this.MessageTypes.NEW_STATISTICS:
                    this.handleStatisticsMessage(message);
                    break;
                    
                case this.MessageTypes.PROJECT_CHANGED:
                    this.handleProjectChangedMessage(message);
                    break;
                    
                case this.MessageTypes.PING:
                    this.handlePingMessage(message);
                    break;
                    
                case this.MessageTypes.ERROR:
                    this.handleErrorMessage(message);
                    break;
                    
                default:
                    console.warn(`Unknown binary message type: ${message.type}`);
            }
            
        } catch (error) {
            console.error('❌ Error handling binary message:', error);
        }
    }
    
    /**
     * Unpack binary message from structured format
     * Format: [type:4][timestamp:8][payload_size:4][payload:N]
     */
    unpackBinaryMessage(arrayBuffer) {
        const view = new DataView(arrayBuffer);
        
        if (arrayBuffer.byteLength < 16) {
            throw new Error('Invalid binary message: too short');
        }
        
        const type = view.getUint32(0, false);        // Big-endian
        const timestamp = view.getFloat64(4, false);   // Big-endian
        const payloadSize = view.getUint32(12, false); // Big-endian
        
        if (arrayBuffer.byteLength !== 16 + payloadSize) {
            throw new Error('Invalid binary message: payload size mismatch');
        }
        
        const payload = arrayBuffer.slice(16);
        
        return {
            type: type,
            timestamp: timestamp,
            payloadSize: payloadSize,
            payload: payload
        };
    }
    
    /**
     * Handle connection confirmation message
     */
    handleConnectedMessage(message) {
        try {
            const textDecoder = new TextDecoder();
            const jsonData = textDecoder.decode(message.payload);
            const data = JSON.parse(jsonData);
            
            this.clientId = data.client_id;
            console.log(`🔌 Binary WebSocket client ID: ${this.clientId}`);
            
            if (this.eventHandler && this.eventHandler.handleCallbackEvent) {
                this.eventHandler.handleCallbackEvent({
                    type: 'connected',
                    client_id: this.clientId,
                    protocol: data.protocol || 'binary_websocket_v1'
                });
            }
            
        } catch (error) {
            console.error('❌ Error handling connected message:', error);
        }
    }
    
    /**
     * Handle new image message with binary buffer
     */
    handleNewImageMessage(message) {
        try {
            this.stats.imagesReceived++;
            
            // Parse binary payload: [metadata_size:4][metadata:N][buffer:M]
            const payloadView = new DataView(message.payload);
            const metadataSize = payloadView.getUint32(0, false); // Big-endian
            
            if (message.payload.byteLength < 4 + metadataSize) {
                throw new Error('Invalid image message: insufficient data');
            }
            
            // Extract metadata JSON
            const metadataBuffer = message.payload.slice(4, 4 + metadataSize);
            const textDecoder = new TextDecoder();
            const metadataJson = textDecoder.decode(metadataBuffer);
            const metadata = JSON.parse(metadataJson);
            
            // Extract raw image buffer
            const imageBuffer = message.payload.slice(4 + metadataSize);
            
            // Calculate bandwidth savings vs base64 (33% overhead)
            const base64Size = imageBuffer.byteLength * 1.33;
            this.stats.bandwidthSaved += (base64Size - imageBuffer.byteLength);
            
            // Estimate decoding time saved (rough approximation)
            this.stats.decodingTimeSaved += imageBuffer.byteLength * 0.000001; // ~1μs per byte
            
            // Create compatible callback event data
            const callbackData = {
                type: 'newImage',
                callback_id: metadata.callback_id,
                user_data: metadata.user_data,
                timestamp: metadata.timestamp,
                render_images: {
                    data: [{
                        ...metadata.image_info,
                        buffer: {
                            data: imageBuffer,        // Raw binary buffer (not base64!)
                            size: imageBuffer.byteLength,
                            encoding: 'binary'        // Mark as binary for processing
                        }
                    }]
                }
            };
            
            // Forward to existing callback handler
            if (this.eventHandler && this.eventHandler.handleCallbackEvent) {
                this.eventHandler.handleCallbackEvent(callbackData);
            }
            
        } catch (error) {
            console.error('❌ Error handling new image message:', error);
        }
    }
    
    /**
     * Handle render failure message
     */
    handleRenderFailureMessage(message) {
        try {
            const textDecoder = new TextDecoder();
            const jsonData = textDecoder.decode(message.payload);
            const data = JSON.parse(jsonData);
            
            if (this.eventHandler && this.eventHandler.handleCallbackEvent) {
                this.eventHandler.handleCallbackEvent({
                    type: 'renderFailure',
                    ...data
                });
            }
            
        } catch (error) {
            console.error('❌ Error handling render failure message:', error);
        }
    }
    
    /**
     * Handle statistics message
     */
    handleStatisticsMessage(message) {
        try {
            const textDecoder = new TextDecoder();
            const jsonData = textDecoder.decode(message.payload);
            const data = JSON.parse(jsonData);
            
            if (this.eventHandler && this.eventHandler.handleCallbackEvent) {
                this.eventHandler.handleCallbackEvent({
                    type: 'newStatistics',
                    ...data
                });
            }
            
        } catch (error) {
            console.error('❌ Error handling statistics message:', error);
        }
    }
    
    /**
     * Handle project changed message
     */
    handleProjectChangedMessage(message) {
        if (this.eventHandler && this.eventHandler.handleCallbackEvent) {
            this.eventHandler.handleCallbackEvent({
                type: 'projectManagerChanged',
                timestamp: message.timestamp
            });
        }
    }
    
    /**
     * Handle ping message
     */
    handlePingMessage(message) {
        // Send pong response if needed
        if (this.websocket && this.websocket.readyState === WebSocket.OPEN) {
            const pongBuffer = new ArrayBuffer(16 + 4); // Header + "pong"
            const view = new DataView(pongBuffer);
            
            view.setUint32(0, this.MessageTypes.PING, false);  // Type
            view.setFloat64(4, Date.now() / 1000, false);      // Timestamp
            view.setUint32(12, 4, false);                      // Payload size
            
            const pongText = new TextEncoder().encode('pong');
            new Uint8Array(pongBuffer, 16).set(pongText);
            
            this.websocket.send(pongBuffer);
        }
    }
    
    /**
     * Handle error message
     */
    handleErrorMessage(message) {
        try {
            const textDecoder = new TextDecoder();
            const errorData = textDecoder.decode(message.payload);
            console.error('❌ Server error:', errorData);
            
        } catch (error) {
            console.error('❌ Error handling error message:', error);
        }
    }
    
    /**
     * Get performance statistics
     */
    getStats() {
        return {
            ...this.stats,
            connected: this.connected,
            clientId: this.clientId,
            reconnectAttempts: this.reconnect.attempts,
            bandwidthSavedMB: this.stats.bandwidthSaved / (1024 * 1024),
            decodingTimeSavedMs: this.stats.decodingTimeSaved * 1000
        };
    }
    
    /**
     * Enable/disable automatic reconnection
     */
    setReconnectEnabled(enabled) {
        this.reconnect.enabled = enabled;
    }
    
    /**
     * Check if connected
     */
    isConnected() {
        return this.connected && this.websocket && this.websocket.readyState === WebSocket.OPEN;
    }
}

// Export for use in other modules
window.BinaryWebSocketClient = BinaryWebSocketClient;