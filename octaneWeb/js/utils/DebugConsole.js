/**
 * Enhanced Debug Console with Auto-Save Logging
 * 
 * Production-ready debug console system that captures all console output,
 * provides real-time log viewing, and automatically saves logs to files
 * for production debugging and error analysis.
 * 
 * Key Features:
 * - Session-based logging with unique session IDs
 * - Real-time console interception and display
 * - Automatic log file saving via proxy server
 * - Keyboard shortcuts (F12, Ctrl+D) for quick access
 * - Color-coded log levels (info, warn, error)
 * - Persistent log storage for post-mortem debugging
 * 
 * Production Usage:
 * - Accessible globally via window.debugConsole
 * - Toggle visibility with toggleUIDebugMode() in browser console
 * - Logs automatically saved to debug_logs/ directory
 * - Session-based log clearing prevents log file bloat
 * 
 * Critical Debugging Rule:
 * - NEVER use browser console for debugging - ALWAYS read log files
 * - Log files provide complete session history and error context
 * - Browser console may miss critical errors during initialization
 */
class DebugConsole {
    constructor() {
        this.logs = [];
        this.isVisible = false;
        this.element = null;
        this.logsContainer = null;
        this.sessionId = this.generateSessionId();
        this.autoSaveInterval = null;
        this.proxyUrl = 'http://localhost:51023';
        this.isDragging = false;
        this.dragTarget = null;
        this.lastMousePos = { x: 0, y: 0 };
        this.eventListeners = [];
        this.theLogLevel = 0;

        // Store original console methods
        this.originalLog = console.log;
        this.originalError = console.error;
        this.originalWarn = console.warn;
        
        this.createConsole();
        this.interceptConsole();
        this.setupEventListeners();
        
        // Add initial test logs
        this.addLog('info', 'Debug Console initialized');
        this.addLog('info', `Session ID: ${this.sessionId}`);
        this.addLog('info', 'Use F12 or Ctrl+D to toggle');
    }
    
        /**
     * Add event listener with automatic cleanup
     */
    addEventListener(event, handler, options = {}) {
        this.eventListeners.push({event, handler, options });
    }

    handleMouseDown(e) {
        this.isDragging = true;
    }
    
    handleMouseMove(e) {
        // Handle dragging
        if (this.isDragging) {
        }
    }
    
        
    handleMouseUp(e) {
        this.isDragging = false;
    }
    
    setupEventListeners() {
        // Mouse events
        this.addEventListener('mousedown', this.handleMouseDown.bind(this));
        this.addEventListener('mousemove', this.handleMouseMove.bind(this));
        this.addEventListener('mouseup', this.handleMouseUp.bind(this));
    }

    generateSessionId() {
        return Date.now().toString(36) + Math.random().toString(36).substr(2);
    }
    
    createConsole() {
        // Create main container
        this.element = document.createElement('div');
        this.element.id = 'debug-console';
        this.element.style.cssText = `
            position: absolute;
            top: 20px;
            left: 200px;
            width: 900px;
            height: 800px;
            background: #2a2a2a;
            border: 1px solid #555;
            border-radius: 5px;
            z-index: 10000;
            display: none;
            font-family: 'Courier New', monospace;
            font-size: 12px;
            color: white;
        `;
        
        // Create header
        const header = document.createElement('div');
        header.style.cssText = `
            background: #333;
            padding: 8px;
            border-bottom: 1px solid #555;
            display: flex;
            justify-content: space-between;
            align-items: center;
            cursor: move;
        `;
        header.innerHTML = `
            <span>🐛 Debug Console (${this.sessionId})</span>
            <div>
                <button id="debug-test-btn" style="background: #555; color: white; border: none; padding: 4px 8px; margin-right: 4px; border-radius: 3px; cursor: pointer;">🧑‍🚒</button>
                <button id="debug-clear-btn" style="background: #555; color: white; border: none; padding: 4px 8px; margin-right: 4px; border-radius: 3px; cursor: pointer;">🗑️</button>
                <button id="debug-close-btn" style="background: #555; color: white; border: none; padding: 4px 8px; border-radius: 3px; cursor: pointer;">✖️</button>
            </div>
        `;
        
        // Create logs container
        this.logsContainer = document.createElement('div');
        this.logsContainer.id = 'debug-logs-container';
        this.logsContainer.style.cssText = `
            overflow-y: scroll;
            padding: 8px;
            background: #1a1a1a;
            max-height: 800px;
            scrollbar-width: auto;
            scrollbar-color: #888 #2a2a2a;
        `;
        
        // Add custom scrollbar styles for webkit browsers
        const scrollbarStyle = document.createElement('style');
        scrollbarStyle.textContent = `
            #debug-logs-container {
                /* Force scrollbar to always be visible */
                overflow-y: scroll !important;
                scrollbar-width: auto;
                scrollbar-color: #888 #2a2a2a;
            }
            
            #debug-logs-container::-webkit-scrollbar {
                width: 12px;
                background: #2a2a2a;
            }
            #debug-logs-container::-webkit-scrollbar-track {
                background: #2a2a2a;
                border-radius: 6px;
            }
            #debug-logs-container::-webkit-scrollbar-thumb {
                background: #888;
                border-radius: 6px;
                border: 2px solid #2a2a2a;
            }
            #debug-logs-container::-webkit-scrollbar-thumb:hover {
                background: #aaa;
            }
            #debug-logs-container::-webkit-scrollbar-thumb:active {
                background: #ccc;
            }
        `;
        document.head.appendChild(scrollbarStyle);
        
        // Assemble console
        this.element.appendChild(header);
        this.element.appendChild(this.logsContainer);
        document.body.appendChild(this.element);
        
        // Add event listeners
        document.getElementById('debug-test-btn').addEventListener('click', () => this.runTest());
        document.getElementById('debug-clear-btn').addEventListener('click', () => this.clear());
        document.getElementById('debug-close-btn').addEventListener('click', () => this.hide());
        
        console.log('Debug console DOM created successfully');
    }
    
    interceptConsole() {
        // Intercept console.log
        console.log = (...args) => {
            this.originalLog(...args);
            this.addLog('info', args.join(' '));
        };
        
        // Intercept console.error
        console.error = (...args) => {
            this.originalError(...args);
            this.addLog('error', args.join(' '));
        };
        
        // Intercept console.warn
        console.warn = (...args) => {
            this.originalWarn(...args);
            this.addLog('warn', args.join(' '));
        };
        
        // Capture uncaught JavaScript errors
        window.addEventListener('error', (event) => {
            const errorMsg = `Uncaught Error: ${event.message} at ${event.filename}:${event.lineno}:${event.colno}`;
            this.addLog('error', errorMsg);
            if (event.error && event.error.stack) {
                this.addLog('error', `Stack: ${event.error.stack}`);
            }
        });
        
        // Capture unhandled promise rejections
        window.addEventListener('unhandledrejection', (event) => {
            const errorMsg = `Unhandled Promise Rejection: ${event.reason}`;
            this.addLog('error', errorMsg);
            if (event.reason && event.reason.stack) {
                this.addLog('error', `Stack: ${event.reason.stack}`);
            }
        });
    }

    log(message) {
        this.addLog("info", message);
    }

    logLevel(level, message) {
        if (this.theLogLevel >= level) {
            this.addLog("info", message);
        }
    }

    logIndent(indent, message) {
        const indents = "  ".repeat(indent) + message; // 2 spaces per level
        this.addLog("info", indents);
    }

    logLevelIndent(level, indent, message) {
        if (this.theLogLevel >= level) {
            this.logIndent(indent, message);
        }
    }

    addLog(type, message) {
        const timestamp = new Date().toLocaleTimeString();
        this.logs.push({
            type: type,
            message: message,
            timestamp: timestamp
        });
        
        // Send to proxy immediately
        this.sendLogToProxy(type, message, timestamp);
        
        // Keep only last 200 logs
        if (this.logs.length > 200) {
            this.logs.shift();
        }
        
        this.updateDisplay();
    }
    
    updateDisplay() {
        if (!this.logsContainer) return;
        
        // Clear container
        this.logsContainer.innerHTML = '';
        
        // Add each log
        this.logs.forEach(log => {
            const logElement = document.createElement('div');
            logElement.style.cssText = `
                margin-bottom: 4px;
                padding: 6px;
                border-left: 3px solid ${this.getLogColor(log.type)};
                background: rgba(255,255,255,0.05);
                word-wrap: break-word;
                overflow-wrap: break-word;
                white-space: pre-wrap;
                line-height: 1.4;
            `;
            
            const timestampSpan = document.createElement('span');
            timestampSpan.style.cssText = 'color: #888; font-size: 10px; margin-right: 8px;';
            timestampSpan.textContent = `[${log.timestamp}]`;
            
            const messageSpan = document.createElement('span');
            messageSpan.style.cssText = `color: ${this.getLogColor(log.type)}; word-break: break-word;`;
            messageSpan.textContent = log.message;
            
            logElement.appendChild(timestampSpan);
            logElement.appendChild(messageSpan);
            
            this.logsContainer.appendChild(logElement);
        });
        
        // Auto-scroll to bottom
        this.logsContainer.scrollTop = this.logsContainer.scrollHeight;
    }
    
    getLogColor(type) {
        switch(type) {
            case 'error': return '#ff4444';
            case 'warn': return '#ffaa00';
            case 'info': return '#44ff44';
            default: return '#ffffff';
        }
    }
    
    show() {
        this.isVisible = true;
        this.element.style.display = 'block';
        this.updateDisplay();
        this.addLog('info', '🐛 Debug Console opened');
    }
    
    hide() {
        this.isVisible = false;
        this.element.style.display = 'none';
    }
    
    toggle() {
        if (this.isVisible) {
            this.hide();
        } else {
            this.show();
        }
    }
    
    clear() {
        this.logs = [];
        this.updateDisplay();
        this.addLog('info', '🧹 Debug console cleared');
    }
    
    async sendLogToProxy(type, message, timestamp) {
        try {
            const logEntry = `[${timestamp}] ${type.toUpperCase()}: ${message}`;
            
            await fetch(`${this.proxyUrl}/debug/append-log`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    sessionId: this.sessionId,
                    logEntry: logEntry,
                    timestamp: new Date().toISOString()
                })
            });
        } catch (error) {
            // Silently fail - don't spam console with proxy connection errors
            // The original console methods will still work
        }
    }
    
    runTest() {
        this.addLog('info', '🧑‍🚒 Running debug test...');
        this.addLog('warn', ' This is a warning message');
        this.addLog('error', '❌ This is an error message');
        this.addLog('info', 'Test completed successfully');
        
        // Add multiple test logs to test scrolling
        for (let i = 1; i <= 10; i++) {
            this.addLog('info', `📝 Test log entry ${i} - This is a longer message to test word wrapping and scrolling functionality in the debug console.`);
        }
        
        // Test API call
        if (window.octaneClient) {
            this.addLog('info', 'Testing API call...');
            window.octaneClient.getPinCount()
                .then(response => {
                    this.addLog('info', `📌 Pin count: ${response.count}`);
                })
                .catch(error => {
                    this.addLog('error', `❌ API error: ${error.message}`);
                });
        } else {
            this.addLog('warn', ' octaneClient not available - skipping API test');
        }
        
        // Test log streaming to proxy
        this.addLog('info', 'All logs are automatically streamed to proxy log file');
    }
}

// Export for use in other modules
window.DebugConsole = DebugConsole;