/**
 * Cache Busting System
 * Ensures fresh code loads during development with visual indicators
 */

class CacheBuster {
    constructor() {
        this.version = this.generateVersion();
        this.loadedFiles = new Set();
        this.failedFiles = new Set();
        
        this.init();
    }
    
    generateVersion() {
        const now = new Date();
        const date = now.toISOString().slice(0, 10).replace(/-/g, '');
        const time = now.toTimeString().slice(0, 8).replace(/:/g, '');
        return `${date}-${time}`;
    }
    
    init() {
        // Add visual indicator to show cache busting is active
        this.addCacheBustingIndicator();
        
        // Monitor script loading
        this.monitorScriptLoading();
        
        // Log cache busting info
        console.info(`🔄 Cache Busting Active - Version: ${this.version}`);
    }
    
    addCacheBustingIndicator() {
        // Create visual indicator in the header
        const indicator = document.createElement('div');
        indicator.id = 'cache-bust-indicator';
        indicator.innerHTML = `
            <span class="cache-bust-icon">🔄</span>
            <span class="cache-bust-text">DEV v${this.version}</span>
        `;
        
        // Add styles
        const style = document.createElement('style');
        style.textContent = `
            #cache-bust-indicator {
                position: fixed;
                top: 10px;
                left: 10px;
                background: rgba(74, 222, 128, 0.9);
                color: #000;
                padding: 4px 8px;
                border-radius: 4px;
                font-size: 11px;
                font-family: monospace;
                z-index: 9999;
                display: flex;
                align-items: center;
                gap: 4px;
                box-shadow: 0 2px 8px rgba(0,0,0,0.3);
            }
            
            .cache-bust-icon {
                animation: spin 2s linear infinite;
            }
            
            @keyframes spin {
                from { transform: rotate(0deg); }
                to { transform: rotate(360deg); }
            }
            
            .cache-bust-text {
                font-weight: bold;
            }
            
            #cache-bust-indicator.error {
                background: rgba(255, 68, 68, 0.9);
                color: #fff;
            }
            
            #cache-bust-indicator.success {
                background: rgba(74, 222, 128, 0.9);
                animation: pulse 1s ease-in-out;
            }
            
            @keyframes pulse {
                0%, 100% { opacity: 1; }
                50% { opacity: 0.7; }
            }
        `;
        document.head.appendChild(style);
        
        // Add to page
        document.body.appendChild(indicator);
        
        // Auto-hide after 5 seconds
        setTimeout(() => {
            if (indicator.parentNode) {
                indicator.style.opacity = '0.3';
            }
        }, 5000);
    }
    
    monitorScriptLoading() {
        // Monitor all script tags
        const scripts = document.querySelectorAll('script[src]');
        
        scripts.forEach(script => {
            const src = script.getAttribute('src');
            
            script.addEventListener('load', () => {
                this.loadedFiles.add(src);
                console.info(`✅ Loaded: ${src}`);
                this.updateIndicator();
            });
            
            script.addEventListener('error', () => {
                this.failedFiles.add(src);
                console.error(`❌ Failed to load: ${src}`);
                this.updateIndicator();
            });
        });
    }
    
    updateIndicator() {
        const indicator = document.getElementById('cache-bust-indicator');
        if (!indicator) return;
        
        const totalScripts = document.querySelectorAll('script[src]').length;
        const loadedCount = this.loadedFiles.size;
        const failedCount = this.failedFiles.size;
        
        if (failedCount > 0) {
            indicator.className = 'error';
            indicator.innerHTML = `
                <span class="cache-bust-icon">❌</span>
                <span class="cache-bust-text">LOAD ERROR (${failedCount})</span>
            `;
        } else if (loadedCount === totalScripts) {
            indicator.className = 'success';
            indicator.innerHTML = `
                <span class="cache-bust-icon">✅</span>
                <span class="cache-bust-text">ALL LOADED v${this.version}</span>
            `;
        }
    }
    
    // Method to manually bust cache for a specific file
    bustFile(url) {
        const separator = url.includes('?') ? '&' : '?';
        return `${url}${separator}v=${this.version}&cb=${Date.now()}`;
    }
    
    // Method to reload all scripts with fresh cache busting
    reloadAllScripts() {
        console.warn('🔄 Reloading all scripts with fresh cache busting...');
        
        const scripts = document.querySelectorAll('script[src]');
        scripts.forEach(script => {
            const originalSrc = script.getAttribute('src');
            const newSrc = this.bustFile(originalSrc.split('?')[0]); // Remove existing params
            
            // Create new script element
            const newScript = document.createElement('script');
            newScript.src = newSrc;
            
            // Replace old script
            script.parentNode.insertBefore(newScript, script);
            script.remove();
            
            console.info(`🔄 Reloaded: ${newSrc}`);
        });
    }
}

// Initialize cache buster
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', () => {
        window.cacheBuster = new CacheBuster();
    });
} else {
    window.cacheBuster = new CacheBuster();
}