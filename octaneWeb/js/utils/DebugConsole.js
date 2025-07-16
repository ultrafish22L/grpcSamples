/**
 * Custom Debug Console Window
 * Captures browser console logs and errors with Ctrl-D toggle
 * Required during active development when F12 may not work reliably
 */

class DebugConsole {
    constructor() {
        this.isVisible = true;  // Show debug console by default
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
                    <button class="debug-btn" onclick="debugConsole.toggle()">Hide</button>
                </div>
            </div>
            <div class="debug-content">
                <div class="debug-logs" id="debug-logs"></div>
            </div>
        `;
        
        // CSS styles now in components.css
        
        // Append to body
        document.body.appendChild(this.element);
        
        // Show by default (changed from initially hidden)
        this.element.style.display = 'block';
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
}

// Initialize debug console when DOM is ready
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', () => {
        window.debugConsole = new DebugConsole();
    });
} else {
    window.debugConsole = new DebugConsole();
}