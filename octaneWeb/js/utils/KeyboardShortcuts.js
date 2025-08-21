/**
 * Keyboard Shortcuts System for OctaneWeb
 * Professional hotkey system matching Octane Studio conventions
 */

class KeyboardShortcuts {
    constructor() {
        this.shortcuts = new Map();
        this.isEnabled = true;
        this.activeModifiers = new Set();
        
        // Initialize default shortcuts
        this.initializeDefaultShortcuts();
        
        // Bind event listeners
        this.bindEvents();
    }
    
    initializeDefaultShortcuts() {
        // Debug Console
        this.register('ctrl+d', () => {
            if (window.debugConsole) {
                window.debugConsole.toggle();
            }
        }, 'Toggle Debug Console');
       
        // Connection
        this.register('ctrl+shift+c', () => {
            const toggle = document.getElementById('connectionToggle');
            if (toggle) {
                toggle.click();
            }
        }, 'Toggle Connection');
        
        // Scene Navigation
        this.register('f', () => {
            // Focus on selected object in scene outliner
            this.focusSelectedObject();
        }, 'Focus Selected Object');
        
        this.register('a', () => {
            // Select all in current context
            this.selectAll();
        }, 'Select All');
        
        // Node Graph
        this.register('tab', (e) => {
            e.preventDefault();
            // Open node creation menu at cursor
            this.openNodeCreationMenu();
        }, 'Create Node');
        
        this.register('delete', () => {
            // Delete selected nodes
            this.deleteSelectedNodes();
        }, 'Delete Selected');
        
        this.register('ctrl+z', () => {
            // Undo last action
            this.undo();
        }, 'Undo');
        
        this.register('ctrl+y', () => {
            // Redo last action
            this.redo();
        }, 'Redo');
        
        // Viewport Controls
        this.register('space', (e) => {
            e.preventDefault();
            // Toggle render/pause
            this.toggleRender();
        }, 'Toggle Render');
        
        this.register('r', () => {
            // Reset camera
            this.resetCamera();
        }, 'Reset Camera');
        
        // Panel Management
        this.register('ctrl+1', () => {
            this.togglePanel('scene-outliner');
        }, 'Toggle Scene Outliner');
        
        this.register('ctrl+2', () => {
            this.togglePanel('render-viewport');
        }, 'Toggle Render Viewport');
        
        this.register('ctrl+3', () => {
            this.togglePanel('node-graph');
        }, 'Toggle Node Graph');
        
        this.register('ctrl+4', () => {
            this.togglePanel('node-inspector');
        }, 'Toggle Node Inspector');
        
        // Help
        this.register('f1', (e) => {
            e.preventDefault();
            this.showHelp();
        }, 'Show Help');
    }
    
    register(shortcut, callback, description = '') {
        const key = this.normalizeShortcut(shortcut);
        this.shortcuts.set(key, {
            callback,
            description,
            originalShortcut: shortcut
        });
    }
    
    unregister(shortcut) {
        const key = this.normalizeShortcut(shortcut);
        this.shortcuts.delete(key);
    }
    
    normalizeShortcut(shortcut) {
        return shortcut.toLowerCase()
            .replace(/\s+/g, '')
            .split('+')
            .sort()
            .join('+');
    }
    
    bindEvents() {
        document.addEventListener('keydown', (e) => {
            if (!this.isEnabled) return;
            
            // Skip if typing in input fields
            if (this.isTypingInInput(e.target)) return;
            
            const shortcut = this.getShortcutFromEvent(e);
            const command = this.shortcuts.get(shortcut);
            
            if (command) {
                e.preventDefault();
                command.callback(e);
            }
        });
        
        document.addEventListener('keyup', (e) => {
            this.activeModifiers.clear();
        });
    }
    
    getShortcutFromEvent(e) {
        const parts = [];
        
        if (e.ctrlKey || e.metaKey) parts.push('ctrl');
        if (e.altKey) parts.push('alt');
        if (e.shiftKey) parts.push('shift');
        
        const key = e.key.toLowerCase();
        if (key !== 'control' && key !== 'alt' && key !== 'shift' && key !== 'meta') {
            parts.push(key);
        }
        
        return parts.sort().join('+');
    }
    
    isTypingInInput(element) {
        const tagName = element.tagName.toLowerCase();
        const inputTypes = ['input', 'textarea', 'select'];
        const contentEditable = element.contentEditable === 'true';
        
        return inputTypes.includes(tagName) || contentEditable;
    }
    
    isOpenHandsEnvironment() {
        // Detect OpenHands/automated environment through multiple indicators
        const indicators = [
            // User agent patterns
            navigator.userAgent.includes('HeadlessChrome'),
            navigator.userAgent.includes('Chrome/') && navigator.webdriver === true,
            
            // Window properties that indicate automation
            window.navigator.webdriver === true,
            window.chrome && window.chrome.runtime && window.chrome.runtime.onConnect,
            
            // Viewport size patterns (OpenHands typically uses specific sizes)
            (window.innerWidth === 1280 && window.innerHeight === 720) ||
            (window.innerWidth === 1920 && window.innerHeight === 1080),
            
            // Check for automation-specific properties
            'webdriver' in window,
            '_phantom' in window,
            'callPhantom' in window,
            
            // Check for specific OpenHands environment variables in URL or referrer
            window.location.hostname === 'localhost' && 
            (window.location.port === '50405' || window.location.port === '56753'),
            
            // Check for absence of typical browser extensions/plugins
            navigator.plugins.length === 0,
            
            // Check for specific automation frameworks
            window.document.documentElement.getAttribute('webdriver') !== null,
            window.document.documentElement.getAttribute('selenium') !== null
        ];
        
        // If any automation indicator is present, assume OpenHands environment
        const automationDetected = indicators.some(indicator => indicator);
        
        // Additional check: look for specific OpenHands patterns
        const openHandsPatterns = [
            // Check if we're running on specific localhost ports used by OpenHands
    //        window.location.hostname === 'localhost' && 
    //        ['50405', '56753'].includes(window.location.port),
            
            // Check for specific user agent patterns
    //        navigator.userAgent.includes('Chrome') && !navigator.userAgent.includes('Edge'),
            
            // Check for missing browser features that are typically present in real browsers
            !window.external || !window.external.AddSearchProvider
        ];
        
        const openHandsDetected = openHandsPatterns.some(pattern => pattern);
        
        // Log detection for debugging
        if (automationDetected || openHandsDetected) {
            console.log('🤖 OpenHands environment detected:', {
                automation: automationDetected,
                openHands: openHandsDetected,
                userAgent: navigator.userAgent,
                webdriver: navigator.webdriver,
                viewport: `${window.innerWidth}x${window.innerHeight}`,
                hostname: window.location.hostname,
                port: window.location.port
            });
        }
        
        return automationDetected || openHandsDetected;
    }
    
    // Action implementations
    focusSelectedObject() {
        // Implementation for focusing selected object
        console.log('Focus selected object');
    }
    
    selectAll() {
        // Implementation for select all
        console.log('Select all');
    }
    
    openNodeCreationMenu() {
        // Trigger right-click menu at center of node graph
        const nodeGraph = document.getElementById('node-graph');
        if (nodeGraph && window.nodeGraphEditor) {
            const rect = nodeGraph.getBoundingClientRect();
            const centerX = rect.width / 2;
            const centerY = rect.height / 2;
            
            // Simulate right-click at center
            const event = new MouseEvent('contextmenu', {
                clientX: rect.left + centerX,
                clientY: rect.top + centerY,
                bubbles: true
            });
            nodeGraph.dispatchEvent(event);
        }
    }
    
    deleteSelectedNodes() {
        if (window.nodeGraphEditor) {
            window.nodeGraphEditor.deleteSelectedNodes();
        }
    }
    
    undo() {
        console.log('Undo action');
    }
    
    redo() {
        console.log('Redo action');
    }
    
    toggleRender() {
        const playButton = document.querySelector('.control-btn[title="Play/Pause"]');
        if (playButton) {
            playButton.click();
        }
    }
    
    resetCamera() {
        console.log('Reset camera');
    }
    
    togglePanel(panelId) {
        const panel = document.getElementById(panelId);
        if (panel) {
            panel.style.display = panel.style.display === 'none' ? '' : 'none';
        }
    }
    
    showHelp() {
        this.displayShortcutHelp();
    }
    
    displayShortcutHelp() {
        const shortcuts = Array.from(this.shortcuts.entries())
            .map(([key, command]) => `${command.originalShortcut.toUpperCase()}: ${command.description}`)
            .join('\n');
        
        const helpText = `
🎮 OCTANEWEB KEYBOARD SHORTCUTS:

${shortcuts}

Press F1 to show/hide this help.
Press Ctrl+D to toggle debug console.
        `;
        
        if (window.debugConsole) {
            window.debugConsole.addLog('info', [helpText]);
            window.debugConsole.show();
        } else {
            alert(helpText);
        }
    }
    
    enable() {
        this.isEnabled = true;
    }
    
    disable() {
        this.isEnabled = false;
    }
    
    getShortcuts() {
        return Array.from(this.shortcuts.entries()).map(([key, command]) => ({
            shortcut: command.originalShortcut,
            description: command.description
        }));
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = KeyboardShortcuts;
} else {
    window.KeyboardShortcuts = KeyboardShortcuts;
}

// Initialize keyboard shortcuts when DOM is ready
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', () => {
        window.keyboardShortcuts = new KeyboardShortcuts();
    });
} else {
    window.keyboardShortcuts = new KeyboardShortcuts();
}