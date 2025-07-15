/**
 * OctaneWeb State Manager
 * Centralized state management for the application
 */

class StateManager {
    constructor(eventSystem) {
        this.eventSystem = eventSystem;
        
        // Application state
        this.state = {
            // Connection state
            connection: {
                isConnected: false,
                serverUrl: null,
                status: 'disconnected'
            },
            
            // Scene state
            scene: {
                objects: new Map(),
                hierarchy: [],
                selection: new Set(),
                cameras: new Map(),
                lights: new Map(),
                materials: new Map()
            },
            
            // Node graph state
            nodeGraph: {
                nodes: new Map(),
                connections: new Map(),
                selectedNodes: new Set(),
                viewport: { x: 0, y: 0, zoom: 1 }
            },
            
            // Render state
            render: {
                isRendering: false,
                progress: 0,
                samples: 0,
                renderTime: 0,
                resolution: { width: 1920, height: 1080 }
            },
            
            // UI state
            ui: {
                activePanel: null,
                selectedTool: null,
                showGrid: true,
                showGizmos: true
            }
        };
        
        // State change listeners
        this.listeners = new Map();
        
        // History for undo/redo
        this.history = [];
        this.historyIndex = -1;
        this.maxHistorySize = 50;
    }
    
    /**
     * Get current state or specific state path
     */
    getState(path = null) {
        if (!path) {
            return this.deepClone(this.state);
        }
        
        const keys = path.split('.');
        let current = this.state;
        
        for (const key of keys) {
            if (current && typeof current === 'object' && key in current) {
                current = current[key];
            } else {
                return undefined;
            }
        }
        
        return this.deepClone(current);
    }
    
    /**
     * Update state
     */
    setState(path, value, options = {}) {
        const { silent = false, addToHistory = true } = options;
        
        // Save current state to history if needed
        if (addToHistory && !silent) {
            this.saveToHistory();
        }
        
        // Update state
        const keys = path.split('.');
        let current = this.state;
        
        for (let i = 0; i < keys.length - 1; i++) {
            const key = keys[i];
            if (!(key in current) || typeof current[key] !== 'object') {
                current[key] = {};
            }
            current = current[key];
        }
        
        const lastKey = keys[keys.length - 1];
        const oldValue = current[lastKey];
        current[lastKey] = value;
        
        // Emit change event if not silent
        if (!silent) {
            this.emitStateChange(path, value, oldValue);
        }
    }
    
    /**
     * Update multiple state paths at once
     */
    updateState(updates, options = {}) {
        const { silent = false, addToHistory = true } = options;
        
        // Save current state to history if needed
        if (addToHistory && !silent) {
            this.saveToHistory();
        }
        
        // Apply all updates
        const changes = [];
        for (const [path, value] of Object.entries(updates)) {
            const keys = path.split('.');
            let current = this.state;
            
            for (let i = 0; i < keys.length - 1; i++) {
                const key = keys[i];
                if (!(key in current) || typeof current[key] !== 'object') {
                    current[key] = {};
                }
                current = current[key];
            }
            
            const lastKey = keys[keys.length - 1];
            const oldValue = current[lastKey];
            current[lastKey] = value;
            
            changes.push({ path, value, oldValue });
        }
        
        // Emit change events if not silent
        if (!silent) {
            changes.forEach(({ path, value, oldValue }) => {
                this.emitStateChange(path, value, oldValue);
            });
        }
    }
    
    /**
     * Subscribe to state changes
     */
    subscribe(path, callback) {
        if (!this.listeners.has(path)) {
            this.listeners.set(path, new Set());
        }
        
        this.listeners.get(path).add(callback);
        
        // Return unsubscribe function
        return () => {
            const pathListeners = this.listeners.get(path);
            if (pathListeners) {
                pathListeners.delete(callback);
                if (pathListeners.size === 0) {
                    this.listeners.delete(path);
                }
            }
        };
    }
    
    /**
     * Emit state change event
     */
    emitStateChange(path, newValue, oldValue) {
        // Emit to specific path listeners
        const pathListeners = this.listeners.get(path);
        if (pathListeners) {
            pathListeners.forEach(callback => {
                try {
                    callback(newValue, oldValue, path);
                } catch (error) {
                    console.error('State change listener error:', error);
                }
            });
        }
        
        // Emit to wildcard listeners
        const wildcardListeners = this.listeners.get('*');
        if (wildcardListeners) {
            wildcardListeners.forEach(callback => {
                try {
                    callback(newValue, oldValue, path);
                } catch (error) {
                    console.error('Wildcard state change listener error:', error);
                }
            });
        }
        
        // Emit through event system
        if (this.eventSystem) {
            this.eventSystem.emit('stateChange', { path, newValue, oldValue });
        }
    }
    
    /**
     * Save current state to history
     */
    saveToHistory() {
        // Remove any history after current index
        this.history = this.history.slice(0, this.historyIndex + 1);
        
        // Add current state to history
        this.history.push(this.deepClone(this.state));
        this.historyIndex++;
        
        // Limit history size
        if (this.history.length > this.maxHistorySize) {
            this.history.shift();
            this.historyIndex--;
        }
    }
    
    /**
     * Undo last state change
     */
    undo() {
        if (this.historyIndex > 0) {
            this.historyIndex--;
            this.state = this.deepClone(this.history[this.historyIndex]);
            this.emitStateChange('*', this.state, null);
            return true;
        }
        return false;
    }
    
    /**
     * Redo last undone state change
     */
    redo() {
        if (this.historyIndex < this.history.length - 1) {
            this.historyIndex++;
            this.state = this.deepClone(this.history[this.historyIndex]);
            this.emitStateChange('*', this.state, null);
            return true;
        }
        return false;
    }
    
    /**
     * Clear history
     */
    clearHistory() {
        this.history = [];
        this.historyIndex = -1;
    }
    
    /**
     * Deep clone object
     */
    deepClone(obj) {
        if (obj === null || typeof obj !== 'object') {
            return obj;
        }
        
        if (obj instanceof Date) {
            return new Date(obj.getTime());
        }
        
        if (obj instanceof Array) {
            return obj.map(item => this.deepClone(item));
        }
        
        if (obj instanceof Map) {
            const cloned = new Map();
            obj.forEach((value, key) => {
                cloned.set(key, this.deepClone(value));
            });
            return cloned;
        }
        
        if (obj instanceof Set) {
            const cloned = new Set();
            obj.forEach(value => {
                cloned.add(this.deepClone(value));
            });
            return cloned;
        }
        
        if (typeof obj === 'object') {
            const cloned = {};
            Object.keys(obj).forEach(key => {
                cloned[key] = this.deepClone(obj[key]);
            });
            return cloned;
        }
        
        return obj;
    }
    
    /**
     * Reset state to initial values
     */
    reset() {
        this.state = {
            connection: {
                isConnected: false,
                serverUrl: null,
                status: 'disconnected'
            },
            scene: {
                objects: new Map(),
                hierarchy: [],
                selection: new Set(),
                cameras: new Map(),
                lights: new Map(),
                materials: new Map()
            },
            nodeGraph: {
                nodes: new Map(),
                connections: new Map(),
                selectedNodes: new Set(),
                viewport: { x: 0, y: 0, zoom: 1 }
            },
            render: {
                isRendering: false,
                progress: 0,
                samples: 0,
                renderTime: 0,
                resolution: { width: 1920, height: 1080 }
            },
            ui: {
                activePanel: null,
                selectedTool: null,
                showGrid: true,
                showGizmos: true
            }
        };
        
        this.clearHistory();
        this.emitStateChange('*', this.state, null);
    }
    
    /**
     * Get state statistics
     */
    getStats() {
        return {
            historySize: this.history.length,
            historyIndex: this.historyIndex,
            listenerCount: Array.from(this.listeners.values()).reduce((sum, set) => sum + set.size, 0),
            sceneObjectCount: this.state.scene.objects.size,
            nodeCount: this.state.nodeGraph.nodes.size,
            connectionCount: this.state.nodeGraph.connections.size
        };
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = StateManager;
} else if (typeof window !== 'undefined') {
    window.StateManager = StateManager;
}