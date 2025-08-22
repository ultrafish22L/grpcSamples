/**
 * Layout Manager
 * Handles resizable panels and responsive layout
 */

class LayoutManager {
    constructor() {
        this.panels = new Map();
        this.splitters = new Map();
        this.isDragging = false;
        this.currentSplitter = null;
        this.startPos = { x: 0, y: 0 };
        this.startSizes = {};
        
        // Bind methods
        this.handleMouseMove = this.handleMouseMove.bind(this);
        this.handleMouseUp = this.handleMouseUp.bind(this);
        
        this.initialize();
    }
    
    initialize() {
        this.setupPanels('.panel');
        this.setupPanels('.panel-horz');
        this.setupSplitters();
        this.setupEventListeners();
        this.handleResize();
    }
    
    setupPanels(classname) {
        const panelElements = document.querySelectorAll(classname);
        
        panelElements.forEach(panel => {
            const panelId = panel.id || this.generateId();
            panel.id = panelId;
            
            this.panels.set(panelId, {
                element: panel,
                minWidth: parseInt(panel.dataset.minWidth) || 150,
                maxWidth: parseInt(panel.dataset.maxWidth) || 500,
                defaultWidth: parseInt(panel.dataset.defaultWidth) || 200,
                minHeight: parseInt(panel.dataset.minHeight) || 150,
                maxHeight: parseInt(panel.dataset.maxHeight) || 600,
                defaultHeight: parseInt(panel.dataset.defaultHeight) || 300,
                isCollapsed: panel.classList.contains('collapsed')
            });
        });
    }
    
    setupSplitters() {
        // Create splitters between panels
        const leftPanel = document.querySelector('.left-panel');
        const rightPanel = document.querySelector('.right-panel');
        const bottomPanel = document.querySelector('.bottom-panel');
        
        if (leftPanel) {
            this.createSplitter('left-splitter', leftPanel, 'vertical');
        }
        
        if (rightPanel) {
            this.createSplitter('right-splitter', rightPanel, 'vertical');
        }
        
        if (bottomPanel) {
            this.createSplitter('bottom-splitter', bottomPanel, 'horizontal');
        }
    }
    
    createSplitter(id, panel, orientation) {
        console.log(`⚠️ createSplitter: "${id}" orient: ${orientation}`);

        const splitter = document.createElement('div');
        splitter.id = id;
        splitter.className = `panel-splitter ${orientation}`;
        splitter.dataset.panel = panel.id;
        splitter.dataset.orientation = orientation;
        
        // For bottom panel, position splitter between center and bottom areas
        if (id === 'bottom-splitter') {
            // Add splitter to the app-layout container, positioned above the bottom panel
            const appLayout = document.querySelector('.app-layout');
            if (appLayout) {
                appLayout.appendChild(splitter);
                // Position it at the border between center and bottom panels
                splitter.style.gridColumn = '2'; // Only span the center column
                splitter.style.gridRow = '1'; // Position at the end of first row
                splitter.style.alignSelf = 'end'; // Align to bottom of first row
                splitter.style.zIndex = '1000'; // Ensure it's above other content
            }
        } else {
            // For left and right panels, add splitter to the panel itself
            panel.appendChild(splitter);
        }
        
        this.splitters.set(id, {
            element: splitter,
            panel: panel,
            orientation: orientation
        });
        
        // Add event listeners
        splitter.addEventListener('mousedown', this.handleSplitterMouseDown.bind(this));
    }
    
    setupEventListeners() {
        // Global mouse events for dragging
        document.addEventListener('mousemove', this.handleMouseMove);
        document.addEventListener('mouseup', this.handleMouseUp);
        
        // Window resize
        window.addEventListener('resize', this.handleResize.bind(this));
        
        // Panel collapse/expand buttons
        const collapseButtons = document.querySelectorAll('.panel-btn[title*="Collapse"], .panel-btn[title*="Expand"]');
        collapseButtons.forEach(button => {
            button.addEventListener('click', (e) => {
                const panel = button.closest('.panel');
                if (panel) {
                    this.togglePanel(panel.id);
                }
            });
        });
    }
    
    handleSplitterMouseDown(e) {
        e.preventDefault();
        
        this.isDragging = true;
        this.currentSplitter = e.target;
        this.startPos = { x: e.clientX, y: e.clientY };
        
        const splitterData = this.splitters.get(this.currentSplitter.id);
        const panelData = this.panels.get(splitterData.panel.id);
        
        this.startSizes = {
            width: splitterData.panel.offsetWidth,
            height: splitterData.panel.offsetHeight
        };
        
        // Add dragging class
        this.currentSplitter.classList.add('dragging');
        document.body.classList.add('resizing');
        
        // Prevent text selection
        document.body.style.userSelect = 'none';
    }
    
    handleMouseMove(e) {
        if (!this.isDragging || !this.currentSplitter) return;
        
        e.preventDefault();
        
        const splitterData = this.splitters.get(this.currentSplitter.id);
        const panelData = this.panels.get(splitterData.panel.id);
        
        if (splitterData.orientation === 'vertical') {
            const deltaX = e.clientX - this.startPos.x;
            let newWidth;
            
            // For right panel, invert the delta (drag left = smaller, drag right = larger)
            if (this.currentSplitter.id === 'right-splitter') {
                newWidth = this.startSizes.width - deltaX;
            } else {
                // For left panel, normal behavior (drag right = larger, drag left = smaller)
                newWidth = this.startSizes.width + deltaX;
            }
            
            // Apply constraints
            newWidth = Math.max(panelData.minWidth, Math.min(panelData.maxWidth, newWidth));
            
            // Update panel width
            splitterData.panel.style.width = `${newWidth}px`;
            
            // Update grid template if needed
            this.updateGridTemplate();
        } else if (splitterData.orientation === 'horizontal') {
            const deltaY = this.startPos.y - e.clientY; // Inverted for bottom panel
            let newHeight = this.startSizes.height + deltaY;
            
            // Apply height constraints
            newHeight = Math.max(panelData.minHeight, Math.min(panelData.maxHeight, newHeight));
            
            // Update panel height
            splitterData.panel.style.height = `${newHeight}px`;
            
            // Update grid template if needed
            this.updateGridTemplate();
        }
    }
    
    handleMouseUp(e) {
        if (!this.isDragging) return;
        
        this.isDragging = false;
        
        if (this.currentSplitter) {
            this.currentSplitter.classList.remove('dragging');
            this.currentSplitter = null;
        }
        
        document.body.classList.remove('resizing');
        document.body.style.userSelect = '';
        
        // Save panel sizes to localStorage
        this.savePanelSizes();
    }
    
    updateGridTemplate() {
        const appLayout = document.querySelector('.app-layout');
        if (!appLayout) return;
        
        const leftPanel = document.querySelector('.left-panel');
        const rightPanel = document.querySelector('.right-panel');
        const bottomPanel = document.querySelector('.bottom-panel');
        
/*
         --splitter-size: 4px;  
    --left-panel-width: 160px;
    --left-panel-min-width: 160px; 
    --right-panel-width: 260px;   
    --right-panel-min-width: 200px;
    --bottom-panel-height: 300px; 
    --bottom-panel-min-height: 200px;
*/
        let leftWidth = '220px';
        let rightWidth = '260px'; 
        let bottomHeight = '300px'; 

        if (leftPanel) {
            const panelData = this.panels.get(leftPanel.id);
            if (panelData) {
                if (panelData.isCollapsed) {
                    leftWidth = '24px';
                } else {
                    // Only use offsetWidth if it's been calculated (> 0), otherwise use default
                    const calculatedWidth = leftPanel.offsetWidth;
                    leftWidth = calculatedWidth > 0 ? `${calculatedWidth}px` : '220px';
                }
            }
        }
        
        if (rightPanel) {
            const panelData = this.panels.get(rightPanel.id);
            if (panelData) {
                if (panelData.isCollapsed) {
                    rightWidth = '24px';
                } else {
                    // Only use offsetWidth if it's been calculated (> 0), otherwise use default
                    const calculatedWidth = rightPanel.offsetWidth;
                    rightWidth = calculatedWidth > 0 ? `${calculatedWidth}px` : '260px';
                }
            }
        }
        
        if (bottomPanel) {
            const panelData = this.panels.get(bottomPanel.id);
            if (panelData) {
                if (panelData.isCollapsed) {
                    bottomHeight = '24px';
                } else {
                    // Only use offsetHeight if it's been calculated (> 0), otherwise use default
                    const calculatedHeight = bottomPanel.offsetHeight;
                    bottomHeight = calculatedHeight > 0 ? `${calculatedHeight}px` : '300px';
                }
            }
            const nodegraph = document.getElementById('node-graph');
            if (nodegraph && typeof nodegraph.handleResize === 'function') {            
                nodegraph.handleResize();
            }
        }
        
        appLayout.style.gridTemplateColumns = `${leftWidth} 1fr ${rightWidth}`;
        appLayout.style.gridTemplateRows = `1fr ${bottomHeight}`;
        
        if (rightPanel && rightPanel.offsetWidth === 0) {
            // Force a reflow to ensure the right panel gets proper dimensions
//            rightPanel.style.minWidth = '300px';
//            rightPanel.offsetHeight; // Force reflow
        }
    }
    
    togglePanel(panelId) {
        const panelData = this.panels.get(panelId);
        if (!panelData) return;
        
        panelData.isCollapsed = !panelData.isCollapsed;
        panelData.element.classList.toggle('collapsed', panelData.isCollapsed);
        
        this.updateGridTemplate();
        this.savePanelSizes();
        
        // Emit resize event for components
        setTimeout(() => {
            window.dispatchEvent(new Event('resize'));
        }, 300);
    }
    
    expandPanel(panelId) {
        const panelData = this.panels.get(panelId);
        if (!panelData || !panelData.isCollapsed) return;
        
        this.togglePanel(panelId);
    }
    
    collapsePanel(panelId) {
        const panelData = this.panels.get(panelId);
        if (!panelData || panelData.isCollapsed) return;
        
        this.togglePanel(panelId);
    }
    
    setPanelWidth(panelId, width) {
        const panelData = this.panels.get(panelId);
        if (!panelData) return;
        
        width = Math.max(panelData.minWidth, Math.min(panelData.maxWidth, width));
        panelData.element.style.width = `${width}px`;
        
        this.updateGridTemplate();
        this.savePanelSizes();
    }
    
    handleResize() {
        // Adjust panel sizes for responsive design
        const windowWidth = window.innerWidth;
        
        if (windowWidth < 768) {
            // Mobile layout
            this.switchToMobileLayout();
        } else if (windowWidth < 1200) {
            // Tablet layout
            this.switchToTabletLayout();
        } else {
            // Desktop layout
            this.switchToDesktopLayout();
        }
        
        this.updateGridTemplate();
    }
    
    switchToMobileLayout() {
        const appLayout = document.querySelector('.app-layout');
        if (appLayout) {
            appLayout.style.gridTemplateColumns = '1fr';
            appLayout.style.gridTemplateRows = 'auto auto 1fr';
        }
        
        // Collapse panels on mobile
        this.panels.forEach((panelData, panelId) => {
            if (!panelData.isCollapsed) {
                panelData.element.style.height = '200px';
            }
        });
    }
    
    switchToTabletLayout() {
        const appLayout = document.querySelector('.app-layout');
        if (appLayout) {
            appLayout.style.gridTemplateColumns = '180px 1fr 250px';
            appLayout.style.gridTemplateRows = '1fr';
        }
        
        // Adjust panel widths for tablet
        this.panels.forEach((panelData, panelId) => {
            if (panelData.element.classList.contains('left-panel')) {
                panelData.element.style.width = '180px';
            } else if (panelData.element.classList.contains('right-panel')) {
                panelData.element.style.width = '250px';
            }
        });
    }
    
    switchToDesktopLayout() {
        const appLayout = document.querySelector('.app-layout');
        if (appLayout) {
            appLayout.style.gridTemplateColumns = '';
            appLayout.style.gridTemplateRows = '';
        }
        
        // Restore saved panel sizes
        this.loadPanelSizes();
    }
    
    savePanelSizes() {
        const sizes = {};
        
        this.panels.forEach((panelData, panelId) => {
            sizes[panelId] = {
                width: panelData.element.offsetWidth,
                height: panelData.element.offsetHeight,
                isCollapsed: panelData.isCollapsed
            };
        });
        
        localStorage.setItem('octaneWeb.panelSizes', JSON.stringify(sizes));
    }
    
    loadPanelSizes() {
        try {
            const saved = localStorage.getItem('octaneWeb.panelSizes');
            if (!saved) return;
            
            const sizes = JSON.parse(saved);
            
            Object.entries(sizes).forEach(([panelId, size]) => {
                const panelData = this.panels.get(panelId);
                if (panelData) {
                    panelData.element.style.width = `${size.width}px`;
                    panelData.isCollapsed = size.isCollapsed;
                    panelData.element.classList.toggle('collapsed', size.isCollapsed);
                }
            });
            
            this.updateGridTemplate();
            
        } catch (error) {
            console.error('Failed to load panel sizes:', error);
        }
    }
    
    resetLayout() {
        // Reset all panels to default sizes
        this.panels.forEach((panelData, panelId) => {
            panelData.element.style.width = `${panelData.defaultWidth}px`;
            panelData.element.style.height = '';
            panelData.isCollapsed = false;
            panelData.element.classList.remove('collapsed');
        });
        
        this.updateGridTemplate();
        
        // Clear saved sizes
        localStorage.removeItem('octaneWeb.panelSizes');
        
        // Emit resize event
        setTimeout(() => {
            window.dispatchEvent(new Event('resize'));
        }, 100);
    }
    
    generateId() {
        return `panel_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
    }
    
    destroy() {
        // Remove event listeners
        document.removeEventListener('mousemove', this.handleMouseMove);
        document.removeEventListener('mouseup', this.handleMouseUp);
        window.removeEventListener('resize', this.handleResize);
        
        // Remove splitters
        this.splitters.forEach((splitterData) => {
            splitterData.element.remove();
        });
        
        this.panels.clear();
        this.splitters.clear();
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = LayoutManager;
} else if (typeof window !== 'undefined') {
    window.LayoutManager = LayoutManager;
}