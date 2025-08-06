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
        // Note: Keyboard shortcuts are handled by the main app (app.js)
        
        // Add some initial logs to show the console is working
        this.addLog('info', ['🚀 Debug Console initialized']);
        this.addLog('info', ['📋 Use Ctrl+D or F12 to toggle this console']);
        this.addLog('info', ['🧹 Use the clear button to clear logs']);
        this.addLog('info', ['🧑‍🚒 Use the test button to run API tests']);
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
                height: calc(100% - 40px);
                overflow-y: auto;
                padding: 8px;
                color: #fff;
                background: #1a1a1a;
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
        this.originalLog = console.log;
        this.originalInfo = console.info;
        this.originalWarn = console.warn;
        this.originalError = console.error;
        
        // Override console methods
        console.log = (...args) => {
            this.originalLog.apply(console, args);
            this.addLog('log', args);
        };
        
        console.info = (...args) => {
            this.originalInfo.apply(console, args);
            this.addLog('info', args);
        };
        
        console.warn = (...args) => {
            this.originalWarn.apply(console, args);
            this.addLog('warn', args);
        };
        
        console.error = (...args) => {
            this.originalError.apply(console, args);
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
        
        // Use original console method to avoid infinite recursion
        if (this.originalLog) {
            this.originalLog(`📝 DebugConsole: Added ${type} log (total: ${this.logs.length})`);
        }
        
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
        if (!logsContainer) {
            // Use original console method to avoid infinite recursion
            if (this.originalError) {
                this.originalError('❌ Debug logs container not found!');
            }
            return;
        }
        
        // Use original console method to avoid infinite recursion
        if (this.originalLog) {
            this.originalLog(`🔍 DebugConsole: Updating display with ${this.logs.length} logs`);
        }
        
        if (this.logs.length === 0) {
            logsContainer.innerHTML = '<div class="debug-log info"><span class="debug-message">No logs yet...</span></div>';
        } else {
            logsContainer.innerHTML = this.logs.map(log => `
                <div class="debug-log ${log.type}">
                    <span class="debug-message">${log.message}</span>
                </div>
            `).join('');
        }
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
    
    // setupKeyboardShortcut() {
    //     // This is now handled by the main app (app.js) to avoid conflicts
    //     document.addEventListener('keydown', (event) => {
    //         // Ctrl-D to toggle debug console
    //         if (event.ctrlKey && event.key === 'd') {
    //             event.preventDefault();
    //             this.toggle();
    //         }
    //     });
    // }
    
    toggle() {
        this.isVisible = !this.isVisible;
        this.element.style.display = this.isVisible ? 'block' : 'none';
        
        if (this.isVisible) {
            this.updateDisplay();
            // Add a log entry when console opens
            this.addLog('info', ['🐛 Debug Console opened (Ctrl+D or F12 to toggle)']);
        }
    }
    
    clear() {
        this.logs = [];
        this.updateDisplay();
        // Use original console method to avoid infinite recursion
        if (this.originalInfo) {
            this.originalInfo('🧹 Debug console cleared');
        }
    }
    
    async unitTest() {
        // Use original console method to avoid infinite recursion
        if (this.originalInfo) {
            this.originalInfo('🧑‍🚒 Starting comprehensive test suite...');
        }
        this.addLog('info', ['🧪 Initiating comprehensive Octane gRPC API test suite']);
        
        // Execute the comprehensive test callback
        await this.comprehensiveTestCallback();
    }

    // Comprehensive Test Suite Callback - Integrated from octaneGrpcTest.py
    async comprehensiveTestCallback() {
        const startTime = Date.now();
        let totalTests = 0;
        let passedTests = 0;
        const testResults = [];
        
        try {
            // Get current server address from the UI
            const serverAddress = document.getElementById('serverAddress')?.value || 'http://localhost:51023';
            const baseUrl = serverAddress.replace('/api', '').replace(/\/$/, '');
            
            this.addLog('info', [`📡 Testing against: ${baseUrl}`]);
            this.addLog('info', ['🔥 CRITICAL: Using ObjectPtr type conversion for polymorphic API access']);
            
            // Test Categories from octaneGrpcTest.py
            const testCategories = [
                { name: 'Project Management', tests: this.testProjectManagement },
                { name: 'Node Creation & Manipulation', tests: this.testNodeOperations },
                { name: 'Pin Operations & Connections', tests: this.testPinOperations },
                { name: 'Attribute Getting/Setting', tests: this.testAttributeOperations },
                { name: 'Graph Operations', tests: this.testGraphOperations },
                { name: 'Scene Outliner', tests: this.testSceneOutliner },
                { name: 'Render Control', tests: this.testRenderControl },
                { name: 'Selection Management', tests: this.testSelectionManagement }
            ];
            
            // Execute each test category
            for (const category of testCategories) {
                this.addLog('info', [`🧪 Testing: ${category.name}`]);
                
                try {
                    const categoryResults = await category.tests.call(this, baseUrl);
                    totalTests += categoryResults.total;
                    passedTests += categoryResults.passed;
                    testResults.push(...categoryResults.details);
                    
                    const successRate = Math.round((categoryResults.passed / categoryResults.total) * 100);
                    const status = successRate >= 80 ? '✅' : successRate >= 50 ? '⚠️' : '❌';
                    this.addLog('info', [`  ${status} ${category.name}: ${categoryResults.passed}/${categoryResults.total} (${successRate}%)`]);
                    
                } catch (error) {
                    this.addLog('error', [`  ❌ ${category.name} failed: ${error.message}`]);
                    totalTests += 1;
                    testResults.push({
                        test: category.name,
                        status: 'FAIL',
                        error: error.message,
                        duration: '0ms'
                    });
                }
            }
            
            // Calculate final results
            const duration = Date.now() - startTime;
            const successRate = Math.round((passedTests / totalTests) * 100);
            
            // Display comprehensive results
            this.addLog('success', [
                `✅ Comprehensive Test Suite Completed!`,
                `📊 Final Results: ${passedTests}/${totalTests} tests passed (${successRate}%)`,
                `⏱️  Total Duration: ${duration}ms`,
                `🕐 Timestamp: ${new Date().toISOString()}`
            ]);
            
            // Show detailed results (first 15)
            if (testResults.length > 0) {
                this.addLog('info', ['📋 Detailed Test Results:']);
                testResults.slice(0, 15).forEach(test => {
                    const status = test.status === 'PASS' ? '✅' : '❌';
                    const errorInfo = test.error ? ` - ${test.error}` : '';
                    this.addLog('info', [`  ${status} ${test.test}${errorInfo}`]);
                });
                
                if (testResults.length > 15) {
                    this.addLog('info', [`  ... and ${testResults.length - 15} more tests`]);
                }
            }
            
            // Final assessment
            if (successRate >= 95) {
                this.addLog('success', ['🎉 EXCELLENT! Comprehensive test suite passed with high success rate']);
            } else if (successRate >= 80) {
                this.addLog('warn', ['⚠️  GOOD: Most tests passed, some minor issues detected']);
            } else if (successRate >= 50) {
                this.addLog('warn', ['🔧 PARTIAL: Significant issues detected, check Octane connection']);
            } else {
                this.addLog('error', ['🚨 CRITICAL: Major failures detected, verify Octane LiveLink is running']);
            }
            
        } catch (error) {
            this.addLog('error', [
                '❌ Comprehensive test suite execution failed:',
                error.message,
                '🔧 Troubleshooting:',
                '  1. Ensure custom proxy server is running',
                '  2. Verify Octane Render is running with LiveLink enabled',
                '  3. Check server address in connection panel',
                '  4. Verify ObjectPtr type conversion is working'
            ]);
            
            // Use original console method to avoid infinite recursion
            if (this.originalError) {
                this.originalError('Comprehensive test suite error:', error);
            }
        }
    }

    // Test Category Methods - Integrated from octaneGrpcTest.py
    
    async testProjectManagement(baseUrl) {
        const results = { total: 0, passed: 0, details: [] };
        const testStart = Date.now();
        
        try {
            // Test 1: Get Project Info
            results.total++;
            const projectResponse = await fetch(`${baseUrl}/api/project/info`, {
                method: 'GET',
                headers: { 'X-Call-Id': `test-project-${Date.now()}` }
            });
            
            if (projectResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Get Project Info', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Get Project Info', status: 'FAIL', error: `HTTP ${projectResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
            // Test 2: Create New Project
            results.total++;
            const createResponse = await fetch(`${baseUrl}/api/project/new`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json', 'X-Call-Id': `test-create-${Date.now()}` },
                body: JSON.stringify({ name: 'Test Project' })
            });
            
            if (createResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Create New Project', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Create New Project', status: 'FAIL', error: `HTTP ${createResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
        } catch (error) {
            results.details.push({ test: 'Project Management', status: 'FAIL', error: error.message, duration: `${Date.now() - testStart}ms` });
        }
        
        return results;
    }
    
    async testNodeOperations(baseUrl) {
        const results = { total: 0, passed: 0, details: [] };
        const testStart = Date.now();
        
        try {
            // Test 1: Create Material Node
            results.total++;
            const createNodeResponse = await fetch(`${baseUrl}/api/nodes/create`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json', 'X-Call-Id': `test-node-${Date.now()}` },
                body: JSON.stringify({ 
                    type: 'DiffuseMaterial',
                    name: 'Test Material'
                })
            });
            
            if (createNodeResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Create Material Node', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Create Material Node', status: 'FAIL', error: `HTTP ${createNodeResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
            // Test 2: List Nodes
            results.total++;
            const listResponse = await fetch(`${baseUrl}/api/nodes/list`, {
                method: 'GET',
                headers: { 'X-Call-Id': `test-list-${Date.now()}` }
            });
            
            if (listResponse.ok) {
                results.passed++;
                results.details.push({ test: 'List Nodes', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'List Nodes', status: 'FAIL', error: `HTTP ${listResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
        } catch (error) {
            results.details.push({ test: 'Node Operations', status: 'FAIL', error: error.message, duration: `${Date.now() - testStart}ms` });
        }
        
        return results;
    }
    
    async testPinOperations(baseUrl) {
        const results = { total: 0, passed: 0, details: [] };
        const testStart = Date.now();
        
        try {
            // Test 1: Get Node Pins
            results.total++;
            const pinsResponse = await fetch(`${baseUrl}/api/nodes/pins`, {
                method: 'GET',
                headers: { 'X-Call-Id': `test-pins-${Date.now()}` }
            });
            
            if (pinsResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Get Node Pins', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Get Node Pins', status: 'FAIL', error: `HTTP ${pinsResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
        } catch (error) {
            results.details.push({ test: 'Pin Operations', status: 'FAIL', error: error.message, duration: `${Date.now() - testStart}ms` });
        }
        
        return results;
    }
    
    async testAttributeOperations(baseUrl) {
        const results = { total: 0, passed: 0, details: [] };
        const testStart = Date.now();
        
        try {
            // Test 1: Get Node Attributes
            results.total++;
            const attrsResponse = await fetch(`${baseUrl}/api/nodes/attributes`, {
                method: 'GET',
                headers: { 'X-Call-Id': `test-attrs-${Date.now()}` }
            });
            
            if (attrsResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Get Node Attributes', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Get Node Attributes', status: 'FAIL', error: `HTTP ${attrsResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
        } catch (error) {
            results.details.push({ test: 'Attribute Operations', status: 'FAIL', error: error.message, duration: `${Date.now() - testStart}ms` });
        }
        
        return results;
    }
    
    async testGraphOperations(baseUrl) {
        const results = { total: 0, passed: 0, details: [] };
        const testStart = Date.now();
        
        try {
            // Test 1: Build Scene Tree
            results.total++;
            const treeResponse = await fetch(`${baseUrl}/api/scene/tree`, {
                method: 'GET',
                headers: { 'X-Call-Id': `test-tree-${Date.now()}` }
            });
            
            if (treeResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Build Scene Tree', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Build Scene Tree', status: 'FAIL', error: `HTTP ${treeResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
        } catch (error) {
            results.details.push({ test: 'Graph Operations', status: 'FAIL', error: error.message, duration: `${Date.now() - testStart}ms` });
        }
        
        return results;
    }
    
    async testSceneOutliner(baseUrl) {
        const results = { total: 0, passed: 0, details: [] };
        const testStart = Date.now();
        
        try {
            // Test 1: Get Scene Objects
            results.total++;
            const objectsResponse = await fetch(`${baseUrl}/api/scene/objects`, {
                method: 'GET',
                headers: { 'X-Call-Id': `test-objects-${Date.now()}` }
            });
            
            if (objectsResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Get Scene Objects', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Get Scene Objects', status: 'FAIL', error: `HTTP ${objectsResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
        } catch (error) {
            results.details.push({ test: 'Scene Outliner', status: 'FAIL', error: error.message, duration: `${Date.now() - testStart}ms` });
        }
        
        return results;
    }
    
    async testRenderControl(baseUrl) {
        const results = { total: 0, passed: 0, details: [] };
        const testStart = Date.now();
        
        try {
            // Test 1: Get Render Status
            results.total++;
            const statusResponse = await fetch(`${baseUrl}/api/render/status`, {
                method: 'GET',
                headers: { 'X-Call-Id': `test-render-${Date.now()}` }
            });
            
            if (statusResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Get Render Status', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Get Render Status', status: 'FAIL', error: `HTTP ${statusResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
        } catch (error) {
            results.details.push({ test: 'Render Control', status: 'FAIL', error: error.message, duration: `${Date.now() - testStart}ms` });
        }
        
        return results;
    }
    
    async testSelectionManagement(baseUrl) {
        const results = { total: 0, passed: 0, details: [] };
        const testStart = Date.now();
        
        try {
            // Test 1: Get Selection
            results.total++;
            const selectionResponse = await fetch(`${baseUrl}/api/selection/get`, {
                method: 'GET',
                headers: { 'X-Call-Id': `test-selection-${Date.now()}` }
            });
            
            if (selectionResponse.ok) {
                results.passed++;
                results.details.push({ test: 'Get Selection', status: 'PASS', duration: `${Date.now() - testStart}ms` });
            } else {
                results.details.push({ test: 'Get Selection', status: 'FAIL', error: `HTTP ${selectionResponse.status}`, duration: `${Date.now() - testStart}ms` });
            }
            
        } catch (error) {
            results.details.push({ test: 'Selection Management', status: 'FAIL', error: error.message, duration: `${Date.now() - testStart}ms` });
        }
        
        return results;
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
