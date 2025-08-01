console.log('LOGGING.JS: VERY FIRST LINE EXECUTED');

/**
 * Shared Logging System for Web Applications
 * Provides console interception and custom logging capabilities
 * Can be used by any web project that needs enhanced logging
 */

console.log('LOGGING.JS: Script started loading');

/**
 * Console Output Router
 * Captures browser console logs and routes them to custom loggers
 */
console.log('LOGGING.JS: About to define ConsoleRouter class');
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
     * Errors and warnings are always logged regardless of logger settings
     */
    routeToLoggers(type, args) {
        const message = args.map(arg => 
            typeof arg === 'object' ? JSON.stringify(arg, null, 2) : String(arg)
        ).join(' ');
        
        this.loggers.forEach(logger => {
            if (logger && typeof logger.log === 'function') {
                // For errors and warnings, bypass the logger's shouldLog check
                if (type === 'error' || type === 'warning') {
                    // Force logging by temporarily storing original shouldLog
                    const originalShouldLog = logger.shouldLog;
                    if (originalShouldLog) {
                        logger.shouldLog = () => true;
                        logger.log(message, type);
                        logger.shouldLog = originalShouldLog;
                    } else {
                        logger.log(message, type);
                    }
                } else {
                    logger.log(message, type);
                }
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
     * All errors are captured and displayed regardless of verbose mode
     */
    setupErrorHandlers() {
        // Capture unhandled JavaScript errors
        window.addEventListener('error', (event) => {
            const errorMessage = event.error?.message || event.message || 'Unknown error';
            const fileName = event.filename || 'Unknown file';
            const lineNumber = event.lineno || 'Unknown line';
            const columnNumber = event.colno || 'Unknown column';
            
            this.routeToLoggers('error', [
                `❌ JavaScript Error: ${errorMessage}`,
                `📁 File: ${fileName}:${lineNumber}:${columnNumber}`,
                event.error?.stack ? `📋 Stack: ${event.error.stack}` : ''
            ].filter(Boolean));
        });
        
        // Capture unhandled promise rejections
        window.addEventListener('unhandledrejection', (event) => {
            const reason = event.reason;
            let reasonMessage = 'Unknown rejection reason';
            
            if (reason instanceof Error) {
                reasonMessage = `${reason.name}: ${reason.message}`;
                if (reason.stack) {
                    reasonMessage += `\n📋 Stack: ${reason.stack}`;
                }
            } else if (typeof reason === 'string') {
                reasonMessage = reason;
            } else if (typeof reason === 'object') {
                reasonMessage = JSON.stringify(reason, null, 2);
            }
            
            this.routeToLoggers('error', [
                `🚫 Unhandled Promise Rejection:`,
                reasonMessage
            ]);
        });
        
        // Capture resource loading errors (images, scripts, etc.)
        window.addEventListener('error', (event) => {
            if (event.target !== window && event.target.tagName) {
                this.routeToLoggers('error', [
                    `📦 Resource Loading Error:`,
                    `Element: ${event.target.tagName}`,
                    `Source: ${event.target.src || event.target.href || 'Unknown source'}`
                ]);
            }
        }, true); // Use capture phase to catch resource errors
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

console.log('LOGGING.JS: ConsoleRouter class defined successfully');

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
    // Debug: Log that we're trying to export ConsoleRouter
    console.log('LOGGING.JS: Exporting ConsoleRouter class to window');
    
    // Make ConsoleRouter class globally available
    window.ConsoleRouter = ConsoleRouter;
    
    // Debug: Confirm export worked
    console.log('LOGGING.JS: window.ConsoleRouter =', window.ConsoleRouter);
    
    // Only create if not already exists
    if (!window.consoleRouter) {
        window.consoleRouter = new ConsoleRouter();
    }
    
    // Create global debug utils
    if (!window.debugUtils) {
        window.debugUtils = new DebugUtils();
    }
}