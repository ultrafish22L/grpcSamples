/**
 * Shared utilities for LiveLink HTML applications
 * Contains common logging, UI, and utility functions
 */

// Activity logging utility with clean timestamp handling
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
        entry.innerHTML = `<span class="log-emoji">${emoji}</span> ${displayMessage}`;
        
        // Add to container (newest first)
        this.container.insertBefore(entry, this.container.firstChild);
        
        // Limit number of entries
        while (this.container.children.length > this.maxEntries) {
            this.container.removeChild(this.container.lastChild);
        }
        
        // Also log to console for debugging
        const consoleMethod = type === 'error' ? 'error' : 
                             type === 'warning' ? 'warn' : 'log';
        console[consoleMethod](`[Activity] ${displayMessage}`, details || '');
    }

    /**
     * Clear all log entries
     */
    clear() {
        if (this.container) {
            this.container.innerHTML = '';
        }
    }
}

// Performance metrics tracker
class PerformanceTracker {
    constructor() {
        this.reset();
    }

    reset() {
        this.callCount = 0;
        this.totalResponseTime = 0;
        this.lastResponseTime = 0;
        this.connectionAttempts = 0;
        this.errorCount = 0;
        this.startTime = Date.now();
    }

    recordCall(responseTime) {
        this.callCount++;
        this.lastResponseTime = responseTime;
        this.totalResponseTime += responseTime;
    }

    recordConnectionAttempt() {
        this.connectionAttempts++;
    }

    recordError() {
        this.errorCount++;
    }

    getAverageResponseTime() {
        return this.callCount > 0 ? Math.round(this.totalResponseTime / this.callCount) : 0;
    }

    getStats() {
        return {
            calls: this.callCount,
            lastResponseTime: this.lastResponseTime,
            averageResponseTime: this.getAverageResponseTime(),
            connectionAttempts: this.connectionAttempts,
            errorCount: this.errorCount,
            uptime: Date.now() - this.startTime
        };
    }
}

// Connection state manager
class ConnectionStateManager {
    constructor(statusElementId, logger) {
        this.statusElement = document.getElementById(statusElementId);
        this.logger = logger;
        this.state = 'disconnected';
        this.callbacks = {};
    }

    setState(newState, message = null) {
        const oldState = this.state;
        this.state = newState;
        
        // Update UI
        if (this.statusElement) {
            this.statusElement.textContent = this.getStateDisplayText(newState);
            this.statusElement.className = `status-${newState}`;
        }
        
        // Log state change
        if (message && this.logger) {
            const logType = newState === 'connected' ? 'success' : 
                           newState === 'error' ? 'error' : 'info';
            this.logger.log(message, logType);
        }
        
        // Trigger callbacks
        if (this.callbacks[newState]) {
            this.callbacks[newState].forEach(callback => {
                try {
                    callback(newState, oldState);
                } catch (error) {
                    console.error('State change callback error:', error);
                }
            });
        }
    }

    getStateDisplayText(state) {
        const stateTexts = {
            'disconnected': 'Disconnected',
            'connecting': 'Connecting...',
            'connected': 'Connected',
            'error': 'Connection Error',
            'reconnecting': 'Reconnecting...'
        };
        return stateTexts[state] || state;
    }

    onStateChange(state, callback) {
        if (!this.callbacks[state]) {
            this.callbacks[state] = [];
        }
        this.callbacks[state].push(callback);
    }

    isConnected() {
        return this.state === 'connected';
    }
}

// UI utilities
class UIUtils {
    /**
     * Enable/disable button with visual feedback
     */
    static setButtonEnabled(buttonId, enabled, text = null) {
        const button = document.getElementById(buttonId);
        if (button) {
            button.disabled = !enabled;
            if (text) {
                button.textContent = text;
            }
            button.className = enabled ? 'btn-enabled' : 'btn-disabled';
        }
    }

    /**
     * Update element text content safely
     */
    static updateElement(elementId, content) {
        const element = document.getElementById(elementId);
        if (element) {
            element.textContent = content;
        }
    }

    /**
     * Show/hide element
     */
    static setElementVisible(elementId, visible) {
        const element = document.getElementById(elementId);
        if (element) {
            element.style.display = visible ? 'block' : 'none';
        }
    }

    /**
     * Add CSS class to element
     */
    static addClass(elementId, className) {
        const element = document.getElementById(elementId);
        if (element) {
            element.classList.add(className);
        }
    }

    /**
     * Remove CSS class from element
     */
    static removeClass(elementId, className) {
        const element = document.getElementById(elementId);
        if (element) {
            element.classList.remove(className);
        }
    }
}

// Error handling utilities
class ErrorHandler {
    static handleGrpcError(error, logger, context = '') {
        let errorMessage = 'Unknown error occurred';
        let errorType = 'error';
        
        if (error) {
            if (typeof error === 'string') {
                errorMessage = error;
            } else if (error.message) {
                errorMessage = error.message;
            } else if (error.details) {
                errorMessage = error.details;
            }
        }
        
        const fullMessage = context ? `${context}: ${errorMessage}` : errorMessage;
        
        if (logger) {
            logger.log(fullMessage, errorType);
        }
        
        console.error('gRPC Error:', error);
        return errorMessage;
    }

    static async withErrorHandling(asyncFn, logger, context = '') {
        try {
            return await asyncFn();
        } catch (error) {
            ErrorHandler.handleGrpcError(error, logger, context);
            throw error;
        }
    }
}

// Export utilities to global scope
window.ActivityLogger = ActivityLogger;
window.PerformanceTracker = PerformanceTracker;
window.ConnectionStateManager = ConnectionStateManager;
window.UIUtils = UIUtils;
window.ErrorHandler = ErrorHandler;

console.log('Shared utilities loaded successfully');