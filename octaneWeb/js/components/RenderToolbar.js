/**
 * RenderToolbar.js - Octane-style render toolbar component
 * Matches the native Octane interface with live render statistics and comprehensive icon toolbar
 */

class RenderToolbar {
    constructor(containerId) {
        this.container = document.getElementById(containerId);
        this.renderStats = {
            samples: 0,
            time: '00:00:00',
            status: 'finished',
            resolution: '1920x1080',
            meshCount: 1,
            gpu: 'NVIDIA GeForce RTX 4090 (RT)',
            version: '1.48.21.224.4',
            memory: 'GB'
        };
        
        this.init();
    }
    
    init() {
        this.createRenderStatsBar();
        this.createRenderToolbar();
        this.updateRenderStats();
    }
    
    createRenderStatsBar() {
        const statsBar = document.createElement('div');
        statsBar.className = 'render-stats-bar';
        statsBar.innerHTML = `
            <div class="render-stats-left">
                <span id="render-samples-display">${this.renderStats.samples} spp</span>
                <span class="stats-separator">,</span>
                <span id="render-time-display">${this.renderStats.time}</span>
                <span id="render-status-display">(${this.renderStats.status})</span>
            </div>
            <div class="render-stats-right">
                <span id="render-resolution-display">${this.renderStats.resolution}</span>
                <span id="render-mesh-count">${this.renderStats.meshCount} mesh</span>
                <span class="stats-separator">,</span>
                <span id="render-gpu-info">${this.renderStats.gpu}</span>
                <span class="stats-separator">,</span>
                <span id="render-version">${this.renderStats.version}</span>
                <span id="render-memory">${this.renderStats.memory}</span>
            </div>
        `;
        
        this.container.appendChild(statsBar);
    }
    
    createRenderToolbar() {
        const toolbar = document.createElement('div');
        toolbar.className = 'render-toolbar';
        
        // Create the comprehensive icon toolbar matching Octane's layout
        const toolbarIcons = this.createToolbarIcons();
        toolbar.appendChild(toolbarIcons);
        
        this.container.appendChild(toolbar);
    }
    
    createToolbarIcons() {
        const iconsContainer = document.createElement('div');
        iconsContainer.className = 'render-toolbar-icons';
        
        // Define the toolbar icons in order (matching Octane's interface exactly)
        const icons = [
            { id: 'center-image', icon: '⌖', tooltip: 'Centers the rendered image in the viewport. Use control to also reset the zoom.' },
            { id: 'reset-camera', icon: '⌂', tooltip: 'Resets the camera to its initial position and target.' },
            { id: 'camera-preset', icon: '▣', tooltip: 'Presets the camera to a pre-defined viewport.' },
            { id: 'stop-render', icon: '■', tooltip: 'Stops the current render.', important: true },
            { id: 'restart-render', icon: '↻', tooltip: 'Restarts the current render.', important: true },
            { id: 'toggle-realtime', icon: '▶', tooltip: 'Toggle real-time rendering.', important: true },
            { id: 'fit-resolution', icon: '⊡', tooltip: 'Modifies the resolution of the rendered image to fit the dimension of the render viewport.' },
            { id: 'focus-picker', icon: '◎', tooltip: 'Toggles the camera focus picker of the render viewport.' },
            { id: 'separator-1', type: 'separator' },
            { id: 'white-point-picker', icon: '◯', tooltip: 'Toggles the image white point picker of the render viewport.' },
            { id: 'material-picker', icon: '●', tooltip: 'Toggles the material picker of the render viewport.' },
            { id: 'object-picker', icon: '▢', tooltip: 'Toggles the object picker of the render viewport.' },
            { id: 'camera-target-picker', icon: '⊙', tooltip: 'Toggles the camera target picker of the render viewport.' },
            { id: 'white-point-picker-2', icon: '○', tooltip: 'Toggles the image white point picker of the render viewport.' },
            { id: 'render-region-lasso', icon: '◊', tooltip: 'Toggles the render region lasso in the render viewport.' },
            { id: 'render-region-lasso-2', icon: '◈', tooltip: 'Toggles the render region lasso in the render viewport.' },
            { id: 'film-region-lasso', icon: '▭', tooltip: 'Toggles the film region lasso in the render viewport.' },
            { id: 'separator-2', type: 'separator' },
            { id: 'clay-mode', icon: '◐', tooltip: 'The clay mode that should be used for rendering.' },
            { id: 'subsample-mode', icon: '▦', tooltip: 'The subsample mode that should be used for rendering.' },
            { id: 'render-priority', icon: '⚡', tooltip: 'Render priority that should be used for rendering.' },
            { id: 'separator-3', type: 'separator' },
            { id: 'copy-render', icon: '⧉', tooltip: 'Copies the current render to the clipboard.' },
            { id: 'save-render', icon: '💾', tooltip: 'Saves the current render to the disk.' },
            { id: 'separator-4', type: 'separator' },
            { id: 'export-passes', icon: '⊞', tooltip: 'Shows a dialog to export the render passes.' },
            { id: 'change-background', icon: '▨', tooltip: 'Shows a dialog to change the background of the render viewport.' },
            { id: 'color-correction', icon: '◑', tooltip: 'Color correction' },
            { id: 'separator-5', type: 'separator' },
            { id: 'export-image', icon: '⇪', tooltip: 'Export image' },
            { id: 'export-animation', icon: '⊟', tooltip: 'Export animation' },
            { id: 'batch-render', icon: '▤', tooltip: 'Batch render' },
            { id: 'separator-6', type: 'separator' },
            { id: 'help', icon: '?', tooltip: 'Help' },
            { id: 'about', icon: 'i', tooltip: 'About' }
        ];
        
        icons.forEach(iconData => {
            if (iconData.type === 'separator') {
                const separator = document.createElement('div');
                separator.className = 'toolbar-separator';
                iconsContainer.appendChild(separator);
            } else {
                const button = document.createElement('button');
                button.className = `toolbar-icon-btn ${iconData.important ? 'important' : ''}`;
                button.id = iconData.id;
                button.innerHTML = iconData.icon;
                button.title = iconData.tooltip;
                button.addEventListener('click', () => this.handleToolbarAction(iconData.id));
                iconsContainer.appendChild(button);
            }
        });
        
        return iconsContainer;
    }
    
    handleToolbarAction(actionId) {
        console.log(`Toolbar action: ${actionId}`);
        
        // Handle specific render control actions
        switch (actionId) {
            case 'center-image':
                this.centerImage();
                break;
            case 'reset-camera':
                this.resetCamera();
                break;
            case 'camera-preset':
                this.showCameraPresets();
                break;
            case 'stop-render':
                this.stopRender();
                break;
            case 'restart-render':
                this.restartRender();
                break;
            case 'toggle-realtime':
                this.toggleRealtimeRendering();
                break;
            case 'fit-resolution':
                this.fitResolution();
                break;
            case 'focus-picker':
                this.toggleFocusPicker();
                break;
            case 'white-point-picker':
            case 'white-point-picker-2':
                this.toggleWhitePointPicker();
                break;
            case 'material-picker':
                this.toggleMaterialPicker();
                break;
            case 'object-picker':
                this.toggleObjectPicker();
                break;
            case 'camera-target-picker':
                this.toggleCameraTargetPicker();
                break;
            case 'render-region-lasso':
            case 'render-region-lasso-2':
                this.toggleRenderRegionLasso();
                break;
            case 'film-region-lasso':
                this.toggleFilmRegionLasso();
                break;
            case 'clay-mode':
                this.toggleClayMode();
                break;
            case 'subsample-mode':
                this.toggleSubsampleMode();
                break;
            case 'render-priority':
                this.toggleRenderPriority();
                break;
            case 'copy-render':
                this.copyRenderToClipboard();
                break;
            case 'save-render':
                this.saveRenderToDisk();
                break;
            case 'export-passes':
                this.showExportPassesDialog();
                break;
            case 'change-background':
                this.showChangeBackgroundDialog();
                break;
            case 'zoom-fit':
                this.zoomToFit();
                break;
            case 'zoom-in':
                this.zoomIn();
                break;
            case 'zoom-out':
                this.zoomOut();
                break;
            default:
                // Placeholder for other actions
                console.log(`Action ${actionId} not yet implemented`);
        }
    }
    
    // Viewport control methods
    centerImage() {
        console.log('Centering rendered image in viewport...');
        // TODO: Integrate with viewport to center image and optionally reset zoom with Ctrl
    }
    
    resetCamera() {
        console.log('Resetting camera to initial position and target...');
        // TODO: Integrate with Octane API to reset camera
    }
    
    showCameraPresets() {
        console.log('Showing camera presets...');
        // TODO: Show camera preset menu/dialog
    }
    
    // Render control methods
    stopRender() {
        console.log('Stopping render...');
        this.updateRenderStatus('stopped');
        // TODO: Integrate with Octane API
    }
    
    restartRender() {
        console.log('Restarting render...');
        this.updateRenderStatus('rendering');
        // TODO: Integrate with Octane API
    }
    
    toggleRealtimeRendering() {
        console.log('Toggling real-time rendering...');
        // Toggle between real-time and manual rendering modes
        const isRealtime = this.renderStats.status === 'rendering';
        if (isRealtime) {
            this.updateRenderStatus('paused');
        } else {
            this.updateRenderStatus('rendering');
        }
        // TODO: Integrate with Octane API
    }
    
    fitResolution() {
        console.log('Fitting resolution to viewport dimensions...');
        // TODO: Modify render resolution to fit viewport
    }
    
    toggleFocusPicker() {
        console.log('Toggling camera focus picker...');
        // TODO: Enable/disable focus picker tool
    }
    
    // Picker tools
    toggleWhitePointPicker() {
        console.log('Toggling image white point picker...');
        // TODO: Enable/disable white point picker tool
    }
    
    toggleMaterialPicker() {
        console.log('Toggling material picker...');
        // TODO: Enable/disable material picker tool
    }
    
    toggleObjectPicker() {
        console.log('Toggling object picker...');
        // TODO: Enable/disable object picker tool
    }
    
    toggleCameraTargetPicker() {
        console.log('Toggling camera target picker...');
        // TODO: Enable/disable camera target picker tool
    }
    
    // Region tools
    toggleRenderRegionLasso() {
        console.log('Toggling render region lasso...');
        // TODO: Enable/disable render region lasso tool
    }
    
    toggleFilmRegionLasso() {
        console.log('Toggling film region lasso...');
        // TODO: Enable/disable film region lasso tool
    }
    
    // Render modes
    toggleClayMode() {
        console.log('Toggling clay mode for rendering...');
        // TODO: Toggle clay rendering mode
    }
    
    toggleSubsampleMode() {
        console.log('Toggling subsample mode for rendering...');
        // TODO: Toggle subsample rendering mode
    }
    
    toggleRenderPriority() {
        console.log('Toggling render priority...');
        // TODO: Toggle render priority settings
    }
    
    // Render output actions
    copyRenderToClipboard() {
        console.log('Copying current render to clipboard...');
        // TODO: Copy render image to system clipboard
    }
    
    saveRenderToDisk() {
        console.log('Saving current render to disk...');
        // TODO: Save render image to file
    }
    
    // Dialog actions
    showExportPassesDialog() {
        console.log('Showing export render passes dialog...');
        // TODO: Show dialog to export render passes
    }
    
    showChangeBackgroundDialog() {
        console.log('Showing change background dialog...');
        // TODO: Show dialog to change render viewport background
    }
    
    // Additional viewport control methods
    zoomToFit() {
        console.log('Zoom to fit');
        // TODO: Integrate with viewport
    }
    
    zoomIn() {
        console.log('Zoom in');
        // TODO: Integrate with viewport
    }
    
    zoomOut() {
        console.log('Zoom out');
        // TODO: Integrate with viewport
    }
    
    // Update methods
    updateRenderStats(stats = {}) {
        this.renderStats = { ...this.renderStats, ...stats };
        
        // Update DOM elements
        const samplesEl = document.getElementById('render-samples-display');
        const timeEl = document.getElementById('render-time-display');
        const statusEl = document.getElementById('render-status-display');
        const resolutionEl = document.getElementById('render-resolution-display');
        const meshCountEl = document.getElementById('render-mesh-count');
        const gpuInfoEl = document.getElementById('render-gpu-info');
        const versionEl = document.getElementById('render-version');
        const memoryEl = document.getElementById('render-memory');
        
        if (samplesEl) samplesEl.textContent = `${this.renderStats.samples} spp`;
        if (timeEl) timeEl.textContent = this.renderStats.time;
        if (statusEl) statusEl.textContent = `(${this.renderStats.status})`;
        if (resolutionEl) resolutionEl.textContent = this.renderStats.resolution;
        if (meshCountEl) meshCountEl.textContent = `${this.renderStats.meshCount} mesh`;
        if (gpuInfoEl) gpuInfoEl.textContent = this.renderStats.gpu;
        if (versionEl) versionEl.textContent = this.renderStats.version;
        if (memoryEl) memoryEl.textContent = this.renderStats.memory;
    }
    
    updateRenderStatus(status) {
        this.renderStats.status = status;
        const statusEl = document.getElementById('render-status-display');
        if (statusEl) {
            statusEl.textContent = `(${status})`;
            statusEl.className = `render-status-${status}`;
        }
    }
    
    // Integration methods for external updates
    onRenderProgress(samples, time) {
        this.updateRenderStats({
            samples: samples,
            time: time,
            status: 'rendering'
        });
    }
    
    onRenderComplete(samples, time) {
        this.updateRenderStats({
            samples: samples,
            time: time,
            status: 'finished'
        });
    }
    
    onRenderError(error) {
        this.updateRenderStats({
            status: 'error'
        });
        console.error('Render error:', error);
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = RenderToolbar;
}