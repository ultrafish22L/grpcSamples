/**
 * OctaneWeb Component System
 * Base component architecture for UI elements
 */

class OctaneComponent {
    constructor(element, client, stateManager, eventSystem) {
        this.element = element;
        this.client = client;
        this.stateManager = stateManager;
        this.eventSystem = eventSystem || (stateManager && stateManager.eventSystem);
        this.isInitialized = false;
        this.eventListeners = [];
        
        // Unique component ID
        this.id = this.generateId();
        
        // Component state
        this.state = {};
        
        // Bind methods
        this.handleResize = this.handleResize.bind(this);
        this.handleDestroy = this.handleDestroy.bind(this);
    }
    
    /**
     * Initialize the component
     */
    async initialize() {
        if (this.isInitialized) return;
        
        try {
            await this.onInitialize();
            this.setupEventListeners();
            this.isInitialized = true;
            console.log(`Component ${this.constructor.name} initialized`);
        } catch (error) {
            console.error(`❌ Failed to initialize component ${this.constructor.name}:`, error);
            throw error;
        }
    }
    
    /**
     * Override in subclasses for initialization logic
     */
    async onInitialize() {
        // Override in subclasses
    }
    
    /**
     * Setup event listeners
     */
    setupEventListeners() {
        // Override in subclasses
    }
    
    /**
     * Add event listener with automatic cleanup
     */
    addEventListener(target, event, handler, options = {}) {
        target.addEventListener(event, handler, options);
        this.eventListeners.push({ target, event, handler, options });
    }
    
    /**
     * Update component state
     */
    setState(newState) {
        this.state = { ...this.state, ...newState };
        this.onStateChange(this.state);
    }
    
    /**
     * Override in subclasses for state change handling
     */
    onStateChange(state) {
        // Override in subclasses
    }
    
    /**
     * Handle resize events
     */
    handleResize() {
        // Override in subclasses
    }
    
    /**
     * Render the component
     */
    render() {
        // Override in subclasses
    }
    
    /**
     * Generate unique component ID
     */
    generateId() {
        return `component_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
    }
    
    /**
     * Cleanup and destroy component
     */
    destroy() {
        this.handleDestroy();
        
        // Remove all event listeners
        this.eventListeners.forEach(({ target, event, handler, options }) => {
            target.removeEventListener(event, handler, options);
        });
        this.eventListeners = [];
        
        // Clear element
        if (this.element) {
            this.element.innerHTML = '';
        }
        
        this.isInitialized = false;
        console.log(`Component ${this.constructor.name} destroyed`);
    }
    
    /**
     * Override in subclasses for cleanup logic
     */
    handleDestroy() {
        // Override in subclasses
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { OctaneComponent };
} else if (typeof window !== 'undefined') {
    window.OctaneComponent = OctaneComponent;
}