/**
 * gRPC Testing Utilities
 * Shared testing and debugging utilities for LiveLink gRPC applications
 * Provides comprehensive testing, debugging, and system information capabilities
 */

/**
 * Enhanced Connection State Manager with Testing Features
 * Extends the base ConnectionStateManager with additional testing capabilities
 */
class EnhancedConnectionStateManager {
    constructor(statusElementId, logger, buttonIds = []) {
        this.baseManager = new ConnectionStateManager(statusElementId, logger);
        this.logger = logger;
        this.buttonIds = buttonIds;
        this.testingButtons = [
            'exportDebugBtn', 'showSystemInfoBtn', 'showDebugInfoBtn', 
            'refreshStatsBtn', 'getMeshBtn'
        ];
    }

    setState(state) {
        this.baseManager.setState(state);
        this.updateTestingButtons(state);
    }

    onStateChange(callback) {
        this.baseManager.onStateChange(callback);
    }

    updateTestingButtons(state) {
        const connected = state === 'connected';
        
        // Update testing-specific buttons
        this.testingButtons.forEach(buttonId => {
            const button = document.getElementById(buttonId);
            if (button) {
                button.disabled = !connected;
            }
        });

        // Update any additional buttons passed in constructor
        this.buttonIds.forEach(buttonId => {
            const button = document.getElementById(buttonId);
            if (button) {
                button.disabled = !connected;
            }
        });
    }
}

/**
 * Statistics Display Manager
 * Manages performance statistics display and updates
 */
class StatsDisplayManager {
    constructor() {
        this.elements = {
            callCount: document.getElementById('grpcCallsValue'),
            lastTime: document.getElementById('avgResponseValue'),
            avgTime: document.getElementById('avgResponseValue'),
            errorCount: document.getElementById('errorCountValue'),
            syncRate: document.getElementById('syncRateValue')
        };
    }

    updateStats(client) {
        if (!client) return;

        try {
            const debugInfo = client.getDebugInfo();
            const stats = client.getStats();

            if (this.elements.callCount) {
                this.elements.callCount.textContent = stats.callCount || 0;
            }
            
            if (this.elements.lastTime) {
                this.elements.lastTime.textContent = Math.round(stats.lastCallTime || 0) + 'ms';
            }
            
            if (this.elements.avgTime) {
                this.elements.avgTime.textContent = Math.round(stats.avgResponseTime || 0) + 'ms';
            }
            
            if (this.elements.errorCount) {
                this.elements.errorCount.textContent = debugInfo.history?.errorHistory?.length || 0;
            }

            if (this.elements.syncRate) {
                // Calculate sync rate if available
                const syncRate = stats.syncRate || 0;
                this.elements.syncRate.textContent = syncRate + '/s';
            }
        } catch (error) {
            console.error('Error updating stats:', error);
        }
    }
}

/**
 * gRPC Test Operations
 * Comprehensive testing operations for LiveLink gRPC functionality
 */
class GrpcTestOperations {
    constructor(logger, statsManager) {
        this.logger = logger;
        this.statsManager = statsManager;
    }

    async testGetCamera(client) {
        if (!client) {
            this.logger.log('No client available for camera test', 'error');
            return null;
        }

        try {
            this.logger.log('🎥 Getting camera from Octane...', 'info');
            const camera = await client.getCamera();
            
            if (camera) {
                this.logger.log('Camera retrieved successfully', 'success');
                // Detailed logging is now handled in livelink.js
            } else {
                this.logger.log('No camera data received', 'warning');
            }
            
            this.statsManager.updateStats(client);
            return camera;
        } catch (error) {
            this.logger.log(`Camera retrieval failed: ${error.message}`, 'error');
            this.statsManager.updateStats(client);
            throw error;
        }
    }

    async testSetCamera(client, cameraData) {
        if (!client) {
            this.logger.log('No client available for camera set', 'error');
            return false;
        }

        try {
            this.logger.log('📤 Setting camera to Octane...', 'info');
            const result = await client.setCamera(cameraData);
            
            if (result) {
                this.logger.log('Camera set successfully', 'success');
            } else {
                this.logger.log('Camera set operation completed', 'info');
            }
            
            this.statsManager.updateStats(client);
            return result;
        } catch (error) {
            this.logger.log(`Camera set failed: ${error.message}`, 'error');
            this.statsManager.updateStats(client);
            throw error;
        }
    }

    async testGetMeshes(client) {
        if (!client) {
            this.logger.log('No client available for mesh list', 'error');
            return null;
        }

        try {
            this.logger.log('🔺 Getting mesh list from Octane...', 'info');
            const meshes = await client.getMeshes();
            
            if (meshes && Array.isArray(meshes)) {
                this.logger.log(`Retrieved ${meshes.length} meshes`, 'success');
                // Detailed logging is now handled in livelink.js
            } else {
                this.logger.log('No mesh data received', 'warning');
            }
            
            this.statsManager.updateStats(client);
            return meshes;
        } catch (error) {
            this.logger.log(`Mesh list retrieval failed: ${error.message}`, 'error');
            this.statsManager.updateStats(client);
            throw error;
        }
    }

    async testGetMesh(client, meshId = null) {
        if (!client) {
            this.logger.log('No client available for mesh retrieval', 'error');
            return null;
        }

        try {
            // If no meshId provided, try to get the first available mesh
            if (!meshId) {
                const meshes = await this.testGetMeshes(client);
                if (!meshes || meshes.length === 0) {
                    this.logger.log('No meshes available to retrieve', 'warning');
                    return null;
                }
                meshId = meshes[0].id || meshes[0].name;
            }

            this.logger.log(`🔺 Getting mesh data for: ${meshId}...`, 'info');
            const mesh = await client.getMesh(meshId);
            
            if (mesh) {
                this.logger.log(`Mesh retrieved: ${mesh.name || meshId}`, 'success');
                this.logger.log(`Vertices: ${mesh.vertices || 0}, Faces: ${mesh.faces || 0}`, 'info');
            } else {
                this.logger.log('No mesh data received', 'warning');
            }
            
            this.statsManager.updateStats(client);
            return mesh;
        } catch (error) {
            this.logger.log(`Mesh retrieval failed: ${error.message}`, 'error');
            this.statsManager.updateStats(client);
            throw error;
        }
    }
}

/**
 * Debug Utilities
 * Comprehensive debugging and system information utilities
 */
class DebugUtils {
    constructor(logger) {
        this.logger = logger;
        this.debugHistory = [];
    }

    exportDebugInfo(client) {
        if (!client) {
            this.logger.log('No client available for debug export', 'error');
            return;
        }
        
        try {
            client.exportDebugInfo();
            this.logger.log('Debug information exported successfully', 'success');
        } catch (error) {
            this.logger.log(`Failed to export debug info: ${error.message}`, 'error');
        }
    }

    showSystemInfo(client) {
        if (!client) {
            this.logger.log('No client available for system info', 'error');
            return;
        }
        
        const systemInfo = client.getSystemInfo();
        this.logger.log('📊 System Information:', 'info');
        
        // Display key system info in a readable format
        if (systemInfo.browser) {
            this.logger.log(`Browser: ${systemInfo.browser.name} ${systemInfo.browser.version}`, 'info');
            this.logger.log(`Platform: ${systemInfo.browser.platform}`, 'info');
        }
        
        if (systemInfo.screen) {
            this.logger.log(`Screen: ${systemInfo.screen.width}x${systemInfo.screen.height} (${systemInfo.screen.colorDepth}-bit)`, 'info');
        }
        
        if (systemInfo.connection) {
            this.logger.log(`Connection: ${systemInfo.connection.effectiveType || 'Unknown'} (${systemInfo.connection.downlink || 'N/A'} Mbps)`, 'info');
        }
        
        if (systemInfo.memory) {
            const memoryMB = Math.round(systemInfo.memory.usedJSHeapSize / 1024 / 1024);
            const limitMB = Math.round(systemInfo.memory.jsHeapSizeLimit / 1024 / 1024);
            this.logger.log(`Memory: ${memoryMB}MB used / ${limitMB}MB limit`, 'info');
        }
        
        this.logger.log(`Timestamp: ${systemInfo.timestamp}`, 'info');
    }

    showDebugInfo(client) {
        if (!client) {
            this.logger.log('No client available for debug info', 'error');
            return;
        }
        
        const debugInfo = client.getDebugInfo();
        this.logger.log('🔍 Debug Information:', 'info');
        
        // Display key debug info in a readable format
        if (debugInfo.client) {
            this.logger.log(`Server URL: ${debugInfo.client.serverUrl}`, 'info');
            this.logger.log(`Connected: ${debugInfo.client.connected}`, 'info');
            this.logger.log(`Connection State: ${debugInfo.client.connectionState}`, 'info');
            this.logger.log(`Connection Attempts: ${debugInfo.client.connectionAttempts}`, 'info');
        }
        
        if (debugInfo.performance) {
            this.logger.log(`Total Calls: ${debugInfo.performance.callCount}`, 'info');
            this.logger.log(`Last Call Time: ${debugInfo.performance.lastCallTime}ms`, 'info');
            this.logger.log(`Avg Response Time: ${debugInfo.performance.avgResponseTime?.toFixed(1)}ms`, 'info');
        }
        
        if (debugInfo.history) {
            if (debugInfo.history.errorHistory?.length > 0) {
                this.logger.log(`Recent Errors: ${debugInfo.history.errorHistory.length}`, 'warning');
                debugInfo.history.errorHistory.slice(-3).forEach((error, index) => {
                    this.logger.log(`  ${index + 1}. ${error.message}`, 'warning');
                });
            }
            
            if (debugInfo.history.connectionHistory?.length > 0) {
                this.logger.log(`Recent Connections: ${debugInfo.history.connectionHistory.length}`, 'info');
            }
        }
        
        if (debugInfo.lastError) {
            this.logger.log(`Last Error: ${debugInfo.lastError.message}`, 'error');
        }
    }

    refreshStats(client, statsManager) {
        if (!client) {
            this.logger.log('No client available for stats refresh', 'error');
            return;
        }

        try {
            statsManager.updateStats(client);
            this.logger.log('Performance statistics refreshed', 'success');
        } catch (error) {
            this.logger.log(`Failed to refresh stats: ${error.message}`, 'error');
        }
    }

    clearDebugHistory() {
        this.debugHistory = [];
        this.logger.log('Debug history cleared', 'info');
    }
}

/**
 * Connection Manager
 * Centralized connection management with enhanced error handling
 */
class ConnectionManager {
    constructor(logger, connectionStateManager) {
        this.logger = logger;
        this.connectionStateManager = connectionStateManager;
        this.client = null;
        this.liveLinkManager = null;
    }

    async connect(serverAddress) {
        try {
            this.connectionStateManager.setState('connecting');
            this.logger.log('Getting LiveLink client...', 'info');
            
            // Get the global liveLinkManager
            if (typeof liveLinkManager === 'undefined') {
                throw new Error('LiveLink manager not available');
            }
            
            this.liveLinkManager = liveLinkManager;
            this.client = this.liveLinkManager.getClient(serverAddress);
            
            this.logger.log('Attempting connection to Octane LiveLink...', 'info');
            const result = await this.client.connect();
            
            if (result) {
                this.connectionStateManager.setState('connected');
                this.logger.log('✅ Connected to Octane LiveLink successfully!', 'success');
                return this.client;
            } else {
                throw new Error('Connection failed - no response from server');
            }
        } catch (error) {
            this.connectionStateManager.setState('disconnected');
            this.logger.log(`❌ Connection failed: ${error.message}`, 'error');
            throw error;
        }
    }

    async disconnect() {
        try {
            if (this.client) {
                await this.client.disconnect();
                this.client = null;
            }
            
            this.connectionStateManager.setState('disconnected');
            this.logger.log('Disconnected from Octane LiveLink', 'info');
        } catch (error) {
            this.logger.log(`Disconnect error: ${error.message}`, 'error');
            this.connectionStateManager.setState('disconnected');
        }
    }

    getClient() {
        return this.client;
    }

    isConnected() {
        return this.client && this.client.connected;
    }
}

// Export classes for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        EnhancedConnectionStateManager,
        StatsDisplayManager,
        GrpcTestOperations,
        DebugUtils,
        ConnectionManager
    };
}