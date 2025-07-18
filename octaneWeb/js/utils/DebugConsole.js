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
                        <button class="debug-btn" title="Start unit testing" onclick="debugConsole.unitTest()">🧑‍🚒</button>
                        <button class="debug-btn" title="Clear debug console logs" onclick="debugConsole.clear()">🗑️</button>
                        <button class="debug-btn" title="Close debug console" onclick="debugConsole.toggle()">✖️</button>
                    </div>
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
                height: 70%;
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
            .debug-controlbar {
                background: #333;
            }

            .debug-controls {
                display: flex;
                justify-content: flex-end;
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
            
            .debug-content {
                height: 100%;
            }
            
            .debug-logs {
                height: 100%;
                overflow-y: hidden;
                padding: 0px;
                color: #fff;
            }
            
            .debug-log {
                margin: 0px 0;
                padding: 0px 0px;
                border-radius: 0px;
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
                <span class="debug-message">${log.message}</span>
            </div>
        `).join('');
/*        
        logsContainer.innerHTML = this.logs.map(log => `
            <div class="debug-log ${log.type}">
                <span class="debug-timestamp">[${log.timestamp}]</span>
                <span class="debug-message">${log.message}</span>
            </div>
        `).join('');
 */       
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
    
    async unitTest() {
        console.info('🧑‍🚒 Starting comprehensive test suite...');
        this.addLog('info', ['🧪 Initiating comprehensive Octane gRPC API test suite']);
        
        try {
            // Get current server address from the UI
            const serverAddress = document.getElementById('serverAddress')?.value || 'http://localhost:51024';
            const testUrl = serverAddress.replace('/api', '/test');
            
            this.addLog('info', [`📡 Test endpoint: ${testUrl}`]);
            
            // Call the test suite endpoint
            const response = await fetch(testUrl, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'X-Call-Id': `test-suite-${Date.now()}`
                }
            });
            
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            
            const result = await response.json();
            
            if (result.success) {
                const data = result.data;
                this.addLog('success', [
                    `✅ Test Suite Completed!`,
                    `📊 Results: ${data.passed}/${data.total_tests} tests passed (${data.success_rate}%)`,
                    `⏱️  Duration: ${data.duration}`,
                    `🕐 Timestamp: ${data.timestamp}`
                ]);
                
                // Log detailed results
                if (data.details && data.details.length > 0) {
                    this.addLog('info', ['📋 Detailed Results:']);
                    data.details.slice(0, 10).forEach(test => {
                        const status = test.status === 'PASS' ? '✅' : '❌';
                        const errorInfo = test.error ? ` - ${test.error}` : '';
                        this.addLog('info', [`  ${status} ${test.test} (${test.duration})${errorInfo}`]);
                    });
                    
                    if (data.details.length > 10) {
                        this.addLog('info', [`  ... and ${data.details.length - 10} more tests`]);
                    }
                }
                
                // Show summary
                if (data.success_rate >= 95) {
                    this.addLog('success', ['🎉 Excellent! Test suite passed with high success rate']);
                } else if (data.success_rate >= 80) {
                    this.addLog('warn', ['⚠️  Good, but some tests failed. Check Octane connection']);
                } else {
                    this.addLog('error', ['🚨 Many tests failed. Verify Octane LiveLink is running']);
                }
                
            } else {
                throw new Error(result.error || 'Test suite failed');
            }
            
        } catch (error) {
            this.addLog('error', [
                '❌ Test suite execution failed:',
                error.message,
                '🔧 Troubleshooting:',
                '  1. Ensure custom proxy server is running (start_proxy.bat)',
                '  2. Verify Octane Render is running with LiveLink enabled',
                '  3. Check server address in connection panel'
            ]);
            
            console.error('Test suite error:', error);
        }
    }

    // Method to add custom success messages
    success(message) {
        this.addLog('success', [message]);
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
