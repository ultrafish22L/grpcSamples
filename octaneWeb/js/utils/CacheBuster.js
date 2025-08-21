/**
 * Cache Busting System
 * Ensures fresh code loads during development with visual indicators
 */

class CacheBuster {
    constructor() {
        this.version = this.generateVersion();
        this.loadedFiles = new Set();
        this.failedFiles = new Set();
        
        // Log cache busting info
        console.info(`CacheBuster`);

        this.init();
    }
    
    generateVersion() {
        const now = new Date();
        const timestamp = now.getTime();
        const date = now.toISOString().slice(0, 10).replace(/-/g, '');
        const time = now.toTimeString().slice(0, 8).replace(/:/g, '');
        return `${date}-${time}-${timestamp}`;
    }
    
    init() {
        // Add visual indicator to show cache busting is active
        this.addCacheBustingIndicator();
        
        // Monitor script loading
        this.monitorScriptLoading();
        
        // Log cache busting info
        console.info(`Cache Busting Active - Version: ${this.version}`);
    }
    
    addCacheBustingIndicator() {
        // Log cache busting info
        console.info(`🔄addCacheBustingIndicator: ${document.URL}`);

        // Create visual indicator for footer center
        const indicator = document.createElement('span');
        indicator.id = 'cache-bust-indicator';
        indicator.className = 'status-item';
        indicator.innerHTML = `
            <span class="cache-bust-icon">🔄</span>
            <span class="cache-bust-text">DEV v${this.version}</span>
        `;
        
        // Add styles
        const style = document.createElement('style');
        style.textContent = `
            #cache-bust-indicator {
                display: flex;
                align-items: center;
                gap: 4px;
                font-size: 10px;
                font-family: monospace;
                color: var(--octane-text-muted);
                opacity: 0.7;
            }
            
            .cache-bust-icon {
                animation: spin 2s linear infinite;
                font-size: 10px;
            }
            
            @keyframes spin {
                from { transform: rotate(0deg); }
                to { transform: rotate(360deg); }
            }
            
            .cache-bust-text {
                font-weight: normal;
                font-size: 10px;
            }
            
            #cache-bust-indicator.error .cache-bust-icon {
                color: var(--octane-accent-red);
                animation: none;
            }
            
            #cache-bust-indicator.success .cache-bust-icon {
                color: var(--octane-accent-green);
                animation: pulse 1s ease-in-out;
            }
            
            @keyframes pulse {
                0%, 100% { opacity: 1; }
                50% { opacity: 0.7; }
            }
        `;
        document.head.appendChild(style);
        
        // Add to footer center
        const statusCenter = document.getElementById('status-center');
        if (statusCenter) {
            statusCenter.appendChild(indicator);
        } else {
            // Fallback to body if status-center not found
            document.body.appendChild(indicator);
        }
        
        // Keep visible (no auto-hide for footer placement)
    }
    
    monitorScriptLoading() {
        // Monitor all script tags
        const scripts = document.querySelectorAll('script[src]');
        
        scripts.forEach(script => {
            const src = script.getAttribute('src');
            
            script.addEventListener('load', () => {
                this.loadedFiles.add(src);
                console.info(`Loaded: ${src}`);
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
        
        // Log cache busting info
        console.info(`🔄addCacheBustingIndicator: ${document.URL}`);

        const totalScripts = document.querySelectorAll('script[src]').length;
        const loadedCount = this.loadedFiles.size;
        const failedCount = this.failedFiles.size;
        
        if (failedCount > 0) {
            indicator.className = 'status-item error';
            indicator.innerHTML = `
                <span class="cache-bust-icon">❌</span>
                <span class="cache-bust-text">LOAD ERROR (${failedCount})</span>
            `;
        } else if (loadedCount === totalScripts) {
            indicator.className = 'status-item success';
            indicator.innerHTML = `
                <span class="cache-bust-icon">✅</span>
                <span class="cache-bust-text">LOADED v${this.version}</span>
            `;
        }
    }
    
    // Method to manually bust cache for a specific file
    bustFile(url) {
        // Log cache busting info
        console.info(`🔄addCacheBustingIndicator: ${url}`);

        const separator = url.includes('?') ? '&' : '?';
        return `${url}${separator}v=${this.version}&cb=${Date.now()}`;
    }
    
    // Method to reload all scripts with fresh cache busting
    reloadAllScripts() {
        console.warn('Reloading all scripts with fresh cache busting...');
        
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
            
            console.info(`Reloaded: ${newSrc}`);
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