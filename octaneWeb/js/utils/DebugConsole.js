/**
 * Custom Debug Console Window
 * Captures browser console logs and errors with Ctrl-D toggle
 * Required during active development when F12 may not work reliably
 */

class DebugConsole {
    constructor() {
        this.isVisible = false;
        this.logs = [];
        this.maxLogs = 1000;
        this.element = null;
        
        this.init();
        this.interceptConsole();
        this.setupKeyboardShortcut();
    }
    
    init() {
        // Create debug console HTML structure
        this.element = document.createElement('div');
        this.element.id = 'debug-console';
        this.element.innerHTML = `
            <div class="debug-header">
                <span class="debug-title">🐛 Debug Console</span>
                <div class="debug-controls">
                    <button class="debug-btn" onclick="debugConsole.clear()">Clear</button>
                    <button class="debug-btn unit-test-btn" onclick="debugConsole.runUnitTests()" title="Run comprehensive gRPC unit tests">🔥 Unit Tests</button>
                    <button class="debug-btn" onclick="debugConsole.toggle()">Hide</button>
                </div>
            </div>
            <div class="debug-content">
                <div class="debug-logs" id="debug-logs"></div>
            </div>
        `;
        
        // Add CSS styles
        this.addStyles();
        
        // Append to body
        document.body.appendChild(this.element);
        
        // Initially hidden
        this.element.style.display = 'none';
    }
    
    addStyles() {
        const style = document.createElement('style');
        style.textContent = `
            #debug-console {
                position: fixed;
                top: 50px;
                right: 20px;
                width: 600px;
                height: 400px;
                background: #1a1a1a;
                border: 2px solid #333;
                border-radius: 8px;
                z-index: 10000;
                font-family: 'Courier New', monospace;
                font-size: 12px;
                box-shadow: 0 4px 20px rgba(0,0,0,0.5);
            }
            
            .debug-header {
                background: #333;
                color: #fff;
                padding: 8px 12px;
                display: flex;
                justify-content: space-between;
                align-items: center;
                border-bottom: 1px solid #555;
            }
            
            .debug-title {
                font-weight: bold;
            }
            
            .debug-controls {
                display: flex;
                gap: 8px;
            }
            
            .debug-btn {
                background: #555;
                color: #fff;
                border: none;
                padding: 4px 8px;
                border-radius: 3px;
                cursor: pointer;
                font-size: 11px;
            }
            
            .debug-btn:hover {
                background: #666;
            }
            
            .debug-btn.unit-test-btn {
                background: #ff4444;
                color: #fff;
                font-weight: bold;
            }
            
            .debug-btn.unit-test-btn:hover {
                background: #ff6666;
            }
            
            .debug-content {
                height: calc(100% - 40px);
                overflow: hidden;
            }
            
            .debug-logs {
                height: 100%;
                overflow-y: auto;
                padding: 8px;
                color: #fff;
            }
            
            .debug-log {
                margin: 2px 0;
                padding: 2px 4px;
                border-radius: 2px;
                word-wrap: break-word;
            }
            
            .debug-log.log {
                color: #ccc;
            }
            
            .debug-log.info {
                color: #4a9eff;
            }
            
            .debug-log.warn {
                color: #ffa500;
                background: rgba(255, 165, 0, 0.1);
            }
            
            .debug-log.error {
                color: #ff4444;
                background: rgba(255, 68, 68, 0.1);
            }
            
            .debug-log.success {
                color: #4ade80;
                background: rgba(74, 222, 128, 0.1);
            }
            
            .debug-timestamp {
                color: #888;
                font-size: 10px;
            }
        `;
        document.head.appendChild(style);
    }
    
    interceptConsole() {
        // Store original console methods
        const originalLog = console.log;
        const originalInfo = console.info;
        const originalWarn = console.warn;
        const originalError = console.error;
        
        // Override console methods
        console.log = (...args) => {
            originalLog.apply(console, args);
            this.addLog('log', args);
        };
        
        console.info = (...args) => {
            originalInfo.apply(console, args);
            this.addLog('info', args);
        };
        
        console.warn = (...args) => {
            originalWarn.apply(console, args);
            this.addLog('warn', args);
        };
        
        console.error = (...args) => {
            originalError.apply(console, args);
            this.addLog('error', args);
        };
        
        // Capture unhandled errors
        window.addEventListener('error', (event) => {
            this.addLog('error', [`❌ ${event.error?.message || event.message}`, event.filename, `Line: ${event.lineno}`]);
        });
        
        // Capture unhandled promise rejections
        window.addEventListener('unhandledrejection', (event) => {
            this.addLog('error', [`🚫 Unhandled Promise Rejection:`, event.reason]);
        });
    }
    
    addLog(type, args) {
        const timestamp = new Date().toLocaleTimeString();
        const message = args.map(arg => 
            typeof arg === 'object' ? JSON.stringify(arg, null, 2) : String(arg)
        ).join(' ');
        
        const logEntry = {
            type,
            message,
            timestamp
        };
        
        this.logs.push(logEntry);
        
        // Limit log history
        if (this.logs.length > this.maxLogs) {
            this.logs.shift();
        }
        
        // Update display if visible
        if (this.isVisible) {
            this.updateDisplay();
        }
    }
    
    updateDisplay() {
        const logsContainer = document.getElementById('debug-logs');
        if (!logsContainer) return;
        
        logsContainer.innerHTML = this.logs.map(log => `
            <div class="debug-log ${log.type}">
                <span class="debug-timestamp">[${log.timestamp}]</span>
                <span class="debug-message">${log.message}</span>
            </div>
        `).join('');
        
        // Auto-scroll to bottom
        logsContainer.scrollTop = logsContainer.scrollHeight;
    }
    
    setupKeyboardShortcut() {
        document.addEventListener('keydown', (event) => {
            // Ctrl-D to toggle debug console
            if (event.ctrlKey && event.key === 'd') {
                event.preventDefault();
                this.toggle();
            }
        });
    }
    
    toggle() {
        this.isVisible = !this.isVisible;
        this.element.style.display = this.isVisible ? 'block' : 'none';
        
        if (this.isVisible) {
            this.updateDisplay();
            console.info('🐛 Debug Console opened (Ctrl-D to toggle)');
        }
    }
    
    clear() {
        this.logs = [];
        this.updateDisplay();
        console.info('🧹 Debug console cleared');
    }
    
    // Method to add custom success messages
    success(message) {
        this.addLog('success', [message]);
    }
    
    // Method to run comprehensive gRPC unit tests
    async runUnitTests() {
        console.log('🔥 GRIND MODE: Starting comprehensive gRPC unit tests from Debug Console...');
        
        // Check if OctaneWeb is available and connected
        if (typeof octaneWebApp === 'undefined' || !octaneWebApp.client) {
            console.error('❌ OctaneWebClient not available. Connect to Octane first.');
            this.addLog('error', ['❌ OctaneWebClient not available. Connect to Octane first.']);
            return;
        }
        
        if (!octaneWebApp.client.isConnected) {
            console.error('❌ Not connected to Octane. Connect first using the connection toggle.');
            this.addLog('error', ['❌ Not connected to Octane. Connect first using the connection toggle.']);
            return;
        }
        
        try {
            // Show starting message
            this.addLog('info', ['🔥 Starting comprehensive gRPC unit tests...']);
            
            // Use the global function instead of client method
            const results = await runAllGrpcTests();
            
            if (results) {
                // Show completion message
                this.addLog('success', [`✅ Unit tests completed! Tested ${results.totalTests} methods with ${results.successRate.toFixed(1)}% success rate`]);
                console.log('🎯 Unit tests completed successfully!', results);
            } else {
                this.addLog('error', ['❌ Unit tests failed to complete']);
            }
            
        } catch (error) {
            console.error('❌ Error running unit tests:', error);
            this.addLog('error', [`❌ Error running unit tests: ${error.message}`]);
        }
    }
}

// Initialize debug console when DOM is ready
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', () => {
        window.debugConsole = new DebugConsole();
    });
} else {
    window.debugConsole = new DebugConsole();
}