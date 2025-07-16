/**
 * Shared Logging System for Web Applications
 * Provides console interception and custom logging capabilities
 * Can be used by any web project that needs enhanced logging
 */

/**
 * Console Output Router
 * Captures browser console logs and routes them to custom loggers
 */
class ConsoleRouter {
    constructor() {
        this.loggers = [];
        this.originalConsole = {
            log: console.log,
            info: console.info,
            warn: console.warn,
            error: console.error
        };
        
        this.interceptConsole();
        this.setupErrorHandlers();
    }
    
    /**
     * Register a logger to receive console output
     * Logger must have a log(message, type) method
     */
    addLogger(logger) {
        this.loggers.push(logger);
    }
    
    /**
     * Remove a logger from receiving console output
     */
    removeLogger(logger) {
        const index = this.loggers.indexOf(logger);
        if (index > -1) {
            this.loggers.splice(index, 1);
        }
    }
    
    /**
     * Route console output to all registered loggers
     */
    routeToLoggers(type, args) {
        const message = args.map(arg => 
            typeof arg === 'object' ? JSON.stringify(arg, null, 2) : String(arg)
        ).join(' ');
        
        this.loggers.forEach(logger => {
            if (logger && typeof logger.log === 'function') {
                logger.log(message, type);
            }
        });
    }
    
    /**
     * Intercept console methods to route to loggers
     */
    interceptConsole() {
        console.log = (...args) => {
            this.originalConsole.log.apply(console, args);
            this.routeToLoggers('info', args);
        };
        
        console.info = (...args) => {
            this.originalConsole.info.apply(console, args);
            this.routeToLoggers('info', args);
        };
        
        console.warn = (...args) => {
            this.originalConsole.warn.apply(console, args);
            this.routeToLoggers('warning', args);
        };
        
        console.error = (...args) => {
            this.originalConsole.error.apply(console, args);
            this.routeToLoggers('error', args);
        };
    }
    
    /**
     * Setup global error handlers
     */
    setupErrorHandlers() {
        // Capture unhandled JavaScript errors
        window.addEventListener('error', (event) => {
            this.routeToLoggers('error', [
                `❌ JavaScript Error: ${event.error?.message || event.message}`,
                `File: ${event.filename}`,
                `Line: ${event.lineno}`
            ]);
        });
        
        // Capture unhandled promise rejections
        window.addEventListener('unhandledrejection', (event) => {
            this.routeToLoggers('error', [
                `🚫 Unhandled Promise Rejection:`,
                event.reason
            ]);
        });
    }
    
    /**
     * Restore original console methods
     */
    restore() {
        console.log = this.originalConsole.log;
        console.info = this.originalConsole.info;
        console.warn = this.originalConsole.warn;
        console.error = this.originalConsole.error;
    }
}

/**
 * Enhanced Activity Logger with Console Integration
 * Extends the basic ActivityLogger with console routing capabilities
 */

// Debug: Check if ActivityLogger is available when this script loads
console.log('logging.js: ActivityLogger available at load time:', typeof ActivityLogger !== 'undefined');

class EnhancedActivityLogger extends ActivityLogger {
    constructor(containerId, enableConsoleRouting = true) {
        super(containerId);
        
        this.consoleRouting = enableConsoleRouting;
        
        if (this.consoleRouting) {
            // Get or create global console router
            if (!window.consoleRouter) {
                window.consoleRouter = new ConsoleRouter();
            }
            
            // Register this logger with the console router
            window.consoleRouter.addLogger(this);
            
            // Log that console routing is active
            this.log('🔗 Console output routing enabled', 'info');
        }
    }
    
    /**
     * Enable/disable console routing for this logger
     */
    setConsoleRouting(enabled) {
        if (!window.consoleRouter) return;
        
        if (enabled && !this.consoleRouting) {
            window.consoleRouter.addLogger(this);
            this.consoleRouting = true;
            this.log('🔗 Console output routing enabled', 'info');
        } else if (!enabled && this.consoleRouting) {
            window.consoleRouter.removeLogger(this);
            this.consoleRouting = false;
            this.log('🔌 Console output routing disabled', 'info');
        }
    }
    
    /**
     * Cleanup when logger is destroyed
     */
    destroy() {
        if (this.consoleRouting && window.consoleRouter) {
            window.consoleRouter.removeLogger(this);
        }
    }
}

/**
 * Debug Console Utilities
 * Provides keyboard shortcuts and debug helpers
 */
class DebugUtils {
    constructor(logger = null) {
        this.logger = logger;
        this.setupKeyboardShortcuts();
    }
    
    /**
     * Set the logger for debug output
     */
    setLogger(logger) {
        this.logger = logger;
    }
    
    /**
     * Setup keyboard shortcuts for debugging
     */
    setupKeyboardShortcuts() {
        document.addEventListener('keydown', (event) => {
            // Ctrl-D to toggle verbose logging
            if (event.ctrlKey && event.key === 'd') {
                event.preventDefault();
                this.toggleVerboseLogging();
            }
            
            // Ctrl-Shift-L to clear logs
            if (event.ctrlKey && event.shiftKey && event.key === 'L') {
                event.preventDefault();
                this.clearLogs();
            }
        });
    }
    
    /**
     * Toggle verbose logging if available
     */
    toggleVerboseLogging() {
        const verboseToggle = document.getElementById('verboseLogsToggle');
        if (verboseToggle) {
            verboseToggle.checked = !verboseToggle.checked;
            verboseToggle.dispatchEvent(new Event('change'));
            
            if (this.logger) {
                this.logger.log(`🐛 Verbose logging ${verboseToggle.checked ? 'ENABLED' : 'DISABLED'} (Ctrl-D to toggle)`, 'info');
            }
        } else {
            console.info('🐛 Verbose logging toggle not found (Ctrl-D pressed)');
        }
    }
    
    /**
     * Clear logs if available
     */
    clearLogs() {
        if (this.logger && typeof this.logger.clear === 'function') {
            this.logger.clear();
            this.logger.log('🧹 Logs cleared via Ctrl-Shift-L', 'info');
        } else {
            console.info('🧹 Log clearing not available (Ctrl-Shift-L pressed)');
        }
    }
    
    /**
     * Log system information
     */
    logSystemInfo() {
        if (!this.logger) return;
        
        this.logger.log('🖥️ System Information:', 'info');
        this.logger.log(`Browser: ${navigator.userAgent}`, 'debug');
        this.logger.log(`Screen: ${screen.width}x${screen.height}`, 'debug');
        this.logger.log(`Viewport: ${window.innerWidth}x${window.innerHeight}`, 'debug');
        this.logger.log(`WebGL: ${this.checkWebGLSupport()}`, 'debug');
    }
    
    /**
     * Check WebGL support
     */
    checkWebGLSupport() {
        try {
            const canvas = document.createElement('canvas');
            const gl = canvas.getContext('webgl') || canvas.getContext('experimental-webgl');
            return gl ? 'Supported' : 'Not supported';
        } catch (e) {
            return 'Error checking support';
        }
    }
}

// Initialize global console router when script loads
if (typeof window !== 'undefined') {
    // Only create if not already exists
    if (!window.consoleRouter) {
        window.consoleRouter = new ConsoleRouter();
    }
    
    // Create global debug utils
    if (!window.debugUtils) {
        window.debugUtils = new DebugUtils();
    }
}