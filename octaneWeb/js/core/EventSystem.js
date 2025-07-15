/**
 * OctaneWeb Event System
 * Centralized event management for the application
 */

class EventSystem {
    constructor() {
        this.listeners = new Map();
        this.onceListeners = new Map();
        this.eventQueue = [];
        this.isProcessing = false;
        this.maxQueueSize = 1000;
        
        // Performance monitoring
        this.stats = {
            eventsEmitted: 0,
            eventsProcessed: 0,
            averageProcessingTime: 0,
            lastProcessingTime: 0
        };
    }
    
    /**
     * Add event listener
     */
    on(event, callback, options = {}) {
        const { priority = 0, once = false } = options;
        
        if (once) {
            return this.once(event, callback, { priority });
        }
        
        if (!this.listeners.has(event)) {
            this.listeners.set(event, []);
        }
        
        const listener = { callback, priority, id: this.generateId() };
        const listeners = this.listeners.get(event);
        
        // Insert based on priority (higher priority first)
        let inserted = false;
        for (let i = 0; i < listeners.length; i++) {
            if (listeners[i].priority < priority) {
                listeners.splice(i, 0, listener);
                inserted = true;
                break;
            }
        }
        
        if (!inserted) {
            listeners.push(listener);
        }
        
        // Return unsubscribe function
        return () => this.off(event, listener.id);
    }
    
    /**
     * Add one-time event listener
     */
    once(event, callback, options = {}) {
        const { priority = 0 } = options;
        
        if (!this.onceListeners.has(event)) {
            this.onceListeners.set(event, []);
        }
        
        const listener = { callback, priority, id: this.generateId() };
        const listeners = this.onceListeners.get(event);
        
        // Insert based on priority (higher priority first)
        let inserted = false;
        for (let i = 0; i < listeners.length; i++) {
            if (listeners[i].priority < priority) {
                listeners.splice(i, 0, listener);
                inserted = true;
                break;
            }
        }
        
        if (!inserted) {
            listeners.push(listener);
        }
        
        // Return unsubscribe function
        return () => this.offOnce(event, listener.id);
    }
    
    /**
     * Remove event listener
     */
    off(event, callbackOrId) {
        const listeners = this.listeners.get(event);
        if (!listeners) return false;
        
        let index = -1;
        if (typeof callbackOrId === 'string') {
            // Remove by ID
            index = listeners.findIndex(l => l.id === callbackOrId);
        } else {
            // Remove by callback function
            index = listeners.findIndex(l => l.callback === callbackOrId);
        }
        
        if (index !== -1) {
            listeners.splice(index, 1);
            if (listeners.length === 0) {
                this.listeners.delete(event);
            }
            return true;
        }
        
        return false;
    }
    
    /**
     * Remove one-time event listener
     */
    offOnce(event, callbackOrId) {
        const listeners = this.onceListeners.get(event);
        if (!listeners) return false;
        
        let index = -1;
        if (typeof callbackOrId === 'string') {
            // Remove by ID
            index = listeners.findIndex(l => l.id === callbackOrId);
        } else {
            // Remove by callback function
            index = listeners.findIndex(l => l.callback === callbackOrId);
        }
        
        if (index !== -1) {
            listeners.splice(index, 1);
            if (listeners.length === 0) {
                this.onceListeners.delete(event);
            }
            return true;
        }
        
        return false;
    }
    
    /**
     * Remove all listeners for an event
     */
    removeAllListeners(event) {
        if (event) {
            this.listeners.delete(event);
            this.onceListeners.delete(event);
        } else {
            this.listeners.clear();
            this.onceListeners.clear();
        }
    }
    
    /**
     * Emit event
     */
    emit(event, data = null, options = {}) {
        const { async = false, delay = 0 } = options;
        
        this.stats.eventsEmitted++;
        
        const eventData = {
            event,
            data,
            timestamp: Date.now(),
            async,
            delay
        };
        
        if (async || delay > 0) {
            // Queue for async processing
            this.queueEvent(eventData);
        } else {
            // Process immediately
            this.processEvent(eventData);
        }
    }
    
    /**
     * Queue event for async processing
     */
    queueEvent(eventData) {
        if (this.eventQueue.length >= this.maxQueueSize) {
            console.warn('Event queue is full, dropping oldest event');
            this.eventQueue.shift();
        }
        
        this.eventQueue.push(eventData);
        
        if (!this.isProcessing) {
            this.processQueue();
        }
    }
    
    /**
     * Process event queue
     */
    async processQueue() {
        if (this.isProcessing) return;
        
        this.isProcessing = true;
        
        while (this.eventQueue.length > 0) {
            const eventData = this.eventQueue.shift();
            
            if (eventData.delay > 0) {
                await this.delay(eventData.delay);
            }
            
            this.processEvent(eventData);
        }
        
        this.isProcessing = false;
    }
    
    /**
     * Process individual event
     */
    processEvent(eventData) {
        const startTime = performance.now();
        
        try {
            // Process regular listeners
            const listeners = this.listeners.get(eventData.event);
            if (listeners) {
                listeners.forEach(listener => {
                    try {
                        listener.callback(eventData.data, eventData);
                    } catch (error) {
                        console.error(`Event listener error for '${eventData.event}':`, error);
                    }
                });
            }
            
            // Process one-time listeners
            const onceListeners = this.onceListeners.get(eventData.event);
            if (onceListeners) {
                // Create copy since we'll be modifying the array
                const listenersToCall = [...onceListeners];
                this.onceListeners.delete(eventData.event);
                
                listenersToCall.forEach(listener => {
                    try {
                        listener.callback(eventData.data, eventData);
                    } catch (error) {
                        console.error(`One-time event listener error for '${eventData.event}':`, error);
                    }
                });
            }
            
            // Process wildcard listeners
            const wildcardListeners = this.listeners.get('*');
            if (wildcardListeners) {
                wildcardListeners.forEach(listener => {
                    try {
                        listener.callback(eventData.data, eventData);
                    } catch (error) {
                        console.error(`Wildcard event listener error:`, error);
                    }
                });
            }
            
        } finally {
            const endTime = performance.now();
            const processingTime = endTime - startTime;
            
            this.stats.eventsProcessed++;
            this.stats.lastProcessingTime = processingTime;
            this.stats.averageProcessingTime = 
                (this.stats.averageProcessingTime * (this.stats.eventsProcessed - 1) + processingTime) / 
                this.stats.eventsProcessed;
        }
    }
    
    /**
     * Wait for event
     */
    waitFor(event, timeout = 5000) {
        return new Promise((resolve, reject) => {
            let timeoutId = null;
            
            const cleanup = this.once(event, (data) => {
                if (timeoutId) clearTimeout(timeoutId);
                resolve(data);
            });
            
            if (timeout > 0) {
                timeoutId = setTimeout(() => {
                    cleanup();
                    reject(new Error(`Timeout waiting for event '${event}'`));
                }, timeout);
            }
        });
    }
    
    /**
     * Check if event has listeners
     */
    hasListeners(event) {
        const regularListeners = this.listeners.get(event);
        const onceListeners = this.onceListeners.get(event);
        
        return (regularListeners && regularListeners.length > 0) || 
               (onceListeners && onceListeners.length > 0);
    }
    
    /**
     * Get listener count for event
     */
    getListenerCount(event) {
        const regularCount = this.listeners.get(event)?.length || 0;
        const onceCount = this.onceListeners.get(event)?.length || 0;
        return regularCount + onceCount;
    }
    
    /**
     * Get all events with listeners
     */
    getEvents() {
        const events = new Set();
        
        this.listeners.forEach((_, event) => events.add(event));
        this.onceListeners.forEach((_, event) => events.add(event));
        
        return Array.from(events);
    }
    
    /**
     * Generate unique ID
     */
    generateId() {
        return `listener_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
    }
    
    /**
     * Delay utility
     */
    delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
    
    /**
     * Get event system statistics
     */
    getStats() {
        return {
            ...this.stats,
            totalListeners: Array.from(this.listeners.values()).reduce((sum, arr) => sum + arr.length, 0) +
                           Array.from(this.onceListeners.values()).reduce((sum, arr) => sum + arr.length, 0),
            queueSize: this.eventQueue.length,
            isProcessing: this.isProcessing,
            eventTypes: this.getEvents().length
        };
    }
    
    /**
     * Clear all listeners and reset
     */
    reset() {
        this.listeners.clear();
        this.onceListeners.clear();
        this.eventQueue = [];
        this.isProcessing = false;
        
        this.stats = {
            eventsEmitted: 0,
            eventsProcessed: 0,
            averageProcessingTime: 0,
            lastProcessingTime: 0
        };
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = EventSystem;
} else if (typeof window !== 'undefined') {
    window.EventSystem = EventSystem;
}