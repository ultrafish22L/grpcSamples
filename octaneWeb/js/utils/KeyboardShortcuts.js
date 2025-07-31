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
        
        // F12 Debug Console (OpenHands environment detection)
        this.register('f12', (e) => {
            if (this.isOpenHandsEnvironment()) {
                // In OpenHands environment, F12 opens our debug console
                e.preventDefault();
                if (window.debugConsole) {
                    window.debugConsole.toggle();
                    window.debugConsole.addLog('info', ['🤖 F12 detected in OpenHands environment - opening debug console']);
                }
            }
            // In regular browser, let F12 work normally (don't preventDefault)
        }, 'F12 Debug Console (OpenHands)');
        
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
                
                // Log shortcut usage for debugging
                if (window.debugConsole) {
                    window.debugConsole.addLog('info', [`⌨️ Shortcut: ${command.originalShortcut} - ${command.description}`]);
                }
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
        // Detect OpenHands/automated environment through SPECIFIC indicators only
        // Be more conservative to avoid false positives on regular Windows browsers
        
        const strongIndicators = [
            // Definitive automation indicators
            navigator.userAgent.includes('HeadlessChrome'),
            window.navigator.webdriver === true,
            'webdriver' in window,
            '_phantom' in window,
            'callPhantom' in window,
            window.document.documentElement.getAttribute('webdriver') !== null,
            window.document.documentElement.getAttribute('selenium') !== null
        ];
        
        // Strong automation detection
        const definiteAutomation = strongIndicators.some(indicator => indicator);
        
        // OpenHands-specific patterns (only if we're on the specific ports)
        const openHandsSpecific = window.location.hostname === 'localhost' && 
            ['50405', '56753'].includes(window.location.port) &&
            // Additional confirmation: check for very specific OpenHands patterns
            (navigator.plugins.length === 0 || // Headless browsers typically have no plugins
             navigator.userAgent.includes('Linux')); // OpenHands typically runs on Linux
        
        // Log detection for debugging
        if (isOpenHands) {
            console.log('🤖 OpenHands environment detected:', {
                definiteAutomation,
                openHandsSpecific,
                userAgent: navigator.userAgent,
                webdriver: navigator.webdriver,
                viewport: `${window.innerWidth}x${window.innerHeight}`,
                hostname: window.location.hostname,
                port: window.location.port,
                plugins: navigator.plugins.length
            });
        }
        
        return isOpenHands;
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