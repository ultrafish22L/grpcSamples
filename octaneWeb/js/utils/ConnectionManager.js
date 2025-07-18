/**
 * Enhanced Connection Manager with automatic retry and fallback
 * Handles connection failures gracefully with exponential backoff
 */

class ConnectionManager {
    constructor() {
        this.isConnected = false;
        this.retryCount = 0;
        this.maxRetries = 5;
        this.retryDelay = 1000; // Start with 1 second
        this.connectionTimeout = 10000; // 10 seconds
        this.heartbeatInterval = null;
        this.reconnectTimer = null;
        
        // Connection state callbacks
        this.onConnected = null;
        this.onDisconnected = null;
        this.onError = null;
        this.onRetrying = null;
    }
    
    async connect(serverAddress) {
        try {
            this.serverAddress = serverAddress;
            
            // Test connection with timeout
            const controller = new AbortController();
            const timeoutId = setTimeout(() => controller.abort(), this.connectionTimeout);
            
            const response = await fetch(`${serverAddress}/test`, {
                method: 'GET',
                signal: controller.signal,
                headers: {
                    'Content-Type': 'application/json',
                }
            });
            
            clearTimeout(timeoutId);
            
            if (response.ok) {
                this.isConnected = true;
                this.retryCount = 0;
                this.startHeartbeat();
                
                if (this.onConnected) {
                    this.onConnected(serverAddress);
                }
                
                return true;
            } else {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            
        } catch (error) {
            this.isConnected = false;
            
            if (this.onError) {
                this.onError(error);
            }
            
            // Attempt retry with exponential backoff
            if (this.retryCount < this.maxRetries) {
                this.scheduleRetry();
            }
            
            return false;
        }
    }
    
    scheduleRetry() {
        this.retryCount++;
        const delay = this.retryDelay * Math.pow(2, this.retryCount - 1); // Exponential backoff
        
        if (this.onRetrying) {
            this.onRetrying(this.retryCount, delay);
        }
        
        this.reconnectTimer = setTimeout(() => {
            this.connect(this.serverAddress);
        }, delay);
    }
    
    startHeartbeat() {
        this.heartbeatInterval = setInterval(async () => {
            try {
                const response = await fetch(`${this.serverAddress}/health`, {
                    method: 'GET',
                    timeout: 5000
                });
                
                if (!response.ok) {
                    throw new Error('Heartbeat failed');
                }
                
            } catch (error) {
                this.handleConnectionLoss();
            }
        }, 30000); // Check every 30 seconds
    }
    
    handleConnectionLoss() {
        this.isConnected = false;
        
        if (this.heartbeatInterval) {
            clearInterval(this.heartbeatInterval);
            this.heartbeatInterval = null;
        }
        
        if (this.onDisconnected) {
            this.onDisconnected();
        }
        
        // Attempt reconnection
        this.scheduleRetry();
    }
    
    disconnect() {
        this.isConnected = false;
        this.retryCount = 0;
        
        if (this.heartbeatInterval) {
            clearInterval(this.heartbeatInterval);
            this.heartbeatInterval = null;
        }
        
        if (this.reconnectTimer) {
            clearTimeout(this.reconnectTimer);
            this.reconnectTimer = null;
        }
        
        if (this.onDisconnected) {
            this.onDisconnected();
        }
    }
    
    getConnectionStatus() {
        return {
            connected: this.isConnected,
            retryCount: this.retryCount,
            maxRetries: this.maxRetries,
            serverAddress: this.serverAddress
        };
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = ConnectionManager;
} else {
    window.ConnectionManager = ConnectionManager;
}