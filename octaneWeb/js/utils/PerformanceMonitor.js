/**
 * Performance Monitor for OctaneWeb
 * Tracks FPS, memory usage, API call performance, and system health
 */

class PerformanceMonitor {
    constructor() {
        this.isRunning = false;
        this.metrics = {
            fps: 0,
            frameTime: 0,
            memoryUsage: 0,
            apiCalls: {
                total: 0,
                successful: 0,
                failed: 0,
                averageResponseTime: 0
            },
            renderStats: {
                triangles: 0,
                drawCalls: 0,
                textureMemory: 0
            }
        };
        
        this.frameCount = 0;
        this.lastTime = performance.now();
        this.fpsHistory = [];
        this.apiCallHistory = [];
        this.maxHistoryLength = 60; // Keep 60 samples
        
        this.callbacks = {
            onUpdate: null,
            onAlert: null
        };
        
        // Performance thresholds
        this.thresholds = {
            lowFPS: 30,
            highMemory: 100 * 1024 * 1024, // 100MB
            slowAPI: 1000 // 1 second
        };
    }
    
    start() {
        if (this.isRunning) return;
        
        this.isRunning = true;
        this.lastTime = performance.now();
        this.frameCount = 0;
        
        // Start monitoring loops
        this.startFPSMonitoring();
        this.startMemoryMonitoring();
        
        console.log('📊 Performance Monitor started');
    }
    
    stop() {
        this.isRunning = false;
        console.log('📊 Performance Monitor stopped');
    }
    
    startFPSMonitoring() {
        const updateFPS = () => {
            if (!this.isRunning) return;
            
            const currentTime = performance.now();
            const deltaTime = currentTime - this.lastTime;
            
            this.frameCount++;
            
            // Update FPS every second
            if (deltaTime >= 1000) {
                this.metrics.fps = Math.round((this.frameCount * 1000) / deltaTime);
                this.metrics.frameTime = deltaTime / this.frameCount;
                
                // Add to history
                this.fpsHistory.push(this.metrics.fps);
                if (this.fpsHistory.length > this.maxHistoryLength) {
                    this.fpsHistory.shift();
                }
                
                // Check for performance issues
                if (this.metrics.fps < this.thresholds.lowFPS) {
                    this.triggerAlert('Low FPS detected', `FPS: ${this.metrics.fps}`);
                }
                
                this.frameCount = 0;
                this.lastTime = currentTime;
                
                this.updateDisplay();
            }
            
            requestAnimationFrame(updateFPS);
        };
        
        requestAnimationFrame(updateFPS);
    }
    
    startMemoryMonitoring() {
        const updateMemory = () => {
            if (!this.isRunning) return;
            
            if (performance.memory) {
                this.metrics.memoryUsage = performance.memory.usedJSHeapSize;
                
                // Check for memory issues
                if (this.metrics.memoryUsage > this.thresholds.highMemory) {
                    this.triggerAlert('High memory usage', `Memory: ${this.formatBytes(this.metrics.memoryUsage)}`);
                }
            }
            
            setTimeout(updateMemory, 5000); // Check every 5 seconds
        };
        
        setTimeout(updateMemory, 5000);
    }
    
    recordAPICall(endpoint, responseTime, success = true) {
        this.metrics.apiCalls.total++;
        
        if (success) {
            this.metrics.apiCalls.successful++;
        } else {
            this.metrics.apiCalls.failed++;
        }
        
        // Add to history for average calculation
        this.apiCallHistory.push(responseTime);
        if (this.apiCallHistory.length > this.maxHistoryLength) {
            this.apiCallHistory.shift();
        }
        
        // Calculate average response time
        this.metrics.apiCalls.averageResponseTime = 
            this.apiCallHistory.reduce((a, b) => a + b, 0) / this.apiCallHistory.length;
        
        // Check for slow API calls
        if (responseTime > this.thresholds.slowAPI) {
            this.triggerAlert('Slow API call', `${endpoint}: ${responseTime}ms`);
        }
        
        this.updateDisplay();
    }
    
    updateRenderStats(triangles, drawCalls, textureMemory) {
        this.metrics.renderStats.triangles = triangles;
        this.metrics.renderStats.drawCalls = drawCalls;
        this.metrics.renderStats.textureMemory = textureMemory;
        
        this.updateDisplay();
    }
    
    updateDisplay() {
        // Update FPS display in status bar
        const fpsElement = document.querySelector('.status-bar .fps-counter span:last-child');
        if (fpsElement) {
            fpsElement.textContent = this.metrics.fps.toString();
        }
        
        // Update memory display if available
        const memoryElement = document.getElementById('memory-usage');
        if (memoryElement) {
            memoryElement.textContent = this.formatBytes(this.metrics.memoryUsage);
        }
        
        // Trigger callback for external updates
        if (this.callbacks.onUpdate) {
            this.callbacks.onUpdate(this.metrics);
        }
    }
    
    triggerAlert(type, message) {
        console.warn(`⚠️ Performance Alert: ${type} - ${message}`);
        
        if (this.callbacks.onAlert) {
            this.callbacks.onAlert(type, message);
        }
        
        // Add to debug console if available
        if (window.debugConsole) {
            window.debugConsole.addLog('warning', [`⚠️ ${type}: ${message}`]);
        }
    }
    
    formatBytes(bytes) {
        if (bytes === 0) return '0 B';
        
        const k = 1024;
        const sizes = ['B', 'KB', 'MB', 'GB'];
        const i = Math.floor(Math.log(bytes) / Math.log(k));
        
        return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + ' ' + sizes[i];
    }
    
    getMetrics() {
        return {
            ...this.metrics,
            fpsHistory: [...this.fpsHistory],
            apiCallHistory: [...this.apiCallHistory]
        };
    }
    
    getHealthScore() {
        let score = 100;
        
        // FPS penalty
        if (this.metrics.fps < this.thresholds.lowFPS) {
            score -= (this.thresholds.lowFPS - this.metrics.fps) * 2;
        }
        
        // Memory penalty
        if (this.metrics.memoryUsage > this.thresholds.highMemory) {
            score -= 20;
        }
        
        // API failure penalty
        const failureRate = this.metrics.apiCalls.failed / Math.max(this.metrics.apiCalls.total, 1);
        score -= failureRate * 50;
        
        // Slow API penalty
        if (this.metrics.apiCalls.averageResponseTime > this.thresholds.slowAPI) {
            score -= 15;
        }
        
        return Math.max(0, Math.min(100, Math.round(score)));
    }
    
    generateReport() {
        const healthScore = this.getHealthScore();
        const avgFPS = this.fpsHistory.reduce((a, b) => a + b, 0) / Math.max(this.fpsHistory.length, 1);
        
        return {
            timestamp: new Date().toISOString(),
            healthScore,
            metrics: this.getMetrics(),
            averageFPS: Math.round(avgFPS),
            recommendations: this.getRecommendations()
        };
    }
    
    getRecommendations() {
        const recommendations = [];
        
        if (this.metrics.fps < this.thresholds.lowFPS) {
            recommendations.push('Consider reducing render quality or viewport size');
        }
        
        if (this.metrics.memoryUsage > this.thresholds.highMemory) {
            recommendations.push('High memory usage detected - consider refreshing the page');
        }
        
        if (this.metrics.apiCalls.averageResponseTime > this.thresholds.slowAPI) {
            recommendations.push('Slow API responses - check network connection');
        }
        
        const failureRate = this.metrics.apiCalls.failed / Math.max(this.metrics.apiCalls.total, 1);
        if (failureRate > 0.1) {
            recommendations.push('High API failure rate - check server connection');
        }
        
        return recommendations;
    }
    
    // Event handlers
    onUpdate(callback) {
        this.callbacks.onUpdate = callback;
    }
    
    onAlert(callback) {
        this.callbacks.onAlert = callback;
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = PerformanceMonitor;
} else {
    window.PerformanceMonitor = PerformanceMonitor;
}