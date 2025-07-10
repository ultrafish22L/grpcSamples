/**
 * Shared Utilities for LiveLink gRPC Applications
 * Consolidated utilities for logging, UI management, testing, and debugging
 * Used by both grpc_test.html and web3d_octane_sync.html
 */

/**
 * Activity Logger with Enhanced Formatting
 * Provides clean timestamp handling and detailed logging capabilities
 */
class ActivityLogger {
    constructor(containerId) {
        this.container = document.getElementById(containerId);
        this.maxEntries = 100; // Limit log entries to prevent memory issues
    }

    /**
     * Log a message with clean timestamp formatting
     * Prevents duplicate timestamps and provides consistent formatting
     */
    log(message, type = 'info', details = null) {
        if (!this.container) {
            console.warn('Activity log container not found');
            return;
        }

        // Check if message already has a timestamp to prevent duplicates
        const hasTimestamp = /^\[\d{1,2}:\d{2}:\d{2}\s(?:AM|PM)\]/.test(message);
        
        // Create log entry element
        const entry = document.createElement('div');
        entry.className = `log-entry log-${type}`;
        
        // Format message with clean timestamp
        const timestamp = new Date().toLocaleTimeString();
        const displayMessage = hasTimestamp ? message : `[${timestamp}] ${message}`;
        
        // Add emoji indicators for different message types
        const typeEmojis = {
            'info': 'ℹ️',
            'success': '✅',
            'warning': '⚠️',
            'error': '❌',
            'debug': '🔍'
        };
        
        const emoji = typeEmojis[type] || 'ℹ️';
        let entryContent = `<span class="log-emoji">${emoji}</span> ${displayMessage}`;
        
        // If details are provided, format them nicely
        if (details && Object.keys(details).length > 0) {
            const detailsStr = this.formatDetails(details);
            if (detailsStr) {
                entryContent += `<div class="log-details">${detailsStr}</div>`;
            }
        }
        
        entry.innerHTML = entryContent;
        
        // Add to container (newest entries at the bottom)
        this.container.appendChild(entry);
        
        // Limit number of entries
        while (this.container.children.length > this.maxEntries) {
            this.container.removeChild(this.container.firstChild);
        }
        
        // Auto-scroll to show latest entry
        this.container.scrollTop = this.container.scrollHeight;
        
        // Add fade-in animation
        entry.classList.add('fade-in');
    }

    /**
     * Format details object for display
     */
    formatDetails(details) {
        if (!details) return '';
        
        if (typeof details === 'string') {
            return details;
        }
        
        if (typeof details === 'object') {
            try {
                // Handle different types of objects
                if (Array.isArray(details)) {
                    return `Array(${details.length}): ${JSON.stringify(details.slice(0, 3))}${details.length > 3 ? '...' : ''}`;
                }
                
                // For objects, show key properties in a readable format
                const keys = Object.keys(details);
                if (keys.length === 0) return '';
                
                if (keys.length <= 3) {
                    return Object.entries(details)
                        .map(([key, value]) => `${key}: ${this.formatValue(value)}`)
                        .join(', ');
                } else {
                    return `Object(${keys.length} keys): ${keys.slice(0, 3).join(', ')}...`;
                }
            } catch (e) {
                return String(details);
            }
        }
        
        return String(details);
    }

    /**
     * Format individual values for display
     */
    formatValue(value) {
        if (value === null) return 'null';
        if (value === undefined) return 'undefined';
        if (typeof value === 'string') return `"${value}"`;
        if (typeof value === 'number') return value.toString();
        if (typeof value === 'boolean') return value.toString();
        if (typeof value === 'object') return '[Object]';
        return String(value);
    }

    /**
     * Clear all log entries
     */
    clear() {
        if (this.container) {
            this.container.innerHTML = '';
        }
    }

    /**
     * Get log history as text
     */
    getHistory() {
        if (!this.container) return '';
        return Array.from(this.container.children)
            .map(entry => entry.textContent)
            .join('\n');
    }
}

/**
 * UI Utilities
 * Common UI manipulation functions
 */
class UIUtils {
    static setButtonEnabled(buttonId, enabled) {
        const button = document.getElementById(buttonId);
        if (button) {
            button.disabled = !enabled;
        }
    }

    static updateElement(elementId, content) {
        const element = document.getElementById(elementId);
        if (element) {
            element.textContent = content;
        }
    }

    static setElementClass(elementId, className) {
        const element = document.getElementById(elementId);
        if (element) {
            element.className = className;
        }
    }

    static showElement(elementId) {
        const element = document.getElementById(elementId);
        if (element) {
            element.style.display = 'block';
        }
    }

    static hideElement(elementId) {
        const element = document.getElementById(elementId);
        if (element) {
            element.style.display = 'none';
        }
    }

    static toggleElement(elementId) {
        const element = document.getElementById(elementId);
        if (element) {
            element.style.display = element.style.display === 'none' ? 'block' : 'none';
        }
    }
}

/**
 * Performance Tracker
 * Tracks application performance metrics
 */
class PerformanceTracker {
    constructor() {
        this.stats = {
            calls: 0,
            errors: 0,
            totalResponseTime: 0,
            connectionAttempts: 0,
            startTime: Date.now()
        };
        this.callHistory = [];
        this.maxHistory = 50;
    }

    recordCall(responseTime) {
        this.stats.calls++;
        this.stats.totalResponseTime += responseTime;
        
        this.callHistory.push({
            timestamp: Date.now(),
            responseTime: responseTime
        });
        
        if (this.callHistory.length > this.maxHistory) {
            this.callHistory.shift();
        }
    }

    recordError() {
        this.stats.errors++;
    }

    recordConnectionAttempt() {
        this.stats.connectionAttempts++;
    }

    getStats() {
        const averageResponseTime = this.stats.calls > 0 
            ? this.stats.totalResponseTime / this.stats.calls 
            : 0;

        return {
            calls: this.stats.calls,
            errors: this.stats.errors,
            averageResponseTime: Math.round(averageResponseTime),
            connectionAttempts: this.stats.connectionAttempts,
            uptime: Date.now() - this.stats.startTime,
            errorCount: this.stats.errors
        };
    }

    reset() {
        this.stats = {
            calls: 0,
            errors: 0,
            totalResponseTime: 0,
            connectionAttempts: 0,
            startTime: Date.now()
        };
        this.callHistory = [];
    }
}

/**
 * Connection State Manager
 * Manages connection state and UI updates
 */
class ConnectionStateManager {
    constructor(statusElementId, logger) {
        this.statusElement = document.getElementById(statusElementId);
        this.logger = logger;
        this.currentState = 'disconnected';
        this.stateCallbacks = {};
    }

    setState(state, message = null) {
        this.currentState = state;
        
        if (this.statusElement) {
            this.statusElement.textContent = this.getStateText(state);
        }
        
        if (message && this.logger) {
            const logType = this.getLogType(state);
            this.logger.log(message, logType);
        }
        
        // Trigger state-specific callbacks
        if (this.stateCallbacks[state]) {
            this.stateCallbacks[state].forEach(callback => {
                try {
                    callback(state);
                } catch (error) {
                    console.error('State callback error:', error);
                }
            });
        }
    }

    onStateChange(state, callback) {
        if (!this.stateCallbacks[state]) {
            this.stateCallbacks[state] = [];
        }
        this.stateCallbacks[state].push(callback);
    }

    getStateText(state) {
        const stateTexts = {
            'connected': 'Connected',
            'connecting': 'Connecting...',
            'disconnected': 'Disconnected',
            'error': 'Connection Error'
        };
        return stateTexts[state] || 'Unknown';
    }

    getLogType(state) {
        const logTypes = {
            'connected': 'success',
            'connecting': 'info',
            'disconnected': 'warning',
            'error': 'error'
        };
        return logTypes[state] || 'info';
    }

    getCurrentState() {
        return this.currentState;
    }
}

/**
 * Enhanced Connection State Manager with Testing Features
 * Extends the base ConnectionStateManager with additional testing capabilities
 */
class EnhancedConnectionStateManager extends ConnectionStateManager {
    constructor(statusElementId, logger, buttonIds = []) {
        super(statusElementId, logger);
        this.buttonIds = buttonIds;
        this.testingButtons = [
            'exportDebugBtn', 'showSystemInfoBtn', 'showDebugInfoBtn', 
            'refreshStatsBtn', 'getMeshBtn'
        ];
    }

    setState(state, message = null) {
        super.setState(state, message);
        this.updateTestingButtons(state);
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
            callCount: document.getElementById('grpcCallsValue') || document.getElementById('callCount'),
            lastTime: document.getElementById('avgResponseValue') || document.getElementById('lastTime'),
            avgTime: document.getElementById('avgResponseValue') || document.getElementById('avgTime'),
            errorCount: document.getElementById('errorCountValue') || document.getElementById('errorCount'),
            syncRate: document.getElementById('syncRateValue'),
            mode: document.getElementById('mode'),
            connectionAttempts: document.getElementById('connectionAttempts')
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
                this.elements.lastTime.textContent = Math.round(stats.lastCallTime || 0) + (this.elements.lastTime.id === 'lastTime' ? 'ms' : '');
            }
            
            if (this.elements.avgTime) {
                this.elements.avgTime.textContent = Math.round(stats.avgResponseTime || 0) + (this.elements.avgTime.id === 'avgTime' ? 'ms' : '');
            }
            
            if (this.elements.errorCount) {
                this.elements.errorCount.textContent = debugInfo.history?.errorHistory?.length || 0;
            }

            if (this.elements.syncRate) {
                const syncRate = stats.syncRate || 0;
                this.elements.syncRate.textContent = syncRate + '/s';
            }

            if (this.elements.mode) {
                this.elements.mode.textContent = client.connected ? 'Live' : 'Disconnected';
            }

            if (this.elements.connectionAttempts) {
                this.elements.connectionAttempts.textContent = debugInfo.client?.connectionAttempts || 0;
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

/**
 * Error Handler
 * Centralized error handling for gRPC operations
 */
class ErrorHandler {
    static handleGrpcError(error, logger, context = 'Operation') {
        let errorMessage = `${context} failed`;
        let errorType = 'error';
        
        if (error.message) {
            errorMessage += `: ${error.message}`;
        }
        
        // Categorize error types
        if (error.message && error.message.includes('network')) {
            errorType = 'warning';
            errorMessage += ' (Network issue)';
        } else if (error.message && error.message.includes('timeout')) {
            errorType = 'warning';
            errorMessage += ' (Timeout)';
        }
        
        logger.log(errorMessage, errorType);
        console.error(`${context}:`, error);
    }
}

// Export classes for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        ActivityLogger,
        UIUtils,
        PerformanceTracker,
        ConnectionStateManager,
        EnhancedConnectionStateManager,
        StatsDisplayManager,
        GrpcTestOperations,
        DebugUtils,
        ConnectionManager,
        ErrorHandler
    };
}