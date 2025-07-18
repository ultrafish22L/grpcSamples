/**
 * OctaneWeb Main Application
 * Initializes and manages the complete OctaneWeb interface
 */

class OctaneWebApp {
    constructor() {
        // Core components
        this.client = null;
        this.stateManager = null;
        this.eventSystem = null;
        this.layoutManager = null;
        
        // UI components
        this.components = {
            sceneOutliner: null,
            renderViewport: null,
            nodeInspector: null,
            nodeGraphEditor: null,
            menuSystem: null
        };
        
        // Application state
        this.isInitialized = false;
        this.isConnected = false;
        
        // Performance monitoring
        this.performanceStats = {
            fps: 0,
            frameTime: 0,
            lastFrameTime: performance.now()
        };
        
        // Bind methods
        this.handleResize = this.handleResize.bind(this);
        this.handleKeyboard = this.handleKeyboard.bind(this);
        this.updatePerformanceStats = this.updatePerformanceStats.bind(this);
    }
    
    /**
     * Initialize the application
     */
    async initialize() {
        try {
            console.log('🚀 Initializing OctaneWeb...');
            
            // Show loading screen
            this.showLoadingScreen('Initializing application...');
            
            // Initialize core systems
            await this.initializeCoreSystems();
            
            // Initialize UI components
            await this.initializeUIComponents();
            
            // Setup event listeners
            this.setupEventListeners();
            
            // Setup performance monitoring
            this.startPerformanceMonitoring();
            
            // Hide loading screen and show app
            this.hideLoadingScreen();
            
            this.isInitialized = true;
            console.log('✅ OctaneWeb initialized successfully');
            
            // Auto-connect if server address is available
            const serverAddress = document.getElementById('serverAddress')?.value;
            if (serverAddress) {
                await this.connectToOctane(serverAddress);
            }
            
        } catch (error) {
            console.error('❌ Failed to initialize OctaneWeb:', error);
            this.showError('Failed to initialize application', error.message);
        }
    }
    
    /**
     * Initialize core systems
     */
    async initializeCoreSystems() {
        // Initialize console error capturing first
        this.setupConsoleErrorCapture();
        
        // Initialize event system
        this.eventSystem = new EventSystem();
        
        // Initialize state manager
        this.stateManager = new StateManager(this.eventSystem);
        
        // Initialize layout manager
        this.layoutManager = new LayoutManager();
        
        // Initialize gRPC client (not connected yet)
        this.client = new OctaneWebClient('http://localhost:51023');
        
        // Setup client event handlers
        this.setupClientEventHandlers();
        
        console.log('Core systems initialized');
    }
    
    /**
     * Initialize UI components
     */
    async initializeUIComponents() {
        // Initialize scene outliner
        this.components.sceneOutliner = new SceneOutliner(
            document.querySelector('#scene-outliner'),
            this.client,
            this.stateManager
        );
/*        
        // Initialize render viewport
        this.components.renderViewport = new RenderViewport(
            document.querySelector('#render-viewport'),
            this.client,
            this.stateManager
        );
*/        
        // Initialize node inspector
        this.components.nodeInspector = new NodeInspector(
            document.querySelector('#node-inspector'),
            this.client,
            this.stateManager
        );
        
        // Initialize node graph editor
        this.components.nodeGraphEditor = new NodeGraphEditor(
            document.querySelector('#node-graph'),
            this.client,
            this.stateManager
        );
        
        // Initialize menu system
        this.components.menuSystem = new MenuSystem(
            document.querySelector('.main-menu'),
            this.client,
            this.stateManager
        );
        
        // Initialize all components
        for (const [name, component] of Object.entries(this.components)) {
            if (component && typeof component.initialize === 'function') {
                await component.initialize();
                console.log(`${name} component initialized`);
            }
        }
        
        console.log('UI components initialized');
    }
    
    /**
     * Setup client event handlers
     */
    setupClientEventHandlers() {
        // Connection events
        this.client.on('connected', () => {
            this.isConnected = true;
            this.updateConnectionStatus('connected', 'Connected to Octane');
            console.log('🔗 Connected to Octane');
        });
        
        this.client.on('disconnected', () => {
            this.isConnected = false;
            this.updateConnectionStatus('disconnected', 'Disconnected');
            console.log('🔌 Disconnected from Octane');
        });
        
        this.client.on('connectionError', (error) => {
            this.isConnected = false;
            this.updateConnectionStatus('error', 'Connection Error');
            console.error('❌ Connection error:', error);
        });
        
        // UI update events
        this.client.on('ui:sceneUpdate', (sceneState) => {
            this.components.sceneOutliner?.updateScene(sceneState);
        });
        
        this.client.on('ui:nodeGraphUpdate', (nodeGraphState) => {
            this.components.nodeGraphEditor?.updateNodeGraph(nodeGraphState);
        });
        
        this.client.on('ui:renderUpdate', (renderState) => {
            this.components.renderViewport?.updateRender(renderState);
            this.updateRenderStats(renderState);
        });
        
        this.client.on('ui:selectionUpdate', (selection) => {
            this.components.sceneOutliner?.updateSelection(selection);
            this.components.nodeInspector?.updateSelection(selection);
        });
    }
    
    /**
     * Setup global event listeners
     */
    setupEventListeners() {
        // Window resize
        window.addEventListener('resize', this.handleResize);
        
        // Keyboard shortcuts
        document.addEventListener('keydown', this.handleKeyboard);
        
        // Prevent context menu on right-click (we'll handle it ourselves)
        document.addEventListener('contextmenu', (e) => {
            e.preventDefault();
        });
        
        // Connection toggle
        const connectionToggle = document.getElementById('connectionToggle');
        if (connectionToggle) {
            connectionToggle.addEventListener('change', (e) => {
                if (e.target.checked) {
                    const serverAddress = document.getElementById('serverAddress')?.value || 'http://localhost:51023';
                    this.connectToOctane(serverAddress);
                } else {
                    this.disconnectFromOctane();
                }
            });
        }
        
        // Server address change
        const serverAddress = document.getElementById('serverAddress');
        if (serverAddress) {
            serverAddress.addEventListener('change', (e) => {
                if (this.isConnected) {
                    this.disconnectFromOctane();
                }
            });
        }
    }
    
    /**
     * Connect to Octane server
     */
    async connectToOctane(serverUrl) {
        try {
            this.updateConnectionStatus('connecting', 'Connecting...');
            
            // Update client server URL
            this.client.serverUrl = serverUrl;
            
            // Attempt connection
            await this.client.connect();
            
            // Update UI
            const connectionToggle = document.getElementById('connectionToggle');
            if (connectionToggle) {
                connectionToggle.checked = true;
            }
            
        } catch (error) {
            console.error('Failed to connect to Octane:', error);
            this.updateConnectionStatus('error', 'Connection Failed');
            
            // Reset toggle
            const connectionToggle = document.getElementById('connectionToggle');
            if (connectionToggle) {
                connectionToggle.checked = false;
            }
        }
    }
    
    /**
     * Disconnect from Octane server
     */
    async disconnectFromOctane() {
        try {
            await this.client.disconnect();
            
            // Update UI
            const connectionToggle = document.getElementById('connectionToggle');
            if (connectionToggle) {
                connectionToggle.checked = false;
            }
            
        } catch (error) {
            console.error('Error during disconnect:', error);
        }
    }
    
    /**
     * Update connection status indicator
     */
    updateConnectionStatus(status, message) {
        const indicator = document.getElementById('connection-indicator');
        const statusDot = indicator?.querySelector('.status-dot');
        const statusText = indicator?.querySelector('.status-text');
        const octaneStatus = document.getElementById('octane-status');
        
        if (statusDot) {
            statusDot.className = `status-dot ${status}`;
        }
        
        if (statusText) {
            statusText.textContent = message;
        }
        
        if (octaneStatus) {
            octaneStatus.textContent = status;
        }
    }
    
    /**
     * Update render statistics
     */
    updateRenderStats(renderState) {
        // Update render time
        const renderTimeElement = document.getElementById('render-time');
        if (renderTimeElement && renderState.renderTime) {
            renderTimeElement.textContent = `${renderState.renderTime.toFixed(2)}s`;
        }
        
        // Update samples
        const renderSamplesElement = document.getElementById('render-samples');
        if (renderSamplesElement && renderState.samples !== undefined) {
            renderSamplesElement.textContent = `${renderState.samples} samples`;
        }
        
        // Update resolution
        const renderResolutionElement = document.getElementById('render-resolution');
        if (renderResolutionElement && renderState.resolution) {
            const { width, height } = renderState.resolution;
            renderResolutionElement.textContent = `${width}x${height}`;
        }
    }
    
    /**
     * Handle window resize
     */
    handleResize() {
        // Notify layout manager
        this.layoutManager?.handleResize();
        
        // Notify components that need to handle resize
        Object.values(this.components).forEach(component => {
            if (component && typeof component.handleResize === 'function') {
                component.handleResize();
            }
        });
    }
    
    /**
     * Handle keyboard shortcuts
     */
    handleKeyboard(event) {
        // Global shortcuts
        if (event.ctrlKey || event.metaKey) {
            switch (event.key) {
                case 's':
                    event.preventDefault();
                    this.saveScene();
                    break;
                case 'o':
                    event.preventDefault();
                    this.openScene();
                    break;
                case 'z':
                    event.preventDefault();
                    if (event.shiftKey) {
                        this.redo();
                    } else {
                        this.undo();
                    }
                    break;
                case 'c':
                    event.preventDefault();
                    this.copy();
                    break;
                case 'v':
                    event.preventDefault();
                    this.paste();
                    break;
                case 'x':
                    event.preventDefault();
                    this.cut();
                    break;
                case 'a':
                    event.preventDefault();
                    this.selectAll();
                    break;
                case 'd':
                    event.preventDefault();
                    this.duplicate();
                    break;
            }
        }
        
        // Function keys
        switch (event.key) {
            case 'F5':
                event.preventDefault();
                this.refreshScene();
                break;
            case 'F11':
                event.preventDefault();
                this.toggleFullscreen();
                break;
            case 'Delete':
                event.preventDefault();
                this.deleteSelected();
                break;
            case 'Escape':
                event.preventDefault();
                this.clearSelection();
                break;
        }
    }
    
    /**
     * Start performance monitoring
     */
    startPerformanceMonitoring() {
        const updateStats = () => {
            this.updatePerformanceStats();
            requestAnimationFrame(updateStats);
        };
        requestAnimationFrame(updateStats);
    }
    
    /**
     * Update performance statistics
     */
    updatePerformanceStats() {
        const now = performance.now();
        const deltaTime = now - this.performanceStats.lastFrameTime;
        
        this.performanceStats.frameTime = deltaTime;
        this.performanceStats.fps = Math.round(1000 / deltaTime);
        this.performanceStats.lastFrameTime = now;
        
        // Update FPS counter in UI
        const fpsCounter = document.getElementById('fps-counter');
        if (fpsCounter) {
            fpsCounter.textContent = this.performanceStats.fps;
        }
    }
    
    /**
     * Show loading screen with message
     */
    showLoadingScreen(message = 'Loading...') {
        const loadingScreen = document.getElementById('loading-screen');
        const loadingStatus = loadingScreen?.querySelector('.loading-status');
        
        if (loadingScreen) {
            loadingScreen.style.display = 'flex';
        }
        
        if (loadingStatus) {
            loadingStatus.textContent = message;
        }
    }
    
    /**
     * Hide loading screen and show app
     */
    hideLoadingScreen() {
        const loadingScreen = document.getElementById('loading-screen');
        const appContainer = document.getElementById('app-container');
        
        if (loadingScreen) {
            loadingScreen.style.display = 'none';
        }
        
        if (appContainer) {
            appContainer.style.display = 'grid';
        }
    }
    
    /**
     * Show error message
     */
    showError(title, message) {
        // Create modal error dialog
        const modal = document.createElement('div');
        modal.className = 'modal-overlay';
        modal.innerHTML = `
            <div class="modal-dialog">
                <div class="modal-header">
                    <div class="modal-title">❌ ${title}</div>
                    <button class="modal-close" onclick="this.closest('.modal-overlay').remove()">×</button>
                </div>
                <div class="modal-content">
                    <p>${message}</p>
                </div>
                <div class="modal-footer">
                    <button class="modal-button primary" onclick="this.closest('.modal-overlay').remove()">OK</button>
                </div>
            </div>
        `;
        
        document.body.appendChild(modal);
        
        // Auto-remove after 10 seconds
        setTimeout(() => {
            if (modal.parentNode) {
                modal.remove();
            }
        }, 10000);
    }
    
    // ==================== MENU ACTIONS ====================
    
    async saveScene() {
        console.log('Save scene requested');
        // TODO: Implement save scene
    }
    
    async openScene() {
        console.log('Open scene requested');
        // TODO: Implement open scene
    }
    
    async undo() {
        console.log('Undo requested');
        // TODO: Implement undo
    }
    
    async redo() {
        console.log('Redo requested');
        // TODO: Implement redo
    }
    
    async copy() {
        console.log('Copy requested');
        // TODO: Implement copy
    }
    
    async paste() {
        console.log('Paste requested');
        // TODO: Implement paste
    }
    
    async cut() {
        console.log('Cut requested');
        // TODO: Implement cut
    }
    
    async selectAll() {
        console.log('Select all requested');
        // TODO: Implement select all
    }
    
    async duplicate() {
//        console.log('Duplicate requested');
        // TODO: Implement duplicate
    }
    
    async refreshScene() {
        if (this.isConnected) {
            // Use working LiveLink methods instead of old sync methods
            try {
                await this.client.getSceneData();
                console.log('🔄 Scene refreshed via LiveLink');
                
                // TODO: Implement node graph refresh with working LiveLink method
                // await this.client.getNodeGraphData(); // When available
                
            } catch (error) {
                console.error('❌ Failed to refresh scene:', error);
            }
        }
    }
    
    async toggleFullscreen() {
        if (document.fullscreenElement) {
            document.exitFullscreen();
        } else {
            document.documentElement.requestFullscreen();
        }
    }
    
    async deleteSelected() {
        console.log('Delete selected requested');
        // TODO: Implement delete selected
    }
    
    async clearSelection() {
        if (this.isConnected) {
            await this.client.selectObjects([]);
        }
    }
    
    /**
     * Setup console error capturing to display all errors in debug console
     * Ensures errors and warnings are always visible regardless of verbose mode
     */
    setupConsoleErrorCapture() {
        // Create a simple logger that writes to debug console
        const debugLogger = {
            log: (message, type) => {
                // Always show errors and warnings in debug console
                if (type === 'error' || type === 'warning') {
                    const debugLog = document.getElementById('debug-log');
                    if (debugLog) {
                        const entry = document.createElement('div');
                        entry.className = `debug-entry debug-${type}`;
                        const timestamp = new Date().toLocaleTimeString();
                        const emoji = type === 'error' ? '❌' : '⚠️';
                        entry.innerHTML = `<span class="debug-time">[${timestamp}]</span> <span class="debug-emoji">${emoji}</span> ${message}`;
                        debugLog.appendChild(entry);
                        debugLog.scrollTop = debugLog.scrollHeight;
                    }
                }
            }
        };
    }

    /**
     * Cleanup and shutdown
     */
    async shutdown() {
        console.log('🛑 Shutting down OctaneWeb...');
        
        // Disconnect from Octane
        if (this.isConnected) {
            await this.disconnectFromOctane();
        }
        
        // Cleanup components
        Object.values(this.components).forEach(component => {
            if (component && typeof component.destroy === 'function') {
                component.destroy();
            }
        });
        
        // Remove event listeners
        window.removeEventListener('resize', this.handleResize);
        document.removeEventListener('keydown', this.handleKeyboard);
        
        console.log('✅ OctaneWeb shutdown complete');
    }
}

// Global application instance
let octaneWebApp = null;

// Initialize application when DOM is ready
document.addEventListener('DOMContentLoaded', async () => {
    try {
        octaneWebApp = new OctaneWebApp();
        await octaneWebApp.initialize();
        
        // Make app globally available for debugging
        window.octaneWebApp = octaneWebApp;
        
        // Expose NodeInspector for debugging
        window.nodeInspector = octaneWebApp.components.nodeInspector;
        
        // Global functions for HTML event handlers
        window.toggleConnection = () => {
            const toggle = document.getElementById('connectionToggle');
            if (toggle.checked) {
                const serverAddress = document.getElementById('serverAddress')?.value || 'http://localhost:51023';
                octaneWebApp.connectToOctane(serverAddress);
            } else {
                octaneWebApp.disconnectFromOctane();
            }
        };

        // Debug console functions (using the DebugConsole class)
        window.toggleDebugConsole = () => {
            if (window.debugConsole) {
                window.debugConsole.toggle();
            }
        };

        window.clearDebugLog = () => {
            if (window.debugConsole) {
                window.debugConsole.clear();
            }
        };
        
    } catch (error) {
        console.error('Failed to start OctaneWeb:', error);
    }
});

// Cleanup on page unload
window.addEventListener('beforeunload', () => {
    if (octaneWebApp) {
        octaneWebApp.shutdown();
    }
});

// Export for module systems
if (typeof module !== 'undefined' && module.exports) {
    module.exports = OctaneWebApp;
}